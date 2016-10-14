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
	private :
		//速度
		float m_Speed = 5.0f;
		//初期座標
		Vector3 m_InitPos;
		//自分の名前
		string m_myName = "Player1";

		//ちょっと肩ボタンいかれてるから調整
		bool m_endFrame = false;

		//操作できるかどうか
		bool m_ActiveFlg = true;
		//状態関数
		void active();
		//キャラ切り替え関数
		void ChangeChar();
	public:
		//構築と破棄
		//引数(初期座標、操作できるか、プレイヤーの名前(Player1かPlayer2))
		Player(const shared_ptr<Stage>& StagePtr,Vector3 pos,bool Active,string Name);
		virtual ~Player() {}
		//初期化
		virtual void OnCreate() override;

		//更新
		virtual void OnUpdate() override;

		//ターンの最終更新時
		virtual void OnLastUpdate() override;

		//操作できるかをセットする関数
		void SetActive(bool);

	};

	

}
//end basecross

