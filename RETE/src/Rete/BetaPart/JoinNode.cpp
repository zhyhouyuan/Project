#include "JoinNode.h"

#include "../../PublicDefine.h"
#include <iostream>
#include <iomanip>
#include "../Structure/Token.h"


//��Ӧnet��buildOrShareJoinNode(parent, am, tests, c)
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
	
//�п�������ʵ������RETE����Ĺؼ�����
const TokenVector & JoinNode::getOutput(){
	if (!isReadyForOutput){
		// Can Be Optimized
		//�²�leftParent��Ϊbeta�ڵ㣬������ѭ��ӦΪWME��Betaƥ�������
		//bool flag = true;
		for (auto&& token : leftParent->getOutput()) {
			//cout << "output:";
			//for (auto&& out : output)
				//out.print(1);
			//cout << "token:" ;
			//token.print(1);
			//��Ϊ���캯����Ĭ��isPositive = true
			if (isPositive) {
				//cout << "ccc" << endl;
				if (!rightParent->getNewOutput().empty()){
					//rightParentΪalpha�ڴ�����ͨ��getOutput�����洢���Ѿ�ƥ�����ʵ��������ѭ������ʹ�õ���wme
					for (auto&& wme : rightParent->getNewOutput()) {
						//cout << "addNewWME:";
						//wme.print(1);
						bool passAllCheck = true;
						//ò����Ϊ$��ֻѭ��һ��
						for (auto&& test : tests) {
							//�²���beta�ڵ������������ڴ������ƥ��Ĺ��̣�token����left�洢����wme����right�洢����
							//������һ�ζ�û����if����û�õ��Ĺ�����
							if (!test.performTest(token, wme)) {
								passAllCheck = false;
								break;
							}
						}

						if (passAllCheck) {
							//�������һ����Ŀ������output���ӣ�ԭ����token : leftParent->getOutput()��ֻ��һ������������һ��������for�ɼ���ѭ��
							//���������ֱ��wme��forѭ������������tokenѭ��Ҳ�ͽ���
							//����ֻ�ǽ�token��ֵ�Ž�ȥ����δ�޸�token
							output.push_back(token);
							//cout << "output_token:";
							//for (auto&& out : output)
								//out.print(1);
							//�����д������Ӧ������output�����һ��Ԫ���ڣ���WME�������Ԫ��������
							//ÿ��ѭ����outputӦ���Ƕ�����
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
					//rightParentΪalpha�ڴ�����ͨ��getOutput�����洢���Ѿ�ƥ�����ʵ��������ѭ������ʹ�õ���wme
					for (auto&& wme : rightParent->getOutput()) {
						//cout << "wme:";
						//wme.print(1);
						bool passAllCheck = true;
						//ò����Ϊ$��ֻѭ��һ��
						for (auto&& test : tests) {
							//�²���beta�ڵ������������ڴ������ƥ��Ĺ��̣�token����left�洢����wme����right�洢����
							//������һ�ζ�û����if����û�õ��Ĺ�����
							if (!test.performTest(token, wme)) {
								passAllCheck = false;
								break;
							}
						}

						if (passAllCheck) {
							//�������һ����Ŀ������output���ӣ�ԭ����token : leftParent->getOutput()��ֻ��һ������������һ��������for�ɼ���ѭ��
							//���������ֱ��wme��forѭ������������tokenѭ��Ҳ�ͽ���
							//����ֻ�ǽ�token��ֵ�Ž�ȥ����δ�޸�token
							output.push_back(token);
							//cout << "output_token:";
							//for (auto&& out : output)
							//	out.print(1);
							//�����д������Ӧ������output�����һ��Ԫ���ڣ���WME�������Ԫ��������
							//ÿ��ѭ����outputӦ���Ƕ�����
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