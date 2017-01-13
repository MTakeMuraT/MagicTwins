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
		//撮影モード
		bool m_CameraMode = true;

		//速度
		float m_Speed = 3.0f;
		//体力
		int m_life = 3;
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
		//カメラ追従処理
		void CameraTarget();
		//カメラの座標
		Vector3 m_CameraPos;
		//カメラの向いてる方向
		Vector3 m_CameraTargetVec;
		//カメラ移動始める範囲
		const float m_CameraMove = 3.0f;

		//無敵時間
		const float m_InvincibleTime = 2.0f;
		//無敵時間計算用
		float m_InvTime = 0;
		//無敵フラグ
		bool m_InviFlg = false;

		//無敵点滅時間
		float m_Flashingtime = 0;
		//透明 感覚
		const float m_FlashingTimeInterval = 0.1f;
		//透明調整
		bool m_FlashingFlg = false;



		//無敵時間中の関数
		void Invincible();

		//瞬間移動できなくなる対処
		bool m_WarpFlg = false;
		//体力表示
		shared_ptr<GameObject> m_LifeSprite;

		//速度
		Vector2 m_velocity;

		//魔法打つ関数
		void ShotMagic();

		//魔法のリスト
		//*********************************//
		//MagicTypeはenum型、stdafx.hに書いてある
		//Fire:炎の玉
		//IceFog:氷の霧
		//*********************************//
		MagicType m_Magic = None;

		//魔法UI
		shared_ptr<GameObject> m_MagicUI;
		//中身UI
		shared_ptr<GameObject> m_MagicUIIn;

		//キャラUI
		shared_ptr<GameObject> m_CharaUI;
		 
		//暗転用幕
		shared_ptr<GameObject> m_Black;

		//キャラ暗転切り替え用
		//そもそも暗転するかどうか
		bool m_BlackFlg = false;
		//今出てる状態か消えてる状態か
		bool m_BlackFlg2 = false;
		float m_BlackAlpha = 0;

		//死んだフラグ
		bool m_DieFlg = false;
		//暗転用幕
		shared_ptr<Black> m_BlackDie;

		//魔法打つ時に移動できなくするフラグ
		bool m_ShotMagicStopFlg = false;
		//魔法打った時の硬直時間
		const float m_ShotStopTime = 1.0f;
		//魔法打った後のカウント用時間
		float m_ShotMagicCountTime = 0;
		//魔法打ったフラグ
		bool m_ShotMagicFlg = false;
		//ターゲットモードフラグ
		bool m_TargetModeFlg = false;
		//ターゲット枠
		shared_ptr<GameObject> m_TargetModeFrame;
		//ターゲットモード中
		void TargetMode();
		//ターゲットモード解除
		void TargetModeRelease();
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

		bool GetActive() { return m_ActiveFlg; };

		//魔法を覚える関数
		void SetMagic(MagicType);

		//カメラ固定？
		void SetCamera(Vector3 At,Vector3 pos);

		//ダメージ処理
		void PlayerDamege();

		//地形ダメージ
		void PlayerTerrainDamege();

		//ライフ表示
		void DispUI() { m_LifeSprite->SetDrawActive(true); m_CharaUI->SetDrawActive(true); }

		//カメラモードかどうか
		bool GetCameraModeFlg() { return m_CameraMode; }

		//ターゲットモード中か
		bool GetTargeModeFlg() { return m_TargetModeFlg; }
	};

	//--------------------------------------------------------------------------------------
	//	class MagicBoal : public GameObject;
	//	用途: 魔法
	//--------------------------------------------------------------------------------------
	class MagicBoal : public GameObject
	{
	private :
		//移動量
		Vector2 m_velocity;
		//座標
		Vector3 m_pos;
		//大きさ
		Vector3 m_magicSize = Vector3(0.25f, 0.25f, 0.25f);

		//生きてるかどうか
		bool m_ActiveFlg = false;
		//速度
		float m_speed = 5.0f;
		//自分の番号
		int m_mynumber;
		//生存時間
		float m_lifeTime;
		const float m_LifeTimeLimit = 1.0f;
		const float m_shortLimitTime = 0.2f;

		//消滅フラグ
		bool m_DeleteFlg = false;
		//自分の属性
		MagicType m_MagicType = None;

		//なんかしらんメッシュのリスト
		vector<shared_ptr<MeshResource>> m_Mesh;

		//今の連番の番号
		unsigned int m_MeshNumber = 0;
		//画像切り替えるタイミング計算用
		float m_CountTime = 0;
		const float m_ConstCountTime = 0.3f;
	public :
		MagicBoal(const shared_ptr<Stage>& StagePtr, Vector3 pos,int m);
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//発射する
		void SetActive(bool,MagicType);

		//移動量算出
		void SetVelo();

		//属性持ってくる
		MagicType GetMagicType();

		//生存情報持ってくる
		bool GetActive();
	};

}
//end basecross

