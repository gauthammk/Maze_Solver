//
//  main.cpp
//  mazeSolver
//
//  Created by Team Thunder Idlis on 02/10/18.
//  Copyright © 2018 Team Thunder Idlis. All rights reserved.
//

//headers
#include <iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;
//class definition of class maze
class maze{
	int n,m;
	//2d array mat will hold the nxm maze matrix
	int mat[100][100],tempmat[100][100];
public:
	//methods are defined
	void matCopy();
	void mazeInput();
	bool findEnd(int&,int&);
	bool findStart(int&,int&);
	bool solveMazeUtil(int,int,int,int);
	void solveMaze();
	void printmat();
}mazeob;
	//object of class maze called mazeob is created
	//matCopy() function is used to copy the originial maze into the variable tempmat since the original matrix mat will undergo change during path finding	
void maze::matCopy(){
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++)
			tempmat[i][j]=mat[i][j];
	}
}
	//mazeInput() function is used to read the maze matrix from a data file
void maze::mazeInput(){
	fstream file;
	char ch,fileName[50],str[100];
	int count=0,tot;
	a:
	//the name of the data file is being accepted here
	cout<<"\nEnter the file name: (with file extension)";
	cin>>fileName;
	//the file bufffer is created and the file is connected through the file object 'file'
	file.open(fileName,ios::in|ios::out);
	//checking if the file exists
	if(file.good()){
		//matrix dimensions are accepted
		file.getline(str,100);
		m=(strlen(str)+1)/2;
		file.seekg(0);
		while(!file.eof()){
			file>>tot;
			count++;
		}
		n=count/m;
		cout<<"\nDimensions: "<<n<<" "<<m;
		//file pointer is placed at the beginning of the file
		file.close();
		file.open(fileName,ios::in|ios::out);
		//matrix is read from the file
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				file>>mat[i][j];
			}
		}
	//the matrix that is read is printed as is
		cout<<"\nPrinting matrix read from file: \n";
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++)
				cout<<mat[i][j]<<" ";
			cout<<"\n";
		}
	}
	//in case the file is not found error message is displayed and file is re entered
	else {
		cout<<"\nFatal error occurred while opening file. Please check if the file exists.\n";
		cout<<"\nDo you want to try again?: (y/n)";
		cin>>ch;
		if(ch=='y'||ch=='Y')
			goto a;
		else if(ch=='n'||ch=='N'){
			cout<<"\nQuittting...\n";
			exit(0);
		}
		else {
			cout<<"\nWrong character entered.";
			goto a;
		}
	}
	file.close();
}
	//findEnd() function is used to find the co-ordinates of the ending point in the matrix 
bool maze::findEnd(int &x,int &y){
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(mat[i][j]==4){
				x=i;
				y=j;
				return true;
			}
		}
	}
	cout<<"\nEnding position not found.";
	return false;
}
	//findStart() function is used to find the co-ordinates of the starting point in the matrix 
bool maze::findStart(int &x,int &y){
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(mat[i][j]==3){
				x=i;
				y=j;
				return true;
			}
		}
	}
		cout<<"\nStarting position not found.";
		return false;
}
	//this function solveMazeUtil() is the main working part of the code and solves the maze
bool maze::solveMazeUtil(int x,int y,int p,int q){
	//checking if the starting point is within bounds of the matrix
	if(x<0 || x>(n-1) || y<0 || y>(m-1)){
		return false;
	}
	//checking and assigning the path value if the starting point is the same as the ending point
	if(x==p && y==q){
		mat[x][y]=2;
		return true;
	}
	//checking if the current position is a wall or a path
	if(mat[x][y]!=1)
		return false;
	//assuming and assigning the value of the current position as a part of the path, will backtrack later
	mat[x][y]=2;
	//recursively checking if the position to  the bottom of the current position is part of the solution path
	if(solveMazeUtil(x+1,y,p,q)){
		return true;
	}
	//recursively checking if the position to  the left of the current position is part of the solution path
	if(solveMazeUtil(x,y-1,p,q)){
		return true;
	}
	//recursively checking if the position to  the right of the current position is part of the solution path
	if(solveMazeUtil(x,y+1,p,q)){
		return true;
	}
	//recursively checking if the position to  the top of the current position is part of the solution path
	if(solveMazeUtil(x-1,y,p,q)){
		return true;
	}
	//major part of the backtracking algorithm. Current position is assigned 0 i.e a wall if it is not a part of the solution path and false is returned to show no path exists
		mat[x][y]=0;
		return false;
}
	//solveMaze() function calls the above functions that are needed to solve the maze
void maze::solveMaze(){
	int startX,startY,endX,endY;
	mazeInput();
	matCopy();
	//checking if maze exists with valid start and end points
	if(findStart(startX,startY) && findEnd(endX,endY)){
		mat[startX][startY]=1;
		mat[endX][endY]=1;
		if(solveMazeUtil(startX,startY,endX,endY)){
			cout<<"\nPath exists. Maze solved!!\n";
			printmat();
			cout<<"\n";
		}
		else
			cout<<"\nUnsolvable.\n";
	}
}
//printmat() function prints the solution matrix
void maze::printmat(){
	cout<<"\n\nMaze solution: \n";
	
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			//accounting for change in the original matrix and printing solution matrix
			if(tempmat[i][j]==1 && mat[i][j]!=2)
				mat[i][j]=1;

			if(mat[i][j]==2)
				cout<<". ";
			
			else
			    cout<<mat[i][j]<<" ";
		}
			
		cout<<"\n";
	}
}
//mainScreen() function displays welcome screen messages
void mainScreen(){
	char ch='y';
	cout<<"\n\nHi there fellow enthusiast! Welcome to the maze solver program. Please read the following rules before you continue to input or upload the maze : ";
	cout<<"\n\n\n1.The maze must consist of a matrix of 0s and 1s where each 0 represents a non traversable path and each 1 represents a traversable path.";
	cout<<"\n\n2.The starting position is to be given by the number 3 and the ending by the number 4. ";
	cout<<"\n\n3.Please ensure that a valid .txt file containing the maze corresponding to the above parameters exists in the folder containing this program.\n\n";
	//Accepting multiple maze inputs
	while(ch=='y'||ch=='Y'){
		mazeob.solveMaze();
		b:
		cout<<"\nDo you want to enter more mazes? (y/n)";
		cin>>ch;
	}
	if(ch=='n'||ch=='N')
		cout<<"\nQuitting...\n";
	else{
		cout<<"\nWrong character entered.";
		ch='y';
		goto b;
	}
}
//main function definiftion
int main(){
	mainScreen();
	return 0;
}
