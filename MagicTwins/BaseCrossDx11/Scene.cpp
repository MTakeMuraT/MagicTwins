
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
		//�L�����P���f��
		auto BoneModelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Char1/Character_01Motion03.bmf");
		App::GetApp()->RegisterResource(L"Character01_MESH", BoneModelMesh);

		//�L�����Q���f��
		BoneModelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Char2/Character_02_MotionMotion.bmf");
		App::GetApp()->RegisterResource(L"Character02_MESH", BoneModelMesh);

		//�G���f��
		auto ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Ghost/Ghost.bmf");
		App::GetApp()->RegisterResource(L"Enemy_Model", ModelMesh);


		//���ԃ��f��
		ModelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Windmill/Windmill.bmf");
		App::GetApp()->RegisterResource(L"Windmill_Model", ModelMesh);
		//�⃂�f��
		ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Rock/Rock04.bmf");
		App::GetApp()->RegisterResource(L"Rock_Model", ModelMesh);
		//�򃂃f��
		ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Fence/FENCE.bmf");
		App::GetApp()->RegisterResource(L"Fence_Model", ModelMesh);
		//�X���f��
		ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"IceBlock/IceBlock.bmf");
		App::GetApp()->RegisterResource(L"IceBlock_Model", ModelMesh);

		//���������f��
		ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"MagicBooks/magicbookF00.bmf");
		App::GetApp()->RegisterResource(L"MagicBookFire_Model", ModelMesh);
		ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"MagicBooks/magicbookI00.bmf");
		App::GetApp()->RegisterResource(L"MagicBookIceFog_Model", ModelMesh);
		ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"MagicBooks/magicbookW00.bmf");
		App::GetApp()->RegisterResource(L"MagicBookWind_Model", ModelMesh);
		
		try {
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			//ResetActiveStage<GameStage>();
			ResetActiveStage<Title>();
			//ResetActiveStage<StageSelect>();
			//ResetActiveStage<GameOver>();
			//ResetActiveStage<Result>();

			//BGM
			
			wstring strMusic = App::GetApp()->m_wstrRelativeDataPath + L"bgm/GameStageBGM.wav";
			App::GetApp()->RegisterWav(L"GameStageBGM", strMusic);
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"bgm/TitleBGM.wav";
			App::GetApp()->RegisterWav(L"TitleBGM", strMusic);
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"bgm/ResultBGM.wav";
			App::GetApp()->RegisterWav(L"ResultBGM", strMusic);
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"bgm/GameOverBGM.wav";
			App::GetApp()->RegisterWav(L"GameOverBGM", strMusic);


			//SE
			//�_��
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/Damage.wav";
			App::GetApp()->RegisterWav(L"DamageSE", strMusic);
			//�n�`�_��
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/TerrainDamage.wav";
			App::GetApp()->RegisterWav(L"TerrainDamageSE", strMusic);
			//���鉹
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/Freeze.wav";
			App::GetApp()->RegisterWav(L"FreezeSE", strMusic);
			//�^�C�g���̑I����
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/Key1.wav";
			App::GetApp()->RegisterWav(L"SelectTitleSE", strMusic);
			//�I����
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/Key2.wav";
			App::GetApp()->RegisterWav(L"SelectSE", strMusic);
			//������鉹
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/Water.wav";
			App::GetApp()->RegisterWav(L"WaterSE", strMusic);
			//���@����
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/Fire.wav";
			App::GetApp()->RegisterWav(L"FireSE", strMusic);
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/Ice.wav";
			App::GetApp()->RegisterWav(L"IceSE", strMusic);
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/Wind.wav";
			App::GetApp()->RegisterWav(L"WindSE", strMusic);
			//�����炤��
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/FireDamage.wav";
			App::GetApp()->RegisterWav(L"FireDamageSE", strMusic);
			//�������擾��
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/MagicGet.wav";
			App::GetApp()->RegisterWav(L"MagicGetSE", strMusic);
			//�X�R�A�A�C�e���擾��
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/ItemGet.wav";
			App::GetApp()->RegisterWav(L"ScoreItemGetSE", strMusic);
			//���Ԃ������傢�Ԙg��
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/Alert.wav";
			App::GetApp()->RegisterWav(L"TimeAlertSE", strMusic);

			
			//�I�[�f�B�I�̏�����
			m_AudioTitle = ObjectFactory::Create<MultiAudioObject>();
			m_AudioTitle->AddAudioResource(L"TitleBGM");
			m_AudioTitle->Start(L"TitleBGM",0.6f);
			m_NowBGM = "Title";

			m_AudioGame = ObjectFactory::Create<MultiAudioObject>();
			m_AudioGame->AddAudioResource(L"GameStageBGM");

			m_AudioResult = ObjectFactory::Create<MultiAudioObject>();
			m_AudioResult->AddAudioResource(L"ResultBGM");

			m_AudioGameOver = ObjectFactory::Create<MultiAudioObject>();
			m_AudioGameOver->AddAudioResource(L"GameOverBGM");

		}
		catch (...) {
			throw;
		}
	}

	void Scene::StopBGM()
	{
		m_AudioGame->Stop(L"GameStageBGM");
		m_AudioResult->Stop(L"ResultBGM");
		m_AudioGameOver->Stop(L"GameOverBGM");
		m_AudioTitle->Stop(L"TitleBGM");
		m_NowBGM = "None";
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		//�^�C�g��
		if (event->m_MsgStr == L"Title")
		{
			//���S��~
			StopBGM();
			//�Đ�
			m_AudioTitle->Start(L"TitleBGM",XAUDIO2_LOOP_INFINITE,0.6f);
			m_NowBGM = "Title";
			ResetActiveStage<Title>();
		}
		//�X�e�[�W�Z���N�g
		else if (event->m_MsgStr == L"StageSelect")
		{
			//���S��~
			if (m_NowBGM != "Title")
			{
				StopBGM();
				m_AudioTitle->Start(L"TitleBGM", XAUDIO2_LOOP_INFINITE, 0.6f);
				//�Ȃ��Ă鉹�X�V
				m_NowBGM = "Title";
			}
			ResetActiveStage<StageSelect>();
		}
		//�Q�[����
		else if (event->m_MsgStr == L"GameStage")
		{
			//�S�[���t���O���Z�b�g
			m_GoalFlg = false;
			//���S��~
			StopBGM();
			//�Đ�
			m_AudioGame->Start(L"GameStageBGM", XAUDIO2_LOOP_INFINITE, 0.7f);
			//�Ȃ��Ă鉹�X�V
			m_NowBGM = "GameStage";
			ResetActiveStage<GameStage>();
		}
		//�N���A
		else if (event->m_MsgStr == L"Result")
		{
			//���S��~
			StopBGM();
			//�Đ�
			m_AudioResult->Start(L"ResultBGM", XAUDIO2_LOOP_INFINITE, 0.5f);
			//�Ȃ��Ă鉹�X�V
			m_NowBGM = "Result";
			ResetActiveStage<Result>();

		}
		//�Q�[���I�[�o�[
		else if (event->m_MsgStr == L"GameOver")
		{
			//���S��~
			StopBGM();
			//�Đ�
			m_AudioGameOver->Start(L"GameOverBGM", XAUDIO2_LOOP_INFINITE, 0.7f);
			//�Ȃ��Ă鉹�X�V
			m_NowBGM = "GameOver";
			ResetActiveStage<GameOver>();
		}
		//�`���[�g���A��
		else if (event->m_MsgStr == L"Tutorial")
		{
			//���S��~
			StopBGM();
			//�`���[�g���A���Ɉړ�
			ResetActiveStage<Tutorial>();
		}
	}

	void Scene::ClearBGM()
	{
		if (!m_GoalFlg)
		{
			StopBGM();
			m_AudioResult->Start(L"ResultBGM", XAUDIO2_LOOP_INFINITE, 0.7f);
			m_GoalFlg = true;
		}
	}

}
//end basecross
