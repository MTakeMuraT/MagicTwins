#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void StageSelect::CreateResourses()
	{
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = DataDir + L"StageSelectLogo.png";
		App::GetApp()->RegisterTexture(L"STAGESELECTLOGO_TX", strTexture);
		strTexture = DataDir + L"TitleBack.png";
		App::GetApp()->RegisterTexture(L"SELECTBACK_TX", strTexture);
		//左矢印画像(仮)
		strTexture = DataDir + L"Left.png";
		App::GetApp()->RegisterTexture(L"LEFT_TX", strTexture);
		//右矢印画像(仮)
		strTexture = DataDir + L"Right.png";
		App::GetApp()->RegisterTexture(L"RIGHT_TX", strTexture);
		//Bボタン
		strTexture = DataDir + L"ButtonA.png";
		App::GetApp()->RegisterTexture(L"ABUTTON_TX", strTexture);
		//決定ロゴ
		strTexture = DataDir + L"Kettei.png";
		App::GetApp()->RegisterTexture(L"KETTEI_TX", strTexture);
		//ステージイメージ枠
		strTexture = DataDir + L"Frame.png";
		App::GetApp()->RegisterTexture(L"FRAME_TX", strTexture);


		//数字
		strTexture = DataDir + L"Number.png";
		App::GetApp()->RegisterTexture(L"NUMBER_TX", strTexture);


		//暗転用の黒
		strTexture = DataDir + L"Black.png";
		App::GetApp()->RegisterTexture(L"BLACK_TX", strTexture);

		//目の画像
		strTexture = DataDir + L"eye_1.png";
		App::GetApp()->RegisterTexture(L"EYE_0_TX", strTexture);
		strTexture = DataDir + L"eye_2.png";
		App::GetApp()->RegisterTexture(L"EYE_1_TX", strTexture);
		strTexture = DataDir + L"eye_3.png";
		App::GetApp()->RegisterTexture(L"EYE_2_TX", strTexture);
		//2
		strTexture = DataDir + L"eye2_1.png";
		App::GetApp()->RegisterTexture(L"EYE2_0_TX", strTexture);
		strTexture = DataDir + L"eye2_2.png";
		App::GetApp()->RegisterTexture(L"EYE2_1_TX", strTexture);
		strTexture = DataDir + L"eye2_3.png";
		App::GetApp()->RegisterTexture(L"EYE2_2_TX", strTexture);

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

		////文字列を付ける(仮)
		//auto Stp = SelectBack->AddComponent<StringSprite>();
		//Stp->SetText(L"");
		//Stp->SetTextRect(Rect2D<float>(1024.0f, -256.0f, 1024.0f, 960.0f));
		//Stp->SetFontColor(Color4(1, 1, 0.4f, 1));
		//Stp->SetFont(L"", 100);

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

	void StageSelect::CreateStageImageFrame()
	{
		auto StageImage = AddGameObject<GameObject>();
		auto SITranform = StageImage->AddComponent<Transform>();
		SITranform->SetPosition(0,0,0);
		SITranform->SetScale(1200,1200,1);
		SITranform->SetRotation(0, 0, 0);

		auto SIDraw = StageImage->AddComponent<PCTSpriteDraw>();
		SIDraw->SetTextureResource(L"FRAME_TX");

		StageImage->SetAlphaActive(true);

		StageImage->SetDrawLayer(3);
	}

	void StageSelect::SceneChange()
	{
		if (GetSharedGameObject<Black>(L"BlackObj", false)->GetBlackFinish())
		{
			if (m_StageNum != 0)
			{
				auto ScenePtr = App::GetApp()->GetScene<Scene>();
				ScenePtr->SetStageNum(m_StageNum);
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameStage");
			}
			else
			{
				auto ScenePtr = App::GetApp()->GetScene<Scene>();
				ScenePtr->SetStageNum(m_StageNum);
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"Tutorial");
			}
		}
	}

	void StageSelect::CreateButtons()
	{
		//Aボタン作成
		auto obj1 = AddGameObject<GameObject>();
		auto OT1 = obj1->AddComponent<Transform>();
		OT1->SetPosition(300, -400, 0);
		OT1->SetScale(100, 100, 1);
		OT1->SetRotation(0, 0, 0);
		auto OD1 = obj1->AddComponent<PCTSpriteDraw>();
		OD1->SetTextureResource(L"ABUTTON_TX");
		obj1->SetAlphaActive(true);
		obj1->SetDrawLayer(3);

		auto obj2 = AddGameObject<GameObject>();
		auto OT2 = obj2->AddComponent<Transform>();
		OT2->SetPosition(450, -400, 0);
		OT2->SetScale(250, 160, 1);
		OT2->SetRotation(0, 0, 0);
		auto OD2 = obj2->AddComponent<PCTSpriteDraw>();
		OD2->SetTextureResource(L"KETTEI_TX");
		obj2->SetAlphaActive(true);
		obj2->SetDrawLayer(3);

		/*
		auto obj2 = AddGameObject<GameObject>();
		auto OT2 = obj2->AddComponent<Transform>();
		OT2->SetPosition(500, -400, 0);
		OT2->SetScale(100, 100, 1);
		OT2->SetRotation(0, 0, 0);
		auto OD2 = obj2->AddComponent<PCTSpriteDraw>();
		OD2->SetTextureResource(L"ABUTTON_TX");
		obj2->SetAlphaActive(true);
		obj2->SetDrawLayer(3);
		*/
	}

	//左矢印(仮)
	void StageSelect::Left()
	{
		auto Left = AddGameObject<GameObject>();
		Left->AddComponent<Transform>();
		auto PtrTransform = Left->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(-890, 0, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(150, 150, 1);

		//スプライトを付ける
		auto PtrSprite = Left->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"LEFT_TX");

		SetSharedGameObject(L"Left", Left);

		Left->SetDrawLayer(2);

		auto PtrAction = Left->AddComponent<Action>();
		PtrAction->AddMoveBy(1.5, Vector3(100, 0, 0));
		PtrAction->AddMoveBy(1.5, Vector3(-100, 0, 0));
		PtrAction->SetLooped(true);
		PtrAction->Run();

		//透明度反映
		Left->SetAlphaActive(true);
		//GetSharedGameObject<GameObject>(L"TiBa", false)->GetComponent<StringSprite>()->SetText(L"0");

	}

	//右矢印(仮)
	void StageSelect::Right()
	{
		auto Right = AddGameObject<GameObject>();
		Right->AddComponent<Transform>();
		auto PtrTransform = Right->GetComponent<Transform>();
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
		PtrTransform->SetPosition(890, 0, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetScale(150, 150, 1);

		//スプライトを付ける
		auto PtrSprite = Right->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"RIGHT_TX");

		SetSharedGameObject(L"Right", Right);

		Right->SetDrawLayer(2);

		auto PtrAction = Right->AddComponent<Action>();
		PtrAction->AddMoveBy(1.5, Vector3(-100, 0, 0));
		PtrAction->AddMoveBy(1.5, Vector3(100, 0, 0));
		PtrAction->SetLooped(true);
		PtrAction->Run();

		//透明度反映
		Right->SetAlphaActive(true);
		//GetSharedGameObject<GameObject>(L"TiBa", false)->GetComponent<StringSprite>()->SetText(L"0");
	}

	//ステージイメージ作成
	void StageSelect::CreateStageImage()
	{
		//画像用意
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture;
		for (int i = 0; i <= 10; i++)
		{
			wstring num = Util::IntToWStr(i);

			wstring pathtxt = DataDir + L"StageImage/Stage_";
			pathtxt += num + L".png";
			strTexture = DataDir + pathtxt;

			wstring numtxt = L"STAGEIMAGE_";
			numtxt += Util::IntToWStr(i) + L"_TX";
			App::GetApp()->RegisterTexture(numtxt, strTexture);

		}

		//生成
		auto ImageP = AddGameObject<GameObject>();
		//座標とか指定
		auto ImageTrans = ImageP->AddComponent<Transform>();
		ImageTrans->SetPosition(5, 2, 0);
		ImageTrans->SetRotation(0, 0, 0);
		ImageTrans->SetScale(955, 565, 1);

		//画像貼り付け
		auto ImageDraw = ImageP->AddComponent<PCTSpriteDraw>();
		ImageDraw->SetTextureResource(L"STAGEIMAGE_0_TX");

		//透明度
		ImageP->SetAlphaActive(true);
		//レイヤー
		ImageP->SetDrawLayer(4);

		//アクセスできるメンバ変数に入れとく
		m_StageImage = ImageP;


	}

	//ステージイメージ回転
	void StageSelect::RotStageImage()
	{

		Vector3 scale = m_StageImage->GetComponent<Transform>()->GetScale();

		//m_SIHalfFlgがfalseなら小さく、trueなら大きく
		if (!m_SIHalfFlg)
		{
			scale.x += -10000 * App::GetApp()->GetElapsedTime();
			//線になったらテクスチャ切り替え
			if (scale.x < 0)
			{
				//テクスチャ張り替え
				wstring txt = L"STAGEIMAGE_";
				txt += Util::IntToWStr(m_StageNum) + L"_TX";
				m_StageImage->GetComponent<PCTSpriteDraw>()->SetTextureResource(txt);

				//スケールとフラグ反転
				scale.x = 0;
				m_SIHalfFlg = true;
			}
		}
		else
		{
			scale.x += 10000 * App::GetApp()->GetElapsedTime();
			if (scale.x > 955)
			{
				scale.x = 955;
				m_SIHalfFlg = false;
				m_StageImageRotFlg = false;
			}

		}

		m_StageImage->GetComponent<Transform>()->SetScale(scale);

		//wstring txt = Util::FloatToWStr(scale.x);
		//GetSharedGameObject<GameObject>(L"StringObject", false)->GetComponent<StringSprite>()->SetText(txt);
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
			//ボタン作成
			CreateButtons();
			//ステージイメージフレーム
			CreateStageImageFrame();
			//ステージイメージ作成
			CreateStageImage();
			//左矢印(仮)
			Left();
			//右矢印(仮)
			Right();
			//左右シーン遷移(仮)
			m_StageNum = 0;
			m_flag = true;

			//SEマネージャー
			SetSharedGameObject(L"SEM", AddGameObject<SEManager>());

			//文字列
			//auto obj = AddGameObject<GameObject>();
			//auto Stp = obj->AddComponent<StringSprite>();
			//Stp->SetText(L"0");
			//Stp->SetTextRect(Rect2D<float>(1024.0f, -1024.0f, 1024.0f, 960.0f));
			//Stp->SetFont(L"", 100);
			//Stp->SetFontColor(Color4(1, 1, 0.4f, 1));
			//obj->SetDrawLayer(10);
			//SetSharedGameObject(L"StringObject",obj);
			auto NumberP = AddGameObject<NumberSprite>(0, Vector2(25, -400.0f), Vector2(128, 128), 4);
			SetSharedGameObject(L"NumberSprite", NumberP);

			//チュートリアルみたかどうか判定して見てたら1にする
			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			if (ScenePtr->GetTutorialOpenFlg())
			{
				//数字1
				NumberP->SetNum(1);
				m_StageNum = 1;
				m_StageImage->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"STAGEIMAGE_1_TX");

			}

			//雲追加
			AddGameObject<Cloud>(Vector3(300, 300, 1), 5, 1,0);

			//キャラ目
			AddGameObject<CharEye>(Vector3(-706, -158, 0), false);
			AddGameObject<CharEye>(Vector3(684, -158, 0), true);

		}
		catch (...) {
			throw;
		}

	}

	void StageSelect::OnUpdate()
	{
		if (!m_SelectFlg)
		{
			//左右でシーン遷移(仮)
			//auto ShareObject = GetSharedGameObject<GameObject>(L"StringObject", false);
			//auto ShareString = ShareObject->GetComponent<StringSprite>();

			//wstring sceneNum(L"");


			//*テスト用
			auto key = App::GetApp()->GetInputDevice().GetKeyState();
			if (key.m_bPressedKeyTbl[VK_SPACE])
			{
				//暗転幕作成していったん終わらせる
				auto BlackObj = AddGameObject<Black>();
				BlackObj->StartBlack();
				BlackObj->SetDrawLayer(10);
				SetSharedGameObject(L"BlackObj", BlackObj);
				m_SelectFlg = true;
				return;

			}
			//*テスト用

			//ステージイメージが回転してるとき以外操作可
			if (!m_StageImageRotFlg)
			{

				auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
				if (CntlVec[0].bConnected)
				{
					//スタートとバック同時押してタイトルに
					if (CntlVec[0].wButtons & XINPUT_GAMEPAD_START && CntlVec[0].wButtons & XINPUT_GAMEPAD_BACK)
					{
						auto ScenePtr = App::GetApp()->GetScene<Scene>();
						PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"Title");
					}

					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B ||
						CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
					{
						//暗転幕作成していったん終わらせる
						auto BlackObj = AddGameObject<Black>();
						BlackObj->StartBlack();
						SetSharedGameObject(L"BlackObj", BlackObj);
						m_SelectFlg = true;
						//SE再生
						GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("Select");
						return;
					}
					//左右シーン遷移(仮)
					if (CntlVec[0].fThumbLX > 0 && m_flag&&m_StageNum < m_MaxStageNum)
					{

						m_StageNum++;
						m_flag = false;
						m_StageImageRotFlg = true;
					}
					if (CntlVec[0].fThumbLX < 0 && m_flag&&m_StageNum>0)
					{
						m_StageNum--;
						m_flag = false;
						m_StageImageRotFlg = true;
					}
					if (CntlVec[0].fThumbLX == 0)
					{
						m_flag = true;
					}

				}
				if (!m_flag)
				{
					GetSharedGameObject<NumberSprite>(L"NumberSprite", false)->SetNum(m_StageNum);
				}
				auto Left = GetSharedGameObject<GameObject>(L"Left");

				if (m_StageNum != 0)
				{
					Left->SetDrawActive(true);
				}

				else {
					/*if (m_SceneNum == 1)
					{
						auto Left = GetSharedGameObject<GameObject>(L"Left");
						Left->SetDrawActive(true);
					}*/
					Left->SetDrawActive(false);
				}

				auto Right = GetSharedGameObject<GameObject>(L"Right");
				if (m_StageNum != m_MaxStageNum)
				{
					Right->SetDrawActive(true);
				}
				else
				{
					Right->SetDrawActive(false);
				}
			}
			//ステージイメージ回転してるフラグ立ってたら関数呼ぶ
			else
			{
				RotStageImage();
			}
		}
		else
		{
			SceneChange();
		}
	}


	//--------------------------------------------------------------------------------------
	//	class CharEye : public GameObject;
	//	用途: キャラの目
	//	設定した時間ごとに瞬きするか判定しながら瞬き
	//--------------------------------------------------------------------------------------
	CharEye::CharEye(const shared_ptr<Stage>& StagePtr,Vector3 pos,bool flg):
		GameObject(StagePtr),
		m_Pos(pos),
		m_2PlayerFlg(flg)
	{}

	void CharEye::OnCreate()
	{
		for (int i = 0; i <= 2; i++)
		{
			auto obj = GetStage()->AddGameObject<GameObject>();
			auto Trans = obj->AddComponent<Transform>();
			Trans->SetPosition(m_Pos);
			Trans->SetScale(788,786,1);
			Trans->SetRotation(0,0,0);
			auto Draw = obj->AddComponent<PCTSpriteDraw>();
			if (!m_2PlayerFlg)
			{
				wstring txt = L"EYE_";
				txt += Util::IntToWStr(i) + L"_TX";
				Draw->SetTextureResource(txt);
			}
			else
			{
				wstring txt = L"EYE2_";
				txt += Util::IntToWStr(i) + L"_TX";
				Draw->SetTextureResource(txt);
			}

			obj->SetAlphaActive(true);
			//一個目以外消す
			if (i >= 1)
			{
				obj->SetDrawActive(false);
			}
			obj->SetDrawLayer(2);
			m_Eyes.push_back(obj);
		}
	}

	void CharEye::OnUpdate()
	{
		if (m_EyeCloseFlg)
		{
			EyeClose();
		}
		else
		{
			m_CountTime += App::GetApp()->GetElapsedTime();
			if (m_CountTime > m_IntarvalEyeTime)
			{
				m_CountTime = 0;
				//確率当てる
				if (rand() % 100 < m_Par)
				{
					m_EyeCloseFlg = true;
				}
			}
		}
	}

	void CharEye::EyeClose()
	{
		m_CountTime += App::GetApp()->GetElapsedTime();
		if (m_CountTime > m_EyeCloseTime)
		{
			m_CountTime = 0;
			m_EyeCloseState++;
			switch (m_EyeCloseState)
			{
				//目半閉じ
			case 1:
				m_Eyes[0]->SetDrawActive(false);
				m_Eyes[1]->SetDrawActive(true);
				break;
				//目閉じ
			case 2:
				m_Eyes[1]->SetDrawActive(false);
				m_Eyes[2]->SetDrawActive(true);
				break;
				//目開け
			case 3:
				m_Eyes[2]->SetDrawActive(false);
				m_Eyes[0]->SetDrawActive(true);

				m_EyeCloseFlg = false;
				m_EyeCloseState = 0;
				break;
			}
		}

	}
}

