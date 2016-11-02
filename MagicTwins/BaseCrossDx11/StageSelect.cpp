#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void StageSelect::CreateResourses()
	{
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = DataDir + L"StageSelectLogo.png";
		App::GetApp()->RegisterTexture(L"STAGESELECTLOGO_TX", strTexture);
		strTexture = DataDir + L"sky.png";
		App::GetApp()->RegisterTexture(L"SELECTBACK_TX", strTexture);
		//StegeSelect�摜(��)
		strTexture = DataDir + L"BButton.png";
		App::GetApp()->RegisterTexture(L"BBUTTON_TX", strTexture);
		//�����摜(��)
		strTexture = DataDir + L"Left.png";
		App::GetApp()->RegisterTexture(L"LEFT_TX", strTexture);
		//�E���摜(��)
		strTexture = DataDir + L"Right.png";
		App::GetApp()->RegisterTexture(L"RIGHT_TX", strTexture);

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

	void StageSelect::SceneChange()
	{
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameStage");
	}

	//�{�^������
	void StageSelect::CreaateStageSelect()
	{
		auto StageSelect = AddGameObject<GameObject>();
		StageSelect->AddComponent<Transform>();
		auto PtrTransform = StageSelect->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(600, -400, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(500, 200, 1);

		//�X�v���C�g��t����
		auto PtrSprite = StageSelect->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"BBUTTON_TX");

		SetSharedGameObject(L"StageSelect", StageSelect);

		StageSelect->SetDrawLayer(2);

		//�����x���f
		StageSelect->SetAlphaActive(true);
		GetSharedGameObject<GameObject>(L"TiBa", false)->GetComponent<StringSprite>()->SetText(L"0");

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

		if (m_SceneNum < 0)
		{

		}

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
			//�X�e�[�W�Z���N�g(��)
			CreaateStageSelect();

			//�����(��)
			Left();
			//�E���(��)
			Right();
			//���E�V�[���J��(��)
			m_SceneNum = 5;
			m_flag = true;

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
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
			{
				SceneChange();
			}
			//���E�V�[���J��(��)
			if (CntlVec[0].fThumbLX > 0 && m_flag&&m_SceneNum<5)
			{

				m_SceneNum++;
				m_flag = false;

			}
			if (CntlVec[0].fThumbLX < 0 && m_flag&&m_SceneNum>0)
			{
				m_SceneNum--;
				m_flag = false;
			}
			if (CntlVec[0].fThumbLX == 0)
			{
				m_flag = true;
			}

		}
		sceneNum += Util::IntToWStr(m_SceneNum);
		ShareString->SetText(sceneNum);
			auto Left = GetSharedGameObject<GameObject>(L"Right");

		if (m_SceneNum != 5)
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
		auto Right = GetSharedGameObject<GameObject>(L"Left");
		if (m_SceneNum != m_MaxNum)
		{
			Right->SetDrawActive(true);
		}
		else
		{
			Right->SetDrawActive(false);
		}

	}

}

