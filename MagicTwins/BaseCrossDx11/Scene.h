/*!
@file Scene.h
@brief �V�[��
*/
#pragma once

#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase
	{
	private:
		//�N���A�^�C��
		unsigned int m_clearTime = 0;
		//��
		shared_ptr<MultiAudioObject> m_AudioObjectPtr;

		//�߂�ǂ����璼�ł��Ŗ��@�̎�ލ��
		const int m_MagicTypeLength = 2;

		//�X�e�[�W�̔ԍ�
		unsigned int m_stageNum = 1;
	public:
		Scene() :SceneBase(){}
		virtual ~Scene(){}
		virtual void OnCreate() override;
		virtual void OnEvent(const shared_ptr<Event>& event) override;

		//�X�e�[�W�ԍ��Z�b�g
		void SetStageNum(int num) { m_stageNum = num; }
		//�X�e�[�W�ԍ��擾
		unsigned int GetStageNum() { return m_stageNum; }

		//�N���A�^�C�����Z�b�g
		void SetClearTime(int num) { m_clearTime = num; }
		//�N���A�^�C���擾
		int GetClearTime() { return m_clearTime; }
	};

}

//end basecross
