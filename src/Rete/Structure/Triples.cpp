#include "Triples.h"

#include "../../PublicDefine.h"
#include "../../StringOp.h"

//����Field�±�
size_t Triples::getIndex(Field::Name fieldName) const
{
	size_t index;
	switch (fieldName)
	{
	case Field::id:
		index = 0;
		break;
	case Field::attr:
		index = 1;
		break;
	case Field::value:
		index = 2;
		break;
	case Field::rel:
		index = 3;
		break;
	default:
		myAssert(false);
	}
	return index;
}

//����Field�Ĳ��ֲ���
void Triples::set(Field::Name fieldName, const std::string& v)
{
	size_t index = getIndex(fieldName);
	fields.at(index) = v;
}

//����Field��Ӧ��������value
const std::string & Triples::get(Field::Name fieldName) const {
	size_t index = getIndex(fieldName);
	return fields.at(index);
}

//��ӡ��Ԫ��
void Triples::print(int level) const {
	std::string prefix = CStringOp::repeat("\t", level);
	std::cout << prefix << fields.at(0) << "," << fields.at(1) << "," << fields.at(2) << "," << fields.at(3)
		<< std::endl;
}
