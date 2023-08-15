/*
Author Name: Nicholas Grzyb
File Name: SudokuSolver.cpp
Date Created/Modified: 5/1/2023

Implementation of the SudokuSolver class
*/


#include "SudokuSolver.hpp"
/*
the default constructor initializes an emtpy board, that is, a board filled with zeros (an array of 9 arrays, each filled with 9 zeros). This board will be marked unsolvable. 
*/
SudokuSolver::SudokuSolver(){
    // dynamically create an array of pointers of size `M`
    board = new int*[SIZE];
 
    // dynamically allocate memory of size `N` for each row
    for (int i = 0; i < SIZE; i++) {
        board[i] = new int[SIZE];
    }
 
    // assign values to the allocated memory
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0;
        }
    }
    }
/*
the parameterized constructor reads the input file to initialize the board. The input files consist of 9 digits on each row separated by commas, and 9 rows separated by new line characters \n, corresponding to a sudoku board. Empty squares contain the digit 0. After reading the puzzle, the constructor tries to solve it and records whether the puzzle has a solution or not.
*/
SudokuSolver::SudokuSolver(std::string input_file){
    int row=0;
    int col=0;
    std::string num;
    board = new int*[SIZE];
    for (int i = 0; i < SIZE; i++) {
        board[i] = new int[SIZE];
    }

      std::ifstream infill(input_file); 
      std::string line;
      while(getline(infill,line)){
        col=0;
        std::istringstream reading(line);
        while(getline(reading,num,',')){
            board[row][col]=atoi(num.c_str());
            col++;
        }
        row++;
      } 

      is_solvable_=solveSudoku();
 }
/*
returns true if the puzzle is solvable, false otherwise
*/
bool SudokuSolver::isPuzzleSolvable(){
        return is_solvable_;
    }
/*
records the puzzle as being solvable.
*/
void SudokuSolver::setSolvable(){
       is_solvable_ = true;
}
/*
returns the  2D pointer array representing the puzzle
*/
int** SudokuSolver::getPuzzleNumbers(){
        return board;
}
/*
sets the  2D pointer array representing the puzzle to the value of the parameter 
*/
void SudokuSolver::setPuzzleNumbers(int** puzzle) {
        board = puzzle;
    }
/*
will display the board as illustrated below: 

Example:

N X X  | N X N  | X X N

N X N  | X N N  | X X X

N X N  | N X X  | X X X

- - - - - - - - - - - - 

X N X  | N X N  | N X X

X X X  | X N X  | X X X

X X N  | N X N  | X N X

- - - - - - - - - - - - 

X X X  | X X N  | N X N

X X X  | N N X  | N X N

N X X  | N X N  | X X N
*/
void SudokuSolver::display(){
     for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (j == 0) {
                std::cout << " ";
            }
            else if ((j % 3) == 0) {
                std::cout << " | ";
            }
           if(j == 8){
            if(board[i][j] == 0){
                std::cout<<"X";
            }else{
                std::cout<<board[i][j];
            }
           }else{
            if(board[i][j] == 0){
                std::cout<<"X ";
            }else{
                std::cout<<board[i][j]<<" ";
            }
           }
            
        }
        if ((i + 1) % 3 == 0 && i != 8){
            std::cout << std::endl << "- - - - - - - - - - - -";
        }
        std::cout << std::endl;
     }
   }
/*
returns true if the value parameter (which can take on values 1-9) can legally be placed at the given location in the 2D array without breaking the rules of sudoku. It returns false if placing value at location is not a legal move
*/
 bool SudokuSolver::checkLegalValue(int value, Sudoku::Location location){
    int r = location.row;
    int c = location.col;
    int gridx = (r/3)*3;
    int gridy = (c/3)*3;
    
    for (int i = 0; i < 9; i++) {
        if (board[r][i] == value || board[i][c] == value) {
            return false;
        }
    }

    for (int i = gridx; i < gridx + 3; i++) {
        for (int j = gridy; j < gridy+ 3; j++) {
            if (board[i][j] == value) {
                return false;
            }
        }
    }

    return true;
   }
/*
returns a Location object with the coordinates of the first 0 found in the 2D pointer array, meaning that it is an empty square in the sudoku board. To find the first empty square you must read the 2D array from top-left (0,0) to bottom right (8,8), one row at a time. Set the row and col of the Location to the indices at which the first 0 is found in the 2D array. If there are no empty squares the Location object should have row and col values of -1.
*/
 Sudoku::Location SudokuSolver::returnNextEmpty(){
       Sudoku::Location locate;
        locate.row = -1;
        locate.col = -1;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == 0) {
                    locate.row = i;
                    locate.col = j;
                    return locate;
                }
            }
        }
        return locate;
    }
/*
helper functions that actually solves the sudoku puzzles
Solves it by backtracking
*/
bool SudokuSolver::solveSudoku(){
   Sudoku::Location low = returnNextEmpty();
   if (low.row==-1 && low.col==-1)
      return true; //when all places are filled
   for (int num = 1; num <= 9; num++){ //valid numbers are 1 - 9
      if (checkLegalValue(num,low)){ //check validation, if yes, put the number in the grid
         board[low.row][low.col] = num;
         if (solveSudoku()) //recursively go for other rooms in the grid
            return true;
         board[low.row][low.col] = 0; //turn to unassigned space when conditions are not satisfied
      }
   }
   return false;
}