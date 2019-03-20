#include <stdio.h>
#include <Windows.h>
#include <tchar.h>

void ShowError(char *pszText);
BOOL GenCreateKey(BYTE **ppPublicKey, DWORD *pdwPublicKeyLength, BYTE **ppPrivateKey, DWORD *pdwPrivateKeyLength);
BOOL RsaEncrypt(BYTE *pPublicKey, DWORD dwPublicKeyLength, BYTE *pData, DWORD &dwDataLength, DWORD dwBufferLength);
BOOL RsaDecrypt(BYTE *pPrivateKey, DWORD dwPrivateKeyLength, BYTE *pData, DWORD &dwDataLength);


int _tmain(int argc, _TCHAR* argv[])
{
	BYTE *pPublicKey = NULL;
	DWORD dwPublicKeyLength = 0;
	BYTE *pPrivateKey = NULL;
	DWORD dwPrivateKeyLength = 0;
	BYTE *pData = NULL;
	DWORD dwDataLength = 0;
	DWORD dwBUfferLength = MAX_PATH;
	DWORD i = 0;

	pData = new BYTE[dwBUfferLength];
	if (NULL == pData)
	{
		ShowError("new");
		return 0;
	}
	RtlZeroMemory(pData, dwBUfferLength);
	lstrcpy((char *)pData, "Hello World !");
	dwDataLength = 1 + lstrlen((char *)pData);
	printf("Text[%d]\n", dwDataLength);
	for (i = 0; i < dwDataLength;i++)
	{
		printf("%x", pData[i]);
	}
	printf("\n\n");

	//生成公钥和私钥
	GenCreateKey(&pPublicKey, &dwPublicKeyLength, &pPrivateKey, &dwPrivateKeyLength);
	printf("Public Key[%d]\n", dwPublicKeyLength);
	for (i = 0; i < dwPublicKeyLength; i++)
	{
		printf("%.2x", pPublicKey[i]);
	}
	printf("\n\n");

	printf("Private Key[%d]\n", dwPrivateKeyLength);
	for (i = 0; i < dwPrivateKeyLength; i++)
	{
		printf("%.2x", pPrivateKey[i]);
	}
	printf("\n\n");

	//公钥加密数据
	RsaEncrypt(pPublicKey, dwPublicKeyLength, pData, dwDataLength, dwBUfferLength);
	printf("RSA Encrypt[%d]\n", dwDataLength);
	for (i = 0; i < dwDataLength;i++)
	{
		printf("%x", pData[i]);
	}
	printf("\n\n");

	//私钥解密数据
	RsaDecrypt(pPrivateKey, dwPrivateKeyLength, pData, dwDataLength);
	printf("RSA Decrypt[%d]\n", dwDataLength);
	for (i = 0; i < dwDataLength; i++)
	{
		printf("%x", pData[i]);
	}
	printf("\n\n");

	if (pData)
	{
		delete[]pData;
		pData = NULL;
	}
	if (pPrivateKey)
	{
		delete[]pPrivateKey;
		pPrivateKey = NULL;
	}
	if (pPublicKey)
	{
		delete[]pPublicKey;
		pPublicKey = NULL;
	}

	system("pause");
	return 0;


}

void ShowError(char *pszText)
{
	char szErr[MAX_PATH] = { 0 };
	wsprintf(szErr, "%s ERROR [%d]", pszText, GetLastError());
	MessageBox(NULL, szErr, "ERROR", MB_ICONERROR | MB_OK);
}

//生成公钥和私钥
BOOL GenCreateKey(BYTE **ppPublicKey, DWORD *pdwPublicKeyLength, BYTE **ppPrivateKey, DWORD *pdwPrivateKeyLength)
{
	BOOL bRet = TRUE;
	HCRYPTPROV hCryptProv = NULL;
	HCRYPTKEY hCryptKey = NULL;
	BYTE *pPublicKey = NULL;
	DWORD dwPublicKeyLength = 0;
	BYTE *pPrivateKey = NULL;
	DWORD dwPrivateKeyLength = 0;

	do 
	{
		//获取CSP句柄
		bRet = CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, 0);
		if (FALSE == bRet)
		{
			ShowError("CryptAcquireContext");
			break;
		}

		//生成公私密钥对
		bRet = CryptGenKey(hCryptProv, AT_KEYEXCHANGE, CRYPT_EXPORTABLE, &hCryptKey);
		if (FALSE == bRet)
		{
			ShowError("CryptGenKey");
			break;
		}

		//获取公钥密钥的长度和内容
		bRet = CryptExportKey(hCryptKey, NULL, PUBLICKEYBLOB, 0, NULL, &dwPublicKeyLength);
		if (FALSE == bRet)
		{
			ShowError("CryptExportKey");
			break;
		}
		pPublicKey = new BYTE[dwPublicKeyLength];
		RtlZeroMemory(pPublicKey, dwPublicKeyLength);
		bRet = CryptExportKey(hCryptKey, NULL, PUBLICKEYBLOB, 0, pPublicKey, &dwPublicKeyLength);
		if (FALSE == bRet)
		{
			ShowError("CryptExportKey");
			break;
		}

		//获取私钥密钥的长度和内容
		bRet = CryptExportKey(hCryptKey, NULL, PRIVATEKEYBLOB, 0, NULL, &dwPrivateKeyLength);
		if (FALSE == bRet)
		{
			ShowError("CryptExportKey");
			break;
		}
		pPrivateKey = new BYTE[dwPrivateKeyLength];
		RtlZeroMemory(pPrivateKey, dwPrivateKeyLength);
		bRet = CryptExportKey(hCryptKey, NULL, PRIVATEKEYBLOB, 0, pPrivateKey, &dwPrivateKeyLength);
		if (FALSE == bRet)
		{
			ShowError("CryptExportKey");
			break;
		}

		//返回数据
		*ppPublicKey = pPublicKey;
		*pdwPublicKeyLength = dwPublicKeyLength;
		*ppPrivateKey = pPrivateKey;
		*pdwPrivateKeyLength = dwPrivateKeyLength;


	} while (FALSE);

	//释放关闭相关句柄
	if (hCryptKey)
	{
		CryptDestroyKey(hCryptKey);
	}
	if (hCryptProv)
	{
		CryptReleaseContext(hCryptProv, 0);
	}
	return bRet;
}

//公钥加密数据
BOOL RsaEncrypt(BYTE *pPublicKey, DWORD dwPublicKeyLength, BYTE *pData, DWORD &dwDataLength, DWORD dwBufferLength)
{
	BOOL bRet = TRUE;
	HCRYPTPROV hCryptProv = NULL;
	HCRYPTKEY hCryptKey = NULL;

	do 
	{
		//获取CSP的句柄
		bRet = CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, 0);
		if (FALSE == bRet)
		{
			ShowError("CryptAcquireContext");
			break;
		}

		//导入公钥
		bRet = CryptImportKey(hCryptProv, pPublicKey, dwPublicKeyLength, NULL, 0, &hCryptKey);
		if (FALSE == bRet)
		{
			ShowError("CryptImportKey");
			break;
		}

		//加密数据
		bRet = CryptEncrypt(hCryptKey, NULL, TRUE, 0, pData, &dwDataLength, dwBufferLength);
		if (FALSE == bRet)
		{
			ShowError("CryptEncrypt");
			break;
		}

	} while (FALSE);

	//释放相关句柄
	if (hCryptKey)
	{
		CryptDestroyKey(hCryptKey);
	}
	if (hCryptProv)
	{
		CryptReleaseContext(hCryptProv, 0);
	}

	return bRet;
}

//私钥解密数据
BOOL RsaDecrypt(BYTE *pPrivateKey, DWORD dwPrivateKeyLength, BYTE *pData, DWORD &dwDataLength)
{
	BOOL bRet = TRUE;
	HCRYPTPROV hCryptProv = NULL;
	HCRYPTKEY hCryptKey = NULL;

	do
	{
		//获取CSP的句柄
		bRet = CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, 0);
		if (FALSE == bRet)
		{
			ShowError("CryptAcquireContext");
			break;
		}

		//导入私钥
		bRet = CryptImportKey(hCryptProv, pPrivateKey, dwPrivateKeyLength, NULL, 0, &hCryptKey);
		if (FALSE == bRet)
		{
			ShowError("CryptImportKey");
			break;
		}

		//解密数据
		bRet = CryptDecrypt(hCryptKey, NULL, TRUE, 0, pData, &dwDataLength);
		if (FALSE == bRet)
		{
			ShowError("CryptDecrypt");
			break;
		}

	} while (FALSE);

	//释放相关句柄
	if (hCryptKey)
	{
		CryptDestroyKey(hCryptKey);
	}
	if (hCryptProv)
	{
		CryptReleaseContext(hCryptProv, 0);
	}

	return bRet;
}