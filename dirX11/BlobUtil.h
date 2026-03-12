#pragma once

#include <wrl/client.h>
#include <d3dcompiler.h>
#include <d3d10.h>
#include <string>
using namespace Microsoft::WRL;

class BlobUtil
{
public: 
	static ComPtr<ID3D10Blob> Create(std::string filePath, std::string version, std::string mainFn = "main");
};

