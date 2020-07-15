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
	// �ṹ��
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
			// HashJoin������
			ret = (ret * 16777619) ^ hash<ReteNode>()(*obj.parent);
			ret = (ret * 16777619) ^ hash<AlphaMemory>()(*obj.alphaMemory);
			ret = (ret * 16777619) ^ hash<ParamTestNodeVector>()(obj.tests);
			ret = (ret * 16777619) ^ hash<Condition>()(obj.c);
			return ret;
		}
	};
}

class Net {
	ReteNodePtr dummyTopNode; //���ⶥ��ڵ㣿
	TestAtTokenFilterNode testAtTokenFilterNode;
	//��ʵ��ͻ��
	vector<TokenVector> ConflictSet;
	// �洢������alpha�ڵ��map
	std::unordered_map<Condition, AlphaMemoryPtr> conditionToAlphaMemory;
	// �洢�����͹���������
	//std::unordered_map<Condition, ProductionNodePtr> conditionToProNode;
	// �洢rete����ڵ�
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
	// ���set
	std::unordered_set<ProductionNodePtr> resultNodes;
public:
	// ���캯��
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