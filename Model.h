#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
class Model
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���f���쐬
	/// </summary>
	void CreateModel();
private:
	// �R�}���h���X�g
	ID3D12GraphicsCommandList* cmdList=nullptr;
};

