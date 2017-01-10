#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�X�e�[�W�Z���N�g
	//--------------------------------------------------------------------------------------
	class  StageSelect: public Stage {
		//���\�[�X�̍쐬
		void CreateResourses();
		//�r���[�̍쐬
		void CreateViewLight();
		//�w�i�摜�쐬
		void CreateBack();
		//�Z���N�g���S
		void CreateSelectLogo();
		//�{�^���쐬
		void CreateButtons();
		//�X�e�[�W�C���[�W�쐬
		void CreateStageImageFrame();
		//�V�[���J��
		void SceneChange();
		//�����(��)
		void Left();
		//�E���(��)
		void Right();
		//�X�e�[�W�C���[�W
		void CreateStageImage();

		//�ő�l
		unsigned int m_MaxStageNum = 20;
		//���ݑI�𒆂̐���
		unsigned int m_StageNum = 0;

		//�I������Ƃ��̒���
		bool m_flag;

		//�{�^���������Ƃ��̏���
		bool m_SelectFlg = false;

		//�X�e�[�W�C���[�W
		shared_ptr<GameObject> m_StageImage;
		//��]���Ă�ƌ��������ăT�C�Y�ύX����B�ǂ����X�v���C�g�ł͉�]���ł��Ȃ��炵��
		//��]��
		bool m_StageImageRotFlg = false;
		//�r���܂ł�������
		bool m_SIHalfFlg = false;
		//�C���[�W��]
		void RotStageImage();
	public:
		//�\�z�Ɣj��
		StageSelect() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}