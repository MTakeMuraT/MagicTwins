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
		//暗転用作成
		void CreateBlack();
		//PRESS START作成
		void CreatePressStart();
		//シーン遷移
		void SceneChange();

		//コントローラー効くかどうか
		bool m_ConFlg = true;

		//PRESS STARTの透明度
		float m_PSAlpha = 1.0f;
		//透明化してるか実体化してるかfalseで透明化
		bool m_PSAlphaFlg = false;
	public:
		//構築と破棄
		Title() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}
