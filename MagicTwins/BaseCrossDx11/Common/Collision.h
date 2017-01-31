/*!
@file Collision.h
@brief �Փ˔���R���|�[�l���g
*/
#pragma once
#include "stdafx.h"

namespace basecross {

	class CollisionSphere;
	class CollisionCapsule;
	class CollisionObb;
	class CollisionTriangles;
	class CollisionRect;

	//--------------------------------------------------------------------------------------
	///	 �Փ˂������̓����`
	//--------------------------------------------------------------------------------------
	enum class IsHitAction {
		AutoOnObjectRepel,	///<����
		Slide,	//����
		AutoOnParent,	//�e�q�֌W����������
		AutoOnParentSlide,	//�e�q�֌W�������X���C�h
	};

	//--------------------------------------------------------------------------------------
	///	 �X�P�[������������ꍇ�̌v�Z�Ɏg�p����X�P�[��
	//--------------------------------------------------------------------------------------
	enum class CalcScaling {
		XScale,
		YScale,
		ZScale,
	};

	//--------------------------------------------------------------------------------------
	///	 �Փ˔���R���|�[�l���g�̐e�N���X
	//--------------------------------------------------------------------------------------
	class Collision : public Component {
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�Փ˔z������؂��ăe���|�����z��ɃZ�b�g����
		@param[in]	Tgt	���؂���I�u�W�F�N�g
		@param[out]	SetVec	�Z�b�g����e���|�����z��
		@param[in]	ScanVec	�X�L��������z��
		@param[in]	IsFind	����������Z�b�g���邩�ǂ����ifalse�̏ꍇ�́u������Ȃ�������v�Z�b�g����j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void FindIfCollisionVector(
			shared_ptr<GameObject> Tgt,
			vector<shared_ptr<GameObject>>& SetVec,
			const vector<shared_ptr<GameObject>>& ScanVec,
			bool IsFind
		);
	protected:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v���e�N�g�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit Collision(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v���e�N�g�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Collision();
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�Œ�Փ˃I�u�W�F�N�g���ǂ����𓾂�B
		@return	�Œ�Փ˃I�u�W�F�N�g�Ȃ�true
		*/
		//--------------------------------------------------------------------------------------
		bool GetFixed() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�Œ�Փ˃I�u�W�F�N�g���ǂ����𓾂�B
		@return	�Œ�Փ˃I�u�W�F�N�g�Ȃ�true
		*/
		//--------------------------------------------------------------------------------------
		bool IsFixed() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�Œ�Փ˃I�u�W�F�N�g���ǂ�����ݒ肷��
		@param[in]	b	�Œ�Փ˃I�u�W�F�N�g�Ȃ�true
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void SetFixed(bool b);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���W�����R�[���B�_�u���f�X�p�b�`�֐�
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionCall(const shared_ptr<Collision>& Src) = 0;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�V����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {
			//�Փ˔���Ǘ��҂ɔC����̂ŉ������Ȃ�
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief �q�b�g�I�u�W�F�N�g�̒ǉ�
		@param[in]	DestColl	����̃Q�[���I�u�W�F�N�g
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void AddHitObject(const shared_ptr<GameObject>& DestObject);
		//--------------------------------------------------------------------------------------
		/*!
		@brief 1�O�̃q�b�g�I�u�W�F�N�g�ɃR�s�[
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetToBeforeHitObject();
		//--------------------------------------------------------------------------------------
		/*!
		@brief �q�b�g�I�u�W�F�N�g�̃N���A
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void ClearHitObject();
		//--------------------------------------------------------------------------------------
		/*!
		@brief �q�b�g�I�u�W�F�N�g�z��̎擾
		@return	�q�b�g�I�u�W�F�N�g�z��
		*/
		//--------------------------------------------------------------------------------------
		vector<shared_ptr<GameObject>>& GetHitObjectVec();
		//--------------------------------------------------------------------------------------
		/*!
		@brief �q�b�g�I�u�W�F�N�g�ɓ����Ă邩�ǂ���
		@return	�q�b�g���Ă����true
		*/
		//--------------------------------------------------------------------------------------
		bool IsHitObject(const shared_ptr<GameObject>& Obj) const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 1�O�̃q�b�g�I�u�W�F�N�g�z��̎擾
		@return	1�O�̃q�b�g�I�u�W�F�N�g�z��
		*/
		//--------------------------------------------------------------------------------------
		vector<shared_ptr<GameObject>>& GetBeforeHitObjectVec();
		//--------------------------------------------------------------------------------------
		/*!
		@brief �V�����q�b�g�I�u�W�F�N�g�z��̎擾
		@return	�V�����q�b�g�I�u�W�F�N�g�z��
		*/
		//--------------------------------------------------------------------------------------
		vector<shared_ptr<GameObject>>& GetNewHitObjectVec();
		//--------------------------------------------------------------------------------------
		/*!
		@brief �Փ˂�������q�b�g�I�u�W�F�N�g�z��̎擾
		@return	�Փ˂�������q�b�g�I�u�W�F�N�g�z��
		*/
		//--------------------------------------------------------------------------------------
		vector<shared_ptr<GameObject>>& GetExcuteHitObjectVec();
		//--------------------------------------------------------------------------------------
		/*!
		@brief �Փ˂��I�������q�b�g�I�u�W�F�N�g�z��̎擾
		@return	�Փ˂��I�������q�b�g�I�u�W�F�N�g�z��
		*/
		//--------------------------------------------------------------------------------------
		vector<shared_ptr<GameObject>>& GetExitHitObjectVec();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�Փ˂������̃A�N�V�����𓾂�B
		@return	�Փ˂������̃A�N�V����
		*/
		//--------------------------------------------------------------------------------------
		IsHitAction GetIsHitAction() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�Փ˂������̃A�N�V������ݒ肷��
		@param[in]	HitAction	�A�N�V����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetIsHitAction(IsHitAction HitAction);
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionSphere�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionSphere>& DestColl) {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionCapsule�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionCapsule>& DestColl) {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionObb�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionObb>& DestColl) {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionTriangles�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionTriangles>& DestColl) {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionRect�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionRect>& DestColl) {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief �P�O�̃^�[������̎w�莞�Ԃ̈ʒu�ɖ߂�
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	SpanTime	����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void BackToBefore(const Vector3 TotalVelocoty, float SpanTime) {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief /Gravity��Rigidbody�̌㏈���iCollision���ʁj
		@param[in]	DestColl	�����Collision
		@param[in]	ContactBase	�X���C�h�̊�ƂȂ�@��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void AfterCollisionSub(const shared_ptr<Collision>& DestColl, const Vector3& ContactBase);
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionSphere�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�Փˎ���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3& TotalVelocoty, const shared_ptr<CollisionSphere>& DestColl, float SpanTime) {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionCapsule�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�Փˎ���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3& TotalVelocoty, const shared_ptr<CollisionCapsule>& DestColl, float SpanTime) {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionObb�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�Փˎ���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3& TotalVelocoty, const shared_ptr<CollisionObb>& DestColl, float SpanTime) {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionTriangles�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�Փˎ���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3& TotalVelocoty, const shared_ptr<CollisionTriangles>& DestColl, float SpanTime) {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionRect�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�Փˎ���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3& TotalVelocoty, const shared_ptr<CollisionRect>& DestColl, float SpanTime) {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionSphere����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionSphere>& DestColl) {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionCapsule����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionCapsule>& DestColl) {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionObb����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionObb>& DestColl) {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionTriangles����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionTriangles>& DestColl) {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionRect����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionRect>& DestColl) {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief 1�O�ƌ��݂̘A��������SPHERE�𓾂�
		@return	�A��������SPHERE
		*/
		//--------------------------------------------------------------------------------------
		virtual SPHERE GetEnclosingSphere()const = 0;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �����Ƒ���̘A������SPHERE�̏Փ˔���i�O�����p�j
		@tparam	T	����̃R���W�����̌^
		@param[in]	DestColl	����̃R���W����
		@return	�q�b�g���Ă��true
		*/
		//--------------------------------------------------------------------------------------
		template <typename T>
		bool CillisionWrappedSphere(const shared_ptr<T>& DestColl) {
			SPHERE Src = GetEnclosingSphere();
			SPHERE Dest = DestColl->GetEnclosingSphere();
			return HitTest::SPHERE_SPHERE(Src, Dest);
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���݂̕�ݍ���AABB��Ԃ��B���z�֐�
		@return	��ݍ���AABB(1�O�̃^�[�����̓��e�͌��Ȃ�)
		*/
		//--------------------------------------------------------------------------------------
		virtual AABB GetWrappingAABB()const = 0;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �����Ǝ����̏Փ˃`�F�b�N�i���肷��̂݁j
		@param[in]	Pos1	�����J�n
		@param[in]	Pos2	�����I��
		@return	�q�b�g���Ă��true
		*/
		//--------------------------------------------------------------------------------------
		virtual bool HitTestWithSegment(const Vector3& Pos1, const Vector3& Pos2) { return false; }
		//--------------------------------------------------------------------------------------
		/*!
		@brief �`�揈���B�f�t�H���g�͉����s��Ȃ�
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override {}
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};

	//--------------------------------------------------------------------------------------
	//	class CollisionSphere : public Collision ;
	//	�p�r: ���Փ˔���R���|�[�l���g
	//--------------------------------------------------------------------------------------
	class CollisionSphere : public Collision {
	protected:
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit CollisionSphere(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~CollisionSphere();
		//--------------------------------------------------------------------------------------
		/*!
		@brief ����������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�쐬���̒��a�𓾂�
		@return	�쐬���̒��a
		*/
		//--------------------------------------------------------------------------------------
		float GetMakedDiameter() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�쐬���̒��a��ݒ肷��
		@param[in]	f	�쐬���̒��a
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetMakedDiameter(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�쐬���̔��a�𓾂�B�����ł͒��a�̂ݎ����Ă���̂ŁA���a��0.5��Ԃ�
		@return	�쐬���̔��a
		*/
		//--------------------------------------------------------------------------------------
		float GetMakedRadius() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�쐬���̒��a�𔼌a�����Ƃɐݒ肷��B�����ł͒��a�̂ݎ����Ă���̂ŁA2�{�������̂𒼌a�ɐݒ肷��
		@param[in]	f	�쐬���̔��a
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetMakedRadius(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v�Z���AXYZ�ǂ̃X�P�[�����g�p���邩�𓾂�(x: 0,y: 1,z: 2)�B�f�t�H���gx
		@return	�v�Z���AXYZ�ǂ̃X�P�[�����g�p���邩
		*/
		//--------------------------------------------------------------------------------------
		CalcScaling GetCalcScaling() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v�Z���AXYZ�ǂ̃X�P�[�����g�p���邩��ݒ肷��(x: 0,y: 1,z: 2)�B�f�t�H���gx
		@param[in]	s	�v�Z���AXYZ�ǂ̃X�P�[�����g�p���邩
		@return	
		*/
		//--------------------------------------------------------------------------------------
		void SetCalcScaling(CalcScaling s);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���݂�SPHER���E�{�����[���𓾂�
		@return	���݂�SPHER���E�{�����[��
		*/
		//--------------------------------------------------------------------------------------
		SPHERE GetSphere() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	1�^�[���O��SPHER���E�{�����[���𓾂�
		@return	1�^�[���O��SPHER���E�{�����[��
		*/
		//--------------------------------------------------------------------------------------
		SPHERE GetBeforeSphere() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���W�����R�[���B�_�u���f�X�p�b�`�֐�
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionCall(const shared_ptr<Collision>& Src)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionSphere�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionSphere>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionCapsule�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionCapsule>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionObb�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionObb>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionTriangles�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionTriangles>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionRect�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionRect>& DestColl)override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief �P�O�̃^�[������̎w�莞�Ԃ̈ʒu�ɖ߂�
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	SpanTime	����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void BackToBefore(const Vector3 TotalVelocoty, float SpanTime)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionSphere�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�������鎞��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3& TotalVelocoty, const shared_ptr<CollisionSphere>& DestColl, float SpanTime) override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionCapsule�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�������鎞��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3& TotalVelocoty, const shared_ptr<CollisionCapsule>& DestColl, float SpanTime) override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionObb�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�������鎞��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3& TotalVelocoty, const shared_ptr<CollisionObb>& DestColl, float SpanTime)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionTriangles�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�Փˎ���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3& TotalVelocoty, const shared_ptr<CollisionTriangles>& DestColl, float SpanTime)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionRect�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�Փˎ���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3& TotalVelocoty, const shared_ptr<CollisionRect>& DestColl, float SpanTime)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionSphere����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionSphere>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionCapsule����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionCapsule>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionObb����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionObb>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionTriangles����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionTriangles>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionRect����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionRect>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 1�O�ƌ��݂̘A��������SPHERE�𓾂�
		@return	�A��������SPHERE
		*/
		//--------------------------------------------------------------------------------------
		virtual SPHERE GetEnclosingSphere()const override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �����Ǝ����̏Փ˃`�F�b�N�i���肷��̂݁j
		@param[in]	Pos1	�����J�n
		@param[in]	Pos2	�����I��
		@return	�q�b�g���Ă��true
		*/
		//--------------------------------------------------------------------------------------
		virtual bool HitTestWithSegment(const Vector3& Pos1, const Vector3& Pos2)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���݂̕�ݍ���AABB��Ԃ��B���z�֐�
		@return	��ݍ���AABB(1�O�̃^�[�����̓��e�͌��Ȃ�)
		*/
		//--------------------------------------------------------------------------------------
		virtual AABB GetWrappingAABB()const override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �`�揈���BDrawActive��true���ɌĂ΂��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};

	//--------------------------------------------------------------------------------------
	//	class CollisionCapsule : public Collision ;
	//	�p�r: �J�v�Z���Փ˔���R���|�[�l���g
	//--------------------------------------------------------------------------------------
	class CollisionCapsule : public Collision {
	protected:
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit CollisionCapsule(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~CollisionCapsule();
		//--------------------------------------------------------------------------------------
		/*!
		@brief ����������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�쐬���̒��a�𓾂�
		@return	�쐬���̒��a
		*/
		//--------------------------------------------------------------------------------------
		float GetMakedDiameter() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�쐬���̒��a��ݒ肷��
		@param[in]	f	�쐬���̒��a
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetMakedDiameter(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�쐬���̔��a�𓾂�B�����ł͒��a�̂ݎ����Ă���̂ŁA���a��0.5��Ԃ�
		@return	�쐬���̔��a
		*/
		//--------------------------------------------------------------------------------------
		float GetMakedRadius() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�쐬���̒��a�𔼌a�����Ƃɐݒ肷��B�����ł͒��a�̂ݎ����Ă���̂ŁA2�{�������̂𒼌a�ɐݒ肷��
		@param[in]	f	�쐬���̔��a
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetMakedRadius(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�쐬���̍����𓾂�
		@return	�쐬���̍���
		*/
		//--------------------------------------------------------------------------------------
		float GetMakedHeight() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�쐬���̍����𓾂�
		@param[in]	f	�쐬���̍���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetMakedHeight(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���݂�CAPSULE���E�{�����[���𓾂�
		@return	���݂�CAPSULE���E�{�����[��
		*/
		//--------------------------------------------------------------------------------------
		CAPSULE GetCapsule() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	1�^�[���O��CAPSULE���E�{�����[���𓾂�
		@return	1�^�[���O��CAPSULE���E�{�����[��
		*/
		//--------------------------------------------------------------------------------------
		CAPSULE GetBeforeCapsule() const;

		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���W�����R�[���B�_�u���f�X�p�b�`�֐�
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionCall(const shared_ptr<Collision>& Src)override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionSphere�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionSphere>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionCapsule�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionCapsule>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionObb�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionObb>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionTriangles�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionTriangles>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionRect�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionRect>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �P�O�̃^�[������̎w�莞�Ԃ̈ʒu�ɖ߂�
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	SpanTime	����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void BackToBefore(const Vector3 TotalVelocoty, float SpanTime)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionSphere�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�������鎞��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3& TotalVelocoty, const shared_ptr<CollisionSphere>& DestColl, float SpanTime) override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionCapsule�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�������鎞��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3& TotalVelocoty, const shared_ptr<CollisionCapsule>& DestColl, float SpanTime) override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionObb�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�������鎞��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3& TotalVelocoty, const shared_ptr<CollisionObb>& DestColl, float SpanTime)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionTriangles�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�Փˎ���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3& TotalVelocoty, const shared_ptr<CollisionTriangles>& DestColl, float SpanTime)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionRect�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�Փˎ���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3& TotalVelocoty, const shared_ptr<CollisionRect>& DestColl, float SpanTime)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionSphere����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionSphere>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionCapsule����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionCapsule>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionObb����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionObb>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionTriangles����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionTriangles>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionRect����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionRect>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 1�O�ƌ��݂̘A��������SPHERE�𓾂�
		@return	�A��������SPHERE
		*/
		//--------------------------------------------------------------------------------------
		virtual SPHERE GetEnclosingSphere()const override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �����Ǝ����̏Փ˃`�F�b�N�i���肷��̂݁j
		@param[in]	Pos1	�����J�n
		@param[in]	Pos2	�����I��
		@return	�q�b�g���Ă��true
		*/
		//--------------------------------------------------------------------------------------
		virtual bool HitTestWithSegment(const Vector3& Pos1, const Vector3& Pos2)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���݂̕�ݍ���AABB��Ԃ��B���z�֐�
		@return	��ݍ���AABB(1�O�̃^�[�����̓��e�͌��Ȃ�)
		*/
		//--------------------------------------------------------------------------------------
		virtual AABB GetWrappingAABB()const override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �`�揈���BDrawActive��true���ɌĂ΂��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};





	//--------------------------------------------------------------------------------------
	//	class CollisionObb : public Collision ;
	//	�p�r: Obb�Փ˔���R���|�[�l���g
	//--------------------------------------------------------------------------------------
	class CollisionObb : public Collision {
	protected:
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit CollisionObb(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~CollisionObb();
		//--------------------------------------------------------------------------------------
		/*!
		@brief ����������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�쐬����1�ӂ̒����𓾂�
		@return	�쐬����1�ӂ̒���
		*/
		//--------------------------------------------------------------------------------------
		float GetMakedSize() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�쐬����1�ӂ̒�����ݒ肷��
		@param[in]	f	�쐬����1�ӂ̒���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetMakedSize(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���݂�OBB���E�{�����[���𓾂�
		@return	���݂�OBB���E�{�����[��
		*/
		//--------------------------------------------------------------------------------------
		OBB GetObb() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	1�^�[���O��OBB���E�{�����[���𓾂�
		@return	1�^�[���O��OBB���E�{�����[��
		*/
		//--------------------------------------------------------------------------------------
		OBB GetBeforeObb() const;

		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���W�����R�[���B�_�u���f�X�p�b�`�֐�
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionCall(const shared_ptr<Collision>& Src)override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionSphere�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionSphere>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionCapsule�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionCapsule>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionObb�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionObb>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionTriangles�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionTriangles>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionRect�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionRect>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �P�O�̃^�[������̎w�莞�Ԃ̈ʒu�ɖ߂�
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	SpanTime	����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void BackToBefore(const Vector3 TotalVelocoty, float SpanTime)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionSphere�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�������鎞��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3& TotalVelocoty, const shared_ptr<CollisionSphere>& DestColl, float SpanTime)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionCapsule�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�������鎞��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3& TotalVelocoty, const shared_ptr<CollisionCapsule>& DestColl, float SpanTime) override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionObb�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�������鎞��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3& TotalVelocoty, const shared_ptr<CollisionObb>& DestColl, float SpanTime)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionTriangles�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�Փˎ���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3& TotalVelocoty, const shared_ptr<CollisionTriangles>& DestColl, float SpanTime)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionRect�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�Փˎ���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3& TotalVelocoty, const shared_ptr<CollisionRect>& DestColl, float SpanTime)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionSphere����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionSphere>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionCapsule����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionCapsule>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionObb����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionObb>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionTriangles����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionTriangles>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionRect����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionRect>& DestColl)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 1�O�ƌ��݂̘A��������SPHERE�𓾂�
		@return	�A��������SPHERE
		*/
		//--------------------------------------------------------------------------------------
		virtual SPHERE GetEnclosingSphere()const override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �����Ǝ����̏Փ˃`�F�b�N�i���肷��̂݁j
		@param[in]	Pos1	�����J�n
		@param[in]	Pos2	�����I��
		@return	�q�b�g���Ă��true
		*/
		//--------------------------------------------------------------------------------------
		virtual bool HitTestWithSegment(const Vector3& Pos1, const Vector3& Pos2)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���݂̕�ݍ���AABB��Ԃ��B���z�֐�
		@return	��ݍ���AABB(1�O�̃^�[�����̓��e�͌��Ȃ�)
		*/
		//--------------------------------------------------------------------------------------
		virtual AABB GetWrappingAABB()const override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �`�揈���BDrawActive��true���ɌĂ΂��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;

	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};


	//--------------------------------------------------------------------------------------
	//	class CollisionTriangles : public Collision ;
	//	�p�r: �O�p�`�̔z��Փ˔���R���|�[�l���g
	//--------------------------------------------------------------------------------------
	class CollisionTriangles : public Collision {
	protected:
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit CollisionTriangles(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~CollisionTriangles();
		//--------------------------------------------------------------------------------------
		/*!
		@brief ����������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�Œ�Փ˃I�u�W�F�N�g���ǂ�����ݒ肷��
		@param[in]	b	�Œ�Փ˃I�u�W�F�N�g�Ȃ�true
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void SetFixed(bool b)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�쐬����1�̎O�p�`�̔z��𓾂�
		@return	�쐬����1�̎O�p�`�̔z��
		*/
		//--------------------------------------------------------------------------------------
		const vector<TRIANGLE>& GetMakedTriangles() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�쐬���̎O�p�`�̔z���ݒ肷��
		@param[in]	trivec	�쐬���̎O�p�`�̔z��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetMakedTriangles(const vector<TRIANGLE>& trivec);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���C�A�t���[�����b�V����ݒ肷��
		@param[in]	Key	���b�V����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetWireFrameMesh(const wstring& Key);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���݂̎O�p�`�̔z��𓾂�
		@param[out]	trivec	�ݒ肳���O�p�`�̔z��i�����ŃN���A�����j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void GetTriangles(vector<TRIANGLE>& trivec) const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	1�O�̎O�p�`�̔z��𓾂�
		@param[out]	trivec	�ݒ肳���O�p�`�̔z��i�����ŃN���A�����j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void GetBeforeTriangles(vector<TRIANGLE>& trivec) const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���݂̕�ݍ���AABB��Ԃ��B���z�֐�
		@return	��ݍ���AABB(1�O�̃^�[�����̓��e�͌��Ȃ�)
		*/
		//--------------------------------------------------------------------------------------
		virtual AABB GetWrappingAABB()const override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�O�p�`�̔z����ݍ���AABB��Ԃ�
		@return	�O�p�`�̔z����ݍ���AABB(1�O�̃^�[�����̓��e�����f�����)
		*/
		//--------------------------------------------------------------------------------------
		AABB GetWrappedAABB()const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���W�����R�[���B�_�u���f�X�p�b�`�֐�
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionCall(const shared_ptr<Collision>& Src)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 1�O�ƌ��݂̘A��������SPHERE�𓾂�
		@return	�A��������SPHERE
		*/
		//--------------------------------------------------------------------------------------
		virtual SPHERE GetEnclosingSphere()const override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �����Ǝ����̏Փ˃`�F�b�N�i���肷��̂݁j
		@param[in]	Pos1	�����J�n
		@param[in]	Pos2	�����I��
		@return	�q�b�g���Ă��true
		*/
		//--------------------------------------------------------------------------------------
		virtual bool HitTestWithSegment(const Vector3& Pos1, const Vector3& Pos2)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �`�揈���BDrawActive��true���ɌĂ΂��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};



	//--------------------------------------------------------------------------------------
	//	class CollisionRect : public Collision ;
	//	�p�r: Rect(��`)�Փ˔���R���|�[�l���g
	//--------------------------------------------------------------------------------------
	class CollisionRect : public Collision {
	protected:
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit CollisionRect(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~CollisionRect();
		//--------------------------------------------------------------------------------------
		/*!
		@brief ����������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�Œ�Փ˃I�u�W�F�N�g���ǂ�����ݒ肷��
		@param[in]	b	�Œ�Փ˃I�u�W�F�N�g�Ȃ�true
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void SetFixed(bool b)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�쐬����1�ӂ̒����𓾂�
		@return	�쐬����1�ӂ̒���
		*/
		//--------------------------------------------------------------------------------------
		float GetMakedSize() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�쐬����1�ӂ̒�����ݒ肷��
		@param[in]	f	�쐬����1�ӂ̒���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetMakedSize(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���݂�COLRECT���E�{�����[���𓾂�
		@return	���݂�COLRECT���E�{�����[��
		*/
		//--------------------------------------------------------------------------------------
		COLRECT GetColRect() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	1�^�[���O��COLRECT���E�{�����[���𓾂�
		@return	1�^�[���O��COLRECT���E�{�����[��
		*/
		//--------------------------------------------------------------------------------------
		COLRECT GetBeforeColRect() const;

		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���W�����R�[���B�_�u���f�X�p�b�`�֐�
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionCall(const shared_ptr<Collision>& Src)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �����Ǝ����̏Փ˃`�F�b�N�i���肷��̂݁j
		@param[in]	Pos1	�����J�n
		@param[in]	Pos2	�����I��
		@return	�q�b�g���Ă��true
		*/
		//--------------------------------------------------------------------------------------
		virtual bool HitTestWithSegment(const Vector3& Pos1, const Vector3& Pos2)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 1�O�ƌ��݂̘A��������SPHERE�𓾂�
		@return	�A��������SPHERE
		*/
		//--------------------------------------------------------------------------------------
		virtual SPHERE GetEnclosingSphere()const override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���݂̕�ݍ���AABB��Ԃ��B���z�֐�
		@return	��ݍ���AABB(1�O�̃^�[�����̓��e�͌��Ȃ�)
		*/
		//--------------------------------------------------------------------------------------
		virtual AABB GetWrappingAABB()const override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �`�揈���BDrawActive��true���ɌĂ΂��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;

	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};




}
//end basecross
