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
		//横部分のみ反発
		PtrCol->SetIsHitAction(IsHitAction::AutoOnObjectRepel);

		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");
		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		if (m_myName == "Player1")
		{
			//描画するテクスチャを設定
			PtrDraw->SetTextureResource(L"TRACE_TX");
		}
		else if (m_myName == "Player2")
		{
			//描画するテクスチャを設定
			PtrDraw->SetTextureResource(L"TRACE2_TX");
		}
		//もし名前違ってる場合
		else
		{
			throw BaseException(
				L"Playerの名前指定ミスってます", L"", L""
				);
		}
		//文字列をつける
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
		PtrString->SetFont(L"", 40);

		//透明処理
		SetAlphaActive(true);
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
			active();
		}
	}

	//操作できる状態
	void Player::active()
	{

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
				Vector3 Posi = TranP->GetPosition();
				inputXY *= ElapsedTime*m_Speed;
				Posi.x += inputXY.x;
				Posi.z += inputXY.y;
				TranP->SetPosition(Posi);

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

		}

	}


	//キャラチェンジ
	void Player::ChangeChar()
	{
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
			//カメラ移動
			CameraP->SetEye(10.0f, 5.0f, -5.0f);
			CameraP->SetAt(10, 0, 0);


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
			CameraP->SetEye(0.0f, 5.0f, -5.0f);
			CameraP->SetAt(0, 0, 0);


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

	//魔法を記憶する
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

	//ターンの最終更新時
	void Player::OnLastUpdate() {

		wstring txt;
		//回転とってるけど表示おかしいのかな？
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


}
//end basecross

