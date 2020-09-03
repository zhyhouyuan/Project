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
#include <windows.h>

using namespace rapidxml;


extern "C" _declspec(dllexport) void reason(string);
extern "C" _declspec(dllexport) void getwme_rule(string, string);


// ��ʽ�������ķ���
std::string format(std::string str) {
	if (CStringOp::startsWith(str, ".")) {
		str.assign(CStringOp::replaceAll(str, ".", ""));
	}
	if (CStringOp::startsWith(str, "$")) {
		str.assign(CStringOp::replaceAll(str, "$", "?"));
	}
	return str;
}

/*
LHS����������
RHS����������
PM������ʽ����
*/

std::string wmesname = "./wmes.xml";
std::string rulename = "./rule_out.xml";
int  count_wme = 0;

void getwme_rule(string name1, string name2) {
	wmesname = name1;
	rulename = name2;
}

void reason(string algoStr) {

	// ��ȡ�ļ�

	ofstream logs("./logs.txt", ios::app);

	try
	{
		file<> rule_file(rulename.c_str());
		file<> wme_file(wmesname.c_str());
		// ��ȡ����
		xml_document<> rule_doc, wme_doc;
		rule_doc.parse<0>(rule_file.data());
		wme_doc.parse<0>(wme_file.data());

		if (algoStr == "rete" || algoStr == "treat") {
			// �Ƚ���һ������
			Net net;
			file<> fdoc(rulename.c_str());
			// ��ȡ����
			// ���ڵ�
			xml_node<>* rules = rule_doc.first_node("rulebase");
			// ��������
			ConditionVector cons;
			vector<Condition> acts;
			//����ԭ�ӹ���
			for (xml_node<>* rulesub = rules->first_node("rulesubbase"); NULL != rulesub; rulesub = rulesub->next_sibling()) {
				for (xml_node<>* rule = rulesub->first_node("rule"); NULL != rule; rule = rule->next_sibling()) {
					// �õ������ܵĽڵ㣬next_sibling����ָ���ڵ�֮�����һ���ֵܽڵ�
					xml_node<>* lhs = rule->first_node("lhs");
					xml_node<>* rhs = rule->first_node("rhs");
					xml_node<>* weight = rule->first_node("weight");
					// ����lhs
					for (xml_node<>* condition = lhs->first_node("condition"); condition != NULL; condition = condition->next_sibling()) {
						xml_attribute<char>* var = condition->first_attribute("var");
						xml_attribute<char>* prop = condition->first_attribute("prop");
						xml_attribute<char>* relation = condition->first_attribute("relation");
						xml_attribute<char>* value = condition->first_attribute("value");

						// ��־д��
						CLog::write(algoStr + "LHS", string(var->value()) + string(prop->value()) + string(relation->value()) + string(value->value()), logs);

						Condition con(var->value(), prop->value(), value->value(), relation->value());
						//con.print(0);
						//cout << relation->value() << endl;
						cons.push_back(con);

					}
					// ����rhs
					for (xml_node<>* action = rhs->first_node("action"); action != NULL; action = action->next_sibling()) {
						xml_attribute<char>* var = action->first_attribute("var");
						xml_attribute<char>* prop = action->first_attribute("prop");
						xml_attribute<char>* relation = action->first_attribute("relation");
						xml_attribute<char>* value = action->first_attribute("value");

						// ��־д��
						CLog::write(algoStr + "RHS", string(var->value()) + string(prop->value()) + string(relation->value()) + string(value->value()), logs);

						Condition act(var->value(), prop->value(), value->value(), relation->value());
						//cout << val->value() << endl;
						acts.push_back(act);
					}

					std::int32_t W = std::stoi(weight->value());
					// cout << W << endl;
					// ���뵽������
					net.addProduction(cons, acts, W);
					// Ȼ�������������׼����һ��
					cons.clear();
					acts.clear();
				}
			}

			// ���ڵ�
			xml_node<>* wmes = wme_doc.first_node("wmes");
			// ��������
			vector<WME> wmefacts;
			int  count0 = 0;
			if (wmes != NULL) {
				for (xml_node<>* wme = wmes->first_node("wme"); wme != NULL; wme = wme->next_sibling()) {
					xml_attribute<char>* var = wme->first_attribute("var");
					xml_attribute<char>* prop = wme->first_attribute("prop");
					xml_attribute<char>* relation = wme->first_attribute("relation");
					xml_attribute<char>* value = wme->first_attribute("value");

					// ��־д��
					CLog::write("WME", string(var->value()) + string(prop->value()) + string(relation->value()) + string(value->value()), logs);

					wmefacts.push_back(WME(var->value(), prop->value(), value->value(), relation->value()));
					count0++;
					if (count0 >= count_wme)
						break;
				}
			}
			//trueΪtreat�㷨��falseΪrete�㷨
			bool selectAlgorithm = (algoStr == "rete" ? 0 : 1);
			//treat
			if (selectAlgorithm) {
				vector<ConditionVector> ans;
				vector<int> index;
				int count = 0;
				for (vector<WME>::iterator& it = wmefacts.begin(); it != wmefacts.end(); it++) {
					auto&& an = net.TreataddWME(*it);
					for (int i = 0; i < an.size(); i++) {
						auto&& anit = std::find(ans.begin(), ans.end(), an.at(i));
						// an.at(i).front().print(0);
						if (anit == ans.end()) {
							ans.push_back(an.at(i));
							index.push_back(count);
							// cout <<"cout::"<< count<<endl;
						}
						count++;
					}

				}
				int count0 = 0;
				for (auto&& VecCon : ans) {
					for (auto&& cond : VecCon) {
						//for (auto&& cond : condVec) {
						cond.print(0);
						// ��־д��
						CLog::write("Result", cond.print_to_log(0), logs);
						//}
						
					}
					if (index[count0] < net.out_W.size())
						cout << "Ȩ�أ�" << net.out_W[index[count0]] << endl;
					count0++;
					puts("");
				}
				// system("pause");
			}
			//rete
			else {
				for (vector<WME>::iterator& it = wmefacts.begin(); it != wmefacts.end(); it++) {
					net.addWME(*it);
				}

				/*	for (auto&& condVec : net.invoke()) {
						for (auto&& cond : condVec) {
							net.addWME({ cond.get(Field::id), cond.get(Field::attr), cond.get(Field::value), cond.get(Field::rel) });
						}
					}*/

				net.clearStatus();
				int count = 0;
				for (auto&& condVec : net.invoke()) {
					for (auto&& cond : condVec) {
						cond.print(0);
						// ��־д��
						CLog::write("Result", cond.print_to_log(0), logs);
					}
					if (count < net.out_W.size())
						cout << "Ȩ�أ�" << net.out_W[count] << endl;

					count++;

					puts("");
				}
				// system("pause");
			}

		}
		else {
			// clips
			// ��ȡ�ļ�
			file<> fdoc_rule(rulename.c_str());
			// ��ȡ����
			xml_document<> doc_rule;
			doc_rule.parse<0>(fdoc_rule.data());
			// �ܵĹ���
			std::string clp = "";
			// ������ڵ�
			xml_node<>* rulebase = doc_rule.first_node("rulebase");
			// ���е�����������
			std::string rule_str = "";
			int count = 0;
			for (xml_node<>* rulesubbase = rulebase->first_node("rulesubbase"); NULL != rulesubbase; rulesubbase = rulesubbase->next_sibling()) {
				for (xml_node<>* rule = rulesubbase->first_node("rule"); NULL != rule; rule = rule->next_sibling()) {
					// ��ձ���������ַ���
					rule_str.clear();
					rule_str.append("(defrule ");
					// �õ��������������
					// xml_attribute<char>* id = rule->first_attribute("id");
					// �����������ƴ�ӵ��﷨��
					// rule_str.append(id->value());
					rule_str.append(std::to_string(count++) + "_");
					rule_str.append("\n");
					// �õ������ܵĽڵ�
					xml_node<>* lhs = rule->first_node("lhs");
					xml_node<>* rhs = rule->first_node("rhs");
					xml_node<>* weight = rule->first_node("weight");
					// Ȩ��ֵ
					std::string W = weight->value();
					
					rule_str.append("(declare (salience " + W + "))");
					rule_str.append("\n");

					// ����lhs
					for (xml_node<>* condition = lhs->first_node("condition"); condition != NULL; condition = condition->next_sibling()) {
						xml_attribute<char>* var = condition->first_attribute("var");
						xml_attribute<char>* prop = condition->first_attribute("prop");
						xml_attribute<char>* relation = condition->first_attribute("relation");
						xml_attribute<char>* value = condition->first_attribute("value");
						// ��ʽ������
						std::string var_str = format(var->value());
						std::string prop_str = format(prop->value());
						std::string relation_str = format(relation->value());
						std::string value_str = format(value->value());
						// ���б�����������
						rule_str.append("(PlatformObj ");
						// �ӱ�����
						rule_str.append("(var ");
						if (CStringOp::startsWith(var_str, "?")) {
							rule_str.append(var_str);
						}
						else {
							rule_str.append("\"" + var_str + "\"");
						}
						rule_str.append(") ");
						// ��������
						rule_str.append("(prop ");
						rule_str.append("\"" + prop_str + "\"");
						rule_str.append(") ");
						// �ӹ�ϵ
						rule_str.append("(relations ");
						rule_str.append("\"" + relation_str + "\"");
						rule_str.append(") ");
						// ��ֵ
						rule_str.append("(values ");
						rule_str.append("\"" + value_str + "\"");
						rule_str.append(") ");
						// ������
						rule_str.append(")");
						// ����
						rule_str.append("\n");
					}
					// ����Ƶ�����
					rule_str.append(" => ");
					rule_str.append("\n");
					// ����rhs
					for (xml_node<>* action = rhs->first_node("action"); action != NULL; action = action->next_sibling()) {
						xml_attribute<char>* var = action->first_attribute("var");
						xml_attribute<char>* prop = action->first_attribute("prop");
						xml_attribute<char>* relation = action->first_attribute("relation");
						xml_attribute<char>* value = action->first_attribute("value");
						// ��ʽ������
						std::string var_str = format(var->value());
						std::string prop_str = format(prop->value());
						std::string relation_str = format(relation->value());
						std::string value_str = format(value->value());
						// ��������ʽ��ǰ����
						rule_str.append("(printout t ");
						// �ӱ�����
						// rule_str.append("(var ");
						if (CStringOp::startsWith(var_str, "?")) {
							rule_str.append(var_str);
						}
						else {
							rule_str.append("\"" + var_str + "\"");
						}
						rule_str.append(" ");
						// rule_str.append(") ");
						// ��������
						// rule_str.append("(prop ");
						rule_str.append("\"" + prop_str + "\"");
						rule_str.append(" ");
						// rule_str.append(") ");
						// �ӹ�ϵ
						// rule_str.append("(relations ");
						rule_str.append("\"" + relation_str + "\"");
						rule_str.append(" ");
						// rule_str.append(") ");
						// ��ֵ
						// rule_str.append("(values ");
						if (CStringOp::startsWith(value_str, "?")) {
							rule_str.append(value_str);
						}
						else {
							rule_str.append("\"" + value_str + "\"");
						}
						rule_str.append(" ");
						// rule_str.append(") ");
						// ������
						rule_str.append("crlf");
						rule_str.append(" ");
						rule_str.append(")");
						// ����
						rule_str.append("\n");
					}
					rule_str.append("(printout t " + std::string( "Ȩ�أ�") + W + std::string(" crlf )"));
					// ��������
					rule_str.append(")");
					// ��ӻ��з�
					rule_str.append("\n");
					// �������������ϣ�������һ��
					clp.append("\n");
					clp.append(rule_str);
				}
				// ������ļ�
				ofstream fout;
				fout.open("./tmp_1.clp");
				fout << clp << std::endl;
				fout.close();
			}
			// ��ȡ��ʵ
			// ��ȡ�ļ�
			file<> fdoc_wmes(wmesname.c_str());
			// ��ȡ����
			xml_document<> doc_wme;
			doc_wme.parse<0>(fdoc_wmes.data());
			xml_node<char>* wmes = doc_wme.first_node("wmes");
			// �ܵ���ʵ
			std::string wmes_str = "";
			wmes_str.append("(deffacts initial_facts");
			wmes_str.append("\n");
			std::string wme_str = "";
			int count0 = 0;
			for (xml_node<>* wme = wmes->first_node("wme"); NULL != wme; wme = wme->next_sibling()) {
				xml_attribute<char>* var = wme->first_attribute("var");
				xml_attribute<char>* prop = wme->first_attribute("prop");
				xml_attribute<char>* relation = wme->first_attribute("relation");
				xml_attribute<char>* value = wme->first_attribute("value");
				// ��ʽ������
				std::string var_str = format(var->value());
				std::string prop_str = format(prop->value());
				std::string relation_str = format(relation->value());
				std::string value_str = format(value->value());
				// ��ӵ�������ʵ
				wme_str.clear();
				// ���б���������
				wme_str.append("(PlatformObj ");
				// �ӱ�����
				wme_str.append("(var ");
				wme_str.append("\"" + var_str + "\"");
				wme_str.append(") ");
				// ��������
				wme_str.append("(prop ");
				wme_str.append("\"" + prop_str + "\"");
				wme_str.append(") ");
				// �ӹ�ϵ
				wme_str.append("(relations ");
				wme_str.append("\"" + relation_str + "\"");
				wme_str.append(") ");
				// ��ֵ
				wme_str.append("(values ");
				wme_str.append("\"" + value_str + "\"");
				wme_str.append(") ");
				// ������
				wme_str.append(")");
				// ����
				wme_str.append("\n");
				// ��ӽ���clp
				wmes_str.append(wme_str);
				count0++;
				if (count0 >= count_wme)
					break;
			}
			// ��ʵ�ĺ�����
			wmes_str.append(")");

			// ������ļ�
			ofstream fout;
			fout.open("./tmp_2.clp");
			fout << wmes_str << std::endl;
			fout.close();

			// ��ʼ����
			CLIPS::CLIPSCPPEnv theEnv;

			// ����ģ��
			theEnv.Load("./template.clp");

			// ���ع�����ʵ
			theEnv.Load("./tmp_1.clp");
			theEnv.Load("./tmp_2.clp");

			theEnv.Reset();
			theEnv.Run(-1);
		}

	}
	catch (const std::exception& e)
	{
		// ��־д��
		CLog::write("Exception", e.what(), logs);
	}
	// ��־�ļ��ر�
	logs.close();
}

int main() {

	//��ȡ�㷨�����ļ�
	char algoChar[16];
	GetPrivateProfileString("algorithm", "algo", "", algoChar, sizeof(algoChar), "./config.ini");
	std::string algoStr(algoChar);

	std::cout << "Current Algorithm is :" << std::ends;
	std::cout << algoStr << std::endl;
	std::cout << "--------------------------------" << endl;
	ofstream times("./time.txt", ios::app);
	while (count_wme < 10000) {
		count_wme += 1000;
		DWORD time_start, time_end;
		// ��ʼʱ��
		time_start = GetTickCount();

		reason(algoStr);

		// ����ʱ��
		time_end = GetTickCount();
		// ����ʱ��
		cout << "Duration Time = " << (time_end - time_start) << "ms\n ";
		times << time_end - time_start << ",";
	}

	return 0;
}
