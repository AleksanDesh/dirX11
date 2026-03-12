#include "TriangleTest.h"
#include "string"
#include <iostream>
#include "BlobUtil.h"
#include "ShaderUtil.h"

TriangleTest::TriangleTest(Renderer& renderer)
	: renderer(renderer)
{
	device = renderer.GetDevice();
	context = renderer.GetContext();
	CreateShaders();

}

void TriangleTest::Render()
{
	context->VSSetShader(vertexShader.Get(), nullptr, 0);
	context->PSSetShader(pixelShader.Get(), nullptr, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->Draw(3, 0);
}

void TriangleTest::CreateShaders()
{
	std::string versionVertexShader = "vs_5_0";
	std::string versionPixelShader = "ps_5_0";

	std::string vertexShaderLoc = "Shaders\\TriangleVertexShader.hlsl";
	std::string pixelShaderLoc = "Shaders\\TrianglePixelShader.hlsl";

	ComPtr<ID3D10Blob> vertexShaderBlob = BlobUtil::Create(vertexShaderLoc, versionVertexShader);
	ComPtr<ID3D10Blob> pixelShaderBlob = BlobUtil::Create(pixelShaderLoc, versionPixelShader);

	vertexShader = ShaderUtil::CreateVertexShader(device, vertexShaderBlob);
	pixelShader = ShaderUtil::CreatePixelShader(device, pixelShaderBlob);

}



