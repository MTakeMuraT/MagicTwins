/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{



	//--------------------------------------------------------------------------------------
	//	class Player : public GameObject;
	//	�p�r: �v���C���[
	//--------------------------------------------------------------------------------------
	class Player : public GameObject {
		shared_ptr< StateMachine<Player> >  m_StateMachine;	//�X�e�[�g�}�V�[��
															//�ړ��̌����𓾂�
		Vector3 GetAngle();
		//�ō����x
		float m_MaxSpeed;
		//������
		float m_Decel;
		//����
		float m_Mass;
	public:
		//�\�z�Ɣj��
		Player(const shared_ptr<Stage>& StagePtr);
		virtual ~Player() {}
		//������
		virtual void OnCreate() override;
		//�A�N�Z�T
		shared_ptr< StateMachine<Player> > GetStateMachine() const {
			return m_StateMachine;
		}
		//�X�V
		virtual void OnUpdate() override;
		//�^�[���̍ŏI�X�V��
		virtual void OnLastUpdate() override;
	};
}
//end basecross

