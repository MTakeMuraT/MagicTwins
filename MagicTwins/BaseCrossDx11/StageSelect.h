#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ステージセレクト
	//--------------------------------------------------------------------------------------
	class  StageSelect: public Stage {
		//リソースの作成
		void CreateResourses();
		//ビューの作成
		void CreateViewLight();
		//背景画像作成
		void CreateBack();
		//セレクトロゴ
		void CreateSelectLogo();
		//ステージセレクト画像(仮)
		void CreaateStageSelect();
		//シーン遷移
		void SceneChange();
		

		int m_SceneNum;

		bool m_flag;

	public:
		//構築と破棄
		StageSelect() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}