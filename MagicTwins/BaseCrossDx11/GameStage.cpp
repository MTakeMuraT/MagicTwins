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

		//�A�j���[�V�����H
		//auto StaticModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Chara_Rst.bmf");
		//App::GetApp()->RegisterResource(L"Chara_Rst_MESH", StaticModelMesh);

	}



	//�r���[�ƃ��C�g�̍쐬
	void GameStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>()
			;
		//�r���[�̃J�����̐ݒ�(�E�X�e�B�b�N�Ō�����ς�����)
		//auto Camera = ObjectFactory::Create<LookAtCamera>();
		//PtrView->SetCamera(Camera);
		//Camera->SetEye(Vector3(0.0f, 1.0f, -8.0f));
		//Camera->SetAt(Vector3(0.0f, 0.0f, 0.0f));

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

	//�v���C���[�̍쐬
	void GameStage::CreatePlayer() {
		
		//�v���[���[�̍쐬
		auto PlayerPtr = AddGameObject<Player>(Vector3(0,0.125f,0),true,"Player1");
		//�V�F�A�z��Ƀv���C���[��ǉ�
		SetSharedGameObject(L"Player1", PlayerPtr);
		
		
		//�v���[���[�̍쐬2�̖�
		auto PlayerPtr2 = AddGameObject<Player>(Vector3(10, 0.125f, 0), false, "Player2");
		//�V�F�A�z��Ƀv���C���[��ǉ�
		SetSharedGameObject(L"Player2", PlayerPtr2);
		

	}

	//�������쐬
	void GameStage::CreateMagicBook()
	{
		auto MBGroup = CreateSharedObjectGroup(L"MagicBook");

		auto MagBooP = AddGameObject<MagicBook>(Vector3(2, 0.3f, 2), Fire);
		MBGroup->IntoGroup(MagBooP);

		MagBooP = AddGameObject<MagicBook>(Vector3(0, 0.3f, 2), IceFog);
		MBGroup->IntoGroup(MagBooP);

	}

	//�S�[���̍쐬
	void GameStage::CreateGoal()
	{
		//�S�[���쐬
		auto GoalP = AddGameObject<Goal>(Vector3(-5, 0.5f, 3),Vector3(1,1,1));
		SetSharedGameObject(L"Goal", GoalP);

	}

	//�������ԍ쐬
	void GameStage::CreateLimitTime()
	{
		auto LTP = AddGameObject<LimitTime>(10);
		SetSharedGameObject(L"LimitTime", LTP);
	}

	//�R���W�����}�l�[�W���[�쐬
	void GameStage::CreateCollisionManager()
	{
		//�A�^������Ǘ��I�u�W�F�N�g�쐬
		auto ColManP = AddGameObject<CollisionManager>();
	}

	void GameStage::OnCreate() {
		try {
			//���\�[�X�̍쐬
			CreateResourses();
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�v���[�g�̍쐬
			CreatePlate();
			//�v���[���[�̍쐬
			CreatePlayer();
			//�������쐬
			CreateMagicBook();
			//�S�[���̍쐬
			CreateGoal();
			//�������Ԃ̍쐬
			CreateLimitTime();
			//�R���W�����}�l�[�W���[�쐬
			CreateCollisionManager();
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
