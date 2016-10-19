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

	//ビューとライトの作成
	void Title::CreateViewLight() {
		
		auto PtrView = CreateView<SingleView>();

		//ビューのカメラの設定(カメラ固定)
		auto PtrCamera = PtrView->GetCamera();
		PtrCamera->SetEye(Vector3(0.0f, 0.0f, -1.0f));
		PtrCamera->SetAt(Vector3(0.0f, 0.0f, 0.0f));


		//シングルライトの作成
		auto PtrSingleLight = CreateLight<SingleLight>();
		//ライトの設定
		PtrSingleLight->GetLight().SetPositionToDirectional(-0.25f, 1.0f, -0.25f);

	}

	//背景画像
	void Title::CreateBack()
	{
		auto TitleBack = AddGameObject<GameObject>();
		TitleBack->AddComponent<Transform>();
		auto PtrTransform = TitleBack->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(0, 0, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(WindowSize.x, WindowSize.y, 1);

		//スプライトをつける
		auto PtrSprite = TitleBack->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"TITLEBACK_TX");

		//透明度反映
		TitleBack->SetAlphaActive(true);

		TitleBack->SetDrawLayer(1);

		SetSharedGameObject(L"TiBa", TitleBack);


		
	}

	//タイトル文字画像
	void Title::CreateTitle()
	{
	
		auto TitleLogo = AddGameObject<GameObject>();
		TitleLogo->AddComponent<Transform>();
		auto PtrTransform = TitleLogo->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(0, WindowSize.y/4, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(1500, 400, 1);

		//スプライトをつける
		auto PtrSprite = TitleLogo->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"TITLE_TX");

		SetSharedGameObject(L"TiLo", TitleLogo);
		
		TitleLogo->SetDrawLayer(2);

		//透明度反映
		TitleLogo->SetAlphaActive(true);
		
	}

	//シーン変更
	void Title::SceneChange()
	{
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"StageSelect");
	}

	void Title::OnCreate() {
		try {
			//リソースの作成
			CreateResourses();
			//ビューとライトの作成
			CreateViewLight();
			//背景作成
			CreateBack();
			//タイトルロゴ作成
			CreateTitle();

		}
		catch (...) {
			throw;
		}
	}

	void Title::OnUpdate()
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