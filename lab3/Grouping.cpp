/*
 * Name: Nathan Goller-Deitsch
 * Date Submitted: 2/7/2023
 * Lab Section: 001
 * Assignment Name: Lab 3: Finding Groups Using Recursion
 */

#include "Grouping.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Implement the (parameterized) constructor and findGroup functions below

Grouping::Grouping(string filename)
{

    ifstream infile(filename);
    char c;
    int currentRow = 0;
    int currentCol = 0;

    // while we are getting characters
    while (infile.get(c))
    {
        // if the character is valid
        if (c == '.' || c == 'X')
        {
            if (c == '.')
            {
                // if the character is a . set the grid pos to 0
                grid[currentRow][currentCol] = 0;
            }
            else
            {
                // otherwise set grid pos to 1
                grid[currentRow][currentCol] = 1;
            }

            // update the current column, moving to the next row if we have exceeded 10
            currentCol = (currentCol + 1);
            if (currentCol > 9)
            {
                currentCol = 0;
                currentRow++;
            }
        }
    }
}

void Grouping::findGroup(int r, int c)
{
    // check all neighbors to find cells that we should group with

    // this cell
    GridSquare thisCell(r, c);

    // stop if this cell is not filled in
    if (grid[r][c] == 0)
    {
        return;
    }

    // stop if this cell is already a member of the temporary group
    for (GridSquare groupMember : tmpGroup)
    {
        if (groupMember == thisCell)
        {
            return;
        }
    }

    // add this cell to the temporary group, then check its neighbors
    tmpGroup.push_back(thisCell);

    // check left neighbor
    if (c > 0){findGroup(r, (c - 1));}

    // check right neighbor
    if (c < 9){findGroup(r, (c + 1));}

    // check top neighbor
    if (r > 0){findGroup((r - 1), c);}

    // check bottom neighbor
    if (r < 9){findGroup((r + 1), c);}
}

// Simple main function to test Grouping
// Be sure to comment out main() before submitting
/* int main()
{
    Grouping input1("input1.txt");
    input1.getGroups();
    input1.printGroups();
    return 0;
} */

// Do not modify anything below

GridSquare::GridSquare() : row(0), col(0) {} // Default constructor, (0,0) square

GridSquare::GridSquare(int r, int c) : row(r), col(c) {} //(r,c) square

// Compare with == operator, used in test cases
bool GridSquare::operator==(const GridSquare r) const
{
    if ((row == r.row) && (col == r.col))
    {
        return true;
    }
    return false;
}

int GridSquare::getRow() // return row value
{
    return row;
}

int GridSquare::getCol() // return column value
{
    return col;
}

// Output using << operator, used in Grouping::printGroups()
// Function definition for <ostream> << <GridSquare>
ostream &operator<<(ostream &os, const GridSquare obj)
{
    os << "(" << obj.row << "," << obj.col << ")";
    return os;
}

Grouping::Grouping() {} // Default constructor, no groups

void Grouping::printGroups() // Displays grid's groups of squares
{
    for (int g = 0; g < groups.size(); g++)
    {
        cout << "Group " << g + 1 << ": ";
        for (int s = 0; s < groups[g].size(); s++)
        {
            cout << " " << groups[g][s];
        }
        cout << endl;
    }
}

void Grouping::finalizeTmpGroup()
{
    if (!tmpGroup.empty())
    {
        groups.push_back(tmpGroup);
        while (!tmpGroup.empty())
        {
            tmpGroup.pop_back();
        }
    }
}
vector< vector<GridSquare> > Grouping::getGroups() // Needed in unit tests
{

    // for each cell...
    for (int i = 0; i <= 9; i++)
    {
        for (int j = 0; j <= 9; j++)
        {
            // the cell should be skipped if it is a member of a group already
            bool shouldSkipThisCell = false;
            
            // search groups to find this cell
            for (vector<GridSquare> group : groups)
            {
                for (GridSquare groupMember : group)
                {
                    if (groupMember == GridSquare(i, j))
                    {
                        // if we found this cell in a group, set the skip flag to true
                        shouldSkipThisCell = true;
                    }
                }
            }

            // otherwise, add this cell (and all of its neighbors, recursively) to a tmp group and move it into the permanent groups list
            if (!shouldSkipThisCell)
            {
                findGroup(i, j);
                finalizeTmpGroup();
            }
        }
    }

    return groups;
}