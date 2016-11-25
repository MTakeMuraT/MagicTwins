/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	//	class Goal : public GameObject;
	//	�p�r: �S�[��
	//--------------------------------------------------------------------------------------
	class Goal : public GameObject
	{
	private :
		Vector3 m_InitPos;
		Vector3 m_Scale;
	public :
		Goal(const shared_ptr<Stage>& StagePtr,Vector3 pos, Vector3 scale);
		void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	//	class Box : public GameObject;
	//	�p�r: ��
	//--------------------------------------------------------------------------------------
	class Box : public GameObject
	{
	private:
		Vector3 m_InitPos;
		Vector3 m_InitScale;
		Vector3 m_InitRot;
	public:
		Box(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale,Vector3 rot);
		void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	//	class Fence : public GameObject;
	//	�p�r: ��
	//--------------------------------------------------------------------------------------
	class Fence : public GameObject
	{
	private:
		Vector3 m_InitPos;
		Vector3 m_InitScale;
		Vector3 m_InitRot;

		shared_ptr<GameObject> m_FenceObj;
	public :
		Fence(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, Vector3 rot);
		void OnCreate() override;

	};
	//--------------------------------------------------------------------------------------
	//	class Rock : public GameObject;
	//�p�r�F��
	//--------------------------------------------------------------------------------------
	class Rock :public GameObject
	{
		//�����ʒu
		Vector3 m_InitPos;
		//�傫��
		Vector3 m_Scale;
	public:
		Rock(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale);
		void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	//	class Enemy : public GameObject;
	//	�p�r: �G
	//--------------------------------------------------------------------------------------
	class Enemy : public GameObject
	{
		//�����ʒu
		Vector3 m_InitPos;
		Vector3 m_Scale;
		//���x
		float m_speed = 2.0f;

		//��~���
		bool m_StopFlg = false;
		//��~����
		const float m_StopTime = 3.0f;
		//�v�Z�p
		float m_time = 0;
	public :
		Enemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale);
		void OnCreate() override;
		void OnUpdate() override;
		void StopEnemy();
		void ResetPos();

		bool GetStopFlg() { return m_StopFlg; }
	};
	
	//--------------------------------------------------------------------------------------
	//	class Black : public GameObject;
	//	�p�r: �Ó]�p���w�i
	//--------------------------------------------------------------------------------------
	class Black : public GameObject
	{
	private :
		float m_alpha = 0;
		bool m_StartFlg = false;
		bool m_EndFlg = false;
	public :
		Black(const shared_ptr<Stage>& StagePtr);
		void OnCreate() override;
		void OnUpdate() override;

		//�Ó]�N��
		void StartBlack();

		//�Ó]�������ǂ����擾
		bool GetBlackFinish();
	};

	//--------------------------------------------------------------------------------------
	//	class MagicBook : public GameObject;
	//	�p�r: ������
	//--------------------------------------------------------------------------------------
	class MagicBook : public GameObject
	{
	private :
		MagicType m_MagicContent = None;
		Vector3 m_InitPos;
		//�X�|�[������
		bool m_ActiveFlg = true;
		//�o�ߎ���
		float m_ElaTime=0;
		//�ďo������
		const float m_LimitTime = 3.0f;
		//���̑傫��
		Vector3 m_Scale = Vector3(0.5f,0.5f,0.5f);
	public :
		MagicBook(const shared_ptr<Stage>& StagePtr, Vector3 initPos,MagicType Magic);
		void OnCreate();
		void OnUpdate();
		//�E����
		void GetPlayer();


		//�A�N�Z�T�[
		Vector3 GetPos();
		Vector3 GetScale();
	};


	//--------------------------------------------------------------------------------------
	//	class NumberSprite : public GameObject;
	//	�p�r: �����̃X�v���C�g
	//--------------------------------------------------------------------------------------
	class NumberSprite : public GameObject
	{
	private:
		//�Ȃ񂩂���񃁃b�V���̃��X�g
		vector<shared_ptr<MeshResource>> m_Mesh;
		int m_num = 0;
		//����
		int m_digit = 0;
		//��������Ă鐔��
		int m_Constdigit = 0;
		//�\�����C���[
		int m_layer = 0;
		//�傫��
		Vector2 m_scale;
		//�ʒu
		Vector2 m_pos;
		//��������vector�z��
		vector<shared_ptr<GameObject>> m_Numbers;
	public :
		NumberSprite(const shared_ptr<Stage>& StagePtr, int num,Vector2 pos,Vector2 scale,int layer);
		
		void OnCreate()override;

		void SetNum(int num);
	};

	//--------------------------------------------------------------------------------------
	//	class LimitTime : public GameObject;
	//	�p�r: ��������
	//--------------------------------------------------------------------------------------
	class LimitTime : public GameObject
	{
	private:
		//�J�E���g����
		float m_nowTime = 0;
		//���~�b�g���Ԉ����ŏ����l���߂�
		float m_LimitTime = 60.0f;
		//�����X�v���C�g
		shared_ptr<NumberSprite> m_numberSp;
	public:
		LimitTime(const shared_ptr<Stage>& StagePtr, float LimitTime);
		void OnCreate() override;
		void OnUpdate() override;

		void TimeOver();

		int GetClearTime() { return (int)(m_LimitTime - m_nowTime); }
	};

	//--------------------------------------------------------------------------------------
	//	class ScoreItem : public GameObject;
	//	�p�r:�@�X�R�A�A�C�e��
	//--------------------------------------------------------------------------------------
	class ScoreItem : public GameObject
	{
	private :
		Vector3 m_InitPos;
		Vector3 m_InitScale;
		bool m_Active = true;
	public :
		ScoreItem(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale);

		void OnCreate() override;

		void Delete();

		bool GetActive() { return m_Active; }


		//****��
		void Detekuru();
		void Kieru();
		//****��
	};

	//--------------------------------------------------------------------------------------
	//	class MenuIcon : public GameObject;
	//	�p�r: ���j���[�{�^���̃A�C�R��
	//--------------------------------------------------------------------------------------
	class MenuIcon : public GameObject
	{
	private :
	public :
		MenuIcon(const shared_ptr<Stage>& StagePtr);
		void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	//	class PauseMenu : public GameObject;
	//	�p�r: �|�[�Y���j���[
	//--------------------------------------------------------------------------------------
	class PauseMenu : public GameObject
	{
	private:
		shared_ptr<GameObject> m_ReTryLogo;
		//shared_ptr<GameObject> m_mapLogo;
		shared_ptr<GameObject> m_StageSelectLogo;
		shared_ptr<GameObject> m_TitleLogo;
		shared_ptr<GameObject> m_Black;

		shared_ptr<GameObject> m_Map;

		//�N�����Ă邩�ǂ���
		bool m_ActivePauseFlg = false;
		//�Ó]���Ă邩�ǂ���
		bool m_BlackOutFlg = false;
		//�}�b�v�I��ł邩
		bool m_selectMapFlg = false;

		//���݉��I��ł邩�̐���
		//0:retry1:map2:stageselect3:title
		//����� 0:retry 1:stageselect 2:title
		int m_selectnum = 0;

		//����t���O
		bool m_moveFlg = false;

		//�I����X
		const float m_SelectX = -750;
		//��I����X
		const float m_NotSelectX = -850;

		//�I����Scale
		const Vector3 m_SelectScale = Vector3(500,500,1);
		const Vector3 m_NotSelectScale = Vector3(400,400,1);

		//�Ó]�̓����x
		float m_BlackAlpha = 0;
	public :
		PauseMenu(const shared_ptr<Stage>& StagePtr);

		void OnCreate();

		void OnUpdate();

		//�Q�[���X�e�[�W�ŌĂԂƁA�|�[�Y��ԂɁB�|�[�Y���ɓǂ񂾂��������B
		void Pause();

		//�|�[�Y���Ă邩�ǂ���
		bool GetPause() { return m_ActivePauseFlg; };

		//�Ó]���Ă邩�ǂ���
		bool GetBlackOut() { return m_BlackOutFlg; };

		//�Ó]�֐�
		void BlackOut();
	};

	//--------------------------------------------------------------------------------------
	//	class SEManager : public GameObject;
	//	�p�r: BGM�ȊO��SE���܂Ƃ߂����
	//--------------------------------------------------------------------------------------
	class SEManager : public GameObject
	{
	private :
		//��
		shared_ptr<MultiAudioObject> m_Se;
	public :
		SEManager(const shared_ptr<Stage>& StagePtr);
		void OnCreate()override;
		void OnSe(string name);
	};
	//--------------------------------------------------------------------------------------
	//	class Gimmick1 : public GameObject;
	//	�p�r: �X�B���̖��@[Fire]�ŗn������
	//--------------------------------------------------------------------------------------
	class Gimmick1 : public GameObject
	{
	private :
		//�����ʒu
		Vector3 m_InitPos;
		//�傫��
		Vector3 m_Scale;
		//�����Ă邩�ǂ���
		bool m_ActiveFlg = true;
	public :
		Gimmick1(const shared_ptr<Stage>& StagePtr,Vector3 pos,Vector3 scale);
		void OnCreate() override;

		void Delete(MagicType MT);

		bool GetActive() { return m_ActiveFlg; }

	};

	//--------------------------------------------------------------------------------------
	//	class Gimmick2 : public GameObject;
	//	�p�r: ���ԁB���̖��@[Fire]�ŔR����@�C��Ƒg�ݍ��킹��ΉH�������Đ���J�����肵�߂���ł���
	//--------------------------------------------------------------------------------------
	class Gimmick2 : public GameObject
	{
	private:
		//�����ʒu
		Vector3 m_InitPos;
		//�傫��
		Vector3 m_Scale;
		//�����Ă邩�ǂ���
		bool m_ActiveFlg = true;
	public:
		Gimmick2(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale);
		void OnCreate() override;

		void Delete(MagicType MT);

		bool GetActive() { return m_ActiveFlg; }
	};

	//--------------------------------------------------------------------------------------
	//	class Gimmick2_1 : public GameObject;
	//	�p�r:�@���Ԃɕ����Ă�ƕ��鐅��
	//--------------------------------------------------------------------------------------
	class Gimmick2_1 : public GameObject
	{
	private :
		//�����ʒu
		Vector3 m_InitPos;
		//�傫��
		Vector3 m_Scale;
		//���Ă邩�ǂ���
		bool m_CloseFlg = false;
		//�����Ă邩�ǂ���
		bool m_MoveFlg = false;
		//�ڎw���Ă���W
		float m_targetY=0;
	public:
		Gimmick2_1(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale);
		void OnCreate()override;
		void OnUpdate()override;
		//�Ȃ񂩓���
		void Action();
	};

	//--------------------------------------------------------------------------------------
	//	class Water : public GameObject;
	//	�p�r: ���B�R�A�����ȊO
	//--------------------------------------------------------------------------------------
	class Water : public GameObject
	{
	private:
		//�����ʒu
		Vector3 m_InitPos;
		//�傫��
		Vector3 m_InitScale;
		//�����Ă邩�ǂ���
		bool m_FreezeFlg = false;
		//����Ă邩�ǂ���
		bool m_FlowFlg = true;
		//�w�ԍ�
		int m_myNum;
		//�����ڂ̕���
		shared_ptr<GameObject> m_waterunder;
	public :
		Water(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale,int num);
		void OnCreate() override;

		//�ԍ��擾
		int GetmyNum() { return m_myNum; }

		//���炷
		void Freeze();
		//�n����
		void Melt();
		//�~�߂�
		void Stop();
		//����
		void Flow();

	};

	//--------------------------------------------------------------------------------------
	//	class Gimmick3 : public GameObject;
	//	�p�r: ��B�̃R�A�����B���点��Ɛ������𓀂点��
	//	�{�̂͐��̏�̓����ȕ����ŉ��̐��͌����ڂ���
	//--------------------------------------------------------------------------------------
	class Gimmick3 : public GameObject
	{
	private:
		//�����ʒu
		Vector3 m_InitPos;
		//�傫��
		Vector3 m_InitScale;
		//�����Ă邩�ǂ���
		bool m_FreezeFlg = false;
		//����Ă邩�ǂ���
		bool m_FlowFlg = true;
		//�������e����^���鐅�̏��
		vector<shared_ptr<Water>> m_waters;
		//�����ڂ̕���
		shared_ptr<GameObject> m_waterunder;
	public:
		Gimmick3(const shared_ptr<Stage>& StagePtr, Vector3 pos,Vector3 scale);
		void OnCreate() override;

		//���@������������
		void HitMagic(MagicType MT);
		//���炷
		void Freeze();
		//�n����
		void Melt();
		//�~�߂�
		void Stop();
		//����
		void Flow();

		void SetWaters(vector<shared_ptr<Water>> waters) { m_waters = waters; }

		bool GetFlow() { return m_FlowFlg; }
	};

	//--------------------------------------------------------------------------------------
	//	class Gimmick5 : public GameObject;
	//	�p�r: ���B�X�̖��@[Icefog]�ŏ�����
	//--------------------------------------------------------------------------------------
	class Gimmick5 : public GameObject
	{
	private:
		//�����ʒu
		Vector3 m_InitPos;
		//�傫��
		Vector3 m_Scale;
		//�����Ă邩�ǂ���
		bool m_ActiveFlg = true;
	public:
		Gimmick5(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale);
		void OnCreate() override;

		void Delete(MagicType MT);

		bool GetActive() { return m_ActiveFlg; }

	};

}
//end basecross
