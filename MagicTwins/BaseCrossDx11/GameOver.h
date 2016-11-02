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
		//

		//�V�[���J��
		void SceneChange();
	public:
		GameOver() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};
}