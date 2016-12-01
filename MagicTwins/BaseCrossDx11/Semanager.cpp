#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class SEManager : public GameObject;
	//	�p�r: BGM�ȊO��SE���܂Ƃ߂����
	//--------------------------------------------------------------------------------------
	SEManager::SEManager(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	void SEManager::OnCreate()
	{
		for (int i = 0; i < 3; i++)
		{	
			m_CreateSe = ObjectFactory::Create<MultiAudioObject>();
			m_Se.push_back(m_CreateSe);
			m_OnFlg[i] = false;
		}

	}

	void SEManager::OnUpdate()
	{
		//3���p�ӂ��ꂽSE�Đ��̔����X�V�A0.5�b��������Ďg�p�\�ɂ���
		for (int i = 0; i < 3; i++)
		{
			if (m_OnFlg[i] == true)
			{
				m_time[i] += App::GetApp()->GetElapsedTime();
				if (m_time[i] > 0.5f)
				{
					m_OnFlg[i] = false;
					m_time[i] = 0;
				}
			}
		}
	}

	void SEManager::OnSe(string name)
	{
		for (int i = 0; i < 3; i++)
		{
			if (m_OnFlg[i] == false)
			{
				bool flgg = false;
				//�^�C�g���̑I����
				if (name == "SelectTitle")
				{
					m_Se[i]->AddAudioResource(L"SelectTitleSE");
					m_Se[i]->Start(L"SelectTitleSE", 0.5f);
					flgg = true;
				}
				//�I����
				if (name == "Select")
				{
					m_Se[i]->AddAudioResource(L"SelectSE");
					m_Se[i]->Start(L"SelectSE", 0.5f);
					flgg = true;
				}
				//�_���[�W�󂯂���
				if (name == "Damege")
				{
					m_Se[i]->AddAudioResource(L"DamageSE");
					m_Se[i]->Start(L"DamageSE", 0.5f);
					flgg = true;
				}
				//������鉹
				if (name == "Water")
				{
					m_Se[i]->AddAudioResource(L"WaterSE");
					m_Se[i]->Start(L"WaterSE", 0.5f);
					flgg = true;
				}
				//���鉹
				if (name == "Freeze")
				{
					m_Se[i]->AddAudioResource(L"FreezeSE");
					m_Se[i]->Start(L"FreezeSE", 0.5f);
					flgg = true;
				}
				//���@�ł��̉�
				if (name == "MagicShotFire")
				{
					m_Se[i]->AddAudioResource(L"FireSE");
					m_Se[i]->Start(L"FireSE", 0.5f);
					flgg = true;
				}
				if (name == "MagicShotIce")
				{
					m_Se[i]->AddAudioResource(L"IceSE");
					m_Se[i]->Start(L"IceSE", 0.5f);
					flgg = true;
				}
				if (name == "MagicShotWind")
				{
					m_Se[i]->AddAudioResource(L"WindSE");
					m_Se[i]->Start(L"WindSE", 0.5f);
					flgg = true;
				}
				//�n�`�_��
				if (name == "TerrainDamage")
				{
					m_Se[i]->AddAudioResource(L"TerrainDamageSE");
					m_Se[i]->Start(L"TerrainDamageSE", 0.5f);
					flgg = true;
				}
				//����炤��
				if (name == "FireDamage")
				{
					m_Se[i]->AddAudioResource(L"FireDamageSE");
					m_Se[i]->Start(L"FireDamageSE", 0.5f);
					flgg = true;
				}
				//�������擾��
				if (name == "MagicGet")
				{
					m_Se[i]->AddAudioResource(L"MagicGetSE");
					m_Se[i]->Start(L"MagicGetSE", 0.5f);
					flgg = true;
				}
				//�X�R�A�A�C�e���擾��
				if (name == "ScoreItemGet")
				{
					m_Se[i]->AddAudioResource(L"ScoreItemGetSE");
					m_Se[i]->Start(L"ScoreItemGetSE", 0.5f);
					flgg = true;
				}

				m_OnFlg[i] = flgg;
				if (flgg = false)
				{
					throw BaseException(
						L"Se�w��~�X", L"", L""
						);
				}
				return;
			}
		}
	}




}
