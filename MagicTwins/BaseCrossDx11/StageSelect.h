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
		//�X�e�[�W�Z���N�g�摜(��)
		void CreaateStageSelect();
		//�V�[���J��
		void SceneChange();
		//�����(��)
		void Left();
		//�E���(��)
		void Right();

		unsigned int m_MaxNum = 5;
		int m_SceneNum;

		bool m_flag;

	public:
		//�\�z�Ɣj��
		StageSelect() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}