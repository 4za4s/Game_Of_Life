#pragma once
#include <raylib.h>
#include <vector>
#include <memory.h>

class Grid
{
private:
    unsigned char *cells;
    int rows;
    int columns;
    int length;
    int cellSize;
    Color LIVE = {255, 255, 255, 255};
    Color DYING = {255, 0, 0 , 255};
    Color DEAD = {55, 55, 55, 255};

public:
    Grid(int width, int height, int cellSize)
    : rows(height/cellSize), columns(width/cellSize), cellSize(cellSize)
    {
        length = rows * columns;
        cells = new unsigned char[length];
        memset(cells, 0, length);
    };
    ~Grid();
    void Draw();
    void SetValue(int row, int column, int state);
    int GetCellState(int row, int column);
    int GetRows() {return rows;};
    int GetColumns() {return columns;};
    unsigned char * GetCells() {return cells;}
    void FillRandom();
};