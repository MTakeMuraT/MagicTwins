#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//�r���[�ƃ��C�g�̍쐬
	void Tutorial::CreateViewLight()
	{

		auto PtrView = CreateView<SingleView>();

		//�r���[�̃J�����̐ݒ�(�J�����Œ�)
		auto PtrCamera = PtrView->GetCamera();
		PtrCamera->SetEye(Vector3(0.0f, 0.0f, -1.0f));
		PtrCamera->SetAt(Vector3(0.0f, 0.0f, 0.0f));


		//�V���O�����C�g�̍쐬
		auto PtrSingleLight = CreateLight<SingleLight>();
		//���C�g�̐ݒ�
		PtrSingleLight->GetLight().SetPositionToDirectional(-0.25f, 1.0f, -0.25f);

	}

	//�N���G�C�g
	void Tutorial::OnCreate()
	{
		//���\�[�X�ǂݍ���
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = DataDir + L"Tutorial/Tex1.png";
		App::GetApp()->RegisterTexture(L"TImage1", strTexture);
		strTexture = DataDir + L"Tutorial/Tex2.png";
		App::GetApp()->RegisterTexture(L"TImage2", strTexture);

		auto obj = AddGameObject<GameObject>();
		auto TranP = obj->AddComponent<Transform>();
		TranP->SetPosition(0, 0, 0);
		TranP->SetRotation(0, 0, 0);
		TranP->SetScale(1920, 1080, 1);

		auto Draw = obj->AddComponent<PCTSpriteDraw>();
		Draw->SetTextureResource(L"TImage1");

		obj->SetAlphaActive(true);
		m_Image = obj;

		//������
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
		}
		catch (...) {
			throw;
		}

	}

	//�A�b�v�f�[�g
	void Tutorial::OnUpdate()
	{
		if (!m_endFlg)
		{
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (CntlVec[0].bConnected)
			{
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B ||
					CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
				{
					m_TexNum++;
					if (m_TexNum > m_MaxTexNum)
					{
						auto black = AddGameObject<Black>();
						SetSharedGameObject(L"Black", black);
						black->StartBlack();
						m_endFlg = true;
						return;
					}
					wstring txt = L"TImage" + Util::IntToWStr(m_TexNum);
					m_Image->GetComponent<PCTSpriteDraw>()->SetTextureResource(txt);
				}
			}
		}
		//�Ó]��
		else
		{
			if (GetSharedGameObject<Black>(L"Black", false)->GetBlackFinish())
			{
				auto ScenePtr = App::GetApp()->GetScene<Scene>();
				//�`���[�g���A���݂����ǂ����̃t���O���X�V(����:true�ɕύX)
				ScenePtr->SetTutorialOpenFlg(true);

				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"StageSelect");
			}
		}
	}
}