/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------


	//リソースの作成
	void GameStage::CreateResourses() {
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = DataDir + L"trace.png";
		App::GetApp()->RegisterTexture(L"TRACE_TX", strTexture);
		strTexture = DataDir + L"trace.png";
		App::GetApp()->RegisterTexture(L"BOX_TX", strTexture);
		//暗転用の黒
		strTexture = DataDir + L"Black.png";
		App::GetApp()->RegisterTexture(L"BLACK_TX", strTexture);
		//数字
		strTexture = DataDir + L"Number.png";
		App::GetApp()->RegisterTexture(L"NUMBER_TX", strTexture);

		strTexture = DataDir + L"trace2.png";
		App::GetApp()->RegisterTexture(L"TRACE2_TX", strTexture);
		strTexture = DataDir + L"MapChip/Leaf.png";
		App::GetApp()->RegisterTexture(L"SKY_TX", strTexture);
		strTexture = DataDir + L"goal.png";
		App::GetApp()->RegisterTexture(L"GOAL_TX", strTexture);
		strTexture = DataDir + L"MagicBookFire.png";
		App::GetApp()->RegisterTexture(L"MAGICBOOKFIRE_TX", strTexture);
		strTexture = DataDir + L"MagicBookIceFog.png";
		App::GetApp()->RegisterTexture(L"MAGICBOOKICEFOG_TX", strTexture);
		strTexture = DataDir + L"MagicBookWind.png";
		App::GetApp()->RegisterTexture(L"MAGICBOOKWIND_TX", strTexture);
		//スコアアイテム
		strTexture = DataDir + L"ScoreItem.png";
		App::GetApp()->RegisterTexture(L"SCOREITEM_TX", strTexture);


		strTexture = DataDir + L"Gimmick1.png";
		App::GetApp()->RegisterTexture(L"GIMMICK1_TX", strTexture);
		strTexture = DataDir + L"Gimmick2.png";
		App::GetApp()->RegisterTexture(L"GIMMICK2_TX", strTexture);
		strTexture = DataDir + L"tex01.png";
		App::GetApp()->RegisterTexture(L"WATERGATE_TX", strTexture);
		strTexture = DataDir + L"water.png";
		App::GetApp()->RegisterTexture(L"WATER_TX", strTexture);
		strTexture = DataDir + L"Ice.png";
		App::GetApp()->RegisterTexture(L"ICE_TX", strTexture);
		strTexture = DataDir + L"Gimmick5.png";
		App::GetApp()->RegisterTexture(L"GIMMICK5_TX", strTexture);
		//地面
		strTexture = DataDir + L"panel.png";
		App::GetApp()->RegisterTexture(L"PANEL_TX", strTexture);
		//エネミー
		strTexture = DataDir + L"enemy.png";
		App::GetApp()->RegisterTexture(L"ENEMY_TX", strTexture);
		//ライフ
		strTexture = DataDir + L"Life00.png";
		App::GetApp()->RegisterTexture(L"LIFE0_TX", strTexture);
		strTexture = DataDir + L"Life01.png";
		App::GetApp()->RegisterTexture(L"LIFE1_TX", strTexture);
		strTexture = DataDir + L"Life02.png";
		App::GetApp()->RegisterTexture(L"LIFE2_TX", strTexture);
		strTexture = DataDir + L"Life03.png";
		App::GetApp()->RegisterTexture(L"LIFE3_TX", strTexture);
		//魔法UI
		strTexture = DataDir + L"icon_magic.png";
		App::GetApp()->RegisterTexture(L"MAGICUI_TX", strTexture);
		//中身
		strTexture = DataDir + L"NullUI.png";
		App::GetApp()->RegisterTexture(L"NULLUI_TX", strTexture);
		strTexture = DataDir + L"FireUI.png";
		App::GetApp()->RegisterTexture(L"FIREUI_TX", strTexture);
		strTexture = DataDir + L"IceUI.png";
		App::GetApp()->RegisterTexture(L"ICEUI_TX", strTexture);
		strTexture = DataDir + L"WindUI.png";
		App::GetApp()->RegisterTexture(L"WINDUI_TX", strTexture);

		//キャラUI
		strTexture = DataDir + L"Chara1UI.png";
		App::GetApp()->RegisterTexture(L"CHARA1UI_TX", strTexture);
		strTexture = DataDir + L"Chara2UI.png";
		App::GetApp()->RegisterTexture(L"CHARA2UI_TX", strTexture);

		//時間
		strTexture = DataDir + L"TimeWindow_01.png";
		App::GetApp()->RegisterTexture(L"TIME_TX", strTexture);
		//メニューアイコン
		strTexture = DataDir + L"Menuicon.png";
		App::GetApp()->RegisterTexture(L"MENUICON_TX", strTexture);
		//魔法
		strTexture = DataDir + L"FireEf.png";
		App::GetApp()->RegisterTexture(L"FIREEF_TX", strTexture);
		//ポーズメニュー
		strTexture = DataDir + L"PauseLogo.png";
		App::GetApp()->RegisterTexture(L"PAUSELOGO_TX", strTexture);
		strTexture = DataDir + L"ReTryLogo.png";
		App::GetApp()->RegisterTexture(L"PAUSERETRY_TX", strTexture);
		//strTexture = DataDir + L"PauseMapLogo.png";
		//App::GetApp()->RegisterTexture(L"PAUSEMAPLOGO_TX", strTexture);
		strTexture = DataDir + L"SelectBackLogo.png";
		App::GetApp()->RegisterTexture(L"PAUSESTAGESELECTLOGO_TX", strTexture);
		strTexture = DataDir + L"TitleBackLogo.png";
		App::GetApp()->RegisterTexture(L"PAUSETITLELOGO_TX", strTexture);
		strTexture = DataDir + L"map/map.png";
		App::GetApp()->RegisterTexture(L"MAP_TX", strTexture);

		//-----------------------------
		//絶対消せ
		strTexture = DataDir + L"W.png";
		App::GetApp()->RegisterTexture(L"W_TX", strTexture);
		strTexture = DataDir + L"I.png";
		App::GetApp()->RegisterTexture(L"I_TX", strTexture);

		//-----------------------------

		//アニメーション？
		//auto StaticModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Chara_Rst.bmf");
		//App::GetApp()->RegisterResource(L"Chara_Rst_MESH", StaticModelMesh);

	}

	//ビューとライトの作成
	void GameStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>()
			;
		//ビューのカメラの設定(右スティックで向きを変えられる)
		/*auto Camera = ObjectFactory::Create<LookAtCamera>();
		PtrView->SetCamera(Camera);
		Camera->SetEye(Vector3(0.0f, 1.0f, -8.0f));
		Camera->SetAt(Vector3(0.0f, 0.0f, 0.0f));*/

		//ビューのカメラの設定(カメラ固定)
		auto PtrCamera = PtrView->GetCamera();
		PtrCamera->SetEye(Vector3(0.0f, 5.0f, -5.0f));
		PtrCamera->SetAt(Vector3(0.0f, 0.0f, 0.0f));

		//シングルライトの作成
		auto PtrSingleLight = CreateLight<SingleLight>();
		//ライトの設定
		PtrSingleLight->GetLight().SetPositionToDirectional(-0.25f, 1.0f, -0.25f);
	}


	//プレートの作成
	void GameStage::CreatePlate() {
		//ステージへのゲームオブジェクトの追加
		auto Ptr = AddGameObject<GameObject>();
		auto PtrTrans = Ptr->GetComponent<Transform>();
		Quaternion Qt;
		Qt.RotationRollPitchYawFromVector(Vector3(XM_PIDIV2, 0, 0));
		Matrix4X4 WorldMat;
		WorldMat.DefTransformation(
			Vector3(1.0f, 1.0f, 1.0f),
			Qt,
			Vector3(0.0f, 0.0f, 0.0f)
			);
		PtrTrans->SetScale(20.0f, 20.0f, 1.0f);
		PtrTrans->SetQuaternion(Qt);
		Vector3 pos = GetSharedGameObject<Player>(L"Player1", false)->GetComponent<Transform>()->GetPosition();
		pos.y = 0;
		PtrTrans->SetPosition(pos);

		//描画コンポーネントの追加
		auto DrawComp = Ptr->AddComponent<PNTStaticDraw>();
		//描画コンポーネントに形状（メッシュ）を設定
		DrawComp->SetMeshResource(L"DEFAULT_SQUARE");
		//自分に影が映りこむようにする
		DrawComp->SetOwnShadowActive(true);

		//描画コンポーネントテクスチャの設定
		DrawComp->SetTextureResource(L"PANEL_TX");

		//ステージへのゲームオブジェクトの追加
		Ptr= AddGameObject<GameObject>();
		PtrTrans = Ptr->GetComponent<Transform>();
		Qt.RotationRollPitchYawFromVector(Vector3(XM_PIDIV2, 0, 0));
		WorldMat.DefTransformation(
			Vector3(1.0f, 1.0f, 1.0f),
			Qt,
			Vector3(0.0f, 0.0f, 0.0f)
			);
		PtrTrans->SetScale(20.0f, 20.0f, 1.0f);
		PtrTrans->SetQuaternion(Qt);
		pos = GetSharedGameObject<Player>(L"Player2", false)->GetComponent<Transform>()->GetPosition();
		pos.y = -0.125f;
		PtrTrans->SetPosition(pos);

		//描画コンポーネントの追加
		DrawComp = Ptr->AddComponent<PNTStaticDraw>();
		//描画コンポーネントに形状（メッシュ）を設定
		DrawComp->SetMeshResource(L"DEFAULT_SQUARE");
		//自分に影が映りこむようにする
		DrawComp->SetOwnShadowActive(true);

		//描画コンポーネントテクスチャの設定
		DrawComp->SetTextureResource(L"PANEL_TX");

	}

	//制限時間作成
	void GameStage::CreateLimitTime()
	{
		auto LTP = AddGameObject<LimitTime>(90);
		SetSharedGameObject(L"LimitTime", LTP);
		GetSharedObjectGroup(L"SetUpdateObj")->IntoGroup(LTP);
	}

	
	//コリジョンマネージャー作成
	void GameStage::CreateCollisionManager()
	{
		//アタリ判定管理オブジェクト作成
		auto ColManP = AddGameObject<CollisionManager>();
		SetSharedGameObject(L"ColMan", ColManP);

	}
	
	//アイコン作成
	void GameStage::CreateIcons()
	{
		AddGameObject<MenuIcon>();
	}

	//ポーズメニュー作成
	void GameStage::CreatePauseMenu() 
	{
		SetSharedGameObject(L"PauseMenu", AddGameObject<PauseMenu>());
	}

	//ゴールした後の処理
	void GameStage::GoalState()
	{
		if (m_GoalState == 0)
		{
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			wstring strTexture = DataDir + L"Result/Result_Logo.png";
			App::GetApp()->RegisterTexture(L"RESULTLOGO_TX", strTexture);
			strTexture = DataDir + L"Result/BookTexture.png";
			App::GetApp()->RegisterTexture(L"BOOK_TX", strTexture);
			strTexture = DataDir + L"Result/Time_Logo.png";
			App::GetApp()->RegisterTexture(L"TIMELOGO_TX", strTexture);
			strTexture = DataDir + L"Result/Time_Logo.png";
			App::GetApp()->RegisterTexture(L"TIMELOGO_TX", strTexture);
			strTexture = DataDir + L"Result/item_Logo.png";
			App::GetApp()->RegisterTexture(L"ITEMLOGO_TX", strTexture);
			strTexture = DataDir + L"Result/Rank_Logo.png";
			App::GetApp()->RegisterTexture(L"RANKLOGO_TX", strTexture);

			strTexture = DataDir + L"Result/Rank_S.png";
			App::GetApp()->RegisterTexture(L"RANKS_TX", strTexture);
			strTexture = DataDir + L"Result/Result_Chara1.png";
			App::GetApp()->RegisterTexture(L"RESULTCHAR1_TX", strTexture);
			strTexture = DataDir + L"Result/Result_Chara2.png";
			App::GetApp()->RegisterTexture(L"RESULTCHAR2_TX", strTexture);

			//選択項目
			strTexture = DataDir + L"Result/NextStage_Logo.png";
			App::GetApp()->RegisterTexture(L"GONEXTSTAGELOGO_TX", strTexture);

		}


		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		bool SkipFlg = false;
		switch (m_GoalState)
		{
			//ゴールロゴ作成
		case 0:
			//なんかこれだといけるっぽい
			if (true)
			{
				auto obj = AddGameObject<GameObject>();
				auto objTrans = obj->AddComponent<Transform>();
				objTrans->SetPosition(0,425,0);
				objTrans->SetScale(2,1.5f,1);
				objTrans->SetRotation(0, 0, 0);
				auto objDraw = obj->AddComponent<PCTSpriteDraw>();
				objDraw->SetTextureResource(L"RESULTLOGO_TX");
				obj->SetAlphaActive(true);
				obj->SetDrawLayer(7);
				m_GoalLogo = obj;
			}
			m_GoalState = 1;
			break;
			//ゴールロゴサイズ大きく
		case 1:
			if (true)
			{

				Vector3 scale = m_GoalLogo->GetComponent<Transform>()->GetScale();
				if (scale.x < 800)
				{
					scale *= 1.1f;
				}
				else
				{
					//二重に動かないように
					SkipFlg = true;

					scale.x = 800;
					scale.y = 600;
					m_GoalState = 2;
					//次で使う本の画像作成
					auto obj = AddGameObject<GameObject>();
					auto objTrans = obj->AddComponent<Transform>();
					objTrans->SetPosition(-1500,0, 0);
					objTrans->SetScale(1000, 650, 1);
					objTrans->SetRotation(0, 0, 0);
					auto objDraw = obj->AddComponent<PCTSpriteDraw>();
					objDraw->SetTextureResource(L"BOOK_TX");
					obj->SetAlphaActive(true);
					obj->SetDrawLayer(7);
					m_Book = obj;

				}

				//ボタン押されたらスキップ
				if (CntlVec[0].bConnected && !SkipFlg)
				{
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
					{
						scale.x = 800;
						scale.y = 600;
						m_GoalState = 2;
						//次で使う本の画像作成
						auto obj = AddGameObject<GameObject>();
						auto objTrans = obj->AddComponent<Transform>();
						objTrans->SetPosition(-1500, 0, 0);
						objTrans->SetScale(1000, 650, 1);
						objTrans->SetRotation(0, 0, 0);
						auto objDraw = obj->AddComponent<PCTSpriteDraw>();
						objDraw->SetTextureResource(L"BOOK_TX");
						obj->SetAlphaActive(true);
						obj->SetDrawLayer(7);
						m_Book = obj;
					}
				}
				m_GoalLogo->GetComponent<Transform>()->SetScale(scale);

			}
			break;
			//左から本の画像持ってくる
		case 2:
			if (true)
			{
				Vector3 pos = m_Book->GetComponent<Transform>()->GetPosition();
				if (pos.x < -400)
				{
					pos.x += 1500 * App::GetApp()->GetElapsedTime();
				}
				else
				{
					//二重に動かないように
					SkipFlg = true;

					m_GoalState = 3;

					//タイムロゴ作成
					auto obj = AddGameObject<GameObject>();
					auto objTrans = obj->AddComponent<Transform>();
					objTrans->SetPosition(-700, 200, 0);
					objTrans->SetScale(300, 300, 1);
					objTrans->SetRotation(0, 0, 0);
					auto objDraw = obj->AddComponent<PCTSpriteDraw>();
					objDraw->SetTextureResource(L"TIMELOGO_TX");
					objDraw->SetDiffuse(Color4(1, 1, 1, 0));
					obj->SetAlphaActive(true);
					obj->SetDrawLayer(7);
					m_TimeLogo = obj;

				}

				//ボタン押されたらスキップ
				if (CntlVec[0].bConnected && !SkipFlg)
				{
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
					{
						pos.x = -400;

						m_GoalState = 3;

						//タイムロゴ作成
						auto obj = AddGameObject<GameObject>();
						auto objTrans = obj->AddComponent<Transform>();
						objTrans->SetPosition(-700, 200, 0);
						objTrans->SetScale(300, 300, 1);
						objTrans->SetRotation(0, 0, 0);
						auto objDraw = obj->AddComponent<PCTSpriteDraw>();
						objDraw->SetTextureResource(L"TIMELOGO_TX");
						objDraw->SetDiffuse(Color4(1, 1, 1, 0));
						obj->SetAlphaActive(true);
						obj->SetDrawLayer(7);
						m_TimeLogo = obj;

					}
				}

				m_Book->GetComponent<Transform>()->SetPosition(pos);

			}
			break;
			//タイム書き込み
		case 3:
			if (true)
			{
				if (m_alpha < 1.0f)
				{
					m_alpha += 1.0f * App::GetApp()->GetElapsedTime();
					m_TimeLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1,m_alpha));
				}
				else
				{
					//二重に動かないように
					SkipFlg = true;

					m_TimeLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1));

					//状態変更＆透明度0
					m_alpha = 0;
					m_GoalState = 4;
					//残り時間計算用初期化
					m_RemainingTime = 0;
					m_LimitTimeGoal = GetSharedGameObject<LimitTime>(L"LimitTime", false)->GetReamingTime();
					m_LimitTimeMax = GetSharedGameObject<LimitTime>(L"LimitTime", false)->GetLimitTime();
					//加算量(大体60fpsで1秒)
					m_AmountTime = (float)(m_LimitTimeMax) / 60;

					//アイテムロゴ作成
					auto obj = AddGameObject<GameObject>();
					auto objTrans = obj->AddComponent<Transform>();
					objTrans->SetPosition(-680, 50, 0);
					objTrans->SetScale(300, 300, 1);
					objTrans->SetRotation(0, 0, 0);
					auto objDraw = obj->AddComponent<PCTSpriteDraw>();
					objDraw->SetTextureResource(L"ITEMLOGO_TX");
					objDraw->SetDiffuse(Color4(1, 1, 1, 0));
					obj->SetAlphaActive(true);
					obj->SetDrawLayer(7);
					m_ScoreItemLogo = obj;

					SetSharedGameObject(L"RemainingNumberSprite",AddGameObject<NumberSprite>(0,Vector2(-250,210),Vector2(100,100),8));
				}


				//ボタン押されたらスキップ
				if (CntlVec[0].bConnected && !SkipFlg)
				{
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
					{
						m_TimeLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1));

						//状態変更＆透明度0
						m_alpha = 0;
						m_GoalState = 4;
						//残り時間計算用初期化
						m_RemainingTime = 0;
						m_LimitTimeGoal = GetSharedGameObject<LimitTime>(L"LimitTime", false)->GetReamingTime();
						m_LimitTimeMax = GetSharedGameObject<LimitTime>(L"LimitTime", false)->GetLimitTime();
						//加算量(大体60fpsで0.5秒)
						m_AmountTime = (float)(m_LimitTimeMax) / 30;

						//アイテムロゴ作成
						auto obj = AddGameObject<GameObject>();
						auto objTrans = obj->AddComponent<Transform>();
						objTrans->SetPosition(-680, 50, 0);
						objTrans->SetScale(300, 300, 1);
						objTrans->SetRotation(0, 0, 0);
						auto objDraw = obj->AddComponent<PCTSpriteDraw>();
						objDraw->SetTextureResource(L"ITEMLOGO_TX");
						objDraw->SetDiffuse(Color4(1, 1, 1, 0));
						obj->SetAlphaActive(true);
						obj->SetDrawLayer(7);
						m_ScoreItemLogo = obj;

						SetSharedGameObject(L"RemainingNumberSprite", AddGameObject<NumberSprite>(0, Vector2(-250, 210), Vector2(100, 100), 8));

					}
				}

			}
			break;
			//残りタイム書き込み
		case 4:
			if (true)
			{
				auto RNS = GetSharedGameObject<NumberSprite>(L"RemainingNumberSprite", false);
				if (m_RemainingTime < m_LimitTimeGoal)
				{
					RNS->SetNum((int)(m_RemainingTime += m_AmountTime));
				}
				else
				{
					//二重に動かないように
					SkipFlg = true;

					m_RemainingTime = m_LimitTimeGoal;
					RNS->SetNum(m_LimitTimeGoal);
					m_GoalState = 5;
				}

				//ボタン押されたらスキップ
				if (CntlVec[0].bConnected && !SkipFlg)
				{
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
					{
						m_RemainingTime = m_LimitTimeGoal;
						RNS->SetNum(m_LimitTimeGoal);
						m_GoalState = 5;

					}
				}
			}
			break;
			//アイテム書き込み
		case 5:
			if (true)
			{				
				if (m_alpha < 1.0f)
				{
					m_alpha += 1.0f * App::GetApp()->GetElapsedTime();
					m_ScoreItemLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_alpha));
				}
				else
				{
					//二重に動かないように
					SkipFlg = true;

					m_alpha = 0;
					m_GoalState = 6;
					m_ScoreItemLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1));


					//スコア取得数書き込み
					m_ScoreItemCount = GetSharedGameObject<CollisionManager>(L"ColMan",false)->GetScoreItem();
					m_AmountScoreCount = (float)(m_ScoreItemCount) / 90;
					//スコア初期化
					m_ScoreItemCountCal = 0;

					SetSharedGameObject(L"ScoreCountNumberSprite", AddGameObject<NumberSprite>(0, Vector2(-250, 50), Vector2(100, 100), 8));
				}


				//ボタン押されたらスキップ
				if (CntlVec[0].bConnected && !SkipFlg)
				{
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
					{
						m_alpha = 0;
						m_GoalState = 6;
						m_ScoreItemLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1));


						//スコア取得数書き込み
						m_ScoreItemCount = GetSharedGameObject<CollisionManager>(L"ColMan", false)->GetScoreItem();
						//1秒
						m_AmountScoreCount = (float)(m_ScoreItemCount) / 60;
						//スコア初期化
						m_ScoreItemCountCal = 0;

						SetSharedGameObject(L"ScoreCountNumberSprite", AddGameObject<NumberSprite>(0, Vector2(-250, 50), Vector2(100, 100), 8));

					}
				}
				
			}
			break;
			//取得数書き込み
		case 6:
			if (true)
			{
				auto SCNP = GetSharedGameObject<NumberSprite>(L"ScoreCountNumberSprite", false);

				if (m_ScoreItemCountCal < m_ScoreItemCount)
				{
					SCNP->SetNum((int)(m_ScoreItemCountCal += m_AmountScoreCount));
				}
				else
				{
					//二重に動かないように
					SkipFlg = true;

					m_ScoreItemCountCal = m_ScoreItemCount;
					m_GoalState = 7;

					SCNP->SetNum((int)m_ScoreItemCount);

					//ランクロゴ作成
					auto obj = AddGameObject<GameObject>();
					auto objTrans = obj->AddComponent<Transform>();
					objTrans->SetPosition(-720, -150, 0);
					objTrans->SetScale(300, 300, 1);
					objTrans->SetRotation(0, 0, 0);
					auto objDraw = obj->AddComponent<PCTSpriteDraw>();
					objDraw->SetTextureResource(L"RANKLOGO_TX");
					objDraw->SetDiffuse(Color4(1, 1, 1, 0));
					obj->SetAlphaActive(true);
					obj->SetDrawLayer(7);
					m_RankLogo = obj;
				}

				//ボタン押されたらスキップ
				if (CntlVec[0].bConnected && !SkipFlg)
				{
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
					{
						m_ScoreItemCountCal = m_ScoreItemCount;
						m_GoalState = 7;

						SCNP->SetNum((int)m_ScoreItemCount);

						//ランクロゴ作成
						auto obj = AddGameObject<GameObject>();
						auto objTrans = obj->AddComponent<Transform>();
						objTrans->SetPosition(-720, -150, 0);
						objTrans->SetScale(300, 300, 1);
						objTrans->SetRotation(0, 0, 0);
						auto objDraw = obj->AddComponent<PCTSpriteDraw>();
						objDraw->SetTextureResource(L"RANKLOGO_TX");
						objDraw->SetDiffuse(Color4(1, 1, 1, 0));
						obj->SetAlphaActive(true);
						obj->SetDrawLayer(7);
						m_RankLogo = obj;

					}
				}

			}
			break;
			//ランク書き込み
		case 7:
			if (true)
			{
				if (m_alpha < 1.0f)
				{
					m_alpha += 1.0f * App::GetApp()->GetElapsedTime();
					m_RankLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_alpha));
				}
				else
				{
					//二重に動かないように
					SkipFlg = true;

					m_RankLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1));

					m_alpha = 0;
					m_GoalState = 8;

					//ランク作成
					auto obj = AddGameObject<GameObject>();
					auto objTrans = obj->AddComponent<Transform>();
					objTrans->SetPosition(-150, -180, 0);
					objTrans->SetScale(300, 300, 1);
					objTrans->SetRotation(0, 0, 0);
					auto objDraw = obj->AddComponent<PCTSpriteDraw>();
					objDraw->SetTextureResource(L"RANKS_TX");
					objDraw->SetDiffuse(Color4(1, 1, 1, 0));
					obj->SetAlphaActive(true);
					obj->SetDrawLayer(7);
					m_RankSprite = obj;
				}

				//ボタン押されたらスキップ
				if (CntlVec[0].bConnected && !SkipFlg)
				{
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
					{
						{
							m_RankLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1));

							m_alpha = 0;
							m_GoalState = 8;

							//ランク作成
							auto obj = AddGameObject<GameObject>();
							auto objTrans = obj->AddComponent<Transform>();
							objTrans->SetPosition(-150, -180, 0);
							objTrans->SetScale(300, 300, 1);
							objTrans->SetRotation(0, 0, 0);
							auto objDraw = obj->AddComponent<PCTSpriteDraw>();
							objDraw->SetTextureResource(L"RANKS_TX");
							objDraw->SetDiffuse(Color4(1, 1, 1, 0));
							obj->SetAlphaActive(true);
							obj->SetDrawLayer(7);
							m_RankSprite = obj;
						}
					}
				}
			}
			break;
			//ランク貼り付け
		case 8:
			if (true)
			{
				if (m_alpha < 1.0f)
				{
					m_alpha += 1.0f * App::GetApp()->GetElapsedTime();
					m_RankSprite->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_alpha));
				}
				else
				{
					//二重に動かないように
					SkipFlg = true;

					m_alpha = 0;
					m_GoalState = 9;
					m_RankSprite->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1));

					//キャラ画像
					auto obj = AddGameObject<GameObject>();
					auto objTrans = obj->AddComponent<Transform>();
					objTrans->SetPosition(1500, -50, 0);
					objTrans->SetScale(600, 600, 1);
					objTrans->SetRotation(0, 0, 0);
					auto objDraw = obj->AddComponent<PCTSpriteDraw>();
					objDraw->SetTextureResource(L"RESULTCHAR1_TX");
					obj->SetAlphaActive(true);
					obj->SetDrawLayer(7);
					m_Char1Sprite = obj;

					obj = AddGameObject<GameObject>();
					objTrans = obj->AddComponent<Transform>();
					objTrans->SetPosition(1500, -50, 0);
					objTrans->SetScale(600, 600, 1);
					objTrans->SetRotation(0, 0, 0);
					objDraw = obj->AddComponent<PCTSpriteDraw>();
					objDraw->SetTextureResource(L"RESULTCHAR2_TX");
					obj->SetAlphaActive(true);
					obj->SetDrawLayer(7);
					m_Char2Sprite = obj;

				}

				//ボタン押されたらスキップ
				if (CntlVec[0].bConnected && !SkipFlg)
				{
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
					{
						{
							m_alpha = 0;
							m_GoalState = 9;
							m_RankSprite->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1));

							//キャラ画像
							auto obj = AddGameObject<GameObject>();
							auto objTrans = obj->AddComponent<Transform>();
							objTrans->SetPosition(1500, -50, 0);
							objTrans->SetScale(600, 600, 1);
							objTrans->SetRotation(0, 0, 0);
							auto objDraw = obj->AddComponent<PCTSpriteDraw>();
							objDraw->SetTextureResource(L"RESULTCHAR1_TX");
							obj->SetAlphaActive(true);
							obj->SetDrawLayer(7);
							m_Char1Sprite = obj;

							obj = AddGameObject<GameObject>();
							objTrans = obj->AddComponent<Transform>();
							objTrans->SetPosition(1500, -50, 0);
							objTrans->SetScale(600, 600, 1);
							objTrans->SetRotation(0, 0, 0);
							objDraw = obj->AddComponent<PCTSpriteDraw>();
							objDraw->SetTextureResource(L"RESULTCHAR2_TX");
							obj->SetAlphaActive(true);
							obj->SetDrawLayer(7);
							m_Char2Sprite = obj;
						}
					}
				}
			}
			break;
			//キャラ右から出てくる
		case 9:
			if (true)
			{
				
				Vector3 pos1 = m_Char1Sprite->GetComponent<Transform>()->GetPosition();
				Vector3 pos2 = m_Char2Sprite->GetComponent<Transform>()->GetPosition();
				float ElaTime = App::GetApp()->GetElapsedTime();

				if (pos1.x > 350)
				{
					pos1.x += -1500 * ElaTime;
				}
				else
				{
					pos1.x = 350;
				}
				if (pos2.x > 600)
				{
					pos2.x += -1200 * ElaTime;
				}
				else
				{
					pos2.x = 600;
				}

				//移動終了
				if (pos1.x == 350 && pos2.x == 600)
				{
					//二重に動かないように
					SkipFlg = true;

					m_GoalState = 10;

					//選択項目作成
					auto obj = AddGameObject<GameObject>();
					auto objTrans = obj->AddComponent<Transform>();
					objTrans->SetPosition(-600, -1000, 0);
					objTrans->SetScale(m_NotSelectScale);
					objTrans->SetRotation(0, 0, 0);
					auto objDraw = obj->AddComponent<PCTSpriteDraw>();
					objDraw->SetTextureResource(L"GONEXTSTAGELOGO_TX");
					obj->SetAlphaActive(true);
					obj->SetDrawLayer(7);
					m_NextStageLogo = obj;

					obj = AddGameObject<GameObject>();
					objTrans = obj->AddComponent<Transform>();
					objTrans->SetPosition(0, -1000, 0);
					objTrans->SetScale(m_NotSelectScale);
					objTrans->SetRotation(0, 0, 0);
					objDraw = obj->AddComponent<PCTSpriteDraw>();
					objDraw->SetTextureResource(L"PAUSESTAGESELECTLOGO_TX");
					obj->SetAlphaActive(true);
					obj->SetDrawLayer(7);
					m_StageSelectLogo = obj;

					obj = AddGameObject<GameObject>();
					objTrans = obj->AddComponent<Transform>();
					objTrans->SetPosition(600, -1000, 0);
					objTrans->SetScale(m_NotSelectScale);
					objTrans->SetRotation(0, 0, 0);
					objDraw = obj->AddComponent<PCTSpriteDraw>();
					objDraw->SetTextureResource(L"PAUSETITLELOGO_TX");
					obj->SetAlphaActive(true);
					obj->SetDrawLayer(7);
					m_TitleLogo = obj;	
				}


				//ボタン押されたらスキップ
				if (CntlVec[0].bConnected&& !SkipFlg)
				{
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
					{
						{
							pos1.x = 350;
							pos2.x = 600;
							m_GoalState = 10;

							//選択項目作成
							auto obj = AddGameObject<GameObject>();
							auto objTrans = obj->AddComponent<Transform>();
							objTrans->SetPosition(-600, -1000, 0);
							objTrans->SetScale(m_NotSelectScale);
							objTrans->SetRotation(0, 0, 0);
							auto objDraw = obj->AddComponent<PCTSpriteDraw>();
							objDraw->SetTextureResource(L"GONEXTSTAGELOGO_TX");
							obj->SetAlphaActive(true);
							obj->SetDrawLayer(7);
							m_NextStageLogo = obj;

							obj = AddGameObject<GameObject>();
							objTrans = obj->AddComponent<Transform>();
							objTrans->SetPosition(0, -1000, 0);
							objTrans->SetScale(m_NotSelectScale);
							objTrans->SetRotation(0, 0, 0);
							objDraw = obj->AddComponent<PCTSpriteDraw>();
							objDraw->SetTextureResource(L"PAUSESTAGESELECTLOGO_TX");
							obj->SetAlphaActive(true);
							obj->SetDrawLayer(7);
							m_StageSelectLogo = obj;

							obj = AddGameObject<GameObject>();
							objTrans = obj->AddComponent<Transform>();
							objTrans->SetPosition(600, -1000, 0);
							objTrans->SetScale(m_NotSelectScale);
							objTrans->SetRotation(0, 0, 0);
							objDraw = obj->AddComponent<PCTSpriteDraw>();
							objDraw->SetTextureResource(L"PAUSETITLELOGO_TX");
							obj->SetAlphaActive(true);
							obj->SetDrawLayer(7);
							m_TitleLogo = obj;

						}
					}
				}

				m_Char1Sprite->GetComponent<Transform>()->SetPosition(pos1);
				m_Char2Sprite->GetComponent<Transform>()->SetPosition(pos2);
			}
			break;
			//選択項目下から出てくる
		case 10:
			if (true)
			{
				Vector3 pos1 = m_NextStageLogo->GetComponent<Transform>()->GetPosition();
				Vector3 pos2 = m_StageSelectLogo->GetComponent<Transform>()->GetPosition();
				Vector3 pos3 = m_TitleLogo->GetComponent<Transform>()->GetPosition();
				float ElaTime = App::GetApp()->GetElapsedTime();

				if (pos1.y < -430)
				{
					pos1.y += 1000 * ElaTime;
				}
				else
				{
					pos1.y = -430;
				}
				if (pos2.y < -430)
				{
					pos2.y += 1000 * ElaTime;
				}
				else
				{
					pos2.y = -430;
				}

				if (pos3.y < -430)
				{
					pos3.y += 1000 * ElaTime;
				}
				else
				{
					pos3.y = -430;
				}


				//移動終了
				if (pos1.y == -430 && pos2.y == -430 && pos3.y == -430)
				{
					//二重に動かないように
					SkipFlg = true;

					m_NextStageLogo->GetComponent<Transform>()->SetScale(m_SelectScale);
					m_GoalState = 11;
				}

				//ボタン押されたらスキップ
				if (CntlVec[0].bConnected && !SkipFlg)
				{
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
					{
						{
							pos1.y = -430;
							pos2.y = -430;
							pos3.y = -430;

							m_NextStageLogo->GetComponent<Transform>()->SetScale(m_SelectScale);
							m_GoalState = 11;

						}
					}
				}

				m_NextStageLogo->GetComponent<Transform>()->SetPosition(pos1);
				m_StageSelectLogo->GetComponent<Transform>()->SetPosition(pos2);
				m_TitleLogo->GetComponent<Transform>()->SetPosition(pos3);


			}
			break;
			//終了、入力待ち
		case 11:
			if (true)
			{
				auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
				if (CntlVec[0].bConnected)
				{
					
					Vector2 InputXY = Vector2(CntlVec[0].fThumbLX, CntlVec[0].fThumbLY);
					bool MoveFlg = false;
					if (m_MoveConFlg)
					{
						//右
						if (InputXY.x > 0.8f)
						{
							m_SelectNum++;
							if (m_SelectNum > 2)
							{
								m_SelectNum = 0;
							}
							m_MoveConFlg = false;
							MoveFlg = true;
						}
						if (InputXY.x < -0.8f)
						{
							m_SelectNum--;
							if (m_SelectNum < 0)
							{
								m_SelectNum = 2;
							}
							m_MoveConFlg = false;
							MoveFlg = true;
						}
					}
					else if (!m_MoveConFlg)
					{
						if (abs(InputXY.x) < 0.1f && abs(InputXY.y) < 0.1f)
						{
							m_MoveConFlg = true;
						}
					}

					//移動したら大きさ変更
					if (MoveFlg)
					{
						switch (m_SelectNum)
						{
							//次のステージ
						case 0:
							m_NextStageLogo->GetComponent<Transform>()->SetScale(m_SelectScale);
							m_StageSelectLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
							m_TitleLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
							break;
							//ステージセレクト
						case 1:
							m_NextStageLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
							m_StageSelectLogo->GetComponent<Transform>()->SetScale(m_SelectScale);
							m_TitleLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
							break;
							//タイトル
						case 2:
							m_NextStageLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
							m_StageSelectLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
							m_TitleLogo->GetComponent<Transform>()->SetScale(m_SelectScale);
							break;
						}
					}
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
					{
						m_GoalState = 12;
					}
				}

			}
			break;
			//選択されたのでシーン移動
		case 12:
			switch (m_SelectNum)
			{
				//次のステージ
			case 0:
				if (true)
				{
					auto ScenePtr = App::GetApp()->GetScene<Scene>();
					int StageNum = ScenePtr->GetStageNum();
					StageNum++;
					ScenePtr->SetStageNum(StageNum);
					PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameStage");
				}
				break;
				//ステセレ
			case 1:
				if (true)
				{
					auto ScenePtr = App::GetApp()->GetScene<Scene>();
					PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"StageSelect");
				}
				break;
				//タイトル
			case 2:
				if (true)
				{
					auto ScenePtr = App::GetApp()->GetScene<Scene>();
					PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"Title");
				}
				break;
			}
			break;
		default:
			break;
		}
		//wstring txt = Util::IntToWStr(m_GoalState);
		//txt += L"\n" + Util::IntToWStr(m_ScoreItemCount);
		//m_StringObj->GetComponent<StringSprite>()->SetText(txt);
	}



	void GameStage::OnUpdate()
	{
		//ゴールした後の処理
		if (m_GoalFlg)
		{
			GoalState();
			return;
		}
		
		//ゴールした瞬間の処理
		if (GetSharedGameObject<GameObject>(L"GoalObj")->GetDrawActive())
		{
			m_GoalFlg = true;
			//アップデート止める
			auto UpdateGroup = GetSharedObjectGroup(L"SetUpdateObj")->GetGroupVector();
			for (auto v : UpdateGroup)
			{
				auto Ptr = dynamic_pointer_cast<GameObject>(v.lock());
				Ptr->SetUpdateActive(false);
			}
			return;
		}

		//*テスト用
		auto key = App::GetApp()->GetInputDevice().GetKeyState();
		if (key.m_bPressedKeyTbl[VK_SPACE])
		{
			//auto ScenePtr = App::GetApp()->GetScene<Scene>();
			//PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameStage");

			GetSharedGameObject<GameObject>(L"GoalObj")->SetDrawActive(true);
		}
		//ポーズ
		if (key.m_bPressedKeyTbl['Q'])
		{
			auto PauseP = GetSharedGameObject<PauseMenu>(L"PauseMenu",false);
			bool PauseFlg = PauseP->GetPause();
			auto SUG = GetSharedObjectGroup(L"SetUpdateObj");
			auto SUGV = SUG->GetGroupVector();
			for (auto v : SUGV)
			{
				auto Ptr = dynamic_pointer_cast<GameObject>(v.lock());
				Ptr->SetUpdateActive(PauseFlg);
			}
			PauseP->Pause();
		}
			//*テスト用

		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_BACK)
			{
				auto ScenePtr = App::GetApp()->GetScene<Scene>();
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameStage");

			}
			//ポーズ
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START)
			{
				auto PauseP = GetSharedGameObject<PauseMenu>(L"PauseMenu", false);
				//暗転状態じゃなければ
				if (!PauseP->GetBlackOut())
				{
					bool PauseFlg = PauseP->GetPause();
					auto SUG = GetSharedObjectGroup(L"SetUpdateObj");
					auto SUGV = SUG->GetGroupVector();
					for (auto v : SUGV)
					{
						auto Ptr = dynamic_pointer_cast<GameObject>(v.lock());
						Ptr->SetUpdateActive(PauseFlg);
					}
					PauseP->Pause();
				}
			}
		}


	}
	
	void GameStage::OnCreate() {
		try {
			//ポーズとかでアップデート止めるオブジェクト
			CreateSharedObjectGroup(L"SetUpdateObj");
			//リソースの作成
			CreateResourses();
			//ビューとライトの作成
			CreateViewLight();
			//CSV作成
			AddGameObject<CSVReader>();
			//プレートの作成
			//CreatePlate();
			//制限時間の作成
			CreateLimitTime();
			//ポーズメニュー作成
			CreatePauseMenu();
			//コリジョンマネージャー作成
			CreateCollisionManager();
			//アイコン作成
			CreateIcons();

			CreateSharedObjectGroup(L"obj1");
			//SEマネージャー
			SetSharedGameObject(L"SEM", AddGameObject<SEManager>());


			//ゴール判定するオブジェクト作成
			auto obj = AddGameObject<GameObject>();
			obj->SetDrawActive(false);
			SetSharedGameObject(L"GoalObj", obj);

			//文字列オブジェクト作成
			auto stringobj = AddGameObject<GameObject>();
			auto PtrString = stringobj->AddComponent<StringSprite>();
			PtrString->SetText(L"");
			PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
			PtrString->SetFont(L"", 80);

			m_StringObj = stringobj;  

		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
