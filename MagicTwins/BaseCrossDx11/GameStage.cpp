/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------


	//���\�[�X�̍쐬
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

		//�A�j���[�V�����H
		//auto StaticModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Chara_Rst.bmf");
		//App::GetApp()->RegisterResource(L"Chara_Rst_MESH", StaticModelMesh);

	}



	//�r���[�ƃ��C�g�̍쐬
	void GameStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>()
			;
		//�r���[�̃J�����̐ݒ�(�E�X�e�B�b�N�Ō�����ς�����)
		/*auto Camera = ObjectFactory::Create<LookAtCamera>();
		PtrView->SetCamera(Camera);
		Camera->SetEye(Vector3(0.0f, 1.0f, -8.0f));
		Camera->SetAt(Vector3(0.0f, 0.0f, 0.0f));*/

		//�r���[�̃J�����̐ݒ�(�J�����Œ�)
		auto PtrCamera = PtrView->GetCamera();
		PtrCamera->SetEye(Vector3(0.0f, 5.0f, -5.0f));
		PtrCamera->SetAt(Vector3(0.0f, 0.0f, 0.0f));

		//�V���O�����C�g�̍쐬
		auto PtrSingleLight = CreateLight<SingleLight>();
		//���C�g�̐ݒ�
		PtrSingleLight->GetLight().SetPositionToDirectional(-0.25f, 1.0f, -0.25f);
	}


	//�v���[�g�̍쐬
	void GameStage::CreatePlate() {
		//�X�e�[�W�ւ̃Q�[���I�u�W�F�N�g�̒ǉ�
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

		//�`��R���|�[�l���g�̒ǉ�
		auto DrawComp = Ptr->AddComponent<PNTStaticDraw>();
		//�`��R���|�[�l���g�Ɍ`��i���b�V���j��ݒ�
		DrawComp->SetMeshResource(L"DEFAULT_SQUARE");
		//�����ɉe���f�肱�ނ悤�ɂ���
		DrawComp->SetOwnShadowActive(true);

		//�`��R���|�[�l���g�e�N�X�`���̐ݒ�
		DrawComp->SetTextureResource(L"SKY_TX");
	}
	/*
	//�v���C���[�̍쐬
	void GameStage::CreatePlayer(Vector3 pos) {

		//�v���[���[�̍쐬
		auto PlayerPtr = AddGameObject<Player>(Vector3(pos),true,"Player1");
		//�V�F�A�z��Ƀv���C���[��ǉ�
		SetSharedGameObject(L"Player1", PlayerPtr);


	}

	//�v���C���[�̍쐬�Q�̖�
	void GameStage::CreatePlayer2(Vector3 pos) {

		//�v���[���[�̍쐬2�̖�
		auto PlayerPtr2 = AddGameObject<Player>(Vector3(pos), false, "Player2");
		//�V�F�A�z��Ƀv���C���[��ǉ�
		SetSharedGameObject(L"Player2", PlayerPtr2);


	}

	////�������쐬
	//void GameStage::CreateMagicBook(vector<Vector3> pos)
	//{
	//	auto MBGroup = CreateSharedObjectGroup(L"MagicBook");

	//	int count = 1;

	//	//�Ȃ�enum�̏������Ă���Ȃ����璼�ł�
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
	//�������쐬
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

	//�S�[���̍쐬
	void GameStage::CreateGoal(Vector3 pos, Vector3 scale)
	{
		//�S�[���쐬
		auto GoalP = AddGameObject<Goal>(pos,scale);
		SetSharedGameObject(L"Goal", GoalP);
		GetSharedObjectGroup(L"MagicObjects")->IntoGroup(GoalP);
	}

	//���쐬
	void GameStage::CreateBox(vector<Vector3> pos, vector<Vector3> scale, vector<Vector3> rot)
	{
		int count = 0;
		for (auto v : pos)
		{
			//pos��v�łƂ�邯�ǃX�P�[���Ƃ�Ȃ�����ʂłƂ�
			Vector3 ToScale = scale[count];
			//rot��������
			Vector3 ToRot = rot[count];
			AddGameObject<Box>(v, ToScale, ToRot);
			count++;
		}
	}

	//�M�~�b�N�n****************************************************
	//�M�~�b�N��
	//�X(�M�~�b�N�P)
	void GameStage::CreateIce(vector<Vector3> pos, vector<Vector3> scale)
	{
		int count = 0;
		for (auto v : pos)
		{
			//pos��v�łƂ�邯�ǃX�P�[���Ƃ�Ȃ�����ʂłƂ�
			Vector3 ToScale = scale[count];
			//�X
			GetSharedObjectGroup(L"MagicObjects")->IntoGroup(AddGameObject<Gimmick1>(v, ToScale));
			count++;
		}
	}
	//��(�M�~�b�N�T)
	void GameStage::CreateFire(vector<Vector3> pos, vector<Vector3> scale)
	{
		int count = 0;
		for (auto v : pos)
		{
			//pos��v�łƂ�邯�ǃX�P�[���Ƃ�Ȃ�����ʂłƂ�
			Vector3 ToScale = scale[count];
			//��
			GetSharedObjectGroup(L"MagicObjects")->IntoGroup(AddGameObject<Gimmick5>(v, ToScale));
			count++;
		}
	}
	//����(�M�~�b�N�Q)
	void GameStage::CreateWindMill(vector<Vector3> pos, vector<Vector3> scale)
	{
		int count = 0;
		for (auto v : pos)
		{
			//pos��v�łƂ�邯�ǃX�P�[���Ƃ�Ȃ�����ʂłƂ�
			Vector3 ToScale = scale[count];
			//��
			GetSharedObjectGroup(L"MagicObjects")->IntoGroup(AddGameObject<Gimmick2>(v, ToScale));
			count++;
		}
	}
	//��
	void GameStage::CreateWaters(vector<Vector3> pos, vector<Vector3> scale,vector<int> num)
	{
		auto Group = CreateSharedObjectGroup(L"Waters");

		int count = 0;
		for (auto v : pos)
		{
			//pos��v�łƂ�邯�ǃX�P�[���Ƃ�Ȃ�����ʂłƂ�
			Vector3 ToScale = scale[count];
			int numb = num[count];
			Group->IntoGroup(AddGameObject<Water>(v, ToScale,numb));
			count++;
		}

	}
	//��̃R�A(�M�~�b�N�R)
	void GameStage::CreateWaterCore(vector<Vector3> pos, vector<Vector3> scale)
	{
		int count = 0;
		for (auto v : pos)
		{
			//pos��v�łƂ�邯�ǃX�P�[���Ƃ�Ȃ�����ʂłƂ�
			Vector3 ToScale = scale[count];
			//��̃R�A
			auto ObjP = AddGameObject<Gimmick3>(Vector3(-2, 0, 2), Vector3(1, 1, 1));
			GetSharedObjectGroup(L"MagicObjects")->IntoGroup(ObjP);
			//�R�A�ɑΉ����������擾
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

	//�M�~�b�N�n****************************************************
	*/


	//�������ԍ쐬
	void GameStage::CreateLimitTime()
	{
		auto LTP = AddGameObject<LimitTime>(1000);
		SetSharedGameObject(L"LimitTime", LTP);
	}

	
	//�R���W�����}�l�[�W���[�쐬
	void GameStage::CreateCollisionManager()
	{
		//�A�^������Ǘ��I�u�W�F�N�g�쐬
		auto ColManP = AddGameObject<CollisionManager>();
	}
	

	void GameStage::OnUpdate()
	{
		//*�e�X�g�p
		auto key = App::GetApp()->GetInputDevice().GetKeyState();
		if (key.m_bPressedKeyTbl[VK_SPACE])
		{
			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameStage");

		}
		//*�e�X�g�p
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
			//���\�[�X�̍쐬
			CreateResourses();
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�v���[�g�̍쐬
			CreatePlate();
			//CSV�쐬
			AddGameObject<CSVReader>();
			//�������Ԃ̍쐬
			CreateLimitTime();
			//�R���W�����}�l�[�W���[�쐬
			CreateCollisionManager();

			/*
			//�v���[���[�̍쐬
			CreatePlayer(Vector3(0, 0.125f, 0));
			CreatePlayer2(Vector3(10, 0.125f, 0));
			//�������쐬
			CreateSharedObjectGroup(L"MagicBook");
			CreateMagicFire(Vector3(2, 0.3f, -2));
			CreateMagicIceFog(Vector3(8, 0.3f, 4));

			//vector<Vector3> MagicPoss;
			//MagicPoss.push_back(Vector3(2, 0.3f, -2));//��
			//MagicPoss.push_back(Vector3(8, 0.3f, 4));//�X
			//CreateMagicBook(MagicPoss);
			//�S�[���̍쐬
			CreateGoal(Vector3(-4, 0.5f, 5), Vector3(1, 1, 1));
			//�������Ԃ̍쐬
			CreateLimitTime();


			//�M�~�b�N�쐬
			//��
			//GetSharedObjectGroup(L"MagicObjects")->IntoGroup(AddGameObject<Gimmick5>(Vector3(-4, 0.5f, 4), Vector3(1, 1, 1)));
			//����
			//GetSharedObjectGroup(L"MagicObjects")->IntoGroup(AddGameObject<Gimmick2>(Vector3(9, 0, 2), Vector3(1, 3, 1)));
			//��̃R�A
			//GetSharedObjectGroup(L"MagicObjects")->IntoGroup(AddGameObject<Gimmick3>(Vector3(-2, 0, 2), Vector3(1, 1, 1)));



			////�����u���b�N�쐬�̂��̂�CSV�łȂ�Ƃ����
			////����
			//AddGameObject<TransBlock>(Vector3(-6,0,0), Vector3(1,1,13));
			//AddGameObject<TransBlock>(Vector3(6, 0, 0), Vector3(1, 1, 13));
			//AddGameObject<TransBlock>(Vector3(0, 0, 6), Vector3(13, 1, 1));
			//AddGameObject<TransBlock>(Vector3(0, 0, -6), Vector3(13, 1, 1));

			////�E��
			//AddGameObject<TransBlock>(Vector3(16, 0, 0), Vector3(1, 1, 13));
			//AddGameObject<TransBlock>(Vector3(10, 0, 6), Vector3(13, 1, 1));
			//AddGameObject<TransBlock>(Vector3(10, 0, -6), Vector3(13, 1, 1));

			////��
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


			//��
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

			//�X
			vector<Vector3> posIce;
			vector<Vector3> scaleIce;
			//��
			vector<Vector3> posFire;
			posFire.push_back(Vector3(-4, 0.5f, 4));
			vector<Vector3> scaleFire;
			scaleFire.push_back(Vector3(1, 1, 1));
			//����
			vector<Vector3> posWind;
			posWind.push_back(Vector3(9, 0, 2));
			vector<Vector3> scaleWind;
			scaleWind.push_back(Vector3(1, 3, 1));
			//��̃R�A
			vector<Vector3> posWaCo;
			posWaCo.push_back(Vector3(-2, 0, 2));
			vector<Vector3> scaleWaCo;
			scaleWaCo.push_back(Vector3(1, 1, 1));

			//�X(�M�~�b�N�P)
			CreateIce(posIce, scaleIce);
			//��(�M�~�b�N�T)
			CreateFire(posFire, scaleFire);
			//����(�M�~�b�N�Q)
			CreateWindMill(posWind, scaleWind);
			//��
			CreateWaters(posWa, scaleWa, numWa);
			//��̃R�A(�M�~�b�N�R)
			CreateWaterCore(posWaCo, scaleWaCo);

			*/
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
