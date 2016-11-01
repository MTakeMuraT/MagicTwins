#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void StageSelect::CreateResourses()
	{
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = DataDir + L"StageSelectLogo.png";
		App::GetApp()->RegisterTexture(L"STAGESELECTLOGO_TX", strTexture);
		strTexture = DataDir + L"sky.png";
		App::GetApp()->RegisterTexture(L"SELECTBACK_TX", strTexture);
		//StegeSelect画像(仮)
		strTexture = DataDir + L"BButtom.png";
		App::GetApp()->RegisterTexture(L"BBUTTOM_TX", strTexture);

	}

	void StageSelect::CreateViewLight()
	{

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

	void StageSelect::CreateBack()
	{
		auto SelectBack = AddGameObject<GameObject>();
		SelectBack->AddComponent<Transform>();
		auto PtrTransform = SelectBack->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(0, 0, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(WindowSize.x, WindowSize.y, 1);

		//スプライトをつける
		auto PtrSprite = SelectBack->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"SELECTBACK_TX");

		//透明度反映
		SelectBack->SetAlphaActive(true);

		SelectBack->SetDrawLayer(1);

		SetSharedGameObject(L"TiBa", SelectBack);
	}

	void StageSelect::CreateSelectLogo()
	{
		auto SelectLogo = AddGameObject<GameObject>();
		SelectLogo->AddComponent<Transform>();
		auto PtrTransform = SelectLogo->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(0, WindowSize.y / 2.5f, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(1000, 200, 1);

		//スプライトをつける
		auto PtrSprite = SelectLogo->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"STAGESELECTLOGO_TX");

		SetSharedGameObject(L"SeLo", SelectLogo);

		SelectLogo->SetDrawLayer(2);

		//透明度反映
		SelectLogo->SetAlphaActive(true);

	}

	void StageSelect::SceneChange()
	{
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameStage");
	}

	//ステージセレクト画像(仮)
	void StageSelect::ButtomInfo()
	{
		auto BButtom = AddGameObject<GameObject>();
		BButtom->AddComponent<Transform>();
		auto PtrTransform = BButtom->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(600, -400, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(500, 200, 1);

		//スプライトを付ける
		auto PtrSprite = BButtom->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"BBUTTOM_TX");

		SetSharedGameObject(L"BButtom", BButtom);

		BButtom->SetDrawLayer(2);

		//透明度反映
		BButtom->SetAlphaActive(true);


	}


	void StageSelect::OnCreate()
	{
		try {
			//リソースの作成
			CreateResourses();
			//ビューとライトの作成
			CreateViewLight();
			//背景作成
			CreateBack();
			//ロゴ作成
			CreateSelectLogo();
			//ボタン説明
			ButtomInfo();

			//文字列を付ける
			StringObj = AddGameObject<GameObject>();
			StringObj->SetDrawLayer(3);
			auto SoSt = StringObj->AddComponent<StringSprite>();
			SoSt->SetText(L"");
			SoSt->SetTextRect(Rect2D<float>(512.0f, 128.0f, 1024.0f, 960.0f));
			SoSt->SetFont(L"", 100);

		}
		catch (...) {
			throw;
		}




	}

	void StageSelect::OnUpdate()
	{
		//*テスト用
		auto key = App::GetApp()->GetInputDevice().GetKeyState();
		if (key.m_bPressedKeyTbl[VK_SPACE])
		{
			SceneChange();
		}
		//*テスト用

		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
			{
				SceneChange();
			}

			//ステージセレクト数字弄る
			if (CntlVec[0].fThumbLX > 0.5f && m_Conflg)
			{
				m_StageNum++;
				m_Conflg = false;

			}
			if (CntlVec[0].fThumbLX < -0.5f && m_Conflg)
			{
				if (m_StageNum != 0)
				{
					m_StageNum--;
					m_Conflg = false;
				}
			}
			if (abs(CntlVec[0].fThumbLX) < 0.2f)
			{
				m_Conflg = true;
			}

		}

		//数字表示
		StringObj->GetComponent<StringSprite>()->SetText(Util::IntToWStr(m_StageNum));
	}
}

