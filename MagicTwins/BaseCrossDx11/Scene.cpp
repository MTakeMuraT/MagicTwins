
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
		auto BoneModelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Char1/Character_01Motion03.bmf");
		App::GetApp()->RegisterResource(L"Character01_MESH", BoneModelMesh);

		//キャラ２モデル
		BoneModelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Char2/Character_02_MotionMotion.bmf");
		App::GetApp()->RegisterResource(L"Character02_MESH", BoneModelMesh);

		//敵モデル
		auto ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Ghost/Ghost.bmf");
		App::GetApp()->RegisterResource(L"Enemy_Model", ModelMesh);


		//風車モデル
		ModelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Windmill/Windmill.bmf");
		App::GetApp()->RegisterResource(L"Windmill_Model", ModelMesh);
		//岩モデル
		ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Rock/Rock04.bmf");
		App::GetApp()->RegisterResource(L"Rock_Model", ModelMesh);
		//柵モデル
		ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Fence/FENCE.bmf");
		App::GetApp()->RegisterResource(L"Fence_Model", ModelMesh);
		//氷モデル
		ModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"IceBlock/IceBlock.bmf");
		App::GetApp()->RegisterResource(L"IceBlock_Model", ModelMesh);
		//スコアアイテム
		ModelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Coin/Coin.bmf");
		App::GetApp()->RegisterResource(L"Coin_Model", ModelMesh);


		//魔導書モデル
		ModelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"MagicbookFire/MagicbookFire.bmf");
		App::GetApp()->RegisterResource(L"MagicBookFire_Model", ModelMesh);
		ModelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"MagicbookIce/Magicbook.bmf");
		App::GetApp()->RegisterResource(L"MagicBookIceFog_Model", ModelMesh);
		ModelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"MagicbookWind/MagicbookWind.bmf");
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
			//時間もうちょい赤枠音
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/Alert.wav";
			App::GetApp()->RegisterWav(L"TimeAlertSE", strMusic);
			//エネミースポーン
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/EnemyRespawn.wav";
			App::GetApp()->RegisterWav(L"EnemySpawnSE", strMusic);
			//選択移動音
			strMusic = App::GetApp()->m_wstrRelativeDataPath + L"se/Button3.wav";
			App::GetApp()->RegisterWav(L"SelectMoveSE", strMusic);

			
			//オーディオの初期化
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
		//タイトル
		if (event->m_MsgStr == L"Title")
		{
			//音全停止
			StopBGM();
			//再生
			m_AudioTitle->Start(L"TitleBGM",XAUDIO2_LOOP_INFINITE,0.6f);
			m_NowBGM = "Title";
			ResetActiveStage<Title>();
		}
		//ステージセレクト
		else if (event->m_MsgStr == L"StageSelect")
		{
			//音全停止
			if (m_NowBGM != "Title")
			{
				StopBGM();
				m_AudioTitle->Start(L"TitleBGM", XAUDIO2_LOOP_INFINITE, 0.6f);
				//なってる音更新
				m_NowBGM = "Title";
			}
			ResetActiveStage<StageSelect>();
		}
		//ゲーム中
		else if (event->m_MsgStr == L"GameStage")
		{
			//ゴールフラグリセット
			m_GoalFlg = false;
			//音全停止
			StopBGM();
			//再生
			m_AudioGame->Start(L"GameStageBGM", XAUDIO2_LOOP_INFINITE, 0.7f);
			//なってる音更新
			m_NowBGM = "GameStage";
			ResetActiveStage<GameStage>();
		}
		//クリア
		else if (event->m_MsgStr == L"Result")
		{
			//音全停止
			StopBGM();
			//再生
			m_AudioResult->Start(L"ResultBGM", XAUDIO2_LOOP_INFINITE, 0.5f);
			//なってる音更新
			m_NowBGM = "Result";
			ResetActiveStage<Result>();

		}
		//ゲームオーバー
		else if (event->m_MsgStr == L"GameOver")
		{
			//音全停止
			StopBGM();
			//再生
			m_AudioGameOver->Start(L"GameOverBGM", XAUDIO2_LOOP_INFINITE, 0.7f);
			//なってる音更新
			m_NowBGM = "GameOver";
			ResetActiveStage<GameOver>();
		}
		//チュートリアル
		else if (event->m_MsgStr == L"Tutorial")
		{
			//音全停止
			StopBGM();
			//チュートリアルに移動
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
