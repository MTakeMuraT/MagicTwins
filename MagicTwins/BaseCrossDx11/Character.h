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
		//リミット時間
		float m_LimitTime = 60.0f;
	public :
		LimitTime(const shared_ptr<Stage>& StagePtr,float LimitTime);
		void OnCreate() override;
		void OnUpdate() override;

		void TimeOver();
	};

	//--------------------------------------------------------------------------------------
	//	class TransBlock : public GameObject;
	//	用途: 氷。炎の魔法[Fire]で溶かせる
	//--------------------------------------------------------------------------------------
	class TransBlock : public GameObject
	{
	private:
		//初期位置
		Vector3 m_InitPos;
		//大きさ
		Vector3 m_Scale;
	public :
		TransBlock(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale);
		void OnCreate() override;
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

}
//end basecross
