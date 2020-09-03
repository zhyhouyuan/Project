// Rule_deduce.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include <windows.h>
using namespace std;
#pragma comment (lib,"Rete.lib")
extern "C" _declspec(dllimport) void reason(string);
extern "C" _declspec(dllimport) void getwme_rule(string);
int main()
{
	//HINSTANCE hDllInst;
	//hDllInst = LoadLibrary(L"Rete.dll"); //调用DLL
	//typedef void(*PLUSFUNC)(); //后边为参数，前面为返回值
	//PLUSFUNC plus_str = (PLUSFUNC)GetProcAddress(hDllInst, "test"); //GetProcAddress为获取该函数的地址
	//plus_str();
	char algoChar[16];
	GetPrivateProfileString("algorithm", "algo", "", algoChar, sizeof(algoChar), "./config.ini");
	std::string algoStr(algoChar);

	std::cout << "Current Algorithm is :" << std::ends;
	std::cout << algoStr << std::endl;
	std::cout << "--------------------------------" << endl;
	reason(algoStr);
    std::cout << "Done!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
