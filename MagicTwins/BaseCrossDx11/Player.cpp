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

		//�ŉ��n�_
		PtrGravity->SetBaseY(0.0f);
		//�Փ˔��������
		auto PtrCol = AddComponent<CollisionSphere>();
		PtrCol->SetIsHitAction(IsHitAction::AutoOnObjectRepel);

		// ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		float angle = -90 * (3.14159265f /180);
		Matrix4X4 SpanMat;
		SpanMat.DefTransformation(
			Vector3(4.0f, 4.0f, 4.0f),
			Vector3(0.0f, angle, 0.0f),
			Vector3(0.0f, 1.0f, 0.0f)
			);



		if (m_myName == "Player1")
		{
			// ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
			angle = -90 * (3.14159265f / 180);
			SpanMat;
			SpanMat.DefTransformation(
				Vector3(2.0f, 2.0f, 2.0f),
				Vector3(0.0f, angle, 0.0f),
				Vector3(0.0f, 1.0f, 0.0f)
				);

			//�e������i�V���h�E�}�b�v��`�悷��j
			auto ShadowPtr = AddComponent<Shadowmap>();
			//�e�̌`�i���b�V���j��ݒ�
			ShadowPtr->SetMeshResource(L"Player1_Model");
			ShadowPtr->SetMeshToTransformMatrix(SpanMat);


			//�`��R���|�[�l���g�̐ݒ�
			auto PtrDraw = AddComponent<PNTStaticModelDraw>();
			//�`�悷�郁�b�V����ݒ�
			PtrDraw->SetMeshResource(L"Player1_Model");
			PtrDraw->SetMeshToTransformMatrix(SpanMat);

			//���@�쐬
			GetStage()->SetSharedGameObject(L"MagicBoal1", GetStage()->AddGameObject<MagicBoal>(Vector3(-100, -5.0f, 0),1));

			//���C�t�\��----------------------------------------
			auto obj = GetStage()->AddGameObject<GameObject>();
			auto objDraw = obj->AddComponent<PCTSpriteDraw>();
			objDraw->SetTextureResource(L"LIFE3_TX");

			auto objtrans = obj->AddComponent<Transform>();
			//1920,1080
			//960,540
			objtrans->SetPosition(-700, 420, 0);
			objtrans->SetRotation(0, 0, 0);
			objtrans->SetScale(400, 200, 1);
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
			MUIT->SetPosition(0,380,0);
			MUIT->SetRotation(0, 0, 0);
			MUIT->SetScale(300, 300, 0);
			MUI->SetAlphaActive(true);
			MUI->SetDrawLayer(3);
			m_MagicUI = MUI;
			//���@UI�\��----------------------------------------

		}
		else if (m_myName == "Player2")
		{
			//�e������i�V���h�E�}�b�v��`�悷��j
			auto ShadowPtr = AddComponent<Shadowmap>();
			//�e�̌`�i���b�V���j��ݒ�
			ShadowPtr->SetMeshResource(L"Player2_Model");
			ShadowPtr->SetMeshToTransformMatrix(SpanMat);


			//�`��R���|�[�l���g�̐ݒ�
			auto PtrDraw = AddComponent<PNTStaticModelDraw>();
			//�`�悷�郁�b�V����ݒ�
			PtrDraw->SetMeshResource(L"Player2_Model");
			PtrDraw->SetMeshToTransformMatrix(SpanMat);

			//���@�쐬
			GetStage()->SetSharedGameObject(L"MagicBoal2", GetStage()->AddGameObject<MagicBoal>(Vector3(-100, -5.0f, 0), 2));
			
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
	}

	//�X�V
	void Player::OnUpdate() {
		if (m_endFrame)
		{
			m_endFrame = false;
			return;
		}
		if (m_ActiveFlg)
		{
			CameraTarget();
			active();
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


			}

			//R�g���K�[�ŃL�����؂�ւ�
			if (CntlVec[0].wPressedButtons&XINPUT_GAMEPAD_RIGHT_SHOULDER)
			{
				ChangeChar();
			}

			//X�{�^���������疂�@����
			if (CntlVec[0].wPressedButtons&XINPUT_GAMEPAD_X)
			{
				ShotMagic();
			}
		}

		//�R���|�[�l���g�ɂ���Ă��炤���W�ړ�
		GetComponent<Rigidbody>()->SetVelocity(Vector3(m_velocity.x,0,m_velocity.y));


	}

	void Player::CameraTarget()
	{			
		//�J�����Ǐ]
		auto View = GetStage()->GetView();
		auto CameraP = View->GetTargetCamera();
		//�J�����ړ�
		Vector3 pos = GetComponent<Transform>()->GetPosition();
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
		m_CameraTargetVec.y = GetComponent<Transform>()->GetPosition().y;
		m_CameraPos.y = m_CameraTargetVec.y + 5.0f;
		CameraP->SetAt(m_CameraTargetVec);
		CameraP->SetEye(m_CameraPos);
	}


	//�L�����`�F���W
	void Player::ChangeChar()
	{
		m_velocity = Vector2(0, 0);
		GetComponent<Rigidbody>()->SetVelocity(Vector3(0, 0, 0));
		//�������ǂ���������
		if (m_myName == "Player1")
		{

			auto DPlayer = GetStage()->GetSharedGameObject<Player>(L"Player2", false);


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

	//�����ԑ���
	void Player::SetActive(bool flg)
	{
		m_ActiveFlg = flg;
		m_endFrame = true;
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
	void Player::OnLastUpdate() {

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
		default:
			break;
		}
		GetComponent<StringSprite>()->SetText(txt);
		
	}

	void Player::PlayerDamege()
	{
		m_life--;
		GetComponent<Rigidbody>()->SetVelocity(0, 10, 0);
		auto ScenePtr = App::GetApp()->GetScene<Scene>();

		switch (m_life)
		{
		case 0:
			//����
			m_LifeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"LIFE0_TX");
			//�Q�[���I�[�o�[�ɑJ��
			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameOver");
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
		Ptr->SetScale(0.25f, 0.25f, 0.25f);
		Ptr->SetRotation(0, 0, 0);
		Ptr->SetPosition(m_pos);

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ShadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");
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

	}

	void MagicBoal::OnUpdate()
	{
		if (m_ActiveFlg)
		{
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
		}
		else if (m_DeleteFlg)
		{
			Vector3 scale = GetComponent<Transform>()->GetScale();
			scale *= 0.95f;
			GetComponent<Transform>()->SetScale(scale);
			if (scale.x < 0)
			{
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
				break;
			case IceFog:
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"MAGICBOOKICEFOG_TX");
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
		GetComponent<Transform>()->SetScale(0.25f, 0.25f, 0.25f);
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

