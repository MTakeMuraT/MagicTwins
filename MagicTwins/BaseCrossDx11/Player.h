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
		float m_Speed = 3.0f;
		//�̗�
		int m_life = 3;
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

		//�̗͕\��
		shared_ptr<GameObject> m_LifeSprite;

		//���x
		Vector2 m_velocity;

		//���@�ł֐�
		void ShotMagic();

		//���@�̃��X�g
		//*********************************//
		//MagicType��enum�^�Astdafx.h�ɏ����Ă���
		//Fire:���̋�
		//IceFog:�X�̖�
		//*********************************//
		MagicType m_Magic = None;

		//���@UI
		shared_ptr<GameObject> m_MagicUI;
		//���gUI
		shared_ptr<GameObject> m_MagicUIIn;

		//�L����UI
		shared_ptr<GameObject> m_CharaUI;
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

		bool GetActive() { return m_ActiveFlg; };

		//���@���o����֐�
		void SetMagic(MagicType);

		//�J�����Œ�H
		void SetCamera(Vector3 At,Vector3 pos);

		//�_���[�W����
		void PlayerDamege();

		//���C�t�\��
		void DispUI() { m_LifeSprite->SetDrawActive(true); m_CharaUI->SetDrawActive(true); }
	};

	//--------------------------------------------------------------------------------------
	//	class MagicBoal : public GameObject;
	//	�p�r: ���@
	//--------------------------------------------------------------------------------------
	class MagicBoal : public GameObject
	{
	private :
		//�ړ���
		Vector2 m_velocity;
		//���W
		Vector3 m_pos;
		//�傫��
		Vector3 m_magicSize = Vector3(0.25f, 0.25f, 0.25f);

		//�����Ă邩�ǂ���
		bool m_ActiveFlg = false;
		//���x
		float m_speed = 5.0f;
		//�����̔ԍ�
		int m_mynumber;
		//��������
		float m_lifeTime;
		const float m_LifeTimeLimit = 1.0f;

		//���Ńt���O
		bool m_DeleteFlg = false;
		//�����̑���
		MagicType m_MagicType = None;

	public :
		MagicBoal(const shared_ptr<Stage>& StagePtr, Vector3 pos,int m);
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//���˂���
		void SetActive(bool,MagicType);

		//�ړ��ʎZ�o
		void SetVelo();

		//���������Ă���
		MagicType GetMagicType();

		//������񎝂��Ă���
		bool GetActive();
	};

}
//end basecross

