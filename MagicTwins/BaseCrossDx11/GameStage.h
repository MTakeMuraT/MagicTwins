/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//リソースの作成
		void CreateResourses();
		//ビューの作成
		void CreateViewLight();
		//プレートの作成
		void CreatePlate();
		//制限時間作成
		void CreateLimitTime();
		//コリジョンマネージャー作成
		void CreateCollisionManager();
		//アイコン作成
		void CreateIcons();

		//ポーズメニュー作成
		void CreatePauseMenu();

		//クリアしたかどうか
		bool m_GoalFlg = false;

		//ゴールした後の処理
		void GoalState();
		//状態
		int m_GoalState = 0;

		//ゴールしたことを判定するオブジェクト
		shared_ptr<GameObject> m_GoalObj;

		//文字表示オブジェクト
		shared_ptr<GameObject> m_StringObj;

		//ゴール後リザルト演出
		//1 リザルトロゴ
		shared_ptr<GameObject> m_GoalLogo;
		//2 本のテクスチャ
		shared_ptr<GameObject> m_Book;
		//3 タイムのロゴ
		shared_ptr<GameObject> m_TimeLogo;
		//透明度
		float m_alpha = 0;
		//4 残りタイム計算用
		float m_RemainingTime = 0;
		//増加量
		float m_AmountTime = 0;
		//残った時間
		int m_LimitTimeGoal = 0;
		//最大時間
		int m_LimitTimeMax = 0;
		//5 スコアアイテムのロゴ
		shared_ptr<GameObject> m_ScoreItemLogo;
		//6 スコアアイテム取得数計算用
		float m_ScoreItemCountCal = 0;
		//スコアアイテム取得数
		int m_ScoreItemCount = 0;
		//増加量
		float m_AmountScoreCount = 0;
		//7 ランクロゴ
		shared_ptr<GameObject> m_RankLogo;
		//8 ランク
		shared_ptr<GameObject> m_RankSprite;
		//9 キャラ画像
		shared_ptr<GameObject> m_Char1Sprite;
		shared_ptr<GameObject> m_Char2Sprite;
		//10項目
		shared_ptr<GameObject> m_NextStageLogo;
		shared_ptr<GameObject> m_StageSelectLogo;
		shared_ptr<GameObject> m_TitleLogo;
		//11 選択大きさ
		Vector3 m_SelectScale = Vector3(500, 500, 1);
		Vector3 m_NotSelectScale = Vector3(400, 400, 1);
		//選択番号 0:次 1:ステセレ 2:タイトル
		int m_SelectNum = 0;
		//移動フラグ
		bool m_MoveConFlg = false;

	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
	};


}
//end basecross

