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

		//最下地点
		PtrGravity->SetBaseY(0.125f);
		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionSphere>();

		// モデルとトランスフォームの間の差分行列
		float angle = -90 * (3.14159265f /180);
		Matrix4X4 SpanMat;
		SpanMat.DefTransformation(
			Vector3(4.0f, 4.0f, 4.0f),
			Vector3(0.0f, angle, 0.0f),
			Vector3(0.0f, 1.0f, 0.0f)
			);



		if (m_myName == "Player1")
		{
			// モデルとトランスフォームの間の差分行列
			angle = -90 * (3.14159265f / 180);
			SpanMat;
			SpanMat.DefTransformation(
				Vector3(2.0f, 2.0f, 2.0f),
				Vector3(0.0f, angle, 0.0f),
				Vector3(0.0f, 1.0f, 0.0f)
				);

			//影をつける（シャドウマップを描画する）
			auto ShadowPtr = AddComponent<Shadowmap>();
			//影の形（メッシュ）を設定
			ShadowPtr->SetMeshResource(L"Player1_Model");
			ShadowPtr->SetMeshToTransformMatrix(SpanMat);


			//描画コンポーネントの設定
			auto PtrDraw = AddComponent<PNTStaticModelDraw>();
			//描画するメッシュを設定
			PtrDraw->SetMeshResource(L"Player1_Model");
			PtrDraw->SetMeshToTransformMatrix(SpanMat);

			//魔法作成
			GetStage()->SetSharedGameObject(L"MagicBoal1", GetStage()->AddGameObject<MagicBoal>(Vector3(-100, -5.0f, 0),1));
		}
		else if (m_myName == "Player2")
		{
			//影をつける（シャドウマップを描画する）
			auto ShadowPtr = AddComponent<Shadowmap>();
			//影の形（メッシュ）を設定
			ShadowPtr->SetMeshResource(L"Player2_Model");
			ShadowPtr->SetMeshToTransformMatrix(SpanMat);


			//描画コンポーネントの設定
			auto PtrDraw = AddComponent<PNTStaticModelDraw>();
			//描画するメッシュを設定
			PtrDraw->SetMeshResource(L"Player2_Model");
			PtrDraw->SetMeshToTransformMatrix(SpanMat);

			//魔法作成
			GetStage()->SetSharedGameObject(L"MagicBoal2", GetStage()->AddGameObject<MagicBoal>(Vector3(-100, -5.0f, 0),2));
		}


		//文字列をつける
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
		PtrString->SetFont(L"", 80);

		//透明処理
		SetAlphaActive(true);

		//カメラ関連
		//向いてるとこ記憶
		m_CameraTargetVec = GetComponent<Transform>()->GetPosition();
		//座標記憶
		auto View = GetStage()->GetView();
		auto CameraP = View->GetTargetCamera();
		m_CameraPos = CameraP->GetEye();
	}

	//更新
	void Player::OnUpdate() {
		if (m_endFrame)
		{
			m_endFrame = false;
			return;
		}
		if (m_ActiveFlg)
		{
			CameraTarget();
			active();
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

				m_velocity += inputXY * m_Speed * ElapsedTime;

				//向きを得る				
				float angle = atan2(inputXY.y, inputXY.x);
				angle *= -1;
				TranP->SetRotation(Vector3(0, angle, 0));


			}

			//Rトリガーでキャラ切り替え
			if (CntlVec[0].wPressedButtons&XINPUT_GAMEPAD_RIGHT_SHOULDER)
			{
				ChangeChar();
			}

			//Xボタン押したら魔法発射
			if (CntlVec[0].wPressedButtons&XINPUT_GAMEPAD_X)
			{
				ShotMagic();
			}
		}

		//コンポーネントにやってもらう座標移動
		GetComponent<Rigidbody>()->SetVelocity(Vector3(m_velocity.x,0,m_velocity.y));


	}

	void Player::CameraTarget()
	{			
		//カメラ追従
		auto View = GetStage()->GetView();
		auto CameraP = View->GetTargetCamera();
		//カメラ移動
		Vector3 pos = GetComponent<Transform>()->GetPosition();
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
		m_CameraTargetVec.y = GetComponent<Transform>()->GetPosition().y;
		m_CameraPos.y = m_CameraTargetVec.y + 5.0f;
		CameraP->SetAt(m_CameraTargetVec);
		CameraP->SetEye(m_CameraPos);
	}


	//キャラチェンジ
	void Player::ChangeChar()
	{
		m_velocity = Vector2(0, 0);
		GetComponent<Rigidbody>()->SetVelocity(Vector3(0, 0, 0));
		//自分がどっちか判定
		if (m_myName == "Player1")
		{

			auto DPlayer = GetStage()->GetSharedGameObject<Player>(L"Player2", false);


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

	//操作状態操作
	void Player::SetActive(bool flg)
	{
		m_ActiveFlg = flg;
		m_endFrame = true;
	}

	//魔法を記憶するこれ常に1のほう呼ばれる
	void Player::SetMagic(MagicType MT)
	{
		if (m_myName == "Player1")
		{
			m_Magic = MT;
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
	void Player::OnLastUpdate() {

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
		default:
			break;
		}
		GetComponent<StringSprite>()->SetText(txt);
		
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
		Ptr->SetScale(0.25f, 0.25f, 0.25f);
		Ptr->SetRotation(0, 0, 0);
		Ptr->SetPosition(m_pos);

		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");
		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//メッシュを設定
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		//テクスチャを設定
		PtrDraw->SetTextureResource(L"MAGICBOOKFIRE_TX");

		//透明化
		SetAlphaActive(true);

		//文字列をつける
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 320.0f, 640.0f, 480.0f));
		PtrString->SetFont(L"", 60);

	}

	void MagicBoal::OnUpdate()
	{
		if (m_ActiveFlg)
		{
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
		}
		else if (m_DeleteFlg)
		{
			Vector3 scale = GetComponent<Transform>()->GetScale();
			scale *= 0.95f;
			GetComponent<Transform>()->SetScale(scale);
			if (scale.x < 0)
			{
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
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"MAGICBOOKFIRE_TX");
				break;
			case IceFog:
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"MAGICBOOKICEFOG_TX");
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
		GetComponent<Transform>()->SetScale(0.25f, 0.25f, 0.25f);
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

