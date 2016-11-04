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

		//ビューのカメラの設定(カメラ固定)
		auto PtrCamera = PtrView->GetCamera();
		PtrCamera->SetEye(Vector3(0.0f, 0.0f, -1.0f));
		PtrCamera->SetAt(Vector3(0.0f, 0.0f, 0.0f));


		//シングルライトの作成
		auto PtrSingleLight = CreateLight<SingleLight>();
		//ライトの設定
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

		//スプライトをつける
		auto PtrSprite = ResultBack->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"RESULTBACK_TX");

		//透明度反映
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

		//スプライトをつける
		auto PtrSprite = ResultLogo->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"RESULTLOGO_TX");

		SetSharedGameObject(L"SeLo", ResultLogo);

		ResultLogo->SetDrawLayer(2);

		//透明度反映
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
			//リソースの作成
			CreateResourses();
			//ビューとライトの作成
			CreateViewLight();
			//背景作成
			CreateBack();
			//ロゴ作成
			CreateResultLogo();


			//文字表示テスト用
			auto obj = AddGameObject<GameObject>();
			auto st = obj->AddComponent<StringSprite>();
			st->SetTextRect(Rect2D<float>(16.0f, 16.0f, 320.0f, 240.0f));
			st->SetFont(L"", 40);
			st->SetText(L"B:Stage\nA:Title\nX:Select");
			obj->SetDrawLayer(10);
			SetSharedGameObject(L"StringObj", obj);

			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			int num = ScenePtr->GetClearTime();

			wstring txt;

			auto obj1 = AddGameObject<GameObject>();
			auto st1 = obj1->AddComponent<StringSprite>();
			st1->SetTextRect(Rect2D<float>(900.0f, 200.0f, 1920.0f, 480.0f));
			st1->SetFontColor(Color4(1, 1, 0, 1));
			st1->SetFont(L"", 200);
			if (num < 10)
			{
				txt = L"S";
			}
			else if (num < 20)
			{
				txt = L"A";
			}
			else if (num < 40)
			{
				txt = L"B";
			}
			else
			{
				txt = L"C";
			}
			st1->SetText(txt);
			obj1->SetDrawLayer(10);


			auto obj2 = AddGameObject<GameObject>();
			auto st2 = obj2->AddComponent<StringSprite>();
			st2->SetTextRect(Rect2D<float>(400.0f, 512.0f, 1920.0f, 480.0f));
			st2->SetFontColor(Color4(0, 0, 0, 1));
			st2->SetFont(L"", 100);
			txt = L"CLEARTIME : " + Util::IntToWStr(num);
			txt += L" Seconds";
			st2->SetText(txt);
			obj2->SetDrawLayer(10);

		}
		catch (...) {
			throw;
		}
	}

	void Result::OnUpdate()
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
			//テスト用、シーン切り替え先変更
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
			{
				auto ScenePtr = App::GetApp()->GetScene<Scene>();
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"Title");
			}
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_X)
			{
				auto ScenePtr = App::GetApp()->GetScene<Scene>();
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"StageSelect");
			}
		}

	}

}