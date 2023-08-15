/*
Author Name: Nicholas Grzyb
File Name: SudokuSolver.hpp
Date Created/Modified: 5/1/2023

Interface of the SudokuSolver class
*/



#ifndef SUDOKU_SOLVER_HPP_
#define SUDOKU_SOLVER_HPP_
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


//We define Location within the Sudoku namespace.
//To use Location, you must specify the namespace Sudoku::Location
//Just like you do when using the standard namespace std::
namespace Sudoku
{ 
  struct Location
  {
    int row;
    int col;
  };
}

class SudokuSolver
{
public:
 
//Add your public members here
SudokuSolver();
SudokuSolver(std::string input_file);
bool isPuzzleSolvable();
void setSolvable();
int** getPuzzleNumbers();
void setPuzzleNumbers(int** puzzle); 
Sudoku::Location returnNextEmpty();
bool checkLegalValue(int value, Sudoku::Location location);
void display();





private:
//Add your private members here
const int SIZE = 9;
int** board;
bool is_solvable_;
bool solveSudoku();
};

#endif
