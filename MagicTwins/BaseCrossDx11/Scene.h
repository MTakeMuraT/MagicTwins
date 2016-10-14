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
	public:
		Scene() :SceneBase(){}
		virtual ~Scene(){}
		virtual void OnCreate() override;

	};

}

//end basecross
