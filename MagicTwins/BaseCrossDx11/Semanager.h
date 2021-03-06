
#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	class SEManager : public GameObject;
	//	用途: BGM以外のSEをまとめるもの
	//--------------------------------------------------------------------------------------
	class SEManager : public GameObject
	{
	private:
		//音
		vector<shared_ptr<MultiAudioObject>> m_Se;
		shared_ptr<MultiAudioObject> m_CreateSe;
		float m_time[3] = { 0 };
		bool m_OnFlg[3] = {false};
	public:
		SEManager(const shared_ptr<Stage>& StagePtr);
		void OnCreate()override;
		void OnUpdate()override;
		void OnSe(string name);
	};

}