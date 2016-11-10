
#include "stdafx.h"
#include "Project.h"

namespace basecross 
{

	CSVReader::CSVReader(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	void CSVReader::OnCreate()
	{
		//まずはCSVを持ってくる処理-------------------
		//パス取得
		wstring Path = App::GetApp()->m_wstrDataPath + L"CSV\\";
		//ステージ番号取得
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		m_stageNum = ScenePtr->GetStageNum();
		//ファイルの名前指定
		wstring FileName = L"stage" + Util::IntToWStr(m_stageNum) + L".csv";

		//パス作成
		Path += FileName;

		//CSV読み込み
		CsvFile GameStageCSV(Path);

		if (!GameStageCSV.ReadCsv())
		{
			//ファイルが存在しなかった
			//初期化失敗
			throw BaseException(
				L"CSVファイルがありません",
				FileName,
				L"選択された場所にアクセスできません"
				);
		}
		//CSV持ってくる処理---------------------------

		//CSVから読み込み-----------------------------

		int RowData = 0;		//0行目のデータを参照
		vector<wstring>StageMapVec;		//行の内容を取得させる用
		GameStageCSV.GetRowVec(RowData, StageMapVec);		//0行目の内容をStageMapVecに保存

		//オブジェクトの情報入れとくはこ-----------------------------
		//Box(Cube)
		vector<Vector3> BoxPoss;
		vector<Vector3> BoxScale;
		vector<Vector3> BoxRot;
		//ゴール
		Vector3 GoalPos;
		Vector3 GoalScale;
		//プレイヤー
		Vector3 Player1Pos;
		Vector3 Player2Pos;
		//魔導書
		Vector3 FirePos;
		Vector3 IceFogPos;
		//ギミック
		//ギミック１(氷)
		vector<Vector3> Gimmick1IcePos;
		vector<Vector3> Gimmick1IceScale;
		//ギミック２(風車)
		vector<Vector3> Gimmick2WindMillPos;
		vector<Vector3> Gimmick2WindMillScale;
		//ギミック３(川のコア)
		vector<Vector3> Gimmick3CorePos;
		vector<Vector3> Gimmick3CoreScale;
		//ギミック５(炎)
		vector<Vector3> Gimmick5FirePos;
		vector<Vector3> Gimmick5FireScale;
		//川 とりあえず3こ分用意
		vector<Vector3> Water1Pos;
		vector<Vector3> Water1Scale;
		vector<Vector3> Water2Pos;
		vector<Vector3> Water2Scale;
		vector<Vector3> Water3Pos;
		vector<Vector3> Water3Scale;
		//オブジェクトの情報入れとくはこ-----------------------------



		//空(最後)になるまで繰り返す
		while (StageMapVec[0] != L"end")
		{
			// 0:name 1:PosX 2:PosY 3:PosZ 4:ScaleX 5:ScaleY 6:ScaleZ 7:RotX 8:RotY 9:RotZ
			//箱
			if (StageMapVec[0] == L"Cube")
			{
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Vector3 rot = Vector3(_wtof(StageMapVec[7].c_str()), _wtof(StageMapVec[8].c_str()), _wtof(StageMapVec[9].c_str()));
				BoxPoss.push_back(pos);
				BoxScale.push_back(scale);
				BoxRot.push_back(rot);
			}
			//ゴール
			if (StageMapVec[0] == L"Goal")
			{
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));

				GoalPos = pos;
				GoalScale = scale;
			}
			//プレイヤー
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
			//ギミック１
			if (StageMapVec[0] == L"Gimmick1")
			{
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Gimmick1IcePos.push_back(pos);
				Gimmick1IceScale.push_back(scale);
			}
			//ギミック２
			if (StageMapVec[0] == L"Gimmick2")
			{
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Gimmick2WindMillPos.push_back(pos);
				Gimmick2WindMillScale.push_back(scale);
			}
			//ギミック３
			if (StageMapVec[0] == L"Gimmick3")
			{
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Gimmick3CorePos.push_back(pos);
				Gimmick3CoreScale.push_back(scale);
			}
			//ギミック５
			if (StageMapVec[0] == L"Gimmick5")
			{
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Gimmick5FirePos.push_back(pos);
				Gimmick5FireScale.push_back(scale);
			}
			//水
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

			//魔導書
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
			//行更新
			RowData++;
			GameStageCSV.GetRowVec(RowData, StageMapVec);	
		}
		//CSVから読み込み-----------------------------
		
		//ステージで作成-----------------------------
		auto st = GetStage();
		//魔法が当たって消えるオブジェクトグループ
		auto MOG = st->CreateSharedObjectGroup(L"MagicObjects");

		//箱作成
		int count = 0;
		for (auto v : BoxPoss)
		{
			//スケールと回転は別で持ってくる
			Vector3 scale = BoxScale[count];
			Vector3 rot = BoxRot[count];
			st->AddGameObject<Box>(v, scale, rot);
			count++;
		}
		count = 0;
		//プレイヤー作成
		st->SetSharedGameObject(L"Player1",st->AddGameObject<Player>(Player1Pos, true, "Player1"));
		st->SetSharedGameObject(L"Player2",st->AddGameObject<Player>(Player2Pos, false, "Player2"));
		//ゴール作成
		st->SetSharedGameObject(L"Goal",st->AddGameObject<Goal>(GoalPos, GoalScale));
		//魔導書作成
		auto MBGroup = st->CreateSharedObjectGroup(L"MagicBook");
		MBGroup->IntoGroup(st->AddGameObject<MagicBook>(FirePos, Fire));
		MBGroup->IntoGroup(st->AddGameObject<MagicBook>(IceFogPos, IceFog));
		//ギミック作成
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
		//5
		for (auto v : Gimmick5FirePos)
		{
			Vector3 scale = Gimmick5FireScale[count];
			MOG->IntoGroup(st->AddGameObject<Gimmick5>(v, scale));
			count++;
		}
		count = 0;
		//水
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
		//3
		for (auto v : Gimmick3CorePos)
		{
			Vector3 scale = Gimmick3CoreScale[count];
			auto Gimi3P = st->AddGameObject<Gimmick3>(v, scale);
			Gimi3P->SetWaters(Water1Vec);
			MOG->IntoGroup(Gimi3P);
			count++;
		}
		count = 0;
		//

		//ステージで作成-----------------------------

		//テスト用------------------------------------
		//文字列をつける
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
		PtrString->SetFont(L"", 80);
		//テスト用------------------------------------

	}
}