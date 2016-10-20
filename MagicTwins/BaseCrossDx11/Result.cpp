#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void Result::CreateResourses()
	{
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = DataDir + L"ResultLogo.png";
		App::GetApp()->RegisterTexture(L"RESULTLOGO_TX", strTexture);
		strTexture = DataDir + L"sky.png";
		App::GetApp()->RegisterTexture(L"RESULTBACK_TX", strTexture);

	}

	void Result::CreateViewLight()
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

	void Result::CreateBack()
	{
		auto ResultBack = AddGameObject<GameObject>();
		ResultBack->AddComponent<Transform>();
		auto PtrTransform = ResultBack->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(0, 0, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(WindowSize.x, WindowSize.y, 1);

		//�X�v���C�g������
		auto PtrSprite = ResultBack->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"RESULTBACK_TX");

		//�����x���f
		ResultBack->SetAlphaActive(true);

		ResultBack->SetDrawLayer(1);

		SetSharedGameObject(L"TiBa", ResultBack);


	}

	void Result::CreateResultLogo()
	{
		auto ResultLogo = AddGameObject<GameObject>();
		ResultLogo->AddComponent<Transform>();
		auto PtrTransform = ResultLogo->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(0, WindowSize.y / 2.5f, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(1000, 200, 1);

		//�X�v���C�g������
		auto PtrSprite = ResultLogo->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"RESULTLOGO_TX");

		SetSharedGameObject(L"SeLo", ResultLogo);

		ResultLogo->SetDrawLayer(2);

		//�����x���f
		ResultLogo->SetAlphaActive(true);

	}

	void Result::SceneChange()
	{
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameStage");
	}

	void Result::OnCreate()
	{
		try {
			//���\�[�X�̍쐬
			CreateResourses();
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�w�i�쐬
			CreateBack();
			//���S�쐬
			CreateResultLogo();

		}
		catch (...) {
			throw;
		}
	}

	void Result::OnUpdate()
	{
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
			{
				SceneChange();
			}
		}

	}

}