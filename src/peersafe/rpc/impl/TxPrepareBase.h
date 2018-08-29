/**
* @file       TxPrepareBase.h
* @brief      ����json����׼��������
* @date       20171209
* @version	  V1.0
* @par Copyright (c):
*      2016-2018 Peersafe Technology Co., Ltd.
*/
//------------------------------------------------------------------------------
/*
 This file is part of chainsqld: https://github.com/chainsql/chainsqld
 Copyright (c) 2016-2018 Peersafe Technology Co., Ltd.
 
	chainsqld is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
 
	chainsqld is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	You should have received a copy of the GNU General Public License
	along with cpp-ethereum.  If not, see <http://www.gnu.org/licenses/>.
 */
//==============================================================================

#ifndef RIPPLE_RPC_TX_PREPARE_BASE_H_INCLUDED
#define RIPPLE_RPC_TX_PREPARE_BASE_H_INCLUDED

#include <ripple/json/json_value.h>
#include <ripple/basics/base_uint.h>
#include <ripple/protocol/Protocol.h>
#include <ripple/protocol/AccountID.h>
#include <ripple/beast/utility/Journal.h>
#include <string>
#include <map>

namespace ripple {

	class Application;
	class Config;
	class SecretKey;

	using getCheckHashFunc = std::function<uint256(uint160)>;

	class TxPrepareBase
	{
	public:
		/**
		*     @brief ���캯��
		*
		*     @param app ��ǰ���еĽڵ����
		*     @param secret ˽Կ
		*     @param publickey ��Կ
		*	  @param tx_json input/output json����
		*	  @param func ��ȡУ��hash�ص�����
		*     @param ws �Ƿ�Ϊwebsocket
		*/
		TxPrepareBase(Application& app, const std::string& secret, const std::string& publickey, Json::Value& tx_json, getCheckHashFunc func, bool ws);
		virtual ~TxPrepareBase();
		/// ׼��������Ҫ��json����
		virtual Json::Value prepare();	
		/**
		* �ж�FutureTxHash�Ƿ���ȷ
		*
		* @param tx_json json����
		* @param app ��ǰ���еĽڵ����
		* @param bWs �Ƿ�Ϊwebsocket
		* @retval ����ֵ����error_message�ֶΣ���FutureTxHash����ȷ������FutureTxHash��ȷ��
		*/
        static Json::Value prepareFutureHash(const Json::Value& tx_json, Application& app, bool bWs);     //just check future hash is right.
		/**
		* �ж��Ƿ�Ϊ����ģʽ
		* @return �����Ƿ�Ϊ����ģʽ
		*/
		bool isConfidential();
	protected:
		/**
		*     @brief ��ȡ���׵�json����
		*
		*     @retval null  û�д���
		*	  @retval !null �д��󣬷��ص�error_message�ֶ�Ϊ������Ϣ
		*/
		Json::Value& getTxJson();
		/**
		*     @brief ׼����������
		*
		*     @retval null  û�д���
		*	  @retval !null �д��󣬷��ص�error_message�ֶ�Ϊ������Ϣ
		*/
		Json::Value prepareBase();
		/**
		*     @brief ΪT_RECREATE��������׼��raw�ֶ�
		*
		*     @retval null  û�д���
		*	  @retval !null �д��󣬷��ص�error_message�ֶ�Ϊ������Ϣ
		*/
        Json::Value prepareGetRaw();  
		/**
		*     @brief ����Ƿ�Ϊ����ģʽ
		*
		*     @retval true  ����ģʽ
		*	  @retval false �Ǽ���ģʽ
		*/
		bool checkConfidentialBase(const AccountID& owner, const std::string& tableName);
		//get decrypted pass_blob
		/**
		*     @brief ��ȡ��������
		*
		*     @param ownerId ӵ���ߵ�accountID
		*     @param userId ������accountID
		*     @param secret_key ���ܼ���������ʹ�õ�˽Կ
		*	  @return std::pair<Blob, Json::Value>(Blob, jsonValue)
		*	  jsonValue:null ˳����ȡ��������
		*	  jsonValue:!null ��ȡ�����������������Ϣ��jsonValue��error_message�ֶ�
		*/
		std::pair<Blob, Json::Value> getPassBlobBase(AccountID& ownerId, AccountID& userId, boost::optional<SecretKey> secret_key);
		/// ׼��У��hash�ֶ�
		Json::Value prepareCheckHash(const std::string& sRaw, const uint256& checkHash, uint256& checkHashNew);
		/// ��������
		Json::Value parseTableName();
	private:
		/**
		*     @brief ����У��hash
		*
		*     @param sAccount �˻�ID
		*     @param sTableName ����
		*	  @param checkHash У��hash
		*/
		virtual void updateCheckHash(const std::string& sAccount, const std::string& sTableName, const uint256& checkHash) {};
		/**
		*     ��ȡУ��hash
		*
		*     @param sAccount �˻�ID
		*     @param sTableName ����
		*     @return ����У��hash
		*/
		virtual uint256 getCheckHashOld(const std::string& sAccount, const std::string& sTableName);

		/**
		*     @brief ��ȡ���raw�ֶν��мӽ����õ�����
		*
		*     @param sAccount �˻�ID
		*     @param sTableName ����
		*	  @return ���ؼ�������
		*/
		virtual Blob getPassblobExtra(const std::string& sAccount, const std::string& sTableName);
		/**
		*     @brief �������raw�ֶν��мӽ����õ�����
		*
		*     @param sAccount �˻�ID
		*     @param sTableName ����
		*	  @param passblob ���raw�ֶν��мӽ����õ�����
		*/
		virtual void updatePassblob(const std::string& sAccount, const std::string& sTableName, const Blob& passblob) {};
		/**
		*     @brief ����ʵ�ʱ���
		*
		*     @param sAccount �˻�ID
		*     @param sTableName ����
		*	  @param sNameInDB ��Ӧ�ײ����ݿ��ʵ�ʱ���
		*/
        virtual void updateNameInDB(const std::string& sAccount, const std::string& sTableName, const std::string& sNameInDB) {};
		/**
		*     @brief ��ȡ��Ӧ�ײ����ݿ��ʵ�ʱ���
		*
		*     @param sAccount �˻�ID
		*     @param sTableName ����
		*/
		virtual std::string getNameInDB(const std::string& sAccount, const std::string& sTableName);

		/**
		*     @brief ����Ƿ�Ϊ����ģʽ
		*
		*     @param owner �˻�ID
		*     @param tableName ����
		*/
		virtual bool checkConfidential(const AccountID& owner, const std::string& tableName);

		/**
		*     @brief ���±���Ϣ
		*
		*     @param sAccount �˻�ID
		*     @param sTableName ����
		*     @param sNameInDB ��Ӧ�ײ����ݿ��ʵ�ʱ���
		*/
        void updateInfo(const std::string& sAccount, const std::string& sTableName, const std::string& sNameInDB);
		/**
		* @brief ׼������Ӧ�ײ����ݿ��ʵ�ʱ�����nameInDB�����ֶ�����
		* @return
		*/
		Json::Value prepareDBName();        
		/**
		*	  @brief ʹ�û���json���ݣ��������յ�json����
		*     @retval null  û�д���
		*	  @retval !null �д��󣬷��ص�error_message�ֶ�Ϊ������Ϣ
		*/
		Json::Value prepareVL(Json::Value& json);

		/**
		* @brief ׼������ģʽ��json����
		* @details ����ģʽ��:
		*	       T_CREATE:׼��Raw��Token�ֶΣ�
		*		   T_ASSERT/R_INSERT/R_UPDATE/R_DELETE��׼��Raw�ֶΣ�
		*		   T_GRANT/T_ASSIGN��׼��Token�ֶ�
		* @retval null  û�д���
		* @retval !null �д��󣬷��ص�error_message�ֶ�Ϊ������Ϣ
		*/
		Json::Value prepareRawEncode();
		/**
		* @brief ׼���ϸ�ģʽ�µ�json����
		* @details �ϸ�ģʽ�£�����TxCheckHash�ֶ�
		* @retval null  û�д���
		* @retval !null �д��󣬷��ص�error_message�ֶ�Ϊ������Ϣ
		*/
		Json::Value prepareStrictMode();
		/**
		* @brief ׼��PressData
		* @details ����Flags�ֶ�
		* @retval null  û�д���
		* @retval !null �д��󣬷��ص�error_message�ֶ�Ϊ������Ϣ
		*/
		void preparePressData();

		/**
		* @brief ׼������ģʽ��json����
		* @details ����ģʽ�£�T_ASSERT/R_INSERT/R_UPDATE/R_DELETE��׼��Raw�ֶΣ�
		* @retval null  û�д���
		* @retval !null �д��󣬷��ص�error_message�ֶ�Ϊ������Ϣ
		*/
		Json::Value prepareForOperating();
		/**
		* @brief ׼������ģʽ��json����
		* @details ����ģʽ�£�T_CREATE:׼��Raw��Token�ֶ�
		* @retval null  û�д���
		* @retval !null �д��󣬷��ص�error_message�ֶ�Ϊ������Ϣ
		*/
		Json::Value prepareForCreate();
		/**
		* @brief ׼������ģʽ��json����
		* @details ����ģʽ�£�T_GRANT/T_ASSIGN��׼��Token�ֶ�
		* @retval null  û�д���
		* @retval !null �д��󣬷��ص�error_message�ֶ�Ϊ������Ϣ
		*/
		Json::Value prepareForAssign();

		//get decrypted pass_blob
		/**
		*     @brief ��ȡУ��hash
		*
		*     @param sAccount �˻�ID
		*	  @param sTableName ����
		*	  @return std::pair<uint256, Json::Value>(checkHash, jsonValue)
		*	  jsonValue:null ˳����ȡУ��hash
		*	  jsonValue:!null ��ȡУ��hash����������Ϣ��jsonValue��error_message�ֶ�
		*/
		std::pair<uint256,Json::Value> getCheckHash(const std::string& sAccount,const std::string& sTableName);

		/**
		*     @brief ��ȡ��������
		*
		*     @param ownerId ӵ���ߵ�accountID
		*     @param userId ������accountID
		*     @param secret_key ���ܼ���������ʹ�õ�˽Կ
		*	  @return std::pair<Blob, Json::Value>(Blob, jsonValue)
		*	  jsonValue:null ˳����ȡ��������
		*	  jsonValue:!null ��ȡ�����������������Ϣ��jsonValue��error_message�ֶ�
		*/
		std::pair<Blob, Json::Value> getPassBlob(
			AccountID& ownerId, AccountID& userId, boost::optional<SecretKey> secret_key);
	protected:
		Application&										app_;
		const std::string&									secret_;
        const std::string&                                  public_;
		Json::Value&										tx_json_;
		getCheckHashFunc									getCheckHashFunc_;
		bool												ws_;

	private:
		std::string                                         sTableName_;
		uint160                                             u160NameInDB_;		
		AccountID                                           ownerID_;

		//is table raw encoded
		bool												m_bConfidential;
	};
} // ripple

#endif
