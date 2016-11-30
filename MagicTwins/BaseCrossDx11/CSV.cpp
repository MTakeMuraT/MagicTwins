
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
		//�n��
		vector<Vector3> PlanePos;
		vector<Vector3> PlaneScale;
		vector<Vector3> PlaneRot;
		//��
		vector<Vector3> RockPos;
		vector<Vector3> RockScale;
		//��
		vector<Vector3> FencePos;
		vector<Vector3> FenceScale;		
		vector<Vector3> FenceRot;
		//�S�[��
		Vector3 GoalPos;
		Vector3 GoalScale;
		//�v���C���[
		Vector3 Player1Pos;
		Vector3 Player2Pos;
		//�G�l�~�[
		vector<Vector3> Enemy1pos;
		vector<Vector3> Enemy1Scale;
		vector<Vector3> Enemy2pos;
		vector<Vector3> Enemy2Scale;

		//������
		Vector3 FirePos;
		Vector3 IceFogPos;
		Vector3 WindPos;
		//�X�R�A�A�C�e��
		vector<Vector3> ScoreItemPos;
		vector<Vector3> ScoreItemScale;
		//�M�~�b�N
		//�M�~�b�N�P(�X)
		vector<Vector3> Gimmick1IcePos;
		vector<Vector3> Gimmick1IceScale;
		//�M�~�b�N�Q(����)
		vector<Vector3> Gimmick2WindMillPos;
		vector<Vector3> Gimmick2WindMillScale;
		//���̐���
		Vector3 Gimmick2_1WaterGatePos;
		Vector3 Gimmick2_1WaterGateScale;
		//�M�~�b�N�R(��̃R�A)�ő�R�܂őΉ�
		vector<Vector3> WaterCore1Pos;
		vector<Vector3> WaterCore2Pos;
		vector<Vector3> WaterCore3Pos;
		//Vector3 WaterCore1Pos;
		//Vector3 WaterCore2Pos;
		//Vector3 WaterCore3Pos;

		vector<Vector3> WaterCore1Scale;
		vector<Vector3> WaterCore2Scale;
		vector<Vector3> WaterCore3Scale;
		//Vector3 WaterCore1Scale;
		//Vector3 WaterCore2Scale;
		//Vector3 WaterCore3Scale;
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
		//�� �Ƃ肠����3�����p��
		vector<Vector3> WaterFall1Pos;
		vector<Vector3> WaterFall1Scale;
		vector<Vector3> WaterFall2Pos;
		vector<Vector3> WaterFall2Scale;
		vector<Vector3> WaterFall3Pos;
		vector<Vector3> WaterFall3Scale;


		//�I�u�W�F�N�g�̏�����Ƃ��͂�-----------------------------


		//��(�Ō�)�ɂȂ�܂ŌJ��Ԃ�
		while (StageMapVec[0] != L"end")
		{
			//�����񂠂������ǂ���
			bool Flgg = false;
			// 0:name 1:PosX 2:PosY 3:PosZ 4:ScaleX 5:ScaleY 6:ScaleZ 7:RotX 8:RotY 9:RotZ
			//��
			if (StageMapVec[0] == L"Cube")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Vector3 rot = Vector3(_wtof(StageMapVec[7].c_str()), _wtof(StageMapVec[8].c_str()), _wtof(StageMapVec[9].c_str()));
				BoxPoss.push_back(pos);
				BoxScale.push_back(scale);
				rot *= (3.14159265f / 180);
				BoxRot.push_back(rot);
			}
			if (StageMapVec[0] == L"Plane")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Vector3 rot = Vector3(_wtof(StageMapVec[7].c_str()), _wtof(StageMapVec[8].c_str()), _wtof(StageMapVec[9].c_str()));
				PlanePos.push_back(pos);
				PlaneScale.push_back(scale);
				PlaneRot.push_back(rot);
			}
			//��
			if (StageMapVec[0] == L"Rock")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				RockPos.push_back(pos);
				RockScale.push_back(scale);
			}
			//��
			if (StageMapVec[0] == L"Fence")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Vector3 rot = Vector3(_wtof(StageMapVec[7].c_str()), _wtof(StageMapVec[8].c_str()), _wtof(StageMapVec[9].c_str()));
				FencePos.push_back(pos);
				FenceScale.push_back(scale);
				rot *= (3.14159265f / 180);
				FenceRot.push_back(rot);
			}
			//�X�R�A�A�C�e��
			if (StageMapVec[0] == L"ScoreItem")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				ScoreItemPos.push_back(pos);
				ScoreItemScale.push_back(scale);
			}

			//�S�[��
			if (StageMapVec[0] == L"Goal")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));

				GoalPos = pos;
				GoalScale = scale;
			}
			//�v���C���[
			if (StageMapVec[0] == L"Player1")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Player1Pos = pos;
			}
			if (StageMapVec[0] == L"Player2")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Player2Pos = pos;
			}
			//�G�l�~�[
			if (StageMapVec[0] == L"Enemy1")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Enemy1pos.push_back(pos);
				Enemy1Scale.push_back(scale);
			}
			//�G�l�~�[
			if (StageMapVec[0] == L"Enemy2")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Enemy2pos.push_back(pos);
				Enemy2Scale.push_back(scale);
			}

			//�M�~�b�N�P
			if (StageMapVec[0] == L"Gimmick1")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Gimmick1IcePos.push_back(pos);
				Gimmick1IceScale.push_back(scale);
			}
			//�M�~�b�N�Q
			if (StageMapVec[0] == L"Gimmick2")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Gimmick2WindMillPos.push_back(pos);
				Gimmick2WindMillScale.push_back(scale);
			}
			//����
			if (StageMapVec[0] == L"Gimmick2_1")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Gimmick2_1WaterGatePos = pos;
				Gimmick2_1WaterGateScale = scale;
			}
			//�M�~�b�N�R
			if (StageMapVec[0] == L"Gimmick31")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				//WaterCore1Pos = pos;
				//WaterCore1Scale = scale;
				WaterCore1Pos.push_back(pos);
				WaterCore1Scale.push_back(scale);
			}
			if (StageMapVec[0] == L"Gimmick32")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				WaterCore2Pos.push_back(pos);
				WaterCore2Scale.push_back(scale);
			}
			if (StageMapVec[0] == L"Gimmick33")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				WaterCore3Pos.push_back(pos);
				WaterCore3Scale.push_back(scale);
			}
			//�M�~�b�N�T
			if (StageMapVec[0] == L"Gimmick5")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Gimmick5FirePos.push_back(pos);
				Gimmick5FireScale.push_back(scale);
			}
			//��
			if (StageMapVec[0] == L"Water1")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Water1Pos.push_back(pos);
				Water1Scale.push_back(scale);
			}
			if (StageMapVec[0] == L"Water2")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Water2Pos.push_back(pos);
				Water2Scale.push_back(scale);
			}
			if (StageMapVec[0] == L"Water3")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Water3Pos.push_back(pos);
				Water3Scale.push_back(scale);
			}
			if (StageMapVec[0] == L"WaterFall1")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				WaterFall1Pos.push_back(pos);
				WaterFall1Scale.push_back(scale);
			}
			if (StageMapVec[0] == L"WaterFall2")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				WaterFall2Pos.push_back(pos);
				WaterFall2Scale.push_back(scale);
			}
			if (StageMapVec[0] == L"WaterFall3")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				WaterFall3Pos.push_back(pos);
				WaterFall3Scale.push_back(scale);
			}

			//������
			if (StageMapVec[0] == L"MagicBookFire")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				FirePos = pos;
			}
			if (StageMapVec[0] == L"MagicBookIceFog")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				IceFogPos = pos;
			}

			if (StageMapVec[0] == L"MagicBookWind")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				WindPos = pos;
			}

			if (!Flgg)
			{
				throw BaseException(
					L"CSV�Ɏw�肳��Ă��Ȃ�������", L"�ݒ肳��Ă��܂�", Util::IntToWStr(RowData+1) + L"�s��"
					);

			}
			//�s�X�V
			RowData++;
			GameStageCSV.GetRowVec(RowData, StageMapVec);	
		}
		//CSV����ǂݍ���-----------------------------
		
		//�|�[�Y�Ƃ��ŃA�b�v�f�[�g�~�߂�I�u�W�F�N�g
		auto SUG = GetStage()->GetSharedObjectGroup(L"SetUpdateObj");

		//�X�e�[�W�ō쐬-----------------------------
		auto st = GetStage();
		//���@���������ď�����I�u�W�F�N�g�O���[�v
		auto MOG = st->CreateSharedObjectGroup(L"MagicObjects");

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
		for (auto v : PlanePos)
		{
			//�X�P�[���Ɖ�]�͕ʂŎ����Ă���
			Vector3 scale = PlaneScale[count];
			Vector3 rot = PlaneRot[count];
			st->AddGameObject<PlaneP>(v, scale, rot);
			count++;
		}
		count = 0;

		//��쐬
		for (auto v : RockPos)
		{
			//�X�P�[���͕ʂŎ����Ă���
			Vector3 scale = RockScale[count];
			st->AddGameObject<Rock>(v, scale);
			count++;
		}
		count = 0;
		//��쐬
		for (auto v : FencePos)
		{
			Vector3 scale = FenceScale[count];
			Vector3 rot = FenceRot[count];
			auto ptr = st->AddGameObject<Fence>(v, scale, rot);
			MOG->IntoGroup(ptr);
			count++;
		}
		count = 0;
		//�X�R�A�A�C�e���쐬
		//�X�R�A�A�C�e���O���[�v
		auto SIG = st->CreateSharedObjectGroup(L"ScoreItem");
		for (auto v : ScoreItemPos)
		{
			//�X�P�[���͕ʂŎ����Ă���
			Vector3 scale = ScoreItemScale[count];
			auto Ptr = st->AddGameObject<ScoreItem>(v, scale);
			SIG->IntoGroup(Ptr);
			count++;
		}
		count = 0;
		//�v���C���[�쐬
		auto PP = st->AddGameObject<Player>(Player1Pos, true, "Player1");
		st->SetSharedGameObject(L"Player1",PP);
		//�A�b�v�f�[�g�O���[�v�ǉ�
		SUG->IntoGroup(PP);
		auto PP2 = st->AddGameObject<Player>(Player2Pos, false, "Player2");
		//�A�b�v�f�[�g�O���[�v�ǉ�
		SUG->IntoGroup(PP2);
		st->SetSharedGameObject(L"Player2",PP2);
		//�G�l�~�[�쐬
		auto EG = GetStage()->CreateSharedObjectGroup(L"Enemy");
		for (auto v : Enemy1pos)
		{
			//�X�P�[���͕ʂŎ����Ă���
			Vector3 scale = Enemy1Scale[count];
			auto EPt = st->AddGameObject<Enemy>(v, scale,1);
			EG->IntoGroup(EPt);
			MOG->IntoGroup(EPt);
			//�A�b�v�f�[�g�O���[�v�ǉ�
			SUG->IntoGroup(EPt);
			count++;
		}
		count = 0;
		for (auto v : Enemy2pos)
		{
			//�X�P�[���͕ʂŎ����Ă���
			Vector3 scale = Enemy2Scale[count];
			auto EPt = st->AddGameObject<Enemy>(v, scale, 2);
			EG->IntoGroup(EPt);
			MOG->IntoGroup(EPt);
			//�A�b�v�f�[�g�O���[�v�ǉ�
			SUG->IntoGroup(EPt);
			count++;
		}
		count = 0;

		//�S�[���쐬
		st->SetSharedGameObject(L"Goal",st->AddGameObject<Goal>(GoalPos, GoalScale));
		//�������쐬
		auto MBGroup = st->CreateSharedObjectGroup(L"MagicBook");
		if (FirePos != Vector3(0,0,0))
		{
			auto MPt = st->AddGameObject<MagicBook>(FirePos, Fire);
			MBGroup->IntoGroup(MPt);
			//�A�b�v�f�[�g�O���[�v�ǉ�
			SUG->IntoGroup(MPt);
		}
		//�X
		if (IceFogPos != Vector3(0, 0, 0))
		{
			auto MPt = st->AddGameObject<MagicBook>(IceFogPos, IceFog);
			MBGroup->IntoGroup(MPt);
			//�A�b�v�f�[�g�O���[�v�ǉ�
			SUG->IntoGroup(MPt);
		}
		//��
		if (WindPos != Vector3(0, 0, 0))
		{
			auto MPt = st->AddGameObject<MagicBook>(WindPos, Wind);
			MBGroup->IntoGroup(MPt);
			//�A�b�v�f�[�g�O���[�v�ǉ�
			SUG->IntoGroup(MPt);
		}

		//�M�~�b�N�쐬
		//1
		for (auto v : Gimmick1IcePos)
		{
			Vector3 scale = Gimmick1IceScale[count];
			MOG->IntoGroup(st->AddGameObject<Gimmick1>(v, scale));
			count++;
		}
		count = 0;
		//2
		for (auto v : Gimmick2WindMillPos)
		{
			Vector3 scale = Gimmick2WindMillScale[count];
			MOG->IntoGroup(st->AddGameObject<Gimmick2>(v, scale));
			count++;
		}
		count = 0;
		//����
		auto waterGate = st->AddGameObject<Gimmick2_1>(Gimmick2_1WaterGatePos, Gimmick2_1WaterGateScale);
		st->SetSharedGameObject(L"WaterGate",waterGate);
		SUG->IntoGroup(waterGate);
		
		//5
		for (auto v : Gimmick5FirePos)
		{
			Vector3 scale = Gimmick5FireScale[count];
			MOG->IntoGroup(st->AddGameObject<Gimmick5>(v, scale));
			count++;
		}
		count = 0;
		//��
		vector<shared_ptr<Water>> Water1Vec;
		for (auto v : Water1Pos)
		{
			Vector3 scale = Water1Scale[count];
			auto waP = st->AddGameObject<Water>(v, scale, 1);
			Water1Vec.push_back(waP);
			count++;
		}
		count = 0;
		vector<shared_ptr<Water>> Water2Vec;
		for (auto v : Water2Pos)
		{
			Vector3 scale = Water2Scale[count];
			auto waP = st->AddGameObject<Water>(v, scale, 1);
			Water2Vec.push_back(waP);
			count++;
		}
		count = 0;
		vector<shared_ptr<Water>> Water3Vec;
		for (auto v : Water3Pos)
		{
			Vector3 scale = Water3Scale[count];
			auto waP = st->AddGameObject<Water>(v, scale, 1);
			Water3Vec.push_back(waP);
			count++;
		}
		count = 0;

		//��
		auto WaterFallGroup = st->CreateSharedObjectGroup(L"WaterFall");
		vector<shared_ptr<WaterFall>> WaterFall1Vec;
		for (auto v : WaterFall1Pos)
		{
			Vector3 scale = WaterFall1Scale[count];
			auto waP = st->AddGameObject<WaterFall>(v, scale);
			WaterFall1Vec.push_back(waP);
			WaterFallGroup->IntoGroup(waP);
			MOG->IntoGroup(waP);
			count++;
		}
		count = 0;

		vector<shared_ptr<WaterFall>> WaterFall2Vec;
		for (auto v : WaterFall2Pos)
		{
			Vector3 scale = WaterFall2Scale[count];
			auto waP = st->AddGameObject<WaterFall>(v, scale);
			WaterFall2Vec.push_back(waP);
			WaterFallGroup->IntoGroup(waP);
			MOG->IntoGroup(waP);
			count++;
		}
		count = 0;

		vector<shared_ptr<WaterFall>> WaterFall3Vec;
		for (auto v : WaterFall3Pos)
		{
			Vector3 scale = WaterFall3Scale[count];
			auto waP = st->AddGameObject<WaterFall>(v, scale);
			WaterFall3Vec.push_back(waP);
			WaterFallGroup->IntoGroup(waP);
			MOG->IntoGroup(waP);
			count++;
		}
		count = 0;

		//3
		//����p�O���[�v
		auto WaterGateGroup = st->CreateSharedObjectGroup(L"WaterCoreGate");
		auto WaterCoreGroup = st->CreateSharedObjectGroup(L"WaterCore");

		for (auto v : WaterCore1Pos)
		{
			Vector3 scale = WaterCore1Scale[count];
			auto Gimi3P = st->AddGameObject<Gimmick3>(v, scale);
			//�R�A�Ɋ֘A���鐅��ǉ�
			Gimi3P->SetWaters(Water1Vec);
			Gimi3P->SetWaterFalls(WaterFall1Vec);
			//���@��������I�u�W�F�N�g�ɐݒ�
			MOG->IntoGroup(Gimi3P);
			//�A�b�v�f�[�g�O���[�v�ǉ�
			SUG->IntoGroup(Gimi3P);
			WaterGateGroup->IntoGroup(Gimi3P);
			WaterCoreGroup->IntoGroup(Gimi3P);
			count++;
		}
		count = 0;
		for (auto v : WaterCore2Pos)
		{
			Vector3 scale = WaterCore2Scale[count];
			auto Gimi3P = st->AddGameObject<Gimmick3>(v, scale);
			//�R�A�Ɋ֘A���鐅��ǉ�
			Gimi3P->SetWaters(Water2Vec);
			Gimi3P->SetWaterFalls(WaterFall2Vec);
			//���@��������I�u�W�F�N�g�ɐݒ�
			MOG->IntoGroup(Gimi3P);
			//�A�b�v�f�[�g�O���[�v�ǉ�
			SUG->IntoGroup(Gimi3P);
			WaterGateGroup->IntoGroup(Gimi3P);
			WaterCoreGroup->IntoGroup(Gimi3P);
			count++;
		}
		count = 0;

		for (auto v : WaterCore3Pos)
		{
			Vector3 scale = WaterCore3Scale[count];
			auto Gimi3P = st->AddGameObject<Gimmick3>(v, scale);
			//�R�A�Ɋ֘A���鐅��ǉ�
			Gimi3P->SetWaters(Water3Vec);
			Gimi3P->SetWaterFalls(WaterFall3Vec);
			//���@��������I�u�W�F�N�g�ɐݒ�
			MOG->IntoGroup(Gimi3P);
			//�A�b�v�f�[�g�O���[�v�ǉ�
			SUG->IntoGroup(Gimi3P);
			WaterGateGroup->IntoGroup(Gimi3P);
			WaterCoreGroup->IntoGroup(Gimi3P);
			count++;
		}
		count = 0;

		/*
		auto Gimi3P = st->AddGameObject<Gimmick3>(WaterCore1Pos, WaterCore1Scale);
		//�R�A�Ɋ֘A���鐅��ǉ�
		Gimi3P->SetWaters(Water1Vec);
		//���@��������I�u�W�F�N�g�ɐݒ�
		MOG->IntoGroup(Gimi3P);
		//�A�b�v�f�[�g�O���[�v�ǉ�
		SUG->IntoGroup(Gimi3P);
		WaterGateGroup->IntoGroup(Gimi3P);
		//�ȉ���
		*/
		/*
		//3�̂Q
		auto Gimi3P = st->AddGameObject<Gimmick3>(WaterCore2Pos, WaterCore2Scale);
		Gimi3P->SetWaters(Water2Vec);
		MOG->IntoGroup(Gimi3P);
		SUG->IntoGroup(Gimi3P);
		WaterGateGroup->IntoGroup(Gimi3P);

		//3��3
		Gimi3P = st->AddGameObject<Gimmick3>(WaterCore3Pos, WaterCore3Scale);
		Gimi3P->SetWaters(Water3Vec);
		MOG->IntoGroup(Gimi3P);
		SUG->IntoGroup(Gimi3P);
		WaterGateGroup->IntoGroup(Gimi3P);
		*/

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