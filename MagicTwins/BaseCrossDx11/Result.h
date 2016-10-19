#pragma once
#include "stdafx.h"

namespace basecross
{
	class Result : public Stage
	{
		//���\�[�X�̍쐬
		void CreateResourses();
		//�r���[�̍쐬
		void CreateViewLight();
		//�w�i�摜�쐬
		void CreateBack();
		//���U���g����
		void CreateResultLogo();

		//�V�[���J��
		void SceneChange();
	public:
		Result() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};
}