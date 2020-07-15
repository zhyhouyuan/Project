#pragma once

#include <unordered_map>
#include <unordered_set>
#include <iterator>

#include "../../PublicDefine.h"
#include "../TestNode/TestAtTokenFilterNode.h"
#include "../BetaPart/BetaNode.h"
#include "../Structure/Condition.h"
#include "../AlphaPart/AlphaMemory.h"
#include "../BetaPart/ProductionNode.h"
#include "../TestNode/ParamTestNode.h"

struct StructForHash {
	// 结构体
	ReteNodePtr parent;
	AlphaMemoryPtr alphaMemory;
	ParamTestNodeVector tests;
	Condition c;
	bool operator== (const StructForHash& rhs) const;
};

namespace std {
	template<>
	struct hash<StructForHash> {
		std::size_t operator()(const StructForHash& obj) const {
			size_t ret = 2166136261;
			// HashJoin？？？
			ret = (ret * 16777619) ^ hash<ReteNode>()(*obj.parent);
			ret = (ret * 16777619) ^ hash<AlphaMemory>()(*obj.alphaMemory);
			ret = (ret * 16777619) ^ hash<ParamTestNodeVector>()(obj.tests);
			ret = (ret * 16777619) ^ hash<Condition>()(obj.c);
			return ret;
		}
	};
}

class Net {
	ReteNodePtr dummyTopNode; //虚拟顶层节点？
	TestAtTokenFilterNode testAtTokenFilterNode;
	//事实冲突集
	vector<TokenVector> ConflictSet;
	// 存储条件和alpha节点的map
	std::unordered_map<Condition, AlphaMemoryPtr> conditionToAlphaMemory;
	// 存储条件和规则条件组
	//std::unordered_map<Condition, ProductionNodePtr> conditionToProNode;
	// 存储rete网络节点
	std::unordered_map<StructForHash, ReteNodePtr> dict;

	ParamTestNodeVector getTestsFromCondition(Condition c
		, const ConditionVector& condsHigherUp);
	ReteNodePtr buildOrShareJoinNode(ReteNodePtr parent, AlphaMemoryPtr am
		, const ParamTestNodeVector& tests, const Condition& c);
	ReteNodePtr buildOrShareTokenFilterNode(ReteNodePtr parent, AlphaMemoryPtr am
		, const ParamTestNodeVector & tests, const Condition& c);
	AlphaMemoryPtr buildOrShareAlphaMemory(const Condition& c);
	ReteNodePtr buildOrShareNetworkForConditions(ReteNodePtr parent
		, const ConditionVector& conds, ConditionVector condsHigherUp);
	// 结果set
	std::unordered_set<ProductionNodePtr> resultNodes;
public:
	// 构造函数
	Net();
	void addProduction(const ConditionVector& conditions, const std::vector<Condition>& getter);
	std::vector<ConditionVector> invoke();
	void clearStatus();
	const vector<TokenVector>& getOutputConflictSet();
	std::vector<ConditionVector> TreataddWME(const WME& wme);
	void addWME(const WME& wme);
	void addFunction(const std::string& key, TestAtTokenFilterNode::JudgeFunctionType judgeFunction);
	bool Net::findAlph(std::unordered_map<Condition, AlphaMemoryPtr>::iterator &it, Condition c0);
	size_t findindex(string a0);
};