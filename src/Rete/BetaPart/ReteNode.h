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

//shared_ptr 是C++11提供的一种智能指针类，可以在任何地方都不使用时自动删除相关指针，从而帮助彻底消除内存泄漏和悬空指针的问题。
using ReteNodePtr = std::shared_ptr<ReteNode>;

namespace std {
	template<>
	struct hash<ReteNode> {
		size_t operator()(const ReteNode& node) const {
			return hash<size_t>()(node.serialNumber);
		}
	};
}