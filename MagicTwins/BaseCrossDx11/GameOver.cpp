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
		strTexture = DataDir + L"PauseReTryLogo.png";
		App::GetApp()->RegisterTexture(L"PAUSERETRYLOGO_TX", strTexture);
		strTexture = DataDir + L"PauseStageSelect.png";
		App::GetApp()->RegisterTexture(L"PAUSESTAGESELECT_TX",strTexture);
		strTexture = DataDir + L"PauseTitleLogo.png";
		App::GetApp()->RegisterTexture(L"PAUSETITLELOGO_TX", strTexture);

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
		PtrTransform->SetScale(500, 500, 1);

		//�X�v���C�g������
		auto PtrSprite = RetryLogo->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"PAUSERETRYLOGO_TX");

		SetSharedGameObject(L"PauseReTryLogo", RetryLogo);

		RetryLogo->SetDrawLayer(2);

		//�����x���f
		RetryLogo->SetAlphaActive(true);

		m_ReTryLogo = RetryLogo;
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
		PtrTransform->SetScale(500, 500, 1);

		//�X�v���C�g������
		auto PtrSprite = StageSelectLogo->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"PAUSESTAGESELECT_TX");

		SetSharedGameObject(L"PauseStageSelect", StageSelectLogo);

		StageSelectLogo->SetDrawLayer(2);

		//�����x���f
		StageSelectLogo->SetAlphaActive(true);

		m_StageSelectLogo = StageSelectLogo;
	}

	//�^�C�g�����S�쐬
	void GameOver::CreateTitle()
	{
		auto TitleLogo = AddGameObject<GameObject>();
		TitleLogo->AddComponent<Transform>();
		auto PtrTransform = TitleLogo->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(-600,-80, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(500, 500, 1);

		//�X�v���C�g������
		auto PtrSprite = TitleLogo->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"PAUSETITLELOGO_TX");

		SetSharedGameObject(L"PauseTitleLogo", TitleLogo);

		TitleLogo->SetDrawLayer(2);

		//�����x���f
		TitleLogo->SetAlphaActive(true);

		m_TitleLogo = TitleLogo;
	}

	void GameOver::SceneChange()
	{
		/*auto ScenePtr = App::GetApp()->GetScene<Scene>();
		PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameStage");*/

		if (m_selectnum == 0)
		{
			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameStage");
		}
		if (m_selectnum == 1)
		{
			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"StageSelect");
		}
		if (m_selectnum == 2)
		{
			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"Title");
		}

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

			//SE�}�l�[�W���[
			SetSharedGameObject(L"SEM", AddGameObject<SEManager>());

			auto obj = AddGameObject<GameObject>();
			//�����������
			auto PtrString = obj->AddComponent<StringSprite>();
			PtrString->SetText(L"");
			PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
			PtrString->SetFont(L"", 80);
			PtrString->SetFontColor(Color4(0, 0, 0, 1));
			obj->SetDrawLayer(10);
			SetSharedGameObject(L"StringTxt", obj);

			//�傫������
			m_ReTryLogo->GetComponent<Transform>()->SetScale(m_SelectScale);
			m_StageSelectLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
			m_TitleLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);


		}
		catch (...) {
			throw;
		}

	}

	void GameOver::OnUpdate()
	{
		//�����\��
		auto getobj = GetSharedGameObject<GameObject>(L"StringTxt", false);
		wstring txt = Util::IntToWStr(m_selectnum);
		getobj->GetComponent<StringSprite>()->SetText(txt);

		//*�e�X�g�p
		auto key = App::GetApp()->GetInputDevice().GetKeyState();
		if (key.m_bPressedKeyTbl[VK_SPACE])
		{
			SceneChange();
		}
		//*�e�X�g�p


		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		Vector2 inputXY = Vector2(CntlVec[0].fThumbLX, CntlVec[0].fThumbLY);
		if (!m_moveFlg)
		{
			if (inputXY.y < -0.8f)
			{
				m_moveFlg = true;
				m_selectnum++;
				if (m_selectnum > 2)
				{
					m_selectnum = 0;
				}
			}
			if (inputXY.y > 0.8f)
			{
				m_moveFlg = true;
				m_selectnum--;
				if (m_selectnum < 0)
				{
					m_selectnum = 2;
				}
			}

			//�ύX��������
			if (m_moveFlg)
			{
				//Vector3 pos;
				Vector3 scale;
				switch (m_selectnum)
				{
				case 0:
					m_ReTryLogo->GetComponent<Transform>()->SetScale(m_SelectScale);
					m_StageSelectLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
					m_TitleLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);


					break;
				case 1:
					m_ReTryLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
					m_StageSelectLogo->GetComponent<Transform>()->SetScale(m_SelectScale);
					m_TitleLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);


					break;
				case 2:
					m_ReTryLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
					m_StageSelectLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
					m_TitleLogo->GetComponent<Transform>()->SetScale(m_SelectScale);

					break;

				}
			}
		}
		else if (inputXY.y < 0.1f && inputXY.y > -0.1f)
		{
			m_moveFlg = false;
		}

		if (CntlVec[0].bConnected)
		{
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
			{
				SceneChange();
			}
		}

	}

}