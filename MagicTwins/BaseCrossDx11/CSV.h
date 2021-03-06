#pragma once

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class CSVReader : public GameObject;
	//	用途: CSVを読み込む
	//--------------------------------------------------------------------------------------
	class CSVReader : public GameObject
	{
	private :
		unsigned int m_stageNum = 0;
	public :
		CSVReader(const shared_ptr<Stage>& StagePtr);

		virtual void OnCreate() override;
	};

	/*auto ScenePtr = App::GetApp()->GetScene<Scene>();
	ScenePtr->SetStageNum(m_StageNum);
	*/

}