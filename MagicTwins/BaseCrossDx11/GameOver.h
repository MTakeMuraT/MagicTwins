#pragma once
#include "stdafx.h"

namespace basecross
{
	class GameOver : public Stage
	{
		
		shared_ptr<GameObject> m_ReTryLogo;
		shared_ptr<GameObject> m_StageSelectLogo;
		shared_ptr<GameObject> m_TitleLogo;
		shared_ptr<GameObject> m_Map;

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

		//シーン遷移
		void SceneChange();

		int m_selectnum = 0;
		//操作フラグ
		bool m_moveFlg = false;
		bool m_selectMapFlg = false;
		//選択時X
		const float m_SelectX = -750;
		//非選択時X
		const float m_NotSelectX = -850;
		

		//選択時Scale
		const Vector3 m_SelectScale = Vector3(500, 500, 1);
		const Vector3 m_NotSelectScale = Vector3(400, 400, 1);

	public:
		GameOver() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};
}