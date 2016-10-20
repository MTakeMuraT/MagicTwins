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
}
//end basecross
