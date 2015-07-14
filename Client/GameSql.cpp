#include "GameSql.h"
#include "GameData.h"

namespace Ogre
{
DBMsgHandler_Callback GameSql::m_pDBMsgHandlerCallbacks[EDBO_MAX] = { NULL,};

#define OpenGameSql(name)\
{\
  gEnv->mDataBase->open(name);\
}

#define CloseGameSql()\
{\
  gEnv->mDataBase->close();\
}

  GameSql::GameSql()
  {
    OpenGameSql("./CatchFish.s3db");
    // 暂时不用异步
    //InitDBMsgHandlerCallBack();
  }

  GameSql::~GameSql()
  {
    CloseGameSql();
  }

  void GameSql::InitDBMsgHandlerCallBack()
  {
    
  }

  void GameSql::HandlerDBMsg(int MsgType, const String& str)
  {
    if((m_pDBMsgHandlerCallbacks[MsgType] && MsgType< EDBO_MAX))
    {
      (this->*m_pDBMsgHandlerCallbacks[MsgType])(str);
    }
    else
    {
      printf(("[DBMsgHandlerCallbacks] Can't Find The MsgType[%d]! In Function: %s"), MsgType, __FUNCTION__);
    }
  }

  void GameSql::UpdateGameLevel(const String& str)
  {
		String strSql ="Update GameInfoTable Set GameLevel = " + str;
		ExcuteGameSql(strSql);
  }

  void GameSql::UpdateMaxBet(const String& str)
  {
    String strSql = "Update GameInfoTable Set MaxBet = " + str;
    ExcuteGameSql(strSql);
  }

  void GameSql::UpdateMinBet(const String& str)
  {
    String strSql = "Update GameInfoTable Set MinBet = " + str;
    ExcuteGameSql(strSql);
  }

  void GameSql::UpdateUpRatio(const String& str)
  {
    String strSql = "Update GameInfoTable Set UpRatio = " + str;
    ExcuteGameSql(strSql);
  }

  void GameSql::UpdateDownRatio(const String& str)
  {
    String strSql = "Update GameInfoTable Set DownRatio = " + str;
    ExcuteGameSql(strSql);
  }

  void GameSql::UpdateTicketRatio(const String& str)
  {
    String strSql = "Update GameInfoTable Set TicketRatio = " + str;
    ExcuteGameSql(strSql);
  }

  void GameSql::UpdateUpLimit(const String& str)
  {
    String strSql = "Update GameInfoTable Set UpLimit = " + str;
    ExcuteGameSql(strSql);
  }

  void GameSql::UpdateBurstSocre(const String& str)
  {
    String strSql = "Update GameInfoTable Set BurstSocre = " + str;
    ExcuteGameSql(strSql);
  }

  void GameSql::UpdateBusinessMode(const String& str)
  {
    String strSql = "Update GameInfoTable Set BusinessMode = " + str;
    ExcuteGameSql(strSql);
  }

  void GameSql::UpdateOutCoinFunction(const String& str)
  {
    String strSql = "Update GameInfoTable Set OutCoinFunction = " + str;
    ExcuteGameSql(strSql);
  }

  void GameSql::UpdateUpDownFunction(const String& str)
  {
    String strSql = "Update GameInfoTable Set UpDownFunction = " + str;
    ExcuteGameSql(strSql);
  }

  void GameSql::UpdateMusicBg(const String& str)
  {
    String strSql = "Update GameInfoTable Set MusicBg = " + str;
    ExcuteGameSql(strSql);
  }

  void GameSql::UpdateVoice(const String& str)
  {
    String strSql = "Update GameInfoTable Set Voice = " + str;
    ExcuteGameSql(strSql);
  }

  void GameSql::UpdateMachineType(const String& str)
  {
    String strSql = "Update GameInfoTable Set MachineType = " + str;
    ExcuteGameSql(strSql);
  }

  void GameSql::UpdatePlayersData(const String& str)
  {
	  String strSql = "Update ConsumerTable Set " + str;
	  ExcuteGameSql(strSql);
  }

  void GameSql::UpdateGameParamSetData(const String& str)
  {
	  String strSql = "Update GameInfoTable Set " + str;
	  ExcuteGameSql(strSql);
  }

  bool GameSql::UpdateDeCodeAdjustData(const String& str)
  {
	  String strSql = "Update DeCodeAdjustTable Set " + str;
	  return ExcuteGameSql(strSql);
  }

  bool GameSql::UpdateMachineNo(const String& str)
  {
	  String strSql = "Update MachineTable Set MachineNo = " + str;
	  return ExcuteGameSql(strSql);
  }

  bool GameSql::UpdateMiMa(const String& str)
  {
	  String strSql = "Update MachineTable Set MiMa = " + str;
	  return ExcuteGameSql(strSql);
  }

  void GameSql::UpdatePlayerData(const String& str)
  {
    String strSql = "Update ConsumerTable " + str;
    ExcuteGameSql(strSql);
  }

  bool GameSql::UpdateTotalProfit(const String& str)
  {
    String strSql = "Update BillTable Set TotalProfit = " + str;
    return ExcuteGameSql(strSql);
  }

  bool GameSql::UpdatePreProfit(const String& str)
  {
    String strSql = "Update BillTable Set PreProfit = " + str;
    return ExcuteGameSql(strSql);
  }

  bool GameSql::UpdateCurProfit(const String& str)
  {
		String strSql = "Update BillTable Set CurrentProfit = " + str;
		return ExcuteGameSql(strSql);
  }

  bool GameSql::UpdateUpPoints(const String& str)
  {
    String strSql = "Update BillTable Set UpPoints = " + str;
    return ExcuteGameSql(strSql);
  }

  bool GameSql::UpdateDownPoints(const String& str)
  {
    String strSql = "Update BillTable Set DownPoints = " + str;
    return ExcuteGameSql(strSql);
  }

  bool GameSql::UpdateInCoins(const String& str)
  {
    String strSql = "Update BillTable Set InCoins = " + str;
    return ExcuteGameSql(strSql);
  }

  bool GameSql::UpdateOutCoins(const String& str)
  {
    String strSql = "Update BillTable Set OutCoins = " + str;
   return  ExcuteGameSql(strSql);
  }

  bool GameSql::UpdateRaffleTickets(const String& str)
  {
    String strSql = "Update BillTable Set RaffleTickets = " + str;
    return ExcuteGameSql(strSql);
  }

  bool GameSql::UpdatePostCodeCount(const String& str)
  {
    String strSql = "Update BillTable Set PostCodeCount = " + str;
    return ExcuteGameSql(strSql);
  }

  IDataBaseTable* GameSql::GetBusinessMode()
  {
    return gEnv->mDataBase->query( "Select ModeID, ModeDesc From BusinessModeTable" );
  }

  IDataBaseTable* GameSql::GetBrustSocre()
  {
    return gEnv->mDataBase->query( "Select LevelID, BrustSocre From BrustSocreTable" );
  }

  IDataBaseTable* GameSql::GetDownRatio()
  {
    return gEnv->mDataBase->query( "Select LevelID, DownRatio From DownRatioTable" );
  }

  IDataBaseTable* GameSql::GetGameLevel()
  {
    return gEnv->mDataBase->query( "Select LevelID, LevelDesc From GameLevelTable" );
  }

  IDataBaseTable* GameSql::GetInCoinsRatio()
  {
    return gEnv->mDataBase->query( "Select LevelID, InCoinsRatio From InCoinsRatioTable" );
  }

  IDataBaseTable* GameSql::GetMachineData()
  {
    return gEnv->mDataBase->query( "Select ID, LineNo, MachineNo From MachineTable" );
  }

  IDataBaseTable* GameSql::GetMachineType()
  {
    return gEnv->mDataBase->query( "Select TypeID, TypeDesc From MachineTypeTable" );
  }

  IDataBaseTable* GameSql::GetMaxBetData()
  {
    return gEnv->mDataBase->query( "Select LevelID, BetRatio From MaxBetTable" );
  }

  IDataBaseTable* GameSql::GetMinBetData()
  {
    return gEnv->mDataBase->query( "Select LevelID, BetRatio From MinBetTable" );
  }

  IDataBaseTable* GameSql::GetMinChangeData()
  {
    return gEnv->mDataBase->query( "Select LevelID, ChangeRatio From MinChangeTable" );
  }

  IDataBaseTable* GameSql::GetTicketRatio()
  {
    return gEnv->mDataBase->query( "Select LevelID, TicketRatio From TicketRatioTable" );
  }

  IDataBaseTable* GameSql::GetUpLimitData()
  {
    return gEnv->mDataBase->query( "Select LevelID, UpLimit From UpLimitTable" );
  }

  IDataBaseTable* GameSql::GetUpRatioData()
  {
    return gEnv->mDataBase->query( "Select LevelID, UpRatio From UpRatioTable" );
  }

  IDataBaseTable* GameSql::GetUpDownFenData()
  {
	  return gEnv->mDataBase->query( "Select LevelID, desc From UpDownFunctionTable" );
  }

  IDataBaseTable* GameSql::GetSceneBackData()
  {
	  return gEnv->mDataBase->query( "Select LevelID, SceneDesc, SceneID From SceneTypeTable" );
  }

  IDataBaseTable* GameSql::GetPostCodeDaysData()
  {
	  return gEnv->mDataBase->query( "Select LevelID, DaysDesc From PostCodeDaysTable" );
  }

  IDataBaseTable* GameSql::GetViewCheckAccountTop()
  {
    return gEnv->mDataBase->query( "Select InCoinsRatio, ModeDesc, TicketRatio From View_CheckAccountTop" );
  }

  IDataBaseTable* GameSql::GetCheckAccountData()
  {
    return gEnv->mDataBase->query(
      "Select TotalProfit, PreProfit, UpPoints, DownPoints, InCoins, OutCoins, RaffleTickets, PostCodeCount, CurrentProfit From BillTable");
  }

  IDataBaseTable* GameSql::GetPostMessageData()
  {
    return gEnv->mDataBase->query(
      "Select TotalProfit, CurrentProfit, PostCodeCount, MachineNo From View_PostMoneyMiddleData");
  }

  IDataBaseTable* GameSql::GetViewParamSettingData()
  {
    String sql = "Select LevelDesc, MaxBetRatio, MinBetRatio, ChangeRatio, UpRatio, DownRatio, UpLimit, BrustSocre, OutCoinFunction,";
    sql += "desc, MusicBg, Voice, SceneDesc, TypeDesc, MachineType, InCoinsRatio, ModeDesc, TicketRatio From View_ParamSetting";
    return gEnv->mDataBase->query(sql);
  }

  IDataBaseTable* GameSql::GetViewDeCodeAdjustData()
  {
    String sql = "Select InCoinsRatio, PostCodeTips, DaysDesc, SceneDesc, PostCodeOnOff From View_DeCodeAdjust";
    return gEnv->mDataBase->query(sql);
  }

  IDataBaseTable* GameSql::GetViewSystemSettingData()
  {
    String sql = "Select LineNo, MachineNo, MiMa From MachineTable";
    return gEnv->mDataBase->query(sql);
  }

  IDataBaseTable* GameSql::GetDeCodeAdjustTableData()
  {
	  String sql = "Select PostCodeDays, PostCodeTips, PostCodeOnOff From DeCodeAdjustTable";
	  return gEnv->mDataBase->query(sql);
  }

  IDataBaseTable* GameSql::GetCurParamSettingByGame()
  {
	String sql = "Select GameLevel, MaxBet, MinBet, MinChange, UpRatio, DownRatio, UpLimit, BurstSocre, OutCoinFunction, UpDownFunction, ";
	sql += "MusicBg, Voice, SceneType, MachineType, InCoinsRatio, BusinessMode, TicketRatio  from  GameInfoTable";
	return gEnv->mDataBase->query(sql);
  }

  IDataBaseTable* GameSql::GetTotalProfit()
  {
	String sql = "Select TotalProfit From BillTable";
	return gEnv->mDataBase->query(sql);
  }

  IDataBaseTable* GameSql::GetPreProfit()
  {
	String sql = "Select PreProfit From BillTable";
	return gEnv->mDataBase->query(sql);
  }

  IDataBaseTable* GameSql::GetCurrentProfit()
  {
	String sql = "Select CurrentProfit From BillTable";
	return gEnv->mDataBase->query(sql);
  }

  IDataBaseTable* GameSql::GetTotalUpFen()
  {
	String sql = "Select UpPoints From BillTable";
	return gEnv->mDataBase->query(sql);
  }

  IDataBaseTable* GameSql::GetTotalDownFen()
  {
	String sql = "Select DownPoints From BillTable";
	return gEnv->mDataBase->query(sql);
  }

  IDataBaseTable* GameSql::GetTotalInCoinsNum()
  {
	String sql = "Select InCoins From BillTable";
	return gEnv->mDataBase->query(sql);
  }

  IDataBaseTable* GameSql::GetTotalOutCoinsNum()
  {
	String sql = "Select OutCoins From BillTable";
	return gEnv->mDataBase->query(sql);
  }

  IDataBaseTable* GameSql::GetTotalTicketNum()
  {
	String sql = "Select RaffleTickets From BillTable";
	return gEnv->mDataBase->query(sql);
  }

  IDataBaseTable* GameSql::GetTotalPostCodeNum()
  {
	  String sql = "Select PostCodeCount From BillTable";
	  return gEnv->mDataBase->query(sql);
  }

  IDataBaseTable* GameSql::GetCurPlayerDataById(int playerId)
  {
	  String sql = "Select CurrentPoints, CurrentGuns From ConsumerTable Where ConsumerID = " + StringConverter::toString(playerId);
	  return gEnv->mDataBase->query(sql);
  }

  bool GameSql::ExcuteGameSql(String strSql)
  {
    if (gEnv->mDataBase->execute(strSql))
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}