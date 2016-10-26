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
	private :
		//���x
		float m_Speed = 5.0f;
		//�������W
		Vector3 m_InitPos;
		//�����̖��O
		string m_myName = "Player1";

		//������ƌ��{�^��������Ă邩�璲��
		bool m_endFrame = false;

		//����ł��邩�ǂ���
		bool m_ActiveFlg = true;
		//��Ԋ֐�
		void active();
		//�L�����؂�ւ��֐�
		void ChangeChar();
		//�J�����Ǐ]����
		void CameraTarget();
		//�J�����̍��W
		Vector3 m_CameraPos;
		//�J�����̌����Ă����
		Vector3 m_CameraTargetVec;
		//�J�����ړ��n�߂�͈�
		const float m_CameraMove = 3.0f;




		//���@�̃��X�g
		//*********************************//
		//MagicType��enum�^�Astdafx.h�ɏ����Ă���
		//Fire:���̋�
		//IceFog:�X�̖�
		//*********************************//
		MagicType m_Magic = None;

	public:
		//�\�z�Ɣj��
		//����(�������W�A����ł��邩�A�v���C���[�̖��O(Player1��Player2))
		Player(const shared_ptr<Stage>& StagePtr,Vector3 pos,bool Active,string Name);
		virtual ~Player() {}
		//������
		virtual void OnCreate() override;

		//�X�V
		virtual void OnUpdate() override;

		//�^�[���̍ŏI�X�V��
		virtual void OnLastUpdate() override;

		//����ł��邩���Z�b�g����֐�
		void SetActive(bool);

		//���@���o����֐�
		void SetMagic(MagicType);

		//�J�����Œ�H
		void SetCamera(Vector3 At,Vector3 pos);
	};

	

}
//end basecross

