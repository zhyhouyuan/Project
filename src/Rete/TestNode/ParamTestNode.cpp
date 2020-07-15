#include "ParamTestNode.h"

#include "../../PublicDefine.h"
#include <iostream>
#include <iomanip>

ParamTestNode::ParamTestNode(Field::Name fieldOfArg1
	, size_t conditionNumberOfArg2, Field::Name fieldOfArg2)
	: fieldOfArg1(fieldOfArg1), conditionNumberOfArg2(conditionNumberOfArg2)
	, fieldOfArg2(fieldOfArg2) {
}

bool ParamTestNode::operator==(const ParamTestNode & rhs) const {
	return fieldOfArg1 == rhs.fieldOfArg1
		&& conditionNumberOfArg2 == rhs.conditionNumberOfArg2
		&& fieldOfArg2 == rhs.fieldOfArg2;
}

bool ParamTestNode::performTest(const Token & token, const WME & wme) const {
	return token.at(conditionNumberOfArg2).get(fieldOfArg2) == wme.get(fieldOfArg1);
}

//为每个原子规则的val属性建立唯一标志，可能是考虑后续会出现原子规则val属性不同，可能是为了保证什么吧，暂时不清楚val属性不同为的是什么
ParamTestNodeVector ParamTestNode::generate(const Condition& c, const ConditionVector& condsHigherUp) {
	ParamTestNodeVector result;
	//创建一个key为string类型，value为pair类型的unordered_map。pair是将2个数据组合成一组数据结构体
	std::unordered_map<std::string, std::pair<size_t, Field::Name>> dict;
	for (size_t i = 0; i < condsHigherUp.size(); ++i) {
		auto&& cond = condsHigherUp.at(i);
		//condition默认为positive
		if (cond.getType() == Condition::positive) {
			for (auto&& fieldName : { Field::id, Field::attr, Field::value }) {
				auto&& fieldString = cond.get(fieldName);
				//判断字符串内是否含有$，有进入if
				if (Field::isParam(fieldString)) {
					auto&& paramName = Field::getParamName(fieldString);
					dict.insert_or_assign(paramName, std::make_pair(i, fieldName));
				}
			}
		}
	}
	//unordered_set本质是使用hash散列的方式存储数据，是一种使用hash值作为key的容器
	std::unordered_set<std::string> checkSet;
	for (auto&& fieldName : { Field::id, Field::attr, Field::value }) {
		auto&& fieldString = c.get(fieldName);
		//判断condition存储的数值是否符合要求，即val含有$
		if (Field::isParam(fieldString)) {
			auto&& paramName = Field::getParamName(fieldString);
			auto&& it = dict.find(paramName);
			//dict里没有的字段可进入
			if (it != dict.end()) {
				//STL容器的插入操作emplace_back，插入的时候直接构造
				result.emplace_back(fieldName, it->second.first, it->second.second);
			}
			else {
				myAssert(checkSet.count(paramName) == 0);
				checkSet.insert(paramName);
			}
		}
	}
	return result;
}

//bool TestNodeVector::performJoinTest(const Token & token, const WME & wme) const {
//	for (auto&& test : *this) {
//		if (!test.performTest(token, wme))
//			return false;
//	}
//	return true;
//}
