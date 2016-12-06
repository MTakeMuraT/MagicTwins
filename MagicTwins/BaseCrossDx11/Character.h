/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	/*�ɂȂƂ����
	//--------------------------------------------------------------------------------------
	//	class MagicParticle : public GameObject;
	//	�p�r: �p�[�e�B�N��
	//	�g�����F(Vec3���W,Vec3�傫��,Vec3�ʒu�͈�,Vec3Velocity,string�e�N�X�`���̖��O,�쐬��,�쐬�Ԋu,��x�ɍ쐬���鐔,��������,���C���[)
	//--------------------------------------------------------------------------------------
	class MagicParticle : public GameObject
	{
	private:
		//�����ʒu
		Vector3 m_InitPos = Vector3(0, 0, 0);
		//�傫��
		Vector3 m_InitScale = Vector3(0, 0, 0);
		//���������Ƃ��̈ʒu�̐U�ꕝ
		Vector3 m_RandRange = Vector3(0, 0, 0);
		//�ړ����x
		Vector3 m_velocity = Vector3(0, 0, 0);
		//�e�N�X�`���̖��O
		string m_TextureName = "None";
		//�p�[�e�B�N���t���O
		bool m_NowParticleFlg = false;
		//���v�쐬��
		int m_CreateCount = 0;
		//�쐬�Ԋu
		float m_Interval = 0;
		//���ɏo����
		int m_OnceCreateCount = 0;
		//�����Ă鎞��
		float m_MoveingTime = 0;
		vector<shared_ptr<GameObject>> m_Particle;
		//�\�����C���[
		int m_DispLayer = 0;

		//���ꂼ��̃J�E���g
		vector<float> m_TimeCount;
		//�N�����邩�ǂ����̃t���O
		vector<bool> m_OnFlg;
	public:
		MagicParticle(const shared_ptr<Stage>& StagePtr);
		void OnCreate()override ;
		//����͎g��Ȃ���������Ȃ�
		void OnUpdate()override ;

		//(Vec3���W,Vec3�傫��,Vec3�ʒu�͈�,Vec3Velocity,string�e�N�X�`���̖��O,�쐬��,�쐬�Ԋu,��x�ɍ쐬���鐔,��������,���C���[)
		void OnParticle(Vector3 pos, Vector3 scale, Vector3 randrange, Vector3 velo, string texturename,
			int createcount,float interval,int oncecreatecount,float moveingtime,int displayer);

		//�p�[�e�B�N���o���Ă邩�ǂ����A���ꂪtrue(�o�Ă�)��ԂȂ�V�������悤�ɂ��Ă��炤
		bool GetNowParticle() { return m_NowParticleFlg; }
	};
	*/

	//--------------------------------------------------------------------------------------
	//	class MagicParticleProt : public GameObject;
	//	�p�r: �p�[�e�B�N��(�����)
	//--------------------------------------------------------------------------------------
	class MagicParticleProt : public GameObject
	{
	private:
		Vector3 m_InitPos;
		Vector3 m_InitScale;
		vector<shared_ptr<GameObject>> m_Particle;
		string m_TextureName;
		int m_Layer = 0;

		//�N�����Ă邩�ǂ���
		bool m_OnFlg = true;

		//�쐬�Ԋu
		const float m_Interval = 0.5f;
		//����
		float m_time = 0;
	public :
		//���W�A�傫��
		MagicParticleProt(const shared_ptr<Stage>& StagePtr,Vector3 pos,Vector3 scale,string txt,int layer);
		void OnCreate()override;
		void OnUpdate()override;

		void SetActiveParticle(bool flg) { m_OnFlg = flg; };
	};

	//--------------------------------------------------------------------------------------
	//	class MPPP : public GameObject;
	//	�p�r: �p�[�e�B�N���Ȉ�
	//--------------------------------------------------------------------------------------
	class MPPP : public GameObject
	{
	private :
		Vector3 m_InitPos;
		Vector3 m_InitScale;
		string m_txt;
		vector<shared_ptr<GameObject>> m_Particle;
	public :
		MPPP(const shared_ptr<Stage>& StagePtr,Vector3 pos , Vector3 scale,string txt) : GameObject(StagePtr),m_InitPos(pos),m_InitScale(scale),m_txt(txt){};
		void OnCreate()
		{
			for (int i = 0; i < 3; i++)
			{
				auto obj = GetStage()->AddGameObject<GameObject>();
				auto objTrans = obj->AddComponent<Transform>();
				Vector3 pos = m_InitPos;
				//�ʒu������Ƃ��炷
				int random = rand() % 100;
				pos.x += random / 100;
				random = rand() % 100;
				pos.y += random / 100;
				random = rand() % 100;
				pos.z += random / 100;
				objTrans->SetPosition(pos);
				objTrans->SetScale(m_InitScale);
				objTrans->SetRotation(0, 0, 0);

				auto objDraw = obj->AddComponent<PNTStaticDraw>();
				objDraw->SetMeshResource(L"DEFAULT_SQUARE");
				objDraw->SetTextureResource(L"FIREEF_TX");
				if (m_txt == "F")
				{
					objDraw->SetTextureResource(L"FIREEF_TX");
				}
				else if (m_txt == "I")
				{
					objDraw->SetTextureResource(L"I_TX");
				}
				else if (m_txt == "W")
				{
					objDraw->SetTextureResource(L"W_TX");
				}


				obj->SetAlphaActive(true);
				obj->SetDrawLayer(5);

				m_Particle.push_back(obj);
			}
			SetAlphaActive(true);
		}

		void OnUpdate()
		{

			for(auto v : m_Particle)
			{
				auto Tra = v->GetComponent<Transform>();
				Vector3 pos = Tra->GetPosition();
				pos.y += (rand()%2) * App::GetApp()->GetElapsedTime();
				Tra->SetPosition(pos);
				if (pos.y > m_InitPos.y + (m_InitScale.y * 3))
				{
					pos.y = m_InitPos.y;
					Tra->SetPosition(pos);
				}
			}
		}
	};
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
	//	class PlaneP : public GameObject;
	//	�p�r: �n��
	//--------------------------------------------------------------------------------------
	class PlaneP : public GameObject
	{
	private:
		Vector3 m_InitPos;
		Vector3 m_InitScale;
		Vector3 m_InitRot;
	public :
		PlaneP(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, Vector3 rot);
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
		float m_speed = 1.5f;
		const float m_InitSpeed = 1.5f;
		//��~���
		bool m_StopFlg = false;
		//��~����
		const float m_StopTime = 0.5f;
		//����ł鎞��
		const float m_ReSponTime = 10.0f;
		//�ǂ��t���O
		bool m_ChaceFlg = false;
		//�ǂ�����
		const float m_ChaceDir = 3.0f;
		//�v�Z�p
		float m_time = 0;
		//�̗�
		int m_life = 3;
		//�����̗�
		const int m_MaxLife = 3;
		//�_���Ă�v���C���[
		int m_TargetPlayernum = 0;
		//�����Ă邩����ł邩
		bool m_ActiveFlg = true;
		//���C�t�o�[
		shared_ptr<GameObject> m_lifeBar;

	public :
		Enemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale,int targetNum);
		void OnCreate() override;
		void OnUpdate() override;
		void StopEnemy(int TargetNum);
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

		//�ʒu����
		void SetPositionVec2(Vector2 pos);
		//�傫������
		void SetScaleVec2(Vector2 scale);
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

		int GetReamingTime() { return (int)m_nowTime; }
		int GetLimitTime() { return (int)m_LimitTime; }
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

		//�v���C���[�����邩�ǂ���
		void OnPlayer();

	};

	//--------------------------------------------------------------------------------------
	//	class WaterFall : public GameObject;
	//	�p�r: ��
	//--------------------------------------------------------------------------------------
	class WaterFall : public GameObject
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
	public:
		WaterFall(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale);
		void OnCreate() override;

		//���炷
		void Freeze();
		//�n����
		void Melt();
		//�~�߂�
		void Stop();
		//����
		void Flow();

		//�v���C���[�����邩�ǂ���
		void OnPlayer();

		bool GetFlow() { return m_FlowFlg; }

		void HitMagic(MagicType mt);
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
		//��̑��
		vector<shared_ptr<WaterFall>> m_waterfalls;
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

		void SetWaterFalls(vector<shared_ptr<WaterFall>> waterfalls) { m_waterfalls = waterfalls; }

		bool GetFlow() { return m_FlowFlg; }

		bool GetFreeze() { return m_FreezeFlg; }

		//�v���C���[�����邩�ǂ���
		void OnPlayer();


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
