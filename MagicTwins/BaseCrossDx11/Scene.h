/*!
@file Scene.h
@brief シーン
*/
#pragma once

#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase
	{
	private:
		//クリアタイム
		unsigned int m_clearTime = 0;
		//スコアアイテム取得数
		unsigned int m_ScoreItemCount = 0;
		//曲
		shared_ptr<MultiAudioObject> m_AudioTitle;
		//ステージ
		shared_ptr<MultiAudioObject> m_AudioGame;
		//リザルト
		shared_ptr<MultiAudioObject> m_AudioResult;
		//ゲームオーバー
		shared_ptr<MultiAudioObject> m_AudioGameOver;


		//めんどいから直打ちで魔法の種類作る
		const int m_MagicTypeLength = 2;

		//ステージの番号
		unsigned int m_stageNum = 0;

		//音全停止
		void StopBGM();

		//ゴールしたフラグ
		bool m_GoalFlg = false;

		//なってるBGM
		string m_NowBGM;
	public:
		Scene() :SceneBase(){}
		virtual ~Scene(){}
		virtual void OnCreate() override;
		virtual void OnEvent(const shared_ptr<Event>& event) override;

		//ステージ番号セット
		void SetStageNum(int num) { m_stageNum = num; }
		//ステージ番号取得
		unsigned int GetStageNum() { return m_stageNum; }

		//たぶんクリアとスコア使ってない
		//クリアタイムをセット
		void SetClearTime(unsigned int num) { m_clearTime = num; }
		//クリアタイム取得
		unsigned int GetClearTime() { return m_clearTime; }

		//スコアアイテム取得数をセット
		void SetScoreItemCount(unsigned int num) { m_ScoreItemCount = num; }
		//スコアアイテム取得
		unsigned int GetScoreItemCount() { return m_ScoreItemCount; }

		//クリアしたときのBGM処理
		void ClearBGM();
	};

}

//end basecross
