
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
		//キャラ１モデル
		auto ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Char1/Character_01.bmf");
		App::GetApp()->RegisterResource(L"Player1_Model", ModelMesh);
		//キャラ２モデル
		ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Char2/Character_02.bmf");
		App::GetApp()->RegisterResource(L"Player2_Model", ModelMesh);
		//風車モデル
		ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Windmill/Windmill.bmf");
		App::GetApp()->RegisterResource(L"Windmill_Model", ModelMesh);
		//岩モデル
		ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Rock/Rock04.bmf");
		App::GetApp()->RegisterResource(L"Rock_Model", ModelMesh);
		//柵モデル
		ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Fence/FENCE.bmf");
		App::GetApp()->RegisterResource(L"Fence_Model", ModelMesh);

		
		//魔導書モデル
		ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"MagicBooks/magicbookF00.bmf");
		App::GetApp()->RegisterResource(L"MagicBookFire_Model", ModelMesh);
		ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"MagicBooks/magicbookI00.bmf");
		App::GetApp()->RegisterResource(L"MagicBookIceFog_Model", ModelMesh);
		ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"MagicBooks/magicbookW00.bmf");
		App::GetApp()->RegisterResource(L"MagicBookWind_Model", ModelMesh);
		
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
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"bgm/ResultBGM.wav";
			App::GetApp()->RegisterWav(L"ResultBGM", strMusic);
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"bgm/GameOverBGM.wav";
			App::GetApp()->RegisterWav(L"GameOverBGM", strMusic);


			//SE
			//ダメ
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/Damage.wav";
			App::GetApp()->RegisterWav(L"DamageSE", strMusic);
			//地形ダメ
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/TerrainDamage.wav";
			App::GetApp()->RegisterWav(L"TerrainDamageSE", strMusic);
			//凍る音
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/Freeze.wav";
			App::GetApp()->RegisterWav(L"FreezeSE", strMusic);
			//タイトルの選択音
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/Key1.wav";
			App::GetApp()->RegisterWav(L"SelectTitleSE", strMusic);
			//選択音
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/Key2.wav";
			App::GetApp()->RegisterWav(L"SelectSE", strMusic);
			//水流れる音
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/Water.wav";
			App::GetApp()->RegisterWav(L"WaterSE", strMusic);
			//魔法撃つ音
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/Fire.wav";
			App::GetApp()->RegisterWav(L"FireSE", strMusic);
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/Ice.wav";
			App::GetApp()->RegisterWav(L"IceSE", strMusic);
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/Wind.wav";
			App::GetApp()->RegisterWav(L"WindSE", strMusic);
			//炎くらう音
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/FireDamage.wav";
			App::GetApp()->RegisterWav(L"FireDamageSE", strMusic);
			//魔導書取得音
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/MagicGet.wav";
			App::GetApp()->RegisterWav(L"MagicGetSE", strMusic);
			//スコアアイテム取得音
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/ItemGet.wav";
			App::GetApp()->RegisterWav(L"ScoreItemGetSE", strMusic);

			//オーディオの初期化
			m_AudioTitle = ObjectFactory::Create<MultiAudioObject>();
			m_AudioTitle->AddAudioResource(L"TitleBGM");
			m_AudioTitle->Start(L"TitleBGM");

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
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		//タイトル
		if (event->m_MsgStr == L"Title")
		{
			//音全停止
			StopBGM();
			//再生
			m_AudioTitle->Start(L"TitleBGM",XAUDIO2_LOOP_INFINITE,0.5f);
			ResetActiveStage<Title>();
		}
		//ステージセレクト
		else if (event->m_MsgStr == L"StageSelect")
		{
			//音全停止
			StopBGM();
			ResetActiveStage<StageSelect>();
		}
		//ゲーム中
		else if (event->m_MsgStr == L"GameStage")
		{
			//音全停止
			StopBGM();
			//再生
			m_AudioGame->Start(L"GameStageBGM", XAUDIO2_LOOP_INFINITE, 0.7f);
			ResetActiveStage<GameStage>();
		}
		//クリア
		else if (event->m_MsgStr == L"Result")
		{
			//音全停止
			StopBGM();
			//再生
			m_AudioResult->Start(L"ResultBGM", XAUDIO2_LOOP_INFINITE, 0.7f);
			ResetActiveStage<Result>();

		}
		//ゲームオーバー
		else if (event->m_MsgStr == L"GameOver")
		{
			//音全停止
			StopBGM();
			//再生
			m_AudioGameOver->Start(L"GameOverBGM", XAUDIO2_LOOP_INFINITE, 0.7f);
			ResetActiveStage<GameOver>();
		}

	}

}
//end basecross
