#pragma once

#include <iterator>

#include "ReteNode.h"
#include "../Structure/Condition.h"

//�����ԱOutput��ProductionNode��AlphaMemory��JoinNode����
class ProductionNode : public ReteNode {
	using PositionIndexer = std::pair<size_t, Field::Name>;

	//leftParentΪnet��curentNode��condsΪnet��conditions��cons��infoGetterΪnet��getter��acts
	ReteNodePtr leftParent;
	ConditionVector conds, infoGetter;
	TokenVector WMEToken;
	std::vector<ConditionVector> outputInfos;
	std::vector<std::pair<PositionIndexer, PositionIndexer>> indexerForInfoGetter;

	ConditionVector getOutputInfo(const Token& token) const;
	void buildIndexer();
public:
	ProductionNode(ReteNodePtr leftParent, const ConditionVector& conds, const ConditionVector& infoGetter);
	void print(int level = 0) const;
	const ConditionVector& getConds();
	virtual TokenVector& getOutput() override;
	virtual void clearStatus() override;
	const TokenVector& getOutputToken();
	std::vector<ConditionVector> getOutputInfos();
};

using ProductionNodePtr = std::shared_ptr<ProductionNode>;

namespace std {
	template<>
	struct hash<ProductionNode> {
		size_t operator()(const ProductionNode& node) const {
			return hash<size_t>()(node.serialNumber);
		}
	};

	template<>
	struct hash<ProductionNodePtr> {
		size_t operator()(const ProductionNodePtr& ptr) const {
			return hash<ProductionNode>()(*ptr);
		}
	};
};