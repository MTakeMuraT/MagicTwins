/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	//	class Goal : public GameObject;
	//	用途: ゴール
	//--------------------------------------------------------------------------------------

	Goal::Goal(const shared_ptr<Stage>& StagePtr,Vector3 pos, Vector3 scale):
		GameObject(StagePtr),
		m_InitPos(pos),
		m_Scale(scale)
		{}
	void Goal::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_Scale);
		Ptr->SetRotation(0, 0, 0);

		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionSphere>();
		//横部分のみ反発
		PtrCol->SetIsHitAction(IsHitAction::AutoOnObjectRepel);

		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//描画するテクスチャを設定
		PtrDraw->SetTextureResource(L"GOAL_TX");

		//透明処理
		SetAlphaActive(true);

	}

}
//end basecross
