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
			//����dict�ҵ���ʱ��ɽ���if���ҵ�Ӧ����$
			if (it != dict.end()) {
				//cout << "sss" << field << endl;
				for (auto&& positionOfInfoGetter : it->second) {
					indexerForInfoGetter.emplace_back(std::make_pair(i, field), positionOfInfoGetter);
				}
				//ɾ��
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
		//Ӧ����JoinNode��getOutput
		//leftParentΪnet��curentNode��net��buildOrShareJoinNode(parent, am, tests, c)�����ö�Ӧ��JoinNode
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
		//�²�Ӧ����joinNode��getOutput
		getOutput();
		//reserve������Ԥ���ռ䣬���ڿռ��ڲ���������Ԫ�ض���������û������µĶ���֮ǰ���������������ڵ�Ԫ�ء������µ�Ԫ��ʱ��Ҫ����push_back()/insert()������
		//������������������һ�������������µĴ�С�� �ڶ���������Ҫ���������е���Ԫ��
		outputInfos.reserve(output.size());
		for (auto&& token : output)
			outputInfos.push_back(getOutputInfo(token));
	}
	return outputInfos;
}
