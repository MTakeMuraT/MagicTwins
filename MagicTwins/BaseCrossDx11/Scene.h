/*!
@file Scene.h
@brief シーン
*/
#pragma once

#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase
	{
	private:
		unsigned int m_clearTime = 0;
	public:
		Scene() :SceneBase(){}
		virtual ~Scene(){}
		virtual void OnCreate() override;
		virtual void OnEvent(const shared_ptr<Event>& event) override;

		void SetClearTime(int num) { m_clearTime = num; }
		int GetClearTime() { return m_clearTime; }
	};

}

//end basecross
