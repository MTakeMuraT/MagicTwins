#pragma once
#include "stdafx.h"

namespace basecross
{
	class GameOver : public Stage
	{
		//リソースの作成
		void CreateResourses();
		//ビューの作成
		void CreateViewLight();
		//背景画像作成
		void CreateBack();
		//ゲームオーバー文字
		void CreateOverLogo();
		//リトライの作成
		void CreateRetry();
		//ステージセレクトの作成
		void CreateStageSelect();
		//タイトルの作成
		void CreateTitle();
		//キャラ作成
		void CreateChar();


		//シーン遷移
		void SceneChange();

		int m_selectnum = 0;
		//操作フラグ
		bool m_moveFlg = false;
		
		//リトライロゴ
		shared_ptr<GameObject> m_ReTryLogo;
		//セレクトロゴ
		shared_ptr<GameObject> m_SelectLogo;
		//タイトルロゴ
		shared_ptr<GameObject> m_TitleLogo;


		//選択時Scale
		const Vector3 m_SelectScale = Vector3(500, 500, 1);
		const Vector3 m_NotSelectScale = Vector3(400, 400, 1);

	public:
		GameOver() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};
}