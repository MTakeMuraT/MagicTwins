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
		//�Ó]�p�̍�
		strTexture = DataDir + L"Black.png";
		App::GetApp()->RegisterTexture(L"BLACK_TX", strTexture);
		//����
		strTexture = DataDir + L"Number.png";
		App::GetApp()->RegisterTexture(L"NUMBER_TX", strTexture);

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
		//�X�R�A�A�C�e��
		strTexture = DataDir + L"ScoreItem.png";
		App::GetApp()->RegisterTexture(L"SCOREITEM_TX", strTexture);


		strTexture = DataDir + L"Gimmick1.png";
		App::GetApp()->RegisterTexture(L"GIMMICK1_TX", strTexture);
		strTexture = DataDir + L"Gimmick2.png";
		App::GetApp()->RegisterTexture(L"GIMMICK2_TX", strTexture);
		strTexture = DataDir + L"tex01.png";
		App::GetApp()->RegisterTexture(L"WATERGATE_TX", strTexture);
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
		//���g
		strTexture = DataDir + L"NullUI.png";
		App::GetApp()->RegisterTexture(L"NULLUI_TX", strTexture);
		strTexture = DataDir + L"FireUI.png";
		App::GetApp()->RegisterTexture(L"FIREUI_TX", strTexture);
		strTexture = DataDir + L"IceUI.png";
		App::GetApp()->RegisterTexture(L"ICEUI_TX", strTexture);
		strTexture = DataDir + L"WindUI.png";
		App::GetApp()->RegisterTexture(L"WINDUI_TX", strTexture);

		//��
		strTexture = DataDir + L"Fire01.png";
		App::GetApp()->RegisterTexture(L"FIREGIMMICK5_0_TX", strTexture);
		strTexture = DataDir + L"Fire02.png";
		App::GetApp()->RegisterTexture(L"FIREGIMMICK5_1_TX", strTexture);
		strTexture = DataDir + L"Fire03.png";
		App::GetApp()->RegisterTexture(L"FIREGIMMICK5_2_TX", strTexture);

		//�L����UI
		strTexture = DataDir + L"Chara1UI.png";
		App::GetApp()->RegisterTexture(L"CHARA1UI_TX", strTexture);
		strTexture = DataDir + L"Chara2UI.png";
		App::GetApp()->RegisterTexture(L"CHARA2UI_TX", strTexture);

		//����
		strTexture = DataDir + L"TimeWindow_01.png";
		App::GetApp()->RegisterTexture(L"TIME_TX", strTexture);
		//���j���[�A�C�R��
		strTexture = DataDir + L"Menuicon.png";
		App::GetApp()->RegisterTexture(L"MENUICON_TX", strTexture);
		//���@
		strTexture = DataDir + L"FireEf.png";
		App::GetApp()->RegisterTexture(L"FIREEF_TX", strTexture);
		strTexture = DataDir + L"IceEF.png";
		App::GetApp()->RegisterTexture(L"ICEEF_TX", strTexture);
		strTexture = DataDir + L"WindEF.png";
		App::GetApp()->RegisterTexture(L"WINDEF_TX", strTexture);

		//�|�[�Y���j���[
		strTexture = DataDir + L"PauseLogo.png";
		App::GetApp()->RegisterTexture(L"PAUSELOGO_TX", strTexture);
		strTexture = DataDir + L"ReTryLogo.png";
		App::GetApp()->RegisterTexture(L"PAUSERETRY_TX", strTexture);
		//strTexture = DataDir + L"PauseMapLogo.png";
		//App::GetApp()->RegisterTexture(L"PAUSEMAPLOGO_TX", strTexture);
		strTexture = DataDir + L"SelectBackLogo.png";
		App::GetApp()->RegisterTexture(L"PAUSESTAGESELECTLOGO_TX", strTexture);
		strTexture = DataDir + L"TitleBackLogo.png";
		App::GetApp()->RegisterTexture(L"PAUSETITLELOGO_TX", strTexture);
		strTexture = DataDir + L"map/map.png";
		App::GetApp()->RegisterTexture(L"MAP_TX", strTexture);
		//�}�b�v
		for (int i = 0; i <= 21; i++)
		{
			wstring txt = L"StageMap/Stage_" + Util::IntToWStr(i) + L".png";
			strTexture = DataDir + txt;
			wstring name = L"MAP_" + Util::IntToWStr(i) + L"_TX";
			App::GetApp()->RegisterTexture(name, strTexture);
		}


		//�G�t�F�N�g�pRight
		strTexture = DataDir + L"Light/RedLight.png";
		App::GetApp()->RegisterTexture(L"FIRELIGHT_TX", strTexture);
		strTexture = DataDir + L"Light/BlueLight.png";
		App::GetApp()->RegisterTexture(L"ICELIGHT_TX", strTexture);
		strTexture = DataDir + L"Light/GreenLight.png";
		App::GetApp()->RegisterTexture(L"WINDLIGHT_TX", strTexture);
		strTexture = DataDir + L"Light/WhiteLight.png";
		App::GetApp()->RegisterTexture(L"LIGHT_TX", strTexture);


		//�w�i
		strTexture = DataDir + L"Back_Sky.jpg";
		App::GetApp()->RegisterTexture(L"BACK_SKY_TX", strTexture);

		//�Q�[���X�^�[�g���S
		strTexture = DataDir + L"Game_Start_Logo.png";
		App::GetApp()->RegisterTexture(L"GAMESTARTLOGO_TX", strTexture);

		//�Ԙg
		strTexture = DataDir + L"Akawaku.png";
		App::GetApp()->RegisterTexture(L"AKAWAKU_TX", strTexture);

		//�^�[�Q�b�g���[�h�̐g
		strTexture = DataDir + L"TargetFrame.png";
		App::GetApp()->RegisterTexture(L"TARGETFRAME_TX", strTexture);

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

	//�������ԍ쐬
	void GameStage::CreateLimitTime()
	{
		auto LTP = AddGameObject<LimitTime>(90);
		SetSharedGameObject(L"LimitTime", LTP);
		GetSharedObjectGroup(L"SetUpdateObj")->IntoGroup(LTP);
	}

	
	//�R���W�����}�l�[�W���[�쐬
	void GameStage::CreateCollisionManager()
	{
		//�A�^������Ǘ��I�u�W�F�N�g�쐬
		auto ColManP = AddGameObject<CollisionManager>();
		SetSharedGameObject(L"ColMan", ColManP);

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

	//�S�[��������̏���
	void GameStage::GoalState()
	{
		if (m_GoalState == 0)
		{
			//���\�[�X�ǂݍ���
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			wstring strTexture = DataDir + L"Result/Result_Logo.png";
			App::GetApp()->RegisterTexture(L"RESULTLOGO_TX", strTexture);
			strTexture = DataDir + L"Result/BookTexture.png";
			App::GetApp()->RegisterTexture(L"BOOK_TX", strTexture);
			strTexture = DataDir + L"Result/Time_Logo.png";
			App::GetApp()->RegisterTexture(L"TIMELOGO_TX", strTexture);
			strTexture = DataDir + L"Result/Time_Logo.png";
			App::GetApp()->RegisterTexture(L"TIMELOGO_TX", strTexture);
			strTexture = DataDir + L"Result/item_Logo.png";
			App::GetApp()->RegisterTexture(L"ITEMLOGO_TX", strTexture);
			strTexture = DataDir + L"Result/Rank_Logo.png";
			App::GetApp()->RegisterTexture(L"RANKLOGO_TX", strTexture);

			strTexture = DataDir + L"Result/Rank_S.png";
			App::GetApp()->RegisterTexture(L"RANKS_TX", strTexture);
			strTexture = DataDir + L"Result/Rank_A.png";
			App::GetApp()->RegisterTexture(L"RANKA_TX", strTexture);
			strTexture = DataDir + L"Result/Rank_B.png";
			App::GetApp()->RegisterTexture(L"RANKB_TX", strTexture);
			strTexture = DataDir + L"Result/Rank_C.png";
			App::GetApp()->RegisterTexture(L"RANKC_TX", strTexture);

			strTexture = DataDir + L"Result/Result_Chara1.png";
			App::GetApp()->RegisterTexture(L"RESULTCHAR1_TX", strTexture);
			strTexture = DataDir + L"Result/Result_Chara2.png";
			App::GetApp()->RegisterTexture(L"RESULTCHAR2_TX", strTexture);

			//�I������
			strTexture = DataDir + L"Result/NextStage_Logo.png";
			App::GetApp()->RegisterTexture(L"GONEXTSTAGELOGO_TX", strTexture);

		}


		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		bool SkipFlg = false;
		switch (m_GoalState)
		{
			//�S�[�����S�쐬
		case 0:
			//�Ȃ񂩂��ꂾ�Ƃ�������ۂ�
			if (true)
			{
				auto obj = AddGameObject<GameObject>();
				auto objTrans = obj->AddComponent<Transform>();
				objTrans->SetPosition(0,425,0);
				objTrans->SetScale(2,1.5f,1);
				objTrans->SetRotation(0, 0, 0);
				auto objDraw = obj->AddComponent<PCTSpriteDraw>();
				objDraw->SetTextureResource(L"RESULTLOGO_TX");
				obj->SetAlphaActive(true);
				obj->SetDrawLayer(7);
				m_GoalLogo = obj;
			}
			m_GoalState = 1;
			break;
			//�S�[�����S�T�C�Y�傫��
		case 1:
			if (true)
			{

				Vector3 scale = m_GoalLogo->GetComponent<Transform>()->GetScale();
				if (scale.x < 800)
				{
					scale *= 1.1f;
				}
				else
				{
					//��d�ɓ����Ȃ��悤��
					SkipFlg = true;

					scale.x = 800;
					scale.y = 600;
					m_GoalState = 2;
					//���Ŏg���{�̉摜�쐬
					auto obj = AddGameObject<GameObject>();
					auto objTrans = obj->AddComponent<Transform>();
					objTrans->SetPosition(-1500,0, 0);
					objTrans->SetScale(1000, 650, 1);
					objTrans->SetRotation(0, 0, 0);
					auto objDraw = obj->AddComponent<PCTSpriteDraw>();
					objDraw->SetTextureResource(L"BOOK_TX");
					obj->SetAlphaActive(true);
					obj->SetDrawLayer(7);
					m_Book = obj;



					//����
					auto objBlack = AddGameObject<GameObject>();
					auto Draw = objBlack->AddComponent<PCTSpriteDraw>();
					Draw->SetTextureResource(L"BLACK_TX");
					Draw->SetDiffuse(Color4(1, 1, 1, 0.6f));
					auto Trans = objBlack->AddComponent<Transform>();
					Trans->SetPosition(0, 0, 0);
					Trans->SetScale(1920, 1080, 1);
					Trans->SetRotation(0, 0, 0);
					objBlack->SetDrawLayer(6);
					objBlack->SetAlphaActive(true);

				}

				//�{�^�������ꂽ��X�L�b�v
				if (CntlVec[0].bConnected && !SkipFlg)
				{
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
					{
						scale.x = 800;
						scale.y = 600;
						m_GoalState = 2;
						//���Ŏg���{�̉摜�쐬
						auto obj = AddGameObject<GameObject>();
						auto objTrans = obj->AddComponent<Transform>();
						objTrans->SetPosition(-1500, 0, 0);
						objTrans->SetScale(1000, 650, 1);
						objTrans->SetRotation(0, 0, 0);
						auto objDraw = obj->AddComponent<PCTSpriteDraw>();
						objDraw->SetTextureResource(L"BOOK_TX");
						obj->SetAlphaActive(true);
						obj->SetDrawLayer(7);
						m_Book = obj;


						//����
						auto objBlack = AddGameObject<GameObject>();
						auto Draw = objBlack->AddComponent<PCTSpriteDraw>();
						Draw->SetTextureResource(L"BLACK_TX");
						Draw->SetDiffuse(Color4(1, 1, 1, 0.6f));
						auto Trans = objBlack->AddComponent<Transform>();
						Trans->SetPosition(0, 0, 0);
						Trans->SetScale(1920, 1080, 1);
						Trans->SetRotation(0, 0, 0);
						objBlack->SetDrawLayer(6);
						objBlack->SetAlphaActive(true);

					}
				}
				m_GoalLogo->GetComponent<Transform>()->SetScale(scale);

			}
			break;
			//������{�̉摜�����Ă���
		case 2:
			if (true)
			{
				Vector3 pos = m_Book->GetComponent<Transform>()->GetPosition();
				if (pos.x < -400)
				{
					pos.x += 1500 * App::GetApp()->GetElapsedTime();
				}
				else
				{
					//��d�ɓ����Ȃ��悤��
					SkipFlg = true;

					m_GoalState = 3;

					//�^�C�����S�쐬
					auto obj = AddGameObject<GameObject>();
					auto objTrans = obj->AddComponent<Transform>();
					objTrans->SetPosition(-700, 200, 0);
					objTrans->SetScale(300, 300, 1);
					objTrans->SetRotation(0, 0, 0);
					auto objDraw = obj->AddComponent<PCTSpriteDraw>();
					objDraw->SetTextureResource(L"TIMELOGO_TX");
					objDraw->SetDiffuse(Color4(1, 1, 1, 0));
					obj->SetAlphaActive(true);
					obj->SetDrawLayer(7);
					m_TimeLogo = obj;

				}

				//�{�^�������ꂽ��X�L�b�v
				if (CntlVec[0].bConnected && !SkipFlg)
				{
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
					{
						pos.x = -400;

						m_GoalState = 3;

						//�^�C�����S�쐬
						auto obj = AddGameObject<GameObject>();
						auto objTrans = obj->AddComponent<Transform>();
						objTrans->SetPosition(-700, 200, 0);
						objTrans->SetScale(300, 300, 1);
						objTrans->SetRotation(0, 0, 0);
						auto objDraw = obj->AddComponent<PCTSpriteDraw>();
						objDraw->SetTextureResource(L"TIMELOGO_TX");
						objDraw->SetDiffuse(Color4(1, 1, 1, 0));
						obj->SetAlphaActive(true);
						obj->SetDrawLayer(7);
						m_TimeLogo = obj;

					}
				}

				m_Book->GetComponent<Transform>()->SetPosition(pos);

			}
			break;
			//�^�C����������
		case 3:
			if (true)
			{
				if (m_alpha < 1.0f)
				{
					m_alpha += 1.0f * App::GetApp()->GetElapsedTime();
					m_TimeLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1,m_alpha));
				}
				else
				{
					//��d�ɓ����Ȃ��悤��
					SkipFlg = true;

					m_TimeLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1));

					//��ԕύX�������x0
					m_alpha = 0;
					m_GoalState = 4;
					//�c�莞�Ԍv�Z�p������
					m_RemainingTime = 0;
					m_LimitTimeGoal = GetSharedGameObject<LimitTime>(L"LimitTime", false)->GetReamingTime();
					m_LimitTimeMax = GetSharedGameObject<LimitTime>(L"LimitTime", false)->GetLimitTime();
					//���Z��(���60fps��1�b)
					m_AmountTime = (float)(m_LimitTimeMax) / 60;

					//�A�C�e�����S�쐬
					auto obj = AddGameObject<GameObject>();
					auto objTrans = obj->AddComponent<Transform>();
					objTrans->SetPosition(-680, 50, 0);
					objTrans->SetScale(300, 300, 1);
					objTrans->SetRotation(0, 0, 0);
					auto objDraw = obj->AddComponent<PCTSpriteDraw>();
					objDraw->SetTextureResource(L"ITEMLOGO_TX");
					objDraw->SetDiffuse(Color4(1, 1, 1, 0));
					obj->SetAlphaActive(true);
					obj->SetDrawLayer(7);
					m_ScoreItemLogo = obj;

					SetSharedGameObject(L"RemainingNumberSprite",AddGameObject<NumberSprite>(0,Vector2(-250,210),Vector2(100,100),8));
				}


				//�{�^�������ꂽ��X�L�b�v
				if (CntlVec[0].bConnected && !SkipFlg)
				{
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
					{
						m_TimeLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1));

						//��ԕύX�������x0
						m_alpha = 0;
						m_GoalState = 4;
						//�c�莞�Ԍv�Z�p������
						m_RemainingTime = 0;
						m_LimitTimeGoal = GetSharedGameObject<LimitTime>(L"LimitTime", false)->GetReamingTime();
						m_LimitTimeMax = GetSharedGameObject<LimitTime>(L"LimitTime", false)->GetLimitTime();
						//���Z��(���60fps��0.5�b)
						m_AmountTime = (float)(m_LimitTimeMax) / 30;

						//�A�C�e�����S�쐬
						auto obj = AddGameObject<GameObject>();
						auto objTrans = obj->AddComponent<Transform>();
						objTrans->SetPosition(-680, 50, 0);
						objTrans->SetScale(300, 300, 1);
						objTrans->SetRotation(0, 0, 0);
						auto objDraw = obj->AddComponent<PCTSpriteDraw>();
						objDraw->SetTextureResource(L"ITEMLOGO_TX");
						objDraw->SetDiffuse(Color4(1, 1, 1, 0));
						obj->SetAlphaActive(true);
						obj->SetDrawLayer(7);
						m_ScoreItemLogo = obj;

						SetSharedGameObject(L"RemainingNumberSprite", AddGameObject<NumberSprite>(0, Vector2(-250, 210), Vector2(100, 100), 8));

					}
				}

			}
			break;
			//�c��^�C����������
		case 4:
			if (true)
			{
				auto RNS = GetSharedGameObject<NumberSprite>(L"RemainingNumberSprite", false);
				if (m_RemainingTime < m_LimitTimeGoal)
				{
					RNS->SetNum((int)(m_RemainingTime += m_AmountTime));
				}
				else
				{
					//��d�ɓ����Ȃ��悤��
					SkipFlg = true;

					m_RemainingTime = m_LimitTimeGoal;
					RNS->SetNum(m_LimitTimeGoal);
					m_GoalState = 5;
				}

				//�{�^�������ꂽ��X�L�b�v
				if (CntlVec[0].bConnected && !SkipFlg)
				{
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
					{
						m_RemainingTime = m_LimitTimeGoal;
						RNS->SetNum(m_LimitTimeGoal);
						m_GoalState = 5;

					}
				}
			}
			break;
			//�A�C�e����������
		case 5:
			if (true)
			{				
				if (m_alpha < 1.0f)
				{
					m_alpha += 1.0f * App::GetApp()->GetElapsedTime();
					m_ScoreItemLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_alpha));
				}
				else
				{
					//��d�ɓ����Ȃ��悤��
					SkipFlg = true;

					m_alpha = 0;
					m_GoalState = 6;
					m_ScoreItemLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1));


					//�X�R�A�擾����������
					m_ScoreItemCount = GetSharedGameObject<CollisionManager>(L"ColMan",false)->GetScoreItem();
					m_AmountScoreCount = (float)(m_ScoreItemCount) / 90;
					//�X�R�A������
					m_ScoreItemCountCal = 0;

					SetSharedGameObject(L"ScoreCountNumberSprite", AddGameObject<NumberSprite>(0, Vector2(-250, 50), Vector2(100, 100), 8));
				}


				//�{�^�������ꂽ��X�L�b�v
				if (CntlVec[0].bConnected && !SkipFlg)
				{
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
					{
						m_alpha = 0;
						m_GoalState = 6;
						m_ScoreItemLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1));


						//�X�R�A�擾����������
						m_ScoreItemCount = GetSharedGameObject<CollisionManager>(L"ColMan", false)->GetScoreItem();
						//1�b
						m_AmountScoreCount = (float)(m_ScoreItemCount) / 60;
						//�X�R�A������
						m_ScoreItemCountCal = 0;

						SetSharedGameObject(L"ScoreCountNumberSprite", AddGameObject<NumberSprite>(0, Vector2(-250, 50), Vector2(100, 100), 8));

					}
				}
				
			}
			break;
			//�擾����������
		case 6:
			if (true)
			{
				auto SCNP = GetSharedGameObject<NumberSprite>(L"ScoreCountNumberSprite", false);

				if (m_ScoreItemCountCal < m_ScoreItemCount)
				{
					SCNP->SetNum((int)(m_ScoreItemCountCal += m_AmountScoreCount));
				}
				else
				{
					//��d�ɓ����Ȃ��悤��
					SkipFlg = true;

					m_ScoreItemCountCal = m_ScoreItemCount;
					m_GoalState = 7;

					SCNP->SetNum((int)m_ScoreItemCount);

					//�����N���S�쐬
					auto obj = AddGameObject<GameObject>();
					auto objTrans = obj->AddComponent<Transform>();
					objTrans->SetPosition(-720, -150, 0);
					objTrans->SetScale(300, 300, 1);
					objTrans->SetRotation(0, 0, 0);
					auto objDraw = obj->AddComponent<PCTSpriteDraw>();
					objDraw->SetTextureResource(L"RANKLOGO_TX");
					objDraw->SetDiffuse(Color4(1, 1, 1, 0));
					obj->SetAlphaActive(true);
					obj->SetDrawLayer(7);
					m_RankLogo = obj;
				}

				//�{�^�������ꂽ��X�L�b�v
				if (CntlVec[0].bConnected && !SkipFlg)
				{
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
					{
						m_ScoreItemCountCal = m_ScoreItemCount;
						m_GoalState = 7;

						SCNP->SetNum((int)m_ScoreItemCount);

						//�����N���S�쐬
						auto obj = AddGameObject<GameObject>();
						auto objTrans = obj->AddComponent<Transform>();
						objTrans->SetPosition(-720, -150, 0);
						objTrans->SetScale(300, 300, 1);
						objTrans->SetRotation(0, 0, 0);
						auto objDraw = obj->AddComponent<PCTSpriteDraw>();
						objDraw->SetTextureResource(L"RANKLOGO_TX");
						objDraw->SetDiffuse(Color4(1, 1, 1, 0));
						obj->SetAlphaActive(true);
						obj->SetDrawLayer(7);
						m_RankLogo = obj;

					}
				}

			}
			break;
			//�����N��������
		case 7:
			if (true)
			{
				if (m_alpha < 1.0f)
				{
					m_alpha += 1.0f * App::GetApp()->GetElapsedTime();
					m_RankLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_alpha));
				}
				else
				{
					//��d�ɓ����Ȃ��悤��
					SkipFlg = true;

					m_RankLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1));

					m_alpha = 0;
					m_GoalState = 8;

					//�����N�쐬
					auto obj = AddGameObject<GameObject>();
					auto objTrans = obj->AddComponent<Transform>();
					objTrans->SetPosition(-150, -180, 0);
					objTrans->SetScale(300, 300, 1);
					objTrans->SetRotation(0, 0, 0);
					auto objDraw = obj->AddComponent<PCTSpriteDraw>();
					objDraw->SetTextureResource(L"RANKS_TX");

					//�����Ń����N�v�Z
					int ScoreItem = m_ScoreItemCount;
					int ClearTime = m_LimitTimeGoal;
					int TotalScore = ClearTime + (ScoreItem * 10);

					if (TotalScore >= 70)
					{
						objDraw->SetTextureResource(L"RANKS_TX");
					}
					else if (TotalScore >= 50)
					{
						objDraw->SetTextureResource(L"RANKA_TX");
					}
					else if (TotalScore >= 30)
					{
						objDraw->SetTextureResource(L"RANKB_TX");
					}
					else
					{
						objDraw->SetTextureResource(L"RANKC_TX");
					}
					objDraw->SetDiffuse(Color4(1, 1, 1, 0));
					obj->SetAlphaActive(true);
					obj->SetDrawLayer(7);
					m_RankSprite = obj;
				}

				//�{�^�������ꂽ��X�L�b�v
				if (CntlVec[0].bConnected && !SkipFlg)
				{
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
					{
						{
							m_RankLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1));

							m_alpha = 0;
							m_GoalState = 8;

							//�����N�쐬
							auto obj = AddGameObject<GameObject>();
							auto objTrans = obj->AddComponent<Transform>();
							objTrans->SetPosition(-150, -180, 0);
							objTrans->SetScale(300, 300, 1);
							objTrans->SetRotation(0, 0, 0);
							auto objDraw = obj->AddComponent<PCTSpriteDraw>();
							objDraw->SetTextureResource(L"RANKS_TX");
							objDraw->SetDiffuse(Color4(1, 1, 1, 0));
							obj->SetAlphaActive(true);
							obj->SetDrawLayer(7);
							//�����N�v�Z
							int ScoreItem = m_ScoreItemCount;
							int ClearTime = m_LimitTimeGoal;
							int TotalScore = ClearTime + (ScoreItem * 10);

							if (TotalScore >= 70)
							{
								objDraw->SetTextureResource(L"RANKS_TX");
							}
							else if (TotalScore >= 50)
							{
								objDraw->SetTextureResource(L"RANKA_TX");
							}
							else if (TotalScore >= 30)
							{
								objDraw->SetTextureResource(L"RANKB_TX");
							}
							else
							{
								objDraw->SetTextureResource(L"RANKC_TX");
							}

							m_RankSprite = obj;
						}
					}
				}
			}
			break;
			//�����N�\��t��
		case 8:
			if (true)
			{
				if (m_alpha < 1.0f)
				{
					m_alpha += 1.0f * App::GetApp()->GetElapsedTime();
					m_RankSprite->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_alpha));
				}
				else
				{
					//��d�ɓ����Ȃ��悤��
					SkipFlg = true;

					m_alpha = 0;
					m_GoalState = 9;
					m_RankSprite->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1));

					//�L�����摜
					auto obj = AddGameObject<GameObject>();
					auto objTrans = obj->AddComponent<Transform>();
					objTrans->SetPosition(1500, -50, 0);
					objTrans->SetScale(600, 600, 1);
					objTrans->SetRotation(0, 0, 0);
					auto objDraw = obj->AddComponent<PCTSpriteDraw>();
					objDraw->SetTextureResource(L"RESULTCHAR1_TX");
					obj->SetAlphaActive(true);
					obj->SetDrawLayer(7);
					m_Char1Sprite = obj;

					obj = AddGameObject<GameObject>();
					objTrans = obj->AddComponent<Transform>();
					objTrans->SetPosition(1500, -50, 0);
					objTrans->SetScale(600, 600, 1);
					objTrans->SetRotation(0, 0, 0);
					objDraw = obj->AddComponent<PCTSpriteDraw>();
					objDraw->SetTextureResource(L"RESULTCHAR2_TX");
					obj->SetAlphaActive(true);
					obj->SetDrawLayer(7);
					m_Char2Sprite = obj;

				}

				//�{�^�������ꂽ��X�L�b�v
				if (CntlVec[0].bConnected && !SkipFlg)
				{
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
					{
						{
							m_alpha = 0;
							m_GoalState = 9;
							m_RankSprite->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1));

							//�L�����摜
							auto obj = AddGameObject<GameObject>();
							auto objTrans = obj->AddComponent<Transform>();
							objTrans->SetPosition(1500, -50, 0);
							objTrans->SetScale(600, 600, 1);
							objTrans->SetRotation(0, 0, 0);
							auto objDraw = obj->AddComponent<PCTSpriteDraw>();
							objDraw->SetTextureResource(L"RESULTCHAR1_TX");
							obj->SetAlphaActive(true);
							obj->SetDrawLayer(7);
							m_Char1Sprite = obj;

							obj = AddGameObject<GameObject>();
							objTrans = obj->AddComponent<Transform>();
							objTrans->SetPosition(1500, -50, 0);
							objTrans->SetScale(600, 600, 1);
							objTrans->SetRotation(0, 0, 0);
							objDraw = obj->AddComponent<PCTSpriteDraw>();
							objDraw->SetTextureResource(L"RESULTCHAR2_TX");
							obj->SetAlphaActive(true);
							obj->SetDrawLayer(7);
							m_Char2Sprite = obj;
						}
					}
				}
			}
			break;
			//�L�����E����o�Ă���
		case 9:
			if (true)
			{
				
				Vector3 pos1 = m_Char1Sprite->GetComponent<Transform>()->GetPosition();
				Vector3 pos2 = m_Char2Sprite->GetComponent<Transform>()->GetPosition();
				float ElaTime = App::GetApp()->GetElapsedTime();

				if (pos1.x > 350)
				{
					pos1.x += -1500 * ElaTime;
				}
				else
				{
					pos1.x = 350;
				}
				if (pos2.x > 600)
				{
					pos2.x += -1200 * ElaTime;
				}
				else
				{
					pos2.x = 600;
				}

				//�ړ��I��
				if (pos1.x == 350 && pos2.x == 600)
				{
					//��d�ɓ����Ȃ��悤��
					SkipFlg = true;

					m_GoalState = 10;

					//�I�����ڍ쐬
					auto obj = AddGameObject<GameObject>();
					auto objTrans = obj->AddComponent<Transform>();
					objTrans->SetPosition(-600, -1000, 0);
					objTrans->SetScale(m_NotSelectScale);
					objTrans->SetRotation(0, 0, 0);
					auto objDraw = obj->AddComponent<PCTSpriteDraw>();
					objDraw->SetTextureResource(L"GONEXTSTAGELOGO_TX");
					obj->SetAlphaActive(true);
					obj->SetDrawLayer(7);
					m_NextStageLogo = obj;

					obj = AddGameObject<GameObject>();
					objTrans = obj->AddComponent<Transform>();
					objTrans->SetPosition(0, -1000, 0);
					objTrans->SetScale(m_NotSelectScale);
					objTrans->SetRotation(0, 0, 0);
					objDraw = obj->AddComponent<PCTSpriteDraw>();
					objDraw->SetTextureResource(L"PAUSESTAGESELECTLOGO_TX");
					obj->SetAlphaActive(true);
					obj->SetDrawLayer(7);
					m_StageSelectLogo = obj;

					obj = AddGameObject<GameObject>();
					objTrans = obj->AddComponent<Transform>();
					objTrans->SetPosition(600, -1000, 0);
					objTrans->SetScale(m_NotSelectScale);
					objTrans->SetRotation(0, 0, 0);
					objDraw = obj->AddComponent<PCTSpriteDraw>();
					objDraw->SetTextureResource(L"PAUSETITLELOGO_TX");
					obj->SetAlphaActive(true);
					obj->SetDrawLayer(7);
					m_TitleLogo = obj;	
				}


				//�{�^�������ꂽ��X�L�b�v
				if (CntlVec[0].bConnected&& !SkipFlg)
				{
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
					{
						{
							pos1.x = 350;
							pos2.x = 600;
							m_GoalState = 10;

							//�I�����ڍ쐬
							auto obj = AddGameObject<GameObject>();
							auto objTrans = obj->AddComponent<Transform>();
							objTrans->SetPosition(-600, -1000, 0);
							objTrans->SetScale(m_NotSelectScale);
							objTrans->SetRotation(0, 0, 0);
							auto objDraw = obj->AddComponent<PCTSpriteDraw>();
							objDraw->SetTextureResource(L"GONEXTSTAGELOGO_TX");
							obj->SetAlphaActive(true);
							obj->SetDrawLayer(7);
							m_NextStageLogo = obj;

							obj = AddGameObject<GameObject>();
							objTrans = obj->AddComponent<Transform>();
							objTrans->SetPosition(0, -1000, 0);
							objTrans->SetScale(m_NotSelectScale);
							objTrans->SetRotation(0, 0, 0);
							objDraw = obj->AddComponent<PCTSpriteDraw>();
							objDraw->SetTextureResource(L"PAUSESTAGESELECTLOGO_TX");
							obj->SetAlphaActive(true);
							obj->SetDrawLayer(7);
							m_StageSelectLogo = obj;

							obj = AddGameObject<GameObject>();
							objTrans = obj->AddComponent<Transform>();
							objTrans->SetPosition(600, -1000, 0);
							objTrans->SetScale(m_NotSelectScale);
							objTrans->SetRotation(0, 0, 0);
							objDraw = obj->AddComponent<PCTSpriteDraw>();
							objDraw->SetTextureResource(L"PAUSETITLELOGO_TX");
							obj->SetAlphaActive(true);
							obj->SetDrawLayer(7);
							m_TitleLogo = obj;

						}
					}
				}

				m_Char1Sprite->GetComponent<Transform>()->SetPosition(pos1);
				m_Char2Sprite->GetComponent<Transform>()->SetPosition(pos2);
			}
			break;
			//�I�����ډ�����o�Ă���
		case 10:
			if (true)
			{
				Vector3 pos1 = m_NextStageLogo->GetComponent<Transform>()->GetPosition();
				Vector3 pos2 = m_StageSelectLogo->GetComponent<Transform>()->GetPosition();
				Vector3 pos3 = m_TitleLogo->GetComponent<Transform>()->GetPosition();
				float ElaTime = App::GetApp()->GetElapsedTime();

				if (pos1.y < -430)
				{
					pos1.y += 1000 * ElaTime;
				}
				else
				{
					pos1.y = -430;
				}
				if (pos2.y < -430)
				{
					pos2.y += 1000 * ElaTime;
				}
				else
				{
					pos2.y = -430;
				}

				if (pos3.y < -430)
				{
					pos3.y += 1000 * ElaTime;
				}
				else
				{
					pos3.y = -430;
				}


				//�ړ��I��
				if (pos1.y == -430 && pos2.y == -430 && pos3.y == -430)
				{
					//��d�ɓ����Ȃ��悤��
					SkipFlg = true;

					m_NextStageLogo->GetComponent<Transform>()->SetScale(m_SelectScale);
					m_GoalState = 11;
				}

				//�{�^�������ꂽ��X�L�b�v
				if (CntlVec[0].bConnected && !SkipFlg)
				{
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
					{
						{
							pos1.y = -430;
							pos2.y = -430;
							pos3.y = -430;

							m_NextStageLogo->GetComponent<Transform>()->SetScale(m_SelectScale);
							m_GoalState = 11;

						}
					}
				}

				m_NextStageLogo->GetComponent<Transform>()->SetPosition(pos1);
				m_StageSelectLogo->GetComponent<Transform>()->SetPosition(pos2);
				m_TitleLogo->GetComponent<Transform>()->SetPosition(pos3);


			}
			break;
			//�I���A���͑҂�
		case 11:
			if (true)
			{
				auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
				if (CntlVec[0].bConnected)
				{
					
					Vector2 InputXY = Vector2(CntlVec[0].fThumbLX, CntlVec[0].fThumbLY);
					bool MoveFlg = false;
					if (m_MoveConFlg)
					{
						//�E
						if (InputXY.x > 0.8f)
						{
							m_SelectNum++;
							if (m_SelectNum > 2)
							{
								m_SelectNum = 0;
							}
							m_MoveConFlg = false;
							MoveFlg = true;
						}
						if (InputXY.x < -0.8f)
						{
							m_SelectNum--;
							if (m_SelectNum < 0)
							{
								m_SelectNum = 2;
							}
							m_MoveConFlg = false;
							MoveFlg = true;
						}
					}
					else if (!m_MoveConFlg)
					{
						if (abs(InputXY.x) < 0.1f && abs(InputXY.y) < 0.1f)
						{
							m_MoveConFlg = true;
						}
					}

					//�ړ�������傫���ύX
					if (MoveFlg)
					{
						switch (m_SelectNum)
						{
							//���̃X�e�[�W
						case 0:
							m_NextStageLogo->GetComponent<Transform>()->SetScale(m_SelectScale);
							m_StageSelectLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
							m_TitleLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
							break;
							//�X�e�[�W�Z���N�g
						case 1:
							m_NextStageLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
							m_StageSelectLogo->GetComponent<Transform>()->SetScale(m_SelectScale);
							m_TitleLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
							break;
							//�^�C�g��
						case 2:
							m_NextStageLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
							m_StageSelectLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
							m_TitleLogo->GetComponent<Transform>()->SetScale(m_SelectScale);
							break;
						}
					}
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
					{
						m_GoalState = 12;
						//�Ó]�p�̖��쐬
						auto obj = AddGameObject<Black>();
						obj->StartBlack();
						obj->SetDrawLayer(10);
						SetSharedGameObject(L"ResultBlack", obj);
						//SE�Đ�
						GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("Select");

					}
				}

			}
			break;
			//�Ó]�I������܂ő҂�
		case 12:
			if (true)
			{
				auto obj = GetSharedGameObject<Black>(L"ResultBlack", false);
				//�Ó]�I��������J��
				if (obj->GetBlackFinish())
				{
					m_GoalState = 13;
				}
			}
			break;
			//�I�����ꂽ�̂ŃV�[���ړ�
		case 13:
			switch (m_SelectNum)
			{
				//���̃X�e�[�W
			case 0:
				if (true)
				{
					auto ScenePtr = App::GetApp()->GetScene<Scene>();
					int StageNum = ScenePtr->GetStageNum();
					StageNum++;
					if (StageNum <= 21)
					{
						ScenePtr->SetStageNum(StageNum);
						PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameStage");
					}
					else
					{
						PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"Title");
					}
				}
				break;
				//�X�e�Z��
			case 1:
				if (true)
				{
					auto ScenePtr = App::GetApp()->GetScene<Scene>();
					PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"StageSelect");
				}
				break;
				//�^�C�g��
			case 2:
				if (true)
				{
					auto ScenePtr = App::GetApp()->GetScene<Scene>();
					PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"Title");
				}
				break;
			}
			break;
		default:
			break;
		}
		//wstring txt = Util::IntToWStr(m_GoalState);
		//txt += L"\n" + Util::IntToWStr(m_ScoreItemCount);
		//m_StringObj->GetComponent<StringSprite>()->SetText(txt);
	}

	//�S���X�g�b�v
	void GameStage::StopAll()
	{
		//�A�b�v�f�[�g�~�߂�
		auto UpdateGroup = GetSharedObjectGroup(L"SetUpdateObj")->GetGroupVector();
		for (auto v : UpdateGroup)
		{
			auto Ptr = dynamic_pointer_cast<GameObject>(v.lock());
			Ptr->SetUpdateActive(false);
		}
	}

	//�S���X�^�[�g
	void GameStage::StartAll()
	{
		//�A�b�v�f�[�g�N��
		auto UpdateGroup = GetSharedObjectGroup(L"SetUpdateObj")->GetGroupVector();
		for (auto v : UpdateGroup)
		{
			auto Ptr = dynamic_pointer_cast<GameObject>(v.lock());
			Ptr->SetUpdateActive(true);
		}
	}

	void GameStage::OnUpdate()
	{
		if (!m_StartFinish)
		{
			//1��ڃX���[
			if (m_StartFlg && !m_StartFlg2)
			{
				m_StartFlg = false;
				auto obj = AddGameObject<GameObject>();
				auto objDraw = obj->AddComponent<PCTSpriteDraw>();
				objDraw->SetTextureResource(L"GAMESTARTLOGO_TX");
				auto objTrans = obj->AddComponent<Transform>();
				objTrans->SetPosition(0, 0, 0);
				objTrans->SetScale(1000, 130, 1);
				objTrans->SetRotation(0, 0, 0);
				obj->SetAlphaActive(true);
				obj->SetDrawLayer(10);
				SetSharedGameObject(L"GameStartLogo", obj);
				return;
			}
			//2��ڃX���[
			else if (!m_StartFlg2 && !m_StartFlg)
			{
				m_StartFlg2 = true;
				StopAll();
				return;
			}
			//�ҋ@��
			else if (!m_StartFlg && m_StartFlg2)
			{

				//�_�ŏ���
				Color4 GSLDif = GetSharedGameObject<GameObject>(L"GameStartLogo")->GetComponent<PCTSpriteDraw>()->GetDiffuse();
				float alpha = GSLDif.GetA();
				alpha += -0.8f * App::GetApp()->GetElapsedTime();
				if (alpha < 0)
				{
					alpha = 1.0f;
				}
				GSLDif.SetA(alpha);
				GetSharedGameObject<GameObject>(L"GameStartLogo")->GetComponent<PCTSpriteDraw>()->SetDiffuse(GSLDif);

				auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
				if (CntlVec[0].bConnected)
				{

					//A��B�{�^�������ꂽ��X�^�[�g
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
					{
						StartAll();
						m_StartFlg = true;
						//SE�Đ�
						GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("Select");
					}

				}
				return;
			}
			else if (m_StartFlg && m_StartFlg2)
			{
				auto obj = GetSharedGameObject<GameObject>(L"GameStartLogo");
				Vector3 pos = obj->GetComponent<Transform>()->GetPosition();
				if (pos.x > 1500 && obj->GetDrawActive())
				{
					obj->SetDrawActive(false);
					m_StartFinish = true;
				}
				else if (pos.x < 1500)
				{
					pos.x += 1000 * App::GetApp()->GetElapsedTime();
					obj->GetComponent<Transform>()->SetPosition(pos);
				}
			}
		}

		//�S�[��������̏���
		if (m_GoalFlg)
		{
			GoalState();
			return;
		}
		
		//�S�[�������u�Ԃ̏���
		if (GetSharedGameObject<GameObject>(L"GoalObj")->GetDrawActive())
		{
			m_GoalFlg = true;
			//�A�b�v�f�[�g�~�߂�
			auto UpdateGroup = GetSharedObjectGroup(L"SetUpdateObj")->GetGroupVector();
			for (auto v : UpdateGroup)
			{
				auto Ptr = dynamic_pointer_cast<GameObject>(v.lock());
				Ptr->SetUpdateActive(false);
			}
			//�G�t�F�N�g�~�߂�
			auto EfGroupVec = GetSharedObjectGroup(L"Effect")->GetGroupVector();
			for (auto v : EfGroupVec)
			{
				auto Ptr = dynamic_pointer_cast<MagicParticle>(v.lock());
				Ptr->StopParticle();
			}
			return;
		}

		//*�e�X�g�p
		auto key = App::GetApp()->GetInputDevice().GetKeyState();
		if (key.m_bPressedKeyTbl[VK_SPACE])
		{
			//auto ScenePtr = App::GetApp()->GetScene<Scene>();
			//PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameStage");

			GetSharedGameObject<GameObject>(L"GoalObj")->SetDrawActive(true);
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

			//�J�������[�h���N�����Ȃ琧�����ԍ��Ȃ�
			if (!GetSharedGameObject<Player>(L"Player1", false)->GetCameraModeFlg())
			{

				//�w�i�쐬--------------------------------------
				auto BackP = AddGameObject<GameObject>();
				auto BPD = BackP->AddComponent<PNTStaticDraw>();
				BPD->SetMeshResource(L"DEFAULT_CUBE");
				BPD->SetTextureResource(L"BACK_SKY_TX");
				auto BPT = BackP->AddComponent<Transform>();
				BPT->SetPosition(0, 0, 0);
				BPT->SetScale(50, 50, 50);
				BPT->SetRotation(0, 0, 0);
				BackP->SetAlphaActive(true);
				BackP->SetDrawLayer(1);

				SetSharedGameObject(L"Back", BackP);
				//�w�i�쐬--------------------------------------
			}
			//�������Ԃ̍쐬
			//�J�������[�h���N�����Ȃ琧�����ԍ��Ȃ�
			if (!GetSharedGameObject<Player>(L"Player1", false)->GetCameraModeFlg())
			{
				CreateLimitTime();
			}
			//�|�[�Y���j���[�쐬
			CreatePauseMenu();
			//�R���W�����}�l�[�W���[�쐬
			CreateCollisionManager();
			//�A�C�R���쐬
			//�J�������[�h���N�����Ȃ�A�C�R�����Ȃ�
			if (!GetSharedGameObject<Player>(L"Player1", false)->GetCameraModeFlg())
			{
				CreateIcons();
			}

			CreateSharedObjectGroup(L"obj1");
			//SE�}�l�[�W���[
			SetSharedGameObject(L"SEM", AddGameObject<SEManager>());


			//�S�[�����肷��I�u�W�F�N�g�쐬
			auto obj = AddGameObject<GameObject>();
			obj->SetDrawActive(false);
			SetSharedGameObject(L"GoalObj", obj);

			//������I�u�W�F�N�g�쐬
			auto stringobj = AddGameObject<GameObject>();
			auto PtrString = stringobj->AddComponent<StringSprite>();
			PtrString->SetText(L"");
			PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
			PtrString->SetFont(L"", 80);

			m_StringObj = stringobj;  


			//�X�^�[�g�t���O��false�ɂ��������ǂȂ񂩕ς����璲��
			m_StartFlg = true;
			m_StartFlg2 = false;
			m_StartFinish = false;
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
