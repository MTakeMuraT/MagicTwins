/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	//	class Goal : public GameObject;
	//	用途: ゴール
	//--------------------------------------------------------------------------------------
	class Goal : public GameObject
	{
	private :
		Vector3 m_InitPos;
		Vector3 m_Scale;
	public :
		Goal(const shared_ptr<Stage>& StagePtr,Vector3 pos, Vector3 scale);
		void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	//	class Box : public GameObject;
	//	用途: 箱
	//--------------------------------------------------------------------------------------
	class Box : public GameObject
	{
	private:
		Vector3 m_InitPos;
		Vector3 m_InitScale;
		Vector3 m_InitRot;
	public:
		Box(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale,Vector3 rot);
		void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	//	class Rock : public GameObject;
	//用途：岩
	//--------------------------------------------------------------------------------------
	class Rock :public GameObject
	{
		//初期位置
		Vector3 m_InitPos;
		//大きさ
		Vector3 m_Scale;
	public:
		Rock(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale);
		void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	//	class Enemy : public GameObject;
	//	用途: 敵
	//--------------------------------------------------------------------------------------
	class Enemy : public GameObject
	{
		//初期位置
		Vector3 m_InitPos;
		Vector3 m_Scale;
		//速度
		float m_speed = 2.0f;

		//停止状態
		bool m_StopFlg = false;
		//停止時間
		const float m_StopTime = 3.0f;
		//計算用
		float m_time = 0;
	public :
		Enemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale);
		void OnCreate() override;
		void OnUpdate() override;
		void StopEnemy();
		void ResetPos();
	};
	
	//--------------------------------------------------------------------------------------
	//	class Black : public GameObject;
	//	用途: 暗転用黒背景
	//--------------------------------------------------------------------------------------
	class Black : public GameObject
	{
	private :
		float m_alpha = 0;
		bool m_StartFlg = false;
		bool m_EndFlg = false;
	public :
		Black(const shared_ptr<Stage>& StagePtr);
		void OnCreate() override;
		void OnUpdate() override;

		//暗転起動
		void StartBlack();

		//暗転したかどうか取得
		bool GetBlackFinish();
	};

	//--------------------------------------------------------------------------------------
	//	class MagicBook : public GameObject;
	//	用途: 魔導書
	//--------------------------------------------------------------------------------------
	class MagicBook : public GameObject
	{
	private :
		MagicType m_MagicContent = None;
		Vector3 m_InitPos;
		//スポーン時間
		bool m_ActiveFlg = true;
		//経過時間
		float m_ElaTime=0;
		//再出現時間
		const float m_LimitTime = 3.0f;
	public :
		MagicBook(const shared_ptr<Stage>& StagePtr, Vector3 initPos,MagicType Magic);
		void OnCreate();
		void OnUpdate();
		//拾った
		void GetPlayer();


		//アクセサー
		Vector3 GetPos();
		Vector3 GetScale();
	};

	//--------------------------------------------------------------------------------------
	//	class LimitTime : public GameObject;
	//	用途: 制限時間
	//--------------------------------------------------------------------------------------
	class LimitTime : public GameObject
	{
	private :
		//カウント時間
		float m_nowTime=0;
		//リミット時間引数で初期値決める
		float m_LimitTime = 60.0f;
	public :
		LimitTime(const shared_ptr<Stage>& StagePtr,float LimitTime);
		void OnCreate() override;
		void OnUpdate() override;

		void TimeOver();

		int GetClearTime() { return (int)(m_LimitTime - m_nowTime); }
	};

	//--------------------------------------------------------------------------------------
	//	class NumberSprite : public GameObject;
	//	用途: 数字のスプライト
	//--------------------------------------------------------------------------------------
	class NumberSprite : public GameObject
	{
	private:
		//なんかしらんメッシュのリスト
		vector<shared_ptr<MeshResource>> m_Mesh;
		unsigned int m_num = 0;
		//大きさ
		Vector2 m_scale;
		//位置
		Vector2 m_pos;
	public :
		NumberSprite(const shared_ptr<Stage>& StagePtr, int num,Vector2 pos,Vector2 scale);
		
		void OnCreate()override;

		void SetNum(int num);
	};
	//--------------------------------------------------------------------------------------
	//	class MenuIcon : public GameObject;
	//	用途: メニューボタンのアイコン
	//--------------------------------------------------------------------------------------
	class MenuIcon : public GameObject
	{
	private :
	public :
		MenuIcon(const shared_ptr<Stage>& StagePtr);
		void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	//	class NumberSprite : public GameObject;
	//	用途: 数字
	//--------------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------------
	//	class PauseMenu : public GameObject;
	//	用途: ポーズメニュー
	//--------------------------------------------------------------------------------------
	class PauseMenu : public GameObject
	{
	private:
		shared_ptr<GameObject> m_ReTryLogo;
		shared_ptr<GameObject> m_mapLogo;
		shared_ptr<GameObject> m_StageSelectLogo;
		shared_ptr<GameObject> m_TitleLogo;
		shared_ptr<GameObject> m_Black;

		shared_ptr<GameObject> m_Map;

		//起動してるかどうか
		bool m_ActivePauseFlg = false;
		//暗転してるかどうか
		bool m_BlackOutFlg = false;
		//マップ選んでるか
		bool m_selectMapFlg = false;

		//現在何選んでるかの数字
		//0:retry1:map2:stageselect3:title
		int m_selectnum = 0;

		//操作フラグ
		bool m_moveFlg = false;

		//選択時X
		const float m_SelectX = -750;
		//非選択時X
		const float m_NotSelectX = -850;

		//暗転の透明度
		float m_BlackAlpha = 0;
	public :
		PauseMenu(const shared_ptr<Stage>& StagePtr);

		void OnCreate();

		void OnUpdate();

		//ゲームステージで呼ぶと、ポーズ状態に。ポーズ中に読んだら解除する。
		void Pause();

		//ポーズしてるかどうか
		bool GetPause() { return m_ActivePauseFlg; };

		//暗転してるかどうか
		bool GetBlackOut() { return m_BlackOutFlg; };

		//暗転関数
		void BlackOut();
	};
	//--------------------------------------------------------------------------------------
	//	class Gimmick1 : public GameObject;
	//	用途: 氷。炎の魔法[Fire]で溶かせる
	//--------------------------------------------------------------------------------------
	class Gimmick1 : public GameObject
	{
	private :
		//初期位置
		Vector3 m_InitPos;
		//大きさ
		Vector3 m_Scale;
		//生きてるかどうか
		bool m_ActiveFlg = false;
	public :
		Gimmick1(const shared_ptr<Stage>& StagePtr,Vector3 pos,Vector3 scale);
		void OnCreate() override;

		void Delete(MagicType MT);
	};

	//--------------------------------------------------------------------------------------
	//	class Gimmick2 : public GameObject;
	//	用途: 風車。炎の魔法[Fire]で燃える　燭台と組み合わせれば羽動かして水門開けたりしめたりできる
	//--------------------------------------------------------------------------------------
	class Gimmick2 : public GameObject
	{
	private:
		//初期位置
		Vector3 m_InitPos;
		//大きさ
		Vector3 m_Scale;
		//生きてるかどうか
		bool m_ActiveFlg = false;
	public:
		Gimmick2(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale);
		void OnCreate() override;

		void Delete(MagicType MT);
	};


	//--------------------------------------------------------------------------------------
	//	class Water : public GameObject;
	//	用途: 水。コア部分以外
	//--------------------------------------------------------------------------------------
	class Water : public GameObject
	{
	private:
		//初期位置
		Vector3 m_InitPos;
		//大きさ
		Vector3 m_InitScale;
		//凍ってるかどうか
		bool m_FreezeFlg = false;
		//流れてるかどうか
		bool m_FlowFlg = true;
		//背番号
		int m_myNum;
		//見た目の部分
		shared_ptr<GameObject> m_waterunder;
	public :
		Water(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale,int num);
		void OnCreate() override;

		//番号取得
		int GetmyNum() { return m_myNum; }

		//凍らす
		void Freeze();
		//溶かす
		void Melt();
		//止める
		void Stop();
		//流す
		void Flow();

	};

	//--------------------------------------------------------------------------------------
	//	class Gimmick3 : public GameObject;
	//	用途: 川。のコア部分。凍らせると水部分を凍らせる
	//	本体は水の上の透明な部分で下の水は見た目だけ
	//--------------------------------------------------------------------------------------
	class Gimmick3 : public GameObject
	{
	private:
		//初期位置
		Vector3 m_InitPos;
		//大きさ
		Vector3 m_InitScale;
		//凍ってるかどうか
		bool m_FreezeFlg = false;
		//流れてるかどうか
		bool m_FlowFlg = true;
		//自分が影響を与える水の情報
		vector<shared_ptr<Water>> m_waters;
		//見た目の部分
		shared_ptr<GameObject> m_waterunder;
	public:
		Gimmick3(const shared_ptr<Stage>& StagePtr, Vector3 pos,Vector3 scale);
		void OnCreate() override;

		//魔法が当たった時
		void HitMagic(MagicType MT);
		//凍らす
		void Freeze();
		//溶かす
		void Melt();
		//止める
		void Stop();
		//流す
		void Flow();

		void SetWaters(vector<shared_ptr<Water>> waters) { m_waters = waters; }
	};

	//--------------------------------------------------------------------------------------
	//	class Gimmick5 : public GameObject;
	//	用途: 炎。氷の魔法[Icefog]で消せる
	//--------------------------------------------------------------------------------------
	class Gimmick5 : public GameObject
	{
	private:
		//初期位置
		Vector3 m_InitPos;
		//大きさ
		Vector3 m_Scale;
		//生きてるかどうか
		bool m_ActiveFlg = false;
	public:
		Gimmick5(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale);
		void OnCreate() override;

		void Delete(MagicType MT);
	};

}
//end basecross
