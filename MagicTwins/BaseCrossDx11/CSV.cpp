
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
		//岩
		vector<Vector3> RockPos;
		vector<Vector3> RockScale;
		//柵
		vector<Vector3> FencePos;
		vector<Vector3> FenceScale;		
		vector<Vector3> FenceRot;
		//ゴール
		Vector3 GoalPos;
		Vector3 GoalScale;
		//プレイヤー
		Vector3 Player1Pos;
		Vector3 Player2Pos;
		//エネミー
		vector<Vector3> Enemypos;
		vector<Vector3> EnemyScale;
		//魔導書
		Vector3 FirePos;
		Vector3 IceFogPos;
		Vector3 WindPos;
		//スコアアイテム
		vector<Vector3> ScoreItemPos;
		vector<Vector3> ScoreItemScale;
		//ギミック
		//ギミック１(氷)
		vector<Vector3> Gimmick1IcePos;
		vector<Vector3> Gimmick1IceScale;
		//ギミック２(風車)
		vector<Vector3> Gimmick2WindMillPos;
		vector<Vector3> Gimmick2WindMillScale;
		//↑の水門
		Vector3 Gimmick2_1WaterGatePos;
		Vector3 Gimmick2_1WaterGateScale;
		//ギミック３(川のコア)最大３個まで対応
		Vector3 WaterCore1Pos;
		Vector3 WaterCore2Pos;
		Vector3 WaterCore3Pos;

		Vector3 WaterCore1Scale;
		Vector3 WaterCore2Scale;
		Vector3 WaterCore3Scale;
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
			//文字列あったかどうか
			bool Flgg = false;
			// 0:name 1:PosX 2:PosY 3:PosZ 4:ScaleX 5:ScaleY 6:ScaleZ 7:RotX 8:RotY 9:RotZ
			//箱
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
			//岩
			if (StageMapVec[0] == L"Rock")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				RockPos.push_back(pos);
				RockScale.push_back(scale);
			}
			//柵
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
			//スコアアイテム
			if (StageMapVec[0] == L"ScoreItem")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				ScoreItemPos.push_back(pos);
				ScoreItemScale.push_back(scale);
			}

			//ゴール
			if (StageMapVec[0] == L"Goal")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));

				GoalPos = pos;
				GoalScale = scale;
			}
			//プレイヤー
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
			//エネミー
			if (StageMapVec[0] == L"Enemy")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Enemypos.push_back(pos);
				EnemyScale.push_back(scale);
			}
			//ギミック１
			if (StageMapVec[0] == L"Gimmick1")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Gimmick1IcePos.push_back(pos);
				Gimmick1IceScale.push_back(scale);
			}
			//ギミック２
			if (StageMapVec[0] == L"Gimmick2")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Gimmick2WindMillPos.push_back(pos);
				Gimmick2WindMillScale.push_back(scale);
			}
			//水門
			if (StageMapVec[0] == L"Gimmick2_1")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Gimmick2_1WaterGatePos = pos;
				Gimmick2_1WaterGateScale = scale;
			}
			//ギミック３
			if (StageMapVec[0] == L"Gimmick31")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				WaterCore1Pos = pos;
				WaterCore1Scale = scale;
			}
			if (StageMapVec[0] == L"Gimmick32")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				WaterCore2Pos = pos;
				WaterCore2Scale = scale;
			}
			if (StageMapVec[0] == L"Gimmick33")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				WaterCore3Pos = pos;
				WaterCore3Scale = scale;
			}
			//ギミック５
			if (StageMapVec[0] == L"Gimmick5")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Gimmick5FirePos.push_back(pos);
				Gimmick5FireScale.push_back(scale);
			}
			//水
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

			//魔導書
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
					L"CSVに指定されていない文字列が", L"設定されています", Util::IntToWStr(RowData+1) + L"行目"
					);

			}
			//行更新
			RowData++;
			GameStageCSV.GetRowVec(RowData, StageMapVec);	
		}
		//CSVから読み込み-----------------------------
		
		//ポーズとかでアップデート止めるオブジェクト
		auto SUG = GetStage()->GetSharedObjectGroup(L"SetUpdateObj");

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
		//岩作成
		for (auto v : RockPos)
		{
			//スケールは別で持ってくる
			Vector3 scale = RockScale[count];
			st->AddGameObject<Rock>(v, scale);
			count++;
		}
		count = 0;
		//柵作成
		for (auto v : FencePos)
		{
			Vector3 scale = FenceScale[count];
			Vector3 rot = FenceRot[count];
			auto ptr = st->AddGameObject<Fence>(v, scale, rot);
			MOG->IntoGroup(ptr);
			count++;
		}
		count = 0;
		//スコアアイテム作成
		//スコアアイテムグループ
		auto SIG = st->CreateSharedObjectGroup(L"ScoreItem");
		for (auto v : ScoreItemPos)
		{
			//スケールは別で持ってくる
			Vector3 scale = ScoreItemScale[count];
			auto Ptr = st->AddGameObject<ScoreItem>(v, scale);
			SIG->IntoGroup(Ptr);
			count++;
		}
		count = 0;
		//プレイヤー作成
		auto PP = st->AddGameObject<Player>(Player1Pos, true, "Player1");
		st->SetSharedGameObject(L"Player1",PP);
		//アップデートグループ追加
		SUG->IntoGroup(PP);
		auto PP2 = st->AddGameObject<Player>(Player2Pos, false, "Player2");
		//アップデートグループ追加
		SUG->IntoGroup(PP2);
		st->SetSharedGameObject(L"Player2",PP2);
		//エネミー作成
		auto EG = GetStage()->CreateSharedObjectGroup(L"Enemy");
		for (auto v : Enemypos)
		{
			//スケールは別で持ってくる
			Vector3 scale = EnemyScale[count];
			auto EPt = st->AddGameObject<Enemy>(v, scale);
			EG->IntoGroup(EPt);
			MOG->IntoGroup(EPt);
			//アップデートグループ追加
			SUG->IntoGroup(EPt);
			count++;
		}
		count = 0;
		//ゴール作成
		st->SetSharedGameObject(L"Goal",st->AddGameObject<Goal>(GoalPos, GoalScale));
		//魔導書作成
		auto MBGroup = st->CreateSharedObjectGroup(L"MagicBook");
		auto MPt = st->AddGameObject<MagicBook>(FirePos, Fire);
		MBGroup->IntoGroup(MPt);
		//アップデートグループ追加
		SUG->IntoGroup(MPt);
		//氷
		MPt = st->AddGameObject<MagicBook>(IceFogPos, IceFog);
		MBGroup->IntoGroup(MPt);
		//アップデートグループ追加
		SUG->IntoGroup(MPt);
		//風
		MPt = st->AddGameObject<MagicBook>(WindPos, Wind);
		MBGroup->IntoGroup(MPt);
		//アップデートグループ追加
		SUG->IntoGroup(MPt);


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
		//水門
		st->SetSharedGameObject(L"WaterGate",st->AddGameObject<Gimmick2_1>(Gimmick2_1WaterGatePos, Gimmick2_1WaterGateScale));
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
		//水門用グループ
		auto WaterGateGroup = st->CreateSharedObjectGroup(L"WaterCoreGate");
		auto Gimi3P = st->AddGameObject<Gimmick3>(WaterCore1Pos, WaterCore1Scale);
		//コアに関連する水を追加
		Gimi3P->SetWaters(Water1Vec);
		//魔法が当たるオブジェクトに設定
		MOG->IntoGroup(Gimi3P);
		//アップデートグループ追加
		SUG->IntoGroup(Gimi3P);
		WaterGateGroup->IntoGroup(Gimi3P);
		//以下同

		Gimi3P = st->AddGameObject<Gimmick3>(WaterCore2Pos, WaterCore2Scale);
		Gimi3P->SetWaters(Water2Vec);
		MOG->IntoGroup(Gimi3P);
		SUG->IntoGroup(Gimi3P);
		WaterGateGroup->IntoGroup(Gimi3P);


		Gimi3P = st->AddGameObject<Gimmick3>(WaterCore3Pos, WaterCore3Scale);
		Gimi3P->SetWaters(Water3Vec);
		MOG->IntoGroup(Gimi3P);
		SUG->IntoGroup(Gimi3P);
		WaterGateGroup->IntoGroup(Gimi3P);


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