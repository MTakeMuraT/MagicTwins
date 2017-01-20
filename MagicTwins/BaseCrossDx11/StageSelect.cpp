#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void StageSelect::CreateResourses()
	{
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = DataDir + L"StageSelectLogo.png";
		App::GetApp()->RegisterTexture(L"STAGESELECTLOGO_TX", strTexture);
		strTexture = DataDir + L"TitleBack.png";
		App::GetApp()->RegisterTexture(L"SELECTBACK_TX", strTexture);
		//�����摜(��)
		strTexture = DataDir + L"Left.png";
		App::GetApp()->RegisterTexture(L"LEFT_TX", strTexture);
		//�E���摜(��)
		strTexture = DataDir + L"Right.png";
		App::GetApp()->RegisterTexture(L"RIGHT_TX", strTexture);
		//B�{�^��
		strTexture = DataDir + L"ButtonA.png";
		App::GetApp()->RegisterTexture(L"ABUTTON_TX", strTexture);
		//���胍�S
		strTexture = DataDir + L"Kettei.png";
		App::GetApp()->RegisterTexture(L"KETTEI_TX", strTexture);
		//�X�e�[�W�C���[�W�g
		strTexture = DataDir + L"Frame.png";
		App::GetApp()->RegisterTexture(L"FRAME_TX", strTexture);


		//����
		strTexture = DataDir + L"Number.png";
		App::GetApp()->RegisterTexture(L"NUMBER_TX", strTexture);


		//�Ó]�p�̍�
		strTexture = DataDir + L"Black.png";
		App::GetApp()->RegisterTexture(L"BLACK_TX", strTexture);

		//�ڂ̉摜
		strTexture = DataDir + L"eye_1.png";
		App::GetApp()->RegisterTexture(L"EYE_0_TX", strTexture);
		strTexture = DataDir + L"eye_2.png";
		App::GetApp()->RegisterTexture(L"EYE_1_TX", strTexture);
		strTexture = DataDir + L"eye_3.png";
		App::GetApp()->RegisterTexture(L"EYE_2_TX", strTexture);
		//2
		strTexture = DataDir + L"eye2_1.png";
		App::GetApp()->RegisterTexture(L"EYE2_0_TX", strTexture);
		strTexture = DataDir + L"eye2_2.png";
		App::GetApp()->RegisterTexture(L"EYE2_1_TX", strTexture);
		strTexture = DataDir + L"eye2_3.png";
		App::GetApp()->RegisterTexture(L"EYE2_2_TX", strTexture);

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

		////�������t����(��)
		//auto Stp = SelectBack->AddComponent<StringSprite>();
		//Stp->SetText(L"");
		//Stp->SetTextRect(Rect2D<float>(1024.0f, -256.0f, 1024.0f, 960.0f));
		//Stp->SetFontColor(Color4(1, 1, 0.4f, 1));
		//Stp->SetFont(L"", 100);

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

	void StageSelect::CreateStageImageFrame()
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
		if (GetSharedGameObject<Black>(L"BlackObj", false)->GetBlackFinish())
		{
			if (m_StageNum != 0)
			{
				auto ScenePtr = App::GetApp()->GetScene<Scene>();
				ScenePtr->SetStageNum(m_StageNum);
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameStage");
			}
			else
			{
				auto ScenePtr = App::GetApp()->GetScene<Scene>();
				ScenePtr->SetStageNum(m_StageNum);
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"Tutorial");
			}
		}
	}

	void StageSelect::CreateButtons()
	{
		//A�{�^���쐬
		auto obj1 = AddGameObject<GameObject>();
		auto OT1 = obj1->AddComponent<Transform>();
		OT1->SetPosition(300, -400, 0);
		OT1->SetScale(100, 100, 1);
		OT1->SetRotation(0, 0, 0);
		auto OD1 = obj1->AddComponent<PCTSpriteDraw>();
		OD1->SetTextureResource(L"ABUTTON_TX");
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
		//GetSharedGameObject<GameObject>(L"TiBa", false)->GetComponent<StringSprite>()->SetText(L"0");

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
		//GetSharedGameObject<GameObject>(L"TiBa", false)->GetComponent<StringSprite>()->SetText(L"0");
	}

	//�X�e�[�W�C���[�W�쐬
	void StageSelect::CreateStageImage()
	{
		//�摜�p��
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture;
		for (int i = 0; i <= 10; i++)
		{
			wstring num = Util::IntToWStr(i);

			wstring pathtxt = DataDir + L"StageImage/Stage_";
			pathtxt += num + L".png";
			strTexture = DataDir + pathtxt;

			wstring numtxt = L"STAGEIMAGE_";
			numtxt += Util::IntToWStr(i) + L"_TX";
			App::GetApp()->RegisterTexture(numtxt, strTexture);

		}

		//����
		auto ImageP = AddGameObject<GameObject>();
		//���W�Ƃ��w��
		auto ImageTrans = ImageP->AddComponent<Transform>();
		ImageTrans->SetPosition(5, 2, 0);
		ImageTrans->SetRotation(0, 0, 0);
		ImageTrans->SetScale(955, 565, 1);

		//�摜�\��t��
		auto ImageDraw = ImageP->AddComponent<PCTSpriteDraw>();
		ImageDraw->SetTextureResource(L"STAGEIMAGE_0_TX");

		//�����x
		ImageP->SetAlphaActive(true);
		//���C���[
		ImageP->SetDrawLayer(4);

		//�A�N�Z�X�ł��郁���o�ϐ��ɓ���Ƃ�
		m_StageImage = ImageP;


	}

	//�X�e�[�W�C���[�W��]
	void StageSelect::RotStageImage()
	{

		Vector3 scale = m_StageImage->GetComponent<Transform>()->GetScale();

		//m_SIHalfFlg��false�Ȃ珬�����Atrue�Ȃ�傫��
		if (!m_SIHalfFlg)
		{
			scale.x += -10000 * App::GetApp()->GetElapsedTime();
			//���ɂȂ�����e�N�X�`���؂�ւ�
			if (scale.x < 0)
			{
				//�e�N�X�`������ւ�
				wstring txt = L"STAGEIMAGE_";
				txt += Util::IntToWStr(m_StageNum) + L"_TX";
				m_StageImage->GetComponent<PCTSpriteDraw>()->SetTextureResource(txt);

				//�X�P�[���ƃt���O���]
				scale.x = 0;
				m_SIHalfFlg = true;
			}
		}
		else
		{
			scale.x += 10000 * App::GetApp()->GetElapsedTime();
			if (scale.x > 955)
			{
				scale.x = 955;
				m_SIHalfFlg = false;
				m_StageImageRotFlg = false;
			}

		}

		m_StageImage->GetComponent<Transform>()->SetScale(scale);

		//wstring txt = Util::FloatToWStr(scale.x);
		//GetSharedGameObject<GameObject>(L"StringObject", false)->GetComponent<StringSprite>()->SetText(txt);
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
			//�X�e�[�W�C���[�W�t���[��
			CreateStageImageFrame();
			//�X�e�[�W�C���[�W�쐬
			CreateStageImage();
			//�����(��)
			Left();
			//�E���(��)
			Right();
			//���E�V�[���J��(��)
			m_StageNum = 0;
			m_flag = true;

			//SE�}�l�[�W���[
			SetSharedGameObject(L"SEM", AddGameObject<SEManager>());

			//������
			//auto obj = AddGameObject<GameObject>();
			//auto Stp = obj->AddComponent<StringSprite>();
			//Stp->SetText(L"0");
			//Stp->SetTextRect(Rect2D<float>(1024.0f, -1024.0f, 1024.0f, 960.0f));
			//Stp->SetFont(L"", 100);
			//Stp->SetFontColor(Color4(1, 1, 0.4f, 1));
			//obj->SetDrawLayer(10);
			//SetSharedGameObject(L"StringObject",obj);
			auto NumberP = AddGameObject<NumberSprite>(0, Vector2(25, -400.0f), Vector2(128, 128), 4);
			SetSharedGameObject(L"NumberSprite", NumberP);

			//�`���[�g���A���݂����ǂ������肵�Č��Ă���1�ɂ���
			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			if (ScenePtr->GetTutorialOpenFlg())
			{
				//����1
				NumberP->SetNum(1);
				m_StageNum = 1;
				m_StageImage->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"STAGEIMAGE_1_TX");

			}

			//�_�ǉ�
			AddGameObject<Cloud>(Vector3(300, 300, 1), 5, 1,0);

			//�L������
			AddGameObject<CharEye>(Vector3(-706, -158, 0), false);
			AddGameObject<CharEye>(Vector3(684, -158, 0), true);

		}
		catch (...) {
			throw;
		}

	}

	void StageSelect::OnUpdate()
	{
		if (!m_SelectFlg)
		{
			//���E�ŃV�[���J��(��)
			//auto ShareObject = GetSharedGameObject<GameObject>(L"StringObject", false);
			//auto ShareString = ShareObject->GetComponent<StringSprite>();

			//wstring sceneNum(L"");


			//*�e�X�g�p
			auto key = App::GetApp()->GetInputDevice().GetKeyState();
			if (key.m_bPressedKeyTbl[VK_SPACE])
			{
				//�Ó]���쐬���Ă�������I��点��
				auto BlackObj = AddGameObject<Black>();
				BlackObj->StartBlack();
				BlackObj->SetDrawLayer(10);
				SetSharedGameObject(L"BlackObj", BlackObj);
				m_SelectFlg = true;
				return;

			}
			//*�e�X�g�p

			//�X�e�[�W�C���[�W����]���Ă�Ƃ��ȊO�����
			if (!m_StageImageRotFlg)
			{

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
						//�Ó]���쐬���Ă�������I��点��
						auto BlackObj = AddGameObject<Black>();
						BlackObj->StartBlack();
						SetSharedGameObject(L"BlackObj", BlackObj);
						m_SelectFlg = true;
						//SE�Đ�
						GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("Select");
						return;
					}
					//���E�V�[���J��(��)
					if (CntlVec[0].fThumbLX > 0 && m_flag&&m_StageNum < m_MaxStageNum)
					{

						m_StageNum++;
						m_flag = false;
						m_StageImageRotFlg = true;
					}
					if (CntlVec[0].fThumbLX < 0 && m_flag&&m_StageNum>0)
					{
						m_StageNum--;
						m_flag = false;
						m_StageImageRotFlg = true;
					}
					if (CntlVec[0].fThumbLX == 0)
					{
						m_flag = true;
					}

				}
				if (!m_flag)
				{
					GetSharedGameObject<NumberSprite>(L"NumberSprite", false)->SetNum(m_StageNum);
				}
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
			//�X�e�[�W�C���[�W��]���Ă�t���O�����Ă���֐��Ă�
			else
			{
				RotStageImage();
			}
		}
		else
		{
			SceneChange();
		}
	}


	//--------------------------------------------------------------------------------------
	//	class CharEye : public GameObject;
	//	�p�r: �L�����̖�
	//	�ݒ肵�����Ԃ��Ƃɏu�����邩���肵�Ȃ���u��
	//--------------------------------------------------------------------------------------
	CharEye::CharEye(const shared_ptr<Stage>& StagePtr,Vector3 pos,bool flg):
		GameObject(StagePtr),
		m_Pos(pos),
		m_2PlayerFlg(flg)
	{}

	void CharEye::OnCreate()
	{
		for (int i = 0; i <= 2; i++)
		{
			auto obj = GetStage()->AddGameObject<GameObject>();
			auto Trans = obj->AddComponent<Transform>();
			Trans->SetPosition(m_Pos);
			Trans->SetScale(788,786,1);
			Trans->SetRotation(0,0,0);
			auto Draw = obj->AddComponent<PCTSpriteDraw>();
			if (!m_2PlayerFlg)
			{
				wstring txt = L"EYE_";
				txt += Util::IntToWStr(i) + L"_TX";
				Draw->SetTextureResource(txt);
			}
			else
			{
				wstring txt = L"EYE2_";
				txt += Util::IntToWStr(i) + L"_TX";
				Draw->SetTextureResource(txt);
			}

			obj->SetAlphaActive(true);
			//��ڈȊO����
			if (i >= 1)
			{
				obj->SetDrawActive(false);
			}
			obj->SetDrawLayer(2);
			m_Eyes.push_back(obj);
		}
	}

	void CharEye::OnUpdate()
	{
		if (m_EyeCloseFlg)
		{
			EyeClose();
		}
		else
		{
			m_CountTime += App::GetApp()->GetElapsedTime();
			if (m_CountTime > m_IntarvalEyeTime)
			{
				m_CountTime = 0;
				//�m�����Ă�
				if (rand() % 100 < m_Par)
				{
					m_EyeCloseFlg = true;
				}
			}
		}
	}

	void CharEye::EyeClose()
	{
		m_CountTime += App::GetApp()->GetElapsedTime();
		if (m_CountTime > m_EyeCloseTime)
		{
			m_CountTime = 0;
			m_EyeCloseState++;
			switch (m_EyeCloseState)
			{
				//�ڔ���
			case 1:
				m_Eyes[0]->SetDrawActive(false);
				m_Eyes[1]->SetDrawActive(true);
				break;
				//�ڕ�
			case 2:
				m_Eyes[1]->SetDrawActive(false);
				m_Eyes[2]->SetDrawActive(true);
				break;
				//�ڊJ��
			case 3:
				m_Eyes[2]->SetDrawActive(false);
				m_Eyes[0]->SetDrawActive(true);

				m_EyeCloseFlg = false;
				m_EyeCloseState = 0;
				break;
			}
		}

	}
}

