#pragma once

#include <vector>
#include <string>

#include "Field.h"
#include "../../StringOp.h"

// 三元组类！！
class Triples
{
protected:
	std::vector<std::string> fields;
	size_t getIndex(Field::Name fieldName) const;
public:
	template<typename ID, typename Attr, typename Value, typename Rel>
	// 模板函数，虚拟数据类型：ID、Attr、Value
	Triples(const ID& id, const Attr& attr, const Value& value,const Rel& rel);
	void set(Field::Name fieldName, const std::string& v);
	const std::string& get(Field::Name fieldName) const;
	void print(int level) const;
};

template<typename ID, typename Attr, typename Value, typename Rel>
// inline 内联函数，用于提高效率防止栈空间耗尽
inline Triples::Triples(const ID & id, const Attr & attr, const Value & value,const Rel& rel)
	: fields({ CStringOp::ToString(id), CStringOp::ToString(attr), CStringOp::ToString(value) ,CStringOp::ToString(rel) }) {
}