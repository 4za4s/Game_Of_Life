#pragma once

#include "grid.hpp"
#include <memory> 

class Simulation
{
private:
    Grid grid;
    unsigned char *temp_cells;
    int length;
    bool run;
    float simulationSpeed;
public:
    Simulation(int width, int height, int cellSize, float simulationSpeed)
    : grid(width, height, cellSize), run(true), simulationSpeed(simulationSpeed)
    {   
        length = grid.GetRows() * grid.GetColumns();
        temp_cells = new unsigned char[length];
        memset(temp_cells, 0, length);
        grid.FillRandom();
    };
    ~Simulation();
    void Draw();
    void SetCell(int row, int column, int value);
    void SetSpeed(float speed) { simulationSpeed = speed; }
    void ToggleCell(int row, int column);
    void Update();
    bool isRunning() {return run;};
    void Start() {run = true;};
    void Stop() {run = false;};
};