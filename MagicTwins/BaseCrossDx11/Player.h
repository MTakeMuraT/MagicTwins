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
		//�B�e���[�h
		bool m_CameraMode = false;

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

		//���G����
		const float m_InvincibleTime = 2.0f;
		//���G���Ԍv�Z�p
		float m_InvTime = 0;
		//���G�t���O
		bool m_InviFlg = false;

		//���G�_�Ŏ���
		float m_Flashingtime = 0;
		//���� ���o
		const float m_FlashingTimeInterval = 0.1f;
		//��������
		bool m_FlashingFlg = false;



		//���G���Ԓ��̊֐�
		void Invincible();

		//�u�Ԉړ��ł��Ȃ��Ȃ�Ώ�
		bool m_WarpFlg = false;
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
		 
		//�Ó]�p��
		shared_ptr<GameObject> m_Black;

		//�L�����Ó]�؂�ւ��p
		//���������Ó]���邩�ǂ���
		bool m_BlackFlg = false;
		//���o�Ă��Ԃ������Ă��Ԃ�
		bool m_BlackFlg2 = false;
		float m_BlackAlpha = 0;

		//���񂾃t���O
		bool m_DieFlg = false;
		//�Ó]�p��
		shared_ptr<Black> m_BlackDie;

		//���@�ł��Ɉړ��ł��Ȃ�����t���O
		bool m_ShotMagicStopFlg = false;
		//���@�ł������̍d������
		const float m_ShotStopTime = 0.8f;
		//���@�ł�����̃J�E���g�p����
		float m_ShotMagicCountTime = 0;
		//���@�ł����t���O
		bool m_ShotMagicFlg = false;
		//�^�[�Q�b�g���[�h�t���O
		bool m_TargetModeFlg = false;
		//�^�[�Q�b�g�g
		shared_ptr<GameObject> m_TargetModeFrame;
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

		//�n�`�_���[�W
		void PlayerTerrainDamege();

		//���C�t�\��
		void DispUI() { m_LifeSprite->SetDrawActive(true); m_CharaUI->SetDrawActive(true); }

		//�J�������[�h���ǂ���
		bool GetCameraModeFlg() { return m_CameraMode; }
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
		const float m_shortLimitTime = 0.2f;

		//���Ńt���O
		bool m_DeleteFlg = false;
		//�����̑���
		MagicType m_MagicType = None;

		//�Ȃ񂩂���񃁃b�V���̃��X�g
		vector<shared_ptr<MeshResource>> m_Mesh;

		//���̘A�Ԃ̔ԍ�
		unsigned int m_MeshNumber = 0;
		//�摜�؂�ւ���^�C�~���O�v�Z�p
		float m_CountTime = 0;
		const float m_ConstCountTime = 0.3f;
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

