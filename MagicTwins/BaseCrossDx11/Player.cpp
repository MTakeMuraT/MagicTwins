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
		PtrGravity->SetBaseY(0.125f);
		//�Փ˔��������
		auto PtrCol = AddComponent<CollisionSphere>();
		//�������̂ݔ���
		PtrCol->SetIsHitAction(IsHitAction::AutoOnObjectRepel);



		// ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		float angle = -90 * (3.14159265f /180);
		Matrix4X4 SpanMat;
		SpanMat.DefTransformation(
			Vector3(1.0f, 1.0f, 1.0f),
			Vector3(0.0f, angle, 0.0f),
			Vector3(-1.0f, -2.5f, 3.0f)
			);

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ShadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ShadowPtr->SetMeshResource(L"Player_Model");
		ShadowPtr->SetMeshToTransformMatrix(SpanMat);

		
		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTStaticModelDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"Player_Model");
		PtrDraw->SetMeshToTransformMatrix(SpanMat);


		//if (m_myName == "Player1")
		//{
		//	//�`�悷��e�N�X�`����ݒ�
		//	PtrDraw->SetTextureResource(L"TRACE_TX");
		//}
		//else if (m_myName == "Player2")
		//{
		//	//�`�悷��e�N�X�`����ݒ�
		//	PtrDraw->SetTextureResource(L"TRACE2_TX");
		//}
		//�������O����Ă�ꍇ
		//else
		//{
		//	throw BaseException(
		//		L"Player�̖��O�w��~�X���Ă܂�", L"", L""
		//		);
		//}

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
		m_CameraPos = CameraP->GetEye();
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
				Vector3 Posi = TranP->GetPosition();
				inputXY *= ElapsedTime*m_Speed;
				Posi.x += inputXY.x;
				Posi.z += inputXY.y;
				TranP->SetPosition(Posi);

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

		}

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
		if (abs(Direction.z) > m_CameraMove)
		{
			//�}�C�i�X(����)
			if (Direction.z < 0)
			{
				Direction.z += m_CameraMove;
				//����Ă镪���炷�@
				m_CameraPos.z += Direction.z;
				m_CameraTargetVec.z += Direction.z;
			}
			//�v���X(�E��)
			else
			{
				Direction.z += -m_CameraMove;
				//����Ă镪���炷�@
				m_CameraPos.z += Direction.z;
				m_CameraTargetVec.z += Direction.z;
			}
		}
		CameraP->SetAt(m_CameraTargetVec);
		CameraP->SetEye(m_CameraPos);
	}


	//�L�����`�F���W
	void Player::ChangeChar()
	{
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

	//���@���L������
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

	//�J�����Œ�
	void Player::SetCamera(Vector3 At, Vector3 pos)
	{
		m_CameraPos = pos;
		m_CameraTargetVec = At;
	}

	//�^�[���̍ŏI�X�V��
	void Player::OnLastUpdate() {

		wstring txt;
		//��]�Ƃ��Ă邯�Ǖ\�����������̂��ȁH
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


}
//end basecross

