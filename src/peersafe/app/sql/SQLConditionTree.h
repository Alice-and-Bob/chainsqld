/**

* @file       SQLConditionTree.h

* @brief      �����﷨������������ SQL ������������.

* @details	�������� Raw Э�齫��������һ����������Ȼ������������㷨���������ʽ���

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

#ifndef RIPPLE_APP_MISC_SQLCONDITIONTREE_H_INCLUDED
#define RIPPLE_APP_MISC_SQLCONDITIONTREE_H_INCLUDED

#include <vector>
#include <functional>
#include <tuple>

#include <peersafe/app/sql/SQLDataType.h>

#include <ripple/json/json_value.h>
#include<ripple/core/SociDB.h> // soci::details::once_temp_type

namespace ripple {

typedef FieldValue BindValue;

/**

* �����﷨��

* chainSQL �Ա���в�ѯ�͸��ĵ�ʱ��Ӧ�ò����� Raw Э�鶨����ֲ�ѯ�����������Ὣ��������һ�Ŷ�������Ȼ������������������ʽ���

*/
class conditionTree {
public:
	typedef std::vector<conditionTree>::iterator iterator;	///< ���ڵ�ָ��
	typedef std::vector<conditionTree>::const_iterator const_iterator; ///< ���ڵ�ָ��
	typedef std::tuple<std::string /*key*/, std::string /*operator*/, std::vector<BindValue> /*key's value*/> expression_result; ///< ���ʽ

	/**
	* �﷨���ڵ�����

	* ����.
	*/
	typedef enum {
		Logical_And,	///< �߼�����ʽ, eg: value = 1 and id = 1
		Logical_Or,		///< �߼�����ʽ, eg: value = 1 or id = 1
		Expression		///< ��ͨ���ʽ, eg: value = 1
	} NodeType;

	conditionTree(NodeType);
	conditionTree(const conditionTree& t);
	~conditionTree();

	conditionTree& operator = (const conditionTree& rhs) {
		type_ = rhs.type_;
		bind_values_index_ = rhs.bind_values_index_;
		expression_ = rhs.expression_;
		children_ = rhs.children_;
		bind_values_ = rhs.bind_values_;
		return *this;
	}

	/** �����﷨�����ڵ�
	*
	*    ��̬���������� Raw Э�鴴���﷨�����ڵ�
	*	@param conditions Raw �﷨Э�� 
	*	@return ���� std::pair ���ͣ�std::pair ���͵ĵ�һ��Ԫ��ֵΪ 0 ��ʾ���ɸ��ڵ�ɹ����������ɸ��ڵ�ʧ�ܣ�std::pair ���͵ĵڶ���Ԫ�ر�ʾ���ڵ����
	*/
	static std::pair<int, conditionTree> createRoot(const Json::Value& conditions);

	/** ��ȡ�﷨���ڵ�����
	*
	*    ��
	*	@param void
	*	@return �������ڵ�����
	*/
	const NodeType node_type() const {
		return type_;
	}

	/** �����﷨���ڵ���ʽ
	*
	*    ��
	*	@param express ���ʽֵ�� json ��ʽ���� {k = v}
	*	@return void
	*/
	void set_expression(const Json::Value& express) {
		expression_ = express;
	}

	expression_result parse_expression() {
		return parse_expression(expression_);
	}

	void set_bind_values_index(int fromindex) {
		bind_values_index_ = fromindex;
	}

	const Json::Value& expression() const {
		return expression_;
	}

	/** ����﷨���ڵ�
	*
	*    ��
	*	@param child ���ڵ�
	*	@return void
	*/
	void add_child(const conditionTree& child) {
		children_.push_back(child);
	}

	iterator begin() {
		return children_.begin();
	}

	const_iterator begin() const {
		return children_.begin();
	}

	iterator end() {
		return children_.end();
	}

	const_iterator end() const {
		return children_.end();
	}

	size_t size() const {
		return children_.size();
	}

	/** ���﷨�����ַ�����ʽ���
	*
	*    ���﷨�����ַ�����ʽ���, eg: `id > 10 and name = 'chainsql'`
	*	@param void
	*	@return string 
	*/
	const std::string asString() const;

	/** ����﷨��
	*
	*    ���﷨������ std::pair<int,std::string> ����
	*	@param void
	*	@return std::pair<int, std::string> std::pair �ĵ�һ��Ԫ��Ϊ 0 ��ʾ�﷨�����ɹ�������ʧ�ܣ�std::pair �ڶ���Ԫ���ڳɹ���ʱ���ַ�����ʽ�磺`id > :id and name = :name`
	*/
	const std::pair<int, std::string> asConditionString() const;
	// bind once_temp_type with values,return {0, "success"} if success,otherwise return {-1, "bind value unsuccessfully"}
	const std::pair<int, std::string> bind_value(soci::details::once_temp_type& t);
private:
	int format_conditions(int style, std::string& conditions) const;
	int format_value(const BindValue& value, std::string& result) const;
	// bind values
	int bind_value(const BindValue& value, soci::details::once_temp_type& t);
	int bind_array(const std::vector<BindValue>& values, soci::details::once_temp_type& t);
	// parse values
	int parse_array(const Json::Value& j, std::vector<BindValue>& v);
	int parse_value(const Json::Value& j, BindValue& v);
	expression_result parse_expression(const Json::Value& e);

	NodeType type_;
	mutable int	bind_values_index_; // binding same fields may be failure in sqlite
	Json::Value expression_;
	std::vector<conditionTree> children_;
	mutable std::vector<std::vector<BindValue>> bind_values_;
};

/**

* �����﷨���� helper ����

* ��

*/
namespace conditionParse {

	/** ���� Raw Э�鲢�������﷨��
	*
	*    ��
	*	@param raw_value Raw Э���е��﷨����
	*	@param root �﷨�����ڵ㣬�� conditionTree::createRoot ��������
	*	@return std::pair�ĵ�һ��Ԫ��Ϊ 0 ��ʾ�﷨�����ɳɹ�������ʧ�ܣ�std::pair �ڶ���Ԫ�ر�ʾʧ�ܵ���Ϣ
	*/
	std::pair<int, std::string> parse_conditions(const Json::Value& raw_value, conditionTree& root);

	typedef std::function<bool(const conditionTree::expression_result&)> handlevaluecb;							///< �����﷨����Ҷ�ӽڵ�
	typedef std::function<int(const conditionTree&, int /*0-starting,1-processing,2-end*/)> handlenodecb;		///< �����﷨���ķ�Ҷ�ӽڵ�
	bool judge(conditionTree& root, handlevaluecb cb);

	/** �����﷨��
	*
	*    ��
	*	@param root �﷨�����ڵ�
	*	@param cb �����﷨��Ҷ�ӽڵ�Ļص�����
	*	@param cb �����﷨����Ҷ�ӽڵ�Ļص�����
	*	@return void
	*/
	void traverse(conditionTree& root, handlevaluecb cb, handlenodecb ncb);
} // namespace helper

} // namespace ripple

#endif // RIPPLE_APP_MISC_SQLCONDITIONTREE_H_INCLUDED
