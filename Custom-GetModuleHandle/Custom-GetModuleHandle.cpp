#include "Windows.h"
#include <stdio.h>
#include <winternl.h>

BOOL IsStringEqual(IN LPCWSTR Str1, IN LPCWSTR Str2) {
    WCHAR lStr1[MAX_PATH], lStr2[MAX_PATH];
    int len1 = lstrlenW(Str1), len2 = lstrlenW(Str2);
    int i = 0;

    // Checking length
    if (len1 >= MAX_PATH || len2 >= MAX_PATH) {
        return FALSE;
    }

    // Converting Str1 to lower case string
    for (i = 0; i < len1; i++) {
        lStr1[i] = (WCHAR)tolower(Str1[i]);
    }
    lStr1[i] = L'\0'; // Null terminating

    // Converting Str2 to lower case
    for (i = 0; i < len2; i++) {
        lStr2[i] = (WCHAR)tolower(Str2[i]);
    }
    lStr2[i] = L'\0'; // Null terminating

    return (lstrcmpiW(lStr1, lStr2) == 0);
}


HMODULE CustomGetModuleHandle(IN LPCWSTR szModuleName) {

#ifdef _WIN64
	PPEB					pPeb = (PEB*)(__readgsqword(0x60));
#elif _WIN32
	PPEB					pPeb = (PEB*)(__readfsdword(0x30));
#endif

	PLDR_DATA_TABLE_ENTRY	pDte = (PLDR_DATA_TABLE_ENTRY)(pPeb->Ldr->InMemoryOrderModuleList.Flink);

	// getting the head of the linked list ( used to get the node & to check the end of the list)
	PLIST_ENTRY				pListHead = (PLIST_ENTRY)&pPeb->Ldr->InMemoryOrderModuleList;
	// getting the node of the linked list
	PLIST_ENTRY				pListNode = (PLIST_ENTRY)pListHead->Flink;

	do
	{
		if (pDte->FullDllName.Length != NULL) {
			if (IsStringEqual(pDte->FullDllName.Buffer, szModuleName)) {
				wprintf(L"[+] Found Dll \"%s\" \n", pDte->FullDllName.Buffer);
				return (HMODULE)(pDte->Reserved2[0]);

			}

			wprintf(L"[i] \"%s\" \n", pDte->FullDllName.Buffer);

			// updating pDte to point to the next PLDR_DATA_TABLE_ENTRY in the linked list
			pDte = (PLDR_DATA_TABLE_ENTRY)(pListNode->Flink);

			// updating the node variable to be the next node in the linked list
			pListNode = (PLIST_ENTRY)pListNode->Flink;

		}

		// when the node is equal to the head, we reached the end of the linked list, so we break out of the loop
	} while (pListNode != pListHead);



	return NULL;
}


int main() {
    printf("[i] Original 0x%p \n", GetModuleHandleW(L"NTDLL.DLL"));
    printf("[i] Replacement 0x%p \n", CustomGetModuleHandle(L"ntdll.dll"));

    printf("[#] Press <Enter> To Quit ... ");
    getchar();
    return 0;
}
