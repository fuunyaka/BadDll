#include <windows.h>
#include <iostream>
#include <wincrypt.h>

#include "detours.h"
#include "resolve.h"

#pragma comment(lib,"detours.lib")


BOOL(WINAPI * TrueCryptDecrypt)(HCRYPTKEY  hKey, HCRYPTHASH  hHash, BOOL Final, DWORD dwFlags, BYTE  *pbData, DWORD  *pdwDataLen) = CryptDecrypt;

__declspec(dllexport) VOID WINAPI MyCryptDecrypt(HCRYPTKEY  hKey, HCRYPTHASH  hHash, BOOL Final, DWORD dwFlags, BYTE  *pbData, DWORD  *pdwDataLen)
{
	std::cout << "ha-ha sirus-virus fooled you!!!!\n";
	HANDLE hFile = CreateFile(L"sirus-virus.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	LPCVOID lpBuffer = "sirus-virus was here!";
	DWORD lpNumberOfBytesWritten;
	BOOL status = WriteFile(hFile,
		lpBuffer,
		21,
		&lpNumberOfBytesWritten,
		NULL
	);
	CloseHandle(hFile);

}

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DetourRestoreAfterWith();
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)TrueCryptDecrypt, MyCryptDecrypt);
		DetourTransactionCommit();
	}

	return TRUE;
}
