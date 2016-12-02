#pragma once
#include "stdafx.h"

namespace basecross
{
	class GameOver : public Stage
	{
		//���\�[�X�̍쐬
		void CreateResourses();
		//�r���[�̍쐬
		void CreateViewLight();
		//�w�i�摜�쐬
		void CreateBack();
		//�Q�[���I�[�o�[����
		void CreateOverLogo();
		//���g���C�̍쐬
		void CreateRetry();
		//�X�e�[�W�Z���N�g�̍쐬
		void CreateStageSelect();
		//�^�C�g���̍쐬
		void CreateTitle();
		//�L�����쐬
		void CreateChar();


		//�V�[���J��
		void SceneChange();

		int m_selectnum = 0;
		//����t���O
		bool m_moveFlg = false;
		
		//���g���C���S
		shared_ptr<GameObject> m_ReTryLogo;
		//�Z���N�g���S
		shared_ptr<GameObject> m_SelectLogo;
		//�^�C�g�����S
		shared_ptr<GameObject> m_TitleLogo;


		//�I����Scale
		const Vector3 m_SelectScale = Vector3(500, 500, 1);
		const Vector3 m_NotSelectScale = Vector3(400, 400, 1);

	public:
		GameOver() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};
}