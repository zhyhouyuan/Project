#include "JoinNode.h"

#include "../../PublicDefine.h"
#include <iostream>
#include <iomanip>
#include "../Structure/Token.h"


//对应net里buildOrShareJoinNode(parent, am, tests, c)
JoinNode::JoinNode(ReteNodePtr leftParent, AlphaMemoryPtr rightParent
	, const ParamTestNodeVector& tests, const Condition& c)
	: BetaNode(leftParent, rightParent, tests) {
	switch (c.getType())
	{
	case Condition::positive:
		isPositive = true;
		break;
	case Condition::negetive:
		isPositive = false;
		break;
	default:
		myAssert(false);
	}
}
	
//有可能是事实区遍历RETE网络的关键函数
const TokenVector & JoinNode::getOutput(){
	if (!isReadyForOutput){
		// Can Be Optimized
		//猜测leftParent均为beta节点，故下列循环应为WME在Beta匹配的流程
		//bool flag = true;
		for (auto&& token : leftParent->getOutput()) {
			//cout << "output:";
			//for (auto&& out : output)
				//out.print(1);
			//cout << "token:" ;
			//token.print(1);
			//因为构造函数，默认isPositive = true
			if (isPositive) {
				//cout << "ccc" << endl;
				if (!rightParent->getNewOutput().empty()){
					//rightParent为alpha内存区，通过getOutput调出存储的已经匹配的事实，故这里循环变量使用的是wme
					for (auto&& wme : rightParent->getNewOutput()) {
						//cout << "addNewWME:";
						//wme.print(1);
						bool passAllCheck = true;
						//貌似因为$，只循环一遍
						for (auto&& test : tests) {
							//猜测是beta节点内联的两个内存表真正匹配的过程，token来自left存储区，wme来自right存储区，
							//经测试一次都没进入if，是没用到的功能吗？
							if (!test.performTest(token, wme)) {
								passAllCheck = false;
								break;
							}
						}

						if (passAllCheck) {
							//特意加这一步的目的是让output增加，原本的token : leftParent->getOutput()内只有一个变量，增加一个后，外层的for可继续循环
							//如此往复，直到wme的for循环结束，外层的token循环也就结束
							//这里只是将token的值放进去，并未修改token
							output.push_back(token);
							//cout << "output_token:";
							//for (auto&& out : output)
								//out.print(1);
							//这里的写法表达的应该是在output的最后一个元素内，把WME插在这个元素里的最后。
							//每个循环的output应该是独立的
							output.back().push_back(wme);
							//cout << "update_token:";
							//for (auto&& out : output)
							//	out.print(1);
						}
					}
					//flag = false;
					rightParent->clearAddNewStatus();
				}
				else {
					//rightParent为alpha内存区，通过getOutput调出存储的已经匹配的事实，故这里循环变量使用的是wme
					for (auto&& wme : rightParent->getOutput()) {
						//cout << "wme:";
						//wme.print(1);
						bool passAllCheck = true;
						//貌似因为$，只循环一遍
						for (auto&& test : tests) {
							//猜测是beta节点内联的两个内存表真正匹配的过程，token来自left存储区，wme来自right存储区，
							//经测试一次都没进入if，是没用到的功能吗？
							if (!test.performTest(token, wme)) {
								passAllCheck = false;
								break;
							}
						}

						if (passAllCheck) {
							//特意加这一步的目的是让output增加，原本的token : leftParent->getOutput()内只有一个变量，增加一个后，外层的for可继续循环
							//如此往复，直到wme的for循环结束，外层的token循环也就结束
							//这里只是将token的值放进去，并未修改token
							output.push_back(token);
							//cout << "output_token:";
							//for (auto&& out : output)
							//	out.print(1);
							//这里的写法表达的应该是在output的最后一个元素内，把WME插在这个元素里的最后。
							//每个循环的output应该是独立的
							output.back().push_back(wme);
							//cout << "update_token:";
							//for (auto&& out : output)
								//out.print(1);
						}
					}
				}
				//cout << "-------------------------------" << endl;
			}
			else {
				bool passNoneCheck = true;
				for (auto&& wme : rightParent->getOutput()) {
					for (auto&& test : tests) {
						if (test.performTest(token, wme)) {
							passNoneCheck = false;
							break;
						}
					}
					if (!passNoneCheck)
						break;
				}
				if (passNoneCheck) {
					output.push_back(token);
					output.back().push_back({ "?", "?", "?","?" });
				}
			}
		}
		isReadyForOutput = true;
	}
	//cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	return output;
}