
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------

	void Scene::OnCreate(){
		//モデル読み込み。なんかゲームステージでやったらミスった希ガス
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
		ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Rock/Rock04.bmf");
		App::GetApp()->RegisterResource(L"Rock_Model", ModelMesh);
		ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Fence/FENCE.bmf");
		App::GetApp()->RegisterResource(L"Fence_Model", ModelMesh);

		try {
			//最初のアクティブステージの設定
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

			//オーディオの初期化
			m_AudioTitle = ObjectFactory::Create<MultiAudioObject>();
			m_AudioTitle->AddAudioResource(L"TitleBGM");
			m_AudioTitle->Start(L"TitleBGM");

			m_AudioGame = ObjectFactory::Create<MultiAudioObject>();
			m_AudioGame->AddAudioResource(L"GameStageBGM");

		}
		catch (...) {
			throw;
		}
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		//タイトル
		if (event->m_MsgStr == L"Title")
		{
			m_AudioGame->Stop(L"GameStageBGM");
			m_AudioTitle->Start(L"TitleBGM",XAUDIO2_LOOP_INFINITE,0.5f);
			ResetActiveStage<Title>();
		}
		//ステージセレクト
		else if (event->m_MsgStr == L"StageSelect")
		{
			//セレクト画面に入ったらTitleBGMを止める
			m_AudioTitle->Stop(L"TitleBGM");
			ResetActiveStage<StageSelect>();
		}
		//ゲーム中
		else if (event->m_MsgStr == L"GameStage")
		{
			m_AudioGame->Start(L"GameStageBGM", XAUDIO2_LOOP_INFINITE, 0.7f);
			ResetActiveStage<GameStage>();
		}
		//クリア
		else if (event->m_MsgStr == L"Result")
		{
			m_AudioGame->Stop(L"GameStageBGM");
			ResetActiveStage<Result>();

		}
		//ゲームオーバー
		else if (event->m_MsgStr == L"GameOver")
		{
			m_AudioGame->Stop(L"GameStageBGM");
			ResetActiveStage<GameOver>();
		}

	}

}
//end basecross
