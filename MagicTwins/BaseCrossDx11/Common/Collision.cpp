/*!
@file Collision.cpp
@brief �Փ˔���R���|�[�l���g����
*/
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	struct Collision::Impl;
	//	�p�r: �R���|�[�l���gImpl�N���X
	//--------------------------------------------------------------------------------------
	struct Collision::Impl {
		bool m_Fixed;		//�Î~�I�u�W�F�N�g���ǂ���
		bool m_SendEventActive;	//�Փ˂����Ƃ���Send�C�x���g�𔭐����邩�ǂ���
		bool m_PostEventActive;	//�Փ˂����Ƃ���Post�C�x���g�𔭐����邩�ǂ���
		float m_PostDispatchTime;		//Post�𔭍s����ꍇ�̒x������
		wstring m_EventString;	//�Փ˂����Ƃ��̃C�x���g�L�[

		weak_ptr<GameObject> m_SubDispatchObject;	//�Փ˂�������m�点��T�u�I�u�W�F�N�g
		weak_ptr<MeshResource> m_MeshResource;	//���b�V�����\�[�X
		weak_ptr<GameObjectGroup> m_ExcludeCollisionGroup;	//���肩�珜�O����O���[�v

		IsHitAction m_IsHitAction;	//�Փ˂������̓����`

		vector<shared_ptr<GameObject>> m_HitObjectVec;	//�q�b�g�����I�u�W�F�N�g

		Impl() :
			m_Fixed(false),
			m_SendEventActive(false),
			m_PostEventActive(false),
			m_PostDispatchTime(0),
			m_EventString(L"CollisionEvent"),
			m_IsHitAction(IsHitAction::AutoOnObjectRepel)
		{
		}
		~Impl() {}
	};

	//--------------------------------------------------------------------------------------
	//	class Collision : public Component ;
	//	�p�r: �Փ˔���R���|�[�l���g�̐e�N���X
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	Collision::Collision(const shared_ptr<GameObject>& GameObjectPtr) :
		Component(GameObjectPtr),
		pImpl(new Impl())
	{}
	Collision::~Collision() {}

	bool Collision::GetFixed() const {
		return pImpl->m_Fixed;
	}
	bool Collision::IsFixed() const {
		return pImpl->m_Fixed;
	}
	void Collision::SetFixed(bool b) {
		pImpl->m_Fixed = b;
	}

	//����

	void Collision::OnUpdate() {
		//Collision���L�����ǂ���
		if (!IsUpdateActive()) {
			return;
		}
		//Fixed���ǂ���
		if (IsFixed()) {
			return;
		}
		auto& ObjVec = GetGameObject()->GetStage()->GetGameObjectVec();
		for (auto& ObjPtr : ObjVec) {
			if ((GetGameObject() != ObjPtr) && ObjPtr->IsUpdateActive()) {
				//���łɓ�������ƏՓ˂��Ă邩�ǂ���
				if (pImpl->m_HitObjectVec.size() > 0) {
					bool chk = false;
					for (auto& v : pImpl->m_HitObjectVec) {
						if (v == ObjPtr) {
							chk = true;
							break;
						}
					}
					if (chk) {
						continue;
					}
				}
				//�����Collision���擾
				auto DestCollisionPtr = ObjPtr->GetComponent<Collision>(false);
				if (DestCollisionPtr) {
					if (!DestCollisionPtr->IsUpdateActive()) {
						//�����Collision������
						continue;
					}
					//�Փ˔���
					CollisionTestBase(DestCollisionPtr);
				}
			}
		}

	}

	void Collision::AddHitObject(const shared_ptr<GameObject>& DestObject) {
		pImpl->m_HitObjectVec.push_back(DestObject);
	}
	void Collision::ClearHitObject() {
		pImpl->m_HitObjectVec.clear();
	}
	vector<shared_ptr<GameObject>>& Collision::GetHitObjectVec() {
		return pImpl->m_HitObjectVec;
	}

	IsHitAction Collision::GetIsHitAction() const {
		return pImpl->m_IsHitAction;

	}
	void Collision::SetIsHitAction(IsHitAction HitAction) {
		pImpl->m_IsHitAction = HitAction;
	}

	void Collision::CollisionTestBase(const shared_ptr<Collision>& DestColl) {
		auto DestCollisionSpherePtr = dynamic_pointer_cast<CollisionSphere>(DestColl);
		auto DestCollisionObbPtr = dynamic_pointer_cast<CollisionObb>(DestColl);
		auto DestCollisionRectPtr = dynamic_pointer_cast<CollisionRect>(DestColl);
		if (DestCollisionSpherePtr) {
			CollisionTest(DestCollisionSpherePtr);
		}
		else if (DestCollisionObbPtr) {
			CollisionTest(DestCollisionObbPtr);
		}
		else if (DestCollisionRectPtr) {
			CollisionTest(DestCollisionRectPtr);
		}
	}


	//--------------------------------------------------------------------------------------
	//	struct CollisionSphere::Impl;
	//	�p�r: �R���|�[�l���gImpl�N���X
	//--------------------------------------------------------------------------------------
	struct CollisionSphere::Impl {
		float m_MakedDiameter;					//�쐬���̒��a
		Impl() :
			m_MakedDiameter(1.0f)
		{}
		~Impl() {}

	};


	//--------------------------------------------------------------------------------------
	//	class CollisionSphere : public Collision ;
	//	�p�r: ���Փ˔���R���|�[�l���g
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	CollisionSphere::CollisionSphere(const shared_ptr<GameObject>& GameObjectPtr) :
		Collision(GameObjectPtr),
		pImpl(new Impl())
	{}
	CollisionSphere::~CollisionSphere() {}

	void CollisionSphere::OnCreate() {
		SetDrawActive(false);
	}

	//�A�N�Z�T
	float CollisionSphere::GetMakedDiameter() const {
		return pImpl->m_MakedDiameter;
	}
	void CollisionSphere::SetMakedDiameter(float f) {
		pImpl->m_MakedDiameter = f;
	}
	float CollisionSphere::GetMakedRadius() const {
		return pImpl->m_MakedDiameter * 0.5f;
	}
	void CollisionSphere::SetMakedRadius(float f) {
		pImpl->m_MakedDiameter = f * 2.0f;
	}

	SPHERE CollisionSphere::GetSphere() const {
		auto TransPtr = GetGameObject()->GetComponent<Transform>();
		Matrix4X4 MatBase;
		MatBase.Scaling(pImpl->m_MakedDiameter, pImpl->m_MakedDiameter, pImpl->m_MakedDiameter);
		MatBase *= TransPtr->GetWorldMatrix();
		//���̃I�u�W�F�N�g��SPHERE���쐬
		SPHERE Ret(MatBase.PosInMatrixSt(), MatBase.ScaleInMatrix().x * 0.5f);
		return Ret;
	}
	SPHERE CollisionSphere::GetBeforeSphere() const {
		auto TransPtr = GetGameObject()->GetComponent<Transform>();
		Matrix4X4 MatBase;
		MatBase.Scaling(pImpl->m_MakedDiameter, pImpl->m_MakedDiameter, pImpl->m_MakedDiameter);
		MatBase *= TransPtr->GetBeforeWorldMatrix();
		//���̃I�u�W�F�N�g��SPHERE���쐬
		SPHERE Ret(MatBase.PosInMatrixSt(), MatBase.ScaleInMatrix().x * 0.5f);
		return Ret;
	}
	void CollisionSphere::CollisionTest(const shared_ptr<CollisionSphere>& DestColl) {
		auto PtrTransform = GetGameObject()->GetComponent<Transform>();
		auto PtrDestTransform = DestColl->GetGameObject()->GetComponent<Transform>();
		Vector3 SrcVelocity = PtrTransform->GetVelocity();
		Vector3 DestVelocity = PtrDestTransform->GetVelocity();

		//�O��̃^�[������̎���
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//���̏ꍇ�́A���ׂĈړ��ȊO�ω��Ȃ��Ƃ���
		SPHERE SrcSphere = GetSphere();
		SPHERE SrcBeforSphere = GetBeforeSphere();
		//�����CollisionSphere
		SPHERE DestSphere = DestColl->GetSphere();
		SPHERE DestBeforeSphere = DestColl->GetBeforeSphere();
		Vector3 SpanVelocity = SrcVelocity - DestVelocity;
		float HitTime = 0;
		if (HitTest::CollisionTestSphereSphere(SrcBeforSphere, SpanVelocity, DestSphere, 0, ElapsedTime, HitTime)) {
			if (HitTime <= 0) {
				HitTime = 0;
			}
			if (HitTime >= ElapsedTime) {
				HitTime = ElapsedTime;
			}
			auto AfterHitTime = ElapsedTime - HitTime;
			//����Fix�łȂ���ΏՓˑO�܂Ŗ߂�
			if (!IsFixed()) {
				AddHitObject(DestColl->GetGameObject());
				BackToBefore(SrcVelocity, HitTime);
				AfterCollision(SrcVelocity, DestColl, AfterHitTime);
			}
			//�������肪Fix�łȂ���Α��葤���ՓˑO�܂Ŗ߂�
			if (!DestColl->IsFixed()) {
				DestColl->AddHitObject(GetGameObject());
				DestColl->BackToBefore(DestVelocity, HitTime);
				DestColl->AfterCollision(DestVelocity,GetThis<CollisionSphere>(), AfterHitTime);
			}
			//���肪Fix�Ȃ玩�ȑޔ������ł͏Փ˂��Ă���\��������̂Ŕ�������ăG�X�P�[�v����
			else {
				CollisionEscape(DestColl);
			}
		}

	}

	void CollisionSphere::CollisionTest(const shared_ptr<CollisionObb>& DestColl) {
		auto PtrTransform = GetGameObject()->GetComponent<Transform>();
		auto PtrDestTransform = DestColl->GetGameObject()->GetComponent<Transform>();
		Vector3 SrcVelocity = PtrTransform->GetVelocity();
		Vector3 DestVelocity = PtrDestTransform->GetVelocity();

		//�O��̃^�[������̎���
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//�ړ��ȊO�ω��Ȃ�
		SPHERE SrcSphere = GetSphere();
		SPHERE SrcBeforSphere = GetBeforeSphere();
		//����
		OBB DestObb = DestColl->GetObb();
		OBB DestBeforeObb = DestColl->GetBeforeObb();

		Vector3 SpanVelocity = SrcVelocity - DestVelocity;
		float HitTime = 0;
		if (HitTest::CollisionTestSphereObb(SrcBeforSphere, SpanVelocity, DestObb, 0, ElapsedTime, HitTime)) {
			if (HitTime <= 0) {
				HitTime = 0;
			}
			if (HitTime >= ElapsedTime) {
				HitTime = ElapsedTime;
			}
			auto AfterHitTime = ElapsedTime - HitTime;
			//����Fix�łȂ���ΏՓˏ��̓o�^
			if (!IsFixed()) {
				AddHitObject(DestColl->GetGameObject());
				BackToBefore(SrcVelocity, HitTime);
				AfterCollision(SrcVelocity, DestColl, AfterHitTime);
			}
			//�������肪Fix�łȂ���ΏՑ��葤�ɓˏ��̓o�^
			if (!DestColl->IsFixed()) {
				DestColl->AddHitObject(GetGameObject());
				DestColl->BackToBefore(DestVelocity,HitTime);
				DestColl->AfterCollision(DestVelocity, GetThis<CollisionSphere>(), AfterHitTime);
			}
			//���肪Fix�Ȃ玩�ȑޔ������ł͏Փ˂��Ă���\��������̂Ŕ�������ăG�X�P�[�v����
			else {
				CollisionEscape(DestColl);
			}
		}
	}

	void CollisionSphere::CollisionTest(const shared_ptr<CollisionRect>& DestColl) {
		auto PtrTransform = GetGameObject()->GetComponent<Transform>();
		auto PtrDestTransform = DestColl->GetGameObject()->GetComponent<Transform>();
		Vector3 SrcVelocity = PtrTransform->GetVelocity();
		Vector3 DestVelocity = PtrDestTransform->GetVelocity();

		//�O��̃^�[������̎���
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//�ړ��ȊO�ω��Ȃ�
		SPHERE SrcSphere = GetSphere();
		SPHERE SrcBeforSphere = GetBeforeSphere();
		//����
		COLRECT DestRect = DestColl->GetColRect();
		COLRECT DestBeforeRect = DestColl->GetBeforeColRect();

		Vector3 SpanVelocity = SrcVelocity - DestVelocity;
		float HitTime = 0;
		if (HitTest::CollisionTestSphereRect(SrcBeforSphere, SpanVelocity, DestRect, 0, ElapsedTime, HitTime)) {
			if (HitTime <= 0) {
				HitTime = 0;
			}
			if (HitTime >= ElapsedTime) {
				HitTime = ElapsedTime;
			}
			auto AfterHitTime = ElapsedTime - HitTime;
			//����Fix�łȂ���ΏՓˏ��̓o�^
			if (!IsFixed()) {
				AddHitObject(DestColl->GetGameObject());
				BackToBefore(SrcVelocity, HitTime);
				AfterCollision(SrcVelocity, DestColl, AfterHitTime);
			}
			//����͕K��FIX�ł���B
			//���肪Fix�Ȃ玩�ȑޔ������ł͏Փ˂��Ă���\��������̂Ŕ�������ăG�X�P�[�v����
			CollisionEscape(DestColl);
		}
	}



	void CollisionSphere::BackToBefore(const Vector3 TotalVelocoty, float SpanTime) {
		//���ׂĈړ��ȊO�ω��Ȃ��Ƃ���
		SPHERE SrcSphere = GetSphere();
		SPHERE SrcBeforSphere = GetBeforeSphere();
		auto PtrTransform = GetGameObject()->GetComponent<Transform>();
		Vector3 Pos = SrcBeforSphere.m_Center + TotalVelocoty * SpanTime;
		PtrTransform->SetPosition(Pos);
	}


	void CollisionSphere::AfterCollision(const Vector3 TotalVelocoty, const shared_ptr<CollisionSphere>& DestColl, float SpanTime) {
		SPHERE sp = GetSphere();
		SPHERE sp2 = DestColl->GetSphere();
		//�ړ_�ւ̃x�N�g��
		Vector3 ContactBase = sp2.m_Center - sp.m_Center;
		ContactBase.Normalize();
		//�ŋߐړ_���璼�s���̒����i���ςŋ��߂�j
		float Len = Vector3EX::Dot(TotalVelocoty, ContactBase);
		Vector3 Contact = ContactBase * Len;
		//��������͑��x����ړ_�ւ̃x�N�g���������Z
		Vector3 Slide = TotalVelocoty - Contact;
		auto PtrTransform = GetGameObject()->GetComponent<Transform>();
		auto Pos = sp.m_Center + Slide * SpanTime;
		PtrTransform->SetToBefore();
		PtrTransform->SetPosition(Pos);

		//Rigidbody��Gravity�͂��ꂼ��̑��x�̕��U��ݒ肷��
		auto PtrGrav = GetGameObject()->GetComponent<Gravity>(false);
		bool horizontal = false;
		if (PtrGrav) {
			auto Grav = PtrGrav->GetGravity();
			Grav.Normalize();
			if (Vector3EX::AngleBetweenNormals(Grav, ContactBase) <= 0.01f) {
				PtrGrav->SetGravityVelocityZero();
				horizontal = true;
			}
			else {
				//�ŋߐړ_���璼�s���̒����i���ςŋ��߂�j
				Len = Vector3EX::Dot(PtrGrav->GetGravityVelocity(), ContactBase);
				Contact = ContactBase * Len;
				Slide = PtrGrav->GetGravityVelocity() - Contact;
				PtrGrav->SetGravityVelocity(Slide);
				horizontal = false;
			}
		}

		auto PtrRigid = GetGameObject()->GetComponent<Rigidbody>(false);
		if (PtrRigid) {
			switch (GetIsHitAction()) {
			case IsHitAction::AutoOnObjectRepel:
			{
				if (horizontal) {
					//�ŋߐړ_���璼�s���̒����i���ςŋ��߂�j
					Len = Vector3EX::Dot(PtrRigid->GetVelocity(), ContactBase);
					Contact = ContactBase * Len;
					Slide = PtrRigid->GetVelocity() - Contact;
					PtrRigid->SetVelocity(Slide);
				}
				else {
					auto Ref = Vector3EX::Reflect(PtrRigid->GetVelocity(), ContactBase);
					//�����W��
					Ref *= PtrRigid->GetReflection();
					PtrRigid->SetVelocity(Ref);
				}
			}
			break;
			case IsHitAction::Slide:
				//�ŋߐړ_���璼�s���̒����i���ςŋ��߂�j
				Len = Vector3EX::Dot(PtrRigid->GetVelocity(), ContactBase);
				Contact = ContactBase * Len;
				Slide = PtrRigid->GetVelocity() - Contact;
				PtrRigid->SetVelocity(Slide);
				break;
			default:
				break;
			}
		}
	}


	void CollisionSphere::AfterCollision(const Vector3 TotalVelocoty, const shared_ptr<CollisionObb>& DestColl, float SpanTime) {
		SPHERE sp = GetSphere();
		OBB obb = DestColl->GetObb();
		Vector3 Ret;
		HitTest::SPHERE_OBB(sp, obb, Ret);
		//�ړ_�ւ̃x�N�g��
		Vector3 ContactBase = Ret - sp.m_Center;
		ContactBase.Normalize();
		//�ŋߐړ_���璼�s���̒����i���ςŋ��߂�j
		float Len = Vector3EX::Dot(TotalVelocoty, ContactBase);
		Vector3 Contact = ContactBase * Len;
		//��������͑��x����ړ_�ւ̃x�N�g���������Z
		Vector3 Slide = TotalVelocoty - Contact;
		auto PtrTransform = GetGameObject()->GetComponent<Transform>();
		auto Pos = sp.m_Center + Slide * SpanTime;
		PtrTransform->SetToBefore();
		PtrTransform->SetPosition(Pos);

		//Rigidbody��Gravity�͂��ꂼ��̑��x�̕��U��ݒ肷��
		auto PtrGrav = GetGameObject()->GetComponent<Gravity>(false);
		bool horizontal = false;
		if (PtrGrav) {
			auto Grav = PtrGrav->GetGravity();
			Grav.Normalize();
			if (Vector3EX::AngleBetweenNormals(Grav, ContactBase) <= 0.01f) {
				PtrGrav->SetGravityVelocityZero();
				horizontal = true;
			}
			else {
				//�ŋߐړ_���璼�s���̒����i���ςŋ��߂�j
				Len = Vector3EX::Dot(PtrGrav->GetGravityVelocity(), ContactBase);
				Contact = ContactBase * Len;
				Slide = PtrGrav->GetGravityVelocity() - Contact;
				PtrGrav->SetGravityVelocity(Slide);
				horizontal = false;
			}
		}

		auto PtrRigid = GetGameObject()->GetComponent<Rigidbody>(false);
		if (PtrRigid) {
			switch (GetIsHitAction()) {
			case IsHitAction::AutoOnObjectRepel:
			{
				if (horizontal) {
					//�ŋߐړ_���璼�s���̒����i���ςŋ��߂�j
					Len = Vector3EX::Dot(PtrRigid->GetVelocity(), ContactBase);
					Contact = ContactBase * Len;
					Slide = PtrRigid->GetVelocity() - Contact;
					PtrRigid->SetVelocity(Slide);
				}
				else {
					auto Ref = Vector3EX::Reflect(PtrRigid->GetVelocity(), ContactBase);
					//�����W��
					Ref *= PtrRigid->GetReflection();
					PtrRigid->SetVelocity(Ref);
				}
			}
				break;
			case IsHitAction::Slide:
				//�ŋߐړ_���璼�s���̒����i���ςŋ��߂�j
				Len = Vector3EX::Dot(PtrRigid->GetVelocity(), ContactBase);
				Contact = ContactBase * Len;
				Slide = PtrRigid->GetVelocity() - Contact;
				PtrRigid->SetVelocity(Slide);
				break;
			default:
				break;
			}
		}
	}

	void CollisionSphere::AfterCollision(const Vector3 TotalVelocoty, const shared_ptr<CollisionRect>& DestColl, float SpanTime) {
		SPHERE sp = GetSphere();
		COLRECT DestRect = DestColl->GetColRect();
		Vector3 Ret;
		HitTest::SPHERE_COLRECT(sp, DestRect, Ret);
		//�ړ_�ւ̃x�N�g��
		Vector3 ContactBase = Ret - sp.m_Center;
		ContactBase.Normalize();
		//�ŋߐړ_���璼�s���̒����i���ςŋ��߂�j
		float Len = Vector3EX::Dot(TotalVelocoty, ContactBase);
		Vector3 Contact = ContactBase * Len;
		//��������͑��x����ړ_�ւ̃x�N�g���������Z
		Vector3 Slide = TotalVelocoty - Contact;
		auto PtrTransform = GetGameObject()->GetComponent<Transform>();
		auto Pos = sp.m_Center + Slide * SpanTime;
		PtrTransform->SetToBefore();
		PtrTransform->SetPosition(Pos);

		//Rigidbody��Gravity�͂��ꂼ��̑��x�̕��U��ݒ肷��
		auto PtrGrav = GetGameObject()->GetComponent<Gravity>(false);
		bool horizontal = true;
		if (PtrGrav) {
			auto Grav = PtrGrav->GetGravity();
			Grav.Normalize();
			if (Vector3EX::AngleBetweenNormals(Grav, ContactBase) <= 0.01f) {
				PtrGrav->SetGravityVelocityZero();
			}
			else {
				//�ŋߐړ_���璼�s���̒����i���ςŋ��߂�j
				Len = Vector3EX::Dot(PtrGrav->GetGravityVelocity(), ContactBase);
				Contact = ContactBase * Len;
				Slide = PtrGrav->GetGravityVelocity() - Contact;
				PtrGrav->SetGravityVelocity(Slide);
				horizontal = false;
			}
		}

		auto PtrRigid = GetGameObject()->GetComponent<Rigidbody>(false);
		if (PtrRigid) {
			switch (GetIsHitAction()) {
			case IsHitAction::AutoOnObjectRepel:
			{
				if (horizontal) {
					//�ŋߐړ_���璼�s���̒����i���ςŋ��߂�j
					Len = Vector3EX::Dot(PtrRigid->GetVelocity(), ContactBase);
					Contact = ContactBase * Len;
					Slide = PtrRigid->GetVelocity() - Contact;
					PtrRigid->SetVelocity(Slide);
				}
				else {
					auto Ref = Vector3EX::Reflect(PtrRigid->GetVelocity(), ContactBase);
					//�����W��
					Ref *= PtrRigid->GetReflection();
					PtrRigid->SetVelocity(Ref);
				}
			}
			break;
			case IsHitAction::Slide:
				//�ŋߐړ_���璼�s���̒����i���ςŋ��߂�j
				Len = Vector3EX::Dot(PtrRigid->GetVelocity(), ContactBase);
				Contact = ContactBase * Len;
				Slide = PtrRigid->GetVelocity() - Contact;
				PtrRigid->SetVelocity(Slide);
				break;
			default:
				break;
			}
		}

	}



	void CollisionSphere::CollisionEscape(const shared_ptr<CollisionSphere>& DestColl) {
		SPHERE SrcSphere = GetSphere();
		SPHERE DestSphere = DestColl->GetSphere();
		if (HitTest::SPHERE_SPHERE(SrcSphere, DestSphere)) {
			Vector3 Normal = SrcSphere.m_Center - DestSphere.m_Center;
			Normal.Normalize();
			float Span = SrcSphere.m_Radius + DestSphere.m_Radius;
			Normal *= Span;
			auto PtrTransform = GetGameObject()->GetComponent<Transform>();
			Vector3 Pos = DestSphere.m_Center + Normal;
			PtrTransform->ResetPosition(Pos);
		}
	}

	void CollisionSphere::CollisionEscape(const shared_ptr<CollisionObb>& DestColl) {
		SPHERE SrcSphere = GetSphere();
		OBB DestObb = DestColl->GetObb();
		Vector3 Ret;
		bool Ishit = HitTest::SPHERE_OBB(SrcSphere, DestObb, Ret);
		if (Ishit) {
			Vector3 Normal = SrcSphere.m_Center - Ret;
			Normal.Normalize();
			Normal *= (SrcSphere.m_Radius * 1.05f);
			Vector3 NewPos = Ret + Normal;
			auto PtrTransform = GetGameObject()->GetComponent<Transform>();
			PtrTransform->ResetPosition(NewPos);
		}
	}

	void CollisionSphere::CollisionEscape(const shared_ptr<CollisionRect>& DestColl) {
		SPHERE SrcSphere = GetSphere();
		COLRECT DestRect = DestColl->GetColRect();
		Vector3 Ret;
		bool Ishit = HitTest::HitTest::SPHERE_COLRECT(SrcSphere, DestRect, Ret);
		if (Ishit) {
			Vector3 Normal = SrcSphere.m_Center - Ret;
			Normal.Normalize();
			Normal *= (SrcSphere.m_Radius * 1.05f);
			Vector3 NewPos = Ret + Normal;
			auto PtrTransform = GetGameObject()->GetComponent<Transform>();
			PtrTransform->ResetPosition(NewPos);
		}
	}


	void CollisionSphere::OnDraw() {
		GenericDraw Draw;
		Draw.DrawWireFrame(GetGameObject(), App::GetApp()->GetResource<MeshResource>(L"DEFAULT_PC_SPHERE"));
	}


	//--------------------------------------------------------------------------------------
	//	struct CollisionObb::Impl;
	//	�p�r: �R���|�[�l���gImpl�N���X
	//--------------------------------------------------------------------------------------
	struct CollisionObb::Impl {
		float m_Size;					//�쐬���̃T�C�Y
		float m_ChkOnUnderLaySize;
		Impl() :
			m_Size(1.0f),
			m_ChkOnUnderLaySize(0.1f)
		{}
		~Impl() {}
	};

	//--------------------------------------------------------------------------------------
	//	class CollisionObb : public Collision ;
	//	�p�r: Obb�Փ˔���R���|�[�l���g
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	CollisionObb::CollisionObb(const shared_ptr<GameObject>& GameObjectPtr) :
		Collision(GameObjectPtr),
		pImpl(new Impl())
	{}
	CollisionObb::~CollisionObb() {}

	//������
	void CollisionObb::OnCreate() {
		SetDrawActive(false);
	}


	//�A�N�Z�T
	float CollisionObb::GetMakedSize() const {
		return pImpl->m_Size;
	}
	void CollisionObb::SetMakedSize(float f) {
		pImpl->m_Size = f;
	}

	OBB CollisionObb::GetObb() const {
		auto PtrT = GetGameObject()->GetComponent<Transform>();
		Matrix4X4 MatBase;
		MatBase.Scaling(pImpl->m_Size, pImpl->m_Size, pImpl->m_Size);
		MatBase *= PtrT->GetWorldMatrix();
		OBB Ret(Vector3(pImpl->m_Size, pImpl->m_Size, pImpl->m_Size), MatBase);
		return Ret;
	}
	OBB CollisionObb::GetBeforeObb() const {
		auto PtrT = GetGameObject()->GetComponent<Transform>();
		Matrix4X4 MatBase;
		MatBase.Scaling(pImpl->m_Size, pImpl->m_Size, pImpl->m_Size);
		MatBase *= PtrT->GetBeforeWorldMatrix();
		OBB Ret(Vector3(pImpl->m_Size, pImpl->m_Size, pImpl->m_Size), MatBase);
		return Ret;
	}

	void CollisionObb::CollisionTest(const shared_ptr<CollisionSphere>& DestColl) {
		auto PtrTransform = GetGameObject()->GetComponent<Transform>();
		auto PtrDestTransform = DestColl->GetGameObject()->GetComponent<Transform>();
		Vector3 SrcVelocity = PtrTransform->GetVelocity();
		Vector3 DestVelocity = PtrDestTransform->GetVelocity();
		//�O��̃^�[������̎���
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//�ړ��ȊO�ω��Ȃ�
		OBB SrcObb = GetObb();
		OBB SrcBeforeObb = GetBeforeObb();
		//����
		SPHERE DestSphere = DestColl->GetSphere();
		SPHERE DestBeforeSphere = DestColl->GetBeforeSphere();
		//SPHERE��OBB�̈������t�ɂȂ�
		Vector3 SpanVelocity = DestVelocity - SrcVelocity;
		float HitTime = 0;
		if (HitTest::CollisionTestSphereObb(DestBeforeSphere, SpanVelocity, SrcObb, 0, ElapsedTime, HitTime)) {
			if (HitTime <= 0) {
				HitTime = 0;
			}
			if (HitTime >= ElapsedTime) {
				HitTime = ElapsedTime;
			}
			auto AfterHitTime = ElapsedTime - HitTime;
			//����Fix�łȂ���ΏՓˏ��̓o�^
			if (!IsFixed()) {
				AddHitObject(DestColl->GetGameObject());
				BackToBefore(SrcVelocity, HitTime);
				AfterCollision(SrcVelocity, DestColl, AfterHitTime);
			}
			//�������肪Fix�łȂ���ΏՑ��葤�ɓˏ��̓o�^
			if (!DestColl->IsFixed()) {
				DestColl->AddHitObject(GetGameObject());
				DestColl->BackToBefore(DestVelocity, HitTime);
				DestColl->AfterCollision(DestVelocity, GetThis<CollisionObb>(), AfterHitTime);
			}
			//���肪Fix�Ȃ玩�ȑޔ������ł͏Փ˂��Ă���\��������̂Ŕ�������ăG�X�P�[�v����
			else {
				CollisionEscape(DestColl);
			}
		}
	}

	void CollisionObb::CollisionTest(const shared_ptr<CollisionObb>& DestColl) {
		auto PtrTransform = GetGameObject()->GetComponent<Transform>();
		auto PtrDestTransform = DestColl->GetGameObject()->GetComponent<Transform>();
		Vector3 SrcVelocity = PtrTransform->GetVelocity();
		Vector3 DestVelocity = PtrDestTransform->GetVelocity();
		//�O��̃^�[������̎���
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//�ړ��ȊO�ω��Ȃ�
		OBB SrcObb = GetObb();
		OBB SrcBeforObb = GetBeforeObb();
		//����
		OBB DestObb = DestColl->GetObb();
		OBB DestBeforeObb = DestColl->GetBeforeObb();
		Vector3 SpanVelocity = SrcVelocity - DestVelocity;
		float HitTime = 0;
		if (HitTest::CollisionTestObbObb(SrcBeforObb, SpanVelocity, DestObb, 0, ElapsedTime, HitTime)) {
			if (HitTime <= 0) {
				HitTime = 0;
			}
			if (HitTime >= ElapsedTime) {
				HitTime = ElapsedTime;
			}
			auto AfterHitTime = ElapsedTime - HitTime;
			//����Fix�łȂ���ΏՓˏ��̓o�^
			if (!IsFixed()) {
				AddHitObject(DestColl->GetGameObject());
				BackToBefore(SrcVelocity, HitTime);
				AfterCollision(SrcVelocity, DestColl, AfterHitTime);
			}
			//�������肪Fix�łȂ���ΏՑ��葤�ɓˏ��̓o�^
			if (!DestColl->IsFixed()) {
				DestColl->AddHitObject(GetGameObject());
				DestColl->BackToBefore(DestVelocity, HitTime);
				DestColl->AfterCollision(DestVelocity, GetThis<CollisionObb>(), AfterHitTime);
			}
			//���肪Fix�Ȃ玩�ȑޔ������ł͏Փ˂��Ă���\��������̂Ŕ�������ăG�X�P�[�v����
			else {
				CollisionEscape(DestColl);
			}
		}
	}

	void CollisionObb::CollisionTest(const shared_ptr<CollisionRect>& DestColl) {
		auto PtrTransform = GetGameObject()->GetComponent<Transform>();
		auto PtrDestTransform = DestColl->GetGameObject()->GetComponent<Transform>();
		Vector3 SrcVelocity = PtrTransform->GetVelocity();
		Vector3 DestVelocity = PtrDestTransform->GetVelocity();
		//�O��̃^�[������̎���
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//�ړ��ȊO�ω��Ȃ�
		OBB SrcObb = GetObb();
		OBB SrcBeforObb = GetBeforeObb();
		//����
		COLRECT DestRect = DestColl->GetColRect();
		COLRECT DestBeforeRect = DestColl->GetBeforeColRect();
		Vector3 SpanVelocity = SrcVelocity - DestVelocity;
		float HitTime = 0;
		if (HitTest::CollisionTestObbRect(SrcBeforObb, SpanVelocity, DestRect, 0, ElapsedTime, HitTime)) {
			if (HitTime <= 0) {
				HitTime = 0;
			}
			if (HitTime >= ElapsedTime) {
				HitTime = ElapsedTime;
			}
			auto AfterHitTime = ElapsedTime - HitTime;
			//����Fix�łȂ���ΏՓˏ��̓o�^
			if (!IsFixed()) {
				AddHitObject(DestColl->GetGameObject());
				BackToBefore(SrcVelocity, HitTime);
				AfterCollision(SrcVelocity, DestColl, AfterHitTime);
			}
			//����͕K��FIX�ł���B
			//���肪Fix�Ȃ玩�ȑޔ������ł͏Փ˂��Ă���\��������̂Ŕ�������ăG�X�P�[�v����
			CollisionEscape(DestColl);
		}

	}



	void CollisionObb::BackToBefore(const Vector3 TotalVelocoty, float SpanTime) {
		//���ׂĈړ��ȊO�ω��Ȃ��Ƃ���
		OBB SrcObb = GetObb();
		OBB SrcBeforObb = GetBeforeObb();
		auto PtrTransform = GetGameObject()->GetComponent<Transform>();
		Vector3 Pos = SrcBeforObb.m_Center + TotalVelocoty * SpanTime;
		PtrTransform->SetPosition(Pos);
	}

	void CollisionObb::AfterCollision(const Vector3 TotalVelocoty, const shared_ptr<CollisionSphere>& DestColl, float SpanTime) {
		OBB obb = GetObb();
		SPHERE sp = DestColl->GetSphere();
		Vector3 Ret;
		HitTest::SPHERE_OBB(sp, obb, Ret);
		//�ړ_�ւ̃x�N�g��
		Vector3 ContactBase = sp.m_Center - Ret;
		ContactBase.Normalize();
		//�ŋߐړ_���璼�s���̒����i���ςŋ��߂�j
		float Len = Vector3EX::Dot(TotalVelocoty, ContactBase);
		Vector3 Contact = ContactBase * Len;
		//��������͑��x����ړ_�ւ̃x�N�g���������Z
		Vector3 Slide = TotalVelocoty - Contact;
		auto PtrTransform = GetGameObject()->GetComponent<Transform>();
		auto Pos = obb.m_Center + Slide * SpanTime;
		PtrTransform->SetToBefore();
		PtrTransform->SetPosition(Pos);

		//Rigidbody��Gravity�͂��ꂼ��̑��x�̕��U��ݒ肷��
		auto PtrGrav = GetGameObject()->GetComponent<Gravity>(false);
		bool horizontal = false;
		if (PtrGrav) {
			auto Grav = PtrGrav->GetGravity();
			Grav.Normalize();
			if (Vector3EX::AngleBetweenNormals(Grav, ContactBase) <= 0.01f) {
				PtrGrav->SetGravityVelocityZero();
				horizontal = true;
			}
			else {
				//�ŋߐړ_���璼�s���̒����i���ςŋ��߂�j
				Len = Vector3EX::Dot(PtrGrav->GetGravityVelocity(), ContactBase);
				Contact = ContactBase * Len;
				Slide = PtrGrav->GetGravityVelocity() - Contact;
				PtrGrav->SetGravityVelocity(Slide);
				horizontal = false;
			}
		}

		auto PtrRigid = GetGameObject()->GetComponent<Rigidbody>(false);
		if (PtrRigid) {
			switch (GetIsHitAction()) {
			case IsHitAction::AutoOnObjectRepel:
			{
				if (horizontal) {
					//�ŋߐړ_���璼�s���̒����i���ςŋ��߂�j
					Len = Vector3EX::Dot(PtrRigid->GetVelocity(), ContactBase);
					Contact = ContactBase * Len;
					Slide = PtrRigid->GetVelocity() - Contact;
					PtrRigid->SetVelocity(Slide);
				}
				else {
					auto Ref = Vector3EX::Reflect(PtrRigid->GetVelocity(), ContactBase);
					//�����W��
					Ref *= PtrRigid->GetReflection();
					PtrRigid->SetVelocity(Ref);
				}
			}
			break;
			case IsHitAction::Slide:
				//�ŋߐړ_���璼�s���̒����i���ςŋ��߂�j
				Len = Vector3EX::Dot(PtrRigid->GetVelocity(), ContactBase);
				Contact = ContactBase * Len;
				Slide = PtrRigid->GetVelocity() - Contact;
				PtrRigid->SetVelocity(Slide);
				break;
			default:
				break;
			}
		}
	}

	void CollisionObb::AfterCollision(const Vector3 TotalVelocoty, const shared_ptr<CollisionObb>& DestColl, float SpanTime) {
		OBB obb = GetObb();
		OBB obb2 = DestColl->GetObb();
		Vector3 Ret;
		//Src��OBB��Dest�̍ŋߐړ_�𓾂�
		HitTest::ClosestPtPointOBB(obb.m_Center, obb2, Ret);
		//�ړ_�ւ̃x�N�g��
		Vector3 ContactBase = Ret - obb.m_Center;
		ContactBase.Normalize();
		//�ŋߐړ_���璼�s���̒����i���ςŋ��߂�j
		float Len = Vector3EX::Dot(TotalVelocoty, ContactBase);
		Vector3 Contact = ContactBase * Len;
		//��������͑��x����ړ_�ւ̃x�N�g���������Z
		Vector3 Slide = TotalVelocoty - Contact;
		auto PtrTransform = GetGameObject()->GetComponent<Transform>();
		auto Pos = obb.m_Center + Slide * SpanTime;
		PtrTransform->SetToBefore();
		PtrTransform->SetPosition(Pos);

		//Rigidbody��Gravity�͂��ꂼ��̑��x�̕��U��ݒ肷��
		auto PtrGrav = GetGameObject()->GetComponent<Gravity>(false);
		bool horizontal = false;
		if (PtrGrav) {
			auto Grav = PtrGrav->GetGravity();
			Grav.Normalize();
			if (Vector3EX::AngleBetweenNormals(Grav, ContactBase) <= 0.01f) {
				PtrGrav->SetGravityVelocityZero();
				horizontal = true;
			}
			else {
				//�ŋߐړ_���璼�s���̒����i���ςŋ��߂�j
				Len = Vector3EX::Dot(PtrGrav->GetGravityVelocity(), ContactBase);
				Contact = ContactBase * Len;
				Slide = PtrGrav->GetGravityVelocity() - Contact;
				PtrGrav->SetGravityVelocity(Slide);
				horizontal = false;
			}
		}

		auto PtrRigid = GetGameObject()->GetComponent<Rigidbody>(false);
		if (PtrRigid) {
			switch (GetIsHitAction()) {
			case IsHitAction::AutoOnObjectRepel:
			{
				if (horizontal) {
					//�ŋߐړ_���璼�s���̒����i���ςŋ��߂�j
					Len = Vector3EX::Dot(PtrRigid->GetVelocity(), ContactBase);
					Contact = ContactBase * Len;
					Slide = PtrRigid->GetVelocity() - Contact;
					PtrRigid->SetVelocity(Slide);
				}
				else {
					auto Ref = Vector3EX::Reflect(PtrRigid->GetVelocity(), ContactBase);
					//�����W��
					Ref *= PtrRigid->GetReflection();
					PtrRigid->SetVelocity(Ref);
				}
			}
			break;
			case IsHitAction::Slide:
				//�ŋߐړ_���璼�s���̒����i���ςŋ��߂�j
				Len = Vector3EX::Dot(PtrRigid->GetVelocity(), ContactBase);
				Contact = ContactBase * Len;
				Slide = PtrRigid->GetVelocity() - Contact;
				PtrRigid->SetVelocity(Slide);
				break;
			default:
				break;
			}
		}
	}


	void CollisionObb::AfterCollision(const Vector3 TotalVelocoty, const shared_ptr<CollisionRect>& DestColl, float SpanTime){
		OBB obb = GetObb();
		COLRECT rect = DestColl->GetColRect();
		//Rect�̃x�N�g��
		Vector3 ContactBase = DestColl->GetColRect().GetPLANE().m_Normal;
	//	Vector3 ContactBase = Vector3(0,1.0,0);
//		ContactBase *= -1.0f;
		ContactBase.Normalize();
		//�ŋߐړ_���璼�s���̒����i���ςŋ��߂�j
		float Len = Vector3EX::Dot(TotalVelocoty, ContactBase);
		Vector3 Contact = ContactBase * Len;
		//��������͑��x����ړ_�ւ̃x�N�g���������Z
		Vector3 Slide = TotalVelocoty - Contact;
		auto PtrTransform = GetGameObject()->GetComponent<Transform>();
		auto Pos = obb.m_Center + Slide * SpanTime;
		PtrTransform->SetToBefore();
		PtrTransform->SetPosition(Pos);

		//Rigidbody��Gravity�͂��ꂼ��̑��x�̕��U��ݒ肷��
		auto PtrGrav = GetGameObject()->GetComponent<Gravity>(false);
		bool horizontal = false;
		if (PtrGrav) {
			auto Grav = PtrGrav->GetGravity();
			Grav.Normalize();
			if (Vector3EX::AngleBetweenNormals(Grav, ContactBase) <= 0.01f) {
				PtrGrav->SetGravityVelocityZero();
				horizontal = true;
			}
			else {
				//�ŋߐړ_���璼�s���̒����i���ςŋ��߂�j
				Len = Vector3EX::Dot(PtrGrav->GetGravityVelocity(), ContactBase);
				Contact = ContactBase * Len;
				Slide = PtrGrav->GetGravityVelocity() - Contact;
				PtrGrav->SetGravityVelocity(Slide);
				horizontal = false;
			}
		}

		auto PtrRigid = GetGameObject()->GetComponent<Rigidbody>(false);
		if (PtrRigid) {
			switch (GetIsHitAction()) {
			case IsHitAction::AutoOnObjectRepel:
			{
				if (horizontal) {
					//�ŋߐړ_���璼�s���̒����i���ςŋ��߂�j
					Len = Vector3EX::Dot(PtrRigid->GetVelocity(), ContactBase);
					Contact = ContactBase * Len;
					Slide = PtrRigid->GetVelocity() - Contact;
					PtrRigid->SetVelocity(Slide);
				}
				else {
					auto Ref = Vector3EX::Reflect(PtrRigid->GetVelocity(), ContactBase);
					//�����W��
					Ref *= PtrRigid->GetReflection();
					PtrRigid->SetVelocity(Ref);
				}
			}
			break;
			case IsHitAction::Slide:
				//�ŋߐړ_���璼�s���̒����i���ςŋ��߂�j
				Len = Vector3EX::Dot(PtrRigid->GetVelocity(), ContactBase);
				Contact = ContactBase * Len;
				Slide = PtrRigid->GetVelocity() - Contact;
				PtrRigid->SetVelocity(Slide);
				break;
			default:
				break;
			}
		}

	}


	void CollisionObb::CollisionEscape(const shared_ptr<CollisionSphere>& DestColl) {
		OBB SrcObb = GetObb();
		SPHERE DestSphere = DestColl->GetSphere();
		Vector3 Ret;
		bool Ishit = HitTest::SPHERE_OBB(DestSphere, SrcObb, Ret);
		if (Ishit) {
			Vector3 NowSpan = Ret - DestSphere.m_Center;
			Vector3 NewSpan = NowSpan;
			NewSpan.Normalize();
			NewSpan *= (DestSphere.m_Radius * 1.05f);
			auto MoveSpan = NewSpan - NowSpan;
			auto PtrTransform = GetGameObject()->GetComponent<Transform>();
			auto Pos = PtrTransform->GetPosition();
			Pos += MoveSpan;
			PtrTransform->ResetPosition(Pos);
		}


	}

	void CollisionObb::CollisionEscape(const shared_ptr<CollisionObb>& DestColl) {
		OBB SrcObb = GetObb();
		OBB DestObb = DestColl->GetObb();
		bool Ishit = HitTest::OBB_OBB(SrcObb, DestObb);
		if (Ishit) {
			Vector3 Ret;
			//Src��OBB��Dest�̍ŋߐړ_�𓾂�
			HitTest::ClosestPtPointOBB(SrcObb.m_Center, DestObb, Ret);
			Vector3 Normal = SrcObb.m_Center - Ret;
			Normal.Normalize();
			//Normal�͑ޔ����
			Normal *= 0.01f;
			SrcObb.m_Center += Normal;
			UINT count = 0;
			while (HitTest::OBB_OBB(SrcObb, DestObb)) {
				SrcObb.m_Center += Normal;
				count++;
				if (count >= 50) {
					break;
				}
			}
			auto PtrTransform = GetGameObject()->GetComponent<Transform>();
			PtrTransform->ResetPosition(SrcObb.m_Center);
		}
	}

	void CollisionObb::CollisionEscape(const shared_ptr<CollisionRect>& DestColl) {
		OBB SrcObb = GetObb();
		COLRECT DestRect = DestColl->GetColRect();
		bool Ishit = HitTest::OBB_COLRECT(SrcObb, DestRect);
		if (Ishit) {
			Vector3 Ret;
			//Src��OBB��Dest�̍ŋߐړ_�𓾂�
			Vector3 Normal = DestColl->GetColRect().GetPLANE().m_Normal;
			Normal.Normalize();
			//Normal�͑ޔ����
			Normal *= -0.01f;
			SrcObb.m_Center += Normal;
			UINT count = 0;
			while (HitTest::OBB_COLRECT(SrcObb, DestRect)) {
				SrcObb.m_Center += Normal;
				count++;
				if (count >= 50) {
					break;
				}
			}
			auto PtrTransform = GetGameObject()->GetComponent<Transform>();
			PtrTransform->ResetPosition(SrcObb.m_Center);
		}
	}


	void CollisionObb::OnDraw() {
		GenericDraw Draw;
		Draw.DrawWireFrame(GetGameObject(), App::GetApp()->GetResource<MeshResource>(L"DEFAULT_PC_CUBE"));

	}

	//--------------------------------------------------------------------------------------
	//	struct CollisionRect::Impl;
	//	�p�r: �R���|�[�l���gImpl�N���X
	//--------------------------------------------------------------------------------------
	struct CollisionRect::Impl {
		float m_Size;					//�쐬���̃T�C�Y
		Impl() :
			m_Size(1.0f)
		{}
		~Impl() {}
	};

	//--------------------------------------------------------------------------------------
	//	class CollisionRect : public Collision ;
	//	�p�r: Rect(��`)�Փ˔���R���|�[�l���g
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	CollisionRect::CollisionRect(const shared_ptr<GameObject>& GameObjectPtr) :
		Collision(GameObjectPtr),
		pImpl(new Impl())
	{}
	CollisionRect::~CollisionRect() {}

	//������
	void CollisionRect::OnCreate() {
		SetFixed(true),
		SetDrawActive(false);
	}

	//�A�N�Z�T
	void CollisionRect::SetFixed(bool b) {
		if (!b) {
			throw BaseException(
				L"CollisionRect��Fixed�ȊO�͑I���ł��܂���",
				L"if (!b)",
				L"CollisionRect::SetFixed()"
			);
		}
	}



	float CollisionRect::GetMakedSize() const {
		return pImpl->m_Size;
	}
	void CollisionRect::SetMakedSize(float f) {
		pImpl->m_Size = f;
	}

	COLRECT CollisionRect::GetColRect() const {
		auto TrasnsPtr = GetGameObject()->GetComponent<Transform>();
		COLRECT rect(GetMakedSize(), GetMakedSize(), TrasnsPtr->GetWorldMatrix());
		return rect;
	}

	COLRECT CollisionRect::GetBeforeColRect() const {
		auto TrasnsPtr = GetGameObject()->GetComponent<Transform>();
		COLRECT rect(GetMakedSize(), GetMakedSize(), TrasnsPtr->GetBeforeWorldMatrix());
		return rect;
	}


	void CollisionRect::OnDraw() {
		GenericDraw Draw;
		Draw.DrawWireFrame(GetGameObject(), App::GetApp()->GetResource<MeshResource>(L"DEFAULT_PC_SQUARE"));

	}








}
//end basecross

