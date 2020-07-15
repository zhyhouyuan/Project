#include "Field.h"

#include "../../PublicDefine.h"

std::string Field::paramPrefix = "$";

std::string Field::getParamString(const std::string & prefix, size_t paramCount) {
	return paramPrefix + prefix + CStringOp::ToString(paramCount);
}

//返回str除$外的参数内容
std::string Field::getParamName(const std::string & str) {
	myAssert(isParam(str));	//断点调试
	return str.substr(paramPrefix.length());
}

//判断paramPrefix是否为str的子串，如果是返回true。即判断str第一个符号是否为$
bool Field::isParam(const std::string & str) {
	return CStringOp::startsWith(str, paramPrefix);
}
