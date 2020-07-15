#include "Net.h"

#include "../BetaPart/JoinNode.h"
#include "../BetaPart/DummyTopNode.h"
#include "../BetaPart/TokenFilterNode.h"
#include <iostream>
#include <iomanip>

ParamTestNodeVector Net::getTestsFromCondition(Condition c, const ConditionVector & condsHigherUp) {
	ParamTestNodeVector ret;
	auto&& paramTests = ParamTestNode::generate(c, condsHigherUp);
	//��paramTests���Ƹ�ret
	std::copy(paramTests.begin(), paramTests.end(), std::back_inserter(ret));
	return ret;
}

//���ݸ��ڵ㡢ԭ������ͷ��val��ԭ��������attr��value����condition����Node��Ȼ�󷵻��¹���Ľڵ�Node
ReteNodePtr Net::buildOrShareJoinNode(ReteNodePtr parent, AlphaMemoryPtr am
	, const ParamTestNodeVector & tests, const Condition& c) {
	StructForHash node = { parent, am, tests, c };
	//���map��û��Ҫ���ҵ����ݣ������صĵ���������end�������صĵ���������findû���ҵ�ʱ���ܽ���if���顣�൱������net������û�еĽڵ㶼�Ὠ���½ڵ�
	//parent�Ǳ���ģ��������ŵ���òparent��Խ��Խ��
	auto&& it = dict.find(node);
	if (it == dict.end()) {
		auto&& ret = ReteNodePtr((ReteNode*)new JoinNode(parent, am, tests, c));
		dict.insert(std::make_pair(node, ret));
		return ret;
	}
	else {
		return it->second;
	}
}

//Ҳ���������й���Node����������ʲô��ͬ�ݲ��������Ϊ��������û�е��ù����Ըú�������δ��ʹ��
ReteNodePtr Net::buildOrShareTokenFilterNode(ReteNodePtr parent, AlphaMemoryPtr am
	, const ParamTestNodeVector & tests, const Condition& c) {
	StructForHash node = { parent, am, tests, c };
	auto&& it = dict.find(node);
	if (it == dict.end()) {
		auto&& ret = ReteNodePtr(new TokenFilterNode(parent, am, tests, c, testAtTokenFilterNode));
		dict.insert(std::make_pair(node, ret));
		return ret;
	}
	else
		return it->second;
}

AlphaMemoryPtr Net::buildOrShareAlphaMemory(const Condition & c) {
	auto&& index = c.getIndex();
	//count()����Ҫ���ҵ�key��map������key�ֵĳ��ִ�������Ϊ�������������ظ�����count()ֻ���ܷ��� 1 �� 0�������жϴ�key�Ƿ����
	if (conditionToAlphaMemory.count(index) == 0) {
		// �����ڵĻ��ʹ����µ�
		//index.print(1);
		return conditionToAlphaMemory[index] = AlphaMemoryPtr(new AlphaMemory());
	}
	// ���ھ�ֱ�ӷ��ؾ���
	return conditionToAlphaMemory[index];
}

ReteNodePtr Net::buildOrShareNetworkForConditions(ReteNodePtr parent
	, const ConditionVector & conds, ConditionVector condsHigherUp) {
	for (auto&& c : conds) {
		//Ŀǰ�²�tests�ڴ����Ҫ����Ϊval,��$A $B $C���൱��ÿ��ԭ�ӹ����Ψһ��ʶ
		auto&& tests = getTestsFromCondition(c, condsHigherUp);
		//Ŀǰ�²�am�洢����ԭ�ӹ����ԭ��������val�����ڵ�ֵһ�ɸĳ�*(���޶�����)
		auto&& am = buildOrShareAlphaMemory(c);
		//��������else����
		if (testAtTokenFilterNode.isNeedFilterToken(c)) {
			parent = buildOrShareTokenFilterNode(parent, am, tests, c);
		}
		else {	
			parent = buildOrShareJoinNode(parent, am, tests, c);
		}
		//push_back��Vector������һ��Ԫ�أ�����ΪҪ�����ֵ��
		condsHigherUp.push_back(c);
	}
	return parent;
}
//����������ڵ�
Net::Net() : dummyTopNode(ReteNodePtr((ReteNode*)(new DummyTopNode()))) {
}

size_t i = 0;
void Net::addProduction(const ConditionVector & conditions, const std::vector<Condition>& getter) {
	auto&& curentNode = buildOrShareNetworkForConditions(dummyTopNode, conditions, {});
	resultNodes.insert(ProductionNodePtr(new ProductionNode(curentNode, conditions, getter)));
}

std::vector<ConditionVector> Net::invoke() {
	std::vector<ConditionVector> ret;
	//nodeѭ�������͹�������һ��
	for (auto&& node : resultNodes) {
		auto&& infos = node->getOutputInfos();
		std::copy(infos.begin(), infos.end(), std::back_inserter(ret));
		//cout << "***************************************" << endl;
	}
	return ret;
}

void Net::clearStatus(){
	for (auto&& node : resultNodes) {
		node->clearStatus();
	}
}

std::vector<ConditionVector> Net::TreataddWME(const WME & wme) {
	std::vector<ConditionVector> ret;
	std::vector<std::vector<std::string>> vt = {
		{ wme.get(Field::id), Condition::arbitraryString },
		{ wme.get(Field::attr), Condition::arbitraryString },
		{ wme.get(Field::value), Condition::arbitraryString },
		{ wme.get(Field::rel), Condition::arbitraryString },
	};
	int x = 0;
	int y = 0;
	int z = 0;
	int zz = 0;
	//auto&& wmeCon = Condition(wme.get(Field::id), wme.get(Field::attr), wme.get(Field::value));
	//cout << "~~~~~~~~~~~~~~$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	//wmeCon.print(1);
	//cout << "~~~~~~~~~~~~~~$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	for (auto&& id : vt.at(0)) {
		x++;
		for (auto&& attr : vt.at(1)) {
			y++;
			for (auto&& value : vt.at(2)) {
				z++;
				for (auto&& rel : vt.at(3)) {
					zz++;
					//conditionToAlphaMemory�洢���ǲ����������ԭ����������xx�������175CM��������Ԫ�������ѭ���У�Ψ�����ﱻ�޸�Ϊ*��Alpha���������ͬ�����Ĳſɽ���if����
					auto&& it = conditionToAlphaMemory.find(Condition(id, attr, value, rel));
					if (it != conditionToAlphaMemory.end())
					{
						//it->second->addNewWME(wme);
						clearStatus();
						//cout << "id:" << id << "  attr:" << attr << "  value:" << value << endl;
						//cout << "-----" << x << "-----" << y << "-----" << z << "-----" << endl;
						for (auto&& node : resultNodes) {  
							for (auto&& condi : node->getConds()) {
								if (condi.getIndex() == Condition(id, attr, value,rel)) {
									it->second->addNewWME(wme);
									//wme.print(1);
									auto&& infos = node->getOutputInfos();
									std::copy(infos.begin(), infos.end(), std::back_inserter(ret));
									//cout << "***************************************" << endl;
									if (!ret.empty()) {
										//cout << "ConflictSet" << endl;
										ConflictSet.push_back(node->getOutputToken());
									}
								}
							}
							//it->second->addNewWME(wme);
							//auto&& infos = node->getOutputInfos();
							//std::copy(infos.begin(), infos.end(), std::back_inserter(ret));
							//cout << "***************************************" << endl;
						}

						//���ǵ�������AlphaMemory��ͬ���������洢��ʵ������output������ΪWME��
						//��������wme������ͬһ��output�ڣ����Ǹ���find���ز�ͬ��it��wme�Ƿֱ���ڲ�ͬ��output��
						//������buildOrShareAlphaMemoryʹ��unordered_map��ԭ�򣬸��������ҵ����Ե�AlphaMemoryPtr��������Alpha�ڴ����и��Ե�wme
						//ʵ���ϣ�ÿһ��Alpha�ڴ���ֻ��һ��wme��wme��alpha��Ӧ��unordered_map����һ��
						it->second->addWME(wme);
						it->second->clearAddNewStatus();
						clearStatus();
						return ret;
					}
				}
			}
		}
	}
}

void Net::addWME(const WME& wme) {
	std::vector<std::vector<std::string>> vt = {
		{ wme.get(Field::id), Condition::arbitraryString },
		{ wme.get(Field::attr), Condition::arbitraryString },
		{ wme.get(Field::value), Condition::arbitraryString },
		{ wme.get(Field::rel), Condition::arbitraryString },
	};
	int x = 0;
	int y = 0;
	int z = 0;
	int zz = 0;
	for (auto&& id : vt.at(0)) {
		//cout << "id:" << id << endl;
		x++;
		auto&& attr = vt.at(1).front();
		auto&& value =vt.at(2).front();
		auto&& rel = vt.at(3).front();
		//for (auto&& attr : vt.at(1)) {
			//cout << "attr:" << attr << endl;
			//y++;
			//for (auto&& value : vt.at(2)) {
				//cout << "value:" << value << endl;
				//z++;
				//for (auto&& rel : vt.at(3)) {
					//zz++;
					//conditionToAlphaMemory�洢���ǲ����������ԭ����������xx�������175CM��������Ԫ�������ѭ���У�Ψ�����ﱻ�޸�Ϊ*��Alpha���������ͬ�����Ĳſɽ���if����
					//auto&& it = conditionToAlphaMemory.find(Condition(id, attr, value, rel));
					std::unordered_map<Condition, AlphaMemoryPtr>::iterator it;
					it = conditionToAlphaMemory.begin();
					//cout << attr<<endl;
					bool flag=findAlph(it, Condition(id, attr, value, rel));
					cout << "bbb"<< endl;
					//cout << (it == conditionToAlphaMemory.end()) << (it == conditionToAlphaMemory.begin()) << endl;
					if (it != conditionToAlphaMemory.end())
					{
						//cout << "+ABC+" << endl;  
						//���ǵ�������AlphaMemory��ͬ���������洢��ʵ������output������ΪWME��
						//��������wme������ͬһ��output�ڣ����Ǹ���find���ز�ͬ��it��wme�Ƿֱ���ڲ�ͬ��output��
						//������buildOrShareAlphaMemoryʹ��unordered_map��ԭ�򣬸��������ҵ����Ե�AlphaMemoryPtr��������Alpha�ڴ����и��Ե�wme
						//ʵ���ϣ�ÿһ��Alpha�ڴ���ֻ��һ��wme��wme��alpha��Ӧ��unordered_map����һ
						//cout << "aaaaaaa"<<endl;
						it->second->addWME(wme);
					}
				//}
			//}
		//}
	}
}
bool Net::findAlph(std::unordered_map<Condition, AlphaMemoryPtr>::iterator &it,Condition c0) {
	int a = 0;
	while (it != conditionToAlphaMemory.end()) {
		if ((*it).first.get(Field::id) == c0.get(Field::id) && (*it).first.get(Field::attr) == c0.get(Field::attr)) {
			if ((*it).first.get(Field::rel) == c0.get(Field::rel) && (*it).first.get(Field::value) == c0.get(Field::value)) {
				return 1;
			}
			if ((*it).first.get(Field::rel) == ">") {
				auto index0 = findindex((*it).first.get(Field::value));
				auto len0 = (*it).first.get(Field::value).length() - index0;
				auto index1 = findindex(c0.get(Field::value));
				auto len1 = c0.get(Field::value).length() - index0;
				//cout << (*it).first.get(Field::value).substr(0, findindex((*it).first.get(Field::value)))<<"   " << stod(c0.get(Field::value).substr(0, findindex(c0.get(Field::value)))) << endl;
				if ((c0.get(Field::rel) == ">" || c0.get(Field::rel) == "=")&& stod((*it).first.get(Field::value).substr(0, index0)) <= stod(c0.get(Field::value).substr(0, index1))&& (*it).first.get(Field::value).substr(index0,len0)== c0.get(Field::value).substr(index0,len0)) {
					
					return 1;
				}
			}
			if ((*it).first.get(Field::rel) == "<") {
				auto index0 = findindex((*it).first.get(Field::value));
				auto len0 = (*it).first.get(Field::value).length() - index0;
				auto index1 = findindex(c0.get(Field::value));
				auto len1 = c0.get(Field::value).length() - index0;
				cout << (*it).first.get(Field::value).substr(0, findindex((*it).first.get(Field::value)))<<endl;
				if ((c0.get(Field::rel) == "<" || c0.get(Field::rel) == "=") && stod((*it).first.get(Field::value).substr(0, index0)) >= stod(c0.get(Field::value).substr(0, index1)) && (*it).first.get(Field::value).substr(index0, len0) == c0.get(Field::value).substr(index0, len0)) {
					return 1;
				}
			}
			it++;
		}
		else {
			it++;
			a++;
			//cout << "cc" <<(it==conditionToAlphaMemory.end())<< endl;
		}
	  }
	return 0;

}
size_t Net::findindex(string a0) {
	for (int i = 0;i < a0.size();i++) {
		if (a0[i] > '9' || a0[i] < '0')
			return i;
	}
	return a0.size() - 1;
}

void Net::addFunction(const std::string & key, TestAtTokenFilterNode::JudgeFunctionType judgeFunction) {
	testAtTokenFilterNode.insertJudgeFunction(key, judgeFunction);
}

const vector<TokenVector>& Net::getOutputConflictSet() {
	return ConflictSet;
}

// ��д==������
bool StructForHash::operator==(const StructForHash & rhs) const {
	return *parent == *rhs.parent && 
		tests == rhs.tests && 
		*alphaMemory == *rhs.alphaMemory && 
		c == rhs.c;
}