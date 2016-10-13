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
		//速度
		float m_Speed;
	public:
		//構築と破棄
		Player(const shared_ptr<Stage>& StagePtr);
		virtual ~Player() {}
		//初期化
		virtual void OnCreate() override;

		//更新
		virtual void OnUpdate() override;

		//ターンの最終更新時
		virtual void OnLastUpdate() override;


	};

	

}
//end basecross

