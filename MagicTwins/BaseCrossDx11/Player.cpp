/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	class Player : public GameObject;
	//	�p�r: �v���C���[
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	Player::Player(const shared_ptr<Stage>& StagePtr, Vector3 pos, bool Active, string name) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_myName(name),
		m_ActiveFlg(Active)
	{}

	//������
	void Player::OnCreate() {
		//�����ʒu�Ȃǂ̐ݒ�
		auto Ptr = GetComponent<Transform>();
		Ptr->SetScale(0.25f, 0.25f, 0.25f);
		Ptr->SetRotation(0, 0, 0);
		Ptr->SetPosition(m_InitPos);


		//Rigidbody������
		auto PtrRedid = AddComponent<Rigidbody>();
		//�����W����0.5�i�����j
		PtrRedid->SetReflection(0.5f);

		//�d�͂�����
		auto PtrGravity = AddComponent<Gravity>();

		//�Փ˔��������
		auto PtrCol = AddComponent<CollisionSphere>();
		PtrCol->SetIsHitAction(IsHitAction::AutoOnObjectRepel);

		// ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		float angle = -90 * (3.14159265f /180);
		Matrix4X4 SpanMat;
		SpanMat.DefTransformation(
			Vector3(1.0f, 1.0f, 1.0f),
			Vector3(0.0f, angle, 0.0f),
			Vector3(0.0f, 1.0f, 0.0f)
			);



		if (m_myName == "Player1")
		{
			// ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
			angle = -90 * (3.14159265f / 180);
			SpanMat.DefTransformation(
				Vector3(1.5f, 1.5f, 1.5f),
				Vector3(0.0f, angle, 0.0f),
				Vector3(0.0f, 1.0f, 0.0f)
				);

			//�e������i�V���h�E�}�b�v��`�悷��j
			auto ShadowPtr = AddComponent<Shadowmap>();
			//�e�̌`�i���b�V���j��ݒ�
			ShadowPtr->SetMeshResource(L"Player1_Model");
			ShadowPtr->SetMeshToTransformMatrix(SpanMat);

			//�`��R���|�[�l���g�̐ݒ�
			auto PtrDraw = AddComponent<PNTBoneModelDraw>();
			//�`�悷�郁�b�V����ݒ�
			PtrDraw->SetMeshResource(L"Character1_Walk_MESH");
			PtrDraw->SetMeshToTransformMatrix(SpanMat);

			//�A�j���[�V�����ǉ�
			PtrDraw->AddAnimation(L"walk", 0, 180, true, 30);

			/*
			//�`��R���|�[�l���g�̐ݒ�
			auto PtrDraw = AddComponent<PNTStaticModelDraw>();
			//�`�悷�郁�b�V����ݒ�
			PtrDraw->SetMeshResource(L"Player1_Model");
			PtrDraw->SetMeshToTransformMatrix(SpanMat);
			*/

			//���@�쐬
			auto magicBoal = GetStage()->AddGameObject<MagicBoal>(Vector3(-100, -5.0f, 0), 1);
			GetStage()->SetSharedGameObject(L"MagicBoal1",magicBoal);
			//�A�b�v�f�[�g�~�߂�O���[�v�ɒǉ�
			GetStage()->GetSharedObjectGroup(L"SetUpdateObj")->IntoGroup(magicBoal);

			//���C�t�\��----------------------------------------
			auto obj = GetStage()->AddGameObject<GameObject>();
			auto objDraw = obj->AddComponent<PCTSpriteDraw>();
			objDraw->SetTextureResource(L"LIFE3_TX");

			auto objtrans = obj->AddComponent<Transform>();
			//1920,1080
			//960,540
			objtrans->SetPosition(-700, 400, 0);
			objtrans->SetRotation(0, 0, 0);
			objtrans->SetScale(400, 130, 1);
			obj->SetAlphaActive(true);
			obj->SetDrawLayer(3);
			m_LifeSprite = obj;
			//���C�t�\��----------------------------------------

			//���@UI�\��----------------------------------------
			//�Е��������Ώ\��
			auto MUI = GetStage()->AddGameObject<GameObject>();
			auto MUIDraw = MUI->AddComponent<PCTSpriteDraw>();
			MUIDraw->SetTextureResource(L"MAGICUI_TX");
			auto MUIT = MUI->AddComponent<Transform>();
			MUIT->SetPosition(0,420,0);
			MUIT->SetRotation(0, 0, 0);
			MUIT->SetScale(220, 220, 0);
			MUI->SetAlphaActive(true);
			MUI->SetDrawLayer(3);
			m_MagicUI = MUI;

			auto MUI2 = GetStage()->AddGameObject<GameObject>();
			auto MUIDraw2 = MUI2->AddComponent<PCTSpriteDraw>();
			MUIDraw2->SetTextureResource(L"NULLUI_TX");
			auto MUIT2 = MUI2->AddComponent<Transform>();
			MUIT2->SetPosition(0, 420, 0);
			MUIT2->SetRotation(0, 0, 0);
			MUIT2->SetScale(150, 150, 0);
			MUI2->SetAlphaActive(true);
			MUI2->SetDrawLayer(4);
			m_MagicUIIn = MUI2;
			//���@UI�\��----------------------------------------


			//�L����UI�\��--------------------------------------
			auto CHU = GetStage()->AddGameObject<GameObject>();
			auto CHUD = CHU->AddComponent<PCTSpriteDraw>();
			CHUD->SetTextureResource(L"CHARA1UI_TX");
			auto CHUT = CHU->AddComponent<Transform>();
			CHUT->SetPosition(-850, 480, 0);
			CHUT->SetRotation(0, 0, 0);
			CHUT->SetScale(100, 100, 0);
			CHU->SetAlphaActive(true);
			CHU->SetDrawLayer(3);
			CHU->SetDrawActive(true);
			m_CharaUI = CHU;
			//�L����UI�\��--------------------------------------

		}
		else if (m_myName == "Player2")
		{
			//�e������i�V���h�E�}�b�v��`�悷��j
			auto ShadowPtr = AddComponent<Shadowmap>();
			//�e�̌`�i���b�V���j��ݒ�
			ShadowPtr->SetMeshResource(L"Player2_Model");

			SpanMat.DefTransformation(
				Vector3(0.5f, 0.5f, 0.5f),
				Vector3(0.0f, angle, 0.0f),
				Vector3(0.0f, 1.0f, 0.0f)
				);

			ShadowPtr->SetMeshToTransformMatrix(SpanMat);


			//�`��R���|�[�l���g�̐ݒ�
			auto PtrDraw = AddComponent<PNTBoneModelDraw>();
			//�`�悷�郁�b�V����ݒ�
			PtrDraw->SetMeshResource(L"Character_02_WalkWalk_BONE_MESH");
			PtrDraw->SetMeshToTransformMatrix(SpanMat);

			//�A�j���[�V�����ǉ�
			PtrDraw->AddAnimation(L"walk", 0, 180, true, 30);

			//���@�쐬
			auto magicBoal = GetStage()->AddGameObject<MagicBoal>(Vector3(-100, -5.0f, 0), 2);
			GetStage()->SetSharedGameObject(L"MagicBoal2", magicBoal);
			//�A�b�v�f�[�g�~�߂�O���[�v�ɒǉ�
			GetStage()->GetSharedObjectGroup(L"SetUpdateObj")->IntoGroup(magicBoal);

			/*
			//���C�t�\��
			auto obj = GetStage()->AddGameObject<GameObject>();
			auto objDraw = obj->AddComponent<PCTSpriteDraw>();
			objDraw->SetTextureResource(L"LIFE3_TX");

			auto objtrans = obj->AddComponent<Transform>();
			//1920,1080
			//960,540
			objtrans->SetPosition(700, 420, 0);
			objtrans->SetRotation(0, 0, 0);
			objtrans->SetScale(400, 200, 1);
			obj->SetAlphaActive(true);
			obj->SetDrawLayer(3);
			m_LifeSprite = obj;

			*/

			//���C�t�\��----------------------------------------
			auto obj = GetStage()->AddGameObject<GameObject>();
			auto objDraw = obj->AddComponent<PCTSpriteDraw>();
			objDraw->SetTextureResource(L"LIFE3_TX");

			auto objtrans = obj->AddComponent<Transform>();
			//1920,1080
			//960,540
			objtrans->SetPosition(-700, 400, 0);
			objtrans->SetRotation(0, 0, 0);
			objtrans->SetScale(400, 130, 1);
			obj->SetAlphaActive(true);
			obj->SetDrawLayer(3);

			obj->SetDrawActive(false);
			m_LifeSprite = obj;
			//���C�t�\��----------------------------------------

			//�L����UI�\��--------------------------------------
			auto CHU = GetStage()->AddGameObject<GameObject>();
			auto CHUD = CHU->AddComponent<PCTSpriteDraw>();
			CHUD->SetTextureResource(L"CHARA2UI_TX");
			auto CHUT = CHU->AddComponent<Transform>();
			CHUT->SetPosition(-850, 480, 0);
			CHUT->SetRotation(0, 0, 0);
			CHUT->SetScale(100, 100, 0);
			CHU->SetAlphaActive(true);
			CHU->SetDrawLayer(3);
			CHU->SetDrawActive(false);
			m_CharaUI = CHU;
			//�L����UI�\��--------------------------------------


		}


		//�����������
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
		PtrString->SetFont(L"", 80);

		//��������
		SetAlphaActive(true);

		//�J�����֘A
		//�����Ă�Ƃ��L��
		m_CameraTargetVec = GetComponent<Transform>()->GetPosition();
		//���W�L��
		auto View = GetStage()->GetView();
		auto CameraP = View->GetTargetCamera();
		m_CameraPos = m_CameraTargetVec;
		m_CameraPos += Vector3(0, 5, -5);

		//�Ó]�p��--------------------------------------
		auto BlackP = GetStage()->AddGameObject<GameObject>();
		auto BlackPT = BlackP->AddComponent<Transform>();
		BlackPT->SetPosition(0, 0, 0);
		BlackPT->SetScale(1920, 1080, 1);
		BlackPT->SetRotation(0, 0, 0);

		auto BlackPD = BlackP->AddComponent<PCTSpriteDraw>();
		BlackPD->SetTextureResource(L"BLACK_TX");
		BlackPD->SetDiffuse(Color4(1, 1, 1, 0));

		BlackP->SetAlphaActive(true);
		BlackP->SetDrawLayer(2);
		m_Black = BlackP;
		//�Ó]�p��--------------------------------------

	}

	//�X�V
	void Player::OnUpdate() {
		//���񂾃t���O�����Ă���
		if (m_DieFlg)
		{
			if (m_BlackDie->GetBlackFinish())
			{
				//�Q�[���I�[�o�[�ɑJ��
				auto ScenePtr = App::GetApp()->GetScene<Scene>();
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameOver");
			}
			return;
		}
		if (m_WarpFlg)
		{
			m_WarpFlg = false;
			//�A�^���ꎮ�߂�
			GetComponent<CollisionSphere>()->SetUpdateActive(true);
			GetComponent<Rigidbody>()->SetUpdateActive(true);
			GetComponent<Gravity>()->SetUpdateActive(true);
		}
		if (m_endFrame)
		{
			m_endFrame = false;
			return;
		}
		if (m_BlackFlg)
		{
			//�Ó]��ԂȂ�
			if (m_BlackFlg)
			{
				if (m_BlackFlg2)
				{
					m_BlackAlpha += 1 * App::GetApp()->GetElapsedTime();
					m_Black->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));
					//�Â��Ȃ�����
					if (m_BlackAlpha > 1.0f)
					{
						ChangeChar();
						m_BlackAlpha = 1.0f;
						m_Black->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));
					}
				}
				else
				{
					m_BlackAlpha += -1 * App::GetApp()->GetElapsedTime();
					m_Black->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));
					if (m_BlackAlpha < 0)
					{
						m_BlackAlpha = 0;
						m_Black->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));
						m_endFrame = false;
						m_BlackFlg = false;

					}
				}
			}
			return;
		}
		if (m_ActiveFlg)
		{
			CameraTarget();
			active();
		}
		//���G���v�Z
		if (m_InviFlg)
		{
			Invincible();
		}
		
	}

	//����ł�����
	void Player::active()
	{
		//*�e�X�g�p
		auto key = App::GetApp()->GetInputDevice().GetKeyState();
		Vector2 velocity;
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		bool flg = false;
		if (key.m_bPushKeyTbl[VK_RIGHT])
		{
			velocity.x = 1 * m_Speed * ElapsedTime;
			flg = true;
		}
		if (key.m_bPushKeyTbl[VK_LEFT])
		{
			velocity.x = -1 * m_Speed * ElapsedTime;		
			flg = true;
		}
		if (key.m_bPushKeyTbl[VK_UP])
		{
			velocity.y = 1 * m_Speed * ElapsedTime;
			flg = true;
		}
		if (key.m_bPushKeyTbl[VK_DOWN])
		{
			velocity.y = -1 * m_Speed * ElapsedTime;
			flg = true;
		}

		//�R���g���[���[�̓���XY
		auto TranP = GetComponent<Transform>();
		Vector3 Posi = TranP->GetPosition();
		Posi.x += velocity.x;
		Posi.z += velocity.y;
		TranP->SetPosition(Posi);

		if (flg)
		{
			//�����𓾂�				
			float angle = atan2(velocity.y, velocity.x);
			angle *= -1;
			TranP->SetRotation(Vector3(0, angle, 0));
		}

		if (key.m_bPressedKeyTbl[VK_TAB])
		{
			ChangeChar();
		}

		if (key.m_bPressedKeyTbl['S'])
		{
			ShotMagic();
		}
		//*�e�X�g�p

		//���x����
		if (m_velocity.x < 0.1f || m_velocity.x > -0.1f || m_velocity.y < 0.1f || m_velocity.y > -0.1f)
		{
			if (m_velocity.x != 0 && m_velocity.y != 0)
			{
				m_velocity.x = 0;
				m_velocity.y = 0;
			}
		}
		else
		{
			m_velocity *= 0.98f;
		}
		

		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			//���͂������ł���������
			if (CntlVec[0].fThumbLX > 0.1f || CntlVec[0].fThumbLX < -0.1f ||
				CntlVec[0].fThumbLY > 0.1f || CntlVec[0].fThumbLY < -0.1f)
			{
				float ElapsedTime = App::GetApp()->GetElapsedTime();
				//�R���g���[���[�̓���XY
				Vector2 inputXY = Vector2(CntlVec[0].fThumbLX, CntlVec[0].fThumbLY);
				auto TranP = GetComponent<Transform>();
				//���W���ژM��
				/*Vector3 Posi = TranP->GetPosition();
				inputXY *= ElapsedTime*m_Speed;
				Posi.x += inputXY.x;
				Posi.z += inputXY.y;
				TranP->SetPosition(Posi);
				*/

				m_velocity += inputXY * m_Speed;

				//�����𓾂�				
				float angle = atan2(inputXY.y, inputXY.x);
				angle *= -1;
				TranP->SetRotation(Vector3(0, angle, 0));


					//�A�j���[�V�������X�V����(�R���g���[���[���X����Ɠ���)
					auto PtrDraw = GetComponent<PNTBoneModelDraw>();
					if (PtrDraw->GetCurrentAnimation() == L"walk") {
						//�A�j���[�V�����X�V
						PtrDraw->UpdateAnimation(ElapsedTime);
						//�A�j���[�V������ς���Ƃ�
						//PtrDraw->ChangeCurrentAnimation(L"Default");
					}
			}

			//R�g���K�[�ŃL�����؂�ւ�
			if (CntlVec[0].wPressedButtons&XINPUT_GAMEPAD_RIGHT_SHOULDER)
			{
				ChangeChar();
			}

			//X�{�^���������疂�@����
			if (CntlVec[0].wPressedButtons&XINPUT_GAMEPAD_A)
			{
				ShotMagic();
			}

			//L���{�^���ňʒu�Œ�
			if (CntlVec[0].wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
			{
				m_velocity = Vector2(0, 0);
			}

		}

		//�R���|�[�l���g�ɂ���Ă��炤���W�ړ�
		GetComponent<Rigidbody>()->SetVelocity(Vector3(m_velocity.x,0,m_velocity.y));


		//���W��������x���ɂȂ�����n�`�_���[�W�^���Ė߂�
		if (GetComponent<Transform>()->GetPosition().y < -10)
		{
			GetComponent<Transform>()->SetPosition(m_InitPos);
			PlayerTerrainDamege();
		}
	}

	void Player::CameraTarget()
	{			
		//�J�����Ǐ]
		auto View = GetStage()->GetView();
		auto CameraP = View->GetTargetCamera();
		//�J�����ړ�
		Vector3 pos = GetComponent<Transform>()->GetPosition();
		/*
		//�J�����ƃv���C���[�̍����v�Z
		pos.z += -5.0f;
		Vector3 Direction = pos - m_CameraPos;
		//���̔���
		if (abs(Direction.x) > m_CameraMove)
		{
			//�}�C�i�X(����)
			if (Direction.x < 0)
			{
				Direction.x += m_CameraMove;
				//����Ă镪���炷�@
				m_CameraPos.x += Direction.x;
				m_CameraTargetVec.x += Direction.x;
			}
			//�v���X(�E��)
			else
			{
				Direction.x += -m_CameraMove;
				//����Ă镪���炷�@
				m_CameraPos.x += Direction.x;
				m_CameraTargetVec.x += Direction.x;
			}
		}

		//���s����(�c�H)
		if (abs(Direction.z) > m_CameraMove-1.0f)
		{
			//�}�C�i�X(����)
			if (Direction.z < 0)
			{
				Direction.z += m_CameraMove-1.0f;
				//����Ă镪���炷�@
				m_CameraPos.z += Direction.z;
				m_CameraTargetVec.z += Direction.z;
			}
			//�v���X(�E��)
			else
			{
				Direction.z += -m_CameraMove + 1.0f;
				//����Ă镪���炷�@
				m_CameraPos.z += Direction.z;
				m_CameraTargetVec.z += Direction.z;
			}
		}
		*/
		//m_CameraTargetVec.y = GetComponent<Transform>()->GetPosition().y;
		m_CameraTargetVec = pos;
		//m_CameraPos.y = m_CameraTargetVec.y + 5.0f;
		m_CameraPos = m_CameraTargetVec;
		m_CameraPos.y += 6.0f;
		m_CameraPos.z += -6.0f;
		CameraP->SetAt(m_CameraTargetVec);
		CameraP->SetEye(m_CameraPos);

		//���łɔw�i���ړ�
		auto obj = GetStage()->GetSharedGameObject<GameObject>(L"Back",false);
		Vector3 PlayerPos = GetComponent<Transform>()->GetPosition();
		PlayerPos.y += -14;
		PlayerPos.z += 15;
		obj->GetComponent<Transform>()->SetPosition(PlayerPos);
	}

	//�L�����`�F���W
	void Player::ChangeChar()
	{
		if (m_BlackFlg2)
		{
			m_BlackFlg2 = false;

			m_velocity = Vector2(0, 0);
			GetComponent<Rigidbody>()->SetVelocity(Vector3(0, 0, 0));

			//�������ǂ���������
			if (m_myName == "Player1")
			{

				auto DPlayer = GetStage()->GetSharedGameObject<Player>(L"Player2", false);

				//���C�t���������\�� �L����UI��
				m_LifeSprite->SetDrawActive(false);
				m_CharaUI->SetDrawActive(false);
				DPlayer->DispUI();

				//���Ȃ�������G���[�I��
				if (!DPlayer)
				{
					throw BaseException(
						L"Player2���܂���", L"", L""
						);
				}

				//���������N��
				DPlayer->SetActive(true);
				//��������~
				m_ActiveFlg = false;


				//�J�����ړ�
				auto View = GetStage()->GetView();
				auto CameraP = View->GetTargetCamera();

				Vector3 At = DPlayer->GetComponent<Transform>()->GetPosition();
				Vector3 pos = At;

				//�J�����ړ����邽�߂ɏ�񑗂�
				pos.y += 5.0f;
				pos.z += -5.0f;

				DPlayer->SetCamera(At, pos);

				return;
			}
			else if (m_myName == "Player2")
			{
				auto DPlayer = GetStage()->GetSharedGameObject<Player>(L"Player1", false);

				//���C�t���������\�� �L����UI��
				m_LifeSprite->SetDrawActive(false);
				m_CharaUI->SetDrawActive(false);
				DPlayer->DispUI();

				//���Ȃ�������G���[�I��
				if (!DPlayer)
				{
					throw BaseException(
						L"Player1���܂���", L"", L""
						);
				}

				//���������N��
				DPlayer->SetActive(true);
				//��������~
				m_ActiveFlg = false;



				//�J�����ړ�
				auto View = GetStage()->GetView();
				auto CameraP = View->GetTargetCamera();

				Vector3 At = DPlayer->GetComponent<Transform>()->GetPosition();
				Vector3 pos = At;

				//�J�����ړ����邽�߂ɏ�񑗂�
				pos.y += 5.0f;
				pos.z += -5.0f;

				DPlayer->SetCamera(At, pos);
				return;
			}

			throw BaseException(
				L"���~�X���Ă܂�", L"", L""
				);
		}
		else
		{
			//�Ó]�p
			m_BlackFlg = true;
			m_BlackFlg2 = true;
			m_ActiveFlg = false;
			m_velocity = Vector3(0, 0, 0);
			GetComponent<Rigidbody>()->SetVelocity(Vector3(m_velocity.x, 0, m_velocity.y));
		}
	}

	//�����ԑ���
	void Player::SetActive(bool flg)
	{
		m_ActiveFlg = flg;
		m_endFrame = true;
	}

	//���G���Ԓ��̊֐�
	void Player::Invincible()
	{
		float ElaTime = App::GetApp()->GetElapsedTime();

		//�_��
		m_Flashingtime += ElaTime;
		if (m_Flashingtime > m_FlashingTimeInterval)
		{
			m_FlashingFlg = !m_FlashingFlg;
			SetDrawActive(m_FlashingFlg);
			m_Flashingtime = 0;
		}
		//���G���ԃJ�E���g
		m_InvTime += ElaTime;

		//�ݒ莞�Ԍo�߂�����
		if (m_InvTime > m_InvincibleTime)
		{
			//���G����
			m_InvTime = 0;
			SetDrawActive(true);
			m_InviFlg = false;

			//�_�ŏ�����
			m_Flashingtime = 0;
			m_FlashingFlg = false;
		}
	}

	//���@���L�����邱����1�̂ق��Ă΂��
	void Player::SetMagic(MagicType MT)
	{
		if (m_myName == "Player1")
		{
			m_Magic = MT;
			GetStage()->GetSharedGameObject<Player>(L"Player2", false)->SetMagic(MT);
		}
		else if (m_myName == "Player2")
		{
			m_Magic = MT;
		}
		else
		{
			throw BaseException(
				L"�N�₨�O", L"Player��myName��", L"���X�g�O��˂�"
				);
		}

		if (m_myName == "Player1")
		{

			//���@UI�ύX
			switch (MT)
			{
			case None:
				m_MagicUIIn->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"NULLUI_TX");
				break;
			case Fire:
				m_MagicUIIn->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"FIREUI_TX");
				//SE�Đ�
				GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("MagicGet");
				break;
			case IceFog:
				m_MagicUIIn->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"ICEUI_TX");
				//SE�Đ�
				GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("MagicGet");
				break;
			case Wind:
				m_MagicUIIn->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"WINDUI_TX");
				//SE�Đ�
				GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("MagicGet");
			default:
				break;
			}
		}
	}

	//���@�𔭎˂���
	void Player::ShotMagic()
	{
		if (m_myName == "Player1")
		{
			GetStage()->GetSharedGameObject<MagicBoal>(L"MagicBoal1", false)->SetActive(true,m_Magic);
		}
		else if (m_myName == "Player2")
		{
			GetStage()->GetSharedGameObject<MagicBoal>(L"MagicBoal2", false)->SetActive(true,m_Magic);

		}
	}

	//�J�����Œ�
	void Player::SetCamera(Vector3 At, Vector3 pos)
	{
		m_CameraPos = pos;
		m_CameraTargetVec = At;
	}

	//�^�[���̍ŏI�X�V��
	void Player::OnLastUpdate()
	{
		/*
		if (m_myName == "Player1")
		{
			wstring txt;
			Vector3 pos = GetComponent<Transform>()->GetPosition();
			txt += L"X = " + Util::FloatToWStr(pos.x) + L"\nY = " + Util::FloatToWStr(pos.y) + L"\nZ = " + Util::FloatToWStr(pos.z);
			GetComponent<StringSprite>()->SetText(txt);
		}
		*/
		/*
		wstring txt;
		//��]�Ƃ��Ă�
		//auto TranP = GetComponent<Transform>();
		//txt = Util::FloatToWStr(TranP->GetRotation().y * 180/3.14159265f);

		switch (m_Magic)
		{
		case None:
			txt += L"None";
			break;
		case Fire:
			txt += L"Fire";
			break;
		case IceFog:
			txt += L"IceFog";
			break;
		case Wind:
			txt += L"Wind";
		default:
			break;
		}
		GetComponent<StringSprite>()->SetText(txt);
		*/
	}

	void Player::PlayerDamege()
	{
		if (!m_InviFlg)
		{
			m_InviFlg = true;
			m_life--;
			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			//�ړ����邽�߃A�^������
			GetComponent<CollisionSphere>()->SetUpdateActive(false);
			GetComponent<Rigidbody>()->SetUpdateActive(false);
			GetComponent<Gravity>()->SetUpdateActive(false);

			Vector3 pos = GetComponent<Transform>()->GetPosition();
			pos.y += 0.25f;
			GetComponent<Transform>()->SetPosition(pos);

			//�ړ���ɃA�^������ꎮ������
			m_WarpFlg = true;

			//SE�Đ�
			GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("Damege");
			switch (m_life)
			{
			case 0:
				//����
				m_LifeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"LIFE0_TX");
				//�Q�[���I�[�o�[�ɑJ��
				//PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameOver");
				//�Ó]������
				m_DieFlg = true;
				if (true)
				{
					auto obj = GetStage()->AddGameObject<Black>();
					obj->StartBlack();
					m_BlackDie = obj;
				}
				break;
			case 1:
				m_LifeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"LIFE1_TX");
				break;
			case 2:
				m_LifeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"LIFE2_TX");
				break;
			}
		}
	}

	void Player::PlayerTerrainDamege()
	{
		//�ړ����邽�߃A�^������
		GetComponent<CollisionSphere>()->SetUpdateActive(false);
		GetComponent<Rigidbody>()->SetUpdateActive(false);
		GetComponent<Gravity>()->SetUpdateActive(false);

		//�ړ�
		Vector3 pos = m_InitPos;
		pos.y += 2;
		GetComponent<Transform>()->SetPosition(pos);

		//�ړ���ɃA�^������ꎮ������
		m_WarpFlg = true;

		//���C�t����
		m_life--;

		auto ScenePtr = App::GetApp()->GetScene<Scene>();

		//SE�Đ�
		GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("TerrainDamage");

		switch (m_life)
		{
		case 0:
			//����
			m_LifeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"LIFE0_TX");
			//�Q�[���I�[�o�[�ɑJ��
			//PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameOver");
			//�Ó]������
			m_DieFlg = true;
			if (true)
			{
				auto obj = GetStage()->AddGameObject<Black>();
				obj->StartBlack();
				m_BlackDie = obj;
			}
			break;
		case 1:
			m_LifeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"LIFE1_TX");
			break;
		case 2:
			m_LifeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"LIFE2_TX");
			break;
		}

	}

	//--------------------------------------------------------------------------------------
	//	class MagicBoal : public GameObject;
	//	�p�r: ���@
	//--------------------------------------------------------------------------------------

	MagicBoal::MagicBoal(const shared_ptr<Stage>& StagePtr, Vector3 pos,int m) :
		GameObject(StagePtr),
		m_pos(pos),
		m_mynumber(m)
	{}

	void MagicBoal::OnCreate()
	{
		//�����ʒu�Ȃǂ̐ݒ�
		auto Ptr = GetComponent<Transform>();
		Ptr->SetScale(m_magicSize);
		Ptr->SetRotation(0, 0, 0);
		Ptr->SetPosition(m_pos);

		//�e������i�V���h�E�}�b�v��`�悷��j
		//auto ShadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		//ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");
		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//���b�V����ݒ�
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		//�e�N�X�`����ݒ�
		PtrDraw->SetTextureResource(L"MAGICBOOKFIRE_TX");

		//������
		SetAlphaActive(true);

		//�����������
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 320.0f, 640.0f, 480.0f));
		PtrString->SetFont(L"", 60);

		/*
		for (int i = 0; i < 10; i++)
		{

			//���_�z��
			vector<VertexPositionNormalTexture> vertices;
			//�C���f�b�N�X���쐬���邽�߂̔z��
			vector<uint16_t> indices;
			//Square�̍쐬(�w���p�[�֐��𗘗p)
			MeshUtill::CreateSquare(1.0f, vertices, indices);
			//UV�l�̕ύX
			float from = i / 10.0f;
			float to = from + (1.0f / 10.0f);
			//���㒸�_
			vertices[0].textureCoordinate = Vector2(from, 0);
			//�E�㒸�_
			vertices[1].textureCoordinate = Vector2(to, 0);
			//�������_
			vertices[2].textureCoordinate = Vector2(from, 1.0f);
			//�E�����_
			vertices[3].textureCoordinate = Vector2(to, 1.0f);
			//���_�̌^��ς����V�������_���쐬
			vector<VertexPositionColorTexture> new_vertices;
			for (auto& v : vertices) {
				VertexPositionColorTexture nv;
				nv.position = v.position;
				nv.color = Color4(1.0f, 1.0f, 1.0f, 1.0f);
				nv.textureCoordinate = v.textureCoordinate;
				new_vertices.push_back(nv);
			}
			//���b�V���쐬
			m_Mesh.push_back(MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true));
		}

		//�A�Ԃ̂P��ݒ�
		PtrDraw->SetMeshResource(m_Mesh[0]);
		*/
	}

	void MagicBoal::OnUpdate()
	{
		if (m_ActiveFlg)
		{
			/*
			//�A�j���[�V�����X�V
			m_CountTime += App::GetApp()->GetElapsedTime();
			//�Ԋu���ԉz������
			if (m_CountTime > m_ConstCountTime)
			{
				m_CountTime = 0;
				m_MeshNumber++;
				if (m_MeshNumber > 9)
				{
					m_MeshNumber = 0;
				}

				//�e�N�X�`���؂�ւ�
				GetComponent<PNTStaticDraw>()->SetMeshResource(m_Mesh[m_MeshNumber]);
			}*/

			Vector3 pos = GetComponent<Transform>()->GetPosition();
			float Elapsed = App::GetApp()->GetElapsedTime();
			pos += Vector3(m_velocity.x*Elapsed, 0, m_velocity.y*Elapsed);
			GetComponent<Transform>()->SetPosition(pos);
			//�������Ԍv�Z
			m_lifeTime += App::GetApp()->GetElapsedTime();
			if (m_lifeTime > m_LifeTimeLimit)
			{
				m_lifeTime = 0;
				m_DeleteFlg = true;
				m_ActiveFlg = false;
			}
			//�X�͒Z��
			if (m_MagicType == IceFog && m_lifeTime > m_shortLimitTime)
			{
				m_lifeTime = 0;
				m_DeleteFlg = true;
				m_ActiveFlg = false;

			}
		}
		else if (m_DeleteFlg)
		{
			Vector3 scale = GetComponent<Transform>()->GetScale();
			scale *= 0.95f;
			GetComponent<Transform>()->SetScale(scale);
			if (scale.x < 0.2f)
			{
				GetComponent<Transform>()->SetPosition(Vector3(0, -10, 0));
				SetDrawActive(false);
				m_DeleteFlg = false;
			}
		}
	}

	//��ԑ���
	void MagicBoal::SetActive(bool flg,MagicType mT)
	{
		if (!m_ActiveFlg && flg == true)
		{

			m_ActiveFlg = flg;
			m_MagicType = mT;
			switch (m_MagicType)
			{
			case None:
				return;
				break;
			case Fire:
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"MAGICBOOKFIRE_TX");
				//SE�Đ�
				GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("MagicShotFire");
				break;
			case IceFog:
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"MAGICBOOKICEFOG_TX");
				//SE�Đ�
				GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("MagicShotIce");
				break;
			case Wind:
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"MAGICBOOKWIND_TX");
				//SE�Đ�
				GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("MagicShotWind");
				break;
			default:
				break;
			}
			SetVelo();
		}
		//�����Ă�Ƃ��Ƀt���O����ꂽ��
		if (m_ActiveFlg && flg == false)
		{
			m_DeleteFlg = true;
			m_ActiveFlg = false;
		}

		m_ActiveFlg = flg;

	}

	//�����A�ړ��ʌv�Z
	void MagicBoal::SetVelo()
	{
		GetComponent<Transform>()->SetScale(m_magicSize);
		SetDrawActive(true);

		if (m_mynumber == 1)
		{
			auto PlayerP = GetStage()->GetSharedGameObject<Player>(L"Player1", false);
			Vector3 pos = PlayerP->GetComponent<Transform>()->GetPosition();
			pos.y += 0.5f;
			float angle = PlayerP->GetComponent<Transform>()->GetRotation().y;
			
			//�ړ��ʎZ�o
			angle *= -1;
			m_velocity.x = cos(angle);
			m_velocity.y = sin(angle);
			m_velocity *= m_speed;

			GetComponent<Transform>()->SetPosition(pos);
		}
		else if(m_mynumber == 2)
		{
			auto PlayerP = GetStage()->GetSharedGameObject<Player>(L"Player2", false);
			Vector3 pos = PlayerP->GetComponent<Transform>()->GetPosition();
			pos.y += 0.5f;
			float angle = PlayerP->GetComponent<Transform>()->GetRotation().y;

			//�ړ��ʎZ�o
			angle *= -1;
			m_velocity.x = cos(angle);
			m_velocity.y = sin(angle);
			m_velocity *= m_speed;

			GetComponent<Transform>()->SetPosition(pos);

		}
	}

	MagicType MagicBoal::GetMagicType()
	{
		return m_MagicType;
	}

	bool MagicBoal::GetActive()
	{
		return m_ActiveFlg;
	}
}
//end basecross

