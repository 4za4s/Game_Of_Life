#include "grid.hpp"

void Grid::Draw()
{
    int offsetX = (GetScreenWidth() - columns*cellSize) / 2;
    int offsetY = (GetScreenHeight() - rows*cellSize) / 2;
    for(int row = 0; row < rows; row++)
    {
        for(int column = 0; column < columns; column++)
        {
            int state = GetCellState(row, column);
            if(state & 0x01)
            {
                DrawRectangle(column * cellSize + offsetX, row * cellSize + offsetY, cellSize, cellSize, LIVE);
            }
        }
    }
}

void Grid::SetValue(int row, int column, int value)
{
    unsigned char *cell_ptr = cells + (row * columns) + column;
    int xleft, xright, yabove, ybelow;

    xleft = (column == 0) ? columns - 1 : -1;
	xright = (column == (columns - 1)) ? -(columns - 1) : 1;
	yabove = (row == 0) ? length - columns : -columns;
	ybelow = (row == (rows - 1)) ? -(length - columns) : columns;

    if (value != 0)
    {
        *(cell_ptr) |= 0x01;

        *(cell_ptr + yabove + xleft) += 0x02;
        *(cell_ptr + yabove) += 0x02;
        *(cell_ptr + yabove + xright) += 0x02;
        *(cell_ptr + xleft) += 0x02;
        *(cell_ptr + xright) += 0x02;
        *(cell_ptr + ybelow + xleft) += 0x02;
        *(cell_ptr + ybelow) += 0x02;
        *(cell_ptr + ybelow + xright) += 0x02;
    }
    else
    {
        *(cell_ptr) &= ~0x01;

        *(cell_ptr + yabove + xleft) -= 0x02;
        *(cell_ptr + yabove) -= 0x02;
        *(cell_ptr + yabove + xright) -= 0x02;
        *(cell_ptr + xleft) -= 0x02;
        *(cell_ptr + xright) -= 0x02;
        *(cell_ptr + ybelow + xleft) -= 0x02;
        *(cell_ptr + ybelow) -= 0x02;
        *(cell_ptr + ybelow + xright) -= 0x02;
    }
}

int Grid::GetCellState(int row, int column)
{
    unsigned char *cell_ptr = cells + (row * columns) + column;
    return *(cell_ptr);
}

void Grid::FillRandom()
{
     for(int row = 0; row < rows; row++)
    {
        for(int column = 0; column < columns; column++)
        {
            int randomValue = GetRandomValue(0, 4);
            randomValue = randomValue == 4 ? 1 : 0;
            if(randomValue)
            {
                SetValue(row, column, randomValue);
            }
        }
    }
}

Grid::~Grid()
{
    delete[] cells;
}