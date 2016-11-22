#include "stdafx.h"
#include "Project.h"

namespace basecross {
	CollisionManager::CollisionManager(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
	{}
	void CollisionManager::OnCreate()
	{
		//�����������
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 64.0f, 640.0f, 480.0f));
		PtrString->SetFont(L"", 40);

		//**************************//
		//�����Ȃ��I�u�W�F�N�g�̏��擾
		//�S�[���̍��W�����Ă���
		GetGoal();
		//�������̏�񎝂��Ă���
		GetMagicBook();
		//**************************//

	}

	void CollisionManager::OnUpdate()
	{
		//���擾�����I�u�W�F�N�g
		//�v���C���[�̍��W�����Ă���
		GetPlayer();
		GetMagicBoal();

		//�v���C���[�ƃS�[������
		if (CollisionTest(PlayerPos1, PlayerScale1, GoalPos, GoalScale) ||
			CollisionTest(PlayerPos2, PlayerScale2, GoalPos, GoalScale))
		{
			PlayerToGoal();
		}

		int count = 0;

		//�v���C���[�Ɩ������̔���
		for (auto v : MagicBooksPos)
		{	
			if (CollisionTest(PlayerPos1, PlayerScale1, MagicBooksPos[count],MagicBooksScale[count] ) ||
				CollisionTest(PlayerPos2, PlayerScale2, MagicBooksPos[count], MagicBooksScale[count]))
			{
				PlayerToMagicBook(count);
			}
			count++;
		}
		count = 0;

		//�v���C���[�ƃG�l�~�[�̂����蔻��
		auto EG = GetStage()->GetSharedObjectGroup(L"Enemy", false);
		auto EGV = EG->GetGroupVector();
		for (auto v : EGV)
		{
			auto Ptr = dynamic_pointer_cast<Enemy>(v.lock());
			Vector3 PPos = Ptr->GetComponent<Transform>()->GetPosition();
			Vector3 PScale = Ptr->GetComponent<Transform>()->GetScale();
			//�v���C���[�P��������
			if (CollisionTest(PlayerPos1, PlayerScale1, PPos, PScale) && !Ptr->GetStopFlg())
			{
				if (GetStage()->GetSharedGameObject<Player>(L"Player1")->GetActive())
				{
					PlayerToEnemy(1);
					Ptr->ResetPos();
				}
			}
			//�v���C���[�Q��������
			else if (CollisionTest(PlayerPos2, PlayerScale2, PPos, PScale) && !Ptr->GetStopFlg())
			{
				if (GetStage()->GetSharedGameObject<Player>(L"Player2")->GetActive())
				{
					PlayerToEnemy(2);
					Ptr->ResetPos();
				}
			}
		}
		
		//�v���C���[�ƃX�R�A�A�C�e���̂����蔻��
		auto SCG = GetStage()->GetSharedObjectGroup(L"ScoreItem", false);
		auto SCGV = SCG->GetGroupVector();
		for (auto v : SCGV)
		{
			auto Ptr = dynamic_pointer_cast<ScoreItem>(v.lock());
			Vector3 PPos = Ptr->GetComponent<Transform>()->GetPosition();
			Vector3 PScale = Ptr->GetComponent<Transform>()->GetScale();
			//�v���C���[�P��������
			if (CollisionTest(PlayerPos1, PlayerScale1, PPos, PScale) && Ptr->GetActive())
			{
				if (GetStage()->GetSharedGameObject<Player>(L"Player1")->GetActive())
				{
					Ptr->Delete();
					//****�X�R�A�A�C�e�����Z
					m_scoreItemCount++;
					//****�X�R�A�A�C�e�����Z
				}
			}
			//�v���C���[�Q��������
			else if (CollisionTest(PlayerPos2, PlayerScale2, PPos, PScale) && Ptr->GetActive())
			{
				if (GetStage()->GetSharedGameObject<Player>(L"Player2")->GetActive())
				{
					Ptr->Delete();
					//****�X�R�A�A�C�e�����Z
					m_scoreItemCount++;
					//****�X�R�A�A�C�e�����Z
				}
			}
		}
		
		//���@�ƃI�u�W�F�N�g�̃A�^������
		auto Objects = GetStage()->GetSharedObjectGroup(L"MagicObjects")->GetGroupVector();
		for (auto v : Objects)
		{
			auto Ptr = dynamic_pointer_cast<GameObject>(v.lock());
			Vector3 PPos = Ptr->GetComponent<Transform>()->GetPosition();
			Vector3 PScale = Ptr->GetComponent<Transform>()->GetScale();

			//��ڂ̖��@������
			if (CollisionTest(MagicPos1, MagicScale1, PPos, PScale))
			{
				MagicToObj(1,shared_ptr<GameObject>(v));
			}
			//��ڂ̖��@������
			if (CollisionTest(MagicPos2, MagicScale2, PPos, PScale))
			{
				MagicToObj(2, shared_ptr<GameObject>(v));
			}

		}
	}

//------------------------------------------------------------------------------------------------

	//�v���C���[�̏�񎝂��Ă���
	void CollisionManager::GetPlayer()
	{
		auto PlayerP = GetStage()->GetSharedGameObject<Player>(L"Player1",false);
		auto PlayerP2 = GetStage()->GetSharedGameObject<Player>(L"Player2", false);

		PlayerPos1 = PlayerP->GetComponent<Transform>()->GetPosition();
		PlayerScale1 = PlayerP->GetComponent<Transform>()->GetScale();

		PlayerPos2 = PlayerP2->GetComponent<Transform>()->GetPosition();
		PlayerScale2 = PlayerP2->GetComponent<Transform>()->GetScale();

	}

	//�S�[���̏�񎝂��Ă���
	void CollisionManager::GetGoal()
	{
		auto GoalP = GetStage()->GetSharedGameObject<Goal>(L"Goal", false);
		GoalPos = GoalP->GetComponent<Transform>()->GetPosition();
		GoalScale = GoalP->GetComponent<Transform>()->GetScale();
	}

	//�������̏�񎝂��Ă���
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

	//���@�̏�񎝂��Ă���
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

	//�v���C���[�ƃS�[����������������
	void CollisionManager::PlayerToGoal()
	{
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		auto num = GetStage()->GetSharedGameObject<LimitTime>(L"LimitTime", false)->GetClearTime();
		ScenePtr->SetClearTime(num);
		ScenePtr->SetScoreItemCount(m_scoreItemCount);
		PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"Result");

	}

	//�v���C���[�Ɩ������̓�����������
	void CollisionManager::PlayerToMagicBook(int count)
	{
		auto MBGroup = GetStage()->GetSharedObjectGroup(L"MagicBook");
		auto MBGVec = MBGroup->GetGroupVector();
		dynamic_pointer_cast<MagicBook>(MBGVec[count].lock())->GetPlayer();
	}

	//�v���C���[�ƃG�l�~�[��������������
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

	//���@�ƃI�u�W�F�N�g�̓�����������
	void CollisionManager::MagicToObj(int num,shared_ptr<GameObject> otherObj)
	{
		if (num == 1)
		{
			bool HitFlg = false;
			auto MaBo = GetStage()->GetSharedGameObject<MagicBoal>(L"MagicBoal1", false);
			//�X�̃M�~�b�N
			if (dynamic_pointer_cast<Gimmick1>(otherObj))
			{
				auto Ptr = dynamic_pointer_cast<Gimmick1>(otherObj);
				if (Ptr->GetActive())
				{
					Ptr->Delete(MaBo->GetMagicType());
					HitFlg = true;
				}
			}
			//����
			else if (dynamic_pointer_cast<Gimmick2>(otherObj))
			{
				auto Ptr = dynamic_pointer_cast<Gimmick2>(otherObj);
				if (Ptr->GetActive())
				{
					Ptr->Delete(MaBo->GetMagicType());
					HitFlg = true;
				}
			}
			//��
			else if (dynamic_pointer_cast<Gimmick5>(otherObj))
			{
				auto Ptr = dynamic_pointer_cast<Gimmick5>(otherObj);
				if (Ptr->GetActive())
				{
					Ptr->Delete(MaBo->GetMagicType());
					HitFlg = true;
				}
			}
			//��̃R�A
			else if (dynamic_pointer_cast<Gimmick3>(otherObj))
			{
				auto Ptr = dynamic_pointer_cast<Gimmick3>(otherObj);
				if (Ptr->GetFlow())
				{
					Ptr->HitMagic(MaBo->GetMagicType());
					HitFlg = true;
				}
			}
			//�G�l�~�[
			else if (dynamic_pointer_cast<Enemy>(otherObj))
			{
				auto Ptr = dynamic_pointer_cast<Enemy>(otherObj);
				//Ptr->ResetPos();
				if (!Ptr->GetStopFlg())
				{
					Ptr->StopEnemy();
					HitFlg = true;
				}
			}
			if (HitFlg)
			{
				MaBo->SetActive(false, None);
			}
		}
		else if (num == 2)
		{
			bool HitFlg = false;
			auto MaBo = GetStage()->GetSharedGameObject<MagicBoal>(L"MagicBoal2", false);
			//�X�̃M�~�b�N
			if (dynamic_pointer_cast<Gimmick1>(otherObj))
			{
				auto Ptr = dynamic_pointer_cast<Gimmick1>(otherObj);
				if (Ptr->GetActive())
				{
					Ptr->Delete(MaBo->GetMagicType());
					HitFlg = true;
				}
			}
			//����
			else if (dynamic_pointer_cast<Gimmick2>(otherObj))
			{
				auto Ptr = dynamic_pointer_cast<Gimmick2>(otherObj);
				if (Ptr->GetActive())
				{
					Ptr->Delete(MaBo->GetMagicType());
					HitFlg = true;
				}
			}
			//��
			else if (dynamic_pointer_cast<Gimmick5>(otherObj))
			{
				auto Ptr = dynamic_pointer_cast<Gimmick5>(otherObj);
				if (Ptr->GetActive())
				{
					Ptr->Delete(MaBo->GetMagicType());
					HitFlg = true;
				}
			}
			//��̃R�A
			else if (dynamic_pointer_cast<Gimmick3>(otherObj))
			{
				auto Ptr = dynamic_pointer_cast<Gimmick3>(otherObj);
				if (Ptr->GetFlow())
				{
					Ptr->HitMagic(MaBo->GetMagicType());
					HitFlg = true;
				}
			}
			//�G�l�~�[
			else if (dynamic_pointer_cast<Enemy>(otherObj))
			{
				auto Ptr = dynamic_pointer_cast<Enemy>(otherObj);
				//Ptr->ResetPos();
				if (!Ptr->GetStopFlg())
				{
					Ptr->StopEnemy();
					HitFlg = true;
				}
			}
			if (HitFlg)
			{
				MaBo->SetActive(false, None);
			}
		}
	}

	//�A�^������֐�
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