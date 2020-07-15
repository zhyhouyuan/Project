#include <iostream>

#include "ReteNet/Net.h"
#include "TestNode/TestAtTokenFilterNode.h"
#include "../Log.h"
#include "../StringOp.h"
#include "Utils/VectorPrinter.h"
#include "../PublicDefine.h"
// 添加进到xml解析
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
LHS：条件集合
RHS：动作集合
PM：产生式集合
*/
void test() {
	// 先建立一个网络
	Net net;

	// 读取文件
	//file<> fdoc("C:\\Users\\10679\\Desktop\\demo.xml");
	file<> fdoc("C:\\Users\\zhy\\Desktop\\demo.xml");
	
	// 获取数据
	xml_document<> doc;
	doc.parse<0>(fdoc.data());
	// 读取数据
	// 根节点
	xml_node<>* rules = doc.first_node("rules");
	// 两个容器
	ConditionVector cons;
	vector<Condition> acts;
	//遍历原子规则
	for (xml_node<>* rule = rules->first_node("rule"); NULL != rule; rule = rule->next_sibling()) {
		// 拿到两个总的节点，next_sibling返回指定节点之后的下一个兄弟节点
		xml_node<>* lhs = rule->first_node("lhs");
		xml_node<>* rhs = rule->first_node("rhs");
		// 遍历lhs
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
		// 遍历rhs
		for (xml_node<>* action = rhs->first_node("action"); action != NULL; action = action->next_sibling()) {
			xml_attribute<char>* val = action->first_attribute("val");
			xml_attribute<char>* relation = action->first_attribute("relation");
			xml_attribute<char>* res = action->first_attribute("res");
			xml_attribute<char>* rel = action->first_attribute("rel");

			Condition act(val->value(), relation->value(), res->value(),rel->value());
			//cout << val->value() << endl;
			acts.push_back(act);
		}
		// 插入到网络中
		net.addProduction(cons, acts);
		// 然后清空两个容器准备下一轮
		cons.clear();
		acts.clear();
	}

	//true为treat算法，false为rete算法
	bool selectAlgorithm = false;
	//treat
	if (selectAlgorithm) {
		vector<vector<ConditionVector>> ans;
		ans.push_back(net.TreataddWME({ "小红", ".sex", "female",">" }));
		auto&& ans2 = net.TreataddWME({ "小明", ".height", "180cm",">" });
		auto&& ans3 = net.TreataddWME({ "小明", ".weight", "70kg","=" });
		auto&& ans4 = net.TreataddWME({ "小红", ".weight", "45kg","=" });
		auto&& ans5 = net.TreataddWME({ "小红", ".height", "145cm","=" });
		auto&& ans6 = net.TreataddWME({ "小明", ".age", "24","=" });
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
		net.addWME({ "小红", ".sex", "female","=" });
		net.addWME({ "小明", ".height", "190cm",">" });
		net.addWME({ "小明", ".weight", "70kg" ,"=" });
		net.addWME({ "小红", ".weight", "46kg",">" });
		net.addWME({ "小红", ".height", "145cm" ,"=" });
		net.addWME({ "小明", ".age", "24" ,"=" });

		
		net.addWME({ "小明", ".height.aa", "200cm",">" });

		//net.addWME({ "小明", ".is_a", "footballPlayer","=" });
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

		//net.addWME({ "小明", ".is_a", "footballPlayer","=" });

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
