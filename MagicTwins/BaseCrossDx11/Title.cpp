#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Title::CreateResourses()
	{
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = DataDir + L"title.png";
		App::GetApp()->RegisterTexture(L"TITLE_TX", strTexture);
		strTexture = DataDir + L"sky.png";
		App::GetApp()->RegisterTexture(L"TITLEBACK_TX", strTexture);

	}

	//�r���[�ƃ��C�g�̍쐬
	void Title::CreateViewLight() {
		
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

	//�w�i�摜
	void Title::CreateBack()
	{
		auto TitleBack = AddGameObject<GameObject>();
		TitleBack->AddComponent<Transform>();
		auto PtrTransform = TitleBack->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(0, 0, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(WindowSize.x, WindowSize.y, 1);

		//�X�v���C�g������
		auto PtrSprite = TitleBack->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"TITLEBACK_TX");

		//�����x���f
		TitleBack->SetAlphaActive(true);

		TitleBack->SetDrawLayer(1);

		SetSharedGameObject(L"TiBa", TitleBack);


		
	}

	//�^�C�g�������摜
	void Title::CreateTitle()
	{
	
		auto TitleLogo = AddGameObject<GameObject>();
		TitleLogo->AddComponent<Transform>();
		auto PtrTransform = TitleLogo->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(0, WindowSize.y/4, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(1500, 400, 1);

		//�X�v���C�g������
		auto PtrSprite = TitleLogo->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"TITLE_TX");

		SetSharedGameObject(L"TiLo", TitleLogo);
		
		TitleLogo->SetDrawLayer(2);

		//�����x���f
		TitleLogo->SetAlphaActive(true);
		
	}

	//�V�[���ύX
	void Title::SceneChange()
	{
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameStage");
	}

	void Title::OnCreate() {
		try {
			//���\�[�X�̍쐬
			CreateResourses();
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�w�i�쐬
			CreateBack();
			//�^�C�g�����S�쐬
			CreateTitle();

		}
		catch (...) {
			throw;
		}
	}

	void Title::OnUpdate()
	{
		SceneChange();
	}


}