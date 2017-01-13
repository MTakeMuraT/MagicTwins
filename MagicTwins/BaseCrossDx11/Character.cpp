/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	/*
	//--------------------------------------------------------------------------------------
	//	class MagicParticle : public GameObject;
	//	用途: パーティクル
	//	使い方：(Vec3座標,Vec3大きさ,Vec3位置範囲,Vec3Velocity,stringテクスチャの名前,作成数,作成間隔,一度に作成する数,生存時間,レイヤー)
	//--------------------------------------------------------------------------------------
	MagicParticle::MagicParticle(const shared_ptr<Stage>& StagePtr):
	GameObject(StagePtr)
	{}
	void MagicParticle::OnCreate(){}
	//上二つ使わない予想…

	//パーティクルを動かす
	void MagicParticle::OnUpdate()
	{
		//起動中
		if (m_NowParticleFlg)
		{
			//数分ループ
			for (int i = 0; i < m_CreateCount; i++)
			{
				//描画されてたら
				if (m_Particle[i]->GetDrawActive())
				{
					//コンポーネントとっとく
					auto Trans = m_Particle[i]->GetComponent<Transform>();

					//最初の更新時
					if (m_TimeCount[i] == 0)
					{
						//ブレ幅
						Vector3 pos = m_InitPos;
						pos.x += rand() % (int)(m_RandRange.x / 2) - m_RandRange.x / 2;
						pos.y += rand() % (int)(m_RandRange.y / 2) - m_RandRange.y / 2;
						pos.z += rand() % (int)(m_RandRange.z / 2) - m_RandRange.z / 2;

						//位置初期化
						Trans->SetPosition(pos);
					}

					//位置更新
					Vector3 pos = Trans->GetPosition();
					

					//時間更新
					m_TimeCount[i] += App::GetApp()->GetElapsedTime();
					if (m_TimeCount[i] > m_MoveingTime)
					{
						//生存時間を越えたら消す
						m_Particle[i]->SetDrawActive(false);
					}
				}
			}
		}
	}

	//パーティクル登録
	void MagicParticle::OnParticle(Vector3 pos, Vector3 scale, Vector3 randrange, Vector3 velo,Vector3 randvelo, wstring texturename,
		int createcount, float interval, int oncecreatecount,float moveingTime,int displayer)
	{
		//パーティクル出していない状態なら
		if (!m_NowParticleFlg)
		{
			//初期位置
			m_InitPos = pos;
			//大きさ
			m_InitScale = scale;
			//生成されるときの位置の振れ幅
			m_RandRange = randrange;
			//移動ブレ幅
			m_randVelocity = randvelo;
			//テクスチャの名前
			m_TextureName = texturename;
			//合計作成数
			m_CreateCount = createcount;
			//作成感覚
			m_Interval = interval;
			//一回に出す数
			m_OnceCreateCount = oncecreatecount;
			//動いてる時間
			m_MoveingTime = moveingTime;
			//表示レイヤー
			m_DispLayer = displayer;
			//パーティクルフラグOn
			m_NowParticleFlg = false;

			//作成数分作成
			//ここで作成間隔で割るのもありだけど時間的に余裕ないから飛ばす
			//最後のほうで時間余ったらやる
			for (int i = 0; i < m_CreateCount; i++)
			{
				auto obj = GetStage()->AddGameObject<GameObject>();
				
				auto objTrans = obj->AddComponent<Transform>();
				objTrans->SetPosition(0,0,0);
				objTrans->SetScale(m_InitScale);
				objTrans->SetRotation(0,0,0);

				auto objDraw = obj->AddComponent<PNTStaticDraw>();
				objDraw->SetMeshResource(L"DEFAULT_SQUARE");
				objDraw->SetTextureResource(m_TextureName);
				obj->SetAlphaActive(true);
				obj->SetDrawLayer(m_DispLayer);

				m_Particle.push_back(obj);


				//管理用の時間もリセット
				m_TimeCount.push_back(0);
				//フラグリセット
				m_OnFlg.push_back(false);
				//移動速度作る分追加
				Vector3 setVelocity = velo;
				Vector3 randVelocity;
				randvelo.x = rand() % (int)randvelo.x - (randvelo.x / 2);
				randvelo.y = rand() % (int)randvelo.y - (randvelo.y / 2);
				randvelo.z = rand() % (int)randvelo.z - (randvelo.z / 2);
				m_velocity.push_back(velo);
			}
		}
	}

	void MagicParticle::StopParticle()
	{
		//全パーティクル消滅
		for (auto v : m_Particle)
		{
			v->SetDrawActive(false);
		}
		m_NowParticleFlg = false;
	}
	*/
	//--------------------------------------------------------------------------------------
	//	class MagicParticle : public GameObject;
	//	用途: パーティクル(簡易対応版)
	//--------------------------------------------------------------------------------------
	MagicParticle::MagicParticle(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	void MagicParticle::OnUpdate()
	{
		//数表示
		//GetComponent<StringSprite>()->SetText(Util::IntToWStr(m_Particle.size()));
		if (m_NowParticleFlg)
		{
			//位置更新
			int count = 0;
			for (auto v : m_Particle)
			{
				//描画されてたら
				if (v->GetDrawActive())
				{
					auto Trans = v->GetComponent<Transform>();
					Vector3 pos = Trans->GetPosition();
					pos += m_velocity[count] * App::GetApp()->GetElapsedTime();
					Trans->SetPosition(pos);

					//消滅処理
					//trueで透明になる
					if (m_DeleteFlg)
					{
						m_alpha[count] += -m_DeleteTime * App::GetApp()->GetElapsedTime();
						v->GetComponent<PNTStaticDraw>()->SetDiffuse(Color4(1, 1, 1, m_alpha[count]));
						//透明化したら
						if (m_alpha[count] < 0)
						{
							m_alpha[count] = 1.0f;
							v->GetComponent<PNTStaticDraw>()->SetDiffuse(Color4(1, 1, 1, 1));
							//停止
							v->SetDrawActive(false);
						}
					}
					else
					{
						//サイズ小さく
						Vector3 scale = Trans->GetScale();
						scale *= 0.98f;
						Trans->SetScale(scale);
						//10分の1まで小さくなったら消える
						if (Trans->GetScale().x < m_Scale.x / 10)
						{
							Trans->SetScale(m_Scale);
							v->SetDrawActive(false);
						}
					}
				}
				count++;
			}
			count = 0;


			//経過時間加算
			m_time += App::GetApp()->GetElapsedTime();
			//生成感覚を越えたら
			if (m_time > m_CreateInterval)
			{
				m_time = 0;
				bool CreateFlg = true;
				//生きてるのあったら再利用
				int count = 0;
				for (auto v : m_Particle)
				{
					if (!v->GetDrawActive())
					{
						//描画
						v->SetDrawActive(true);
						//速度位置設定
						SetVeloPos(count);
						//作成フラグを消す
						CreateFlg = false;

						//一回で終わらせるために抜ける
						break;
					}

					count++;
				}
				count = 0;
				if (CreateFlg)
				{
					//無かったら生成
					CreateParticle();
				}
			}
		}
		//パーティクル停止
		else
		{
			//残ってるのあったら
			if (m_NokoriFlg)
			{
				//位置更新
				int count = 0;
				//パーティクル出てる数
				int PaticleCount = 0;
				for (auto v : m_Particle)
				{
					//描画されてたら
					if (v->GetDrawActive())
					{
						//出てる数かさん
						PaticleCount++;

						auto Trans = v->GetComponent<Transform>();
						Vector3 pos = Trans->GetPosition();
						pos += m_velocity[count] * App::GetApp()->GetElapsedTime();
						Trans->SetPosition(pos);

						//消滅処理
						//trueで透明になる
						if (m_DeleteFlg)
						{
							m_alpha[count] += -m_DeleteTime * App::GetApp()->GetElapsedTime();
							v->GetComponent<PNTStaticDraw>()->SetDiffuse(Color4(1, 1, 1, m_alpha[count]));
							//透明化したら
							if (m_alpha[count] < 0)
							{
								m_alpha[count] = 1.0f;
								v->GetComponent<PNTStaticDraw>()->SetDiffuse(Color4(1, 1, 1, 1));
								//停止
								v->SetDrawActive(false);
							}
						}
						else
						{
							//サイズ小さく
							Vector3 scale = Trans->GetScale();
							scale *= 0.98f;
							Trans->SetScale(scale);
							//10分の1まで小さくなったら消える
							if (Trans->GetScale().x < m_Scale.x / 10)
							{
								Trans->SetScale(m_Scale);
								v->SetDrawActive(false);
							}
						}
					}
					count++;
				}
				//パーティクルが一個も出てなければ更新すんのやめ
				if (PaticleCount <= 0)
				{
					m_NokoriFlg = false;
				}
				count = 0;
			}
		}
	}

	void MagicParticle::OnParticle(Vector3 InitPos, Vector3 RandPos, Vector3 Velo, Vector3 RandVelo, Vector3 scale, wstring TextureName, bool DeleteFlg, float CreateInterval,int layer,float deleteTime)
	{
		//初期位置設定
		m_InitPos = InitPos;
		//位置振れ幅設定
		m_RandPos = RandPos;
		//初期速度
		m_Initvelocity = Velo;
		//速度ブレ幅
		m_RandVelocity = RandVelo;
		//大きさ設定
		m_Scale = scale;
		//テクスチャの名前設定
		m_TextureName = TextureName;
		//消滅演出設定
		m_DeleteFlg = DeleteFlg;
		//作成間隔設定
		m_CreateInterval = CreateInterval;
		//レイヤー設定
		m_Layer = layer;
		//消滅時間
		m_DeleteTime = deleteTime;

		//起動フラグをON
		m_NowParticleFlg = true;

		//文字列をつける
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
		PtrString->SetFont(L"", 60);

	}

	void MagicParticle::StopParticle()
	{
		/*エフェクトも消す
		for (auto v : m_Particle)
		{
			v->SetDrawActive(false);
		}*/
		m_NowParticleFlg = false;
		//現状残ってるエフェクト出し切るためのフラグ
		m_NokoriFlg = true;
	}

	void MagicParticle::SetVeloPos(int num)
	{

		//位置調整-------------------------------------------------------------
		Vector3 pos = m_InitPos;
		Vector3 random;
		if (m_RandPos.x != 0)
		{
			random.x = (float)(rand() % (int)(m_RandPos.x * 100)) / 100 - (m_RandPos.x / 2);
		}
		if (m_RandPos.y != 0)
		{
			random.y = (float)(rand() % (int)(m_RandPos.y * 100)) / 100 - (m_RandPos.y / 2);
		}
		if (m_RandPos.z != 0)
		{
			random.z = (float)(rand() % (int)(m_RandPos.z * 100)) / 100 - (m_RandPos.z / 2);
		}
		pos += random;
		m_Particle[num]->GetComponent<Transform>()->SetPosition(pos);

		//速度調整-------------------------------------------------------------
		Vector3 velo = m_Initvelocity;
		Vector3 randvelo;
		if (m_RandVelocity.x != 0)
		{
			randvelo.x = (float)(rand() % (int)(m_RandVelocity.x * 100)) / 100 - (m_RandVelocity.x / 2);
		}
		if (m_RandVelocity.y != 0)
		{
			randvelo.y = (float)(rand() % (int)(m_RandVelocity.y * 100)) / 100 - (m_RandVelocity.y / 2);
		}
		if (m_RandVelocity.z != 0)
		{
			randvelo.z = (float)(rand() % (int)(m_RandVelocity.z * 100)) / 100 - (m_RandVelocity.z / 2);
		}
		velo += randvelo;
		m_velocity[num] = velo;

	}

	void MagicParticle::CreateParticle()
	{
		//生成
		auto obj = GetStage()->AddGameObject<GameObject>();
		auto Trans = obj->AddComponent<Transform>();
		//生成位置調整
		Vector3 pos = m_InitPos;
		Vector3 random;
		if (m_RandPos.x != 0)
		{
			random.x = (float)(rand() % (int)(m_RandPos.x * 100)) / 100 - (m_RandPos.x / 2);
		}
		if (m_RandPos.y != 0)
		{
			random.y = (float)(rand() % (int)(m_RandPos.y * 100)) / 100 - (m_RandPos.y / 2);
		}
		if (m_RandPos.z != 0)
		{
			random.z = (float)(rand() % (int)(m_RandPos.z * 100)) / 100 - (m_RandPos.z / 2);
		}
		pos += random;
		//位置設定
		Trans->SetPosition(pos);
		//大きさ設定
		Trans->SetScale(m_Scale);
		//かいて…、意味あるん？
		Trans->SetRotation(0, 0, 0);

		//描画設定
		auto Draw = obj->AddComponent<PNTStaticDraw>();
		Draw->SetMeshResource(L"DEFAULT_SQUARE");
		Draw->SetTextureResource(m_TextureName);
		obj->SetAlphaActive(true);
		obj->SetDrawLayer(m_Layer);

		//速さ設定
		Vector3 velo = m_Initvelocity;
		Vector3 randvelo;
		if (m_RandVelocity.x != 0)
		{
			randvelo.x = (float)(rand() % (int)(m_RandVelocity.x * 100)) / 100 - (m_RandVelocity.x / 2);
		}
		if (m_RandVelocity.y != 0)
		{
			randvelo.y = (float)(rand() % (int)(m_RandVelocity.y * 100)) / 100 - (m_RandVelocity.y / 2);
		}
		if (m_RandVelocity.z != 0)
		{
			randvelo.z = (float)(rand() % (int)(m_RandVelocity.z * 100)) / 100 - (m_RandVelocity.z / 2);
		}
		
		velo += randvelo;

		m_velocity.push_back(velo);
		m_Particle.push_back(obj);
		m_alpha.push_back(1.0f);
		//wstring txt;
		//txt += L"RandPos.X = " + Util::FloatToWStr(random.x) + L"RandPos.Y = " + Util::FloatToWStr(random.y + L"RandPos.Z = " + Util::FloatToWStr(random.z);
		//GetComponent<StringSprite>()->SetText(Util::IntToWStr(m_Particle.size()));
	}
	//--------------------------------------------------------------------------------------
	//	class Goal : public GameObject;
	//	用途: ゴール
	//--------------------------------------------------------------------------------------

	Goal::Goal(const shared_ptr<Stage>& StagePtr,Vector3 pos, Vector3 scale):
		GameObject(StagePtr),
		m_InitPos(pos),
		m_Scale(scale)
		{}
	void Goal::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Vector3 pos = m_InitPos;
		pos.y += -0.3f;
		Ptr->SetPosition(pos);
		Ptr->SetScale(m_Scale);
		float rotangle = 90 * (3.14159265f / 180);
		Ptr->SetRotation(rotangle, 0, 0);

		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionObb>();
		//横部分のみ反発
		//PtrCol->SetIsHitAction(IsHitAction::Stop);

		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(L"DEFAULT_SQUARE");
		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"DEFAULT_SQUARE");
		//描画するテクスチャを設定
		PtrDraw->SetTextureResource(L"GOAL_TX");

		//透明処理
		SetAlphaActive(true);
		SetDrawLayer(1);
	}

	//--------------------------------------------------------------------------------------
	//	class Plane : public GameObject;
	//	用途: 地面
	//--------------------------------------------------------------------------------------

	PlaneP::PlaneP(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, Vector3 rot):
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale),
		m_InitRot(rot)
	{}

	void PlaneP::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_InitScale);
		Ptr->SetRotation(m_InitRot);

		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionObb>();
		//横部分のみ反発
		PtrCol->SetIsHitAction(IsHitAction::AutoOnObjectRepel);

		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//描画するテクスチャを設定
		PtrDraw->SetTextureResource(L"PANEL_TX");

		//透明処理
		SetAlphaActive(true);

	}
	//--------------------------------------------------------------------------------------
	//	class Rock : public GameObject;
	//	用途：岩
	//--------------------------------------------------------------------------------------
	Rock::Rock(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_Scale(scale)
	{}

	void Rock::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_Scale);
		Ptr->SetRotation(0, 0, 0);

		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionObb>();

		// モデルとトランスフォームの間の差分行列
		float angle = (-90) * (3.14159265f / 180);
		Matrix4X4 SpanMat;
		SpanMat.DefTransformation(
			Vector3(0.5f, 0.5f, 0.5f),
			Vector3(0, angle, 0),
			Vector3(0, 0, 0)
			);

		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(L"Rock_Model");
		ShadowPtr->SetMeshToTransformMatrix(SpanMat);


		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticModelDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"Rock_Model");
		PtrDraw->SetMeshToTransformMatrix(SpanMat);

		//透明処理
		SetAlphaActive(true);
	}

	//--------------------------------------------------------------------------------------
	//	class Fence : public GameObject;
	//	用途: 柵
	//--------------------------------------------------------------------------------------
	Fence::Fence(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, Vector3 rot) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale),
		m_InitRot(rot)
	{}

	void Fence::OnCreate()
	{

		auto TranP = AddComponent<Transform>();
		TranP->SetPosition(m_InitPos);
		Vector3 scale = m_InitScale * 0.5f;
		TranP->SetScale(scale);
		TranP->SetRotation(m_InitRot);


		//以下フェンス
		auto obj = GetStage()->AddGameObject<GameObject>();
		//衝突判定をつける
		auto PtrCol = obj->AddComponent<CollisionObb>();

		auto Ptr = obj->AddComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		//Vector3 scale = m_InitScale * 0.7f;
		Ptr->SetScale(m_InitScale);
		Ptr->SetRotation(m_InitRot);


		// モデルとトランスフォームの間の差分行列
		float angle = (-90) * (3.14159265f / 180);
		Matrix4X4 SpanMat;
		SpanMat.DefTransformation(
			Vector3(0.8f, 0.8f, 0.8f),
			Vector3(0,0, 0),
			Vector3(0, -0.5f, 0)
			);

		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = obj->AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(L"Fence_Model");
		ShadowPtr->SetMeshToTransformMatrix(SpanMat);


		//描画コンポーネントの設定
		auto PtrDraw = obj->AddComponent<PNTStaticModelDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"Fence_Model");
		PtrDraw->SetMeshToTransformMatrix(SpanMat);

		//透明処理
		obj->SetAlphaActive(true);

		m_FenceObj = obj;
	}

	//--------------------------------------------------------------------------------------
	//	class Box : public GameObject;
	//	用途: 箱
	//--------------------------------------------------------------------------------------

	Box::Box(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale,Vector3 rot) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale),
		m_InitRot(rot)
	{}
	void Box::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_InitScale);
		Ptr->SetRotation(m_InitRot);

		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionObb>();

		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//描画するテクスチャを設定
		PtrDraw->SetTextureResource(L"BOX_TX");

		//透明処理
		SetAlphaActive(true);

	}
	//--------------------------------------------------------------------------------------
	//	class Enemy : public GameObject;
	//	用途: 敵
	//--------------------------------------------------------------------------------------
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale,int num):
		GameObject(StagePtr),
		m_InitPos(pos),
		m_Scale(scale),
		m_TargetPlayernum(num)
	{}

	void Enemy::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_Scale);

		// モデルとトランスフォームの間の差分行列
		Matrix4X4 SpanMat;
		SpanMat.DefTransformation(
			Vector3(0.5f, 0.5f, 0.5f),
			Vector3(0.0f, 0.0f, 0.0f),
			Vector3(0.0f, -0.3f, 0.0f)
			);


		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticModelDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"Enemy_Model");
		PtrDraw->SetMeshToTransformMatrix(SpanMat);

		//透明処理
		SetAlphaActive(true);

	}

	void Enemy::OnUpdate()
	{
		//死んでたらやめ
		if (!m_ActiveFlg)
		{
			if (m_deleteFlg)
			{
				//小さくしてく
				Vector3 nowScale = GetComponent<Transform>()->GetScale();
				nowScale *= 0.98f;
				GetComponent<Transform>()->SetScale(nowScale);

				//ある程度小さくなったら
				if (nowScale.x < 0.1f)
				{
					SetDrawActive(false);
					m_ChaceFlg = false;
					m_deleteFlg = false;
					GetComponent<Transform>()->SetPosition(0, -15, 0);
					GetComponent<Transform>()->SetScale(m_Scale);
				}
				return ;
			}

			m_time += App::GetApp()->GetElapsedTime();
			//復活するまで経過したら
			if (m_time > m_ReSponTime)
			{
				m_ActiveFlg = true;
				m_life = m_MaxLife;
				m_speed = m_InitSpeed;
				SetDrawActive(true);
				GetComponent<Transform>()->SetPosition(m_InitPos);
			}
			return;
		}
		//止まってない、かつ追う状態なら
		if (!m_StopFlg && m_ChaceFlg)
		{
			
			auto P1P = GetStage()->GetSharedGameObject<Player>(L"Player1", false);
			auto P2P = GetStage()->GetSharedGameObject<Player>(L"Player2", false);

			if (m_TargetPlayernum == 1)
			{
				if (P1P->GetActive())
				{
					Vector3 topos = P1P->GetComponent<Transform>()->GetPosition();
					Vector3 nowpos = GetComponent<Transform>()->GetPosition();
					Vector3 dir;
					dir = topos - nowpos;
					Vector2 velo = Vector2(dir.x, dir.z);
					float angle = atan2(velo.y, velo.x);
					velo.x = cos(angle);
					velo.y = sin(angle);

					//もしプレイヤーがターゲットモード中なら移動速度遅くする
					if (P1P->GetTargeModeFlg())
					{
						velo *= 0.5f;
					}

					nowpos.x += velo.x * App::GetApp()->GetElapsedTime() * m_speed;
					nowpos.z += velo.y * App::GetApp()->GetElapsedTime() * m_speed;
					GetComponent<Transform>()->SetPosition(nowpos);

					//向き更新
					angle = atan2(velo.y, velo.x);
					angle += (3.14159265f / 180) * 90;
					angle *= -1;
					GetComponent<Transform>()->SetRotation(Vector3(0, angle, 0));

				}
			}
			else if (m_TargetPlayernum == 2)
			{
				if (P2P->GetActive())
				{
					Vector3 topos = P2P->GetComponent<Transform>()->GetPosition();
					Vector3 nowpos = GetComponent<Transform>()->GetPosition();
					Vector3 dir;
					dir = topos - nowpos;
					Vector2 velo = Vector2(dir.x, dir.z);
					float angle = atan2(velo.y, velo.x);
					velo.x = cos(angle);
					velo.y = sin(angle);

					//もしプレイヤーがターゲットモード中なら移動速度遅くする
					if (P2P->GetTargeModeFlg())
					{
						velo *= 0.5f;
					}

					nowpos.x += velo.x * App::GetApp()->GetElapsedTime() * m_speed;
					nowpos.z += velo.y * App::GetApp()->GetElapsedTime() * m_speed;
					GetComponent<Transform>()->SetPosition(nowpos);

					//向き更新
					angle = atan2(velo.y, velo.x);
					angle *= -1;
					GetComponent<Transform>()->SetRotation(Vector3(0, angle, 0));

				}
			}
		}
		//止まってる状態
		else if(m_StopFlg)
		{
			m_time += App::GetApp()->GetElapsedTime();
			if (m_time > m_StopTime)
			{
				m_StopFlg = false;
				m_time = 0;
				GetComponent<PNTStaticModelDraw>()->SetDiffuse(Color4(1, 1, 1, 1));
			}
		}
		//止まってなくて追ってない状態なら
		else if (!m_ChaceFlg)
		{
			auto P1P = GetStage()->GetSharedGameObject<Player>(L"Player1", false);
			auto P2P = GetStage()->GetSharedGameObject<Player>(L"Player2", false);

			if (m_TargetPlayernum == 1)
			{
				if (P1P->GetActive())
				{
					Vector3 topos = P1P->GetComponent<Transform>()->GetPosition();
					Vector3 nowpos = GetComponent<Transform>()->GetPosition();
					Vector3 dir;
					dir = topos - nowpos;
					if (dir.Length() < m_ChaceDir)
					{
						m_ChaceFlg = true;
					}
				}
			}
			else if (m_TargetPlayernum == 2)
			{
				if (P2P->GetActive())
				{
					Vector3 topos = P2P->GetComponent<Transform>()->GetPosition();
					Vector3 nowpos = GetComponent<Transform>()->GetPosition();
					Vector3 dir;
					dir = topos - nowpos;
					if (dir.Length() < m_ChaceDir)
					{
						m_ChaceFlg = true;
					}
				}
			}
		}
	}

	void Enemy::StopEnemy(int TargetNum)
	{
		if (TargetNum == m_TargetPlayernum)
		{
			m_ChaceFlg = true;
			m_StopFlg = true;
			m_life--;
			m_time = 0;
			GetComponent<PNTStaticModelDraw>()->SetDiffuse(Color4(1, 1, 1, 0.5f));

			m_speed *= 2.0f;


			if (m_life <= 0)
			{
				m_deleteFlg = true;
				m_ActiveFlg = false;
			}
			//死んでなければ座標移動
			else
			{
				Vector3 pos = GetComponent<Transform>()->GetPosition();
				pos += Vector3(rand() % 10 - 5, 0, rand() % 10 - 5);
				GetComponent<Transform>()->SetPosition(pos);

			}
		}
	}

	void Enemy::ResetPos()
	{
		m_speed = m_InitSpeed;
		m_ChaceFlg = false;
		GetComponent<Transform>()->SetPosition(m_InitPos);
	}

	//--------------------------------------------------------------------------------------
	//	class Black : public GameObject;
	//	用途: 暗転用黒
	//--------------------------------------------------------------------------------------
	Black::Black(const shared_ptr<Stage>& StagePtr)	:
		GameObject(StagePtr)
	{}

	void Black::OnCreate()
	{
		//ウィンドウサイズ取得
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());

		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(0,0,0);
		Ptr->SetScale(WindowSize.x,WindowSize.y,1);
		Ptr->SetRotation(0, 0, 0);

		//テクスチャをつける
		auto PtrSprite = this->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"BLACK_TX");

		//透明化
		PtrSprite->SetDiffuse(Color4(1,1,1,0));

		//表示レイヤー10設定
		SetDrawLayer(10);

		//透明度反映
		SetAlphaActive(true);

	}

	void Black::OnUpdate()
	{
		//起動状態
		if (m_StartFlg)
		{
			//実体化
			auto PtrSprite = this->AddComponent<PCTSpriteDraw>();
			m_alpha += 1 * App::GetApp()->GetElapsedTime();
			PtrSprite->SetDiffuse(Color4(1, 1, 1, m_alpha));
			
			if (m_alpha >= 1.2f)
			{
				m_StartFlg = false;
				m_EndFlg = true;
			}
		}
	}

	void Black::StartBlack()
	{
		m_StartFlg = true;
	}

	bool Black::GetBlackFinish()
	{
		return m_EndFlg;
	}

	//--------------------------------------------------------------------------------------
	//	class MagicBook : public GameObject;
	//	用途: 魔導書
	//--------------------------------------------------------------------------------------
	MagicBook::MagicBook(const shared_ptr<Stage>& StagePtr, Vector3 pos, MagicType magic) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_MagicContent(magic)
	{}

	void MagicBook::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetScale(m_Scale);
		Ptr->SetRotation(0, 0, 0);
		Ptr->SetPosition(m_InitPos);

		/*
		//丸用
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

		switch (m_MagicContent)
		{
		case Fire:
			PtrDraw->SetTextureResource(L"MAGICBOOKFIRE_TX");
			break;
		case IceFog :
			PtrDraw->SetTextureResource(L"MAGICBOOKICEFOG_TX");
			break;
		case Wind:
			PtrDraw->SetTextureResource(L"MAGICBOOKWIND_TX");
		default:
			break;
		}
		*/
		
		//モデル用
		// モデルとトランスフォームの間の差分行列
		float angle = (-90) * (3.14159265f / 180);
		Matrix4X4 SpanMat;
		SpanMat.DefTransformation(
			Vector3(0.5f, 0.5f, 0.5f),
			Vector3(0, 0, 0),
			Vector3(0, -0.5f, 0)
			);

		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(L"MagicBookFire_Model");
		ShadowPtr->SetMeshToTransformMatrix(SpanMat);


		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticModelDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"MagicBookFire_Model");
		PtrDraw->SetMeshToTransformMatrix(SpanMat);


		switch (m_MagicContent)
		{
		case Fire:
			ShadowPtr->SetMeshResource(L"MagicBookFire_Model");
			PtrDraw->SetMeshResource(L"MagicBookFire_Model");
			break;
		case IceFog:
			ShadowPtr->SetMeshResource(L"MagicBookIceFog_Model");
			PtrDraw->SetMeshResource(L"MagicBookIceFog_Model");		
			break;
		case Wind:
			ShadowPtr->SetMeshResource(L"MagicBookWind_Model");
			PtrDraw->SetMeshResource(L"MagicBookWind_Model");	
			break;
		}
		

		/*//モデル版
		// モデルとトランスフォームの間の差分行列
		float angle = (-90) * (3.14159265f / 180);
		Matrix4X4 SpanMat;
		SpanMat.DefTransformation(
		Vector3(1.0f, 0.3f, 1.0f),
		Vector3(0, 0, 0),
		Vector3(0, 0, 0)
		);

		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(L"MagicBook_Model");
		ShadowPtr->SetMeshToTransformMatrix(SpanMat);


		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticModelDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"MagicBook_Model");
		PtrDraw->SetMeshToTransformMatrix(SpanMat);

		//色変える用だけどモデル読み込みだからちょっとやり方変える
		switch (m_MagicContent)
		{
		case Fire:
		//PtrDraw->SetTextureResource(L"MAGICBOOKFIRE_TX");
		PtrDraw->SetDiffuse(Color4(1, 1, 1, 1));
		break;
		case IceFog :
		//PtrDraw->SetTextureResource(L"MAGICBOOKICEFOG_TX");
		PtrDraw->SetDiffuse(Color4(0, 0, 1, 1));
		break;
		default:
		break;
		}
		*/

		//透明処理
		SetAlphaActive(true);

		SetUpdateActive(false);
	}

	void MagicBook::OnUpdate()
	{
		m_ElaTime += App::GetApp()->GetElapsedTime();
		if (m_ElaTime >= m_LimitTime)
		{
			GetComponent<PNTStaticModelDraw>()->SetDiffuse(Color4(1, 1, 1, 1));
			m_ElaTime = 0;
			SetUpdateActive(false);
			m_ActiveFlg = true;
			GetComponent<Transform>()->SetScale(m_Scale);

		}
	}

	//とったとき
	void MagicBook::GetPlayer()
	{
		if (m_ActiveFlg)
		{
			GetStage()->GetSharedGameObject<Player>(L"Player1", false)->SetMagic(m_MagicContent);
			GetComponent<PNTStaticModelDraw>()->SetDiffuse(Color4(1, 1, 1, 0.1f));
			SetUpdateActive(true);
			m_ActiveFlg = false;

			//モデルにしたら透明化できなくなったから小さくする
			Vector3 scale = m_Scale / 2;
			GetComponent<Transform>()->SetScale(scale);
		}
	}

	Vector3 MagicBook::GetPos()
	{
		return GetComponent<Transform>()->GetPosition();
	}

	Vector3 MagicBook::GetScale()
	{
		return GetComponent<Transform>()->GetScale();
	}

	//--------------------------------------------------------------------------------------
	//	class LimitTime : public GameObject;
	//	用途: 制限時間
	//--------------------------------------------------------------------------------------
	LimitTime::LimitTime(const shared_ptr<Stage>& StagePtr,float LimitTime):
		GameObject(StagePtr),
		m_LimitTime(LimitTime)
	{}
	
	void LimitTime::OnCreate()
	{
		auto DrawP = AddComponent<PCTSpriteDraw>();
		DrawP->SetTextureResource(L"TIME_TX");
		auto TranP = AddComponent<Transform>();
		TranP->SetPosition(800,470,0);
		TranP->SetRotation(0, 0, 0);
		TranP->SetScale(300, 300, 0);
		SetAlphaActive(true);

		//文字列をつける
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(1700.0f, 15.0f, 2000.0f, 300.0f));
		PtrString->SetFont(L"", 80);
		//調整用に+1
		m_nowTime = m_LimitTime + 1;
		SetDrawLayer(4);

		auto numobj = GetStage()->AddGameObject<NumberSprite>(0, Vector2(830, 470), Vector2(100, 100), 6);
		m_numberSp = numobj;



		//赤枠スプライト作成
		auto akaobj = GetStage()->AddGameObject<GameObject>();
		auto AkaTrans = akaobj->AddComponent<Transform>();
		AkaTrans->SetPosition(0, 0, 0);
		AkaTrans->SetRotation(0, 0, 0);
		AkaTrans->SetScale(1920, 1080, 1);

		auto AkaDraw = akaobj->AddComponent<PCTSpriteDraw>();
		AkaDraw->SetTextureResource(L"AKAWAKU_TX");

		akaobj->SetDrawLayer(5);
		akaobj->SetAlphaActive(true);
		akaobj->SetDrawActive(false);

		m_AkaWakuSprite = akaobj;
	}

	void LimitTime::OnUpdate()
	{
		//wstring txt = Util::IntToWStr((int)m_nowTime);
		//GetComponent<StringSprite>()->SetText(txt);

		if (m_AkaWakuFlg)
		{
			//falseで透明化
			if (!m_AlphaAkaFlg)
			{
				m_AlphaAka += -1 * App::GetApp()->GetElapsedTime();
				m_AkaWakuSprite->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_AlphaAka));
				if (m_AlphaAka <0)
				{
					m_AlphaAkaFlg = true;
				}
			}
			//trueで実体化
			else
			{
				m_AlphaAka += 1 * App::GetApp()->GetElapsedTime();
				m_AkaWakuSprite->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_AlphaAka));

				if (m_AlphaAka > 1.0f)
				{
					m_AlphaAkaFlg = false;
				}
			}
			if (m_nowTime > 10)
			{
				m_AkaWakuFlg = false;
				m_AkaWakuSprite->SetDrawActive(false);
			}


		}
		//10秒未満で赤枠
		if (!m_AkaWakuFlg && m_nowTime <= 10)
		{
			m_AkaWakuFlg = true;
			m_AkaWakuSprite->SetDrawActive(true);
			GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("TimeAlert");
		}
		
		//時間経過処理
		m_nowTime += -App::GetApp()->GetElapsedTime();

		//スプライト変更
		m_numberSp->SetNum((int)m_nowTime);

		if (m_nowTime < 1)
		{
			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameOver");
		}
	}

	//--------------------------------------------------------------------------------------
	//	class NumberSprite : public GameObject;
	//	用途: 数字のスプライト
	//--------------------------------------------------------------------------------------
	NumberSprite::NumberSprite(const shared_ptr<Stage>& StagePtr,int numb,Vector2 pos,Vector2 Scale,int layer):
		GameObject(StagePtr),
		m_num(numb),
		m_pos(pos),
		m_scale(Scale),
		m_layer(layer)
	{}

	void NumberSprite::OnCreate()
	{
		//数字の大きさによって回数変更
		int count = m_num;
		do
		{
			count /= 10;
			m_digit++;
		} while (count > 0);

		//数字のスプライト作成
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

		int masternum = m_num;
		
		//桁分ループ
		for (int j = m_digit-1; j >= 0; j--)
		{
			//生成桁数追加
			m_Constdigit++;

			int digi = j;
			int num = masternum / pow(10, (digi));
			masternum = masternum % (int)(pow(10, (digi)));

			auto NumP = GetStage()->AddGameObject<GameObject>();

			float distance = m_scale.x / 1.8f;

			auto TranP = NumP->AddComponent<Transform>();
			TranP->SetPosition(m_pos.x - (distance*j), m_pos.y, 0);
			TranP->SetScale(m_scale.x, m_scale.y, 1);
			TranP->SetRotation(0, 0, 0);

			auto DrawP = NumP->AddComponent<PCTSpriteDraw>();
			DrawP->SetTextureResource(L"NUMBER_TX");
			DrawP->SetMeshResource(m_Mesh[num]);
			NumP->SetAlphaActive(true);

			NumP->SetDrawLayer(m_layer);
			m_Numbers.push_back(NumP);
		}
	}

	void NumberSprite::SetPositionVec2(Vector2 pos)
	{
		int count = 0;
		for (auto v : m_Numbers)
		{
			v->GetComponent<Transform>()->SetPosition(m_pos.x,m_pos.y,0);
			count++;
		}
	}

	void NumberSprite::SetScaleVec2(Vector2 scale)
	{

	}

	void NumberSprite::SetNum(int num)
	{
		//マイナス弾く
		if (m_num >= 0)
		{
			m_num = num;
			//入力された桁持ってくる
			int digit = 0;
			int innum = num;
			do
			{
				innum /= 10;
				digit++;
			} while (innum > 0);

			//入力されたほうが大きかったら
			if (digit > m_digit)
			{
				for (int j = 0; j < (digit - m_Constdigit); j++)
				{
					//左側に桁追加
					int digitDif = digit - m_digit;

					m_Constdigit++;

					auto NumP = GetStage()->AddGameObject<GameObject>();

					float distance = m_scale.x / 1.8f;

					auto TranP = NumP->AddComponent<Transform>();
					TranP->SetPosition(m_pos.x - (distance*(m_digit)), m_pos.y, 0);
					TranP->SetScale(m_scale.x, m_scale.y, 1);
					TranP->SetRotation(0, 0, 0);

					auto DrawP = NumP->AddComponent<PCTSpriteDraw>();
					DrawP->SetTextureResource(L"NUMBER_TX");
					DrawP->SetMeshResource(m_Mesh[0]);
					NumP->SetAlphaActive(true);

					NumP->SetDrawLayer(m_layer);
					m_Numbers.push_back(NumP);
				}

				for (int i = 0; i < m_Constdigit; i++)
				{
					m_Numbers[i]->SetDrawActive(true);
				}
			}

			//入力されたほうが小さい
			if (digit < m_digit)
			{
				for (int i = m_digit - 1; i > digit - 1; i--)
				{
					m_Numbers[i]->SetDrawActive(false);
				}
			}

			//桁更新
			m_digit = digit;

			//数字入れ替え
			int masternum = m_num;
			for (int i = m_digit - 1; i >= 0; i--)
			{
				int digi = i;
				int setnum = masternum / pow(10, (digi));
				masternum = masternum % (int)(pow(10, (digi)));

				m_Numbers[i]->GetComponent<PCTSpriteDraw>()->SetMeshResource(m_Mesh[setnum]);
			}
		}
	}

	//--------------------------------------------------------------------------------------
	//	class PauseMenu : public GameObject;
	//	用途: ポーズメニュー
	//--------------------------------------------------------------------------------------
	PauseMenu::PauseMenu(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
	{}

	void PauseMenu::OnCreate()
	{
		//ポーズのロゴ
		auto TranP = AddComponent<Transform>();
		TranP->SetPosition(Vector3(0,400,0));
		TranP->SetScale(500, 100, 1);
		TranP->SetRotation(0, 0, 0);

		auto DrawP = AddComponent<PCTSpriteDraw>();
		DrawP->SetTextureResource(L"PAUSELOGO_TX");
		SetAlphaActive(true);
		SetDrawActive(false);
		SetDrawLayer(8);

		//暗転
		auto BlackP = GetStage()->AddGameObject<GameObject>();
		auto BTranP = BlackP->AddComponent<Transform>();
		BTranP->SetPosition(0, 0, 0);
		BTranP->SetScale(1920, 1080, 1);
		BTranP->SetRotation(0, 0, 0);
		auto BDrawP = BlackP->AddComponent<PCTSpriteDraw>();
		BDrawP->SetTextureResource(L"BLACK_TX");
		BDrawP->SetDiffuse(Color4(1, 1, 1, 0.5f));

		BlackP->SetDrawLayer(7);
		BlackP->SetAlphaActive(true);
		BlackP->SetDrawActive(false);
		m_Black = BlackP;

		//サイズ
		Vector3 LogoScale = Vector3(400, 400, 1);

		//リトライロゴ
		auto ReTryP = GetStage()->AddGameObject<GameObject>();
		auto RTTP = ReTryP->AddComponent<Transform>();
		//RTTP->SetPosition(m_SelectX, 300, 0);
		RTTP->SetPosition(-500, -400, 0);
		RTTP->SetScale(m_SelectScale);
		RTTP->SetRotation(0, 0, 0);
		auto RTDP = ReTryP->AddComponent<PCTSpriteDraw>();
		RTDP->SetTextureResource(L"PAUSERETRY_TX");
		ReTryP->SetAlphaActive(true);
		ReTryP->SetDrawActive(false);
		ReTryP->SetDrawLayer(8);
		m_ReTryLogo = ReTryP;

		/*
		//マップロゴ
		auto MaPP = GetStage()->AddGameObject<GameObject>();
		auto MTPP = MaPP->AddComponent<Transform>();
		MTPP->SetPosition(m_NotSelectX, 150, 0);
		MTPP->SetScale(LogoScale);
		MTPP->SetRotation(0, 0, 0);
		auto MDPP = MaPP->AddComponent<PCTSpriteDraw>();
		MDPP->SetTextureResource(L"PAUSEMAPLOGO_TX");
		MaPP->SetAlphaActive(true);
		MaPP->SetDrawActive(false);
		MaPP->SetDrawLayer(8);
		m_mapLogo = MaPP;
		*/

		//ステージセレクトロゴ
		auto SSP = GetStage()->AddGameObject<GameObject>();
		auto SSTP = SSP->AddComponent<Transform>();
		//SSTP->SetPosition(m_NotSelectX, 0, 0);
		SSTP->SetPosition(0, -400, 0);
		SSTP->SetScale(m_NotSelectScale);
		SSTP->SetRotation(0, 0, 0);
		auto SSDP = SSP->AddComponent<PCTSpriteDraw>();
		SSDP->SetTextureResource(L"PAUSESTAGESELECTLOGO_TX");
		SSP->SetAlphaActive(true);
		SSP->SetDrawActive(false);
		SSP->SetDrawLayer(8);
		m_StageSelectLogo = SSP;

		//タイトルロゴ
		auto TiP = GetStage()->AddGameObject<GameObject>();
		auto TTP = TiP->AddComponent<Transform>();
		//TTP->SetPosition(m_NotSelectX, -150, 0);
		TTP->SetPosition(500, -400, 0);
		TTP->SetScale(m_NotSelectScale);
		TTP->SetRotation(0, 0, 0);
		auto TDP = TiP->AddComponent<PCTSpriteDraw>();
		TDP->SetTextureResource(L"PAUSETITLELOGO_TX");
		TiP->SetAlphaActive(true);
		TiP->SetDrawActive(false);
		TiP->SetDrawLayer(8);
		m_TitleLogo = TiP;

		//マップ画像
		auto MaP = GetStage()->AddGameObject<GameObject>();
		auto MaTP = MaP->AddComponent<Transform>();
		MaTP->SetPosition(0, 0, 0);
		MaTP->SetScale(500,500,1);
		MaTP->SetRotation(0, 0, 0);
		auto MaTDP = MaP->AddComponent<PCTSpriteDraw>();
		//シーンからステージ番号取得
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		int StageNum = ScenePtr->GetStageNum();
		wstring texturetxt = L"MAP_" + Util::IntToWStr(StageNum) + L"_TX";
		MaTDP->SetTextureResource(texturetxt);
		MaP->SetAlphaActive(true);
		MaP->SetDrawActive(false);
		MaP->SetDrawLayer(8);
		m_Map = MaP;

	}

	void PauseMenu::OnUpdate()
	{
		if (m_BlackOutFlg)
		{
			BlackOut();
			return;
		}
		//マップ表示してない
		if (!m_selectMapFlg)
		{
			//ポーズ中かつ暗転入ってない
			if (m_ActivePauseFlg && !m_BlackOutFlg)
			{
				auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
				//決定押されたら
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
				{/*
					//マップじゃなければ
					if (m_selectnum != 1)
					{
						//暗転状態へ
						m_BlackOutFlg = true;

						m_Black->SetDrawLayer(8);
						return;
					}
					else
					{
						m_Map->SetDrawActive(true);
						m_selectMapFlg = true;
					}
					*/

					//暗転状態へ
					m_BlackOutFlg = true;

					m_Black->SetDrawLayer(10);
					//SE再生
					GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("Select");

					return;

				}
				Vector2 inputXY = Vector2(CntlVec[0].fThumbLX, CntlVec[0].fThumbLY);
				if (!m_moveFlg)
				{
					if (inputXY.x > 0.8f)
					{
						m_moveFlg = true;
						m_selectnum++;
						if (m_selectnum > 2)
						{
							m_selectnum = 0;
						}
					}
					if (inputXY.x < -0.8f)
					{
						m_moveFlg = true;
						m_selectnum--;
						if (m_selectnum < 0)
						{
							m_selectnum = 2;
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
							m_StageSelectLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
							m_TitleLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);

							/*
							//前後の物を移動
							//0なら(3,1)
							//3

							pos = m_TitleLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_NotSelectX;
							m_TitleLogo->GetComponent<Transform>()->SetPosition(pos);
							//1
							pos = m_mapLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_NotSelectX;
							m_mapLogo->GetComponent<Transform>()->SetPosition(pos);

							//0
							pos = m_ReTryLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_SelectX;
							m_ReTryLogo->GetComponent<Transform>()->SetPosition(pos);
							*/
							break;
						case 1:
							m_ReTryLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
							m_StageSelectLogo->GetComponent<Transform>()->SetScale(m_SelectScale);
							m_TitleLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);

							/*
							//0
							pos = m_ReTryLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_NotSelectX;
							m_ReTryLogo->GetComponent<Transform>()->SetPosition(pos);
							//2
							pos = m_StageSelectLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_NotSelectX;
							m_StageSelectLogo->GetComponent<Transform>()->SetPosition(pos);
							//1
							pos = m_mapLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_SelectX;
							m_mapLogo->GetComponent<Transform>()->SetPosition(pos);
							*/
							break;
						case 2:
							m_ReTryLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
							m_StageSelectLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
							m_TitleLogo->GetComponent<Transform>()->SetScale(m_SelectScale);

							/*
							//1
							pos = m_mapLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_NotSelectX;
							m_mapLogo->GetComponent<Transform>()->SetPosition(pos);
							//3
							pos = m_TitleLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_NotSelectX;
							m_TitleLogo->GetComponent<Transform>()->SetPosition(pos);
							//2
							pos = m_StageSelectLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_SelectX;
							m_StageSelectLogo->GetComponent<Transform>()->SetPosition(pos);
							*/
							break;
							/*
						case 3:
							
							//0
							pos = m_ReTryLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_NotSelectX;
							m_ReTryLogo->GetComponent<Transform>()->SetPosition(pos);
							//2
							pos = m_StageSelectLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_NotSelectX;
							m_StageSelectLogo->GetComponent<Transform>()->SetPosition(pos);
							//3
							pos = m_TitleLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_SelectX;
							m_TitleLogo->GetComponent<Transform>()->SetPosition(pos);
							
							break;
							*/
						default:
							throw BaseException(
								L"(PauseMenu)変なの入ってる",
								L"",
								L""
								);
							break;
						}
					}
				}
				else if (inputXY.x < 0.1f && inputXY.x > -0.1f)
				{
					m_moveFlg = false;
				}
			}
		}
		//マップ表示してる状態
		else
		{
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
			{
				m_Map->SetDrawActive(false);
				m_selectMapFlg = false;
			}
		}
	}

	void PauseMenu::BlackOut()
	{
		if (m_BlackAlpha >= 1.2f)
		{
			auto ScenePtr = App::GetApp()->GetScene<Scene>();

			switch (m_selectnum)
			{
			case 0:
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameStage");

				break;
			case 1:
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"StageSelect");

				break;
			case 2:
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"Title");

				break;

			default:
				break;
			}
		}
		else
		{
			m_BlackAlpha += 1 * App::GetApp()->GetElapsedTime();
			m_Black->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));
		}
	}

	void PauseMenu::Pause()
	{
		//フラグ反転
		m_ActivePauseFlg = !m_ActivePauseFlg;
		//それぞれ実体or透明化
		SetDrawActive(m_ActivePauseFlg);
		m_Black->SetDrawActive(m_ActivePauseFlg);
		m_ReTryLogo->SetDrawActive(m_ActivePauseFlg);
		//m_mapLogo->SetDrawActive(m_ActivePauseFlg);
		m_StageSelectLogo->SetDrawActive(m_ActivePauseFlg);
		m_TitleLogo->SetDrawActive(m_ActivePauseFlg);

		m_Map->SetDrawActive(m_ActivePauseFlg);
		m_selectMapFlg = false;
		m_selectnum = 0;

		//サイズ調整
		m_ReTryLogo->GetComponent<Transform>()->SetScale(m_SelectScale);
		m_StageSelectLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
		m_TitleLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);

		/*
		//位置調整
		Vector3 pos;
		//0
		pos = m_ReTryLogo->GetComponent<Transform>()->GetPosition();
		pos.x = m_SelectX;
		m_ReTryLogo->GetComponent<Transform>()->SetPosition(pos);

		//1
		pos = m_mapLogo->GetComponent<Transform>()->GetPosition();
		pos.x = m_NotSelectX;
		m_mapLogo->GetComponent<Transform>()->SetPosition(pos);
		//2
		pos = m_StageSelectLogo->GetComponent<Transform>()->GetPosition();
		pos.x = m_NotSelectX;
		m_StageSelectLogo->GetComponent<Transform>()->SetPosition(pos);
		//3
		pos = m_TitleLogo->GetComponent<Transform>()->GetPosition();
		pos.x = m_NotSelectX;
		m_TitleLogo->GetComponent<Transform>()->SetPosition(pos);
		*/

	}
	//--------------------------------------------------------------------------------------
	//	class MenuIcon : public GameObject;
	//	用途: メニューボタンのアイコン
	//--------------------------------------------------------------------------------------
	MenuIcon::MenuIcon(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
	{}

	void MenuIcon::OnCreate()
	{
		auto DrawP = AddComponent<PCTSpriteDraw>();
		DrawP->SetTextureResource(L"MENUICON_TX");
		auto TranP = AddComponent<Transform>();
		TranP->SetPosition(750,-450, 0);
		TranP->SetRotation(0, 0, 0);
		TranP->SetScale(100, 100, 0);
		SetAlphaActive(true);
		SetDrawLayer(5);

	}

	//--------------------------------------------------------------------------------------
	//	class ScoreItem : public GameObject;
	//	用途:　スコアアイテム
	//--------------------------------------------------------------------------------------
	ScoreItem::ScoreItem(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale):
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale)
	{}

	void ScoreItem::OnCreate()
	{
		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");
		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//メッシュを設定
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");

		//テクスチャを設定
		PtrDraw->SetTextureResource(L"SCOREITEM_TX");

		SetAlphaActive(true);

		auto TranP = AddComponent<Transform>();
		TranP->SetPosition(m_InitPos);
		TranP->SetScale(m_InitScale);
		TranP->SetRotation(0, 0, 0);


		//****仮	
		//Kieru();
		//****仮
	}

	void ScoreItem::Delete()
	{
		m_Active = false;
		SetDrawActive(false);
		GetComponent<Transform>()->SetPosition(0, -10, 0);
		//SE再生
		GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("ScoreItemGet");

		//エフェクト停止
		for (auto v : m_Particle)
		{
			v->StopParticle();
		}
	}

	void ScoreItem::Detekuru()
	{
		if (m_Active)
		{
			GetComponent<Transform>()->SetPosition(m_InitPos);
		}
	}

	void ScoreItem::Kieru()
	{
		if (m_Active)
		{
			GetComponent<Transform>()->SetPosition(0, -10, 0);
		}
	}
	//--------------------------------------------------------------------------------------
	//	class Gimmick1 : public GameObject;
	//	用途: 氷。炎の魔法[Fire]で溶かせる
	//--------------------------------------------------------------------------------------
	Gimmick1::Gimmick1(const shared_ptr<Stage>& StagePtr,Vector3 pos,Vector3 scale):
		GameObject(StagePtr),
		m_InitPos(pos),
		m_Scale(scale)
	{}

	void Gimmick1::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_Scale);
		Ptr->SetRotation(0, 0, 0);

		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionObb>();

		// モデルとトランスフォームの間の差分行列
		Matrix4X4 SpanMat;
		SpanMat.DefTransformation(
			Vector3(0.6f, 0.6f, 0.6f),
			Vector3(0.0f, 0.0f, 0.0f),
			Vector3(0.0f, -0.3f, 0.0f)
			);


		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticModelDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"IceBlock_Model");
		PtrDraw->SetMeshToTransformMatrix(SpanMat);

		//透明処理
		SetAlphaActive(true);

	}

	void Gimmick1::Delete(MagicType MT)
	{
		if (MT == Fire)
		{
			m_ActiveFlg = false;
			SetDrawActive(false);
			GetComponent<CollisionObb>()->SetUpdateActive(false);
			GetComponent<Transform>()->SetPosition(0, -10, 0);
			//SE再生
			GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("FireDamage");

			//エフェクト停止
			for (auto v : m_Particle)
			{
				v->StopParticle();
			}
		}
	}

	//--------------------------------------------------------------------------------------
	//	class Gimmick2 : public GameObject;
	//	用途: 風車、炎で消せる
	//--------------------------------------------------------------------------------------
	Gimmick2::Gimmick2(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_Scale(scale)
	{}

	void Gimmick2::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_Scale);
		Ptr->SetRotation(0, 0, 0);

		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionObb>();

		// モデルとトランスフォームの間の差分行列
		float angle = (-90) * (3.14159265f / 180);
		Matrix4X4 SpanMat;
		SpanMat.DefTransformation(
			Vector3(0.7f, 0.2f, 0.7f),
			Vector3(0, 0, 0),
			Vector3(0, 0, 0)
			);

		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(L"Windmill_Model");
		ShadowPtr->SetMeshToTransformMatrix(SpanMat);


		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTBoneModelDraw>();
		//描画するメッシュを設定
		//PtrDraw->SetMeshResource(L"Windmill_Model");
		PtrDraw->SetMeshResource(L"Windmill_Model");
		PtrDraw->SetMeshToTransformMatrix(SpanMat);
		//アニメーション追加
		PtrDraw->AddAnimation(L"rot", 0, 20, true, 30);
		PtrDraw->ChangeCurrentAnimation(L"rot");

		//透明処理
		SetAlphaActive(true);

	}

	void Gimmick2::OnUpdate()
	{
		if (m_RotFlg)
		{
			float ElapsedTime = App::GetApp()->GetElapsedTime();
			m_time += ElapsedTime;
			if (m_time > m_LimitTime)
			{
				m_RotFlg = false;
				m_time = 0;
			}
			//アニメーション更新
			GetComponent<PNTBoneModelDraw>()->UpdateAnimation(ElapsedTime);
		}
	}

	void Gimmick2::Delete(MagicType MT)
	{
		if (MT == Fire)
		{
			m_ActiveFlg = false;
			GetComponent<CollisionObb>()->SetUpdateActive(false);
			SetDrawActive(false);
			GetComponent<Transform>()->SetPosition(0, -10, 0);
			m_ActiveFlg = false;
			//SE再生
			GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("FireDamage");

			//エフェクト停止
			for (auto v : m_Particle)
			{
				v->StopParticle();
			}

		}

		if (MT == Wind)
		{
			GetStage()->GetSharedGameObject<Gimmick2_1>(L"WaterGate", false)->Action();
			m_RotFlg = true;
		}
	}

	//--------------------------------------------------------------------------------------
	//	class Gimmick2_1 : public GameObject;
	//	用途:　風車に風当てると閉じる水門
	//--------------------------------------------------------------------------------------
		Gimmick2_1::Gimmick2_1(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale):
			GameObject(StagePtr),
			m_InitPos(pos),
			m_Scale(scale)
		{}

		void Gimmick2_1::OnCreate()
		{
		
			auto Ptr = GetComponent<Transform>();
			Ptr->SetScale(m_Scale);
			Ptr->SetRotation(0, 0, 0);
			Ptr->SetPosition(m_InitPos);

			//影をつける（シャドウマップを描画する）
			auto ShadowPtr = AddComponent<Shadowmap>();
			//影の形（メッシュ）を設定
			ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");
			//描画コンポーネントの設定
			auto PtrDraw = AddComponent<PNTStaticDraw>();
			//メッシュを設定
			PtrDraw->SetMeshResource(L"DEFAULT_CUBE");

			//テクスチャを設定
			PtrDraw->SetTextureResource(L"WATERGATE_TX");

			//透明処理
			SetAlphaActive(true);

			auto PtrCol = AddComponent<CollisionObb>();
			PtrCol->SetUpdateActive(false);
		}

		void Gimmick2_1::OnUpdate()
		{
			if (m_MoveFlg)
			{
				Vector3 pos = GetComponent<Transform>()->GetPosition();
				//閉じてる最中
				if (m_CloseFlg)
				{
					pos.y += -0.02f;
					if (pos.y <= m_targetY)
					{
						m_MoveFlg = false;
						pos.y = m_targetY;
						//水閉じる
						auto WaterCoreGroupVec = GetStage()->GetSharedObjectGroup(L"WaterCoreGate")->GetGroupVector();
						for (auto v : WaterCoreGroupVec)
						{
							auto WCP = dynamic_pointer_cast<Gimmick3>(v.lock());
							WCP->Stop();
						}
						//アタリつける
						GetComponent<CollisionObb>()->SetUpdateActive(true);

						//スコアアイテム出現
						//****仮
						auto SIGV = GetStage()->GetSharedObjectGroup(L"ScoreItem")->GetGroupVector();
						for (auto v : SIGV)
						{
							auto Ptr = dynamic_pointer_cast<ScoreItem>(v.lock());
							Ptr->Detekuru();
						}
						//****仮
					}
				}
				//開いてる最中
				else
				{
					pos.y += 0.02f;
					if (pos.y >= m_targetY)
					{
						m_MoveFlg = false;
						pos.y = m_targetY;
						//水開く
						auto WaterCoreGroupVec = GetStage()->GetSharedObjectGroup(L"WaterCoreGate")->GetGroupVector();
						for (auto v : WaterCoreGroupVec)
						{
							auto WCP = dynamic_pointer_cast<Gimmick3>(v.lock());
							//SE再生
							GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("Water");
							WCP->Flow();
						}
						//スコアアイテム消える
						//****仮
						auto SIGV = GetStage()->GetSharedObjectGroup(L"ScoreItem")->GetGroupVector();
						for (auto v : SIGV)
						{
							auto Ptr = dynamic_pointer_cast<ScoreItem>(v.lock());
							Ptr->Kieru();
						}
						//****仮
					}
				}
				GetComponent<Transform>()->SetPosition(pos);
			}
		}

		void Gimmick2_1::Action()
		{
			if (!m_MoveFlg)
			{
				//開く
				if (m_CloseFlg)
				{
					Vector3 pos = GetComponent<Transform>()->GetPosition();
					m_targetY = pos.y + m_Scale.y;

					m_CloseFlg = false;
					m_MoveFlg = true;

					//アタリ消す
					GetComponent<CollisionObb>()->SetUpdateActive(false);

				}
				//閉じる
				else
				{
					//もし凍ってるコアがあれば流すの中止
					/*
					auto WaterCoreGroup = GetStage()->GetSharedObjectGroup(L"WaterCore");
					for (auto v : WaterCoreGroup->GetGroupVector())
					{
						auto Ptr = dynamic_pointer_cast<Gimmick3>(v.lock());
						if (Ptr)
						{
							if (Ptr->GetFreeze())
							{
								return;
							}
						}
					}
					*/
					Vector3 pos = GetComponent<Transform>()->GetPosition();
					m_targetY = pos.y + -m_Scale.y;

					m_CloseFlg = true;
					m_MoveFlg = true;

				}
			}
		}

	//--------------------------------------------------------------------------------------
	//	class Water : public GameObject;
	//	用途: 水。コア部分以外
	//--------------------------------------------------------------------------------------
	Water::Water(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale,int num) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale),
		m_myNum(num)
	{}

	void Water::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_InitScale);
		Ptr->SetRotation(0, 0, 0);

		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionObb>();
		//影をつける（シャドウマップを描画する）
		//auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		//ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		//描画コンポーネントの設定
		//auto PtrDraw = AddComponent<PNTStaticDraw>();
		//描画するメッシュを設定
		//PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//描画するテクスチャを設定
		//PtrDraw->SetTextureResource(L"WATER_TX");

		//透明処理
		//SetAlphaActive(true);

		auto ObjPtr = GetStage()->AddGameObject<GameObject>();
		auto OPT = ObjPtr->AddComponent<Transform>();
		Vector3 ObPos = m_InitPos;
		ObPos.y += -m_InitScale.y / 2.5f;
		OPT->SetPosition(ObPos);
		OPT->SetScale(m_InitScale);
		OPT->SetRotation(0, 0, 0);
		auto OPD = ObjPtr->AddComponent<PNTStaticDraw>();
		OPD->SetMeshResource(L"DEFAULT_CUBE");
		OPD->SetTextureResource(L"WATER_TX");

		m_waterunder = ObjPtr;


	}

	//凍らす
	void Water::Freeze()
	{
		GetComponent<CollisionObb>()->SetUpdateActive(false);
		m_waterunder->GetComponent<PNTStaticDraw>()->SetTextureResource(L"ICE_TX");
		//SE再生
		GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("Freeze");

	}
	//溶かす
	void Water::Melt()
	{
		GetComponent<CollisionObb>()->SetUpdateActive(true);
		m_waterunder->GetComponent<PNTStaticDraw>()->SetTextureResource(L"WATER_TX");
		//SE再生
		GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("Water");

		OnPlayer();
	}
	//止める
	void Water::Stop()
	{
		GetComponent<CollisionObb>()->SetUpdateActive(false);

		//水の部分
		//Vector3 pos = m_waterunder->GetComponent<Transform>()->GetPosition();
		//pos.y += -m_InitScale.y;
		//m_waterunder->GetComponent<Transform>()->SetPosition(pos);
		m_waterunder->SetDrawActive(false);
	}
	//流す
	void Water::Flow()
	{
		//水の部分
		//Vector3 pos = m_waterunder->GetComponent<Transform>()->GetPosition();
		//pos.y += m_InitScale.y;
		//m_waterunder->GetComponent<Transform>()->SetPosition(pos);
		m_waterunder->SetDrawActive(true);

		GetComponent<CollisionObb>()->SetUpdateActive(true);

		OnPlayer();
	}

	void Water::OnPlayer() 
	{

		//プレイヤーが上にいるかどうか判定
		auto PlayerPtr = GetStage()->GetSharedGameObject<Player>(L"Player1", false);
		Vector3 Playerpos = PlayerPtr->GetComponent<Transform>()->GetPosition();

		Vector3 pos = GetComponent<Transform>()->GetPosition();
		Vector3 scale = GetComponent<Transform>()->GetScale();
		scale /= 2;
		//座標から判定
		if ((Playerpos.x < pos.x + scale.x && Playerpos.x > pos.x - scale.x) &&	/*X座標判定*/
			(Playerpos.z < pos.z + scale.z && Playerpos.z > pos.z - scale.z) 	/*Z座標判定*/
																				/*(Playerpos.y < pos.y + (scale.y * 3) && Playerpos.y > pos.y - scale.x)*/	/*Y座標判定*/
			)
		{
			//もしいたら地形ダメージ与える
			PlayerPtr->PlayerTerrainDamege();
		}

		//2体目
		//プレイヤーが上にいるかどうか判定
		PlayerPtr = GetStage()->GetSharedGameObject<Player>(L"Player2", false);
		Playerpos = PlayerPtr->GetComponent<Transform>()->GetPosition();
		//座標から判定
		if ((Playerpos.x < pos.x + scale.x && Playerpos.x > pos.x - scale.x) &&	/*X座標判定*/
			(Playerpos.z < pos.z + scale.z && Playerpos.z > pos.z - scale.z) 	/*Z座標判定*/
																				/*(Playerpos.y < pos.y + (scale.y * 3) && Playerpos.y > pos.y - scale.x)*/	/*Y座標判定*/
			)
		{
			//もしいたら地形ダメージ与える
			PlayerPtr->PlayerTerrainDamege();
		}
	}

	//--------------------------------------------------------------------------------------
	//	class WaterFall : public GameObject;
	//	用途: 滝
	//--------------------------------------------------------------------------------------
	WaterFall::WaterFall(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale)	
	{}

	void WaterFall::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_InitScale);
		Ptr->SetRotation(0, 0, 0);

		//衝突判定をつける
		AddComponent<CollisionObb>();

		GetStage()->AddGameObject<GameObject>();
		auto OPT = AddComponent<Transform>();
		OPT->SetPosition(m_InitPos);
		OPT->SetScale(m_InitScale);
		OPT->SetRotation(0, 0, 0);
		auto OPD = AddComponent<PNTStaticDraw>();
		OPD->SetMeshResource(L"DEFAULT_CUBE");
		OPD->SetTextureResource(L"WATER_TX");



	}

	//凍らす
	void WaterFall::Freeze()
	{
		GetComponent<CollisionObb>()->SetUpdateActive(true);
		GetComponent<PNTStaticDraw>()->SetTextureResource(L"ICE_TX");
		//SE再生
		GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("Freeze");
		//エフェクト停止
		for (auto v : m_ParticleIce)
		{
			v->StopParticle();
		}
		//エフェクト出現
		for (auto v : m_ParticleFire)
		{
			v->OnParticle(GetComponent<Transform>()->GetPosition(), Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(1.0f, 0.5f, 1.0f), Vector3(2.0f, 2.0f, 2.0f), L"FIRELIGHT_TX", false, 0.2f, 1, 2.0f);
		}
	}
	//溶かす
	void WaterFall::Melt()
	{
		GetComponent<CollisionObb>()->SetUpdateActive(true);
		GetComponent<PNTStaticDraw>()->SetTextureResource(L"WATER_TX");
		//SE再生
		GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("Water");

		OnPlayer();

		//エフェクト停止
		for (auto v : m_ParticleFire)
		{
			v->StopParticle();
		}
		//エフェクト出現
		for (auto v : m_ParticleIce)
		{
			v->OnParticle(GetComponent<Transform>()->GetPosition(), Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(1.0f, 0.5f, 1.0f), Vector3(2.0f, 2.0f, 2.0f), L"ICELIGHT_TX", false, 0.2f, 1, 2.0f);
		}

	}
	//止める
	void WaterFall::Stop()
	{
		//アタリ消す
		GetComponent<CollisionObb>()->SetUpdateActive(false);

		m_FlowFlg = false;

		//水の部分
		SetDrawActive(false);
		//エフェクト停止
		for (auto v : m_ParticleFire)
		{
			v->StopParticle();
		}
		for (auto v : m_ParticleIce)
		{
			v->StopParticle();
		}
	}
	//流す
	void WaterFall::Flow()
	{
		SetDrawActive(true);

		m_FlowFlg = true;

		//当たり戻す
		GetComponent<CollisionObb>()->SetUpdateActive(true);

		OnPlayer();
		//エフェクト出現
		for (auto v : m_ParticleIce)
		{
			v->OnParticle(GetComponent<Transform>()->GetPosition(), Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(1.0f, 0.5f, 1.0f), Vector3(2.0f, 2.0f, 2.0f), L"ICELIGHT_TX", false, 0.2f, 1, 2.0f);
		}

	}

	void WaterFall::OnPlayer()
	{

		//プレイヤーが上にいるかどうか判定
		auto PlayerPtr = GetStage()->GetSharedGameObject<Player>(L"Player1", false);
		Vector3 Playerpos = PlayerPtr->GetComponent<Transform>()->GetPosition();

		Vector3 pos = GetComponent<Transform>()->GetPosition();
		Vector3 scale = GetComponent<Transform>()->GetScale();
		scale /= 2;
		//座標から判定
		if ((Playerpos.x < pos.x + scale.x && Playerpos.x > pos.x - scale.x) &&	/*X座標判定*/
			(Playerpos.z < pos.z + scale.z && Playerpos.z > pos.z - scale.z) 	/*Z座標判定*/
																				/*(Playerpos.y < pos.y + (scale.y * 3) && Playerpos.y > pos.y - scale.x)*/	/*Y座標判定*/
			)
		{
			//もしいたら地形ダメージ与える
			PlayerPtr->PlayerTerrainDamege();
		}

		//2体目
		//プレイヤーが上にいるかどうか判定
		PlayerPtr = GetStage()->GetSharedGameObject<Player>(L"Player2", false);
		Playerpos = PlayerPtr->GetComponent<Transform>()->GetPosition();
		//座標から判定
		if ((Playerpos.x < pos.x + scale.x && Playerpos.x > pos.x - scale.x) &&	/*X座標判定*/
			(Playerpos.z < pos.z + scale.z && Playerpos.z > pos.z - scale.z) 	/*Z座標判定*/
																				/*(Playerpos.y < pos.y + (scale.y * 3) && Playerpos.y > pos.y - scale.x)*/	/*Y座標判定*/
			)
		{
			//もしいたら地形ダメージ与える
			PlayerPtr->PlayerTerrainDamege();
		}

	}

	void WaterFall::HitMagic(MagicType mt)
	{
		if (mt == IceFog && !m_FreezeFlg)
		{
			m_FreezeFlg = true;
			Freeze();
		}
		else if (mt == Fire && m_FreezeFlg)
		{
			m_FreezeFlg = false;
			Melt();
		}
	}

	//--------------------------------------------------------------------------------------
	//	class Gimmick3 : public GameObject;
	//	用途: 川。のコア部分。凍らせると水部分を凍らせる
	//--------------------------------------------------------------------------------------
	Gimmick3::Gimmick3(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale):
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale)
	{}

	void Gimmick3::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_InitScale);
		Ptr->SetRotation(0, 0, 0);

		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionObb>();
		//影をつける（シャドウマップを描画する）
		//auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		//ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		//描画コンポーネントの設定
		//auto PtrDraw = AddComponent<PNTStaticDraw>();
		//描画するメッシュを設定
		//PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//描画するテクスチャを設定
		//PtrDraw->SetTextureResource(L"WATER_TX");

		//透明処理
		//SetAlphaActive(true);

		auto ObjPtr = GetStage()->AddGameObject<GameObject>();
		auto OPT = ObjPtr->AddComponent<Transform>();
		Vector3 ObPos = m_InitPos;
		ObPos.y += -m_InitScale.y / 2.5f;
		OPT->SetPosition(ObPos);
		OPT->SetScale(m_InitScale);
		OPT->SetRotation(0, 0, 0);
		auto OPD = ObjPtr->AddComponent<PNTStaticDraw>();
		OPD->SetMeshResource(L"DEFAULT_CUBE");
		OPD->SetTextureResource(L"WATER_TX");

		m_waterunder = ObjPtr;
	}


	//魔法が当たった時
	void Gimmick3::HitMagic(MagicType MT)
	{
		//凍ってたら溶かす
		if (m_FreezeFlg && MT == Fire)
		{
			Melt();
			GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("Water");
			m_FreezeFlg = false;
		}

		//凍ってなかったら凍らせる
		if (!m_FreezeFlg && MT == IceFog)
		{
			Freeze();	
			//SE再生
			GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("Freeze");
			m_FreezeFlg = true;
		}
	}

	//凍らす
	void Gimmick3::Freeze()
	{
		//流れてるときのみ有効
		if (m_FlowFlg)
		{
			GetComponent<CollisionObb>()->SetUpdateActive(false);
			m_waterunder->GetComponent<PNTStaticDraw>()->SetTextureResource(L"ICE_TX");
			for (auto v : m_waters)
			{
				v->Freeze();
			}

			for (auto v : m_waterfalls)
			{
				v->Freeze();
			}

			//エフェクト停止
			for (auto v : m_ParticleIce)
			{
				v->StopParticle();
			}
			//エフェクト出現
			for (auto v : m_ParticleFire)
			{
				v->OnParticle(GetComponent<Transform>()->GetPosition(), Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(1.0f, 0.5f, 1.0f), Vector3(2.0f, 2.0f, 2.0f), L"FIRELIGHT_TX", false, 0.2f, 1, 2.0f);
			}
		}
	}

	//溶かす
	void Gimmick3::Melt()
	{
		//流れてるときのみ有効
		if (m_FlowFlg)
		{
			GetComponent<CollisionObb>()->SetUpdateActive(true);
			m_waterunder->GetComponent<PNTStaticDraw>()->SetTextureResource(L"WATER_TX");
			for (auto v : m_waters)
			{
				v->Melt();
			}

			for (auto v : m_waterfalls)
			{
				v->Melt();
			}
			OnPlayer();

			//エフェクト停止
			for (auto v : m_ParticleFire)
			{
				v->StopParticle();
			}
			//エフェクト出現
			for (auto v : m_ParticleIce)
			{
				v->OnParticle(GetComponent<Transform>()->GetPosition(), Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(1.0f, 0.5f, 1.0f), Vector3(2.0f, 2.0f, 2.0f), L"ICELIGHT_TX", false, 0.2f, 1, 2.0f);
			}
		}
	}

	//止める
	void Gimmick3::Stop()
	{
		//凍ってないときのみ有効
		if (!m_FreezeFlg)
		{
			//アタリ判定の部分
			GetComponent<CollisionObb>()->SetUpdateActive(false);

			//水の部分
			//Vector3 pos = m_waterunder->GetComponent<Transform>()->GetPosition();
			//pos.y += -m_InitScale.y;
			//m_waterunder->GetComponent<Transform>()->SetPosition(pos);

			m_waterunder->SetDrawActive(false);
			for (auto v : m_waters)
			{
				v->Stop();
			}
			for (auto v : m_waterfalls)
			{
				v->Stop();
			}
			//エフェクト停止
			for (auto v : m_ParticleFire)
			{
				v->StopParticle();
			}
			for (auto v : m_ParticleIce)
			{
				v->StopParticle();
			}
		}
	}

	//流す
	void Gimmick3::Flow()
	{
		if (!m_FlowFlg)
		{
			//アタリ判定の部分
			GetComponent<CollisionObb>()->SetUpdateActive(true);

			//水の部分
			//Vector3 pos = m_waterunder->GetComponent<Transform>()->GetPosition();
			//pos.y += m_InitScale.y;
			//m_waterunder->GetComponent<Transform>()->SetPosition(pos);

			m_waterunder->SetDrawActive(true);


			for (auto v : m_waters)
			{
				v->Flow();
			}
			for (auto v : m_waterfalls)
			{
				v->Flow();
			}
			OnPlayer();

			//エフェクト出現
			for (auto v : m_ParticleIce)
			{
				v->OnParticle(GetComponent<Transform>()->GetPosition(), Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(1.0f, 0.5f, 1.0f), Vector3(2.0f, 2.0f, 2.0f), L"ICELIGHT_TX", false, 0.2f, 1, 2.0f);
			}
		}
	}

	void Gimmick3::OnPlayer()
	{

		//プレイヤーが上にいるかどうか判定
		auto PlayerPtr = GetStage()->GetSharedGameObject<Player>(L"Player1", false);
		Vector3 Playerpos = PlayerPtr->GetComponent<Transform>()->GetPosition();

		Vector3 pos = GetComponent<Transform>()->GetPosition();
		Vector3 scale = GetComponent<Transform>()->GetScale();
		scale /= 2;
		//座標から判定
		if ((Playerpos.x < pos.x + scale.x && Playerpos.x > pos.x - scale.x) &&	/*X座標判定*/
			(Playerpos.z < pos.z + scale.z && Playerpos.z > pos.z - scale.z) 	/*Z座標判定*/
																				/*(Playerpos.y < pos.y + (scale.y * 3) && Playerpos.y > pos.y - scale.x)*/	/*Y座標判定*/
			)
		{
			//もしいたら地形ダメージ与える
			PlayerPtr->PlayerTerrainDamege();
		}

		//2体目
		//プレイヤーが上にいるかどうか判定
		PlayerPtr = GetStage()->GetSharedGameObject<Player>(L"Player2", false);
		Playerpos = PlayerPtr->GetComponent<Transform>()->GetPosition();
		//座標から判定
		if ((Playerpos.x < pos.x + scale.x && Playerpos.x > pos.x - scale.x) &&	/*X座標判定*/
			(Playerpos.z < pos.z + scale.z && Playerpos.z > pos.z - scale.z) 	/*Z座標判定*/
																				/*(Playerpos.y < pos.y + (scale.y * 3) && Playerpos.y > pos.y - scale.x)*/	/*Y座標判定*/
			)
		{
			//もしいたら地形ダメージ与える
			PlayerPtr->PlayerTerrainDamege();
		}
	}
	//--------------------------------------------------------------------------------------
	//	class Gimmick5 : public GameObject;
	//	用途: 炎。氷の魔法[Icefog]で消せる
	//--------------------------------------------------------------------------------------

	Gimmick5::Gimmick5(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_Scale(scale)
	{}

	void Gimmick5::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_Scale);
		Ptr->SetRotation(0, 0, 0);

		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionObb>();

		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"DEFAULT_SQUARE");
		//描画するテクスチャを設定
		PtrDraw->SetTextureResource(L"FIREGIMMICK5_0_TX");

		//透明処理
		SetAlphaActive(true);
		SetDrawLayer(1);
	}

	void Gimmick5::OnUpdate()
	{
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time > m_IntervalTime)
		{
			m_time = 0;
			m_nowTexture++;
			if (m_nowTexture > 2)
			{
				m_nowTexture = 0;
			}

			switch (m_nowTexture)
			{
			case 0:
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"FIREGIMMICK5_0_TX");
				break;
			case 1:
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"FIREGIMMICK5_1_TX");
				break;
			case 2:
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"FIREGIMMICK5_2_TX");
				break;
			default:
				break;
			}
		}
	}

	void Gimmick5::Delete(MagicType MT)
	{
		if (MT == IceFog)
		{
			m_ActiveFlg = false;
			SetDrawActive(false);
			GetComponent<CollisionObb>()->SetUpdateActive(false);
			GetComponent<Transform>()->SetPosition(0, -10, 0);
			//SE再生
			GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("Freeze");

			//アップデート停止
			SetUpdateActive(false);
			//エフェクト停止
			for (auto v : m_Particle)
			{
				v->StopParticle();
			}

		}
	}
}
//end basecross
