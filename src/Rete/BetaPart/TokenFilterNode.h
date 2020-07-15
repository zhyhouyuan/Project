#pragma once

#include "BetaNode.h"
#include "../TestNode/TestAtTokenFilterNode.h"

// 过滤类型符合要求的节点
class TokenFilterNode : public BetaNode {
public:
	TokenFilterNode(ReteNodePtr leftParent, AlphaMemoryPtr rightParent,
		const ParamTestNodeVector & tests, const Condition& c, TestAtTokenFilterNode& testAtTokenFilterNode);
	const TokenVector& getOutput() override;
private:
	Condition c;
	bool isPositive;
	TestAtTokenFilterNode& testAtTokenFilterNode;
};