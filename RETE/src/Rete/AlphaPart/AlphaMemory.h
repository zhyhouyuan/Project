#pragma once

#include <memory>

#include "../Structure/Node.h"
#include "../Structure/WME.h"

//�����ԱOutput��ProductionNode��AlphaMemory��JoinNode����
class AlphaMemory : public Node<WMEVector> {
public:
	// ���WME������ʵ�ķ���
	void addWME(const WME& wme);
	void addNewWME(const WME& wme);
	const WMEVector& getOutput() override;
	const WMEVector& getNewOutput();
	void clearStatus() override;
	void clearAddNewStatus();
private:
	WMEVector addNew;
};

// ָ��ϼ�
using AlphaMemoryPtr = std::shared_ptr<AlphaMemory>;

// hash����
namespace std {
	template<>
	struct hash<AlphaMemory> {
		size_t operator()(const AlphaMemory& am) const {
			return hash<size_t>()(am.serialNumber);
		}
	};
}