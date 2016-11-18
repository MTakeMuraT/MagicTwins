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
		strTexture = DataDir + L"MagicBookWind.png";
		App::GetApp()->RegisterTexture(L"MAGICBOOKWIND_TX", strTexture);

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
		//�n��
		strTexture = DataDir + L"panel.png";
		App::GetApp()->RegisterTexture(L"PANEL_TX", strTexture);
		//�G�l�~�[
		strTexture = DataDir + L"enemy.png";
		App::GetApp()->RegisterTexture(L"ENEMY_TX", strTexture);
		//���C�t
		strTexture = DataDir + L"Life00.png";
		App::GetApp()->RegisterTexture(L"LIFE0_TX", strTexture);
		strTexture = DataDir + L"Life01.png";
		App::GetApp()->RegisterTexture(L"LIFE1_TX", strTexture);
		strTexture = DataDir + L"Life02.png";
		App::GetApp()->RegisterTexture(L"LIFE2_TX", strTexture);
		strTexture = DataDir + L"Life03.png";
		App::GetApp()->RegisterTexture(L"LIFE3_TX", strTexture);
		//���@UI
		strTexture = DataDir + L"icon_magic.png";
		App::GetApp()->RegisterTexture(L"MAGICUI_TX", strTexture);
		strTexture = DataDir + L"TimeWindow_01.png";
		App::GetApp()->RegisterTexture(L"TIME_TX", strTexture);
		//���j���[�A�C�R��
		strTexture = DataDir + L"Menuicon.png";
		App::GetApp()->RegisterTexture(L"MENUICON_TX", strTexture);
		//���@
		strTexture = DataDir + L"FireEf.png";
		App::GetApp()->RegisterTexture(L"FIREEF_TX", strTexture);
		//�|�[�Y���j���[
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
			Vector3(1.0f, 1.0f, 1.0f),
			Qt,
			Vector3(0.0f, 0.0f, 0.0f)
			);
		PtrTrans->SetScale(20.0f, 20.0f, 1.0f);
		PtrTrans->SetQuaternion(Qt);
		Vector3 pos = GetSharedGameObject<Player>(L"Player1", false)->GetComponent<Transform>()->GetPosition();
		pos.y = 0;
		PtrTrans->SetPosition(pos);

		//�`��R���|�[�l���g�̒ǉ�
		auto DrawComp = Ptr->AddComponent<PNTStaticDraw>();
		//�`��R���|�[�l���g�Ɍ`��i���b�V���j��ݒ�
		DrawComp->SetMeshResource(L"DEFAULT_SQUARE");
		//�����ɉe���f�肱�ނ悤�ɂ���
		DrawComp->SetOwnShadowActive(true);

		//�`��R���|�[�l���g�e�N�X�`���̐ݒ�
		DrawComp->SetTextureResource(L"PANEL_TX");

		//�X�e�[�W�ւ̃Q�[���I�u�W�F�N�g�̒ǉ�
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

		//�`��R���|�[�l���g�̒ǉ�
		DrawComp = Ptr->AddComponent<PNTStaticDraw>();
		//�`��R���|�[�l���g�Ɍ`��i���b�V���j��ݒ�
		DrawComp->SetMeshResource(L"DEFAULT_SQUARE");
		//�����ɉe���f�肱�ނ悤�ɂ���
		DrawComp->SetOwnShadowActive(true);

		//�`��R���|�[�l���g�e�N�X�`���̐ݒ�
		DrawComp->SetTextureResource(L"PANEL_TX");

	}

	//�������ԍ쐬
	void GameStage::CreateLimitTime()
	{
		auto LTP = AddGameObject<LimitTime>(1000);
		SetSharedGameObject(L"LimitTime", LTP);
		GetSharedObjectGroup(L"SetUpdateObj")->IntoGroup(LTP);
	}

	
	//�R���W�����}�l�[�W���[�쐬
	void GameStage::CreateCollisionManager()
	{
		//�A�^������Ǘ��I�u�W�F�N�g�쐬
		auto ColManP = AddGameObject<CollisionManager>();
	}
	
	//�A�C�R���쐬
	void GameStage::CreateIcons()
	{
		AddGameObject<MenuIcon>();
	}

	//�|�[�Y���j���[�쐬
	void GameStage::CreatePauseMenu() 
	{
		SetSharedGameObject(L"PauseMenu", AddGameObject<PauseMenu>());
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
		//�|�[�Y
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
			//*�e�X�g�p

		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_BACK)
			{
				auto ScenePtr = App::GetApp()->GetScene<Scene>();
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameStage");

			}
			//�|�[�Y
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START)
			{
				auto PauseP = GetSharedGameObject<PauseMenu>(L"PauseMenu", false);
				//�Ó]��Ԃ���Ȃ����
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
			//�|�[�Y�Ƃ��ŃA�b�v�f�[�g�~�߂�I�u�W�F�N�g
			CreateSharedObjectGroup(L"SetUpdateObj");
			//���\�[�X�̍쐬
			CreateResourses();
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//CSV�쐬
			AddGameObject<CSVReader>();
			//�v���[�g�̍쐬
			CreatePlate();
			//�������Ԃ̍쐬
			CreateLimitTime();
			//�|�[�Y���j���[�쐬
			CreatePauseMenu();
			//�R���W�����}�l�[�W���[�쐬
			CreateCollisionManager();
			//�A�C�R���쐬
			CreateIcons();

		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
