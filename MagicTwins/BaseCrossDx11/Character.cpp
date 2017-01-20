/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	/*
	//--------------------------------------------------------------------------------------
	//	class MagicParticle : public GameObject;
	//	�p�r: �p�[�e�B�N��
	//	�g�����F(Vec3���W,Vec3�傫��,Vec3�ʒu�͈�,Vec3Velocity,string�e�N�X�`���̖��O,�쐬��,�쐬�Ԋu,��x�ɍ쐬���鐔,��������,���C���[)
	//--------------------------------------------------------------------------------------
	MagicParticle::MagicParticle(const shared_ptr<Stage>& StagePtr):
	GameObject(StagePtr)
	{}
	void MagicParticle::OnCreate(){}
	//���g��Ȃ��\�z�c

	//�p�[�e�B�N���𓮂���
	void MagicParticle::OnUpdate()
	{
		//�N����
		if (m_NowParticleFlg)
		{
			//�������[�v
			for (int i = 0; i < m_CreateCount; i++)
			{
				//�`�悳��Ă���
				if (m_Particle[i]->GetDrawActive())
				{
					//�R���|�[�l���g�Ƃ��Ƃ�
					auto Trans = m_Particle[i]->GetComponent<Transform>();

					//�ŏ��̍X�V��
					if (m_TimeCount[i] == 0)
					{
						//�u����
						Vector3 pos = m_InitPos;
						pos.x += rand() % (int)(m_RandRange.x / 2) - m_RandRange.x / 2;
						pos.y += rand() % (int)(m_RandRange.y / 2) - m_RandRange.y / 2;
						pos.z += rand() % (int)(m_RandRange.z / 2) - m_RandRange.z / 2;

						//�ʒu������
						Trans->SetPosition(pos);
					}

					//�ʒu�X�V
					Vector3 pos = Trans->GetPosition();
					

					//���ԍX�V
					m_TimeCount[i] += App::GetApp()->GetElapsedTime();
					if (m_TimeCount[i] > m_MoveingTime)
					{
						//�������Ԃ��z���������
						m_Particle[i]->SetDrawActive(false);
					}
				}
			}
		}
	}

	//�p�[�e�B�N���o�^
	void MagicParticle::OnParticle(Vector3 pos, Vector3 scale, Vector3 randrange, Vector3 velo,Vector3 randvelo, wstring texturename,
		int createcount, float interval, int oncecreatecount,float moveingTime,int displayer)
	{
		//�p�[�e�B�N���o���Ă��Ȃ���ԂȂ�
		if (!m_NowParticleFlg)
		{
			//�����ʒu
			m_InitPos = pos;
			//�傫��
			m_InitScale = scale;
			//���������Ƃ��̈ʒu�̐U�ꕝ
			m_RandRange = randrange;
			//�ړ��u����
			m_randVelocity = randvelo;
			//�e�N�X�`���̖��O
			m_TextureName = texturename;
			//���v�쐬��
			m_CreateCount = createcount;
			//�쐬���o
			m_Interval = interval;
			//���ɏo����
			m_OnceCreateCount = oncecreatecount;
			//�����Ă鎞��
			m_MoveingTime = moveingTime;
			//�\�����C���[
			m_DispLayer = displayer;
			//�p�[�e�B�N���t���OOn
			m_NowParticleFlg = false;

			//�쐬�����쐬
			//�����ō쐬�Ԋu�Ŋ���̂����肾���ǎ��ԓI�ɗ]�T�Ȃ������΂�
			//�Ō�̂ق��Ŏ��ԗ]��������
			for (int i = 0; i < m_CreateCount; i++)
			{
				auto obj = GetStage()->AddGameObject<GameObject>();
				
				auto objTrans = obj->AddComponent<Transform>();
				objTrans->SetPosition(0,0,0);
				objTrans->SetScale(m_InitScale);
				objTrans->SetRotation(0,0,0);

				auto objDraw = obj->AddComponent<PNTStaticDraw>();
				objDraw->SetMeshResource(L"DEFAULT_SQUARE");
				objDraw->SetTextureResource(m_TextureName);
				obj->SetAlphaActive(true);
				obj->SetDrawLayer(m_DispLayer);

				m_Particle.push_back(obj);


				//�Ǘ��p�̎��Ԃ����Z�b�g
				m_TimeCount.push_back(0);
				//�t���O���Z�b�g
				m_OnFlg.push_back(false);
				//�ړ����x��镪�ǉ�
				Vector3 setVelocity = velo;
				Vector3 randVelocity;
				randvelo.x = rand() % (int)randvelo.x - (randvelo.x / 2);
				randvelo.y = rand() % (int)randvelo.y - (randvelo.y / 2);
				randvelo.z = rand() % (int)randvelo.z - (randvelo.z / 2);
				m_velocity.push_back(velo);
			}
		}
	}

	void MagicParticle::StopParticle()
	{
		//�S�p�[�e�B�N������
		for (auto v : m_Particle)
		{
			v->SetDrawActive(false);
		}
		m_NowParticleFlg = false;
	}
	*/
	//--------------------------------------------------------------------------------------
	//	class MagicParticle : public GameObject;
	//	�p�r: �p�[�e�B�N��(�ȈՑΉ���)
	//--------------------------------------------------------------------------------------
	MagicParticle::MagicParticle(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	void MagicParticle::OnUpdate()
	{
		//���\��
		//GetComponent<StringSprite>()->SetText(Util::IntToWStr(m_Particle.size()));
		if (m_NowParticleFlg)
		{
			//�ʒu�X�V
			int count = 0;
			for (auto v : m_Particle)
			{
				//�`�悳��Ă���
				if (v->GetDrawActive())
				{
					auto Trans = v->GetComponent<Transform>();
					Vector3 pos = Trans->GetPosition();
					pos += m_velocity[count] * App::GetApp()->GetElapsedTime();
					Trans->SetPosition(pos);

					//���ŏ���
					//true�œ����ɂȂ�
					if (m_DeleteFlg)
					{
						m_alpha[count] += -m_DeleteTime * App::GetApp()->GetElapsedTime();
						v->GetComponent<PNTStaticDraw>()->SetDiffuse(Color4(1, 1, 1, m_alpha[count]));
						//������������
						if (m_alpha[count] < 0)
						{
							m_alpha[count] = 1.0f;
							v->GetComponent<PNTStaticDraw>()->SetDiffuse(Color4(1, 1, 1, 1));
							//��~
							v->SetDrawActive(false);
						}
					}
					else
					{
						//�T�C�Y������
						Vector3 scale = Trans->GetScale();
						scale *= 0.98f;
						Trans->SetScale(scale);
						//10����1�܂ŏ������Ȃ����������
						if (Trans->GetScale().x < m_Scale.x / 10)
						{
							Trans->SetScale(m_Scale);
							v->SetDrawActive(false);
						}
					}
				}
				count++;
			}
			count = 0;


			//�o�ߎ��ԉ��Z
			m_time += App::GetApp()->GetElapsedTime();
			//�������o���z������
			if (m_time > m_CreateInterval)
			{
				m_time = 0;
				bool CreateFlg = true;
				//�����Ă�̂�������ė��p
				int count = 0;
				for (auto v : m_Particle)
				{
					if (!v->GetDrawActive())
					{
						//�`��
						v->SetDrawActive(true);
						//���x�ʒu�ݒ�
						SetVeloPos(count);
						//�쐬�t���O������
						CreateFlg = false;

						//���ŏI��点�邽�߂ɔ�����
						break;
					}

					count++;
				}
				count = 0;
				if (CreateFlg)
				{
					//���������琶��
					CreateParticle();
				}
			}
		}
		//�p�[�e�B�N����~
		else
		{
			//�c���Ă�̂�������
			if (m_NokoriFlg)
			{
				//�ʒu�X�V
				int count = 0;
				//�p�[�e�B�N���o�Ă鐔
				int PaticleCount = 0;
				for (auto v : m_Particle)
				{
					//�`�悳��Ă���
					if (v->GetDrawActive())
					{
						//�o�Ă鐔������
						PaticleCount++;

						auto Trans = v->GetComponent<Transform>();
						Vector3 pos = Trans->GetPosition();
						pos += m_velocity[count] * App::GetApp()->GetElapsedTime();
						Trans->SetPosition(pos);

						//���ŏ���
						//true�œ����ɂȂ�
						if (m_DeleteFlg)
						{
							m_alpha[count] += -m_DeleteTime * App::GetApp()->GetElapsedTime();
							v->GetComponent<PNTStaticDraw>()->SetDiffuse(Color4(1, 1, 1, m_alpha[count]));
							//������������
							if (m_alpha[count] < 0)
							{
								m_alpha[count] = 1.0f;
								v->GetComponent<PNTStaticDraw>()->SetDiffuse(Color4(1, 1, 1, 1));
								//��~
								v->SetDrawActive(false);
							}
						}
						else
						{
							//�T�C�Y������
							Vector3 scale = Trans->GetScale();
							scale *= 0.98f;
							Trans->SetScale(scale);
							//10����1�܂ŏ������Ȃ����������
							if (Trans->GetScale().x < m_Scale.x / 10)
							{
								Trans->SetScale(m_Scale);
								v->SetDrawActive(false);
							}
						}
					}
					count++;
				}
				//�p�[�e�B�N��������o�ĂȂ���΍X�V����̂��
				if (PaticleCount <= 0)
				{
					m_NokoriFlg = false;
				}
				count = 0;
			}
		}
	}

	void MagicParticle::OnParticle(Vector3 InitPos, Vector3 RandPos, Vector3 Velo, Vector3 RandVelo, Vector3 scale, wstring TextureName, bool DeleteFlg, float CreateInterval,int layer,float deleteTime)
	{
		//�����ʒu�ݒ�
		m_InitPos = InitPos;
		//�ʒu�U�ꕝ�ݒ�
		m_RandPos = RandPos;
		//�������x
		m_Initvelocity = Velo;
		//���x�u����
		m_RandVelocity = RandVelo;
		//�傫���ݒ�
		m_Scale = scale;
		//�e�N�X�`���̖��O�ݒ�
		m_TextureName = TextureName;
		//���ŉ��o�ݒ�
		m_DeleteFlg = DeleteFlg;
		//�쐬�Ԋu�ݒ�
		m_CreateInterval = CreateInterval;
		//���C���[�ݒ�
		m_Layer = layer;
		//���Ŏ���
		m_DeleteTime = deleteTime;

		//�N���t���O��ON
		m_NowParticleFlg = true;

		//�����������
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
		PtrString->SetFont(L"", 60);

	}

	void MagicParticle::StopParticle()
	{
		/*�G�t�F�N�g������
		for (auto v : m_Particle)
		{
			v->SetDrawActive(false);
		}*/
		m_NowParticleFlg = false;
		//����c���Ă�G�t�F�N�g�o���؂邽�߂̃t���O
		m_NokoriFlg = true;
	}

	void MagicParticle::SetVeloPos(int num)
	{

		//�ʒu����-------------------------------------------------------------
		Vector3 pos = m_InitPos;
		Vector3 random;
		if (m_RandPos.x != 0)
		{
			random.x = (float)(rand() % (int)(m_RandPos.x * 100)) / 100 - (m_RandPos.x / 2);
		}
		if (m_RandPos.y != 0)
		{
			random.y = (float)(rand() % (int)(m_RandPos.y * 100)) / 100 - (m_RandPos.y / 2);
		}
		if (m_RandPos.z != 0)
		{
			random.z = (float)(rand() % (int)(m_RandPos.z * 100)) / 100 - (m_RandPos.z / 2);
		}
		pos += random;
		m_Particle[num]->GetComponent<Transform>()->SetPosition(pos);

		//���x����-------------------------------------------------------------
		Vector3 velo = m_Initvelocity;
		Vector3 randvelo;
		if (m_RandVelocity.x != 0)
		{
			randvelo.x = (float)(rand() % (int)(m_RandVelocity.x * 100)) / 100 - (m_RandVelocity.x / 2);
		}
		if (m_RandVelocity.y != 0)
		{
			randvelo.y = (float)(rand() % (int)(m_RandVelocity.y * 100)) / 100 - (m_RandVelocity.y / 2);
		}
		if (m_RandVelocity.z != 0)
		{
			randvelo.z = (float)(rand() % (int)(m_RandVelocity.z * 100)) / 100 - (m_RandVelocity.z / 2);
		}
		velo += randvelo;
		m_velocity[num] = velo;

	}

	void MagicParticle::CreateParticle()
	{
		//����
		auto obj = GetStage()->AddGameObject<GameObject>();
		auto Trans = obj->AddComponent<Transform>();
		//�����ʒu����
		Vector3 pos = m_InitPos;
		Vector3 random;
		if (m_RandPos.x != 0)
		{
			random.x = (float)(rand() % (int)(m_RandPos.x * 100)) / 100 - (m_RandPos.x / 2);
		}
		if (m_RandPos.y != 0)
		{
			random.y = (float)(rand() % (int)(m_RandPos.y * 100)) / 100 - (m_RandPos.y / 2);
		}
		if (m_RandPos.z != 0)
		{
			random.z = (float)(rand() % (int)(m_RandPos.z * 100)) / 100 - (m_RandPos.z / 2);
		}
		pos += random;
		//�ʒu�ݒ�
		Trans->SetPosition(pos);
		//�傫���ݒ�
		Trans->SetScale(m_Scale);
		//�����āc�A�Ӗ������H
		Trans->SetRotation(0, 0, 0);

		//�`��ݒ�
		auto Draw = obj->AddComponent<PNTStaticDraw>();
		Draw->SetMeshResource(L"DEFAULT_SQUARE");
		Draw->SetTextureResource(m_TextureName);
		obj->SetAlphaActive(true);
		obj->SetDrawLayer(m_Layer);

		//�����ݒ�
		Vector3 velo = m_Initvelocity;
		Vector3 randvelo;
		if (m_RandVelocity.x != 0)
		{
			randvelo.x = (float)(rand() % (int)(m_RandVelocity.x * 100)) / 100 - (m_RandVelocity.x / 2);
		}
		if (m_RandVelocity.y != 0)
		{
			randvelo.y = (float)(rand() % (int)(m_RandVelocity.y * 100)) / 100 - (m_RandVelocity.y / 2);
		}
		if (m_RandVelocity.z != 0)
		{
			randvelo.z = (float)(rand() % (int)(m_RandVelocity.z * 100)) / 100 - (m_RandVelocity.z / 2);
		}
		
		velo += randvelo;

		m_velocity.push_back(velo);
		m_Particle.push_back(obj);
		m_alpha.push_back(1.0f);
		//wstring txt;
		//txt += L"RandPos.X = " + Util::FloatToWStr(random.x) + L"RandPos.Y = " + Util::FloatToWStr(random.y + L"RandPos.Z = " + Util::FloatToWStr(random.z);
		//GetComponent<StringSprite>()->SetText(Util::IntToWStr(m_Particle.size()));
	}
	//--------------------------------------------------------------------------------------
	//	class Goal : public GameObject;
	//	�p�r: �S�[��
	//--------------------------------------------------------------------------------------

	Goal::Goal(const shared_ptr<Stage>& StagePtr,Vector3 pos, Vector3 scale):
		GameObject(StagePtr),
		m_InitPos(pos),
		m_Scale(scale)
		{}
	void Goal::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Vector3 pos = m_InitPos;
		pos.y += -0.3f;
		Ptr->SetPosition(pos);
		Ptr->SetScale(m_Scale);
		float rotangle = 90 * (3.14159265f / 180);
		Ptr->SetRotation(rotangle, 0, 0);

		//�Փ˔��������
		auto PtrCol = AddComponent<CollisionObb>();
		//�������̂ݔ���
		//PtrCol->SetIsHitAction(IsHitAction::Stop);

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ShadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ShadowPtr->SetMeshResource(L"DEFAULT_SQUARE");
		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"DEFAULT_SQUARE");
		//�`�悷��e�N�X�`����ݒ�
		PtrDraw->SetTextureResource(L"GOAL_TX");

		//��������
		SetAlphaActive(true);
		SetDrawLayer(1);
	}

	//--------------------------------------------------------------------------------------
	//	class Plane : public GameObject;
	//	�p�r: �n��
	//--------------------------------------------------------------------------------------

	PlaneP::PlaneP(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, Vector3 rot):
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale),
		m_InitRot(rot)
	{}

	void PlaneP::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_InitScale);
		Ptr->SetRotation(m_InitRot);

		//�Փ˔��������
		auto PtrCol = AddComponent<CollisionObb>();
		//�������̂ݔ���
		PtrCol->SetIsHitAction(IsHitAction::AutoOnObjectRepel);

		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//�`�悷��e�N�X�`����ݒ�
		PtrDraw->SetTextureResource(L"PANEL_TX");

		//��������
		SetAlphaActive(true);

	}
	//--------------------------------------------------------------------------------------
	//	class Rock : public GameObject;
	//	�p�r�F��
	//--------------------------------------------------------------------------------------
	Rock::Rock(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_Scale(scale)
	{}

	void Rock::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_Scale);
		Ptr->SetRotation(0, 0, 0);

		//�Փ˔��������
		auto PtrCol = AddComponent<CollisionObb>();

		// ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		float angle = (-90) * (3.14159265f / 180);
		Matrix4X4 SpanMat;
		SpanMat.DefTransformation(
			Vector3(0.5f, 0.5f, 0.5f),
			Vector3(0, angle, 0),
			Vector3(0, 0, 0)
			);

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ShadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ShadowPtr->SetMeshResource(L"Rock_Model");
		ShadowPtr->SetMeshToTransformMatrix(SpanMat);


		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTStaticModelDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"Rock_Model");
		PtrDraw->SetMeshToTransformMatrix(SpanMat);

		//��������
		SetAlphaActive(true);
	}

	//--------------------------------------------------------------------------------------
	//	class Fence : public GameObject;
	//	�p�r: ��
	//--------------------------------------------------------------------------------------
	Fence::Fence(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, Vector3 rot) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale),
		m_InitRot(rot)
	{}

	void Fence::OnCreate()
	{

		auto TranP = AddComponent<Transform>();
		TranP->SetPosition(m_InitPos);
		Vector3 scale = m_InitScale * 0.5f;
		TranP->SetScale(scale);
		TranP->SetRotation(m_InitRot);


		//�ȉ��t�F���X
		auto obj = GetStage()->AddGameObject<GameObject>();
		//�Փ˔��������
		auto PtrCol = obj->AddComponent<CollisionObb>();

		auto Ptr = obj->AddComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		//Vector3 scale = m_InitScale * 0.7f;
		Ptr->SetScale(m_InitScale);
		Ptr->SetRotation(m_InitRot);


		// ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		float angle = (-90) * (3.14159265f / 180);
		Matrix4X4 SpanMat;
		SpanMat.DefTransformation(
			Vector3(0.8f, 0.8f, 0.8f),
			Vector3(0,0, 0),
			Vector3(0, -0.5f, 0)
			);

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ShadowPtr = obj->AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ShadowPtr->SetMeshResource(L"Fence_Model");
		ShadowPtr->SetMeshToTransformMatrix(SpanMat);


		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = obj->AddComponent<PNTStaticModelDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"Fence_Model");
		PtrDraw->SetMeshToTransformMatrix(SpanMat);

		//��������
		obj->SetAlphaActive(true);

		m_FenceObj = obj;
	}

	//--------------------------------------------------------------------------------------
	//	class Box : public GameObject;
	//	�p�r: ��
	//--------------------------------------------------------------------------------------

	Box::Box(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale,Vector3 rot) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale),
		m_InitRot(rot)
	{}
	void Box::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_InitScale);
		Ptr->SetRotation(m_InitRot);

		//�Փ˔��������
		auto PtrCol = AddComponent<CollisionObb>();

		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//�`�悷��e�N�X�`����ݒ�
		PtrDraw->SetTextureResource(L"BOX_TX");

		//��������
		SetAlphaActive(true);

	}
	//--------------------------------------------------------------------------------------
	//	class Enemy : public GameObject;
	//	�p�r: �G
	//--------------------------------------------------------------------------------------
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale,int num):
		GameObject(StagePtr),
		m_InitPos(pos),
		m_Scale(scale),
		m_TargetPlayernum(num)
	{}

	void Enemy::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_Scale);

		// ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		Matrix4X4 SpanMat;
		SpanMat.DefTransformation(
			Vector3(0.5f, 0.5f, 0.5f),
			Vector3(0.0f, 0.0f, 0.0f),
			Vector3(0.0f, -0.3f, 0.0f)
			);


		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTStaticModelDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"Enemy_Model");
		PtrDraw->SetMeshToTransformMatrix(SpanMat);

		//��������
		SetAlphaActive(true);

	}

	void Enemy::OnUpdate()
	{
		//����ł�����
		if (!m_ActiveFlg)
		{
			if (m_deleteFlg)
			{
				//���������Ă�
				Vector3 nowScale = GetComponent<Transform>()->GetScale();
				nowScale *= 0.98f;
				GetComponent<Transform>()->SetScale(nowScale);

				//������x�������Ȃ�����
				if (nowScale.x < 0.1f)
				{
					SetDrawActive(false);
					m_ChaceFlg = false;
					m_deleteFlg = false;
					GetComponent<Transform>()->SetPosition(0, -15, 0);
					GetComponent<Transform>()->SetScale(m_Scale);
				}
				return ;
			}

			m_time += App::GetApp()->GetElapsedTime();
			//��������܂Ōo�߂�����
			if (m_time > m_ReSponTime)
			{
				m_ActiveFlg = true;
				m_life = m_MaxLife;
				m_speed = m_InitSpeed;
				SetDrawActive(true);
				GetComponent<Transform>()->SetPosition(m_InitPos);
			}
			return;
		}
		//�~�܂��ĂȂ��A���ǂ���ԂȂ�
		if (!m_StopFlg && m_ChaceFlg)
		{
			
			auto P1P = GetStage()->GetSharedGameObject<Player>(L"Player1", false);
			auto P2P = GetStage()->GetSharedGameObject<Player>(L"Player2", false);

			if (m_TargetPlayernum == 1)
			{
				if (P1P->GetActive())
				{
					Vector3 topos = P1P->GetComponent<Transform>()->GetPosition();
					Vector3 nowpos = GetComponent<Transform>()->GetPosition();
					Vector3 dir;
					dir = topos - nowpos;
					Vector2 velo = Vector2(dir.x, dir.z);
					float angle = atan2(velo.y, velo.x);
					velo.x = cos(angle);
					velo.y = sin(angle);

					//�����v���C���[���^�[�Q�b�g���[�h���Ȃ�ړ����x�x������
					if (P1P->GetTargeModeFlg())
					{
						velo *= 0.5f;
					}

					nowpos.x += velo.x * App::GetApp()->GetElapsedTime() * m_speed;
					nowpos.z += velo.y * App::GetApp()->GetElapsedTime() * m_speed;
					GetComponent<Transform>()->SetPosition(nowpos);

					//�����X�V
					angle = atan2(velo.y, velo.x);
					angle += (3.14159265f / 180) * 90;
					angle *= -1;
					GetComponent<Transform>()->SetRotation(Vector3(0, angle, 0));

				}
			}
			else if (m_TargetPlayernum == 2)
			{
				if (P2P->GetActive())
				{
					Vector3 topos = P2P->GetComponent<Transform>()->GetPosition();
					Vector3 nowpos = GetComponent<Transform>()->GetPosition();
					Vector3 dir;
					dir = topos - nowpos;
					Vector2 velo = Vector2(dir.x, dir.z);
					float angle = atan2(velo.y, velo.x);
					velo.x = cos(angle);
					velo.y = sin(angle);

					//�����v���C���[���^�[�Q�b�g���[�h���Ȃ�ړ����x�x������
					if (P2P->GetTargeModeFlg())
					{
						velo *= 0.5f;
					}

					nowpos.x += velo.x * App::GetApp()->GetElapsedTime() * m_speed;
					nowpos.z += velo.y * App::GetApp()->GetElapsedTime() * m_speed;
					GetComponent<Transform>()->SetPosition(nowpos);

					//�����X�V
					angle = atan2(velo.y, velo.x);
					angle *= -1;
					GetComponent<Transform>()->SetRotation(Vector3(0, angle, 0));

				}
			}
		}
		//�~�܂��Ă���
		else if(m_StopFlg)
		{
			m_time += App::GetApp()->GetElapsedTime();
			if (m_time > m_StopTime)
			{
				m_StopFlg = false;
				m_time = 0;
				GetComponent<PNTStaticModelDraw>()->SetDiffuse(Color4(1, 1, 1, 1));
			}
		}
		//�~�܂��ĂȂ��Ēǂ��ĂȂ���ԂȂ�
		else if (!m_ChaceFlg)
		{
			auto P1P = GetStage()->GetSharedGameObject<Player>(L"Player1", false);
			auto P2P = GetStage()->GetSharedGameObject<Player>(L"Player2", false);

			if (m_TargetPlayernum == 1)
			{
				if (P1P->GetActive())
				{
					Vector3 topos = P1P->GetComponent<Transform>()->GetPosition();
					Vector3 nowpos = GetComponent<Transform>()->GetPosition();
					Vector3 dir;
					dir = topos - nowpos;
					if (dir.Length() < m_ChaceDir)
					{
						m_ChaceFlg = true;
					}
				}
			}
			else if (m_TargetPlayernum == 2)
			{
				if (P2P->GetActive())
				{
					Vector3 topos = P2P->GetComponent<Transform>()->GetPosition();
					Vector3 nowpos = GetComponent<Transform>()->GetPosition();
					Vector3 dir;
					dir = topos - nowpos;
					if (dir.Length() < m_ChaceDir)
					{
						m_ChaceFlg = true;
					}
				}
			}
		}
	}

	void Enemy::StopEnemy(int TargetNum)
	{
		if (TargetNum == m_TargetPlayernum)
		{
			m_ChaceFlg = true;
			m_StopFlg = true;
			m_life--;
			m_time = 0;
			GetComponent<PNTStaticModelDraw>()->SetDiffuse(Color4(1, 1, 1, 0.5f));

			m_speed *= 2.0f;


			if (m_life <= 0)
			{
				m_deleteFlg = true;
				m_ActiveFlg = false;
			}
			//����łȂ���΍��W�ړ�
			else
			{
				Vector3 pos = GetComponent<Transform>()->GetPosition();
				pos += Vector3(rand() % 10 - 5, 0, rand() % 10 - 5);
				GetComponent<Transform>()->SetPosition(pos);

			}
		}
	}

	void Enemy::ResetPos()
	{
		m_speed = m_InitSpeed;
		m_ChaceFlg = false;
		GetComponent<Transform>()->SetPosition(m_InitPos);
	}

	//--------------------------------------------------------------------------------------
	//	class Black : public GameObject;
	//	�p�r: �Ó]�p��
	//--------------------------------------------------------------------------------------
	Black::Black(const shared_ptr<Stage>& StagePtr)	:
		GameObject(StagePtr)
	{}

	void Black::OnCreate()
	{
		//�E�B���h�E�T�C�Y�擾
		Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());

		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(0,0,0);
		Ptr->SetScale(WindowSize.x,WindowSize.y,1);
		Ptr->SetRotation(0, 0, 0);

		//�e�N�X�`��������
		auto PtrSprite = this->AddComponent<PCTSpriteDraw>();
		PtrSprite->SetTextureResource(L"BLACK_TX");

		//������
		PtrSprite->SetDiffuse(Color4(1,1,1,0));

		//�\�����C���[10�ݒ�
		SetDrawLayer(10);

		//�����x���f
		SetAlphaActive(true);

	}

	void Black::OnUpdate()
	{
		//�N�����
		if (m_StartFlg)
		{
			//���̉�
			auto PtrSprite = this->AddComponent<PCTSpriteDraw>();
			m_alpha += 1 * App::GetApp()->GetElapsedTime();
			PtrSprite->SetDiffuse(Color4(1, 1, 1, m_alpha));
			
			if (m_alpha >= 1.2f)
			{
				m_StartFlg = false;
				m_EndFlg = true;
			}
		}
	}

	void Black::StartBlack()
	{
		m_StartFlg = true;
	}

	bool Black::GetBlackFinish()
	{
		return m_EndFlg;
	}

	//--------------------------------------------------------------------------------------
	//	class MagicBook : public GameObject;
	//	�p�r: ������
	//--------------------------------------------------------------------------------------
	MagicBook::MagicBook(const shared_ptr<Stage>& StagePtr, Vector3 pos, MagicType magic) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_MagicContent(magic)
	{}

	void MagicBook::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetScale(m_Scale);
		Ptr->SetRotation(0, 0, 0);
		Ptr->SetPosition(m_InitPos);

		/*
		//�ۗp
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ShadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");
		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//���b�V����ݒ�
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");

		//�e�N�X�`����ݒ�
		PtrDraw->SetTextureResource(L"MAGICBOOKFIRE_TX");

		switch (m_MagicContent)
		{
		case Fire:
			PtrDraw->SetTextureResource(L"MAGICBOOKFIRE_TX");
			break;
		case IceFog :
			PtrDraw->SetTextureResource(L"MAGICBOOKICEFOG_TX");
			break;
		case Wind:
			PtrDraw->SetTextureResource(L"MAGICBOOKWIND_TX");
		default:
			break;
		}
		*/
		
		//���f���p
		// ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		float angle = (-90) * (3.14159265f / 180);
		Matrix4X4 SpanMat;
		SpanMat.DefTransformation(
			Vector3(0.5f, 0.5f, 0.5f),
			Vector3(0, 0, 0),
			Vector3(0, -0.5f, 0)
			);

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ShadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ShadowPtr->SetMeshResource(L"MagicBookFire_Model");
		ShadowPtr->SetMeshToTransformMatrix(SpanMat);


		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTStaticModelDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"MagicBookFire_Model");
		PtrDraw->SetMeshToTransformMatrix(SpanMat);


		switch (m_MagicContent)
		{
		case Fire:
			ShadowPtr->SetMeshResource(L"MagicBookFire_Model");
			PtrDraw->SetMeshResource(L"MagicBookFire_Model");
			break;
		case IceFog:
			ShadowPtr->SetMeshResource(L"MagicBookIceFog_Model");
			PtrDraw->SetMeshResource(L"MagicBookIceFog_Model");		
			break;
		case Wind:
			ShadowPtr->SetMeshResource(L"MagicBookWind_Model");
			PtrDraw->SetMeshResource(L"MagicBookWind_Model");	
			break;
		}
		

		/*//���f����
		// ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		float angle = (-90) * (3.14159265f / 180);
		Matrix4X4 SpanMat;
		SpanMat.DefTransformation(
		Vector3(1.0f, 0.3f, 1.0f),
		Vector3(0, 0, 0),
		Vector3(0, 0, 0)
		);

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ShadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ShadowPtr->SetMeshResource(L"MagicBook_Model");
		ShadowPtr->SetMeshToTransformMatrix(SpanMat);


		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTStaticModelDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"MagicBook_Model");
		PtrDraw->SetMeshToTransformMatrix(SpanMat);

		//�F�ς���p�����ǃ��f���ǂݍ��݂����炿����Ƃ����ς���
		switch (m_MagicContent)
		{
		case Fire:
		//PtrDraw->SetTextureResource(L"MAGICBOOKFIRE_TX");
		PtrDraw->SetDiffuse(Color4(1, 1, 1, 1));
		break;
		case IceFog :
		//PtrDraw->SetTextureResource(L"MAGICBOOKICEFOG_TX");
		PtrDraw->SetDiffuse(Color4(0, 0, 1, 1));
		break;
		default:
		break;
		}
		*/

		//��������
		SetAlphaActive(true);

		SetUpdateActive(false);
	}

	void MagicBook::OnUpdate()
	{
		m_ElaTime += App::GetApp()->GetElapsedTime();
		if (m_ElaTime >= m_LimitTime)
		{
			GetComponent<PNTStaticModelDraw>()->SetDiffuse(Color4(1, 1, 1, 1));
			m_ElaTime = 0;
			SetUpdateActive(false);
			m_ActiveFlg = true;
			GetComponent<Transform>()->SetScale(m_Scale);

		}
	}

	//�Ƃ����Ƃ�
	void MagicBook::GetPlayer()
	{
		if (m_ActiveFlg)
		{
			GetStage()->GetSharedGameObject<Player>(L"Player1", false)->SetMagic(m_MagicContent);
			GetComponent<PNTStaticModelDraw>()->SetDiffuse(Color4(1, 1, 1, 0.1f));
			SetUpdateActive(true);
			m_ActiveFlg = false;

			//���f���ɂ����瓧�����ł��Ȃ��Ȃ������珬��������
			Vector3 scale = m_Scale / 2;
			GetComponent<Transform>()->SetScale(scale);
		}
	}

	Vector3 MagicBook::GetPos()
	{
		return GetComponent<Transform>()->GetPosition();
	}

	Vector3 MagicBook::GetScale()
	{
		return GetComponent<Transform>()->GetScale();
	}

	//--------------------------------------------------------------------------------------
	//	class LimitTime : public GameObject;
	//	�p�r: ��������
	//--------------------------------------------------------------------------------------
	LimitTime::LimitTime(const shared_ptr<Stage>& StagePtr,float LimitTime):
		GameObject(StagePtr),
		m_LimitTime(LimitTime)
	{}
	
	void LimitTime::OnCreate()
	{
		auto DrawP = AddComponent<PCTSpriteDraw>();
		DrawP->SetTextureResource(L"TIME_TX");
		auto TranP = AddComponent<Transform>();
		TranP->SetPosition(800,470,0);
		TranP->SetRotation(0, 0, 0);
		TranP->SetScale(300, 300, 0);
		SetAlphaActive(true);

		//�����������
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(1700.0f, 15.0f, 2000.0f, 300.0f));
		PtrString->SetFont(L"", 80);
		//�����p��+1
		m_nowTime = m_LimitTime + 1;
		SetDrawLayer(4);

		auto numobj = GetStage()->AddGameObject<NumberSprite>(0, Vector2(830, 470), Vector2(100, 100), 6);
		m_numberSp = numobj;



		//�Ԙg�X�v���C�g�쐬
		auto akaobj = GetStage()->AddGameObject<GameObject>();
		auto AkaTrans = akaobj->AddComponent<Transform>();
		AkaTrans->SetPosition(0, 0, 0);
		AkaTrans->SetRotation(0, 0, 0);
		AkaTrans->SetScale(1920, 1080, 1);

		auto AkaDraw = akaobj->AddComponent<PCTSpriteDraw>();
		AkaDraw->SetTextureResource(L"AKAWAKU_TX");

		akaobj->SetDrawLayer(5);
		akaobj->SetAlphaActive(true);
		akaobj->SetDrawActive(false);

		m_AkaWakuSprite = akaobj;
	}

	void LimitTime::OnUpdate()
	{
		//wstring txt = Util::IntToWStr((int)m_nowTime);
		//GetComponent<StringSprite>()->SetText(txt);

		if (m_AkaWakuFlg)
		{
			//false�œ�����
			if (!m_AlphaAkaFlg)
			{
				m_AlphaAka += -1 * App::GetApp()->GetElapsedTime();
				m_AkaWakuSprite->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_AlphaAka));
				if (m_AlphaAka <0)
				{
					m_AlphaAkaFlg = true;
				}
			}
			//true�Ŏ��̉�
			else
			{
				m_AlphaAka += 1 * App::GetApp()->GetElapsedTime();
				m_AkaWakuSprite->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_AlphaAka));

				if (m_AlphaAka > 1.0f)
				{
					m_AlphaAkaFlg = false;
				}
			}
			if (m_nowTime > 10)
			{
				m_AkaWakuFlg = false;
				m_AkaWakuSprite->SetDrawActive(false);
			}


		}
		//10�b�����ŐԘg
		if (!m_AkaWakuFlg && m_nowTime <= 10)
		{
			m_AkaWakuFlg = true;
			m_AkaWakuSprite->SetDrawActive(true);
			GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("TimeAlert");
		}
		
		//���Ԍo�ߏ���
		m_nowTime += -App::GetApp()->GetElapsedTime();

		//�X�v���C�g�ύX
		m_numberSp->SetNum((int)m_nowTime);

		if (m_nowTime < 1)
		{
			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameOver");
		}
	}

	//--------------------------------------------------------------------------------------
	//	class NumberSprite : public GameObject;
	//	�p�r: �����̃X�v���C�g
	//--------------------------------------------------------------------------------------
	NumberSprite::NumberSprite(const shared_ptr<Stage>& StagePtr,int numb,Vector2 pos,Vector2 Scale,int layer):
		GameObject(StagePtr),
		m_num(numb),
		m_pos(pos),
		m_scale(Scale),
		m_layer(layer)
	{}

	void NumberSprite::OnCreate()
	{
		//�����̑傫���ɂ���ĉ񐔕ύX
		int count = m_num;
		do
		{
			count /= 10;
			m_digit++;
		} while (count > 0);

		//�����̃X�v���C�g�쐬
		for (int i = 0; i < 10; i++)
		{
			//���_�z��
			vector<VertexPositionNormalTexture> vertices;
			//�C���f�b�N�X���쐬���邽�߂̔z��
			vector<uint16_t> indices;
			//Square�̍쐬(�w���p�[�֐��𗘗p)
			MeshUtill::CreateSquare(1.0f, vertices, indices);
			//UV�l�̕ύX
			float from = i / 10.0f;
			float to = from + (1.0f / 10.0f);
			//���㒸�_
			vertices[0].textureCoordinate = Vector2(from, 0);
			//�E�㒸�_
			vertices[1].textureCoordinate = Vector2(to, 0);
			//�������_
			vertices[2].textureCoordinate = Vector2(from, 1.0f);
			//�E�����_
			vertices[3].textureCoordinate = Vector2(to, 1.0f);
			//���_�̌^��ς����V�������_���쐬
			vector<VertexPositionColorTexture> new_vertices;
			for (auto& v : vertices) {
				VertexPositionColorTexture nv;
				nv.position = v.position;
				nv.color = Color4(1.0f, 1.0f, 1.0f, 1.0f);
				nv.textureCoordinate = v.textureCoordinate;
				new_vertices.push_back(nv);
			}
			//���b�V���쐬
			m_Mesh.push_back(MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true));
		}

		int masternum = m_num;
		
		//�������[�v
		for (int j = m_digit-1; j >= 0; j--)
		{
			//���������ǉ�
			m_Constdigit++;

			int digi = j;
			int num = masternum / pow(10, (digi));
			masternum = masternum % (int)(pow(10, (digi)));

			auto NumP = GetStage()->AddGameObject<GameObject>();

			float distance = m_scale.x / 1.8f;

			auto TranP = NumP->AddComponent<Transform>();
			TranP->SetPosition(m_pos.x - (distance*j), m_pos.y, 0);
			TranP->SetScale(m_scale.x, m_scale.y, 1);
			TranP->SetRotation(0, 0, 0);

			auto DrawP = NumP->AddComponent<PCTSpriteDraw>();
			DrawP->SetTextureResource(L"NUMBER_TX");
			DrawP->SetMeshResource(m_Mesh[num]);
			NumP->SetAlphaActive(true);

			NumP->SetDrawLayer(m_layer);
			m_Numbers.push_back(NumP);
		}
	}

	void NumberSprite::SetPositionVec2(Vector2 pos)
	{
		int count = 0;
		for (auto v : m_Numbers)
		{
			v->GetComponent<Transform>()->SetPosition(m_pos.x,m_pos.y,0);
			count++;
		}
	}

	void NumberSprite::SetScaleVec2(Vector2 scale)
	{

	}

	void NumberSprite::SetNum(int num)
	{
		//�}�C�i�X�e��
		if (m_num >= 0)
		{
			m_num = num;
			//���͂��ꂽ�������Ă���
			int digit = 0;
			int innum = num;
			do
			{
				innum /= 10;
				digit++;
			} while (innum > 0);

			//���͂��ꂽ�ق����傫��������
			if (digit > m_digit)
			{
				for (int j = 0; j < (digit - m_Constdigit); j++)
				{
					//�����Ɍ��ǉ�
					int digitDif = digit - m_digit;

					m_Constdigit++;

					auto NumP = GetStage()->AddGameObject<GameObject>();

					float distance = m_scale.x / 1.8f;

					auto TranP = NumP->AddComponent<Transform>();
					TranP->SetPosition(m_pos.x - (distance*(m_digit)), m_pos.y, 0);
					TranP->SetScale(m_scale.x, m_scale.y, 1);
					TranP->SetRotation(0, 0, 0);

					auto DrawP = NumP->AddComponent<PCTSpriteDraw>();
					DrawP->SetTextureResource(L"NUMBER_TX");
					DrawP->SetMeshResource(m_Mesh[0]);
					NumP->SetAlphaActive(true);

					NumP->SetDrawLayer(m_layer);
					m_Numbers.push_back(NumP);
				}

				for (int i = 0; i < m_Constdigit; i++)
				{
					m_Numbers[i]->SetDrawActive(true);
				}
			}

			//���͂��ꂽ�ق���������
			if (digit < m_digit)
			{
				for (int i = m_digit - 1; i > digit - 1; i--)
				{
					m_Numbers[i]->SetDrawActive(false);
				}
			}

			//���X�V
			m_digit = digit;

			//��������ւ�
			int masternum = m_num;
			for (int i = m_digit - 1; i >= 0; i--)
			{
				int digi = i;
				int setnum = masternum / pow(10, (digi));
				masternum = masternum % (int)(pow(10, (digi)));

				m_Numbers[i]->GetComponent<PCTSpriteDraw>()->SetMeshResource(m_Mesh[setnum]);
			}
		}
	}

	//--------------------------------------------------------------------------------------
	//	class PauseMenu : public GameObject;
	//	�p�r: �|�[�Y���j���[
	//--------------------------------------------------------------------------------------
	PauseMenu::PauseMenu(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
	{}

	void PauseMenu::OnCreate()
	{
		//�|�[�Y�̃��S
		auto TranP = AddComponent<Transform>();
		TranP->SetPosition(Vector3(0,400,0));
		TranP->SetScale(500, 100, 1);
		TranP->SetRotation(0, 0, 0);

		auto DrawP = AddComponent<PCTSpriteDraw>();
		DrawP->SetTextureResource(L"PAUSELOGO_TX");
		SetAlphaActive(true);
		SetDrawActive(false);
		SetDrawLayer(8);

		//�Ó]
		auto BlackP = GetStage()->AddGameObject<GameObject>();
		auto BTranP = BlackP->AddComponent<Transform>();
		BTranP->SetPosition(0, 0, 0);
		BTranP->SetScale(1920, 1080, 1);
		BTranP->SetRotation(0, 0, 0);
		auto BDrawP = BlackP->AddComponent<PCTSpriteDraw>();
		BDrawP->SetTextureResource(L"BLACK_TX");
		BDrawP->SetDiffuse(Color4(1, 1, 1, 0.5f));

		BlackP->SetDrawLayer(7);
		BlackP->SetAlphaActive(true);
		BlackP->SetDrawActive(false);
		m_Black = BlackP;

		//�T�C�Y
		Vector3 LogoScale = Vector3(400, 400, 1);

		//���g���C���S
		auto ReTryP = GetStage()->AddGameObject<GameObject>();
		auto RTTP = ReTryP->AddComponent<Transform>();
		//RTTP->SetPosition(m_SelectX, 300, 0);
		RTTP->SetPosition(-500, -400, 0);
		RTTP->SetScale(m_SelectScale);
		RTTP->SetRotation(0, 0, 0);
		auto RTDP = ReTryP->AddComponent<PCTSpriteDraw>();
		RTDP->SetTextureResource(L"PAUSERETRY_TX");
		ReTryP->SetAlphaActive(true);
		ReTryP->SetDrawActive(false);
		ReTryP->SetDrawLayer(8);
		m_ReTryLogo = ReTryP;

		/*
		//�}�b�v���S
		auto MaPP = GetStage()->AddGameObject<GameObject>();
		auto MTPP = MaPP->AddComponent<Transform>();
		MTPP->SetPosition(m_NotSelectX, 150, 0);
		MTPP->SetScale(LogoScale);
		MTPP->SetRotation(0, 0, 0);
		auto MDPP = MaPP->AddComponent<PCTSpriteDraw>();
		MDPP->SetTextureResource(L"PAUSEMAPLOGO_TX");
		MaPP->SetAlphaActive(true);
		MaPP->SetDrawActive(false);
		MaPP->SetDrawLayer(8);
		m_mapLogo = MaPP;
		*/

		//�X�e�[�W�Z���N�g���S
		auto SSP = GetStage()->AddGameObject<GameObject>();
		auto SSTP = SSP->AddComponent<Transform>();
		//SSTP->SetPosition(m_NotSelectX, 0, 0);
		SSTP->SetPosition(0, -400, 0);
		SSTP->SetScale(m_NotSelectScale);
		SSTP->SetRotation(0, 0, 0);
		auto SSDP = SSP->AddComponent<PCTSpriteDraw>();
		SSDP->SetTextureResource(L"PAUSESTAGESELECTLOGO_TX");
		SSP->SetAlphaActive(true);
		SSP->SetDrawActive(false);
		SSP->SetDrawLayer(8);
		m_StageSelectLogo = SSP;

		//�^�C�g�����S
		auto TiP = GetStage()->AddGameObject<GameObject>();
		auto TTP = TiP->AddComponent<Transform>();
		//TTP->SetPosition(m_NotSelectX, -150, 0);
		TTP->SetPosition(500, -400, 0);
		TTP->SetScale(m_NotSelectScale);
		TTP->SetRotation(0, 0, 0);
		auto TDP = TiP->AddComponent<PCTSpriteDraw>();
		TDP->SetTextureResource(L"PAUSETITLELOGO_TX");
		TiP->SetAlphaActive(true);
		TiP->SetDrawActive(false);
		TiP->SetDrawLayer(8);
		m_TitleLogo = TiP;

		//�}�b�v�摜
		auto MaP = GetStage()->AddGameObject<GameObject>();
		auto MaTP = MaP->AddComponent<Transform>();
		MaTP->SetPosition(0, 0, 0);
		MaTP->SetScale(1024,650,1);
		MaTP->SetRotation(0, 0, 0);
		auto MaTDP = MaP->AddComponent<PCTSpriteDraw>();
		//�V�[������X�e�[�W�ԍ��擾
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		int StageNum = ScenePtr->GetStageNum();
		wstring texturetxt = L"MAP_" + Util::IntToWStr(StageNum) + L"_TX";
		MaTDP->SetTextureResource(texturetxt);
		MaP->SetAlphaActive(true);
		MaP->SetDrawActive(false);
		MaP->SetDrawLayer(8);
		m_Map = MaP;

	}

	void PauseMenu::OnUpdate()
	{
		if (m_BlackOutFlg)
		{
			BlackOut();
			return;
		}
		//�}�b�v�\�����ĂȂ�
		if (!m_selectMapFlg)
		{
			//�|�[�Y�����Ó]�����ĂȂ�
			if (m_ActivePauseFlg && !m_BlackOutFlg)
			{
				auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
				//���艟���ꂽ��
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
				{/*
					//�}�b�v����Ȃ����
					if (m_selectnum != 1)
					{
						//�Ó]��Ԃ�
						m_BlackOutFlg = true;

						m_Black->SetDrawLayer(8);
						return;
					}
					else
					{
						m_Map->SetDrawActive(true);
						m_selectMapFlg = true;
					}
					*/

					//�Ó]��Ԃ�
					m_BlackOutFlg = true;

					m_Black->SetDrawLayer(10);
					//SE�Đ�
					GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("Select");

					return;

				}
				Vector2 inputXY = Vector2(CntlVec[0].fThumbLX, CntlVec[0].fThumbLY);
				if (!m_moveFlg)
				{
					if (inputXY.x > 0.8f)
					{
						m_moveFlg = true;
						m_selectnum++;
						if (m_selectnum > 2)
						{
							m_selectnum = 0;
						}
					}
					if (inputXY.x < -0.8f)
					{
						m_moveFlg = true;
						m_selectnum--;
						if (m_selectnum < 0)
						{
							m_selectnum = 2;
						}
					}

					//�ύX��������
					if (m_moveFlg)
					{
						//Vector3 pos;
						Vector3 scale;
						switch (m_selectnum)
						{
						case 0:
							m_ReTryLogo->GetComponent<Transform>()->SetScale(m_SelectScale);
							m_StageSelectLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
							m_TitleLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);

							/*
							//�O��̕����ړ�
							//0�Ȃ�(3,1)
							//3

							pos = m_TitleLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_NotSelectX;
							m_TitleLogo->GetComponent<Transform>()->SetPosition(pos);
							//1
							pos = m_mapLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_NotSelectX;
							m_mapLogo->GetComponent<Transform>()->SetPosition(pos);

							//0
							pos = m_ReTryLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_SelectX;
							m_ReTryLogo->GetComponent<Transform>()->SetPosition(pos);
							*/
							break;
						case 1:
							m_ReTryLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
							m_StageSelectLogo->GetComponent<Transform>()->SetScale(m_SelectScale);
							m_TitleLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);

							/*
							//0
							pos = m_ReTryLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_NotSelectX;
							m_ReTryLogo->GetComponent<Transform>()->SetPosition(pos);
							//2
							pos = m_StageSelectLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_NotSelectX;
							m_StageSelectLogo->GetComponent<Transform>()->SetPosition(pos);
							//1
							pos = m_mapLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_SelectX;
							m_mapLogo->GetComponent<Transform>()->SetPosition(pos);
							*/
							break;
						case 2:
							m_ReTryLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
							m_StageSelectLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
							m_TitleLogo->GetComponent<Transform>()->SetScale(m_SelectScale);

							/*
							//1
							pos = m_mapLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_NotSelectX;
							m_mapLogo->GetComponent<Transform>()->SetPosition(pos);
							//3
							pos = m_TitleLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_NotSelectX;
							m_TitleLogo->GetComponent<Transform>()->SetPosition(pos);
							//2
							pos = m_StageSelectLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_SelectX;
							m_StageSelectLogo->GetComponent<Transform>()->SetPosition(pos);
							*/
							break;
							/*
						case 3:
							
							//0
							pos = m_ReTryLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_NotSelectX;
							m_ReTryLogo->GetComponent<Transform>()->SetPosition(pos);
							//2
							pos = m_StageSelectLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_NotSelectX;
							m_StageSelectLogo->GetComponent<Transform>()->SetPosition(pos);
							//3
							pos = m_TitleLogo->GetComponent<Transform>()->GetPosition();
							pos.x = m_SelectX;
							m_TitleLogo->GetComponent<Transform>()->SetPosition(pos);
							
							break;
							*/
						default:
							throw BaseException(
								L"(PauseMenu)�ςȂ̓����Ă�",
								L"",
								L""
								);
							break;
						}
					}
				}
				else if (inputXY.x < 0.1f && inputXY.x > -0.1f)
				{
					m_moveFlg = false;
				}
			}
		}
		//�}�b�v�\�����Ă���
		else
		{
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
			{
				m_Map->SetDrawActive(false);
				m_selectMapFlg = false;
			}
		}
	}

	void PauseMenu::BlackOut()
	{
		if (m_BlackAlpha >= 1.2f)
		{
			auto ScenePtr = App::GetApp()->GetScene<Scene>();

			switch (m_selectnum)
			{
			case 0:
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"GameStage");

				break;
			case 1:
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"StageSelect");

				break;
			case 2:
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"Title");

				break;

			default:
				break;
			}
		}
		else
		{
			m_BlackAlpha += 1 * App::GetApp()->GetElapsedTime();
			m_Black->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));
		}
	}

	void PauseMenu::Pause()
	{
		//�t���O���]
		m_ActivePauseFlg = !m_ActivePauseFlg;
		//���ꂼ�����or������
		SetDrawActive(m_ActivePauseFlg);
		m_Black->SetDrawActive(m_ActivePauseFlg);
		m_ReTryLogo->SetDrawActive(m_ActivePauseFlg);
		//m_mapLogo->SetDrawActive(m_ActivePauseFlg);
		m_StageSelectLogo->SetDrawActive(m_ActivePauseFlg);
		m_TitleLogo->SetDrawActive(m_ActivePauseFlg);

		m_Map->SetDrawActive(m_ActivePauseFlg);
		m_selectMapFlg = false;
		m_selectnum = 0;

		//�T�C�Y����
		m_ReTryLogo->GetComponent<Transform>()->SetScale(m_SelectScale);
		m_StageSelectLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);
		m_TitleLogo->GetComponent<Transform>()->SetScale(m_NotSelectScale);

		/*
		//�ʒu����
		Vector3 pos;
		//0
		pos = m_ReTryLogo->GetComponent<Transform>()->GetPosition();
		pos.x = m_SelectX;
		m_ReTryLogo->GetComponent<Transform>()->SetPosition(pos);

		//1
		pos = m_mapLogo->GetComponent<Transform>()->GetPosition();
		pos.x = m_NotSelectX;
		m_mapLogo->GetComponent<Transform>()->SetPosition(pos);
		//2
		pos = m_StageSelectLogo->GetComponent<Transform>()->GetPosition();
		pos.x = m_NotSelectX;
		m_StageSelectLogo->GetComponent<Transform>()->SetPosition(pos);
		//3
		pos = m_TitleLogo->GetComponent<Transform>()->GetPosition();
		pos.x = m_NotSelectX;
		m_TitleLogo->GetComponent<Transform>()->SetPosition(pos);
		*/

	}
	//--------------------------------------------------------------------------------------
	//	class MenuIcon : public GameObject;
	//	�p�r: ���j���[�{�^���̃A�C�R��
	//--------------------------------------------------------------------------------------
	MenuIcon::MenuIcon(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
	{}

	void MenuIcon::OnCreate()
	{
		auto DrawP = AddComponent<PCTSpriteDraw>();
		DrawP->SetTextureResource(L"MENUICON_TX");
		auto TranP = AddComponent<Transform>();
		TranP->SetPosition(750,-450, 0);
		TranP->SetRotation(0, 0, 0);
		TranP->SetScale(100, 100, 0);
		SetAlphaActive(true);
		SetDrawLayer(5);

	}

	//--------------------------------------------------------------------------------------
	//	class ScoreItem : public GameObject;
	//	�p�r:�@�X�R�A�A�C�e��
	//--------------------------------------------------------------------------------------
	ScoreItem::ScoreItem(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale)
	{}

	void ScoreItem::OnCreate()
	{

		// ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		float angle = (-90) * (3.14159265f / 180);
		Matrix4X4 SpanMat;
		SpanMat.DefTransformation(
			Vector3(0.5f, 0.5f, 0.5f),
			Vector3(0, 0, 0),
			Vector3(0, 0, 0)
			);


		/*�e������i�V���h�E�}�b�v��`�悷��j
		auto ShadowPtr = AddComponent<Shadowmap>();
		�e�̌`�i���b�V���j��ݒ�
		ShadowPtr->SetMeshResource(L"Coin_Model");
		ShadowPtr->SetMeshToTransformMatrix(SpanMat);*/


		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTBoneModelDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"Coin_Model");
		PtrDraw->SetMeshToTransformMatrix(SpanMat);
		PtrDraw->AddAnimation(L"Coin", 0, 60, 60);


		SetAlphaActive(true);

		auto TranP = AddComponent<Transform>();
		TranP->SetPosition(m_InitPos);
		TranP->SetScale(m_InitScale);
		TranP->SetRotation(0, 0, 0);


		//****��	
		//Kieru();
		//****��
	}

	void ScoreItem::OnUpdate()
	{

		//��]
		/*auto Trans = GetComponent<Transform>();
		Vector3 rot = Trans->GetRotation();
		rot.y += 50 * (3.14159265f / 180);
		Trans->SetRotation(rot);*/

		float ElapsedTime = App::GetApp()->GetElapsedTime();
		GetComponent<PNTBoneModelDraw>()->UpdateAnimation(ElapsedTime);

	}

	void ScoreItem::Delete()
	{
		m_Active = false;
		SetDrawActive(false);
		GetComponent<Transform>()->SetPosition(0, -10, 0);
		//SE�Đ�
		GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("ScoreItemGet");

		//�G�t�F�N�g��~
		for (auto v : m_Particle)
		{
			v->StopParticle();
		}
	}

	void ScoreItem::Detekuru()
	{
		if (m_Active)
		{
			GetComponent<Transform>()->SetPosition(m_InitPos);
		}
	}

	void ScoreItem::Kieru()
	{
		if (m_Active)
		{
			GetComponent<Transform>()->SetPosition(0, -10, 0);
		}
	}
	//--------------------------------------------------------------------------------------
	//	class Gimmick1 : public GameObject;
	//	�p�r: �X�B���̖��@[Fire]�ŗn������
	//--------------------------------------------------------------------------------------
	Gimmick1::Gimmick1(const shared_ptr<Stage>& StagePtr,Vector3 pos,Vector3 scale):
		GameObject(StagePtr),
		m_InitPos(pos),
		m_Scale(scale)
	{}

	void Gimmick1::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_Scale);
		Ptr->SetRotation(0, 0, 0);

		//�Փ˔��������
		auto PtrCol = AddComponent<CollisionObb>();

		// ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		Matrix4X4 SpanMat;
		SpanMat.DefTransformation(
			Vector3(0.6f, 0.6f, 0.6f),
			Vector3(0.0f, 0.0f, 0.0f),
			Vector3(0.0f, -0.3f, 0.0f)
			);


		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTStaticModelDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"IceBlock_Model");
		PtrDraw->SetMeshToTransformMatrix(SpanMat);

		//��������
		SetAlphaActive(true);

	}

	void Gimmick1::Delete(MagicType MT)
	{
		if (MT == Fire)
		{
			m_ActiveFlg = false;
			SetDrawActive(false);
			GetComponent<CollisionObb>()->SetUpdateActive(false);
			GetComponent<Transform>()->SetPosition(0, -10, 0);
			//SE�Đ�
			GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("FireDamage");

			//�G�t�F�N�g��~
			for (auto v : m_Particle)
			{
				v->StopParticle();
			}
		}
	}

	//--------------------------------------------------------------------------------------
	//	class Gimmick2 : public GameObject;
	//	�p�r: ���ԁA���ŏ�����
	//--------------------------------------------------------------------------------------
	Gimmick2::Gimmick2(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_Scale(scale)
	{}

	void Gimmick2::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_Scale);
		Ptr->SetRotation(0, 0, 0);

		//�Փ˔��������
		auto PtrCol = AddComponent<CollisionObb>();

		// ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		float angle = (-90) * (3.14159265f / 180);
		Matrix4X4 SpanMat;
		SpanMat.DefTransformation(
			Vector3(0.7f, 0.2f, 0.7f),
			Vector3(0, 0, 0),
			Vector3(0, 0, 0)
			);

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ShadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ShadowPtr->SetMeshResource(L"Windmill_Model");
		ShadowPtr->SetMeshToTransformMatrix(SpanMat);


		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTBoneModelDraw>();
		//�`�悷�郁�b�V����ݒ�
		//PtrDraw->SetMeshResource(L"Windmill_Model");
		PtrDraw->SetMeshResource(L"Windmill_Model");
		PtrDraw->SetMeshToTransformMatrix(SpanMat);
		//�A�j���[�V�����ǉ�
		PtrDraw->AddAnimation(L"rot", 0, 20, true, 30);
		PtrDraw->ChangeCurrentAnimation(L"rot");

		//��������
		SetAlphaActive(true);

	}

	void Gimmick2::OnUpdate()
	{
		if (m_RotFlg)
		{
			float ElapsedTime = App::GetApp()->GetElapsedTime();
			m_time += ElapsedTime;
			if (m_time > m_LimitTime)
			{
				m_RotFlg = false;
				m_time = 0;
			}
			//�A�j���[�V�����X�V
			GetComponent<PNTBoneModelDraw>()->UpdateAnimation(ElapsedTime);
		}
	}

	void Gimmick2::Delete(MagicType MT)
	{
		if (MT == Fire)
		{
			m_ActiveFlg = false;
			GetComponent<CollisionObb>()->SetUpdateActive(false);
			SetDrawActive(false);
			GetComponent<Transform>()->SetPosition(0, -10, 0);
			m_ActiveFlg = false;
			//SE�Đ�
			GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("FireDamage");

			//�G�t�F�N�g��~
			for (auto v : m_Particle)
			{
				v->StopParticle();
			}

		}

		if (MT == Wind)
		{
			GetStage()->GetSharedGameObject<Gimmick2_1>(L"WaterGate", false)->Action();
			m_RotFlg = true;
		}
	}

	//--------------------------------------------------------------------------------------
	//	class Gimmick2_1 : public GameObject;
	//	�p�r:�@���Ԃɕ����Ă�ƕ��鐅��
	//--------------------------------------------------------------------------------------
		Gimmick2_1::Gimmick2_1(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale):
			GameObject(StagePtr),
			m_InitPos(pos),
			m_Scale(scale)
		{}

		void Gimmick2_1::OnCreate()
		{
		
			auto Ptr = GetComponent<Transform>();
			Ptr->SetScale(m_Scale);
			Ptr->SetRotation(0, 0, 0);
			Ptr->SetPosition(m_InitPos);

			//�e������i�V���h�E�}�b�v��`�悷��j
			auto ShadowPtr = AddComponent<Shadowmap>();
			//�e�̌`�i���b�V���j��ݒ�
			ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");
			//�`��R���|�[�l���g�̐ݒ�
			auto PtrDraw = AddComponent<PNTStaticDraw>();
			//���b�V����ݒ�
			PtrDraw->SetMeshResource(L"DEFAULT_CUBE");

			//�e�N�X�`����ݒ�
			PtrDraw->SetTextureResource(L"WATERGATE_TX");

			//��������
			SetAlphaActive(true);

			auto PtrCol = AddComponent<CollisionObb>();
			PtrCol->SetUpdateActive(false);
		}

		void Gimmick2_1::OnUpdate()
		{
			if (m_MoveFlg)
			{
				Vector3 pos = GetComponent<Transform>()->GetPosition();
				//���Ă�Œ�
				if (m_CloseFlg)
				{
					pos.y += -0.02f;
					if (pos.y <= m_targetY)
					{
						m_MoveFlg = false;
						pos.y = m_targetY;
						//������
						auto WaterCoreGroupVec = GetStage()->GetSharedObjectGroup(L"WaterCoreGate")->GetGroupVector();
						for (auto v : WaterCoreGroupVec)
						{
							auto WCP = dynamic_pointer_cast<Gimmick3>(v.lock());
							WCP->Stop();
						}
						//�A�^������
						GetComponent<CollisionObb>()->SetUpdateActive(true);

						//�X�R�A�A�C�e���o��
						//****��
						auto SIGV = GetStage()->GetSharedObjectGroup(L"ScoreItem")->GetGroupVector();
						for (auto v : SIGV)
						{
							auto Ptr = dynamic_pointer_cast<ScoreItem>(v.lock());
							Ptr->Detekuru();
						}
						//****��
					}
				}
				//�J���Ă�Œ�
				else
				{
					pos.y += 0.02f;
					if (pos.y >= m_targetY)
					{
						m_MoveFlg = false;
						pos.y = m_targetY;
						//���J��
						auto WaterCoreGroupVec = GetStage()->GetSharedObjectGroup(L"WaterCoreGate")->GetGroupVector();
						for (auto v : WaterCoreGroupVec)
						{
							auto WCP = dynamic_pointer_cast<Gimmick3>(v.lock());
							//SE�Đ�
							GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("Water");
							WCP->Flow();
						}
						//�X�R�A�A�C�e��������
						//****��
						auto SIGV = GetStage()->GetSharedObjectGroup(L"ScoreItem")->GetGroupVector();
						for (auto v : SIGV)
						{
							auto Ptr = dynamic_pointer_cast<ScoreItem>(v.lock());
							Ptr->Kieru();
						}
						//****��
					}
				}
				GetComponent<Transform>()->SetPosition(pos);
			}
		}

		void Gimmick2_1::Action()
		{
			if (!m_MoveFlg)
			{
				//�J��
				if (m_CloseFlg)
				{
					Vector3 pos = GetComponent<Transform>()->GetPosition();
					m_targetY = pos.y + m_Scale.y;

					m_CloseFlg = false;
					m_MoveFlg = true;

					//�A�^������
					GetComponent<CollisionObb>()->SetUpdateActive(false);

				}
				//����
				else
				{
					//���������Ă�R�A������Η����̒��~
					/*
					auto WaterCoreGroup = GetStage()->GetSharedObjectGroup(L"WaterCore");
					for (auto v : WaterCoreGroup->GetGroupVector())
					{
						auto Ptr = dynamic_pointer_cast<Gimmick3>(v.lock());
						if (Ptr)
						{
							if (Ptr->GetFreeze())
							{
								return;
							}
						}
					}
					*/
					Vector3 pos = GetComponent<Transform>()->GetPosition();
					m_targetY = pos.y + -m_Scale.y;

					m_CloseFlg = true;
					m_MoveFlg = true;

				}
			}
		}

	//--------------------------------------------------------------------------------------
	//	class Water : public GameObject;
	//	�p�r: ���B�R�A�����ȊO
	//--------------------------------------------------------------------------------------
	Water::Water(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale,int num) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale),
		m_myNum(num)
	{}

	void Water::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_InitScale);
		Ptr->SetRotation(0, 0, 0);

		//�Փ˔��������
		auto PtrCol = AddComponent<CollisionObb>();
		//�e������i�V���h�E�}�b�v��`�悷��j
		//auto ShadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		//ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		//�`��R���|�[�l���g�̐ݒ�
		//auto PtrDraw = AddComponent<PNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		//PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//�`�悷��e�N�X�`����ݒ�
		//PtrDraw->SetTextureResource(L"WATER_TX");

		//��������
		//SetAlphaActive(true);

		auto ObjPtr = GetStage()->AddGameObject<GameObject>();
		auto OPT = ObjPtr->AddComponent<Transform>();
		Vector3 ObPos = m_InitPos;
		ObPos.y += -m_InitScale.y / 2.5f;
		OPT->SetPosition(ObPos);
		OPT->SetScale(m_InitScale);
		OPT->SetRotation(0, 0, 0);
		auto OPD = ObjPtr->AddComponent<PNTStaticDraw>();
		OPD->SetMeshResource(L"DEFAULT_CUBE");
		OPD->SetTextureResource(L"WATER_TX");

		m_waterunder = ObjPtr;


	}

	//���炷
	void Water::Freeze()
	{
		GetComponent<CollisionObb>()->SetUpdateActive(false);
		m_waterunder->GetComponent<PNTStaticDraw>()->SetTextureResource(L"ICE_TX");
		//SE�Đ�
		GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("Freeze");

	}
	//�n����
	void Water::Melt()
	{
		GetComponent<CollisionObb>()->SetUpdateActive(true);
		m_waterunder->GetComponent<PNTStaticDraw>()->SetTextureResource(L"WATER_TX");
		//SE�Đ�
		GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("Water");

		OnPlayer();
	}
	//�~�߂�
	void Water::Stop()
	{
		GetComponent<CollisionObb>()->SetUpdateActive(false);

		//���̕���
		//Vector3 pos = m_waterunder->GetComponent<Transform>()->GetPosition();
		//pos.y += -m_InitScale.y;
		//m_waterunder->GetComponent<Transform>()->SetPosition(pos);
		m_waterunder->SetDrawActive(false);
	}
	//����
	void Water::Flow()
	{
		//���̕���
		//Vector3 pos = m_waterunder->GetComponent<Transform>()->GetPosition();
		//pos.y += m_InitScale.y;
		//m_waterunder->GetComponent<Transform>()->SetPosition(pos);
		m_waterunder->SetDrawActive(true);

		GetComponent<CollisionObb>()->SetUpdateActive(true);

		OnPlayer();
	}

	void Water::OnPlayer() 
	{

		//�v���C���[����ɂ��邩�ǂ�������
		auto PlayerPtr = GetStage()->GetSharedGameObject<Player>(L"Player1", false);
		Vector3 Playerpos = PlayerPtr->GetComponent<Transform>()->GetPosition();

		Vector3 pos = GetComponent<Transform>()->GetPosition();
		Vector3 scale = GetComponent<Transform>()->GetScale();
		scale /= 2;
		//���W���画��
		if ((Playerpos.x < pos.x + scale.x && Playerpos.x > pos.x - scale.x) &&	/*X���W����*/
			(Playerpos.z < pos.z + scale.z && Playerpos.z > pos.z - scale.z) 	/*Z���W����*/
																				/*(Playerpos.y < pos.y + (scale.y * 3) && Playerpos.y > pos.y - scale.x)*/	/*Y���W����*/
			)
		{
			//����������n�`�_���[�W�^����
			PlayerPtr->PlayerTerrainDamege();
		}

		//2�̖�
		//�v���C���[����ɂ��邩�ǂ�������
		PlayerPtr = GetStage()->GetSharedGameObject<Player>(L"Player2", false);
		Playerpos = PlayerPtr->GetComponent<Transform>()->GetPosition();
		//���W���画��
		if ((Playerpos.x < pos.x + scale.x && Playerpos.x > pos.x - scale.x) &&	/*X���W����*/
			(Playerpos.z < pos.z + scale.z && Playerpos.z > pos.z - scale.z) 	/*Z���W����*/
																				/*(Playerpos.y < pos.y + (scale.y * 3) && Playerpos.y > pos.y - scale.x)*/	/*Y���W����*/
			)
		{
			//����������n�`�_���[�W�^����
			PlayerPtr->PlayerTerrainDamege();
		}
	}

	//--------------------------------------------------------------------------------------
	//	class WaterFall : public GameObject;
	//	�p�r: ��
	//--------------------------------------------------------------------------------------
	WaterFall::WaterFall(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale)	
	{}

	void WaterFall::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_InitScale);
		Ptr->SetRotation(0, 0, 0);

		//�Փ˔��������
		AddComponent<CollisionObb>();

		GetStage()->AddGameObject<GameObject>();
		auto OPT = AddComponent<Transform>();
		OPT->SetPosition(m_InitPos);
		OPT->SetScale(m_InitScale);
		OPT->SetRotation(0, 0, 0);
		auto OPD = AddComponent<PNTStaticDraw>();
		OPD->SetMeshResource(L"DEFAULT_CUBE");
		OPD->SetTextureResource(L"WATER_TX");



	}

	//���炷
	void WaterFall::Freeze()
	{
		GetComponent<CollisionObb>()->SetUpdateActive(true);
		GetComponent<PNTStaticDraw>()->SetTextureResource(L"ICE_TX");
		//SE�Đ�
		GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("Freeze");
		//�G�t�F�N�g��~
		for (auto v : m_ParticleIce)
		{
			v->StopParticle();
		}
		//�G�t�F�N�g�o��
		for (auto v : m_ParticleFire)
		{
			v->OnParticle(GetComponent<Transform>()->GetPosition(), Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(1.0f, 0.5f, 1.0f), Vector3(2.0f, 2.0f, 2.0f), L"FIRELIGHT_TX", false, 0.2f, 1, 2.0f);
		}
	}
	//�n����
	void WaterFall::Melt()
	{
		GetComponent<CollisionObb>()->SetUpdateActive(true);
		GetComponent<PNTStaticDraw>()->SetTextureResource(L"WATER_TX");
		//SE�Đ�
		GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("Water");

		OnPlayer();

		//�G�t�F�N�g��~
		for (auto v : m_ParticleFire)
		{
			v->StopParticle();
		}
		//�G�t�F�N�g�o��
		for (auto v : m_ParticleIce)
		{
			v->OnParticle(GetComponent<Transform>()->GetPosition(), Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(1.0f, 0.5f, 1.0f), Vector3(2.0f, 2.0f, 2.0f), L"ICELIGHT_TX", false, 0.2f, 1, 2.0f);
		}

	}
	//�~�߂�
	void WaterFall::Stop()
	{
		//�A�^������
		GetComponent<CollisionObb>()->SetUpdateActive(false);

		m_FlowFlg = false;

		//���̕���
		SetDrawActive(false);
		//�G�t�F�N�g��~
		for (auto v : m_ParticleFire)
		{
			v->StopParticle();
		}
		for (auto v : m_ParticleIce)
		{
			v->StopParticle();
		}
	}
	//����
	void WaterFall::Flow()
	{
		SetDrawActive(true);

		m_FlowFlg = true;

		//������߂�
		GetComponent<CollisionObb>()->SetUpdateActive(true);

		OnPlayer();
		//�G�t�F�N�g�o��
		for (auto v : m_ParticleIce)
		{
			v->OnParticle(GetComponent<Transform>()->GetPosition(), Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(1.0f, 0.5f, 1.0f), Vector3(2.0f, 2.0f, 2.0f), L"ICELIGHT_TX", false, 0.2f, 1, 2.0f);
		}

	}

	void WaterFall::OnPlayer()
	{

		//�v���C���[����ɂ��邩�ǂ�������
		auto PlayerPtr = GetStage()->GetSharedGameObject<Player>(L"Player1", false);
		Vector3 Playerpos = PlayerPtr->GetComponent<Transform>()->GetPosition();

		Vector3 pos = GetComponent<Transform>()->GetPosition();
		Vector3 scale = GetComponent<Transform>()->GetScale();
		scale /= 2;
		//���W���画��
		if ((Playerpos.x < pos.x + scale.x && Playerpos.x > pos.x - scale.x) &&	/*X���W����*/
			(Playerpos.z < pos.z + scale.z && Playerpos.z > pos.z - scale.z) 	/*Z���W����*/
																				/*(Playerpos.y < pos.y + (scale.y * 3) && Playerpos.y > pos.y - scale.x)*/	/*Y���W����*/
			)
		{
			//����������n�`�_���[�W�^����
			PlayerPtr->PlayerTerrainDamege();
		}

		//2�̖�
		//�v���C���[����ɂ��邩�ǂ�������
		PlayerPtr = GetStage()->GetSharedGameObject<Player>(L"Player2", false);
		Playerpos = PlayerPtr->GetComponent<Transform>()->GetPosition();
		//���W���画��
		if ((Playerpos.x < pos.x + scale.x && Playerpos.x > pos.x - scale.x) &&	/*X���W����*/
			(Playerpos.z < pos.z + scale.z && Playerpos.z > pos.z - scale.z) 	/*Z���W����*/
																				/*(Playerpos.y < pos.y + (scale.y * 3) && Playerpos.y > pos.y - scale.x)*/	/*Y���W����*/
			)
		{
			//����������n�`�_���[�W�^����
			PlayerPtr->PlayerTerrainDamege();
		}

	}

	void WaterFall::HitMagic(MagicType mt)
	{
		if (mt == IceFog && !m_FreezeFlg)
		{
			m_FreezeFlg = true;
			Freeze();
		}
		else if (mt == Fire && m_FreezeFlg)
		{
			m_FreezeFlg = false;
			Melt();
		}
	}

	//--------------------------------------------------------------------------------------
	//	class Gimmick3 : public GameObject;
	//	�p�r: ��B�̃R�A�����B���点��Ɛ������𓀂点��
	//--------------------------------------------------------------------------------------
	Gimmick3::Gimmick3(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale):
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale)
	{}

	void Gimmick3::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_InitScale);
		Ptr->SetRotation(0, 0, 0);

		//�Փ˔��������
		auto PtrCol = AddComponent<CollisionObb>();
		//�e������i�V���h�E�}�b�v��`�悷��j
		//auto ShadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		//ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		//�`��R���|�[�l���g�̐ݒ�
		//auto PtrDraw = AddComponent<PNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		//PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//�`�悷��e�N�X�`����ݒ�
		//PtrDraw->SetTextureResource(L"WATER_TX");

		//��������
		//SetAlphaActive(true);

		auto ObjPtr = GetStage()->AddGameObject<GameObject>();
		auto OPT = ObjPtr->AddComponent<Transform>();
		Vector3 ObPos = m_InitPos;
		ObPos.y += -m_InitScale.y / 2.5f;
		OPT->SetPosition(ObPos);
		OPT->SetScale(m_InitScale);
		OPT->SetRotation(0, 0, 0);
		auto OPD = ObjPtr->AddComponent<PNTStaticDraw>();
		OPD->SetMeshResource(L"DEFAULT_CUBE");
		OPD->SetTextureResource(L"WATER_TX");

		m_waterunder = ObjPtr;
	}


	//���@������������
	void Gimmick3::HitMagic(MagicType MT)
	{
		//�����Ă���n����
		if (m_FreezeFlg && MT == Fire)
		{
			Melt();
			GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("Water");
			m_FreezeFlg = false;
		}

		//�����ĂȂ������瓀�点��
		if (!m_FreezeFlg && MT == IceFog)
		{
			Freeze();	
			//SE�Đ�
			GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("Freeze");
			m_FreezeFlg = true;
		}
	}

	//���炷
	void Gimmick3::Freeze()
	{
		//����Ă�Ƃ��̂ݗL��
		if (m_FlowFlg)
		{
			GetComponent<CollisionObb>()->SetUpdateActive(false);
			m_waterunder->GetComponent<PNTStaticDraw>()->SetTextureResource(L"ICE_TX");
			for (auto v : m_waters)
			{
				v->Freeze();
			}

			for (auto v : m_waterfalls)
			{
				v->Freeze();
			}

			//�G�t�F�N�g��~
			for (auto v : m_ParticleIce)
			{
				v->StopParticle();
			}
			//�G�t�F�N�g�o��
			for (auto v : m_ParticleFire)
			{
				v->OnParticle(GetComponent<Transform>()->GetPosition(), Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(1.0f, 0.5f, 1.0f), Vector3(2.0f, 2.0f, 2.0f), L"FIRELIGHT_TX", false, 0.2f, 1, 2.0f);
			}
		}
	}

	//�n����
	void Gimmick3::Melt()
	{
		//����Ă�Ƃ��̂ݗL��
		if (m_FlowFlg)
		{
			GetComponent<CollisionObb>()->SetUpdateActive(true);
			m_waterunder->GetComponent<PNTStaticDraw>()->SetTextureResource(L"WATER_TX");
			for (auto v : m_waters)
			{
				v->Melt();
			}

			for (auto v : m_waterfalls)
			{
				v->Melt();
			}
			OnPlayer();

			//�G�t�F�N�g��~
			for (auto v : m_ParticleFire)
			{
				v->StopParticle();
			}
			//�G�t�F�N�g�o��
			for (auto v : m_ParticleIce)
			{
				v->OnParticle(GetComponent<Transform>()->GetPosition(), Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(1.0f, 0.5f, 1.0f), Vector3(2.0f, 2.0f, 2.0f), L"ICELIGHT_TX", false, 0.2f, 1, 2.0f);
			}
		}
	}

	//�~�߂�
	void Gimmick3::Stop()
	{
		//�����ĂȂ��Ƃ��̂ݗL��
		if (!m_FreezeFlg)
		{
			//�A�^������̕���
			GetComponent<CollisionObb>()->SetUpdateActive(false);

			//���̕���
			//Vector3 pos = m_waterunder->GetComponent<Transform>()->GetPosition();
			//pos.y += -m_InitScale.y;
			//m_waterunder->GetComponent<Transform>()->SetPosition(pos);

			m_waterunder->SetDrawActive(false);
			for (auto v : m_waters)
			{
				v->Stop();
			}
			for (auto v : m_waterfalls)
			{
				v->Stop();
			}
			//�G�t�F�N�g��~
			for (auto v : m_ParticleFire)
			{
				v->StopParticle();
			}
			for (auto v : m_ParticleIce)
			{
				v->StopParticle();
			}
		}
	}

	//����
	void Gimmick3::Flow()
	{
		if (!m_FlowFlg)
		{
			//�A�^������̕���
			GetComponent<CollisionObb>()->SetUpdateActive(true);

			//���̕���
			//Vector3 pos = m_waterunder->GetComponent<Transform>()->GetPosition();
			//pos.y += m_InitScale.y;
			//m_waterunder->GetComponent<Transform>()->SetPosition(pos);

			m_waterunder->SetDrawActive(true);


			for (auto v : m_waters)
			{
				v->Flow();
			}
			for (auto v : m_waterfalls)
			{
				v->Flow();
			}
			OnPlayer();

			//�G�t�F�N�g�o��
			for (auto v : m_ParticleIce)
			{
				v->OnParticle(GetComponent<Transform>()->GetPosition(), Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(1.0f, 0.5f, 1.0f), Vector3(2.0f, 2.0f, 2.0f), L"ICELIGHT_TX", false, 0.2f, 1, 2.0f);
			}
		}
	}

	void Gimmick3::OnPlayer()
	{

		//�v���C���[����ɂ��邩�ǂ�������
		auto PlayerPtr = GetStage()->GetSharedGameObject<Player>(L"Player1", false);
		Vector3 Playerpos = PlayerPtr->GetComponent<Transform>()->GetPosition();

		Vector3 pos = GetComponent<Transform>()->GetPosition();
		Vector3 scale = GetComponent<Transform>()->GetScale();
		scale /= 2;
		//���W���画��
		if ((Playerpos.x < pos.x + scale.x && Playerpos.x > pos.x - scale.x) &&	/*X���W����*/
			(Playerpos.z < pos.z + scale.z && Playerpos.z > pos.z - scale.z) 	/*Z���W����*/
																				/*(Playerpos.y < pos.y + (scale.y * 3) && Playerpos.y > pos.y - scale.x)*/	/*Y���W����*/
			)
		{
			//����������n�`�_���[�W�^����
			PlayerPtr->PlayerTerrainDamege();
		}

		//2�̖�
		//�v���C���[����ɂ��邩�ǂ�������
		PlayerPtr = GetStage()->GetSharedGameObject<Player>(L"Player2", false);
		Playerpos = PlayerPtr->GetComponent<Transform>()->GetPosition();
		//���W���画��
		if ((Playerpos.x < pos.x + scale.x && Playerpos.x > pos.x - scale.x) &&	/*X���W����*/
			(Playerpos.z < pos.z + scale.z && Playerpos.z > pos.z - scale.z) 	/*Z���W����*/
																				/*(Playerpos.y < pos.y + (scale.y * 3) && Playerpos.y > pos.y - scale.x)*/	/*Y���W����*/
			)
		{
			//����������n�`�_���[�W�^����
			PlayerPtr->PlayerTerrainDamege();
		}
	}
	//--------------------------------------------------------------------------------------
	//	class Gimmick5 : public GameObject;
	//	�p�r: ���B�X�̖��@[Icefog]�ŏ�����
	//--------------------------------------------------------------------------------------

	Gimmick5::Gimmick5(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_Scale(scale)
	{}

	void Gimmick5::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_Scale);
		Ptr->SetRotation(0, 0, 0);

		//�Փ˔��������
		auto PtrCol = AddComponent<CollisionObb>();

		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"DEFAULT_SQUARE");
		//�`�悷��e�N�X�`����ݒ�
		PtrDraw->SetTextureResource(L"FIREGIMMICK5_0_TX");

		//��������
		SetAlphaActive(true);
		SetDrawLayer(1);
	}

	void Gimmick5::OnUpdate()
	{
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time > m_IntervalTime)
		{
			m_time = 0;
			m_nowTexture++;
			if (m_nowTexture > 2)
			{
				m_nowTexture = 0;
			}

			switch (m_nowTexture)
			{
			case 0:
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"FIREGIMMICK5_0_TX");
				break;
			case 1:
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"FIREGIMMICK5_1_TX");
				break;
			case 2:
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"FIREGIMMICK5_2_TX");
				break;
			default:
				break;
			}
		}
	}

	void Gimmick5::Delete(MagicType MT)
	{
		if (MT == IceFog)
		{
			m_ActiveFlg = false;
			SetDrawActive(false);
			GetComponent<CollisionObb>()->SetUpdateActive(false);
			GetComponent<Transform>()->SetPosition(0, -10, 0);
			//SE�Đ�
			GetStage()->GetSharedGameObject<SEManager>(L"SEM", false)->OnSe("Freeze");

			//�A�b�v�f�[�g��~
			SetUpdateActive(false);
			//�G�t�F�N�g��~
			for (auto v : m_Particle)
			{
				v->StopParticle();
			}

		}
	}

	//--------------------------------------------------------------------------------------
	//	class Cloud : public GameObject;
	//	�p�r: �E���獶�ɗ����_�̐��݂̐e
	//--------------------------------------------------------------------------------------
	Cloud::Cloud(const shared_ptr<Stage>& StagePtr, Vector3 scale, float speed,int layer,int mode):
		GameObject(StagePtr),
		m_Scale(scale),
		m_Speed(speed),
		m_Layer(layer),
		m_mode(mode)
	{}

	void Cloud::OnUpdate()
	{
		m_time += App::GetApp()->GetElapsedTime();
		for (auto v : m_Clouds)
		{
			//�\������Ă�Έړ�
			if (v->GetDrawActive())
			{
				Vector3 pos = v->GetComponent<Transform>()->GetPosition();
				pos.x += -m_Speed;
				v->GetComponent<Transform>()->SetPosition(pos);
				//���W�����[�{�����̃X�P�[���̔����ړ��ł�����
				if (pos.x < (-960 - (m_Scale.x / 2)))
				{
					v->SetDrawActive(false);

				}
			}
		}

		if (m_SpawnFlg)
		{
			if (m_time > m_IntTime/2)
			{
				if (m_MoveFlg)
				{
					m_MoveFlg = false;
					//��莞�Ԃŕό`
					for (auto v : m_Clouds)
					{
						//�\������Ă�Εό`
						if (v->GetDrawActive())
						{
							Vector3 scale = v->GetComponent<Transform>()->GetScale();
							scale.x += rand() % 50 - 25;
							scale.y += rand() % 50 - 25;
							v->GetComponent<Transform>()->SetScale(scale);
						}
					}
				}
			}
			if (m_time > m_IntTime)
			{
				m_MoveFlg = true;
				//��莞�Ԃŕό`
				for (auto v : m_Clouds)
				{
					//�\������Ă�Εό`
					if (v->GetDrawActive())
					{
						Vector3 scale = v->GetComponent<Transform>()->GetScale();
						scale.x += rand() % 50 - 25;
						scale.y += rand() % 50 - 25;
						v->GetComponent<Transform>()->SetScale(scale);
					}
				}

				//�o�Ă������ǂ����̃t���O
				bool SpawnFlg = true;
				m_time = 0;
				//�ݒ肵���m���ɂ���������
				if (rand() % 100 < m_ParSpawn)
				{
					for (auto v : m_Clouds)
					{
						//�����\������ĂȂ���΍ė��p
						if (!v->GetDrawActive())
						{
							SpawnFlg = false;
							v->SetDrawActive(true);
							Vector3 pos;
							if (m_mode == 0)
							{
								pos = Vector3(1200, rand() % 600 -200, 0);
							}
							else
							{
								pos = Vector3(1200, rand() % 400 + 200, 0);
							}
							v->GetComponent<Transform>()->SetPosition(pos);

							if (rand() % 2 == 1)
							{
								v->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"CLOUD1_TX");
							}
							else
							{
								v->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"CLOUD2_TX");
							}
							//�T�C�Y������
							v->GetComponent<Transform>()->SetScale(m_Scale);

							break;
						}
					}
					//�����ė��p�ł��Ȃ�������
					if (SpawnFlg)
					{
						auto obj = GetStage()->AddGameObject<GameObject>();
						auto obTrans = obj->AddComponent<Transform>();
						Vector3 pos;
						if (m_mode == 0)
						{
							pos = Vector3(1200, rand() % 600 - 200, 0);
						}
						else
						{
							pos = Vector3(1200, rand() % 400 + 200, 0);
						}

						obTrans->SetPosition(pos);
						obTrans->SetScale(m_Scale);
						obTrans->SetRotation(0, 0, 0);
						auto obDraw = obj->AddComponent<PCTSpriteDraw>();
						obDraw->SetTextureResource(L"CLOUD1_TX");
						obj->SetAlphaActive(true);
						obj->SetDrawLayer(m_Layer);

						m_Clouds.push_back(obj);
					}
				}
			}
		}
	}

	void Cloud::StopCloud()
	{
		m_SpawnFlg = false;
		m_Speed *= 10;
	}
}
//end basecross
