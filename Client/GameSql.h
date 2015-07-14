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
    EDBO_UPDATE_GAMELEVEL, // �޸���Ϸ�Ѷ�
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

    // �������
	public:
		// ��Ϸ�������
		void HandlerDBMsg(int MsgType, const String& str);
		void UpdateGameLevel(const String& str);// ������Ϸ�Ѷ�
		void UpdateMaxBet(const String& str);// �������Ѻע
		void UpdateMinBet(const String& str);// ������СѺע
		void UpdateUpRatio(const String& str);// �����Ϸ���
		void UpdateDownRatio(const String& str);// �����·���
		void UpdateTicketRatio(const String& str);// ���²�Ʊ����
		void UpdateUpLimit(const String& str);// �����Ϸּ���
		void UpdateBurstSocre(const String& str);// ���±��ַ���
		void UpdateBusinessMode(const String& str);// Ӫҵģʽ
		void UpdateOutCoinFunction(const String& str);// �˱ҹ��ܿ���
		void UpdateUpDownFunction(const String& str);// ���·ֹ��ܿ���
		void UpdateMusicBg(const String& str);// ���ֿ���
		void UpdateVoice(const String& str);// ��������
		void UpdateMachineType(const String& str);// ��̨����
		void UpdatePlayersData(const String& str);// �������
		void UpdateGameParamSetData(const String& str); // ������Ϸ������������
		bool UpdateDeCodeAdjustData(const String& str); // �����������
		bool UpdateMachineNo(const String& str); // �޸Ļ�����
		bool UpdateMiMa(const String& str); // �޸ĵ�¼����

		// ����������
		void UpdatePlayerData(const String& str);// ����������ݣ��ⲿƴ��

		// �����������
		bool UpdateTotalProfit(const String& str); // ����ȫ����ӯ��
		bool UpdatePreProfit(const String& str);// �����ϴ���ӯ��
		bool UpdateCurProfit(const String& str);// ���汾��ӯ��
		bool UpdateUpPoints(const String& str);// �����Ϸ���
		bool UpdateDownPoints(const String& str);// �����·���
		bool UpdateInCoins(const String& str);// ����Ͷ����
		bool UpdateOutCoins(const String& str);// �����˱���
		bool UpdateRaffleTickets(const String& str);// ���²�Ʊ��
		bool UpdatePostCodeCount(const String& str);// ���±������

	/////// ��ѯ��� ///////////
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

		/////// Ϊǰ̨��Ϸ�ṩ ��ʼ///////////
		IDataBaseTable* GetCurParamSettingByGame();
		/////// Ϊǰ̨��Ϸ�ṩ ����///////////

  private:
    static DBMsgHandler_Callback m_pDBMsgHandlerCallbacks[EDBO_MAX];
    void InitDBMsgHandlerCallBack();
  };
}
#endif