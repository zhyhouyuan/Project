#include "Log.h"

string Now() {
	time_t t = time(0);
	char tmp[32];

	struct tm tt;   //tm�ṹָ��
	time_t now;  //����time_t���ͱ���
	time(&now);      //��ȡϵͳ���ں�ʱ��
	localtime_s(&tt, &now);   //��ȡ�������ں�ʱ��

	strftime(tmp, sizeof(tmp), "[%Y-%m-%d %X]", &tt);
	return string(tmp);
}
void CLog::write(const std::string& type, const std::string & infos, std::ofstream& log_file)
{
	log_file << Now() << " [" << type << "]��" << infos << std::endl;
}

void CLog::write(const std::string & infos, std::ofstream& log_file)
{
	log_file << Now() << infos << std::endl;
}

