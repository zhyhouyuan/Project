#pragma once

template <typename O>
class Node {
	static size_t count;
protected:
	O output;
public:
	size_t serialNumber;
	Node();
	// 两个纯虚函数，设置纯虚函数的目的是其派生类忘记实现基类方法
	virtual const O& getOutput() = 0;
	virtual void clearStatus() = 0;
	// 重载==运算符
	bool operator==(const Node<O>& rhs) const;
};

template <typename O>
size_t Node<O>::count = 0;

// 注意：非线程安全
template<typename O>
inline Node<O>::Node() : serialNumber(count++) {
}

template<typename O>
inline bool Node<O>::operator==(const Node<O>& rhs) const {
	return serialNumber == rhs.serialNumber;
}
