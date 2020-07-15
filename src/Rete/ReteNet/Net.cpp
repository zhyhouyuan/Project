#include "Net.h"

#include "../BetaPart/JoinNode.h"
#include "../BetaPart/DummyTopNode.h"
#include "../BetaPart/TokenFilterNode.h"
#include <iostream>
#include <iomanip>

ParamTestNodeVector Net::getTestsFromCondition(Condition c, const ConditionVector & condsHigherUp) {
	ParamTestNodeVector ret;
	auto&& paramTests = ParamTestNode::generate(c, condsHigherUp);
	//将paramTests复制给ret
	std::copy(paramTests.begin(), paramTests.end(), std::back_inserter(ret));
	return ret;
}

//根据父节点、原子条件头部val、原子条件（attr与value）、condition构造Node。然后返回新构造的节点Node
ReteNodePtr Net::buildOrShareJoinNode(ReteNodePtr parent, AlphaMemoryPtr am
	, const ParamTestNodeVector & tests, const Condition& c) {
	StructForHash node = { parent, am, tests, c };
	//如果map中没有要查找的数据，它返回的迭代器等于end函数返回的迭代器。即find没有找到时都能进入if语句块。相当于遇到net网络中没有的节点都会建立新节点
	//parent是必须的，而且随着迭代貌parent会越来越深
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

//也是在网络中构造Node，和上面有什么不同暂不清楚。因为父级函数没有调用过所以该函数功能未曾使用
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
	//count()返回要查找的key在map的所有key种的出现次数。因为此容器不允许重复，故count()只可能返回 1 或 0，即可判断此key是否存在
	if (conditionToAlphaMemory.count(index) == 0) {
		// 不存在的话就创建新的
		//index.print(1);
		return conditionToAlphaMemory[index] = AlphaMemoryPtr(new AlphaMemory());
	}
	// 存在就直接返回就行
	return conditionToAlphaMemory[index];
}

ReteNodePtr Net::buildOrShareNetworkForConditions(ReteNodePtr parent
	, const ConditionVector & conds, ConditionVector condsHigherUp) {
	for (auto&& c : conds) {
		//目前猜测tests内存的主要内容为val,即$A $B $C。相当于每个原子规则的唯一标识
		auto&& tests = getTestsFromCondition(c, condsHigherUp);
		//目前猜测am存储的是原子规则的原子条件，val属性内的值一律改成*(不限定主语)
		auto&& am = buildOrShareAlphaMemory(c);
		//基本进入else语句块
		if (testAtTokenFilterNode.isNeedFilterToken(c)) {
			parent = buildOrShareTokenFilterNode(parent, am, tests, c);
		}
		else {	
			parent = buildOrShareJoinNode(parent, am, tests, c);
		}
		//push_back在Vector最后添加一个元素（参数为要插入的值）
		condsHigherUp.push_back(c);
	}
	return parent;
}
//建立虚拟根节点
Net::Net() : dummyTopNode(ReteNodePtr((ReteNode*)(new DummyTopNode()))) {
}

size_t i = 0;
void Net::addProduction(const ConditionVector & conditions, const std::vector<Condition>& getter) {
	auto&& curentNode = buildOrShareNetworkForConditions(dummyTopNode, conditions, {});
	resultNodes.insert(ProductionNodePtr(new ProductionNode(curentNode, conditions, getter)));
}

std::vector<ConditionVector> Net::invoke() {
	std::vector<ConditionVector> ret;
	//node循环次数和规则数量一致
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
					//conditionToAlphaMemory存储的是不包含主语的原子条件，如xx的身高是175CM。所以三元组的三层循环中，唯有主语被修改为*且Alpha区域存在相同条件的才可进入if语句块
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

						//不是调用自身，AlphaMemory的同名函数，存储事实区数据output（类型为WME）
						//不是所有wme都放在同一个output内，而是根据find返回不同的it。wme是分别放在不同的output内
						//这正是buildOrShareAlphaMemory使用unordered_map的原因，根据索引找到各自的AlphaMemoryPtr，即各自Alpha内存区有各自的wme
						//实际上，每一个Alpha内存区只有一个wme，wme和alpha对应的unordered_map索引一致
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
					//conditionToAlphaMemory存储的是不包含主语的原子条件，如xx的身高是175CM。所以三元组的三层循环中，唯有主语被修改为*且Alpha区域存在相同条件的才可进入if语句块
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
						//不是调用自身，AlphaMemory的同名函数，存储事实区数据output（类型为WME）
						//不是所有wme都放在同一个output内，而是根据find返回不同的it。wme是分别放在不同的output内
						//这正是buildOrShareAlphaMemory使用unordered_map的原因，根据索引找到各自的AlphaMemoryPtr，即各自Alpha内存区有各自的wme
						//实际上，每一个Alpha内存区只有一个wme，wme和alpha对应的unordered_map索引一
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

// 重写==操作符
bool StructForHash::operator==(const StructForHash & rhs) const {
	return *parent == *rhs.parent && 
		tests == rhs.tests && 
		*alphaMemory == *rhs.alphaMemory && 
		c == rhs.c;
}