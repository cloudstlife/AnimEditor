#pragma once
#ifndef GAMESTRUCTDATA_H
#define GAMESTRUCTDATA_H
#include "SystemPrerequisites.h"

namespace Ogre
{
  struct BusinessMode
  {
    int m_iMode;
    String m_strModeDesc;
  };

  struct BrustScore
  {
    int m_iLevelID;
    String m_strBrustSocre;
  };

  struct DownRatio
  {
    int m_iLevelID;
	INT64  m_iDownRatio;
    String m_strDownRatio;
  };

  struct GameLevel
  {
    int m_iLevelID;
    String m_strLevelDesc;
  };

  struct InCoinsRatio
  {
    int		m_iLevelID;
	int64	m_iInCoinsRatio;
    String	m_strInCoinsRatio;
  };

  struct MachineData
  {
    int m_iID;
    String m_strLineNo;
    String m_strMachineNo;
  };

  struct MachineType
  {
    int m_iTypeID;
    String m_strTypeDesc;
  };

  struct MaxBetData
  {
    int m_iLevelID;
    String m_strBetRatio;
  };

  struct MinBetData
  {
    int m_iLevelID;
    String m_strBetRatio;
  };

  struct MinChangeData
  {
    int m_iLevelID;
    String m_strChangeRatio;
  };

  struct TicketRatio
  {
    int m_iLevelID;
    String m_strTicketRatio;
	int64  m_iTicketRatio;
  };

  struct UpLimitData
  {
    int m_iLevelID;
    String m_strUpLimit;
	int64 m_iUpLimit;
  };

  struct UpRatioData
  {
    int m_iLevelID;
	int64 m_iUpRatio;
    String m_strUpRatio;
  };

  struct UpDownFenData
  {
	  int m_iLevelID;
	  String m_strDesc;
  };

  struct SceneBackground
  {
		int m_iLevelID;
		String m_strDesc;
		String m_strSceneID;
  };

  struct PostCodeDays
  {
	  int m_iLevelID;
	  int DaysDesc;
  };

  //////////////// 这里数据用于提供给游戏使用 开始/////////////////////////////////////
  struct CurrentGameParamByGame
  {
		int		m_iGameLevel;
		int64	m_iMaxBetRatio;
		int64	m_iMinBetRatio;
		int64	m_iMinChangeRatio;
		int64	m_iInCoinsRatio;
		int64	m_iUpFenRatio;
		int64	m_iDownFenRatio;
		int		m_iBusinessMode;
		int64	m_iTicketRatio;
		int64	m_iUpLimit;
		int64	m_iBrustScore;
		int		m_bOutCoinsFun;
		int		m_iUpDownFenFun;
		int		m_bMusicBgFun;
		int		m_bVoiceFun;
		int		m_iMachineType;
		int		m_iSceneType;
  };

  struct SystemSettingParam
  {
	  String m_strMachineNo;
	  String m_strLineNo;
	  String m_strMiMa;
  };

  struct DeCodeAdjustParam
  {
	  int	m_iPostDays;
	  int	m_bVisibleSucess;
	  int	m_bPostCodeOnOff;
  };

  struct PlayerDataByStart
  {
	  int64	m_CurrentPoints;
	  int64	m_CurrentGuns;
  };
  //////////////// 这里数据用于提供给游戏使用 结束/////////////////////////////////////
}
#endif
