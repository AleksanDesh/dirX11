#include "ShaderUtil.h"
#include <iostream>

ComPtr<ID3D11VertexShader> ShaderUtil::CreateVertexShader(ComPtr<ID3D11Device> device, ComPtr<ID3D10Blob> blob)
{
	ComPtr<ID3D11VertexShader> shader;
	HRESULT hr = device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader);
	if (FAILED(hr)) {
		std::cerr << "Failed to create veretx shader" << std::endl;
		return nullptr;
	}
	return shader;
}

ComPtr<ID3D11PixelShader> ShaderUtil::CreatePixelShader(ComPtr<ID3D11Device> device, ComPtr<ID3D10Blob> blob)
{
	ComPtr<ID3D11PixelShader> shader;
	HRESULT hr = device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader);
	if (FAILED(hr)) {
		std::cerr << "Failed to create pixel shader" << std::endl;
		return nullptr;
	}
	return shader;
}
