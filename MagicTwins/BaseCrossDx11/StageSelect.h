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

		//ステージロゴ作成
		void CreateStageLogo();

		//最大値
		unsigned int m_MaxStageNum = 10;
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

	//--------------------------------------------------------------------------------------
	//	class CharEye : public GameObject;
	//	用途: キャラの目
	//	設定した時間ごとに瞬きするか判定しながら瞬き
	//--------------------------------------------------------------------------------------

	class CharEye : public GameObject
	{
	private :
		//初期位置
		Vector3 m_Pos;
		//目が変わる間隔
		const float m_EyeCloseTime = 0.05f;
		//間隔
		const float m_IntarvalEyeTime = 1.0f;
		//計算用
		float m_CountTime = 0;
		//目閉じてるフラグ
		bool m_EyeCloseFlg = false;
		//確率
		const float m_Par = 50.0f;
		int m_EyeCloseState = 0;
		//0開き 1目半閉じ 2目閉じ
		vector<shared_ptr<GameObject>> m_Eyes;

		//2キャラ目かどうか
		bool m_2PlayerFlg = false;
	public :
		CharEye(const shared_ptr<Stage>& StagePtr,Vector3 pos,bool flg);
		void OnCreate() override;
		void OnUpdate() override;

		void EyeClose();
	};
}