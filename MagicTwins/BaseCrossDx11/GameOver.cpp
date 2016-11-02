#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void GameOver::CreateResourses()
	{
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = DataDir + L"GameOverLogo.png";
		App::GetApp()->RegisterTexture(L"GAMEOVERLOGO_TX", strTexture);
		strTexture = DataDir + L"OverBack.png";
		App::GetApp()->RegisterTexture(L"GAMEOVERBACK_TX", strTexture);
		strTexture = DataDir + L"RetryLogo.png";
		App::GetApp()->RegisterTexture(L"RETRYLOGO_TX", strTexture);
		strTexture = DataDir + L"StageSelectLogo.png";
		App::GetApp()->RegisterTexture(L"STAGESELECTLOGO_TX",strTexture);
		strTexture = DataDir + L"Title.png";
		App::GetApp()->RegisterTexture(L"TITLE_TX", strTexture);

	}

	void GameOver::CreateViewLight()
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

	void GameOver::CreateBack()
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
		PtrSprite->SetTextureResource(L"GAMEOVERBACK_TX");

		//�����x���f
		SelectBack->SetAlphaActive(true);

		SelectBack->SetDrawLayer(1);

		SetSharedGameObject(L"OvBa", SelectBack);


	}

	void GameOver::CreateOverLogo()
	{
		auto OverLogo = AddGameObject<GameObject>();
		OverLogo->AddComponent<Transform>();
		auto PtrTransform = OverLogo->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(350, WindowSize.y / 2.5f, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(1100, 300, 1);

		//�X�v���C�g������
		auto PtrSprite = OverLogo->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"GAMEOVERLOGO_TX");

		SetSharedGameObject(L"OvLo", OverLogo);

		OverLogo->SetDrawLayer(2);

		//�����x���f
		OverLogo->SetAlphaActive(true);

	}

	//���g���C���S�쐬
	void GameOver::CreateRetry()
	{
		auto RetryLogo = AddGameObject<GameObject>();
		RetryLogo->AddComponent<Transform>();
		auto PtrTransform = RetryLogo->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(-600, WindowSize.y / 3.5f, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(500, 150, 1);

		//�X�v���C�g������
		auto PtrSprite = RetryLogo->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"RETRYLOGO_TX");

		SetSharedGameObject(L"RetryLogo", RetryLogo);

		RetryLogo->SetDrawLayer(2);

		//�����x���f
		RetryLogo->SetAlphaActive(true);
	}

	//�X�e�[�W�Z���N�g���S�쐬
	void GameOver::CreateStageSelect()
	{
		auto StageSelectLogo = AddGameObject<GameObject>();
		StageSelectLogo->AddComponent<Transform>();
		auto PtrTransform = StageSelectLogo->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(-600, WindowSize.y / 9.5f, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(500, 150, 1);

		//�X�v���C�g������
		auto PtrSprite = StageSelectLogo->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"STAGESELECTLOGO_TX");

		SetSharedGameObject(L"StageSelectLogo", StageSelectLogo);

		StageSelectLogo->SetDrawLayer(2);

		//�����x���f
		StageSelectLogo->SetAlphaActive(true);
	}

	//�^�C�g�����S�쐬
	void GameOver::CreateTitle()
	{
		auto TitleLogo = AddGameObject<GameObject>();
		TitleLogo->AddComponent<Transform>();
		auto PtrTransform = TitleLogo->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(-600,-30, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(600, 200, 1);

		//�X�v���C�g������
		auto PtrSprite = TitleLogo->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"TITLE_TX");

		SetSharedGameObject(L"TitleLogo", TitleLogo);

		TitleLogo->SetDrawLayer(2);

		//�����x���f
		TitleLogo->SetAlphaActive(true);
	}

	void GameOver::SceneChange()
	{
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameStage");
	}

	void GameOver::OnCreate()
	{
		try {
			//���\�[�X�̍쐬
			CreateResourses();
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�w�i�쐬
			CreateBack();
			//���S�쐬
			CreateOverLogo();
			//���g���C���S�쐬
			CreateRetry();
			//�X�e�[�W�Z���N�g���S�쐬
			CreateStageSelect();
			//�^�C�g�����S�쐬
			CreateTitle();

		}
		catch (...) {
			throw;
		}
	}

	void GameOver::OnUpdate()
	{
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
		}

	}

}