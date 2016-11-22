
#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class CollisionManager : public GameObject;
	//	用途: あたり判定まとめて処理
	//--------------------------------------------------------------------------------------
	class CollisionManager : public GameObject
	{
	private :
		//プレイヤー１
		Vector3 PlayerPos1;
		Vector3 PlayerScale1;
		//プレイヤー２
		Vector3 PlayerPos2;
		Vector3 PlayerScale2;
		//ゴール
		Vector3 GoalPos;
		Vector3 GoalScale;
		//魔導書
		vector<Vector3> MagicBooksPos;
		vector<Vector3> MagicBooksScale;
		//魔法1
		Vector3 MagicPos1;
		Vector3 MagicScale1;
		bool MagicFlg1;
		//魔法2
		Vector3 MagicPos2;
		Vector3 MagicScale2;
		bool MagicFlg2;


		//スコアアイテム取得数
		unsigned int m_scoreItemCount = 0;
	public :
		CollisionManager(const shared_ptr<Stage>& StagePtr);
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//プレイヤーの座標持ってくる
		void GetPlayer();
		//ゴールの座標持ってくる
		void GetGoal();
		//魔導書の情報持ってくる
		void GetMagicBook();
		//魔法の情報持ってくる
		void GetMagicBoal();

		//プレイヤーとゴールの当たった処理
		void PlayerToGoal();
		//プレイヤーと魔導書の当たった処理
		void PlayerToMagicBook(int count);
		//プレイヤーとエネミーが当たった処理
		void PlayerToEnemy(int Playernum);
		//魔法とオブジェクトの当たった処理
		void MagicToObj(int num,shared_ptr<GameObject> otherObj);

		//アタリ判定計算関数(球体)
		bool CollisionTest(Vector3 pos1, Vector3 scale1, Vector3 pos2, Vector3 scale2);
	};

}