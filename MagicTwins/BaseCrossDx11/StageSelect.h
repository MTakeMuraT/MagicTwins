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
		//ボタン作成
		void CreateButtons();
		//ステージイメージ作成
		void CreateStageImage();
		//シーン遷移
		void SceneChange();
		//左矢印(仮)
		void Left();
		//右矢印(仮)
		void Right();

		//最大値
		unsigned int m_MaxStageNum = 5;
		//現在選択中の数字
		unsigned int m_StageNum = 1;

		//選択するときの調整
		bool m_flag;

	public:
		//構築と破棄
		StageSelect() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}