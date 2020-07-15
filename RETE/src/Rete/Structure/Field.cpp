#include "Field.h"

#include "../../PublicDefine.h"

std::string Field::paramPrefix = "$";

std::string Field::getParamString(const std::string & prefix, size_t paramCount) {
	return paramPrefix + prefix + CStringOp::ToString(paramCount);
}

//����str��$��Ĳ�������
std::string Field::getParamName(const std::string & str) {
	myAssert(isParam(str));	//�ϵ����
	return str.substr(paramPrefix.length());
}

//�ж�paramPrefix�Ƿ�Ϊstr���Ӵ�������Ƿ���true�����ж�str��һ�������Ƿ�Ϊ$
bool Field::isParam(const std::string & str) {
	return CStringOp::startsWith(str, paramPrefix);
}
