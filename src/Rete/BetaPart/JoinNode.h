#pragma once

#include <iterator>

#include "BetaNode.h"
#include "../Structure/Condition.h"

//�����ԱOutput��ProductionNode��AlphaMemory��JoinNode����
class JoinNode : public BetaNode {
public:
	JoinNode(ReteNodePtr leftParent, AlphaMemoryPtr rightParent
		, const ParamTestNodeVector& tests, const Condition& c);
	//��̬�ص㡣���麯�������ǲ�������ʵ�����ģ�ֻ������ʵ���˴��麯�����п��ܱ�ʵ������
	//�������������һ�������ָ��ָ�������ʵ��ʱ�Ϳ��Ե��õ����ʵ���˵��麯���ˡ�
	const TokenVector& getOutput() override;
private:
	bool isPositive;
};