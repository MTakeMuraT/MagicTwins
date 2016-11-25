#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Title::CreateResourses()
	{
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = DataDir + L"title.png";
		App::GetApp()->RegisterTexture(L"TITLE_TX", strTexture);
		strTexture = DataDir + L"sky.png";
		App::GetApp()->RegisterTexture(L"TITLEBACK_TX", strTexture);
		strTexture = DataDir + L"Black.png";
		App::GetApp()->RegisterTexture(L"BLACK_TX", strTexture);
		strTexture = DataDir + L"PS.png";
		App::GetApp()->RegisterTexture(L"PRESSSTART_TX", strTexture);

		strTexture = DataDir + L"Number.png";
		App::GetApp()->RegisterTexture(L"NUMBER_TX", strTexture);

	}

	//�r���[�ƃ��C�g�̍쐬
	void Title::CreateViewLight() {
		
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

	//�w�i�摜
	void Title::CreateBack()
	{
		auto TitleBack = AddGameObject<GameObject>();
		TitleBack->AddComponent<Transform>();
		auto PtrTransform = TitleBack->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(0, 0, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(WindowSize.x, WindowSize.y, 1);

		//�X�v���C�g������
		auto PtrSprite = TitleBack->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"TITLEBACK_TX");

		//�����x���f
		TitleBack->SetAlphaActive(true);

		TitleBack->SetDrawLayer(1);
		
	}

	//�^�C�g�������摜
	void Title::CreateTitle()
	{
	
		auto TitleLogo = AddGameObject<GameObject>();
		TitleLogo->AddComponent<Transform>();
		auto PtrTransform = TitleLogo->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(0, WindowSize.y/4, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(1500, 400, 1);

		//�X�v���C�g������
		auto PtrSprite = TitleLogo->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"TITLE_TX");
		
		TitleLogo->SetDrawLayer(2);

		//�����x���f
		TitleLogo->SetAlphaActive(true);
		
	}

	//�Ó]�p���쐬
	void Title::CreateBlack()
	{
		auto BlackP = AddGameObject<Black>();
		SetSharedGameObject(L"Black", BlackP);
	}

	//PRESS START�쐬
	void Title::CreatePressStart()
	{
		auto PressLogo = AddGameObject<GameObject>();
		PressLogo->AddComponent<Transform>();
		auto PtrTransform = PressLogo->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(0, -WindowSize.y / 4, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(800, 200, 1);

		//�X�v���C�g������
		auto PtrSprite = PressLogo->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"PRESSSTART_TX");

		SetSharedGameObject(L"PSLo", PressLogo);

		PressLogo->SetDrawLayer(2);

		//�����x���f
		PressLogo->SetAlphaActive(true);

	}

	//�V�[���ύX
	void Title::SceneChange()
	{
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"StageSelect");
	}

	void Title::OnCreate() {
		try {
			//���\�[�X�̍쐬
			CreateResourses();
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�w�i�쐬
			CreateBack();
			//�^�C�g�����S�쐬
			CreateTitle();
			//�Ó]�p���쐬
			CreateBlack();
			//PRESS START�쐬
			CreatePressStart();
			
		}
		catch (...) {
			throw;
		}
	}

	void Title::OnUpdate()
	{
		if (m_ConFlg)
		{

			//*�e�X�g�p
			auto key = App::GetApp()->GetInputDevice().GetKeyState();
			if (key.m_bPressedKeyTbl[VK_SPACE])
			{
				m_ConFlg = false;
				GetSharedGameObject<Black>(L"Black", false)->StartBlack();
			}
			//*�e�X�g�p

			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (CntlVec[0].bConnected)
			{
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
				{
					m_ConFlg = false;
					GetSharedGameObject<Black>(L"Black", false)->StartBlack();
				}
			}

			auto PSLoP = GetSharedGameObject<GameObject>(L"PSLo", false);
			//������
			if(!m_PSAlphaFlg)
			{
				m_PSAlpha += -0.02f;
				if (m_PSAlpha <= 0)
				{
					m_PSAlphaFlg = true;
				}
			}
			//���̉�
			else
			{
				m_PSAlpha += 0.02f;
				if (m_PSAlpha >= 1.0f)
				{
					m_PSAlphaFlg = false;
				}
			}
			PSLoP->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_PSAlpha));
		}
		//�{�^��������ĈÓ]�n�܂�����
		else
		{
			auto PSLoP = GetSharedGameObject<GameObject>(L"PSLo", false);
			//������
			if (!m_PSAlphaFlg)
			{
				m_PSAlpha += -0.5f;
				if (m_PSAlpha <= 0)
				{
					m_PSAlphaFlg = true;
				}
			}
			//���̉�
			else
			{
				m_PSAlpha += 0.5f;
				if (m_PSAlpha >= 1.0f)
				{
					m_PSAlphaFlg = false;
				}
			}
			PSLoP->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_PSAlpha));

			//�Ó]�I���
			if (GetSharedGameObject<Black>(L"Black", false)->GetBlackFinish())
			{
				SceneChange();
			}
		}
	}


}