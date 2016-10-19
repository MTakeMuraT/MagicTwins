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
		//�Ó]�p�쐬
		void CreateBlack();
		//PRESS START�쐬
		void CreatePressStart();
		//�V�[���J��
		void SceneChange();

		//�R���g���[���[�������ǂ���
		bool m_ConFlg = true;

		//PRESS START�̓����x
		float m_PSAlpha = 1.0f;
		//���������Ă邩���̉����Ă邩false�œ�����
		bool m_PSAlphaFlg = false;
	public:
		//�\�z�Ɣj��
		Title() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}
