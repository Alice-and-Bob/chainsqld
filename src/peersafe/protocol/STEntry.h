/**
* @file       STEntry.h
* @brief      TableList��TableEntries������Ԫ��
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

#ifndef RIPPLE_PROTOCOL_STENTRY_H_INCLUDED
#define RIPPLE_PROTOCOL_STENTRY_H_INCLUDED

#include <ripple/protocol/PublicKey.h>
#include <ripple/protocol/SecretKey.h>
#include <ripple/protocol/STObject.h>
#include <ripple/app/tx/impl/ApplyContext.h>
#include <peersafe/protocol/TableDefines.h>
#include <cstdint>
#include <memory>

namespace ripple { 
    class STEntry final
        : public STObject
        , public CountedObject <STEntry>
    {
    public:
        static char const* getCountedObjectName() { return "STEntry"; }

        using pointer = std::shared_ptr<STEntry>;
        using ref = const std::shared_ptr<STEntry>&;

        enum
        {
            kFullFlag = 0x1
        };


        STEntry();  
		/**
		* ��ʼ��TableList��TableEntries������Ԫ�ظ��ֶε�ֵ
		*
		* @param tableName ����
		* @param nameInDB ��Ӧ�ײ����ݿ���ʵ�ʵı�����LedgerSequence+OwnerAccountID+������
		* @param deleted ��ʾ���Ƿ�ɾ��
		* @param createLgrSeq  �����׵�ledger���к�-1
		* @param createdLedgerHash  ���ν��׵�ledger HASH
		* @param createdTxnHash TransactionID
		* @param txnLedgerSequence  �����׵�ledger���к�
		* @param txnLedgerhash  ���ν��׵�ledger HASH
		* @param prevTxnLedgerSequence �ϴν��׵�ledger���к�
		* @param prevTxnLedgerhash �ϴν��׵�ledger HASH
		* @param txCheckhash У��hash
		* @param users ��Ȩ�û��б�
		*/
		void init(ripple::Blob tableName, uint160 nameInDB, uint8 deleted, uint32 createLgrSeq, uint256 createdLedgerHash, uint256 createdTxnHash, uint32 txnLedgerSequence, uint256 txnLedgerhash, uint32 prevTxnLedgerSequence, uint256 prevTxnLedgerhash, uint256 txCheckhash, STArray users);

		/**
		* ��ʼ���м����ƹ���
		*
		* @param operationRule �м����ƹ����ַ���
		*/
		void initOperationRule(ripple::Blob operationRule);

		/**
		* ��ȡ�������Ͷ�Ӧ���м����ƹ���
		*
		* @param opType ��������
		*/
		std::string getOperationRule(TableOpType opType) const;

		/**
		* �ж��˻��Ƿ���ĳ�ֲ���Ȩ��
		*
		* @param account �˻���ַ
		* @param flag ��������
		*/
		bool hasAuthority(const AccountID& account, TableRoleFlags flag);
		/// �ж��Ƿ��Ǽ���ģʽ
		bool isConfidential();

        STBase*
            copy(std::size_t n, void* buf) const override
        {
            return emplace(n, buf, *this);
        }

        STBase*
            move(std::size_t n, void* buf) override
        {
            return emplace(n, buf, std::move(*this));
        }
    private:
        static SOTemplate const& getFormat();
    };

} // ripple

#endif
