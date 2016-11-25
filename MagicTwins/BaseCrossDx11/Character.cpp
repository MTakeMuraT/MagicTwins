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
	//	class Rock : public GameObject;
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
	//	class Fence : public GameObject;
	//	用途: 柵
	//--------------------------------------------------------------------------------------
	Fence::Fence(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, Vector3 rot) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale),
		m_InitRot(rot)
	{}

	void Fence::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		m_InitScale *= 0.9f;
		Ptr->SetScale(m_InitScale);
		Ptr->SetRotation(m_InitRot);

		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionObb>();

		// モデルとトランスフォームの間の差分行列
		float angle = (-90) * (3.14159265f / 180);
		Matrix4X4 SpanMat;
		SpanMat.DefTransformation(
			Vector3(1.0f, 1.0f, 1.0f),
			Vector3(0,0, 0),
			Vector3(0, -0.5f, 0)
			);

		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(L"Fence_Model");
		ShadowPtr->SetMeshToTransformMatrix(SpanMat);


		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticModelDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"Fence_Model");
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
		case Wind:
			PtrDraw->SetTextureResource(L"MAGICBOOKWIND_TX");
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

		auto numobj = GetStage()->AddGameObject<NumberSprite>(0, Vector2(830, 470), Vector2(100, 100), 6);
		m_numberSp = numobj;
	}

	void LimitTime::OnUpdate()
	{
		//wstring txt = Util::IntToWStr((int)m_nowTime);
		//GetComponent<StringSprite>()->SetText(txt);

		//時間経過処理
		m_nowTime += -App::GetApp()->GetElapsedTime();

		//スプライト変更
		m_numberSp->SetNum((int)m_nowTime);

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
	NumberSprite::NumberSprite(const shared_ptr<Stage>& StagePtr,int numb,Vector2 pos,Vector2 Scale,int layer):
		GameObject(StagePtr),
		m_num(numb),
		m_pos(pos),
		m_scale(Scale),
		m_layer(layer)
	{}

	void NumberSprite::OnCreate()
	{
		//数字の大きさによって回数変更
		int count = m_num;
		do
		{
			count /= 10;
			m_digit++;
		} while (count > 0);

		//数字のスプライト作成
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

		int masternum = m_num;
		
		//桁分ループ
		for (int j = m_digit-1; j >= 0; j--)
		{
			//生成桁数追加
			m_Constdigit++;

			int digi = j;
			int num = masternum / pow(10, (digi));
			masternum = masternum % (int)(pow(10, (digi)));

			auto NumP = GetStage()->AddGameObject<GameObject>();

			float distance = m_scale.x / 1.8f;

			auto TranP = NumP->AddComponent<Transform>();
			TranP->SetPosition(m_pos.x - (distance*((m_digit-1)-j)), m_pos.y, 0);
			TranP->SetScale(m_scale.x, m_scale.y, 1);
			TranP->SetRotation(0, 0, 0);

			auto DrawP = NumP->AddComponent<PCTSpriteDraw>();
			DrawP->SetTextureResource(L"NUMBER_TX");
			DrawP->SetMeshResource(m_Mesh[num]);
			NumP->SetAlphaActive(true);

			NumP->SetDrawLayer(m_layer);
			m_Numbers.push_back(NumP);
		}
	}

	void NumberSprite::SetNum(int num)
	{
		m_num = num;
		//入力された桁持ってくる
		int digit = 0;
		int innum = num;
		do
		{
			innum /= 10;
			digit++;
		} while (innum > 0);

		//入力されたほうが大きかったら
		if (digit > m_digit)
		{
			for (int j = 0; j < (digit - m_Constdigit); j++)
			{
				//左側に桁追加
				int digitDif = digit - m_digit;

					m_Constdigit++;

					auto NumP = GetStage()->AddGameObject<GameObject>();

					float distance = m_scale.x / 1.8f;

					auto TranP = NumP->AddComponent<Transform>();
					TranP->SetPosition(m_pos.x - (distance*(m_digit)), m_pos.y, 0);
					TranP->SetScale(m_scale.x, m_scale.y, 1);
					TranP->SetRotation(0, 0, 0);

					auto DrawP = NumP->AddComponent<PCTSpriteDraw>();
					DrawP->SetTextureResource(L"NUMBER_TX");
					DrawP->SetMeshResource(m_Mesh[0]);
					NumP->SetAlphaActive(true);

					NumP->SetDrawLayer(m_layer);
					m_Numbers.push_back(NumP);
			}
		
			for (int i = 0; i < m_Constdigit; i++)
			{
				m_Numbers[i]->SetDrawActive(true);
			}
		}

		//入力されたほうが小さい
		if (digit < m_digit)
		{
			for (int i = m_digit - 1; i > digit - 1; i--)
			{
				m_Numbers[i]->SetDrawActive(false);
			}
		}

		//桁更新
		m_digit = digit;

		//数字入れ替え
		int masternum = m_num;
		for (int i = m_digit-1; i >= 0; i--)
		{
			int digi = i;
			int setnum = masternum / pow(10, (digi));
			masternum = masternum % (int)(pow(10, (digi)));

			m_Numbers[i]->GetComponent<PCTSpriteDraw>()->SetMeshResource(m_Mesh[setnum]);
		}
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
		Vector3 LogoScale = Vector3(400, 400, 1);

		//リトライロゴ
		auto ReTryP = GetStage()->AddGameObject<GameObject>();
		auto RTTP = ReTryP->AddComponent<Transform>();
		//RTTP->SetPosition(m_SelectX, 300, 0);
		RTTP->SetPosition(-500, -400, 0);
		RTTP->SetScale(m_SelectScale);
		RTTP->SetRotation(0, 0, 0);
		auto RTDP = ReTryP->AddComponent<PCTSpriteDraw>();
		RTDP->SetTextureResource(L"PAUSERETRY_TX");
		ReTryP->SetAlphaActive(true);
		ReTryP->SetDrawActive(false);
		ReTryP->SetDrawLayer(7);
		m_ReTryLogo = ReTryP;

		/*
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
		*/

		//ステージセレクトロゴ
		auto SSP = GetStage()->AddGameObject<GameObject>();
		auto SSTP = SSP->AddComponent<Transform>();
		//SSTP->SetPosition(m_NotSelectX, 0, 0);
		SSTP->SetPosition(0, -400, 0);
		SSTP->SetScale(m_NotSelectScale);
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
		//TTP->SetPosition(m_NotSelectX, -150, 0);
		TTP->SetPosition(500, -400, 0);
		TTP->SetScale(m_NotSelectScale);
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
				{/*
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
					*/

					//暗転状態へ
					m_BlackOutFlg = true;

					m_Black->SetDrawLayer(8);
					return;

				}
				Vector2 inputXY = Vector2(CntlVec[0].fThumbLX, CntlVec[0].fThumbLY);
				if (!m_moveFlg)
				{
					if (inputXY.x > 0.8f)
					{
						m_moveFlg = true;
						m_selectnum++;
						if (m_selectnum > 2)
						{
							m_selectnum = 0;
						}
					}
					if (inputXY.x < -0.8f)
					{
						m_moveFlg = true;
						m_selectnum--;
						if (m_selectnum < 0)
						{
							m_selectnum = 2;
						}
					}

					//変更あったら
					if (m_moveFlg)
					{
						//Vector3 pos;
						Vector3 scale;
						switch (m_selectnum)
						{
						case 0:
							m_ReTryLogo->GetComponent<Transform>()->SetScale(m_SelectScale);
							m_StageSelectLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
							m_TitleLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);

							/*
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
							*/
							break;
						case 1:
							m_ReTryLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
							m_StageSelectLogo->GetComponent<Transform>()->SetScale(m_SelectScale);
							m_TitleLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);

							/*
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
							*/
							break;
						case 2:
							m_ReTryLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
							m_StageSelectLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
							m_TitleLogo->GetComponent<Transform>()->SetScale(m_SelectScale);

							/*
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
							*/
							break;
							/*
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
							*/
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
				else if (inputXY.x < 0.1f && inputXY.x > -0.1f)
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
			case 1:
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"StageSelect");

				break;
			case 2:
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
		//m_mapLogo->SetDrawActive(m_ActivePauseFlg);
		m_StageSelectLogo->SetDrawActive(m_ActivePauseFlg);
		m_TitleLogo->SetDrawActive(m_ActivePauseFlg);

		m_Map->SetDrawActive(m_ActivePauseFlg);
		m_selectMapFlg = false;
		m_selectnum = 0;

		//サイズ調整
		m_ReTryLogo->GetComponent<Transform>()->SetScale(m_SelectScale);
		m_StageSelectLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
		m_TitleLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);

		/*
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
		*/

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
	//	class ScoreItem : public GameObject;
	//	用途:　スコアアイテム
	//--------------------------------------------------------------------------------------
	ScoreItem::ScoreItem(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale):
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale)
	{}

	void ScoreItem::OnCreate()
	{
		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");
		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//メッシュを設定
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");

		//テクスチャを設定
		PtrDraw->SetTextureResource(L"SCOREITEM_TX");

		SetAlphaActive(true);

		auto TranP = AddComponent<Transform>();
		TranP->SetPosition(m_InitPos);
		TranP->SetScale(m_InitScale);
		TranP->SetRotation(0, 0, 0);


		//****仮	
		Kieru();
		//****仮
	}

	void ScoreItem::Delete()
	{
		m_Active = false;
		SetDrawActive(false);
		GetComponent<Transform>()->SetPosition(0, -10, 0);

	}

	void ScoreItem::Detekuru()
	{
		if (m_Active)
		{
			GetComponent<Transform>()->SetPosition(m_InitPos);
		}
	}

	void ScoreItem::Kieru()
	{
		if (m_Active)
		{
			GetComponent<Transform>()->SetPosition(0, -10, 0);
		}
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
			GetComponent<CollisionObb>()->SetUpdateActive(false);
			GetComponent<Transform>()->SetPosition(0, -10, 0);
			
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
			GetComponent<CollisionObb>()->SetUpdateActive(false);
			SetDrawActive(false);
			GetComponent<Transform>()->SetPosition(0, -10, 0);
			m_ActiveFlg = false;
		}

		if (MT == Wind)
		{
			GetStage()->GetSharedGameObject<Gimmick2_1>(L"WaterGate", false)->Action();
		}
	}

	//--------------------------------------------------------------------------------------
	//	class Gimmick2_1 : public GameObject;
	//	用途:　風車に風当てると閉じる水門
	//--------------------------------------------------------------------------------------
		Gimmick2_1::Gimmick2_1(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale):
			GameObject(StagePtr),
			m_InitPos(pos),
			m_Scale(scale)
		{}

		void Gimmick2_1::OnCreate()
		{
		
			auto Ptr = GetComponent<Transform>();
			Ptr->SetScale(m_Scale);
			Ptr->SetRotation(0, 0, 0);
			Ptr->SetPosition(m_InitPos);

			//影をつける（シャドウマップを描画する）
			auto ShadowPtr = AddComponent<Shadowmap>();
			//影の形（メッシュ）を設定
			ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");
			//描画コンポーネントの設定
			auto PtrDraw = AddComponent<PNTStaticDraw>();
			//メッシュを設定
			PtrDraw->SetMeshResource(L"DEFAULT_CUBE");

			//テクスチャを設定
			PtrDraw->SetTextureResource(L"WATERGATE_TX");

			//透明処理
			SetAlphaActive(true);

			auto PtrCol = AddComponent<CollisionObb>();
			PtrCol->SetUpdateActive(false);
		}

		void Gimmick2_1::OnUpdate()
		{
			if (m_MoveFlg)
			{
				Vector3 pos = GetComponent<Transform>()->GetPosition();
				//閉じてる最中
				if (m_CloseFlg)
				{
					pos.y += -0.02f;
					if (pos.y <= m_targetY)
					{
						m_MoveFlg = false;
						pos.y = m_targetY;
						//水閉じる
						auto WaterCoreGroupVec = GetStage()->GetSharedObjectGroup(L"WaterCoreGate")->GetGroupVector();
						for (auto v : WaterCoreGroupVec)
						{
							auto WCP = dynamic_pointer_cast<Gimmick3>(v.lock());
							WCP->Stop();
						}
						//アタリつける
						GetComponent<CollisionObb>()->SetUpdateActive(true);

						//スコアアイテム出現
						//****仮
						auto SIGV = GetStage()->GetSharedObjectGroup(L"ScoreItem")->GetGroupVector();
						for (auto v : SIGV)
						{
							auto Ptr = dynamic_pointer_cast<ScoreItem>(v.lock());
							Ptr->Detekuru();
						}
						//****仮
					}
				}
				//開いてる最中
				else
				{
					pos.y += 0.02f;
					if (pos.y >= m_targetY)
					{
						m_MoveFlg = false;
						pos.y = m_targetY;
						//水開く
						auto WaterCoreGroupVec = GetStage()->GetSharedObjectGroup(L"WaterCoreGate")->GetGroupVector();
						for (auto v : WaterCoreGroupVec)
						{
							auto WCP = dynamic_pointer_cast<Gimmick3>(v.lock());
							WCP->Flow();
						}
						//スコアアイテム消える
						//****仮
						auto SIGV = GetStage()->GetSharedObjectGroup(L"ScoreItem")->GetGroupVector();
						for (auto v : SIGV)
						{
							auto Ptr = dynamic_pointer_cast<ScoreItem>(v.lock());
							Ptr->Kieru();
						}
						//****仮
					}
				}
				GetComponent<Transform>()->SetPosition(pos);
			}
		}

		void Gimmick2_1::Action()
		{
			if (!m_MoveFlg)
			{
				//開く
				if (m_CloseFlg)
				{
					Vector3 pos = GetComponent<Transform>()->GetPosition();
					m_targetY = pos.y + m_Scale.y;

					m_CloseFlg = false;
					m_MoveFlg = true;

					//アタリ消す
					GetComponent<CollisionObb>()->SetUpdateActive(false);

				}
				//閉じる
				else
				{
					Vector3 pos = GetComponent<Transform>()->GetPosition();
					m_targetY = pos.y + -m_Scale.y;

					m_CloseFlg = true;
					m_MoveFlg = true;

				}
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
		GetComponent<CollisionObb>()->SetUpdateActive(false);

		//水の部分
		Vector3 pos = m_waterunder->GetComponent<Transform>()->GetPosition();
		pos.y += -m_InitScale.y;
		m_waterunder->GetComponent<Transform>()->SetPosition(pos);

	}
	//流す
	void Water::Flow()
	{
		//水の部分
		Vector3 pos = m_waterunder->GetComponent<Transform>()->GetPosition();
		pos.y += m_InitScale.y;
		m_waterunder->GetComponent<Transform>()->SetPosition(pos);

		GetComponent<CollisionObb>()->SetUpdateActive(true);
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
		//アタリ判定の部分
		GetComponent<CollisionObb>()->SetUpdateActive(false);

		//水の部分
		Vector3 pos = m_waterunder->GetComponent<Transform>()->GetPosition();
		pos.y += -m_InitScale.y;
		m_waterunder->GetComponent<Transform>()->SetPosition(pos);

			for (auto v : m_waters)
		{
			v->Stop();
		}
	}

	//流す
	void Gimmick3::Flow()
	{
		//アタリ判定の部分
		GetComponent<CollisionObb>()->SetUpdateActive(true);

		//水の部分
		Vector3 pos = m_waterunder->GetComponent<Transform>()->GetPosition();
		pos.y += m_InitScale.y;
		m_waterunder->GetComponent<Transform>()->SetPosition(pos);


		for (auto v : m_waters)
		{
			v->Flow();
		}
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
			GetComponent<CollisionObb>()->SetUpdateActive(false);
			GetComponent<Transform>()->SetPosition(0, -10, 0);

		}
	}
}
//end basecross
