/**
* @file       TxSingleTransPrepare.h
* @brief      �������е���������Ϣjson׼����
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

#ifndef RIPPLE_RPC_TX_SINGLE_TRANS_PREPARE_H_INCLUDED
#define RIPPLE_RPC_TX_SINGLE_TRANS_PREPARE_H_INCLUDED

#include <ripple/json/json_value.h>
#include <ripple/basics/base_uint.h>
#include <ripple/protocol/Protocol.h>
#include <ripple/protocol/AccountID.h>
#include <ripple/beast/utility/Journal.h>
#include <peersafe/rpc/impl/TxPrepareBase.h>
#include <string>
#include <map>

namespace ripple {

	class Application;
	class SecretKey;
	class TxTransactionPrepare;

	class TxSingleTransPrepare : public TxPrepareBase
	{
	public:
		/**
		* ���캯��
		* @param app ��ǰ���нڵ����
		* @param trans ��������Ϣ׼��
		* @param secret ˽Կ
		* @param publickey ��Կ
		* @param tx_json �������͵�json����
		* @param func ��ȡУ��hash�ص����� 
		* @param ws �Ƿ�Ϊwebsocket
		*/
		TxSingleTransPrepare(Application& app, TxTransactionPrepare* trans, 
			const std::string& secret, const std::string& publickey, Json::Value& tx_json, getCheckHashFunc func,bool ws);

	private:
		/**
		*     @brief ����Ƿ�Ϊ����ģʽ
		*
		*     @param owner �˻�ID
		*     @param tableName ����
		*/
		virtual bool checkConfidential(const AccountID& owner, const std::string& tableName) override;
		/**
		*     ��ȡУ��hash
		*
		*     @param sAccount �˻�ID
		*     @param sTableName ����
		*     @return ����У��hash
		*/
		virtual uint256 getCheckHashOld(const std::string& sAccount, const std::string& sTableName) override;

		/**
		*     @brief ����У��hash
		*
		*     @param sAccount �˻�ID
		*     @param sTableName ����
		*	  @param checkHash У��hash
		*/
		virtual void updateCheckHash(const std::string& sAccount, const std::string& sTableName,const uint256& checkHash) override;

		/**
		*     @brief ��ȡ���raw�ֶν��мӽ����õ�����
		*
		*     @param sAccount �˻�ID
		*     @param sTableName ����
		*	  @return ���ؼ�������
		*/
		virtual Blob getPassblobExtra(const std::string& sAccount, const std::string& sTableName) override;

		/**
		*     @brief �������raw�ֶν��мӽ����õ�����
		*
		*     @param sAccount �˻�ID
		*     @param sTableName ����
		*	  @param passblob ���raw�ֶν��мӽ����õ�����
		*/
		virtual void updatePassblob(const std::string& sAccount, const std::string& sTableName, const Blob& passblob) override;

		/**
		*     @brief ����ʵ�ʱ���
		*
		*     @param sAccount �˻�ID
		*     @param sTableName ����
		*	  @param sNameInDB ��Ӧ�ײ����ݿ��ʵ�ʱ���
		*/
		void updateNameInDB(const std::string& sAccount, const std::string& sTableName, const std::string& sNameInDB) override;
		/**
		*     @brief ��ȡ��Ӧ�ײ����ݿ��ʵ�ʱ���
		*
		*     @param sAccount �˻�ID
		*     @param sTableName ����
		*/
		virtual std::string getNameInDB(const std::string& sAccount, const std::string& sTableName) override;

	private:
		TxTransactionPrepare*								m_pTransaction;
	};
} // ripple

#endif
