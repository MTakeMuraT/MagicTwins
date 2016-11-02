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
		//プレイヤーの作成
		void CreatePlayer();
		//魔導書作成
		void CreateMagicBook();
		//ゴール作成
		void CreateGoal();
		//制限時間作成
		void CreateLimitTime();
		//コリジョンマネージャー作成
		void CreateCollisionManager();
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

