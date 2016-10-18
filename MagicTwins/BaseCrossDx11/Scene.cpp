
/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------

	void Scene::OnCreate(){
		try {
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			//ResetActiveStage<GameStage>();
			ResetActiveStage<Title>();

		}
		catch (...) {
			throw;
		}
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		//�^�C�g��
		if (event->m_MsgStr == L"Title")
		{
			ResetActiveStage<Title>();

		}
		//�X�e�[�W�Z���N�g
		else if (event->m_MsgStr == L"StageSelect")
		{

		}
		//�Q�[����
		else if (event->m_MsgStr == L"GameStage")
		{
			ResetActiveStage<GameStage>();
		}
		//�N���A
		else if (event->m_MsgStr == L"Clear")
		{

		}
		//�Q�[���I�[�o�[
		else if (event->m_MsgStr == L"GameOver")
		{

		}

	}

}
//end basecross
