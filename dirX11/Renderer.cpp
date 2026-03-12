#include "Renderer.h"
#include <iostream>
#include <SDL2/SDL_syswm.h>

Renderer::Renderer(SDL_Window* window, int frameBufferWidth, int frameBufferHeight) 
	: window(window), frameBufferHeight(frameBufferHeight), frameBufferWidth(frameBufferWidth) {
	CreateDeviceAndContext();
    CreateSwapChain();
    RetreiveBackBuffer();
}

// With other word: collect everything that has to be displayed
void Renderer::BeginRenderPass() {
    const float clearColor[4] = { 1, 0, 0, 0 }; // RED
    context->ClearRenderTargetView(renderTargetView.Get(), clearColor);

    const CD3D11_VIEWPORT viewport(0.0f, 0.0f, frameBufferWidth, frameBufferHeight);
    context->RSSetViewports(1, &viewport);

    ID3D11RenderTargetView* renderTargets[] = { renderTargetView.Get() };
    context->OMSetRenderTargets(1, renderTargets, nullptr); // render to this buffer
}

// Display it
void Renderer::EndRenderPass() {
    swapChain->Present(0, 0); // Present with vsync (first number 1 for vsync)
}

void Renderer::CreateDeviceAndContext() {
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

    if (FAILED(hr)) { // TODO: make a proper error handling
        std::cerr << "Failed to create Direct3D 11 device. HRESULT: " << std::hex << hr << std::endl;
        return;
    }

    ComPtr<IDXGIDevice> dxgiDevice;
    device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(dxgiDevice.GetAddressOf()));

    ComPtr<IDXGIAdapter> dxgiAdapter;
    dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf());

    DXGI_ADAPTER_DESC adapterDesc;
    dxgiAdapter->GetDesc(&adapterDesc);

    std::wcout << L"Using adapter: " << adapterDesc.Description << std::endl;
}

void Renderer::CreateSwapChain() {
    ComPtr<IDXGIFactory2> factory;
    
    HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&factory));
    if (FAILED(hr)) {
        std::cerr << "Failed to create DXGI factory. HRESULT: " << std::hex << std::endl;
        return;
    }

    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.Width = frameBufferWidth;
    swapChainDesc.Height = frameBufferHeight;
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 2; // Double buffering that was mentioned in the header
    swapChainDesc.SampleDesc.Count = 1; // No multi sampling
    swapChainDesc.SampleDesc.Quality = 0; // default
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // Let the screen take whatever it wants. VALID ONLY IF BufferCount is > 1

    SDL_SysWMinfo wmInfo; // Might fail if no version specified
    SDL_VERSION(&wmInfo.version);

    if (SDL_GetWindowWMInfo(window, &wmInfo) != SDL_TRUE) {
        std::cerr << "Failed to get window info. SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    HWND hwnd = wmInfo.info.win.window;

    factory->CreateSwapChainForHwnd(
        device.Get(),
        hwnd,
        &swapChainDesc,
        nullptr,
        nullptr,
        &swapChain
    );

    if (FAILED(hr)) {
        std::cerr << "Failed to create swapChain. HRESULT: " << std::hex << hr << std::endl;
        return;
    }
}

void Renderer::RetreiveBackBuffer() {
    HRESULT hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
    if (FAILED(hr)) {
        std::cerr << "Failed to retrieve back buffer. HRESULT: " << std::hex << hr << std::endl;
        return;
    }

    D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
    rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    hr = device->CreateRenderTargetView(backBuffer.Get(), &rtvDesc, &renderTargetView);
    if (FAILED(hr)) {
        std::cerr << "Failed to create render target view. HRESULT: " << std::hex << hr << std::endl;
        return;
    }
}