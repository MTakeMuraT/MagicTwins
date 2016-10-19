#pragma once
#include "stdafx.h"

namespace basecross
{
	class Result : public Stage
	{
		//リソースの作成
		void CreateResourses();
		//ビューの作成
		void CreateViewLight();
		//背景画像作成
		void CreateBack();
		//リザルト文字
		void CreateResultLogo();

		//シーン遷移
		void SceneChange();
	public:
		Result() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};
}