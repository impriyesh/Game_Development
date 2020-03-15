// A Backtracking program in C++ to solve Sudoku problem 
#include <bits/stdc++.h> 
using namespace std;
// UNASSIGNED is used for empty cells in sudoku grid 
#define UNASSIGNED 0 

// N is used for the size of Sudoku grid. 
// Size will be NxN 
#define N 9 


// write a c++ class for sudoku solver
class SolveSudoku {

public:
	SolveSudoku(vector<vector<int>> &grid ) {
		for(int i=0; i< grid.size();i++)
			for(int j=0;j<grid[0].size();j++)
				m_grid[i][j] = grid[i][j];
	}
// This function finds an entry in grid 
// that is still unassigned 
	const bool FindUnassignedLocation(int &row, int &col) const;
// Checks whether it will be legal
// to assign num to the given row, col 
	const bool isSafe(int row,
			int col, int num) const;
/* Takes a partially filled-in grid and attempts
	to assign values to all unassigned locations in
	such a way to meet the requirements for
	Sudoku solution (non-duplication across rows,
	columns, and boxes) */
	bool SolveSudoku_();

/* Returns a boolean which indicates whether
	an assigned entry in the specified row matches
	the given number. */
	const bool UsedInRow(int row, int num) const;

/* Returns a boolean which indicates whether
	an assigned entry in the specified column
	matches the given number. */
  const	bool UsedInCol(int col, int num) const;

/* Returns a boolean which indicates whether
	an assigned entry within the specified 3x3 box
	matches the given number. */
  const bool UsedInBox(int boxStartRow, int boxStartCol, int num) const;

	/* A utility function to print grid */
	const void printGrid() const;

private:
	vector<vector<int>> m_grid;


};
/* Takes a partially filled-in grid and attempts
to assign values to all unassigned locations in
such a way to meet the requirements for
Sudoku solution (non-duplication across rows,
columns, and boxes) */
bool SolveSudoku::SolveSudoku_()
{
	int row =0 , col = 0;

	// If there is no unassigned location, 
	// we are done 
	if (!FindUnassignedLocation(row, col))
		return true; // success! 

		// consider digits 1 to 9 
	for (int num = 1; num <= 9; num++)
	{
		// if looks promising 
		if (isSafe(row, col, num))
		{
			// make tentative assignment 
			m_grid[row][col] = num;

			// return, if success, yay! 
			if (SolveSudoku_())
				return true;

			// failure, unmake & try again 
			m_grid[row][col] = UNASSIGNED;
		}
	}
	return false; // this triggers backtracking 
}

/* Searches the grid to find an entry that is
still unassigned. If found, the reference
parameters row, col will be set the location
that is unassigned, and true is returned.
If no unassigned entries remain, false is returned. */
const bool SolveSudoku::FindUnassignedLocation(int &row, int &col) const
{
	for (row = 0; row < N; row++)
		for (col = 0; col < N; col++)
			if (m_grid[row][col] == UNASSIGNED)
				return true;
	return false;
}

/* Returns a boolean which indicates whether
an assigned entry in the specified row matches
the given number. */
const bool SolveSudoku::UsedInRow(int row, int num) const
{
	for (int col = 0; col < N; col++)
		if (m_grid[row][col] == num)
			return true;
	return false;
}

/* Returns a boolean which indicates whether
an assigned entry in the specified column
matches the given number. */
const bool SolveSudoku::UsedInCol(int col, int num) const
{
	for (int row = 0; row < N; row++)
		if (m_grid[row][col] == num)
			return true;
	return false;
}

/* Returns a boolean which indicates whether
an assigned entry within the specified 3x3 box
matches the given number. */
const bool SolveSudoku::UsedInBox(int boxStartRow, int boxStartCol, int num) const
{
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (m_grid[row + boxStartRow]
				[col + boxStartCol] == num)
				return true;
	return false;
}

/* Returns a boolean which indicates whether
it will be legal to assign num to the given
row, col location. */
const bool SolveSudoku::isSafe(int row,int col, int num) const
{
	/* Check if 'num' is not already placed in
	current row, current column and current 3x3 box */
	return !UsedInRow(row, num) &&
		!UsedInCol(col, num) &&
		!UsedInBox(row - row % 3,
			col - col % 3, num) &&
		m_grid[row][col] == UNASSIGNED;
}

/* A utility function to print grid */
const void SolveSudoku::printGrid() const
{
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
			cout << m_grid[row][col] << " ";
		cout << endl;
	}
}

// Driver Code 
int main()
{

	// 0 means unassigned cells 
	vector<vector<int>> grid = { 
					{0, 9, 0, 0, 8, 0, 0, 0, 4},
					{1, 0, 8, 4, 3, 2, 0, 6, 0},
					{0, 0, 0, 1, 7, 0, 8, 5, 2},
					{6, 0, 0, 9, 0, 0, 5, 2, 0},
					{0, 1, 0, 0, 0, 0, 0, 4, 0},
					{0, 2, 9, 0, 0, 5, 0, 0, 6},
					{2, 3, 0, 0, 9, 4, 0, 0, 0},
					{0, 4, 0, 3, 5, 1, 2, 0, 7},
					{9, 0, 0, 0, 6, 0, 0, 3, 0}					
			
	};
	SolveSudoku s(grid);
	if (s.SolveSudoku_() == true)
		s.printGrid();
	else
		cout << "No solution exists";

	getchar();
	return 0;
}

// This is code is contributed by rathbhupendra 
