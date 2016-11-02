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
		//ボタン説明
		void CreaateStageSelect();
		//シーン遷移
		void SceneChange();
		//左矢印(仮)
		void Left();
		//右矢印(仮)
		void Right();

		//最大値
		unsigned int m_MaxNum = 5;
		//現在選択中の数字
		int m_SceneNum;

		bool m_flag;

	public:
		//構築と破棄
		StageSelect() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}