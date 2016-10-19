#pragma once
#include "stdafx.h"

namespace basecross
{
	class GameOver : public Stage
	{
		//リソースの作成
		void CreateResourses();
		//ビューの作成
		void CreateViewLight();
		//背景画像作成
		void CreateBack();
		//ゲームオーバー文字
		void CreateOverLogo();

		//シーン遷移
		void SceneChange();
	public:
		GameOver() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};
}