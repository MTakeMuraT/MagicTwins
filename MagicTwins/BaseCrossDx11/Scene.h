/*!
@file Scene.h
@brief �V�[��
*/
#pragma once

#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
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
