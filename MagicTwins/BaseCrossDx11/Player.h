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
		
		
		//�ړ����Č������ړ������ɂ���
		void MoveRotationMotion();
		

		//�X�V
		virtual void OnUpdate() override;
		//void OnCollision(const shared_ptr<GameObject>& other);
		//�^�[���̍ŏI�X�V��
		virtual void OnLastUpdate() override;


	};

	

}
//end basecross

