#pragma once
#include "stdafx.h"

namespace basecross 
{
	//--------------------------------------------------------------------------------------
	//　チュートリアルの画像
	//--------------------------------------------------------------------------------------

	class Tutorial : public Stage 
	{
		//ビューの作成
		void CreateViewLight();

		//画像の番号
		int m_TexNum = 1;
		const int m_MaxTexNum = 2;

		//終わったフラグ
		bool m_endFlg = false;
		//画像
		shared_ptr<GameObject> m_Image;
	public :
		Tutorial() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};
}