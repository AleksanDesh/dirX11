// dirX11.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>

// THIS MUST BE IN THIS ORDER
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <wrl/client.h>

#include <dxgi.h>
#pragma comment(lib, "dxgi.lib")

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

using namespace Microsoft::WRL;

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

    ComPtr<ID3D11Device> device;
    ComPtr<ID3D11DeviceContext> context;

    D3D_FEATURE_LEVEL featureLevelRequested = D3D_FEATURE_LEVEL_11_0;
    D3D_FEATURE_LEVEL featureLevelSupported;
    
    HRESULT hr = D3D11CreateDevice(
        nullptr, // chose a default adapter (GPU)
        D3D_DRIVER_TYPE_HARDWARE, //use the hardware GPU driver. Alternatives: D3D_DRIVER_TYPE_WARP (software rasterizer), D3D_DRIVER_TYPE_REFERENCE, D3D_DRIVER_TYPE_NULL
        nullptr, // software restirizer (useless for now)
        0, // no flags
        &featureLevelRequested, // pointer to an array of feature requests
        1, // number of entries in that array ^
        D3D11_SDK_VERSION, 
        &device, // destination for the created Device
        &featureLevelSupported, // Actual feature (may be not supported, but normally it is supported)
        &context // destination for the context
    );
    
    if (FAILED(hr)) {
        std::cerr << "Failed to create Direct3D 11 device. HRESULT: " << std::hex << hr << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    
    ComPtr<IDXGIDevice> dxgiDevice;
    device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(dxgiDevice.GetAddressOf()));
    
    ComPtr<IDXGIAdapter> dxgiAdapter;
    dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf());
    
    DXGI_ADAPTER_DESC adapterDesc;
    dxgiAdapter->GetDesc(&adapterDesc);
    
    std::wcout << L"Using adapter: " << adapterDesc.Description << std::endl;

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_Delay(16); // Simulates a frame delay (it says around 60 fps?)

    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
