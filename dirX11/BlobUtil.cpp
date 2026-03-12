#include "BlobUtil.h"
#include <iostream>

ComPtr<ID3D10Blob> BlobUtil::Create(std::string filePath, std::string version, std::string mainFn)
{
	ComPtr<ID3D10Blob> shaderBlob;
	ComPtr<ID3D10Blob> errorBlob;


	HRESULT hr = D3DCompileFromFile(
		std::wstring(filePath.begin(), filePath.end()).c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		mainFn.c_str(), // HAS TO CORRESPOND TO THE NAME OF THE METHOD INSIDE THE SHADER
		version.c_str(), // VERSION
		0, // Flags
		0, // effect Flags
		&shaderBlob,
		&errorBlob
	);

	if (FAILED(hr)) {
		if (errorBlob) {
			std::cerr << "Vertex shader compilation failed: "
				<< static_cast<const char*>(errorBlob->GetBufferPointer())
				<< std::endl;
		}
		else {
			std::cerr << "Vertex shader compilation failed" << std::endl;
		}
		return nullptr;
	}
	return shaderBlob;
}
