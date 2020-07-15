#pragma once

#include "Triples.h"
#include "../../PublicDefine.h"

// WME������ʵ��
// �����洢��Ԫ��
class WME : public Triples {
public:
	template<typename ID, typename Attr, typename Value, typename Rel>
	// ID�����ԡ�ֵ
	WME(const ID& id, const Attr& attr, const Value& value,const Rel& rel);
};

// ���WME��Vector
class WMEVector : public std::vector<WME> {
};

template<typename ID, typename Attr, typename Value,typename Rel>
inline WME::WME(const ID & id, const Attr & attr, const Value & value, const Rel& rel)
	: Triples({ id, attr, value,rel }) {
	myAssert(!Field::isParam(fields.at(0)));
	myAssert(!Field::isParam(fields.at(1)));
	myAssert(!Field::isParam(fields.at(2)));
	myAssert(!Field::isParam(fields.at(3)));
}
