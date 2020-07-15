#include "Condition.h"

#include "../../StringOp.h"

// 标识符 *
const std::string Condition::arbitraryString = "*"; 

//// isParam为判断参数是否含$，即判断参数是否为val，是则函数返回false
bool Condition::isConstTest(Field::Name fieldName) const {
	return !Field::isParam(this->get(fieldName));
}

//只有当属性为val时才进入if语句，作用是把val属性的值一律改成 * ，相当于不限定主语
Condition Condition::getIndex() const {
	Condition ret = *this;
	// id是参数的时候，进入
	if (!ret.isConstTest(Field::id))
		// 把这个参数置为 * ？
		ret.fields.at(0) = Condition::arbitraryString;
	// attr是参数的时候，进入
	if (!ret.isConstTest(Field::attr))
		// 把这个参数置为 * ？
		ret.fields.at(1) = Condition::arbitraryString;
	// value是参数的时候，进入
	if (!ret.isConstTest(Field::value))
		// 把这个参数置为 * ？
		ret.fields.at(2) = Condition::arbitraryString;
	return ret;
}

const Condition::Type & Condition::getType() const {
	return type;
}

// 打印输出
void Condition::print(int level) const {
	std::string prefix = CStringOp::repeat("\t", level);
	std::cout << prefix << fields.at(0) << ","
		<< (type == negetive ? "~" : "")
		<< fields.at(1)
		<< "," << fields.at(2) << std::endl;
}

// 判等
bool Condition::operator==(const Condition & rhs) const {
	return (fields.at(0) == rhs.fields.at(0)
		&& fields.at(1) == rhs.fields.at(1)
		&& fields.at(2) == rhs.fields.at(2)
		&& type == rhs.type);
}
