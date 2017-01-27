/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	class Player : public GameObject;
	//	用途: プレイヤー
	//--------------------------------------------------------------------------------------
	//構築と破棄
	Player::Player(const shared_ptr<Stage>& StagePtr, Vector3 pos, bool Active, string name) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_myName(name),
		m_ActiveFlg(Active)
	{}

	//初期化
	void Player::OnCreate() {
		//初期位置などの設定
		auto Ptr = GetComponent<Transform>();
		Ptr->SetScale(0.25f, 0.25f, 0.25f);
		Ptr->SetRotation(0, 0, 0);
		Ptr->SetPosition(m_InitPos);


		//Rigidbodyをつける
		auto PtrRedid = AddComponent<Rigidbody>();
		//反発係数は0.5（半分）
		PtrRedid->SetReflection(0.5f);

		//重力をつける
		auto PtrGravity = AddComponent<Gravity>();

		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionSphere>();
		PtrCol->SetIsHitAction(IsHitAction::AutoOnObjectRepel);

		// モデルとトランスフォームの間の差分行列
		float angle = -90 * (3.14159265f /180);
		Matrix4X4 SpanMat;
		SpanMat.DefTransformation(
			Vector3(1.0f, 1.0f, 1.0f),
			Vector3(0.0f, angle, 0.0f),
			Vector3(0.0f, 1.0f, 0.0f)
			);



		if (m_myName == "Player1")
		{
			// モデルとトランスフォームの間の差分行列
			angle = -90 * (3.14159265f / 180);
			SpanMat.DefTransformation(
				Vector3(1.5f, 1.5f, 1.5f),
				Vector3(0.0f, angle, 0.0f),
				Vector3(0.0f, 1.0f, 0.0f)
				);

			//影をつける（シャドウマップを描画する）
			auto ShadowPtr = AddComponent<Shadowmap>();
			//影の形（メッシュ）を設定
			ShadowPtr->SetMeshResource(L"Character01_MESH");
			ShadowPtr->SetMeshToTransformMatrix(SpanMat);

			//描画コンポーネントの設定
			auto PtrDraw = AddComponent<PNTBoneModelDraw>();
			//描画するメッシュを設定
			PtrDraw->SetMeshResource(L"Character01_MESH");
			PtrDraw->SetMeshToTransformMatrix(SpanMat);

			//アニメーション追加
			PtrDraw->AddAnimation(L"walk", 0, 20, true, 30);
			PtrDraw->AddAnimation(L"attack", 21, 24, false, 30);
			PtrDraw->AddAnimation(L"wait", 40, 130, true, 30);

			/*
			//描画コンポーネントの設定
			auto PtrDraw = AddComponent<PNTStaticModelDraw>();
			//描画するメッシュを設定
			PtrDraw->SetMeshResource(L"Player1_Model");
			PtrDraw->SetMeshToTransformMatrix(SpanMat);
			*/

			//魔法作成
			auto magicBoal = GetStage()->AddGameObject<MagicBoal>(Vector3(-100, -5.0f, 0), 1);
			GetStage()->SetSharedGameObject(L"MagicBoal1",magicBoal);
			//アップデート止めるグループに追加
			GetStage()->GetSharedObjectGroup(L"SetUpdateObj")->IntoGroup(magicBoal);

			//カメラモードじゃないとき
			if (!m_CameraMode)
			{
				//ライフ表示----------------------------------------
				auto obj = GetStage()->AddGameObject<GameObject>();
				auto objDraw = obj->AddComponent<PCTSpriteDraw>();
				objDraw->SetTextureResource(L"LIFE3_TX");

				auto objtrans = obj->AddComponent<Transform>();
				//1920,1080
				//960,540
				objtrans->SetPosition(-550, 420, 0);
				objtrans->SetRotation(0, 0, 0);
				objtrans->SetScale(400, 130, 1);
				obj->SetAlphaActive(true);
				obj->SetDrawLayer(3);
				m_LifeSprite = obj;
				//ライフ表示----------------------------------------

				//魔法UI表示----------------------------------------
				//片方だけ作れば十分
				auto MUI = GetStage()->AddGameObject<GameObject>();
				auto MUIDraw = MUI->AddComponent<PCTSpriteDraw>();
				MUIDraw->SetTextureResource(L"MAGICUI_TX");
				auto MUIT = MUI->AddComponent<Transform>();
				MUIT->SetPosition(0, 420, 0);
				MUIT->SetRotation(0, 0, 0);
				MUIT->SetScale(220, 220, 0);
				MUI->SetAlphaActive(true);
				MUI->SetDrawLayer(3);
				m_MagicUI = MUI;

				auto MUI2 = GetStage()->AddGameObject<GameObject>();
				auto MUIDraw2 = MUI2->AddComponent<PCTSpriteDraw>();
				MUIDraw2->SetTextureResource(L"NULLUI_TX");
				auto MUIT2 = MUI2->AddComponent<Transform>();
				MUIT2->SetPosition(0, 420, 0);
				MUIT2->SetRotation(0, 0, 0);
				MUIT2->SetScale(150, 150, 0);
				MUI2->SetAlphaActive(true);
				MUI2->SetDrawLayer(4);
				m_MagicUIIn = MUI2;
				//魔法UI表示----------------------------------------


				//キャラUI表示--------------------------------------
				auto CHU = GetStage()->AddGameObject<GameObject>();
				auto CHUD = CHU->AddComponent<PCTSpriteDraw>();
				CHUD->SetTextureResource(L"CHARA1UI_TX");
				auto CHUT = CHU->AddComponent<Transform>();
				CHUT->SetPosition(-850, 420, 0);
				CHUT->SetRotation(0, 0, 0);
				CHUT->SetScale(200, 200, 0);
				CHU->SetAlphaActive(true);
				CHU->SetDrawLayer(3);
				CHU->SetDrawActive(true);
				m_CharaUI = CHU;
				//キャラUI表示--------------------------------------


				//ターゲットモード照準(ステージに保存)--------------------------------------
				auto TargetAim = GetStage()->AddGameObject<GameObject>();
				auto TAT = TargetAim->AddComponent<Transform>();
				TAT->SetPosition(0, 0, 0);
				float TAangle = 45 * 3.14159265f / 180;
				TAT->SetRotation(TAangle, 0, 0);
				TAT->SetScale(1.5f, 1.5f, 1.5f);
				auto TAD = TargetAim->AddComponent<PNTStaticDraw>();
				TAD->SetTextureResource(L"TARGETAIM_TX");
				TAD->SetMeshResource(L"DEFAULT_SQUARE");
				TargetAim->SetAlphaActive(true);
				TargetAim->SetDrawLayer(2);
				TargetAim->SetDrawActive(false);
				GetStage()->SetSharedGameObject(L"TargetAim", TargetAim);
				//ターゲットモード照準(ステージに保存)--------------------------------------

			}
		}
		else if (m_myName == "Player2")
		{
			//影をつける（シャドウマップを描画する）
			auto ShadowPtr = AddComponent<Shadowmap>();
			//影の形（メッシュ）を設定
			ShadowPtr->SetMeshResource(L"Character02_MESH");

			SpanMat.DefTransformation(
				Vector3(1.5f, 1.5f, 1.5f),
				Vector3(0.0f, angle, 0.0f),
				Vector3(0.0f, 1.0f, 0.0f)
				);

			ShadowPtr->SetMeshToTransformMatrix(SpanMat);


			//描画コンポーネントの設定
			auto PtrDraw = AddComponent<PNTBoneModelDraw>();
			//描画するメッシュを設定
			PtrDraw->SetMeshResource(L"Character02_MESH");
			PtrDraw->SetMeshToTransformMatrix(SpanMat);

			//アニメーション追加
			PtrDraw->AddAnimation(L"walk", 0, 20, true, 30);
			PtrDraw->AddAnimation(L"attack", 20, 23, false, 30);
			PtrDraw->AddAnimation(L"wait", 40, 130, true, 30);


			//魔法作成
			auto magicBoal = GetStage()->AddGameObject<MagicBoal>(Vector3(-100, -5.0f, 0), 2);
			GetStage()->SetSharedGameObject(L"MagicBoal2", magicBoal);
			//アップデート止めるグループに追加
			GetStage()->GetSharedObjectGroup(L"SetUpdateObj")->IntoGroup(magicBoal);

			/*
			//ライフ表示
			auto obj = GetStage()->AddGameObject<GameObject>();
			auto objDraw = obj->AddComponent<PCTSpriteDraw>();
			objDraw->SetTextureResource(L"LIFE3_TX");

			auto objtrans = obj->AddComponent<Transform>();
			//1920,1080
			//960,540
			objtrans->SetPosition(700, 420, 0);
			objtrans->SetRotation(0, 0, 0);
			objtrans->SetScale(400, 200, 1);
			obj->SetAlphaActive(true);
			obj->SetDrawLayer(3);
			m_LifeSprite = obj;

			*/
			//カメラモードじゃないとき
			if (!m_CameraMode)
			{
				//ライフ表示----------------------------------------
				auto obj = GetStage()->AddGameObject<GameObject>();
				auto objDraw = obj->AddComponent<PCTSpriteDraw>();
				objDraw->SetTextureResource(L"LIFE3_TX");

				auto objtrans = obj->AddComponent<Transform>();
				//1920,1080
				//960,540
				objtrans->SetPosition(-550, 420, 0);
				objtrans->SetRotation(0, 0, 0);
				objtrans->SetScale(400, 130, 1);
				obj->SetAlphaActive(true);
				obj->SetDrawLayer(3);

				obj->SetDrawActive(false);
				m_LifeSprite = obj;
				//ライフ表示----------------------------------------

				//キャラUI表示--------------------------------------
				auto CHU = GetStage()->AddGameObject<GameObject>();
				auto CHUD = CHU->AddComponent<PCTSpriteDraw>();
				CHUD->SetTextureResource(L"CHARA2UI_TX");
				auto CHUT = CHU->AddComponent<Transform>();
				CHUT->SetPosition(-850, 420, 0);
				CHUT->SetRotation(0, 0, 0);
				CHUT->SetScale(200, 200, 0);
				CHU->SetAlphaActive(true);
				CHU->SetDrawLayer(3);
				CHU->SetDrawActive(false);
				m_CharaUI = CHU;
				//キャラUI表示--------------------------------------

			}
		}


		//文字列をつける
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 200.0f, 640.0f, 480.0f));
		PtrString->SetFont(L"", 80);

		//透明処理
		SetAlphaActive(true);

		//カメラ関連
		//向いてるとこ記憶
		m_CameraTargetVec = GetComponent<Transform>()->GetPosition();
		//座標記憶
		auto View = GetStage()->GetView();
		auto CameraP = View->GetTargetCamera();
		m_CameraPos = m_CameraTargetVec;
		m_CameraPos += Vector3(0, 5, -5);

		//暗転用幕--------------------------------------
		auto BlackP = GetStage()->AddGameObject<GameObject>();
		auto BlackPT = BlackP->AddComponent<Transform>();
		BlackPT->SetPosition(0, 0, 0);
		BlackPT->SetScale(1920, 1080, 1);
		BlackPT->SetRotation(0, 0, 0);

		auto BlackPD = BlackP->AddComponent<PCTSpriteDraw>();
		BlackPD->SetTextureResource(L"BLACK_TX");
		BlackPD->SetDiffuse(Color4(1, 1, 1, 0));

		BlackP->SetAlphaActive(true);
		BlackP->SetDrawLayer(2);
		m_Black = BlackP;
		//暗転用幕--------------------------------------


		if (m_CameraMode)
		{
			m_CameraPos = Vector3(5, 5, -3);
			m_CameraTargetVec = Vector3(0, 0, 0);
		}
	}

	//更新
	void Player::OnUpdate() {
		//----------------------------------------
		/*
		if (m_myName == "Player1")
		{
			float angle = GetComponent<Transform>()->GetRotation().y;
			GetComponent<StringSprite>()->SetText(Util::FloatToWStr(angle));
		}
		*/
		//----------------------------------------
		//カメラモード
		if (m_CameraMode)
		{
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (CntlVec[0].bConnected)
			{

				auto View = GetStage()->GetView();
				auto CameraP = View->GetTargetCamera();

				float speed = 1;
				//右肩ボタンで低速化
				if (CntlVec[0].wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
				{
					speed = 0.5f;
				}

				//移動入力
				if (abs(CntlVec[0].fThumbLX) > 0.1f || abs(CntlVec[0].fThumbLY) > 0.1f)
				{
					Vector2 InputXY = Vector2(CntlVec[0].fThumbLX, CntlVec[0].fThumbLY);
					InputXY *= 0.3f * speed;
					m_CameraPos += Vector3(InputXY.x,0, InputXY.y);
					m_CameraTargetVec += Vector3(InputXY.x, 0, InputXY.y);

				}
				if (abs(CntlVec[0].fThumbRX) > 0.1f || abs(CntlVec[0].fThumbRY) > 0.1f)
				{
					Vector2 InputXY = Vector2(CntlVec[0].fThumbRX, CntlVec[0].fThumbRY);
					InputXY *= 0.3f * speed;
					m_CameraPos += Vector3(InputXY.x, 0, InputXY.y);
				}
				//十字キー上でカメラ↑行く
				if (abs(CntlVec[0].wButtons & XINPUT_GAMEPAD_DPAD_UP))
				{
					m_CameraPos += Vector3(0, 0.1f * speed, 0);
				}
				//十字キー下でカメラ↓行く
				if (abs(CntlVec[0].wButtons & XINPUT_GAMEPAD_DPAD_DOWN))
				{
					m_CameraPos += Vector3(0, -0.1f * speed, 0);
				}


				CameraP->SetAt(m_CameraTargetVec);
				CameraP->SetEye(m_CameraPos);
			}
			return;
		}
		//死んだフラグ立ってたら
		if (m_DieFlg)
		{
			if (m_BlackDie->GetBlackFinish())
			{
				//ゲームオーバーに遷移
				auto ScenePtr = App::GetApp()->GetScene<Scene>();
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameOver");
			}
			return;
		}
		if (m_LifeFlg)
		{
			LifeDelete();
		}
		if (m_ChangeMagicUIFlg && m_myName == "Player1")
		{
			ChangeMagicAnima();
		}
		if (m_WarpFlg)
		{
			m_WarpFlg = false;
			//アタリ一式戻す
			GetComponent<CollisionSphere>()->SetUpdateActive(true);
			GetComponent<Rigidbody>()->SetUpdateActive(true);
			GetComponent<Gravity>()->SetUpdateActive(true);
		}
		if (m_endFrame)
		{
			m_endFrame = false;
			return;
		}
		//切り替えの暗転処理
		if (m_BlackFlg)
		{
			////HPバー後ろに
			//if (!m_ActiveFlg)
			//{
			//	Vector3 pos = m_LifeSprite->GetComponent<Transform>()->GetPosition();
			//	if (pos.x > -600)
			//	{
			//		pos.x += +100 * App::GetApp()->GetElapsedTime();
			//	}
			//	else
			//	{
			//		pos.x = -600;
			//	}
			//	if (pos.y > 350)
			//	{
			//		pos.y = -50 * App::GetApp()->GetElapsedTime();
			//	}
			//	else
			//	{
			//		pos.y = 350;
			//	}
			//	if (pos.x == -600 && pos.y == 350)
			//	{
			//		m_LifeSprite->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 0.5f));
			//	}
			//}
			//暗転状態なら
			if (m_BlackFlg)
			{
				if (m_BlackFlg2)
				{
					m_BlackAlpha += 1 * App::GetApp()->GetElapsedTime();
					m_Black->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));
					//暗くなったら
					if (m_BlackAlpha > 1.0f)
					{
						ChangeChar();
						m_BlackAlpha = 1.0f;
						m_Black->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));
					}
				}
				else
				{
					m_BlackAlpha += -1 * App::GetApp()->GetElapsedTime();
					m_Black->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));
					if (m_BlackAlpha < 0)
					{
						m_BlackAlpha = 0;
						m_Black->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));
						m_endFrame = false;
						m_BlackFlg = false;

					}
				}
			}
			return;
		}
		if (m_ActiveFlg)
		{
			CameraTarget();
			active();
		}
		//無敵中計算
		if (m_InviFlg)
		{
			Invincible();
		}
		
	}

	//操作できる状態
	void Player::active()
	{
		//*テスト用
		auto key = App::GetApp()->GetInputDevice().GetKeyState();
		Vector2 velocity;
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		bool flg = false;
		if (key.m_bPushKeyTbl[VK_RIGHT])
		{
			velocity.x = 1 * m_Speed * ElapsedTime;
			flg = true;
		}
		if (key.m_bPushKeyTbl[VK_LEFT])
		{
			velocity.x = -1 * m_Speed * ElapsedTime;		
			flg = true;
		}
		if (key.m_bPushKeyTbl[VK_UP])
		{
			velocity.y = 1 * m_Speed * ElapsedTime;
			flg = true;
		}
		if (key.m_bPushKeyTbl[VK_DOWN])
		{
			velocity.y = -1 * m_Speed * ElapsedTime;
			flg = true;
		}

		//コントローラーの入力XY
		auto TranP = GetComponent<Transform>();
		Vector3 Posi = TranP->GetPosition();
		Posi.x += velocity.x;
		Posi.z += velocity.y;
		TranP->SetPosition(Posi);

		if (flg)
		{
			//向きを得る				
			float angle = atan2(velocity.y, velocity.x);
			angle *= -1;
			TranP->SetRotation(Vector3(0, angle, 0));
		}

		if (key.m_bPressedKeyTbl[VK_TAB])
		{
			ChangeChar();
		}

		if (key.m_bPressedKeyTbl['S'])
		{
			ShotMagic();
		}
		//*テスト用

		//速度減衰
		if (m_velocity.x < 0.1f || m_velocity.x > -0.1f || m_velocity.y < 0.1f || m_velocity.y > -0.1f)
		{
			if (m_velocity.x != 0 && m_velocity.y != 0)
			{
				m_velocity.x = 0;
				m_velocity.y = 0;
			}
		}
		else
		{
			m_velocity *= 0.98f;
		}
		

		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			//魔法打ってる状態じゃなければ移動許可
			if (!m_ShotMagicStopFlg)
			{
				//入力が少しでもあったら
				if (CntlVec[0].fThumbLX > 0.1f || CntlVec[0].fThumbLX < -0.1f ||
					CntlVec[0].fThumbLY > 0.1f || CntlVec[0].fThumbLY < -0.1f)
				{
					float ElapsedTime = App::GetApp()->GetElapsedTime();
					//コントローラーの入力XY
					Vector2 inputXY = Vector2(CntlVec[0].fThumbLX, CntlVec[0].fThumbLY);
					auto TranP = GetComponent<Transform>();
					//座標直接弄る
					/*Vector3 Posi = TranP->GetPosition();
					inputXY *= ElapsedTime*m_Speed;
					Posi.x += inputXY.x;
					Posi.z += inputXY.y;
					TranP->SetPosition(Posi);
					*/

					m_velocity += inputXY * m_Speed;

					//向きを得る				
					float angle = atan2(inputXY.y, inputXY.x);
					angle *= -1;
					TranP->SetRotation(Vector3(0, angle, 0));

					//アニメーション更新
					auto PtrDraw = GetComponent<PNTBoneModelDraw>();
					if (PtrDraw->GetCurrentAnimation() == L"walk")
					{
						//アニメーション更新
						PtrDraw->UpdateAnimation(1.5f * ElapsedTime * ((abs(inputXY.x) + abs(inputXY.y)) / 2));
					}
					else
					{
						//アニメーション変更
						PtrDraw->ChangeCurrentAnimation(L"walk");
					}
				
					////アニメーションを更新する(コントローラーを傾けると動く)
					//auto PtrDraw = GetComponent<PNTBoneModelDraw>();
					//if (PtrDraw->GetCurrentAnimation() == L"walk") {
					//	//アニメーション更新
					//	PtrDraw->UpdateAnimation(ElapsedTime);
					//	//アニメーションを変えるとき
					//	//PtrDraw->ChangeCurrentAnimation(L"Default");
					//}
				}
				//移動入力がなければ
				else
				{
					//アニメーション
					auto PtrDraw = GetComponent<PNTBoneModelDraw>();
					if (PtrDraw->GetCurrentAnimation() == L"wait")
					{
						//アニメーション更新
						PtrDraw->UpdateAnimation(ElapsedTime);
					}
					else
					{
						//アニメーション変更
						PtrDraw->ChangeCurrentAnimation(L"wait");
					}
				}
				//ターゲットモード中
				if (m_TargetModeFlg)
				{
					TargetMode();
					if (CntlVec[0].wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
					{
					}
					else
					{
						m_TargetModeFlg = false;

						TargetModeRelease();

					}
				}
				
				
				//L肩ボタンで位置固定
				if (CntlVec[0].wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
				{
					//これ入れると押したとき停止
					//m_velocity = Vector2(0, 0);
					m_TargetModeFlg = true;
				}

				//if (CntlVec[0].wReleasedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
				//{
				//	m_TargetModeFlg = false;

				//	TargetModeRelease();
				//}

				//Xボタン押したら魔法発射
				if (CntlVec[0].wPressedButtons&XINPUT_GAMEPAD_A)
				{
					if (m_Magic != None)
					{
						//アニメーションとタイミング合わないから硬直後に発射する
						//魔法発射処理
						//ShotMagic();
						//硬直処理
						m_ShotMagicStopFlg = true;
					}
				}

			}
			//魔法打った後の硬直中処理
			else
			{
				//アニメーション更新
				auto PtrDraw = GetComponent<PNTBoneModelDraw>();
				if (PtrDraw->GetCurrentAnimation() == L"attack")
				{
					//アニメーション更新
					PtrDraw->UpdateAnimation(ElapsedTime);
				}
				else
				{
					//アニメーション変更
					PtrDraw->ChangeCurrentAnimation(L"attack");
				}

				//硬直後時間計測
				m_ShotMagicCountTime += ElapsedTime;

				if (m_ShotMagicCountTime > 0.3f && !m_ShotMagicFlg)
				{
					//魔法発射処理
					ShotMagic();
					m_ShotMagicFlg = true;
				}

				//一定時間たったら硬直解除
				if (m_ShotMagicCountTime > m_ShotStopTime)
				{
					m_ShotMagicStopFlg = false;	
					m_ShotMagicFlg = false;
					m_ShotMagicCountTime = 0;

					//アニメーション変更
					//停止するの防止
					PtrDraw->ChangeCurrentAnimation(L"wait");

				}
			}

			//キャラチェンジはいつでもできるようにする
			//Rトリガーでキャラ切り替え
			if (CntlVec[0].wPressedButtons&XINPUT_GAMEPAD_RIGHT_SHOULDER)
			{
				ChangeChar();
			}

		}

		//コンポーネントにやってもらう座標移動
		GetComponent<Rigidbody>()->SetVelocity(Vector3(m_velocity.x,0,m_velocity.y));


		//座標がある程度下になったら地形ダメージ与えて戻す
		if (GetComponent<Transform>()->GetPosition().y < -10)
		{
			GetComponent<Transform>()->SetPosition(m_InitPos);
			PlayerTerrainDamege();
		}
	}

	void Player::CameraTarget()
	{			
		//カメラ追従
		auto View = GetStage()->GetView();
		auto CameraP = View->GetTargetCamera();
		//カメラ移動
		Vector3 pos = GetComponent<Transform>()->GetPosition();
		/*
		//カメラとプレイヤーの差を計算
		pos.z += -5.0f;
		Vector3 Direction = pos - m_CameraPos;
		//横の判定
		if (abs(Direction.x) > m_CameraMove)
		{
			//マイナス(左側)
			if (Direction.x < 0)
			{
				Direction.x += m_CameraMove;
				//ずれてる分ずらす　
				m_CameraPos.x += Direction.x;
				m_CameraTargetVec.x += Direction.x;
			}
			//プラス(右側)
			else
			{
				Direction.x += -m_CameraMove;
				//ずれてる分ずらす　
				m_CameraPos.x += Direction.x;
				m_CameraTargetVec.x += Direction.x;
			}
		}

		//奥行方向(縦？)
		if (abs(Direction.z) > m_CameraMove-1.0f)
		{
			//マイナス(左側)
			if (Direction.z < 0)
			{
				Direction.z += m_CameraMove-1.0f;
				//ずれてる分ずらす　
				m_CameraPos.z += Direction.z;
				m_CameraTargetVec.z += Direction.z;
			}
			//プラス(右側)
			else
			{
				Direction.z += -m_CameraMove + 1.0f;
				//ずれてる分ずらす　
				m_CameraPos.z += Direction.z;
				m_CameraTargetVec.z += Direction.z;
			}
		}
		*/
		//m_CameraTargetVec.y = GetComponent<Transform>()->GetPosition().y;
		m_CameraTargetVec = pos;
		//m_CameraPos.y = m_CameraTargetVec.y + 5.0f;
		m_CameraPos = m_CameraTargetVec;
		m_CameraPos.y += 6.0f;
		m_CameraPos.z += -6.0f;
		CameraP->SetAt(m_CameraTargetVec);
		CameraP->SetEye(m_CameraPos);

		//ついでに背景も移動
		auto obj = GetStage()->GetSharedGameObject<GameObject>(L"Back",false);
		Vector3 PlayerPos = GetComponent<Transform>()->GetPosition();
		PlayerPos.y += -40;
		PlayerPos.z += 0;
		obj->GetComponent<Transform>()->SetPosition(PlayerPos);
		
	}

	//キャラチェンジ
	void Player::ChangeChar()
	{
		if (m_BlackFlg2)
		{
			m_BlackFlg2 = false;

			m_velocity = Vector2(0, 0);
			GetComponent<Rigidbody>()->SetVelocity(Vector3(0, 0, 0));

			//自分がどっちか判定
			if (m_myName == "Player1")
			{

				auto DPlayer = GetStage()->GetSharedGameObject<Player>(L"Player2", false);

				//ライフ透明化＆表示 キャラUIも
				m_LifeSprite->SetDrawActive(false);
				m_CharaUI->SetDrawActive(false);
				DPlayer->DispUI();

				//いなかったらエラー終了
				if (!DPlayer)
				{
					throw BaseException(
						L"Player2いません", L"", L""
						);
				}

				//あっち側起動
				DPlayer->SetActive(true);
				//こっち停止
				m_ActiveFlg = false;


				//カメラ移動
				auto View = GetStage()->GetView();
				auto CameraP = View->GetTargetCamera();

				Vector3 At = DPlayer->GetComponent<Transform>()->GetPosition();
				Vector3 pos = At;

				//カメラ移動するために情報送る
				pos.y += 5.0f;
				pos.z += -5.0f;

				DPlayer->SetCamera(At, pos);

				return;
			}
			else if (m_myName == "Player2")
			{
				auto DPlayer = GetStage()->GetSharedGameObject<Player>(L"Player1", false);

				//ライフ透明化＆表示 キャラUIも
				m_LifeSprite->SetDrawActive(false);
				m_CharaUI->SetDrawActive(false);
				DPlayer->DispUI();

				//いなかったらエラー終了
				if (!DPlayer)
				{
					throw BaseException(
						L"Player1いません", L"", L""
						);
				}

				//あっち側起動
				DPlayer->SetActive(true);
				//こっち停止
				m_ActiveFlg = false;



				//カメラ移動
				auto View = GetStage()->GetView();
				auto CameraP = View->GetTargetCamera();

				Vector3 At = DPlayer->GetComponent<Transform>()->GetPosition();
				Vector3 pos = At;

				//カメラ移動するために情報送る
				pos.y += 5.0f;
				pos.z += -5.0f;

				DPlayer->SetCamera(At, pos);
				return;
			}

			throw BaseException(
				L"交代ミスってます", L"", L""
				);
		}
		else
		{
			//暗転用
			m_BlackFlg = true;
			m_BlackFlg2 = true;
			m_ActiveFlg = false;
			m_velocity = Vector3(0, 0, 0);
			GetComponent<Rigidbody>()->SetVelocity(Vector3(m_velocity.x, 0, m_velocity.y));
		}
	}

	//操作状態操作
	void Player::SetActive(bool flg)
	{
		m_ActiveFlg = flg;
		m_endFrame = true;
	}

	//無敵時間中の関数
	void Player::Invincible()
	{
		float ElaTime = App::GetApp()->GetElapsedTime();

		//点滅
		m_Flashingtime += ElaTime;
		if (m_Flashingtime > m_FlashingTimeInterval)
		{
			m_FlashingFlg = !m_FlashingFlg;
			SetDrawActive(m_FlashingFlg);
			m_Flashingtime = 0;
		}
		//無敵時間カウント
		m_InvTime += ElaTime;

		//設定時間経過したら
		if (m_InvTime > m_InvincibleTime)
		{
			//無敵解除
			m_InvTime = 0;
			SetDrawActive(true);
			m_InviFlg = false;

			//点滅初期化
			m_Flashingtime = 0;
			m_FlashingFlg = false;
		}
	}

	//魔法を記憶するこれ常に1のほう呼ばれる
	void Player::SetMagic(MagicType MT)
	{
		if (m_myName == "Player1")
		{
			m_Magic = MT;
			//演出
			if (m_ChangeMagicUIFlg)
			{
				m_MagicUIIn->GetComponent<Transform>()->SetScale(m_CMUInitScale);
				//m_ChangeMagicUIFlg = true;
				m_CMUUp = false;
				m_CMUDown = false;
				m_CMUTime = 0;
			}
			else
			{
				m_ChangeMagicUIFlg = true;
			}
			GetStage()->GetSharedGameObject<Player>(L"Player2", false)->SetMagic(MT);
		}
		else if (m_myName == "Player2")
		{
			m_Magic = MT;
		}
		else
		{
			throw BaseException(
				L"誰やお前", L"PlayerのmyNameが", L"リスト外やねん"
				);
		}

		if (m_myName == "Player1")
		{

			//魔法UI変更
			switch (MT)
			{
			case None:
				m_MagicUIIn->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"NULLUI_TX");
				break;
			case Fire:
				m_MagicUIIn->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"FIREUI_TX");
				//SE再生
				GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("MagicGet");
				break;
			case IceFog:
				m_MagicUIIn->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"ICEUI_TX");
				//SE再生
				GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("MagicGet");
				break;
			case Wind:
				m_MagicUIIn->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"WINDUI_TX");
				//SE再生
				GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("MagicGet");
			default:
				break;
			}
		}
	}

	void Player::ChangeMagicAnima()
	{
		//でかくなる
		if (!m_CMUUp)
		{
			auto scale = m_MagicUIIn->GetComponent<Transform>()->GetScale();
			scale *= 1.1f;
			m_MagicUIIn->GetComponent<Transform>()->SetScale(scale);
			if (scale.x > m_CMUInitScale.x*2)
			{
				m_CMUUp = true;
			}
		}
		//でかくなった後一定時間計測
		else
		{
			m_CMUTime += App::GetApp()->GetElapsedTime();
			if (m_CMUTime > m_CMUCTime)
			{
				m_CMUDown = true;
			}
		}
		//小さくする
		if (m_CMUDown)
		{
			auto scale = m_MagicUIIn->GetComponent<Transform>()->GetScale();
			scale *= 0.9f;
			m_MagicUIIn->GetComponent<Transform>()->SetScale(scale);
			if (scale.x < m_CMUInitScale.x)
			{
				m_ChangeMagicUIFlg = false;
				m_CMUUp = false;
				m_CMUDown = false;
				m_MagicUIIn->GetComponent<Transform>()->SetScale(m_CMUInitScale);
				m_CMUTime = 0;
			}

		}
	}

	//魔法を発射する
	void Player::ShotMagic()
	{
		if (m_myName == "Player1")
		{
			GetStage()->GetSharedGameObject<MagicBoal>(L"MagicBoal1", false)->SetActive(true,m_Magic);
		}
		else if (m_myName == "Player2")
		{
			GetStage()->GetSharedGameObject<MagicBoal>(L"MagicBoal2", false)->SetActive(true,m_Magic);

		}
	}

	//カメラ固定
	void Player::SetCamera(Vector3 At, Vector3 pos)
	{
		m_CameraPos = pos;
		m_CameraTargetVec = At;
	}

	//ターンの最終更新時
	void Player::OnLastUpdate()
	{
		/*
		if (m_myName == "Player1")
		{
			wstring txt;
			Vector3 pos = GetComponent<Transform>()->GetPosition();
			txt += L"X = " + Util::FloatToWStr(pos.x) + L"\nY = " + Util::FloatToWStr(pos.y) + L"\nZ = " + Util::FloatToWStr(pos.z);
			GetComponent<StringSprite>()->SetText(txt);
		}
		*/
		/*
		wstring txt;
		//回転とってる
		//auto TranP = GetComponent<Transform>();
		//txt = Util::FloatToWStr(TranP->GetRotation().y * 180/3.14159265f);

		switch (m_Magic)
		{
		case None:
			txt += L"None";
			break;
		case Fire:
			txt += L"Fire";
			break;
		case IceFog:
			txt += L"IceFog";
			break;
		case Wind:
			txt += L"Wind";
		default:
			break;
		}
		GetComponent<StringSprite>()->SetText(txt);
		*/
	}

	void Player::PlayerDamege()
	{
		if (!m_InviFlg)
		{
			m_InviFlg = true;
			m_life--;
			m_LifeFlg = true;

			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			//移動するためアタリ消す
			GetComponent<CollisionSphere>()->SetUpdateActive(false);
			GetComponent<Rigidbody>()->SetUpdateActive(false);
			GetComponent<Gravity>()->SetUpdateActive(false);

			Vector3 pos = GetComponent<Transform>()->GetPosition();
			pos.y += 0.25f;
			GetComponent<Transform>()->SetPosition(pos);

			//移動後にアタリ判定一式を治す
			m_WarpFlg = true;

			//SE再生
			GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("Damege");
			switch (m_life)
			{
			case 0:
				//しんだ
				m_LifeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"LIFE0_TX");
				//ゲームオーバーに遷移
				//PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameOver");
				//暗転させる
				m_DieFlg = true;
				if (true)
				{
					auto obj = GetStage()->AddGameObject<Black>();
					obj->StartBlack();
					m_BlackDie = obj;
				}
				break;
			case 1:
				m_LifeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"LIFE1_TX");
				break;
			case 2:
				m_LifeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"LIFE2_TX");
				break;
			}
		}
	}


	void Player::LifeDelete()
	{
		//auto Trans = m_LifeSprite->GetComponent<Transform>();
		auto Draw = m_LifeSprite->GetComponent<PCTSpriteDraw>();
		switch (m_LifeState)
		{
		case 0:
			if (true)
			{
				/*
				auto scale = Trans->GetScale();
				scale *= 1.1f;
				Trans->SetScale(scale);
				if (scale.x > m_lifeSize.x * 1.5f)
				{
					m_LifeState = 1;
				}
				*/
				//点滅版
				m_LifeAlpha += -m_LifeAlphaSpeed;

				Draw->SetDiffuse(Color4(1, 1, 1, m_LifeAlpha));

				if (m_LifeAlpha <= 0)
				{
					m_LifeAlpha = 0;
					m_LifeState = 1;
				}
			}
			break;
		case 1:
			if (true)
			{
				/*
				auto scale = Trans->GetScale();
				scale *= 0.9f;
				Trans->SetScale(scale);
				if (scale.x < m_lifeSize.x * 0.5f)
				{
					m_LifeState = 0;
					m_lifeCount++;
					if (m_lifeCount >= m_lifeConCount)
					{
						m_LifeState = 2;
					}
				}
				*/

				//点滅版
				m_LifeAlpha += m_LifeAlphaSpeed;

				Draw->SetDiffuse(Color4(1, 1, 1, m_LifeAlpha));

				if (m_LifeAlpha >= 1)
				{
					m_LifeAlpha = 1;
					m_LifeState = 0;

					//カウント
					m_lifeCount++;
					if (m_lifeCount >= m_lifeConCount)
					{
						m_LifeState = 2;
					}

				}

			}
			break;
		case 2:
			//Trans->SetScale(m_lifeSize);
			Draw->SetDiffuse(Color4(1, 1, 1, 1));
			m_LifeFlg = false;
			m_LifeState = 0;
			m_lifeCount = 0;
			break;
		default:
			break;
		}

		

	}

	void Player::PlayerTerrainDamege()
	{
		//移動するためアタリ消す
		GetComponent<CollisionSphere>()->SetUpdateActive(false);
		GetComponent<Rigidbody>()->SetUpdateActive(false);
		GetComponent<Gravity>()->SetUpdateActive(false);

		//移動
		Vector3 pos = m_InitPos;
		pos.y += 2;
		GetComponent<Transform>()->SetPosition(pos);

		//移動後にアタリ判定一式を治す
		m_WarpFlg = true;

		//ライフ現象
		m_life--;
		m_LifeFlg = true;
		auto ScenePtr = App::GetApp()->GetScene<Scene>();

		//SE再生
		GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("TerrainDamage");

		switch (m_life)
		{
		case 0:
			//しんだ
			m_LifeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"LIFE0_TX");
			//ゲームオーバーに遷移
			//PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameOver");
			//暗転させる
			m_DieFlg = true;
			if (true)
			{
				auto obj = GetStage()->AddGameObject<Black>();
				obj->StartBlack();
				m_BlackDie = obj;
			}
			break;
		case 1:
			m_LifeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"LIFE1_TX");
			break;
		case 2:
			m_LifeSprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"LIFE2_TX");
			break;
		}

	}

	void Player::TargetMode()
	{
		//一番近い敵を保存
		auto EnemyGroup = GetStage()->GetSharedObjectGroup(L"Enemy", false)->GetGroupVector();

		//最短の距離
		float Distance = 99999;

		//自分の座標
		Vector3 PlayerPos = GetComponent<Transform>()->GetPosition();

		//敵がいるフラグ
		bool EnemySurvivalFlg = false;
		//最短的キャラへの角度
		float angle = 0;
		for (auto v : EnemyGroup)
		{
			auto EnemyPtr = dynamic_pointer_cast<Enemy>(v.lock());
			Vector3 EnemyPos = EnemyPtr->GetComponent<Transform>()->GetPosition();

			//上下の差
			float defY = PlayerPos.y - EnemyPos.y;
			
			//差を計算
			Vector3 DistanceVec3 = EnemyPos - PlayerPos;

			//距離を計算
			float nowDistance = (DistanceVec3.x * DistanceVec3.x) + (DistanceVec3.z + DistanceVec3.z);


			//エネミーが生きてたら
			if (EnemyPtr->GetActive() && abs(defY) < 1.5f && nowDistance < 50)
			{

				////差を計算
				//DistanceVec3 = EnemyPos - PlayerPos;

				////距離を計算
				//nowDistance = (DistanceVec3.x * DistanceVec3.x) + (DistanceVec3.z + DistanceVec3.z);
				//もし一番近かったら
				if (nowDistance < Distance)
				{
					EnemySurvivalFlg = true;

					//照準をもってきて消えてたら表示
					auto TargetAim = GetStage()->GetSharedGameObject<GameObject>(L"TargetAim", false);
					if (!TargetAim->GetDrawActive())
					{
						TargetAim->SetDrawActive(true);
					}

					//比較用距離を更新
					Distance = nowDistance;
					//プレイヤーの角度変更
					angle = atan2(DistanceVec3.z, DistanceVec3.x);
					angle *= -1;
					GetComponent<Transform>()->SetRotation(0, angle, 0);

					//照準を持ってくる
					Vector3 AimPos = EnemyPos;
					//縦のサイズ分座標ずらす
					float EnemySizeH = EnemyPtr->GetComponent<Transform>()->GetScale().y / 2;
					AimPos.y += EnemySizeH;
					//エネミーの大きさに合わせてサイズ変える
					Vector3 AimScale = TargetAim->GetComponent<Transform>()->GetScale();
					float ToScale = (EnemySizeH * 2) * 1.5f;
					AimScale = Vector3(ToScale, ToScale, ToScale);

					TargetAim->GetComponent<Transform>()->SetPosition(AimPos);
					TargetAim->GetComponent<Transform>()->SetScale(AimScale);
				}

			}

		}
		auto TargetAim = GetStage()->GetSharedGameObject<GameObject>(L"TargetAim", false);
		if (!EnemySurvivalFlg && TargetAim->GetDrawActive())
		{
			TargetAim->SetDrawActive(false);
		}
	}

	void Player::TargetModeRelease()
	{
		auto TargetAim = GetStage()->GetSharedGameObject<GameObject>(L"TargetAim", false);
		if (TargetAim->GetDrawActive())
		{
			TargetAim->SetDrawActive(false);
		}
	}
	//--------------------------------------------------------------------------------------
	//	class MagicBoal : public GameObject;
	//	用途: 魔法
	//--------------------------------------------------------------------------------------

	MagicBoal::MagicBoal(const shared_ptr<Stage>& StagePtr, Vector3 pos,int m) :
		GameObject(StagePtr),
		m_pos(pos),
		m_mynumber(m)
	{}

	void MagicBoal::OnCreate()
	{
		//初期位置などの設定
		auto Ptr = GetComponent<Transform>();
		Ptr->SetScale(m_magicSize);
		Ptr->SetRotation(0, 0, 0);
		Ptr->SetPosition(m_pos);

		//影をつける（シャドウマップを描画する）
		//auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		//ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");
		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//メッシュを設定
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		//テクスチャを設定
		PtrDraw->SetTextureResource(L"MAGICFIRE_TX");

		//透明化
		SetAlphaActive(true);

		//文字列をつける
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 320.0f, 640.0f, 480.0f));
		PtrString->SetFont(L"", 60);

		/*
		for (int i = 0; i < 10; i++)
		{

			//頂点配列
			vector<VertexPositionNormalTexture> vertices;
			//インデックスを作成するための配列
			vector<uint16_t> indices;
			//Squareの作成(ヘルパー関数を利用)
			MeshUtill::CreateSquare(1.0f, vertices, indices);
			//UV値の変更
			float from = i / 10.0f;
			float to = from + (1.0f / 10.0f);
			//左上頂点
			vertices[0].textureCoordinate = Vector2(from, 0);
			//右上頂点
			vertices[1].textureCoordinate = Vector2(to, 0);
			//左下頂点
			vertices[2].textureCoordinate = Vector2(from, 1.0f);
			//右下頂点
			vertices[3].textureCoordinate = Vector2(to, 1.0f);
			//頂点の型を変えた新しい頂点を作成
			vector<VertexPositionColorTexture> new_vertices;
			for (auto& v : vertices) {
				VertexPositionColorTexture nv;
				nv.position = v.position;
				nv.color = Color4(1.0f, 1.0f, 1.0f, 1.0f);
				nv.textureCoordinate = v.textureCoordinate;
				new_vertices.push_back(nv);
			}
			//メッシュ作成
			m_Mesh.push_back(MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true));
		}

		//連番の１を設定
		PtrDraw->SetMeshResource(m_Mesh[0]);
		*/
	}

	void MagicBoal::OnUpdate()
	{
		if (m_ActiveFlg)
		{
			/*
			//アニメーション更新
			m_CountTime += App::GetApp()->GetElapsedTime();
			//間隔時間越えたら
			if (m_CountTime > m_ConstCountTime)
			{
				m_CountTime = 0;
				m_MeshNumber++;
				if (m_MeshNumber > 9)
				{
					m_MeshNumber = 0;
				}

				//テクスチャ切り替え
				GetComponent<PNTStaticDraw>()->SetMeshResource(m_Mesh[m_MeshNumber]);
			}*/

			Vector3 pos = GetComponent<Transform>()->GetPosition();
			float Elapsed = App::GetApp()->GetElapsedTime();
			pos += Vector3(m_velocity.x*Elapsed, 0, m_velocity.y*Elapsed);
			GetComponent<Transform>()->SetPosition(pos);
			//生存時間計算
			m_lifeTime += App::GetApp()->GetElapsedTime();
			if (m_lifeTime > m_LifeTimeLimit)
			{
				m_lifeTime = 0;
				m_DeleteFlg = true;
				m_ActiveFlg = false;
			}
			//氷は短く
			if (m_MagicType == IceFog && m_lifeTime > m_shortLimitTime)
			{
				m_lifeTime = 0;
				m_DeleteFlg = true;
				m_ActiveFlg = false;

			}
		}
		else if (m_DeleteFlg)
		{
			Vector3 scale = GetComponent<Transform>()->GetScale();
			scale *= 0.95f;
			GetComponent<Transform>()->SetScale(scale);
			if (scale.x < 0.2f)
			{
				GetComponent<Transform>()->SetPosition(Vector3(0, -10, 0));
				SetDrawActive(false);
				m_DeleteFlg = false;
			}
		}
	}

	//状態操作
	void MagicBoal::SetActive(bool flg,MagicType mT)
	{
		if (!m_ActiveFlg && flg == true)
		{

			m_ActiveFlg = flg;
			m_MagicType = mT;
			switch (m_MagicType)
			{
			case None:
				return;
				break;
			case Fire:
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"MAGICFIRE_TX");
				//SE再生
				GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("MagicShotFire");
				break;
			case IceFog:
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"MAGICICE_TX");
				//SE再生
				GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("MagicShotIce");
				break;
			case Wind:
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"MAGICWIND_TX");
				//SE再生
				GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("MagicShotWind");
				break;
			default:
				break;
			}
			SetVelo();
		}
		//生きてるときにフラグおられたら
		if (m_ActiveFlg && flg == false)
		{
			m_DeleteFlg = true;
			m_ActiveFlg = false;
		}

		m_ActiveFlg = flg;

	}

	//向き、移動量計算
	void MagicBoal::SetVelo()
	{
		GetComponent<Transform>()->SetScale(m_magicSize);
		SetDrawActive(true);

		if (m_mynumber == 1)
		{
			auto PlayerP = GetStage()->GetSharedGameObject<Player>(L"Player1", false);
			Vector3 pos = PlayerP->GetComponent<Transform>()->GetPosition();
			pos.y += 0.5f;
			float angle = PlayerP->GetComponent<Transform>()->GetRotation().y;
			
			//移動量算出
			angle *= -1;
			m_velocity.x = cos(angle);
			m_velocity.y = sin(angle);
			m_velocity *= m_speed;

			GetComponent<Transform>()->SetPosition(pos);
		}
		else if(m_mynumber == 2)
		{
			auto PlayerP = GetStage()->GetSharedGameObject<Player>(L"Player2", false);
			Vector3 pos = PlayerP->GetComponent<Transform>()->GetPosition();
			pos.y += 0.5f;
			float angle = PlayerP->GetComponent<Transform>()->GetRotation().y;

			//移動量算出
			angle *= -1;
			m_velocity.x = cos(angle);
			m_velocity.y = sin(angle);
			m_velocity *= m_speed;

			GetComponent<Transform>()->SetPosition(pos);

		}
	}

	MagicType MagicBoal::GetMagicType()
	{
		return m_MagicType;
	}

	bool MagicBoal::GetActive()
	{
		return m_ActiveFlg;
	}
}
//end basecross

