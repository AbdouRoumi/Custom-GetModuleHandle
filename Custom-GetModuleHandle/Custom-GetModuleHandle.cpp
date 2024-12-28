#include "Windows.h"
#include <stdio.h>
#include <winternl.h>


BOOL IsStringEqual(IN LPCWSTR Str1, IN LPCWSTR Str2) {

	WCHAR lStr1[MAX_PATH], lStr2[MAX_PATH];
	int len1 = lstrlenW(Str1), len2 = lstrlenW(Str2);
	int i = 0, j = 0;

	//Checking length 
}

HMODULE CustomGetModuleHandle(IN LPCWSTR szModuleName) {
#ifdef _WIN64
	PPEB pPeb = (PEB*)(__readgsqword(0x60));
#elif _WIN32
	PPEB pPeb = (PEB*)(__readgsqword(0x30));
#endif

	//Getting the Ldr
	PPEB_LDR_DATA pLdr = (PPEB_LDR_DATA)(pPeb->Ldr);

	//Getting the first element in the linked list 

	PLDR_DATA_TABLE_ENTRY pDte = (PLDR_DATA_TABLE_ENTRY)(pLdr->InMemoryOrderModuleList.Flink);


	//Enumerating the Dlls

	while (pDte) {
		//If not null
		if (pDte->FullDllName.Length != NULL) {
			//print the DLL name
			wprintf(L"The dll name is : %s\n", pDte->FullDllName.Buffer);

		}
		else
		{
			break;
		}

		//Next element in the linked list 
		pDte = *(PLDR_DATA_TABLE_ENTRY*)(pDte);

	}
	return NULL;
}



int main() {



	printf("[i] Original 0x%p \n", GetModuleHandleW(L"NTDLL.DLL"));

	printf("[i] Replacement 0x%p \n", CustomGetModuleHandle(L"NTDLL.DLL"));
	printf("[i] Replacement 2 0x%p \n", CustomGetModuleHandle(L"NTDLL.DLL"));

	printf("[#] Press <Enter> To Quit ... ");
	getchar();

	return 0;

}
