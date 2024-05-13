
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>


FARPROC cusgetprocaddress(HMODULE hmodule,LPSTR apiname,int *found);
int main(int argc,char*argv[]) {

	int found = NULL;
	if (argc != 3) {
		printf("please enter a valid command\n");
		goto  END;
	}
	


	LPCSTR apiname = argv[2];

	
	HMODULE hmodule = GetModuleHandleA(argv[1]);
	


	if (hmodule == NULL) {


		printf("The getprocess failed with error no %d\n",GetLastError());
	}


	else {
		cusgetprocaddress(hmodule,apiname,&found);

		if (1 != found) {
			printf("Cannot find the API specified\n");
		}
		FreeLibrary(hmodule);

	}


END:

		printf("press enter to exit");
		getchar();

}


FARPROC cusgetprocaddress(HMODULE hmodule,LPSTR apiname,int *found) {

	
	PBYTE dllbase = (PBYTE)hmodule;


	PIMAGE_DOS_HEADER pimgagedos = (PIMAGE_DOS_HEADER)dllbase;


	PIMAGE_NT_HEADERS pimagent = (PIMAGE_NT_HEADERS)((DWORD_PTR)dllbase + pimgagedos->e_lfanew);



	if (pimagent->Signature != IMAGE_NT_SIGNATURE) {
		printf("failure in signature");
		return FALSE;
	}


	PIMAGE_EXPORT_DIRECTORY pimageexport = (PIMAGE_EXPORT_DIRECTORY)((DWORD_PTR) dllbase + pimagent->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);




	PDWORD functionnames = (PDWORD)((DWORD_PTR)dllbase + pimageexport->AddressOfNames);
	PDWORD ordionalsaddr = (PDWORD)((DWORD_PTR)dllbase + pimageexport->AddressOfNameOrdinals);
	PDWORD pfunctionaddresses = (PDWORD)((DWORD_PTR)dllbase + pimageexport->AddressOfFunctions);


	for (DWORD i = 0; i < pimageexport->NumberOfNames;i++) {

		LPSTR name = (LPSTR)((DWORD_PTR)pimgagedos + functionnames[i]);

		WORD  ordionals = ordionalsaddr[i];

		PVOID functionaddress = (PVOID)((DWORD_PTR)dllbase + pfunctionaddresses[i]);

		

		if (strcmp(apiname, name) == 0) {
			printf("[%d] %s at ORDIOANL %d \t Address: %p\n", i, name, ordionals, functionaddress);
			*found = 1;
			break;
		}
		else {
			
			continue;
		}

		



	
	
	}
	

}
