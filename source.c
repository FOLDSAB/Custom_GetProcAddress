#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <winternl.h>
#include <intrin.h>


HMODULE CustomGetmodulehandle(LPWSTR dllname);
FARPROC cusgetprocaddress(HMODULE hmodule, LPSTR apiname, int* found);
int main(int argc,char* argv[]) {

	int found = NULL;


	if (argc != 3) {
	
		printf("[!] Please enter full command line arguments like <DLL name> <API name>");
		goto END;

	}
	//converting to widestring;
	int len = MultiByteToWideChar(CP_UTF8, 0, argv[1], -1, NULL, 0);


	LPWSTR dllname = (LPWSTR)malloc(len * sizeof(WCHAR));

	
	MultiByteToWideChar(CP_UTF8, 0, argv[1], -1, dllname, len);

	

	

	

HMODULE hmodule = 	CustomGetmodulehandle(dllname);


if ( hmodule == NULL) {
	wprintf(L"[!] Cannot find the desired DLL %ls\n",dllname);
}

else {
	

	LPVOID dllbase = cusgetprocaddress(hmodule, argv[2], &found);

	if (found != 1) {
		printf("[!] Cannot find requested API: %s\n", argv[2]);
	}
}	


free(dllname);

END:
	
	printf("\n\npress enter to exit\n");
	getchar();
	return 0;

}

HMODULE CustomGetmodulehandle(LPWSTR dllname) {

	PTEB pthreadeblock = (PTEB)__readgsqword(0x30);

	PLDR_DATA_TABLE_ENTRY pdatatableentry1 = { 0 };
	pdatatableentry1 = (PLDR_DATA_TABLE_ENTRY)pthreadeblock->ProcessEnvironmentBlock->Ldr->InMemoryOrderModuleList.Flink;

	PLDR_DATA_TABLE_ENTRY pdatatableentry2 = (PLDR_DATA_TABLE_ENTRY)pthreadeblock->ProcessEnvironmentBlock->Ldr->Reserved2[1];


	while (pdatatableentry1->FullDllName.Buffer != NULL) {

		if (lstrcmpiW(dllname, (LPWSTR)pdatatableentry1->FullDllName.Buffer)==0) {
			printf("\n\n[+] Found %ls\n", pdatatableentry1->FullDllName.Buffer);
			printf("[+] The Dllbase is at: %p\n\n\n\n", pdatatableentry2->DllBase);
			
			return (HMODULE)pdatatableentry2->DllBase;
		}
		pdatatableentry1 = *(PLDR_DATA_TABLE_ENTRY*)pdatatableentry1;
		pdatatableentry2 = *(PLDR_DATA_TABLE_ENTRY*)pdatatableentry2;


	}

	return NULL;

	
}



FARPROC cusgetprocaddress(HMODULE hmodule, LPSTR apiname, int* found) {


	PBYTE dllbase = (PBYTE)hmodule;


	PIMAGE_DOS_HEADER pimgagedos = (PIMAGE_DOS_HEADER)dllbase;


	PIMAGE_NT_HEADERS pimagent = (PIMAGE_NT_HEADERS)((DWORD_PTR)dllbase + pimgagedos->e_lfanew);



	if (pimagent->Signature != IMAGE_NT_SIGNATURE) {
		printf("failure in signature");
		return FALSE;
	}


	PIMAGE_EXPORT_DIRECTORY pimageexport = (PIMAGE_EXPORT_DIRECTORY)((DWORD_PTR)dllbase + pimagent->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);




	PDWORD functionnames = (PDWORD)((DWORD_PTR)dllbase + pimageexport->AddressOfNames);
	PDWORD ordionalsaddr = (PDWORD)((DWORD_PTR)dllbase + pimageexport->AddressOfNameOrdinals);
	PDWORD pfunctionaddresses = (PDWORD)((DWORD_PTR)dllbase + pimageexport->AddressOfFunctions);


	for (DWORD i = 0; i < pimageexport->NumberOfNames;i++) {

		LPSTR name = (LPSTR)((DWORD_PTR)pimgagedos + functionnames[i]);

		WORD  ordionals = ordionalsaddr[i];

		PVOID functionaddress = (PVOID)((DWORD_PTR)dllbase + pfunctionaddresses[i]);



		if (strcmp(apiname, name) == 0) {
			printf("[+] %s \t Address: %p\n", name, functionaddress);
			*found = 1;
			break;
		}
		else {

			continue;
		}







	}


}
