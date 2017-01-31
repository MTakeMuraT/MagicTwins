/*!
@file Collision.h
@brief �Փ˔���R���|�[�l���g
@copyright Copyright (c) 2016 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/
#pragma once
#include "stdafx.h"

namespace basecross {

	class CollisionSphere;
	class CollisionObb;
	class CollisionRect;

	//--------------------------------------------------------------------------------------
	///	 �Փ˂������̓����`
	//--------------------------------------------------------------------------------------
	enum class IsHitAction {
		AutoOnObjectRepel,	///<����
		Slide,	//����
	};

	//--------------------------------------------------------------------------------------
	///	 �Փ˔���R���|�[�l���g�̐e�N���X
	//--------------------------------------------------------------------------------------
	class Collision : public Component {
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
		@brief �X�V����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;

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
		@brief �Փ˃e�X�g�e
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void CollisionTestBase(const shared_ptr<Collision>& DestColl);
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionSphere�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionSphere>& DestColl) = 0;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionObb�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionObb>& DestColl) = 0;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionRect�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionRect>& DestColl) = 0;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �P�O�̃^�[������̎w�莞�Ԃ̈ʒu�ɖ߂�
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	SpanTime	����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void BackToBefore(const Vector3 TotalVelocoty, float SpanTime) = 0;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionSphere�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�Փˎ���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3 TotalVelocoty, const shared_ptr<CollisionSphere>& DestColl, float SpanTime) = 0;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionObb�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�Փˎ���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3 TotalVelocoty, const shared_ptr<CollisionObb>& DestColl, float SpanTime) = 0;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionRect�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�Փˎ���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3 TotalVelocoty, const shared_ptr<CollisionRect>& DestColl, float SpanTime) = 0;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionSphere����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionSphere>& DestColl) = 0;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionObb����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionObb>& DestColl) = 0;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionRect����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionRect>& DestColl) = 0;
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
		@brief CollisionSphere�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionSphere>& DestColl)override;
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
		virtual void AfterCollision(const Vector3 TotalVelocoty, const shared_ptr<CollisionSphere>& DestColl, float SpanTime) override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionObb�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�������鎞��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3 TotalVelocoty, const shared_ptr<CollisionObb>& DestColl, float SpanTime)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionRect�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�Փˎ���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3 TotalVelocoty, const shared_ptr<CollisionRect>& DestColl, float SpanTime)override;
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
		@brief CollisionObb����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionObb>& DestColl)override;
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
		@brief CollisionSphere�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionSphere>& DestColl)override;
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
		virtual void AfterCollision(const Vector3 TotalVelocoty, const shared_ptr<CollisionSphere>& DestColl, float SpanTime)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionObb�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�������鎞��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3 TotalVelocoty, const shared_ptr<CollisionObb>& DestColl, float SpanTime)override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionRect�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�Փˎ���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3 TotalVelocoty, const shared_ptr<CollisionRect>& DestColl, float SpanTime)override;
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
		@brief CollisionObb����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionObb>& DestColl)override;
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
		@brief CollisionSphere�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionSphere>& DestColl) override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionObb�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionObb>& DestColl)override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionRect�Ƃ̏Փ˃e�X�g
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionTest(const shared_ptr<CollisionRect>& DestColl)override{}
		//--------------------------------------------------------------------------------------
		/*!
		@brief �P�O�̃^�[������̎w�莞�Ԃ̈ʒu�ɖ߂�
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	SpanTime	����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void BackToBefore(const Vector3 TotalVelocoty, float SpanTime)override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionSphere�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�������鎞��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3 TotalVelocoty, const shared_ptr<CollisionSphere>& DestColl, float SpanTime)override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionObb�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�������鎞��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3 TotalVelocoty, const shared_ptr<CollisionObb>& DestColl, float SpanTime)override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionRect�Ƃ̏Փˌ㏈��
		@param[in]	TotalVelocoty	�g�[�^���̑��x�iRigidbody��Gravity�𑫂������́j
		@param[in]	DestColl	����̃R���W����
		@param[in]	SpanTime	�Փˎ���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AfterCollision(const Vector3 TotalVelocoty, const shared_ptr<CollisionRect>& DestColl, float SpanTime)override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionSphere����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionSphere>& DestColl)override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionObb����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionObb>& DestColl)override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief CollisionRect����̃G�X�P�[�v
		@param[in]	DestColl	����̃R���W����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void CollisionEscape(const shared_ptr<CollisionRect>& DestColl)override {}
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
