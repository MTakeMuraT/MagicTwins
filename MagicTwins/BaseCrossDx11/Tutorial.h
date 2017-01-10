#pragma once
#include "stdafx.h"

namespace basecross 
{
	//--------------------------------------------------------------------------------------
	//�@�`���[�g���A���̉摜
	//--------------------------------------------------------------------------------------

	class Tutorial : public Stage 
	{
		//�r���[�̍쐬
		void CreateViewLight();

		//�摜�̔ԍ�
		int m_TexNum = 1;
		const int m_MaxTexNum = 2;

		//�I������t���O
		bool m_endFlg = false;
		//�摜
		shared_ptr<GameObject> m_Image;
	public :
		Tutorial() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};
}