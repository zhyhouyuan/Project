#include "ProductionNode.h"

#include "../TestNode/ParamTestNode.h"
#include "../Utils/VectorPrinter.h"
#include <iostream>
#include <iomanip>

//
ConditionVector ProductionNode::getOutputInfo(const Token & token) const {
	ConditionVector ret = infoGetter;
	for (auto&& pair : indexerForInfoGetter) {
		auto&& value = token.at(pair.first.first).get(pair.first.second);
		ret.at(pair.second.first).set(pair.second.second, value);
	}
	return ret;
}

void ProductionNode::buildIndexer(){
	using namespace Field;
	std::unordered_map<std::string, std::vector<PositionIndexer>> dict;
	//acts
	for (size_t i = 0; i < infoGetter.size(); ++i) {
		for (auto&& field : { id, attr, value,rel }) {
			auto&& fieldString = infoGetter.at(i).get(field);
			if (Field::isParam(fieldString)) {
				dict[fieldString].emplace_back(i, field);
			}
		}
	}
	//conds
	for (size_t i = 0; i < conds.size(); ++i) {
		for (auto&& field : { id, attr, value }) {
			auto&& fieldString = conds.at(i).get(field);
			auto&& it = dict.find(fieldString);
			//当在dict找到的时候可进入if，找的应该是$
			if (it != dict.end()) {
				//cout << "sss" << field << endl;
				for (auto&& positionOfInfoGetter : it->second) {
					indexerForInfoGetter.emplace_back(std::make_pair(i, field), positionOfInfoGetter);
				}
				//删除
				dict.erase(it);
			}
		}
	}
	myAssert(dict.empty());
}

ProductionNode::ProductionNode(ReteNodePtr leftParent, const ConditionVector & conds, const ConditionVector& infoGetter)
	: ReteNode(false), leftParent(leftParent), conds(conds), infoGetter(infoGetter) {
	buildIndexer();
}

void ProductionNode::print(int level) const {
	//if (!output.empty()) {
		std::cout << "matched productions:" << std::endl;
		VectorPrinter::print(conds, level);
		//std::cout << "matched woking memory elements:" << std::endl;
		//VectorPrinter::print(output, level);
	//}
}

const ConditionVector & ProductionNode::getConds() {
	return conds;
}

TokenVector & ProductionNode::getOutput() {

	if (!isReadyForOutput) {
		//应该是JoinNode的getOutput
		//leftParent为net的curentNode即net里buildOrShareJoinNode(parent, am, tests, c)，正好对应上JoinNode
		output = leftParent->getOutput();
	
		WMEToken = output;
		isReadyForOutput = true;


		//if (!output.empty()) {
		//	ConditionVector condsHigherUp;
		//	for (size_t i = 0; i < conds.size(); ++i) {
		//		auto&& c = conds.at(i);
		//		if (c.getType() == Condition::negetive) {
		//			for (auto&& test : ParamTestNode::generate(c, conds)) {
		//				for (size_t j = 0; j < output.size(); ++j) {
		//					for (auto&& fieldName : { Field::id, Field::attr, Field::value }) {
		//						output.at(j).at(i).set(fieldName, c.get(fieldName));
		//					}
		//					output.at(j).at(i).set(test->fieldOfArg1
		//						, output.at(j).at(test->conditionNumberOfArg2).get(test->fieldOfArg2));
		//				}
		//			}
		//			for (size_t j = 0; j < output.size(); ++j) {
		//				output.at(j).at(i).set(Field::attr, c.get(Field::attr) + "_neq");
		//			}
		//		}
		//	}
		//}
	}
	return output;
}

void ProductionNode::clearStatus() {
	if (isReadyForOutput) {
		isReadyForOutput = false;
		output.clear();
		outputInfos.clear();
		leftParent->clearStatus();
	}
}

const TokenVector& ProductionNode::getOutputToken() {
	return WMEToken;
}

std::vector<ConditionVector> ProductionNode::getOutputInfos() {
	if (!isReadyForOutput) {
		//猜测应该是joinNode的getOutput
		getOutput();
		//reserve是容器预留空间，但在空间内不真正创建元素对象，所以在没有添加新的对象之前，不能引用容器内的元素。加入新的元素时，要调用push_back()/insert()函数。
		//可以有两个参数，第一个参数是容器新的大小， 第二个参数是要加入容器中的新元素
		outputInfos.reserve(output.size());
		for (auto&& token : output)
			outputInfos.push_back(getOutputInfo(token));
	}
	return outputInfos;
}
