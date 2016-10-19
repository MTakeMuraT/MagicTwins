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

		//�V�[���J��
		void SceneChange();
	public:
		GameOver() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};
}