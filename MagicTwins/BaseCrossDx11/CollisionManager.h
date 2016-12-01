
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
		//������
		vector<Vector3> MagicBooksPos;
		vector<Vector3> MagicBooksScale;
		//���@1
		Vector3 MagicPos1;
		Vector3 MagicScale1;
		bool MagicFlg1;
		//���@2
		Vector3 MagicPos2;
		Vector3 MagicScale2;
		bool MagicFlg2;


		//�X�R�A�A�C�e���擾��
		unsigned int m_scoreItemCount = 0;
	public :
		CollisionManager(const shared_ptr<Stage>& StagePtr);
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//�v���C���[�̍��W�����Ă���
		void GetPlayer();
		//�S�[���̍��W�����Ă���
		void GetGoal();
		//�������̏�񎝂��Ă���
		void GetMagicBook();
		//���@�̏�񎝂��Ă���
		void GetMagicBoal();

		//�v���C���[�ƃS�[���̓�����������
		void PlayerToGoal();
		//�v���C���[�Ɩ������̓�����������
		void PlayerToMagicBook(int count,int Playercount);
		//�v���C���[�ƃG�l�~�[��������������
		void PlayerToEnemy(int Playernum);
		//���@�ƃI�u�W�F�N�g�̓�����������
		void MagicToObj(int num,shared_ptr<GameObject> otherObj);

		//�A�^������v�Z�֐�(����)
		bool CollisionTest(Vector3 pos1, Vector3 scale1, Vector3 pos2, Vector3 scale2);
	};

}