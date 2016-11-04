
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

		//曲
		/*
		wstring BGMWav = App::GetApp()->m_wstrRelativeDataPath + L"bgm/gamebgm.wav";
		App::GetApp()->RegisterWav(L"GAMEBGM", BGMWav);
		BGMWav = App::GetApp()->m_wstrRelativeDataPath + L"bgm/titlebgm.wav";
		App::GetApp()->RegisterWav(L"TITLEBGM", BGMWav);
		*/
		try {
			//最初のアクティブステージの設定
			//ResetActiveStage<GameStage>();
			ResetActiveStage<Title>();
			//ResetActiveStage<StageSelect>();
			//ResetActiveStage<GameOver>();
			//ResetActiveStage<Result>();

			//曲再生
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
		//オーディオの初期化
		//曲
		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		m_AudioObjectPtr->AddAudioResource(L"TITLEBGM");
		m_AudioObjectPtr->Start(L"TITLEBGM", XAUDIO2_LOOP_INFINITE, 1.0f);
		*/
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		//タイトル
		if (event->m_MsgStr == L"Title")
		{
			ResetActiveStage<Title>();
		}
		//ステージセレクト
		else if (event->m_MsgStr == L"StageSelect")
		{
			ResetActiveStage<StageSelect>();
		}
		//ゲーム中
		else if (event->m_MsgStr == L"GameStage")
		{
			ResetActiveStage<GameStage>();
		}
		//クリア
		else if (event->m_MsgStr == L"Result")
		{
			ResetActiveStage<Result>();
		}
		//ゲームオーバー
		else if (event->m_MsgStr == L"GameOver")
		{
			ResetActiveStage<GameOver>();
		}

	}

}
//end basecross
