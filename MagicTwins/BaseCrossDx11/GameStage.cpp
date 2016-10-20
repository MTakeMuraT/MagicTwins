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
		strTexture = DataDir + L"trace2.png";
		App::GetApp()->RegisterTexture(L"TRACE2_TX", strTexture);
		strTexture = DataDir + L"sky.png";
		App::GetApp()->RegisterTexture(L"SKY_TX", strTexture);
		strTexture = DataDir + L"goal.png";
		App::GetApp()->RegisterTexture(L"GOAL_TX", strTexture);
		strTexture = DataDir + L"MagicBookFire.png";
		App::GetApp()->RegisterTexture(L"MAGICBOOKFIRE_TX", strTexture);
		strTexture = DataDir + L"MagicBookIceFog.png";
		App::GetApp()->RegisterTexture(L"MAGICBOOKICEFOG_TX", strTexture);

	}



	//ビューとライトの作成
	void GameStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>()
			;
		//ビューのカメラの設定(右スティックで向きを変えられる)
		//auto Camera = ObjectFactory::Create<LookAtCamera>();
		//PtrView->SetCamera(Camera);
		//Camera->SetEye(Vector3(0.0f, 1.0f, -8.0f));
		//Camera->SetAt(Vector3(0.0f, 0.0f, 0.0f));

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

	//プレイヤーの作成
	void GameStage::CreatePlayer() {
		
		//プレーヤーの作成
		auto PlayerPtr = AddGameObject<Player>(Vector3(0,0.125f,0),true,"Player1");
		//シェア配列にプレイヤーを追加
		SetSharedGameObject(L"Player1", PlayerPtr);
		
		
		//プレーヤーの作成2体目
		auto PlayerPtr2 = AddGameObject<Player>(Vector3(10, 0.125f, 0), false, "Player2");
		//シェア配列にプレイヤーを追加
		SetSharedGameObject(L"Player2", PlayerPtr2);
		

	}

	//魔導書作成
	void GameStage::CreateMagicBook()
	{
		auto MBGroup = CreateSharedObjectGroup(L"MagicBook");

		auto MagBooP = AddGameObject<MagicBook>(Vector3(2, 0.3f, 2), Fire);
		MBGroup->IntoGroup(MagBooP);

		MagBooP = AddGameObject<MagicBook>(Vector3(0, 0.3f, 2), IceFog);
		MBGroup->IntoGroup(MagBooP);

	}

	//ゴールの作成
	void GameStage::CreateGoal()
	{
		//ゴール作成
		auto GoalP = AddGameObject<Goal>(Vector3(-5, 0.5f, 3),Vector3(1,1,1));
		SetSharedGameObject(L"Goal", GoalP);

	}

	//コリジョンマネージャー作成
	void GameStage::CreateCollisionManager()
	{
		//アタリ判定管理オブジェクト作成
		auto ColManP = AddGameObject<CollisionManager>();
	}

	void GameStage::OnCreate() {
		try {
			//リソースの作成
			CreateResourses();
			//ビューとライトの作成
			CreateViewLight();
			//プレートの作成
			CreatePlate();
			//プレーヤーの作成
			CreatePlayer();
			//魔導書作成
			CreateMagicBook();
			//ゴールの作成
			CreateGoal();
			//コリジョンマネージャー作成
			CreateCollisionManager();
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
