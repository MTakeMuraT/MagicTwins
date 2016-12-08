/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	/*
	//--------------------------------------------------------------------------------------
	//	class MagicParticle : public GameObject;
	//	用途: パーティクル
	//--------------------------------------------------------------------------------------
	class MagicParticle : public GameObject
	{
	private:
		//初期位置
		Vector3 m_InitPos = Vector3(0, 0, 0);
		//大きさ
		Vector3 m_InitScale = Vector3(0, 0, 0);
		//生成されるときの位置の振れ幅
		Vector3 m_RandRange = Vector3(0, 0, 0);
		//移動速度
		vector<Vector3> m_velocity;
		//移動速度ブレ幅
		Vector3 m_randVelocity = Vector3(0, 0, 0);
		//テクスチャの名前
		wstring m_TextureName = L"None";
		//パーティクルフラグ
		bool m_NowParticleFlg = false;
		//合計作成数
		int m_CreateCount = 0;
		//作成間隔
		float m_Interval = 0;
		//一回に出す数
		int m_OnceCreateCount = 0;
		//動いてる時間
		float m_MoveingTime = 0;
		vector<shared_ptr<GameObject>> m_Particle;
		//表示レイヤー
		int m_DispLayer = 0;

		//それぞれのカウント
		vector<float> m_TimeCount;
		//起動するかどうかのフラグ
		vector<bool> m_OnFlg;
	public:
		MagicParticle(const shared_ptr<Stage>& StagePtr);
		void OnCreate()override ;
		//↑二つは使わないかもしれない
		void OnUpdate()override ;

		//(Vec3座標,Vec3大きさ,Vec3位置範囲,Vec3Velocity,Vec3速さの振れ幅stringテクスチャの名前,作成数,作成間隔,一度に作成する数,生存時間,レイヤー)
		void OnParticle(Vector3 pos, Vector3 scale, Vector3 randrange, Vector3 velo, Vector3 randvelo,wstring texturename,
			int createcount,float interval,int oncecreatecount,float moveingtime,int displayer);

		//パーティクル出してるかどうか、これがtrue(出てる)状態なら新しく作るようにしてもらう
		bool GetNowParticle() { return m_NowParticleFlg; }

		void StopParticle();
	};
	*/
	/*
	//--------------------------------------------------------------------------------------
	//	class MPPP : public GameObject;
	//	用途: パーティクル簡易
	//--------------------------------------------------------------------------------------
	class MPPP : public GameObject
	{
	private :
		Vector3 m_InitPos;
		Vector3 m_InitScale;
		string m_txt;
		vector<shared_ptr<GameObject>> m_Particle;
	public :
		MPPP(const shared_ptr<Stage>& StagePtr,Vector3 pos , Vector3 scale,string txt) : GameObject(StagePtr),m_InitPos(pos),m_InitScale(scale),m_txt(txt){};
		void OnCreate()
		{
			for (int i = 0; i < 3; i++)
			{
				auto obj = GetStage()->AddGameObject<GameObject>();
				auto objTrans = obj->AddComponent<Transform>();
				Vector3 pos = m_InitPos;
				//位置ちょっとずらす
				int random = rand() % 100;
				pos.x += random / 100;
				random = rand() % 100;
				pos.y += random / 100;
				random = rand() % 100;
				pos.z += random / 100;
				objTrans->SetPosition(pos);
				objTrans->SetScale(m_InitScale);
				objTrans->SetRotation(0, 0, 0);

				auto objDraw = obj->AddComponent<PNTStaticDraw>();
				objDraw->SetMeshResource(L"DEFAULT_SQUARE");
				objDraw->SetTextureResource(L"FIREEF_TX");
				if (m_txt == "F")
				{
					objDraw->SetTextureResource(L"FIREEF_TX");
				}
				else if (m_txt == "I")
				{
					objDraw->SetTextureResource(L"I_TX");
				}
				else if (m_txt == "W")
				{
					objDraw->SetTextureResource(L"W_TX");
				}


				obj->SetAlphaActive(true);
				obj->SetDrawLayer(5);

				m_Particle.push_back(obj);
			}
			SetAlphaActive(true);
		}

		void OnUpdate()
		{

			for(auto v : m_Particle)
			{
				auto Tra = v->GetComponent<Transform>();
				Vector3 pos = Tra->GetPosition();
				pos.y += (rand()%2) * App::GetApp()->GetElapsedTime();
				Tra->SetPosition(pos);
				if (pos.y > m_InitPos.y + (m_InitScale.y * 3))
				{
					pos.y = m_InitPos.y;
					Tra->SetPosition(pos);
				}
			}
		}
	};
	*/

	//--------------------------------------------------------------------------------------
	//	class MagicParticle : public GameObject;
	//	用途: パーティクル(簡易対応版)
	//--------------------------------------------------------------------------------------
	class MagicParticle : public GameObject
	{
	private :
		//設定用
		//初期位置
		Vector3 m_InitPos;
		//位置ブレ幅
		Vector3 m_RandPos;
		//速度
		Vector3 m_Initvelocity;
		//速度ブレ幅
		Vector3 m_RandVelocity;
		//大きさ
		Vector3 m_Scale;
		//作成する間隔
		float m_CreateInterval;
		//テクスチャの名前
		wstring m_TextureName;
		//消滅演出
		bool m_DeleteFlg = false;
		//現在パーティクルを出しているかどうか
		bool m_NowParticleFlg = false;
		//レイヤー
		int m_Layer;

		//消える時間
		float m_DeleteTime = 1.0f;
		//計算用
		//経過時間
		float m_time = 0;
		//パーティクルデータ
		vector<shared_ptr<GameObject>> m_Particle;
		//速度
		vector<Vector3> m_velocity;
		vector<float> m_alpha;

		//パーティクル生成関数
		void CreateParticle();

		//再利用されるとき設定
		void SetVeloPos(int num);

		//残り消えてるかどうか
		bool m_NokoriFlg = false;
	public :
		MagicParticle(const shared_ptr<Stage>& StagePtr);
		void OnUpdate() override;

		//初期位置、ブレ幅、速度、速度ブレ幅、大きさ、テクスチャの名前、消滅演出(true:薄くなるfalse:小さくなる)、作成間隔、レイヤー、消える時間
		void OnParticle(Vector3 InitPos , Vector3 RandPos , Vector3 Velo, Vector3 RandVelo,Vector3 scale,wstring TextureName,bool DeleteFlg,float CreateInterval,int Layer,float deleteTime);

		//パーティクル停止
		void StopParticle();

		//パーティクル指導
		void StartParticle() { m_NowParticleFlg = true; }
	};
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
	//	class PlaneP : public GameObject;
	//	用途: 地面
	//--------------------------------------------------------------------------------------
	class PlaneP : public GameObject
	{
	private:
		Vector3 m_InitPos;
		Vector3 m_InitScale;
		Vector3 m_InitRot;
	public :
		PlaneP(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, Vector3 rot);
		void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	//	class Fence : public GameObject;
	//	用途: 柵
	//--------------------------------------------------------------------------------------
	class Fence : public GameObject
	{
	private:
		Vector3 m_InitPos;
		Vector3 m_InitScale;
		Vector3 m_InitRot;

		shared_ptr<GameObject> m_FenceObj;
	public :
		Fence(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, Vector3 rot);
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
		float m_speed = 1.5f;
		const float m_InitSpeed = 1.5f;
		//停止状態
		bool m_StopFlg = false;
		//停止時間
		const float m_StopTime = 0.5f;
		//死んでる時間
		const float m_ReSponTime = 10.0f;
		//追うフラグ
		bool m_ChaceFlg = false;
		//追う距離
		const float m_ChaceDir = 3.0f;
		//計算用
		float m_time = 0;
		//体力
		int m_life = 3;
		//初期体力
		const int m_MaxLife = 3;
		//狙ってるプレイヤー
		int m_TargetPlayernum = 0;
		//生きてるか死んでるか
		bool m_ActiveFlg = true;
		//ライフバー
		shared_ptr<GameObject> m_lifeBar;

	public :
		Enemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale,int targetNum);
		void OnCreate() override;
		void OnUpdate() override;
		void StopEnemy(int TargetNum);
		void ResetPos();

		bool GetStopFlg() { return m_StopFlg; }
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
		//元の大きさ
		Vector3 m_Scale = Vector3(0.5f,0.5f,0.5f);
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
	//	class NumberSprite : public GameObject;
	//	用途: 数字のスプライト
	//--------------------------------------------------------------------------------------
	class NumberSprite : public GameObject
	{
	private:
		//なんかしらんメッシュのリスト
		vector<shared_ptr<MeshResource>> m_Mesh;
		int m_num = 0;
		//桁数
		int m_digit = 0;
		//生成されてる数字
		int m_Constdigit = 0;
		//表示レイヤー
		int m_layer = 0;
		//大きさ
		Vector2 m_scale;
		//位置
		Vector2 m_pos;
		//数字分のvector配列
		vector<shared_ptr<GameObject>> m_Numbers;
	public :
		NumberSprite(const shared_ptr<Stage>& StagePtr, int num,Vector2 pos,Vector2 scale,int layer);
		
		void OnCreate()override;

		//位置調整
		void SetPositionVec2(Vector2 pos);
		//大きさ調整
		void SetScaleVec2(Vector2 scale);
		void SetNum(int num);
	};

	//--------------------------------------------------------------------------------------
	//	class LimitTime : public GameObject;
	//	用途: 制限時間
	//--------------------------------------------------------------------------------------
	class LimitTime : public GameObject
	{
	private:
		//カウント時間
		float m_nowTime = 0;
		//リミット時間引数で初期値決める
		float m_LimitTime = 60.0f;
		//数字スプライト
		shared_ptr<NumberSprite> m_numberSp;
	public:
		LimitTime(const shared_ptr<Stage>& StagePtr, float LimitTime);
		void OnCreate() override;
		void OnUpdate() override;

		void TimeOver();

		int GetReamingTime() { return (int)m_nowTime; }
		int GetLimitTime() { return (int)m_LimitTime; }
		int GetClearTime() { return (int)(m_LimitTime - m_nowTime); }
	};

	//--------------------------------------------------------------------------------------
	//	class ScoreItem : public GameObject;
	//	用途:　スコアアイテム
	//--------------------------------------------------------------------------------------
	class ScoreItem : public GameObject
	{
	private :
		Vector3 m_InitPos;
		Vector3 m_InitScale;
		bool m_Active = true;
	public :
		ScoreItem(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale);

		void OnCreate() override;

		void Delete();

		bool GetActive() { return m_Active; }


		//****仮
		void Detekuru();
		void Kieru();
		//****仮
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
	//	class PauseMenu : public GameObject;
	//	用途: ポーズメニュー
	//--------------------------------------------------------------------------------------
	class PauseMenu : public GameObject
	{
	private:
		shared_ptr<GameObject> m_ReTryLogo;
		//shared_ptr<GameObject> m_mapLogo;
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
		//改定後 0:retry 1:stageselect 2:title
		int m_selectnum = 0;

		//操作フラグ
		bool m_moveFlg = false;

		//選択時X
		const float m_SelectX = -750;
		//非選択時X
		const float m_NotSelectX = -850;

		//選択時Scale
		const Vector3 m_SelectScale = Vector3(500,500,1);
		const Vector3 m_NotSelectScale = Vector3(400,400,1);

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
		bool m_ActiveFlg = true;

		//エフェクト
		vector<shared_ptr<MagicParticle>> m_Particle;
	public :
		Gimmick1(const shared_ptr<Stage>& StagePtr,Vector3 pos,Vector3 scale);
		void OnCreate() override;

		void Delete(MagicType MT);

		bool GetActive() { return m_ActiveFlg; }

		void SetParticle(shared_ptr<MagicParticle> ParticleVec) { m_Particle.push_back(ParticleVec); }
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
		bool m_ActiveFlg = true;
	public:
		Gimmick2(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale);
		void OnCreate() override;

		void Delete(MagicType MT);

		bool GetActive() { return m_ActiveFlg; }
	};

	//--------------------------------------------------------------------------------------
	//	class Gimmick2_1 : public GameObject;
	//	用途:　風車に風当てると閉じる水門
	//--------------------------------------------------------------------------------------
	class Gimmick2_1 : public GameObject
	{
	private :
		//初期位置
		Vector3 m_InitPos;
		//大きさ
		Vector3 m_Scale;
		//閉じてるかどうか
		bool m_CloseFlg = false;
		//動いてるかどうか
		bool m_MoveFlg = false;
		//目指してる座標
		float m_targetY=0;
	public:
		Gimmick2_1(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale);
		void OnCreate()override;
		void OnUpdate()override;
		//なんか動く
		void Action();
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

		//プレイヤーがいるかどうか
		void OnPlayer();

	};

	//--------------------------------------------------------------------------------------
	//	class WaterFall : public GameObject;
	//	用途: 滝
	//--------------------------------------------------------------------------------------
	class WaterFall : public GameObject
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
	public:
		WaterFall(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale);
		void OnCreate() override;

		//凍らす
		void Freeze();
		//溶かす
		void Melt();
		//止める
		void Stop();
		//流す
		void Flow();

		//プレイヤーがいるかどうか
		void OnPlayer();

		bool GetFlow() { return m_FlowFlg; }

		void HitMagic(MagicType mt);
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
		//上の滝版
		vector<shared_ptr<WaterFall>> m_waterfalls;
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

		void SetWaterFalls(vector<shared_ptr<WaterFall>> waterfalls) { m_waterfalls = waterfalls; }

		bool GetFlow() { return m_FlowFlg; }

		bool GetFreeze() { return m_FreezeFlg; }

		//プレイヤーがいるかどうか
		void OnPlayer();


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
		bool m_ActiveFlg = true;
	public:
		Gimmick5(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale);
		void OnCreate() override;

		void Delete(MagicType MT);

		bool GetActive() { return m_ActiveFlg; }

	};

}
//end basecross
