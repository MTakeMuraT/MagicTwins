/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{



	//--------------------------------------------------------------------------------------
	//	class Player : public GameObject;
	//	用途: プレイヤー
	//--------------------------------------------------------------------------------------
	class Player : public GameObject {
		
		Vector3 GetAngle();
		//最高速度
		float m_MaxSpeed;
		//減速率
		float m_Decel;
		//質量
		float m_Mass;
	public:
		//構築と破棄
		Player(const shared_ptr<Stage>& StagePtr);
		virtual ~Player() {}
		//初期化
		virtual void OnCreate() override;
		
		
		//移動して向きを移動方向にする
		void MoveRotationMotion();
		

		//更新
		virtual void OnUpdate() override;
		//void OnCollision(const shared_ptr<GameObject>& other);
		//ターンの最終更新時
		virtual void OnLastUpdate() override;


	};

	

}
//end basecross

