#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Title::CreateResourses()
	{
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = DataDir + L"Title.png";
		App::GetApp()->RegisterTexture(L"TITLE_TX", strTexture);
		strTexture = DataDir + L"TitleBack.png";
		App::GetApp()->RegisterTexture(L"TITLEBACK_TX", strTexture);
		strTexture = DataDir + L"PS.png";
		App::GetApp()->RegisterTexture(L"PRESSSTART_TX", strTexture);
		//キャラ１
		strTexture = DataDir + L"TitleChar1.png";
		App::GetApp()->RegisterTexture(L"CHAR1_TX", strTexture);
		//キャラ２
		strTexture = DataDir + L"TitleChar2.png";
		App::GetApp()->RegisterTexture(L"CHAR2_TX", strTexture);

		//ステージセレクトロゴ
		strTexture = DataDir + L"StageSelectLogo.png";
		App::GetApp()->RegisterTexture(L"STAGESELECTLOGO_TX", strTexture);

		//左矢印画像(仮)
		strTexture = DataDir + L"Left.png";
		App::GetApp()->RegisterTexture(L"LEFTARROW_TX", strTexture);
		//右矢印画像(仮)
		strTexture = DataDir + L"Right.png";
		App::GetApp()->RegisterTexture(L"RIGHTARROW_TX", strTexture);
		//ステージイメージ0
		strTexture = DataDir + L"StageImage/StageImage_0.png";
		App::GetApp()->RegisterTexture(L"STAGEIMAGE_0_TX", strTexture);


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
		
	}

	//タイトル文字画像
	void Title::CreateTitle()
	{
	
		auto TitleLogo = AddGameObject<GameObject>();
		TitleLogo->AddComponent<Transform>();
		auto PtrTransform = TitleLogo->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(0, WindowSize.y/5, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(1500, 600, 1);

		//スプライトをつける
		auto PtrSprite = TitleLogo->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"TITLE_TX");
		
		TitleLogo->SetDrawLayer(2);

		//透明度反映
		TitleLogo->SetAlphaActive(true);
		
		m_TitleLogo = TitleLogo;
	}

	//PRESS START作成
	void Title::CreatePressStart()
	{
		auto PressLogo = AddGameObject<GameObject>();
		PressLogo->AddComponent<Transform>();
		auto PtrTransform = PressLogo->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(0, -WindowSize.y / 4, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(800, 300, 1);

		//スプライトをつける
		auto PtrSprite = PressLogo->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"PRESSSTART_TX");

		PressLogo->SetDrawLayer(2);

		//透明度反映
		PressLogo->SetAlphaActive(true);

		m_PressStartLogo = PressLogo;
	}

	//ステージセレクトロゴ作成
	void Title::CreateStageSelectLogo()
	{		
		auto StageSelectLogoPtr = AddGameObject<GameObject>();
		auto SSLT = StageSelectLogoPtr->AddComponent<Transform>();
		SSLT->SetPosition(0, -1000, 0);
		SSLT->SetRotation(0, 0, 0);
		SSLT->SetScale(1000, 200, 1);
		//スプライトつけ
		auto SSLD = StageSelectLogoPtr->AddComponent<PCTSpriteDraw>();
		SSLD->SetTextureResource(L"STAGESELECTLOGO_TX");
		//透明度有効
		StageSelectLogoPtr->SetAlphaActive(true);
		//レイヤー設定
		StageSelectLogoPtr->SetDrawLayer(3);
		//アクセス用
		m_StageSelectLogo = StageSelectLogoPtr;

	}
	//ステージセレクト矢印
	void Title::CreateArrow()
	{
		//左
		auto ArrowPtr = AddGameObject<GameObject>();
		auto ArrowTra = ArrowPtr->AddComponent<Transform>();
		ArrowTra->SetPosition(1500, 0, 0);
		ArrowTra->SetRotation(0, 0, 0);
		ArrowTra->SetScale(150, 150, 1);
		//スプライトつけ
		auto ArrowDraw = ArrowPtr->AddComponent<PCTSpriteDraw>();
		ArrowDraw->SetTextureResource(L"LEFTARROW_TX");
		//透明度有効
		ArrowPtr->SetAlphaActive(true);
		//レイヤー設定
		ArrowPtr->SetDrawLayer(3);
		//アクセス用
		m_ArrowL = ArrowPtr;

		//右
		ArrowPtr = AddGameObject<GameObject>();
		ArrowTra = ArrowPtr->AddComponent<Transform>();
		ArrowTra->SetPosition(-1500, 0, 0);
		ArrowTra->SetRotation(0, 0, 0);
		ArrowTra->SetScale(150, 150, 1);
		//スプライトつけ
		ArrowDraw = ArrowPtr->AddComponent<PCTSpriteDraw>();
		ArrowDraw->SetTextureResource(L"RIGHTARROW_TX");
		//透明度有効
		ArrowPtr->SetAlphaActive(true);
		//レイヤー設定
		ArrowPtr->SetDrawLayer(3);
		//アクセス用
		m_ArrowR = ArrowPtr;

	}

	//キャラ達を作成
	void Title::CreateChar()
	{
		//1体目
		auto Char1Ptr = AddGameObject<GameObject>();
		auto Char1Tra = Char1Ptr->AddComponent<Transform>();
		Char1Tra->SetPosition(-706, -1500, 0);
		Char1Tra->SetRotation(0, 0, 0);
		Char1Tra->SetScale(788, 786, 1);
		//スプライトつけ
		auto C1Draw = Char1Ptr->AddComponent<PCTSpriteDraw>();
		C1Draw->SetTextureResource(L"CHAR1_TX");
		//透明度有効
		Char1Ptr->SetAlphaActive(true);
		//レイヤー設定
		Char1Ptr->SetDrawLayer(3);
		//アクセス用
		m_Char1 = Char1Ptr;

		//2体目
		auto Char2Ptr = AddGameObject<GameObject>();
		auto Char2Tra = Char2Ptr->AddComponent<Transform>();
		Char2Tra->SetPosition(684, -1500, 0);
		Char2Tra->SetRotation(0, 0, 0);
		Char2Tra->SetScale(788, 786, 1);
		//スプライトつけ
		auto C2Draw = Char2Ptr->AddComponent<PCTSpriteDraw>();
		C2Draw->SetTextureResource(L"CHAR2_TX");
		//透明度有効
		Char2Ptr->SetAlphaActive(true);
		//レイヤー設定
		Char2Ptr->SetDrawLayer(3);
		//アクセス用
		m_Char2 = Char2Ptr;

	}

	//ステージイメージ作成
	void Title::CreateStageImage()
	{
		//0のチュートリアル
		auto StageImagePtr = AddGameObject<GameObject>();
		auto SIPT = StageImagePtr->AddComponent<Transform>();
		SIPT->SetPosition(0, 0, 0);
		SIPT->SetRotation(0, 0, 0);
		SIPT->SetScale(10, 10, 1);
		//スプライトつけ
		auto SIPD = StageImagePtr->AddComponent<PCTSpriteDraw>();
		SIPD->SetTextureResource(L"STAGEIMAGE_0_TX");
		//透明度有効
		StageImagePtr->SetAlphaActive(true);
		//レイヤー設定
		StageImagePtr->SetDrawLayer(4);
		//アクセス用
		m_StageImage = StageImagePtr;

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
			//PRESS START作成
			CreatePressStart();
			//ステージセレクトロゴ作成
			CreateStageSelectLogo();
			//ステージセレクト矢印
			CreateArrow();

			//キャラ作成
			CreateChar();

			//ステージイメージ作成
			CreateStageImage();
		
			SetSharedGameObject(L"SEM", AddGameObject<SEManager>());


			//文字作成
			auto StringPtr = AddGameObject<GameObject>();
			auto SST = StringPtr->AddComponent<StringSprite>();
			SST->SetText(L"");
			SST->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
			SST->SetFont(L"", 40);
			SST->SetFontColor(Color4(0, 0, 0, 1));
			StringPtr->SetDrawLayer(10);
			m_String = StringPtr;
		}
		catch (...) {
			throw;
		}
	}

	void Title::OnUpdate()
	{
		//アニメーションしてればやって処理終わり
		if (m_AnimationFlg)
		{
			//透明化
			if (!m_PSAlphaFlg)
			{
				m_PSAlpha += -0.5f;
				if (m_PSAlpha <= 0)
				{
					m_PSAlphaFlg = true;
				}
			}
			//実体化
			else
			{
				m_PSAlpha += 0.5f;
				if (m_PSAlpha >= 1.0f)
				{
					m_PSAlphaFlg = false;
				}
			}
			m_PressStartLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_PSAlpha));
				
			//アニメーション
			Animation();
			return;
		}

		if (!m_AnimationFlg)
		{

			//*テスト用
			auto key = App::GetApp()->GetInputDevice().GetKeyState();
			if (key.m_bPressedKeyTbl[VK_SPACE])
			{
				m_AnimationFlg = true;
			}
			//*テスト用

			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (CntlVec[0].bConnected)
			{
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B ||
					CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
				{
					m_AnimationFlg = true;

					//SE再生
					GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("SelectTitle");
				}
			}

			//プレスBUTTONのロゴ
			//透明化
			if(!m_PSAlphaFlg)
			{
				m_PSAlpha += -0.02f;
				if (m_PSAlpha <= 0)
				{
					m_PSAlphaFlg = true;
				}
			}
			//実体化
			else
			{
				m_PSAlpha += 0.02f;
				if (m_PSAlpha >= 1.0f)
				{
					m_PSAlphaFlg = false;
				}
			}
			m_PressStartLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_PSAlpha));
		}
	}

	void Title::Animation()
	{
		//0
		float ElaTime = App::GetApp()->GetElapsedTime();

		//1,2
		auto TitleTra = m_TitleLogo->GetComponent<Transform>();
		auto PressTra = m_PressStartLogo->GetComponent<Transform>();

		Vector3 Titlepos = TitleTra->GetPosition();
		Vector3 Presspos = PressTra->GetPosition();

		//2
		/*調整用
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		Vector2 velo;
		Vector3 pos;
		Vector3 scale;
		auto key = App::GetApp()->GetInputDevice().GetKeyState();
		*/
		auto Char1Tra = m_Char1->GetComponent<Transform>();
		auto Char2Tra = m_Char2->GetComponent<Transform>();

		Vector3 Char1pos = Char1Tra->GetPosition();
		Vector3 Char2pos = Char2Tra->GetPosition();

		//3
		auto StageSeleLogoTra = m_StageSelectLogo->GetComponent<Transform>();
		auto ArrowRTra = m_ArrowR->GetComponent<Transform>();
		auto ArrowLTra = m_ArrowL->GetComponent<Transform>();

		Vector3 SSLpos = StageSeleLogoTra->GetPosition();
		Vector3 ArrowRpos = ArrowRTra->GetPosition();
		Vector3 ArrowLpos = ArrowLTra->GetPosition();

		//4
		auto StageImageTra = m_StageImage->GetComponent<Transform>();
		Vector3 SIscale = StageImageTra->GetScale();

		switch (m_AnimationState)
		{
			//0:1秒松
		case 0:
			m_time += ElaTime;
			if (m_time > 1.0f)
			{
				m_time = 0;
				m_AnimationState = 1;
			}
			break;

			//1:ロゴたちが上へ行く、キャラが出てくる直前まで
		case 1:
			if (Presspos.y < 400)
			{
				Titlepos.y += 1000 * ElaTime;
				Presspos.y += 1000 * ElaTime;

				TitleTra->SetPosition(Titlepos);
				PressTra->SetPosition(Presspos);
			}
			else
			{
				m_AnimationState = 2;
			}
			break;
			//2:キャラが下から出てきて文字が↑へ消える
		case 2:
			if (Presspos.y < 600)
			{
				Titlepos.y += 1000 * ElaTime;
				Presspos.y += 1000 * ElaTime;

				TitleTra->SetPosition(Titlepos);
				PressTra->SetPosition(Presspos);
			}
			//１体目動かす
			if (Char1pos.y < -158)
			{
				Char1pos.y += 1000 * ElaTime;
				Char1Tra->SetPosition(Char1pos);
			}
			else
			{
				Char1pos.y = -158;
				Char1Tra->SetPosition(Char1pos);
			}
			//２体目動かす
			if (Char2pos.y < -158)
			{
				Char2pos.y += 1000 * ElaTime;
				Char2Tra->SetPosition(Char2pos);
			}
			else
			{
				Char2pos.y = -158;
				Char2Tra->SetPosition(Char2pos);
			}
			
			if (Presspos.y >= 600 && Char1pos.y == -158 && Char2pos.y == -158)
			{
				m_AnimationState = 3;
			}
			/*位置調整用
			if (CntlVec[0].fThumbLX > 0.1f || CntlVec[0].fThumbLX < -0.1f ||
				CntlVec[0].fThumbLY > 0.1f || CntlVec[0].fThumbLY < -0.1f)
			{
				velo = Vector2(CntlVec[0].fThumbLX, CntlVec[0].fThumbLY);
				pos = m_Char1->GetComponent<Transform>()->GetPosition();
				pos.x += velo.x * 2;
				pos.y += velo.y * 2;
				m_Char1->GetComponent<Transform>()->SetPosition(pos);
			}
			if (key.m_bPushKeyTbl[VK_UP])
			{
				scale = m_Char1->GetComponent<Transform>()->GetScale();
				scale.y += 50 * ElaTime;
				m_Char1->GetComponent<Transform>()->SetScale(scale);
			}
			if (key.m_bPushKeyTbl[VK_DOWN])
			{
				scale = m_Char1->GetComponent<Transform>()->GetScale();
				scale.y += -50 * ElaTime;
				m_Char1->GetComponent<Transform>()->SetScale(scale);
			}
			if (key.m_bPushKeyTbl[VK_RIGHT])
			{
				scale = m_Char1->GetComponent<Transform>()->GetScale();
				scale.x += 50 * ElaTime;
				m_Char1->GetComponent<Transform>()->SetScale(scale);
			}
			if (key.m_bPushKeyTbl[VK_LEFT])
			{
				scale = m_Char1->GetComponent<Transform>()->GetScale();
				scale.x += -50 * ElaTime;
				m_Char1->GetComponent<Transform>()->SetScale(scale);
			}*/
			break;
			//3:ステージセレクトロゴ下から来て、矢印左右から出る
		case 3:
			//ステージセレクトロゴ移動
			if (SSLpos.y < 432)
			{
				SSLpos.y += 2000 * ElaTime;
				StageSeleLogoTra->SetPosition(SSLpos);
			}
			else
			{
				SSLpos.y = 432;
				StageSeleLogoTra->SetPosition(SSLpos);
			}
			//矢印R移動
			if (ArrowRpos.x < 890)
			{
				ArrowRpos.x += 3000 * ElaTime;
				ArrowRTra->SetPosition(ArrowRpos);
			}
			else
			{
				ArrowRpos.x = 890;
				ArrowRTra->SetPosition(ArrowRpos);
			}
			//矢印L移動
			if (ArrowLpos.x > -890)
			{
				ArrowLpos.x += -3000 * ElaTime;
				ArrowLTra->SetPosition(ArrowLpos);
			}
			else
			{
				ArrowLpos.x = -890;
				ArrowLTra->SetPosition(ArrowLpos);
			}

			if (SSLpos.y == 432 && ArrowRpos.x == 890 && ArrowLpos.x == -890)
			{
				m_AnimationState = 4;
			}
			break;
			//ステージイメージをスケールアップで作成して終了
		case 4:
			if (SIscale.x < 1500)
			{
				SIscale *= 1.2f;
				StageImageTra->SetScale(SIscale);
			}
			else
			{
				SIscale.x = 1500;
				SIscale.y = 1500;
				StageImageTra->SetScale(SIscale);
				m_AnimationState = 5;
			}
			break;
			//ちょっと小さく
		case 5:
			if (SIscale.x > 1200)
			{
				SIscale *= 0.9f;
				StageImageTra->SetScale(SIscale);
			}
			else
			{
				SIscale.x = 1200;
				SIscale.y = 1200;
				StageImageTra->SetScale(SIscale);
				m_AnimationState = 6;
			}

			break;
			//終了
		case 6:
			SceneChange();
			break;
		default:
			break;
		}

		//wstring txt = Util::IntToWStr(m_AnimationState);
		/*位置調整用
		if (m_AnimationState == 2)
		{
			Vector3 postxt = m_Char1->GetComponent<Transform>()->GetPosition();
			Vector3 scaletxt = m_Char1->GetComponent<Transform>()->GetScale();
			txt += L"\nPOS_X = " + Util::FloatToWStr(postxt.x) + L"\nPOS_Y = " + Util::FloatToWStr(postxt.y);
			txt += L"\nSCALE_X = " + Util::FloatToWStr(scaletxt.x) + L"\nSCALE_Y = " + Util::FloatToWStr(scaletxt.y);
			
		}
		*/
		/*
		if (m_AnimationState == 3)
		{
			txt += L"\nLX = " + Util::FloatToWStr(ArrowLpos.x);
			txt += L"\nRX = " + Util::FloatToWStr(ArrowRpos.x);
		}
		*/
		/*
		if (m_AnimationState == 4)
		{
			txt += L"\nXSc = " + Util::FloatToWStr(SIscale.x);
			txt += L"\nYSc = " + Util::FloatToWStr(SIscale.x);
		}
		*/
		//m_String->GetComponent<StringSprite>()->SetText(txt);

	}


}