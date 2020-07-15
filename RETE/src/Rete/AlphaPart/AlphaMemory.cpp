#include "AlphaMemory.h"
#include <iostream>
#include <iomanip>

void AlphaMemory::addWME(const WME & wme) {
	output.push_back(wme);
}

const WMEVector & AlphaMemory::getOutput() {
	//cout << "ddd" << endl;
	return output;
}

void AlphaMemory::addNewWME(const WME& wme) {
	addNew.push_back(wme);
}

const WMEVector& AlphaMemory::getNewOutput() {
	//cout << "new" << endl;
	return addNew;
}

void AlphaMemory::clearAddNewStatus() {
	//cout << "pop_back" << endl;
	addNew.clear();
}

void AlphaMemory::clearStatus() {
	//×Ô¼º×¢ÊÍµÄ
	//output.clear();
}
