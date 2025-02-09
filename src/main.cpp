#include <raylib.h>
#include <iostream>
#include "simulation.hpp"

int main() 
{
    const Color GREY = {29, 29, 29, 255};

    // Initialize window
    const int WINDOW_WIDTH = 1000;
    const int WINDOW_HEIGHT = 1000;
    int fps = 0;
    float simulationSpeed = 1;
    const int CELL_SIZE = 15;
    const int MAP_WIDTH = 100;
    const int MAP_HEIGHT = 100;
    int key;
    float lastUpdate = 0;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game of Life");
    SetTargetFPS(fps);
    Simulation simulation(MAP_WIDTH*CELL_SIZE, MAP_HEIGHT*CELL_SIZE, CELL_SIZE, simulationSpeed);

    // Main game loop
    while (!WindowShouldClose()) 
    {
        // Events
        key = GetKeyPressed();
        if(key == KEY_SPACE)
        {
            if(simulation.isRunning()){
                simulation.Stop();
            }
            else
            {
                simulation.Start();
            }
        }
        else if(key == KEY_LEFT)
        {
            simulationSpeed = std::min(simulationSpeed*2, 4.0f);
            simulation.SetSpeed(simulationSpeed);
        }
        else if(key == KEY_RIGHT)
        {
            simulationSpeed = std::max(simulationSpeed/2, 0.015625f);
            simulation.SetSpeed(simulationSpeed);
        }

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            int row = GetMouseY() / CELL_SIZE;
            int column = GetMouseX() / CELL_SIZE;
            simulation.ToggleCell(row, column);
        } 

        // Update
        if((lastUpdate += GetFrameTime()) >= simulationSpeed)
        {
            lastUpdate = 0;
            simulation.Update();
        }

        // Draw
        BeginDrawing();
        ClearBackground(GREY);
        simulation.Draw();
        EndDrawing();
    }

    CloseWindow();
}