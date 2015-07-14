#include "GameData.h"
#include "GameEnvironment.h"

namespace Ogre
{
  GameData::GameData()
  {
    Initialize();
  }

  GameData::~GameData()
  {

  }

  void GameData::Initialize()
  {
    LoadCommonData();
  }

  void GameData::LoadCommonData()
  {
    if (gEnvGame.mGameSql)
    {
      _getBusinessMode();
      _getBrustSocre();
      _getDownRatio();
      _getGameLevel();
      _getInCoinsRatio();
      _getMachineData();
      _getMachineType();
      _getMaxBetData();
      _getMinBetData();
      _getMinChangeData();
      _getTicketRatio();
      _getUpLimitData();
      _getUpRatioData();
	  _getUpDownFenData();
	  _getPostCodeDaysData();
	  _getSceneBackData();
	  GetViewSystemSettingData();

	  /////// 为前台游戏提供 开始///////////
	  GetCurrentGameParmByGame();
	  /////// 为前台游戏提供 结束///////////
    }
  }

  void GameData::_getBusinessMode()
  {
    IDataBaseTable* table = gEnvGame.mGameSql->GetBusinessMode();
    if (table)
    {
      for (int iRow = 0; iRow< table->getRowCount(); ++iRow)
      {
        BusinessMode *pMode = new BusinessMode();
        pMode->m_iMode = table->toInt32( iRow, "ModeID" );
        pMode->m_strModeDesc = table->toString( iRow, "ModeDesc" );
        if (m_MapBusinessMode.find(pMode->m_iMode) == m_MapBusinessMode.end())
        {
          m_MapBusinessMode.insert(std::make_pair(pMode->m_iMode, pMode));
        }
      }
    }
  }

  void GameData::_getBrustSocre()
  {
    IDataBaseTable* table = gEnvGame.mGameSql->GetBrustSocre();
    if (table)
    {
      for (int iRow = 0; iRow< table->getRowCount(); ++iRow)
      {
        BrustScore *pBrustScore = new BrustScore();
        pBrustScore->m_iLevelID = table->toInt32(iRow, "LevelID");
        pBrustScore->m_strBrustSocre = table->toString(iRow, "BrustSocre");
        if (m_MapBrustScore.find(pBrustScore->m_iLevelID) == m_MapBrustScore.end())
        {
          m_MapBrustScore.insert(std::make_pair(pBrustScore->m_iLevelID, pBrustScore));
        }
      }
    }
  }

  void GameData::_getDownRatio()
  {
    IDataBaseTable* table = gEnvGame.mGameSql->GetDownRatio();
    if (table)
    {
      for (int iRow = 0; iRow< table->getRowCount(); ++iRow)
      {
        DownRatio *pDownRatio = new DownRatio();
        pDownRatio->m_iLevelID = table->toInt32(iRow, "LevelID");
        pDownRatio->m_strDownRatio = table->toString(iRow, "DownRatio") + "币";
		pDownRatio->m_iDownRatio = table->toInt64(iRow, "DownRatio");
        if (m_MapDownRatio.find(pDownRatio->m_iLevelID) == m_MapDownRatio.end())
        {
          m_MapDownRatio.insert(std::make_pair(pDownRatio->m_iLevelID, pDownRatio));
        }
      }
    }
  }

  void GameData::_getGameLevel()
  {
    IDataBaseTable* table = gEnvGame.mGameSql->GetGameLevel();
    if (table)
    {
      for (int iRow = 0; iRow< table->getRowCount(); ++iRow)
      {
        GameLevel *pGameLevel = new GameLevel();
        pGameLevel->m_iLevelID = table->toInt32(iRow, "LevelID");
        pGameLevel->m_strLevelDesc = table->toString(iRow, "LevelDesc");
        if (m_MapGameLevel.find(pGameLevel->m_iLevelID) == m_MapGameLevel.end())
        {
          m_MapGameLevel.insert(std::make_pair(pGameLevel->m_iLevelID, pGameLevel));
        }
      }
    }

  }

  void GameData::_getInCoinsRatio()
  {
    IDataBaseTable* table = gEnvGame.mGameSql->GetInCoinsRatio();
    if (table)
    {
      for (int iRow = 0; iRow< table->getRowCount(); ++iRow)
      {
        InCoinsRatio *pInCoinsRatio = new InCoinsRatio();
        pInCoinsRatio->m_iLevelID = table->toInt32(iRow, "LevelID");
		pInCoinsRatio->m_iInCoinsRatio = table->toInt64(iRow, "InCoinsRatio");
		pInCoinsRatio->m_strInCoinsRatio = "1:" + table->toString(iRow, "InCoinsRatio") + "分";
        if (m_MapInCoinsRatio.find(pInCoinsRatio->m_iLevelID) == m_MapInCoinsRatio.end())
        {
          m_MapInCoinsRatio.insert(std::make_pair(pInCoinsRatio->m_iLevelID, pInCoinsRatio));
        }
      }
    }
  }

  void GameData::_getMachineData()
  {
    IDataBaseTable *table = gEnvGame.mGameSql->GetMachineData();
    if (table)
    {
      for (int iRow = 0; iRow< table->getRowCount(); ++iRow)
      {
        MachineData *pMachineData = new MachineData();
        pMachineData->m_iID = table->toInt32(iRow, "ID");
        pMachineData->m_strLineNo = table->toString(iRow, "LineNo");
        pMachineData->m_strMachineNo = table->toString(iRow, "MachineNo");
        if (m_MapMachineData.find(pMachineData->m_iID) == m_MapMachineData.end())
        {
          m_MapMachineData.insert(std::make_pair(pMachineData->m_iID, pMachineData));
        }
      }
    }
  }

  void GameData::_getMachineType()
  {
    IDataBaseTable *table = gEnvGame.mGameSql->GetMachineType();
    if (table)
    {
      for (int iRow = 0; iRow< table->getRowCount(); ++iRow)
      {
        MachineType *pMachineType = new MachineType();
        pMachineType->m_iTypeID = table->toInt32(iRow, "TypeID");
        pMachineType->m_strTypeDesc = table->toString(iRow, "TypeDesc");
        if (m_MapMachineType.find(pMachineType->m_iTypeID) == m_MapMachineType.end())
        {
          m_MapMachineType.insert(std::make_pair(pMachineType->m_iTypeID, pMachineType));
        }
      }
    }
  }

  void GameData::_getMaxBetData()
  {
    IDataBaseTable *table = gEnvGame.mGameSql->GetMaxBetData();
    if (table)
    {
      for (int iRow = 0; iRow< table->getRowCount(); ++iRow)
      {
        MaxBetData *pMaxBetData = new MaxBetData();
        pMaxBetData->m_iLevelID = table->toInt32(iRow, "LevelID");
        pMaxBetData->m_strBetRatio = table->toString(iRow, "BetRatio");
        if (m_MapMaxBetData.find(pMaxBetData->m_iLevelID) == m_MapMaxBetData.end())
        {
          m_MapMaxBetData.insert(std::make_pair(pMaxBetData->m_iLevelID, pMaxBetData));
        }
      }
    }
  }

  void GameData::_getMinBetData()
  {
    IDataBaseTable* table = gEnvGame.mGameSql->GetMinBetData();
    if (table)
    {
      for (int iRow = 0; iRow< table->getRowCount(); ++iRow)
      {
        MinBetData *pMinBetData = new MinBetData();
        pMinBetData->m_iLevelID = table->toInt32(iRow, "LevelID");
        pMinBetData->m_strBetRatio = table->toString(iRow, "BetRatio");
        if (m_MapMinBetData.find(pMinBetData->m_iLevelID) == m_MapMinBetData.end())
        {
          m_MapMinBetData.insert(std::make_pair(pMinBetData->m_iLevelID, pMinBetData));
        }
      }
    }
  }

  void GameData::_getMinChangeData()
  {
    IDataBaseTable *table = gEnvGame.mGameSql->GetMinChangeData();
    if (table)
    {
      for (int iRow = 0; iRow< table->getRowCount(); ++iRow)
      {
        MinChangeData *pMinChangeData = new MinChangeData();
        pMinChangeData->m_iLevelID = table->toInt32(iRow, "LevelID");
        pMinChangeData->m_strChangeRatio = table->toString(iRow, "ChangeRatio");
        if (m_MapMinChangeData.find(pMinChangeData->m_iLevelID) == m_MapMinChangeData.end())
        {
          m_MapMinChangeData.insert(std::make_pair(pMinChangeData->m_iLevelID, pMinChangeData));
        }
      }
    }
  }

  void GameData::_getTicketRatio()
  {
    IDataBaseTable *table = gEnvGame.mGameSql->GetTicketRatio();
    if (table)
    {
      for (int iRow = 0; iRow< table->getRowCount(); ++iRow)
      {
        TicketRatio *pTicketRatio = new TicketRatio();
        pTicketRatio->m_iLevelID = table->toInt32(iRow, "LevelID");
        //pTicketRatio->m_strTicketRatio = table->toString(iRow, "TicketRatio");
		pTicketRatio->m_strTicketRatio = "1币" + table->toString(iRow, "TicketRatio") + "彩票";
		pTicketRatio->m_iTicketRatio = table->toInt64(iRow, "TicketRatio");
        if (m_MapTicketRatio.find(pTicketRatio->m_iLevelID) == m_MapTicketRatio.end())
        {
          m_MapTicketRatio.insert(std::make_pair(pTicketRatio->m_iLevelID, pTicketRatio));
        }
      }
    }
  }

  void GameData::_getUpLimitData()
  {
    IDataBaseTable *table = gEnvGame.mGameSql->GetUpLimitData();
    if (table)
    {
      for (int iRow = 0; iRow< table->getRowCount(); ++iRow)
      {
        UpLimitData *pUpLimitData = new UpLimitData();
        pUpLimitData->m_iLevelID = table->toInt32(iRow, "LevelID");
        pUpLimitData->m_strUpLimit = table->toString(iRow, "UpLimit") + "币";
		pUpLimitData->m_iUpLimit = table->toInt64(iRow, "UpLimit");
        if (m_MapUpLimitData.find(pUpLimitData->m_iLevelID) == m_MapUpLimitData.end())
        {
          m_MapUpLimitData.insert(std::make_pair(pUpLimitData->m_iLevelID, pUpLimitData));
        }
      }
    }
  }

  void GameData::_getUpRatioData()
  {
    IDataBaseTable *table = gEnvGame.mGameSql->GetUpRatioData();
    if (table)
    {
      for (int iRow = 0; iRow< table->getRowCount(); ++iRow)
      {
        UpRatioData *pUpRatioData = new UpRatioData();
        pUpRatioData->m_iLevelID = table->toInt32(iRow, "LevelID");
        pUpRatioData->m_strUpRatio = table->toString(iRow, "UpRatio") + "币";
		pUpRatioData->m_iUpRatio = table->toInt64(iRow, "UpRatio");
        if (m_MapUpRatioData.find(pUpRatioData->m_iLevelID) == m_MapUpRatioData.end())
        {
          m_MapUpRatioData.insert(std::make_pair(pUpRatioData->m_iLevelID, pUpRatioData));
        }
      }
    }
  }

  void GameData::_getUpDownFenData()
  {
	IDataBaseTable *table = gEnvGame.mGameSql->GetUpDownFenData();
	if (table)
	{
		for (int iRow = 0; iRow< table->getRowCount(); ++iRow)
		{
			UpDownFenData *pUpDownFenData = new UpDownFenData();
			pUpDownFenData->m_iLevelID = table->toInt32(iRow, "LevelID");
			pUpDownFenData->m_strDesc = table->toString(iRow, "desc");
			if (m_MapUpDownFenData.find(pUpDownFenData->m_iLevelID) == m_MapUpDownFenData.end())
			{
				m_MapUpDownFenData.insert(std::make_pair(pUpDownFenData->m_iLevelID, pUpDownFenData));
			}
		}
	}
  }

  void GameData::_getSceneBackData()
  {
	  IDataBaseTable *table = gEnvGame.mGameSql->GetSceneBackData();
	  if (table)
	  {
		  for (int iRow = 0; iRow< table->getRowCount(); ++iRow)
		  {
			  SceneBackground *pSceneBack = new SceneBackground();
			  pSceneBack->m_iLevelID = table->toInt32(iRow, "LevelID");
			  pSceneBack->m_strDesc = table->toString(iRow, "SceneDesc");
			  pSceneBack->m_strSceneID = table->toString(iRow, "SceneID");
			  if (m_MapSceneBackData.find(pSceneBack->m_iLevelID) == m_MapSceneBackData.end())
			  {
				  m_MapSceneBackData.insert(std::make_pair(pSceneBack->m_iLevelID, pSceneBack));
			  }
		  }
	  }
  }

  void GameData::_getPostCodeDaysData()
  {
	  IDataBaseTable *table = gEnvGame.mGameSql->GetPostCodeDaysData();
	  if (table)
	  {
		  for (int iRow = 0; iRow< table->getRowCount(); ++iRow)
		  {
			PostCodeDays *pPostCodeDays = new PostCodeDays();
			pPostCodeDays->m_iLevelID = table->toInt32(iRow, "LevelID");
			pPostCodeDays->DaysDesc = table->toInt32(iRow, "DaysDesc");
			if (m_MapPostCodeDaysData.find(pPostCodeDays->m_iLevelID) == m_MapPostCodeDaysData.end())
			{
				m_MapPostCodeDaysData.insert(std::make_pair(pPostCodeDays->m_iLevelID, pPostCodeDays));
			}
		  }
	  }
  }

  String GameData::_int64ToString(int64 val)
  {
	  char buffer[32] = {0};
	  String retStr;
	  memset(buffer, 0, sizeof(buffer));
	  sprintf_s(buffer, "%I64d", val);
	  retStr = buffer;
	  return retStr;
  }

  void GameData::GetCurrentGameParmByGame()
  {
	IDataBaseTable *table = gEnvGame.mGameSql->GetCurParamSettingByGame();
	if (table)
	{
		m_CurrentGameParamByGame.m_iGameLevel = table->toInt32(0, "GameLevel");
		m_CurrentGameParamByGame.m_iMaxBetRatio = table->toInt64(0, "MaxBet");
		m_CurrentGameParamByGame.m_iMinBetRatio = table->toInt64(0, "MinBet");
		m_CurrentGameParamByGame.m_iMinChangeRatio = table->toInt64(0, "MinChange");
		m_CurrentGameParamByGame.m_iUpFenRatio = table->toInt64(0, "UpRatio");
		m_CurrentGameParamByGame.m_iDownFenRatio = table->toInt64(0, "DownRatio");
		m_CurrentGameParamByGame.m_iUpLimit = table->toInt64(0, "UpLimit");
		m_CurrentGameParamByGame.m_iBrustScore = table->toInt64(0, "BurstSocre");
		m_CurrentGameParamByGame.m_bOutCoinsFun = table->toInt32(0, "OutCoinFunction");
		m_CurrentGameParamByGame.m_iUpDownFenFun = table->toInt32(0, "UpDownFunction");
		m_CurrentGameParamByGame.m_bMusicBgFun = table->toInt32(0, "MusicBg");
		m_CurrentGameParamByGame.m_bVoiceFun = table->toInt32(0, "Voice");
		m_CurrentGameParamByGame.m_iSceneType = table->toInt32(0, "SceneType");
		m_CurrentGameParamByGame.m_iMachineType = table->toInt32(0, "MachineType");
		m_CurrentGameParamByGame.m_iInCoinsRatio = table->toInt64(0, "InCoinsRatio");
		m_CurrentGameParamByGame.m_iBusinessMode = table->toInt32(0, "BusinessMode");
		m_CurrentGameParamByGame.m_iTicketRatio = table->toInt64(0, "TicketRatio");
	}
  }

  void GameData::GetCurrentDeAdjustByGame()
  {
	  IDataBaseTable* table = gEnvGame.mGameSql->GetDeCodeAdjustTableData();
	  if (table)
	  {
		  m_CurrentDeCodeAdjustParam.m_iPostDays = table->toInt32(0, "PostCodeDays");
		  m_CurrentDeCodeAdjustParam.m_bVisibleSucess = table->toInt32(0, "PostCodeTips");
		  m_CurrentDeCodeAdjustParam.m_bPostCodeOnOff = table->toInt32(0, "PostCodeOnOff");
	  }
  }

  SystemSettingParam GameData::GetViewSystemSettingParamByGame()
  {
	  return m_CurrentSystemSettingParam;
  }

  PlayerDataByStart* GameData::GetPlayerDataById(int playerId)
  {
	  PlayerDataByStart *pPlayerData = new PlayerDataByStart();
	  IDataBaseTable* table = gEnvGame.mGameSql->GetCurPlayerDataById(playerId);
	  if (table)
	  {
		  pPlayerData->m_CurrentPoints = table->toInt64(0, "CurrentPoints");
		  pPlayerData->m_CurrentGuns = table->toInt64(0, "CurrentGuns");
		  return pPlayerData;
	  }
	  return NULL;
  }

  BusinessMode* GameData::GetBusinessModeById(int id)
  {
    std::map<int, BusinessMode*>::iterator iter = m_MapBusinessMode.find(id);
    if (iter != m_MapBusinessMode.end())
    {
      return iter->second;
    }
    return NULL;
  }

  IDataBaseTable* GameData::GetViewCheckAccountTop()
  {
    return gEnvGame.mGameSql->GetViewCheckAccountTop();
  }

  IDataBaseTable* GameData::GetCheckAccountData()
  {
    return gEnvGame.mGameSql->GetCheckAccountData();
  }

  IDataBaseTable* GameData::GetPostMessageData()
  {
    return gEnvGame.mGameSql->GetPostMessageData();
  }

  IDataBaseTable* GameData::GetViewParamSettingData()
  {
    return gEnvGame.mGameSql->GetViewParamSettingData();
  }

  void GameData::GetViewSystemSettingData()
  {
	  IDataBaseTable *table = gEnvGame.mGameSql->GetViewSystemSettingData();
	  if (table)
	  {
		  m_CurrentSystemSettingParam.m_strLineNo = table->toString(0, "LineNo");
		  m_CurrentSystemSettingParam.m_strMachineNo = table->toString(0, "MachineNo");
		  m_CurrentSystemSettingParam.m_strMiMa = table->toString(0, "MiMa");
	  }
  }

  GameLevel* GameData::GetGameLevel(int lv)
  {
	  std::map<int, GameLevel*>::iterator iter = m_MapGameLevel.begin();
	  std::map<int, GameLevel*>::iterator iterEnd = m_MapGameLevel.end();
	  for (; iter!= iterEnd; ++iter)
	  {
		  if (iter->first == lv)
		  {
			  m_CurrentGameParamByGame.m_iGameLevel = lv;
			  return iter->second;
		  }
	  }
	  return NULL;
  }

  int	GameData::GetGameLeveNum()
  {
	  return m_MapGameLevel.size();
  }

  MaxBetData* GameData::GetMaxBetData(int lv)
  {
	  std::map<int, MaxBetData*>::iterator iter = m_MapMaxBetData.begin();
	  std::map<int, MaxBetData*>::iterator iterEnd = m_MapMaxBetData.end();
	  for (; iter!= iterEnd; ++iter)
	  {
		  if (iter->first == lv)
		  {
			  m_CurrentGameParamByGame.m_iMaxBetRatio = lv;
			  return iter->second;
		  }
	  }
	  return NULL;
  }

  int	GameData::GetMaxBetNum()
  {
	  return m_MapMaxBetData.size();
  }

  MinBetData*	GameData::GetMinBetData(int lv)
  {
	  std::map<int, MinBetData*>::iterator iter = m_MapMinBetData.begin();
	  std::map<int, MinBetData*>::iterator iterEnd = m_MapMinBetData.end();
	  for (; iter!= iterEnd; ++iter)
	  {
		  if (iter->first == lv)
		  {
			  m_CurrentGameParamByGame.m_iMinBetRatio = lv;
			  return iter->second;
		  }
	  }
	  return NULL;
  }

  int	GameData::GetMinBetNum()
  {
	  return m_MapMinBetData.size();
  }

  MinChangeData*	GameData::GetMinChangeData(int lv)
  {
	  std::map<int, MinChangeData*>::iterator iter = m_MapMinChangeData.begin();
	  std::map<int, MinChangeData*>::iterator iterEnd = m_MapMinChangeData.end();
	  for (; iter!= iterEnd; ++iter)
	  {
		  if (iter->first == lv)
		  {
			  m_CurrentGameParamByGame.m_iMinChangeRatio = lv;
			  return iter->second;
		  }
	  }
	  return NULL;
  }

  int	GameData::GetMinChangeNum()
  {
	return m_MapMinChangeData.size();
  }

  UpRatioData*	GameData::GetUpRatioData(int lv)
  {
	  std::map<int, UpRatioData*>::iterator iter = m_MapUpRatioData.begin();
	  std::map<int, UpRatioData*>::iterator iterEnd = m_MapUpRatioData.end();
	  for (; iter!= iterEnd; ++iter)
	  {
		  if (iter->first == lv)
		  {
			  m_CurrentGameParamByGame.m_iUpFenRatio = lv;
			  return iter->second;
		  }
	  }
	  return NULL;
  }

  int	GameData::GetUpRatioNum()
  {
	  return m_MapUpRatioData.size();
  }

  DownRatio*	GameData::GetDownRatioData(int lv)
  {
	  std::map<int, DownRatio*>::iterator iter = m_MapDownRatio.begin();
	  std::map<int, DownRatio*>::iterator iterEnd = m_MapDownRatio.end();
	  for (; iter!= iterEnd; ++iter)
	  {
		  if (iter->first == lv)
		  {
			  m_CurrentGameParamByGame.m_iDownFenRatio = lv;
			  return iter->second;
		  }
	  }
	  return NULL;
  }

  int	GameData::GetDownRatioNum()
  {
	  return m_MapDownRatio.size();
  }

  BusinessMode*	GameData::GetBusinessModeData(int lv)
  {
	  std::map<int, BusinessMode*>::iterator iter = m_MapBusinessMode.begin();
	  std::map<int, BusinessMode*>::iterator iterEnd = m_MapBusinessMode.end();
	  for (; iter!= iterEnd; ++iter)
	  {
		  if (iter->first == lv)
		  {
			  m_CurrentGameParamByGame.m_iBusinessMode = lv;
			  return iter->second;
		  }
	  }
	  return NULL;
  }

  int	GameData::GetBusinessNum()
  {
	  return m_MapBusinessMode.size();
  }

  TicketRatio*	GameData::GetTicketRatioData(int lv)
  {
	  std::map<int, TicketRatio*>::iterator iter = m_MapTicketRatio.begin();
	  std::map<int, TicketRatio*>::iterator iterEnd = m_MapTicketRatio.end();
	  for (; iter!= iterEnd; ++iter)
	  {
		  if (iter->first == lv)
		  {
			  m_CurrentGameParamByGame.m_iTicketRatio = lv;
			  return iter->second;
		  }
	  }
	  return NULL;
  }

  int	GameData::GetTicketRatioNum()
  {
	  return m_MapTicketRatio.size();
  }

  UpLimitData*	GameData::GetUpLimitData(int lv)
  {
	  std::map<int, UpLimitData*>::iterator iter = m_MapUpLimitData.begin();
	  std::map<int, UpLimitData*>::iterator iterEnd = m_MapUpLimitData.end();
	  for (; iter!= iterEnd; ++iter)
	  {
		  if (iter->first == lv)
		  {
			  m_CurrentGameParamByGame.m_iUpLimit = lv;
			  return iter->second;
		  }
	  }
	  return NULL;
  }

  int	GameData::GetUpLimitNum()
  {
	  return m_MapUpLimitData.size();
  }

  BrustScore*	GameData::GetBrustScoreData(int lv)
  {
	  std::map<int, BrustScore*>::iterator iter = m_MapBrustScore.begin();
	  std::map<int, BrustScore*>::iterator iterEnd = m_MapBrustScore.end();
	  for (; iter!= iterEnd; ++iter)
	  {
		  if (iter->first == lv)
		  {
			  m_CurrentGameParamByGame.m_iBrustScore = lv;
			  return iter->second;
		  }
	  }
	  return NULL;
  }

  int	GameData::GetBrustNum()
  {
	  return m_MapBrustScore.size();
  }

  MachineType*	GameData::GetMachineTypeData(int lv)
  {
	  std::map<int, MachineType*>::iterator iter = m_MapMachineType.begin();
	  std::map<int, MachineType*>::iterator iterEnd = m_MapMachineType.end();
	  for (; iter!= iterEnd; ++iter)
	  {
		  if (iter->first == lv)
		  {
			  m_CurrentGameParamByGame.m_iMachineType = lv;
			  return iter->second;
		  }
	  }
	  return NULL;
  }

  int	GameData::GetMachineTypeNum()
  {
	return m_MapMachineType.size();
  }

  UpDownFenData*	GameData::GetUpDownFenData(int lv)
  {
	  std::map<int, UpDownFenData*>::iterator iter = m_MapUpDownFenData.begin();
	  std::map<int, UpDownFenData*>::iterator iterEnd = m_MapUpDownFenData.end();
	  for (; iter!= iterEnd; ++iter)
	  {
		  if (iter->first == lv)
		  {
			  m_CurrentGameParamByGame.m_iUpDownFenFun = lv;
			  return iter->second;
		  }
	  }
	  return NULL;
  }

  int	GameData::GetUpDownFenNum()
  {
	  return m_MapUpDownFenData.size();
  }

  InCoinsRatio*	GameData::GetCoinsRatio(int lv)
  {
	  std::map<int, InCoinsRatio*>::iterator iter = m_MapInCoinsRatio.begin();
	  std::map<int, InCoinsRatio*>::iterator iterEnd = m_MapInCoinsRatio.end();
	  for (; iter!= iterEnd; ++iter)
	  {
		  if (iter->first == lv)
		  {
			  m_CurrentGameParamByGame.m_iInCoinsRatio = lv;
			  return iter->second;
		  }
	  }
	  return NULL;
  }

  int	GameData::GetCoinsRatioNum()
  {
	  return m_MapInCoinsRatio.size();
  }

  PostCodeDays*	GameData::GetPostCodeDays(int lv)
  {
	  std::map<int, PostCodeDays*>::iterator iter = m_MapPostCodeDaysData.begin();
	  std::map<int, PostCodeDays*>::iterator iterEnd = m_MapPostCodeDaysData.end();
	  for (; iter!= iterEnd; ++iter)
	  {
		  if (iter->first == lv)
		  {
			  m_CurrentDeCodeAdjustParam.m_iPostDays = lv;
			  return iter->second;
		  }
	  }
	  return NULL;
  }

  int	GameData::GetPostCodeNum()
  {
	  return m_MapPostCodeDaysData.size();
  }

  SceneBackground* GameData::GetSceneType(int lv)
  {
	  std::map<int, SceneBackground*>::iterator iter = m_MapSceneBackData.begin();
	  std::map<int, SceneBackground*>::iterator iterEnd = m_MapSceneBackData.end();
	  for (; iter!= iterEnd; ++iter)
	  {
		  if (iter->first == lv)
		  {
			  m_CurrentGameParamByGame.m_iSceneType = lv;
			  return iter->second;
		  }
	  }
	  return NULL;
  }

  int	GameData::GetSceneTypeNum()
  {
	  return m_MapSceneBackData.size();
  }

  void	GameData::SetOutCoinsFun(bool val)
  {
		m_CurrentGameParamByGame.m_bOutCoinsFun = val;
  }

  void	GameData::SetBackMusic(bool val)
  {
		m_CurrentGameParamByGame.m_bMusicBgFun = val;
  }

  void	GameData::SetVoice(bool val)
  {
		m_CurrentGameParamByGame.m_bVoiceFun = val;
  }

  void	GameData::SaveGameParam()
  {
	  String strVal = _int64ToString(m_CurrentGameParamByGame.m_iGameLevel);
	  String strSql = "GameLevel = " + strVal;

	  strVal = _int64ToString(m_CurrentGameParamByGame.m_iMaxBetRatio);
	  strSql = strSql + ", MaxBet = " + strVal;

	  strVal = _int64ToString(m_CurrentGameParamByGame.m_iMinBetRatio);
	  strSql = strSql + ", MinBet = " + strVal;

	  strVal = _int64ToString(m_CurrentGameParamByGame.m_iMinChangeRatio);
	  strSql = strSql + ", MinChange = " + strVal;

	  strVal = _int64ToString(m_CurrentGameParamByGame.m_iUpFenRatio);
	  strSql = strSql + ", UpRatio = " + strVal;

	  strVal = _int64ToString(m_CurrentGameParamByGame.m_iUpDownFenFun);
	  strSql = strSql + ", DownRatio = " + strVal;

	  strSql = strSql + ", BusinessMode = " + StringConverter::toString(m_CurrentGameParamByGame.m_iBusinessMode);

	  strVal = _int64ToString(m_CurrentGameParamByGame.m_iTicketRatio);
	  strSql = strSql + ", TicketRatio = " + strVal;

	  strVal = _int64ToString(m_CurrentGameParamByGame.m_iUpLimit);
	  strSql = strSql + ", UpLimit = " + strVal;

	  strVal = _int64ToString(m_CurrentGameParamByGame.m_iBrustScore);
	  strSql = strSql + ", BurstSocre = " + strVal;

	  strSql = strSql + ", OutCoinFunction = " + StringConverter::toString(m_CurrentGameParamByGame.m_bOutCoinsFun);

	  strSql = strSql + ", UpDownFunction = " + StringConverter::toString(m_CurrentGameParamByGame.m_iUpDownFenFun);
	  strSql = strSql + ", MusicBg = " + StringConverter::toString(m_CurrentGameParamByGame.m_bMusicBgFun);
	  strSql = strSql + ", Voice = " + StringConverter::toString(m_CurrentGameParamByGame.m_bVoiceFun);
	  strSql = strSql + ", MachineType = " + StringConverter::toString(m_CurrentGameParamByGame.m_iMachineType);
	  gEnvGame.mGameSql->UpdateGameParamSetData( strSql );
  }

  bool	GameData::SaveDeCodeAdjustParam()
  {
	  // 数据放在两张表中
	  String strInCoinsRatio = _int64ToString(m_CurrentGameParamByGame.m_iInCoinsRatio);
	  String strSql = "InCoinsRatio = " + strInCoinsRatio;
	  strSql += ", SceneType = " + StringConverter::toString(m_CurrentGameParamByGame.m_iSceneType);
	  gEnvGame.mGameSql->UpdateGameParamSetData(strSql);

	  strSql = "PostCodeDays = " + StringConverter::toString(m_CurrentDeCodeAdjustParam.m_iPostDays);
	  strSql += ", PostCodeTips = " + StringConverter::toString(m_CurrentDeCodeAdjustParam.m_bVisibleSucess);
	  strSql += ", PostCodeOnOff = " + StringConverter::toString(m_CurrentDeCodeAdjustParam.m_bPostCodeOnOff);
	  return gEnvGame.mGameSql->UpdateDeCodeAdjustData(strSql);
  }

  void	GameData::SetVisibleSucessDeCode(bool val)
  {
	m_CurrentDeCodeAdjustParam.m_bVisibleSucess = val;
  }

  void	GameData::SetPostCodeOnOff(bool val)
  {
	  m_CurrentDeCodeAdjustParam.m_bPostCodeOnOff = val;
  }

  int	GameData::GetPostCodeOnOff()
  {
	  return m_CurrentDeCodeAdjustParam.m_bPostCodeOnOff;
  }

  DeCodeAdjustParam GameData::GetDeCodeAdjustParamData()
  {
	  return m_CurrentDeCodeAdjustParam;
  }

  int	GameData::GetGamePlayerNum()
  {
	  return m_CurrentGameParamByGame.m_iMachineType;
  }

  int64		GameData::GetGameCurMaxBet()
  {
	  int64 retVal = 0;
	  std::map<int, MaxBetData*>::iterator iter = m_MapMaxBetData.begin();
	  std::map<int, MaxBetData*>::iterator iterEnd = m_MapMaxBetData.end();
	  for (; iter!= iterEnd; ++iter)
	  {
		  if (iter->first == m_CurrentGameParamByGame.m_iMaxBetRatio)
		  {
			  retVal =  StringConverter::parseLong(iter->second->m_strBetRatio);
			  return retVal;
		  }
	  }
	  return retVal;
  }

  int64		GameData::GetGameCurMinBet()
  {
		int64 retVal = 0;
		std::map<int, MinBetData*>::iterator iter = m_MapMinBetData.begin();
		std::map<int, MinBetData*>::iterator iterEnd = m_MapMinBetData.end();
		for (; iter!= iterEnd; ++iter)
		{
			if (iter->first == m_CurrentGameParamByGame.m_iMinBetRatio)
			{
				retVal = StringConverter::parseLong(iter->second->m_strBetRatio);
				return retVal;
			}
		}
		return retVal;
  }

  int64		GameData::GetGameCurMinChange()
  {
		int64 retVal = 0;
		std::map<int, MinChangeData*>::iterator iter = m_MapMinChangeData.begin();
		std::map<int, MinChangeData*>::iterator iterEnd = m_MapMinChangeData.end();
		for (; iter!= iterEnd; ++iter)
		{
			if (iter->first == m_CurrentGameParamByGame.m_iMinChangeRatio)
			{
				retVal = StringConverter::parseLong(iter->second->m_strChangeRatio);
				return retVal;
			}
		}
		return retVal;
  }

  int64	GameData::GetGameCurInCoinsRatio()
  {
	  int64 retVal = 0;
	  std::map<int, InCoinsRatio*>::iterator iter = m_MapInCoinsRatio.begin();
 	  std::map<int, InCoinsRatio*>::iterator iterEnd = m_MapInCoinsRatio.end();
	  for (; iter!= iterEnd; ++iter)
	  {
		  if (iter->first == m_CurrentGameParamByGame.m_iInCoinsRatio)
		  {
			  retVal = iter->second->m_iInCoinsRatio;
			  return retVal;
		  }
	  }
	  return retVal;
  }

  int64	GameData::GetGameCurDownFenRatio()
  {
	  int64 retVal = 0;
	  std::map<int, DownRatio*>::iterator iter = m_MapDownRatio.begin();
	  std::map<int, DownRatio*>::iterator iterEnd = m_MapDownRatio.end();
	  for (; iter!= iterEnd; ++iter)
	  {
		  if (iter->first == m_CurrentGameParamByGame.m_iDownFenRatio)
		  {
			  retVal = iter->second->m_iDownRatio;
			  return retVal;
		  }
	  }
	  return retVal;
  }

  int64	GameData::GetGameCurUpFenRatio()
  {
	  int64 retVal = 0;
	  std::map<int, UpRatioData*>::iterator iter = m_MapUpRatioData.begin();
	  std::map<int, UpRatioData*>::iterator iterEnd = m_MapUpRatioData.end();
	  for (; iter!= iterEnd; ++iter)
	  {
		  if (iter->first == m_CurrentGameParamByGame.m_iUpFenRatio)
		  {
			  retVal = iter->second->m_iUpRatio; 
			  return retVal;
		  }
	  }
	  return retVal;
  }

  int64	GameData::GetGameCurTicketRatio()
  {
	  int64 retVal = 0;
	  std::map<int, TicketRatio*>::iterator iter = m_MapTicketRatio.begin();
	  std::map<int, TicketRatio*>::iterator iterEnd = m_MapTicketRatio.end();
	  for (; iter!= iterEnd; ++iter)
	  {
		  if (iter->first == m_CurrentGameParamByGame.m_iTicketRatio)
		  {
			  retVal = iter->second->m_iTicketRatio;
			  return retVal;
		  }
	  }
	  return retVal;
  }

  int64	GameData::GetGameTotalProfit()
  {
	  int64 retVal = 0;
	  IDataBaseTable *table = gEnvGame.mGameSql->GetTotalProfit();
	  if (table)
	  {
		 retVal =  table->toInt64(0, "TotalProfit");
	  }
	  return retVal;
  }

  int64	GameData::GetGamePreProfit()
  {
		int64 retVal = 0;
		IDataBaseTable *table = gEnvGame.mGameSql->GetPreProfit();
		if (table)
		{
			retVal = table->toInt64(0, "PreProfit");
		}
		return retVal;
  }

  int64	GameData::GetGameCurProfit()
  {
		int64 retVal = 0;
		IDataBaseTable *table = gEnvGame.mGameSql->GetCurrentProfit();
		if (table)
		{
			retVal = table->toInt64(0, "CurrentProfit");
		}
		return retVal;
  }

  int64	GameData::GetGameTotalUpFen()
  {
		int64 retVal = 0;
		IDataBaseTable *table = gEnvGame.mGameSql->GetTotalUpFen();
		if (table)
		{
			retVal = table->toInt64(0, "UpPoints");
		}
		return retVal;
  }

  int64	GameData::GetGameTotalDownFen()
  {
		int64 retVal = 0;
		IDataBaseTable *table = gEnvGame.mGameSql->GetTotalDownFen();
		if (table)
		{
			retVal = table->toInt64(0, "DownPoints");
		}
		return retVal;
  }

  int64	GameData::GetGameTotalInCoinsNum()
  {
		int64 retVal = 0;
		IDataBaseTable *table = gEnvGame.mGameSql->GetTotalInCoinsNum();
		if (table)
		{
			retVal = table->toInt64(0, "InCoins");
		}
		return retVal;
  }

  int64	GameData::GetGameTotalOutCoinsNum()
  {
		int64 retVal = 0;
		IDataBaseTable *table = gEnvGame.mGameSql->GetTotalOutCoinsNum();
		if (table)
		{
			retVal = table->toInt64(0, "OutCoins");
		}
		return retVal;
  }

  int64	GameData::GetGameTotalTicketNum()
  {
		int64 retVal = 0;
		IDataBaseTable *table = gEnvGame.mGameSql->GetTotalTicketNum();
		if (table)
		{
			retVal = table->toInt64(0, "RaffleTickets");
		}
		return retVal;
  }

  int	GameData::GetGameTotalPostCodeNum()
  {
		int retVal = 0;
		IDataBaseTable *table = gEnvGame.mGameSql->GetTotalPostCodeNum();
		if (table)
		{
			retVal = table->toInt32(0, "PostCodeCount");
		}
		return retVal;
  }

  int64 GameData::GetGameUpLimit()
  {
	  int64 retVal = 0;
	  std::map<int, UpLimitData*>::iterator iter = m_MapUpLimitData.begin();
	  std::map<int, UpLimitData*>::iterator iterEnd = m_MapUpLimitData.end();
	  for (; iter!= iterEnd; ++iter)
	  {
		  if (iter->first == m_CurrentGameParamByGame.m_iUpLimit)
		  {
			  retVal = iter->second->m_iUpLimit;
			  return retVal;
		  }
	  }
	  return retVal;
  }

  int GameData::GetGameCurBusinessMode()
  {
	  int retVal = 0;
	  std::map<int, BusinessMode*>::iterator iter = m_MapBusinessMode.begin();
	  std::map<int, BusinessMode*>::iterator iterEnd = m_MapBusinessMode.end();
	  for (; iter!= iterEnd; ++iter)
	  {
		  if (iter->first == m_CurrentGameParamByGame.m_iBusinessMode)
		  {
			  retVal = m_CurrentGameParamByGame.m_iBusinessMode;
			  return retVal;
		  }
	  }
	  return retVal;
  }
}