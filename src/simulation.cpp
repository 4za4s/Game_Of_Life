#include <vector>
#include <utility>
#include "simulation.hpp"
#include <iostream>
#include <bitset>

void Simulation::Draw()
{
    grid.Draw();
    DrawRectangle(10, 10, 200, 60, Color{94, 104, 112, 255});
    DrawText(TextFormat("FPS: %i", GetFPS()), 20, 20, 20, RAYWHITE);
    DrawText(TextFormat("SPEED: %f", simulationSpeed), 20, 40, 20, RAYWHITE);
}

void Simulation::SetCell(int row, int column, int value)
{
    grid.SetValue(row, column, value);
}

void Simulation::ToggleCell(int row, int column)
{
    unsigned int cellState = grid.GetCellState(row, column);
    grid.SetValue(row, column, (cellState & 0x01) ^ 0x01);
}

void Simulation::Update()
{
    if(isRunning())
    {
        int liveNeighbours;
        int rows = grid.GetRows(), columns = grid.GetColumns();
        unsigned char *cell_ptr;
        memcpy(temp_cells, grid.GetCells(), length);

        cell_ptr = temp_cells;

        for(int row = 0; row < rows; row++)
        {
            for(int column = 0; column < columns; column++)
            {
                cell_ptr = temp_cells + (row * columns) + column;

                if (*cell_ptr != 0)
                {
                liveNeighbours = *cell_ptr >> 1;
                // std::bitset<8> x(*cell_ptr);
                // std::cout << row << ", " << column << std::endl;
                // std::cout << x << std::endl;
                // std::cout << liveNeighbours << std::endl;

                if(*cell_ptr & 0x01)
                {   
                    if(liveNeighbours != 3 && liveNeighbours != 2)
                    {
                        grid.SetValue(row, column, 0);
                    }
                }
                else
                {
                    if(liveNeighbours == 3)
                    {
                        grid.SetValue(row, column, 1);
                    }
                }
                }
            }
        }
    }
}

Simulation::~Simulation()
{
    delete[] temp_cells;
}
