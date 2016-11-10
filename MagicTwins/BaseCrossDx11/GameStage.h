/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//���\�[�X�̍쐬
		void CreateResourses();
		//�r���[�̍쐬
		void CreateViewLight();
		//�v���[�g�̍쐬
		void CreatePlate();
		//�������ԍ쐬
		void CreateLimitTime();
		//�R���W�����}�l�[�W���[�쐬
		void CreateCollisionManager();
		/*
		//�X�e�[�W�\�z�֘A-----------------
		//�{�b�N�X
		void CreateBox(vector<Vector3> pos, vector<Vector3> scale, vector<Vector3> rot);
		//�S�[���쐬
		void CreateGoal(Vector3 pos, Vector3 scale);
		//�v���C���[�̍쐬
		void CreatePlayer(Vector3 pos);
		//�v���C���[�̍쐬�Q�̖�
		void CreatePlayer2(Vector3 pos);

		//�������쐬������MagicType�̏��ɐ���
		//void CreateMagicBook(vector<Vector3> pos);

		//���悤�Ǝv�������ǎ��Ԃ����邩��p�X
		void CreateMagicFire(Vector3 pos);
		void CreateMagicIceFog(Vector3 pos);

		//�M�~�b�N��
		//�X(�M�~�b�N�P)
		void CreateIce(vector<Vector3> pos, vector<Vector3> scale);
		//��(�M�~�b�N�T)
		void CreateFire(vector<Vector3> pos, vector<Vector3> scale);
		//����(�M�~�b�N�Q)
		void CreateWindMill(vector<Vector3> pos, vector<Vector3> scale);
		//��
		void CreateWaters(vector<Vector3> pos, vector<Vector3> scale, vector<int> num);
		//��̃R�A(�M�~�b�N�R)
		void CreateWaterCore(vector<Vector3> pos, vector<Vector3> scale);
		*/
		//�M�~�b�N��
		//�X�e�[�W�\�z�֘A-----------------
	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate() override;

	};


}
//end basecross

