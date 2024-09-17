// Implementation of Maze class
// By Mary Elaine Califf and Dane Iwema

#include "Maze.h"
using namespace std;

Maze::Maze(int rows, int cols)
{
    numRows = rows;
    numColumns = cols;
    int numCells = rows * cols;
    mazeWalls = new CellWalls[numCells];
    mazeWalls[numCells - 1].east = false;
}

Maze &Maze::operator=(const Maze &rhs)
{
    if (this != &rhs)
    {
        delete [] mazeWalls;
        this->copy(rhs);
    }
    return *this;
}

void Maze::generateMaze()
{
    int numCells = numRows * numColumns;
    DisjointSet mySet(numCells);
    bool mazeComplete = false;

    // to do -- see assignment instructions for details
    while (!mazeComplete) {
        int cell = rand() % numCells;
        int direction = rand() % 4;

        switch(direction) {
            case 0:
                if (cell % numColumns == 0)
                    mazeComplete = moveRight(mySet, cell);
                else
                    mazeComplete = moveLeft(mySet, cell);
                break;
            case 1:
                if (cell >= numCells - numColumns)
                    mazeComplete = moveUp(mySet, cell);
                else
                    mazeComplete = moveDown(mySet, cell);
                break;
            case 2:
                if (cell % numColumns == numColumns - 1)
                    mazeComplete = moveLeft(mySet, cell);
                else
                    mazeComplete = moveRight(mySet, cell);
                break;
            case 3:
                if (cell < numColumns - 1)
                    mazeComplete = moveDown(mySet, cell);
                else
                    mazeComplete = moveUp(mySet, cell);
                break;
        }
    }
}

void Maze::print(ostream &outputStream)
{
    // print the top row of walls
    for (int i = 0; i < numColumns; i++)
        outputStream << " _";
    outputStream << '\n';
    for (int i = 0; i < numRows; i++)
    {
        int cellbase = i * numColumns;
        // print west wall (except at entrance)
        if (i == 0)
            outputStream << ' ';
        else
            outputStream << '|';
        for (int j = 0; j < numColumns; j++)
        {
            if (mazeWalls[cellbase + j].south)
                outputStream << '_';
            else
                outputStream << ' ';
            if (mazeWalls[cellbase + j].east)
                outputStream << '|';
            else
                outputStream << ' ';
        }
        outputStream << '\n';
    }
}

void Maze::copy(const Maze &orig)
{
    this->numRows = orig.numRows;
    this->numColumns = orig.numColumns;
    int numCells = numRows * numColumns;
    mazeWalls = new CellWalls[numCells];
    for (int i = 0; i < numCells; i++)
    {
        this->mazeWalls[i] = orig.mazeWalls[i];
    }
}

bool Maze::moveUp(DisjointSet& set, int cell) {
    int nextCell = cell - numColumns;
    if (set.find(cell) != set.find(nextCell)) {
        mazeWalls[nextCell].south = false;
        return set.doUnion(cell, nextCell);
    }
    return false;
}

bool Maze::moveDown(DisjointSet& set, int cell) {
    int nextCell = cell + numColumns;
    if (set.find(cell) != set.find(nextCell)) {
        mazeWalls[cell].south = false;
        return set.doUnion(cell, nextCell);
    }
    return false;
}

bool Maze::moveLeft(DisjointSet& set, int cell) {
    int nextCell = cell - 1;
    if (set.find(cell) != set.find(nextCell)) {
        mazeWalls[nextCell].east = false;
        return set.doUnion(cell, nextCell);
    }
    return false;
}

bool Maze::moveRight(DisjointSet& set, int cell) {
    int nextCell = cell + 1;
    if (set.find(cell) != set.find(nextCell)) {
        mazeWalls[cell].east = false;
        return set.doUnion(cell, nextCell);
    }
    return false;
}