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
		//Nextステージロゴ作成
		void CreateNextStageLogo();
		//リトライロゴ作成
		void CreateRetryLogo();
		//ステージセレクトロゴ作成
		void CreateStageSelectLogo();
		//タイトルロゴ作成
		void CreateTitleLogo();
		//empty1
		void Createempty1();
		//empty2
		void Createempty2();
		//empty3
		void Createempty3();

		//シーン遷移
		void SceneChange();
	public:
		Result() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};
}