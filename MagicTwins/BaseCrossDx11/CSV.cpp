
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
		//地面
		vector<Vector3> PlanePos;
		vector<Vector3> PlaneScale;
		vector<Vector3> PlaneRot;
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
		vector<Vector3> Enemy1pos;
		vector<Vector3> Enemy1Scale;
		vector<Vector3> Enemy2pos;
		vector<Vector3> Enemy2Scale;
		//突撃エネミー
		vector<Vector3> EnemyRush1pos;
		vector<Vector3> EnemyRush1Scale;
		vector<Vector3> EnemyRush2pos;
		vector<Vector3> EnemyRush2Scale;
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
		//滝 とりあえず3こ分用意
		vector<Vector3> WaterFall1Pos;
		vector<Vector3> WaterFall1Scale;
		vector<Vector3> WaterFall2Pos;
		vector<Vector3> WaterFall2Scale;
		vector<Vector3> WaterFall3Pos;
		vector<Vector3> WaterFall3Scale;


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
			//床
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
			if (StageMapVec[0] == L"Enemy1")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Enemy1pos.push_back(pos);
				Enemy1Scale.push_back(scale);
			}
			//エネミー
			if (StageMapVec[0] == L"Enemy2")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				Enemy2pos.push_back(pos);
				Enemy2Scale.push_back(scale);
			}
			//突撃エネミー
			if (StageMapVec[0] == L"EnemyRush1")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				EnemyRush1pos.push_back(pos);
				EnemyRush1Scale.push_back(scale);
			}
			if (StageMapVec[0] == L"EnemRush2")
			{
				Flgg = true;
				Vector3 pos = Vector3(_wtof(StageMapVec[1].c_str()), _wtof(StageMapVec[2].c_str()), _wtof(StageMapVec[3].c_str()));
				Vector3 scale = Vector3(_wtof(StageMapVec[4].c_str()), _wtof(StageMapVec[5].c_str()), _wtof(StageMapVec[6].c_str()));
				EnemyRush2pos.push_back(pos);
				EnemyRush2Scale.push_back(scale);
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

		//エフェクトグループ
		auto EfGroup = GetStage()->CreateSharedObjectGroup(L"Effect");
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
		for (auto v : PlanePos)
		{
			//スケールと回転は別で持ってくる
			Vector3 scale = PlaneScale[count];
			Vector3 rot = PlaneRot[count];
			st->AddGameObject<PlaneP>(v, scale, rot);
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
			//エフェクト
			vector<shared_ptr<MagicParticle>> Parti;
			auto mPobj = st->AddGameObject<MagicParticle>();
			//Vector3 InitPos, Vector3 RandPos, Vector3 Velo, Vector3 RandVelo, Vector3 scale, wstring TextureName, bool DeleteFlg, float CreateInterval, int layer,deleteTime
			mPobj->OnParticle(v, Vector3(1.0f, 0, 1.0f), Vector3(0, 0.0f, 0), Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), L"LIGHT_TX", true, 0.2f, 1, 2.0f);
			EfGroup->IntoGroup(mPobj);
			Parti.push_back(mPobj);
			//2個目
			mPobj = st->AddGameObject<MagicParticle>();
			mPobj->OnParticle(v, Vector3(1.0f, 0, 1.0f), Vector3(0, 0.0f, 0), Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), L"LIGHT_TX", true, 0.2f, 1, 1.0f);
			EfGroup->IntoGroup(mPobj);
			Parti.push_back(mPobj);

			Ptr->SetParticle(Parti);
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
		for (auto v : Enemy1pos)
		{
			//スケールは別で持ってくる
			Vector3 scale = Enemy1Scale[count];
			auto EPt = st->AddGameObject<Enemy>(v, scale,1);
			EG->IntoGroup(EPt);
			MOG->IntoGroup(EPt);
			//アップデートグループ追加
			SUG->IntoGroup(EPt);
			count++;
		}
		count = 0;
		for (auto v : Enemy2pos)
		{
			//スケールは別で持ってくる
			Vector3 scale = Enemy2Scale[count];
			auto EPt = st->AddGameObject<Enemy>(v, scale, 2);
			EG->IntoGroup(EPt);
			MOG->IntoGroup(EPt);
			//アップデートグループ追加
			SUG->IntoGroup(EPt);
			count++;
		}
		count = 0;

		//突撃エネミー作成
		//auto EG = GetStage()->CreateSharedObjectGroup(L"Enemy");	//いらぬ
		for (auto v : EnemyRush1pos)
		{
			//スケールは別で持ってくる
			Vector3 scale = EnemyRush1Scale[count];
			auto EPt = st->AddGameObject<EnemyRush>(v, scale, 1);
			EG->IntoGroup(EPt);
			MOG->IntoGroup(EPt);
			//アップデートグループ追加
			SUG->IntoGroup(EPt);
			count++;
		}
		count = 0;
		for (auto v : EnemyRush2pos)
		{
			//スケールは別で持ってくる
			Vector3 scale = EnemyRush2Scale[count];
			auto EPt = st->AddGameObject<EnemyRush>(v, scale, 2);
			EG->IntoGroup(EPt);
			MOG->IntoGroup(EPt);
			//アップデートグループ追加
			SUG->IntoGroup(EPt);
			count++;
		}
		count = 0;


		//ゴール作成
		st->SetSharedGameObject(L"Goal",st->AddGameObject<Goal>(GoalPos, GoalScale));
		auto mPobj = st->AddGameObject<MagicParticle>();
		//Vector3 InitPos, Vector3 RandPos, Vector3 Velo, Vector3 RandVelo, Vector3 scale, wstring TextureName, bool DeleteFlg, float CreateInterval, int layer,deleteTime
		mPobj->OnParticle(GoalPos, Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(0.5f, 0.5f, 0.5f), Vector3(1.0f, 1.0f, 1.0f), L"LIGHT_TX", false, 0.2f, 1, 2.0f);


		//魔導書作成
		auto MBGroup = st->CreateSharedObjectGroup(L"MagicBook");
		if (FirePos != Vector3(0,0,0))
		{
			auto MPt = st->AddGameObject<MagicBook>(FirePos, Fire);
			MBGroup->IntoGroup(MPt);
			//アップデートグループ追加
			SUG->IntoGroup(MPt);

			//2個作るエフェクト
			for (int i = 0; i < 2; i++)
			{
				auto mPobj = st->AddGameObject<MagicParticle>();
				//Vector3 InitPos, Vector3 RandPos, Vector3 Velo, Vector3 RandVelo, Vector3 scale, wstring TextureName, bool DeleteFlg, float CreateInterval, int layer,deleteTime
				mPobj->OnParticle(FirePos, Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(0.5f, 0.5f, 0.5f), Vector3(1.0f, 1.0f, 1.0f), L"FIRELIGHT_TX", false, 0.4f, 1, 2.0f);
				EfGroup->IntoGroup(mPobj);
			}

		}
		//氷
		if (IceFogPos != Vector3(0, 0, 0))
		{
			auto MPt = st->AddGameObject<MagicBook>(IceFogPos, IceFog);
			MBGroup->IntoGroup(MPt);
			//アップデートグループ追加
			SUG->IntoGroup(MPt);
			//2個作るエフェクト
			for (int i = 0; i < 2; i++)
			{
				auto mPobj = st->AddGameObject<MagicParticle>();
				//Vector3 InitPos, Vector3 RandPos, Vector3 Velo, Vector3 RandVelo, Vector3 scale, wstring TextureName, bool DeleteFlg, float CreateInterval, int layer,deleteTime
				mPobj->OnParticle(IceFogPos, Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(0.5f, 0.5f, 0.5f), Vector3(1.0f, 1.0f, 1.0f), L"ICELIGHT_TX", false, 0.4f, 1, 2.0f);
				EfGroup->IntoGroup(mPobj);
			}
		}
		//風
		if (WindPos != Vector3(0, 0, 0))
		{
			auto MPt = st->AddGameObject<MagicBook>(WindPos, Wind);
			MBGroup->IntoGroup(MPt);
			//アップデートグループ追加
			SUG->IntoGroup(MPt);

			//2個作るエフェクト
			for (int i = 0; i < 2; i++)
			{
				auto mPobj = st->AddGameObject<MagicParticle>();
				//Vector3 InitPos, Vector3 RandPos, Vector3 Velo, Vector3 RandVelo, Vector3 scale, wstring TextureName, bool DeleteFlg, float CreateInterval, int layer,deleteTime
				mPobj->OnParticle(WindPos, Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(0.5f, 0.5f, 0.5f), Vector3(1.0f, 1.0f, 1.0f), L"WINDLIGHT_TX", false, 0.4f, 1, 2.0f);
				EfGroup->IntoGroup(mPobj);
			}

		}

		//ギミック作成
		//1
		for (auto v : Gimmick1IcePos)
		{
			Vector3 scale = Gimmick1IceScale[count];
			auto obj = st->AddGameObject<Gimmick1>(v, scale);
			MOG->IntoGroup(obj);
			count++;

			//エフェクト
			auto mPobj = st->AddGameObject<MagicParticle>();
			//Vector3 InitPos, Vector3 RandPos, Vector3 Velo, Vector3 RandVelo, Vector3 scale, wstring TextureName, bool DeleteFlg, float CreateInterval, int layer,deleteTime
			mPobj->OnParticle(v, Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(1.0f, 0.5f, 1.0f), Vector3(2.0f, 2.0f,2.0f), L"FIRELIGHT_TX", false, 0.2f, 1, 2.0f);
			EfGroup->IntoGroup(mPobj);

			obj->SetParticle(mPobj);
		}
		count = 0;
		//2
		for (auto v : Gimmick2WindMillPos)
		{
			Vector3 scale = Gimmick2WindMillScale[count];
			auto obj = st->AddGameObject<Gimmick2>(v, scale);
			MOG->IntoGroup(obj);
			count++;

			//エフェクト
			auto mPobj = st->AddGameObject<MagicParticle>();
			//Vector3 InitPos, Vector3 RandPos, Vector3 Velo, Vector3 RandVelo, Vector3 scale, wstring TextureName, bool DeleteFlg, float CreateInterval, int layer,deleteTime
			mPobj->OnParticle(v, Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(1.0f, 0.5f, 1.0f), Vector3(2.0f, 2.0f, 2.0f), L"FIRELIGHT_TX", false, 0.2f, 1, 2.0f);
			EfGroup->IntoGroup(mPobj);

			obj->SetParticle(mPobj);

			mPobj = st->AddGameObject<MagicParticle>();
			//Vector3 InitPos, Vector3 RandPos, Vector3 Velo, Vector3 RandVelo, Vector3 scale, wstring TextureName, bool DeleteFlg, float CreateInterval, int layer,deleteTime
			mPobj->OnParticle(v, Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(1.0f, 0.5f, 1.0f), Vector3(2.0f, 2.0f, 2.0f), L"WINDLIGHT_TX", false, 0.2f, 1, 2.0f);
			EfGroup->IntoGroup(mPobj);

			obj->SetParticle(mPobj);

		}
		count = 0;
		//水門
		auto waterGate = st->AddGameObject<Gimmick2_1>(Gimmick2_1WaterGatePos, Gimmick2_1WaterGateScale);
		st->SetSharedGameObject(L"WaterGate",waterGate);
		SUG->IntoGroup(waterGate);
		
		//5
		for (auto v : Gimmick5FirePos)
		{
			Vector3 scale = Gimmick5FireScale[count];
			auto obj = st->AddGameObject<Gimmick5>(v, scale);
			MOG->IntoGroup(obj);
			count++;
			//エフェクト
			auto mPobj = st->AddGameObject<MagicParticle>();
			//Vector3 InitPos, Vector3 RandPos, Vector3 Velo, Vector3 RandVelo, Vector3 scale, wstring TextureName, bool DeleteFlg, float CreateInterval, int layer,deleteTime
			mPobj->OnParticle(v, Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(1.0f, 0.5f, 1.0f), Vector3(2.0f, 2.0f, 2.0f), L"ICELIGHT_TX", false, 0.2f, 1, 2.0f);
			EfGroup->IntoGroup(mPobj);

			obj->SetParticle(mPobj);
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

		//滝
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

			//エフェクト(凍っていない時)
			auto mPobj = st->AddGameObject<MagicParticle>();
			//Vector3 InitPos, Vector3 RandPos, Vector3 Velo, Vector3 RandVelo, Vector3 scale, wstring TextureName, bool DeleteFlg, float CreateInterval, int layer,deleteTime
			mPobj->OnParticle(v, Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(1.0f, 0.5f, 1.0f), Vector3(2.0f, 2.0f, 2.0f), L"ICELIGHT_TX", false, 0.2f, 1, 2.0f);
			EfGroup->IntoGroup(mPobj);
			waP->SetParticleIce(mPobj);

			//エフェクト(凍ってる時)
			mPobj = st->AddGameObject<MagicParticle>();
			//Vector3 InitPos, Vector3 RandPos, Vector3 Velo, Vector3 RandVelo, Vector3 scale, wstring TextureName, bool DeleteFlg, float CreateInterval, int layer,deleteTime
			//mPobj->OnParticle(v, Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(1.0f, 0.5f, 1.0f), Vector3(3.0f, 3.0f, 3.0f), L"FIRELIGHT_TX", false, 0.2f, 1, 2.0f);
			EfGroup->IntoGroup(mPobj);
			waP->SetParticleFire(mPobj);

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
		//水門用グループ
		auto WaterGateGroup = st->CreateSharedObjectGroup(L"WaterCoreGate");
		auto WaterCoreGroup = st->CreateSharedObjectGroup(L"WaterCore");

		for (auto v : WaterCore1Pos)
		{
			Vector3 scale = WaterCore1Scale[count];
			auto Gimi3P = st->AddGameObject<Gimmick3>(v, scale);
			//コアに関連する水を追加
			Gimi3P->SetWaters(Water1Vec);
			Gimi3P->SetWaterFalls(WaterFall1Vec);
			//魔法が当たるオブジェクトに設定
			MOG->IntoGroup(Gimi3P);
			//アップデートグループ追加
			SUG->IntoGroup(Gimi3P);
			WaterGateGroup->IntoGroup(Gimi3P);
			WaterCoreGroup->IntoGroup(Gimi3P);
			count++;

			//エフェクト(凍っていない時)
			auto mPobj = st->AddGameObject<MagicParticle>();
			//Vector3 InitPos, Vector3 RandPos, Vector3 Velo, Vector3 RandVelo, Vector3 scale, wstring TextureName, bool DeleteFlg, float CreateInterval, int layer,deleteTime
			mPobj->OnParticle(v, Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(1.0f, 0.5f, 1.0f), Vector3(2.0f, 2.0f, 2.0f), L"ICELIGHT_TX", false, 0.2f, 1, 2.0f);
			EfGroup->IntoGroup(mPobj);
			Gimi3P->SetParticleIce(mPobj);

			//エフェクト(凍ってる時)
			mPobj = st->AddGameObject<MagicParticle>();
			//Vector3 InitPos, Vector3 RandPos, Vector3 Velo, Vector3 RandVelo, Vector3 scale, wstring TextureName, bool DeleteFlg, float CreateInterval, int layer,deleteTime
			//mPobj->OnParticle(v, Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(1.0f, 0.5f, 1.0f), Vector3(3.0f, 3.0f, 3.0f), L"FIRELIGHT_TX", false, 0.2f, 1, 2.0f);
			EfGroup->IntoGroup(mPobj);
			Gimi3P->SetParticleFire(mPobj);

		}
		count = 0;
		for (auto v : WaterCore2Pos)
		{
			Vector3 scale = WaterCore2Scale[count];
			auto Gimi3P = st->AddGameObject<Gimmick3>(v, scale);
			//コアに関連する水を追加
			Gimi3P->SetWaters(Water2Vec);
			Gimi3P->SetWaterFalls(WaterFall2Vec);
			//魔法が当たるオブジェクトに設定
			MOG->IntoGroup(Gimi3P);
			//アップデートグループ追加
			SUG->IntoGroup(Gimi3P);
			WaterGateGroup->IntoGroup(Gimi3P);
			WaterCoreGroup->IntoGroup(Gimi3P);
			count++;

			//エフェクト(凍っていない時)
			auto mPobj = st->AddGameObject<MagicParticle>();
			//Vector3 InitPos, Vector3 RandPos, Vector3 Velo, Vector3 RandVelo, Vector3 scale, wstring TextureName, bool DeleteFlg, float CreateInterval, int layer,deleteTime
			mPobj->OnParticle(v, Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(1.0f, 0.5f, 1.0f), Vector3(2.0f, 2.0f, 2.0f), L"ICELIGHT_TX", false, 0.2f, 1, 2.0f);
			EfGroup->IntoGroup(mPobj);
			Gimi3P->SetParticleIce(mPobj);

			//エフェクト(凍ってる時)
			mPobj = st->AddGameObject<MagicParticle>();
			//Vector3 InitPos, Vector3 RandPos, Vector3 Velo, Vector3 RandVelo, Vector3 scale, wstring TextureName, bool DeleteFlg, float CreateInterval, int layer,deleteTime
			//mPobj->OnParticle(v, Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(1.0f, 0.5f, 1.0f), Vector3(3.0f, 3.0f, 3.0f), L"FIRELIGHT_TX", false, 0.2f, 1, 2.0f);
			EfGroup->IntoGroup(mPobj);
			Gimi3P->SetParticleFire(mPobj);

		}
		count = 0;

		for (auto v : WaterCore3Pos)
		{
			Vector3 scale = WaterCore3Scale[count];
			auto Gimi3P = st->AddGameObject<Gimmick3>(v, scale);
			//コアに関連する水を追加
			Gimi3P->SetWaters(Water3Vec);
			Gimi3P->SetWaterFalls(WaterFall3Vec);
			//魔法が当たるオブジェクトに設定
			MOG->IntoGroup(Gimi3P);
			//アップデートグループ追加
			SUG->IntoGroup(Gimi3P);
			WaterGateGroup->IntoGroup(Gimi3P);
			WaterCoreGroup->IntoGroup(Gimi3P);
			count++;

			//エフェクト(凍っていない時)
			auto mPobj = st->AddGameObject<MagicParticle>();
			//Vector3 InitPos, Vector3 RandPos, Vector3 Velo, Vector3 RandVelo, Vector3 scale, wstring TextureName, bool DeleteFlg, float CreateInterval, int layer,deleteTime
			mPobj->OnParticle(v, Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(1.0f, 0.5f, 1.0f), Vector3(2.0f, 2.0f, 2.0f), L"ICELIGHT_TX", false, 0.2f, 1, 2.0f);
			EfGroup->IntoGroup(mPobj);
			Gimi3P->SetParticleIce(mPobj);

			//エフェクト(凍ってる時)
			mPobj = st->AddGameObject<MagicParticle>();
			//Vector3 InitPos, Vector3 RandPos, Vector3 Velo, Vector3 RandVelo, Vector3 scale, wstring TextureName, bool DeleteFlg, float CreateInterval, int layer,deleteTime
			//mPobj->OnParticle(v, Vector3(1.0f, 0, 1.0f), Vector3(0, 1.0f, 0), Vector3(1.0f, 0.5f, 1.0f), Vector3(3.0f, 3.0f, 3.0f), L"FIRELIGHT_TX", false, 0.2f, 1, 2.0f);
			EfGroup->IntoGroup(mPobj);
			Gimi3P->SetParticleFire(mPobj);

		}
		count = 0;

		/*
		auto Gimi3P = st->AddGameObject<Gimmick3>(WaterCore1Pos, WaterCore1Scale);
		//コアに関連する水を追加
		Gimi3P->SetWaters(Water1Vec);
		//魔法が当たるオブジェクトに設定
		MOG->IntoGroup(Gimi3P);
		//アップデートグループ追加
		SUG->IntoGroup(Gimi3P);
		WaterGateGroup->IntoGroup(Gimi3P);
		//以下同
		*/
		/*
		//3の２
		auto Gimi3P = st->AddGameObject<Gimmick3>(WaterCore2Pos, WaterCore2Scale);
		Gimi3P->SetWaters(Water2Vec);
		MOG->IntoGroup(Gimi3P);
		SUG->IntoGroup(Gimi3P);
		WaterGateGroup->IntoGroup(Gimi3P);

		//3の3
		Gimi3P = st->AddGameObject<Gimmick3>(WaterCore3Pos, WaterCore3Scale);
		Gimi3P->SetWaters(Water3Vec);
		MOG->IntoGroup(Gimi3P);
		SUG->IntoGroup(Gimi3P);
		WaterGateGroup->IntoGroup(Gimi3P);
		*/

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