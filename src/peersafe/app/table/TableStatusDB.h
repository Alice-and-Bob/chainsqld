/**

* @file       TableStatusDB.h

* @brief      ���ݿ��״̬����.

* @details	 ���ݿ��״̬����

* @author     peersafe

* @date       2017/12/09

* @version v1.0

* @par Copyright (c):

*      Copyright (c) 2016-2018 Peersafe Technology Co., Ltd.

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

#ifndef RIPPLE_APP_TABLE_TABLESTATUSDB_H_INCLUDED
#define RIPPLE_APP_TABLE_TABLESTATUSDB_H_INCLUDED

#include <ripple/app/main/Application.h>
#include <ripple/core/DatabaseCon.h>
#include <ripple/protocol/AccountID.h>
#include <ripple/protocol/Protocol.h>

namespace ripple {
	/**
	*
	* ���ݲ�������ֵ
	*
	* ����
	*/
	enum soci_ret {
		soci_success = 1,		///< ���ݲ����ɹ�
		soci_failed = 0,		///< ���ݲ���ʧ��
		soci_exception = -1		///< ���ݲ����쳣
	};

/**

* ���ݿ��״̬����̬

* ���ݿ��״̬����

*/
class TableStatusDB {
public:
    TableStatusDB(DatabaseCon* dbconn, Application*  app,beast::Journal& journal);
    virtual ~TableStatusDB();

    virtual bool InitDB(DatabaseCon::Setup setup) = 0;

    virtual bool GetAutoListFromDB(uint256 chainId, std::list<std::tuple<std::string, std::string, std::string, bool> > &list) = 0;

    virtual bool ReadSyncDB(std::string nameInDB, LedgerIndex &txnseq,
        uint256 &txnhash, LedgerIndex &seq, uint256 &hash, uint256 &TxnUpdateHash) = 0;

    virtual bool GetMaxTxnInfo(std::string TableName, std::string Owner, LedgerIndex &TxnLedgerSeq, uint256 &TxnLedgerHash) = 0;

    virtual bool InsertSnycDB(std::string TableName, std::string TableNameInDB, std::string Owner,LedgerIndex LedgerSeq, uint256 LedgerHash, bool IsAutoSync,std::string TxnLedgerTime, uint256 chainId) = 0;

    virtual bool CreateSnycDB(DatabaseCon::Setup setup) = 0;

    virtual bool isNameInDBExist(std::string TableName, std::string Owner, bool delCheck, std::string &TableNameInDB) = 0;

	/**  ���±���
	*
	*    ���ݱ� id ����ĳ�˻��µı���
	*	@param accountID �˻� id
	*	@param TableNameInDB �� id
	*	@param TableName ����
	*	@return true ���³ɹ���������³�ʧ��
	*/
    virtual bool RenameRecord(AccountID accountID, std::string TableNameInDB, std::string TableName) = 0;

	/**  ���±� id
	*
	*    ����ĳ�˺������б��id
	*	@param accountID �˻� id
	*	@param tablename ����
	*	@param TableNameInDB �� id
	*	@return true ���³ɹ���������³�ʧ��
	*/
    virtual soci_ret UpdateSyncDB(AccountID accountID, std::string TableName, std::string TableNameInDB) = 0;

	/**  ���±�״̬
	*
	*    ����ĳ�˻��µı�״̬
	*	@param owner ���������˺�
	*	@param tablename ����
	*	@param isAutoSync �Ƿ��Զ�ͬ��
	*	@return true ���³ɹ���������³�ʧ��
	*/
    virtual bool UpdateStateDB(const std::string & owner, const std::string & tablename, const bool &isAutoSync) = 0;
    
	/**  ɾ�����¼
	*
	*    ɾ��ĳ�˻��µı�����
	*	@param accountID �˻�id
	*	@param TableName ����
	*	@return true ɾ���ɹ�������ɾ��ʧ��
	*/
    virtual bool DeleteRecord(AccountID accountID, std::string TableName) =0;

	/**  �жϱ��Ƿ����
	*
	*    �ж�ĳ�˺����Ƿ�ӵ��ĳ��
	*	@param accountID �˻�id
	*	@param TableNameInDB ��id
	*	@return true ����ڣ����������
	*/
    virtual bool IsExist(AccountID accountID, std::string TableNameInDB) = 0;

    virtual soci_ret UpdateSyncDB(const std::string &Owner, const std::string &TableNameInDB,
        const std::string &TxnLedgerHash, const std::string &TxnLedgerSeq, const std::string &LedgerHash,
        const std::string &LedgerSeq, const std::string &TxHash, const std::string &TxnLedgerTime, const std::string &PreviousCommit) = 0;

    virtual soci_ret UpdateSyncDB(const std::string &Owner, const std::string &TableNameInDB,
            const std::string &LedgerHash, const std::string &LedgerSeq, const std::string &PreviousCommit) = 0;

    virtual soci_ret UpdateSyncDB(const std::string &Owner, const std::string &TableNameInDB,
        const std::string &TxnUpdateHash, const std::string &PreviousCommit) = 0;

    virtual soci_ret UpdateSyncDB(const std::string &Owner, const std::string &TableNameInDB,
        bool bDel, const std::string &PreviousCommit) = 0;

protected:
    DatabaseCon*                                                 databasecon_;
    Application*                                                 app_;
    beast::Journal&                                              journal_;
}; // class TxStoreStatus

}

#endif
