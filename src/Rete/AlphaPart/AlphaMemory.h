#pragma once

#include <memory>

#include "../Structure/Node.h"
#include "../Structure/WME.h"

//基类成员Output，ProductionNode、AlphaMemory与JoinNode共享
class AlphaMemory : public Node<WMEVector> {
public:
	// 添加WME，即事实的方法
	void addWME(const WME& wme);
	void addNewWME(const WME& wme);
	const WMEVector& getOutput() override;
	const WMEVector& getNewOutput();
	void clearStatus() override;
	void clearAddNewStatus();
private:
	WMEVector addNew;
};

// 指针合集
using AlphaMemoryPtr = std::shared_ptr<AlphaMemory>;

// hash计算
namespace std {
	template<>
	struct hash<AlphaMemory> {
		size_t operator()(const AlphaMemory& am) const {
			return hash<size_t>()(am.serialNumber);
		}
	};
}