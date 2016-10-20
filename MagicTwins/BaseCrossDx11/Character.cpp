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
	//--------------------------------------------------------------------------------------
	//	class Black : public GameObject;
	//	用途: 暗転用黒
	//--------------------------------------------------------------------------------------
	Black::Black(const shared_ptr<Stage>& StagePtr)	:
		GameObject(StagePtr)
	{}

	void Black::OnCreate()
	{
		//ウィンドウサイズ取得
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());

		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(0,0,0);
		Ptr->SetScale(WindowSize.x,WindowSize.y,1);
		Ptr->SetRotation(0, 0, 0);

		//テクスチャをつける
		auto PtrSprite = this->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"BRACK_TX");

		//透明化
		PtrSprite->SetDiffuse(Color4(1,1,1,0));

		//表示レイヤー10設定
		SetDrawLayer(10);

		//透明度反映
		SetAlphaActive(true);

	}

	void Black::OnUpdate()
	{
		//起動状態
		if (m_StartFlg)
		{
			//実体化
			auto PtrSprite = this->AddComponent<PCTSpriteDraw>();
			m_alpha += 0.01f;
			PtrSprite->SetDiffuse(Color4(1, 1, 1, m_alpha));
			
			if (m_alpha >= 1.2f)
			{
				m_StartFlg = false;
				m_EndFlg = true;
			}
		}
	}

	void Black::StartBlack()
	{
		m_StartFlg = true;
	}

	bool Black::GetBlackFinish()
	{
		return m_EndFlg;
	}

	//--------------------------------------------------------------------------------------
	//	class MagicBook : public GameObject;
	//	用途: 魔導書
	//--------------------------------------------------------------------------------------
	MagicBook::MagicBook(const shared_ptr<Stage>& StagePtr, Vector3 pos, MagicType magic) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_MagicContent(magic)
	{}

	void MagicBook::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetScale(0.5f, 0.5f, 0.5f);
		Ptr->SetRotation(0, 0, 0);
		Ptr->SetPosition(m_InitPos);

		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");
		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//メッシュを設定
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");

		//テクスチャを設定
		PtrDraw->SetTextureResource(L"MAGICBOOKFIRE_TX");

		switch (m_MagicContent)
		{
		case Fire:
			PtrDraw->SetTextureResource(L"MAGICBOOKFIRE_TX");
			break;
		case IceFog :
			PtrDraw->SetTextureResource(L"MAGICBOOKICEFOG_TX");
			break;
		default:
			break;
		}

		//透明処理
		SetAlphaActive(true);

		SetUpdateActive(false);
	}

	void MagicBook::OnUpdate()
	{
		m_ElaTime += App::GetApp()->GetElapsedTime();
		if (m_ElaTime >= m_LimitTime)
		{
			GetComponent<PNTStaticDraw>()->SetDiffuse(Color4(1, 1, 1, 1));
			m_ElaTime = 0;
			SetUpdateActive(false);
			m_ActiveFlg = true;
		}
	}

	//とったとき
	void MagicBook::GetPlayer()
	{
		if (m_ActiveFlg)
		{
			GetStage()->GetSharedGameObject<Player>(L"Player1", false)->SetMagic(m_MagicContent);
			GetComponent<PNTStaticDraw>()->SetDiffuse(Color4(1, 1, 1, 0.1f));
			SetUpdateActive(true);
			m_ActiveFlg = false;
		}
	}

	Vector3 MagicBook::GetPos()
	{
		return GetComponent<Transform>()->GetPosition();
	}

	Vector3 MagicBook::GetScale()
	{
		return GetComponent<Transform>()->GetScale();
	}

	//-----------------------------------
	//制限時間
	//-----------------------------------
	LimitTime::LimitTime(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{
	}

	/*float LimitTime::GetApp()
	{
	App::GetApp()->GetElapsedTime;
	}*/

	void LimitTime::OnCreate()
	{
		//文字列をつける
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(512.0f, 16.0f, 640.0f, 480.0f));
		PtrString->SetFont(L"", 40);

		//auto  Countdown = 
	}

	void LimitTime::OnUpdate()
	{
		//タイム表示
		int time = (int)limitTime;
		wstring txt = Util::IntToWStr(time);
		GetComponent<StringSprite>()->SetText(txt);

		limitTime += -App::GetApp()->GetElapsedTime();
		if (limitTime < 0)
		{

		}
	}

}
//end basecross
