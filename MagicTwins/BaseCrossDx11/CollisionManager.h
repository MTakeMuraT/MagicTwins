
#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class CollisionManager : public GameObject;
	//	�p�r: �����蔻��܂Ƃ߂ď���
	//--------------------------------------------------------------------------------------
	class CollisionManager : public GameObject
	{
	private :
		//�v���C���[�P
		Vector3 PlayerPos1;
		Vector3 PlayerScale1;
		//�v���C���[�Q
		Vector3 PlayerPos2;
		Vector3 PlayerScale2;
		//�S�[��
		Vector3 GoalPos;
		Vector3 GoalScale;
	public :
		CollisionManager(const shared_ptr<Stage>& StagePtr);
		virtual void OnUpdate() override;
		//�v���C���[�̍��W�����Ă���
		void GetPlayer();
		//�S�[���̍��W�����Ă���
		void GetGoal();
		//�v���C���[�ƃS�[���̓�����������
		void PlayerToGoal();
		//�A�^������v�Z�֐�(����)
		bool CollisionTest(Vector3 pos1, Vector3 scale1, Vector3 pos2, Vector3 scale2);
	};

}