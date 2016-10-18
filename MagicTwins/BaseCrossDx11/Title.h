#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	タイトル
	//--------------------------------------------------------------------------------------
	class Title : public Stage {
		//リソースの作成
		void CreateResourses();
		//ビューの作成
		void CreateViewLight();
		//背景画像作成
		void CreateBack();
		//タイトル文字
		void CreateTitle();

		//シーン遷移
		void SceneChange();
	public:
		//構築と破棄
		Title() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}
