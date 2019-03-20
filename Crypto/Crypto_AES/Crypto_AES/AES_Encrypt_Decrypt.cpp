#include <Windows.h>
#include <tchar.h>
#include <stdio.h>


void ShowError(char *pszText);
BOOL AesEncrypt(BYTE *pPassword, DWORD dwPasswordLength, BYTE *pData, DWORD &dwDataLength, DWORD dwBufferLength);
BOOL AesDecrypt(BYTE *pPassword, DWORD dwPasswordLength, BYTE *pData, DWORD &dwDataLength, DWORD dwBufferLength);


int _tmain(int argc, _TCHAR* argv[])
{
	BYTE pData[MAX_PATH] = { 0 };
	DWORD dwDataLength = 0, dwBufferLength = MAX_PATH;
	DWORD i = 0;

	RtlZeroMemory(pData, dwBufferLength);
	lstrcpy((char *)pData, "Hello World !");
	dwDataLength = 1 + lstrlen((char *)pData);

	printf("Text[%d]\n", dwDataLength);
	for (i = 0; i < dwDataLength;i++)
	{
		printf("%x ", pData[i]);
	}
	printf("\n\n");

	//AES加密
	AesEncrypt((BYTE *)"yxx", 3, pData, dwDataLength, dwBufferLength);
	printf("AES Encrypt[%d]\n", dwDataLength);
	for (i = 0; i < dwDataLength;i++)
	{
		printf("%x ", pData[i]);
	}
	printf("\n\n");

	//AES解密
	AesDecrypt((BYTE *)"yxx", 3, pData, dwDataLength, dwBufferLength);
	printf("AES Decrypt[%d]\n", dwDataLength);
	for (i = 0; i < dwDataLength; i++)
	{
		printf("%x ", pData[i]);
	}
	printf("\n\n");

	system("pause");
	return 0;
}


void ShowError(char *pszText)
{
	char szErr[MAX_PATH] = { 0 };
	wsprintf(szErr, "%s Error [%d]", pszText, GetLastError());
	MessageBox(NULL, szErr, "ERROR", MB_OK | MB_ICONERROR);
}


//AES加密
BOOL AesEncrypt(BYTE *pPassword, DWORD dwPasswordLength, BYTE *pData, DWORD &dwDataLength, DWORD dwBufferLength)
{
	BOOL bRet = TRUE;
	HCRYPTPROV hCryptprov = NULL;
	HCRYPTHASH hCryptHash = NULL;
	HCRYPTKEY hCryptKey = NULL;

	do 
	{
		//获取CSP句柄
		bRet = CryptAcquireContext(&hCryptprov, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
		if (FALSE == bRet)
		{
			ShowError("CryptAcquireContext");
			break;
		}

		//创建HASH对象
		bRet = CryptCreateHash(hCryptprov, CALG_MD5, NULL, 0, &hCryptHash);
		if (FALSE == bRet)
		{
			ShowError("CryptCreateHash");
			break;
		}

		//对密钥进行HASH计算
		bRet = CryptHashData(hCryptHash, pPassword, dwPasswordLength, 0);
		if (FALSE == bRet)
		{
			ShowError("CryptHashData");
			break;
		}

		//使用HASH来生成密钥
		bRet = CryptDeriveKey(hCryptprov, CALG_AES_128, hCryptHash, CRYPT_EXPORTABLE, &hCryptKey);
		if (FALSE == bRet)
		{
			ShowError("CryptDeriveKey");
			break;
		}

		bRet = CryptEncrypt(hCryptKey, NULL, TRUE, 0, pData, &dwDataLength, dwBufferLength);
		if (FALSE == bRet)
		{
			ShowError("CryptEncrypt");
			break;
		}

	} while (FALSE);

	if (hCryptKey)
	{
		CryptDestroyKey(hCryptKey);
	}
	if (hCryptHash)
	{
		CryptDestroyHash(hCryptHash);
	}
	if (hCryptprov)
	{
		CryptReleaseContext(hCryptprov, 0);
	}
	return bRet;
}

//AES解密
BOOL AesDecrypt(BYTE *pPassword, DWORD dwPasswordLength, BYTE *pData, DWORD &dwDataLength, DWORD dwBufferLength)
{
	BOOL bRet = TRUE;
	HCRYPTPROV hCryptprov = NULL;
	HCRYPTHASH hCryptHash = NULL;
	HCRYPTKEY hCryptKey = NULL;

	do
	{
		//获取CSP句柄
		bRet = CryptAcquireContext(&hCryptprov, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
		if (FALSE == bRet)
		{
			ShowError("CryptAcquireContext");
			break;
		}

		//创建HASH对象
		bRet = CryptCreateHash(hCryptprov, CALG_MD5, NULL, 0, &hCryptHash);
		if (FALSE == bRet)
		{
			ShowError("CryptCreateHash");
			break;
		}

		//对密钥进行HASH计算
		bRet = CryptHashData(hCryptHash, pPassword, dwPasswordLength, 0);
		if (FALSE == bRet)
		{
			ShowError("CryptHashData");
			break;
		}

		//使用HASH来生成密钥
		bRet = CryptDeriveKey(hCryptprov, CALG_AES_128, hCryptHash, CRYPT_EXPORTABLE, &hCryptKey);
		if (FALSE == bRet)
		{
			ShowError("CryptDeriveKey");
			break;
		}

		bRet = CryptDecrypt(hCryptKey, NULL, TRUE, 0, pData, &dwDataLength);
		if (FALSE == bRet)
		{
			ShowError("CryptDecrypt");
			break;
		}

	} while (FALSE);

	if (hCryptKey)
	{
		CryptDestroyKey(hCryptKey);
	}
	if (hCryptHash)
	{
		CryptDestroyHash(hCryptHash);
	}
	if (hCryptprov)
	{
		CryptReleaseContext(hCryptprov, 0);
	}
	return bRet;
}