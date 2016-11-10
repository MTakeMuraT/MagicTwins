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
	//	class LimitTime : public GameObject;
	//	�p�r: ��������
	//--------------------------------------------------------------------------------------
	class LimitTime : public GameObject
	{
	private :
		//�J�E���g����
		float m_nowTime=0;
		//���~�b�g���Ԉ����ŏ����l���߂�
		float m_LimitTime = 60.0f;
	public :
		LimitTime(const shared_ptr<Stage>& StagePtr,float LimitTime);
		void OnCreate() override;
		void OnUpdate() override;

		void TimeOver();

		int GetClearTime() { return (int)(m_LimitTime - m_nowTime); }
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
		bool m_ActiveFlg = false;
	public :
		Gimmick1(const shared_ptr<Stage>& StagePtr,Vector3 pos,Vector3 scale);
		void OnCreate() override;

		void Delete(MagicType MT);
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
		bool m_ActiveFlg = false;
	public:
		Gimmick2(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale);
		void OnCreate() override;

		void Delete(MagicType MT);
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
		bool m_ActiveFlg = false;
	public:
		Gimmick5(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale);
		void OnCreate() override;

		void Delete(MagicType MT);
	};

}
//end basecross
