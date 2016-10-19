/*!
@file Character.h
@brief ÉLÉÉÉâÉNÉ^Å[Ç»Ç«
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	//	class Goal : public GameObject;
	//	ópìr: ÉSÅ[Éã
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
	//	ópìr: à√ì]ópçïîwåi
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

		//à√ì]ãNìÆ
		void StartBlack();

		//à√ì]ÇµÇΩÇ©Ç«Ç§Ç©éÊìæ
		bool GetBlackFinish();
	};

}
//end basecross
