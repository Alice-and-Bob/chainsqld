/**
* @file       TableAssistant.h
* @brief      ��������
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

#ifndef RIPPLE_RPC_TABLE_ASSISTANT_H_INCLUDED
#define RIPPLE_RPC_TABLE_ASSISTANT_H_INCLUDED

#include <ripple/json/json_value.h>
#include <ripple/basics/base_uint.h>
#include <ripple/protocol/Protocol.h>
#include <ripple/protocol/AccountID.h>
#include <ripple/beast/utility/Journal.h>
#include <utility>
#include <string>
#include <map>
#include <list>
#include <chrono>

namespace ripple {

	class Application;
	class Config;
	class SecretKey;
	class STTx;

	using clock_type = std::chrono::steady_clock;
	using time_point_type = clock_type::time_point;

	class TableAssistant
	{
		/**
		* ������Ϣ
		*/
		typedef struct
		{
			LedgerIndex                                                  uTxLedgerVersion;		///< �����Լ��������߶�
			uint256                                                      uTxHash;				///< ����hash
			uint256                                                      uTxCheckHash;			///< У��hash
			bool                                                         bStrictMode;			///< �Ƿ�Ϊ�ϸ�ģʽ
		}txInfo;
		/**
		* У����Ϣ
		*/
		typedef struct
		{
			uint256                                                      uTxCheckHash;			///< У��hash
			uint256                                                      uTxBackupHash;			///< ����У��hash����raw�ֶ�һ�𴴽��µ�У��hash
			std::string													 sTableName;			///< 
			AccountID													 accountID;
			time_point_type												 timer;
			std::list<std::shared_ptr<txInfo>>							 listTx;
		}checkInfo;

	public:
		TableAssistant(Application& app, Config& cfg, beast::Journal journal);
		~TableAssistant() {}

		//
		//	t_create:generate token & crypt raw
		//	t_assign:generate token
		//	r_insert&r_delete&r_update:crypt raw
		/**
		*     ׼����ͨ����/���������json����
		*
		*		t_create:����Token����Raw�ֶμӽ�������ʹ���û���Կ���ܺ�����ģ�������raw�ֶ�
		*
		*		r_insert&r_delete&r_update:����raw�ֶ�
		*
		*     @param secret ˽Կ
		*     @param publickey ��Կ
		*	  @param tx_json input/output json����
		*	  @param ws �Ƿ�Ϊwebsocket
		*     @return �д���ʱ�����ص�error_message��error
		*/
		Json::Value prepare(const std::string& secret,const std::string& publickey,Json::Value& tx_json,bool ws = false);
		/**
		*     ��ȡ��Ӧ�ײ����ݿ��ʵ�ʱ���
		*
		*     @param accountIdStr �˻�ID
		*     @param tableNameStr ����
		*/
		Json::Value getDBName(const std::string& accountIdStr, const std::string& tableNameStr);
		/// �洢��ͨ����/�����и������׵�У����Ϣ��map��
		bool Put(STTx const& tx);
		/// ������У��hash�߳�
		void TryTableCheckHash();

		/// ��ȡ��У��hash
		uint256 getCheckHash(uint160 nameInDB);
	private:
		/// �洢���׵�У����Ϣ��map��
		bool PutOne(STTx const& tx, const uint256 &uHash);
		/**
		* ��У��hash�߳�
		*
		*	���ѽ�����֤����Ľ��ף���m_map��У����Ϣ�еĽ�����Ϣ�б����Ƴ�
		*/
		void TableCheckHashThread();
        Config& GetConfig() {return cfg_;}

	private:
		Application&										app_;
		beast::Journal										journal_;
		Config&												cfg_;

		//key:nameInDB
		std::map<uint160, std::shared_ptr<checkInfo>>		m_map;

		std::mutex											mutexMap_;
		bool												bTableCheckHashThread_;

	};
} // ripple

#endif
