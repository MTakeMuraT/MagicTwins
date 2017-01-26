#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class SEManager : public GameObject;
	//	用途: BGM以外のSEをまとめるもの
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
		//3個分用意されたSE再生の箱を更新、0.5秒たったら再使用可能にする
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
				//タイトルの選択音
				if (name == "SelectTitle")
				{
					m_Se[i]->AddAudioResource(L"SelectTitleSE");
					m_Se[i]->Start(L"SelectTitleSE", 0.5f);
					flgg = true;
				}
				//選択音
				if (name == "Select")
				{
					m_Se[i]->AddAudioResource(L"SelectSE");
					m_Se[i]->Start(L"SelectSE", 0.5f);
					flgg = true;
				}
				//選択移動音
				if (name == "SelectMove")
				{
					m_Se[i]->AddAudioResource(L"SelectMoveSE");
					m_Se[i]->Start(L"SelectMoveSE", 0.5f);
					flgg = true;
				}
				//エネミースポーン音
				if (name == "EnemySpawn")
				{
					m_Se[i]->AddAudioResource(L"EnemySpawnSE");
					m_Se[i]->Start(L"EnemySpawnSE", 0,20.0f);
					flgg = true;
				}
				//ダメージ受けた音
				if (name == "Damege")
				{
					m_Se[i]->AddAudioResource(L"DamageSE");
					m_Se[i]->Start(L"DamageSE", 0.5f);
					flgg = true;
				}
				//水流れる音
				if (name == "Water")
				{
					m_Se[i]->AddAudioResource(L"WaterSE");
					m_Se[i]->Start(L"WaterSE", 0.5f);
					flgg = true;
				}
				//凍る音
				if (name == "Freeze")
				{
					m_Se[i]->AddAudioResource(L"FreezeSE");
					m_Se[i]->Start(L"FreezeSE", 0,0.3f);
					flgg = true;
				}
				//魔法打つ時の音
				if (name == "MagicShotFire")
				{
					m_Se[i]->AddAudioResource(L"FireSE");
					m_Se[i]->Start(L"FireSE", 0.5f);
					flgg = true;
				}
				if (name == "MagicShotIce")
				{
					m_Se[i]->AddAudioResource(L"IceSE");
					m_Se[i]->Start(L"IceSE",0, 0.3f);
					flgg = true;
				}
				if (name == "MagicShotWind")
				{
					m_Se[i]->AddAudioResource(L"WindSE");
					m_Se[i]->Start(L"WindSE", 0.5f);
					flgg = true;
				}
				//地形ダメ
				if (name == "TerrainDamage")
				{
					m_Se[i]->AddAudioResource(L"TerrainDamageSE");
					m_Se[i]->Start(L"TerrainDamageSE", 0.5f);
					flgg = true;
				}
				//炎喰らう音
				if (name == "FireDamage")
				{
					m_Se[i]->AddAudioResource(L"FireDamageSE");
					m_Se[i]->Start(L"FireDamageSE", 0,1.5f);
					flgg = true;
				}
				//魔導書取得音
				if (name == "MagicGet")
				{
					m_Se[i]->AddAudioResource(L"MagicGetSE");
					m_Se[i]->Start(L"MagicGetSE", 0.5f);
					flgg = true;
				}
				//スコアアイテム取得音
				if (name == "ScoreItemGet")
				{
					m_Se[i]->AddAudioResource(L"ScoreItemGetSE");
					m_Se[i]->Start(L"ScoreItemGetSE", 0.5f);
					flgg = true;
				}
				//タイムもうちょい赤枠
				if (name == "TimeAlert")
				{
					m_Se[i]->AddAudioResource(L"TimeAlertSE");
					m_Se[i]->Start(L"TimeAlertSE", 0.5f);
					flgg = true;
				}
				m_OnFlg[i] = flgg;
				if (flgg == false)
				{
					throw BaseException(
						L"Se指定ミス", L"", L""
						);
				}
				return;
			}
		}
	}




}
