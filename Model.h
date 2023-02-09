#pragma once
#include <d3d12.h>
#include<string>
#include<vector>
#include <wrl.h>
#include <DirectXMath.h>
#include <d3dx12.h>
class Model
{
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:	//�T�u�N���X
	// ���_�f�[�^�\����
	struct VertexPosNormalUv
	{
		XMFLOAT3 pos; // xyz���W
		XMFLOAT3 normal; // �@���x�N�g��
		XMFLOAT2 uv;  // uv���W
	};
	//�}�e���A��
	struct Material
	{
		std::string name;	//�}�e���A����
		XMFLOAT3 ambient;	//�A���r�G���g�e���x
		XMFLOAT3 diffuse;	//�f�B�t���[�Y�e���x
		XMFLOAT3 specular;	//�X�y�L�����[�e���x
		float alpha;		//�A���t�@
		std::string textureFilename;	//�e�N�X�`���t�@�C����
		//�R���X�g���N�^
		Material() {
			ambient = { 0.3f,0.3f,0.3f };
			diffuse = { 0.0f,0.0f,0.0f };
			specular = { 0.0f,0.0f,0.0f };
			alpha = 1.0f;
		}
	};
	// �萔�o�b�t�@�p�f�[�^�\����B0
	struct ConstBufferDataB0
	{
		//XMFLOAT4 color;	// �F (RGBA)
		XMMATRIX mat;	// �R�c�ϊ��s��
	};

	//�萔�o�b�t�@�p�f�[�^�\����B1
	struct ConstBufferDataB1
	{
		XMFLOAT3 ambient;	//�A���r�G���g�W��
		float pad1;			//�p�f�B���O
		XMFLOAT3 diffuse;	//�f�B�t���[�Y�W��
		float pad2;			//�p�f�B���O
		XMFLOAT3 specular;	//�X�y�L�����[�W��
		float alpha;		//�A���t�@
	};
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(std::string filepath);

	void Draw(ID3D12GraphicsCommandList* cmdList);

	//Getter
	Material GetMaerial() { return material; }

public://�ÓI�����o�[�֐�
	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="device">�f�o�C�X</param>
	static void StaticInitialize(ID3D12Device* _device);

	static Model* StaticCreateFromOBJ(std::string filePath);

private:
	/// <summary>
	/// �f�X�N���v�^�q�[�v�̏�����
	/// </summary>
	void InitializeDescriptorHeap();

	/// <summary>
	/// ���f���쐬
	/// </summary>
	void LoadModel(std::string filepath);

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	bool LoadTexture(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// �}�e���A���ǂݍ���
	/// </summary>
	/// <param name="directoryPath"></param>
	/// <param name="filename"></param>
	void LoadMaterial(const std::string& directoryPath, const std::string& filename);

private://�ÓI�����o�[�ϐ�
	// �f�o�C�X
	static ID3D12Device* device;

private:
	ComPtr<ID3D12Resource> constBuffB0; // �萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffB1; // �萔�o�b�t�@
	// �f�X�N���v�^�T�C�Y
	UINT descriptorHandleIncrementSize;
	// �f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// ���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	// �C���f�b�N�X�o�b�t�@
	ComPtr<ID3D12Resource> indexBuff;
	//�}�e���A��
	Material material;
	// �e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource> texbuff;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// �C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView;
	// ���_�f�[�^�z��
	std::vector<VertexPosNormalUv>vertices;
	// ���_�C���f�b�N�X�z��
	//static unsigned short indices[planeCount * 3];
	std::vector<unsigned short>indices;
};

