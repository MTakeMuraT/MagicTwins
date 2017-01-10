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
		void CreateStageImageFrame();
		//シーン遷移
		void SceneChange();
		//左矢印(仮)
		void Left();
		//右矢印(仮)
		void Right();
		//ステージイメージ
		void CreateStageImage();

		//最大値
		unsigned int m_MaxStageNum = 20;
		//現在選択中の数字
		unsigned int m_StageNum = 0;

		//選択するときの調整
		bool m_flag;

		//ボタン押したときの処理
		bool m_SelectFlg = false;

		//ステージイメージ
		shared_ptr<GameObject> m_StageImage;
		//回転してると見せかけてサイズ変更する。どうやらスプライトでは回転ができないらしい
		//回転中
		bool m_StageImageRotFlg = false;
		//途中までいったか
		bool m_SIHalfFlg = false;
		//イメージ回転
		void RotStageImage();
	public:
		//構築と破棄
		StageSelect() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}