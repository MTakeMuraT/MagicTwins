#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�^�C�g��
	//--------------------------------------------------------------------------------------
	class Title : public Stage {
		//���\�[�X�̍쐬
		void CreateResourses();
		//�r���[�̍쐬
		void CreateViewLight();
		//�w�i�摜�쐬
		void CreateBack();
		//�^�C�g������
		void CreateTitle();
		//PRESS START�쐬
		void CreatePressStart();
		//�X�e�[�W�Z���N�g���S�쐬
		void CreateStageSelectLogo();
		//�X�e�[�W�Z���N�g���
		void CreateArrow();

		//�L�����B���쐬
		void CreateChar();
		//�X�e�[�W�C���[�W�쐬
		void CreateStageImage();

		//�V�[���J��
		void SceneChange();

		//PRESS START�̓����x
		float m_PSAlpha = 1.0f;
		//���������Ă邩���̉����Ă邩false�œ�����
		bool m_PSAlphaFlg = false;

		//�A�j���[�V�����̏��
		int m_AnimationState = 0;
		//�A�j���[�V�������Ă邩�ǂ���
		bool m_AnimationFlg = false;

		//����
		float m_time = 0;

		//�^�C�g�����S
		shared_ptr<GameObject> m_TitleLogo;
		//�v���X�X�^�[�g���S
		shared_ptr<GameObject> m_PressStartLogo;
		//�����\���p
		shared_ptr<GameObject> m_String;
		//�L�����P�̉摜
		shared_ptr<GameObject> m_Char1;
		//�L�����Q�̉摜
		shared_ptr<GameObject> m_Char2;

		//�X�e�[�W�Z���N�g���S
		shared_ptr<GameObject> m_StageSelectLogo;
		//�X�e�[�W�Z���N�g���
		shared_ptr<GameObject> m_ArrowL;
		shared_ptr<GameObject> m_ArrowR;

		//�X�e�[�W�C���[�W
		shared_ptr<GameObject> m_StageImage;

		//�L�����̈ʒu�����p
		Vector3 m_Scale;
		Vector3 m_pos;

		//�`���[�g���A���݂����ǂ����X�V����t���O
		bool m_TutorialChamgeFlg = false;
	public:
		//�\�z�Ɣj��
		Title() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void Animation();
	};


}
