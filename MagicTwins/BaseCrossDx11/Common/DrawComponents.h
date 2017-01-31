/*!
@file DrawComponents.h
@brief �`��R���|�[�l���g
*/
#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	/*!
	@brief	�r���[�|�[�g�ƃV�T�[��`�ݒ�
	@param[in]	vp	�r���[�|�[�g
	@return	�Ȃ�
	*/
	//--------------------------------------------------------------------------------------
	inline void RsSetViewport(const Viewport& vp) {
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pID3D11DeviceContext = Dev->GetD3DDeviceContext();
		D3D11_VIEWPORT vp11;
		vp11.Height = vp.Height;
		vp11.Width = vp.Width;
		vp11.MinDepth = vp.MinDepth;
		vp11.MaxDepth = vp.MaxDepth;
		vp11.TopLeftX = vp.TopLeftX;
		vp11.TopLeftY = vp.TopLeftY;
		pID3D11DeviceContext->RSSetViewports(1, &vp11);
		CD3D11_RECT rect(
			(LONG)vp11.TopLeftX,
			(LONG)vp11.TopLeftY,
			(LONG)vp11.TopLeftX + (LONG)vp11.Width,
			(LONG)vp11.TopLeftY + (LONG)vp11.Height
		);
		pID3D11DeviceContext->RSSetScissorRects(1, &rect);
	}



	//--------------------------------------------------------------------------------------
	///	Shadow�R���X�^���g�o�b�t�@�\����
	//--------------------------------------------------------------------------------------
	struct ShadowConstantBuffer
	{
		/// ���[���h�s��
		XMMATRIX mWorld;
		/// �r���[�s��
		XMMATRIX mView;
		/// �ˉe�s��
		XMMATRIX mProj;
		/// Bone�p
		XMVECTOR Bones[3 * 72];
		ShadowConstantBuffer() {
			memset(this, 0, sizeof(ShadowConstantBuffer));
		};
	};
	DECLARE_DX11_CONSTANT_BUFFER(CBShadow, ShadowConstantBuffer)
	DECLARE_DX11_VERTEX_SHADER(VSShadowmap, VertexPositionNormalTexture)
	DECLARE_DX11_VERTEX_SHADER(VSShadowmapBone, VertexPositionNormalTextureSkinning)


	//--------------------------------------------------------------------------------------
	///	�X�v���C�g�p�R���X�^���g�o�b�t�@�\����
	//--------------------------------------------------------------------------------------
	struct SpriteConstantBuffer
	{
		/// ���[���h�s��
		Matrix4X4 World;
		/// �G�~�b�V�u�F
		Color4 Emissive;
		/// �f�t���[�Y�F
		Color4 Diffuse;
		SpriteConstantBuffer() {
			memset(this, 0, sizeof(SpriteConstantBuffer));
			Diffuse = Color4(1.0f, 1.0f, 1.0f, 1.0f);
		};
	};
	DECLARE_DX11_CONSTANT_BUFFER(CBSprite, SpriteConstantBuffer)
	//PCSprite
	DECLARE_DX11_VERTEX_SHADER(VSPCSprite, VertexPositionColor)
	DECLARE_DX11_PIXEL_SHADER(PSPCSprite)
	//PTSprite
	DECLARE_DX11_VERTEX_SHADER(VSPTSprite, VertexPositionTexture)
	DECLARE_DX11_PIXEL_SHADER(PSPTSprite)
	//PCTSprite
	DECLARE_DX11_VERTEX_SHADER(VSPCTSprite, VertexPositionColorTexture)
	DECLARE_DX11_PIXEL_SHADER(PSPCTSprite)


	//--------------------------------------------------------------------------------------
	///	static�n�R���X�^���g�o�b�t�@�\����
	//--------------------------------------------------------------------------------------
	struct StaticConstantBuffer
	{
		/// ���[���h�s��
		Matrix4X4 World;
		/// �r���[�s��
		Matrix4X4 View;
		/// �ˉe�s��
		Matrix4X4 Projection;
		/// �G�~�b�V�u�F
		Color4 Emissive;
		/// �f�t���[�Y�F
		Color4 Diffuse;
		StaticConstantBuffer() {
			memset(this, 0, sizeof(StaticConstantBuffer));
			Diffuse = Color4(1.0f, 1.0f, 1.0f, 1.0f);
		};
	};
	DECLARE_DX11_CONSTANT_BUFFER(CBStatic, StaticConstantBuffer)
	//PCStatic
	DECLARE_DX11_VERTEX_SHADER(VSPCStatic, VertexPositionColor)
	DECLARE_DX11_PIXEL_SHADER(PSPCStatic)
	//PTStatic
	DECLARE_DX11_VERTEX_SHADER(VSPTStatic, VertexPositionTexture)
	DECLARE_DX11_PIXEL_SHADER(PSPTStatic)
	///PCTStatic
	DECLARE_DX11_VERTEX_SHADER(VSPCTInstance, VertexPositionColorTextureMatrix)
	DECLARE_DX11_VERTEX_SHADER(VSPCTStatic, VertexPositionColorTexture)
	DECLARE_DX11_PIXEL_SHADER(PSPCTStatic)

	//--------------------------------------------------------------------------------------
	///	���C�e�B���O���g�p����static�n�R���X�^���g�o�b�t�@�\����
	//--------------------------------------------------------------------------------------
	struct StaticLightingConstantBuffer
	{
		/// ���[���h�s��
		Matrix4X4 World;
		/// �r���[�s��
		Matrix4X4 View;
		/// �ˉe�s��
		Matrix4X4 Projection;
		/// ���C�C�g����
		Vector4 LightDir;
		/// �G�~�b�V�u�F
		Color4 Emissive;
		/// �f�t���[�Y�F
		Color4 Diffuse;
		StaticLightingConstantBuffer() {
			memset(this, 0, sizeof(StaticLightingConstantBuffer));
			Diffuse = Color4(1.0f, 1.0f, 1.0f, 1.0f);
		};
	};

	DECLARE_DX11_CONSTANT_BUFFER(CBStaticLighting, StaticLightingConstantBuffer)
	DECLARE_DX11_VERTEX_SHADER(VSPNStatic, VertexPositionNormal)
	DECLARE_DX11_VERTEX_SHADER(VSPNTStatic, VertexPositionNormalTexture)
	DECLARE_DX11_VERTEX_SHADER(VSPNTStaticMidium, VertexPositionNormalTexture)
	DECLARE_DX11_PIXEL_SHADER(PSPNStatic)
	DECLARE_DX11_PIXEL_SHADER(PSPNTStatic)
	DECLARE_DX11_PIXEL_SHADER(PSPNTStaticNoTex)
	DECLARE_DX11_PIXEL_SHADER(PSPNTStaticMidium)
	DECLARE_DX11_PIXEL_SHADER(PSPNTStaticMidiumNoTex)

	//--------------------------------------------------------------------------------------
	///	���A�����C�e�B���O���g�p����static�n�R���X�^���g�o�b�t�@�\����
	//--------------------------------------------------------------------------------------
	struct StaticRealLightingConstantBuffer
	{
		/// ���[���h�s��
		Matrix4X4 World;
		/// �r���[�s��
		Matrix4X4 View;
		/// �ˉe�s��
		Matrix4X4 Projection;
		/// ���C�C�g����
		Vector4 LightDir;
		/// �G�~�b�V�u�F
		Color4 Emissive;
		/// �f�t���[�Y�F
		Color4 Diffuse;
		/// Eye�̈ʒu
		Vector4 EyePosition;
		StaticRealLightingConstantBuffer() {
			memset(this, 0, sizeof(StaticRealLightingConstantBuffer));
			Diffuse = Color4(1.0f, 1.0f, 1.0f, 1.0f);
		};
	};
	DECLARE_DX11_CONSTANT_BUFFER(CBStaticRealLighting, StaticRealLightingConstantBuffer)
	DECLARE_DX11_VERTEX_SHADER(VSPNTStaticReal, VertexPositionNormalTexture)
	DECLARE_DX11_PIXEL_SHADER(PSPNTStaticReal)
	DECLARE_DX11_PIXEL_SHADER(PSPNTStaticRealNoTex)



	//--------------------------------------------------------------------------------------
	///	�e�t��static�n�R���X�^���g�o�b�t�@�\����
	//--------------------------------------------------------------------------------------
	struct PNTStaticShadowConstantBuffer
	{
		/// ���[���h�s��
		Matrix4X4 World;
		/// �r���[�s��
		Matrix4X4 View;
		/// �ˉe�s��
		Matrix4X4 Projection;
		/// ���C�C�g����
		Vector4 LightDir;
		/// �G�~�b�V�u�F
		Color4 Emissive;
		/// �f�t���[�Y�F
		Color4 Diffuse;
		/// ���C�g�ʒu
		Vector4 LightPos;
		/// Eye�̈ʒu
		Vector4 EyePos;
		/// �ėp�t���O
		XMUINT4 ActiveFlg;
		/// ���C�g�r���[�s��
		Matrix4X4 LightView;
		/// ���C�g�ˉe�s��
		Matrix4X4 LightProjection;
		PNTStaticShadowConstantBuffer() {
			memset(this, 0, sizeof(PNTStaticShadowConstantBuffer));
			Diffuse = Color4(1.0f, 1.0f, 1.0f, 1.0f);
		};
	};
	DECLARE_DX11_CONSTANT_BUFFER(CBPNTStaticShadow, PNTStaticShadowConstantBuffer)
	DECLARE_DX11_VERTEX_SHADER(VSPNTStaticShadow, VertexPositionNormalTexture)
	DECLARE_DX11_PIXEL_SHADER(PSPNTStaticShadow)
	DECLARE_DX11_PIXEL_SHADER(PSPNTStaticShadow2)


	//--------------------------------------------------------------------------------------
	///	Bone�t�R���X�^���g�o�b�t�@�\����
	//--------------------------------------------------------------------------------------
	struct PNTBoneConstantBuffer
	{
		/// ���[���h�s��
		Matrix4X4 World;
		/// �r���[�s��
		Matrix4X4 View;
		/// �ˉe�s��
		Matrix4X4 Projection;
		/// ���C�C�g����
		Vector4 LightDir;
		/// �G�~�b�V�u�F
		Color4 Emissive;
		/// �f�t���[�Y�F
		Color4 Diffuse;
		/// Bone�z��
		XMVECTOR Bones[3 * 72];
		PNTBoneConstantBuffer() {
			memset(this, 0, sizeof(PNTBoneConstantBuffer));
		};
	};

	DECLARE_DX11_CONSTANT_BUFFER(CBPNTBone, PNTBoneConstantBuffer)
	DECLARE_DX11_VERTEX_SHADER(VSPNTBone, VertexPositionNormalTextureSkinning)
	DECLARE_DX11_VERTEX_SHADER(VSPNTBoneMidium, VertexPositionNormalTextureSkinning)

	//--------------------------------------------------------------------------------------
	///	���A�����C�e�B���O���g�p����Bone�t�R���X�^���g�o�b�t�@�\����
	//--------------------------------------------------------------------------------------
	struct PNTBoneRealLightingConstantBuffer
	{
		/// ���[���h�s��
		Matrix4X4 World;
		/// �r���[�s��
		Matrix4X4 View;
		/// �ˉe�s��
		Matrix4X4 Projection;
		/// ���C�C�g����
		Vector4 LightDir;
		/// �G�~�b�V�u�F
		Color4 Emissive;
		/// �f�t���[�Y�F
		Color4 Diffuse;
		/// Eye�̈ʒu
		Vector4 EyePosition;
		/// Bone�z��
		XMVECTOR Bones[3 * 72];
		PNTBoneRealLightingConstantBuffer() {
			memset(this, 0, sizeof(PNTBoneRealLightingConstantBuffer));
			Diffuse = Color4(1.0f, 1.0f, 1.0f, 1.0f);
		};
	};
	DECLARE_DX11_CONSTANT_BUFFER(CBPNTBoneRealLighting, PNTBoneRealLightingConstantBuffer)
	DECLARE_DX11_VERTEX_SHADER(VSPNTBoneReal, VertexPositionNormalTextureSkinning)



	//--------------------------------------------------------------------------------------
	///	�e��Bone�t�R���X�^���g�o�b�t�@�\����
	//--------------------------------------------------------------------------------------
	struct PNTBoneShadowConstantBuffer
	{
		/// ���[���h�s��
		Matrix4X4 World;
		/// �r���[�s��
		Matrix4X4 View;
		/// �ˉe�s��
		Matrix4X4 Projection;
		/// ���C�C�g����
		Vector4 LightDir;
		/// �G�~�b�V�u�F
		Color4 Emissive;
		/// �f�t���[�Y�F
		Color4 Diffuse;
		/// ���C�g�ʒu
		Vector4 LightPos;
		/// Eye�̈ʒu
		Vector4 EyePos;
		/// �e�N�X�`��=x���A�N�e�B�u���ǂ���
		XMUINT4 ActiveFlg;
		/// ���C�g�r���[�s��
		Matrix4X4 LightView;
		/// ���C�g�ˉe�s��
		Matrix4X4 LightProjection;
		/// Bone�z��
		XMVECTOR Bones[3 * 72];
		PNTBoneShadowConstantBuffer() {
			memset(this, 0, sizeof(PNTBoneShadowConstantBuffer));
		};
	};
	DECLARE_DX11_CONSTANT_BUFFER(CBPNTBoneShadow, PNTBoneShadowConstantBuffer)
	DECLARE_DX11_VERTEX_SHADER(VSPNTBoneShadow, VertexPositionNormalTextureSkinning)



	class GameObject;

	//--------------------------------------------------------------------------------------
	///	�`��R���|�[�l���g�̐e�N���X
	//--------------------------------------------------------------------------------------
	class DrawComponent : public Component {
	protected:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v���e�N�g�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		DrawComponent(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v���e�N�g�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~DrawComponent();
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�u�����h�X�e�[�g�̎擾
		@return	�u�����h�X�e�[�g
		*/
		//--------------------------------------------------------------------------------------
		BlendState GetBlendState() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�v�X�X�e���V���X�e�[�g�̎擾
		@return	�f�v�X�X�e���V���X�e�[�g
		*/
		//--------------------------------------------------------------------------------------
		DepthStencilState GetDepthStencilState() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���X�^���C�U�X�e�[�g�̎擾
		@return	���X�^���C�U�X�e�[�g
		*/
		//--------------------------------------------------------------------------------------
		RasterizerState GetRasterizerState() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�T���v���[�X�e�[�g�̎擾
		@return	�T���v���[�X�e�[�g
		*/
		//--------------------------------------------------------------------------------------
		SamplerState GetSamplerState() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�u�����h�X�e�[�g�̐ݒ�
		@param[in]	state	�u�����h�X�e�[�g
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetBlendState(const BlendState state);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�u�����h�X�e�[�g�̃f�o�C�X�ւ̐ݒ�B
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetDeviceBlendState();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�v�X�X�e���V���X�e�[�g�̐ݒ�
		@param[in]	state	�f�v�X�X�e���V���X�e�[�g
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetDepthStencilState(const DepthStencilState state);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�v�X�X�e���V���X�e�[�g�̃f�o�C�X�ւ̐ݒ�
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetDeviceDepthStencilState();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���X�^���C�U�X�e�[�g�̐ݒ�
		@param[in]	state	���X�^���C�U�X�e�[�g
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetRasterizerState(const RasterizerState state);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���X�^���C�U�X�e�[�g�̃f�o�C�X�ւ̐ݒ�
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetDeviceRasterizerState();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�T���v���[�X�e�[�g�̐ݒ�
		@param[in]	state	�T���v���[�X�e�[�g
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetSamplerState(const SamplerState state);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�T���v���[�X�e�[�g�̃f�o�C�X�ւ̐ݒ�
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetDeviceSamplerState();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���b�V���ƃ��[���h�s��̊Ԃ�⊮����s��̎擾<br />
		���b�V���̃T�C�Y������A���S�̈ʒu���Q�[���I�u�W�F�N�g�̃��[���h�s��ƍ��ق�����ꍇ�A<br />
		���̊Ԃ�⊮����s���ݒ�ł���B
		@return	���b�V���ƃ��[���h�s��̊Ԃ�⊮����s��
		*/
		//--------------------------------------------------------------------------------------
		const Matrix4X4& GetMeshToTransformMatrix() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���b�V���ƃ��[���h�s��̊Ԃ�⊮����s��̎擾<br />
		���b�V���̃T�C�Y������A���S�̈ʒu���Q�[���I�u�W�F�N�g�̃��[���h�s��ƍ��ق�����ꍇ�A<br />
		���̊Ԃ�⊮����s���ݒ�ł���B
		@param[in]	Mat	�ݒ肷��s��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetMeshToTransformMatrix(const Matrix4X4& Mat);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�e�I�u�W�F�N�g���ƂɃ{�[�����������Ă����|�C���^<br />
		�V���h�E�}�b�v�Ȃǂ���Q�Ƃł���悤�ɉ��z�֐��ɂ���<br />
		�h���N���X�Ń{�[������������ꍇ�͑��d��`����
		@return	�{�[���s��̔z��̃|�C���^
		*/
		//--------------------------------------------------------------------------------------
		virtual const vector< Matrix4X4 >* GetVecLocalBonesPtr() const { return nullptr; }
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};

	//--------------------------------------------------------------------------------------
	//	�V���h�E�}�b�v�R���|�[�l���g�i�O�����p�j
	//--------------------------------------------------------------------------------------
	class Shadowmap : public DrawComponent {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit Shadowmap(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Shadowmap();
		//�A�N�Z�T
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���C�g�̍����𓾂�
		@return	���C�g�̍���
		*/
		//--------------------------------------------------------------------------------------
		static float GetLightHeight();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���C�g��Near�l�𓾂�
		@return	���C�g��Near�l
		*/
		//--------------------------------------------------------------------------------------
		static float GetLightNear();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���C�g��Far�l�𓾂�
		@return	���C�g��Far�l
		*/
		//--------------------------------------------------------------------------------------
		static float GetLightFar();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�r���[�̕��𓾂�
		@return	�r���[�̕�
		*/
		//--------------------------------------------------------------------------------------
		static float GetViewWidth();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�r���[�̍����𓾂�
		@return	�r���[�̍���
		*/
		//--------------------------------------------------------------------------------------
		static float GetViewHeight();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���C�g�̍�����ݒ肷��
		@param[in]	f	����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		static void SetLightHeight(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���C�g��Near�l��ݒ肷��
		@param[in]	f	Near�l
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		static void SetLightNear(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���C�g��Far�l��ݒ肷��
		@param[in]	f	Far�l
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		static void SetLightFar(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�r���[�̕���ݒ肷��
		@param[in]	f	�r���[�̕�
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		static void SetViewWidth(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�r���[�̍�����ݒ肷��
		@param[in]	f	�r���[�̍���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		static void SetViewHeight(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�r���[�̕��y�э����𓯂��l�ɐݒ肷��
		@param[in]	f	�r���[�̕��y�э����i���l�j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		static void SetViewSize(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���b�V�����\�[�X�𓾂�
		@param[in]	ExceptionActive	�G���[���ɗ�O���������邩�ǂ���
		@return	���b�V�����\�[�X
		*/
		//--------------------------------------------------------------------------------------
		shared_ptr<MeshResource> GetMeshResource(bool ExceptionActive = true) const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���b�V�����\�[�X��ݒ肷��
		@param[in]	ResKey	���b�V�����\�[�X�̃L�[
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetMeshResource(const wstring& ResKey);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���b�V�����\�[�X��ݒ肷��
		@param[in]	MeshResourcePtr	���b�V�����\�[�X
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetMeshResource(const shared_ptr<MeshResource>& MeshResourcePtr);
		//����
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�V�����B�i��֐��j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�`�揈���B
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};



	//--------------------------------------------------------------------------------------
	///	PCTParticle�`��R���|�[�l���g(�p�[�e�B�N���`��)
	//--------------------------------------------------------------------------------------
	class PCTParticleDraw : public DrawComponent {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		@param[in]	MaxInstance	�p�[�e�B�N�������
		*/
		//--------------------------------------------------------------------------------------
		explicit PCTParticleDraw(const shared_ptr<GameObject>& GameObjectPtr, size_t MaxInstance);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PCTParticleDraw();
		//����
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�`��p�p�[�e�B�N����o�^����
		@param[in]	ToCaneraLength	�J�����܂ł̋���
		@param[in]	WorldMatrix	���[���h�s��
		@param[in]	TextureRes	�e�N�X�`��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void AddParticle(float ToCaneraLength, const Matrix4X4& WorldMatrix, const shared_ptr<TextureResource>& TextureRes);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate�����i��֐��j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};

	//--------------------------------------------------------------------------------------
	///	�e�N�X�`���`��C���^�[�t�F�C�X
	//--------------------------------------------------------------------------------------
	class TextureDrawInterface {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		TextureDrawInterface();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~TextureDrawInterface();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�e�N�X�`�����\�[�X�̐ݒ�
		@param[in]	TextureRes	�e�N�X�`�����\�[�X
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetTextureResource(const shared_ptr<TextureResource>& TextureRes);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�e�N�X�`�����\�[�X�̐ݒ�
		@param[in]	TextureKey	�o�^����Ă���e�N�X�`���L�[
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetTextureResource(const wstring& TextureKey);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�e�N�X�`�����\�[�X�̎擾
		@return	�e�N�X�`�����\�[�X
		*/
		//--------------------------------------------------------------------------------------
		shared_ptr<TextureResource> GetTextureResource() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���b�s���O�T���v���[���ǂ����𓾂�
		@return	���b�s���O�T���v���[���ǂ���
		*/
		//--------------------------------------------------------------------------------------
		bool GetWrapSampler() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���b�s���O�T���v���[���ǂ����ݒ肷��
		@param[in]	b	���b�s���O�T���v���[���ǂ���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetWrapSampler(bool b);
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};


	//--------------------------------------------------------------------------------------
	///	Sprite�`��R���|�[�l���g�̐e
	//--------------------------------------------------------------------------------------
	class SpriteBaseDraw : public DrawComponent {
	protected:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v���e�N�g�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit SpriteBaseDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v���e�N�g�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~SpriteBaseDraw();
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���b�V�����\�[�X�̎擾
		@return	���b�V�����\�[�X
		*/
		//--------------------------------------------------------------------------------------
		shared_ptr<MeshResource> GetMeshResource() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���b�V�����\�[�X�̐ݒ�
		@param[in]	MeshRes	���b�V�����\�[�X
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetMeshResource(const shared_ptr<MeshResource>& MeshRes);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�G�~�b�V�u�F�̎擾
		@return	�G�~�b�V�u�F
		*/
		//--------------------------------------------------------------------------------------
		Color4 GetEmissive() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�G�~�b�V�u�F�̐ݒ�
		@param[in]	col	�G�~�b�V�u�F
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetEmissive(const Color4& col);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�t���[�Y�F�̎擾
		@return	�f�t���[�Y�F
		*/
		//--------------------------------------------------------------------------------------
		Color4 GetDiffuse() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�t���[�Y�F�̐ݒ�
		@param[in]	col	�f�t���[�Y�F
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetDiffuse(const Color4& col);
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};


	//--------------------------------------------------------------------------------------
	///	PCSprite�`��R���|�[�l���g
	//--------------------------------------------------------------------------------------
	class PCSpriteDraw : public SpriteBaseDraw {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit PCSpriteDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		@param[in]	Vertices	�������_�̔z��
		@param[in]	indices		�����C���f�b�N�X�̔z��
		*/
		//--------------------------------------------------------------------------------------
		explicit PCSpriteDraw(const shared_ptr<GameObject>& GameObjectPtr,
			vector<VertexPositionColor>& Vertices, vector<uint16_t>& indices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PCSpriteDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���_�ύX�ł���X�v���C�g���b�V�����쐬����i���łɂ���ꍇ�͍����ւ���j
		@param[in]	Vertices	���_�̔z��
		@param[in]	indices		�C���f�b�N�X�̔z��
		*/
		//--------------------------------------------------------------------------------------
		void CreateMesh(vector<VertexPositionColor>& Vertices, vector<uint16_t>& indices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���_�o�b�t�@�̍X�V
		@param[in]	Vertices	���_�z��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void UpdateVertices(const vector<VertexPositionColor>& Vertices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate�����i��֐��j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};



	//--------------------------------------------------------------------------------------
	///	PTSprite�`��R���|�[�l���g
	//--------------------------------------------------------------------------------------
	class PTSpriteDraw : public SpriteBaseDraw,public TextureDrawInterface {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit PTSpriteDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		@param[in]	Vertices	�������_�̔z��
		@param[in]	indices		�����C���f�b�N�X�̔z��
		*/
		//--------------------------------------------------------------------------------------
		explicit PTSpriteDraw(const shared_ptr<GameObject>& GameObjectPtr,
			vector<VertexPositionTexture>& Vertices, vector<uint16_t>& indices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PTSpriteDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���_�ύX�ł���X�v���C�g���b�V�����쐬����i���łɂ���ꍇ�͍����ւ���j
		@param[in]	Vertices	���_�̔z��
		@param[in]	indices		�C���f�b�N�X�̔z��
		*/
		//--------------------------------------------------------------------------------------
		void CreateMesh(vector<VertexPositionTexture>& Vertices, vector<uint16_t>& indices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���_�o�b�t�@�̍X�V
		@param[in]	Vertices	���_�z��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void UpdateVertices(const vector<VertexPositionTexture>& Vertices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate�����i��֐��j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};


	//--------------------------------------------------------------------------------------
	///	PCTSprite�`��R���|�[�l���g
	//--------------------------------------------------------------------------------------
	class PCTSpriteDraw : public SpriteBaseDraw, public TextureDrawInterface {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit PCTSpriteDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		@param[in]	Vertices	�������_�̔z��
		@param[in]	indices		�����C���f�b�N�X�̔z��
		*/
		//--------------------------------------------------------------------------------------
		explicit PCTSpriteDraw(const shared_ptr<GameObject>& GameObjectPtr,
			vector<VertexPositionColorTexture>& Vertices, vector<uint16_t>& indices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PCTSpriteDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���_�ύX�ł���X�v���C�g���b�V�����쐬����i���łɂ���ꍇ�͍����ւ���j
		@param[in]	Vertices	���_�̔z��
		@param[in]	indices		�C���f�b�N�X�̔z��
		*/
		//--------------------------------------------------------------------------------------
		void CreateMesh(vector<VertexPositionColorTexture>& Vertices, vector<uint16_t>& indices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���_�o�b�t�@�̍X�V
		@param[in]	Vertices	���_�z��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void UpdateVertices(const vector<VertexPositionColorTexture>& Vertices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate�����i��֐��j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};

	//--------------------------------------------------------------------------------------
	/// ���C�e�B���O�V�F�[�_�ݒ�p��enum
	//--------------------------------------------------------------------------------------
	enum class ShaderLighting {
		Simple,
		Midium,
		Real
	};

	//--------------------------------------------------------------------------------------
	///	3D�`��R���|�[�l���g�̐e(3D�`��̐e)
	//--------------------------------------------------------------------------------------
	class Base3DDraw : public DrawComponent {
	protected:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v���e�N�g�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit Base3DDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v���e�N�g�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Base3DDraw();
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���b�V�����\�[�X�̎擾(���z�֐�)
		@return	���b�V�����\�[�X
		*/
		//--------------------------------------------------------------------------------------
		virtual shared_ptr<MeshResource> GetMeshResource() const = 0;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���b�V�����\�[�X�̐ݒ�i���z�֐��j
		@param[in]	MeshRes	���b�V�����\�[�X
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void SetMeshResource(const shared_ptr<MeshResource>& MeshRes) = 0;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�G�~�b�V�u�F�̎擾
		@return	�G�~�b�V�u�F
		*/
		//--------------------------------------------------------------------------------------
		Color4 GetEmissive() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�G�~�b�V�u�F�̐ݒ�
		@param[in]	col	�G�~�b�V�u�F
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetEmissive(const Color4& col);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�t���[�Y�F�̎擾
		@return	�f�t���[�Y�F
		*/
		//--------------------------------------------------------------------------------------
		Color4 GetDiffuse() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�t���[�Y�F�̐ݒ�
		@param[in]	col	�f�t���[�Y�F
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetDiffuse(const Color4& col);
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;

	};



	//--------------------------------------------------------------------------------------
	///	Dynamic�`��R���|�[�l���g�̐e(���_��ύX�ł���3D�`��)
	//--------------------------------------------------------------------------------------
	class DynamicBaseDraw : public Base3DDraw {
	protected:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v���e�N�g�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit DynamicBaseDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v���e�N�g�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~DynamicBaseDraw();
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���b�V�����\�[�X�̎擾
		@return	���b�V�����\�[�X
		*/
		//--------------------------------------------------------------------------------------
		virtual shared_ptr<MeshResource> GetMeshResource() const override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���b�V�����\�[�X�̐ݒ�
		@param[in]	MeshRes	���b�V�����\�[�X
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void SetMeshResource(const shared_ptr<MeshResource>& MeshRes)override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};

	//--------------------------------------------------------------------------------------
	///	PCDynamic�`��R���|�[�l���g
	//--------------------------------------------------------------------------------------
	class PCDynamicDraw : public DynamicBaseDraw {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit PCDynamicDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PCDynamicDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���_�ύX�ł��郁�b�V�����쐬����i���łɂ���ꍇ�͍����ւ���j
		@param[in]	Vertices	���_�̔z��
		@param[in]	indices		�C���f�b�N�X�̔z��
		*/
		//--------------------------------------------------------------------------------------
		void CreateMesh(vector<VertexPositionColor>& Vertices, vector<uint16_t>& indices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���_�o�b�t�@�̐ݒ�
		@param[in]	Vertices	���_�z��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void UpdateVertices(const vector<VertexPositionColor>& Vertices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate�����i��֐��j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};

	//--------------------------------------------------------------------------------------
	///	PTDynamic�`��R���|�[�l���g
	//--------------------------------------------------------------------------------------
	class PTDynamicDraw : public DynamicBaseDraw, public TextureDrawInterface {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit PTDynamicDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PTDynamicDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���_�ύX�ł��郁�b�V�����쐬����i���łɂ���ꍇ�͍����ւ���j
		@param[in]	Vertices	���_�̔z��
		@param[in]	indices		�C���f�b�N�X�̔z��
		*/
		//--------------------------------------------------------------------------------------
		void CreateMesh(vector<VertexPositionTexture>& Vertices, vector<uint16_t>& indices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���_�o�b�t�@�̐ݒ�
		@param[in]	Vertices	���_�z��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void UpdateVertices(const vector<VertexPositionTexture>& Vertices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate�����i��֐��j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};



	//--------------------------------------------------------------------------------------
	///	PCTDynamic�`��R���|�[�l���g
	//--------------------------------------------------------------------------------------
	class PCTDynamicDraw : public DynamicBaseDraw, public TextureDrawInterface {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit PCTDynamicDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PCTDynamicDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���_�ύX�ł��郁�b�V�����쐬����i���łɂ���ꍇ�͍����ւ���j
		@param[in]	Vertices	���_�̔z��
		@param[in]	indices		�C���f�b�N�X�̔z��
		*/
		//--------------------------------------------------------------------------------------
		void CreateMesh(vector<VertexPositionColorTexture>& Vertices, vector<uint16_t>& indices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���_�o�b�t�@�̐ݒ�
		@param[in]	Vertices	���_�z��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void UpdateVertices(const vector<VertexPositionColorTexture>& Vertices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate�����i��֐��j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};


	//--------------------------------------------------------------------------------------
	///	PNTDynamic�`��R���|�[�l���g
	//--------------------------------------------------------------------------------------
	class PNTDynamicDraw : public DynamicBaseDraw, public TextureDrawInterface {
		void DrawNotShadow();
		void DrawWithShadow();
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit PNTDynamicDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PNTDynamicDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���_�ύX�ł��郁�b�V�����쐬����i���łɂ���ꍇ�͍����ւ���j
		@param[in]	Vertices	���_�̔z��
		@param[in]	indices		�C���f�b�N�X�̔z��
		*/
		//--------------------------------------------------------------------------------------
		void CreateMesh(vector<VertexPositionNormalTexture>& Vertices, vector<uint16_t>& indices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���_�o�b�t�@�̐ݒ�
		@param[in]	Vertices	���_�z��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void UpdateVertices(const vector<VertexPositionNormalTexture>& Vertices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�e��`�悷�邩�ǂ�������
		@return	�e��`�悷���true
		*/
		//--------------------------------------------------------------------------------------
		bool GetOwnShadowActive() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�e��`�悷�邩�ǂ�������
		@return	�e��`�悷���true
		*/
		//--------------------------------------------------------------------------------------
		bool IsOwnShadowActive() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�e��`�悷�邩�ǂ����ݒ肷��
		@param[in]	b		�e��`�悷�邩�ǂ���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetOwnShadowActive(bool b);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate�����i��֐��j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};






	//--------------------------------------------------------------------------------------
	///	static�`��R���|�[�l���g�̐e(���_��ύX�ł��Ȃ�3D�`��)
	//--------------------------------------------------------------------------------------
	class StaticBaseDraw : public Base3DDraw {
	protected:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v���e�N�g�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit StaticBaseDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v���e�N�g�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~StaticBaseDraw();
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���b�V�����\�[�X�̎擾
		@return	���b�V�����\�[�X
		*/
		//--------------------------------------------------------------------------------------
		virtual shared_ptr<MeshResource> GetMeshResource() const override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���b�V�����\�[�X�̐ݒ�
		@param[in]	MeshRes	���b�V�����\�[�X
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void SetMeshResource(const shared_ptr<MeshResource>& MeshRes)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���b�V�����\�[�X�̓o�^
		@param[in]	MeshKey	�o�^����Ă��郁�b�V���L�[
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void SetMeshResource(const wstring& MeshKey);
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};


	//--------------------------------------------------------------------------------------
	///	PCStatic�`��R���|�[�l���g
	//--------------------------------------------------------------------------------------
	class PCStaticDraw : public StaticBaseDraw {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit PCStaticDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PCStaticDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate�����i��֐��j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};

	//--------------------------------------------------------------------------------------
	///	PTStatic�`��R���|�[�l���g
	//--------------------------------------------------------------------------------------
	class PTStaticDraw : public StaticBaseDraw, public TextureDrawInterface {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit PTStaticDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PTStaticDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate�����i��֐��j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};


	//--------------------------------------------------------------------------------------
	///	PCTStatic�`��R���|�[�l���g
	//--------------------------------------------------------------------------------------
	class PCTStaticDraw : public StaticBaseDraw, public TextureDrawInterface {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit PCTStaticDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PCTStaticDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate�����i��֐��j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};


	//--------------------------------------------------------------------------------------
	///	PNStatic�`��R���|�[�l���g
	//--------------------------------------------------------------------------------------
	class PNStaticDraw : public StaticBaseDraw {
		void DrawNotShadow();
		void DrawWithShadow();
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit PNStaticDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PNStaticDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�e��`�悷�邩�ǂ�������
		@return	�e��`�悷���true
		*/
		//--------------------------------------------------------------------------------------
		bool GetOwnShadowActive() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�e��`�悷�邩�ǂ�������
		@return	�e��`�悷���true
		*/
		//--------------------------------------------------------------------------------------
		bool IsOwnShadowActive() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�e��`�悷�邩�ǂ����ݒ肷��
		@param[in]	b		�e��`�悷�邩�ǂ���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetOwnShadowActive(bool b);
		//����
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate�����i��֐��j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};



	//--------------------------------------------------------------------------------------
	///	PNTStatic�`��R���|�[�l���g
	//--------------------------------------------------------------------------------------
	class PNTStaticDraw : public StaticBaseDraw, public TextureDrawInterface {
		void DrawNotShadow();
		void DrawWithShadow();
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit PNTStaticDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PNTStaticDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���C�e�B���O�𓾂�
		@return	�V�F�[�_�[���C�e�B���O
		*/
		//--------------------------------------------------------------------------------------
		ShaderLighting GetLighting() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���C�e�B���O��ݒ肷��
		@param[in]	Lighting	�V�F�[�_�[���C�e�B���O
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetLighting(ShaderLighting Lighting);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�e��`�悷�邩�ǂ�������
		@return	�e��`�悷���true
		*/
		//--------------------------------------------------------------------------------------
		bool GetOwnShadowActive() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�e��`�悷�邩�ǂ�������
		@return	�e��`�悷���true
		*/
		//--------------------------------------------------------------------------------------
		bool IsOwnShadowActive() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�e��`�悷�邩�ǂ����ݒ肷��
		@param[in]	b		�e��`�悷�邩�ǂ���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetOwnShadowActive(bool b);
		//����
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate�����i��֐��j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};

	//--------------------------------------------------------------------------------------
	//	class PNTStaticModelDraw : public DrawComponent;
	//	�p�r: PNTStaticModelDraw�`��R���|�[�l���g
	//--------------------------------------------------------------------------------------
	class PNTStaticModelDraw : public StaticBaseDraw {
		void DrawWithShadow();
		void DrawNotShadow();
	public:
		explicit PNTStaticModelDraw(const shared_ptr<GameObject>& GameObjectPtr);
		virtual ~PNTStaticModelDraw();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	���C�e�B���O�𓾂�
		@return	�V�F�[�_�[���C�e�B���O
		*/
		//--------------------------------------------------------------------------------------
		ShaderLighting GetLighting() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���C�e�B���O��ݒ肷��
		@param[in]	Lighting	�V�F�[�_�[���C�e�B���O
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetLighting(ShaderLighting Lighting);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�e��`�悷�邩�ǂ�������
		@return	�e��`�悷���true
		*/
		//--------------------------------------------------------------------------------------
		bool GetOwnShadowActive() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�e��`�悷�邩�ǂ�������
		@return	�e��`�悷���true
		*/
		//--------------------------------------------------------------------------------------
		bool IsOwnShadowActive() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�e��`�悷�邩�ǂ����ݒ肷��
		@param[in]	b		�e��`�悷�邩�ǂ���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetOwnShadowActive(bool b);
		//����
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate�����i��֐��j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};




	//--------------------------------------------------------------------------------------
	///	�A�j���[�V�����f�[�^�\����.
	//--------------------------------------------------------------------------------------
	struct	AnimationData
	{
		///	�X�^�[�g�T���v��
		UINT	m_StartSample;
		///	�T���v���̒���
		UINT	m_SampleLength;
		///	���[�v���邩�ǂ���
		bool	m_IsLoop;
		///	�A�j�����I���������ǂ���
		bool	m_IsAnimeEnd;
		///	1�b������̃t���[��
		float	m_SamplesParSecond;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^.
		*/
		//--------------------------------------------------------------------------------------
		AnimationData()
		{
			ZeroMemory(this, sizeof(AnimationData));
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^.
		@param[in]	StartSample	�X�^�[�g�t���[��
		@param[in]	SampleLength	�t���[���̒���
		@param[in]	bLoop	���[�v���邩�ǂ���
		@param[in]	SamplesParSecond = 30.0f	1�b������̃t���[����
		*/
		//--------------------------------------------------------------------------------------
		AnimationData(UINT StartSample, UINT SampleLength, bool bLoop,
			float SamplesParSecond = 30.0f) :
			m_StartSample{ StartSample },
			m_SampleLength{ SampleLength },
			m_IsLoop{ bLoop },
			m_IsAnimeEnd{ false },
			m_SamplesParSecond{ SamplesParSecond }
		{}
	};


	//--------------------------------------------------------------------------------------
	///	PNTBoneModelDraw�`��R���|�[�l���g�i�{�[�����f���`��p�j
	//--------------------------------------------------------------------------------------
	class PNTBoneModelDraw : public Base3DDraw {
		void DrawWithShadow();
		void DrawNotShadow();
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit PNTBoneModelDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PNTBoneModelDraw();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	���C�e�B���O�𓾂�
		@return	�V�F�[�_�[���C�e�B���O
		*/
		//--------------------------------------------------------------------------------------
		ShaderLighting GetLighting() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���C�e�B���O��ݒ肷��
		@param[in]	Lighting	�V�F�[�_�[���C�e�B���O
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetLighting(ShaderLighting Lighting);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	���b�V�����\�[�X�̎擾
		@return	���b�V�����\�[�X
		*/
		//--------------------------------------------------------------------------------------
		virtual shared_ptr<MeshResource> GetMeshResource() const override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���b�V�����\�[�X�̐ݒ�
		@param[in]	MeshRes	���b�V�����\�[�X
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void SetMeshResource(const shared_ptr<MeshResource>& MeshRes)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���b�V�����\�[�X�̓o�^
		@param[in]	MeshKey	�o�^����Ă��郁�b�V���L�[
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetMeshResource(const wstring& MeshKey);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���ȉe�`����s�����ǂ����̎擾
		@return	���ȉe�`����s�����ǂ���
		*/
		//--------------------------------------------------------------------------------------
		bool GetOwnShadowActive() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���ȉe�`����s�����ǂ����̎擾
		@return	���ȉe�`����s�����ǂ���
		*/
		//--------------------------------------------------------------------------------------
		bool IsOwnShadowActive() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���ȉe�`����s�����ǂ����̐ݒ�
		@param[in]	b	���ȉe�`����s�����ǂ���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetOwnShadowActive(bool b);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�J�n�s�񂩂�I���s��̊Ԃ�t���Ԏ��̍s���Ԃ�
		@param[in]	m1	�J�n�̍s��
		@param[in]	m2	�I���̍s��
		@param[in]	t	���ԁi0����1.0f�j
		@param[out]	out	���ʂ��󂯎��s��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void InterpolationMatrix(const Matrix4X4& m1, const Matrix4X4& m2, float t, Matrix4X4& out);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�A�j���[�V������ǉ�����
		@param[in]	Name	�A�j���[�V������
		@param[in]	StartSample	�J�n�T���v��
		@param[in]	SampleLength	�T���v���̒���
		@param[in]	Loop	���[�v���邩�ǂ���
		@param[in]	SamplesParSecond = 30.0f	1�b������̃T���v����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void AddAnimation(const wstring& Name, int StartSample, int SampleLength, bool Loop,
			float SamplesParSecond = 30.0f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���݂̃A�j���[�V������ύX����
		@param[in]	AnemationName	�A�j���[�V�������i���łɒǉ�����Ă�����́j
		@param[in]	StartTime = 0.0f	�J�n����̕b��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void ChangeCurrentAnimation(const wstring& AnemationName, float StartTime = 0.0f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���݂̃A�j���[�V�������𓾂�
		@return	�A�j���[�V�������i������j
		*/
		//--------------------------------------------------------------------------------------
		const wstring& GetCurrentAnimation() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���݂̃A�j���[�V������i�߂�
		@param[in]	ElapsedTime	�o�ߎ���
		@return	�A�j���[�V�������I�������true
		*/
		//--------------------------------------------------------------------------------------
		bool UpdateAnimation(float ElapsedTime);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���[�J���{�[���s��z��𓾂�
		@return	���[�J���{�[���s��z��̐擪�|�C���^
		*/
		//--------------------------------------------------------------------------------------
		virtual const vector< Matrix4X4 >* GetVecLocalBonesPtr() const;
		//����
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate�����i��֐��j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};

	//--------------------------------------------------------------------------------------
	///	�ėp�`��p�iPNTStatic�Œ�j
	//--------------------------------------------------------------------------------------
	class GenericDraw :public ObjectInterface {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		GenericDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~GenericDraw();
		//����
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���C�A�t���[���`�揈��
		@param[in]	GameObj	�Q�[���I�u�W�F�N�g
		@param[in]	Mesh	PC���b�V��

		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void DrawWireFrame(const shared_ptr<GameObject>& GameObj,
			const shared_ptr<MeshResource>& Mesh,const Matrix4X4& MeshToTransformMatrix = Matrix4X4());
	};




}
//end basecross
