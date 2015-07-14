#ifndef GAMEDATA_H
#define GAMEDATA_H
#include "GameStructData.h"
#include "GameSql.h"

namespace Ogre
{
  class GameData
  {
  public:
    GameData();
    ~GameData();

  public:
    void Initialize();
    void LoadCommonData();// 公共数据，从数据库读取
    BusinessMode* GetBusinessModeById(int id);
    IDataBaseTable* GetViewCheckAccountTop();
    IDataBaseTable* GetCheckAccountData();
    IDataBaseTable* GetPostMessageData();
    IDataBaseTable* GetViewParamSettingData();

	GameLevel*		GetGameLevel(int lv);
	int				GetGameLeveNum();
	int				GetCurGameLevel();
	MaxBetData*		GetMaxBetData(int lv);
	int				GetMaxBetNum();
	MinBetData*		GetMinBetData(int lv);
	int				GetMinBetNum();
	MinChangeData*	GetMinChangeData(int lv);
	int				GetMinChangeNum();
	UpRatioData*	GetUpRatioData(int lv);
	int				GetUpRatioNum();
	DownRatio*		GetDownRatioData(int lv);
	int				GetDownRatioNum();
	BusinessMode*	GetBusinessModeData(int lv);
	int				GetBusinessNum();
	TicketRatio*	GetTicketRatioData(int lv);
	int				GetTicketRatioNum();
	UpLimitData*	GetUpLimitData(int lv);
	int				GetUpLimitNum();
	BrustScore*		GetBrustScoreData(int lv);
	int				GetBrustNum();
	MachineType*	GetMachineTypeData(int lv);
	int				GetMachineTypeNum();
	UpDownFenData*	GetUpDownFenData(int lv);
	int				GetUpDownFenNum();

	InCoinsRatio*	GetCoinsRatio(int lv);
	int				GetCoinsRatioNum();
	PostCodeDays*	GetPostCodeDays(int lv);
	int				GetPostCodeNum();
	SceneBackground* GetSceneType(int lv);
	int				GetSceneTypeNum();

	void			SetOutCoinsFun(bool val);
	void			SetBackMusic(bool val);
	void			SetVoice(bool val);
	void			SaveGameParam();// to do
	bool			SaveDeCodeAdjustParam();

	void			SetVisibleSucessDeCode(bool val);
	void			SetPostCodeOnOff(bool val);
	int				GetPostCodeOnOff();
	DeCodeAdjustParam	GetDeCodeAdjustParamData();


	int				GetGamePlayerNum();
	int64			GetGameCurMaxBet();
	int64			GetGameCurMinBet();
	int64			GetGameCurMinChange();
	int64			GetGameCurInCoinsRatio();
	int64			GetGameCurDownFenRatio();
	int64			GetGameCurUpFenRatio();
	int64			GetGameCurTicketRatio();

	int64			GetGameTotalProfit();
	int64			GetGamePreProfit();
	int64			GetGameCurProfit();
	int64			GetGameTotalUpFen();
	int64			GetGameTotalDownFen();
	int64			GetGameTotalInCoinsNum();
	int64			GetGameTotalOutCoinsNum();
	int64			GetGameTotalTicketNum();
	int				GetGameTotalPostCodeNum();
	int64			GetGameUpLimit();
	int				GetGameCurBusinessMode();

	///////// 为前台游戏提供 开始/////////
	void GetCurrentGameParmByGame();
	void GetCurrentDeAdjustByGame();
	SystemSettingParam GetViewSystemSettingParamByGame();
	PlayerDataByStart*	GetPlayerDataById(int playerId);
	///////// 为前台游戏提供 结束/////////

	void GetViewSystemSettingData();
  private:
    void _getBusinessMode();
    void _getBrustSocre();
    void _getDownRatio();
    void _getGameLevel();
    void _getInCoinsRatio();
    void _getMachineData();
    void _getMachineType();
    void _getMaxBetData();
    void _getMinBetData();
    void _getMinChangeData();
    void _getTicketRatio();
    void _getUpLimitData();
    void _getUpRatioData();
	void _getUpDownFenData();
	void _getSceneBackData();
	void _getPostCodeDaysData();
	String _int64ToString(int64 val);
  private:
    std::map<int, BusinessMode*> m_MapBusinessMode;
    std::map<int, BrustScore*> m_MapBrustScore;
    std::map<int, DownRatio*> m_MapDownRatio;
    std::map<int, GameLevel*> m_MapGameLevel;
    std::map<int, InCoinsRatio*> m_MapInCoinsRatio;
    std::map<int, MachineData*> m_MapMachineData;
    std::map<int, MachineType*> m_MapMachineType;
    std::map<int, MaxBetData*> m_MapMaxBetData;
    std::map<int, MinBetData*> m_MapMinBetData;
    std::map<int, MinChangeData*> m_MapMinChangeData;
    std::map<int, TicketRatio*> m_MapTicketRatio;
    std::map<int, UpLimitData*> m_MapUpLimitData;
    std::map<int, UpRatioData*> m_MapUpRatioData;
	std::map<int, UpDownFenData*> m_MapUpDownFenData;
	std::map<int, SceneBackground*> m_MapSceneBackData;
	std::map<int, PostCodeDays*> m_MapPostCodeDaysData;
	CurrentGameParamByGame			m_CurrentGameParamByGame;
	SystemSettingParam				m_CurrentSystemSettingParam;
	DeCodeAdjustParam				m_CurrentDeCodeAdjustParam;
  };
}

#endif