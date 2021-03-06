/*!
@file DrawComponents.cpp
@brief 描画コンポーネント実体
@copyright Copyright (c) 2016 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/

#include "stdafx.h"
#include <pix.h>


namespace basecross {


	//これより個別シェーダー
	IMPLEMENT_DX12SHADER(VSShadowmap, App::GetApp()->m_wstrRelativeShadersPath + L"VSShadowmap.cso")


	IMPLEMENT_DX12SHADER(VSPCDirect, App::GetApp()->m_wstrRelativeShadersPath + L"VSPCDirect.cso")
	IMPLEMENT_DX12SHADER(PSPCDirect, App::GetApp()->m_wstrRelativeShadersPath + L"PSPCDirect.cso")

	IMPLEMENT_DX12SHADER(VSPTDirect, App::GetApp()->m_wstrRelativeShadersPath + L"VSPTDirect.cso")
	IMPLEMENT_DX12SHADER(PSPTDirect, App::GetApp()->m_wstrRelativeShadersPath + L"PSPTDirect.cso")

	IMPLEMENT_DX12SHADER(VSPCSprite, App::GetApp()->m_wstrRelativeShadersPath + L"VSPCSprite.cso")
	IMPLEMENT_DX12SHADER(PSPCSprite, App::GetApp()->m_wstrRelativeShadersPath + L"PSPCSprite.cso")

	IMPLEMENT_DX12SHADER(VSPTSprite, App::GetApp()->m_wstrRelativeShadersPath + L"VSPTSprite.cso")
	IMPLEMENT_DX12SHADER(PSPTSprite, App::GetApp()->m_wstrRelativeShadersPath + L"PSPTSprite.cso")

	IMPLEMENT_DX12SHADER(VSPCTSprite, App::GetApp()->m_wstrRelativeShadersPath + L"VSPCTSprite.cso")
	IMPLEMENT_DX12SHADER(PSPCTSprite, App::GetApp()->m_wstrRelativeShadersPath + L"PSPCTSprite.cso")


	IMPLEMENT_DX12SHADER(VSPCStatic, App::GetApp()->m_wstrRelativeShadersPath + L"VSPCStatic.cso")
	IMPLEMENT_DX12SHADER(PSPCStatic, App::GetApp()->m_wstrRelativeShadersPath + L"PSPCStatic.cso")

	IMPLEMENT_DX12SHADER(VSPTStatic, App::GetApp()->m_wstrRelativeShadersPath + L"VSPTStatic.cso")
	IMPLEMENT_DX12SHADER(PSPTStatic, App::GetApp()->m_wstrRelativeShadersPath + L"PSPTStatic.cso")

	IMPLEMENT_DX12SHADER(VSPCTInstance, App::GetApp()->m_wstrRelativeShadersPath + L"VSPCTInstance.cso")
	IMPLEMENT_DX12SHADER(VSPCTStatic, App::GetApp()->m_wstrRelativeShadersPath + L"VSPCTStatic.cso")
	IMPLEMENT_DX12SHADER(PSPCTStatic, App::GetApp()->m_wstrRelativeShadersPath + L"PSPCTStatic.cso")


	IMPLEMENT_DX12SHADER(VSPNTStatic, App::GetApp()->m_wstrRelativeShadersPath + L"VSPNTStatic.cso")
	IMPLEMENT_DX12SHADER(PSPNTStatic, App::GetApp()->m_wstrRelativeShadersPath + L"PSPNTStatic.cso")

	IMPLEMENT_DX12SHADER(VSPNTStaticShadow, App::GetApp()->m_wstrRelativeShadersPath + L"VSPNTStaticShadow.cso")
	IMPLEMENT_DX12SHADER(PSPNTStaticShadow, App::GetApp()->m_wstrRelativeShadersPath + L"PSPNTStaticShadow.cso")
	IMPLEMENT_DX12SHADER(PSPNTStaticShadow2, App::GetApp()->m_wstrRelativeShadersPath + L"PSPNTStaticShadow2.cso")



	//--------------------------------------------------------------------------------------
	//	struct DrawComponent::Impl;
	//	用途: Implイディオム
	//--------------------------------------------------------------------------------------
	struct DrawComponent::Impl {
		BlendState m_BlendState;
		DepthStencilState m_DepthStencilState;
		RasterizerState m_RasterizerState;
		SamplerState m_SamplerState;
		Matrix4X4 m_MeshToTransformMatrix;
		Impl() :
			m_MeshToTransformMatrix() {}
	};

	//--------------------------------------------------------------------------------------
	///	描画コンポーネントの親クラス実体
	//--------------------------------------------------------------------------------------
	DrawComponent::DrawComponent(const shared_ptr<GameObject>& GameObjectPtr) :
		Component(GameObjectPtr),
		pImpl(new Impl())
	{}
	DrawComponent::~DrawComponent() {}


	BlendState DrawComponent::GetBlendState() const {
		return pImpl->m_BlendState;
	}
	DepthStencilState DrawComponent::GetDepthStencilState() const {
		return pImpl->m_DepthStencilState;
	}
	RasterizerState DrawComponent::GetRasterizerState() const {
		return pImpl->m_RasterizerState;
	}
	SamplerState DrawComponent::GetSamplerState() const {
		return pImpl->m_SamplerState;
	}


	void DrawComponent::SetBlendState(const BlendState state) {
		pImpl->m_BlendState = state;
	}
	void DrawComponent::SetDepthStencilState(const DepthStencilState state) {
		pImpl->m_DepthStencilState = state;

	}
	void DrawComponent::SetRasterizerState(const RasterizerState state) {
		pImpl->m_RasterizerState = state;
	}
	void DrawComponent::SetSamplerState(const SamplerState state) {
		pImpl->m_SamplerState = state;
	}

	const Matrix4X4& DrawComponent::GetMeshToTransformMatrix() const {
		return pImpl->m_MeshToTransformMatrix;
	}
	void DrawComponent::SetMeshToTransformMatrix(const Matrix4X4& Mat) {
		pImpl->m_MeshToTransformMatrix = Mat;
	}

	//--------------------------------------------------------------------------------------
	//	struct Shadowmap::Impl;
	//	用途: Implイディオム
	//--------------------------------------------------------------------------------------
	struct Shadowmap::Impl {
		static float m_LightHeight;	//ライトの高さ（向きをこの値で掛ける）
		static float m_LightNear;	//ライトのNear
		static float m_LightFar;		//ライトのFar
		static float m_ViewWidth;
		static float m_ViewHeight;

		weak_ptr<MeshResource> m_MeshResource;	//メッシュリソース

												///ルートシグネチャ
		ComPtr<ID3D12RootSignature> m_RootSignature;
		///CbvSrvのデスクプリタハンドルのインクリメントサイズ
		UINT m_CbvSrvDescriptorHandleIncrementSize{ 0 };
		///デスクプリタヒープ
		ComPtr<ID3D12DescriptorHeap> m_CbvSrvUavDescriptorHeap;
		///GPU側デスクプリタのハンドルの配列
		vector<CD3DX12_GPU_DESCRIPTOR_HANDLE> m_GPUDescriptorHandleVec;
		// コンスタントバッファ
		struct ShadowConstantBuffer
		{
			Matrix4X4 mWorld;
			Matrix4X4 mView;
			Matrix4X4 mProj;
			Vector4 Bones[3 * 72];	//Bone用
			ShadowConstantBuffer() {
				memset(this, 0, sizeof(ShadowConstantBuffer));
			};
		};
		ShadowConstantBuffer m_ShadowConstantBuffer;
		///コンスタントバッファアップロードヒープ
		ComPtr<ID3D12Resource> m_ConstantBufferUploadHeap;
		///コンスタントバッファのGPU側変数
		void* m_pConstantBuffer{ nullptr };
		//パイプラインステート
		ComPtr<ID3D12PipelineState> m_PipelineState;
		///コマンドリスト
		ComPtr<ID3D12GraphicsCommandList> m_CommandList;

		///ルートシグネチャ作成
		void CreateRootSignature();
		///デスクプリタヒープ作成
		void CreateDescriptorHeap();
		///コンスタントバッファ作成
		void CreateConstantBuffer();
		///パイプラインステート作成
		void CreatePipelineState();
		///コマンドリスト作成
		void CreateCommandList();
		//コンスタントバッファ更新
		void UpdateConstantBuffer();
		///描画処理
		void DrawObject();

		Impl()
		{
			try {
				///ルートシグネチャ作成
				CreateRootSignature();
				///デスクプリタヒープ作成
				CreateDescriptorHeap();
				///コンスタントバッファ作成
				CreateConstantBuffer();
				///パイプラインステート作成
				CreatePipelineState();
				///コマンドリスト作成
				CreateCommandList();
				//コンスタントバッファ更新
				UpdateConstantBuffer();
			}
			catch (...) {
				throw;

			}

		}
		~Impl() {}
	};

	float Shadowmap::Impl::m_LightHeight(20.0f);
	float Shadowmap::Impl::m_LightNear(1.0f);
	float Shadowmap::Impl::m_LightFar(200.0f);
	float Shadowmap::Impl::m_ViewWidth(32.0f);
	float Shadowmap::Impl::m_ViewHeight(32.0f);

	///ルートシグネチャ作成
	void Shadowmap::Impl::CreateRootSignature() {
		//コンスタントバッファ付ルートシグネチャ
		m_RootSignature = RootSignature::CreateCbv();
	}
	///デスクプリタヒープ作成
	void Shadowmap::Impl::CreateDescriptorHeap() {
		auto Dev = App::GetApp()->GetDeviceResources();
		m_CbvSrvDescriptorHandleIncrementSize
			= Dev->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		//CbvSrvデスクプリタヒープ(コンスタントバッファのみ)
		m_CbvSrvUavDescriptorHeap = DescriptorHeap::CreateCbvSrvUavHeap(1);
		//GPU側デスクプリタヒープのハンドルの配列の作成
		m_GPUDescriptorHandleVec.clear();
		CD3DX12_GPU_DESCRIPTOR_HANDLE CbvHandle(
			m_CbvSrvUavDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
			0,
			0
		);
		m_GPUDescriptorHandleVec.push_back(CbvHandle);
	}
	///コンスタントバッファ作成
	void Shadowmap::Impl::CreateConstantBuffer() {
		auto Dev = App::GetApp()->GetDeviceResources();
		//コンスタントバッファは256バイトにアラインメント
		UINT ConstBuffSize = (sizeof(ShadowConstantBuffer) + 255) & ~255;
		ThrowIfFailed(Dev->GetDevice()->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(ConstBuffSize),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_ConstantBufferUploadHeap)),
			L"コンスタントバッファ用のアップロードヒープ作成に失敗しました",
			L"Dev->GetDevice()->CreateCommittedResource()",
			L"Shadowmap::Impl::CreateConstantBuffer()"
		);
		//コンスタントバッファのビューを作成
		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
		cbvDesc.BufferLocation = m_ConstantBufferUploadHeap->GetGPUVirtualAddress();
		//コンスタントバッファは256バイトにアラインメント
		cbvDesc.SizeInBytes = ConstBuffSize;
		//コンスタントバッファビューを作成すべきデスクプリタヒープ上のハンドルを取得
		//シェーダリソースがある場合コンスタントバッファはシェーダリソースビューのあとに設置する
		CD3DX12_CPU_DESCRIPTOR_HANDLE cbvSrvHandle(
			m_CbvSrvUavDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
			0,
			0
		);
		Dev->GetDevice()->CreateConstantBufferView(&cbvDesc, cbvSrvHandle);
		//コンスタントバッファのアップロードヒープのマップ
		CD3DX12_RANGE readRange(0, 0);
		ThrowIfFailed(m_ConstantBufferUploadHeap->Map(0, &readRange, reinterpret_cast<void**>(&m_pConstantBuffer)),
			L"コンスタントバッファのマップに失敗しました",
			L"pImpl->m_ConstantBufferUploadHeap->Map()",
			L"Shadowmap::Impl::CreateConstantBuffer()"
		);
	}
	///パイプラインステート作成
	void Shadowmap::Impl::CreatePipelineState() {
		D3D12_GRAPHICS_PIPELINE_STATE_DESC PineLineDesc;
		m_PipelineState = PipelineState::CreateShadowmap3D<VertexPositionNormalTexture, VSShadowmap>(m_RootSignature, PineLineDesc);
	}
	///コマンドリスト作成
	void Shadowmap::Impl::CreateCommandList() {
		m_CommandList = CommandList::CreateDefault(m_PipelineState);
		CommandList::Close(m_CommandList);
	}


	void Shadowmap::Impl::UpdateConstantBuffer() {
		//更新
		memcpy(m_pConstantBuffer, reinterpret_cast<void**>(&m_ShadowConstantBuffer),
			sizeof(m_ShadowConstantBuffer));
	}

	///描画処理
	void Shadowmap::Impl::DrawObject() {
		auto Dev = App::GetApp()->GetDeviceResources();
		auto ShMesh = m_MeshResource.lock();
		if (!ShMesh) {
			return;
		}
		//コマンドリストのリセット
		CommandList::Reset(m_PipelineState, m_CommandList);
		//メッシュが更新されていればリソース更新
		ShMesh->UpdateResources<VertexPositionNormalTexture>(m_CommandList);
		//ルートシグネチャのセット
		m_CommandList->SetGraphicsRootSignature(m_RootSignature.Get());
		//デスクプリタヒープのセット
		ID3D12DescriptorHeap* ppHeaps[] = { m_CbvSrvUavDescriptorHeap.Get() };
		m_CommandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
		//GPUデスクプリタヒープハンドルのセット
		for (size_t i = 0; i < m_GPUDescriptorHandleVec.size(); i++) {
			m_CommandList->SetGraphicsRootDescriptorTable(i, m_GPUDescriptorHandleVec[i]);
		}

		auto ShadowMapDimension = Dev->GetShadowMapRenderTarget()->GetShadowMapDimension();


		D3D12_VIEWPORT Viewport = {};
		Viewport.Width = static_cast<float>(ShadowMapDimension);
		Viewport.Height = static_cast<float>(ShadowMapDimension);
		Viewport.MaxDepth = 1.0f;

		D3D12_RECT ScissorRect = {};

		ScissorRect.right = static_cast<LONG>(ShadowMapDimension);
		ScissorRect.bottom = static_cast<LONG>(ShadowMapDimension);


		m_CommandList->RSSetViewports(1, &Viewport);
		m_CommandList->RSSetScissorRects(1, &ScissorRect);

		//デプスステンシルビューのハンドルを取得
		auto SMRenderTarget = Dev->GetShadowMapRenderTarget();
		CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle = SMRenderTarget->GetDsvHandle();
		//取得したハンドルをセット
		m_CommandList->OMSetRenderTargets(0, nullptr, FALSE, &dsvHandle);

		m_CommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_CommandList->IASetVertexBuffers(0, 1, &ShMesh->GetVertexBufferView());
		//インデックスバッファをセット
		m_CommandList->IASetIndexBuffer(&ShMesh->GetIndexBufferView());
		//インデックス描画
		m_CommandList->DrawIndexedInstanced(ShMesh->GetNumIndicis(), 1, 0, 0, 0);
		//コマンドリストのクローズ
		CommandList::Close(m_CommandList);
		//デバイスにコマンドリストを送る
		Dev->InsertDrawCommandLists(m_CommandList.Get());


	}






	//--------------------------------------------------------------------------------------
	//	シャドウマップコンポーネント（前処理用）
	//--------------------------------------------------------------------------------------
	Shadowmap::Shadowmap(const shared_ptr<GameObject>& GameObjectPtr) :
		DrawComponent(GameObjectPtr),
		pImpl(new Impl())
	{}
	Shadowmap::~Shadowmap() {}

	float Shadowmap::GetLightHeight() { return Impl::m_LightHeight; }
	float Shadowmap::GetLightNear() { return  Impl::m_LightNear; }
	float Shadowmap::GetLightFar() { return  Impl::m_LightFar; }
	float Shadowmap::GetViewWidth() { return  Impl::m_ViewWidth; }
	float Shadowmap::GetViewHeight() { return  Impl::m_ViewHeight; }

	void Shadowmap::SetLightHeight(float f) { Impl::m_LightHeight = f; }
	void Shadowmap::SetLightNear(float f) { Impl::m_LightNear = f; }
	void Shadowmap::SetLightFar(float f) { Impl::m_LightFar = f; }
	void Shadowmap::SetViewWidth(float f) { Impl::m_ViewWidth = f; }
	void Shadowmap::SetViewHeight(float f) { Impl::m_ViewHeight = f; }
	void Shadowmap::SetViewSize(float f) { Impl::m_ViewWidth = Impl::m_ViewHeight = f; }

	shared_ptr<MeshResource> Shadowmap::GetMeshResource(bool ExceptionActive) const {
		if (!pImpl->m_MeshResource.expired()) {
			return pImpl->m_MeshResource.lock();
		}
		else {
			if (ExceptionActive) {
				throw BaseException(
					L"メッシュリソースが見つかりません",
					L"if (pImpl->m_MeshResource.expired())",
					L"ShadowmapComp::GetMeshResource()"
				);
			}
		}
		return nullptr;
	}


	void Shadowmap::SetMeshResource(const wstring& ResKey) {
		try {
			if (ResKey == L"") {
				throw BaseException(
					L"メッシュキーが空白です",
					L"if (ResKey == L\"\"",
					L"ShadowmapComp::SetMeshResource()"
				);
			}
			pImpl->m_MeshResource = App::GetApp()->GetResource<MeshResource>(ResKey);
		}
		catch (...) {
			throw;
		}
	}
	void Shadowmap::SetMeshResource(const shared_ptr<MeshResource>& MeshResourcePtr) {
		pImpl->m_MeshResource = MeshResourcePtr;
	}

	void Shadowmap::OnDraw() {
		auto PtrGameObject = GetGameObject();
		auto PtrStage = PtrGameObject->GetStage();
		if (!PtrStage) {
			return;
		}
		//メッシュリソースの取得
		auto PtrMeshResource = GetMeshResource();

		//行列の定義
		Matrix4X4 World, LightView, LightProj;
		//行列の定義
		auto PtrTrans = GetGameObject()->GetComponent<Transform>();
		//ワールド行列の決定
		World = GetMeshToTransformMatrix() * PtrTrans->GetWorldMatrix();
		//ビュー行列の決定
		auto StageView = PtrStage->GetView();
		//ライトの取得
		auto StageLight = PtrStage->GetLight();
		Vector3 LightDir = -1.0 * StageLight->GetTargetLight().m_Directional;
		Vector3 LightAt = StageView->GetTargetCamera()->GetAt();
		Vector3 LightEye = LightAt + (LightDir * GetLightHeight());
		//ライトのビューと射影を計算
		LightView.LookAtLH(LightEye, LightAt, Vector3(0, 1.0f, 0));
		LightProj.OrthographicLH(GetViewWidth(), GetViewHeight(), GetLightNear(), GetLightFar());

		pImpl->m_ShadowConstantBuffer.mWorld = Matrix4X4EX::Transpose(World);
		pImpl->m_ShadowConstantBuffer.mView = Matrix4X4EX::Transpose(LightView);
		pImpl->m_ShadowConstantBuffer.mProj = Matrix4X4EX::Transpose(LightProj);

		pImpl->UpdateConstantBuffer();
		pImpl->DrawObject();
	}

	//--------------------------------------------------------------------------------------
	// static系コンスタントバッファ
	//--------------------------------------------------------------------------------------
	struct StaticConstantBuffer
	{
		Matrix4X4 World;
		Matrix4X4 View;
		Matrix4X4 Projection;
		Color4 Emissive;
		Color4 Diffuse;
		StaticConstantBuffer() {
			memset(this, 0, sizeof(StaticConstantBuffer));
			Diffuse = Color4(1.0f, 1.0f, 1.0f, 1.0f);
		};
	};


	//--------------------------------------------------------------------------------------
	//ParticleDraw準備のための構造体
	//--------------------------------------------------------------------------------------
	struct DrawParticleSprite {
		//パーティクルのカメラまでの距離
		float m_ToCaneraLength;
		//ワールド行列
		Matrix4X4 m_WorldMatrix;
		//テクスチャ
		shared_ptr<TextureResource> m_TextureRes;
		DrawParticleSprite() :
			m_ToCaneraLength(0)
		{}
	};

	//--------------------------------------------------------------------------------------
	//ParticleDrawインスタンス描画のための構造体
	//--------------------------------------------------------------------------------------
	struct InstanceDrawStr {
		size_t Start;
		size_t Count;
		shared_ptr<TextureResource> Tex;
		InstanceDrawStr(size_t s, size_t c, shared_ptr<TextureResource> t) :
			Start(s), Count(c), Tex(t) {}
	};


	//--------------------------------------------------------------------------------------
	//	struct PCTParticleDraw::Impl;
	//	用途: Implイディオム
	//--------------------------------------------------------------------------------------
	struct PCTParticleDraw::Impl {
		shared_ptr<MeshResource> m_MeshResource;	///<メッシュリソース
		shared_ptr<MeshResource> m_InstanceMatrixMesh;	///<マトリクスメッシュ
		vector<DrawParticleSprite> m_DrawParticleSpriteVec;
		const size_t m_MaxInstance;				///<インスタンス最大値
		ComPtr<ID3D11Buffer> m_MatrixBuffer;	///<行列用の頂点バッファ

		///ルートシグネチャ
		ComPtr<ID3D12RootSignature> m_RootSignature;
		///CbvSrvのデスクプリタハンドルのインクリメントサイズ
		UINT m_CbvSrvDescriptorHandleIncrementSize{ 0 };
		///デスクプリタヒープ
		ComPtr<ID3D12DescriptorHeap> m_CbvSrvUavDescriptorHeap;
		ComPtr<ID3D12DescriptorHeap> m_SamplerDescriptorHeap;
		///GPU側デスクプリタのハンドルの配列
		vector<CD3DX12_GPU_DESCRIPTOR_HANDLE> m_GPUDescriptorHandleVec;
		///コンスタントバッファアップロードヒープ
		ComPtr<ID3D12Resource> m_ConstantBufferUploadHeap;
		///コンスタントバッファのGPU側変数
		void* m_pConstantBuffer{ nullptr };
		///パイプラインステート
		ComPtr<ID3D12PipelineState> m_PipelineState;
		///コマンドリスト
		ComPtr<ID3D12GraphicsCommandList> m_CommandList;


		Impl(size_t MaxInstance) :
			m_MaxInstance(MaxInstance)
		{}
		~Impl() {}

		///各初期化関数
		//頂点バッファの作成
		void CreateParticleBuffers();
		///ルートシグネチャ作成
		void CreateRootSignature();
		///デスクプリタヒープ作成
		void CreateDescriptorHeap();
		///サンプラー作成
		void CreateSampler();
		///シェーダーリソースビュー作成
		void CreateShaderResourceView(const shared_ptr<TextureResource>& TexRes);
		///コンスタントバッファ作成
		void CreateConstantBuffer();
		///パイプラインステート作成
		void CreatePipelineState();
		///コマンドリスト作成
		void CreateCommandList();
		//コンスタントバッファ更新
		void UpdateConstantBuffer(const shared_ptr<GameObject>& GameObjectPtr);
		///描画処理
		void DrawObject();



	};

	void PCTParticleDraw::Impl::CreateParticleBuffers() {
		try {
			float HelfSize = 0.5f;
			Vector4 col(1.0f, 1.0f, 1.0f, 1.0f);
			//頂点配列
			vector<VertexPositionColorTexture> vertices = {
				{ VertexPositionColorTexture(Vector3(-HelfSize, HelfSize, 0),  col,Vector2(0.0f, 0.0f)) },
				{ VertexPositionColorTexture(Vector3(HelfSize, HelfSize, 0), col, Vector2(1.0f, 0.0f)) },
				{ VertexPositionColorTexture(Vector3(-HelfSize, -HelfSize, 0),  col,Vector2(0.0f, 1.0f)) },
				{ VertexPositionColorTexture(Vector3(HelfSize, -HelfSize, 0),  col, Vector2(1.0f, 1.0f)) },
			};
			//インデックス配列
			vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
			//メッシュの作成
			m_MeshResource = MeshResource::CreateMeshResource(vertices, indices, false);

			//インスタンス行列バッファの作成
			//Max値で作成する
			vector<Matrix4X4> matrices(m_MaxInstance, Matrix4X4());
			//インスタンス描画用の行列のメッシュ（内容変更できる）
			m_InstanceMatrixMesh = MeshResource::CreateMeshResource(matrices, true);
		}
		catch (...) {
			throw;
		}
	}

	///ルートシグネチャ作成
	void PCTParticleDraw::Impl::CreateRootSignature() {
		//ルートシグネチャ
		m_RootSignature = RootSignature::CreateSrvSmpCbv();
	}
	///デスクプリタヒープ作成
	void PCTParticleDraw::Impl::CreateDescriptorHeap() {
		auto Dev = App::GetApp()->GetDeviceResources();
		m_CbvSrvDescriptorHandleIncrementSize =
			Dev->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		//CbvSrvデスクプリタヒープ
		m_CbvSrvUavDescriptorHeap = DescriptorHeap::CreateCbvSrvUavHeap(1 + 1);
		//サンプラーデスクプリタヒープ
		m_SamplerDescriptorHeap = DescriptorHeap::CreateSamplerHeap(1);
		//GPU側デスクプリタヒープのハンドルの配列の作成
		m_GPUDescriptorHandleVec.clear();
		CD3DX12_GPU_DESCRIPTOR_HANDLE SrvHandle(
			m_CbvSrvUavDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
			0,
			0
		);
		m_GPUDescriptorHandleVec.push_back(SrvHandle);
		CD3DX12_GPU_DESCRIPTOR_HANDLE SamplerHandle(
			m_SamplerDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
			0,
			0
		);
		m_GPUDescriptorHandleVec.push_back(SamplerHandle);
		CD3DX12_GPU_DESCRIPTOR_HANDLE CbvHandle(
			m_CbvSrvUavDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
			1,
			m_CbvSrvDescriptorHandleIncrementSize
		);
		m_GPUDescriptorHandleVec.push_back(CbvHandle);
	}
	///サンプラー作成
	void PCTParticleDraw::Impl::CreateSampler() {
		auto SamplerDescriptorHandle = m_SamplerDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
		DynamicSampler::CreateSampler(SamplerState::LinearClamp, SamplerDescriptorHandle);
	}
	///コンスタントバッファ作成
	void PCTParticleDraw::Impl::CreateConstantBuffer() {
		auto Dev = App::GetApp()->GetDeviceResources();
		//コンスタントバッファは256バイトにアラインメント
		UINT ConstBuffSize = (sizeof(StaticConstantBuffer) + 255) & ~255;

		//コンスタントバッファリソース（アップロードヒープ）の作成
		ThrowIfFailed(Dev->GetDevice()->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(ConstBuffSize),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_ConstantBufferUploadHeap)),
			L"コンスタントバッファ用のアップロードヒープ作成に失敗しました",
			L"Dev->GetDevice()->CreateCommittedResource()",
			L"PCTParticleDraw::Impl::CreateConstantBuffer()"
		);
		//コンスタントバッファのビューを作成
		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
		cbvDesc.BufferLocation = m_ConstantBufferUploadHeap->GetGPUVirtualAddress();
		//コンスタントバッファは256バイトにアラインメント
		cbvDesc.SizeInBytes = ConstBuffSize;
		//コンスタントバッファビューを作成すべきデスクプリタヒープ上のハンドルを取得
		//シェーダリソースがある場合コンスタントバッファはシェーダリソースビューのあとに設置する
		CD3DX12_CPU_DESCRIPTOR_HANDLE cbvSrvHandle(
			m_CbvSrvUavDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
			1,
			m_CbvSrvDescriptorHandleIncrementSize
		);
		Dev->GetDevice()->CreateConstantBufferView(&cbvDesc, cbvSrvHandle);
		//コンスタントバッファのアップロードヒープのマップ
		CD3DX12_RANGE readRange(0, 0);
		ThrowIfFailed(m_ConstantBufferUploadHeap->Map(0, &readRange, reinterpret_cast<void**>(&m_pConstantBuffer)),
			L"コンスタントバッファのマップに失敗しました",
			L"pImpl->m_ConstantBufferUploadHeap->Map()",
			L"PCTParticleDraw::Impl::CreateConstantBuffer()"
		);
	}
	///シェーダーリソースビュー（テクスチャ）作成
	void PCTParticleDraw::Impl::CreateShaderResourceView(const shared_ptr<TextureResource>& TexRes) {
		auto Dev = App::GetApp()->GetDeviceResources();



		m_CommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(
			TexRes->GetTexture().Get(),
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_COPY_DEST));


		//テクスチャハンドルを作成
		CD3DX12_CPU_DESCRIPTOR_HANDLE Handle(
			m_CbvSrvUavDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
			0,
			0
		);
		//テクスチャのシェーダリソースビューを作成
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		//フォーマット
		srvDesc.Format = TexRes->GetTextureResDesc().Format;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = TexRes->GetTextureResDesc().MipLevels;
		//シェーダリソースビュー
		Dev->GetDevice()->CreateShaderResourceView(
			TexRes->GetTexture().Get(),
			&srvDesc,
			Handle);
		m_CommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(
			TexRes->GetTexture().Get(),
			D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));

	}
	///パイプラインステート作成
	void PCTParticleDraw::Impl::CreatePipelineState() {
		//パイプラインステートの作成
		D3D12_GRAPHICS_PIPELINE_STATE_DESC PineLineDesc;
		PipelineState::CreateDefault3D<VertexPositionColorTextureMatrix, VSPCTInstance, PSPCTStatic>(m_RootSignature, PineLineDesc);
		PineLineDesc.RasterizerState.FillMode = D3D12_FILL_MODE::D3D12_FILL_MODE_SOLID;
		PineLineDesc.RasterizerState.CullMode = D3D12_CULL_MODE::D3D12_CULL_MODE_BACK;

		D3D12_BLEND_DESC blend_desc;
		D3D12_RENDER_TARGET_BLEND_DESC Target;
		ZeroMemory(&blend_desc, sizeof(blend_desc));
		blend_desc.AlphaToCoverageEnable = false;
		blend_desc.IndependentBlendEnable = false;
		ZeroMemory(&Target, sizeof(Target));
		Target.BlendEnable = true;
		Target.SrcBlend = D3D12_BLEND_SRC_ALPHA;
		Target.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
		Target.BlendOp = D3D12_BLEND_OP_ADD;
		Target.SrcBlendAlpha = D3D12_BLEND_ONE;
		Target.DestBlendAlpha = D3D12_BLEND_ZERO;
		Target.BlendOpAlpha = D3D12_BLEND_OP_ADD;
		Target.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
		for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; i++) {
			blend_desc.RenderTarget[i] = Target;
		}
		PineLineDesc.BlendState = blend_desc;
		m_PipelineState = PipelineState::CreateDirect(PineLineDesc);
	}
	///コマンドリスト作成
	void PCTParticleDraw::Impl::CreateCommandList() {
		//コマンドリストは裏面カリングに初期化
		m_CommandList = CommandList::CreateDefault(m_PipelineState);
		CommandList::Close(m_CommandList);
	}

	void PCTParticleDraw::Impl::UpdateConstantBuffer(const shared_ptr<GameObject>& GameObjectPtr) {
		//行列の定義
		Matrix4X4 World, ViewMat, ProjMat;

		//カメラを得る
		auto CameraPtr = GameObjectPtr->OnGetDrawCamera();
		//ビューと射影行列を得る
		ViewMat = CameraPtr->GetViewMatrix();
		//転置する
		ViewMat.Transpose();
		//転置する
		ProjMat = CameraPtr->GetProjMatrix();
		ProjMat.Transpose();

		//コンスタントバッファの準備
		StaticConstantBuffer cb;
		cb.World = Matrix4X4();	//ワールド行列はダミー
		cb.View = ViewMat;
		cb.Projection = ProjMat;
		//ディフューズ
		cb.Diffuse = Color4(1.0f, 1.0f, 1.0f, 1.0f);
		//エミッシブ加算は行わない。
		cb.Emissive = Color4(0, 0, 0, 0);
		//更新
		memcpy(m_pConstantBuffer, reinterpret_cast<void**>(&cb),
			sizeof(StaticConstantBuffer));
	}


	///描画処理
	void PCTParticleDraw::Impl::DrawObject() {

		//カメラ位置でソート
		auto func = [](DrawParticleSprite& Left, DrawParticleSprite& Right)->bool {
			return (Left.m_ToCaneraLength > Right.m_ToCaneraLength);
		};
		std::sort(m_DrawParticleSpriteVec.begin(), m_DrawParticleSpriteVec.end(), func);
		//行列の変更
		vector<Matrix4X4> MatVec;
		for (auto& v : m_DrawParticleSpriteVec) {
			Matrix4X4 World = v.m_WorldMatrix;
			//転置する
			World.Transpose();
			MatVec.push_back(World);
		}
		//メッシュの頂点の変更
		m_InstanceMatrixMesh->UpdateVirtex(MatVec);



		//先頭のテクスチャを得る
		auto  NowTexPtr = m_DrawParticleSpriteVec[0].m_TextureRes;

		vector<InstanceDrawStr> InstancVec;
		size_t NowStartIndex = 0;
		size_t NowDrawCount = 0;

		shared_ptr<TextureResource> NowTexRes = m_DrawParticleSpriteVec[0].m_TextureRes;
		for (size_t i = 0; i < m_DrawParticleSpriteVec.size(); i++) {
			if (m_DrawParticleSpriteVec[i].m_TextureRes != NowTexRes) {
				InstancVec.push_back(InstanceDrawStr(NowStartIndex, NowDrawCount, NowTexRes));
				NowStartIndex = i;
				NowDrawCount = 0;
				NowTexRes = m_DrawParticleSpriteVec[i].m_TextureRes;
			}
			else {
				NowDrawCount++;
			}
		}
		InstancVec.push_back(InstanceDrawStr(NowStartIndex, NowDrawCount, NowTexRes));


		CommandList::Reset(m_PipelineState, m_CommandList);

		m_MeshResource->UpdateResources<VertexPositionColorTexture>(m_CommandList);
		m_InstanceMatrixMesh->UpdateResources<Matrix4X4>(m_CommandList);

		auto Dev = App::GetApp()->GetDeviceResources();
		m_CommandList->RSSetViewports(1, &Dev->GetViewport());
		m_CommandList->RSSetScissorRects(1, &Dev->GetScissorRect());


		//描画
		m_CommandList->SetGraphicsRootSignature(m_RootSignature.Get());
		ID3D12DescriptorHeap* ppHeaps[] = { m_CbvSrvUavDescriptorHeap.Get(), m_SamplerDescriptorHeap.Get() };
		m_CommandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

		for (size_t i = 0; i < m_GPUDescriptorHandleVec.size(); i++) {
			m_CommandList->SetGraphicsRootDescriptorTable(i, m_GPUDescriptorHandleVec[i]);
		}

		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(
			Dev->GetRtvHeap()->GetCPUDescriptorHandleForHeapStart(),
			Dev->GetFrameIndex(),
			Dev->GetRtvDescriptorSize());
		CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(
			Dev->GetDsvHeap()->GetCPUDescriptorHandleForHeapStart()
		);
		m_CommandList->OMSetRenderTargets(1, &rtvHandle, FALSE, &dsvHandle);

		m_CommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_CommandList->IASetIndexBuffer(&m_MeshResource->GetIndexBufferView());
		//インスタンス描画は、頂点バッファを複数登録する
		const D3D12_VERTEX_BUFFER_VIEW Buf[2] = {
			m_MeshResource->GetVertexBufferView(),
			m_InstanceMatrixMesh->GetVertexBufferView()
		};
		m_CommandList->IASetVertexBuffers(0, 2, Buf);

		for (auto& v : InstancVec) {
			v.Tex->UpdateResources(m_CommandList);
			CreateShaderResourceView(v.Tex);
			//描画
			m_CommandList->DrawIndexedInstanced(m_MeshResource->GetNumIndicis(), v.Count, 0, 0, v.Start);
		}
		//コマンドリストのクローズ
		CommandList::Close(m_CommandList);
		//デバイスにコマンドリストを送る
		Dev->InsertDrawCommandLists(m_CommandList.Get());


		//パーティクルの配列のクリア
		m_DrawParticleSpriteVec.clear();
	}






	//--------------------------------------------------------------------------------------
	///	PCTParticle描画コンポーネント(パーティクル描画)
	//--------------------------------------------------------------------------------------

	PCTParticleDraw::PCTParticleDraw(const shared_ptr<GameObject>& GameObjectPtr, size_t MaxInstance):
		DrawComponent(GameObjectPtr),
		pImpl(new Impl(MaxInstance))
	{
		//パイプラインステートをデフォルトの3D
		SetBlendState(BlendState::Opaque);
		SetDepthStencilState(DepthStencilState::Default);
		SetRasterizerState(RasterizerState::CullBack);
		SetSamplerState(SamplerState::LinearClamp);
	}
	PCTParticleDraw::~PCTParticleDraw() {}

	void PCTParticleDraw::AddParticle(float ToCaneraLength, const Matrix4X4& WorldMatrix, const shared_ptr<TextureResource>& TextureRes) {
		DrawParticleSprite Item;
		Item.m_ToCaneraLength = ToCaneraLength;
		Item.m_WorldMatrix = WorldMatrix;
		Item.m_TextureRes = TextureRes;
		pImpl->m_DrawParticleSpriteVec.push_back(Item);


	}
	void PCTParticleDraw::OnCreate(){
		pImpl->CreateParticleBuffers();
		///各初期化関数呼び出し
		///ルートシグネチャ作成
		pImpl->CreateRootSignature();
		///デスクプリタヒープ作成
		pImpl->CreateDescriptorHeap();
		///サンプラー作成
		pImpl->CreateSampler();
		///コンスタントバッファ作成
		pImpl->CreateConstantBuffer();
		///パイプラインステート作成
		pImpl->CreatePipelineState();
		///コマンドリスト作成
		pImpl->CreateCommandList();
		//コンスタントバッファの更新
//		pImpl->UpdateConstantBuffer(GetGameObject());

	}
	void PCTParticleDraw::OnDraw(){
		auto PtrStage = GetGameObject()->GetStage();
		if (!PtrStage) {
			return;
		}
		if (pImpl->m_DrawParticleSpriteVec.size() <= 0) {
			return;
		}
		//コンスタントバッファの更新
		pImpl->UpdateConstantBuffer(GetGameObject());
		pImpl->DrawObject();
	}


	//--------------------------------------------------------------------------------------
	//	struct TextureDrawInterface::Impl;
	//--------------------------------------------------------------------------------------
	struct TextureDrawInterface::Impl {
		//テクスチャ
		weak_ptr<TextureResource> m_TextureResource;
		//ラップサンプラーかどうか
		bool m_WrapSampler;
		Impl() :
			m_WrapSampler(false)
		{}
	};

	//--------------------------------------------------------------------------------------
	///	テクスチャ描画インターフェイス
	//--------------------------------------------------------------------------------------
	TextureDrawInterface::TextureDrawInterface() :
		pImpl(new Impl())
	{}

	TextureDrawInterface::~TextureDrawInterface() {}

	void TextureDrawInterface::SetTextureResource(const shared_ptr<TextureResource>& TextureRes) {
		pImpl->m_TextureResource = TextureRes;
	}

	void TextureDrawInterface::SetTextureResource(const wstring& TextureKey) {
		auto Res = App::GetApp()->GetResource<TextureResource>(TextureKey);
		pImpl->m_TextureResource = Res;
	}

	shared_ptr<TextureResource> TextureDrawInterface::GetTextureResource() const {
		//テクスチャがなければnullを返す
		auto shptr = pImpl->m_TextureResource.lock();
		if (!shptr) {
			return nullptr;
		}
		return shptr;
	}

	bool TextureDrawInterface::GetWrapSampler() const {
		return pImpl->m_WrapSampler;

	}
	void TextureDrawInterface::SetWrapSampler(bool b) {
		pImpl->m_WrapSampler = b;
	}



	//--------------------------------------------------------------------------------------
	//	struct SpriteBaseDraw::Impl;
	//	用途: SpriteBaseDrawイディオム
	//--------------------------------------------------------------------------------------
	struct SpriteBaseDraw::Impl {
		//メッシュ
		shared_ptr<MeshResource> m_SpriteMesh;
		//エミッシブ色
		Color4 m_Emissive;
		//デフューズ色
		Color4 m_Diffuse;
		Impl() :
			m_Emissive(0, 0, 0, 0),
			m_Diffuse(1.0f, 1.0f, 1.0f, 1.0f)
		{}
	};

	//--------------------------------------------------------------------------------------
	//	class SpriteBaseDraw : public DrawComponent;
	//--------------------------------------------------------------------------------------
	SpriteBaseDraw::SpriteBaseDraw(const shared_ptr<GameObject>& GameObjectPtr) :
		DrawComponent(GameObjectPtr),
		pImpl(new Impl())
	{}
	SpriteBaseDraw::~SpriteBaseDraw() {}


	shared_ptr<MeshResource> SpriteBaseDraw::GetMeshResource() const {
		return pImpl->m_SpriteMesh;
	}
	void SpriteBaseDraw::SetMeshResource(const shared_ptr<MeshResource>& MeshRes) {
		pImpl->m_SpriteMesh = MeshRes;
	}


	Color4 SpriteBaseDraw::GetEmissive() const {
		return pImpl->m_Emissive;
	}
	void SpriteBaseDraw::SetEmissive(const Color4& col) {
		pImpl->m_Emissive = col;
	}

	Color4 SpriteBaseDraw::GetDiffuse() const {
		return pImpl->m_Diffuse;
	}
	void SpriteBaseDraw::SetDiffuse(const Color4& col) {
		pImpl->m_Diffuse = col;
	}

	//--------------------------------------------------------------------------------------
	//	スプライト用コンスタントバッファ
	//--------------------------------------------------------------------------------------
	struct SpriteConstantBuffer
	{
		Matrix4X4 World;
		Color4 Emissive;
		Color4 Diffuse;
		SpriteConstantBuffer() {
			memset(this, 0, sizeof(SpriteConstantBuffer));
			Diffuse = Color4(1.0f, 1.0f, 1.0f, 1.0f);
		};
	};

	//--------------------------------------------------------------------------------------
	//	struct PCSpriteDraw::Impl;
	//--------------------------------------------------------------------------------------
	struct PCSpriteDraw::Impl {
		///ルートシグネチャ
		ComPtr<ID3D12RootSignature> m_RootSignature;
		///CbvSrvのデスクプリタハンドルのインクリメントサイズ
		UINT m_CbvSrvDescriptorHandleIncrementSize{ 0 };
		///デスクプリタヒープ
		ComPtr<ID3D12DescriptorHeap> m_CbvSrvUavDescriptorHeap;
		///GPU側デスクプリタのハンドルの配列
		vector<CD3DX12_GPU_DESCRIPTOR_HANDLE> m_GPUDescriptorHandleVec;
		///コンスタントバッファアップロードヒープ
		ComPtr<ID3D12Resource> m_ConstantBufferUploadHeap;
		///コンスタントバッファのGPU側変数
		void* m_pConstantBuffer{ nullptr };
		//パイプラインステート
		ComPtr<ID3D12PipelineState> m_PipelineState;
		bool m_Trace;
		///コマンドリスト
		ComPtr<ID3D12GraphicsCommandList> m_CommandList;
		///ルートシグネチャ作成
		void CreateRootSignature();
		///デスクプリタヒープ作成
		void CreateDescriptorHeap();
		///コンスタントバッファ作成
		void CreateConstantBuffer();
		///パイプラインステート作成
		void CreatePipelineState();
		///コマンドリスト作成
		void CreateCommandList();
		//コンスタントバッファ更新
		void UpdateConstantBuffer(const shared_ptr<GameObject>& GameObjectPtr,
			const Color4& Emissive, const Color4& Diffuse);
		///描画処理
		void DrawObject(const shared_ptr<MeshResource>& MeshRes,bool Trace);
		Impl():
			m_Trace(false)
		{}
	};

	///ルートシグネチャ作成
	void PCSpriteDraw::Impl::CreateRootSignature() {
		//コンスタントバッファ付ルートシグネチャ
		m_RootSignature = RootSignature::CreateCbv();
	}
	///デスクプリタヒープ作成
	void PCSpriteDraw::Impl::CreateDescriptorHeap() {
		auto Dev = App::GetApp()->GetDeviceResources();
		m_CbvSrvDescriptorHandleIncrementSize
			= Dev->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		//CbvSrvデスクプリタヒープ(コンスタントバッファのみ)
		m_CbvSrvUavDescriptorHeap = DescriptorHeap::CreateCbvSrvUavHeap(1);
		//GPU側デスクプリタヒープのハンドルの配列の作成
		m_GPUDescriptorHandleVec.clear();
		CD3DX12_GPU_DESCRIPTOR_HANDLE CbvHandle(
			m_CbvSrvUavDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
			0,
			0
		);
		m_GPUDescriptorHandleVec.push_back(CbvHandle);
	}
	///コンスタントバッファ作成
	void PCSpriteDraw::Impl::CreateConstantBuffer() {
		auto Dev = App::GetApp()->GetDeviceResources();
		//コンスタントバッファは256バイトにアラインメント
		UINT ConstBuffSize = (sizeof(SpriteConstantBuffer) + 255) & ~255;
		ThrowIfFailed(Dev->GetDevice()->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(ConstBuffSize),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_ConstantBufferUploadHeap)),
			L"コンスタントバッファ用のアップロードヒープ作成に失敗しました",
			L"Dev->GetDevice()->CreateCommittedResource()",
			L"PCSpriteDraw::Impl::CreateConstantBuffer()"
		);
		//コンスタントバッファのビューを作成
		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
		cbvDesc.BufferLocation = m_ConstantBufferUploadHeap->GetGPUVirtualAddress();
		cbvDesc.SizeInBytes = ConstBuffSize;
		//コンスタントバッファビューを作成すべきデスクプリタヒープ上のハンドルを取得
		//シェーダリソースがある場合コンスタントバッファはシェーダリソースビューのあとに設置する
		CD3DX12_CPU_DESCRIPTOR_HANDLE cbvSrvHandle(
			m_CbvSrvUavDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
			0,
			0
		);
		Dev->GetDevice()->CreateConstantBufferView(&cbvDesc, cbvSrvHandle);
		//コンスタントバッファのアップロードヒープのマップ
		CD3DX12_RANGE readRange(0, 0);
		ThrowIfFailed(m_ConstantBufferUploadHeap->Map(0, &readRange, reinterpret_cast<void**>(&m_pConstantBuffer)),
			L"コンスタントバッファのマップに失敗しました",
			L"pImpl->m_ConstantBufferUploadHeap->Map()",
			L"PCSpriteDraw::Impl::CreateConstantBuffer()"
		);
	}
	///パイプラインステート作成
	void PCSpriteDraw::Impl::CreatePipelineState() {
		D3D12_GRAPHICS_PIPELINE_STATE_DESC PineLineDesc;
		m_PipelineState
			= PipelineState::CreateDefault2D<VertexPositionColor, VSPCSprite, PSPCSprite>(m_RootSignature, PineLineDesc);
	}
	///コマンドリスト作成
	void PCSpriteDraw::Impl::CreateCommandList() {
		m_CommandList = CommandList::CreateDefault(m_PipelineState);
		CommandList::Close(m_CommandList);
	}

	void PCSpriteDraw::Impl::UpdateConstantBuffer(const shared_ptr<GameObject>& GameObjectPtr,
		const Color4& Emissive, const Color4& Diffuse) {
		//行列の定義
		auto PtrTrans = GameObjectPtr->GetComponent<Transform>();
		Vector2 Scale, Pos, Pivot;
		Scale.x = PtrTrans->GetScale().x;
		Scale.y = PtrTrans->GetScale().y;
		Pos.x = PtrTrans->GetPosition().x;
		Pos.y = PtrTrans->GetPosition().y;
		Pivot.x = PtrTrans->GetPivot().x;
		Pivot.y = PtrTrans->GetPivot().y;
		Vector3 Rot = PtrTrans->GetRotation();

		//行列の定義
		Matrix4X4 World, Proj;
		//ワールド行列の決定
		World.AffineTransformation2D(
			Scale,			//スケーリング
			Pivot,		//回転の中心（重心）
			Rot.z,			//回転角度(Z軸回転)
			Pos				//位置
		);
		//射影行列の決定
		GameObjectPtr->OnGet2DDrawProjMatrix(Proj);
		//行列の合成
		World *= Proj;
		//コンスタントバッファ
		SpriteConstantBuffer cb;
		//エミッシブ
		cb.Emissive = Emissive;
		//デフィーズはすべて通す
		cb.Diffuse = Diffuse;
		//行列の設定
		cb.World = World;
		//更新
		memcpy(m_pConstantBuffer, reinterpret_cast<void**>(&cb),
			sizeof(SpriteConstantBuffer));
	}


	///描画処理
	void PCSpriteDraw::Impl::DrawObject(const shared_ptr<MeshResource>& MeshRes, bool Trace) {
		auto Dev = App::GetApp()->GetDeviceResources();
		if (m_Trace != Trace) {
			D3D12_GRAPHICS_PIPELINE_STATE_DESC PineLineDesc;
			m_PipelineState = PipelineState::CreateDefault2D<VertexPositionColor, VSPCSprite, PSPCSprite>(m_RootSignature, PineLineDesc);
			//透明の場合はブレンドステート差し替え
			if (Trace) {
				D3D12_BLEND_DESC blend_desc;
				D3D12_RENDER_TARGET_BLEND_DESC Target;
				ZeroMemory(&blend_desc, sizeof(blend_desc));
				blend_desc.AlphaToCoverageEnable = false;
				blend_desc.IndependentBlendEnable = false;
				ZeroMemory(&Target, sizeof(Target));
				Target.BlendEnable = true;
				Target.SrcBlend = D3D12_BLEND_SRC_ALPHA;
				Target.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
				Target.BlendOp = D3D12_BLEND_OP_ADD;
				Target.SrcBlendAlpha = D3D12_BLEND_ONE;
				Target.DestBlendAlpha = D3D12_BLEND_ZERO;
				Target.BlendOpAlpha = D3D12_BLEND_OP_ADD;
				Target.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
				for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; i++) {
					blend_desc.RenderTarget[i] = Target;
				}
				PineLineDesc.BlendState = blend_desc;
				m_PipelineState = PipelineState::CreateDirect(PineLineDesc);
				m_Trace = Trace;
			}
		}
		//コマンドリストのリセット
		CommandList::Reset(m_PipelineState, m_CommandList);
		//メッシュが更新されていればリソース更新
		MeshRes->UpdateResources<VertexPositionColor>(m_CommandList);
		//ルートシグネチャのセット
		m_CommandList->SetGraphicsRootSignature(m_RootSignature.Get());
		//デスクプリタヒープのセット
		ID3D12DescriptorHeap* ppHeaps[] = { m_CbvSrvUavDescriptorHeap.Get() };
		m_CommandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
		//GPUデスクプリタヒープハンドルのセット
		for (size_t i = 0; i < m_GPUDescriptorHandleVec.size(); i++) {
			m_CommandList->SetGraphicsRootDescriptorTable(i, m_GPUDescriptorHandleVec[i]);
		}
		//ビューポートのセット
		m_CommandList->RSSetViewports(1, &Dev->GetViewport());
		//シザー矩形（クリップ矩形）のセット
		m_CommandList->RSSetScissorRects(1, &Dev->GetScissorRect());

		//レンダーターゲットビューのハンドルを取得
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle = Dev->GetRtvHandle();
		//デプスステンシルビューのハンドルを取得
		CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle = Dev->GetDsvHandle();
		//取得したハンドルをセット
		m_CommandList->OMSetRenderTargets(1, &rtvHandle, FALSE, &dsvHandle);
		//描画方法のセット（三角形リスト）
		m_CommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		//頂点バッファのセット
		m_CommandList->IASetVertexBuffers(0, 1, &MeshRes->GetVertexBufferView());
		//インデックスバッファをセット
		m_CommandList->IASetIndexBuffer(&MeshRes->GetIndexBufferView());
		//インデックス描画
		m_CommandList->DrawIndexedInstanced(MeshRes->GetNumIndicis(), 1, 0, 0, 0);

		//コマンドリストのクローズ
		CommandList::Close(m_CommandList);
		//デバイスにコマンドリストを送る
		Dev->InsertDrawCommandLists(m_CommandList.Get());


	}






	//--------------------------------------------------------------------------------------
	///	PCSprite描画コンポーネント
	//--------------------------------------------------------------------------------------
	PCSpriteDraw::PCSpriteDraw(const shared_ptr<GameObject>& GameObjectPtr) :
		SpriteBaseDraw(GameObjectPtr),
		pImpl(new Impl())
	{
		//パイプラインステートをデフォルトの2D
		SetBlendState(BlendState::Opaque);
		SetDepthStencilState(DepthStencilState::None);
		SetRasterizerState(RasterizerState::CullBack);
		SetSamplerState(SamplerState::LinearClamp);
	}
	PCSpriteDraw::PCSpriteDraw(const shared_ptr<GameObject>& GameObjectPtr,
		vector<VertexPositionColor>& Vertices, vector<uint16_t>& indices) :
		SpriteBaseDraw(GameObjectPtr),
		pImpl(new Impl())
	{
		try {
			//パイプラインステートをデフォルトの2D
			SetBlendState(BlendState::Opaque);
			SetDepthStencilState(DepthStencilState::None);
			SetRasterizerState(RasterizerState::CullBack);
			SetSamplerState(SamplerState::LinearClamp);
			//メッシュの作成（変更できる）
			auto SpriteMesh = MeshResource::CreateMeshResource(Vertices, indices, true);
			SetMeshResource(SpriteMesh);
		}
		catch (...) {
			throw;
		}
	}

	PCSpriteDraw::~PCSpriteDraw() {}

	void PCSpriteDraw::CreateMesh(vector<VertexPositionColor>& Vertices, vector<uint16_t>& indices) {
		try {
			//メッシュの作成（変更できる）
			auto SpriteMesh = MeshResource::CreateMeshResource(Vertices, indices, true);
			SetMeshResource(SpriteMesh);
		}
		catch (...) {
			throw;
		}
	}

	void PCSpriteDraw::UpdateVertices(const vector<VertexPositionColor>& Vertices) {
		auto SpriteMesh = GetMeshResource();
		if (!SpriteMesh) {
			throw BaseException(
				L"メッシュが作成されていません",
				L"if (!SpriteMesh)",
				L"PCSpriteDraw::UpdateVertices()"
			);
		}
		//メッシュの頂点の変更
		SpriteMesh->UpdateVirtex(Vertices);
	}
	void PCSpriteDraw::OnCreate() {
		auto SpriteMesh = GetMeshResource();
		if (!SpriteMesh) {
			//作成されてなかったら作成する
			float HelfSize = 0.5f;
			//頂点配列
			vector<VertexPositionColor> Vertices = {
				{ VertexPositionColor(Vector3(-HelfSize, HelfSize, 0), Color4(1.0f,1.0f,1.0f,1.0f)) },
				{ VertexPositionColor(Vector3(HelfSize, HelfSize, 0), Color4(1.0f,1.0f,1.0f,1.0f)) },
				{ VertexPositionColor(Vector3(-HelfSize, -HelfSize, 0), Color4(1.0f,1.0f,1.0f,1.0f)) },
				{ VertexPositionColor(Vector3(HelfSize, -HelfSize, 0), Color4(1.0f,1.0f,1.0f,1.0f)) },
			};
			//インデックス配列
			vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
			//メッシュの作成（変更できる）
			SpriteMesh = MeshResource::CreateMeshResource(Vertices, indices, true);
			SetMeshResource(SpriteMesh);
		}
		///ルートシグネチャ作成
		pImpl->CreateRootSignature();
		///デスクプリタヒープ作成
		pImpl->CreateDescriptorHeap();
		///コンスタントバッファ作成
		pImpl->CreateConstantBuffer();
		///パイプラインステート作成
		pImpl->CreatePipelineState();
		///コマンドリスト作成
		pImpl->CreateCommandList();
		//コンスタントバッファの更新
		pImpl->UpdateConstantBuffer(GetGameObject(),
			GetEmissive(), GetDiffuse());
	}
	void PCSpriteDraw::OnDraw() {
		//メッシュがなければ描画しない
		auto SpriteMesh = GetMeshResource();
		if (!SpriteMesh) {
			throw BaseException(
				L"メッシュが作成されていません",
				L"if (!SpriteMesh)",
				L"PCSpriteDraw::OnDraw()"
			);
		}
		//コンスタントバッファの更新
		pImpl->UpdateConstantBuffer(GetGameObject(),
			GetEmissive(), GetDiffuse());
		pImpl->DrawObject(SpriteMesh, GetGameObject()->IsAlphaActive());
	}



	//--------------------------------------------------------------------------------------
	//	struct PTSpriteDraw::Impl;
	//--------------------------------------------------------------------------------------
	struct PTSpriteDraw::Impl {
		///ルートシグネチャ
		ComPtr<ID3D12RootSignature> m_RootSignature;
		///CbvSrvのデスクプリタハンドルのインクリメントサイズ
		UINT m_CbvSrvDescriptorHandleIncrementSize{ 0 };
		///デスクプリタヒープ
		ComPtr<ID3D12DescriptorHeap> m_CbvSrvUavDescriptorHeap;
		ComPtr<ID3D12DescriptorHeap> m_SamplerDescriptorHeap;
		///GPU側デスクプリタのハンドルの配列
		vector<CD3DX12_GPU_DESCRIPTOR_HANDLE> m_GPUDescriptorHandleVec;
		///コンスタントバッファアップロードヒープ
		ComPtr<ID3D12Resource> m_ConstantBufferUploadHeap;
		///コンスタントバッファのGPU側変数
		void* m_pConstantBuffer{ nullptr };
		///パイプラインステート
		ComPtr<ID3D12PipelineState> m_PipelineState;
		bool m_Trace;
		///コマンドリスト
		ComPtr<ID3D12GraphicsCommandList> m_CommandList;
		///各初期化関数
		///ルートシグネチャ作成
		void CreateRootSignature();
		///デスクプリタヒープ作成
		void CreateDescriptorHeap();
		///サンプラー作成
		void CreateSampler();
		bool m_Wrap;
		///シェーダーリソースビュー作成
		void CreateShaderResourceView(const shared_ptr<TextureResource>& TextureRes);
		///コンスタントバッファ作成
		void CreateConstantBuffer();
		///パイプラインステート作成
		void CreatePipelineState();
		///コマンドリスト作成
		void CreateCommandList();
		///コンスタントバッファ更新
		void UpdateConstantBuffer(const shared_ptr<GameObject>& GameObjectPtr,
			const Color4& Emissive, const Color4& Diffuse);
		///描画処理
		void DrawObject(const shared_ptr<MeshResource>& MeshRes, bool Trace,
			const shared_ptr<TextureResource>& TextureRes, bool WrapSampler);
		Impl():
			m_Trace(false),
			m_Wrap(false)
		{}
	};

	///ルートシグネチャ作成
	void PTSpriteDraw::Impl::CreateRootSignature() {
		//ルートシグネチャ
		m_RootSignature = RootSignature::CreateSrvSmpCbv();
	}
	///デスクプリタヒープ作成
	void PTSpriteDraw::Impl::CreateDescriptorHeap() {
		auto Dev = App::GetApp()->GetDeviceResources();
		m_CbvSrvDescriptorHandleIncrementSize =
			Dev->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		//CbvSrvデスクプリタヒープ
		m_CbvSrvUavDescriptorHeap = DescriptorHeap::CreateCbvSrvUavHeap(1 + 1);
		//サンプラーデスクプリタヒープ
		m_SamplerDescriptorHeap = DescriptorHeap::CreateSamplerHeap(1);
		//GPU側デスクプリタヒープのハンドルの配列の作成
		m_GPUDescriptorHandleVec.clear();
		CD3DX12_GPU_DESCRIPTOR_HANDLE SrvHandle(
			m_CbvSrvUavDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
			0,
			0
		);
		m_GPUDescriptorHandleVec.push_back(SrvHandle);
		CD3DX12_GPU_DESCRIPTOR_HANDLE SamplerHandle(
			m_SamplerDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
			0,
			0
		);
		m_GPUDescriptorHandleVec.push_back(SamplerHandle);
		CD3DX12_GPU_DESCRIPTOR_HANDLE CbvHandle(
			m_CbvSrvUavDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
			1,
			m_CbvSrvDescriptorHandleIncrementSize
		);
		m_GPUDescriptorHandleVec.push_back(CbvHandle);
	}
	///サンプラー作成
	void PTSpriteDraw::Impl::CreateSampler() {
		auto SamplerDescriptorHandle = m_SamplerDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
		DynamicSampler::CreateSampler(SamplerState::LinearClamp, SamplerDescriptorHandle);
	}
	///シェーダーリソースビュー作成
	void PTSpriteDraw::Impl::CreateShaderResourceView(const shared_ptr<TextureResource>& TextureRes) {
		auto Dev = App::GetApp()->GetDeviceResources();
		//テクスチャハンドルを作成
		CD3DX12_CPU_DESCRIPTOR_HANDLE Handle(
			m_CbvSrvUavDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
			0,
			0
		);
		//テクスチャのシェーダリソースビューを作成
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		//フォーマット
		srvDesc.Format = TextureRes->GetTextureResDesc().Format;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = TextureRes->GetTextureResDesc().MipLevels;
		//シェーダリソースビュー
		Dev->GetDevice()->CreateShaderResourceView(
			TextureRes->GetTexture().Get(),
			&srvDesc,
			Handle);
	}
	///コンスタントバッファ作成
	void PTSpriteDraw::Impl::CreateConstantBuffer() {
		auto Dev = App::GetApp()->GetDeviceResources();
		//コンスタントバッファは256バイトにアラインメント
		UINT ConstBuffSize = (sizeof(SpriteConstantBuffer) + 255) & ~255;

		//コンスタントバッファリソース（アップロードヒープ）の作成
		ThrowIfFailed(Dev->GetDevice()->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(ConstBuffSize),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_ConstantBufferUploadHeap)),
			L"コンスタントバッファ用のアップロードヒープ作成に失敗しました",
			L"Dev->GetDevice()->CreateCommittedResource()",
			L"PTSpriteDraw::Impl::CreateConstantBuffer()"
		);
		//コンスタントバッファのビューを作成
		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
		cbvDesc.BufferLocation = m_ConstantBufferUploadHeap->GetGPUVirtualAddress();
		//コンスタントバッファは256バイトにアラインメント
		cbvDesc.SizeInBytes = ConstBuffSize;
		//コンスタントバッファビューを作成すべきデスクプリタヒープ上のハンドルを取得
		//シェーダリソースがある場合コンスタントバッファはシェーダリソースビューのあとに設置する
		CD3DX12_CPU_DESCRIPTOR_HANDLE cbvSrvHandle(
			m_CbvSrvUavDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
			1,
			m_CbvSrvDescriptorHandleIncrementSize
		);
		Dev->GetDevice()->CreateConstantBufferView(&cbvDesc, cbvSrvHandle);
		//コンスタントバッファのアップロードヒープのマップ
		CD3DX12_RANGE readRange(0, 0);
		ThrowIfFailed(m_ConstantBufferUploadHeap->Map(0, &readRange, reinterpret_cast<void**>(&m_pConstantBuffer)),
			L"コンスタントバッファのマップに失敗しました",
			L"pImpl->m_ConstantBufferUploadHeap->Map()",
			L"PTSpriteDraw::Impl::CreateConstantBuffer()"
		);
	}
	///パイプラインステート作成
	void PTSpriteDraw::Impl::CreatePipelineState() {
		D3D12_GRAPHICS_PIPELINE_STATE_DESC PineLineDesc;
		m_PipelineState
			= PipelineState::CreateDefault2D<VertexPositionTexture, VSPTSprite, PSPTSprite>(m_RootSignature, PineLineDesc);
	}
	///コマンドリスト作成
	void PTSpriteDraw::Impl::CreateCommandList() {
		m_CommandList = CommandList::CreateDefault(m_PipelineState);
		CommandList::Close(m_CommandList);
	}

	///コンスタントバッファ更新
	void PTSpriteDraw::Impl::UpdateConstantBuffer(const shared_ptr<GameObject>& GameObjectPtr,
		const Color4& Emissive, const Color4& Diffuse) {
		//行列の定義
		auto PtrTrans = GameObjectPtr->GetComponent<Transform>();
		Vector2 Scale, Pos, Pivot;
		Scale.x = PtrTrans->GetScale().x;
		Scale.y = PtrTrans->GetScale().y;
		Pos.x = PtrTrans->GetPosition().x;
		Pos.y = PtrTrans->GetPosition().y;
		Pivot.x = PtrTrans->GetPivot().x;
		Pivot.y = PtrTrans->GetPivot().y;
		Vector3 Rot = PtrTrans->GetRotation();

		//行列の定義
		Matrix4X4 World, Proj;
		//ワールド行列の決定
		World.AffineTransformation2D(
			Scale,			//スケーリング
			Pivot,		//回転の中心（重心）
			Rot.z,			//回転角度(Z軸回転)
			Pos				//位置
		);
		//射影行列の決定
		GameObjectPtr->OnGet2DDrawProjMatrix(Proj);
		//行列の合成
		World *= Proj;
		SpriteConstantBuffer cb;
		//エミッシブ
		cb.Emissive = Emissive;
		//デフィーズはすべて通す
		cb.Diffuse = Diffuse;
		//行列の設定
		cb.World = World;
		//更新
		memcpy(m_pConstantBuffer, reinterpret_cast<void**>(&cb),
			sizeof(SpriteConstantBuffer));

	}
	///描画処理
	void PTSpriteDraw::Impl::DrawObject(const shared_ptr<MeshResource>& MeshRes, bool Trace,
		const shared_ptr<TextureResource>& TextureRes, bool WrapSampler) {
		if (m_Wrap != WrapSampler) {
			auto SamplerDescriptorHandle = m_SamplerDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
			if (WrapSampler) {
				//ラッピングサンプラー
				DynamicSampler::CreateSampler(SamplerState::LinearWrap, SamplerDescriptorHandle);
			}
			else {
				DynamicSampler::CreateSampler(SamplerState::LinearClamp, SamplerDescriptorHandle);
			}
			m_Wrap = WrapSampler;
		}
		if (m_Trace != Trace) {
			D3D12_GRAPHICS_PIPELINE_STATE_DESC PineLineDesc;
			m_PipelineState = PipelineState::CreateDefault2D<VertexPositionTexture, VSPTSprite, PSPTSprite>(m_RootSignature, PineLineDesc);
			//透明の場合はブレンドステート差し替え
			if (Trace) {
				D3D12_BLEND_DESC blend_desc;
				D3D12_RENDER_TARGET_BLEND_DESC Target;
				ZeroMemory(&blend_desc, sizeof(blend_desc));
				blend_desc.AlphaToCoverageEnable = false;
				blend_desc.IndependentBlendEnable = false;
				ZeroMemory(&Target, sizeof(Target));
				Target.BlendEnable = true;
				Target.SrcBlend = D3D12_BLEND_SRC_ALPHA;
				Target.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
				Target.BlendOp = D3D12_BLEND_OP_ADD;
				Target.SrcBlendAlpha = D3D12_BLEND_ONE;
				Target.DestBlendAlpha = D3D12_BLEND_ZERO;
				Target.BlendOpAlpha = D3D12_BLEND_OP_ADD;
				Target.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
				for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; i++) {
					blend_desc.RenderTarget[i] = Target;
				}
				PineLineDesc.BlendState = blend_desc;
				m_PipelineState = PipelineState::CreateDirect(PineLineDesc);
				m_Trace = Trace;
			}
		}
		//コマンドリストのリセット
		CommandList::Reset(m_PipelineState, m_CommandList);

		MeshRes->UpdateResources<VertexPositionTexture>(m_CommandList);
		TextureRes->UpdateResources(m_CommandList);

		//描画
		m_CommandList->SetGraphicsRootSignature(m_RootSignature.Get());
		ID3D12DescriptorHeap* ppHeaps[] = { m_CbvSrvUavDescriptorHeap.Get(), m_SamplerDescriptorHeap.Get() };
		m_CommandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
		for (size_t i = 0; i < m_GPUDescriptorHandleVec.size(); i++) {
			m_CommandList->SetGraphicsRootDescriptorTable(i, m_GPUDescriptorHandleVec[i]);
		}
		auto Dev = App::GetApp()->GetDeviceResources();
		m_CommandList->RSSetViewports(1, &Dev->GetViewport());
		m_CommandList->RSSetScissorRects(1, &Dev->GetScissorRect());

		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(
			Dev->GetRtvHeap()->GetCPUDescriptorHandleForHeapStart(),
			Dev->GetFrameIndex(),
			Dev->GetRtvDescriptorSize());
		CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(
			Dev->GetDsvHeap()->GetCPUDescriptorHandleForHeapStart()
		);
		m_CommandList->OMSetRenderTargets(1, &rtvHandle, FALSE, &dsvHandle);

		m_CommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_CommandList->IASetIndexBuffer(&MeshRes->GetIndexBufferView());
		m_CommandList->IASetVertexBuffers(0, 1, &MeshRes->GetVertexBufferView());
		m_CommandList->DrawIndexedInstanced(MeshRes->GetNumIndicis(), 1, 0, 0, 0);

		//コマンドリストのクローズ
		CommandList::Close(m_CommandList);
		//デバイスにコマンドリストを送る
		Dev->InsertDrawCommandLists(m_CommandList.Get());
	}



	//--------------------------------------------------------------------------------------
	///	PTSprite描画コンポーネント
	//--------------------------------------------------------------------------------------
	PTSpriteDraw::PTSpriteDraw(const shared_ptr<GameObject>& GameObjectPtr) :
		SpriteBaseDraw(GameObjectPtr),
		pImpl(new Impl())
	{
		//パイプラインステートをデフォルトの2D
		SetBlendState(BlendState::Opaque);
		SetDepthStencilState(DepthStencilState::None);
		SetRasterizerState(RasterizerState::CullBack);
		SetSamplerState(SamplerState::LinearClamp);
	}

	PTSpriteDraw::PTSpriteDraw(const shared_ptr<GameObject>& GameObjectPtr,
		vector<VertexPositionTexture>& Vertices, vector<uint16_t>& indices) :
		SpriteBaseDraw(GameObjectPtr),
		pImpl(new Impl())
	{
		try {
			//パイプラインステートをデフォルトの2D
			SetBlendState(BlendState::Opaque);
			SetDepthStencilState(DepthStencilState::None);
			SetRasterizerState(RasterizerState::CullBack);
			SetSamplerState(SamplerState::LinearClamp);
			//メッシュの作成（変更できる）
			auto SpriteMesh = MeshResource::CreateMeshResource(Vertices, indices, true);
			SetMeshResource(SpriteMesh);
		}
		catch (...) {
			throw;
		}
	}

	PTSpriteDraw::~PTSpriteDraw() {}

	void PTSpriteDraw::CreateMesh(vector<VertexPositionTexture>& Vertices, vector<uint16_t>& indices) {
		try {
			//メッシュの作成（変更できる）
			auto SpriteMesh = MeshResource::CreateMeshResource(Vertices, indices, true);
			SetMeshResource(SpriteMesh);
		}
		catch (...) {
			throw;
		}
	}

	void PTSpriteDraw::UpdateVertices(const vector<VertexPositionTexture>& Vertices) {
		auto SpriteMesh = GetMeshResource();
		if (!SpriteMesh) {
			throw BaseException(
				L"メッシュが作成されていません",
				L"if (!SpriteMesh)",
				L"PTSpriteDraw::UpdateVertices()"
			);
		}
		//メッシュの頂点の変更
		SpriteMesh->UpdateVirtex(Vertices);
	}

	void PTSpriteDraw::SetTextureResource(const shared_ptr<TextureResource>& TextureRes) {
		TextureDrawInterface::SetTextureResource(TextureRes);
		pImpl->CreateShaderResourceView(TextureRes);
	}
	void PTSpriteDraw::SetTextureResource(const wstring& TextureKey) {
		TextureDrawInterface::SetTextureResource(TextureKey);
		pImpl->CreateShaderResourceView(GetTextureResource());
	}


	void PTSpriteDraw::OnCreate() {
		auto SpriteMesh = GetMeshResource();
		if (!SpriteMesh) {
			//作成されてなかったら作成する
			float HelfSize = 0.5f;
			//頂点配列
			vector<VertexPositionTexture> Vertices = {
				{ VertexPositionTexture(Vector3(-HelfSize, HelfSize, 0), Vector2(0.0f, 0.0f)) },
				{ VertexPositionTexture(Vector3(HelfSize, HelfSize, 0), Vector2(1.0f, 0.0f)) },
				{ VertexPositionTexture(Vector3(-HelfSize, -HelfSize, 0), Vector2(0.0f, 1.0f)) },
				{ VertexPositionTexture(Vector3(HelfSize, -HelfSize, 0), Vector2(1.0f, 1.0f)) },
			};
			//インデックス配列
			vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
			//メッシュの作成（変更できる）
			SpriteMesh = MeshResource::CreateMeshResource(Vertices, indices, true);
			SetMeshResource(SpriteMesh);
		}
		///ルートシグネチャ作成
		pImpl->CreateRootSignature();
		///デスクプリタヒープ作成
		pImpl->CreateDescriptorHeap();
		///サンプラー作成
		pImpl->CreateSampler();
		///コンスタントバッファ作成
		pImpl->CreateConstantBuffer();
		///パイプラインステート作成
		pImpl->CreatePipelineState();
		///コマンドリスト作成
		pImpl->CreateCommandList();
		//コンスタントバッファの更新
		pImpl->UpdateConstantBuffer(GetGameObject(),
			GetEmissive(), GetDiffuse());

	}

	void PTSpriteDraw::OnDraw() {
		//メッシュがなければ描画しない
		auto SpriteMesh = GetMeshResource();
		if (!SpriteMesh) {
			throw BaseException(
				L"メッシュが作成されていません",
				L"if (!SpriteMesh)",
				L"PCSpriteDraw::OnDraw()"
			);
		}
		//テクスチャがなければ描画しない
		auto shTex = GetTextureResource();
		if (!shTex) {
			return;
		}
		//コンスタントバッファの更新
		pImpl->UpdateConstantBuffer(GetGameObject(),
			GetEmissive(), GetDiffuse());
		pImpl->DrawObject(SpriteMesh, GetGameObject()->IsAlphaActive(),
			shTex, GetWrapSampler());
	}

	//--------------------------------------------------------------------------------------
	//	struct PCTSpriteDraw::Impl;
	//--------------------------------------------------------------------------------------
	struct PCTSpriteDraw::Impl {
		///ルートシグネチャ
		ComPtr<ID3D12RootSignature> m_RootSignature;
		///CbvSrvのデスクプリタハンドルのインクリメントサイズ
		UINT m_CbvSrvDescriptorHandleIncrementSize{ 0 };
		///デスクプリタヒープ
		ComPtr<ID3D12DescriptorHeap> m_CbvSrvUavDescriptorHeap;
		ComPtr<ID3D12DescriptorHeap> m_SamplerDescriptorHeap;
		///GPU側デスクプリタのハンドルの配列
		vector<CD3DX12_GPU_DESCRIPTOR_HANDLE> m_GPUDescriptorHandleVec;
		///コンスタントバッファアップロードヒープ
		ComPtr<ID3D12Resource> m_ConstantBufferUploadHeap;
		///コンスタントバッファのGPU側変数
		void* m_pConstantBuffer{ nullptr };
		///パイプラインステート
		ComPtr<ID3D12PipelineState> m_PipelineState;
		bool m_Trace;
		///コマンドリスト
		ComPtr<ID3D12GraphicsCommandList> m_CommandList;
		///各初期化関数
		///ルートシグネチャ作成
		void CreateRootSignature();
		///デスクプリタヒープ作成
		void CreateDescriptorHeap();
		///サンプラー作成
		void CreateSampler();
		bool m_Wrap;
		///シェーダーリソースビュー作成
		void CreateShaderResourceView(const shared_ptr<TextureResource>& TextureRes);
		///コンスタントバッファ作成
		void CreateConstantBuffer();
		///パイプラインステート作成
		void CreatePipelineState();
		///コマンドリスト作成
		void CreateCommandList();
		///コンスタントバッファ更新
		void UpdateConstantBuffer(const shared_ptr<GameObject>& GameObjectPtr,
			const Color4& Emissive, const Color4& Diffuse);
		///描画処理
		void DrawObject(const shared_ptr<MeshResource>& MeshRes, bool Trace,
			const shared_ptr<TextureResource>& TextureRes, bool WrapSampler);
		Impl() :
			m_Trace(false),
			m_Wrap(false)
		{}
	};

	///ルートシグネチャ作成
	void PCTSpriteDraw::Impl::CreateRootSignature() {
		//ルートシグネチャ
		m_RootSignature = RootSignature::CreateSrvSmpCbv();
	}
	///デスクプリタヒープ作成
	void PCTSpriteDraw::Impl::CreateDescriptorHeap() {
		auto Dev = App::GetApp()->GetDeviceResources();
		m_CbvSrvDescriptorHandleIncrementSize =
			Dev->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		//CbvSrvデスクプリタヒープ
		m_CbvSrvUavDescriptorHeap = DescriptorHeap::CreateCbvSrvUavHeap(1 + 1);
		//サンプラーデスクプリタヒープ
		m_SamplerDescriptorHeap = DescriptorHeap::CreateSamplerHeap(1);
		//GPU側デスクプリタヒープのハンドルの配列の作成
		m_GPUDescriptorHandleVec.clear();
		CD3DX12_GPU_DESCRIPTOR_HANDLE SrvHandle(
			m_CbvSrvUavDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
			0,
			0
		);
		m_GPUDescriptorHandleVec.push_back(SrvHandle);
		CD3DX12_GPU_DESCRIPTOR_HANDLE SamplerHandle(
			m_SamplerDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
			0,
			0
		);
		m_GPUDescriptorHandleVec.push_back(SamplerHandle);
		CD3DX12_GPU_DESCRIPTOR_HANDLE CbvHandle(
			m_CbvSrvUavDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
			1,
			m_CbvSrvDescriptorHandleIncrementSize
		);
		m_GPUDescriptorHandleVec.push_back(CbvHandle);
	}
	///サンプラー作成
	void PCTSpriteDraw::Impl::CreateSampler() {
		auto SamplerDescriptorHandle = m_SamplerDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
		DynamicSampler::CreateSampler(SamplerState::LinearClamp, SamplerDescriptorHandle);
	}
	///シェーダーリソースビュー作成
	void PCTSpriteDraw::Impl::CreateShaderResourceView(const shared_ptr<TextureResource>& TextureRes) {
		auto Dev = App::GetApp()->GetDeviceResources();
		//テクスチャハンドルを作成
		CD3DX12_CPU_DESCRIPTOR_HANDLE Handle(
			m_CbvSrvUavDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
			0,
			0
		);
		//テクスチャのシェーダリソースビューを作成
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		//フォーマット
		srvDesc.Format = TextureRes->GetTextureResDesc().Format;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = TextureRes->GetTextureResDesc().MipLevels;
		//シェーダリソースビュー
		Dev->GetDevice()->CreateShaderResourceView(
			TextureRes->GetTexture().Get(),
			&srvDesc,
			Handle);
	}
	///コンスタントバッファ作成
	void PCTSpriteDraw::Impl::CreateConstantBuffer() {
		auto Dev = App::GetApp()->GetDeviceResources();
		//コンスタントバッファは256バイトにアラインメント
		UINT ConstBuffSize = (sizeof(SpriteConstantBuffer) + 255) & ~255;

		//コンスタントバッファリソース（アップロードヒープ）の作成
		ThrowIfFailed(Dev->GetDevice()->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(ConstBuffSize),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_ConstantBufferUploadHeap)),
			L"コンスタントバッファ用のアップロードヒープ作成に失敗しました",
			L"Dev->GetDevice()->CreateCommittedResource()",
			L"PCTSpriteDraw::Impl::CreateConstantBuffer()"
		);
		//コンスタントバッファのビューを作成
		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
		cbvDesc.BufferLocation = m_ConstantBufferUploadHeap->GetGPUVirtualAddress();
		//コンスタントバッファは256バイトにアラインメント
		cbvDesc.SizeInBytes = ConstBuffSize;
		//コンスタントバッファビューを作成すべきデスクプリタヒープ上のハンドルを取得
		//シェーダリソースがある場合コンスタントバッファはシェーダリソースビューのあとに設置する
		CD3DX12_CPU_DESCRIPTOR_HANDLE cbvSrvHandle(
			m_CbvSrvUavDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
			1,
			m_CbvSrvDescriptorHandleIncrementSize
		);
		Dev->GetDevice()->CreateConstantBufferView(&cbvDesc, cbvSrvHandle);
		//コンスタントバッファのアップロードヒープのマップ
		CD3DX12_RANGE readRange(0, 0);
		ThrowIfFailed(m_ConstantBufferUploadHeap->Map(0, &readRange, reinterpret_cast<void**>(&m_pConstantBuffer)),
			L"コンスタントバッファのマップに失敗しました",
			L"pImpl->m_ConstantBufferUploadHeap->Map()",
			L"PCTSpriteDraw::Impl::CreateConstantBuffer()"
		);
	}
	///パイプラインステート作成
	void PCTSpriteDraw::Impl::CreatePipelineState() {
		D3D12_GRAPHICS_PIPELINE_STATE_DESC PineLineDesc;
		m_PipelineState
			= PipelineState::CreateDefault2D<VertexPositionColorTexture, VSPCTSprite, PSPCTSprite>(m_RootSignature, PineLineDesc);
	}
	///コマンドリスト作成
	void PCTSpriteDraw::Impl::CreateCommandList() {
		m_CommandList = CommandList::CreateDefault(m_PipelineState);
		CommandList::Close(m_CommandList);
	}

	///コンスタントバッファ更新
	void PCTSpriteDraw::Impl::UpdateConstantBuffer(const shared_ptr<GameObject>& GameObjectPtr,
		const Color4& Emissive, const Color4& Diffuse) {
		//行列の定義
		auto PtrTrans = GameObjectPtr->GetComponent<Transform>();
		Vector2 Scale, Pos, Pivot;
		Scale.x = PtrTrans->GetScale().x;
		Scale.y = PtrTrans->GetScale().y;
		Pos.x = PtrTrans->GetPosition().x;
		Pos.y = PtrTrans->GetPosition().y;
		Pivot.x = PtrTrans->GetPivot().x;
		Pivot.y = PtrTrans->GetPivot().y;
		Vector3 Rot = PtrTrans->GetRotation();

		//行列の定義
		Matrix4X4 World, Proj;
		//ワールド行列の決定
		World.AffineTransformation2D(
			Scale,			//スケーリング
			Pivot,		//回転の中心（重心）
			Rot.z,			//回転角度(Z軸回転)
			Pos				//位置
		);
		//射影行列の決定
		GameObjectPtr->OnGet2DDrawProjMatrix(Proj);
		//行列の合成
		World *= Proj;
		SpriteConstantBuffer cb;
		//エミッシブ
		cb.Emissive = Emissive;
		//デフィーズはすべて通す
		cb.Diffuse = Diffuse;
		//行列の設定
		cb.World = World;
		//更新
		memcpy(m_pConstantBuffer, reinterpret_cast<void**>(&cb),
			sizeof(SpriteConstantBuffer));

	}
	///描画処理
	void PCTSpriteDraw::Impl::DrawObject(const shared_ptr<MeshResource>& MeshRes, bool Trace,
		const shared_ptr<TextureResource>& TextureRes, bool WrapSampler) {
		if (m_Wrap != WrapSampler) {
			auto SamplerDescriptorHandle = m_SamplerDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
			if (WrapSampler) {
				//ラッピングサンプラー
				DynamicSampler::CreateSampler(SamplerState::LinearWrap, SamplerDescriptorHandle);
			}
			else {
				DynamicSampler::CreateSampler(SamplerState::LinearClamp, SamplerDescriptorHandle);
			}
			m_Wrap = WrapSampler;
		}
		if (m_Trace != Trace) {
			D3D12_GRAPHICS_PIPELINE_STATE_DESC PineLineDesc;
			m_PipelineState = PipelineState::CreateDefault2D<VertexPositionColorTexture, VSPCTSprite, PSPCTSprite>(m_RootSignature, PineLineDesc);
			//透明の場合はブレンドステート差し替え
			if (Trace) {
				D3D12_BLEND_DESC blend_desc;
				D3D12_RENDER_TARGET_BLEND_DESC Target;
				ZeroMemory(&blend_desc, sizeof(blend_desc));
				blend_desc.AlphaToCoverageEnable = false;
				blend_desc.IndependentBlendEnable = false;
				ZeroMemory(&Target, sizeof(Target));
				Target.BlendEnable = true;
				Target.SrcBlend = D3D12_BLEND_SRC_ALPHA;
				Target.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
				Target.BlendOp = D3D12_BLEND_OP_ADD;
				Target.SrcBlendAlpha = D3D12_BLEND_ONE;
				Target.DestBlendAlpha = D3D12_BLEND_ZERO;
				Target.BlendOpAlpha = D3D12_BLEND_OP_ADD;
				Target.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
				for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; i++) {
					blend_desc.RenderTarget[i] = Target;
				}
				PineLineDesc.BlendState = blend_desc;
				m_PipelineState = PipelineState::CreateDirect(PineLineDesc);
				m_Trace = Trace;
			}
		}
		//コマンドリストのリセット
		CommandList::Reset(m_PipelineState, m_CommandList);

		MeshRes->UpdateResources<VertexPositionColorTexture>(m_CommandList);
		TextureRes->UpdateResources(m_CommandList);

		//描画
		m_CommandList->SetGraphicsRootSignature(m_RootSignature.Get());
		ID3D12DescriptorHeap* ppHeaps[] = { m_CbvSrvUavDescriptorHeap.Get(), m_SamplerDescriptorHeap.Get() };
		m_CommandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
		for (size_t i = 0; i < m_GPUDescriptorHandleVec.size(); i++) {
			m_CommandList->SetGraphicsRootDescriptorTable(i, m_GPUDescriptorHandleVec[i]);
		}
		auto Dev = App::GetApp()->GetDeviceResources();
		m_CommandList->RSSetViewports(1, &Dev->GetViewport());
		m_CommandList->RSSetScissorRects(1, &Dev->GetScissorRect());

		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(
			Dev->GetRtvHeap()->GetCPUDescriptorHandleForHeapStart(),
			Dev->GetFrameIndex(),
			Dev->GetRtvDescriptorSize());
		CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(
			Dev->GetDsvHeap()->GetCPUDescriptorHandleForHeapStart()
		);
		m_CommandList->OMSetRenderTargets(1, &rtvHandle, FALSE, &dsvHandle);

		m_CommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_CommandList->IASetIndexBuffer(&MeshRes->GetIndexBufferView());
		m_CommandList->IASetVertexBuffers(0, 1, &MeshRes->GetVertexBufferView());
		m_CommandList->DrawIndexedInstanced(MeshRes->GetNumIndicis(), 1, 0, 0, 0);

		//コマンドリストのクローズ
		CommandList::Close(m_CommandList);
		//デバイスにコマンドリストを送る
		Dev->InsertDrawCommandLists(m_CommandList.Get());
	}




	//--------------------------------------------------------------------------------------
	///	PCTSprite描画コンポーネント
	//--------------------------------------------------------------------------------------
	PCTSpriteDraw::PCTSpriteDraw(const shared_ptr<GameObject>& GameObjectPtr) :
		SpriteBaseDraw(GameObjectPtr),
		pImpl(new Impl())
	{
		//パイプラインステートをデフォルトの2D
		SetBlendState(BlendState::Opaque);
		SetDepthStencilState(DepthStencilState::None);
		SetRasterizerState(RasterizerState::CullBack);
		SetSamplerState(SamplerState::LinearClamp);
	}
	PCTSpriteDraw::PCTSpriteDraw(const shared_ptr<GameObject>& GameObjectPtr,
		vector<VertexPositionColorTexture>& Vertices, vector<uint16_t>& indices) :
		SpriteBaseDraw(GameObjectPtr),
		pImpl(new Impl())
	{
		try {
			//パイプラインステートをデフォルトの2D
			SetBlendState(BlendState::Opaque);
			SetDepthStencilState(DepthStencilState::None);
			SetRasterizerState(RasterizerState::CullBack);
			SetSamplerState(SamplerState::LinearClamp);
			//メッシュの作成（変更できる）
			auto SpriteMesh = MeshResource::CreateMeshResource(Vertices, indices, true);
			SetMeshResource(SpriteMesh);
		}
		catch (...) {
			throw;
		}
	}
	PCTSpriteDraw::~PCTSpriteDraw() {}

	void PCTSpriteDraw::CreateMesh(vector<VertexPositionColorTexture>& Vertices, vector<uint16_t>& indices) {
		try {
			//メッシュの作成（変更できる）
			auto SpriteMesh = MeshResource::CreateMeshResource(Vertices, indices, true);
			SetMeshResource(SpriteMesh);
		}
		catch (...) {
			throw;
		}
	}

	void PCTSpriteDraw::UpdateVertices(const vector<VertexPositionColorTexture>& Vertices) {
		auto SpriteMesh = GetMeshResource();
		if (!SpriteMesh) {
			throw BaseException(
				L"メッシュが作成されていません",
				L"if (!SpriteMesh)",
				L"PTSpriteDraw::UpdateVertices()"
			);
		}
		//メッシュの頂点の変更
		SpriteMesh->UpdateVirtex(Vertices);
	}

	void PCTSpriteDraw::SetTextureResource(const shared_ptr<TextureResource>& TextureRes) {
		TextureDrawInterface::SetTextureResource(TextureRes);
		pImpl->CreateShaderResourceView(TextureRes);
	}
	void PCTSpriteDraw::SetTextureResource(const wstring& TextureKey) {
		TextureDrawInterface::SetTextureResource(TextureKey);
		pImpl->CreateShaderResourceView(GetTextureResource());
	}


	void PCTSpriteDraw::OnCreate() {
		auto SpriteMesh = GetMeshResource();
		if (!SpriteMesh) {
			//作成されてなかったら作成する
			float HelfSize = 0.5f;
			//頂点配列
			vector<VertexPositionColorTexture> vertices = {
				{ VertexPositionColorTexture(Vector3(-HelfSize, HelfSize, 0),Color4(1.0f,1.0f,1.0f,1.0f), Vector2(0.0f, 0.0f)) },
				{ VertexPositionColorTexture(Vector3(HelfSize, HelfSize, 0), Color4(1.0f,1.0f,1.0f,1.0f), Vector2(1.0f, 0.0f)) },
				{ VertexPositionColorTexture(Vector3(-HelfSize, -HelfSize, 0), Color4(1.0f,1.0f,1.0f,1.0f), Vector2(0.0f, 1.0f)) },
				{ VertexPositionColorTexture(Vector3(HelfSize, -HelfSize, 0), Color4(1.0f,1.0f,1.0f,1.0f), Vector2(1.0f, 1.0f)) },
			};
			//インデックス配列
			vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
			//メッシュの作成（変更できる）
			SpriteMesh = MeshResource::CreateMeshResource(vertices, indices, true);
			SetMeshResource(SpriteMesh);
		}
		///ルートシグネチャ作成
		pImpl->CreateRootSignature();
		///デスクプリタヒープ作成
		pImpl->CreateDescriptorHeap();
		///サンプラー作成
		pImpl->CreateSampler();
		///コンスタントバッファ作成
		pImpl->CreateConstantBuffer();
		///パイプラインステート作成
		pImpl->CreatePipelineState();
		///コマンドリスト作成
		pImpl->CreateCommandList();
		//コンスタントバッファの更新
		pImpl->UpdateConstantBuffer(GetGameObject(),
			GetEmissive(), GetDiffuse());

	}

	void PCTSpriteDraw::OnDraw() {
		//メッシュがなければ描画しない
		auto SpriteMesh = GetMeshResource();
		if (!SpriteMesh) {
			throw BaseException(
				L"メッシュが作成されていません",
				L"if (!SpriteMesh)",
				L"PCTSpriteDraw::OnDraw()"
			);
		}
		//テクスチャがなければ描画しない
		auto shTex = GetTextureResource();
		if (!shTex) {
			return;
		}
		//コンスタントバッファの更新
		pImpl->UpdateConstantBuffer(GetGameObject(),
			GetEmissive(), GetDiffuse());
		pImpl->DrawObject(SpriteMesh, GetGameObject()->IsAlphaActive(),
			shTex, GetWrapSampler());
	}


	//--------------------------------------------------------------------------------------
	//	struct Base3DDraw::Impl;
	//	用途: Base3DDrawイディオム
	//--------------------------------------------------------------------------------------
	struct Base3DDraw::Impl {
		//エミッシブ色
		Color4 m_Emissive;
		//デフューズ色
		Color4 m_Diffuse;
		//ビュー行列
		Matrix4X4 m_ViewMatrix;
		//射影行列
		Matrix4X4 m_ProjMatrix;
		Impl() :
			m_Emissive(0, 0, 0, 0),
			m_Diffuse(1.0f, 1.0f, 1.0f, 1.0f),
			m_ViewMatrix(),
			m_ProjMatrix()
		{}
	};

	//--------------------------------------------------------------------------------------
	///	3D描画コンポーネントの親(3D描画の親)
	//--------------------------------------------------------------------------------------
	Base3DDraw::Base3DDraw(const shared_ptr<GameObject>& GameObjectPtr) :
		DrawComponent(GameObjectPtr),
		pImpl(new Impl())
	{}
	Base3DDraw::~Base3DDraw() {}
	Color4 Base3DDraw::GetEmissive() const {
		return pImpl->m_Emissive;
	}
	void Base3DDraw::SetEmissive(const Color4& col) {
		pImpl->m_Emissive = col;
	}
	Color4 Base3DDraw::GetDiffuse() const {
		return pImpl->m_Diffuse;
	}
	void Base3DDraw::SetDiffuse(const Color4& col) {
		pImpl->m_Diffuse = col;
	}

	const Matrix4X4& Base3DDraw::GetViewMatrix() const {
		return pImpl->m_ViewMatrix;
	}
	void Base3DDraw::SetViewMatrix(const Matrix4X4& mat) {
		pImpl->m_ViewMatrix = mat;
	}
	const Matrix4X4& Base3DDraw::GetProjMatrix() const {
		return pImpl->m_ProjMatrix;
	}
	void Base3DDraw::SetProjMatrix(const Matrix4X4& mat) {
		pImpl->m_ProjMatrix = mat;
	}




	//--------------------------------------------------------------------------------------
	//	struct DynamicBaseDraw::Impl;
	//	用途: DynamicBaseDrawイディオム
	//--------------------------------------------------------------------------------------
	struct DynamicBaseDraw::Impl {
		//メッシュ
		shared_ptr<MeshResource> m_MeshResource;
		Impl()
		{}
	};


	//--------------------------------------------------------------------------------------
	///	Dynamic描画コンポーネントの親(頂点を変更できる3D描画)
	//--------------------------------------------------------------------------------------
	DynamicBaseDraw::DynamicBaseDraw(const shared_ptr<GameObject>& GameObjectPtr) :
		Base3DDraw(GameObjectPtr),
		pImpl(new Impl())
	{}
	DynamicBaseDraw::~DynamicBaseDraw() {}
	shared_ptr<MeshResource> DynamicBaseDraw::GetMeshResource() const {
		return pImpl->m_MeshResource;
	}
	void DynamicBaseDraw::SetMeshResource(const shared_ptr<MeshResource>& MeshRes) {
		pImpl->m_MeshResource = MeshRes;
	}



	//--------------------------------------------------------------------------------------
	//	struct PCDynamicDraw::Impl;
	//--------------------------------------------------------------------------------------
	struct PCDynamicDraw::Impl {
		///ルートシグネチャ
		ComPtr<ID3D12RootSignature> m_RootSignature;
		///CbvSrvのデスクプリタハンドルのインクリメントサイズ
		UINT m_CbvSrvDescriptorHandleIncrementSize{ 0 };
		///デスクプリタヒープ
		ComPtr<ID3D12DescriptorHeap> m_CbvSrvUavDescriptorHeap;
		///GPU側デスクプリタのハンドルの配列
		vector<CD3DX12_GPU_DESCRIPTOR_HANDLE> m_GPUDescriptorHandleVec;
		///コンスタントバッファアップロードヒープ
		ComPtr<ID3D12Resource> m_ConstantBufferUploadHeap;
		///コンスタントバッファのGPU側変数
		void* m_pConstantBuffer{ nullptr };
		//パイプラインステート
		ComPtr<ID3D12PipelineState> m_PipelineState;
		bool m_Trace;
		///コマンドリスト
		ComPtr<ID3D12GraphicsCommandList> m_CommandList;
		///ルートシグネチャ作成
		void CreateRootSignature();
		///デスクプリタヒープ作成
		void CreateDescriptorHeap();
		///コンスタントバッファ作成
		void CreateConstantBuffer();
		///パイプラインステート作成
		void CreatePipelineState();
		///コマンドリスト作成
		void CreateCommandList();
		///コンスタントバッファ更新
		void UpdateConstantBuffer(const shared_ptr<GameObject>& GameObjectPtr,
			const Color4& Emissive, const Color4& Diffuse, const Matrix4X4& MeshToTransformMatrix);
		///描画処理
		void DrawObject(const shared_ptr<MeshResource>& MeshRes, bool Trace);
		Impl() :
			m_Trace(false)
		{}
	};


	///ルートシグネチャ作成
	void PCDynamicDraw::Impl::CreateRootSignature() {
		//コンスタントバッファ付ルートシグネチャ
		m_RootSignature = RootSignature::CreateCbv();
	}
	///デスクプリタヒープ作成
	void PCDynamicDraw::Impl::CreateDescriptorHeap() {
		auto Dev = App::GetApp()->GetDeviceResources();
		m_CbvSrvDescriptorHandleIncrementSize
			= Dev->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		//CbvSrvデスクプリタヒープ(コンスタントバッファのみ)
		m_CbvSrvUavDescriptorHeap = DescriptorHeap::CreateCbvSrvUavHeap(1);
		//GPU側デスクプリタヒープのハンドルの配列の作成
		m_GPUDescriptorHandleVec.clear();
		CD3DX12_GPU_DESCRIPTOR_HANDLE CbvHandle(
			m_CbvSrvUavDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
			0,
			0
		);
		m_GPUDescriptorHandleVec.push_back(CbvHandle);
	}
	///コンスタントバッファ作成
	void PCDynamicDraw::Impl::CreateConstantBuffer() {
		auto Dev = App::GetApp()->GetDeviceResources();
		//コンスタントバッファは256バイトにアラインメント
		UINT ConstBuffSize = (sizeof(StaticConstantBuffer) + 255) & ~255;
		ThrowIfFailed(Dev->GetDevice()->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(ConstBuffSize),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_ConstantBufferUploadHeap)),
			L"コンスタントバッファ用のアップロードヒープ作成に失敗しました",
			L"Dev->GetDevice()->CreateCommittedResource()",
			L"PCDynamicDraw::Impl::CreateConstantBuffer()"
		);
		//コンスタントバッファのビューを作成
		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
		cbvDesc.BufferLocation = m_ConstantBufferUploadHeap->GetGPUVirtualAddress();
		cbvDesc.SizeInBytes = ConstBuffSize;
		//コンスタントバッファビューを作成すべきデスクプリタヒープ上のハンドルを取得
		//シェーダリソースがある場合コンスタントバッファはシェーダリソースビューのあとに設置する
		CD3DX12_CPU_DESCRIPTOR_HANDLE cbvSrvHandle(
			m_CbvSrvUavDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
			0,
			0
		);
		Dev->GetDevice()->CreateConstantBufferView(&cbvDesc, cbvSrvHandle);
		//コンスタントバッファのアップロードヒープのマップ
		CD3DX12_RANGE readRange(0, 0);
		ThrowIfFailed(m_ConstantBufferUploadHeap->Map(0, &readRange, reinterpret_cast<void**>(&m_pConstantBuffer)),
			L"コンスタントバッファのマップに失敗しました",
			L"pImpl->m_ConstantBufferUploadHeap->Map()",
			L"PCDynamicDraw::Impl::CreateConstantBuffer()"
		);
	}
	///パイプラインステート作成
	void PCDynamicDraw::Impl::CreatePipelineState() {
		D3D12_GRAPHICS_PIPELINE_STATE_DESC PineLineDesc;
		m_PipelineState
			= PipelineState::CreateDefault3D<VertexPositionColor, VSPCStatic, PSPCStatic>(m_RootSignature, PineLineDesc);
	}
	///コマンドリスト作成
	void PCDynamicDraw::Impl::CreateCommandList() {
		m_CommandList = CommandList::CreateDefault(m_PipelineState);
		CommandList::Close(m_CommandList);
	}

	///コンスタントバッファ更新
	void PCDynamicDraw::Impl::UpdateConstantBuffer(const shared_ptr<GameObject>& GameObjectPtr,
		const Color4& Emissive, const Color4& Diffuse, const Matrix4X4& MeshToTransformMatrix) {
		//行列の定義
		auto PtrTrans = GameObjectPtr->GetComponent<Transform>();
		//行列の定義
		Matrix4X4 World, ViewMat, ProjMat;
		//ワールド行列の決定
		World = MeshToTransformMatrix * PtrTrans->GetWorldMatrix();
		//転置する
		World.Transpose();
		//カメラを得る
		auto CameraPtr = GameObjectPtr->OnGetDrawCamera();
		//ビューと射影行列を得る
		ViewMat = CameraPtr->GetViewMatrix();
		//転置する
		ViewMat.Transpose();
		//転置する
		ProjMat = CameraPtr->GetProjMatrix();
		ProjMat.Transpose();
		//コンスタントバッファの準備
		StaticConstantBuffer cb;
		cb.World = World;
		cb.View = ViewMat;
		cb.Projection = ProjMat;
		//エミッシブ
		cb.Emissive = Emissive;
		//デフィーズ
		cb.Diffuse = Diffuse;
		//更新
		memcpy(m_pConstantBuffer, reinterpret_cast<void**>(&cb),
			sizeof(StaticConstantBuffer));

	}

	///描画処理
	void PCDynamicDraw::Impl::DrawObject(const shared_ptr<MeshResource>& MeshRes, bool Trace) {
		if (m_Trace != Trace) {
			D3D12_GRAPHICS_PIPELINE_STATE_DESC PineLineDesc;
			m_PipelineState = PipelineState::CreateDefault3D<VertexPositionColor, VSPCStatic, PSPCStatic>(m_RootSignature, PineLineDesc);
			//透明の場合はブレンドステート差し替え
			if (Trace) {
				D3D12_BLEND_DESC blend_desc;
				D3D12_RENDER_TARGET_BLEND_DESC Target;
				ZeroMemory(&blend_desc, sizeof(blend_desc));
				blend_desc.AlphaToCoverageEnable = false;
				blend_desc.IndependentBlendEnable = false;
				ZeroMemory(&Target, sizeof(Target));
				Target.BlendEnable = true;
				Target.SrcBlend = D3D12_BLEND_SRC_ALPHA;
				Target.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
				Target.BlendOp = D3D12_BLEND_OP_ADD;
				Target.SrcBlendAlpha = D3D12_BLEND_ONE;
				Target.DestBlendAlpha = D3D12_BLEND_ZERO;
				Target.BlendOpAlpha = D3D12_BLEND_OP_ADD;
				Target.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
				for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; i++) {
					blend_desc.RenderTarget[i] = Target;
				}
				PineLineDesc.BlendState = blend_desc;
				m_PipelineState = PipelineState::CreateDirect(PineLineDesc);
				m_Trace = Trace;
			}
		}
		//コマンドリストのリセット
		CommandList::Reset(m_PipelineState, m_CommandList);

		MeshRes->UpdateResources<VertexPositionColor>(m_CommandList);

		//描画
		m_CommandList->SetGraphicsRootSignature(m_RootSignature.Get());
		ID3D12DescriptorHeap* ppHeaps[] = { m_CbvSrvUavDescriptorHeap.Get() };
		m_CommandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
		for (size_t i = 0; i < m_GPUDescriptorHandleVec.size(); i++) {
			m_CommandList->SetGraphicsRootDescriptorTable(i, m_GPUDescriptorHandleVec[i]);
		}
		auto Dev = App::GetApp()->GetDeviceResources();
		m_CommandList->RSSetViewports(1, &Dev->GetViewport());
		m_CommandList->RSSetScissorRects(1, &Dev->GetScissorRect());

		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(
			Dev->GetRtvHeap()->GetCPUDescriptorHandleForHeapStart(),
			Dev->GetFrameIndex(),
			Dev->GetRtvDescriptorSize());
		CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(
			Dev->GetDsvHeap()->GetCPUDescriptorHandleForHeapStart()
		);
		m_CommandList->OMSetRenderTargets(1, &rtvHandle, FALSE, &dsvHandle);

		m_CommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_CommandList->IASetIndexBuffer(&MeshRes->GetIndexBufferView());
		m_CommandList->IASetVertexBuffers(0, 1, &MeshRes->GetVertexBufferView());
		m_CommandList->DrawIndexedInstanced(MeshRes->GetNumIndicis(), 1, 0, 0, 0);

		//コマンドリストのクローズ
		CommandList::Close(m_CommandList);
		//デバイスにコマンドリストを送る
		Dev->InsertDrawCommandLists(m_CommandList.Get());
	}




	//--------------------------------------------------------------------------------------
	///	PCDynamic描画コンポーネント
	//--------------------------------------------------------------------------------------
	PCDynamicDraw::PCDynamicDraw(const shared_ptr<GameObject>& GameObjectPtr) :
		DynamicBaseDraw(GameObjectPtr),
		pImpl(new Impl())
	{
		//パイプラインステートをデフォルトの3D
		SetBlendState(BlendState::Opaque);
		SetDepthStencilState(DepthStencilState::Default);
		SetRasterizerState(RasterizerState::CullBack);
		SetSamplerState(SamplerState::LinearClamp);
	}

	PCDynamicDraw::~PCDynamicDraw() {}

	void PCDynamicDraw::CreateMesh(vector<VertexPositionColor>& Vertices, vector<uint16_t>& indices) {
		try {
			//メッシュの作成（変更できる）
			auto MeshRes = MeshResource::CreateMeshResource(Vertices, indices, true);
			SetMeshResource(MeshRes);
		}
		catch (...) {
			throw;
		}
	}

	void PCDynamicDraw::UpdateVertices(const vector<VertexPositionColor>& Vertices) {
		auto Mesh = GetMeshResource();
		if (!Mesh) {
			throw BaseException(
				L"メッシュが作成されていません",
				L"if (!Mesh)",
				L"PCDynamicDraw::UpdateVertices()"
			);
		}
		//メッシュの頂点の変更
		Mesh->UpdateVirtex(Vertices);

	}
	void PCDynamicDraw::OnCreate() {
		///ルートシグネチャ作成
		pImpl->CreateRootSignature();
		///デスクプリタヒープ作成
		pImpl->CreateDescriptorHeap();
		///コンスタントバッファ作成
		pImpl->CreateConstantBuffer();
		///パイプラインステート作成
		pImpl->CreatePipelineState();
		///コマンドリスト作成
		pImpl->CreateCommandList();
		//コンスタントバッファの更新
		pImpl->UpdateConstantBuffer(GetGameObject(),
			GetEmissive(), GetDiffuse(), GetMeshToTransformMatrix());

	}
	void PCDynamicDraw::OnDraw() {
		auto Mesh = GetMeshResource();
		if (!Mesh) {
			throw BaseException(
				L"メッシュが作成されていません",
				L"if (!Mesh)",
				L"PCDynamicDraw::OnDraw()"
			);
		}
		//コンスタントバッファの更新
		pImpl->UpdateConstantBuffer(GetGameObject(),
			GetEmissive(), GetDiffuse(), GetMeshToTransformMatrix());
		pImpl->DrawObject(Mesh, GetGameObject()->IsAlphaActive());

	}

	//--------------------------------------------------------------------------------------
	//	struct PTDynamicDraw::Impl;
	//--------------------------------------------------------------------------------------
	struct PTDynamicDraw::Impl {
		///ルートシグネチャ
		ComPtr<ID3D12RootSignature> m_RootSignature;
		///CbvSrvのデスクプリタハンドルのインクリメントサイズ
		UINT m_CbvSrvDescriptorHandleIncrementSize{ 0 };
		///デスクプリタヒープ
		ComPtr<ID3D12DescriptorHeap> m_CbvSrvUavDescriptorHeap;
		ComPtr<ID3D12DescriptorHeap> m_SamplerDescriptorHeap;
		///GPU側デスクプリタのハンドルの配列
		vector<CD3DX12_GPU_DESCRIPTOR_HANDLE> m_GPUDescriptorHandleVec;
		///コンスタントバッファアップロードヒープ
		ComPtr<ID3D12Resource> m_ConstantBufferUploadHeap;
		///コンスタントバッファのGPU側変数
		void* m_pConstantBuffer{ nullptr };
		///パイプラインステート
		ComPtr<ID3D12PipelineState> m_PipelineState;
		bool m_Trace;
		///コマンドリスト
		ComPtr<ID3D12GraphicsCommandList> m_CommandList;
		///各初期化関数
		///ルートシグネチャ作成
		void CreateRootSignature();
		///デスクプリタヒープ作成
		void CreateDescriptorHeap();
		///サンプラー作成
		void CreateSampler();
		bool m_Wrap;
		///シェーダーリソースビュー作成
		void CreateShaderResourceView(const shared_ptr<TextureResource>& TextureRes);
		///コンスタントバッファ作成
		void CreateConstantBuffer();
		///パイプラインステート作成
		void CreatePipelineState();
		///コマンドリスト作成
		void CreateCommandList();
		///コンスタントバッファ更新
		void UpdateConstantBuffer(const shared_ptr<GameObject>& GameObjectPtr,
			const Color4& Emissive, const Color4& Diffuse, const Matrix4X4& MeshToTransformMatrix);
		///描画処理
		void DrawObject(const shared_ptr<MeshResource>& MeshRes, bool Trace,
			const shared_ptr<TextureResource>& TextureRes, bool WrapSampler);
		Impl() :
			m_Trace(false),
			m_Wrap(false)
		{}
	};

	///ルートシグネチャ作成
	void PTDynamicDraw::Impl::CreateRootSignature() {
		//ルートシグネチャ
		m_RootSignature = RootSignature::CreateSrvSmpCbv();
	}
	///デスクプリタヒープ作成
	void PTDynamicDraw::Impl::CreateDescriptorHeap() {
		auto Dev = App::GetApp()->GetDeviceResources();
		m_CbvSrvDescriptorHandleIncrementSize =
			Dev->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		//CbvSrvデスクプリタヒープ
		m_CbvSrvUavDescriptorHeap = DescriptorHeap::CreateCbvSrvUavHeap(1 + 1);
		//サンプラーデスクプリタヒープ
		m_SamplerDescriptorHeap = DescriptorHeap::CreateSamplerHeap(1);
		//GPU側デスクプリタヒープのハンドルの配列の作成
		m_GPUDescriptorHandleVec.clear();
		CD3DX12_GPU_DESCRIPTOR_HANDLE SrvHandle(
			m_CbvSrvUavDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
			0,
			0
		);
		m_GPUDescriptorHandleVec.push_back(SrvHandle);
		CD3DX12_GPU_DESCRIPTOR_HANDLE SamplerHandle(
			m_SamplerDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
			0,
			0
		);
		m_GPUDescriptorHandleVec.push_back(SamplerHandle);
		CD3DX12_GPU_DESCRIPTOR_HANDLE CbvHandle(
			m_CbvSrvUavDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
			1,
			m_CbvSrvDescriptorHandleIncrementSize
		);
		m_GPUDescriptorHandleVec.push_back(CbvHandle);
	}
	///サンプラー作成
	void PTDynamicDraw::Impl::CreateSampler() {
		auto SamplerDescriptorHandle = m_SamplerDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
		DynamicSampler::CreateSampler(SamplerState::LinearClamp, SamplerDescriptorHandle);
	}
	///シェーダーリソースビュー作成
	void PTDynamicDraw::Impl::CreateShaderResourceView(const shared_ptr<TextureResource>& TextureRes) {
		auto Dev = App::GetApp()->GetDeviceResources();
		//テクスチャハンドルを作成
		CD3DX12_CPU_DESCRIPTOR_HANDLE Handle(
			m_CbvSrvUavDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
			0,
			0
		);
		//テクスチャのシェーダリソースビューを作成
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		//フォーマット
		srvDesc.Format = TextureRes->GetTextureResDesc().Format;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = TextureRes->GetTextureResDesc().MipLevels;
		//シェーダリソースビュー
		Dev->GetDevice()->CreateShaderResourceView(
			TextureRes->GetTexture().Get(),
			&srvDesc,
			Handle);
	}
	///コンスタントバッファ作成
	void PTDynamicDraw::Impl::CreateConstantBuffer() {
		auto Dev = App::GetApp()->GetDeviceResources();
		//コンスタントバッファは256バイトにアラインメント
		UINT ConstBuffSize = (sizeof(StaticConstantBuffer) + 255) & ~255;

		//コンスタントバッファリソース（アップロードヒープ）の作成
		ThrowIfFailed(Dev->GetDevice()->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(ConstBuffSize),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_ConstantBufferUploadHeap)),
			L"コンスタントバッファ用のアップロードヒープ作成に失敗しました",
			L"Dev->GetDevice()->CreateCommittedResource()",
			L"PCTDynamicDraw::Impl::CreateConstantBuffer()"
		);
		//コンスタントバッファのビューを作成
		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
		cbvDesc.BufferLocation = m_ConstantBufferUploadHeap->GetGPUVirtualAddress();
		//コンスタントバッファは256バイトにアラインメント
		cbvDesc.SizeInBytes = ConstBuffSize;
		//コンスタントバッファビューを作成すべきデスクプリタヒープ上のハンドルを取得
		//シェーダリソースがある場合コンスタントバッファはシェーダリソースビューのあとに設置する
		CD3DX12_CPU_DESCRIPTOR_HANDLE cbvSrvHandle(
			m_CbvSrvUavDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
			1,
			m_CbvSrvDescriptorHandleIncrementSize
		);
		Dev->GetDevice()->CreateConstantBufferView(&cbvDesc, cbvSrvHandle);
		//コンスタントバッファのアップロードヒープのマップ
		CD3DX12_RANGE readRange(0, 0);
		ThrowIfFailed(m_ConstantBufferUploadHeap->Map(0, &readRange, reinterpret_cast<void**>(&m_pConstantBuffer)),
			L"コンスタントバッファのマップに失敗しました",
			L"pImpl->m_ConstantBufferUploadHeap->Map()",
			L"PCTDynamicDraw::Impl::CreateConstantBuffer()"
		);
	}
	///パイプラインステート作成
	void PTDynamicDraw::Impl::CreatePipelineState() {
		D3D12_GRAPHICS_PIPELINE_STATE_DESC PineLineDesc;
		m_PipelineState
			= PipelineState::CreateDefault3D<VertexPositionTexture, VSPTStatic, PSPTStatic>(m_RootSignature, PineLineDesc);
	}
	///コマンドリスト作成
	void PTDynamicDraw::Impl::CreateCommandList() {
		m_CommandList = CommandList::CreateDefault(m_PipelineState);
		CommandList::Close(m_CommandList);
	}

	///コンスタントバッファ更新
	void PTDynamicDraw::Impl::UpdateConstantBuffer(const shared_ptr<GameObject>& GameObjectPtr,
		const Color4& Emissive, const Color4& Diffuse, const Matrix4X4& MeshToTransformMatrix) {
		//行列の定義
		auto PtrTrans = GameObjectPtr->GetComponent<Transform>();
		//行列の定義
		Matrix4X4 World, ViewMat, ProjMat;
		//ワールド行列の決定
		World = MeshToTransformMatrix * PtrTrans->GetWorldMatrix();
		//転置する
		World.Transpose();
		//カメラを得る
		auto CameraPtr = GameObjectPtr->OnGetDrawCamera();
		//ビューと射影行列を得る
		ViewMat = CameraPtr->GetViewMatrix();
		//転置する
		ViewMat.Transpose();
		//転置する
		ProjMat = CameraPtr->GetProjMatrix();
		ProjMat.Transpose();
		//コンスタントバッファの準備
		StaticConstantBuffer cb;
		cb.World = World;
		cb.View = ViewMat;
		cb.Projection = ProjMat;
		//エミッシブ
		cb.Emissive = Emissive;
		//デフィーズはすべて通す
		cb.Diffuse = Diffuse;
		//更新
		memcpy(m_pConstantBuffer, reinterpret_cast<void**>(&cb),
			sizeof(StaticConstantBuffer));

	}
	///描画処理
	void PTDynamicDraw::Impl::DrawObject(const shared_ptr<MeshResource>& MeshRes, bool Trace,
		const shared_ptr<TextureResource>& TextureRes, bool WrapSampler) {
		if (m_Wrap != WrapSampler) {
			auto SamplerDescriptorHandle = m_SamplerDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
			if (WrapSampler) {
				//ラッピングサンプラー
				DynamicSampler::CreateSampler(SamplerState::LinearWrap, SamplerDescriptorHandle);
			}
			else {
				DynamicSampler::CreateSampler(SamplerState::LinearClamp, SamplerDescriptorHandle);
			}
			m_Wrap = WrapSampler;
		}
		if (m_Trace != Trace) {
			D3D12_GRAPHICS_PIPELINE_STATE_DESC PineLineDesc;
			m_PipelineState = PipelineState::CreateDefault3D<VertexPositionTexture, VSPTStatic, PSPTStatic>(m_RootSignature, PineLineDesc);
			//透明の場合はブレンドステート差し替え
			if (Trace) {
				D3D12_BLEND_DESC blend_desc;
				D3D12_RENDER_TARGET_BLEND_DESC Target;
				ZeroMemory(&blend_desc, sizeof(blend_desc));
				blend_desc.AlphaToCoverageEnable = false;
				blend_desc.IndependentBlendEnable = false;
				ZeroMemory(&Target, sizeof(Target));
				Target.BlendEnable = true;
				Target.SrcBlend = D3D12_BLEND_SRC_ALPHA;
				Target.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
				Target.BlendOp = D3D12_BLEND_OP_ADD;
				Target.SrcBlendAlpha = D3D12_BLEND_ONE;
				Target.DestBlendAlpha = D3D12_BLEND_ZERO;
				Target.BlendOpAlpha = D3D12_BLEND_OP_ADD;
				Target.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
				for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; i++) {
					blend_desc.RenderTarget[i] = Target;
				}
				PineLineDesc.BlendState = blend_desc;
				m_PipelineState = PipelineState::CreateDirect(PineLineDesc);
				m_Trace = Trace;
			}
		}
		//コマンドリストのリセット
		CommandList::Reset(m_PipelineState, m_CommandList);

		MeshRes->UpdateResources<VertexPositionTexture>(m_CommandList);
		TextureRes->UpdateResources(m_CommandList);

		//描画
		m_CommandList->SetGraphicsRootSignature(m_RootSignature.Get());
		ID3D12DescriptorHeap* ppHeaps[] = { m_CbvSrvUavDescriptorHeap.Get(), m_SamplerDescriptorHeap.Get() };
		m_CommandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
		for (size_t i = 0; i < m_GPUDescriptorHandleVec.size(); i++) {
			m_CommandList->SetGraphicsRootDescriptorTable(i, m_GPUDescriptorHandleVec[i]);
		}
		auto Dev = App::GetApp()->GetDeviceResources();
		m_CommandList->RSSetViewports(1, &Dev->GetViewport());
		m_CommandList->RSSetScissorRects(1, &Dev->GetScissorRect());

		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(
			Dev->GetRtvHeap()->GetCPUDescriptorHandleForHeapStart(),
			Dev->GetFrameIndex(),
			Dev->GetRtvDescriptorSize());
		CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(
			Dev->GetDsvHeap()->GetCPUDescriptorHandleForHeapStart()
		);
		m_CommandList->OMSetRenderTargets(1, &rtvHandle, FALSE, &dsvHandle);

		m_CommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_CommandList->IASetIndexBuffer(&MeshRes->GetIndexBufferView());
		m_CommandList->IASetVertexBuffers(0, 1, &MeshRes->GetVertexBufferView());
		m_CommandList->DrawIndexedInstanced(MeshRes->GetNumIndicis(), 1, 0, 0, 0);

		//コマンドリストのクローズ
		CommandList::Close(m_CommandList);
		//デバイスにコマンドリストを送る
		Dev->InsertDrawCommandLists(m_CommandList.Get());
	}


	//--------------------------------------------------------------------------------------
	///	PTDynamicDraw描画コンポーネント
	//--------------------------------------------------------------------------------------
	PTDynamicDraw::PTDynamicDraw(const shared_ptr<GameObject>& GameObjectPtr) :
		DynamicBaseDraw(GameObjectPtr),
		pImpl(new Impl())
	{
		//パイプラインステートをデフォルトの3D
		SetBlendState(BlendState::Opaque);
		SetDepthStencilState(DepthStencilState::Default);
		SetRasterizerState(RasterizerState::CullBack);
		SetSamplerState(SamplerState::LinearClamp);
	}

	PTDynamicDraw::~PTDynamicDraw() {}

	void PTDynamicDraw::SetTextureResource(const shared_ptr<TextureResource>& TextureRes) {
		TextureDrawInterface::SetTextureResource(TextureRes);
		pImpl->CreateShaderResourceView(TextureRes);
	}
	void PTDynamicDraw::SetTextureResource(const wstring& TextureKey) {
		TextureDrawInterface::SetTextureResource(TextureKey);
		pImpl->CreateShaderResourceView(GetTextureResource());
	}


	void PTDynamicDraw::CreateMesh(vector<VertexPositionTexture>& Vertices, vector<uint16_t>& indices) {
		try {
			//メッシュの作成（変更できる）
			auto MeshRes = MeshResource::CreateMeshResource(Vertices, indices, true);
			SetMeshResource(MeshRes);
		}
		catch (...) {
			throw;
		}
	}

	void PTDynamicDraw::UpdateVertices(const vector<VertexPositionTexture>& Vertices) {
		auto Mesh = GetMeshResource();
		if (!Mesh) {
			throw BaseException(
				L"メッシュが作成されていません",
				L"if (!Mesh)",
				L"PTDynamicDraw::UpdateVertices()"
			);
		}
		//メッシュの頂点の変更
		Mesh->UpdateVirtex(Vertices);
	}

	void PTDynamicDraw::OnCreate() {
		///ルートシグネチャ作成
		pImpl->CreateRootSignature();
		///デスクプリタヒープ作成
		pImpl->CreateDescriptorHeap();
		///サンプラー作成
		pImpl->CreateSampler();
		///コンスタントバッファ作成
		pImpl->CreateConstantBuffer();
		///パイプラインステート作成
		pImpl->CreatePipelineState();
		///コマンドリスト作成
		pImpl->CreateCommandList();
		//コンスタントバッファの更新
		pImpl->UpdateConstantBuffer(GetGameObject(),
			GetEmissive(), GetDiffuse(), GetMeshToTransformMatrix());
	}
	void PTDynamicDraw::OnDraw() {
		auto Mesh = GetMeshResource();
		if (!Mesh) {
			throw BaseException(
				L"メッシュが作成されていません",
				L"if (!Mesh)",
				L"PTDynamicDraw::OnDraw()"
			);
		}
		//テクスチャがなければ描画しない
		auto shTex = GetTextureResource();
		if (!shTex) {
			return;
		}
		//コンスタントバッファの更新
		pImpl->UpdateConstantBuffer(GetGameObject(),
			GetEmissive(), GetDiffuse(), GetMeshToTransformMatrix());
		pImpl->DrawObject(Mesh, GetGameObject()->IsAlphaActive(),
			shTex, GetWrapSampler());

	}





	//--------------------------------------------------------------------------------------
	//	struct PCTDynamicDraw::Impl;
	//--------------------------------------------------------------------------------------
	struct PCTDynamicDraw::Impl {
		///ルートシグネチャ
		ComPtr<ID3D12RootSignature> m_RootSignature;
		///CbvSrvのデスクプリタハンドルのインクリメントサイズ
		UINT m_CbvSrvDescriptorHandleIncrementSize{ 0 };
		///デスクプリタヒープ
		ComPtr<ID3D12DescriptorHeap> m_CbvSrvUavDescriptorHeap;
		ComPtr<ID3D12DescriptorHeap> m_SamplerDescriptorHeap;
		///GPU側デスクプリタのハンドルの配列
		vector<CD3DX12_GPU_DESCRIPTOR_HANDLE> m_GPUDescriptorHandleVec;
		///コンスタントバッファアップロードヒープ
		ComPtr<ID3D12Resource> m_ConstantBufferUploadHeap;
		///コンスタントバッファのGPU側変数
		void* m_pConstantBuffer{ nullptr };
		///パイプラインステート
		ComPtr<ID3D12PipelineState> m_PipelineState;
		bool m_Trace;
		///コマンドリスト
		ComPtr<ID3D12GraphicsCommandList> m_CommandList;
		///各初期化関数
		///ルートシグネチャ作成
		void CreateRootSignature();
		///デスクプリタヒープ作成
		void CreateDescriptorHeap();
		///サンプラー作成
		void CreateSampler();
		bool m_Wrap;
		///シェーダーリソースビュー作成
		void CreateShaderResourceView(const shared_ptr<TextureResource>& TextureRes);
		///コンスタントバッファ作成
		void CreateConstantBuffer();
		///パイプラインステート作成
		void CreatePipelineState();
		///コマンドリスト作成
		void CreateCommandList();
		///コンスタントバッファ更新
		void UpdateConstantBuffer(const shared_ptr<GameObject>& GameObjectPtr,
			const Color4& Emissive, const Color4& Diffuse, const Matrix4X4& MeshToTransformMatrix);
		///描画処理
		void DrawObject(const shared_ptr<MeshResource>& MeshRes, bool Trace,
			const shared_ptr<TextureResource>& TextureRes, bool WrapSampler);
		Impl() :
			m_Trace(false),
			m_Wrap(false)
		{}
	};

	///ルートシグネチャ作成
	void PCTDynamicDraw::Impl::CreateRootSignature() {
		//ルートシグネチャ
		m_RootSignature = RootSignature::CreateSrvSmpCbv();
	}
	///デスクプリタヒープ作成
	void PCTDynamicDraw::Impl::CreateDescriptorHeap() {
		auto Dev = App::GetApp()->GetDeviceResources();
		m_CbvSrvDescriptorHandleIncrementSize =
			Dev->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		//CbvSrvデスクプリタヒープ
		m_CbvSrvUavDescriptorHeap = DescriptorHeap::CreateCbvSrvUavHeap(1 + 1);
		//サンプラーデスクプリタヒープ
		m_SamplerDescriptorHeap = DescriptorHeap::CreateSamplerHeap(1);
		//GPU側デスクプリタヒープのハンドルの配列の作成
		m_GPUDescriptorHandleVec.clear();
		CD3DX12_GPU_DESCRIPTOR_HANDLE SrvHandle(
			m_CbvSrvUavDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
			0,
			0
		);
		m_GPUDescriptorHandleVec.push_back(SrvHandle);
		CD3DX12_GPU_DESCRIPTOR_HANDLE SamplerHandle(
			m_SamplerDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
			0,
			0
		);
		m_GPUDescriptorHandleVec.push_back(SamplerHandle);
		CD3DX12_GPU_DESCRIPTOR_HANDLE CbvHandle(
			m_CbvSrvUavDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
			1,
			m_CbvSrvDescriptorHandleIncrementSize
		);
		m_GPUDescriptorHandleVec.push_back(CbvHandle);
	}
	///サンプラー作成
	void PCTDynamicDraw::Impl::CreateSampler() {
		auto SamplerDescriptorHandle = m_SamplerDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
		DynamicSampler::CreateSampler(SamplerState::LinearClamp, SamplerDescriptorHandle);
	}
	///シェーダーリソースビュー作成
	void PCTDynamicDraw::Impl::CreateShaderResourceView(const shared_ptr<TextureResource>& TextureRes) {
		auto Dev = App::GetApp()->GetDeviceResources();
		//テクスチャハンドルを作成
		CD3DX12_CPU_DESCRIPTOR_HANDLE Handle(
			m_CbvSrvUavDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
			0,
			0
		);
		//テクスチャのシェーダリソースビューを作成
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		//フォーマット
		srvDesc.Format = TextureRes->GetTextureResDesc().Format;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = TextureRes->GetTextureResDesc().MipLevels;
		//シェーダリソースビュー
		Dev->GetDevice()->CreateShaderResourceView(
			TextureRes->GetTexture().Get(),
			&srvDesc,
			Handle);
	}
	///コンスタントバッファ作成
	void PCTDynamicDraw::Impl::CreateConstantBuffer() {
		auto Dev = App::GetApp()->GetDeviceResources();
		//コンスタントバッファは256バイトにアラインメント
		UINT ConstBuffSize = (sizeof(StaticConstantBuffer) + 255) & ~255;

		//コンスタントバッファリソース（アップロードヒープ）の作成
		ThrowIfFailed(Dev->GetDevice()->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(ConstBuffSize),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_ConstantBufferUploadHeap)),
			L"コンスタントバッファ用のアップロードヒープ作成に失敗しました",
			L"Dev->GetDevice()->CreateCommittedResource()",
			L"PCTDynamicDraw::Impl::CreateConstantBuffer()"
		);
		//コンスタントバッファのビューを作成
		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
		cbvDesc.BufferLocation = m_ConstantBufferUploadHeap->GetGPUVirtualAddress();
		//コンスタントバッファは256バイトにアラインメント
		cbvDesc.SizeInBytes = ConstBuffSize;
		//コンスタントバッファビューを作成すべきデスクプリタヒープ上のハンドルを取得
		//シェーダリソースがある場合コンスタントバッファはシェーダリソースビューのあとに設置する
		CD3DX12_CPU_DESCRIPTOR_HANDLE cbvSrvHandle(
			m_CbvSrvUavDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
			1,
			m_CbvSrvDescriptorHandleIncrementSize
		);
		Dev->GetDevice()->CreateConstantBufferView(&cbvDesc, cbvSrvHandle);
		//コンスタントバッファのアップロードヒープのマップ
		CD3DX12_RANGE readRange(0, 0);
		ThrowIfFailed(m_ConstantBufferUploadHeap->Map(0, &readRange, reinterpret_cast<void**>(&m_pConstantBuffer)),
			L"コンスタントバッファのマップに失敗しました",
			L"pImpl->m_ConstantBufferUploadHeap->Map()",
			L"PCTDynamicDraw::Impl::CreateConstantBuffer()"
		);
	}
	///パイプラインステート作成
	void PCTDynamicDraw::Impl::CreatePipelineState() {
		D3D12_GRAPHICS_PIPELINE_STATE_DESC PineLineDesc;
		m_PipelineState
			= PipelineState::CreateDefault3D<VertexPositionColorTexture, VSPCTStatic, PSPCTStatic>(m_RootSignature, PineLineDesc);
	}
	///コマンドリスト作成
	void PCTDynamicDraw::Impl::CreateCommandList() {
		m_CommandList = CommandList::CreateDefault(m_PipelineState);
		CommandList::Close(m_CommandList);
	}

	///コンスタントバッファ更新
	void PCTDynamicDraw::Impl::UpdateConstantBuffer(const shared_ptr<GameObject>& GameObjectPtr,
		const Color4& Emissive, const Color4& Diffuse, const Matrix4X4& MeshToTransformMatrix) {
		//行列の定義
		auto PtrTrans = GameObjectPtr->GetComponent<Transform>();
		//行列の定義
		Matrix4X4 World, ViewMat, ProjMat;
		//ワールド行列の決定
		World = MeshToTransformMatrix * PtrTrans->GetWorldMatrix();
		//転置する
		World.Transpose();
		//カメラを得る
		auto CameraPtr = GameObjectPtr->OnGetDrawCamera();
		//ビューと射影行列を得る
		ViewMat = CameraPtr->GetViewMatrix();
		//転置する
		ViewMat.Transpose();
		//転置する
		ProjMat = CameraPtr->GetProjMatrix();
		ProjMat.Transpose();
		//コンスタントバッファの準備
		StaticConstantBuffer cb;
		cb.World = World;
		cb.View = ViewMat;
		cb.Projection = ProjMat;
		//エミッシブ
		cb.Emissive = Emissive;
		//デフィーズはすべて通す
		cb.Diffuse = Diffuse;
		//更新
		memcpy(m_pConstantBuffer, reinterpret_cast<void**>(&cb),
			sizeof(StaticConstantBuffer));

	}
	///描画処理
	void PCTDynamicDraw::Impl::DrawObject(const shared_ptr<MeshResource>& MeshRes, bool Trace,
		const shared_ptr<TextureResource>& TextureRes, bool WrapSampler) {
		if (m_Wrap != WrapSampler) {
			auto SamplerDescriptorHandle = m_SamplerDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
			if (WrapSampler) {
				//ラッピングサンプラー
				DynamicSampler::CreateSampler(SamplerState::LinearWrap, SamplerDescriptorHandle);
			}
			else {
				DynamicSampler::CreateSampler(SamplerState::LinearClamp, SamplerDescriptorHandle);
			}
			m_Wrap = WrapSampler;
		}
		if (m_Trace != Trace) {
			D3D12_GRAPHICS_PIPELINE_STATE_DESC PineLineDesc;
			m_PipelineState = PipelineState::CreateDefault3D<VertexPositionColorTexture, VSPCTStatic, PSPCTStatic>(m_RootSignature, PineLineDesc);
			//透明の場合はブレンドステート差し替え
			if (Trace) {
				D3D12_BLEND_DESC blend_desc;
				D3D12_RENDER_TARGET_BLEND_DESC Target;
				ZeroMemory(&blend_desc, sizeof(blend_desc));
				blend_desc.AlphaToCoverageEnable = false;
				blend_desc.IndependentBlendEnable = false;
				ZeroMemory(&Target, sizeof(Target));
				Target.BlendEnable = true;
				Target.SrcBlend = D3D12_BLEND_SRC_ALPHA;
				Target.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
				Target.BlendOp = D3D12_BLEND_OP_ADD;
				Target.SrcBlendAlpha = D3D12_BLEND_ONE;
				Target.DestBlendAlpha = D3D12_BLEND_ZERO;
				Target.BlendOpAlpha = D3D12_BLEND_OP_ADD;
				Target.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
				for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; i++) {
					blend_desc.RenderTarget[i] = Target;
				}
				PineLineDesc.BlendState = blend_desc;
				m_PipelineState = PipelineState::CreateDirect(PineLineDesc);
				m_Trace = Trace;
			}
		}
		//コマンドリストのリセット
		CommandList::Reset(m_PipelineState, m_CommandList);

		MeshRes->UpdateResources<VertexPositionColorTexture>(m_CommandList);
		TextureRes->UpdateResources(m_CommandList);

		//描画
		m_CommandList->SetGraphicsRootSignature(m_RootSignature.Get());
		ID3D12DescriptorHeap* ppHeaps[] = { m_CbvSrvUavDescriptorHeap.Get(), m_SamplerDescriptorHeap.Get() };
		m_CommandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
		for (size_t i = 0; i < m_GPUDescriptorHandleVec.size(); i++) {
			m_CommandList->SetGraphicsRootDescriptorTable(i, m_GPUDescriptorHandleVec[i]);
		}
		auto Dev = App::GetApp()->GetDeviceResources();
		m_CommandList->RSSetViewports(1, &Dev->GetViewport());
		m_CommandList->RSSetScissorRects(1, &Dev->GetScissorRect());

		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(
			Dev->GetRtvHeap()->GetCPUDescriptorHandleForHeapStart(),
			Dev->GetFrameIndex(),
			Dev->GetRtvDescriptorSize());
		CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(
			Dev->GetDsvHeap()->GetCPUDescriptorHandleForHeapStart()
		);
		m_CommandList->OMSetRenderTargets(1, &rtvHandle, FALSE, &dsvHandle);

		m_CommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_CommandList->IASetIndexBuffer(&MeshRes->GetIndexBufferView());
		m_CommandList->IASetVertexBuffers(0, 1, &MeshRes->GetVertexBufferView());
		m_CommandList->DrawIndexedInstanced(MeshRes->GetNumIndicis(), 1, 0, 0, 0);

		//コマンドリストのクローズ
		CommandList::Close(m_CommandList);
		//デバイスにコマンドリストを送る
		Dev->InsertDrawCommandLists(m_CommandList.Get());
	}


	//--------------------------------------------------------------------------------------
	///	PCTDynamic描画コンポーネント
	//--------------------------------------------------------------------------------------
	PCTDynamicDraw::PCTDynamicDraw(const shared_ptr<GameObject>& GameObjectPtr) :
		DynamicBaseDraw(GameObjectPtr),
		pImpl(new Impl())
	{
		//パイプラインステートをデフォルトの3D
		SetBlendState(BlendState::Opaque);
		SetDepthStencilState(DepthStencilState::Default);
		SetRasterizerState(RasterizerState::CullBack);
		SetSamplerState(SamplerState::LinearClamp);
	}

	PCTDynamicDraw::~PCTDynamicDraw() {}

	void PCTDynamicDraw::SetTextureResource(const shared_ptr<TextureResource>& TextureRes) {
		TextureDrawInterface::SetTextureResource(TextureRes);
		pImpl->CreateShaderResourceView(TextureRes);
	}
	void PCTDynamicDraw::SetTextureResource(const wstring& TextureKey) {
		TextureDrawInterface::SetTextureResource(TextureKey);
		pImpl->CreateShaderResourceView(GetTextureResource());
	}


	void PCTDynamicDraw::CreateMesh(vector<VertexPositionColorTexture>& Vertices, vector<uint16_t>& indices) {
		try {
			//メッシュの作成（変更できる）
			auto MeshRes = MeshResource::CreateMeshResource(Vertices, indices, true);
			SetMeshResource(MeshRes);
		}
		catch (...) {
			throw;
		}
	}

	void PCTDynamicDraw::UpdateVertices(const vector<VertexPositionColorTexture>& Vertices) {
		auto Mesh = GetMeshResource();
		if (!Mesh) {
			throw BaseException(
				L"メッシュが作成されていません",
				L"if (!Mesh)",
				L"PCTDynamicDraw::UpdateVertices()"
			);
		}
		//メッシュの頂点の変更
		Mesh->UpdateVirtex(Vertices);
	}

	void PCTDynamicDraw::OnCreate() {
		///ルートシグネチャ作成
		pImpl->CreateRootSignature();
		///デスクプリタヒープ作成
		pImpl->CreateDescriptorHeap();
		///サンプラー作成
		pImpl->CreateSampler();
		///コンスタントバッファ作成
		pImpl->CreateConstantBuffer();
		///パイプラインステート作成
		pImpl->CreatePipelineState();
		///コマンドリスト作成
		pImpl->CreateCommandList();
		//コンスタントバッファの更新
		pImpl->UpdateConstantBuffer(GetGameObject(),
			GetEmissive(), GetDiffuse(), GetMeshToTransformMatrix());
	}
	void PCTDynamicDraw::OnDraw() {
		auto Mesh = GetMeshResource();
		if (!Mesh) {
			throw BaseException(
				L"メッシュが作成されていません",
				L"if (!Mesh)",
				L"PCTDynamicDraw::OnDraw()"
			);
		}
		//テクスチャがなければ描画しない
		auto shTex = GetTextureResource();
		if (!shTex) {
			return;
		}
		//コンスタントバッファの更新
		pImpl->UpdateConstantBuffer(GetGameObject(),
			GetEmissive(), GetDiffuse(), GetMeshToTransformMatrix());
		pImpl->DrawObject(Mesh, GetGameObject()->IsAlphaActive(),
			shTex, GetWrapSampler());

	}

	//--------------------------------------------------------------------------------------
	//	struct PNTDynamicDraw::Impl;
	//--------------------------------------------------------------------------------------
	struct PNTDynamicDraw::Impl {
		bool m_OwnShadowActive;
		Impl() :
			m_OwnShadowActive(false)
		{}
		~Impl() {}
	};

	//--------------------------------------------------------------------------------------
	///	PNTDynamic描画コンポーネント
	//--------------------------------------------------------------------------------------
	PNTDynamicDraw::PNTDynamicDraw(const shared_ptr<GameObject>& GameObjectPtr) :
		DynamicBaseDraw(GameObjectPtr),
		pImpl(new Impl())
	{
	}

	PNTDynamicDraw::~PNTDynamicDraw() {}

	void PNTDynamicDraw::CreateMesh(vector<VertexPositionNormalTexture>& Vertices, vector<uint16_t>& indices) {
	}

	void PNTDynamicDraw::UpdateVertices(const vector<VertexPositionNormalTexture>& Vertices) {
	}


	bool PNTDynamicDraw::GetOwnShadowActive() const {
		return pImpl->m_OwnShadowActive;
	}
	bool PNTDynamicDraw::IsOwnShadowActive() const {
		return pImpl->m_OwnShadowActive;
	}
	void PNTDynamicDraw::SetOwnShadowActive(bool b) {
		pImpl->m_OwnShadowActive = b;
	}



	void PNTDynamicDraw::OnCreate() {
	}

	void PNTDynamicDraw::DrawNotShadow() {
	}

	void PNTDynamicDraw::DrawWithShadow() {
	}

	void PNTDynamicDraw::OnDraw() {
		if (GetOwnShadowActive()) {
			DrawWithShadow();
		}
		else {
			DrawNotShadow();
		}
	}



	//--------------------------------------------------------------------------------------
	//	struct StaticBaseDraw::Impl;
	//	用途: StaticBaseDrawイディオム
	//--------------------------------------------------------------------------------------
	struct StaticBaseDraw::Impl {
		//メッシュのweak_ptr
		weak_ptr<MeshResource> m_MeshResource;
		Impl()
		{}
	};


	//--------------------------------------------------------------------------------------
	///	static描画コンポーネントの親(頂点を変更できない3D描画)
	//--------------------------------------------------------------------------------------
	StaticBaseDraw::StaticBaseDraw(const shared_ptr<GameObject>& GameObjectPtr) :
		Base3DDraw(GameObjectPtr),
		pImpl(new Impl())
	{}
	StaticBaseDraw::~StaticBaseDraw() {}
	shared_ptr<MeshResource> StaticBaseDraw::GetMeshResource() const {
		auto shptr = pImpl->m_MeshResource.lock();
		if (shptr) {
			return shptr;
		}
		return nullptr;
	}
	void StaticBaseDraw::SetMeshResource(const shared_ptr<MeshResource>& MeshRes) {
		pImpl->m_MeshResource = MeshRes;
	}
	void StaticBaseDraw::SetMeshResource(const wstring& MeshKey) {
		pImpl->m_MeshResource = App::GetApp()->GetResource<MeshResource>(MeshKey);
	}

	//--------------------------------------------------------------------------------------
	//	struct PCStaticDraw::Impl;
	//--------------------------------------------------------------------------------------
	struct PCStaticDraw::Impl {
		Impl()
		{}
	};



	//--------------------------------------------------------------------------------------
	///	PCStatic描画コンポーネント
	//--------------------------------------------------------------------------------------
	PCStaticDraw::PCStaticDraw(const shared_ptr<GameObject>& GameObjectPtr) :
		StaticBaseDraw(GameObjectPtr),
		pImpl(new Impl())
	{
	}

	PCStaticDraw::~PCStaticDraw() {}

	void PCStaticDraw::OnDraw() {
	}


	//--------------------------------------------------------------------------------------
	//	struct PTStaticDraw::Impl;
	//--------------------------------------------------------------------------------------
	struct PTStaticDraw::Impl {
		Impl()
		{}
	};


	//--------------------------------------------------------------------------------------
	///	PTStatic描画コンポーネント
	//--------------------------------------------------------------------------------------
	PTStaticDraw::PTStaticDraw(const shared_ptr<GameObject>& GameObjectPtr) :
		StaticBaseDraw(GameObjectPtr),
		pImpl(new Impl())
	{
	}

	PTStaticDraw::~PTStaticDraw() {}


	void PTStaticDraw::OnDraw() {
	}


	//--------------------------------------------------------------------------------------
	//	struct PCTStaticDraw::Impl;
	//--------------------------------------------------------------------------------------
	struct PCTStaticDraw::Impl {
		Impl()
		{}
	};


	//--------------------------------------------------------------------------------------
	///	PCTStatic描画コンポーネント
	//--------------------------------------------------------------------------------------
	PCTStaticDraw::PCTStaticDraw(const shared_ptr<GameObject>& GameObjectPtr) :
		StaticBaseDraw(GameObjectPtr),
		pImpl(new Impl())
	{
	}

	PCTStaticDraw::~PCTStaticDraw() {}


	void PCTStaticDraw::OnDraw() {
	}


	//--------------------------------------------------------------------------------------
	//	struct PNTStaticDraw::Impl;
	//	用途: Implイディオム
	//--------------------------------------------------------------------------------------
	struct PNTStaticDraw::Impl {

		//メッシュリソース
		weak_ptr<MeshResource> m_MeshResource;
		//テクスチャ
		weak_ptr<TextureResource> m_TextureResource;
		bool m_OwnShadowActive;
		bool m_Trace;

		///ルートシグネチャ
		ComPtr<ID3D12RootSignature> m_RootSignature;
		///CbvSrvのデスクプリタハンドルのインクリメントサイズ
		UINT m_CbvSrvDescriptorHandleIncrementSize{ 0 };
		///Samplerのデスクプリタハンドルのインクリメントサイズ
		UINT m_SamplerDescriptorHandleIncrementSize{ 0 };

		///デスクプリタヒープ
		ComPtr<ID3D12DescriptorHeap> m_CbvSrvUavDescriptorHeap;
		ComPtr<ID3D12DescriptorHeap> m_SamplerDescriptorHeap;
		///GPU側デスクプリタのハンドルの配列
		vector<CD3DX12_GPU_DESCRIPTOR_HANDLE> m_GPUDescriptorHandleVec;
		///コンスタントバッファ
		struct StaticConstantBuffer
		{
			Matrix4X4 World;
			Matrix4X4 View;
			Matrix4X4 Projection;
			Vector4 LightDir;
			Color4 Emissive;
			Color4 Diffuse;
			StaticConstantBuffer() {
				memset(this, 0, sizeof(StaticConstantBuffer));
			};
		};
		///コンスタントバッファのオブジェクト側変数
		StaticConstantBuffer m_StaticConstantBuffer;
		///影付きコンスタントバッファ
		struct StaticConstantBufferWithShadow
		{
			Matrix4X4 World;
			Matrix4X4 View;
			Matrix4X4 Projection;
			Vector4 LightDir;
			Color4 Emissive;
			Color4 Diffuse;
			Vector4 LightPos;
			Vector4 EyePos;
			XMUINT4 ActiveFlg;			//テクスチャ=xがアクティブかどうか
			Matrix4X4 LightView;
			Matrix4X4 LightProjection;
			StaticConstantBufferWithShadow() {
				memset(this, 0, sizeof(StaticConstantBufferWithShadow));
			};
		};
		///コンスタントバッファのオブジェクト側変数
		StaticConstantBufferWithShadow m_StaticConstantBufferWithShadow;


		///コンスタントバッファアップロードヒープ
		ComPtr<ID3D12Resource> m_ConstantBufferUploadHeap;
		ComPtr<ID3D12Resource> m_ConstantBufferUploadHeapWithShadow;
		///コンスタントバッファのGPU側変数
		void* m_pConstantBuffer{ nullptr };
		void* m_pConstantBufferWithShadow{ nullptr };
		///パイプラインステート
		D3D12_GRAPHICS_PIPELINE_STATE_DESC m_PineLineDesc;

		ComPtr<ID3D12PipelineState> m_CullBackPipelineState;
		ComPtr<ID3D12PipelineState> m_CullFrontPipelineState;
		///コマンドリスト
		ComPtr<ID3D12GraphicsCommandList> m_CommandList;

		///初期化関数
		///シェーダーリソースビュー作成
		void CreateShaderResourceView(bool IsShadow);
		//コンスタントバッファ更新
		void UpdateConstantBuffer(bool IsShadow);
		///描画処理
		void DrawObject();

		void DrawObjectWithShadow();


		///プロパティ変更
		void RefreshTrace();


		Impl() :
			m_OwnShadowActive(false), m_Trace(false)
		{
			//各行列をIdentityに初期化
			ZeroMemory(&m_StaticConstantBuffer, sizeof(m_StaticConstantBuffer));
			m_StaticConstantBuffer.World = Matrix4X4EX::Identity();
			m_StaticConstantBuffer.View = Matrix4X4EX::Identity();
			m_StaticConstantBuffer.Projection = Matrix4X4EX::Identity();
			m_StaticConstantBuffer.Emissive = Color4(0.0f, 0.0f, 0.0f, 0.0f);
			m_StaticConstantBuffer.Diffuse = Color4(1.0000000f, 0.9607844f, 0.8078432f, 1.0f);
		}
		~Impl() {}
	};


	///シェーダーリソースビュー（テクスチャ）作成
	void PNTStaticDraw::Impl::CreateShaderResourceView(bool IsShadow) {
		auto ShPtr = m_TextureResource.lock();
		if (!ShPtr) {
			return;
		}
		auto Dev = App::GetApp()->GetDeviceResources();
		//テクスチャハンドルを作成
		CD3DX12_CPU_DESCRIPTOR_HANDLE Handle(
			m_CbvSrvUavDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
			0,
			0
		);
		//テクスチャのシェーダリソースビューを作成
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		//フォーマット
		srvDesc.Format = ShPtr->GetTextureResDesc().Format;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = ShPtr->GetTextureResDesc().MipLevels;
		//シェーダリソースビュー
		Dev->GetDevice()->CreateShaderResourceView(
			ShPtr->GetTexture().Get(),
			&srvDesc,
			Handle);

		if (IsShadow) {
			auto ShdowRender = Dev->GetShadowMapRenderTarget();

			CD3DX12_CPU_DESCRIPTOR_HANDLE ShadowHandle(
				m_CbvSrvUavDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
				1,
				m_CbvSrvDescriptorHandleIncrementSize
			);

			D3D12_SHADER_RESOURCE_VIEW_DESC shadowSrvDesc = {};
			shadowSrvDesc.Format = DXGI_FORMAT_R32_FLOAT;
			shadowSrvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
			shadowSrvDesc.Texture2D.MipLevels = 1;
			shadowSrvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

			Dev->GetDevice()->CreateShaderResourceView(ShdowRender->GetDepthStencil().Get(), &shadowSrvDesc, ShadowHandle);
		}
	}

	void PNTStaticDraw::Impl::RefreshTrace() {
		//ブレンドステートとラスタライザ差し替え
		if (m_Trace) {
			D3D12_BLEND_DESC blend_desc;
			D3D12_RENDER_TARGET_BLEND_DESC Target;
			ZeroMemory(&blend_desc, sizeof(blend_desc));
			blend_desc.AlphaToCoverageEnable = false;
			blend_desc.IndependentBlendEnable = false;
			ZeroMemory(&Target, sizeof(Target));
			Target.BlendEnable = true;
			Target.SrcBlend = D3D12_BLEND_SRC_ALPHA;
			Target.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
			Target.BlendOp = D3D12_BLEND_OP_ADD;
			Target.SrcBlendAlpha = D3D12_BLEND_ONE;
			Target.DestBlendAlpha = D3D12_BLEND_ZERO;
			Target.BlendOpAlpha = D3D12_BLEND_OP_ADD;
			Target.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
			for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; i++) {
				blend_desc.RenderTarget[i] = Target;
			}
			m_PineLineDesc.BlendState = blend_desc;
		}
		else {
			m_PineLineDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		}
		m_PineLineDesc.RasterizerState.CullMode = D3D12_CULL_MODE::D3D12_CULL_MODE_FRONT;
		m_CullFrontPipelineState = PipelineState::CreateDirect(m_PineLineDesc);

		m_PineLineDesc.RasterizerState.CullMode = D3D12_CULL_MODE::D3D12_CULL_MODE_BACK;
		m_CullBackPipelineState = PipelineState::CreateDirect(m_PineLineDesc);

	}

	void PNTStaticDraw::Impl::UpdateConstantBuffer(bool IsShadow) {
		if (IsShadow) {
			memcpy(m_pConstantBufferWithShadow, reinterpret_cast<void**>(&m_StaticConstantBufferWithShadow),
				sizeof(m_StaticConstantBufferWithShadow));
		}
		else {
			memcpy(m_pConstantBuffer, reinterpret_cast<void**>(&m_StaticConstantBuffer),
				sizeof(m_StaticConstantBuffer));
		}
	}


	///描画処理
	void PNTStaticDraw::Impl::DrawObject() {
		auto ShMesh = m_MeshResource.lock();
		auto ShTex = m_TextureResource.lock();
		if (!ShMesh || !ShTex) {
			return;
		}

		//コマンドリストのリセット
		if (m_Trace) {
			CommandList::Reset(m_CullFrontPipelineState, m_CommandList);
		}
		else {
			CommandList::Reset(m_CullBackPipelineState, m_CommandList);
		}

		ShMesh->UpdateResources<VertexPositionNormalTexture>(m_CommandList);
		ShTex->UpdateResources(m_CommandList);

		//描画
		m_CommandList->SetGraphicsRootSignature(m_RootSignature.Get());
		ID3D12DescriptorHeap* ppHeaps[] = { m_CbvSrvUavDescriptorHeap.Get(), m_SamplerDescriptorHeap.Get() };
		m_CommandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

		for (size_t i = 0; i < m_GPUDescriptorHandleVec.size(); i++) {
			m_CommandList->SetGraphicsRootDescriptorTable(i, m_GPUDescriptorHandleVec[i]);
		}
		auto Dev = App::GetApp()->GetDeviceResources();
		m_CommandList->RSSetViewports(1, &Dev->GetViewport());
		m_CommandList->RSSetScissorRects(1, &Dev->GetScissorRect());



		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(
			Dev->GetRtvHeap()->GetCPUDescriptorHandleForHeapStart(),
			Dev->GetFrameIndex(),
			Dev->GetRtvDescriptorSize());
		CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(
			Dev->GetDsvHeap()->GetCPUDescriptorHandleForHeapStart()
		);
		m_CommandList->OMSetRenderTargets(1, &rtvHandle, FALSE, &dsvHandle);

		m_CommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_CommandList->IASetIndexBuffer(&ShMesh->GetIndexBufferView());
		m_CommandList->IASetVertexBuffers(0, 1, &ShMesh->GetVertexBufferView());


		m_CommandList->DrawIndexedInstanced(ShMesh->GetNumIndicis(), 1, 0, 0, 0);
		if (m_Trace) {
			m_CommandList->SetPipelineState(m_CullBackPipelineState.Get());
			m_CommandList->DrawIndexedInstanced(ShMesh->GetNumIndicis(), 1, 0, 0, 0);
		}

		//コマンドリストのクローズ
		CommandList::Close(m_CommandList);
		//デバイスにコマンドリストを送る
		Dev->InsertDrawCommandLists(m_CommandList.Get());
	}

	void PNTStaticDraw::Impl::DrawObjectWithShadow() {
		auto ShMesh = m_MeshResource.lock();
		auto ShTex = m_TextureResource.lock();
		if (!ShMesh || !ShTex) {
			return;
		}

		//コマンドリストのリセット
		if (m_Trace) {
			CommandList::Reset(m_CullFrontPipelineState, m_CommandList);
		}
		else {
			CommandList::Reset(m_CullBackPipelineState, m_CommandList);
		}

		ShMesh->UpdateResources<VertexPositionNormalTexture>(m_CommandList);
		ShTex->UpdateResources(m_CommandList);

		//描画
		m_CommandList->SetGraphicsRootSignature(m_RootSignature.Get());
		ID3D12DescriptorHeap* ppHeaps[] = { m_CbvSrvUavDescriptorHeap.Get(), m_SamplerDescriptorHeap.Get() };
		m_CommandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

		for (size_t i = 0; i < m_GPUDescriptorHandleVec.size(); i++) {
			m_CommandList->SetGraphicsRootDescriptorTable(i, m_GPUDescriptorHandleVec[i]);
		}
		auto Dev = App::GetApp()->GetDeviceResources();
		m_CommandList->RSSetViewports(1, &Dev->GetViewport());
		m_CommandList->RSSetScissorRects(1, &Dev->GetScissorRect());



		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(
			Dev->GetRtvHeap()->GetCPUDescriptorHandleForHeapStart(),
			Dev->GetFrameIndex(),
			Dev->GetRtvDescriptorSize());
		CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(
			Dev->GetDsvHeap()->GetCPUDescriptorHandleForHeapStart()
		);
		m_CommandList->OMSetRenderTargets(1, &rtvHandle, FALSE, &dsvHandle);

		


		m_CommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_CommandList->IASetIndexBuffer(&ShMesh->GetIndexBufferView());
		m_CommandList->IASetVertexBuffers(0, 1, &ShMesh->GetVertexBufferView());



		m_CommandList->DrawIndexedInstanced(ShMesh->GetNumIndicis(), 1, 0, 0, 0);
		if (m_Trace) {
			m_CommandList->SetPipelineState(m_CullBackPipelineState.Get());
			m_CommandList->DrawIndexedInstanced(ShMesh->GetNumIndicis(), 1, 0, 0, 0);
		}
		//コマンドリストのクローズ
		CommandList::Close(m_CommandList);
		//デバイスにコマンドリストを送る
		Dev->InsertDrawCommandLists(m_CommandList.Get());

	}






	//--------------------------------------------------------------------------------------
	//	class PNTStaticDraw : public DrawComponent;
	//	用途: PNTStatic描画コンポーネント
	//--------------------------------------------------------------------------------------
	PNTStaticDraw::PNTStaticDraw(const shared_ptr<GameObject>& GameObjectPtr) :
		DrawComponent(GameObjectPtr),
		pImpl(new Impl()) {
		//パイプラインステートをデフォルトの３D
		SetBlendState(BlendState::Opaque);
		SetDepthStencilState(DepthStencilState::Default);
		SetRasterizerState(RasterizerState::CullBack);
		SetSamplerState(SamplerState::LinearClamp);
	}

	PNTStaticDraw::~PNTStaticDraw() {}

	void PNTStaticDraw::CreateNotShadow() {
		if (ObjectInterface::IsCreated() && !pImpl->m_OwnShadowActive) {
			return;
		}
		//ルートシグネチャ
		pImpl->m_RootSignature = RootSignature::CreateSrvSmpCbv();
		//デスクプリタヒープ
		auto Dev = App::GetApp()->GetDeviceResources();
		{
			pImpl->m_CbvSrvDescriptorHandleIncrementSize =
				Dev->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
			//CbvSrvデスクプリタヒープ
			pImpl->m_CbvSrvUavDescriptorHeap = DescriptorHeap::CreateCbvSrvUavHeap(1 + 1);
			//サンプラーデスクプリタヒープ
			pImpl->m_SamplerDescriptorHeap = DescriptorHeap::CreateSamplerHeap(1);
			//GPU側デスクプリタヒープのハンドルの配列の作成
			pImpl->m_GPUDescriptorHandleVec.clear();
			CD3DX12_GPU_DESCRIPTOR_HANDLE SrvHandle(
				pImpl->m_CbvSrvUavDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
				0,
				0
			);
			pImpl->m_GPUDescriptorHandleVec.push_back(SrvHandle);
			CD3DX12_GPU_DESCRIPTOR_HANDLE SamplerHandle(
				pImpl->m_SamplerDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
				0,
				0
			);
			pImpl->m_GPUDescriptorHandleVec.push_back(SamplerHandle);
			CD3DX12_GPU_DESCRIPTOR_HANDLE CbvHandle(
				pImpl->m_CbvSrvUavDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
				1,
				pImpl->m_CbvSrvDescriptorHandleIncrementSize
			);
			pImpl->m_GPUDescriptorHandleVec.push_back(CbvHandle);

		}
		//サンプラー
		{
			auto SamplerDescriptorHandle = pImpl->m_SamplerDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
			DynamicSampler::CreateSampler(SamplerState::LinearClamp, SamplerDescriptorHandle);
		}
		//コンスタントバッファ
		{
			//コンスタントバッファは256バイトにアラインメント
			UINT ConstBuffSize = (sizeof(pImpl->m_StaticConstantBuffer) + 255) & ~255;
			//コンスタントバッファリソース（アップロードヒープ）の作成
			ThrowIfFailed(Dev->GetDevice()->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
				D3D12_HEAP_FLAG_NONE,
				&CD3DX12_RESOURCE_DESC::Buffer(ConstBuffSize),
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&pImpl->m_ConstantBufferUploadHeap)),
				L"コンスタントバッファ用のアップロードヒープ作成に失敗しました",
				L"Dev->GetDevice()->CreateCommittedResource()",
				L"PNTStaticDraw::CreateNotShadow()"
			);
			//コンスタントバッファのビューを作成
			D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
			cbvDesc.BufferLocation = pImpl->m_ConstantBufferUploadHeap->GetGPUVirtualAddress();
			cbvDesc.SizeInBytes = ConstBuffSize;
			//コンスタントバッファビューを作成すべきデスクプリタヒープ上のハンドルを取得
			//シェーダリソースがある場合コンスタントバッファはシェーダリソースビューのあとに設置する
			CD3DX12_CPU_DESCRIPTOR_HANDLE cbvSrvHandle(
				pImpl->m_CbvSrvUavDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
				1,
				pImpl->m_CbvSrvDescriptorHandleIncrementSize
			);

			Dev->GetDevice()->CreateConstantBufferView(&cbvDesc, cbvSrvHandle);
			//コンスタントバッファのアップロードヒープのマップ
			CD3DX12_RANGE readRange(0, 0);
			ThrowIfFailed(pImpl->m_ConstantBufferUploadHeap->Map(0, &readRange, reinterpret_cast<void**>(&pImpl->m_pConstantBuffer)),
				L"コンスタントバッファのマップに失敗しました",
				L"pImpl->m_ConstantBufferUploadHeap->Map()",
				L"PNTStaticDraw::CreateNotShadow()"
			);

		}
		//シェーダリソースビューはテクスチャセット時に作成
		//パイプラインステートの作成
		{
			PipelineState::CreateDefault3D<VertexPositionNormalTexture, VSPNTStatic, PSPNTStatic>(pImpl->m_RootSignature, pImpl->m_PineLineDesc);
			pImpl->m_PineLineDesc.RasterizerState.FillMode = D3D12_FILL_MODE::D3D12_FILL_MODE_SOLID;
			pImpl->m_PineLineDesc.RasterizerState.CullMode = D3D12_CULL_MODE::D3D12_CULL_MODE_FRONT;
			pImpl->m_CullFrontPipelineState = PipelineState::CreateDirect(pImpl->m_PineLineDesc);
			pImpl->m_PineLineDesc.RasterizerState.CullMode = D3D12_CULL_MODE::D3D12_CULL_MODE_BACK;
			pImpl->m_CullBackPipelineState = PipelineState::CreateDirect(pImpl->m_PineLineDesc);
		}
		//コマンドリストは裏面カリングに初期化
		{
			pImpl->m_CommandList = CommandList::CreateDefault(pImpl->m_CullBackPipelineState);
			pImpl->UpdateConstantBuffer(false);
			CommandList::Close(pImpl->m_CommandList);
		}
		//コンスタントバッファ更新
		pImpl->UpdateConstantBuffer(false);
		pImpl->m_OwnShadowActive = false;
	}

	void PNTStaticDraw::CreateWithShadow() {
		if (ObjectInterface::IsCreated() && pImpl->m_OwnShadowActive) {
			return;
		}
		//ルートシグネチャシャドウ付き
		pImpl->m_RootSignature = RootSignature::CreateSrv2Smp2Cbv();
		//デスクプリタヒープ
		auto Dev = App::GetApp()->GetDeviceResources();
		{
			pImpl->m_CbvSrvDescriptorHandleIncrementSize =
				Dev->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
			pImpl->m_SamplerDescriptorHandleIncrementSize =
				Dev->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER);

			//CbvSrvデスクプリタヒープ
			pImpl->m_CbvSrvUavDescriptorHeap = DescriptorHeap::CreateCbvSrvUavHeap(1 + 2);
			//サンプラーデスクプリタヒープ
			pImpl->m_SamplerDescriptorHeap = DescriptorHeap::CreateSamplerHeap(2);
			//GPU側デスクプリタヒープのハンドルの配列の作成
			pImpl->m_GPUDescriptorHandleVec.clear();
			CD3DX12_GPU_DESCRIPTOR_HANDLE SrvHandle1(
				pImpl->m_CbvSrvUavDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
				0,
				0
			);
			pImpl->m_GPUDescriptorHandleVec.push_back(SrvHandle1);
			CD3DX12_GPU_DESCRIPTOR_HANDLE SrvHandle2(
				pImpl->m_CbvSrvUavDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
				1,
				pImpl->m_CbvSrvDescriptorHandleIncrementSize
			);
			pImpl->m_GPUDescriptorHandleVec.push_back(SrvHandle2);

			CD3DX12_GPU_DESCRIPTOR_HANDLE SamplerHandle1(
				pImpl->m_SamplerDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
				0,
				0
			);
			pImpl->m_GPUDescriptorHandleVec.push_back(SamplerHandle1);

			CD3DX12_GPU_DESCRIPTOR_HANDLE SamplerHandle2(
				pImpl->m_SamplerDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
				1,
				pImpl->m_SamplerDescriptorHandleIncrementSize
			);
			pImpl->m_GPUDescriptorHandleVec.push_back(SamplerHandle2);


			CD3DX12_GPU_DESCRIPTOR_HANDLE CbvHandle(
				pImpl->m_CbvSrvUavDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
				2,
				pImpl->m_CbvSrvDescriptorHandleIncrementSize
			);
			pImpl->m_GPUDescriptorHandleVec.push_back(CbvHandle);
		}
		//サンプラー
		{
			auto SamplerDescriptorHandleWithShadow1 = pImpl->m_SamplerDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
			DynamicSampler::CreateSampler(SamplerState::LinearClamp, SamplerDescriptorHandleWithShadow1);

			CD3DX12_CPU_DESCRIPTOR_HANDLE SamplerDescriptorHandleWithShadow2{
				pImpl->m_SamplerDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
				1,
				pImpl->m_SamplerDescriptorHandleIncrementSize
			};
			DynamicSampler::CreateSampler(SamplerState::ComparisonLinear, SamplerDescriptorHandleWithShadow2);
		}
		//コンスタントバッファ
		{
			//コンスタントバッファは256バイトにアラインメント
			UINT ConstBuffSize = (sizeof(pImpl->m_StaticConstantBufferWithShadow) + 255) & ~255;
			//コンスタントバッファリソース（アップロードヒープ）の作成
			ThrowIfFailed(Dev->GetDevice()->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
				D3D12_HEAP_FLAG_NONE,
				&CD3DX12_RESOURCE_DESC::Buffer(ConstBuffSize),
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&pImpl->m_ConstantBufferUploadHeapWithShadow)),
				L"コンスタントバッファ用のアップロードヒープ作成に失敗しました",
				L"Dev->GetDevice()->CreateCommittedResource()",
				L"PNTStaticDraw::CreateWithShadow()"
			);
			//コンスタントバッファのビューを作成
			D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
			cbvDesc.BufferLocation = pImpl->m_ConstantBufferUploadHeapWithShadow->GetGPUVirtualAddress();
			cbvDesc.SizeInBytes = ConstBuffSize;
			//コンスタントバッファビューを作成すべきデスクプリタヒープ上のハンドルを取得
			//シェーダリソースがある場合コンスタントバッファはシェーダリソースビューのあとに設置する
			CD3DX12_CPU_DESCRIPTOR_HANDLE cbvSrvHandle(
				pImpl->m_CbvSrvUavDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
				2,
				pImpl->m_CbvSrvDescriptorHandleIncrementSize
			);

			Dev->GetDevice()->CreateConstantBufferView(&cbvDesc, cbvSrvHandle);
			//コンスタントバッファのアップロードヒープのマップ
			CD3DX12_RANGE readRange(0, 0);
			ThrowIfFailed(pImpl->m_ConstantBufferUploadHeapWithShadow->Map(0, &readRange, reinterpret_cast<void**>(&pImpl->m_pConstantBufferWithShadow)),
				L"コンスタントバッファのマップに失敗しました",
				L"pImpl->m_ConstantBufferUploadHeapWithShadow->Map()",
				L"PNTStaticDraw::CreateWithShadow()"
			);

		}
		//シェーダリソースビューはテクスチャセット時に作成
		//パイプラインステートの作成
		{
			//シャドウ付きパイプラインステートの作成
			PipelineState::CreateDefault3D<VertexPositionNormalTexture, VSPNTStaticShadow, PSPNTStaticShadow>(pImpl->m_RootSignature,
				pImpl->m_PineLineDesc);
			pImpl->m_PineLineDesc.RasterizerState.FillMode = D3D12_FILL_MODE::D3D12_FILL_MODE_SOLID;
			pImpl->m_PineLineDesc.RasterizerState.CullMode = D3D12_CULL_MODE::D3D12_CULL_MODE_FRONT;
			pImpl->m_CullFrontPipelineState = PipelineState::CreateDirect(pImpl->m_PineLineDesc);
			pImpl->m_PineLineDesc.RasterizerState.CullMode = D3D12_CULL_MODE::D3D12_CULL_MODE_BACK;
			pImpl->m_CullBackPipelineState = PipelineState::CreateDirect(pImpl->m_PineLineDesc);
		}
		//コマンドリストは裏面カリングに初期化
		{
			pImpl->m_CommandList = CommandList::CreateDefault(pImpl->m_CullBackPipelineState);
			pImpl->UpdateConstantBuffer(true);
			CommandList::Close(pImpl->m_CommandList);
		}
		//コンスタントバッファ更新
		pImpl->UpdateConstantBuffer(true);
		pImpl->m_OwnShadowActive = true;

	}



	void PNTStaticDraw::OnCreate() {
		//影無しに初期化
		CreateNotShadow();
	}

	shared_ptr<MeshResource> PNTStaticDraw::GetMeshResource() const {
		//メッシュがなければリターン
		auto shptr = pImpl->m_MeshResource.lock();
		if (!shptr) {
			throw BaseException(
				L"メッシュが設定されてません",
				L"if (!shptr)",
				L"PNTStaticDraw::GetMeshResource()"
			);
		}
		return shptr;
	}

	void PNTStaticDraw::SetMeshResource(const shared_ptr<MeshResource>& MeshRes) {
		pImpl->m_MeshResource = MeshRes;
	}
	void PNTStaticDraw::SetMeshResource(const wstring& MeshKey) {
		pImpl->m_MeshResource = App::GetApp()->GetResource<MeshResource>(MeshKey);
	}
	void PNTStaticDraw::SetTextureResource(const shared_ptr<TextureResource>& TextureRes) {
		pImpl->m_TextureResource = TextureRes;
		pImpl->CreateShaderResourceView(IsOwnShadowActive());
	}
	void PNTStaticDraw::SetTextureResource(const wstring& TextureKey) {
		auto Res = App::GetApp()->GetResource<TextureResource>(TextureKey);
		pImpl->m_TextureResource = Res;
		pImpl->CreateShaderResourceView(IsOwnShadowActive());
	}
	shared_ptr<TextureResource> PNTStaticDraw::GetTextureResource() const {
		//テクスチャがなければnullを返す
		auto shptr = pImpl->m_TextureResource.lock();
		if (!shptr){
			return nullptr;
		}
		return pImpl->m_TextureResource.lock();
	}

	Color4 PNTStaticDraw::GetEmissive() const {
		return pImpl->m_StaticConstantBuffer.Emissive;
	}
	void PNTStaticDraw::SetEmissive(const Color4& col) {
		pImpl->m_StaticConstantBuffer.Emissive = col;
	}

	bool PNTStaticDraw::GetAlphaActive() const {
		return pImpl->m_Trace;

	}
	void PNTStaticDraw::SetAlphaActive(bool b) {
		if (b != pImpl->m_Trace) {
			pImpl->m_Trace = b;
			pImpl->RefreshTrace();
		}
	}

	bool PNTStaticDraw::GetOwnShadowActive() const {
		return pImpl->m_OwnShadowActive;
	}
	bool PNTStaticDraw::IsOwnShadowActive() const {
		return pImpl->m_OwnShadowActive;
	}
	void PNTStaticDraw::SetOwnShadowActive(bool b) {
		if (b) {
			CreateWithShadow();
		}
		else {
			CreateNotShadow();
		}
	}


	void PNTStaticDraw::DrawNotShadow() {
		auto PtrStage = GetGameObject()->GetStage();
		SetAlphaActive(GetGameObject()->GetAlphaActive());
		auto PtrMeshResource = GetMeshResource();
		//行列の定義
		auto PtrTrans = GetGameObject()->GetComponent<Transform>();
		//ワールド行列の決定
		pImpl->m_StaticConstantBuffer.World = GetMeshToTransformMatrix() * PtrTrans->GetWorldMatrix();
		//転置する
		pImpl->m_StaticConstantBuffer.World.Transpose();
		//ビュー行列の決定
		auto StageView = PtrStage->GetView();
		pImpl->m_StaticConstantBuffer.View = StageView->GetTargetCamera()->GetViewMatrix();
		//転置する
		pImpl->m_StaticConstantBuffer.View.Transpose();
		//射影行列の決定
		pImpl->m_StaticConstantBuffer.Projection = StageView->GetTargetCamera()->GetProjMatrix();
		//転置する
		pImpl->m_StaticConstantBuffer.Projection.Transpose();



		//ライティング
		auto StageLight = PtrStage->GetLight();
		pImpl->m_StaticConstantBuffer.LightDir = StageLight->GetTargetLight().m_Directional;
		//エミッシブ
		pImpl->m_StaticConstantBuffer.Emissive = GetEmissive();
		//ディフューズ
		pImpl->m_StaticConstantBuffer.Diffuse = StageLight->GetTargetLight().m_DiffuseColor;
		//更新
		pImpl->UpdateConstantBuffer(false);
		pImpl->DrawObject();
	}

	void PNTStaticDraw::DrawWithShadow() {
		auto PtrStage = GetGameObject()->GetStage();
		SetAlphaActive(GetGameObject()->GetAlphaActive());
		auto PtrMeshResource = GetMeshResource();
		//行列の定義
		auto PtrTrans = GetGameObject()->GetComponent<Transform>();
		//ワールド行列の決定
		pImpl->m_StaticConstantBufferWithShadow.World = GetMeshToTransformMatrix() * PtrTrans->GetWorldMatrix();
		//転置する
		pImpl->m_StaticConstantBufferWithShadow.World.Transpose();
		//ビュー行列の決定
		auto StageView = PtrStage->GetView();
		pImpl->m_StaticConstantBufferWithShadow.View = StageView->GetTargetCamera()->GetViewMatrix();
		//転置する
		pImpl->m_StaticConstantBufferWithShadow.View.Transpose();
		//射影行列の決定
		pImpl->m_StaticConstantBufferWithShadow.Projection = StageView->GetTargetCamera()->GetProjMatrix();
		//転置する
		pImpl->m_StaticConstantBufferWithShadow.Projection.Transpose();
		//ライティング
		auto StageLight = PtrStage->GetLight();
		pImpl->m_StaticConstantBufferWithShadow.LightDir = StageLight->GetTargetLight().m_Directional;
		//エミッシブ
		pImpl->m_StaticConstantBufferWithShadow.Emissive = GetEmissive();
		//ディフューズ
		pImpl->m_StaticConstantBufferWithShadow.Diffuse = StageLight->GetTargetLight().m_DiffuseColor;



		Vector3 CalcLightDir = -1.0 * StageLight->GetTargetLight().m_Directional;
		Vector3 LightAt = StageView->GetTargetCamera()->GetAt();
		Vector3 LightEye = CalcLightDir;
		LightEye *= Shadowmap::GetLightHeight();
		LightEye = LightAt + LightEye;

		pImpl->m_StaticConstantBufferWithShadow.LightPos = LightEye;
		pImpl->m_StaticConstantBufferWithShadow.LightPos.w = 1.0f;

		pImpl->m_StaticConstantBufferWithShadow.EyePos = StageView->GetTargetCamera()->GetEye();
		pImpl->m_StaticConstantBufferWithShadow.EyePos.w = 1.0f;
		pImpl->m_StaticConstantBufferWithShadow.ActiveFlg.x = 1;

		Matrix4X4 LightView, LightProj;
		//ライトのビューと射影を計算
		LightView.LookAtLH(LightEye, LightAt, Vector3(0, 1.0f, 0));
		LightProj.OrthographicLH(Shadowmap::GetViewWidth(), Shadowmap::GetViewHeight(),
			Shadowmap::GetLightNear(), Shadowmap::GetLightFar());
		pImpl->m_StaticConstantBufferWithShadow.LightView = Matrix4X4EX::Transpose(LightView);
		pImpl->m_StaticConstantBufferWithShadow.LightProjection = Matrix4X4EX::Transpose(LightProj);

		//更新
		pImpl->UpdateConstantBuffer(true);
		pImpl->DrawObjectWithShadow();

	}


	void PNTStaticDraw::OnDraw() {
		if (GetOwnShadowActive()) {
			DrawWithShadow();
		}
		else {
			DrawNotShadow();
		}
	}



}
//end basecross
