/*!
@file DrawComponentsEx.h
@brief 拡張描画コンポーネント
@copyright Copyright (c) 2017 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/
#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	Basicシェーダー
	//--------------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------------
	///	Basicシェーダー用コンスタントバッファ
	//--------------------------------------------------------------------------------------
	struct BasicEffectConstants
	{
		XMVECTOR diffuseColor;
		XMVECTOR emissiveColor;
		XMVECTOR specularColorAndPower;

		XMVECTOR lightDirection[3];
		XMVECTOR lightDiffuseColor[3];
		XMVECTOR lightSpecularColor[3];

		XMVECTOR eyePosition;

		XMVECTOR fogColor;
		XMVECTOR fogVector;

		XMMATRIX world;
		XMVECTOR worldInverseTranspose[3];
		XMMATRIX worldViewProj;
		//汎用フラグ
		XMUINT4 activeFlg;
		//以下影
		XMVECTOR lightPos;
		XMVECTOR eyePos;
		XMMATRIX lightView;
		XMMATRIX lightProjection;

		XMVECTOR bones[3 * 72];

	};
	//--------------------------------------------------------------------------------------
	/// コンスタントバッファ
	//--------------------------------------------------------------------------------------
	DECLARE_DX11_CONSTANT_BUFFER(CBBasicEffect, BasicEffectConstants)

	//--------------------------------------------------------------------------------------
	/// PT頂点シェーダ
	//--------------------------------------------------------------------------------------
	DECLARE_DX11_VERTEX_SHADER(BcVSPTStatic, VertexPositionTexture)


	//--------------------------------------------------------------------------------------
	/// PTピクセルシェーダ
	//--------------------------------------------------------------------------------------
	DECLARE_DX11_PIXEL_SHADER(BcPSPTStatic);


	//--------------------------------------------------------------------------------------
	/// PNT頂点シェーダ(頂点ライティング)
	//--------------------------------------------------------------------------------------
	//影無し
	DECLARE_DX11_VERTEX_SHADER(BcVSPNTStaticVL, VertexPositionNormalTexture)
	//影無しBone
	DECLARE_DX11_VERTEX_SHADER(BcVSPNTBoneVL, VertexPositionNormalTextureSkinning)

	//影付き
	DECLARE_DX11_VERTEX_SHADER(BcVSPNTStaticVLShadow, VertexPositionNormalTexture)
	//影付きBone
	DECLARE_DX11_VERTEX_SHADER(BcVSPNTBoneVLShadow, VertexPositionNormalTextureSkinning)


	
	//バイアス付き影無し
	DECLARE_DX11_VERTEX_SHADER(BcVSPNTStaticVLBn, VertexPositionNormalTexture)
	//バイアス付き影無しBone
	DECLARE_DX11_VERTEX_SHADER(BcVSPNTBoneVLBn, VertexPositionNormalTextureSkinning)

	//バイアス付き影付き
	DECLARE_DX11_VERTEX_SHADER(BcVSPNTStaticVLBnShadow, VertexPositionNormalTexture)
	//バイアス付き影付きBone
	DECLARE_DX11_VERTEX_SHADER(BcVSPNTBoneVLBnShadow, VertexPositionNormalTextureSkinning)


	//--------------------------------------------------------------------------------------
	/// PNTピクセルシェーダ(頂点ライティング)
	//--------------------------------------------------------------------------------------
	//影無し
	DECLARE_DX11_PIXEL_SHADER(BcPSPNTVL);
	//影付き
	DECLARE_DX11_PIXEL_SHADER(BcPSPNTVLShadow);


	//--------------------------------------------------------------------------------------
	/// PNT頂点シェーダ(ピクセルライティング)
	//--------------------------------------------------------------------------------------
	//影無し
	DECLARE_DX11_VERTEX_SHADER(BcVSPNTStaticPL, VertexPositionNormalTexture)
	//影無しBone
	DECLARE_DX11_VERTEX_SHADER(BcVSPNTBonePL, VertexPositionNormalTextureSkinning)
	//影付き
	DECLARE_DX11_VERTEX_SHADER(BcVSPNTStaticPLShadow, VertexPositionNormalTexture)
	//影付きBone
	DECLARE_DX11_VERTEX_SHADER(BcVSPNTBonePLShadow, VertexPositionNormalTextureSkinning)

	//バイアス付き影無し
	DECLARE_DX11_VERTEX_SHADER(BcVSPNTStaticPLBn, VertexPositionNormalTexture)
	//バイアス付き影無しBone
	DECLARE_DX11_VERTEX_SHADER(BcVSPNTBonePLBn, VertexPositionNormalTextureSkinning)

	//バイアス付き影付き
	DECLARE_DX11_VERTEX_SHADER(BcVSPNTStaticPLBnShadow, VertexPositionNormalTexture)
	//バイアス付き影付きBone
	DECLARE_DX11_VERTEX_SHADER(BcVSPNTBonePLBnShadow, VertexPositionNormalTextureSkinning)


	


	//--------------------------------------------------------------------------------------
	/// PNTピクセルシェーダ(ピクセルライティング)
	//--------------------------------------------------------------------------------------
	//影無し
	DECLARE_DX11_PIXEL_SHADER(BcPSPNTPL);
	//影付き
	DECLARE_DX11_PIXEL_SHADER(BcPSPNTPLShadow);




	//--------------------------------------------------------------------------------------
	///	Basic描画コンポーネントの親(3D描画)
	//--------------------------------------------------------------------------------------
	class Bc3DDraw : public DrawComponent {
	protected:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	プロテクトコンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		explicit Bc3DDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	プロテクトデストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual	~Bc3DDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンスタントバッファの設定
		@param[out]	BcCb	設定する構造体
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetConstants(BasicEffectConstants& BcCb, bool shadowUse = false);
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	メッシュリソースの取得(仮想関数)
		@return	メッシュリソース
		*/
		//--------------------------------------------------------------------------------------
		virtual shared_ptr<MeshResource> GetMeshResource() const = 0;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	メッシュリソースの設定（仮想関数）
		@param[in]	MeshRes	メッシュリソース
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void SetMeshResource(const shared_ptr<MeshResource>& MeshRes) = 0;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	エミッシブ色の取得
		@return	エミッシブ色
		*/
		//--------------------------------------------------------------------------------------
		Color4 GetEmissive() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	エミッシブ色の設定
		@param[in]	col	エミッシブ色
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetEmissive(const Color4& col);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デフューズ色の取得
		@return	デフューズ色
		*/
		//--------------------------------------------------------------------------------------
		Color4 GetDiffuse() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デフューズ色の設定
		@param[in]	col	デフューズ色
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetDiffuse(const Color4& col);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	スペキュラー色の取得
		@return	スペキュラー色
		*/
		//--------------------------------------------------------------------------------------
		Color4 GetSpecularColor() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	スペキュラー色の設定
		@param[in]	col	スペキュラー色
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetSpecularColor(const Color4& col);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	スペキュラー色をなくす
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void DisableSpecular();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	スペキュラーパワーの取得
		@return	スペキュラーパワー色
		*/
		//--------------------------------------------------------------------------------------
		float GetSpecularPower() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	スペキュラーパワーの設定
		@param[in]	pow	スペキュラーパワー色
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetSpecularPower(float pow);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	スペキュラーとパワー色の取得
		@return	スペキュラーとパワー色
		*/
		//--------------------------------------------------------------------------------------
		Color4 GetSpecularColorAndPower() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	スペキュラーとパワー色の設定
		@param[in]	col	スペキュラーとパワー色
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetSpecularColorAndPower(const Color4& col);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	アルファ値の取得
		@return	アルファ値
		*/
		//--------------------------------------------------------------------------------------
		float GetAlpha() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	アルファ値の設定
		@param[in]	pow	アルファ値
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetAlpha(float a);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	カラーとアルファ色の取得
		@return	カラーとアルファ色
		*/
		//--------------------------------------------------------------------------------------
		Color4 GetColorAndAlpha() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	カラーとアルファ色の設定
		@param[in]	col カラーとアルファ色
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetColorAndAlpha(const Color4& col);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ライティングするかどうか
		@return	する場合はtrue
		*/
		//--------------------------------------------------------------------------------------
		bool IsLightingEnabled() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ライティングするかどうか
		@return	する場合はtrue
		*/
		//--------------------------------------------------------------------------------------
		bool GetLightingEnabled() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ライティングするかどうか設定
		@param[in] value ライティングするかどうか
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetLightingEnabled(bool value);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ピクセルライティングするかどうか
		@return	する場合はtrue
		*/
		//--------------------------------------------------------------------------------------
		bool GetPerPixelLighting() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ピクセルライティングするかどうか
		@return	する場合はtrue
		*/
		//--------------------------------------------------------------------------------------
		bool IsPerPixelLighting() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ピクセルライティングするかどうか設定
		@param[in] value ピクセルライティングするかどうか
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetPerPixelLighting(bool value);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	法線にバイアスをかけるかどうか
		@return	する場合はtrue
		*/
		//--------------------------------------------------------------------------------------
		bool GetBiasedNormals() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	法線にバイアスをかけるかどうか
		@return	する場合はtrue
		*/
		//--------------------------------------------------------------------------------------
		bool IsBiasedNormals() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	法線にバイアスをかけるかどうか設定
		@param[in] value 法線にバイアスをかけるかどうか
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetBiasedNormals(bool value);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	アンビエントライト色の取得
		@return	アンビエントライト色
		*/
		//--------------------------------------------------------------------------------------
		Color4 GetAmbientLightColor()const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	アンビエントライト色の設定
		@param[in] value アンビエントライト色
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetAmbientLightColor(const Color4& value);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	インデックスが有効かどうかチェックする（無効なら例外）
		@param[in] whichLight ライトのインデックス
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		static void ValidateLightIndex(int whichLight);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ライトの最大値を得る
		@return	ライトの最大値
		*/
		//--------------------------------------------------------------------------------------
		int GetMaxDirectionalLights();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	指定のライトを有効にするかどうかを得る
		@param[in] whichLight ライトのインデックス
		@return	有効ならtrue
		*/
		//--------------------------------------------------------------------------------------
		bool GetLightEnabled(int whichLight)const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	指定のライトを有効にするかどうかを得る
		@param[in] whichLight ライトのインデックス
		@return	有効ならtrue
		*/
		//--------------------------------------------------------------------------------------
		bool IsLightEnabled(int whichLight)const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	指定のライトを有効にするかどうか
		@param[in] whichLight ライトのインデックス
		@param[in] value 有効にするかどうか
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetLightEnabled(int whichLight, bool value);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	指定のライトの向きを得る
		@param[in] whichLight ライトのインデックス
		@return	指定のライトの向き
		*/
		//--------------------------------------------------------------------------------------
		Vector3 GetLightDirection(int whichLight) const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	指定のライトの向きを設定する
		@param[in] whichLight ライトのインデックス
		@param[in] value 値
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetLightDirection(int whichLight,const Vector3& value);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	指定のライトのデフューズ色を得る
		@param[in] whichLight ライトのインデックス
		@return	指定のライトのデフューズ色
		*/
		//--------------------------------------------------------------------------------------
		Color4 GetLightDiffuseColor(int whichLight) const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	指定のライトのデフューズ色を設定する
		@param[in] whichLight ライトのインデックス
		@param[in] value 値
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetLightDiffuseColor(int whichLight,const Color4& value);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	指定のライトのスペキュラー色を得る
		@param[in] whichLight ライトのインデックス
		@return	指定のライトのスペキュラー色
		*/
		//--------------------------------------------------------------------------------------
		Color4 GetLightSpecularColor(int whichLight) const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	指定のライトのスペキュラー色を設定する
		@param[in] whichLight ライトのインデックス
		@param[in] value 値
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetLightSpecularColor(int whichLight, const Color4& value);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	フォグを使うかどうか
		@return	フォグを使うならtrue
		*/
		//--------------------------------------------------------------------------------------
		bool GetFogEnabled() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	フォグを使うかどうか
		@return	フォグを使うならtrue
		*/
		//--------------------------------------------------------------------------------------
		bool IsFogEnabled() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	フォグを使うかどうか指定
		@param[in]	b	フォグを使うならtrue
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetFogEnabled(bool b);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	フォグの開始位置を得る
		@return	フォグの開始位置
		*/
		//--------------------------------------------------------------------------------------
		float GetFogStart() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	フォグの開始位置指定
		@param[in]	value	フォグの開始位置
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetFogStart(float value);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	フォグの終了位置を得る
		@return	フォグの終了位置
		*/
		//--------------------------------------------------------------------------------------
		float GetFogEnd() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	フォグの終了位置指定
		@param[in]	value	フォグの終了位置
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetFogEnd(float value);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	フォグ色の取得
		@return	フォグ色
		*/
		//--------------------------------------------------------------------------------------
		Color4 GetFogColor() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	フォグ色の設定
		@param[in]	col	フォグ色
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetFogColor(const Color4& col);
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};

	//--------------------------------------------------------------------------------------
	///	BasicPNT描画コンポーネント
	//--------------------------------------------------------------------------------------
	class BcPNTStaticDraw : public Bc3DDraw, public TextureDrawInterface {
	protected:
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		explicit BcPNTStaticDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~BcPNTStaticDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	影を描画するかどうか得る
		@return	影を描画すればtrue
		*/
		//--------------------------------------------------------------------------------------
		bool GetOwnShadowActive() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	影を描画するかどうか得る
		@return	影を描画すればtrue
		*/
		//--------------------------------------------------------------------------------------
		bool IsOwnShadowActive() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	影を描画するかどうか設定する
		@param[in]	b		影を描画するかどうか
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetOwnShadowActive(bool b);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	メッシュリソースの取得(仮想関数)
		@return	メッシュリソース
		*/
		//--------------------------------------------------------------------------------------
		virtual shared_ptr<MeshResource> GetMeshResource() const override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	メッシュリソースの設定（仮想関数）
		@param[in]	MeshRes	メッシュリソース
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void SetMeshResource(const shared_ptr<MeshResource>& MeshRes) override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	メッシュリソースの設定（仮想関数）
		@param[in]	MeshKey	メッシュキー
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void SetMeshResource(const wstring& MeshKey);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate処理（空関数）
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};


	//--------------------------------------------------------------------------------------
	///	BasicPNTモデル描画コンポーネント
	//--------------------------------------------------------------------------------------
	class BcPNTStaticModelDraw : public BcPNTStaticDraw {
	protected:
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		explicit BcPNTStaticModelDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~BcPNTStaticModelDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デフィーズ色をモデル設定優先かどうか得る
		@return	デフィーズ色をモデル設定優先ならtrue
		*/
		//--------------------------------------------------------------------------------------
		bool GetModelDiffusePriority() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デフィーズ色をモデル設定優先かどうか得る
		@return	デフィーズ色をモデル設定優先ならtrue
		*/
		//--------------------------------------------------------------------------------------
		bool IsModelDiffusePriority() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デフィーズ色をモデル設定優先かどうか設定する
		@param[in]	b	デフィーズ色をモデル設定優先かどうか
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetModelDiffusePriority(bool b);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	エミッシブ色をモデル設定優先かどうか得る
		@return	エミッシブ色をモデル設定優先ならtrue
		*/
		//--------------------------------------------------------------------------------------
		bool GetModelEmissivePriority() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	エミッシブ色をモデル設定優先かどうか得る
		@return	エミッシブ色をモデル設定優先ならtrue
		*/
		//--------------------------------------------------------------------------------------
		bool IsModelEmissivePriority() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	エミッシブ色をモデル設定優先かどうか設定する
		@param[in]	b	エミッシブ色をモデル設定優先かどうか
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetModelEmissivePriority(bool b);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	モデルのテクスチャを有効にするかどうか得る
		@return	モデルのテクスチャを有効ならtrue
		*/
		//--------------------------------------------------------------------------------------
		bool GetModelTextureEnabled() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	モデルのテクスチャを有効にするかどうか得る
		@return	モデルのテクスチャを有効ならtrue
		*/
		//--------------------------------------------------------------------------------------
		bool IsModelTextureEnabled() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	モデルのテクスチャを有効にするかどうか設定する
		@param[in]	b	モデルのテクスチャを有効にするかどうか
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SeModelTextureEnabled(bool b);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};


	//--------------------------------------------------------------------------------------
	///	BcPNTBoneModelDraw描画コンポーネント（ボーンモデル描画用）
	//--------------------------------------------------------------------------------------
	class BcPNTBoneModelDraw : public BcPNTStaticModelDraw {
	protected:
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		explicit BcPNTBoneModelDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~BcPNTBoneModelDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	メッシュリソースの取得
		@return	メッシュリソース
		*/
		//--------------------------------------------------------------------------------------
		virtual shared_ptr<MeshResource> GetMeshResource() const override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	メッシュリソースの設定
		@param[in]	MeshRes	メッシュリソース
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void SetMeshResource(const shared_ptr<MeshResource>& MeshRes)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	メッシュリソースの登録
		@param[in]	MeshKey	登録されているメッシュキー
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void SetMeshResource(const wstring& MeshKey) override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	開始行列から終了行列の間のt時間時の行列を返す
		@param[in]	m1	開始の行列
		@param[in]	m2	終了の行列
		@param[in]	t	時間（0から1.0f）
		@param[out]	out	結果を受け取る行列
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void InterpolationMatrix(const Matrix4X4& m1, const Matrix4X4& m2, float t, Matrix4X4& out);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	アニメーションを追加する
		@param[in]	Name	アニメーション名
		@param[in]	StartSample	開始サンプル
		@param[in]	SampleLength	サンプルの長さ
		@param[in]	Loop	ループするかどうか
		@param[in]	SamplesParSecond = 30.0f	1秒あたりのサンプル数
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void AddAnimation(const wstring& Name, int StartSample, int SampleLength, bool Loop,
			float SamplesParSecond = 30.0f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	現在のアニメーションを変更する
		@param[in]	AnemationName	アニメーション名（すでに追加されているもの）
		@param[in]	StartTime = 0.0f	開始からの秒数
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void ChangeCurrentAnimation(const wstring& AnemationName, float StartTime = 0.0f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	現在のアニメーション名を得る
		@return	アニメーション名（文字列）
		*/
		//--------------------------------------------------------------------------------------
		const wstring& GetCurrentAnimation() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	現在のアニメーションを進める
		@param[in]	ElapsedTime	経過時間
		@return	アニメーションが終了すればtrue
		*/
		//--------------------------------------------------------------------------------------
		bool UpdateAnimation(float ElapsedTime);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ローカルボーン行列配列を得る
		@return	ローカルボーン行列配列の先頭ポインタ
		*/
		//--------------------------------------------------------------------------------------
		virtual const vector< Matrix4X4 >* GetVecLocalBonesPtr() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};





}
// end basecross
