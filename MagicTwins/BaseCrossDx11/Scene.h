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
		//�X�R�A�A�C�e���擾��
		unsigned int m_ScoreItemCount = 0;
		//��
		shared_ptr<MultiAudioObject> m_AudioTitle;
		//�X�e�[�W
		shared_ptr<MultiAudioObject> m_AudioGame;
		//���U���g
		shared_ptr<MultiAudioObject> m_AudioResult;
		//�Q�[���I�[�o�[
		shared_ptr<MultiAudioObject> m_AudioGameOver;


		//�߂�ǂ����璼�ł��Ŗ��@�̎�ލ��
		const int m_MagicTypeLength = 2;

		//�X�e�[�W�̔ԍ�
		unsigned int m_stageNum = 1;

		//���S��~
		void StopBGM();

		//�S�[�������t���O
		bool m_GoalFlg = false;
	public:
		Scene() :SceneBase(){}
		virtual ~Scene(){}
		virtual void OnCreate() override;
		virtual void OnEvent(const shared_ptr<Event>& event) override;

		//�X�e�[�W�ԍ��Z�b�g
		void SetStageNum(int num) { m_stageNum = num; }
		//�X�e�[�W�ԍ��擾
		unsigned int GetStageNum() { return m_stageNum; }

		//���Ԃ�N���A�ƃX�R�A�g���ĂȂ�
		//�N���A�^�C�����Z�b�g
		void SetClearTime(unsigned int num) { m_clearTime = num; }
		//�N���A�^�C���擾
		unsigned int GetClearTime() { return m_clearTime; }

		//�X�R�A�A�C�e���擾�����Z�b�g
		void SetScoreItemCount(unsigned int num) { m_ScoreItemCount = num; }
		//�X�R�A�A�C�e���擾
		unsigned int GetScoreItemCount() { return m_ScoreItemCount; }

		//�N���A�����Ƃ���BGM����
		void ClearBGM();
	};

}

//end basecross
