#include "Triples.h"

#include "../../PublicDefine.h"
#include "../../StringOp.h"

//返回Field下标
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

//设置Field的部分参数
void Triples::set(Field::Name fieldName, const std::string& v)
{
	size_t index = getIndex(fieldName);
	fields.at(index) = v;
}

//返回Field对应类型名的value
const std::string & Triples::get(Field::Name fieldName) const {
	size_t index = getIndex(fieldName);
	return fields.at(index);
}

//打印三元组
void Triples::print(int level) const {
	std::string prefix = CStringOp::repeat("\t", level);
	std::cout << prefix << fields.at(0) << "," << fields.at(1) << "," << fields.at(2) << "," << fields.at(3)
		<< std::endl;
}
