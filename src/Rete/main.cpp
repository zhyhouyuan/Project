#include <iostream>

#include "ReteNet/Net.h"
#include "TestNode/TestAtTokenFilterNode.h"
#include "../Log.h"
#include "../StringOp.h"
#include "Utils/VectorPrinter.h"
#include "../PublicDefine.h"
// ��ӽ���xml����
#include "../rapidxml.hpp"
#include "../rapidxml_iterators.hpp"
#include "../rapidxml_print.hpp"
#include "../rapidxml_utils.hpp"
#include <vector>
#include <string>
#include <map>
#include <typeinfo>
#include "../../clipscpp.h"

using namespace rapidxml;

/*
LHS����������
RHS����������
PM������ʽ����
*/
void test() {
	// �Ƚ���һ������
	Net net;

	// ��ȡ�ļ�
	//file<> fdoc("C:\\Users\\10679\\Desktop\\demo.xml");
	file<> fdoc("C:\\Users\\zhy\\Desktop\\demo.xml");
	
	// ��ȡ����
	xml_document<> doc;
	doc.parse<0>(fdoc.data());
	// ��ȡ����
	// ���ڵ�
	xml_node<>* rules = doc.first_node("rules");
	// ��������
	ConditionVector cons;
	vector<Condition> acts;
	//����ԭ�ӹ���
	for (xml_node<>* rule = rules->first_node("rule"); NULL != rule; rule = rule->next_sibling()) {
		// �õ������ܵĽڵ㣬next_sibling����ָ���ڵ�֮�����һ���ֵܽڵ�
		xml_node<>* lhs = rule->first_node("lhs");
		xml_node<>* rhs = rule->first_node("rhs");
		// ����lhs
		for (xml_node<>* condition = lhs->first_node("condition"); condition != NULL; condition = condition->next_sibling()) {
			xml_attribute<char>* val = condition->first_attribute("val");
			xml_attribute<char>* relation = condition->first_attribute("relation");
			xml_attribute<char>* res = condition->first_attribute("res");
			xml_attribute<char>* rel = condition->first_attribute("rel");

			Condition con(val->value(), relation->value(), res->value(),rel->value());
			//con.print(0);
			//cout << relation->value() << endl;
			cons.push_back(con);
			
		}
		// ����rhs
		for (xml_node<>* action = rhs->first_node("action"); action != NULL; action = action->next_sibling()) {
			xml_attribute<char>* val = action->first_attribute("val");
			xml_attribute<char>* relation = action->first_attribute("relation");
			xml_attribute<char>* res = action->first_attribute("res");
			xml_attribute<char>* rel = action->first_attribute("rel");

			Condition act(val->value(), relation->value(), res->value(),rel->value());
			//cout << val->value() << endl;
			acts.push_back(act);
		}
		// ���뵽������
		net.addProduction(cons, acts);
		// Ȼ�������������׼����һ��
		cons.clear();
		acts.clear();
	}

	//trueΪtreat�㷨��falseΪrete�㷨
	bool selectAlgorithm = false;
	//treat
	if (selectAlgorithm) {
		vector<vector<ConditionVector>> ans;
		ans.push_back(net.TreataddWME({ "С��", ".sex", "female",">" }));
		auto&& ans2 = net.TreataddWME({ "С��", ".height", "180cm",">" });
		auto&& ans3 = net.TreataddWME({ "С��", ".weight", "70kg","=" });
		auto&& ans4 = net.TreataddWME({ "С��", ".weight", "45kg","=" });
		auto&& ans5 = net.TreataddWME({ "С��", ".height", "145cm","=" });
		auto&& ans6 = net.TreataddWME({ "С��", ".age", "24","=" });
		ans.push_back(ans2);
		ans.push_back(ans3);
		ans.push_back(ans4);
		ans.push_back(ans5);
		ans.push_back(ans6);

		//auto&& Conflict = net.getOutputConflictSet();

		cout << "Treat:" << endl;
		for (auto&& VecCon : ans) {
			for (auto&& condVec : VecCon) {
				for (auto&& cond : condVec) {
					cond.print(0);
				}
				puts("");
			}
		}
		system("pause");
	}
	//rete
	else {
		net.addWME({ "С��", ".sex", "female","=" });
		net.addWME({ "С��", ".height", "190cm",">" });
		net.addWME({ "С��", ".weight", "70kg" ,"=" });
		net.addWME({ "С��", ".weight", "46kg",">" });
		net.addWME({ "С��", ".height", "145cm" ,"=" });
		net.addWME({ "С��", ".age", "24" ,"=" });

		
		net.addWME({ "С��", ".height.aa", "200cm",">" });

		//net.addWME({ "С��", ".is_a", "footballPlayer","=" });
		//cout << "Rete:" << endl;
		for (auto&& condVec : net.invoke()){
			for (auto&& cond : condVec){
				net.addWME({cond.get(Field::id), cond.get(Field::attr), cond.get(Field::value), cond.get(Field::rel)});
				//cout << cond.get(Field::id) << cond.get(Field::attr) << cond.get(Field::value) << cond.get(Field::rel) << endl;
				//cond.print(0);
			}
			//puts("");
		}
		
		net.clearStatus();

		//net.addWME({ "С��", ".is_a", "footballPlayer","=" });

		for (auto&& condVec : net.invoke()) {
			for (auto&& cond : condVec) {
				cond.print(0);
			}
			puts("");
		}
		system("pause");
	}

}


int main() {
	test();
	//CLIPS::CLIPSCPPEnv theEnv;

	//theEnv.Load("C:\\Users\\hasee\\Desktop\\killing.clp");

	//theEnv.Reset();
	//theEnv.Run(-1);

	return 0;
}
