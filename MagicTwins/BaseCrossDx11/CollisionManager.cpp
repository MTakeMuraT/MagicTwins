#include "stdafx.h"
#include "Project.h"

namespace basecross {
	CollisionManager::CollisionManager(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
	{}
	void CollisionManager::OnCreate()
	{
		//文字列をつける
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 64.0f, 640.0f, 480.0f));
		PtrString->SetFont(L"", 40);

		//**************************//
		//動かないオブジェクトの情報取得
		//ゴールの座標持ってくる
		GetGoal();
		//魔導書の情報持ってくる
		GetMagicBook();
		//**************************//

	}

	void CollisionManager::OnUpdate()
	{
		//情報取得動くオブジェクト
		//プレイヤーの座標持ってくる
		GetPlayer();
		GetMagicBoal();

		//プレイヤーとゴール判定
		if (CollisionTest(PlayerPos1, PlayerScale1, GoalPos, GoalScale) ||
			CollisionTest(PlayerPos2, PlayerScale2, GoalPos, GoalScale))
		{
			PlayerToGoal();
		}

		int count = 0;

		//プレイヤーと魔導書の判定
		for (auto v : MagicBooksPos)
		{	
			//どっち当たってるか
			int PlayerCount = 0;
			if (CollisionTest(PlayerPos1, PlayerScale1, MagicBooksPos[count],MagicBooksScale[count]))
			{
				PlayerToMagicBook(count,PlayerCount);
			}

			PlayerCount++;

			if(CollisionTest(PlayerPos2, PlayerScale2, MagicBooksPos[count], MagicBooksScale[count]))
			{
				PlayerToMagicBook(count, PlayerCount);
			}
			count++;
		}
		count = 0;

		//プレイヤーとエネミーのあたり判定
		auto EG = GetStage()->GetSharedObjectGroup(L"Enemy", false);
		auto EGV = EG->GetGroupVector();
		for (auto v : EGV)
		{
			auto Ptr = dynamic_pointer_cast<GameObject>(v.lock());
			Vector3 PPos = Ptr->GetComponent<Transform>()->GetPosition();
			Vector3 PScale = Ptr->GetComponent<Transform>()->GetScale();
			//プレイヤー１が当たる
			if (CollisionTest(PlayerPos1, PlayerScale1, PPos, PScale))
			{
				if (GetStage()->GetSharedGameObject<Player>(L"Player1")->GetActive())
				{
					//プレイヤー側の処理
					PlayerToEnemy(1);
					//エネミー側の処理、エネミーの種類が増えたら追加する
					auto enemyPtr = dynamic_pointer_cast<Enemy>(v.lock());
					if (enemyPtr && !enemyPtr->GetStopFlg())
					{
						enemyPtr->ResetPos();
					}
				}
			}
			//プレイヤー２が当たる
			else if (CollisionTest(PlayerPos2, PlayerScale2, PPos, PScale))
			{
				if (GetStage()->GetSharedGameObject<Player>(L"Player2")->GetActive())
				{
					//プレイヤー側の処理
					PlayerToEnemy(2);
					//エネミー側の処理、エネミーの種類が増えたら追加する
					auto enemyPtr = dynamic_pointer_cast<Enemy>(v.lock());
					if (enemyPtr && !enemyPtr->GetStopFlg())
					{
						enemyPtr->ResetPos();
					}
				}
			}
		}
		
		//プレイヤーとスコアアイテムのあたり判定
		auto SCG = GetStage()->GetSharedObjectGroup(L"ScoreItem", false);
		auto SCGV = SCG->GetGroupVector();
		for (auto v : SCGV)
		{
			auto Ptr = dynamic_pointer_cast<ScoreItem>(v.lock());
			Vector3 PPos = Ptr->GetComponent<Transform>()->GetPosition();
			Vector3 PScale = Ptr->GetComponent<Transform>()->GetScale();
			//プレイヤー１が当たる
			if (CollisionTest(PlayerPos1, PlayerScale1, PPos, PScale) && Ptr->GetActive())
			{
				if (GetStage()->GetSharedGameObject<Player>(L"Player1")->GetActive())
				{
					Ptr->Delete();
					//****スコアアイテム加算
					m_scoreItemCount++;
					//****スコアアイテム加算
				}
			}
			//プレイヤー２が当たる
			else if (CollisionTest(PlayerPos2, PlayerScale2, PPos, PScale) && Ptr->GetActive())
			{
				if (GetStage()->GetSharedGameObject<Player>(L"Player2")->GetActive())
				{
					Ptr->Delete();
					//****スコアアイテム加算
					m_scoreItemCount++;
					//****スコアアイテム加算
				}
			}
		}
		
		//魔法とオブジェクトのアタリ判定
		auto Objects = GetStage()->GetSharedObjectGroup(L"MagicObjects")->GetGroupVector();
		for (auto v : Objects)
		{
			auto Ptr = dynamic_pointer_cast<GameObject>(v.lock());
			Vector3 PPos = Ptr->GetComponent<Transform>()->GetPosition();
			Vector3 PScale = Ptr->GetComponent<Transform>()->GetScale();

			//一個目の魔法当たる
			if (CollisionTest(MagicPos1, MagicScale1, PPos, PScale))
			{
				MagicToObj(1,shared_ptr<GameObject>(v));
			}
			//二個目の魔法当たる
			if (CollisionTest(MagicPos2, MagicScale2, PPos, PScale))
			{
				MagicToObj(2, shared_ptr<GameObject>(v));
			}

		}
	}

//------------------------------------------------------------------------------------------------

	//プレイヤーの情報持ってくる
	void CollisionManager::GetPlayer()
	{
		auto PlayerP = GetStage()->GetSharedGameObject<Player>(L"Player1",false);
		auto PlayerP2 = GetStage()->GetSharedGameObject<Player>(L"Player2", false);

		PlayerPos1 = PlayerP->GetComponent<Transform>()->GetPosition();
		PlayerScale1 = PlayerP->GetComponent<Transform>()->GetScale();

		PlayerPos2 = PlayerP2->GetComponent<Transform>()->GetPosition();
		PlayerScale2 = PlayerP2->GetComponent<Transform>()->GetScale();

	}

	//ゴールの情報持ってくる
	void CollisionManager::GetGoal()
	{
		auto GoalP = GetStage()->GetSharedGameObject<Goal>(L"Goal", false);
		GoalPos = GoalP->GetComponent<Transform>()->GetPosition();
		GoalScale = GoalP->GetComponent<Transform>()->GetScale();
	}

	//魔導書の情報持ってくる
	void CollisionManager::GetMagicBook()
	{
		auto MBGroup = GetStage()->GetSharedObjectGroup(L"MagicBook");
		auto MBGVec = MBGroup->GetGroupVector();
		for (auto Ptr : MBGVec)
		{
			if (!Ptr.expired())
			{
				auto MBP = dynamic_pointer_cast<MagicBook>(Ptr.lock());
				MagicBooksPos.push_back(MBP->GetPos());
				MagicBooksScale.push_back(MBP->GetScale() * 0.8f);
			}
		}
	}

	//魔法の情報持ってくる
	void CollisionManager::GetMagicBoal()
	{
		auto Magic1 = GetStage()->GetSharedGameObject<MagicBoal>(L"MagicBoal1", false);
		auto Magic2 = GetStage()->GetSharedGameObject<MagicBoal>(L"MagicBoal2", false);

		MagicPos1 = Magic1->GetComponent<Transform>()->GetPosition();
		MagicScale1 = Magic1->GetComponent<Transform>()->GetScale();
		MagicFlg1 = Magic1->GetActive();

		MagicPos2 = Magic2->GetComponent<Transform>()->GetPosition();
		MagicScale2 = Magic2->GetComponent<Transform>()->GetScale();
		MagicFlg2 = Magic2->GetActive();
	}

	//プレイヤーとゴールが当たった処理
	void CollisionManager::PlayerToGoal()
	{
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		auto num = GetStage()->GetSharedGameObject<LimitTime>(L"LimitTime", false)->GetClearTime();
		ScenePtr->SetClearTime(num);
		ScenePtr->SetScoreItemCount(m_scoreItemCount);
		//PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"Result");

		GetStage()->GetSharedGameObject<GameObject>(L"GoalObj")->SetDrawActive(true);
	}

	//プレイヤーと魔導書の当たった処理
	void CollisionManager::PlayerToMagicBook(int count,int Playercount)
	{
		auto MBGroup = GetStage()->GetSharedObjectGroup(L"MagicBook");
		auto MBGVec = MBGroup->GetGroupVector();
		//プレイヤーがアクティブなら取得
		bool P1 = GetStage()->GetSharedGameObject<Player>(L"Player1", false)->GetActive();
		bool P2 = GetStage()->GetSharedGameObject<Player>(L"Player2", false)->GetActive();
		if ((Playercount == 0 && P1) || (Playercount == 1 && P2))
		{
			dynamic_pointer_cast<MagicBook>(MBGVec[count].lock())->GetPlayer();
		}
	}

	//プレイヤーとエネミーが当たった処理
	void CollisionManager::PlayerToEnemy(int Playernum)
	{
		if (Playernum == 1)
		{
			GetStage()->GetSharedGameObject<Player>(L"Player1", false)->PlayerDamege();
			GetStage()->GetSharedGameObject<Player>(L"Player1", false)->SetMagic(None);
		}
		else if (Playernum == 2)
		{
			GetStage()->GetSharedGameObject<Player>(L"Player2", false)->PlayerDamege();
			GetStage()->GetSharedGameObject<Player>(L"Player1", false)->SetMagic(None);

		}
	}

	//魔法とオブジェクトの当たった処理
	void CollisionManager::MagicToObj(int num,shared_ptr<GameObject> otherObj)
	{
		if (num == 1)
		{
			bool HitFlg = true;
			auto MaBo = GetStage()->GetSharedGameObject<MagicBoal>(L"MagicBoal1", false);
			//氷のギミック
			if (dynamic_pointer_cast<Gimmick1>(otherObj))
			{
				auto Ptr = dynamic_pointer_cast<Gimmick1>(otherObj);
				if (Ptr->GetActive())
				{
					Ptr->Delete(MaBo->GetMagicType());
					HitFlg = true;
				}
				else
				{
					HitFlg = false;
				}
			}
			//風車
			else if (dynamic_pointer_cast<Gimmick2>(otherObj))
			{
				auto Ptr = dynamic_pointer_cast<Gimmick2>(otherObj);
				if (Ptr->GetActive())
				{
					Ptr->Delete(MaBo->GetMagicType());
					HitFlg = true;
				}
				else
				{
					HitFlg = false;
				}
			}
			//炎
			else if (dynamic_pointer_cast<Gimmick5>(otherObj))
			{
				auto Ptr = dynamic_pointer_cast<Gimmick5>(otherObj);
				if (Ptr->GetActive())
				{
					Ptr->Delete(MaBo->GetMagicType());
					HitFlg = true;
				}
				else
				{
					HitFlg = false;
				}

			}
			//川のコア
			else if (dynamic_pointer_cast<Gimmick3>(otherObj))
			{
				auto Ptr = dynamic_pointer_cast<Gimmick3>(otherObj);
				if (Ptr->GetFlow())
				{
					Ptr->HitMagic(MaBo->GetMagicType());
					HitFlg = true;
				}
				else
				{
					HitFlg = false;
				}

			}
			//滝
			else if (dynamic_pointer_cast<WaterFall>(otherObj))
			{
				auto Ptr = dynamic_pointer_cast<WaterFall>(otherObj);
				if (Ptr->GetFlow())
				{
					Ptr->HitMagic(MaBo->GetMagicType());
					HitFlg = true;
				}
				else
				{
					HitFlg = false;
				}
			}
			//エネミー
			else if (dynamic_pointer_cast<Enemy>(otherObj))
			{
				auto Ptr = dynamic_pointer_cast<Enemy>(otherObj);
				//Ptr->ResetPos();
				if (!Ptr->GetStopFlg())
				{
					Ptr->StopEnemy(1);
					HitFlg = true;
				}
				else
				{
					HitFlg = false;
				}

			}

			if (HitFlg)
			{
				MaBo->SetActive(false, None);
			}
		}
		else if (num == 2)
		{
			bool HitFlg = true;
			auto MaBo = GetStage()->GetSharedGameObject<MagicBoal>(L"MagicBoal2", false);
			//氷のギミック
			if (dynamic_pointer_cast<Gimmick1>(otherObj))
			{
				auto Ptr = dynamic_pointer_cast<Gimmick1>(otherObj);
				if (Ptr->GetActive())
				{
					Ptr->Delete(MaBo->GetMagicType());
					HitFlg = true;
				}
				else
				{
					HitFlg = false;
				}
			}
			//風車
			else if (dynamic_pointer_cast<Gimmick2>(otherObj))
			{
				auto Ptr = dynamic_pointer_cast<Gimmick2>(otherObj);
				if (Ptr->GetActive())
				{
					Ptr->Delete(MaBo->GetMagicType());
					HitFlg = true;
				}
				else
				{
					HitFlg = false;
				}
			}
			//炎
			else if (dynamic_pointer_cast<Gimmick5>(otherObj))
			{
				auto Ptr = dynamic_pointer_cast<Gimmick5>(otherObj);
				if (Ptr->GetActive())
				{
					Ptr->Delete(MaBo->GetMagicType());
					HitFlg = true;
				}
				else
				{
					HitFlg = false;
				}

			}
			//川のコア
			else if (dynamic_pointer_cast<Gimmick3>(otherObj))
			{
				auto Ptr = dynamic_pointer_cast<Gimmick3>(otherObj);
				if (Ptr->GetFlow())
				{
					Ptr->HitMagic(MaBo->GetMagicType());
					HitFlg = true;
				}
				else
				{
					HitFlg = false;
				}

			}
			//滝
			else if (dynamic_pointer_cast<WaterFall>(otherObj))
			{
				auto Ptr = dynamic_pointer_cast<WaterFall>(otherObj);
				if (Ptr->GetFlow())
				{
					Ptr->HitMagic(MaBo->GetMagicType());
					HitFlg = true;
				}
				else
				{
					HitFlg = false;
				}
			}
			//エネミー
			else if (dynamic_pointer_cast<Enemy>(otherObj))
			{
				auto Ptr = dynamic_pointer_cast<Enemy>(otherObj);
				//Ptr->ResetPos();
				if (!Ptr->GetStopFlg())
				{
					Ptr->StopEnemy(2);
					HitFlg = true;
				}
				else
				{
					HitFlg = false;
				}

			}

			if (HitFlg)
			{
				MaBo->SetActive(false, None);
			}
		}
	}

	//アタリ判定関数
	bool CollisionManager::CollisionTest(Vector3 pos1, Vector3 scale1, Vector3 pos2, Vector3 scale2)
	{
		float dx = pos2.x - pos1.x;
		float dy = pos2.y - pos1.y;
		float dz = pos2.z - pos1.z;
		float dhalf = (scale1.x + scale2.x)/2;
		dhalf *= 1.3f;
		if ((dx*dx + dy*dy + dz*dz) < dhalf*dhalf)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}