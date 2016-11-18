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
		auto PtrCol = AddComponent<CollisionObb>();
		//横部分のみ反発
		//PtrCol->SetIsHitAction(IsHitAction::Stop);

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
	//	class Rpck : public GameObject;
	//	用途：岩
	//--------------------------------------------------------------------------------------
	Rock::Rock(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_Scale(scale)
	{}

	void Rock::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_Scale);
		Ptr->SetRotation(0, 0, 0);

		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionObb>();

		// モデルとトランスフォームの間の差分行列
		float angle = (-90) * (3.14159265f / 180);
		Matrix4X4 SpanMat;
		SpanMat.DefTransformation(
			Vector3(0.5f, 0.5f, 0.5f),
			Vector3(0, angle, 0),
			Vector3(0, 0, 0)
			);

		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(L"Rock_Model");
		ShadowPtr->SetMeshToTransformMatrix(SpanMat);


		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticModelDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"Rock_Model");
		PtrDraw->SetMeshToTransformMatrix(SpanMat);

		//透明処理
		SetAlphaActive(true);
	}

	//--------------------------------------------------------------------------------------
	//	class Box : public GameObject;
	//	用途: 箱
	//--------------------------------------------------------------------------------------

	Box::Box(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale,Vector3 rot) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale),
		m_InitRot(rot)
	{}
	void Box::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_InitScale);
		Ptr->SetRotation(m_InitRot);

		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionObb>();
		//横部分のみ反発
		PtrCol->SetIsHitAction(IsHitAction::Stop);

		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//描画するテクスチャを設定
		PtrDraw->SetTextureResource(L"BOX_TX");

		//透明処理
		SetAlphaActive(true);

	}

	//--------------------------------------------------------------------------------------
	//	class Enemy : public GameObject;
	//	用途: 敵
	//--------------------------------------------------------------------------------------
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale):
		GameObject(StagePtr),
		m_InitPos(pos),
		m_Scale(scale)
	{}

	void Enemy::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_Scale);

		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		//描画するテクスチャを設定
		PtrDraw->SetTextureResource(L"ENEMY_TX");

		//透明処理
		SetAlphaActive(true);

	}

	void Enemy::OnUpdate()
	{
		//止まってなければ追う
		if (!m_StopFlg)
		{
			auto P1P = GetStage()->GetSharedGameObject<Player>(L"Player1", false);
			auto P2P = GetStage()->GetSharedGameObject<Player>(L"Player2", false);

			if (P1P->GetActive())
			{
				Vector3 topos = P1P->GetComponent<Transform>()->GetPosition();
				Vector3 nowpos = GetComponent<Transform>()->GetPosition();
				Vector3 dir;
				dir = topos - nowpos;
				Vector2 velo = Vector2(dir.x, dir.z);
				float angle = atan2(velo.y, velo.x);
				velo.x = cos(angle);
				velo.y = sin(angle);
				nowpos.x += velo.x * App::GetApp()->GetElapsedTime() * m_speed;
				nowpos.z += velo.y * App::GetApp()->GetElapsedTime() * m_speed;
				GetComponent<Transform>()->SetPosition(nowpos);
			}

			else if (P2P->GetActive())
			{
				Vector3 topos = P2P->GetComponent<Transform>()->GetPosition();
				Vector3 nowpos = GetComponent<Transform>()->GetPosition();
				Vector3 dir;
				dir = topos - nowpos;
				Vector2 velo = Vector2(dir.x, dir.z);
				float angle = atan2(velo.y, velo.x);
				velo.x = cos(angle);
				velo.y = sin(angle);
				nowpos.x += velo.x * App::GetApp()->GetElapsedTime() * m_speed;
				nowpos.z += velo.y * App::GetApp()->GetElapsedTime() * m_speed;
				GetComponent<Transform>()->SetPosition(nowpos);
			}
		}
		else
		{
			m_time += App::GetApp()->GetElapsedTime();
			if (m_time > m_StopTime)
			{
				m_StopFlg = false;
				m_time = 0;
				GetComponent<PNTStaticDraw>()->SetDiffuse(Color4(1, 1, 1, 1));
			}
		}
	}

	void Enemy::StopEnemy()
	{
		m_StopFlg = true;
		m_time = 0;
		GetComponent<PNTStaticDraw>()->SetDiffuse(Color4(1, 1, 1,0.5f));

	}

	void Enemy::ResetPos()
	{
		GetComponent<Transform>()->SetPosition(m_InitPos);
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
		PtrSprite->SetTextureResource(L"BLACK_TX");

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


		/*//モデル版
		// モデルとトランスフォームの間の差分行列
		float angle = (-90) * (3.14159265f / 180);
		Matrix4X4 SpanMat;
		SpanMat.DefTransformation(
		Vector3(1.0f, 0.3f, 1.0f),
		Vector3(0, 0, 0),
		Vector3(0, 0, 0)
		);

		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(L"MagicBook_Model");
		ShadowPtr->SetMeshToTransformMatrix(SpanMat);


		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticModelDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"MagicBook_Model");
		PtrDraw->SetMeshToTransformMatrix(SpanMat);

		//色変える用だけどモデル読み込みだからちょっとやり方変える
		switch (m_MagicContent)
		{
		case Fire:
		//PtrDraw->SetTextureResource(L"MAGICBOOKFIRE_TX");
		PtrDraw->SetDiffuse(Color4(1, 1, 1, 1));
		break;
		case IceFog :
		//PtrDraw->SetTextureResource(L"MAGICBOOKICEFOG_TX");
		PtrDraw->SetDiffuse(Color4(0, 0, 1, 1));
		break;
		default:
		break;
		}



		*/
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

	//--------------------------------------------------------------------------------------
	//	class LimitTime : public GameObject;
	//	用途: 制限時間
	//--------------------------------------------------------------------------------------
	LimitTime::LimitTime(const shared_ptr<Stage>& StagePtr,float LimitTime):
		GameObject(StagePtr),
		m_LimitTime(LimitTime)
	{}
	
	void LimitTime::OnCreate()
	{
		auto DrawP = AddComponent<PCTSpriteDraw>();
		DrawP->SetTextureResource(L"TIME_TX");
		auto TranP = AddComponent<Transform>();
		TranP->SetPosition(800,470,0);
		TranP->SetRotation(0, 0, 0);
		TranP->SetScale(300, 300, 0);
		SetAlphaActive(true);

		//文字列をつける
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(1700.0f, 15.0f, 2000.0f, 300.0f));
		PtrString->SetFont(L"", 80);
		m_nowTime = m_LimitTime;
		SetDrawLayer(5);
	}

	void LimitTime::OnUpdate()
	{
		m_nowTime += -App::GetApp()->GetElapsedTime();
		wstring txt = Util::IntToWStr((int)m_nowTime);
		GetComponent<StringSprite>()->SetText(txt);

		if (m_nowTime < 1)
		{
			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameOver");
		}
	}

	//--------------------------------------------------------------------------------------
	//	class NumberSprite : public GameObject;
	//	用途: 数字のスプライト
	//--------------------------------------------------------------------------------------
	NumberSprite::NumberSprite(const shared_ptr<Stage>& StagePtr,int numb,Vector2 pos,Vector2 Scale):
		GameObject(StagePtr),
		m_num(numb),
		m_pos(pos),
		m_scale(Scale)
	{}

	void NumberSprite::OnCreate()
	{
		for (int i = 0; i < 10; i++)
		{
			//頂点配列
			vector<VertexPositionNormalTexture> vertices;
			//インデックスを作成するための配列
			vector<uint16_t> indices;
			//Squareの作成(ヘルパー関数を利用)
			MeshUtill::CreateSquare(1.0f, vertices, indices);
			//UV値の変更
			float from = i / 10.0f;
			float to = from + (1.0f / 10.0f);
			//左上頂点
			vertices[0].textureCoordinate = Vector2(from, 0);
			//右上頂点
			vertices[1].textureCoordinate = Vector2(to, 0);
			//左下頂点
			vertices[2].textureCoordinate = Vector2(from, 1.0f);
			//右下頂点
			vertices[3].textureCoordinate = Vector2(to, 1.0f);
			//頂点の型を変えた新しい頂点を作成
			vector<VertexPositionColorTexture> new_vertices;
			for (auto& v : vertices) {
				VertexPositionColorTexture nv;
				nv.position = v.position;
				nv.color = Color4(1.0f, 1.0f, 1.0f, 1.0f);
				nv.textureCoordinate = v.textureCoordinate;
				new_vertices.push_back(nv);
			}
			//メッシュ作成
			m_Mesh.push_back(MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true));
		}
		
		auto TranP = AddComponent<Transform>();
		TranP->SetPosition(m_pos.x,m_pos.y, 0);
		TranP->SetScale(m_scale.x,m_scale.y, 1);
		TranP->SetRotation(0, 0, 0);
		
		auto DrawP = AddComponent<PCTSpriteDraw>();
		DrawP->SetMeshResource(m_Mesh[m_num]);
		DrawP->SetTextureResource(L"NUMBER_TX");
		SetAlphaActive(true);

	}
	//--------------------------------------------------------------------------------------
	//	class PauseMenu : public GameObject;
	//	用途: ポーズメニュー
	//--------------------------------------------------------------------------------------
	PauseMenu::PauseMenu(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
	{}

	void PauseMenu::OnCreate()
	{
		//ポーズのロゴ
		auto TranP = AddComponent<Transform>();
		TranP->SetPosition(Vector3(0,400,0));
		TranP->SetScale(500, 100, 1);
		TranP->SetRotation(0, 0, 0);

		auto DrawP = AddComponent<PCTSpriteDraw>();
		DrawP->SetTextureResource(L"PAUSELOGO_TX");
		SetAlphaActive(true);
		SetDrawActive(false);
		SetDrawLayer(7);

		//暗転
		auto BlackP = GetStage()->AddGameObject<GameObject>();
		auto BTranP = BlackP->AddComponent<Transform>();
		BTranP->SetPosition(0, 0, 0);
		BTranP->SetScale(1920, 1080, 1);
		BTranP->SetRotation(0, 0, 0);
		auto BDrawP = BlackP->AddComponent<PCTSpriteDraw>();
		BDrawP->SetTextureResource(L"BLACK_TX");
		BDrawP->SetDiffuse(Color4(1, 1, 1, 0.5f));

		BlackP->SetDrawLayer(6);
		BlackP->SetAlphaActive(true);
		BlackP->SetDrawActive(false);
		m_Black = BlackP;

		//サイズ
		Vector3 LogoScale = Vector3(500, 200, 1);

		//リトライロゴ
		auto ReTryP = GetStage()->AddGameObject<GameObject>();
		auto RTTP = ReTryP->AddComponent<Transform>();
		RTTP->SetPosition(m_SelectX, 300, 0);
		RTTP->SetScale(LogoScale);
		RTTP->SetRotation(0, 0, 0);
		auto RTDP = ReTryP->AddComponent<PCTSpriteDraw>();
		RTDP->SetTextureResource(L"PAUSERETRY_TX");
		ReTryP->SetAlphaActive(true);
		ReTryP->SetDrawActive(false);
		ReTryP->SetDrawLayer(7);
		m_ReTryLogo = ReTryP;

		//マップロゴ
		auto MaPP = GetStage()->AddGameObject<GameObject>();
		auto MTPP = MaPP->AddComponent<Transform>();
		MTPP->SetPosition(m_NotSelectX, 150, 0);
		MTPP->SetScale(LogoScale);
		MTPP->SetRotation(0, 0, 0);
		auto MDPP = MaPP->AddComponent<PCTSpriteDraw>();
		MDPP->SetTextureResource(L"PAUSEMAPLOGO_TX");
		MaPP->SetAlphaActive(true);
		MaPP->SetDrawActive(false);
		MaPP->SetDrawLayer(7);
		m_mapLogo = MaPP;

		//ステージセレクトロゴ
		auto SSP = GetStage()->AddGameObject<GameObject>();
		auto SSTP = SSP->AddComponent<Transform>();
		SSTP->SetPosition(m_NotSelectX, 0, 0);
		SSTP->SetScale(LogoScale);
		SSTP->SetRotation(0, 0, 0);
		auto SSDP = SSP->AddComponent<PCTSpriteDraw>();
		SSDP->SetTextureResource(L"PAUSESTAGESELECTLOGO_TX");
		SSP->SetAlphaActive(true);
		SSP->SetDrawActive(false);
		SSP->SetDrawLayer(7);
		m_StageSelectLogo = SSP;

		//タイトルロゴ
		auto TiP = GetStage()->AddGameObject<GameObject>();
		auto TTP = TiP->AddComponent<Transform>();
		TTP->SetPosition(m_NotSelectX, -150, 0);
		TTP->SetScale(LogoScale);
		TTP->SetRotation(0, 0, 0);
		auto TDP = TiP->AddComponent<PCTSpriteDraw>();
		TDP->SetTextureResource(L"PAUSETITLELOGO_TX");
		TiP->SetAlphaActive(true);
		TiP->SetDrawActive(false);
		TiP->SetDrawLayer(7);
		m_TitleLogo = TiP;

		//マップ画像
		auto MaP = GetStage()->AddGameObject<GameObject>();
		auto MaTP = MaP->AddComponent<Transform>();
		MaTP->SetPosition(0, 0, 0);
		MaTP->SetScale(500,500,1);
		MaTP->SetRotation(0, 0, 0);
		auto MaTDP = MaP->AddComponent<PCTSpriteDraw>();
		MaTDP->SetTextureResource(L"MAP_TX");
		MaP->SetAlphaActive(true);
		MaP->SetDrawActive(false);
		MaP->SetDrawLayer(7);
		m_Map = MaP;

	}

	void PauseMenu::OnUpdate()
	{
		if (m_BlackOutFlg)
		{
			BlackOut();
			return;
		}
		//マップ表示してない
		if (!m_selectMapFlg)
		{
			//ポーズ中かつ暗転入ってない
			if (m_ActivePauseFlg && !m_BlackOutFlg)
			{
				auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
				//決定押されたら
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
				{
					//マップじゃなければ
					if (m_selectnum != 1)
					{
						//暗転状態へ
						m_BlackOutFlg = true;

						m_Black->SetDrawLayer(8);
						return;
					}
					else
					{
						m_Map->SetDrawActive(true);
						m_selectMapFlg = true;
					}
				}
				Vector2 inputXY = Vector2(CntlVec[0].fThumbLX, CntlVec[0].fThumbLY);
				if (!m_moveFlg)
				{
					if (inputXY.y < -0.8f)
					{
						m_moveFlg = true;
						m_selectnum++;
						if (m_selectnum > 3)
						{
							m_selectnum = 0;
						}
					}
					if (inputXY.y > 0.8f)
					{
						m_moveFlg = true;
						m_selectnum--;
						if (m_selectnum < 0)
						{
							m_selectnum = 3;
						}
					}

					//変更あったら
					if (m_moveFlg)
					{
						Vector3 pos;
						switch (m_selectnum)
						{
						case 0:
							//前後の物を移動
							//0なら(3,1)
							//3
							pos = m_TitleLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_NotSelectX;
							m_TitleLogo->GetComponent<Transform>()->SetPosition(pos);
							//1
							pos = m_mapLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_NotSelectX;
							m_mapLogo->GetComponent<Transform>()->SetPosition(pos);

							//0
							pos = m_ReTryLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_SelectX;
							m_ReTryLogo->GetComponent<Transform>()->SetPosition(pos);
							break;
						case 1:
							//0
							pos = m_ReTryLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_NotSelectX;
							m_ReTryLogo->GetComponent<Transform>()->SetPosition(pos);
							//2
							pos = m_StageSelectLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_NotSelectX;
							m_StageSelectLogo->GetComponent<Transform>()->SetPosition(pos);
							//1
							pos = m_mapLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_SelectX;
							m_mapLogo->GetComponent<Transform>()->SetPosition(pos);

							break;
						case 2:
							//1
							pos = m_mapLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_NotSelectX;
							m_mapLogo->GetComponent<Transform>()->SetPosition(pos);
							//3
							pos = m_TitleLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_NotSelectX;
							m_TitleLogo->GetComponent<Transform>()->SetPosition(pos);
							//2
							pos = m_StageSelectLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_SelectX;
							m_StageSelectLogo->GetComponent<Transform>()->SetPosition(pos);
							break;
						case 3:
							//0
							pos = m_ReTryLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_NotSelectX;
							m_ReTryLogo->GetComponent<Transform>()->SetPosition(pos);
							//2
							pos = m_StageSelectLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_NotSelectX;
							m_StageSelectLogo->GetComponent<Transform>()->SetPosition(pos);
							//3
							pos = m_TitleLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_SelectX;
							m_TitleLogo->GetComponent<Transform>()->SetPosition(pos);
							break;
						default:
							throw BaseException(
								L"(PauseMenu)変なの入ってる",
								L"",
								L""
								);
							break;
						}
					}
				}
				else if (inputXY.y < 0.1f && inputXY.y > -0.1f)
				{
					m_moveFlg = false;
				}
			}
		}
		//マップ表示してる状態
		else
		{
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
			{
				m_Map->SetDrawActive(false);
				m_selectMapFlg = false;
			}
		}
	}

	void PauseMenu::BlackOut()
	{
		if (m_BlackAlpha >= 1.2f)
		{
			auto ScenePtr = App::GetApp()->GetScene<Scene>();

			switch (m_selectnum)
			{
			case 0:
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameStage");

				break;
			case 2:
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"StageSelect");

				break;
			case 3:
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"Title");

				break;

			default:
				break;
			}
		}
		else
		{
			m_BlackAlpha += +0.01f;
			m_Black->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));
		}
	}

	void PauseMenu::Pause()
	{
		//フラグ反転
		m_ActivePauseFlg = !m_ActivePauseFlg;
		//それぞれ実体or透明化
		SetDrawActive(m_ActivePauseFlg);
		m_Black->SetDrawActive(m_ActivePauseFlg);
		m_ReTryLogo->SetDrawActive(m_ActivePauseFlg);
		m_mapLogo->SetDrawActive(m_ActivePauseFlg);
		m_StageSelectLogo->SetDrawActive(m_ActivePauseFlg);
		m_TitleLogo->SetDrawActive(m_ActivePauseFlg);

		m_Map->SetDrawActive(false);
		m_selectMapFlg = false;
		m_selectnum = 0;

		//位置調整
		Vector3 pos;
		//0
		pos = m_ReTryLogo->GetComponent<Transform>()->GetPosition();
		pos.x = m_SelectX;
		m_ReTryLogo->GetComponent<Transform>()->SetPosition(pos);

		//1
		pos = m_mapLogo->GetComponent<Transform>()->GetPosition();
		pos.x = m_NotSelectX;
		m_mapLogo->GetComponent<Transform>()->SetPosition(pos);
		//2
		pos = m_StageSelectLogo->GetComponent<Transform>()->GetPosition();
		pos.x = m_NotSelectX;
		m_StageSelectLogo->GetComponent<Transform>()->SetPosition(pos);
		//3
		pos = m_TitleLogo->GetComponent<Transform>()->GetPosition();
		pos.x = m_NotSelectX;
		m_TitleLogo->GetComponent<Transform>()->SetPosition(pos);


	}
	//--------------------------------------------------------------------------------------
	//	class MenuIcon : public GameObject;
	//	用途: メニューボタンのアイコン
	//--------------------------------------------------------------------------------------
	MenuIcon::MenuIcon(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
	{}

	void MenuIcon::OnCreate()
	{
		auto DrawP = AddComponent<PCTSpriteDraw>();
		DrawP->SetTextureResource(L"MENUICON_TX");
		auto TranP = AddComponent<Transform>();
		TranP->SetPosition(450,-450, 0);
		TranP->SetRotation(0, 0, 0);
		TranP->SetScale(100, 100, 0);
		SetAlphaActive(true);
		SetDrawLayer(5);

	}

	//--------------------------------------------------------------------------------------
	//	class Gimmick1 : public GameObject;
	//	用途: 氷。炎の魔法[Fire]で溶かせる
	//--------------------------------------------------------------------------------------
	Gimmick1::Gimmick1(const shared_ptr<Stage>& StagePtr,Vector3 pos,Vector3 scale):
		GameObject(StagePtr),
		m_InitPos(pos),
		m_Scale(scale)
	{}

	void Gimmick1::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_Scale);
		Ptr->SetRotation(0, 0, 0);

		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionObb>();

		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");
		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		//描画するテクスチャを設定
		PtrDraw->SetTextureResource(L"GIMMICK1_TX");

		//透明処理
		SetAlphaActive(true);

	}

	void Gimmick1::Delete(MagicType MT)
	{
		if (MT == Fire)
		{
			m_ActiveFlg = false;
			SetDrawActive(false);
			GetComponent<Transform>()->SetPosition(0, -10, 0);
			GetComponent<CollisionObb>()->SetUpdateActive(false);
			
		}
	}

	//--------------------------------------------------------------------------------------
	//	class Gimmick2 : public GameObject;
	//	用途: 風車、炎で消せる
	//--------------------------------------------------------------------------------------
	Gimmick2::Gimmick2(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_Scale(scale)
	{}

	void Gimmick2::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_Scale);
		Ptr->SetRotation(0, 0, 0);

		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionObb>();

		// モデルとトランスフォームの間の差分行列
		float angle = (-90) * (3.14159265f / 180);
		Matrix4X4 SpanMat;
		SpanMat.DefTransformation(
			Vector3(1.0f, 0.3f, 1.0f),
			Vector3(0,angle, 0),
			Vector3(0, 0, 0)
			);

		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		//ShadowPtr->SetMeshResource(L"Windmill_Model");
		ShadowPtr->SetMeshResource(L"Windmill_Model");
		ShadowPtr->SetMeshToTransformMatrix(SpanMat);


		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticModelDraw>();
		//描画するメッシュを設定
		//PtrDraw->SetMeshResource(L"Windmill_Model");
		PtrDraw->SetMeshResource(L"Windmill_Model");
		PtrDraw->SetMeshToTransformMatrix(SpanMat);

		//透明処理
		SetAlphaActive(true);

	}

	void Gimmick2::Delete(MagicType MT)
	{
		if (MT == Fire)
		{
			m_ActiveFlg = false;
			SetDrawActive(false);
			GetComponent<Transform>()->SetPosition(0, -10, 0);
			GetComponent<CollisionObb>()->SetUpdateActive(false);

		}
	}

	//--------------------------------------------------------------------------------------
	//	class Water : public GameObject;
	//	用途: 水。コア部分以外
	//--------------------------------------------------------------------------------------
	Water::Water(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale,int num) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale),
		m_myNum(num)
	{}

	void Water::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_InitScale);
		Ptr->SetRotation(0, 0, 0);

		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionObb>();
		//影をつける（シャドウマップを描画する）
		//auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		//ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		//描画コンポーネントの設定
		//auto PtrDraw = AddComponent<PNTStaticDraw>();
		//描画するメッシュを設定
		//PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//描画するテクスチャを設定
		//PtrDraw->SetTextureResource(L"WATER_TX");

		//透明処理
		//SetAlphaActive(true);

		auto ObjPtr = GetStage()->AddGameObject<GameObject>();
		auto OPT = ObjPtr->AddComponent<Transform>();
		Vector3 ObPos = m_InitPos;
		ObPos.y += -m_InitScale.y / 2.5f;
		OPT->SetPosition(ObPos);
		OPT->SetScale(m_InitScale);
		OPT->SetRotation(0, 0, 0);
		auto OPD = ObjPtr->AddComponent<PNTStaticDraw>();
		OPD->SetMeshResource(L"DEFAULT_CUBE");
		OPD->SetTextureResource(L"WATER_TX");

		m_waterunder = ObjPtr;


	}

	//凍らす
	void Water::Freeze()
	{
		GetComponent<CollisionObb>()->SetUpdateActive(false);
		m_waterunder->GetComponent<PNTStaticDraw>()->SetTextureResource(L"ICE_TX");

	}
	//溶かす
	void Water::Melt()
	{
		GetComponent<CollisionObb>()->SetUpdateActive(true);
		m_waterunder->GetComponent<PNTStaticDraw>()->SetTextureResource(L"WATER_TX");

	}
	//止める
	void Water::Stop()
	{

	}
	//流す
	void Water::Flow()
	{

	}



	//--------------------------------------------------------------------------------------
	//	class Gimmick3 : public GameObject;
	//	用途: 川。のコア部分。凍らせると水部分を凍らせる
	//--------------------------------------------------------------------------------------
	Gimmick3::Gimmick3(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale):
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale)
	{}

	void Gimmick3::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_InitScale);
		Ptr->SetRotation(0, 0, 0);

		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionObb>();
		//影をつける（シャドウマップを描画する）
		//auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		//ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		//描画コンポーネントの設定
		//auto PtrDraw = AddComponent<PNTStaticDraw>();
		//描画するメッシュを設定
		//PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//描画するテクスチャを設定
		//PtrDraw->SetTextureResource(L"WATER_TX");

		//透明処理
		//SetAlphaActive(true);

		auto ObjPtr = GetStage()->AddGameObject<GameObject>();
		auto OPT = ObjPtr->AddComponent<Transform>();
		Vector3 ObPos = m_InitPos;
		ObPos.y += -m_InitScale.y / 2.5f;
		OPT->SetPosition(ObPos);
		OPT->SetScale(m_InitScale);
		OPT->SetRotation(0, 0, 0);
		auto OPD = ObjPtr->AddComponent<PNTStaticDraw>();
		OPD->SetMeshResource(L"DEFAULT_CUBE");
		OPD->SetTextureResource(L"WATER_TX");

		m_waterunder = ObjPtr;
	}


	//魔法が当たった時
	void Gimmick3::HitMagic(MagicType MT)
	{
		//凍ってたら溶かす
		if (m_FreezeFlg && MT == Fire)
		{
			Melt();
			m_FreezeFlg = false;
		}

		//凍ってなかったら凍らせる
		if (!m_FreezeFlg && MT == IceFog)
		{
			Freeze();	
			m_FreezeFlg = true;
		}
	}

	//凍らす
	void Gimmick3::Freeze()
	{
		GetComponent<CollisionObb>()->SetUpdateActive(false);
		m_waterunder->GetComponent<PNTStaticDraw>()->SetTextureResource(L"ICE_TX");
		for (auto v : m_waters)
		{
			v->Freeze();
		}
	}

	//溶かす
	void Gimmick3::Melt()
	{
		GetComponent<CollisionObb>()->SetUpdateActive(true);
		m_waterunder->GetComponent<PNTStaticDraw>()->SetTextureResource(L"WATER_TX");
		for (auto v : m_waters)
		{
			v->Melt();
		}
	}

	//止める
	void Gimmick3::Stop()
	{

	}

	//流す
	void Gimmick3::Flow()
	{

	}


	//--------------------------------------------------------------------------------------
	//	class Gimmick5 : public GameObject;
	//	用途: 炎。氷の魔法[Icefog]で消せる
	//--------------------------------------------------------------------------------------

	Gimmick5::Gimmick5(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_Scale(scale)
	{}

	void Gimmick5::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_Scale);
		Ptr->SetRotation(0, 0, 0);

		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionObb>();

		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");
		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		//描画するテクスチャを設定
		PtrDraw->SetTextureResource(L"GIMMICK5_TX");

		//透明処理
		SetAlphaActive(true);
	}

	void Gimmick5::Delete(MagicType MT)
	{
		if (MT == IceFog)
		{
			m_ActiveFlg = false;
			SetDrawActive(false);
			GetComponent<Transform>()->SetPosition(0, -10, 0);
			GetComponent<CollisionObb>()->SetUpdateActive(false);

		}
	}
}
//end basecross
