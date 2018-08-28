/**

* @file       SQLDataType.h

* @brief      ���� chainSQL Э�����������͹��ɵ����ݿ���ֶ�����.

* @details	��ϸ������ chainSQL ���ɵ�������ݿ� (MYSQL) ���ֶ�����ӳ�䡣���ж����� InnerDateTime,InnerDate,InnerDecimal ��

* @author     dbliu

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

#ifndef RIPPLE_APP_MISC_SQLDATATYPE_H_INCLUDED
#define RIPPLE_APP_MISC_SQLDATATYPE_H_INCLUDED

#include <string>
#include <cstring> // std::strcmp
#include <cassert> // assert

namespace ripple {

/**

* only for holding space, no sense.

* ��

*/
class InnerDateTime
{
public:
	InnerDateTime() {}
	~InnerDateTime() {}
};

/**

* only for holding space, no sense.

* ��

*/
class InnerDate {
public:
	InnerDate() {}
	~InnerDate() {}
};

/**

* Deciaml ����

* ����������ֶ����ͽ����� innerDecimal ���ͣ��������ͺ�double��float���������ǿ��Զ��徫ȷ��

*/

class InnerDecimal
{
public:
	InnerDecimal(int length, int accuracy)
		: length_(length)
		, accuracy_(accuracy) {
	}

	~InnerDecimal() {}
	const int length() {
		return length_;
	}

	const int length() const {
		return length_;
	}

	const int accuracy() {
		return accuracy_;
	}

	const int accuracy() const {
		return accuracy_;
	}

	void update(const InnerDecimal& v) {
		length_ = v.length_;
		accuracy_ = v.accuracy_;
	}

	InnerDecimal& operator =(const InnerDecimal& value) {
		length_ = value.length_;
		accuracy_ = value.accuracy_;
		return *this;
	}

	bool operator ==(const InnerDecimal& value) {
		return length_ == value.length_ && accuracy_ == value.accuracy_;
	}

private:
	InnerDecimal() {}
	int length_;	///< length of decimal
	int accuracy_;	///< accuracy of decimal
};

/**

* ������ʱ�����ڽ��������ֶ�����

* chainSQL �����ı��ʱ��Ӧ�ò����� Raw Э�鶨����ֶεĸ������ͣ���������ڽ������ֶε����ơ����� 

*/
class FieldValue {
public:
	/** FieldValue ���캯��
	*
	*    FieldValue Ĭ�Ϲ��캯�� 
	*/
	explicit FieldValue()
		: value_type_(INNER_UNKOWN) {};

	/** FieldValue ���캯��
	*
	*    ��������Ϊ string ��ֵ���� FieldValue
	*	@param value �ֶ�ֵ
	*/
	explicit FieldValue(const std::string& value)
		: value_type_(STRING) {
		value_.str = new std::string;
		if (value_.str) {
			value_.str->assign(value);
		}
	}

	enum { fVARCHAR, fCHAR, fTEXT, fBLOB };
	/** FieldValue ���캯��
	*
	*    ��������Ϊ string ��ֵ������Ϊ int ��ֵ���� FieldValue			
	*	@param value �ֶ�ֵ
	*	@param flag	�ֶ�����
	*/
	explicit FieldValue(const std::string& value, int flag)
		: value_type_(STRING) {

		if (flag == fVARCHAR)
			value_type_ = VARCHAR;
		else if (flag == fCHAR)
			value_type_ = CHAR;
		else if (flag == fTEXT)
			value_type_ = TEXT;
		else if (flag == fBLOB)
			value_type_ = BLOB;

		value_.str = new std::string;
		if (value_.str) {
			value_.str->assign(value);
		}
	}

	/** FieldValue ���캯��
	*
	*    ��������Ϊ int ��ֵ���� FieldValue
	*	@param value �ֶ�ֵ
	*/
	explicit FieldValue(const int value)
		: value_type_(INT) {
		value_.i = value;
	}

	/** FieldValue ���캯��
	*
	*    ��������Ϊ unsigned int ��ֵ���� FieldValue
	*	@param value �ֶ�ֵ
	*/
	explicit FieldValue(const unsigned int value)
		: value_type_(UINT) {
		value_.ui = value;
	}

	/** FieldValue ���캯��
	*
	*    ��������Ϊ float ��ֵ���� FieldValue
	*	@param f �ֶ�ֵ
	*/
	explicit FieldValue(const float f)
		: value_type_(FLOAT) {
		value_.f = f;
	}

	/** FieldValue ���캯��
	*
	*    ��������Ϊ double ��ֵ���� FieldValue
	*	@param d �ֶ�ֵ
	*/
	explicit FieldValue(const double d)
		: value_type_(DOUBLE) {
		value_.d = d;
	}

	/** FieldValue ���캯��
	*
	*    ��������Ϊ int64_t ��ֵ���� FieldValue
	*	@param value �ֶ�ֵ
	*/
	explicit FieldValue(const int64_t value)
		: value_type_(LONG64) {
		value_.i64 = value;
	}

	/** FieldValue ���캯��
	*
	*    ��������Ϊ InnerDateTime ��ֵ���� FieldValueE
	*	@param datetime �ֶ�ֵ
	*/
	explicit FieldValue(const InnerDateTime& datetime)
		: value_type_(DATETIME) {
		value_.datetime = nullptr;
	}

	/** FieldValue ���캯��
	*
	*    ��������Ϊ InnerDate ��ֵ���� FieldValue
	*	@param date �ֶ�ֵ
	*/
	explicit FieldValue(const InnerDate& date)
		: value_type_(DATE) {
		value_.date = nullptr;
	}

	/** FieldValue ���캯��
	*
	*    ��������Ϊ InnerDecimal ��ֵ���� FieldValueL
	*	@param d �ֶ�ֵ
	*/
	explicit FieldValue(const InnerDecimal& d)
		: value_type_(DECIMAL) {
		value_.decimal = new InnerDecimal(d.length(), d.accuracy());
	}

	/** FieldValue �������캯��
	*
	*    ��������Ϊ FieldValue ��ֵ���� FieldValue
	*	@param value �ֶ�ֵ
	*/
	explicit FieldValue(const FieldValue& value)
		: value_type_(value.value_type_) {
		assign(value);
	}

	/** FieldValue ��ֵ�����
	*
	*    ������ֵ����Ϊ FieldValue ��ֵ���� FieldValue ����
	*	@param value ��ֵ
	*	@return ���� FieldValue ���Ͷ��� 
	*/
	FieldValue& operator =(const FieldValue& value) {
		value_type_ = value.value_type_;
		assign(value);
		return *this;
	}

	/** ��ֵʵ��
	*
	*    �� value �����ֵ�����͸�ֵ���¶���
	*	@param value ��Ҫ��ֵ�Ķ���
	*/
	void assign(const FieldValue& value) {
		if (value_type_ == INT) {
			value_.i = value.value_.i;
		}
		else if (value_type_ == UINT) {
			value_.ui = value.value_.ui;
		}
		else if (value_type_ == STRING || value_type_ == VARCHAR
			|| value_type_ == TEXT || value_type_ == BLOB
			|| value_type_ == CHAR) {

			value_.str = new std::string;
			if (value_.str) {
				value_.str->assign(value.value_.str->c_str());
			}
		}
		else if (value_type_ == DATETIME) {
			value_.datetime = value.value_.datetime;
		}
		else if (value_type_ == DATE) {
			value_.date = value.value_.date;
		} else if (value_type_ == LONG64) {
			value_.i64 = value.value_.i64;
		}
		else if (value_type_ == FLOAT) {
			value_.f = value.value_.f;
		}
		else if (value_type_ == DOUBLE) {
			value_.d = value.value_.d;
		}
		else if (value_type_ == DECIMAL) {
			value_.decimal = new InnerDecimal(value.value_.decimal->length(),
				value.value_.decimal->accuracy());
		}
	}

	/** FieldValue ��ֵ�����
	*
	*    ������ֵ����Ϊ string ��ֵ���� FieldValue ����
	*	@param value ��ֵ
	*	@return ���� FieldValue ���Ͷ���
	*/
	FieldValue& operator =(const std::string& value) {
		value_type_ = STRING;
		value_.str = new std::string;
		if (value_.str) {
			value_.str->assign(value);
		}
		return *this;
	}

	/** FieldValue ��ֵ�����
	*
	*    ������ֵ����Ϊ int ��ֵ���� FieldValue ����
	*	@param value ��ֵ
	*	@return ���� FieldValue ���Ͷ���
	*/
	FieldValue& operator =(const int value) {
		value_type_ = INT;
		value_.i = value;
		return *this;
	}

	/** FieldValue ��ֵ�����
	*
	*    ������ֵ����Ϊ unsigned int ��ֵ���� FieldValue ����
	*	@param value ��ֵ
	*	@return ���� FieldValue ���Ͷ���
	*/
	FieldValue& operator =(const unsigned int value) {
		value_type_ = UINT;
		value_.ui = value;
		return *this;
	}

	/** FieldValue ��ֵ�����
	*
	*    ������ֵ����Ϊ float ��ֵ���� FieldValue ����
	*	@param value ��ֵ
	*	@return ���� FieldValue ���Ͷ���
	*/
	FieldValue& operator =(const float value) {
		value_type_ = FLOAT;
		value_.f = value;
		return *this;
	}

	/** FieldValue ��ֵ�����
	*
	*    ������ֵ����Ϊ double ��ֵ���� FieldValue ����
	*	@param value ��ֵ
	*	@return ���� FieldValue ���Ͷ���
	*/
	FieldValue& operator =(const double value) {
		value_type_ = DOUBLE;
		value_.d = value;
		return *this;
	}

	/** FieldValue ��ֵ�����
	*
	*    ������ֵ����Ϊ InnerDateTime ��ֵ���� FieldValue ����
	*	@param value ��ֵ
	*	@return ���� FieldValue ���Ͷ���
	*/
	FieldValue& operator =(const InnerDateTime& value) {
		value_type_ = DATETIME;
		value_.datetime = nullptr;
		return *this;
	}

	/** FieldValue ��ֵ�����
	*
	*    ������ֵ����Ϊ InnerDate ��ֵ���� FieldValue ����
	*	@param value ��ֵ
	*	@return ���� FieldValue ���Ͷ���
	*/
	FieldValue& operator =(const InnerDate& value) {
		value_type_ = DATE;
		value_.date = nullptr;
		return *this;
	}

	/** FieldValue ��ֵ�����
	*
	*    ������ֵ����Ϊ InnerDecimal ��ֵ���� FieldValue ����
	*	@param value ��ֵ
	*	@return ���� FieldValue ���Ͷ���
	*/
	FieldValue& operator =(const InnerDecimal& value) {
		value_type_ = DECIMAL;
		value_.decimal = new InnerDecimal(value.length(), value.accuracy());
		return *this;
	}

	/** FieldValue ��ֵ�����
	*
	*    ������ֵ����Ϊ int64_t ��ֵ���� FieldValue ����
	*	@param value ��ֵ
	*	@return ���� FieldValue ���Ͷ���
	*/
	FieldValue& operator =(const int64_t value) {
		value_type_ = LONG64;
		value_.i64 = value;
		return *this;
	}

	/** FieldValue ��ϵ�����
	*
	*    �������� FieldValue �����ֵ�����ͼ�����������Ƿ����
	*	@param left ��ֵ
	*	@param right ��ֵ
	*	@return ������������൱�򷵻� TRUE, ���򷵻� FALSE
	*/
	bool operator ==(const FieldValue& r) const {
		bool eq = false;
		assert(value_type_ == r.value_type_);
		if (value_type_ != r.value_type_)
			return eq;

		if (value_type_ == INT)
			eq = (value_.i == r.value_.i);
		else if (value_type_ == UINT)
			eq = (value_.ui == r.value_.ui);
		else if (value_type_ == FLOAT)
			eq = (value_.f == r.value_.f);
		else if (value_type_ == DOUBLE)
			eq = (value_.d == r.value_.d);
		else if (value_type_ == DECIMAL)
			eq = (*value_.decimal) == (*r.value_.decimal);
		else if (value_type_ == LONG64)
			eq = (value_.i64 == r.value_.i64);
		else if (value_type_ == STRING || value_type_ == VARCHAR
			|| value_type_ == TEXT || value_type_ == BLOB
			|| value_type_ == CHAR) {
			if (std::strcmp(value_.str->c_str(), r.value_.str->c_str()) == 0)
				eq = true;
		}
		else if (value_type_ == DATETIME || value_type_ == DATE) // TODO ??
			eq = false;

		return eq;
	}

	/** FieldValue ��ϵ�����
	*
	*    �������� FieldValue �����ֵ�����ͼ����ֵ�����Ƿ�С����ֵ����
	*	@param left ��ֵ
	*	@param right ��ֵ
	*	@return �����ֵС����ֵ�򷵻� TRUE, ���򷵻� FALSE
	*/
	bool operator <(const FieldValue& r) const {
		bool eq = false;
		assert(value_type_ == r.value_type_);
		if (value_type_ != r.value_type_)
			return eq;

		if (value_type_ == INT)
			eq = (value_.i < r.value_.i);
		else if (value_type_ == UINT)
			eq = (value_.ui < r.value_.ui);
		else if (value_type_ == FLOAT)
			eq = (value_.f < r.value_.f);
		else if (value_type_ == DOUBLE)
			eq = (value_.d < r.value_.d);
		else if (value_type_ == LONG64)
			eq = (value_.i64 < r.value_.i64);
		else if (value_type_ == STRING || value_type_ == VARCHAR
			|| value_type_ == TEXT || value_type_ == BLOB
			|| value_type_ == CHAR) {
			if (std::strcmp(value_.str->c_str(), r.value_.str->c_str()) < 0)
				eq = true;
		}
		else if (value_type_ == DECIMAL) {
			assert(0);
		}
		else if (value_type_ == DATETIME || value_type_ == DATE) // TODO ??
			eq = false;

		return eq;
	}

	/** FieldValue ��ϵ�����
	*
	*    �������� FieldValue �����ֵ�����ͼ����ֵ�����Ƿ�С�ڵ�����ֵ����
	*	@param left ��ֵ
	*	@param right ��ֵ
	*	@return �����ֵС�ڵ���TRUE, ���򷵻� FALSE
	*/
	bool operator <=(const FieldValue& r) const {
		bool eq = false;
		assert(value_type_ == r.value_type_);
		if (value_type_ != r.value_type_)
			return eq;

		if (value_type_ == INT)
			eq = (value_.i <= r.value_.i);
		else if (value_type_ == UINT)
			eq = (value_.ui <= r.value_.ui);
		else if (value_type_ == FLOAT)
			eq = (value_.f <= r.value_.f);
		else if (value_type_ == DOUBLE)
			eq = (value_.d <= r.value_.d);
		else if (value_type_ == DECIMAL)
			assert(0);
		else if (value_type_ == LONG64)
			eq = (value_.i64 <= r.value_.i64);
		else if (value_type_ == STRING || value_type_ == VARCHAR
			|| value_type_ == TEXT || value_type_ == BLOB
			|| value_type_ == CHAR) {
			if (std::strcmp(value_.str->c_str(), r.value_.str->c_str()) < 0
				||std::strcmp(value_.str->c_str(), r.value_.str->c_str()) == 0)
				eq = true;
		}
		else if (value_type_ == DATETIME || value_type_ == DATE) // TODO ??
			eq = false;

		return eq;
	}

	/** FieldValue ��ϵ�����
	*
	*    �������� FieldValue �����ֵ�����ͼ����ֵ�����Ƿ������ֵ����
	*	@param left ��ֵ
	*	@param right ��ֵ
	*	@return �����ֵ����TRUE, ���򷵻� FALSE
	*/
	bool operator >(const FieldValue& r) const {
		bool eq = false;
		assert(value_type_ == r.value_type_);
		if (value_type_ != r.value_type_)
			return eq;

		if (value_type_ == INT)
			eq = (value_.i > r.value_.i);
		else if (value_type_ == UINT)
			eq = (value_.ui > r.value_.ui);
		else if (value_type_ == FLOAT)
			eq = (value_.f > r.value_.f);
		else if (value_type_ == DOUBLE)
			eq = (value_.d > r.value_.d);
		else if (value_type_ == DECIMAL)
			assert(0);
		else if (value_type_ == LONG64)
			eq = (value_.i64 > r.value_.i64);
		else if (value_type_ == STRING || value_type_ == VARCHAR
			|| value_type_ == TEXT || value_type_ == BLOB
			|| value_type_ == CHAR) {
			if (std::strcmp(value_.str->c_str(), r.value_.str->c_str()) > 0)
				eq = true;
		}
		else if (value_type_ == DATETIME || value_type_ == DATE) // TODO ??
			eq = false;

		return eq;
	}

	/** FieldValue ��ϵ�����
	*
	*    �������� FieldValue �����ֵ�����ͼ����ֵ�����Ƿ���ڵ�����ֵ����
	*	@param left ��ֵ
	*	@param right ��ֵ
	*	@return �����ֵ���ڵ��� TRUE, ���򷵻� FALSE
	*/
	bool operator >=(const FieldValue& r) const {
		bool eq = false;
		assert(value_type_ == r.value_type_);
		if (value_type_ != r.value_type_)
			return eq;

		if (value_type_ == INT)
			eq = (value_.i >= r.value_.i);
		else if (value_type_ == UINT)
			eq = (value_.ui >= r.value_.ui);
		else if (value_type_ == FLOAT)
			eq = (value_.f >= r.value_.f);
		else if (value_type_ == DOUBLE)
			eq = (value_.d >= r.value_.d);
		else if (value_type_ == DECIMAL)
			assert(0);
		else if (value_type_ == LONG64)
			eq = (value_.i64 >= r.value_.i64);
		else if (value_type_ == STRING || value_type_ == VARCHAR
			|| value_type_ == TEXT || value_type_ == BLOB
			|| value_type_ == CHAR) {
			if (std::strcmp(value_.str->c_str(), r.value_.str->c_str()) > 0
				|| std::strcmp(value_.str->c_str(), r.value_.str->c_str()) == 0)
				eq = true;
		}
		else if (value_type_ == DATETIME || value_type_ == DATE) // TODO ??
			eq = false;

		return eq;
	}

	~FieldValue() {
		if ((value_type_ == STRING || value_type_ == VARCHAR
			|| value_type_ == TEXT || value_type_ == BLOB
			|| value_type_ == CHAR)
			&& value_.str) {
			delete value_.str;
			value_.str = nullptr;
		}
		else if (value_type_ == DECIMAL) {
			delete value_.decimal;
			value_.decimal = nullptr;
		}
	}

	bool isNumeric() {
		return (value_type_ == INT || value_type_ == UINT || value_type_ == LONG64
			|| value_type_ == FLOAT || value_type_ == DOUBLE || value_type_ == DECIMAL);
	}

	bool isNumeric() const {
		return (value_type_ == INT || value_type_ == UINT || value_type_ == LONG64
			|| value_type_ == FLOAT || value_type_ == DOUBLE || value_type_ == DECIMAL);
	}

	bool isInt() {
		return value_type_ == INT;
	}

	bool isInt() const {
		return value_type_ == INT;
	}

	bool isUint() {
		return value_type_ == UINT;
	}

	bool isUint() const {
		return value_type_ == UINT;
	}

	bool isFloat() {
		return value_type_ == FLOAT;
	}

	bool isFloat() const {
		return value_type_ == FLOAT;
	}

	bool isDouble() {
		return value_type_ == DOUBLE;
	}

	bool isDouble() const {
		return value_type_ == DOUBLE;
	}

	bool isDecimal() {
		return value_type_ == DECIMAL;
	}

	bool isDecimal() const {
		return value_type_ == DECIMAL;
	}

	bool isInt64() {
		return value_type_ == LONG64;
	}

	bool isInt64() const {
		return value_type_ == LONG64;
	}

	bool isString() {
		return value_type_ == STRING;
	}

	bool isString() const {
		return value_type_ == STRING;
	}

	bool isVarchar() {
		return value_type_ == VARCHAR;
	}

	bool isVarchar() const {
		return value_type_ == VARCHAR;
	}

	bool isChar() {
		return value_type_ == CHAR;
	}

	bool isChar() const {
		return value_type_ == CHAR;
	}

	bool isText() {
		return value_type_ == TEXT;
	}

	bool isText() const {
		return value_type_ == TEXT;
	}

	bool isBlob() {
		return value_type_ == BLOB;
	}

	bool isBlob() const {
		return value_type_ == BLOB;
	}

	bool isDateTime() {
		return value_type_ == DATETIME;
	}

	bool isDateTime() const {
		return value_type_ == DATETIME;
	}

	bool isDate() {
		return value_type_ == DATE;
	}

	bool isDate() const {
		return value_type_ == DATE;
	}

	const int& asInt() {
		return value_.i;
	}

	const int& asInt() const {
		return value_.i;
	}

	const unsigned int& asUint() {
		return value_.ui;
	}

	const unsigned int& asUint() const {
		return value_.ui;
	}

	const int64_t& asInt64() {
		return value_.i64;
	}

	const int64_t& asInt64() const {
		return value_.i64;
	}

	const float& asFloat() {
		return value_.f;
	}

	const float& asFloat() const {
		return value_.f;
	}

	const double& asDouble() {
		return value_.d;
	}

	const double& asDouble() const {
		return value_.d;
	}

	InnerDecimal& asDecimal() {
		return *value_.decimal;
	}

	const InnerDecimal& asDecimal() const {
		return *value_.decimal;
	}

	const std::string& asString() {
		return *value_.str;
	}

	const std::string& asString() const {
		return *value_.str;
	}


	void update(const InnerDecimal& d) {
		assert(value_.decimal);
		value_.decimal->update(d);
	}

private:

	/**

	* chainSQL ֧�ֵ��ڲ�����

	* ����.

	*/
	enum inner_type {
		INNER_UNKOWN,	///< δ֪����
		INT,			///< integer 
		UINT,			///< unsigned integer
		FLOAT,			///< float
		DOUBLE,			///< double
		LONG64,			///< long64
		DECIMAL,		///< decimal
		DATETIME,		///< datetime
		DATE,			///< date
		TEXT,			///< text
		VARCHAR,		///< varchar
		CHAR,			///< char
		BLOB,			///< blob
		STRING			///< string
	};

	int value_type_;	///< @enum inner_type 
	/**

	* chainSQL ֧�ֵ� inner_type ��Ӧ��ϵͳ����

	* ����.

	*/
	union inner_value {
		int i;				///< int
		unsigned int ui;	///< unsigned int
		int64_t i64;		///< int64_t
		float f;			///< float
		double d;			///< date
		InnerDateTime *datetime;	///< @var InnerDateTime
		InnerDate *date;			///< @var InnerDate
		InnerDecimal *decimal;		///< @var InnerDateTime
		std::string *str;	///< @var inner_type::TEXT/inner_type::VARCHAR/inner_type::TEXT/inner_type::BLOB/inner_type::DECIMAL
	} value_;
};

} // namespace ripple

#endif // RIPPLE_APP_MISC_SQLDATATYPE_H_INCLUDED
