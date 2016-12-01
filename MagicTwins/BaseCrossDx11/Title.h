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
		//PRESS START作成
		void CreatePressStart();
		//ステージセレクトロゴ作成
		void CreateStageSelectLogo();
		//ステージセレクト矢印
		void CreateArrow();

		//キャラ達を作成
		void CreateChar();
		//ステージイメージ作成
		void CreateStageImage();

		//シーン遷移
		void SceneChange();

		//PRESS STARTの透明度
		float m_PSAlpha = 1.0f;
		//透明化してるか実体化してるかfalseで透明化
		bool m_PSAlphaFlg = false;

		//アニメーションの状態
		int m_AnimationState = 0;
		//アニメーションしてるかどうか
		bool m_AnimationFlg = false;

		//時間
		float m_time = 0;

		//タイトルロゴ
		shared_ptr<GameObject> m_TitleLogo;
		//プレススタートロゴ
		shared_ptr<GameObject> m_PressStartLogo;
		//文字表示用
		shared_ptr<GameObject> m_String;
		//キャラ１の画像
		shared_ptr<GameObject> m_Char1;
		//キャラ２の画像
		shared_ptr<GameObject> m_Char2;

		//ステージセレクトロゴ
		shared_ptr<GameObject> m_StageSelectLogo;
		//ステージセレクト矢印
		shared_ptr<GameObject> m_ArrowL;
		shared_ptr<GameObject> m_ArrowR;

		//ステージイメージ
		shared_ptr<GameObject> m_StageImage;

		//キャラの位置調整用
		Vector3 m_Scale;
		Vector3 m_pos;
	public:
		//構築と破棄
		Title() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void Animation();
	};


}
