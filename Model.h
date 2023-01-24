#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
class Model
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// モデル作成
	/// </summary>
	void CreateModel();
private:
	// コマンドリスト
	ID3D12GraphicsCommandList* cmdList=nullptr;
};

