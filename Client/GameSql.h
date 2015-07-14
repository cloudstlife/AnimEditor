#ifndef DATALOGIC_H
#define DATALOGIC_H
#include "SystemPrerequisites.h"
#include "IDataBase.h"
//#include "GameData.h"

namespace Ogre
{
  enum  EDBO
  {
    EDBO_NONE = 0,
    EDBO_UPDATE_GAMELEVEL, // 修改游戏难度
    EDBO_MAX,
  };


  class GameSql;
  typedef void (GameSql::*DBMsgHandler_Callback)(String strSql);

  class GameSql
  {
  public:
    GameSql();
    ~GameSql();

		inline bool ExcuteGameSql(String strSql);

    // 具体操作
	public:
		// 游戏设置相关
		void HandlerDBMsg(int MsgType, const String& str);
		void UpdateGameLevel(const String& str);// 更新游戏难度
		void UpdateMaxBet(const String& str);// 更新最大押注
		void UpdateMinBet(const String& str);// 更新最小押注
		void UpdateUpRatio(const String& str);// 更新上分数
		void UpdateDownRatio(const String& str);// 更新下分数
		void UpdateTicketRatio(const String& str);// 更新彩票比率
		void UpdateUpLimit(const String& str);// 更新上分极限
		void UpdateBurstSocre(const String& str);// 更新爆分分数
		void UpdateBusinessMode(const String& str);// 营业模式
		void UpdateOutCoinFunction(const String& str);// 退币功能开关
		void UpdateUpDownFunction(const String& str);// 上下分功能开关
		void UpdateMusicBg(const String& str);// 音乐开关
		void UpdateVoice(const String& str);// 声音开关
		void UpdateMachineType(const String& str);// 机台类型
		void UpdatePlayersData(const String& str);// 玩家数据
		void UpdateGameParamSetData(const String& str); // 保存游戏参数设置数据
		bool UpdateDeCodeAdjustData(const String& str); // 保存解码数据
		bool UpdateMachineNo(const String& str); // 修改机器码
		bool UpdateMiMa(const String& str); // 修改登录密码

		// 玩家数据相关
		void UpdatePlayerData(const String& str);// 更新玩家数据，外部拼接

		// 帐务数据相关
		bool UpdateTotalProfit(const String& str); // 更新全部总盈利
		bool UpdatePreProfit(const String& str);// 更新上次总盈利
		bool UpdateCurProfit(const String& str);// 保存本总盈利
		bool UpdateUpPoints(const String& str);// 更新上分数
		bool UpdateDownPoints(const String& str);// 更新下分数
		bool UpdateInCoins(const String& str);// 更新投币数
		bool UpdateOutCoins(const String& str);// 更新退币数
		bool UpdateRaffleTickets(const String& str);// 更新彩票数
		bool UpdatePostCodeCount(const String& str);// 更新报码次数

	/////// 查询相关 ///////////
		IDataBaseTable* GetBusinessMode();
		IDataBaseTable* GetBrustSocre();
		IDataBaseTable* GetDownRatio();
		IDataBaseTable* GetGameLevel();
		IDataBaseTable* GetInCoinsRatio();
		IDataBaseTable* GetMachineData();
		IDataBaseTable* GetMachineType();
		IDataBaseTable* GetMaxBetData();
		IDataBaseTable* GetMinBetData();
		IDataBaseTable* GetMinChangeData();
		IDataBaseTable* GetTicketRatio();
		IDataBaseTable* GetUpLimitData();
		IDataBaseTable* GetUpRatioData();
		IDataBaseTable* GetUpDownFenData();
		IDataBaseTable* GetSceneBackData();
		IDataBaseTable* GetPostCodeDaysData();
		IDataBaseTable* GetViewCheckAccountTop();
		IDataBaseTable* GetCheckAccountData();
		IDataBaseTable* GetPostMessageData();
		IDataBaseTable* GetViewParamSettingData();
		IDataBaseTable* GetViewDeCodeAdjustData();
		IDataBaseTable* GetViewSystemSettingData();
		IDataBaseTable* GetDeCodeAdjustTableData();

		IDataBaseTable* GetTotalProfit();
		IDataBaseTable* GetPreProfit();
		IDataBaseTable* GetCurrentProfit();
		IDataBaseTable* GetTotalUpFen();
		IDataBaseTable* GetTotalDownFen();
		IDataBaseTable* GetTotalInCoinsNum();
		IDataBaseTable* GetTotalOutCoinsNum();
		IDataBaseTable* GetTotalTicketNum();
		IDataBaseTable* GetTotalPostCodeNum();
		IDataBaseTable* GetCurPlayerDataById(int playerId);

		/////// 为前台游戏提供 开始///////////
		IDataBaseTable* GetCurParamSettingByGame();
		/////// 为前台游戏提供 结束///////////

  private:
    static DBMsgHandler_Callback m_pDBMsgHandlerCallbacks[EDBO_MAX];
    void InitDBMsgHandlerCallBack();
  };
}
#endif