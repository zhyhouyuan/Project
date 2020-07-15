#pragma once

#include <iterator>

#include "BetaNode.h"
#include "../Structure/Condition.h"

//基类成员Output，ProductionNode、AlphaMemory与JoinNode共享
class JoinNode : public BetaNode {
public:
	JoinNode(ReteNodePtr leftParent, AlphaMemoryPtr rightParent
		, const ParamTestNodeVector& tests, const Condition& c);
	//多态特点。纯虚函数的类是不能用来实例化的，只有子类实现了纯虚函数才有可能被实例化。
	//这样，如果声明一个基类的指针指向子类的实例时就可以调用到这个实现了的虚函数了。
	const TokenVector& getOutput() override;
private:
	bool isPositive;
};