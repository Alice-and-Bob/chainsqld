/**

* @file       TxStore.h

* @brief      �� chainSQL �Ľ���ת���� native SQL.

* @details	�������� Raw Э������ native SQL,����ִ�� SQL ���

* @author     dbliu

* @date       2017/12/09

* @version v1.0

* @par Copyright (c):

*      Copyright (c) 2016-2018 Peersafe Technology Co., Ltd

* @par History:

*   v1.0: dbliu, 2017/12/09, originator\n

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

#ifndef RIPPLE_APP_MISC_TXSTORE_H_INCLUDED
#define RIPPLE_APP_MISC_TXSTORE_H_INCLUDED

#include <memory>
#include <string>
#include <utility>

#include <ripple/app/tx/impl/ApplyContext.h>
#include <ripple/core/DatabaseCon.h>
#include <ripple/rpc/Context.h>
#include <ripple/json/json_value.h>
#include <ripple/basics/Log.h>

namespace ripple {

class TxStoreDBConn {
public:
	TxStoreDBConn(const Config& cfg);
	~TxStoreDBConn();

	DatabaseCon* GetDBConn() {
		if (databasecon_)
			return databasecon_.get();
		return nullptr;
	}

private:
	std::shared_ptr<DatabaseCon> databasecon_;
};

class TxStoreTransaction {
public:
	TxStoreTransaction(TxStoreDBConn* storeDBConn);
	~TxStoreTransaction();

	soci::transaction* GetTransaction() {
		if (tr_)
			return tr_.get();
		return nullptr;
	}

	void commit() {
		tr_->commit();
	}

    void rollback() {
        tr_->rollback();
    }

private:
	std::shared_ptr<soci::transaction> tr_;
    std::shared_ptr<LockedSociSession> lockSession_;
};

/**

* ת�� chainSQL ����Ϊ native SQL.

* �� chainSQL ����ת��Ϊ native SQL ��䣬����ִ�� native SQL�������������� chainSQL ������ݿ�ʵ������

*/
class TxStore {
public:
	//TxStore(const Config& cfg);

	/** TxStore ���캯��
	*
	*    �������ݿ����Ӷ������õȹ��� txStore ����
	*	@param dbconn �������Ӷ���
	*	@param cfg ���ݿ���������
	*	@param journal ��־����
	*	@return void
	*/
	TxStore(DatabaseCon* dbconn, const Config& cfg, const beast::Journal& journal);
	~TxStore();

	/** ���� chainSQL ����
	*
	*    ���� chainSQL ���׵�����������ص� native SQL,����ִ�� SQL
	*	@param tx chainSQL ���׶���
	*	@param operationRule  �м����ƹ���
	*	@param verifyAffectedRows  ��������Ƿ��Ӱ�쵽��
	*	@return std::pair �ĵ�һ��Ԫ��Ϊ 0 ��ʾ���ý����Ƿ�ɹ��������ý���ʧ�ܣ��ڶ���Ԫ��Ϊʧ�ܺ�Ĵ�����ʾ
	*/
	std::pair<bool,std::string> Dispose(const STTx& tx,const std::string& operationRule = "", bool verifyAffectedRows = false);

	/** �����ݿ���ֱ��ɾ��ָ���ı�
	*
	*    ��
	*	@param tablename ����
	*	@return std::pair �ĵ�һ��Ԫ��Ϊ 0 ��ʾ���ý����Ƿ�ɹ��������ý���ʧ�ܣ��ڶ���Ԫ��Ϊʧ�ܺ�Ĵ�����ʾ
	*/
	std::pair<bool, std::string> DropTable(const std::string& tablename);

	/** �����ݿ���ֱ�Ӳ�ѯ����
	*
	*    ���Ӳ�ѯ����ֱ�Ӵ����ݿ����ѯ����
	*	@param context tx context ��ѯ����
	*	@return Json::Value
	*/
	Json::Value txHistory(RPC::Context& context);
    Json::Value txHistory(Json::Value& tx_json);
    Json::Value txHistory(std::string sql);

	DatabaseCon* getDatabaseCon();
private:
	const Config& cfg_;
	std::string db_type_;
	DatabaseCon* databasecon_;
	beast::Journal journal_;
};	// class TxStore

}	// namespace ripple
#endif // RIPPLE_APP_MISC_TXSTORE_H_INCLUDED
