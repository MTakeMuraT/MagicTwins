#pragma once

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class CSVReader : public GameObject;
	//	�p�r: CSV��ǂݍ���
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