
#include "stdafx.h"
#include "Project.h"

namespace basecross 
{

	CSVReader::CSVReader(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	void CSVReader::OnCreate()
	{
		//�܂���CSV�������Ă��鏈��-------------------
		//�p�X�擾
		wstring Path = App::GetApp()->m_wstrDataPath + L"CSV\\";
		//�X�e�[�W�ԍ��擾
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		m_stageNum = ScenePtr->GetStageNum();
		//�t�@�C���̖��O�w��
		wstring FileName = L"stage" + Util::IntToWStr(m_stageNum) + L".csv";

		//�p�X�쐬
		Path += FileName;

		//CSV�ǂݍ���
		CsvFile GameStageCSV(Path);

		if (!GameStageCSV.ReadCsv())
		{
			//�t�@�C�������݂��Ȃ�����
			//���������s
			throw BaseException(
				L"CSV�t�@�C��������܂���",
				FileName,
				L"�I�����ꂽ�ꏊ�ɃA�N�Z�X�ł��܂���"
				);
		}
		//CSV�����Ă��鏈��---------------------------

		//CSV����ǂݍ���-----------------------------

		int RowData = 0;		//0�s�ڂ̃f�[�^���Q��
		vector<wstring>StageMapVec;		//�s�̓��e���擾������p
		GameStageCSV.GetRowVec(RowData, StageMapVec);		//0�s�ڂ̓��e��StageMapVec�ɕۑ�

		//�I�u�W�F�N�g�̏�����Ƃ��͂�-----------------------------
		//Box(Cube)
		vector<Vector3> BoxPoss;
		vector<Vector3> BoxScale;
		vector<Vector3> BoxRot;
		//�S�[��
		Vector3 GoalPos;
		Vector3 GoalScale;
		//�v���C���[
		Vector3 Player1Pos;
		Vector3 Player2Pos;
		//������
		Vector3 FirePos;
		Vector3 IceFogPos;
		//�M�~�b�N
		//�M�~�b�N�P(�X)
		vector<Vector3> Gimmick1IcePos;
		vector<Vector3> Gimmick1IceScale;
		//�M�~�b�N�Q(����)
		vector<Vector3> Gimmick2WindMillPos;
		vector<Vector3> Gimmick2WindMillScale;
		//�M�~�b�N�R(��̃R�A)
		vector<Vector3> Gimmick3CorePos;
		vector<Vector3> Gimmick3CoreScale;
		//�M�~�b�N�T(��)
		vector<Vector3> Gimmick5FirePos;
		vector<Vector3> Gimmick5FireScale;
		//�� �Ƃ肠����3�����p��
		vector<Vector3> Water1Pos;
		vector<Vector3> Water1Scale;
		vector<Vector3> Water2Pos;
		vector<Vector3> Water2Scale;
		vector<Vector3> Water3Pos;
		vector<Vector3> Water3Scale;
		//�I�u�W�F�N�g�̏�����Ƃ��͂�-----------------------------



		//��(�Ō�)�ɂȂ�܂ŌJ��Ԃ�
		while (StageMapVec[0] != L"end")
		{
			// 0:name 1:PosX 2:PosY 3:PosZ 4:ScaleX 5:ScaleY 6:ScaleZ 7:RotX 8:RotY 9:RotZ
			//��
			if (StageMapVec[0] == L"Cube")
			{
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Vector3 rot = Vector3(_wtof(StageMapVec[7].c_str()), _wtof(StageMapVec[8].c_str()), _wtof(StageMapVec[9].c_str()));
				BoxPoss.push_back(pos);
				BoxScale.push_back(scale);
				BoxRot.push_back(rot);
			}
			//�S�[��
			if (StageMapVec[0] == L"Goal")
			{
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));

				GoalPos = pos;
				GoalScale = scale;
			}
			//�v���C���[
			if (StageMapVec[0] == L"Player1")
			{
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Player1Pos = pos;
			}
			if (StageMapVec[0] == L"Player2")
			{
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Player2Pos = pos;
			}
			//�M�~�b�N�P
			if (StageMapVec[0] == L"Gimmick1")
			{
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Gimmick1IcePos.push_back(pos);
				Gimmick1IceScale.push_back(scale);
			}
			//�M�~�b�N�Q
			if (StageMapVec[0] == L"Gimmick2")
			{
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Gimmick2WindMillPos.push_back(pos);
				Gimmick2WindMillScale.push_back(scale);
			}
			//�M�~�b�N�R
			if (StageMapVec[0] == L"Gimmick3")
			{
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Gimmick3CorePos.push_back(pos);
				Gimmick3CoreScale.push_back(scale);
			}
			//�M�~�b�N�T
			if (StageMapVec[0] == L"Gimmick5")
			{
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Gimmick5FirePos.push_back(pos);
				Gimmick5FireScale.push_back(scale);
			}
			//��
			if (StageMapVec[0] == L"Water1")
			{
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Water1Pos.push_back(pos);
				Water1Scale.push_back(scale);
			}
			if (StageMapVec[0] == L"Water2")
			{
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Water2Pos.push_back(pos);
				Water2Scale.push_back(scale);
			}
			if (StageMapVec[0] == L"Water3")
			{
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Water3Pos.push_back(pos);
				Water3Scale.push_back(scale);
			}

			//������
			if (StageMapVec[0] == L"MagicBookFire")
			{
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				FirePos = pos;
			}
			if (StageMapVec[0] == L"MagicBookIceFog")
			{
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				IceFogPos = pos;
			}
			//�s�X�V
			RowData++;
			GameStageCSV.GetRowVec(RowData, StageMapVec);	
		}
		//CSV����ǂݍ���-----------------------------
		
		//�X�e�[�W�ō쐬-----------------------------
		auto st = GetStage();
		//���쐬
		int count = 0;
		for (auto v : BoxPoss)
		{
			//�X�P�[���Ɖ�]�͕ʂŎ����Ă���
			Vector3 scale = BoxScale[count];
			Vector3 rot = BoxRot[count];
			st->AddGameObject<Box>(v, scale, rot);
			count++;
		}
		count = 0;
		//�v���C���[�쐬
		//�S�[���쐬
		//�������쐬
		//�M�~�b�N�쐬
		//1
		//2
		//3
		//5
		//��
		//

		//�X�e�[�W�ō쐬-----------------------------

		//�e�X�g�p------------------------------------
		//�����������
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
		PtrString->SetFont(L"", 80);
		//�e�X�g�p------------------------------------

	}
}