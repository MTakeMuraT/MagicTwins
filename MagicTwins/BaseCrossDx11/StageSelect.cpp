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
		strTexture = DataDir + L"StageSelect.png";
		App::GetApp()->RegisterTexture(L"STAGESELECT_TX", strTexture);

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

		//文字列を付ける(仮)
		auto Stp = SelectBack->AddComponent<StringSprite>();
		Stp->SetText(L"");
		Stp->SetTextRect(Rect2D<float>(512.0f, 16.0f, 1024.0f, 960.0f));
		Stp->SetFont(L"", 100);

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
	void StageSelect::CreaateStageSelect()
	{
		auto StageSelect = AddGameObject<GameObject>();
		StageSelect->AddComponent<Transform>();
		auto PtrTransform = StageSelect->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(600, -400, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(500, 200, 1);

		//スプライトを付ける
		auto PtrSprite = StageSelect->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"STAGESELECT_TX");

		SetSharedGameObject(L"StageSelect", StageSelect);

		StageSelect->SetDrawLayer(2);

		//透明度反映
		StageSelect->SetAlphaActive(true);
		GetSharedGameObject<GameObject>(L"TiBa", false)->GetComponent<StringSprite>()->SetText(L"0");


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
			//ステージセレクト(仮)
			CreaateStageSelect();

			//左右シーン遷移(仮)
			m_SceneNum = 0;
			m_flag = true;

		}
		catch (...) {
			throw;
		}

		

		
	}

	void StageSelect::OnUpdate()
	{


		//左右でシーン遷移(仮)
		auto ShareObject = GetSharedGameObject<GameObject>(L"TiBa", false);
		auto ShareString = ShareObject->GetComponent<StringSprite>();

		wstring sceneNum(L"");

		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
			{
				SceneChange();
			}
			//左右シーン遷移(仮)
			if (CntlVec[0].fThumbLX>0&&m_flag)
			{

				m_SceneNum++;
				m_flag=false;
				
			}
			if (CntlVec[0].fThumbLX < 0 && m_flag)
			{
				//m_SceneNum--;
				//m_flag = false;
			}
			if (CntlVec[0].fThumbLX == 0)
			{
				m_flag = true;
			}

		}
		sceneNum +=  Util::IntToWStr(m_SceneNum);
		ShareString->SetText(sceneNum);
		
	
	}

	}

