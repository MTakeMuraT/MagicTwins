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
	}

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

	//�v���C���[�ƃS�[����������������
	void CollisionManager::PlayerToGoal()
	{
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"Result");

	}

	//�v���C���[�Ɩ������̓�����������
	void CollisionManager::PlayerToMagicBook(int count)
	{
		auto MBGroup = GetStage()->GetSharedObjectGroup(L"MagicBook");
		auto MBGVec = MBGroup->GetGroupVector();
		dynamic_pointer_cast<MagicBook>(MBGVec[count].lock())->GetPlayer();
	}

	//�A�^������֐�
	bool CollisionManager::CollisionTest(Vector3 pos1, Vector3 scale1, Vector3 pos2, Vector3 scale2)
	{
		float dx = pos2.x - pos1.x;
		float dy = pos2.y - pos1.y;
		float dz = pos2.z - pos1.z;
		float dhalf = scale1.x + scale2.x;
		//������ƒ���
		dhalf *= 0.7f;
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