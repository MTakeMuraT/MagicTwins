#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void Result::CreateResourses()
	{
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = DataDir + L"ResultLogo.png";
		App::GetApp()->RegisterTexture(L"RESULTLOGO_TX", strTexture);
		strTexture = DataDir + L"sky.png";
		App::GetApp()->RegisterTexture(L"RESULTBACK_TX", strTexture);
		//Next�X�e�[�W���S�쐬
		strTexture = DataDir + L"NextStageLogo.png";
		App::GetApp()->RegisterTexture(L"NEXTSTAGELOGO_TX", strTexture);
		//���g���C���S�쐬
		strTexture = DataDir + L"RetryLogo.png";
		App::GetApp()->RegisterTexture(L"RETRYLOGO_TX", strTexture);
		//�X�e�[�W�Z���N�g���S�쐬
		strTexture = DataDir + L"StageselectLogo.png";
		App::GetApp()->RegisterTexture(L"STAGESELECTLOGO_TX", strTexture);
		//�^�C�g�����S�쐬
		strTexture = DataDir + L"titleLogo.png";
		App::GetApp()->RegisterTexture(L"TITLELOGO_TX", strTexture);
		//empty1
		strTexture = DataDir + L"empty1.png";
		App::GetApp()->RegisterTexture(L"EMPTY1_TX", strTexture);
		//empty2
		strTexture = DataDir + L"empty2.png";
		App::GetApp()->RegisterTexture(L"EMPTY2_TX", strTexture);
		//empty3
		strTexture = DataDir + L"empty3.png";
		App::GetApp()->RegisterTexture(L"EMPTY3_TX", strTexture);


	}

	void Result::CreateViewLight()
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

	void Result::CreateBack()
	{
		auto ResultBack = AddGameObject<GameObject>();
		ResultBack->AddComponent<Transform>();
		auto PtrTransform = ResultBack->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(0, 0, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(WindowSize.x, WindowSize.y, 1);

		//�X�v���C�g������
		auto PtrSprite = ResultBack->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"RESULTBACK_TX");

		//�����x���f
		ResultBack->SetAlphaActive(true);

		ResultBack->SetDrawLayer(1);

		SetSharedGameObject(L"TiBa", ResultBack);


	}

	void Result::CreateResultLogo()
	{
		auto ResultLogo = AddGameObject<GameObject>();
		ResultLogo->AddComponent<Transform>();
		auto PtrTransform = ResultLogo->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(-500, WindowSize.y / 2.5f, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(1000, 200, 1);

		//�X�v���C�g������
		auto PtrSprite = ResultLogo->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"RESULTLOGO_TX");

		SetSharedGameObject(L"SeLo", ResultLogo);

		ResultLogo->SetDrawLayer(2);

		//�����x���f
		ResultLogo->SetAlphaActive(true);

	}

	//Next�X�e�[�W���S�쐬
	void Result::CreateNextStageLogo()
	{
		auto NextStageLogo = AddGameObject<GameObject>();
		NextStageLogo->AddComponent<Transform>();
		auto PtrTransform = NextStageLogo->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(650, WindowSize.y / 4.5f, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(500, 150, 1);

		//�X�v���C�g������
		auto PtrSprite = NextStageLogo->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"NEXTSTAGELOGO_TX");

		SetSharedGameObject(L"NextStageLogo", NextStageLogo);

		NextStageLogo->SetDrawLayer(2);

		//�����x���f
		NextStageLogo->SetAlphaActive(true);
	}

	//���g���C���S�쐬
	void Result::CreateRetryLogo()
	{
		auto RetryLogo = AddGameObject<GameObject>();
		RetryLogo->AddComponent<Transform>();
		auto PtrTransform = RetryLogo->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(650, 50, 0);
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
	void Result::CreateStageSelectLogo()
	{
		auto StageSelectLogo = AddGameObject<GameObject>();
		StageSelectLogo->AddComponent<Transform>();
		auto PtrTransform = StageSelectLogo->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(650, -100, 0);
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
	void Result::CreateTitleLogo()
	{
		auto TitleLogo = AddGameObject<GameObject>();
		TitleLogo->AddComponent<Transform>();
		auto PtrTransform = TitleLogo->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(650, -250, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(500, 150, 1);

		//�X�v���C�g������
		auto PtrSprite = TitleLogo->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"TITLELOGO_TX");

		SetSharedGameObject(L"TitleLogo", TitleLogo);

		TitleLogo->SetDrawLayer(2);

		//�����x���f
		TitleLogo->SetAlphaActive(true);
	}

	//empty1
	void Result::Createempty1()
	{
		auto empty1 = AddGameObject<GameObject>();
		empty1->AddComponent<Transform>();
		auto PtrTransform = empty1->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(-650, 150, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(500, 150, 1);

		//�X�v���C�g������
		auto PtrSprite = empty1->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"EMPTY1_TX");

		SetSharedGameObject(L"empty1", empty1);

		empty1->SetDrawLayer(2);

		//�����x���f
		empty1->SetAlphaActive(true);
	}

	//empty2
	void Result::Createempty2()
	{
		auto empty2 = AddGameObject<GameObject>();
		empty2->AddComponent<Transform>();
		auto PtrTransform = empty2->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(-650, -50, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(500, 150, 1);

		//�X�v���C�g������
		auto PtrSprite = empty2->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"EMPTY2_TX");

		SetSharedGameObject(L"empty2", empty2);

		empty2->SetDrawLayer(2);

		//�����x���f
		empty2->SetAlphaActive(true);
	}

	//empty3
	void Result::Createempty3()
	{
		auto empty3 = AddGameObject<GameObject>();
		empty3->AddComponent<Transform>();
		auto PtrTransform = empty3->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(-650, -250, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(500, 150, 1);

		//�X�v���C�g������
		auto PtrSprite = empty3->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"EMPTY3_TX");

		SetSharedGameObject(L"empty3", empty3);

		empty3->SetDrawLayer(2);

		//�����x���f
		empty3->SetAlphaActive(true);
	}

	void Result::SceneChange()
	{
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameStage");
	}

	void Result::OnCreate()
	{
		try {
			//���\�[�X�̍쐬
			CreateResourses();
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�w�i�쐬
			CreateBack();
			//���S�쐬
			CreateResultLogo();
			//Next�X�e�[�W���S�쐬
			CreateNextStageLogo();
			//���g���C���S�쐬
			CreateRetryLogo();
			//�X�e�[�W�Z���N�g���S�쐬
			CreateStageSelectLogo();
			//�^�C�g�����S�쐬
			CreateTitleLogo();
			//empty1
			Createempty1();
			//empty2
		    Createempty2();
			//empty3
		    Createempty3();


			//�����\���e�X�g�p
			auto obj = AddGameObject<GameObject>();
			auto st = obj->AddComponent<StringSprite>();
			st->SetTextRect(Rect2D<float>(16.0f, 16.0f, 320.0f, 240.0f));
			st->SetFont(L"", 40);
			st->SetText(L"B:Stage\nA:Title\nX:Select");
			obj->SetDrawLayer(10);
			SetSharedGameObject(L"StringObj", obj);

			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			int num = ScenePtr->GetClearTime();

			wstring txt;

			auto obj1 = AddGameObject<GameObject>();
			auto st1 = obj1->AddComponent<StringSprite>();
			st1->SetTextRect(Rect2D<float>(900.0f, 200.0f, 1920.0f, 480.0f));
			st1->SetFontColor(Color4(1, 1, 0, 1));
			st1->SetFont(L"", 200);
			if (num < 10)
			{
				txt = L"S";
			}
			else if (num < 20)
			{
				txt = L"A";
			}
			else if (num < 40)
			{
				txt = L"B";
			}
			else
			{
				txt = L"C";
			}
			st1->SetText(txt);
			obj1->SetDrawLayer(10);


			auto obj2 = AddGameObject<GameObject>();
			auto st2 = obj2->AddComponent<StringSprite>();
			st2->SetTextRect(Rect2D<float>(400.0f, 512.0f, 1920.0f, 480.0f));
			st2->SetFontColor(Color4(0, 0, 0, 1));
			st2->SetFont(L"", 100);
			txt = L"CLEARTIME : " + Util::IntToWStr(num);
			txt += L" Seconds";
			st2->SetText(txt);
			obj2->SetDrawLayer(10);

			auto obj3 = AddGameObject<GameObject>();
			auto st3 = obj3->AddComponent<StringSprite>();
			st3->SetTextRect(Rect2D<float>(400.0f, 800.0f, 1920.0f, 1080.0f));
			st3->SetFontColor(Color4(0, 0, 0, 1));
			st3->SetFont(L"", 100);
			txt = L"SCOREITEM : " + Util::IntToWStr(ScenePtr->GetScoreItemCount());
			st3->SetText(txt);
			obj3->SetDrawLayer(10);
		}
		catch (...) {
			throw;
		}
	}

	void Result::OnUpdate()
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
			//�e�X�g�p�A�V�[���؂�ւ���ύX
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
			{
				auto ScenePtr = App::GetApp()->GetScene<Scene>();
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"Title");
			}
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_X)
			{
				auto ScenePtr = App::GetApp()->GetScene<Scene>();
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"StageSelect");
			}
		}

	}

}