#include "Condition.h"

#include "../../StringOp.h"

// ��ʶ�� *
const std::string Condition::arbitraryString = "*"; 

//// isParamΪ�жϲ����Ƿ�$�����жϲ����Ƿ�Ϊval������������false
bool Condition::isConstTest(Field::Name fieldName) const {
	return !Field::isParam(this->get(fieldName));
}

//ֻ�е�����Ϊvalʱ�Ž���if��䣬�����ǰ�val���Ե�ֵһ�ɸĳ� * ���൱�ڲ��޶�����
Condition Condition::getIndex() const {
	Condition ret = *this;
	// id�ǲ�����ʱ�򣬽���
	if (!ret.isConstTest(Field::id))
		// �����������Ϊ * ��
		ret.fields.at(0) = Condition::arbitraryString;
	// attr�ǲ�����ʱ�򣬽���
	if (!ret.isConstTest(Field::attr))
		// �����������Ϊ * ��
		ret.fields.at(1) = Condition::arbitraryString;
	// value�ǲ�����ʱ�򣬽���
	if (!ret.isConstTest(Field::value))
		// �����������Ϊ * ��
		ret.fields.at(2) = Condition::arbitraryString;
	return ret;
}

const Condition::Type & Condition::getType() const {
	return type;
}

// ��ӡ���
void Condition::print(int level) const {
	std::string prefix = CStringOp::repeat("\t", level);
	std::cout << prefix << fields.at(0) << ","
		<< (type == negetive ? "~" : "")
		<< fields.at(1)
		<< "," << fields.at(2) << std::endl;
}

// �е�
bool Condition::operator==(const Condition & rhs) const {
	return (fields.at(0) == rhs.fields.at(0)
		&& fields.at(1) == rhs.fields.at(1)
		&& fields.at(2) == rhs.fields.at(2)
		&& type == rhs.type);
}
