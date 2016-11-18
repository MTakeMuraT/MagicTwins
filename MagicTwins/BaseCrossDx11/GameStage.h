/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//���\�[�X�̍쐬
		void CreateResourses();
		//�r���[�̍쐬
		void CreateViewLight();
		//�v���[�g�̍쐬
		void CreatePlate();
		//�������ԍ쐬
		void CreateLimitTime();
		//�R���W�����}�l�[�W���[�쐬
		void CreateCollisionManager();
		//�A�C�R���쐬
		void CreateIcons();

		//�|�[�Y���j���[�쐬
		void CreatePauseMenu();
	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate() override;

	};


}
//end basecross

