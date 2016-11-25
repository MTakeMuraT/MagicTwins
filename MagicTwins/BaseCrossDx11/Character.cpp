/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
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
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_Scale);
		Ptr->SetRotation(0, 0, 0);

		//�Փ˔��������
		auto PtrCol = AddComponent<CollisionObb>();
		//�������̂ݔ���
		//PtrCol->SetIsHitAction(IsHitAction::Stop);

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ShadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//�`�悷��e�N�X�`����ݒ�
		PtrDraw->SetTextureResource(L"GOAL_TX");

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
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		m_InitScale *= 0.9f;
		Ptr->SetScale(m_InitScale);
		Ptr->SetRotation(m_InitRot);

		//�Փ˔��������
		auto PtrCol = AddComponent<CollisionObb>();

		// ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		float angle = (-90) * (3.14159265f / 180);
		Matrix4X4 SpanMat;
		SpanMat.DefTransformation(
			Vector3(1.0f, 1.0f, 1.0f),
			Vector3(0,0, 0),
			Vector3(0, -0.5f, 0)
			);

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ShadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ShadowPtr->SetMeshResource(L"Fence_Model");
		ShadowPtr->SetMeshToTransformMatrix(SpanMat);


		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTStaticModelDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"Fence_Model");
		PtrDraw->SetMeshToTransformMatrix(SpanMat);

		//��������
		SetAlphaActive(true);

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
		//�������̂ݔ���
		PtrCol->SetIsHitAction(IsHitAction::Stop);

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
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale):
		GameObject(StagePtr),
		m_InitPos(pos),
		m_Scale(scale)
	{}

	void Enemy::OnCreate()
	{
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(m_InitPos);
		Ptr->SetScale(m_Scale);

		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		//�`�悷��e�N�X�`����ݒ�
		PtrDraw->SetTextureResource(L"ENEMY_TX");

		//��������
		SetAlphaActive(true);

	}

	void Enemy::OnUpdate()
	{
		//�~�܂��ĂȂ���Βǂ�
		if (!m_StopFlg)
		{
			auto P1P = GetStage()->GetSharedGameObject<Player>(L"Player1", false);
			auto P2P = GetStage()->GetSharedGameObject<Player>(L"Player2", false);

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
				nowpos.x += velo.x * App::GetApp()->GetElapsedTime() * m_speed;
				nowpos.z += velo.y * App::GetApp()->GetElapsedTime() * m_speed;
				GetComponent<Transform>()->SetPosition(nowpos);
			}

			else if (P2P->GetActive())
			{
				Vector3 topos = P2P->GetComponent<Transform>()->GetPosition();
				Vector3 nowpos = GetComponent<Transform>()->GetPosition();
				Vector3 dir;
				dir = topos - nowpos;
				Vector2 velo = Vector2(dir.x, dir.z);
				float angle = atan2(velo.y, velo.x);
				velo.x = cos(angle);
				velo.y = sin(angle);
				nowpos.x += velo.x * App::GetApp()->GetElapsedTime() * m_speed;
				nowpos.z += velo.y * App::GetApp()->GetElapsedTime() * m_speed;
				GetComponent<Transform>()->SetPosition(nowpos);
			}
		}
		else
		{
			m_time += App::GetApp()->GetElapsedTime();
			if (m_time > m_StopTime)
			{
				m_StopFlg = false;
				m_time = 0;
				GetComponent<PNTStaticDraw>()->SetDiffuse(Color4(1, 1, 1, 1));
			}
		}
	}

	void Enemy::StopEnemy()
	{
		m_StopFlg = true;
		m_time = 0;
		GetComponent<PNTStaticDraw>()->SetDiffuse(Color4(1, 1, 1,0.5f));

	}

	void Enemy::ResetPos()
	{
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
			m_alpha += 0.01f;
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
		m_nowTime = m_LimitTime;
		SetDrawLayer(5);

		auto numobj = GetStage()->AddGameObject<NumberSprite>(0, Vector2(830, 470), Vector2(100, 100), 6);
		m_numberSp = numobj;
	}

	void LimitTime::OnUpdate()
	{
		//wstring txt = Util::IntToWStr((int)m_nowTime);
		//GetComponent<StringSprite>()->SetText(txt);

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
			TranP->SetPosition(m_pos.x - (distance*((m_digit-1)-j)), m_pos.y, 0);
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

	void NumberSprite::SetNum(int num)
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
		for (int i = m_digit-1; i >= 0; i--)
		{
			int digi = i;
			int setnum = masternum / pow(10, (digi));
			masternum = masternum % (int)(pow(10, (digi)));

			m_Numbers[i]->GetComponent<PCTSpriteDraw>()->SetMeshResource(m_Mesh[setnum]);
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
		SetDrawLayer(7);

		//�Ó]
		auto BlackP = GetStage()->AddGameObject<GameObject>();
		auto BTranP = BlackP->AddComponent<Transform>();
		BTranP->SetPosition(0, 0, 0);
		BTranP->SetScale(1920, 1080, 1);
		BTranP->SetRotation(0, 0, 0);
		auto BDrawP = BlackP->AddComponent<PCTSpriteDraw>();
		BDrawP->SetTextureResource(L"BLACK_TX");
		BDrawP->SetDiffuse(Color4(1, 1, 1, 0.5f));

		BlackP->SetDrawLayer(6);
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
		ReTryP->SetDrawLayer(7);
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
		MaPP->SetDrawLayer(7);
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
		SSP->SetDrawLayer(7);
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
		TiP->SetDrawLayer(7);
		m_TitleLogo = TiP;

		//�}�b�v�摜
		auto MaP = GetStage()->AddGameObject<GameObject>();
		auto MaTP = MaP->AddComponent<Transform>();
		MaTP->SetPosition(0, 0, 0);
		MaTP->SetScale(500,500,1);
		MaTP->SetRotation(0, 0, 0);
		auto MaTDP = MaP->AddComponent<PCTSpriteDraw>();
		MaTDP->SetTextureResource(L"MAP_TX");
		MaP->SetAlphaActive(true);
		MaP->SetDrawActive(false);
		MaP->SetDrawLayer(7);
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
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
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

					m_Black->SetDrawLayer(8);
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
			m_BlackAlpha += +0.01f;
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
		TranP->SetPosition(450,-450, 0);
		TranP->SetRotation(0, 0, 0);
		TranP->SetScale(100, 100, 0);
		SetAlphaActive(true);
		SetDrawLayer(5);

	}

	//--------------------------------------------------------------------------------------
	//	class ScoreItem : public GameObject;
	//	�p�r:�@�X�R�A�A�C�e��
	//--------------------------------------------------------------------------------------
	ScoreItem::ScoreItem(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale):
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale)
	{}

	void ScoreItem::OnCreate()
	{
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ShadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");
		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//���b�V����ݒ�
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");

		//�e�N�X�`����ݒ�
		PtrDraw->SetTextureResource(L"SCOREITEM_TX");

		SetAlphaActive(true);

		auto TranP = AddComponent<Transform>();
		TranP->SetPosition(m_InitPos);
		TranP->SetScale(m_InitScale);
		TranP->SetRotation(0, 0, 0);


		//****��	
		Kieru();
		//****��
	}

	void ScoreItem::Delete()
	{
		m_Active = false;
		SetDrawActive(false);
		GetComponent<Transform>()->SetPosition(0, -10, 0);

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
	//	class SEManager : public GameObject;
	//	�p�r: BGM�ȊO��SE���܂Ƃ߂����
	//--------------------------------------------------------------------------------------
	SEManager::SEManager(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
	{}

	void SEManager::OnCreate()
	{
		m_Se = ObjectFactory::Create<MultiAudioObject>();
	}

	void SEManager::OnSe(string name)
	{
		//�^�C�g�����艹
		if (name == "SelectTitle")
		{
			m_Se->AddAudioResource(L"SelectTitleSE");
			m_Se->Start(L"SelectTitleSE", 0.5f);
		}
		if (name == "Select")
		{
			m_Se->AddAudioResource(L"SelectSE");
			m_Se->Start(L"SelectSE", 0.5f);
		}
		if (name == "Damege")
		{
			m_Se->AddAudioResource(L"DamageSE");
			m_Se->Start(L"DamageSE", 0.5f);
		}
		if (name == "Water")
		{
			m_Se->AddAudioResource(L"WaterSE");
			m_Se->Start(L"WaterSE", 0.5f);
		}
		if (name == "Freeze")
		{
			m_Se->AddAudioResource(L"FreezeSE");
			m_Se->Start(L"FreezeSE", XAUDIO2_LOOP_INFINITE, 0.5f);
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

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ShadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");
		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		//�`�悷��e�N�X�`����ݒ�
		PtrDraw->SetTextureResource(L"GIMMICK1_TX");

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
			Vector3(1.0f, 0.3f, 1.0f),
			Vector3(0,angle, 0),
			Vector3(0, 0, 0)
			);

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ShadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		//ShadowPtr->SetMeshResource(L"Windmill_Model");
		ShadowPtr->SetMeshResource(L"Windmill_Model");
		ShadowPtr->SetMeshToTransformMatrix(SpanMat);


		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTStaticModelDraw>();
		//�`�悷�郁�b�V����ݒ�
		//PtrDraw->SetMeshResource(L"Windmill_Model");
		PtrDraw->SetMeshResource(L"Windmill_Model");
		PtrDraw->SetMeshToTransformMatrix(SpanMat);

		//��������
		SetAlphaActive(true);

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
		}

		if (MT == Wind)
		{
			GetStage()->GetSharedGameObject<Gimmick2_1>(L"WaterGate", false)->Action();
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

	}
	//�n����
	void Water::Melt()
	{
		GetComponent<CollisionObb>()->SetUpdateActive(true);
		m_waterunder->GetComponent<PNTStaticDraw>()->SetTextureResource(L"WATER_TX");

	}
	//�~�߂�
	void Water::Stop()
	{
		GetComponent<CollisionObb>()->SetUpdateActive(false);

		//���̕���
		Vector3 pos = m_waterunder->GetComponent<Transform>()->GetPosition();
		pos.y += -m_InitScale.y;
		m_waterunder->GetComponent<Transform>()->SetPosition(pos);

	}
	//����
	void Water::Flow()
	{
		//���̕���
		Vector3 pos = m_waterunder->GetComponent<Transform>()->GetPosition();
		pos.y += m_InitScale.y;
		m_waterunder->GetComponent<Transform>()->SetPosition(pos);

		GetComponent<CollisionObb>()->SetUpdateActive(true);
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
		GetComponent<CollisionObb>()->SetUpdateActive(false);
		m_waterunder->GetComponent<PNTStaticDraw>()->SetTextureResource(L"ICE_TX");
		for (auto v : m_waters)
		{
			v->Freeze();
		}
	}

	//�n����
	void Gimmick3::Melt()
	{
		GetComponent<CollisionObb>()->SetUpdateActive(true);
		m_waterunder->GetComponent<PNTStaticDraw>()->SetTextureResource(L"WATER_TX");
		for (auto v : m_waters)
		{
			v->Melt();
		}
	}

	//�~�߂�
	void Gimmick3::Stop()
	{
		//�A�^������̕���
		GetComponent<CollisionObb>()->SetUpdateActive(false);

		//���̕���
		Vector3 pos = m_waterunder->GetComponent<Transform>()->GetPosition();
		pos.y += -m_InitScale.y;
		m_waterunder->GetComponent<Transform>()->SetPosition(pos);

			for (auto v : m_waters)
		{
			v->Stop();
		}
	}

	//����
	void Gimmick3::Flow()
	{
		//�A�^������̕���
		GetComponent<CollisionObb>()->SetUpdateActive(true);

		//���̕���
		Vector3 pos = m_waterunder->GetComponent<Transform>()->GetPosition();
		pos.y += m_InitScale.y;
		m_waterunder->GetComponent<Transform>()->SetPosition(pos);


		for (auto v : m_waters)
		{
			v->Flow();
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

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ShadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");
		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		//�`�悷��e�N�X�`����ݒ�
		PtrDraw->SetTextureResource(L"GIMMICK5_TX");

		//��������
		SetAlphaActive(true);
	}

	void Gimmick5::Delete(MagicType MT)
	{
		if (MT == IceFog)
		{
			m_ActiveFlg = false;
			SetDrawActive(false);
			GetComponent<CollisionObb>()->SetUpdateActive(false);
			GetComponent<Transform>()->SetPosition(0, -10, 0);

		}
	}
}
//end basecross
