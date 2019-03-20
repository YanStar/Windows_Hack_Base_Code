#include <windows.h>

void ShowError(char *lpszText);
BOOL Reg_CurrentUser(char *lpszFileName, char *lpszValueName);
BOOL Reg_LocalMachine(char *lpszFileName, char *lpszValueName);