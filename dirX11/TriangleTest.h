#pragma once

#include "Renderer.h"

class TriangleTest
{
public: 
	TriangleTest(Renderer& renderer);

	void Render();
	

private:
	Renderer& renderer;
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> context;

	ComPtr<ID3D11VertexShader> vertexShader;
	ComPtr<ID3D11PixelShader> pixelShader;

	void CreateShaders();
};

