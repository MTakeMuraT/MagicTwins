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
		void ButtomInfo();
		//シーン遷移
		void SceneChange();
		
		//ステージ番号
		unsigned int m_StageNum;
		//スティック判定
		bool m_Conflg;
		//文字列つけるオブジェクト
		shared_ptr<GameObject> StringObj;
	public:
		//構築と破棄
		StageSelect() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}