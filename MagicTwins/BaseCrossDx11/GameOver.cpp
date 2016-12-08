#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void GameOver::CreateResourses()
	{
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture;
		//背景
		strTexture = DataDir + L"GameOver_Back.png";
		App::GetApp()->RegisterTexture(L"GAMEOVERBACK_TX", strTexture);
		//ゲームオーバーロゴ
		strTexture = DataDir + L"GemeOver_Logo.png";
		App::GetApp()->RegisterTexture(L"GAMEOVERLOGO_TX", strTexture);
		//リトライロゴ
		strTexture = DataDir + L"ReTryLogo.png";
		App::GetApp()->RegisterTexture(L"RETRYLOGO_TX", strTexture);
		//セレクトロゴ
		strTexture = DataDir + L"SelectBackLogo.png";
		App::GetApp()->RegisterTexture(L"SELECTLOGO_TX", strTexture);
		//タイトルロゴ
		strTexture = DataDir + L"TitleBackLogo.png";
		App::GetApp()->RegisterTexture(L"TITLELOGO_TX", strTexture);
		//キャラ１ロゴ
		strTexture = DataDir + L"GameOver_Chara1.png";
		App::GetApp()->RegisterTexture(L"GAMEOVERCHARA1_TX", strTexture);
		//キャラ２ロゴ
		strTexture = DataDir + L"GameOver_Chara2.png";
		App::GetApp()->RegisterTexture(L"GAMEOVERCHARA2_TX", strTexture);


		//暗転用の黒
		strTexture = DataDir + L"Black.png";
		App::GetApp()->RegisterTexture(L"BLACK_TX", strTexture);

	}

	void GameOver::CreateViewLight()
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

	void GameOver::CreateBack()
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
		PtrSprite->SetTextureResource(L"GAMEOVERBACK_TX");
		
		SelectBack->SetDrawLayer(1);

	}

	void GameOver::CreateOverLogo()
	{
		auto OverLogo = AddGameObject<GameObject>();
		OverLogo->AddComponent<Transform>();
		auto PtrTransform = OverLogo->GetComponent<Transform>();
		PtrTransform->SetPosition(0, 400, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(1100, 700, 1);

		//スプライトをつける
		auto PtrSprite = OverLogo->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"GAMEOVERLOGO_TX");

		OverLogo->SetDrawLayer(2);

		//透明度反映
		OverLogo->SetAlphaActive(true);

	}

	//リトライロゴ作成
	void GameOver::CreateRetry()
	{
		auto RetryLogo = AddGameObject<GameObject>();
		RetryLogo->AddComponent<Transform>();
		auto PtrTransform = RetryLogo->GetComponent<Transform>();
		PtrTransform->SetPosition(-600, -350, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(500, 500, 1);

		//スプライトをつける
		auto PtrSprite = RetryLogo->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"RETRYLOGO_TX");

		RetryLogo->SetDrawLayer(2);

		//透明度反映
		RetryLogo->SetAlphaActive(true);

		m_ReTryLogo = RetryLogo;
	}

	//セレクトロゴ作成
	void GameOver::CreateStageSelect()
	{
		auto StageSelectLogo = AddGameObject<GameObject>();
		StageSelectLogo->AddComponent<Transform>();
		auto PtrTransform = StageSelectLogo->GetComponent<Transform>();
		PtrTransform->SetPosition(0, -350, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(500, 500, 500);

		//スプライトをつける
		auto PtrSprite = StageSelectLogo->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"SELECTLOGO_TX");

		StageSelectLogo->SetDrawLayer(2);

		//透明度反映
		StageSelectLogo->SetAlphaActive(true);

		m_SelectLogo = StageSelectLogo;
	}

	//タイトルロゴ作成
	void GameOver::CreateTitle()
	{
		auto TitleLogo = AddGameObject<GameObject>();
		TitleLogo->AddComponent<Transform>();
		auto PtrTransform = TitleLogo->GetComponent<Transform>();
		PtrTransform->SetPosition(600,-350, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(500, 500, 1);

		//スプライトをつける
		auto PtrSprite = TitleLogo->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"TITLELOGO_TX");

		TitleLogo->SetDrawLayer(2);

		//透明度反映
		TitleLogo->SetAlphaActive(true);

		m_TitleLogo = TitleLogo;
	}
	//キャラ作成
	void GameOver::CreateChar()
	{
		auto CharPtr = AddGameObject<GameObject>();
		auto CPTrans = CharPtr->AddComponent<Transform>();
		CPTrans->SetPosition(-200, 0, 0);
		CPTrans->SetScale(500, 500, 1);
		CPTrans->SetRotation(0, 0, 0);

		auto CPDraw = CharPtr->AddComponent<PCTSpriteDraw>();
		CPDraw->SetTextureResource(L"GAMEOVERCHARA1_TX");
		CharPtr->SetAlphaActive(true);
		CharPtr->SetDrawLayer(2);

		CharPtr = AddGameObject<GameObject>();
		CPTrans = CharPtr->AddComponent<Transform>();
		CPTrans->SetPosition(200, 0, 0);
		CPTrans->SetScale(500, 500, 1);
		CPTrans->SetRotation(0, 0, 0);

		CPDraw = CharPtr->AddComponent<PCTSpriteDraw>();
		CPDraw->SetTextureResource(L"GAMEOVERCHARA2_TX");
		CharPtr->SetAlphaActive(true);
		CharPtr->SetDrawLayer(2);

	}

	void GameOver::SceneChange()
	{
		if (m_selectnum == 0)
		{
			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameStage");
		}
		if (m_selectnum == 1)
		{
			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"StageSelect");
		}
		if (m_selectnum == 2)
		{
			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"Title");
		}

	}

	void GameOver::OnCreate()
	{
		try {
			//リソースの作成
			CreateResourses();
			//ビューとライトの作成
			CreateViewLight();
			//背景作成
			CreateBack();
			//ロゴ作成
			CreateOverLogo();
			//リトライロゴ作成
			CreateRetry();
			//ステージセレクトロゴ作成
			CreateStageSelect();
			//タイトルロゴ作成
			CreateTitle();
			//キャラ作成
			CreateChar();

			//SEマネージャー
			SetSharedGameObject(L"SEM", AddGameObject<SEManager>());

			auto obj = AddGameObject<GameObject>();
			//文字列をつける
			auto PtrString = obj->AddComponent<StringSprite>();
			PtrString->SetText(L"");
			PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
			PtrString->SetFont(L"", 80);
			PtrString->SetFontColor(Color4(0, 0, 0, 1));
			obj->SetDrawLayer(10);
			SetSharedGameObject(L"StringTxt", obj);

			//大きさ調整
			m_ReTryLogo->GetComponent<Transform>()->SetScale(m_SelectScale);
			m_SelectLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
			m_TitleLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);

		}
		catch (...) {
			throw;
		}

	}

	void GameOver::OnUpdate()
	{
		if (!GetSharedGameObject<Black>(L"OverBlack", false))
		{
			//文字表示
			auto getobj = GetSharedGameObject<GameObject>(L"StringTxt", false);
			wstring txt = Util::IntToWStr(m_selectnum);
			getobj->GetComponent<StringSprite>()->SetText(txt);

			//*テスト用
			auto key = App::GetApp()->GetInputDevice().GetKeyState();
			if (key.m_bPressedKeyTbl[VK_SPACE])
			{
				//SceneChange();
				auto obj = AddGameObject<Black>();
				obj->StartBlack();
				obj->SetDrawLayer(10);
				SetSharedGameObject(L"OverBlack", obj);
				//SE再生
				GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("Select");

			}
			//*テスト用


			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

			Vector2 inputXY = Vector2(CntlVec[0].fThumbLX, CntlVec[0].fThumbLY);
			if (!m_moveFlg)
			{
				if (inputXY.x < -0.8f)
				{
					m_moveFlg = true;
					m_selectnum--;
					if (m_selectnum < 0)
					{
						m_selectnum = 2;
					}
				}
				if (inputXY.x > 0.8f)
				{
					m_moveFlg = true;
					m_selectnum++;
					if (m_selectnum > 2)
					{
						m_selectnum = 0;
					}
				}

				//変更あったら
				if (m_moveFlg)
				{
					//Vector3 pos;
					Vector3 scale;
					switch (m_selectnum)
					{
					case 0:
						m_ReTryLogo->GetComponent<Transform>()->SetScale(m_SelectScale);
						m_SelectLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
						m_TitleLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);


						break;
					case 1:
						m_ReTryLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
						m_SelectLogo->GetComponent<Transform>()->SetScale(m_SelectScale);
						m_TitleLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);


						break;
					case 2:
						m_ReTryLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
						m_SelectLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
						m_TitleLogo->GetComponent<Transform>()->SetScale(m_SelectScale);

						break;

					}
				}
			}
			else if (inputXY.x < 0.1f && inputXY.x > -0.1f &&
				inputXY.y < 0.1f && inputXY.y > -0.1f)
			{
				m_moveFlg = false;
			}

			if (CntlVec[0].bConnected)
			{
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
				{
					auto obj = AddGameObject<Black>();
					obj->StartBlack();
					obj->SetDrawLayer(10);
					SetSharedGameObject(L"OverBlack",obj);

					//SE再生
					GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("Select");
					//SceneChange();

				}
			}
		}
		//暗転幕が存在したら
		else
		{
			if (GetSharedGameObject<Black>(L"OverBlack", false)->GetBlackFinish())
			{
				SceneChange();
			}
		}
	}

}