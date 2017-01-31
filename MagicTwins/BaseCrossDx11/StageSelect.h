#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�X�e�[�W�Z���N�g
	//--------------------------------------------------------------------------------------
	class  StageSelect: public Stage {
		//���\�[�X�̍쐬
		void CreateResourses();
		//�r���[�̍쐬
		void CreateViewLight();
		//�w�i�摜�쐬
		void CreateBack();
		//�Z���N�g���S
		void CreateSelectLogo();
		//�{�^���쐬
		void CreateButtons();
		//�X�e�[�W�C���[�W�쐬
		void CreateStageImageFrame();
		//�V�[���J��
		void SceneChange();
		//�����(��)
		void Left();
		//�E���(��)
		void Right();
		//�X�e�[�W�C���[�W
		void CreateStageImage();

		//�X�e�[�W���S�쐬
		void CreateStageLogo();

		//�ő�l
		unsigned int m_MaxStageNum = 10;
		//���ݑI�𒆂̐���
		unsigned int m_StageNum = 0;

		//�I������Ƃ��̒���
		bool m_flag;

		//�{�^���������Ƃ��̏���
		bool m_SelectFlg = false;

		//�X�e�[�W�C���[�W
		shared_ptr<GameObject> m_StageImage;
		//��]���Ă�ƌ��������ăT�C�Y�ύX����B�ǂ����X�v���C�g�ł͉�]���ł��Ȃ��炵��
		//��]��
		bool m_StageImageRotFlg = false;
		//�r���܂ł�������
		bool m_SIHalfFlg = false;
		//�C���[�W��]
		void RotStageImage();
	public:
		//�\�z�Ɣj��
		StageSelect() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

	//--------------------------------------------------------------------------------------
	//	class CharEye : public GameObject;
	//	�p�r: �L�����̖�
	//	�ݒ肵�����Ԃ��Ƃɏu�����邩���肵�Ȃ���u��
	//--------------------------------------------------------------------------------------

	class CharEye : public GameObject
	{
	private :
		//�����ʒu
		Vector3 m_Pos;
		//�ڂ��ς��Ԋu
		const float m_EyeCloseTime = 0.05f;
		//�Ԋu
		const float m_IntarvalEyeTime = 1.0f;
		//�v�Z�p
		float m_CountTime = 0;
		//�ڕ��Ă�t���O
		bool m_EyeCloseFlg = false;
		//�m��
		const float m_Par = 50.0f;
		int m_EyeCloseState = 0;
		//0�J�� 1�ڔ��� 2�ڕ�
		vector<shared_ptr<GameObject>> m_Eyes;

		//2�L�����ڂ��ǂ���
		bool m_2PlayerFlg = false;
	public :
		CharEye(const shared_ptr<Stage>& StagePtr,Vector3 pos,bool flg);
		void OnCreate() override;
		void OnUpdate() override;

		void EyeClose();
	};
}