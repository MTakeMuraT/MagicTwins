/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//���\�[�X�̍쐬
		void CreateResourses();
		//�r���[�̍쐬
		void CreateViewLight();
		//�������ԍ쐬
		void CreateLimitTime();
		//�R���W�����}�l�[�W���[�쐬
		void CreateCollisionManager();
		//�A�C�R���쐬
		void CreateIcons();

		//�|�[�Y���j���[�쐬
		void CreatePauseMenu();

		//�N���A�������ǂ���
		bool m_GoalFlg = false;

		//�S�[��������̏���
		void GoalState();
		//���
		int m_GoalState = 0;

		//�S�[���������Ƃ𔻒肷��I�u�W�F�N�g
		shared_ptr<GameObject> m_GoalObj;

		//�����\���I�u�W�F�N�g
		shared_ptr<GameObject> m_StringObj;

		//�S�[���ナ�U���g���o
		//1 ���U���g���S
		shared_ptr<GameObject> m_GoalLogo;
		//2 �{�̃e�N�X�`��
		shared_ptr<GameObject> m_Book;
		//3 �^�C���̃��S
		shared_ptr<GameObject> m_TimeLogo;
		//�����x
		float m_alpha = 0;
		//4 �c��^�C���v�Z�p
		float m_RemainingTime = 0;
		//������
		float m_AmountTime = 0;
		//�c��������
		int m_LimitTimeGoal = 0;
		//�ő厞��
		int m_LimitTimeMax = 0;
		//5 �X�R�A�A�C�e���̃��S
		shared_ptr<GameObject> m_ScoreItemLogo;
		//6 �X�R�A�A�C�e���擾���v�Z�p
		float m_ScoreItemCountCal = 0;
		//�X�R�A�A�C�e���擾��
		int m_ScoreItemCount = 0;
		//������
		float m_AmountScoreCount = 0;
		//7 �����N���S
		shared_ptr<GameObject> m_RankLogo;
		//8 �����N
		shared_ptr<GameObject> m_RankSprite;
		//9 �L�����摜
		shared_ptr<GameObject> m_Char1Sprite;
		shared_ptr<GameObject> m_Char2Sprite;
		//10����
		shared_ptr<GameObject> m_NextStageLogo;
		shared_ptr<GameObject> m_StageSelectLogo;
		shared_ptr<GameObject> m_TitleLogo;
		//11 �I��傫��
		Vector3 m_SelectScale = Vector3(500, 500, 1);
		Vector3 m_NotSelectScale = Vector3(400, 400, 1);
		//�I��ԍ� 0:�� 1:�X�e�Z�� 2:�^�C�g��
		int m_SelectNum = 0;
		//�ړ��t���O
		bool m_MoveConFlg = false;


		//�n�܂邩�ǂ����̃t���O
		bool m_StartFlg = false;
		//�Ȃ񂩂��܂������Ȃ����璲���p
		bool m_StartFlg2 = false;

		void StopAll();
		void StartAll();
	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
	};


}
//end basecross

