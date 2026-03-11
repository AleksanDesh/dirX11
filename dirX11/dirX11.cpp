// dirX11.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>

// THIS MUST BE IN THIS ORDER
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "Renderer.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")


int main()
{
    if (SDL_INIT_VIDEO < 0) {
        std::cerr << "SDL could not initialize! SDL_Rrror " << SDL_GetError() << std::endl;
    }

    SDL_Window* window = SDL_CreateWindow("DirectX engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Rrror " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }
    
    Renderer renderer(window, 800, 600);

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        //SDL_Delay(16); // Simulates a frame delay (it says around 60 fps?)
        renderer.BeginRenderPass();
        renderer.EndRenderPass();
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
