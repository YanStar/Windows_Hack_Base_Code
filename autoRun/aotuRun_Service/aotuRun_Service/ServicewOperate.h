#ifndef _SERVICE_OPERATE_H_
#define _SERVICE_OPERATE_H_


#include <Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")


// 0 ���ط���    1 ��������    2 ֹͣ����    3 ɾ������
BOOL SystemServiceOperate(char *lpszDriverPath, int iOperateType);


#endif