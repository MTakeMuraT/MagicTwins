/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	//	class Goal : public GameObject;
	//	�p�r: �S�[��
	//--------------------------------------------------------------------------------------

	Goal::Goal(const shared_ptr<Stage>& StagePtr,Vector3 pos, Vector3 scale):
		GameObject(StagePtr),
		m_InitPos(pos),
		m_Scale(scale)
		{}
	void Goal::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_Scale);
		Ptr->SetRotation(0, 0, 0);

		//�Փ˔��������
		auto PtrCol = AddComponent<CollisionSphere>();
		//�������̂ݔ���
		PtrCol->SetIsHitAction(IsHitAction::AutoOnObjectRepel);

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ShadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//�`�悷��e�N�X�`����ݒ�
		PtrDraw->SetTextureResource(L"GOAL_TX");

		//��������
		SetAlphaActive(true);

	}
	//--------------------------------------------------------------------------------------
	//	class Black : public GameObject;
	//	�p�r: �Ó]�p��
	//--------------------------------------------------------------------------------------
	Black::Black(const shared_ptr<Stage>& StagePtr)	:
		GameObject(StagePtr)
	{}

	void Black::OnCreate()
	{
		//�E�B���h�E�T�C�Y�擾
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());

		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(0,0,0);
		Ptr->SetScale(WindowSize.x,WindowSize.y,1);
		Ptr->SetRotation(0, 0, 0);

		//�e�N�X�`��������
		auto PtrSprite = this->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"BRACK_TX");

		//������
		PtrSprite->SetDiffuse(Color4(1,1,1,0));

		//�\�����C���[10�ݒ�
		SetDrawLayer(10);

		//�����x���f
		SetAlphaActive(true);

	}

	void Black::OnUpdate()
	{
		//�N�����
		if (m_StartFlg)
		{
			//���̉�
			auto PtrSprite = this->AddComponent<PCTSpriteDraw>();
			m_alpha += 0.01f;
			PtrSprite->SetDiffuse(Color4(1, 1, 1, m_alpha));
			
			if (m_alpha >= 1.2f)
			{
				m_StartFlg = false;
				m_EndFlg = true;
			}
		}
	}

	void Black::StartBlack()
	{
		m_StartFlg = true;
	}

	bool Black::GetBlackFinish()
	{
		return m_EndFlg;
	}
}
//end basecross
