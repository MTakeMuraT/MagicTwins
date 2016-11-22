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
		strTexture = DataDir + L"PauseReTryLogo.png";
		App::GetApp()->RegisterTexture(L"PAUSERETRY_TX", strTexture);
		strTexture = DataDir + L"PauseMapLogo.png";
		App::GetApp()->RegisterTexture(L"PAUSEMAPLOGO_TX", strTexture);
		strTexture = DataDir + L"PauseStageSelect.png";
		App::GetApp()->RegisterTexture(L"PAUSESTAGESELECTLOGO_TX", strTexture);
		strTexture = DataDir + L"PauseTitleLogo.png";
		App::GetApp()->RegisterTexture(L"PAUSETITLELOGO_TX", strTexture);
		strTexture = DataDir + L"map/map.png";
		App::GetApp()->RegisterTexture(L"MAP_TX", strTexture);

		
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
		auto LTP = AddGameObject<LimitTime>(1000);
		SetSharedGameObject(L"LimitTime", LTP);
		GetSharedObjectGroup(L"SetUpdateObj")->IntoGroup(LTP);
	}

	
	//コリジョンマネージャー作成
	void GameStage::CreateCollisionManager()
	{
		//アタリ判定管理オブジェクト作成
		auto ColManP = AddGameObject<CollisionManager>();
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

	void GameStage::OnUpdate()
	{
		//*テスト用
		auto key = App::GetApp()->GetInputDevice().GetKeyState();
		if (key.m_bPressedKeyTbl[VK_SPACE])
		{
			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameStage");

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
			CreatePlate();
			//制限時間の作成
			CreateLimitTime();
			//ポーズメニュー作成
			CreatePauseMenu();
			//コリジョンマネージャー作成
			CreateCollisionManager();
			//アイコン作成
			CreateIcons();

			CreateSharedObjectGroup(L"obj1");
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
