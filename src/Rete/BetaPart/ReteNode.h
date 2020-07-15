#pragma once

#include <memory>

#include "../Structure/Node.h"
#include "../Structure/Token.h"

class ReteNode : public Node<TokenVector> {
protected:
	bool isReadyForOutput;
public:
	ReteNode(bool isReadyForOutput);
};

//shared_ptr ��C++11�ṩ��һ������ָ���࣬�������κεط�����ʹ��ʱ�Զ�ɾ�����ָ�룬�Ӷ��������������ڴ�й©������ָ������⡣
using ReteNodePtr = std::shared_ptr<ReteNode>;

namespace std {
	template<>
	struct hash<ReteNode> {
		size_t operator()(const ReteNode& node) const {
			return hash<size_t>()(node.serialNumber);
		}
	};
}