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
		strTexture = DataDir + L"Gimmick1.png";
		App::GetApp()->RegisterTexture(L"GIMMICK1_TX", strTexture);
		strTexture = DataDir + L"Gimmick2.png";
		App::GetApp()->RegisterTexture(L"GIMMICK2_TX", strTexture);
		strTexture = DataDir + L"water.png";
		App::GetApp()->RegisterTexture(L"WATER_TX", strTexture);
		strTexture = DataDir + L"Ice.png";
		App::GetApp()->RegisterTexture(L"ICE_TX", strTexture);
		strTexture = DataDir + L"Gimmick5.png";
		App::GetApp()->RegisterTexture(L"GIMMICK5_TX", strTexture);

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
			Vector3(200.0f, 200.0f, 1.0f),
			Qt,
			Vector3(0.0f, 0.0f, 0.0f)
			);
		PtrTrans->SetScale(200.0f, 200.0f, 1.0f);
		PtrTrans->SetQuaternion(Qt);
		PtrTrans->SetPosition(0.0f, 0.0f, 0.0f);

		//描画コンポーネントの追加
		auto DrawComp = Ptr->AddComponent<PNTStaticDraw>();
		//描画コンポーネントに形状（メッシュ）を設定
		DrawComp->SetMeshResource(L"DEFAULT_SQUARE");
		//自分に影が映りこむようにする
		DrawComp->SetOwnShadowActive(true);

		//描画コンポーネントテクスチャの設定
		DrawComp->SetTextureResource(L"SKY_TX");
	}
	/*
	//プレイヤーの作成
	void GameStage::CreatePlayer(Vector3 pos) {

		//プレーヤーの作成
		auto PlayerPtr = AddGameObject<Player>(Vector3(pos),true,"Player1");
		//シェア配列にプレイヤーを追加
		SetSharedGameObject(L"Player1", PlayerPtr);


	}

	//プレイヤーの作成２体目
	void GameStage::CreatePlayer2(Vector3 pos) {

		//プレーヤーの作成2体目
		auto PlayerPtr2 = AddGameObject<Player>(Vector3(pos), false, "Player2");
		//シェア配列にプレイヤーを追加
		SetSharedGameObject(L"Player2", PlayerPtr2);


	}

	////魔導書作成
	//void GameStage::CreateMagicBook(vector<Vector3> pos)
	//{
	//	auto MBGroup = CreateSharedObjectGroup(L"MagicBook");

	//	int count = 1;

	//	//なんかenumの情報もってこれないから直打ち
	//	for (auto v : pos)
	//	{
	//		MagicType MT = None;
	//		switch (count)
	//		{
	//		case 1:
	//			MT = Fire;
	//			break;
	//		case 2:
	//			MT = IceFog;
	//			break;
	//		}
	//		auto MagBooP = AddGameObject<MagicBook>(v, MT);
	//		MBGroup->IntoGroup(MagBooP);
	//		count++;

	//	}
	//}
	//魔導書作成
	void GameStage::CreateMagicFire(Vector3 pos)
	{
		auto MBGroup = GetSharedObjectGroup(L"MagicBook");

		auto MagBooP = AddGameObject<MagicBook>(pos, Fire);
		MBGroup->IntoGroup(MagBooP);

	}

	void GameStage::CreateMagicIceFog(Vector3 pos)
	{
		auto MBGroup = GetSharedObjectGroup(L"MagicBook");

		auto MagBooP = AddGameObject<MagicBook>(pos, IceFog);
		MBGroup->IntoGroup(MagBooP);

	}

	//ゴールの作成
	void GameStage::CreateGoal(Vector3 pos, Vector3 scale)
	{
		//ゴール作成
		auto GoalP = AddGameObject<Goal>(pos,scale);
		SetSharedGameObject(L"Goal", GoalP);
		GetSharedObjectGroup(L"MagicObjects")->IntoGroup(GoalP);
	}

	//箱作成
	void GameStage::CreateBox(vector<Vector3> pos, vector<Vector3> scale, vector<Vector3> rot)
	{
		int count = 0;
		for (auto v : pos)
		{
			//posはvでとれるけどスケールとれないから別でとる
			Vector3 ToScale = scale[count];
			//rotも同じく
			Vector3 ToRot = rot[count];
			AddGameObject<Box>(v, ToScale, ToRot);
			count++;
		}
	}

	//ギミック系****************************************************
	//ギミック類
	//氷(ギミック１)
	void GameStage::CreateIce(vector<Vector3> pos, vector<Vector3> scale)
	{
		int count = 0;
		for (auto v : pos)
		{
			//posはvでとれるけどスケールとれないから別でとる
			Vector3 ToScale = scale[count];
			//氷
			GetSharedObjectGroup(L"MagicObjects")->IntoGroup(AddGameObject<Gimmick1>(v, ToScale));
			count++;
		}
	}
	//炎(ギミック５)
	void GameStage::CreateFire(vector<Vector3> pos, vector<Vector3> scale)
	{
		int count = 0;
		for (auto v : pos)
		{
			//posはvでとれるけどスケールとれないから別でとる
			Vector3 ToScale = scale[count];
			//炎
			GetSharedObjectGroup(L"MagicObjects")->IntoGroup(AddGameObject<Gimmick5>(v, ToScale));
			count++;
		}
	}
	//風車(ギミック２)
	void GameStage::CreateWindMill(vector<Vector3> pos, vector<Vector3> scale)
	{
		int count = 0;
		for (auto v : pos)
		{
			//posはvでとれるけどスケールとれないから別でとる
			Vector3 ToScale = scale[count];
			//炎
			GetSharedObjectGroup(L"MagicObjects")->IntoGroup(AddGameObject<Gimmick2>(v, ToScale));
			count++;
		}
	}
	//川
	void GameStage::CreateWaters(vector<Vector3> pos, vector<Vector3> scale,vector<int> num)
	{
		auto Group = CreateSharedObjectGroup(L"Waters");

		int count = 0;
		for (auto v : pos)
		{
			//posはvでとれるけどスケールとれないから別でとる
			Vector3 ToScale = scale[count];
			int numb = num[count];
			Group->IntoGroup(AddGameObject<Water>(v, ToScale,numb));
			count++;
		}

	}
	//川のコア(ギミック３)
	void GameStage::CreateWaterCore(vector<Vector3> pos, vector<Vector3> scale)
	{
		int count = 0;
		for (auto v : pos)
		{
			//posはvでとれるけどスケールとれないから別でとる
			Vector3 ToScale = scale[count];
			//川のコア
			auto ObjP = AddGameObject<Gimmick3>(Vector3(-2, 0, 2), Vector3(1, 1, 1));
			GetSharedObjectGroup(L"MagicObjects")->IntoGroup(ObjP);
			//コアに対応した水を取得
			auto Group = GetSharedObjectGroup(L"Waters");
			auto GV = Group->GetGroupVector();

			vector<shared_ptr<Water>> WatersVec;
			for (auto v : GV)
			{
				auto WP = dynamic_pointer_cast<Water>(v.lock());
				if (WP->GetmyNum() == count)
				{
					WatersVec.push_back(WP);
				}
			}
			ObjP->SetWaters(WatersVec);

			count++;
		}
	}

	//ギミック系****************************************************
	*/


	//制限時間作成
	void GameStage::CreateLimitTime()
	{
		auto LTP = AddGameObject<LimitTime>(1000);
		SetSharedGameObject(L"LimitTime", LTP);
	}

	
	//コリジョンマネージャー作成
	void GameStage::CreateCollisionManager()
	{
		//アタリ判定管理オブジェクト作成
		auto ColManP = AddGameObject<CollisionManager>();
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
		//*テスト用
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_BACK)
			{
				auto ScenePtr = App::GetApp()->GetScene<Scene>();
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameStage");

			}
		}


	}
	
	void GameStage::OnCreate() {
		try {
			//リソースの作成
			CreateResourses();
			//ビューとライトの作成
			CreateViewLight();
			//プレートの作成
			CreatePlate();
			//CSV作成
			AddGameObject<CSVReader>();
			//制限時間の作成
			CreateLimitTime();
			//コリジョンマネージャー作成
			CreateCollisionManager();

			/*
			//プレーヤーの作成
			CreatePlayer(Vector3(0, 0.125f, 0));
			CreatePlayer2(Vector3(10, 0.125f, 0));
			//魔導書作成
			CreateSharedObjectGroup(L"MagicBook");
			CreateMagicFire(Vector3(2, 0.3f, -2));
			CreateMagicIceFog(Vector3(8, 0.3f, 4));

			//vector<Vector3> MagicPoss;
			//MagicPoss.push_back(Vector3(2, 0.3f, -2));//炎
			//MagicPoss.push_back(Vector3(8, 0.3f, 4));//氷
			//CreateMagicBook(MagicPoss);
			//ゴールの作成
			CreateGoal(Vector3(-4, 0.5f, 5), Vector3(1, 1, 1));
			//制限時間の作成
			CreateLimitTime();


			//ギミック作成
			//炎
			//GetSharedObjectGroup(L"MagicObjects")->IntoGroup(AddGameObject<Gimmick5>(Vector3(-4, 0.5f, 4), Vector3(1, 1, 1)));
			//風車
			//GetSharedObjectGroup(L"MagicObjects")->IntoGroup(AddGameObject<Gimmick2>(Vector3(9, 0, 2), Vector3(1, 3, 1)));
			//川のコア
			//GetSharedObjectGroup(L"MagicObjects")->IntoGroup(AddGameObject<Gimmick3>(Vector3(-2, 0, 2), Vector3(1, 1, 1)));



			////透明ブロック作成のちのちCSVでなんとか作る
			////左壁
			//AddGameObject<TransBlock>(Vector3(-6,0,0), Vector3(1,1,13));
			//AddGameObject<TransBlock>(Vector3(6, 0, 0), Vector3(1, 1, 13));
			//AddGameObject<TransBlock>(Vector3(0, 0, 6), Vector3(13, 1, 1));
			//AddGameObject<TransBlock>(Vector3(0, 0, -6), Vector3(13, 1, 1));

			////右壁
			//AddGameObject<TransBlock>(Vector3(16, 0, 0), Vector3(1, 1, 13));
			//AddGameObject<TransBlock>(Vector3(10, 0, 6), Vector3(13, 1, 1));
			//AddGameObject<TransBlock>(Vector3(10, 0, -6), Vector3(13, 1, 1));

			////左
			//AddGameObject<TransBlock>(Vector3(1, 0, 4), Vector3(9, 1, 1));
			//AddGameObject<TransBlock>(Vector3(-5, 0, 4), Vector3(1, 1, 1));

			vector<Vector3> posBox;
			posBox.push_back(Vector3(-6, 0, 0));
			posBox.push_back(Vector3(6, 0, 0));
			posBox.push_back(Vector3(0, 0, 6));
			posBox.push_back(Vector3(0, 0, -6));

			posBox.push_back(Vector3(16, 0, 0));
			posBox.push_back(Vector3(10, 0, 6));
			posBox.push_back(Vector3(10, 0, -6));

			posBox.push_back(Vector3(1, 0, 4));
			posBox.push_back(Vector3(-5, 0, 4));

			vector<Vector3> scaleBox;
			scaleBox.push_back(Vector3(1, 1, 13));
			scaleBox.push_back(Vector3(1, 1, 13));
			scaleBox.push_back(Vector3(13, 1, 1));
			scaleBox.push_back(Vector3(13, 1, 1));

			scaleBox.push_back(Vector3(1, 1, 13));
			scaleBox.push_back(Vector3(13, 1, 1));
			scaleBox.push_back(Vector3(13, 1, 1));

			scaleBox.push_back(Vector3(9, 1, 1));
			scaleBox.push_back(Vector3(1, 1, 1));

			vector<Vector3> rotBox;
			rotBox.push_back(Vector3(0,0,0));
			rotBox.push_back(Vector3(0, 0, 0));
			rotBox.push_back(Vector3(0, 0, 0));
			rotBox.push_back(Vector3(0, 0, 0));

			rotBox.push_back(Vector3(0, 0, 0));
			rotBox.push_back(Vector3(0, 0, 0));
			rotBox.push_back(Vector3(0, 0, 0));

			rotBox.push_back(Vector3(0, 0, 0));
			rotBox.push_back(Vector3(0, 0, 0));

			CreateBox(posBox,scaleBox,rotBox);


			//川
			vector<Vector3> posWa;
			posWa.push_back(Vector3(2, 0, 2));
			posWa.push_back(Vector3(-3, 0, -1.5f));
			posWa.push_back(Vector3(12.5f, 0, 2));
			posWa.push_back(Vector3(7.5f, 0, 2));

			vector<Vector3> scaleWa;
			scaleWa.push_back(Vector3(7, 1, 1));
			scaleWa.push_back(Vector3(1, 1, 8));
			scaleWa.push_back(Vector3(6, 1, 1));
			scaleWa.push_back(Vector3(2, 1, 1));

			vector<int> numWa;
			numWa.push_back(0);
			numWa.push_back(0);
			numWa.push_back(0);
			numWa.push_back(0);

			//氷
			vector<Vector3> posIce;
			vector<Vector3> scaleIce;
			//炎
			vector<Vector3> posFire;
			posFire.push_back(Vector3(-4, 0.5f, 4));
			vector<Vector3> scaleFire;
			scaleFire.push_back(Vector3(1, 1, 1));
			//風車
			vector<Vector3> posWind;
			posWind.push_back(Vector3(9, 0, 2));
			vector<Vector3> scaleWind;
			scaleWind.push_back(Vector3(1, 3, 1));
			//川のコア
			vector<Vector3> posWaCo;
			posWaCo.push_back(Vector3(-2, 0, 2));
			vector<Vector3> scaleWaCo;
			scaleWaCo.push_back(Vector3(1, 1, 1));

			//氷(ギミック１)
			CreateIce(posIce, scaleIce);
			//炎(ギミック５)
			CreateFire(posFire, scaleFire);
			//風車(ギミック２)
			CreateWindMill(posWind, scaleWind);
			//川
			CreateWaters(posWa, scaleWa, numWa);
			//川のコア(ギミック３)
			CreateWaterCore(posWaCo, scaleWaCo);

			*/
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
