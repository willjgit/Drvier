#pragma warning (disable : 4047 4024)

#include "../include/Entry.h"
#include "../include/events.h"

VOID Unload(IN PDRIVER_OBJECT driverObject) {
	IoDeleteSymbolicLink(&DeviceLink);
	IoDeleteDevice(DeviceObj);
	PsRemoveLoadImageNotifyRoutine(ImageLoaded);
	DbgPrint("Unloaded");
	
}


NTSTATUS DriverEntry(IN PDRIVER_OBJECT driverObject, IN PCUNICODE_STRING registryPath) {
	NTSTATUS status;

	driverObject->DriverUnload = Unload;
	

	status = IoCreateDevice(driverObject, 0, &DeviceName, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &DeviceObj);
	
	if (!NT_SUCCESS(status))
	{
		KdPrint(("Device Creation Failed"));
		return status;
	}

	status = IoCreateSymbolicLink(&DeviceLink, &DeviceName);

	if (!NT_SUCCESS(status))
	{
		KdPrint(("Link Creation Failed"));
		IoDeleteDevice(DeviceObj);
		return status;
	}

	KdPrint(("Driver Loaded"));

	
	PsSetLoadImageNotifyRoutine(ImageLoaded);




	DbgPrint("Hello World");
	return STATUS_SUCCESS;

}