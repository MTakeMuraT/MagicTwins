
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
			//ResetActiveStage<Title>();
			ResetActiveStage<StageSelect>();
			//ResetActiveStage<GameOver>();
			//ResetActiveStage<Result>();
		}
		catch (...) {
			throw;
		}
		//���f���ǂݍ��݁B�Ȃ񂩃Q�[���X�e�[�W�ł������~�X������K�X
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		auto ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Char/Character_01.bmf");
		App::GetApp()->RegisterResource(L"Player_Model", ModelMesh);
		ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Windmill/Windmill.bmf");
		App::GetApp()->RegisterResource(L"Windmill_Model", ModelMesh);

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
			ResetActiveStage<StageSelect>();
		}
		//�Q�[����
		else if (event->m_MsgStr == L"GameStage")
		{
			ResetActiveStage<GameStage>();
		}
		//�N���A
		else if (event->m_MsgStr == L"Result")
		{
			ResetActiveStage<Result>();
		}
		//�Q�[���I�[�o�[
		else if (event->m_MsgStr == L"GameOver")
		{
			ResetActiveStage<GameOver>();
		}

	}

}
//end basecross
