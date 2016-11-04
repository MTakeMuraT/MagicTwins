
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
		//���f���ǂݍ��݁B�Ȃ񂩃Q�[���X�e�[�W�ł������~�X������K�X
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		auto ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Char1/Character_01.bmf");
		App::GetApp()->RegisterResource(L"Player1_Model", ModelMesh);
		ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Char2/Character_02.bmf");
		App::GetApp()->RegisterResource(L"Player2_Model", ModelMesh);
		ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Windmill/Windmill.bmf");
		App::GetApp()->RegisterResource(L"Windmill_Model", ModelMesh);
		ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"MagicBook/magicbook2.bmf");
		App::GetApp()->RegisterResource(L"MagicBook_Model", ModelMesh);

		//��
		/*
		wstring BGMWav = App::GetApp()->m_wstrRelativeDataPath + L"bgm/gamebgm.wav";
		App::GetApp()->RegisterWav(L"GAMEBGM", BGMWav);
		BGMWav = App::GetApp()->m_wstrRelativeDataPath + L"bgm/titlebgm.wav";
		App::GetApp()->RegisterWav(L"TITLEBGM", BGMWav);
		*/
		try {
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			//ResetActiveStage<GameStage>();
			ResetActiveStage<Title>();
			//ResetActiveStage<StageSelect>();
			//ResetActiveStage<GameOver>();
			//ResetActiveStage<Result>();

			//�ȍĐ�
			/*
			m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
			m_AudioObjectPtr->AddAudioResource(L"TITLEBGM");
			m_AudioObjectPtr->Start(L"TITLEBGM", XAUDIO2_LOOP_INFINITE, 1.0f);
			*/
		}
		catch (...) {
			throw;
		}

		/*
		//�I�[�f�B�I�̏�����
		//��
		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		m_AudioObjectPtr->AddAudioResource(L"TITLEBGM");
		m_AudioObjectPtr->Start(L"TITLEBGM", XAUDIO2_LOOP_INFINITE, 1.0f);
		*/
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
