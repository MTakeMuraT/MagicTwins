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
		shared_ptr< StateMachine<Player> >  m_StateMachine;	//ステートマシーン
															//移動の向きを得る
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
		//アクセサ
		shared_ptr< StateMachine<Player> > GetStateMachine() const {
			return m_StateMachine;
		}
		//更新
		virtual void OnUpdate() override;
		//ターンの最終更新時
		virtual void OnLastUpdate() override;
	};
}
//end basecross

