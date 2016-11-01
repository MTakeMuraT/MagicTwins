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
		//�{�^������
		void ButtomInfo();
		//�V�[���J��
		void SceneChange();
		
		//�X�e�[�W�ԍ�
		unsigned int m_StageNum;
		//�X�e�B�b�N����
		bool m_Conflg;
		//���������I�u�W�F�N�g
		shared_ptr<GameObject> StringObj;
	public:
		//�\�z�Ɣj��
		StageSelect() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}