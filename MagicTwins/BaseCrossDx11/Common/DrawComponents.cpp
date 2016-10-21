/*!
@file DrawComponents.cpp
@brief �`��R���|�[�l���g����
*/
#include "stdafx.h"

namespace basecross {

	//Shadowmap
	IMPLEMENT_DX11_CONSTANT_BUFFER(CBShadow)
	IMPLEMENT_DX11_VERTEX_SHADER(VSShadowmap, App::GetApp()->m_wstrRelativeShadersPath + L"VSShadowmap.cso")
	IMPLEMENT_DX11_VERTEX_SHADER(VSShadowmapBone, App::GetApp()->m_wstrRelativeShadersPath + L"VSShadowmapBone.cso")

	//�X�v���C�g�p
	IMPLEMENT_DX11_CONSTANT_BUFFER(CBSprite)

	//PCSprite
	IMPLEMENT_DX11_VERTEX_SHADER(VSPCSprite, App::GetApp()->m_wstrRelativeShadersPath + L"VSPCSprite.cso")
	IMPLEMENT_DX11_PIXEL_SHADER(PSPCSprite, App::GetApp()->m_wstrRelativeShadersPath + L"PSPCSprite.cso")

	//PTSprite
	IMPLEMENT_DX11_VERTEX_SHADER(VSPTSprite, App::GetApp()->m_wstrRelativeShadersPath + L"VSPTSprite.cso")
	IMPLEMENT_DX11_PIXEL_SHADER(PSPTSprite, App::GetApp()->m_wstrRelativeShadersPath + L"PSPTSprite.cso")

	//PCTSprite
	IMPLEMENT_DX11_VERTEX_SHADER(VSPCTSprite, App::GetApp()->m_wstrRelativeShadersPath + L"VSPCTSprite.cso")
	IMPLEMENT_DX11_PIXEL_SHADER(PSPCTSprite, App::GetApp()->m_wstrRelativeShadersPath + L"PSPCTSprite.cso")


	//PCStatic
	IMPLEMENT_DX11_CONSTANT_BUFFER(CBStatic)
	IMPLEMENT_DX11_VERTEX_SHADER(VSPCStatic, App::GetApp()->m_wstrRelativeShadersPath + L"VSPCStatic.cso")
	IMPLEMENT_DX11_PIXEL_SHADER(PSPCStatic, App::GetApp()->m_wstrRelativeShadersPath + L"PSPCStatic.cso")
	//PTStatic
	IMPLEMENT_DX11_VERTEX_SHADER(VSPTStatic, App::GetApp()->m_wstrRelativeShadersPath + L"VSPTStatic.cso")
	IMPLEMENT_DX11_PIXEL_SHADER(PSPTStatic, App::GetApp()->m_wstrRelativeShadersPath + L"PSPTStatic.cso")

	//PCTStatic
	IMPLEMENT_DX11_VERTEX_SHADER(VSPCTInstance, App::GetApp()->m_wstrRelativeShadersPath + L"VSPCTInstance.cso")
	IMPLEMENT_DX11_VERTEX_SHADER(VSPCTStatic, App::GetApp()->m_wstrRelativeShadersPath + L"VSPCTStatic.cso")
	IMPLEMENT_DX11_PIXEL_SHADER(PSPCTStatic, App::GetApp()->m_wstrRelativeShadersPath + L"PSPCTStatic.cso")



	//PNTStatic
	IMPLEMENT_DX11_CONSTANT_BUFFER(CBPNTStatic)
	IMPLEMENT_DX11_VERTEX_SHADER(VSPNTStatic, App::GetApp()->m_wstrRelativeShadersPath + L"VSPNTStatic.cso")
	IMPLEMENT_DX11_PIXEL_SHADER(PSPNTStatic, App::GetApp()->m_wstrRelativeShadersPath + L"PSPNTStatic.cso")
	IMPLEMENT_DX11_PIXEL_SHADER(PSPNTStaticNoTexture, App::GetApp()->m_wstrRelativeShadersPath + L"PSPNTStaticNoTexture.cso")

	//PNTStaticShadow
	IMPLEMENT_DX11_CONSTANT_BUFFER(CBPNTStaticShadow)
	IMPLEMENT_DX11_VERTEX_SHADER(VSPNTStaticShadow, App::GetApp()->m_wstrRelativeShadersPath + L"VSPNTStaticShadow.cso")
	IMPLEMENT_DX11_PIXEL_SHADER(PSPNTStaticShadow, App::GetApp()->m_wstrRelativeShadersPath + L"PSPNTStaticShadow.cso")
	IMPLEMENT_DX11_PIXEL_SHADER(PSPNTStaticShadow2, App::GetApp()->m_wstrRelativeShadersPath + L"PSPNTStaticShadow2.cso")

	//PNTBone
	IMPLEMENT_DX11_CONSTANT_BUFFER(CBPNTBone)
	IMPLEMENT_DX11_VERTEX_SHADER(VSPNTBone, App::GetApp()->m_wstrRelativeShadersPath + L"VSPNTBone.cso")

	IMPLEMENT_DX11_CONSTANT_BUFFER(CBPNTBoneShadow)
	IMPLEMENT_DX11_VERTEX_SHADER(VSPNTBoneShadow, App::GetApp()->m_wstrRelativeShadersPath + L"VSPNTBoneShadow.cso")


	//--------------------------------------------------------------------------------------
	//	struct DrawComponent::Impl;
	//	�p�r: Impl�C�f�B�I��
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
	///	�`��R���|�[�l���g�̐e�N���X����
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
	//	�p�r: Impl�C�f�B�I��
	//--------------------------------------------------------------------------------------
	struct Shadowmap::Impl {
		static float m_LightHeight;	//���C�g�̍����i���������̒l�Ŋ|����j
		static float m_LightNear;	//���C�g��Near
		static float m_LightFar;		//���C�g��Far
		static float m_ViewWidth;
		static float m_ViewHeight;

		weak_ptr<MeshResource> m_MeshResource;	//���b�V�����\�[�X


		Impl()
		{}
		~Impl() {}
	};

	float Shadowmap::Impl::m_LightHeight(20.0f);
	float Shadowmap::Impl::m_LightNear(1.0f);
	float Shadowmap::Impl::m_LightFar(200.0f);
	float Shadowmap::Impl::m_ViewWidth(32.0f);
	float Shadowmap::Impl::m_ViewHeight(32.0f);


	//--------------------------------------------------------------------------------------
	//	class Shadowmap : public Component;
	//	�p�r: �V���h�E�}�b�v�R���|�[�l���g�i�O�����p�j
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
					L"���b�V�����\�[�X��������܂���",
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
					L"���b�V���L�[���󔒂ł�",
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
		//���b�V�����\�[�X�̎擾
		auto PtrMeshResource = GetMeshResource();

		if (PtrMeshResource) {


			auto Dev = App::GetApp()->GetDeviceResources();
			auto pID3D11DeviceContext = Dev->GetD3DDeviceContext();
			//�X�e�[�^�X�̃|�C���^
			auto RenderStatePtr = Dev->GetRenderState();

			//�s��̒�`
			Matrix4X4 World, LightView, LightProj;
			//�s��̒�`
			auto PtrTrans = GetGameObject()->GetComponent<Transform>();
			//���[���h�s��̌���
			World.AffineTransformation(
				PtrTrans->GetScale(),			//�X�P�[�����O
				PtrTrans->GetPivot(),		//��]�̒��S�i�d�S�j
				PtrTrans->GetQuaternion(),				//��]�p�x
				PtrTrans->GetPosition()				//�ʒu
			);
			Matrix4X4 RealWorldMatrix = GetMeshToTransformMatrix() * World;
			//�r���[�s��̌���
			auto StageView = PtrStage->GetView();
			//���C�g�̎擾
			auto StageLight = PtrStage->GetLight();
			Vector3 LightDir = -1.0 * StageLight->GetTargetLight().m_Directional;
			Vector3 LightAt = StageView->GetTargetCamera()->GetAt();
			Vector3 LightEye = LightAt + (LightDir * GetLightHeight());
			//���C�g�̃r���[�Ǝˉe���v�Z
			LightView.LookAtLH(LightEye, LightAt, Vector3(0, 1.0f, 0));
			LightProj.OrthographicLH(GetViewWidth(), GetViewHeight(), GetLightNear(), GetLightFar());

			ShadowConstantBuffer Cb;
			Cb.mWorld = Matrix4X4EX::Transpose(RealWorldMatrix);
			Cb.mView = Matrix4X4EX::Transpose(LightView);
			Cb.mProj = Matrix4X4EX::Transpose(LightProj);

			bool IsSkin = false;
			bool IsSkinStride = false;
			if (PtrMeshResource->IsSkining()) {
				auto DrawCompPtr = GetGameObject()->GetDynamicComponent<DrawComponent>(false);
				if (auto* pLocalBoneVec = DrawCompPtr->GetVecLocalBonesPtr()) {
					if (pLocalBoneVec) {
						//�{�[���̐ݒ�
						size_t BoneSz = pLocalBoneVec->size();
						UINT cb_count = 0;
						for (size_t b = 0; b < BoneSz; b++) {
							Matrix4X4 mat = pLocalBoneVec->at(b);
							mat.Transpose();
							Cb.Bones[cb_count] = ((XMMATRIX)mat).r[0];
							Cb.Bones[cb_count + 1] = ((XMMATRIX)mat).r[1];
							Cb.Bones[cb_count + 2] = ((XMMATRIX)mat).r[2];
							cb_count += 3;
						}
						IsSkin = true;
					}
				}
				IsSkinStride = true;
			}
			//������`�揈��
			//�R���X�^���g�o�b�t�@�̍X�V
			pID3D11DeviceContext->UpdateSubresource(CBShadow::GetPtr()->GetBuffer(), 0, nullptr, &Cb, 0, 0);

			if (IsSkin) {
				//�C���v�b�g���C�A�E�g�̃Z�b�g
				pID3D11DeviceContext->IASetInputLayout(VSShadowmapBone::GetPtr()->GetInputLayout());
				//�X�g���C�h�ƃI�t�Z�b�g
				UINT stride = sizeof(VertexPositionNormalTextureSkinning);
				UINT offset = 0;
				//���_�o�b�t�@���Z�b�g
				pID3D11DeviceContext->IASetVertexBuffers(0, 1, PtrMeshResource->GetVertexBuffer().GetAddressOf(), &stride, &offset);
				//���_�V�F�[�_�[�̃Z�b�g
				pID3D11DeviceContext->VSSetShader(VSShadowmapBone::GetPtr()->GetShader(), nullptr, 0);
			}
			else {
				//�C���v�b�g���C�A�E�g�̃Z�b�g
				pID3D11DeviceContext->IASetInputLayout(VSShadowmap::GetPtr()->GetInputLayout());
				//�X�g���C�h�ƃI�t�Z�b�g
				UINT stride = sizeof(VertexPositionNormalTexture);
				if (IsSkinStride) {
					stride = sizeof(VertexPositionNormalTextureSkinning);
				}
				UINT offset = 0;
				//���_�o�b�t�@���Z�b�g
				pID3D11DeviceContext->IASetVertexBuffers(0, 1, PtrMeshResource->GetVertexBuffer().GetAddressOf(), &stride, &offset);
				//���_�V�F�[�_�[�̃Z�b�g
				pID3D11DeviceContext->VSSetShader(VSShadowmap::GetPtr()->GetShader(), nullptr, 0);
			}



			//�C���f�b�N�X�o�b�t�@�̃Z�b�g
			pID3D11DeviceContext->IASetIndexBuffer(PtrMeshResource->GetIndexBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);
			//�`����@�i3�p�`�j
			pID3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			//�s�N�Z���V�F�[�_�̓Z�b�g���Ȃ��I
			pID3D11DeviceContext->PSSetShader(nullptr, nullptr, 0);
			//�W�I���g���V�F�[�_�̐ݒ�i�g�p���Ȃ��j
			pID3D11DeviceContext->GSSetShader(nullptr, nullptr, 0);

			//�R���X�^���g�o�b�t�@�̐ݒ�
			ID3D11Buffer* pConstantBuffer = CBShadow::GetPtr()->GetBuffer();
			ID3D11Buffer* pNullConstantBuffer = nullptr;
			pID3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
			//�R���X�^���g�o�b�t�@���s�N�Z���V�F�[�_�ɃZ�b�g
			pID3D11DeviceContext->PSSetConstantBuffers(0, 1, &pNullConstantBuffer);
			//�`��
			pID3D11DeviceContext->DrawIndexed(PtrMeshResource->GetNumIndicis(), 0, 0);
			//��n��
			Dev->InitializeStates();

		}

	}



	//--------------------------------------------------------------------------------------
	//ParticleDraw�����̂��߂̍\����
	//--------------------------------------------------------------------------------------
	struct DrawParticleSprite {
		//�p�[�e�B�N���̃J�����܂ł̋���
		float m_ToCaneraLength;
		//���[���h�s��
		Matrix4X4 m_WorldMatrix;
		//�e�N�X�`��
		shared_ptr<TextureResource> m_TextureRes;
		DrawParticleSprite() :
			m_ToCaneraLength(0)
		{}
	};



	//--------------------------------------------------------------------------------------
	//	struct PCTParticleDraw::Impl;
	//	�p�r: Impl�C�f�B�I��
	//--------------------------------------------------------------------------------------
	struct PCTParticleDraw::Impl {
		//�`��R���e�L�X�g
		shared_ptr<MeshResource> m_MeshResource;	//���b�V�����\�[�X
		vector<DrawParticleSprite> m_DrawParticleSpriteVec;
		const size_t m_MaxInstance;				///<�C���X�^���X�ő�l
		ComPtr<ID3D11Buffer> m_MatrixBuffer;	///<�s��p�̒��_�o�b�t�@

		Impl(size_t MaxInstance) :
			m_MaxInstance(MaxInstance)
		{}
		~Impl() {}
		//���_�o�b�t�@�̍쐬
		void CreateParticleBuffers();
	};


	void PCTParticleDraw::Impl::CreateParticleBuffers() {
		try {
			float HelfSize = 0.5f;
			Vector4 col(1.0f, 1.0f, 1.0f, 1.0f);
			//���_�z��
			vector<VertexPositionColorTexture> vertices = {
				{ VertexPositionColorTexture(Vector3(-HelfSize, HelfSize, 0),  col,Vector2(0.0f, 0.0f)) },
				{ VertexPositionColorTexture(Vector3(HelfSize, HelfSize, 0), col, Vector2(1.0f, 0.0f)) },
				{ VertexPositionColorTexture(Vector3(-HelfSize, -HelfSize, 0),  col,Vector2(0.0f, 1.0f)) },
				{ VertexPositionColorTexture(Vector3(HelfSize, -HelfSize, 0),  col, Vector2(1.0f, 1.0f)) },
			};
			//�C���f�b�N�X�z��
			vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
			//���b�V���̍쐬
			m_MeshResource = MeshResource::CreateMeshResource(vertices, indices, false);

			//�C���X�^���X�s��o�b�t�@�̍쐬
			//Max�l�ō쐬����
			vector<Matrix4X4> matrices(m_MaxInstance, Matrix4X4());
			MeshResource::CreateDynamicVertexBuffer(m_MatrixBuffer, matrices);

		}
		catch (...) {
			throw;
		}
	}




	//--------------------------------------------------------------------------------------
	///	PCTParticle�`��R���|�[�l���g(�p�[�e�B�N���`��)
	//--------------------------------------------------------------------------------------
	PCTParticleDraw::PCTParticleDraw(const shared_ptr<GameObject>& GameObjectPtr, size_t MaxInstance) :
		DrawComponent(GameObjectPtr),
		pImpl(new Impl(MaxInstance))
	{}

	PCTParticleDraw::~PCTParticleDraw() {}

	void PCTParticleDraw::AddParticle(float ToCaneraLength, const Matrix4X4& WorldMatrix, const shared_ptr<TextureResource>& TextureRes) {
		DrawParticleSprite Item;
		Item.m_ToCaneraLength = ToCaneraLength;
		Item.m_WorldMatrix = WorldMatrix;
		Item.m_TextureRes = TextureRes;
		pImpl->m_DrawParticleSpriteVec.push_back(Item);
	}

	void PCTParticleDraw::OnCreate() {
		pImpl->CreateParticleBuffers();
	}

	struct InstanceDrawStr {
		size_t Start;
		size_t Count;
		shared_ptr<TextureResource> Tex;
		InstanceDrawStr(size_t s, size_t c, shared_ptr<TextureResource> t) :
			Start(s), Count(c), Tex(t) {}
	};

	void PCTParticleDraw::OnDraw() {
		auto PtrStage = GetGameObject()->GetStage();
		if (!PtrStage) {
			return;
		}
		if (pImpl->m_DrawParticleSpriteVec.size() <= 0) {
			return;
		}

		//�J�����ʒu�Ń\�[�g
		auto func = [](DrawParticleSprite& Left, DrawParticleSprite& Right)->bool {
			return (Left.m_ToCaneraLength > Right.m_ToCaneraLength);
		};
		std::sort(pImpl->m_DrawParticleSpriteVec.begin(), pImpl->m_DrawParticleSpriteVec.end(), func);
		//�f�o�C�X�ƃR���e�L�X�g�C���^�[�t�F�C�X�̎擾
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
		auto RenderState = Dev->GetRenderState();
		//�擪�̃e�N�X�`���𓾂�
		auto  NowTexPtr = pImpl->m_DrawParticleSpriteVec[0].m_TextureRes;

		vector<InstanceDrawStr> m_InstancVec;
		size_t NowStartIndex = 0;
		size_t NowDrawCount = 0;

		shared_ptr<TextureResource> NowTexRes = pImpl->m_DrawParticleSpriteVec[0].m_TextureRes;
		for (size_t i = 0; i < pImpl->m_DrawParticleSpriteVec.size(); i++) {
			if (pImpl->m_DrawParticleSpriteVec[i].m_TextureRes != NowTexRes) {
				m_InstancVec.push_back(InstanceDrawStr(NowStartIndex, NowDrawCount, NowTexRes));
				NowStartIndex = i;
				NowDrawCount = 0;
				NowTexRes = pImpl->m_DrawParticleSpriteVec[i].m_TextureRes;
			}
			else {
				NowDrawCount++;
			}
		}
		m_InstancVec.push_back(InstanceDrawStr(NowStartIndex, NowDrawCount, NowTexRes));


		//�C���X�^���X�o�b�t�@�Ƀ}�b�v
		D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
		D3D11_MAPPED_SUBRESOURCE mappedBuffer;
		//�s��̃}�b�v
		if (FAILED(pD3D11DeviceContext->Map(pImpl->m_MatrixBuffer.Get(), 0, mapType, 0, &mappedBuffer))) {
			// Map���s
			throw BaseException(
				L"�s���Map�Ɏ��s���܂����B",
				L"if(FAILED(pD3D11DeviceContext->Map()))",
				L"PCTParticleDraw::OnDraw()"
			);
		}
		//�s��̕ύX
		auto* matrices = (Matrix4X4*)mappedBuffer.pData;
		Matrix4X4 World;
		for (size_t i = 0; i < pImpl->m_DrawParticleSpriteVec.size(); i++) {
			World = pImpl->m_DrawParticleSpriteVec[i].m_WorldMatrix;
			//�]�u����
			World.Transpose();
			matrices[i] = World;
		}
		//�A���}�b�v
		pD3D11DeviceContext->Unmap(pImpl->m_MatrixBuffer.Get(), 0);
		//�X�g���C�h�ƃI�t�Z�b�g
		//�`��̒��_�o�b�t�@�ƍs��o�b�t�@��ݒ�
		UINT stride[2] = { sizeof(VertexPositionColorTexture), sizeof(Matrix4X4) };
		UINT offset[2] = { 0, 0 };

		ID3D11Buffer* pBuf[2] = { pImpl->m_MeshResource->GetVertexBuffer().Get(), pImpl->m_MatrixBuffer.Get() };
		pD3D11DeviceContext->IASetVertexBuffers(0, 2, pBuf, stride, offset);
		//�C���f�b�N�X�o�b�t�@�̃Z�b�g
		pD3D11DeviceContext->IASetIndexBuffer(pImpl->m_MeshResource->GetIndexBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);

		//�`����@�i3�p�`�j
		pD3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//�V�F�[�_�̐ݒ�
		pD3D11DeviceContext->VSSetShader(VSPCTInstance::GetPtr()->GetShader(), nullptr, 0);
		pD3D11DeviceContext->PSSetShader(PSPCTStatic::GetPtr()->GetShader(), nullptr, 0);
		//�C���v�b�g���C�A�E�g�̐ݒ�
		pD3D11DeviceContext->IASetInputLayout(VSPCTInstance::GetPtr()->GetInputLayout());

		//�u�����h�X�e�[�g
		//��������
		pD3D11DeviceContext->OMSetBlendState(RenderState->GetAlphaBlendEx(), nullptr, 0xffffffff);
		//�f�v�X�X�e���V���X�e�[�g
		pD3D11DeviceContext->OMSetDepthStencilState(RenderState->GetDepthDefault(), 0);
		//�e�N�X�`���ƃT���v���[�̐ݒ�
		ID3D11ShaderResourceView* pNull[1] = { 0 };
		ID3D11SamplerState* pSampler = RenderState->GetLinearClamp();
		pD3D11DeviceContext->PSSetSamplers(0, 1, &pSampler);
		//���X�^���C�U�X�e�[�g�i�\�ʕ`��j
		pD3D11DeviceContext->RSSetState(RenderState->GetCullBack());

		//�r���[�s��̌���
		Matrix4X4 View, Proj;
		//�r���[�s��̌���
		auto StageView = PtrStage->GetView();
		View = StageView->GetTargetCamera()->GetViewMatrix();
		//�]�u����
		View.Transpose();
		//�ˉe�s��̌���
		Proj = StageView->GetTargetCamera()->GetProjMatrix();
		//�]�u����
		Proj.Transpose();


		//�R���X�^���g�o�b�t�@�̏���
		StaticConstantBuffer sb;
		sb.World = Matrix4X4();	//���[���h�s��̓_�~�[
		sb.View = View;
		sb.Projection = Proj;
		//�G�~�b�V�u���Z�͍s��Ȃ��B
		sb.Emissive = Color4(0, 0, 0, 0);
		sb.Diffuse = Color4(1, 1, 1, 1);
		//�R���X�^���g�o�b�t�@�̍X�V
		pD3D11DeviceContext->UpdateSubresource(CBStatic::GetPtr()->GetBuffer(), 0, nullptr, &sb, 0, 0);

		//�R���X�^���g�o�b�t�@�̐ݒ�
		ID3D11Buffer* pConstantBuffer = CBStatic::GetPtr()->GetBuffer();
		ID3D11Buffer* pNullConstantBuffer = nullptr;
		//���_�V�F�[�_�ɓn��
		pD3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
		//�s�N�Z���V�F�[�_�ɓn��
		pD3D11DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);

		for (auto& v : m_InstancVec) {
			pD3D11DeviceContext->PSSetShaderResources(0, 1, v.Tex->GetShaderResourceView().GetAddressOf());
			//�`��
			pD3D11DeviceContext->DrawIndexedInstanced(pImpl->m_MeshResource->GetNumIndicis(), v.Count, 0, 0, v.Start);
		}
		//��n��
		Dev->InitializeStates();
		pImpl->m_DrawParticleSpriteVec.clear();
	}

	//--------------------------------------------------------------------------------------
	//	struct TextureDrawInterface::Impl;
	//--------------------------------------------------------------------------------------
	struct TextureDrawInterface::Impl {
		//�e�N�X�`��
		weak_ptr<TextureResource> m_TextureResource;
		//���b�v�T���v���[���ǂ���
		bool m_WrapSampler;
		Impl() :
			m_WrapSampler(false)
		{}
	};

	//--------------------------------------------------------------------------------------
	///	�e�N�X�`���`��C���^�[�t�F�C�X
	//--------------------------------------------------------------------------------------
	TextureDrawInterface::TextureDrawInterface():
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
		//�e�N�X�`�����Ȃ����null��Ԃ�
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
	//	�p�r: SpriteBaseDraw�C�f�B�I��
	//--------------------------------------------------------------------------------------
	struct SpriteBaseDraw::Impl {
		//���b�V��
		shared_ptr<MeshResource> m_SpriteMesh;
		//�G�~�b�V�u�F
		Color4 m_Emissive;
		//�f�t���[�Y�F
		Color4 m_Diffuse;
		Impl():
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
	//	struct PCSpriteDraw::Impl;
	//--------------------------------------------------------------------------------------
	struct PCSpriteDraw::Impl {
		Impl()
		{}
	};



	//--------------------------------------------------------------------------------------
	///	PCSprite�`��R���|�[�l���g
	//--------------------------------------------------------------------------------------
	PCSpriteDraw::PCSpriteDraw(const shared_ptr<GameObject>& GameObjectPtr):
		SpriteBaseDraw(GameObjectPtr),
		pImpl(new Impl())
	{
		//�p�C�v���C���X�e�[�g���f�t�H���g��2D
		SetBlendState(BlendState::Opaque);
		SetDepthStencilState(DepthStencilState::None);
		SetRasterizerState(RasterizerState::CullBack);
		SetSamplerState(SamplerState::LinearClamp);
	}
	PCSpriteDraw::PCSpriteDraw(const shared_ptr<GameObject>& GameObjectPtr,
		vector<VertexPositionColor>& Vertices, vector<uint16_t>& indices):
		SpriteBaseDraw(GameObjectPtr),
		pImpl(new Impl())
	{
		try {
			//�p�C�v���C���X�e�[�g���f�t�H���g��2D
			SetBlendState(BlendState::Opaque);
			SetDepthStencilState(DepthStencilState::None);
			SetRasterizerState(RasterizerState::CullBack);
			SetSamplerState(SamplerState::LinearClamp);
			//���b�V���̍쐬�i�ύX�ł���j
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
			//���b�V���̍쐬�i�ύX�ł���j
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
				L"���b�V�����쐬����Ă��܂���",
				L"if (!GetMeshResource())",
				L"PCSpriteDraw::UpdateVertices()"
			);

		}
		if (Vertices.size() > SpriteMesh->GetNumVertices()) {
			throw BaseException(
				L"�X�V���钸�_���傫�����܂�",
				L"if (Vertices.size() > SpriteMesh->GetNumVertices())",
				L"PCSpriteDraw::UpdateVertices()"
			);
		}
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();

		//���_�̕ύX
		//D3D11_MAP_WRITE_DISCARD�͏d�v�B���̏����ɂ��AGPU�Ɏז�����Ȃ�
		D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
		D3D11_MAPPED_SUBRESOURCE mappedBuffer;
		//���_�̃}�b�v
		if (FAILED(pD3D11DeviceContext->Map(SpriteMesh->GetVertexBuffer().Get(), 0, mapType, 0, &mappedBuffer))) {
			// Map���s
			throw BaseException(
				L"���_��Map�Ɏ��s���܂����B",
				L"if(FAILED(pID3D11DeviceContext->Map()))",
				L"PCSpriteDraw::UpdateVertices()"
			);
		}
		//���_�̕ύX
		VertexPositionColor* vertices
			= (VertexPositionColor*)mappedBuffer.pData;
		for (size_t i = 0; i < SpriteMesh->GetNumVertices(); i++) {
			vertices[i] = Vertices[i];
		}
		//�A���}�b�v
		pD3D11DeviceContext->Unmap(SpriteMesh->GetVertexBuffer().Get(), 0);
	}
	void PCSpriteDraw::OnCreate() {
		auto SpriteMesh = GetMeshResource();
		if (!SpriteMesh) {
			//�쐬����ĂȂ�������쐬����
			float HelfSize = 0.5f;
			//���_�z��
			vector<VertexPositionColor> Vertices = {
				{ VertexPositionColor(Vector3(-HelfSize, HelfSize, 0), Color4(1.0f,1.0f,1.0f,1.0f)) },
				{ VertexPositionColor(Vector3(HelfSize, HelfSize, 0), Color4(1.0f,1.0f,1.0f,1.0f)) },
				{ VertexPositionColor(Vector3(-HelfSize, -HelfSize, 0), Color4(1.0f,1.0f,1.0f,1.0f)) },
				{ VertexPositionColor(Vector3(HelfSize, -HelfSize, 0), Color4(1.0f,1.0f,1.0f,1.0f)) },
			};
			//�C���f�b�N�X�z��
			vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
			//���b�V���̍쐬�i�ύX�ł���j
			SpriteMesh = MeshResource::CreateMeshResource(Vertices, indices, true);
			SetMeshResource(SpriteMesh);
		}

	}
	void PCSpriteDraw::OnDraw() {
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
		auto RenderState = Dev->GetRenderState();
		//���b�V�����Ȃ���Ε`�悵�Ȃ�
		auto SpriteMesh = GetMeshResource();
		if (!SpriteMesh) {
			throw BaseException(
				L"���b�V�����쐬����Ă��܂���",
				L"if (!SpriteMesh)",
				L"PCSpriteDraw::OnDraw()"
			);
		}

		//�s��̒�`
		auto PtrTrans = GetGameObject()->GetComponent<Transform>();
		Vector2 Scale, Pos, Pivot;
		Scale.x = PtrTrans->GetScale().x;
		Scale.y = PtrTrans->GetScale().y;
		Pos.x = PtrTrans->GetPosition().x;
		Pos.y = PtrTrans->GetPosition().y;
		Pivot.x = PtrTrans->GetPivot().x;
		Pivot.y = PtrTrans->GetPivot().y;
		Vector3 Rot = PtrTrans->GetRotation();

		//�s��̒�`
		Matrix4X4 World, Proj;
		//���[���h�s��̌���
		World.AffineTransformation2D(
			Scale,			//�X�P�[�����O
			Pivot,		//��]�̒��S�i�d�S�j
			Rot.z,			//��]�p�x(Z����])
			Pos				//�ʒu
		);
		//�ˉe�s��̌���
		GetGameObject()->OnGet2DDrawProjMatrix(Proj);
		//�s��̍���
		World *= Proj;
		//�R���X�^���g�o�b�t�@�̏���
		SpriteConstantBuffer sb;
		//�G�~�b�V�u
		sb.Emissive = GetEmissive();
		//�f�t�B�[�Y�͂��ׂĒʂ�
		sb.Diffuse = GetDiffuse();
		//�s��̐ݒ�
		sb.World = World;
		//�R���X�^���g�o�b�t�@�̍X�V
		pD3D11DeviceContext->UpdateSubresource(CBSprite::GetPtr()->GetBuffer(), 0, nullptr, &sb, 0, 0);
		//�X�g���C�h�ƃI�t�Z�b�g
		UINT stride = sizeof(VertexPositionColor);
		UINT offset = 0;
		//���_�o�b�t�@�̃Z�b�g
		pD3D11DeviceContext->IASetVertexBuffers(0, 1, SpriteMesh->GetVertexBuffer().GetAddressOf(), &stride, &offset);
		//�C���f�b�N�X�o�b�t�@�̃Z�b�g
		pD3D11DeviceContext->IASetIndexBuffer(SpriteMesh->GetIndexBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);

		//�`����@�i3�p�`�j
		pD3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//�R���X�^���g�o�b�t�@�̐ݒ�
		ID3D11Buffer* pConstantBuffer = CBSprite::GetPtr()->GetBuffer();
		ID3D11Buffer* pNullConstantBuffer = nullptr;
		//���_�V�F�[�_�ɓn��
		pD3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
		//�s�N�Z���V�F�[�_�ɓn��
		pD3D11DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);
		//�V�F�[�_�̐ݒ�
		pD3D11DeviceContext->VSSetShader(VSPCSprite::GetPtr()->GetShader(), nullptr, 0);
		pD3D11DeviceContext->PSSetShader(PSPCSprite::GetPtr()->GetShader(), nullptr, 0);
		//�C���v�b�g���C�A�E�g�̐ݒ�
		pD3D11DeviceContext->IASetInputLayout(VSPCSprite::GetPtr()->GetInputLayout());

		//�u�����h�X�e�[�g
		if (GetGameObject()->GetAlphaActive()) {
			//��������
			pD3D11DeviceContext->OMSetBlendState(RenderState->GetAlphaBlendEx(), nullptr, 0xffffffff);
		}
		else {
			//�����������Ȃ�
			pD3D11DeviceContext->OMSetBlendState(RenderState->GetOpaque(), nullptr, 0xffffffff);
		}
		//�f�v�X�X�e���V���X�e�[�g
		pD3D11DeviceContext->OMSetDepthStencilState(RenderState->GetDepthNone(), 0);
		//���X�^���C�U�X�e�[�g
		pD3D11DeviceContext->RSSetState(RenderState->GetCullBack());

		//�`��
		pD3D11DeviceContext->DrawIndexed(SpriteMesh->GetNumIndicis(), 0, 0);
		//��n��
		Dev->InitializeStates();
	}



	//--------------------------------------------------------------------------------------
	//	struct PTSpriteDraw::Impl;
	//--------------------------------------------------------------------------------------
	struct PTSpriteDraw::Impl {
		Impl()
		{}
	};

	//--------------------------------------------------------------------------------------
	///	PTSprite�`��R���|�[�l���g
	//--------------------------------------------------------------------------------------
	PTSpriteDraw::PTSpriteDraw(const shared_ptr<GameObject>& GameObjectPtr):
		SpriteBaseDraw(GameObjectPtr),
		pImpl(new Impl())
	{
		//�p�C�v���C���X�e�[�g���f�t�H���g��2D
		SetBlendState(BlendState::Opaque);
		SetDepthStencilState(DepthStencilState::None);
		SetRasterizerState(RasterizerState::CullBack);
		SetSamplerState(SamplerState::LinearClamp);
	}

	PTSpriteDraw::PTSpriteDraw(const shared_ptr<GameObject>& GameObjectPtr,
		vector<VertexPositionTexture>& Vertices, vector<uint16_t>& indices):
		SpriteBaseDraw(GameObjectPtr),
		pImpl(new Impl())
	{
		try {
			//�p�C�v���C���X�e�[�g���f�t�H���g��2D
			SetBlendState(BlendState::Opaque);
			SetDepthStencilState(DepthStencilState::None);
			SetRasterizerState(RasterizerState::CullBack);
			SetSamplerState(SamplerState::LinearClamp);
			//���b�V���̍쐬�i�ύX�ł���j
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
			//���b�V���̍쐬�i�ύX�ł���j
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
				L"���b�V�����쐬����Ă��܂���",
				L"if (!GetMeshResource())",
				L"PTSpriteDraw::UpdateVertices()"
			);

		}
		if (Vertices.size() > SpriteMesh->GetNumVertices()) {
			throw BaseException(
				L"�X�V���钸�_���傫�����܂�",
				L"if (Vertices.size() > SpriteMesh->GetNumVertices())",
				L"PTSpriteDraw::UpdateVertices()"
			);
		}
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();

		//���_�̕ύX
		//D3D11_MAP_WRITE_DISCARD�͏d�v�B���̏����ɂ��AGPU�Ɏז�����Ȃ�
		D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
		D3D11_MAPPED_SUBRESOURCE mappedBuffer;
		//���_�̃}�b�v
		if (FAILED(pD3D11DeviceContext->Map(SpriteMesh->GetVertexBuffer().Get(), 0, mapType, 0, &mappedBuffer))) {
			// Map���s
			throw BaseException(
				L"���_��Map�Ɏ��s���܂����B",
				L"if(FAILED(pID3D11DeviceContext->Map()))",
				L"PTSpriteDraw::UpdateVertices()"
			);
		}
		//���_�̕ύX
		VertexPositionTexture* vertices
			= (VertexPositionTexture*)mappedBuffer.pData;
		for (size_t i = 0; i < SpriteMesh->GetNumVertices(); i++) {
			vertices[i] = Vertices[i];
		}
		//�A���}�b�v
		pD3D11DeviceContext->Unmap(SpriteMesh->GetVertexBuffer().Get(), 0);
	}

	void PTSpriteDraw::OnCreate() {
		auto SpriteMesh = GetMeshResource();
		if (!SpriteMesh) {
			//�쐬����ĂȂ�������쐬����
			float HelfSize = 0.5f;
			//���_�z��
			vector<VertexPositionTexture> Vertices = {
				{ VertexPositionTexture(Vector3(-HelfSize, HelfSize, 0), Vector2(0.0f, 0.0f)) },
				{ VertexPositionTexture(Vector3(HelfSize, HelfSize, 0), Vector2(1.0f, 0.0f)) },
				{ VertexPositionTexture(Vector3(-HelfSize, -HelfSize, 0), Vector2(0.0f, 1.0f)) },
				{ VertexPositionTexture(Vector3(HelfSize, -HelfSize, 0), Vector2(1.0f, 1.0f)) },
			};
			//�C���f�b�N�X�z��
			vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
			//���b�V���̍쐬�i�ύX�ł���j
			SpriteMesh = MeshResource::CreateMeshResource(Vertices, indices, true);
			SetMeshResource(SpriteMesh);
		}
	}

	void PTSpriteDraw::OnDraw() {
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
		auto RenderState = Dev->GetRenderState();
		//���b�V�����Ȃ���Ε`�悵�Ȃ�
		auto SpriteMesh = GetMeshResource();
		if (!SpriteMesh) {
			throw BaseException(
				L"���b�V�����쐬����Ă��܂���",
				L"if (!SpriteMesh)",
				L"PTSpriteDraw::OnDraw()"
			);
		}
		//�e�N�X�`�����Ȃ���Ε`�悵�Ȃ�
		auto shTex = GetTextureResource();
		if (!shTex) {
			return;
		}

		//�s��̒�`
		auto PtrTrans = GetGameObject()->GetComponent<Transform>();
		Vector2 Scale,Pos,Pivot;
		Scale.x = PtrTrans->GetScale().x;
		Scale.y = PtrTrans->GetScale().y;
		Pos.x = PtrTrans->GetPosition().x;
		Pos.y = PtrTrans->GetPosition().y;
		Pivot.x = PtrTrans->GetPivot().x;
		Pivot.y = PtrTrans->GetPivot().y;
		Vector3 Rot = PtrTrans->GetRotation();

		//�s��̒�`
		Matrix4X4 World, Proj;
		//���[���h�s��̌���
		World.AffineTransformation2D(
			Scale,			//�X�P�[�����O
			Pivot,		//��]�̒��S�i�d�S�j
			Rot.z,			//��]�p�x(Z����])
			Pos				//�ʒu
		);

		//�ˉe�s��̌���
		GetGameObject()->OnGet2DDrawProjMatrix(Proj);
		//�s��̍���
		World *= Proj;
		//�R���X�^���g�o�b�t�@�̏���
		SpriteConstantBuffer sb;
		//�G�~�b�V�u
		sb.Emissive = GetEmissive();
		//�f�t�B�[�Y�͂��ׂĒʂ�
		sb.Diffuse = GetDiffuse();
		//�s��̐ݒ�
		sb.World = World;
		//�R���X�^���g�o�b�t�@�̍X�V
		pD3D11DeviceContext->UpdateSubresource(CBSprite::GetPtr()->GetBuffer(), 0, nullptr, &sb, 0, 0);
		//�X�g���C�h�ƃI�t�Z�b�g
		UINT stride = sizeof(VertexPositionTexture);
		UINT offset = 0;
		//���_�o�b�t�@�̃Z�b�g
		pD3D11DeviceContext->IASetVertexBuffers(0, 1, SpriteMesh->GetVertexBuffer().GetAddressOf(), &stride, &offset);
		//�C���f�b�N�X�o�b�t�@�̃Z�b�g
		pD3D11DeviceContext->IASetIndexBuffer(SpriteMesh->GetIndexBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);

		//�`����@�i3�p�`�j
		pD3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//�R���X�^���g�o�b�t�@�̐ݒ�
		ID3D11Buffer* pConstantBuffer = CBSprite::GetPtr()->GetBuffer();
		ID3D11Buffer* pNullConstantBuffer = nullptr;
		//���_�V�F�[�_�ɓn��
		pD3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
		//�s�N�Z���V�F�[�_�ɓn��
		pD3D11DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);
		//�V�F�[�_�̐ݒ�
		pD3D11DeviceContext->VSSetShader(VSPTSprite::GetPtr()->GetShader(), nullptr, 0);
		pD3D11DeviceContext->PSSetShader(PSPTSprite::GetPtr()->GetShader(), nullptr, 0);
		//�C���v�b�g���C�A�E�g�̐ݒ�
		pD3D11DeviceContext->IASetInputLayout(VSPTSprite::GetPtr()->GetInputLayout());

		//�u�����h�X�e�[�g
		if (GetGameObject()->GetAlphaActive()) {
			//��������
			pD3D11DeviceContext->OMSetBlendState(RenderState->GetAlphaBlendEx(), nullptr, 0xffffffff);
		}
		else {
			//�����������Ȃ�
			pD3D11DeviceContext->OMSetBlendState(RenderState->GetOpaque(), nullptr, 0xffffffff);
		}
		//�f�v�X�X�e���V���X�e�[�g
		pD3D11DeviceContext->OMSetDepthStencilState(RenderState->GetDepthNone(), 0);
		//���X�^���C�U�X�e�[�g
		pD3D11DeviceContext->RSSetState(RenderState->GetCullBack());
		//�e�N�X�`���ƃT���v���[�̐ݒ�
		ID3D11ShaderResourceView* pNull[1] = { 0 };
		pD3D11DeviceContext->PSSetShaderResources(0, 1, shTex->GetShaderResourceView().GetAddressOf());
		//���b�s���O�T���v���[
		ID3D11SamplerState* pSampler = RenderState->GetLinearClamp();
		if (GetWrapSampler()) {
			pSampler = RenderState->GetLinearWrap();
		}
		pD3D11DeviceContext->PSSetSamplers(0, 1, &pSampler);
		//�`��
		pD3D11DeviceContext->DrawIndexed(SpriteMesh->GetNumIndicis(), 0, 0);
		//��n��
		Dev->InitializeStates();
	}

	//--------------------------------------------------------------------------------------
	//	struct PCTSpriteDraw::Impl;
	//--------------------------------------------------------------------------------------
	struct PCTSpriteDraw::Impl {
		Impl()
		{}
	};


	//--------------------------------------------------------------------------------------
	///	PCTSprite�`��R���|�[�l���g
	//--------------------------------------------------------------------------------------
	PCTSpriteDraw::PCTSpriteDraw(const shared_ptr<GameObject>& GameObjectPtr):
		SpriteBaseDraw(GameObjectPtr),
		pImpl(new Impl())
	{
		//�p�C�v���C���X�e�[�g���f�t�H���g��2D
		SetBlendState(BlendState::Opaque);
		SetDepthStencilState(DepthStencilState::None);
		SetRasterizerState(RasterizerState::CullBack);
		SetSamplerState(SamplerState::LinearClamp);
	}
	PCTSpriteDraw::PCTSpriteDraw(const shared_ptr<GameObject>& GameObjectPtr,
		vector<VertexPositionColorTexture>& Vertices, vector<uint16_t>& indices):
		SpriteBaseDraw(GameObjectPtr),
		pImpl(new Impl())
	{
		try {
			//�p�C�v���C���X�e�[�g���f�t�H���g��2D
			SetBlendState(BlendState::Opaque);
			SetDepthStencilState(DepthStencilState::None);
			SetRasterizerState(RasterizerState::CullBack);
			SetSamplerState(SamplerState::LinearClamp);
			//���b�V���̍쐬�i�ύX�ł���j
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
			//���b�V���̍쐬�i�ύX�ł���j
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
				L"���b�V�����쐬����Ă��܂���",
				L"if (!SpriteMesh)",
				L"PCTSpriteDraw::UpdateVertices()"
			);

		}
		if (Vertices.size() > SpriteMesh->GetNumVertices()) {
			throw BaseException(
				L"�X�V���钸�_���傫�����܂�",
				L"if (Vertices.size() > SpriteMesh->GetNumVertices())",
				L"PCTSpriteDraw::UpdateVertices()"
			);
		}
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();

		//���_�̕ύX
		//D3D11_MAP_WRITE_DISCARD�͏d�v�B���̏����ɂ��AGPU�Ɏז�����Ȃ�
		D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
		D3D11_MAPPED_SUBRESOURCE mappedBuffer;
		//���_�̃}�b�v
		if (FAILED(pD3D11DeviceContext->Map(SpriteMesh->GetVertexBuffer().Get(), 0, mapType, 0, &mappedBuffer))) {
			// Map���s
			throw BaseException(
				L"���_��Map�Ɏ��s���܂����B",
				L"if(FAILED(pID3D11DeviceContext->Map()))",
				L"PCTSpriteDraw::UpdateVertices()"
			);
		}
		//���_�̕ύX
		VertexPositionColorTexture* vertices
			= (VertexPositionColorTexture*)mappedBuffer.pData;
		for (size_t i = 0; i < SpriteMesh->GetNumVertices(); i++) {
			vertices[i] = Vertices[i];
		}
		//�A���}�b�v
		pD3D11DeviceContext->Unmap(SpriteMesh->GetVertexBuffer().Get(), 0);


	}
	void PCTSpriteDraw::OnCreate() {
		auto SpriteMesh = GetMeshResource();
		if (!SpriteMesh) {
			//�쐬����ĂȂ�������쐬����
			float HelfSize = 0.5f;
			//���_�z��
			vector<VertexPositionColorTexture> vertices = {
				{ VertexPositionColorTexture(Vector3(-HelfSize, HelfSize, 0),Color4(1.0f,1.0f,1.0f,1.0f), Vector2(0.0f, 0.0f)) },
				{ VertexPositionColorTexture(Vector3(HelfSize, HelfSize, 0), Color4(1.0f,1.0f,1.0f,1.0f), Vector2(1.0f, 0.0f)) },
				{ VertexPositionColorTexture(Vector3(-HelfSize, -HelfSize, 0), Color4(1.0f,1.0f,1.0f,1.0f), Vector2(0.0f, 1.0f)) },
				{ VertexPositionColorTexture(Vector3(HelfSize, -HelfSize, 0), Color4(1.0f,1.0f,1.0f,1.0f), Vector2(1.0f, 1.0f)) },
			};
			//�C���f�b�N�X�z��
			vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
			//���b�V���̍쐬�i�ύX�ł���j
			SpriteMesh = MeshResource::CreateMeshResource(vertices, indices, true);
			SetMeshResource(SpriteMesh);
		}
	}

	void PCTSpriteDraw::OnDraw() {
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
		auto RenderState = Dev->GetRenderState();
		//���b�V�����Ȃ���Ε`�悵�Ȃ�
		auto SpriteMesh = GetMeshResource();
		if (!SpriteMesh) {
			throw BaseException(
				L"���b�V�����쐬����Ă��܂���",
				L"if (!SpriteMesh)",
				L"PCTSpriteDraw::OnDraw()"
			);
		}
		//�e�N�X�`�����Ȃ���Ε`�悵�Ȃ�
		auto shTex = GetTextureResource();
		if (!shTex) {
			return;
		}

		//�s��̒�`
		auto PtrTrans = GetGameObject()->GetComponent<Transform>();
		Vector2 Scale, Pos, Pivot;
		Scale.x = PtrTrans->GetScale().x;
		Scale.y = PtrTrans->GetScale().y;
		Pos.x = PtrTrans->GetPosition().x;
		Pos.y = PtrTrans->GetPosition().y;
		Pivot.x = PtrTrans->GetPivot().x;
		Pivot.y = PtrTrans->GetPivot().y;
		Vector3 Rot = PtrTrans->GetRotation();

		//�s��̒�`
		Matrix4X4 World, Proj;
		//���[���h�s��̌���
		World.AffineTransformation2D(
			Scale,			//�X�P�[�����O
			Pivot,		//��]�̒��S�i�d�S�j
			Rot.z,			//��]�p�x(Z����])
			Pos				//�ʒu
		);

		//�ˉe�s��̌���
		GetGameObject()->OnGet2DDrawProjMatrix(Proj);
		//�s��̍���
		World *= Proj;
		//�R���X�^���g�o�b�t�@�̏���
		SpriteConstantBuffer sb;
		//�G�~�b�V�u
		sb.Emissive = GetEmissive();
		//�f�t�B�[�Y�͂��ׂĒʂ�
		sb.Diffuse = GetDiffuse();
		//�s��̐ݒ�
		sb.World = World;
		//�R���X�^���g�o�b�t�@�̍X�V
		pD3D11DeviceContext->UpdateSubresource(CBSprite::GetPtr()->GetBuffer(), 0, nullptr, &sb, 0, 0);
		//�X�g���C�h�ƃI�t�Z�b�g
		UINT stride = sizeof(VertexPositionColorTexture);
		UINT offset = 0;
		//���_�o�b�t�@�̃Z�b�g
		pD3D11DeviceContext->IASetVertexBuffers(0, 1, SpriteMesh->GetVertexBuffer().GetAddressOf(), &stride, &offset);
		//�C���f�b�N�X�o�b�t�@�̃Z�b�g
		pD3D11DeviceContext->IASetIndexBuffer(SpriteMesh->GetIndexBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);

		//�`����@�i3�p�`�j
		pD3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//�R���X�^���g�o�b�t�@�̐ݒ�
		ID3D11Buffer* pConstantBuffer = CBSprite::GetPtr()->GetBuffer();
		ID3D11Buffer* pNullConstantBuffer = nullptr;
		//���_�V�F�[�_�ɓn��
		pD3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
		//�s�N�Z���V�F�[�_�ɓn��
		pD3D11DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);
		//�V�F�[�_�̐ݒ�
		pD3D11DeviceContext->VSSetShader(VSPCTSprite::GetPtr()->GetShader(), nullptr, 0);
		pD3D11DeviceContext->PSSetShader(PSPCTSprite::GetPtr()->GetShader(), nullptr, 0);
		//�C���v�b�g���C�A�E�g�̐ݒ�
		pD3D11DeviceContext->IASetInputLayout(VSPCTSprite::GetPtr()->GetInputLayout());

		//�u�����h�X�e�[�g
		if (GetGameObject()->GetAlphaActive()) {
			//��������
			pD3D11DeviceContext->OMSetBlendState(RenderState->GetAlphaBlendEx(), nullptr, 0xffffffff);
		}
		else {
			//�����������Ȃ�
			pD3D11DeviceContext->OMSetBlendState(RenderState->GetOpaque(), nullptr, 0xffffffff);
		}
		//�f�v�X�X�e���V���X�e�[�g
		pD3D11DeviceContext->OMSetDepthStencilState(RenderState->GetDepthNone(), 0);
		//���X�^���C�U�X�e�[�g
		pD3D11DeviceContext->RSSetState(RenderState->GetCullBack());
		//�e�N�X�`���ƃT���v���[�̐ݒ�
		ID3D11ShaderResourceView* pNull[1] = { 0 };
		pD3D11DeviceContext->PSSetShaderResources(0, 1, shTex->GetShaderResourceView().GetAddressOf());
		//���b�s���O�T���v���[
		ID3D11SamplerState* pSampler = RenderState->GetLinearClamp();
		if (GetWrapSampler()) {
			pSampler = RenderState->GetLinearWrap();
		}
		pD3D11DeviceContext->PSSetSamplers(0, 1, &pSampler);
		//�`��
		pD3D11DeviceContext->DrawIndexed(SpriteMesh->GetNumIndicis(), 0, 0);
		//��n��
		Dev->InitializeStates();
	}


	//--------------------------------------------------------------------------------------
	//	3D�p�V�F�[�_���ƕ`��\����
	//--------------------------------------------------------------------------------------
	struct Draw3DPrim {
		static void PCDraw(const shared_ptr<GameObject>& GameObjectPtr, const shared_ptr<MeshResource>& MeshRes,
			const Color4& Emissive, const Color4& Diffuse,const Matrix4X4& MeshToTransformMatrix) {
			auto Dev = App::GetApp()->GetDeviceResources();
			auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
			auto RenderState = Dev->GetRenderState();
			//�s��̒�`
			auto PtrTrans = GameObjectPtr->GetComponent<Transform>();
			//�s��̒�`
			Matrix4X4 World, ViewMat, ProjMat;
			//���[���h�s��̌���
			World = MeshToTransformMatrix * PtrTrans->GetWorldMatrix();
			//�]�u����
			World.Transpose();
			//�J�����𓾂�
			auto CameraPtr = GameObjectPtr->OnGetDrawCamera();
			//�r���[�Ǝˉe�s��𓾂�
			ViewMat = CameraPtr->GetViewMatrix();
			//�]�u����
			ViewMat.Transpose();
			//�]�u����
			ProjMat = CameraPtr->GetProjMatrix();
			ProjMat.Transpose();
			//�R���X�^���g�o�b�t�@�̏���
			StaticConstantBuffer sb;
			sb.World = World;
			sb.View = ViewMat;
			sb.Projection = ProjMat;
			//�G�~�b�V�u
			sb.Emissive = Emissive;
			//�f�t�B�[�Y�͂��ׂĒʂ�
			sb.Diffuse = Diffuse;
			//�R���X�^���g�o�b�t�@�̍X�V
			pD3D11DeviceContext->UpdateSubresource(CBStatic::GetPtr()->GetBuffer(), 0, nullptr, &sb, 0, 0);

			//�X�g���C�h�ƃI�t�Z�b�g
			UINT stride = sizeof(VertexPositionColor);
			UINT offset = 0;
			//���_�o�b�t�@�̃Z�b�g
			pD3D11DeviceContext->IASetVertexBuffers(0, 1, MeshRes->GetVertexBuffer().GetAddressOf(), &stride, &offset);
			//�C���f�b�N�X�o�b�t�@�̃Z�b�g
			pD3D11DeviceContext->IASetIndexBuffer(MeshRes->GetIndexBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);

			//�`����@�i3�p�`�j
			pD3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			//�R���X�^���g�o�b�t�@�̐ݒ�
			ID3D11Buffer* pConstantBuffer = CBStatic::GetPtr()->GetBuffer();
			ID3D11Buffer* pNullConstantBuffer = nullptr;
			//���_�V�F�[�_�ɓn��
			pD3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
			//�s�N�Z���V�F�[�_�ɓn��
			pD3D11DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);
			//�V�F�[�_�̐ݒ�
			pD3D11DeviceContext->VSSetShader(VSPCStatic::GetPtr()->GetShader(), nullptr, 0);
			pD3D11DeviceContext->PSSetShader(PSPCStatic::GetPtr()->GetShader(), nullptr, 0);
			//�C���v�b�g���C�A�E�g�̐ݒ�
			pD3D11DeviceContext->IASetInputLayout(VSPCStatic::GetPtr()->GetInputLayout());
			//�u�����h�X�e�[�g
			if (GameObjectPtr->GetAlphaActive()) {
				//��������
				pD3D11DeviceContext->OMSetBlendState(RenderState->GetAlphaBlendEx(), nullptr, 0xffffffff);
			}
			else {
				//�����������Ȃ�
				pD3D11DeviceContext->OMSetBlendState(RenderState->GetOpaque(), nullptr, 0xffffffff);
			}
			//�f�v�X�X�e���V���X�e�[�g
			pD3D11DeviceContext->OMSetDepthStencilState(RenderState->GetDepthDefault(), 0);

			//���������Ȃ�
			if (GameObjectPtr->GetAlphaActive()) {
				//���X�^���C�U�X�e�[�g(���`��)
				pD3D11DeviceContext->RSSetState(RenderState->GetCullFront());
				//�`��
				pD3D11DeviceContext->DrawIndexed(MeshRes->GetNumIndicis(), 0, 0);
				//���X�^���C�U�X�e�[�g�i�\�`��j
				pD3D11DeviceContext->RSSetState(RenderState->GetCullBack());
				//�`��
				pD3D11DeviceContext->DrawIndexed(MeshRes->GetNumIndicis(), 0, 0);
			}
			else {
				//���X�^���C�U�X�e�[�g
				pD3D11DeviceContext->RSSetState(RenderState->GetCullBack());
				//�`��
				pD3D11DeviceContext->DrawIndexed(MeshRes->GetNumIndicis(), 0, 0);
			}
			//��n��
			Dev->InitializeStates();
		}

		static void PTDraw(const shared_ptr<GameObject>& GameObjectPtr,
			const shared_ptr<MeshResource>& MeshRes,
			const shared_ptr<TextureResource>& TextureRes, bool WrapSampler,
			const Color4& Emissive, const Color4& Diffuse, const Matrix4X4& MeshToTransformMatrix) {
			auto Dev = App::GetApp()->GetDeviceResources();
			auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
			auto RenderState = Dev->GetRenderState();
			//�s��̒�`
			auto PtrTrans = GameObjectPtr->GetComponent<Transform>();
			//�s��̒�`
			Matrix4X4 World, ViewMat, ProjMat;
			//���[���h�s��̌���
			World = MeshToTransformMatrix * PtrTrans->GetWorldMatrix();
			//�]�u����
			World.Transpose();
			//�J�����𓾂�
			auto CameraPtr = GameObjectPtr->OnGetDrawCamera();
			//�r���[�Ǝˉe�s��𓾂�
			ViewMat = CameraPtr->GetViewMatrix();
			//�]�u����
			ViewMat.Transpose();
			//�]�u����
			ProjMat = CameraPtr->GetProjMatrix();
			ProjMat.Transpose();
			//�R���X�^���g�o�b�t�@�̏���
			StaticConstantBuffer sb;
			sb.World = World;
			sb.View = ViewMat;
			sb.Projection = ProjMat;
			//�G�~�b�V�u
			sb.Emissive = Emissive;
			//�f�t�B�[�Y�͂��ׂĒʂ�
			sb.Diffuse = Diffuse;
			//�R���X�^���g�o�b�t�@�̍X�V
			pD3D11DeviceContext->UpdateSubresource(CBStatic::GetPtr()->GetBuffer(), 0, nullptr, &sb, 0, 0);

			//�X�g���C�h�ƃI�t�Z�b�g
			UINT stride = sizeof(VertexPositionTexture);
			UINT offset = 0;
			//���_�o�b�t�@�̃Z�b�g
			pD3D11DeviceContext->IASetVertexBuffers(0, 1, MeshRes->GetVertexBuffer().GetAddressOf(), &stride, &offset);
			//�C���f�b�N�X�o�b�t�@�̃Z�b�g
			pD3D11DeviceContext->IASetIndexBuffer(MeshRes->GetIndexBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);

			//�`����@�i3�p�`�j
			pD3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			//�R���X�^���g�o�b�t�@�̐ݒ�
			ID3D11Buffer* pConstantBuffer = CBStatic::GetPtr()->GetBuffer();
			ID3D11Buffer* pNullConstantBuffer = nullptr;
			//���_�V�F�[�_�ɓn��
			pD3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
			//�s�N�Z���V�F�[�_�ɓn��
			pD3D11DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);
			//�V�F�[�_�̐ݒ�
			pD3D11DeviceContext->VSSetShader(VSPTStatic::GetPtr()->GetShader(), nullptr, 0);
			pD3D11DeviceContext->PSSetShader(PSPTStatic::GetPtr()->GetShader(), nullptr, 0);
			//�C���v�b�g���C�A�E�g�̐ݒ�
			pD3D11DeviceContext->IASetInputLayout(VSPTStatic::GetPtr()->GetInputLayout());
			//�u�����h�X�e�[�g
			if (GameObjectPtr->GetAlphaActive()) {
				//��������
				pD3D11DeviceContext->OMSetBlendState(RenderState->GetAlphaBlendEx(), nullptr, 0xffffffff);
			}
			else {
				//�����������Ȃ�
				pD3D11DeviceContext->OMSetBlendState(RenderState->GetOpaque(), nullptr, 0xffffffff);
			}
			//�f�v�X�X�e���V���X�e�[�g
			pD3D11DeviceContext->OMSetDepthStencilState(RenderState->GetDepthDefault(), 0);

			//�e�N�X�`���ƃT���v���[�̐ݒ�
			ID3D11ShaderResourceView* pNull[1] = { 0 };
			pD3D11DeviceContext->PSSetShaderResources(0, 1, TextureRes->GetShaderResourceView().GetAddressOf());
			//���b�s���O�T���v���[
			ID3D11SamplerState* pSampler = RenderState->GetLinearClamp();
			if (WrapSampler) {
				pSampler = RenderState->GetLinearWrap();
			}
			pD3D11DeviceContext->PSSetSamplers(0, 1, &pSampler);

			//���������Ȃ�
			if (GameObjectPtr->GetAlphaActive()) {
				//���X�^���C�U�X�e�[�g(���`��)
				pD3D11DeviceContext->RSSetState(RenderState->GetCullFront());
				//�`��
				pD3D11DeviceContext->DrawIndexed(MeshRes->GetNumIndicis(), 0, 0);
				//���X�^���C�U�X�e�[�g�i�\�`��j
				pD3D11DeviceContext->RSSetState(RenderState->GetCullBack());
				//�`��
				pD3D11DeviceContext->DrawIndexed(MeshRes->GetNumIndicis(), 0, 0);
			}
			else {
				//���X�^���C�U�X�e�[�g
				pD3D11DeviceContext->RSSetState(RenderState->GetCullBack());
				//�`��
				pD3D11DeviceContext->DrawIndexed(MeshRes->GetNumIndicis(), 0, 0);
			}
			//��n��
			Dev->InitializeStates();
		}



		static void PCTDraw(const shared_ptr<GameObject>& GameObjectPtr,
			const shared_ptr<MeshResource>& MeshRes,
			const shared_ptr<TextureResource>& TextureRes, bool WrapSampler,
			const Color4& Emissive, const Color4& Diffuse, const Matrix4X4& MeshToTransformMatrix) {
			auto Dev = App::GetApp()->GetDeviceResources();
			auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
			auto RenderState = Dev->GetRenderState();
			//�s��̒�`
			auto PtrTrans = GameObjectPtr->GetComponent<Transform>();
			//�s��̒�`
			Matrix4X4 World, ViewMat, ProjMat;
			//���[���h�s��̌���
			World = MeshToTransformMatrix * PtrTrans->GetWorldMatrix();
			//�]�u����
			World.Transpose();
			//�J�����𓾂�
			auto CameraPtr = GameObjectPtr->OnGetDrawCamera();
			//�r���[�Ǝˉe�s��𓾂�
			ViewMat = CameraPtr->GetViewMatrix();
			//�]�u����
			ViewMat.Transpose();
			//�]�u����
			ProjMat = CameraPtr->GetProjMatrix();
			ProjMat.Transpose();
			//�R���X�^���g�o�b�t�@�̏���
			StaticConstantBuffer sb;
			sb.World = World;
			sb.View = ViewMat;
			sb.Projection = ProjMat;
			//�G�~�b�V�u
			sb.Emissive = Emissive;
			//�f�t�B�[�Y�͂��ׂĒʂ�
			sb.Diffuse = Diffuse;
			//�R���X�^���g�o�b�t�@�̍X�V
			pD3D11DeviceContext->UpdateSubresource(CBStatic::GetPtr()->GetBuffer(), 0, nullptr, &sb, 0, 0);

			//�X�g���C�h�ƃI�t�Z�b�g
			UINT stride = sizeof(VertexPositionColorTexture);
			UINT offset = 0;
			//���_�o�b�t�@�̃Z�b�g
			pD3D11DeviceContext->IASetVertexBuffers(0, 1, MeshRes->GetVertexBuffer().GetAddressOf(), &stride, &offset);
			//�C���f�b�N�X�o�b�t�@�̃Z�b�g
			pD3D11DeviceContext->IASetIndexBuffer(MeshRes->GetIndexBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);

			//�`����@�i3�p�`�j
			pD3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			//�R���X�^���g�o�b�t�@�̐ݒ�
			ID3D11Buffer* pConstantBuffer = CBStatic::GetPtr()->GetBuffer();
			ID3D11Buffer* pNullConstantBuffer = nullptr;
			//���_�V�F�[�_�ɓn��
			pD3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
			//�s�N�Z���V�F�[�_�ɓn��
			pD3D11DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);
			//�V�F�[�_�̐ݒ�
			pD3D11DeviceContext->VSSetShader(VSPCTStatic::GetPtr()->GetShader(), nullptr, 0);
			pD3D11DeviceContext->PSSetShader(PSPCTStatic::GetPtr()->GetShader(), nullptr, 0);
			//�C���v�b�g���C�A�E�g�̐ݒ�
			pD3D11DeviceContext->IASetInputLayout(VSPCTStatic::GetPtr()->GetInputLayout());
			//�u�����h�X�e�[�g
			if (GameObjectPtr->GetAlphaActive()) {
				//��������
				pD3D11DeviceContext->OMSetBlendState(RenderState->GetAlphaBlendEx(), nullptr, 0xffffffff);
			}
			else {
				//�����������Ȃ�
				pD3D11DeviceContext->OMSetBlendState(RenderState->GetOpaque(), nullptr, 0xffffffff);
			}
			//�f�v�X�X�e���V���X�e�[�g
			pD3D11DeviceContext->OMSetDepthStencilState(RenderState->GetDepthDefault(), 0);

			//�e�N�X�`���ƃT���v���[�̐ݒ�
			ID3D11ShaderResourceView* pNull[1] = { 0 };
			pD3D11DeviceContext->PSSetShaderResources(0, 1, TextureRes->GetShaderResourceView().GetAddressOf());
			//���b�s���O�T���v���[
			ID3D11SamplerState* pSampler = RenderState->GetLinearClamp();
			if (WrapSampler) {
				pSampler = RenderState->GetLinearWrap();
			}
			pD3D11DeviceContext->PSSetSamplers(0, 1, &pSampler);

			//���������Ȃ�
			if (GameObjectPtr->GetAlphaActive()) {
				//���X�^���C�U�X�e�[�g(���`��)
				pD3D11DeviceContext->RSSetState(RenderState->GetCullFront());
				//�`��
				pD3D11DeviceContext->DrawIndexed(MeshRes->GetNumIndicis(), 0, 0);
				//���X�^���C�U�X�e�[�g�i�\�`��j
				pD3D11DeviceContext->RSSetState(RenderState->GetCullBack());
				//�`��
				pD3D11DeviceContext->DrawIndexed(MeshRes->GetNumIndicis(), 0, 0);
			}
			else {
				//���X�^���C�U�X�e�[�g
				pD3D11DeviceContext->RSSetState(RenderState->GetCullBack());
				//�`��
				pD3D11DeviceContext->DrawIndexed(MeshRes->GetNumIndicis(), 0, 0);
			}
			//��n��
			Dev->InitializeStates();
		}
		static void PNTNotShadowDraw(const shared_ptr<GameObject>& GameObjectPtr,
			const shared_ptr<MeshResource>& MeshRes,
			const shared_ptr<TextureResource>& TextureRes, bool WrapSampler,
			const Color4& Emissive, const Color4& Diffuse, const Matrix4X4& MeshToTransformMatrix) {
			auto Dev = App::GetApp()->GetDeviceResources();
			auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
			auto RenderState = Dev->GetRenderState();
			//�s��̒�`
			auto PtrTrans = GameObjectPtr->GetComponent<Transform>();
			//�s��̒�`
			Matrix4X4 World, ViewMat, ProjMat;
			//���[���h�s��̌���
			World = MeshToTransformMatrix * PtrTrans->GetWorldMatrix();
			//�]�u����
			World.Transpose();
			//�J�����𓾂�
			auto CameraPtr = GameObjectPtr->OnGetDrawCamera();
			//�r���[�Ǝˉe�s��𓾂�
			ViewMat = CameraPtr->GetViewMatrix();
			//�]�u����
			ViewMat.Transpose();
			//�]�u����
			ProjMat = CameraPtr->GetProjMatrix();
			ProjMat.Transpose();

			//�R���X�^���g�o�b�t�@�̐ݒ�
			PNTStaticConstantBuffer cb1;
			//�s��̐ݒ�(�]�u����)
			//�R���X�^���g�o�b�t�@�̐ݒ�
			cb1.World = World;
			cb1.View = ViewMat;
			cb1.Projection = ProjMat;
			//���C�e�B���O
			auto StageLight = GameObjectPtr->OnGetDrawLight();
			cb1.LightDir = StageLight.m_Directional;
			cb1.LightDir.w = 1.0f;
			cb1.Emissive = Emissive;
			cb1.Diffuse = Diffuse;
			//�R���X�^���g�o�b�t�@�̍X�V
			pD3D11DeviceContext->UpdateSubresource(CBPNTStatic::GetPtr()->GetBuffer(), 0, nullptr, &cb1, 0, 0);

			//�X�g���C�h�ƃI�t�Z�b�g
			UINT stride = sizeof(VertexPositionNormalTexture);
			UINT offset = 0;
			//���_�o�b�t�@�̃Z�b�g
			pD3D11DeviceContext->IASetVertexBuffers(0, 1, MeshRes->GetVertexBuffer().GetAddressOf(), &stride, &offset);
			//�C���f�b�N�X�o�b�t�@�̃Z�b�g
			pD3D11DeviceContext->IASetIndexBuffer(MeshRes->GetIndexBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);

			//�`����@�i3�p�`�j
			pD3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			//�R���X�^���g�o�b�t�@�̐ݒ�
			ID3D11Buffer* pConstantBuffer = CBPNTStatic::GetPtr()->GetBuffer();
			ID3D11Buffer* pNullConstantBuffer = nullptr;
			//���_�V�F�[�_�ɓn��
			pD3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
			//�s�N�Z���V�F�[�_�ɓn��
			pD3D11DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);
			//�V�F�[�_�̐ݒ�
			pD3D11DeviceContext->VSSetShader(VSPNTStatic::GetPtr()->GetShader(), nullptr, 0);
			pD3D11DeviceContext->PSSetShader(PSPNTStatic::GetPtr()->GetShader(), nullptr, 0);
			//�C���v�b�g���C�A�E�g�̐ݒ�
			pD3D11DeviceContext->IASetInputLayout(VSPNTStatic::GetPtr()->GetInputLayout());
			//�u�����h�X�e�[�g
			if (GameObjectPtr->GetAlphaActive()) {
				//��������
				pD3D11DeviceContext->OMSetBlendState(RenderState->GetAlphaBlendEx(), nullptr, 0xffffffff);
			}
			else {
				//�����������Ȃ�
				pD3D11DeviceContext->OMSetBlendState(RenderState->GetOpaque(), nullptr, 0xffffffff);
			}
			//�f�v�X�X�e���V���X�e�[�g
			pD3D11DeviceContext->OMSetDepthStencilState(RenderState->GetDepthDefault(), 0);

			//�e�N�X�`���ƃT���v���[�̐ݒ�
			ID3D11ShaderResourceView* pNull[1] = { 0 };
			pD3D11DeviceContext->PSSetShaderResources(0, 1, TextureRes->GetShaderResourceView().GetAddressOf());
			//���b�s���O�T���v���[
			ID3D11SamplerState* pSampler = RenderState->GetLinearClamp();
			if (WrapSampler) {
				pSampler = RenderState->GetLinearWrap();
			}
			pD3D11DeviceContext->PSSetSamplers(0, 1, &pSampler);
			//���������Ȃ�
			if (GameObjectPtr->GetAlphaActive()) {
				//���X�^���C�U�X�e�[�g(���`��)
				pD3D11DeviceContext->RSSetState(RenderState->GetCullFront());
				//�`��
				pD3D11DeviceContext->DrawIndexed(MeshRes->GetNumIndicis(), 0, 0);
				//���X�^���C�U�X�e�[�g�i�\�`��j
				pD3D11DeviceContext->RSSetState(RenderState->GetCullBack());
				//�`��
				pD3D11DeviceContext->DrawIndexed(MeshRes->GetNumIndicis(), 0, 0);
			}
			else {
				//���X�^���C�U�X�e�[�g
				pD3D11DeviceContext->RSSetState(RenderState->GetCullBack());
				//�`��
				pD3D11DeviceContext->DrawIndexed(MeshRes->GetNumIndicis(), 0, 0);
			}
			//��n��
			Dev->InitializeStates();
		}

		static void PNTWithShadowDraw(const shared_ptr<GameObject>& GameObjectPtr,
			const shared_ptr<MeshResource>& MeshRes,
			const shared_ptr<TextureResource>& TextureRes, bool WrapSampler,
			const Color4& Emissive, const Color4& Diffuse, const Matrix4X4& MeshToTransformMatrix) {
			auto Dev = App::GetApp()->GetDeviceResources();
			auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
			auto RenderState = Dev->GetRenderState();
			//�s��̒�`
			auto PtrTrans = GameObjectPtr->GetComponent<Transform>();
			//�s��̒�`
			Matrix4X4 World, ViewMat, ProjMat;
			//���[���h�s��̌���
			World = MeshToTransformMatrix * PtrTrans->GetWorldMatrix();
			//�]�u����
			World.Transpose();
			//�J�����𓾂�
			auto CameraPtr = GameObjectPtr->OnGetDrawCamera();
			//�r���[�Ǝˉe�s��𓾂�
			ViewMat = CameraPtr->GetViewMatrix();
			//�]�u����
			ViewMat.Transpose();
			//�]�u����
			ProjMat = CameraPtr->GetProjMatrix();
			ProjMat.Transpose();


			//�R���X�^���g�o�b�t�@�̐ݒ�
			PNTStaticShadowConstantBuffer cb1;
			ZeroMemory(&cb1, sizeof(cb1));
			//�s��̐ݒ�(�]�u����)
			//�R���X�^���g�o�b�t�@�̐ݒ�
			cb1.World = World;
			cb1.View = ViewMat;
			cb1.Projection = ProjMat;
			//���C�e�B���O
			auto StageLight = GameObjectPtr->OnGetDrawLight();
			cb1.LightDir = StageLight.m_Directional;
			cb1.LightDir.w = 1.0f;
			cb1.Emissive = Emissive;
			cb1.Diffuse = Diffuse;
			Vector3 CalcLightDir = -1.0 * StageLight.m_Directional;
			Vector3 LightAt = CameraPtr->GetAt();
			Vector3 LightEye = CalcLightDir;
			LightEye *= Shadowmap::GetLightHeight();
			LightEye = LightAt + LightEye;
			cb1.LightPos = LightEye;
			cb1.LightPos.w = 1.0f;
			cb1.EyePos = CameraPtr->GetEye();
			cb1.EyePos.w = 1.0f;
			cb1.ActiveFlg.x = 1;
			Matrix4X4 LightView, LightProj;
			//���C�g�̃r���[�Ǝˉe���v�Z
			LightView.LookAtLH(LightEye, LightAt, Vector3(0, 1.0f, 0));
			LightProj.OrthographicLH(Shadowmap::GetViewWidth(), Shadowmap::GetViewHeight(),
				Shadowmap::GetLightNear(), Shadowmap::GetLightFar());
			cb1.LightView = Matrix4X4EX::Transpose(LightView);
			cb1.LightProjection = Matrix4X4EX::Transpose(LightProj);

			//�R���X�^���g�o�b�t�@�̍X�V
			pD3D11DeviceContext->UpdateSubresource(CBPNTStaticShadow::GetPtr()->GetBuffer(), 0, nullptr, &cb1, 0, 0);
			//�X�g���C�h�ƃI�t�Z�b�g
			UINT stride = sizeof(VertexPositionNormalTexture);
			UINT offset = 0;
			//���_�o�b�t�@�̃Z�b�g
			pD3D11DeviceContext->IASetVertexBuffers(0, 1, MeshRes->GetVertexBuffer().GetAddressOf(), &stride, &offset);
			//�C���f�b�N�X�o�b�t�@�̃Z�b�g
			pD3D11DeviceContext->IASetIndexBuffer(MeshRes->GetIndexBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);
			//�`����@�i3�p�`�j
			pD3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			//�R���X�^���g�o�b�t�@�̐ݒ�
			ID3D11Buffer* pConstantBuffer = CBPNTStaticShadow::GetPtr()->GetBuffer();
			ID3D11Buffer* pNullConstantBuffer = nullptr;
			//���_�V�F�[�_�ɓn��
			pD3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
			//�s�N�Z���V�F�[�_�ɓn��
			pD3D11DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);
			//�V�F�[�_�̐ݒ�
			bool IsShadowmap = false;
			if (GameObjectPtr->GetComponent<Shadowmap>(false)) {
				//�V���h�E�}�b�v������Ύ��ȉe�h�~�p�̃s�N�Z���V�F�[�_
				pD3D11DeviceContext->VSSetShader(VSPNTStaticShadow::GetPtr()->GetShader(), nullptr, 0);
				pD3D11DeviceContext->PSSetShader(PSPNTStaticShadow2::GetPtr()->GetShader(), nullptr, 0);
				IsShadowmap = true;
			}
			else {
				pD3D11DeviceContext->VSSetShader(VSPNTStaticShadow::GetPtr()->GetShader(), nullptr, 0);
				pD3D11DeviceContext->PSSetShader(PSPNTStaticShadow::GetPtr()->GetShader(), nullptr, 0);
			}
			//�C���v�b�g���C�A�E�g�̐ݒ�
			pD3D11DeviceContext->IASetInputLayout(VSPNTStaticShadow::GetPtr()->GetInputLayout());
			//�u�����h�X�e�[�g
			if (GameObjectPtr->GetAlphaActive()) {
				//��������
				pD3D11DeviceContext->OMSetBlendState(RenderState->GetAlphaBlendEx(), nullptr, 0xffffffff);
			}
			else {
				//�����������Ȃ�
				pD3D11DeviceContext->OMSetBlendState(RenderState->GetOpaque(), nullptr, 0xffffffff);
			}
			//�f�v�X�X�e���V���X�e�[�g
			pD3D11DeviceContext->OMSetDepthStencilState(RenderState->GetDepthDefault(), 0);
			//�e�N�X�`���ƃT���v���[�̐ݒ�
			ID3D11ShaderResourceView* pNull[1] = { 0 };
			pD3D11DeviceContext->PSSetShaderResources(0, 1, TextureRes->GetShaderResourceView().GetAddressOf());
			//���b�s���O�T���v���[
			ID3D11SamplerState* pSampler = RenderState->GetLinearClamp();
			if (WrapSampler) {
				pSampler = RenderState->GetLinearWrap();
			}
			pD3D11DeviceContext->PSSetSamplers(0, 1, &pSampler);
			//�V���h�E�}�b�v�̃����_���[�^�[�Q�b�g
			auto ShadowmapPtr = Dev->GetShadowMapRenderTarget();
			ID3D11ShaderResourceView* pShadowSRV = ShadowmapPtr->GetShaderResourceView();
			pD3D11DeviceContext->PSSetShaderResources(1, 1, &pShadowSRV);
			//�V���h�E�}�b�v�T���v���[
			ID3D11SamplerState* pShadowSampler = RenderState->GetComparisonLinear();
			pD3D11DeviceContext->PSSetSamplers(1, 1, &pShadowSampler);
			//���������Ȃ�
			if (GameObjectPtr->GetAlphaActive()) {
				//���X�^���C�U�X�e�[�g(���`��)
				pD3D11DeviceContext->RSSetState(RenderState->GetCullFront());
				//�`��
				pD3D11DeviceContext->DrawIndexed(MeshRes->GetNumIndicis(), 0, 0);
				//���X�^���C�U�X�e�[�g�i�\�`��j
				pD3D11DeviceContext->RSSetState(RenderState->GetCullBack());
				//�`��
				pD3D11DeviceContext->DrawIndexed(MeshRes->GetNumIndicis(), 0, 0);
			}
			else {
				//���X�^���C�U�X�e�[�g
				pD3D11DeviceContext->RSSetState(RenderState->GetCullBack());
				//�`��
				pD3D11DeviceContext->DrawIndexed(MeshRes->GetNumIndicis(), 0, 0);
			}
			//��n��
			Dev->InitializeStates();
		}
	};




	//--------------------------------------------------------------------------------------
	//	struct Base3DDraw::Impl;
	//	�p�r: Base3DDraw�C�f�B�I��
	//--------------------------------------------------------------------------------------
	struct Base3DDraw::Impl {
		//�G�~�b�V�u�F
		Color4 m_Emissive;
		//�f�t���[�Y�F
		Color4 m_Diffuse;
		//�r���[�s��
		Matrix4X4 m_ViewMatrix;
		//�ˉe�s��
		Matrix4X4 m_ProjMatrix;
		Impl() :
			m_Emissive(0, 0, 0, 0),
			m_Diffuse(1.0f, 1.0f, 1.0f, 1.0f),
			m_ViewMatrix(),
			m_ProjMatrix()
		{}
	};

	//--------------------------------------------------------------------------------------
	///	3D�`��R���|�[�l���g�̐e(3D�`��̐e)
	//--------------------------------------------------------------------------------------
	Base3DDraw::Base3DDraw(const shared_ptr<GameObject>& GameObjectPtr):
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
	//	�p�r: DynamicBaseDraw�C�f�B�I��
	//--------------------------------------------------------------------------------------
	struct DynamicBaseDraw::Impl {
		//���b�V��
		shared_ptr<MeshResource> m_MeshResource;
		Impl()
		{}
	};


	//--------------------------------------------------------------------------------------
	///	Dynamic�`��R���|�[�l���g�̐e(���_��ύX�ł���3D�`��)
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
		Impl()
		{}
	};



	//--------------------------------------------------------------------------------------
	///	PCDynamic�`��R���|�[�l���g
	//--------------------------------------------------------------------------------------
	PCDynamicDraw::PCDynamicDraw(const shared_ptr<GameObject>& GameObjectPtr) :
		DynamicBaseDraw(GameObjectPtr),
		pImpl(new Impl())
	{
		//�p�C�v���C���X�e�[�g���f�t�H���g��3D
		SetBlendState(BlendState::Opaque);
		SetDepthStencilState(DepthStencilState::Default);
		SetRasterizerState(RasterizerState::CullBack);
		SetSamplerState(SamplerState::LinearClamp);
	}

	PCDynamicDraw::~PCDynamicDraw() {}

	void PCDynamicDraw::CreateMesh(vector<VertexPositionColor>& Vertices, vector<uint16_t>& indices) {
		try {
			//���b�V���̍쐬�i�ύX�ł���j
			auto MeshRes = MeshResource::CreateMeshResource(Vertices, indices, true);
			SetMeshResource(MeshRes);
		}
		catch (...) {
			throw;
		}
	}

	void PCDynamicDraw::UpdateVertices(const vector<VertexPositionColor>& Vertices) {
		auto MeshRes = GetMeshResource();
		if (!MeshRes) {
			throw BaseException(
				L"���b�V�����쐬����Ă��܂���",
				L"if (!GetMeshResource())",
				L"PCDynamicDraw::UpdateVertices()"
			);

		}
		MeshRes->UpdateVirtexBuffer(Vertices);

	}
	void PCDynamicDraw::OnCreate() {
	}
	void PCDynamicDraw::OnDraw() {
		auto PtrStage = GetGameObject()->GetStage();
		if (!PtrStage) {
			return;
		}
		//���b�V�����Ȃ���Ε`�悵�Ȃ�
		auto MeshRes = GetMeshResource();
		if (!MeshRes) {
			throw BaseException(
				L"���b�V�����쐬����Ă��܂���",
				L"if (!MeshRes)",
				L"PCDynamicDraw::OnDraw()"
			);
		}

		Draw3DPrim::PCDraw(GetGameObject(), MeshRes,GetEmissive(), GetDiffuse(), GetMeshToTransformMatrix());
	}



	//--------------------------------------------------------------------------------------
	//	struct PTDynamicDraw::Impl;
	//--------------------------------------------------------------------------------------
	struct PTDynamicDraw::Impl {
		Impl()
		{}
	};

	//--------------------------------------------------------------------------------------
	///	PTDynamic�`��R���|�[�l���g
	//--------------------------------------------------------------------------------------
	PTDynamicDraw::PTDynamicDraw(const shared_ptr<GameObject>& GameObjectPtr) :
		DynamicBaseDraw(GameObjectPtr),
		pImpl(new Impl())
	{
		//�p�C�v���C���X�e�[�g���f�t�H���g��3D
		SetBlendState(BlendState::Opaque);
		SetDepthStencilState(DepthStencilState::Default);
		SetRasterizerState(RasterizerState::CullBack);
		SetSamplerState(SamplerState::LinearClamp);
	}

	PTDynamicDraw::~PTDynamicDraw() {}

	void PTDynamicDraw::CreateMesh(vector<VertexPositionTexture>& Vertices, vector<uint16_t>& indices) {
		try {
			//���b�V���̍쐬�i�ύX�ł���j
			auto MeshRes = MeshResource::CreateMeshResource(Vertices, indices, true);
			SetMeshResource(MeshRes);
		}
		catch (...) {
			throw;
		}
	}

	void PTDynamicDraw::UpdateVertices(const vector<VertexPositionTexture>& Vertices) {
		auto MeshRes = GetMeshResource();
		if (!MeshRes) {
			throw BaseException(
				L"���b�V�����쐬����Ă��܂���",
				L"if (!GetMeshResource())",
				L"PTDynamicDraw::UpdateVertices()"
			);

		}
		MeshRes->UpdateVirtexBuffer(Vertices);
	}

	void PTDynamicDraw::OnCreate() {
	}
	void PTDynamicDraw::OnDraw() {
		auto PtrStage = GetGameObject()->GetStage();
		if (!PtrStage) {
			return;
		}
		//���b�V�����Ȃ���Ε`�悵�Ȃ�
		auto MeshRes = GetMeshResource();
		if (!MeshRes) {
			throw BaseException(
				L"���b�V�����쐬����Ă��܂���",
				L"if (!MeshRes)",
				L"PTDynamicDraw::OnDraw()"
			);
		}
		//�e�N�X�`�����Ȃ���Ε`�悵�Ȃ�
		auto shTex = GetTextureResource();
		if (!shTex) {
			return;
		}
		Draw3DPrim::PTDraw(GetGameObject(), MeshRes,
			shTex, GetWrapSampler(),
			GetEmissive(), GetDiffuse(), GetMeshToTransformMatrix());
	}



	//--------------------------------------------------------------------------------------
	//	struct PCTDynamicDraw::Impl;
	//--------------------------------------------------------------------------------------
	struct PCTDynamicDraw::Impl {
		Impl() 
		{}
	};

	//--------------------------------------------------------------------------------------
	///	PCTDynamic�`��R���|�[�l���g
	//--------------------------------------------------------------------------------------
	PCTDynamicDraw::PCTDynamicDraw(const shared_ptr<GameObject>& GameObjectPtr) :
		DynamicBaseDraw(GameObjectPtr),
		pImpl(new Impl())
	{
		//�p�C�v���C���X�e�[�g���f�t�H���g��3D
		SetBlendState(BlendState::Opaque);
		SetDepthStencilState(DepthStencilState::Default);
		SetRasterizerState(RasterizerState::CullBack);
		SetSamplerState(SamplerState::LinearClamp);
	}

	PCTDynamicDraw::~PCTDynamicDraw() {}

	void PCTDynamicDraw::CreateMesh(vector<VertexPositionColorTexture>& Vertices, vector<uint16_t>& indices) {
		try {
			//���b�V���̍쐬�i�ύX�ł���j
			auto MeshRes = MeshResource::CreateMeshResource(Vertices, indices, true);
			SetMeshResource(MeshRes);
		}
		catch (...) {
			throw;
		}
	}

	void PCTDynamicDraw::UpdateVertices(const vector<VertexPositionColorTexture>& Vertices) {
		auto MeshRes = GetMeshResource();
		if (!MeshRes) {
			throw BaseException(
				L"���b�V�����쐬����Ă��܂���",
				L"if (!GetMeshResource())",
				L"PCTDynamicDraw::UpdateVertices()"
			);

		}
		MeshRes->UpdateVirtexBuffer(Vertices);
	}

	void PCTDynamicDraw::OnCreate() {
	}
	void PCTDynamicDraw::OnDraw() {
		auto PtrStage = GetGameObject()->GetStage();
		if (!PtrStage) {
			return;
		}
		//���b�V�����Ȃ���Ε`�悵�Ȃ�
		auto MeshRes = GetMeshResource();
		if (!MeshRes) {
			throw BaseException(
				L"���b�V�����쐬����Ă��܂���",
				L"if (!MeshRes)",
				L"PCTDynamicDraw::OnDraw()"
			);
		}
		//�e�N�X�`�����Ȃ���Ε`�悵�Ȃ�
		auto shTex = GetTextureResource();
		if (!shTex) {
			return;
		}
		Draw3DPrim::PCTDraw(GetGameObject(),MeshRes,
			shTex, GetWrapSampler(),
			GetEmissive(), GetDiffuse(), GetMeshToTransformMatrix());
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
	///	PNTDynamic�`��R���|�[�l���g
	//--------------------------------------------------------------------------------------
	PNTDynamicDraw::PNTDynamicDraw(const shared_ptr<GameObject>& GameObjectPtr) :
		DynamicBaseDraw(GameObjectPtr),
		pImpl(new Impl())
	{
		//�p�C�v���C���X�e�[�g���f�t�H���g��3D
		SetBlendState(BlendState::Opaque);
		SetDepthStencilState(DepthStencilState::Default);
		SetRasterizerState(RasterizerState::CullBack);
		SetSamplerState(SamplerState::LinearClamp);
	}

	PNTDynamicDraw::~PNTDynamicDraw() {}

	void PNTDynamicDraw::CreateMesh(vector<VertexPositionNormalTexture>& Vertices, vector<uint16_t>& indices) {
		try {
			//���b�V���̍쐬�i�ύX�ł���j
			auto MeshRes = MeshResource::CreateMeshResource(Vertices, indices, true);
			SetMeshResource(MeshRes);
		}
		catch (...) {
			throw;
		}
	}

	void PNTDynamicDraw::UpdateVertices(const vector<VertexPositionNormalTexture>& Vertices) {
		auto MeshRes = GetMeshResource();
		if (!MeshRes) {
			throw BaseException(
				L"���b�V�����쐬����Ă��܂���",
				L"if (!GetMeshResource())",
				L"PNTDynamicDraw::UpdateVertices()"
			);

		}
		MeshRes->UpdateVirtexBuffer(Vertices);
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
		auto PtrStage = GetGameObject()->GetStage();
		if (!PtrStage) {
			return;
		}
		//���b�V�����Ȃ���Ε`�悵�Ȃ�
		auto MeshRes = GetMeshResource();
		if (!MeshRes) {
			throw BaseException(
				L"���b�V�����쐬����Ă��܂���",
				L"if (!MeshRes)",
				L"PNTStaticDraw::OnDraw()"
			);
		}
		//�e�N�X�`�����Ȃ���Ε`�悵�Ȃ�
		auto shTex = GetTextureResource();
		if (!shTex) {
			return;
		}
		Draw3DPrim::PNTNotShadowDraw(GetGameObject(),
			MeshRes,
			shTex, GetWrapSampler(),
			GetEmissive(), GetDiffuse(), GetMeshToTransformMatrix());
	}

	void PNTDynamicDraw::DrawWithShadow() {
		auto PtrStage = GetGameObject()->GetStage();
		if (!PtrStage) {
			return;
		}
		//���b�V�����Ȃ���Ε`�悵�Ȃ�
		auto MeshRes = GetMeshResource();
		if (!MeshRes) {
			throw BaseException(
				L"���b�V�����쐬����Ă��܂���",
				L"if (!MeshRes)",
				L"PNTStaticDraw::OnDraw()"
			);
		}
		//�e�N�X�`�����Ȃ���Ε`�悵�Ȃ�
		auto shTex = GetTextureResource();
		if (!shTex) {
			return;
		}
		Draw3DPrim::PNTWithShadowDraw(GetGameObject(),
			MeshRes,
			shTex, GetWrapSampler(),
			GetEmissive(), GetDiffuse(), GetMeshToTransformMatrix());
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
	//	�p�r: StaticBaseDraw�C�f�B�I��
	//--------------------------------------------------------------------------------------
	struct StaticBaseDraw::Impl {
		//���b�V����weak_ptr
		weak_ptr<MeshResource> m_MeshResource;
		Impl()
		{}
	};


	//--------------------------------------------------------------------------------------
	///	static�`��R���|�[�l���g�̐e(���_��ύX�ł��Ȃ�3D�`��)
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
	///	PCStatic�`��R���|�[�l���g
	//--------------------------------------------------------------------------------------
	PCStaticDraw::PCStaticDraw(const shared_ptr<GameObject>& GameObjectPtr) :
		StaticBaseDraw(GameObjectPtr),
		pImpl(new Impl())
	{
		//�p�C�v���C���X�e�[�g���f�t�H���g��3D
		SetBlendState(BlendState::Opaque);
		SetDepthStencilState(DepthStencilState::Default);
		SetRasterizerState(RasterizerState::CullBack);
		SetSamplerState(SamplerState::LinearClamp);
	}

	PCStaticDraw::~PCStaticDraw() {}

	void PCStaticDraw::OnDraw() {
		auto PtrStage = GetGameObject()->GetStage();
		if (!PtrStage) {
			return;
		}
		//���b�V�����Ȃ���Ε`�悵�Ȃ�
		auto MeshRes = GetMeshResource();
		if (!MeshRes) {
			throw BaseException(
				L"���b�V�����쐬����Ă��܂���",
				L"if (!MeshRes)",
				L"PCStaticDraw::OnDraw()"
			);
		}
		Draw3DPrim::PCDraw(GetGameObject(), MeshRes, GetEmissive(), GetDiffuse(), GetMeshToTransformMatrix());
	}

	//--------------------------------------------------------------------------------------
	//	struct PCTStaticDraw::Impl;
	//--------------------------------------------------------------------------------------
	struct PCTStaticDraw::Impl {
		Impl()
		{}
	};


	//--------------------------------------------------------------------------------------
	///	PCTStatic�`��R���|�[�l���g
	//--------------------------------------------------------------------------------------
	PCTStaticDraw::PCTStaticDraw(const shared_ptr<GameObject>& GameObjectPtr) :
		StaticBaseDraw(GameObjectPtr),
		pImpl(new Impl())
	{
		//�p�C�v���C���X�e�[�g���f�t�H���g��3D
		SetBlendState(BlendState::Opaque);
		SetDepthStencilState(DepthStencilState::Default);
		SetRasterizerState(RasterizerState::CullBack);
		SetSamplerState(SamplerState::LinearClamp);
	}

	PCTStaticDraw::~PCTStaticDraw() {}


	void PCTStaticDraw::OnDraw() {
		auto PtrStage = GetGameObject()->GetStage();
		if (!PtrStage) {
			return;
		}
		//���b�V�����Ȃ���Ε`�悵�Ȃ�
		auto MeshRes = GetMeshResource();
		if (!MeshRes) {
			throw BaseException(
				L"���b�V�����쐬����Ă��܂���",
				L"if (!MeshRes)",
				L"PCTDynamicDraw::OnDraw()"
			);
		}
		//�e�N�X�`�����Ȃ���Ε`�悵�Ȃ�
		auto shTex = GetTextureResource();
		if (!shTex) {
			return;
		}
		Draw3DPrim::PCTDraw(GetGameObject(), MeshRes,
			shTex, GetWrapSampler(),
			GetEmissive(), GetDiffuse(), GetMeshToTransformMatrix());
	}




	//--------------------------------------------------------------------------------------
	//	struct PNTStaticDraw::Impl;
	//	�p�r: Impl�C�f�B�I��
	//--------------------------------------------------------------------------------------
	struct PNTStaticDraw::Impl {
		bool m_OwnShadowActive;
		Impl() :
			m_OwnShadowActive(false)
		{}
		~Impl() {}
	};



	//--------------------------------------------------------------------------------------
	//	class PNTStaticDraw : public DrawComponent;
	//	�p�r: PNTStatic�`��R���|�[�l���g
	//--------------------------------------------------------------------------------------
	PNTStaticDraw::PNTStaticDraw(const shared_ptr<GameObject>& GameObjectPtr) :
		StaticBaseDraw(GameObjectPtr),
		pImpl(new Impl()) {
		//�p�C�v���C���X�e�[�g���f�t�H���g�̂RD
		SetBlendState(BlendState::Opaque);
		SetDepthStencilState(DepthStencilState::Default);
		SetRasterizerState(RasterizerState::CullBack);
		SetSamplerState(SamplerState::LinearClamp);
	}

	PNTStaticDraw::~PNTStaticDraw() {}

	void PNTStaticDraw::OnCreate() {
	}

	bool PNTStaticDraw::GetOwnShadowActive() const {
		return pImpl->m_OwnShadowActive;
	}
	bool PNTStaticDraw::IsOwnShadowActive() const {
		return pImpl->m_OwnShadowActive;
	}
	void PNTStaticDraw::SetOwnShadowActive(bool b) {
		pImpl->m_OwnShadowActive = b;
	}

	void PNTStaticDraw::DrawNotShadow() {
		auto PtrStage = GetGameObject()->GetStage();
		if (!PtrStage) {
			return;
		}
		//���b�V�����Ȃ���Ε`�悵�Ȃ�
		auto MeshRes = GetMeshResource();
		if (!MeshRes) {
			throw BaseException(
				L"���b�V�����쐬����Ă��܂���",
				L"if (!MeshRes)",
				L"PNTStaticDraw::OnDraw()"
			);
		}
		//�e�N�X�`�����Ȃ���Ε`�悵�Ȃ�
		auto shTex = GetTextureResource();
		if (!shTex) {
			return;
		}
		Draw3DPrim::PNTNotShadowDraw(GetGameObject(),
			MeshRes,
			shTex, GetWrapSampler(),
			GetEmissive(), GetDiffuse(), GetMeshToTransformMatrix());
	}

	void PNTStaticDraw::DrawWithShadow() {
		auto PtrStage = GetGameObject()->GetStage();
		if (!PtrStage) {
			return;
		}
		//���b�V�����Ȃ���Ε`�悵�Ȃ�
		auto MeshRes = GetMeshResource();
		if (!MeshRes) {
			throw BaseException(
				L"���b�V�����쐬����Ă��܂���",
				L"if (!MeshRes)",
				L"PNTStaticDraw::OnDraw()"
			);
		}
		//�e�N�X�`�����Ȃ���Ε`�悵�Ȃ�
		auto shTex = GetTextureResource();
		if (!shTex) {
			return;
		}
		Draw3DPrim::PNTWithShadowDraw(GetGameObject(),
			MeshRes,
			shTex, GetWrapSampler(),
			GetEmissive(), GetDiffuse(), GetMeshToTransformMatrix());
	}

	void PNTStaticDraw::OnDraw() {
		if (GetOwnShadowActive()) {
			DrawWithShadow();
		}
		else {
			DrawNotShadow();
		}
	}

	//--------------------------------------------------------------------------------------
	//	struct PNTStaticModelDraw::Impl;
	//	�p�r: Impl�C�f�B�I��
	//--------------------------------------------------------------------------------------
	struct PNTStaticModelDraw::Impl {
		weak_ptr<MeshResource> m_MeshResource;	//���b�V�����\�[�X
		bool m_OwnShadowActive;
		Impl() :
			m_OwnShadowActive(false)
		{}
		~Impl() {}
	};

	//--------------------------------------------------------------------------------------
	//	class PNTStaticModelDraw : public DrawComponent;
	//	�p�r: PNTStaticModelDraw�`��R���|�[�l���g
	//--------------------------------------------------------------------------------------
	PNTStaticModelDraw::PNTStaticModelDraw(const shared_ptr<GameObject>& GameObjectPtr) :
		Base3DDraw(GameObjectPtr),
		pImpl(new Impl()) {
		//�p�C�v���C���X�e�[�g���f�t�H���g�̂RD
		SetBlendState(BlendState::Opaque);
		SetDepthStencilState(DepthStencilState::Default);
		SetRasterizerState(RasterizerState::CullBack);
		SetSamplerState(SamplerState::LinearClamp);
	}

	PNTStaticModelDraw::~PNTStaticModelDraw() {}

	void PNTStaticModelDraw::OnCreate() {
	}

	shared_ptr<MeshResource> PNTStaticModelDraw::GetMeshResource() const {
		//���b�V�����Ȃ���΃��^�[��
		if (pImpl->m_MeshResource.expired()) {
			throw BaseException(
				L"���b�V�����ݒ肳��Ă܂���",
				L"if (pImpl->m_MeshResource.expired())",
				L"PNTStaticModelDraw::GetMeshResource()"
			);
		}
		return pImpl->m_MeshResource.lock();
	}

	void PNTStaticModelDraw::SetMeshResource(const shared_ptr<MeshResource>& MeshRes) {
		pImpl->m_MeshResource = MeshRes;
	}
	void PNTStaticModelDraw::SetMeshResource(const wstring& MeshKey) {
		pImpl->m_MeshResource = App::GetApp()->GetResource<MeshResource>(MeshKey);
	}

	bool PNTStaticModelDraw::GetOwnShadowActive() const {
		return pImpl->m_OwnShadowActive;
	}
	bool PNTStaticModelDraw::IsOwnShadowActive() const {
		return pImpl->m_OwnShadowActive;
	}
	void PNTStaticModelDraw::SetOwnShadowActive(bool b) {
		pImpl->m_OwnShadowActive = b;
	}



	void PNTStaticModelDraw::DrawWithShadow() {
		auto PtrStage = GetGameObject()->GetStage();
		if (!PtrStage) {
			return;
		}
		//���b�V�����Ȃ���Ε`�悵�Ȃ�
		auto MeshRes = GetMeshResource();
		if (!MeshRes) {
			throw BaseException(
				L"���b�V�����쐬����Ă��܂���",
				L"if (!MeshRes)",
				L"PNTStaticModelDraw::OnDraw()"
			);
		}
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pID3D11DeviceContext = Dev->GetD3DDeviceContext();
		auto RenderStatePtr = Dev->GetRenderState();

		auto GameObjectPtr = GetGameObject();
		auto PtrTrans = GetGameObject()->GetComponent<Transform>();
		//�s��̒�`
		Matrix4X4 World, ViewMat, ProjMat;
		//���[���h�s��̌���
		World = GetMeshToTransformMatrix() * PtrTrans->GetWorldMatrix();
		//�]�u����
		World.Transpose();
		//�J�����𓾂�
		auto CameraPtr = GameObjectPtr->OnGetDrawCamera();
		//�r���[�Ǝˉe�s��𓾂�
		ViewMat = CameraPtr->GetViewMatrix();
		//�]�u����
		ViewMat.Transpose();
		//�]�u����
		ProjMat = CameraPtr->GetProjMatrix();
		ProjMat.Transpose();

		//�R���X�^���g�o�b�t�@�̐ݒ�
		PNTStaticShadowConstantBuffer cb1;

		ZeroMemory(&cb1, sizeof(cb1));
		//�s��̐ݒ�(�]�u����)
		//�R���X�^���g�o�b�t�@�̐ݒ�
		cb1.World = World;
		cb1.View = ViewMat;
		cb1.Projection = ProjMat;

		//���C�e�B���O
		auto StageLight = GameObjectPtr->OnGetDrawLight();
		cb1.LightDir = StageLight.m_Directional;
		cb1.LightDir.w = 1.0f;

		Vector3 CalcLightDir = -1.0 * StageLight.m_Directional;
		Vector3 LightAt = CameraPtr->GetAt();
		Vector3 LightEye = CalcLightDir;
		LightEye *= Shadowmap::GetLightHeight();
		LightEye = LightAt + LightEye;

		cb1.LightPos = LightEye;
		cb1.LightPos.w = 1.0f;

		cb1.EyePos = CameraPtr->GetEye();
		cb1.EyePos.w = 1.0f;
		//���f���̓e�N�X�`���K�{
		cb1.ActiveFlg.x = 1;

		Matrix4X4 LightView, LightProj;
		//���C�g�̃r���[�Ǝˉe���v�Z
		LightView.LookAtLH(LightEye, LightAt, Vector3(0, 1.0f, 0));
		LightProj.OrthographicLH(Shadowmap::GetViewWidth(), Shadowmap::GetViewHeight(),
			Shadowmap::GetLightNear(), Shadowmap::GetLightFar());
		cb1.LightView = Matrix4X4EX::Transpose(LightView);
		cb1.LightProjection = Matrix4X4EX::Transpose(LightProj);

		//�V���h�E�}�b�v�̃��\�[�X�r���[���擾
		//�V���h�E�}�b�v�̃����_���[�^�[�Q�b�g
		auto ShadoumapPtr = Dev->GetShadowMapRenderTarget();
		ID3D11ShaderResourceView* pShadowSRV = ShadoumapPtr->GetShaderResourceView();


		auto MeshPtr = GetMeshResource();
		auto& MatVec = MeshPtr->GetMaterialExVec();

		//�V�F�[�_�̐ݒ�
		bool IsShadowmap = false;
		if (GameObjectPtr->GetComponent<Shadowmap>(false)) {
			//�V���h�E�}�b�v������Ύ��ȉe�h�~�p�̃s�N�Z���V�F�[�_
			pID3D11DeviceContext->VSSetShader(VSPNTStaticShadow::GetPtr()->GetShader(), nullptr, 0);
			pID3D11DeviceContext->PSSetShader(PSPNTStaticShadow2::GetPtr()->GetShader(), nullptr, 0);

			IsShadowmap = true;
		}
		else {
			pID3D11DeviceContext->VSSetShader(VSPNTStaticShadow::GetPtr()->GetShader(), nullptr, 0);
			pID3D11DeviceContext->PSSetShader(PSPNTStaticShadow::GetPtr()->GetShader(), nullptr, 0);
		}

		//�C���v�b�g���C�A�E�g�̐ݒ�
		pID3D11DeviceContext->IASetInputLayout(VSPNTStaticShadow::GetPtr()->GetInputLayout());

		//�X�g���C�h�ƃI�t�Z�b�g
		UINT stride = sizeof(VertexPositionNormalTexture);
		UINT offset = 0;
		//���_�o�b�t�@�̐ݒ�
		pID3D11DeviceContext->IASetVertexBuffers(0, 1, MeshPtr->GetVertexBuffer().GetAddressOf(), &stride, &offset);
		//�C���f�b�N�X�o�b�t�@�̃Z�b�g
		pID3D11DeviceContext->IASetIndexBuffer(MeshPtr->GetIndexBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);

		//�`����@�i3�p�`�j
		pID3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//�f�v�X�X�e���V��
		switch (GetDepthStencilState()) {
		case DepthStencilState::None:
			pID3D11DeviceContext->OMSetDepthStencilState(RenderStatePtr->GetDepthNone(), 0);
			break;
		case DepthStencilState::Default:
			pID3D11DeviceContext->OMSetDepthStencilState(RenderStatePtr->GetDepthDefault(), 0);
			break;
		case DepthStencilState::Read:
			pID3D11DeviceContext->OMSetDepthStencilState(RenderStatePtr->GetDepthRead(), 0);
			break;
		}
		//�T���v���[

		//null�ɏ�����
		ID3D11SamplerState* pSampler = nullptr;
		switch (GetSamplerState()) {
		case SamplerState::SamplerNone:
			break;
		case SamplerState::PointWrap:
			pSampler = RenderStatePtr->GetPointWrap();
			break;
		case SamplerState::PointClamp:
			pSampler = RenderStatePtr->GetPointClamp();
			break;
		case SamplerState::LinearWrap:
			pSampler = RenderStatePtr->GetLinearWrap();
			break;
		case SamplerState::LinearClamp:
			pSampler = RenderStatePtr->GetLinearClamp();
			break;
		case SamplerState::AnisotropicWrap:
			pSampler = RenderStatePtr->GetAnisotropicWrap();
			break;
		case SamplerState::AnisotropicClamp:
			pSampler = RenderStatePtr->GetAnisotropicClamp();
			break;
		case SamplerState::ComparisonLinear:
			pSampler = RenderStatePtr->GetComparisonLinear();
			break;
		}
		//�T���v���[��ݒ�
		pID3D11DeviceContext->PSSetSamplers(0, 1, &pSampler);
		//�e�̃V�F�[�_���\�[�X
		pID3D11DeviceContext->PSSetShaderResources(1, 1, &pShadowSRV);
		pSampler = RenderStatePtr->GetComparisonLinear();
		//�e�̃T���v���[
		pID3D11DeviceContext->PSSetSamplers(1, 1, &pSampler);

		for (auto& m : MatVec) {
			cb1.Emissive = m.m_Emissive;
			cb1.Diffuse = m.m_Diffuse;
			//�R���X�^���g�o�b�t�@�̍X�V
			ID3D11Buffer* pConstantBuffer = CBPNTStaticShadow::GetPtr()->GetBuffer();
			pID3D11DeviceContext->UpdateSubresource(pConstantBuffer, 0, nullptr, &cb1, 0, 0);
			pID3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
			pID3D11DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);
			//�e�N�X�`����ݒ�
			pID3D11DeviceContext->PSSetShaderResources(0, 1, m.m_TextureResource->GetShaderResourceView().GetAddressOf());
			if (GetRasterizerState() == RasterizerState::Wireframe) {
				pID3D11DeviceContext->OMSetBlendState(RenderStatePtr->GetOpaque(), nullptr, 0xffffffff);
				pID3D11DeviceContext->RSSetState(RenderStatePtr->GetWireframe());
				//�`��
				pID3D11DeviceContext->DrawIndexed(m.m_IndexCount, m.m_StartIndex, 0);
			}
			else {
				//�u�����h�X�e�[�g�ƃ��X�^���C�U��ݒ肵�ĕ`��
				//�����A�����`��Ȃ�AlphaBlendEx�ɐݒ肵�A�����łȂ���΁A�w��ɏ]���B
				if (GameObjectPtr->GetAlphaActive()) {
					pID3D11DeviceContext->OMSetBlendState(RenderStatePtr->GetAlphaBlendEx(), nullptr, 0xffffffff);
					//���X�^���C�U�X�e�[�g
					pID3D11DeviceContext->RSSetState(RenderStatePtr->GetCullFront());
					//�`��
					pID3D11DeviceContext->DrawIndexed(m.m_IndexCount, m.m_StartIndex, 0);
					//���X�^���C�U�X�e�[�g
					pID3D11DeviceContext->RSSetState(RenderStatePtr->GetCullBack());
					//�`��
					pID3D11DeviceContext->DrawIndexed(m.m_IndexCount, m.m_StartIndex, 0);
				}
				else {
					switch (GetBlendState()) {
					case BlendState::Opaque:
						pID3D11DeviceContext->OMSetBlendState(RenderStatePtr->GetOpaque(), nullptr, 0xffffffff);
						break;
					case BlendState::AlphaBlend:
						pID3D11DeviceContext->OMSetBlendState(RenderStatePtr->GetAlphaBlendEx(), nullptr, 0xffffffff);
						break;
					case BlendState::Additive:
						pID3D11DeviceContext->OMSetBlendState(RenderStatePtr->GetAdditive(), nullptr, 0xffffffff);
						break;
					case BlendState::NonPremultiplied:
						pID3D11DeviceContext->OMSetBlendState(RenderStatePtr->GetNonPremultiplied(), nullptr, 0xffffffff);
						break;
					}
					switch (GetRasterizerState()) {
					case RasterizerState::CullBack:
						pID3D11DeviceContext->RSSetState(RenderStatePtr->GetCullBack());
						break;
					case RasterizerState::CullFront:
						pID3D11DeviceContext->RSSetState(RenderStatePtr->GetCullFront());
						break;
					case RasterizerState::CullNone:
						pID3D11DeviceContext->RSSetState(RenderStatePtr->GetCullNone());
						break;
					}
					//�`��
					pID3D11DeviceContext->DrawIndexed(m.m_IndexCount, m.m_StartIndex, 0);
				}
			}
		}
		Dev->InitializeStates();
	}

	void PNTStaticModelDraw::DrawNotShadow() {
		auto PtrStage = GetGameObject()->GetStage();
		if (!PtrStage) {
			return;
		}
		//���b�V�����Ȃ���Ε`�悵�Ȃ�
		auto MeshRes = GetMeshResource();
		if (!MeshRes) {
			throw BaseException(
				L"���b�V�����쐬����Ă��܂���",
				L"if (!MeshRes)",
				L"PNTStaticModelDraw::OnDraw()"
			);
		}
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pID3D11DeviceContext = Dev->GetD3DDeviceContext();
		auto RenderStatePtr = Dev->GetRenderState();

		auto GameObjectPtr = GetGameObject();
		auto PtrTrans = GetGameObject()->GetComponent<Transform>();
		//�s��̒�`
		Matrix4X4 World, ViewMat, ProjMat;
		//���[���h�s��̌���
		World = GetMeshToTransformMatrix() * PtrTrans->GetWorldMatrix();
		//�]�u����
		World.Transpose();
		//�J�����𓾂�
		auto CameraPtr = GameObjectPtr->OnGetDrawCamera();
		//�r���[�Ǝˉe�s��𓾂�
		ViewMat = CameraPtr->GetViewMatrix();
		//�]�u����
		ViewMat.Transpose();
		//�]�u����
		ProjMat = CameraPtr->GetProjMatrix();
		ProjMat.Transpose();

		//�R���X�^���g�o�b�t�@�̐ݒ�
		PNTStaticConstantBuffer cb1;
		ZeroMemory(&cb1, sizeof(cb1));
		//�s��̐ݒ�(�]�u����)
		//�R���X�^���g�o�b�t�@�̐ݒ�
		cb1.World = World;
		cb1.View = ViewMat;
		cb1.Projection = ProjMat;

		//���C�e�B���O
		auto StageLight = GameObjectPtr->OnGetDrawLight();
		cb1.LightDir = StageLight.m_Directional;
		cb1.LightDir.w = 1.0f;


		auto MeshPtr = GetMeshResource();
		auto& MatVec = MeshPtr->GetMaterialExVec();

		//�V�F�[�_�̐ݒ�
		pID3D11DeviceContext->VSSetShader(VSPNTStatic::GetPtr()->GetShader(), nullptr, 0);
		pID3D11DeviceContext->PSSetShader(PSPNTStatic::GetPtr()->GetShader(), nullptr, 0);
		//�C���v�b�g���C�A�E�g�̐ݒ�
		pID3D11DeviceContext->IASetInputLayout(VSPNTStatic::GetPtr()->GetInputLayout());

		//�X�g���C�h�ƃI�t�Z�b�g
		UINT stride = sizeof(VertexPositionNormalTexture);
		UINT offset = 0;
		//���_�o�b�t�@�̐ݒ�
		pID3D11DeviceContext->IASetVertexBuffers(0, 1, MeshPtr->GetVertexBuffer().GetAddressOf(), &stride, &offset);
		//�C���f�b�N�X�o�b�t�@�̃Z�b�g
		pID3D11DeviceContext->IASetIndexBuffer(MeshPtr->GetIndexBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);

		//�`����@�i3�p�`�j
		pID3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//�f�v�X�X�e���V��
		switch (GetDepthStencilState()) {
		case DepthStencilState::None:
			pID3D11DeviceContext->OMSetDepthStencilState(RenderStatePtr->GetDepthNone(), 0);
			break;
		case DepthStencilState::Default:
			pID3D11DeviceContext->OMSetDepthStencilState(RenderStatePtr->GetDepthDefault(), 0);
			break;
		case DepthStencilState::Read:
			pID3D11DeviceContext->OMSetDepthStencilState(RenderStatePtr->GetDepthRead(), 0);
			break;
		}
		//�T���v���[
		//null�ɏ�����
		ID3D11SamplerState* pSampler = nullptr;
		switch (GetSamplerState()) {
		case SamplerState::SamplerNone:
			break;
		case SamplerState::PointWrap:
			pSampler = RenderStatePtr->GetPointWrap();
			break;
		case SamplerState::PointClamp:
			pSampler = RenderStatePtr->GetPointClamp();
			break;
		case SamplerState::LinearWrap:
			pSampler = RenderStatePtr->GetLinearWrap();
			break;
		case SamplerState::LinearClamp:
			pSampler = RenderStatePtr->GetLinearClamp();
			break;
		case SamplerState::AnisotropicWrap:
			pSampler = RenderStatePtr->GetAnisotropicWrap();
			break;
		case SamplerState::AnisotropicClamp:
			pSampler = RenderStatePtr->GetAnisotropicClamp();
			break;
		case SamplerState::ComparisonLinear:
			pSampler = RenderStatePtr->GetComparisonLinear();
			break;
		}
		//�T���v���[��ݒ�
		pID3D11DeviceContext->PSSetSamplers(0, 1, &pSampler);

		for (auto& m : MatVec) {
			cb1.Emissive = m.m_Emissive;
			cb1.Diffuse = m.m_Diffuse;
			//�R���X�^���g�o�b�t�@�̍X�V
			ID3D11Buffer* pConstantBuffer = CBPNTStatic::GetPtr()->GetBuffer();
			pID3D11DeviceContext->UpdateSubresource(pConstantBuffer, 0, nullptr, &cb1, 0, 0);
			pID3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
			pID3D11DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);
			//�e�N�X�`����ݒ�
			pID3D11DeviceContext->PSSetShaderResources(0, 1, m.m_TextureResource->GetShaderResourceView().GetAddressOf());
			if (GetRasterizerState() == RasterizerState::Wireframe) {
				pID3D11DeviceContext->OMSetBlendState(RenderStatePtr->GetOpaque(), nullptr, 0xffffffff);
				pID3D11DeviceContext->RSSetState(RenderStatePtr->GetWireframe());
				//�`��
				pID3D11DeviceContext->DrawIndexed(m.m_IndexCount, m.m_StartIndex, 0);
			}
			else {
				//�u�����h�X�e�[�g�ƃ��X�^���C�U��ݒ肵�ĕ`��
				//�����A�����`��Ȃ�AlphaBlendEx�ɐݒ肵�A�����łȂ���΁A�w��ɏ]���B
				if (GameObjectPtr->GetAlphaActive()) {
					pID3D11DeviceContext->OMSetBlendState(RenderStatePtr->GetAlphaBlendEx(), nullptr, 0xffffffff);
					//���X�^���C�U�X�e�[�g
					pID3D11DeviceContext->RSSetState(RenderStatePtr->GetCullFront());
					//�`��
					pID3D11DeviceContext->DrawIndexed(m.m_IndexCount, m.m_StartIndex, 0);
					//���X�^���C�U�X�e�[�g
					pID3D11DeviceContext->RSSetState(RenderStatePtr->GetCullBack());
					//�`��
					pID3D11DeviceContext->DrawIndexed(m.m_IndexCount, m.m_StartIndex, 0);
				}
				else {
					switch (GetBlendState()) {
					case BlendState::Opaque:
						pID3D11DeviceContext->OMSetBlendState(RenderStatePtr->GetOpaque(), nullptr, 0xffffffff);
						break;
					case BlendState::AlphaBlend:
						pID3D11DeviceContext->OMSetBlendState(RenderStatePtr->GetAlphaBlendEx(), nullptr, 0xffffffff);
						break;
					case BlendState::Additive:
						pID3D11DeviceContext->OMSetBlendState(RenderStatePtr->GetAdditive(), nullptr, 0xffffffff);
						break;
					case BlendState::NonPremultiplied:
						pID3D11DeviceContext->OMSetBlendState(RenderStatePtr->GetNonPremultiplied(), nullptr, 0xffffffff);
						break;
					}
					switch (GetRasterizerState()) {
					case RasterizerState::CullBack:
						pID3D11DeviceContext->RSSetState(RenderStatePtr->GetCullBack());
						break;
					case RasterizerState::CullFront:
						pID3D11DeviceContext->RSSetState(RenderStatePtr->GetCullFront());
						break;
					case RasterizerState::CullNone:
						pID3D11DeviceContext->RSSetState(RenderStatePtr->GetCullNone());
						break;
					}
					//�`��
					pID3D11DeviceContext->DrawIndexed(m.m_IndexCount, m.m_StartIndex, 0);
				}
			}
		}
		Dev->InitializeStates();
	}
	void PNTStaticModelDraw::OnDraw() {
		if (GetOwnShadowActive()) {
			DrawWithShadow();
		}
		else {
			DrawNotShadow();
		}
	}


	//--------------------------------------------------------------------------------------
	//	struct PNTBoneModelDraw::Impl;
	//	�p�r: Impl�C�f�B�I��
	//--------------------------------------------------------------------------------------
	struct PNTBoneModelDraw::Impl {
		weak_ptr<MeshResource> m_MeshResource;	//���b�V�����\�[�X
		bool m_OwnShadowActive;
		//�V�F�[�_�ɓn���{�[���s��
		vector<Matrix4X4> m_LocalBonesMatrix;
		map<wstring, AnimationData> m_AnimationMap;
		wstring m_CurrentAnimeName;
		float m_CurrentAnimeTime;
		Impl() :
			m_OwnShadowActive(false),
			m_CurrentAnimeName(L""),
			m_CurrentAnimeTime(0)
		{}
		~Impl() {}
	};

	//--------------------------------------------------------------------------------------
	//	class PNTBoneModelDraw : public StaticBaseDraw;
	//	�p�r: PNTBoneModelDraw�`��R���|�[�l���g
	//--------------------------------------------------------------------------------------
	PNTBoneModelDraw::PNTBoneModelDraw(const shared_ptr<GameObject>& GameObjectPtr) :
		Base3DDraw(GameObjectPtr),
		pImpl(new Impl()) {
		//�p�C�v���C���X�e�[�g���f�t�H���g�̂RD
		SetBlendState(BlendState::Opaque);
		SetDepthStencilState(DepthStencilState::Default);
		SetRasterizerState(RasterizerState::CullBack);
		SetSamplerState(SamplerState::LinearClamp);
	}

	PNTBoneModelDraw::~PNTBoneModelDraw() {}

	void PNTBoneModelDraw::OnCreate() {

	}

	shared_ptr<MeshResource> PNTBoneModelDraw::GetMeshResource() const {
		//���b�V�����Ȃ���΃��^�[��
		if (pImpl->m_MeshResource.expired()) {
			throw BaseException(
				L"���b�V�����ݒ肳��Ă܂���",
				L"if (pImpl->m_MeshResource.expired())",
				L"PNTStaticModelDraw::GetMeshResource()"
			);
		}
		return pImpl->m_MeshResource.lock();
	}

	void PNTBoneModelDraw::SetMeshResource(const shared_ptr<MeshResource>& MeshRes) {
		if (!MeshRes->IsSkining() || MeshRes->GetBoneCount() == 0 || MeshRes->GetSampleCount() == 0) {
			throw BaseException(
				L"���b�V�����{�[�����b�V���ł͂���܂���",
				L"if (!MeshRes->IsSkining() || MeshRes->GetBoneCount() == 0 || MeshRes->GetSampleCount() == 0)",
				L"PNTBoneModelDraw::SetMeshResource()"
			);

		}
		//�擪�̃{�[�����̍s��ŏ�����
		pImpl->m_LocalBonesMatrix.resize(MeshRes->GetBoneCount());
		auto& SampleMatrixVec = MeshRes->GetSampleMatrixVec();
		for (UINT i = 0; i < pImpl->m_LocalBonesMatrix.size(); i++) {
			pImpl->m_LocalBonesMatrix[i] = SampleMatrixVec[i];
		}
		pImpl->m_MeshResource = MeshRes;
	}
	void PNTBoneModelDraw::SetMeshResource(const wstring& MeshKey) {
		auto MeshRes = App::GetApp()->GetResource<MeshResource>(MeshKey);
		if (!MeshRes->IsSkining() || MeshRes->GetBoneCount() == 0 || MeshRes->GetSampleCount() == 0) {
			throw BaseException(
				L"���b�V�����{�[�����b�V���ł͂���܂���",
				L"if (!MeshRes->IsSkining() || MeshRes->GetBoneCount() == 0 || MeshRes->GetSampleCount() == 0)",
				L"PNTBoneModelDraw::SetMeshResource()"
			);

		}
		//�擪�̃{�[�����̍s��ŏ�����
		pImpl->m_LocalBonesMatrix.resize(MeshRes->GetBoneCount());
		auto& SampleMatrixVec = MeshRes->GetSampleMatrixVec();
		for (UINT i = 0; i < pImpl->m_LocalBonesMatrix.size(); i++) {
			pImpl->m_LocalBonesMatrix[i] = SampleMatrixVec[i];
		}
		pImpl->m_MeshResource = MeshRes;
	}

	bool PNTBoneModelDraw::GetOwnShadowActive() const {
		return pImpl->m_OwnShadowActive;
	}
	bool PNTBoneModelDraw::IsOwnShadowActive() const {
		return pImpl->m_OwnShadowActive;
	}
	void PNTBoneModelDraw::SetOwnShadowActive(bool b) {
		pImpl->m_OwnShadowActive = b;
	}

	const vector< Matrix4X4 >* PNTBoneModelDraw::GetVecLocalBonesPtr() const {
		return &pImpl->m_LocalBonesMatrix;
	}


	void PNTBoneModelDraw::AddAnimation(const wstring& Name, int StartSample, int SampleLength, bool Loop,
		float SamplesParSecond) {
		if (Name == L"") {
			throw BaseException(
				L"�A�j���[�V���������󔒂ł�",
				L"if (Name == L\"\")",
				L"PNTBoneModelDraw::AddAnimation()"
			);
		}
		if (StartSample < 0 || SampleLength < 0) {
			throw BaseException(
				L"�J�n�T���v�����T���v������0�����ł�",
				L"if (StartSample < 0 || SampleLength < 0)",
				L"PNTBoneModelDraw::AddAnimation()"
			);
		}
		if (SamplesParSecond <= 0.0f) {
			throw BaseException(
				L"�T���v�����b��0�ȉ��ł�",
				L"if (SamplesParSecond <= 0.0f)",
				L"PNTBoneModelDraw::AddAnimation()"
			);
		}
		//�d���L�[������΍����ւ���
		AnimationData Data((UINT)StartSample, (UINT)SampleLength, Loop, SamplesParSecond);
		pImpl->m_AnimationMap[Name] = Data;
		if (pImpl->m_AnimationMap.size() == 1) {
			//1�����o�^���Ȃ�������A�J�����g�A�j���͊Y���A�j���ƂȂ�
			ChangeCurrentAnimation(Name, 0);
		}


	}

	void PNTBoneModelDraw::ChangeCurrentAnimation(const wstring& AnemationName, float StartTime) {
		if (AnemationName == L"") {
			throw BaseException(
				L"�A�j���[�V���������󔒂ł�",
				L"if (AnemationName == L\"\")",
				L"PNTBoneModelDraw::SetCurrentAnimation()"
			);
		}
		auto it = pImpl->m_AnimationMap.find(AnemationName);
		if (it != pImpl->m_AnimationMap.end()) {
			//�w��̖��O����������
			pImpl->m_CurrentAnimeName = AnemationName;
			pImpl->m_CurrentAnimeTime = StartTime;
			//�A�j���[�V�����͏I�����Ă��Ȃ�
			it->second.m_IsAnimeEnd = false;
		}
		else {
			//������Ȃ�
			throw BaseException(
				L"�w��̃A�j���[�V�����͓o�^����Ă܂���",
				AnemationName,
				L"PNTBoneModelDraw::SetCurrentAnimation()"
			);
		}
	}

	const wstring& PNTBoneModelDraw::GetCurrentAnimation() const {
		return pImpl->m_CurrentAnimeName;
	}

	bool PNTBoneModelDraw::UpdateAnimation(float ElapsedTime) {
		if (ElapsedTime < 0.0f) {
			throw BaseException(
				L"�A�j���[�V�����X�V�Ƀ}�C�i�X�͐ݒ�ł��܂���",
				L"if (ElapsedTime < 0.0f)",
				L"PNTBoneModelDraw::UpdateAnimation()"
			);
		}
		if (pImpl->m_CurrentAnimeName == L"") {
			//������Ȃ�
			throw BaseException(
				L"�J�����g�A�j���[�V�������ݒ肳��Ă܂���",
				L"if (pImpl->m_CurrentAnimeName == L\"\")",
				L"PNTBoneModelDraw::UpdateAnimation()"
			);
		}
		auto PtrMesh = GetMeshResource();
		UINT SampleCount = PtrMesh->GetSampleCount();
		auto& SampleMatrixVec = PtrMesh->GetSampleMatrixVec();
		UINT BoneCount = PtrMesh->GetBoneCount();
		auto& TgtAnimeData = pImpl->m_AnimationMap[pImpl->m_CurrentAnimeName];
		if (TgtAnimeData.m_StartSample >= SampleCount) {
			//�X�^�[�g�̃T���v�����Ō�̃T���v���ȍ~������
			TgtAnimeData.m_StartSample = SampleCount - 1;
			TgtAnimeData.m_SampleLength = 0;
			UINT UITgtSample = TgtAnimeData.m_StartSample;
			//�Ō�̃T���v����\��
			for (UINT i = 0; i < pImpl->m_LocalBonesMatrix.size(); i++) {
				pImpl->m_LocalBonesMatrix[i] = SampleMatrixVec[BoneCount * UITgtSample + i];
			}
			pImpl->m_CurrentAnimeTime = 0;
			if (TgtAnimeData.m_IsLoop) {
				TgtAnimeData.m_IsAnimeEnd = false;
				return false;
			}
			else {
				TgtAnimeData.m_IsAnimeEnd = true;
				return true;
			}
		}
		//���łɃA�j�����I�����Ă���
		if (TgtAnimeData.m_IsAnimeEnd) {
			//���݂̃��[�J���s����g�p
			return true;
		}
		//�J�����g�^�C�����X�V
		pImpl->m_CurrentAnimeTime += ElapsedTime;
		//�X�^�[�g�ʒu���v�Z
		auto FLOATTgtSample = (float)TgtAnimeData.m_StartSample + pImpl->m_CurrentAnimeTime * TgtAnimeData.m_SamplesParSecond;
		UINT UITgtSample = (UINT)FLOATTgtSample;
		UINT UILastSample = TgtAnimeData.m_StartSample + TgtAnimeData.m_SampleLength;
		if (UILastSample >= SampleCount) {
			UILastSample = SampleCount - 1;
		}
		if (UITgtSample >= UILastSample) {
			UITgtSample = UILastSample - 1;
			//�Ō�̃T���v����\��
			for (UINT i = 0; i < pImpl->m_LocalBonesMatrix.size(); i++) {
				pImpl->m_LocalBonesMatrix[i] = SampleMatrixVec[BoneCount * UITgtSample + i];
			}
			if (TgtAnimeData.m_IsLoop) {
				TgtAnimeData.m_IsAnimeEnd = false;
				//���[�v����̂ŃJ�����g�^�C����0�ɂ���
				pImpl->m_CurrentAnimeTime = 0;
				return false;
			}
			else {
				pImpl->m_CurrentAnimeTime = TgtAnimeData.m_SampleLength / TgtAnimeData.m_SamplesParSecond;
				TgtAnimeData.m_IsAnimeEnd = true;
				return true;
			}
		}
		else {
			//�T���v���ƃT���v���̊Ԃ̊������v�Z
			FLOATTgtSample -= (float)UITgtSample;
			UINT UINextSample = UITgtSample + 1;
			for (UINT i = 0; i < pImpl->m_LocalBonesMatrix.size(); i++) {
				InterpolationMatrix(
					SampleMatrixVec[BoneCount * UITgtSample + i],
					SampleMatrixVec[BoneCount * UINextSample + i],
					FLOATTgtSample, pImpl->m_LocalBonesMatrix[i]);
			}
			//�A�j���͏I����ĂȂ�
			return false;
		}
	}


	void PNTBoneModelDraw::InterpolationMatrix(const Matrix4X4& m1, const Matrix4X4& m2, float t, Matrix4X4& out) {
		Vector3 Scale1, Pos1;
		Quaternion Qt1;
		m1.Decompose(Scale1, Qt1, Pos1);
		Qt1.Normalize();

		Vector3 Scale2, Pos2;
		Quaternion Qt2;

		m2.Decompose(Scale2, Qt2, Pos2);
		Qt2.Normalize();

		Vector3 ScaleOut, PosOut;
		Quaternion QtOut;

		ScaleOut = Lerp::CalculateLerp(Scale1, Scale2, 0.0f, 1.0f, t, Lerp::Linear);
		PosOut = Lerp::CalculateLerp(Pos1, Pos2, 0.0f, 1.0f, t, Lerp::Linear);
		QtOut = QuaternionEX::Slerp(Qt1, Qt2, t);
		out.DefTransformation(ScaleOut, QtOut, PosOut);
	}


	void PNTBoneModelDraw::DrawWithShadow() {
		auto PtrStage = GetGameObject()->GetStage();
		if (!PtrStage) {
			return;
		}
		//���b�V�����Ȃ���Ε`�悵�Ȃ�
		auto MeshRes = GetMeshResource();
		if (!MeshRes) {
			throw BaseException(
				L"���b�V�����쐬����Ă��܂���",
				L"if (!MeshRes)",
				L"PNTBoneModelDraw::OnDraw()"
			);
		}
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pID3D11DeviceContext = Dev->GetD3DDeviceContext();
		auto RenderStatePtr = Dev->GetRenderState();

		auto GameObjectPtr = GetGameObject();
		auto PtrTrans = GetGameObject()->GetComponent<Transform>();
		//�s��̒�`
		Matrix4X4 World, ViewMat, ProjMat;
		//���[���h�s��̌���
		World = GetMeshToTransformMatrix() * PtrTrans->GetWorldMatrix();
		//�]�u����
		World.Transpose();
		//�J�����𓾂�
		auto CameraPtr = GameObjectPtr->OnGetDrawCamera();
		//�r���[�Ǝˉe�s��𓾂�
		ViewMat = CameraPtr->GetViewMatrix();
		//�]�u����
		ViewMat.Transpose();
		//�]�u����
		ProjMat = CameraPtr->GetProjMatrix();
		ProjMat.Transpose();


		//�R���X�^���g�o�b�t�@�̐ݒ�
		PNTBoneShadowConstantBuffer cb1;

		ZeroMemory(&cb1, sizeof(cb1));
		//�s��̐ݒ�(�]�u����)
		//�R���X�^���g�o�b�t�@�̐ݒ�
		cb1.World = World;
		cb1.View = ViewMat;
		cb1.Projection = ProjMat;

		//���C�e�B���O
		auto StageLight = GameObjectPtr->OnGetDrawLight();
		cb1.LightDir = StageLight.m_Directional;
		cb1.LightDir.w = 1.0f;

		Vector3 CalcLightDir = -1.0 * StageLight.m_Directional;
		Vector3 LightAt = CameraPtr->GetAt();
		Vector3 LightEye = CalcLightDir;
		LightEye *= Shadowmap::GetLightHeight();
		LightEye = LightAt + LightEye;

		cb1.LightPos = LightEye;
		cb1.LightPos.w = 1.0f;

		cb1.EyePos = CameraPtr->GetEye();
		cb1.EyePos.w = 1.0f;
		//���f���̓e�N�X�`���K�{
		cb1.ActiveFlg.x = 1;

		Matrix4X4 LightView, LightProj;
		//���C�g�̃r���[�Ǝˉe���v�Z
		LightView.LookAtLH(LightEye, LightAt, Vector3(0, 1.0f, 0));
		LightProj.OrthographicLH(Shadowmap::GetViewWidth(), Shadowmap::GetViewHeight(),
			Shadowmap::GetLightNear(), Shadowmap::GetLightFar());
		cb1.LightView = Matrix4X4EX::Transpose(LightView);
		cb1.LightProjection = Matrix4X4EX::Transpose(LightProj);

		//�{�[���̐ݒ�
		size_t BoneSz = pImpl->m_LocalBonesMatrix.size();
		UINT cb_count = 0;
		for (size_t b = 0; b < BoneSz; b++) {
			Matrix4X4 mat = pImpl->m_LocalBonesMatrix[b];
			mat.Transpose();
			cb1.Bones[cb_count] = ((XMMATRIX)mat).r[0];
			cb1.Bones[cb_count + 1] = ((XMMATRIX)mat).r[1];
			cb1.Bones[cb_count + 2] = ((XMMATRIX)mat).r[2];
			cb_count += 3;
		}


		//�V���h�E�}�b�v�̃��\�[�X�r���[���擾
		//�V���h�E�}�b�v�̃����_���[�^�[�Q�b�g
		auto ShadoumapPtr = Dev->GetShadowMapRenderTarget();
		ID3D11ShaderResourceView* pShadowSRV = ShadoumapPtr->GetShaderResourceView();

		auto MeshPtr = GetMeshResource();
		auto& MatVec = MeshPtr->GetMaterialExVec();

		//�V�F�[�_�̐ݒ�
		bool IsShadowmap = false;
		if (GameObjectPtr->GetComponent<Shadowmap>(false)) {
			//�V���h�E�}�b�v������Ύ��ȉe�h�~�p�̃s�N�Z���V�F�[�_
			pID3D11DeviceContext->VSSetShader(VSPNTBoneShadow::GetPtr()->GetShader(), nullptr, 0);
			pID3D11DeviceContext->PSSetShader(PSPNTStaticShadow2::GetPtr()->GetShader(), nullptr, 0);

			IsShadowmap = true;
		}
		else {
			pID3D11DeviceContext->VSSetShader(VSPNTBoneShadow::GetPtr()->GetShader(), nullptr, 0);
			pID3D11DeviceContext->PSSetShader(PSPNTStaticShadow::GetPtr()->GetShader(), nullptr, 0);
		}

		//�C���v�b�g���C�A�E�g�̐ݒ�
		pID3D11DeviceContext->IASetInputLayout(VSPNTBoneShadow::GetPtr()->GetInputLayout());

		//�X�g���C�h�ƃI�t�Z�b�g
		UINT stride = sizeof(VertexPositionNormalTextureSkinning);
		UINT offset = 0;
		//���_�o�b�t�@�̐ݒ�
		pID3D11DeviceContext->IASetVertexBuffers(0, 1, MeshPtr->GetVertexBuffer().GetAddressOf(), &stride, &offset);
		//�C���f�b�N�X�o�b�t�@�̃Z�b�g
		pID3D11DeviceContext->IASetIndexBuffer(MeshPtr->GetIndexBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);

		//�`����@�i3�p�`�j
		pID3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//�f�v�X�X�e���V��
		switch (GetDepthStencilState()) {
		case DepthStencilState::None:
			pID3D11DeviceContext->OMSetDepthStencilState(RenderStatePtr->GetDepthNone(), 0);
			break;
		case DepthStencilState::Default:
			pID3D11DeviceContext->OMSetDepthStencilState(RenderStatePtr->GetDepthDefault(), 0);
			break;
		case DepthStencilState::Read:
			pID3D11DeviceContext->OMSetDepthStencilState(RenderStatePtr->GetDepthRead(), 0);
			break;
		}
		//�T���v���[

		//null�ɏ�����
		ID3D11SamplerState* pSampler = nullptr;
		switch (GetSamplerState()) {
		case SamplerState::SamplerNone:
			break;
		case SamplerState::PointWrap:
			pSampler = RenderStatePtr->GetPointWrap();
			break;
		case SamplerState::PointClamp:
			pSampler = RenderStatePtr->GetPointClamp();
			break;
		case SamplerState::LinearWrap:
			pSampler = RenderStatePtr->GetLinearWrap();
			break;
		case SamplerState::LinearClamp:
			pSampler = RenderStatePtr->GetLinearClamp();
			break;
		case SamplerState::AnisotropicWrap:
			pSampler = RenderStatePtr->GetAnisotropicWrap();
			break;
		case SamplerState::AnisotropicClamp:
			pSampler = RenderStatePtr->GetAnisotropicClamp();
			break;
		case SamplerState::ComparisonLinear:
			pSampler = RenderStatePtr->GetComparisonLinear();
			break;
		}
		//�T���v���[��ݒ�
		pID3D11DeviceContext->PSSetSamplers(0, 1, &pSampler);
		//�e�̃V�F�[�_���\�[�X
		pID3D11DeviceContext->PSSetShaderResources(1, 1, &pShadowSRV);
		pSampler = RenderStatePtr->GetComparisonLinear();
		//�e�̃T���v���[��ݒ�
		pID3D11DeviceContext->PSSetSamplers(1, 1, &pSampler);

		for (auto& m : MatVec) {
			cb1.Emissive = m.m_Emissive;
			cb1.Diffuse = m.m_Diffuse;
			//�R���X�^���g�o�b�t�@�̍X�V
			ID3D11Buffer* pConstantBuffer = CBPNTBoneShadow::GetPtr()->GetBuffer();
			pID3D11DeviceContext->UpdateSubresource(pConstantBuffer, 0, nullptr, &cb1, 0, 0);
			pID3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
			pID3D11DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);
			//�e�N�X�`����ݒ�
			pID3D11DeviceContext->PSSetShaderResources(0, 1, m.m_TextureResource->GetShaderResourceView().GetAddressOf());
			if (GetRasterizerState() == RasterizerState::Wireframe) {
				pID3D11DeviceContext->OMSetBlendState(RenderStatePtr->GetOpaque(), nullptr, 0xffffffff);
				pID3D11DeviceContext->RSSetState(RenderStatePtr->GetWireframe());
				//�`��
				pID3D11DeviceContext->DrawIndexed(m.m_IndexCount, m.m_StartIndex, 0);
			}
			else {
				//�u�����h�X�e�[�g�ƃ��X�^���C�U��ݒ肵�ĕ`��
				//�����A�����`��Ȃ�AlphaBlendEx�ɐݒ肵�A�����łȂ���΁A�w��ɏ]���B
				if (GameObjectPtr->GetAlphaActive()) {
					pID3D11DeviceContext->OMSetBlendState(RenderStatePtr->GetAlphaBlendEx(), nullptr, 0xffffffff);
					//���X�^���C�U�X�e�[�g
					pID3D11DeviceContext->RSSetState(RenderStatePtr->GetCullFront());
					//�`��
					pID3D11DeviceContext->DrawIndexed(m.m_IndexCount, m.m_StartIndex, 0);
					//���X�^���C�U�X�e�[�g
					pID3D11DeviceContext->RSSetState(RenderStatePtr->GetCullBack());
					//�`��
					pID3D11DeviceContext->DrawIndexed(m.m_IndexCount, m.m_StartIndex, 0);
				}
				else {
					switch (GetBlendState()) {
					case BlendState::Opaque:
						pID3D11DeviceContext->OMSetBlendState(RenderStatePtr->GetOpaque(), nullptr, 0xffffffff);
						break;
					case BlendState::AlphaBlend:
						pID3D11DeviceContext->OMSetBlendState(RenderStatePtr->GetAlphaBlendEx(), nullptr, 0xffffffff);
						break;
					case BlendState::Additive:
						pID3D11DeviceContext->OMSetBlendState(RenderStatePtr->GetAdditive(), nullptr, 0xffffffff);
						break;
					case BlendState::NonPremultiplied:
						pID3D11DeviceContext->OMSetBlendState(RenderStatePtr->GetNonPremultiplied(), nullptr, 0xffffffff);
						break;
					}
					switch (GetRasterizerState()) {
					case RasterizerState::CullBack:
						pID3D11DeviceContext->RSSetState(RenderStatePtr->GetCullBack());
						break;
					case RasterizerState::CullFront:
						pID3D11DeviceContext->RSSetState(RenderStatePtr->GetCullFront());
						break;
					case RasterizerState::CullNone:
						pID3D11DeviceContext->RSSetState(RenderStatePtr->GetCullNone());
						break;
					}
					//�`��
					pID3D11DeviceContext->DrawIndexed(m.m_IndexCount, m.m_StartIndex, 0);
				}
			}
		}
		Dev->InitializeStates();

	}

	void PNTBoneModelDraw::DrawNotShadow() {
		auto PtrStage = GetGameObject()->GetStage();
		if (!PtrStage) {
			return;
		}
		//���b�V�����Ȃ���Ε`�悵�Ȃ�
		auto MeshRes = GetMeshResource();
		if (!MeshRes) {
			throw BaseException(
				L"���b�V�����쐬����Ă��܂���",
				L"if (!MeshRes)",
				L"PNTBoneModelDraw::OnDraw()"
			);
		}
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pID3D11DeviceContext = Dev->GetD3DDeviceContext();
		auto RenderStatePtr = Dev->GetRenderState();

		auto GameObjectPtr = GetGameObject();
		auto PtrTrans = GetGameObject()->GetComponent<Transform>();
		//�s��̒�`
		Matrix4X4 World, ViewMat, ProjMat;
		//���[���h�s��̌���
		World = GetMeshToTransformMatrix() * PtrTrans->GetWorldMatrix();
		//�]�u����
		World.Transpose();
		//�J�����𓾂�
		auto CameraPtr = GameObjectPtr->OnGetDrawCamera();
		//�r���[�Ǝˉe�s��𓾂�
		ViewMat = CameraPtr->GetViewMatrix();
		//�]�u����
		ViewMat.Transpose();
		//�]�u����
		ProjMat = CameraPtr->GetProjMatrix();
		ProjMat.Transpose();

		//�R���X�^���g�o�b�t�@�̐ݒ�
		PNTBoneConstantBuffer cb1;
		ZeroMemory(&cb1, sizeof(cb1));
		//�s��̐ݒ�(�]�u����)
		//�R���X�^���g�o�b�t�@�̐ݒ�
		cb1.World = World;
		cb1.View = ViewMat;
		cb1.Projection = ProjMat;
		auto StageLight = GameObjectPtr->OnGetDrawLight();
		cb1.LightDir = StageLight.m_Directional;
		cb1.LightDir.w = 1.0f;

		//�{�[���̐ݒ�
		size_t BoneSz = pImpl->m_LocalBonesMatrix.size();
		UINT cb_count = 0;
		for (size_t b = 0; b < BoneSz; b++) {
			Matrix4X4 mat = pImpl->m_LocalBonesMatrix[b];
			mat.Transpose();
			cb1.Bones[cb_count] = ((XMMATRIX)mat).r[0];
			cb1.Bones[cb_count + 1] = ((XMMATRIX)mat).r[1];
			cb1.Bones[cb_count + 2] = ((XMMATRIX)mat).r[2];
			cb_count += 3;
		}

		auto MeshPtr = GetMeshResource();
		auto& MatVec = MeshPtr->GetMaterialExVec();

		//�V�F�[�_�̐ݒ�
		pID3D11DeviceContext->VSSetShader(VSPNTBone::GetPtr()->GetShader(), nullptr, 0);
		pID3D11DeviceContext->PSSetShader(PSPNTStatic::GetPtr()->GetShader(), nullptr, 0);
		//�C���v�b�g���C�A�E�g�̐ݒ�
		pID3D11DeviceContext->IASetInputLayout(VSPNTBone::GetPtr()->GetInputLayout());

		//�X�g���C�h�ƃI�t�Z�b�g
		UINT stride = sizeof(VertexPositionNormalTextureSkinning);
		UINT offset = 0;
		//���_�o�b�t�@�̐ݒ�
		pID3D11DeviceContext->IASetVertexBuffers(0, 1, MeshPtr->GetVertexBuffer().GetAddressOf(), &stride, &offset);
		//�C���f�b�N�X�o�b�t�@�̃Z�b�g
		pID3D11DeviceContext->IASetIndexBuffer(MeshPtr->GetIndexBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);

		//�`����@�i3�p�`�j
		pID3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//�f�v�X�X�e���V��
		switch (GetDepthStencilState()) {
		case DepthStencilState::None:
			pID3D11DeviceContext->OMSetDepthStencilState(RenderStatePtr->GetDepthNone(), 0);
			break;
		case DepthStencilState::Default:
			pID3D11DeviceContext->OMSetDepthStencilState(RenderStatePtr->GetDepthDefault(), 0);
			break;
		case DepthStencilState::Read:
			pID3D11DeviceContext->OMSetDepthStencilState(RenderStatePtr->GetDepthRead(), 0);
			break;
		}
		//�T���v���[
		//null�ɏ�����
		ID3D11SamplerState* pSampler = nullptr;
		switch (GetSamplerState()) {
		case SamplerState::SamplerNone:
			break;
		case SamplerState::PointWrap:
			pSampler = RenderStatePtr->GetPointWrap();
			break;
		case SamplerState::PointClamp:
			pSampler = RenderStatePtr->GetPointClamp();
			break;
		case SamplerState::LinearWrap:
			pSampler = RenderStatePtr->GetLinearWrap();
			break;
		case SamplerState::LinearClamp:
			pSampler = RenderStatePtr->GetLinearClamp();
			break;
		case SamplerState::AnisotropicWrap:
			pSampler = RenderStatePtr->GetAnisotropicWrap();
			break;
		case SamplerState::AnisotropicClamp:
			pSampler = RenderStatePtr->GetAnisotropicClamp();
			break;
		case SamplerState::ComparisonLinear:
			pSampler = RenderStatePtr->GetComparisonLinear();
			break;
		}
		//�T���v���[��ݒ�
		pID3D11DeviceContext->PSSetSamplers(0, 1, &pSampler);

		for (auto& m : MatVec) {
			cb1.Emissive = m.m_Emissive;
			cb1.Diffuse = m.m_Diffuse;
			//�R���X�^���g�o�b�t�@�̍X�V
			ID3D11Buffer* pConstantBuffer = CBPNTBone::GetPtr()->GetBuffer();
			pID3D11DeviceContext->UpdateSubresource(pConstantBuffer, 0, nullptr, &cb1, 0, 0);
			pID3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
			pID3D11DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);
			//�e�N�X�`����ݒ�
			pID3D11DeviceContext->PSSetShaderResources(0, 1, m.m_TextureResource->GetShaderResourceView().GetAddressOf());
			if (GetRasterizerState() == RasterizerState::Wireframe) {
				pID3D11DeviceContext->OMSetBlendState(RenderStatePtr->GetOpaque(), nullptr, 0xffffffff);
				pID3D11DeviceContext->RSSetState(RenderStatePtr->GetWireframe());
				//�`��
				pID3D11DeviceContext->DrawIndexed(m.m_IndexCount, m.m_StartIndex, 0);
			}
			else {
				//�u�����h�X�e�[�g�ƃ��X�^���C�U��ݒ肵�ĕ`��
				//�����A�����`��Ȃ�AlphaBlendEx�ɐݒ肵�A�����łȂ���΁A�w��ɏ]���B
				if (GameObjectPtr->GetAlphaActive()) {
					pID3D11DeviceContext->OMSetBlendState(RenderStatePtr->GetAlphaBlendEx(), nullptr, 0xffffffff);
					//���X�^���C�U�X�e�[�g
					pID3D11DeviceContext->RSSetState(RenderStatePtr->GetCullFront());
					//�`��
					pID3D11DeviceContext->DrawIndexed(m.m_IndexCount, m.m_StartIndex, 0);
					//���X�^���C�U�X�e�[�g
					pID3D11DeviceContext->RSSetState(RenderStatePtr->GetCullBack());
					//�`��
					pID3D11DeviceContext->DrawIndexed(m.m_IndexCount, m.m_StartIndex, 0);
				}
				else {
					switch (GetBlendState()) {
					case BlendState::Opaque:
						pID3D11DeviceContext->OMSetBlendState(RenderStatePtr->GetOpaque(), nullptr, 0xffffffff);
						break;
					case BlendState::AlphaBlend:
						pID3D11DeviceContext->OMSetBlendState(RenderStatePtr->GetAlphaBlendEx(), nullptr, 0xffffffff);
						break;
					case BlendState::Additive:
						pID3D11DeviceContext->OMSetBlendState(RenderStatePtr->GetAdditive(), nullptr, 0xffffffff);
						break;
					case BlendState::NonPremultiplied:
						pID3D11DeviceContext->OMSetBlendState(RenderStatePtr->GetNonPremultiplied(), nullptr, 0xffffffff);
						break;
					}
					switch (GetRasterizerState()) {
					case RasterizerState::CullBack:
						pID3D11DeviceContext->RSSetState(RenderStatePtr->GetCullBack());
						break;
					case RasterizerState::CullFront:
						pID3D11DeviceContext->RSSetState(RenderStatePtr->GetCullFront());
						break;
					case RasterizerState::CullNone:
						pID3D11DeviceContext->RSSetState(RenderStatePtr->GetCullNone());
						break;
					}
					//�`��
					pID3D11DeviceContext->DrawIndexed(m.m_IndexCount, m.m_StartIndex, 0);
				}
			}
		}
		Dev->InitializeStates();
	}
	void PNTBoneModelDraw::OnDraw() {
		if (GetOwnShadowActive()) {
			DrawWithShadow();
		}
		else {
			DrawNotShadow();
		}
	}


}
//end basecross
