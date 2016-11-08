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
		//Next�X�e�[�W���S�쐬
		void CreateNextStageLogo();
		//���g���C���S�쐬
		void CreateRetryLogo();
		//�X�e�[�W�Z���N�g���S�쐬
		void CreateStageSelectLogo();
		//�^�C�g�����S�쐬
		void CreateTitleLogo();
		//empty1
		void Createempty1();
		//empty2
		void Createempty2();
		//empty3
		void Createempty3();

		//�V�[���J��
		void SceneChange();
	public:
		Result() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};
}