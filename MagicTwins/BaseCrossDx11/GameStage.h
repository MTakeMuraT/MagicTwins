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
		/*
		//ステージ構築関連-----------------
		//ボックス
		void CreateBox(vector<Vector3> pos, vector<Vector3> scale, vector<Vector3> rot);
		//ゴール作成
		void CreateGoal(Vector3 pos, Vector3 scale);
		//プレイヤーの作成
		void CreatePlayer(Vector3 pos);
		//プレイヤーの作成２体目
		void CreatePlayer2(Vector3 pos);

		//魔導書作成自動でMagicTypeの順に生成
		//void CreateMagicBook(vector<Vector3> pos);

		//しようと思ったけど時間かかるからパス
		void CreateMagicFire(Vector3 pos);
		void CreateMagicIceFog(Vector3 pos);

		//ギミック類
		//氷(ギミック１)
		void CreateIce(vector<Vector3> pos, vector<Vector3> scale);
		//炎(ギミック５)
		void CreateFire(vector<Vector3> pos, vector<Vector3> scale);
		//風車(ギミック２)
		void CreateWindMill(vector<Vector3> pos, vector<Vector3> scale);
		//川
		void CreateWaters(vector<Vector3> pos, vector<Vector3> scale, vector<int> num);
		//川のコア(ギミック３)
		void CreateWaterCore(vector<Vector3> pos, vector<Vector3> scale);
		*/
		//ギミック類
		//ステージ構築関連-----------------
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

