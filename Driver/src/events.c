#pragma warning (disable : 4047 4024)
#include "../include/events.h"


PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoaded(PUNICODE_STRING FullImageName, HANDLE ProcessId, PIMAGE_INFO ImageInfo) {
	
	if (wcsstr(FullImageName->Buffer, L"\\Device\\HarddiskVolume4\\Program Files (x86)\\Steam\\steamapps\\common\\Among Us\\GameAssembly.dll")) {
		DLLAdress = ImageInfo->ImageBase;
		procID = ProcessId;
		Print("AmongUS DLL Found");

	}

	return STATUS_SUCCESS;
}