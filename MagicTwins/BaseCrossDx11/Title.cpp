#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Title::CreateResourses()
	{
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = DataDir + L"Title.png";
		App::GetApp()->RegisterTexture(L"TITLE_TX", strTexture);
		strTexture = DataDir + L"TitleBack.png";
		App::GetApp()->RegisterTexture(L"TITLEBACK_TX", strTexture);
		strTexture = DataDir + L"PS.png";
		App::GetApp()->RegisterTexture(L"PRESSSTART_TX", strTexture);
		//�L�����P
		strTexture = DataDir + L"eye_1.png";
		App::GetApp()->RegisterTexture(L"CHAR1_TX", strTexture);
		//�L�����Q
		strTexture = DataDir + L"eye2_1.png";
		App::GetApp()->RegisterTexture(L"CHAR2_TX", strTexture);

		//�X�e�[�W�Z���N�g���S
		strTexture = DataDir + L"StageSelectLogo.png";
		App::GetApp()->RegisterTexture(L"STAGESELECTLOGO_TX", strTexture);

		//�����摜(��)
		strTexture = DataDir + L"Left.png";
		App::GetApp()->RegisterTexture(L"LEFTARROW_TX", strTexture);
		//�E���摜(��)
		strTexture = DataDir + L"Right.png";
		App::GetApp()->RegisterTexture(L"RIGHTARROW_TX", strTexture);
		//�g
		strTexture = DataDir + L"Frame.png";
		App::GetApp()->RegisterTexture(L"FRAME_TX", strTexture);

		//�_�P
		strTexture = DataDir + L"Cloud01.png";
		App::GetApp()->RegisterTexture(L"CLOUD1_TX", strTexture);
		//�_�Q
		strTexture = DataDir + L"Cloud02.png";
		App::GetApp()->RegisterTexture(L"CLOUD2_TX", strTexture);

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
		PtrTransform->SetPosition(0, WindowSize.y/5, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(1500, 600, 1);

		//�X�v���C�g������
		auto PtrSprite = TitleLogo->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"TITLE_TX");
		
		TitleLogo->SetDrawLayer(2);

		//�����x���f
		TitleLogo->SetAlphaActive(true);
		
		m_TitleLogo = TitleLogo;
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
		PtrTransform->SetScale(1200, 150, 1);

		//�X�v���C�g������
		auto PtrSprite = PressLogo->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"PRESSSTART_TX");

		PressLogo->SetDrawLayer(2);

		//�����x���f
		PressLogo->SetAlphaActive(true);

		m_PressStartLogo = PressLogo;
	}

	//�X�e�[�W�Z���N�g���S�쐬
	void Title::CreateStageSelectLogo()
	{		
		auto StageSelectLogoPtr = AddGameObject<GameObject>();
		auto SSLT = StageSelectLogoPtr->AddComponent<Transform>();
		SSLT->SetPosition(0, -1000, 0);
		SSLT->SetRotation(0, 0, 0);
		SSLT->SetScale(1000, 200, 1);
		//�X�v���C�g��
		auto SSLD = StageSelectLogoPtr->AddComponent<PCTSpriteDraw>();
		SSLD->SetTextureResource(L"STAGESELECTLOGO_TX");
		//�����x�L��
		StageSelectLogoPtr->SetAlphaActive(true);
		//���C���[�ݒ�
		StageSelectLogoPtr->SetDrawLayer(3);
		//�A�N�Z�X�p
		m_StageSelectLogo = StageSelectLogoPtr;

	}
	//�X�e�[�W�Z���N�g���
	void Title::CreateArrow()
	{
		//��
		auto ArrowPtr = AddGameObject<GameObject>();
		auto ArrowTra = ArrowPtr->AddComponent<Transform>();
		ArrowTra->SetPosition(1500, 0, 0);
		ArrowTra->SetRotation(0, 0, 0);
		ArrowTra->SetScale(150, 150, 1);
		//�X�v���C�g��
		auto ArrowDraw = ArrowPtr->AddComponent<PCTSpriteDraw>();
		ArrowDraw->SetTextureResource(L"LEFTARROW_TX");
		//�����x�L��
		ArrowPtr->SetAlphaActive(true);
		//���C���[�ݒ�
		ArrowPtr->SetDrawLayer(4);
		//�A�N�Z�X�p
		m_ArrowL = ArrowPtr;

		//�E
		ArrowPtr = AddGameObject<GameObject>();
		ArrowTra = ArrowPtr->AddComponent<Transform>();
		ArrowTra->SetPosition(-1500, 0, 0);
		ArrowTra->SetRotation(0, 0, 0);
		ArrowTra->SetScale(150, 150, 1);
		//�X�v���C�g��
		ArrowDraw = ArrowPtr->AddComponent<PCTSpriteDraw>();
		ArrowDraw->SetTextureResource(L"RIGHTARROW_TX");
		//�����x�L��
		ArrowPtr->SetAlphaActive(true);
		//���C���[�ݒ�
		ArrowPtr->SetDrawLayer(4);
		//�A�N�Z�X�p
		m_ArrowR = ArrowPtr;

	}

	//�L�����B���쐬
	void Title::CreateChar()
	{
		//1�̖�
		auto Char1Ptr = AddGameObject<GameObject>();
		auto Char1Tra = Char1Ptr->AddComponent<Transform>();
		Char1Tra->SetPosition(-706, -1500, 0);
		Char1Tra->SetRotation(0, 0, 0);
		Char1Tra->SetScale(788, 786, 1);
		//�X�v���C�g��
		auto C1Draw = Char1Ptr->AddComponent<PCTSpriteDraw>();
		C1Draw->SetTextureResource(L"CHAR1_TX");
		//�����x�L��
		Char1Ptr->SetAlphaActive(true);
		//���C���[�ݒ�
		Char1Ptr->SetDrawLayer(3);
		//�A�N�Z�X�p
		m_Char1 = Char1Ptr;

		//2�̖�
		auto Char2Ptr = AddGameObject<GameObject>();
		auto Char2Tra = Char2Ptr->AddComponent<Transform>();
		Char2Tra->SetPosition(684, -1500, 0);
		Char2Tra->SetRotation(0, 0, 0);
		Char2Tra->SetScale(788, 786, 1);
		//�X�v���C�g��
		auto C2Draw = Char2Ptr->AddComponent<PCTSpriteDraw>();
		C2Draw->SetTextureResource(L"CHAR2_TX");
		//�����x�L��
		Char2Ptr->SetAlphaActive(true);
		//���C���[�ݒ�
		Char2Ptr->SetDrawLayer(3);
		//�A�N�Z�X�p
		m_Char2 = Char2Ptr;

	}

	//�X�e�[�W�C���[�W�쐬
	void Title::CreateStageImage()
	{
		//0�̃`���[�g���A��
		auto StageImagePtr = AddGameObject<GameObject>();
		auto SIPT = StageImagePtr->AddComponent<Transform>();
		SIPT->SetPosition(0, 0, 0);
		SIPT->SetRotation(0, 0, 0);
		SIPT->SetScale(10, 10, 1);
		//�X�v���C�g��
		auto SIPD = StageImagePtr->AddComponent<PCTSpriteDraw>();
		SIPD->SetTextureResource(L"FRAME_TX");
		//�����x�L��
		StageImagePtr->SetAlphaActive(true);
		//���C���[�ݒ�
		StageImagePtr->SetDrawLayer(4);
		//�����Ƃ�
		StageImagePtr->SetDrawActive(false);
		//�A�N�Z�X�p
		m_StageImage = StageImagePtr;


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
			//PRESS START�쐬
			CreatePressStart();
			//�X�e�[�W�Z���N�g���S�쐬
			CreateStageSelectLogo();
			//�X�e�[�W�Z���N�g���
			CreateArrow();

			//�L�����쐬
			CreateChar();

			//�X�e�[�W�C���[�W�쐬
			CreateStageImage();
		
			SetSharedGameObject(L"SEM", AddGameObject<SEManager>());


			//�����쐬
			auto StringPtr = AddGameObject<GameObject>();
			auto SST = StringPtr->AddComponent<StringSprite>();
			SST->SetText(L"");
			SST->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
			SST->SetFont(L"", 40);
			SST->SetFontColor(Color4(0, 0, 0, 1));
			StringPtr->SetDrawLayer(10);
			m_String = StringPtr;


			//�_�ǉ�
			SetSharedGameObject(L"Cloud",AddGameObject<Cloud>(Vector3(300, 200, 1), 5, 1,0));
		}
		catch (...) {
			throw;
		}
	}

	void Title::OnUpdate()
	{
		if (!m_TutorialChamgeFlg)
		{
			m_TutorialChamgeFlg = true;
			//�`���[�g���A���݂����ǂ����̃t���O���X�V(���ĂȂ�:false�ɕύX)
			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			ScenePtr->SetTutorialOpenFlg(false);
		}
		//�A�j���[�V�������Ă�΂���ď����I���
		if (m_AnimationFlg)
		{
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
			m_PressStartLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_PSAlpha));
				
			//�A�j���[�V����
			Animation();
			return;
		}

		if (!m_AnimationFlg)
		{

			//*�e�X�g�p
			auto key = App::GetApp()->GetInputDevice().GetKeyState();
			if (key.m_bPressedKeyTbl[VK_SPACE])
			{
				m_AnimationFlg = true;
			}
			//*�e�X�g�p

			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (CntlVec[0].bConnected)
			{
					//�X�^�[�g�ƃo�b�N���������ă^�C�g����
				if (CntlVec[0].wButtons & XINPUT_GAMEPAD_START && CntlVec[0].wButtons & XINPUT_GAMEPAD_BACK)
				{
					auto ScenePtr = App::GetApp()->GetScene<Scene>();
					PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"Title");
				}

				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B ||
					CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
				{
					m_AnimationFlg = true;

					//�_��~
					GetSharedGameObject<Cloud>(L"Cloud", false)->StopCloud();
					//SE�Đ�
					GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("SelectTitle");
				}
			}

			//�v���XBUTTON�̃��S
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
			m_PressStartLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_PSAlpha));
		}
	}

	void Title::Animation()
	{
		//0
		float ElaTime = App::GetApp()->GetElapsedTime();

		//1,2
		auto TitleTra = m_TitleLogo->GetComponent<Transform>();
		auto PressTra = m_PressStartLogo->GetComponent<Transform>();

		Vector3 Titlepos = TitleTra->GetPosition();
		Vector3 Presspos = PressTra->GetPosition();

		//2
		/*�����p
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		Vector2 velo;
		Vector3 pos;
		Vector3 scale;
		auto key = App::GetApp()->GetInputDevice().GetKeyState();
		*/
		auto Char1Tra = m_Char1->GetComponent<Transform>();
		auto Char2Tra = m_Char2->GetComponent<Transform>();

		Vector3 Char1pos = Char1Tra->GetPosition();
		Vector3 Char2pos = Char2Tra->GetPosition();

		//3
		auto StageSeleLogoTra = m_StageSelectLogo->GetComponent<Transform>();
		auto ArrowRTra = m_ArrowR->GetComponent<Transform>();
		auto ArrowLTra = m_ArrowL->GetComponent<Transform>();

		Vector3 SSLpos = StageSeleLogoTra->GetPosition();
		Vector3 ArrowRpos = ArrowRTra->GetPosition();
		Vector3 ArrowLpos = ArrowLTra->GetPosition();

		//4
		auto StageImageTra = m_StageImage->GetComponent<Transform>();
		Vector3 SIscale = StageImageTra->GetScale();

		switch (m_AnimationState)
		{
			//0:1�b��
		case 0:
			m_time += ElaTime;
			if (m_time > 1.0f)
			{
				m_time = 0;
				m_AnimationState = 1;
			}
			break;

			//1:���S��������֍s���A�L�������o�Ă��钼�O�܂�
		case 1:
			if (Presspos.y < 400)
			{
				Titlepos.y += 1000 * ElaTime;
				Presspos.y += 1000 * ElaTime;

				TitleTra->SetPosition(Titlepos);
				PressTra->SetPosition(Presspos);
			}
			else
			{
				m_AnimationState = 2;
			}
			break;
			//2:�L������������o�Ă��ĕ��������֏�����
		case 2:
			if (Presspos.y < 600)
			{
				Titlepos.y += 1000 * ElaTime;
				Presspos.y += 1000 * ElaTime;

				TitleTra->SetPosition(Titlepos);
				PressTra->SetPosition(Presspos);
			}
			//�P�̖ړ�����
			if (Char1pos.y < -158)
			{
				Char1pos.y += 1000 * ElaTime;
				Char1Tra->SetPosition(Char1pos);
			}
			else
			{
				Char1pos.y = -158;
				Char1Tra->SetPosition(Char1pos);
			}
			//�Q�̖ړ�����
			if (Char2pos.y < -158)
			{
				Char2pos.y += 1000 * ElaTime;
				Char2Tra->SetPosition(Char2pos);
			}
			else
			{
				Char2pos.y = -158;
				Char2Tra->SetPosition(Char2pos);
			}
			
			if (Presspos.y >= 600 && Char1pos.y == -158 && Char2pos.y == -158)
			{
				m_AnimationState = 3;
			}
			/*�ʒu�����p
			if (CntlVec[0].fThumbLX > 0.1f || CntlVec[0].fThumbLX < -0.1f ||
				CntlVec[0].fThumbLY > 0.1f || CntlVec[0].fThumbLY < -0.1f)
			{
				velo = Vector2(CntlVec[0].fThumbLX, CntlVec[0].fThumbLY);
				pos = m_Char1->GetComponent<Transform>()->GetPosition();
				pos.x += velo.x * 2;
				pos.y += velo.y * 2;
				m_Char1->GetComponent<Transform>()->SetPosition(pos);
			}
			if (key.m_bPushKeyTbl[VK_UP])
			{
				scale = m_Char1->GetComponent<Transform>()->GetScale();
				scale.y += 50 * ElaTime;
				m_Char1->GetComponent<Transform>()->SetScale(scale);
			}
			if (key.m_bPushKeyTbl[VK_DOWN])
			{
				scale = m_Char1->GetComponent<Transform>()->GetScale();
				scale.y += -50 * ElaTime;
				m_Char1->GetComponent<Transform>()->SetScale(scale);
			}
			if (key.m_bPushKeyTbl[VK_RIGHT])
			{
				scale = m_Char1->GetComponent<Transform>()->GetScale();
				scale.x += 50 * ElaTime;
				m_Char1->GetComponent<Transform>()->SetScale(scale);
			}
			if (key.m_bPushKeyTbl[VK_LEFT])
			{
				scale = m_Char1->GetComponent<Transform>()->GetScale();
				scale.x += -50 * ElaTime;
				m_Char1->GetComponent<Transform>()->SetScale(scale);
			}*/
			break;
			//3:�X�e�[�W�Z���N�g���S�����痈�āA��󍶉E����o��
		case 3:
			//�X�e�[�W�Z���N�g���S�ړ�
			if (SSLpos.y < 432)
			{
				SSLpos.y += 2000 * ElaTime;
				StageSeleLogoTra->SetPosition(SSLpos);
			}
			else
			{
				SSLpos.y = 432;
				StageSeleLogoTra->SetPosition(SSLpos);
			}
			//���R�ړ�
			if (ArrowRpos.x < 890)
			{
				ArrowRpos.x += 3000 * ElaTime;
				ArrowRTra->SetPosition(ArrowRpos);
			}
			else
			{
				ArrowRpos.x = 890;
				ArrowRTra->SetPosition(ArrowRpos);
			}
			//���L�ړ�
			if (ArrowLpos.x > -890)
			{
				ArrowLpos.x += -3000 * ElaTime;
				ArrowLTra->SetPosition(ArrowLpos);
			}
			else
			{
				ArrowLpos.x = -890;
				ArrowLTra->SetPosition(ArrowLpos);
			}

			if (SSLpos.y == 432 && ArrowRpos.x == 890 && ArrowLpos.x == -890)
			{
				m_AnimationState = 4;
				//�g��\��
				m_StageImage->SetDrawActive(true);
			}
			break;
			//�X�e�[�W�C���[�W���X�P�[���A�b�v�ō쐬���ďI��
		case 4:
			if (SIscale.x < 1500)
			{
				SIscale *= 1.2f;
				StageImageTra->SetScale(SIscale);
			}
			else
			{
				SIscale.x = 1500;
				SIscale.y = 1500;
				StageImageTra->SetScale(SIscale);
				m_AnimationState = 5;
			}
			break;
			//������Ə�����
		case 5:
			if (SIscale.x > 1200)
			{
				SIscale *= 0.9f;
				StageImageTra->SetScale(SIscale);
			}
			else
			{
				SIscale.x = 1200;
				SIscale.y = 1200;
				StageImageTra->SetScale(SIscale);
				m_AnimationState = 6;
			}

			break;
			//�I��
		case 6:
			SceneChange();
			break;
		default:
			break;
		}

		//wstring txt = Util::IntToWStr(m_AnimationState);
		/*�ʒu�����p
		if (m_AnimationState == 2)
		{
			Vector3 postxt = m_Char1->GetComponent<Transform>()->GetPosition();
			Vector3 scaletxt = m_Char1->GetComponent<Transform>()->GetScale();
			txt += L"\nPOS_X = " + Util::FloatToWStr(postxt.x) + L"\nPOS_Y = " + Util::FloatToWStr(postxt.y);
			txt += L"\nSCALE_X = " + Util::FloatToWStr(scaletxt.x) + L"\nSCALE_Y = " + Util::FloatToWStr(scaletxt.y);
			
		}
		*/
		/*
		if (m_AnimationState == 3)
		{
			txt += L"\nLX = " + Util::FloatToWStr(ArrowLpos.x);
			txt += L"\nRX = " + Util::FloatToWStr(ArrowRpos.x);
		}
		*/
		/*
		if (m_AnimationState == 4)
		{
			txt += L"\nXSc = " + Util::FloatToWStr(SIscale.x);
			txt += L"\nYSc = " + Util::FloatToWStr(SIscale.x);
		}
		*/
		//m_String->GetComponent<StringSprite>()->SetText(txt);

	}


}