#include <stdio.h>
#include <Windows.h>
#include <Lm.h>
#pragma comment(lib, "Netapi32.lib")

// Returns TRUE if the machine is domain joined
BOOL CheckDomainStatus(){
	LPWSTR lpNameBuffer = NULL;
	PNETSETUP_JOIN_STATUS status;

	NET_API_STATUS nStatus = NetGetJoinInformation(NULL, &lpNameBuffer, &status);

	if (nStatus == NERR_Success) {
		if (status == NetSetupDomainName) {
			NetApiBufferFree(lpNameBuffer);
			return TRUE;
		}
		else {
			NetApiBufferFree(lpNameBuffer);
			return FALSE;
		}
	}
}

int main() {

	// Check the domain join status, exit if not domain joined
	if (!CheckDomainStatus()) {
		printf("[!] Machine is not domain joined, exiting!");
		return 1;
	}

	printf("[+] Machine is domain joined, continuing...");

	return 0;
}
