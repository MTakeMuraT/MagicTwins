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
		//���x
		float m_Speed;
	public:
		//�\�z�Ɣj��
		Player(const shared_ptr<Stage>& StagePtr);
		virtual ~Player() {}
		//������
		virtual void OnCreate() override;

		//�X�V
		virtual void OnUpdate() override;

		//�^�[���̍ŏI�X�V��
		virtual void OnLastUpdate() override;


	};

	

}
//end basecross

