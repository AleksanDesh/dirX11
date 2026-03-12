#pragma once

#include <wrl/client.h>
#include <d3d11.h>
using namespace Microsoft::WRL;


class ShaderUtil
{
public:
	static ComPtr<ID3D11VertexShader> CreateVertexShader(ComPtr<ID3D11Device> device, ComPtr<ID3D10Blob> blob);
	static ComPtr<ID3D11PixelShader> CreatePixelShader(ComPtr<ID3D11Device> device, ComPtr<ID3D10Blob> blob);



};

