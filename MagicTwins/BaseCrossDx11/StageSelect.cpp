#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void StageSelect::CreateResourses()
	{
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = DataDir + L"StageSelectLogo.png";
		App::GetApp()->RegisterTexture(L"STAGESELECTLOGO_TX", strTexture);
		strTexture = DataDir + L"StageSelect_Back.png";
		App::GetApp()->RegisterTexture(L"SELECTBACK_TX", strTexture);
		//�����摜(��)
		strTexture = DataDir + L"Left.png";
		App::GetApp()->RegisterTexture(L"LEFT_TX", strTexture);
		//�E���摜(��)
		strTexture = DataDir + L"Right.png";
		App::GetApp()->RegisterTexture(L"RIGHT_TX", strTexture);
		//B�{�^��
		strTexture = DataDir + L"ButtonB.png";
		App::GetApp()->RegisterTexture(L"BBUTTON_TX", strTexture);
		//���胍�S
		strTexture = DataDir + L"Kettei.png";
		App::GetApp()->RegisterTexture(L"KETTEI_TX", strTexture);
		//�X�e�[�W�C���[�W�g
		strTexture = DataDir + L"Frame.png";
		App::GetApp()->RegisterTexture(L"FRAME_TX", strTexture);

	}

	void StageSelect::CreateViewLight()
	{

		auto PtrView = CreateView<SingleView>();

		//�r���[�̃J�����̐ݒ�(�J�����Œ�)
		auto PtrCamera = PtrView->GetCamera();
		PtrCamera->SetEye(Vector3(0.0f, 0.0f, -1.0f));
		PtrCamera->SetAt(Vector3(0.0f, 0.0f, 0.0f));


		//�V���O�����C�g�̍쐬
		auto PtrSingleLight = CreateLight<SingleLight>();
		//���C�g�̐ݒ�
		PtrSingleLight->GetLight().SetPositionToDirectional(-0.25f, 1.0f, -0.25f);

	}

	void StageSelect::CreateBack()
	{
		auto SelectBack = AddGameObject<GameObject>();
		SelectBack->AddComponent<Transform>();
		auto PtrTransform = SelectBack->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(0, 0, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(WindowSize.x, WindowSize.y, 1);

		//�X�v���C�g������
		auto PtrSprite = SelectBack->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"SELECTBACK_TX");

		//�����x���f
		SelectBack->SetAlphaActive(true);

		SelectBack->SetDrawLayer(1);

		SetSharedGameObject(L"TiBa", SelectBack);

		//�������t����(��)
		auto Stp = SelectBack->AddComponent<StringSprite>();
		Stp->SetText(L"");
		Stp->SetTextRect(Rect2D<float>(512.0f, 16.0f, 1024.0f, 960.0f));
		Stp->SetFont(L"", 100);

	}

	void StageSelect::CreateSelectLogo()
	{
		auto SelectLogo = AddGameObject<GameObject>();
		SelectLogo->AddComponent<Transform>();
		auto PtrTransform = SelectLogo->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(0, WindowSize.y / 2.5f, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(1000, 200, 1);

		//�X�v���C�g������
		auto PtrSprite = SelectLogo->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"STAGESELECTLOGO_TX");

		SetSharedGameObject(L"SeLo", SelectLogo);

		SelectLogo->SetDrawLayer(2);

		//�����x���f
		SelectLogo->SetAlphaActive(true);

	}

	void StageSelect::CreateStageImage()
	{
		auto StageImage = AddGameObject<GameObject>();
		auto SITranform = StageImage->AddComponent<Transform>();
		SITranform->SetPosition(0,0,0);
		SITranform->SetScale(1200,1200,1);
		SITranform->SetRotation(0, 0, 0);

		auto SIDraw = StageImage->AddComponent<PCTSpriteDraw>();
		SIDraw->SetTextureResource(L"FRAME_TX");

		StageImage->SetAlphaActive(true);

		StageImage->SetDrawLayer(3);
	}

	void StageSelect::SceneChange()
	{
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		ScenePtr->SetStageNum(m_StageNum);
		PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameStage");
	}

	void StageSelect::CreateButtons()
	{
		//B�{�^���쐬
		auto obj1 = AddGameObject<GameObject>();
		auto OT1 = obj1->AddComponent<Transform>();
		OT1->SetPosition(300, -400, 0);
		OT1->SetScale(100, 100, 1);
		OT1->SetRotation(0, 0, 0);
		auto OD1 = obj1->AddComponent<PCTSpriteDraw>();
		OD1->SetTextureResource(L"BBUTTON_TX");
		obj1->SetAlphaActive(true);
		obj1->SetDrawLayer(3);

		auto obj2 = AddGameObject<GameObject>();
		auto OT2 = obj2->AddComponent<Transform>();
		OT2->SetPosition(450, -400, 0);
		OT2->SetScale(250, 160, 1);
		OT2->SetRotation(0, 0, 0);
		auto OD2 = obj2->AddComponent<PCTSpriteDraw>();
		OD2->SetTextureResource(L"KETTEI_TX");
		obj2->SetAlphaActive(true);
		obj2->SetDrawLayer(3);

		/*
		auto obj2 = AddGameObject<GameObject>();
		auto OT2 = obj2->AddComponent<Transform>();
		OT2->SetPosition(500, -400, 0);
		OT2->SetScale(100, 100, 1);
		OT2->SetRotation(0, 0, 0);
		auto OD2 = obj2->AddComponent<PCTSpriteDraw>();
		OD2->SetTextureResource(L"ABUTTON_TX");
		obj2->SetAlphaActive(true);
		obj2->SetDrawLayer(3);
		*/
	}

	//�����(��)
	void StageSelect::Left()
	{
		auto Left = AddGameObject<GameObject>();
		Left->AddComponent<Transform>();
		auto PtrTransform = Left->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(-890, 0, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(150, 150, 1);

		//�X�v���C�g��t����
		auto PtrSprite = Left->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"LEFT_TX");

		SetSharedGameObject(L"Left", Left);

		Left->SetDrawLayer(2);

		auto PtrAction = Left->AddComponent<Action>();
		PtrAction->AddMoveBy(1.5, Vector3(100, 0, 0));
		PtrAction->AddMoveBy(1.5, Vector3(-100, 0, 0));
		PtrAction->SetLooped(true);
		PtrAction->Run();

		//�����x���f
		Left->SetAlphaActive(true);
		GetSharedGameObject<GameObject>(L"TiBa", false)->GetComponent<StringSprite>()->SetText(L"0");

	}

	//�E���(��)
	void StageSelect::Right()
	{
		auto Right = AddGameObject<GameObject>();
		Right->AddComponent<Transform>();
		auto PtrTransform = Right->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(890, 0, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(150, 150, 1);

		//�X�v���C�g��t����
		auto PtrSprite = Right->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"RIGHT_TX");

		SetSharedGameObject(L"Right", Right);

		Right->SetDrawLayer(2);

		auto PtrAction = Right->AddComponent<Action>();
		PtrAction->AddMoveBy(1.5, Vector3(-100, 0, 0));
		PtrAction->AddMoveBy(1.5, Vector3(100, 0, 0));
		PtrAction->SetLooped(true);
		PtrAction->Run();

		//�����x���f
		Right->SetAlphaActive(true);
		GetSharedGameObject<GameObject>(L"TiBa", false)->GetComponent<StringSprite>()->SetText(L"0");
	}


	void StageSelect::OnCreate()
	{
		try {
			//���\�[�X�̍쐬
			CreateResourses();
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�w�i�쐬
			CreateBack();
			//���S�쐬
			CreateSelectLogo();
			//�{�^���쐬
			CreateButtons();
			//�X�e�[�W�C���[�W�쐬
			CreateStageImage();
			//�����(��)
			Left();
			//�E���(��)
			Right();
			//���E�V�[���J��(��)
			m_StageNum = 1;
			m_flag = true;

			//SE�}�l�[�W���[
			SetSharedGameObject(L"SEM", AddGameObject<SEManager>());

		}
		catch (...) {
			throw;
		}




	}

	void StageSelect::OnUpdate()
	{


		//���E�ŃV�[���J��(��)
		auto ShareObject = GetSharedGameObject<GameObject>(L"TiBa", false);
		auto ShareString = ShareObject->GetComponent<StringSprite>();

		wstring sceneNum(L"");


		//*�e�X�g�p
		auto key = App::GetApp()->GetInputDevice().GetKeyState();
		if (key.m_bPressedKeyTbl[VK_SPACE])
		{
			SceneChange();
		}
		//*�e�X�g�p

		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B||
				CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
			{
				SceneChange();
			}
			//���E�V�[���J��(��)
			if (CntlVec[0].fThumbLX > 0 && m_flag&&m_StageNum<m_MaxStageNum)
			{

				m_StageNum++;
				m_flag = false;

			}
			if (CntlVec[0].fThumbLX < 0 && m_flag&&m_StageNum>0)
			{
				m_StageNum--;
				m_flag = false;
			}
			if (CntlVec[0].fThumbLX == 0)
			{
				m_flag = true;
			}

		}
		sceneNum += Util::IntToWStr(m_StageNum);
		ShareString->SetText(sceneNum);
			auto Left = GetSharedGameObject<GameObject>(L"Left");

		if (m_StageNum != 0)
		{
			Left->SetDrawActive(true);
		}

		else {
			/*if (m_SceneNum == 1)
			{
				auto Left = GetSharedGameObject<GameObject>(L"Left");
				Left->SetDrawActive(true);
			}*/
			Left->SetDrawActive(false);
		}
		auto Right = GetSharedGameObject<GameObject>(L"Right");
		if (m_StageNum != m_MaxStageNum)
		{
			Right->SetDrawActive(true);
		}
		else
		{
			Right->SetDrawActive(false);
		}

	}

}

