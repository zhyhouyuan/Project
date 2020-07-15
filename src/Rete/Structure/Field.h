#pragma once

#include <string>

#include "../../StringOp.h"

namespace Field
{
	// 枚举类型，Name是类型名，枚举的话只取这几种中的某一个
	enum Name {
		id,
		attr,
		value,
		rel,
		undefined,
	};
	extern std::string paramPrefix;

	template<typename T>
	std::string getParamString(const T& paramName);
	std::string getParamString(const std::string& prefix, size_t paramCount);
	std::string getParamName(const std::string& str);
	bool isParam(const std::string& str);
};


template<typename T>
inline std::string Field::getParamString(const T & paramName) {
	return paramPrefix + CStringOp::ToString(paramName);
}
