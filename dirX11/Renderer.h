#pragma once
#include <dxgi.h>
#include <d3d11.h>
#include <dxgi1_2.h>
#include <wrl/client.h>
#include <SDL2/SDL_video.h>
#include <d3dcompiler.h>
using namespace Microsoft::WRL;


class Renderer
{
public: 
	Renderer(SDL_Window* window, int frameBufferWidth, int frameBufferHeight);

	ComPtr<ID3D11Device> GetDevice() const { return device; }
	ComPtr<ID3D11DeviceContext> GetContext() const { return context; }


	void BeginRenderPass();
	void EndRenderPass();
	 
private: 
	SDL_Window* window;
	int frameBufferWidth, frameBufferHeight;

	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> context;

	ComPtr<IDXGISwapChain1> swapChain; // format, size, amount
	ComPtr<ID3D11Texture2D> backBuffer; // the texture itself (frame 1 - buffer 1, frame 2 - buffer 2, frame 3 - buffer 1) with 2, but IF one buffer, then always 1, and if 3.. yes.
	ComPtr<ID3D11RenderTargetView> renderTargetView; // Viewing of the buffer


	void CreateDeviceAndContext();
	void CreateSwapChain();
	void RetreiveBackBuffer();
};

