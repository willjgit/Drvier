#pragma warning (disable : 4047 4024)

#include "../include/Entry.h"
#include "../include/events.h"

VOID Unload(IN PDRIVER_OBJECT driverObject) {
	UNREFERENCED_PARAMETER(driverObject);
	IoDeleteSymbolicLink(&DeviceLink);
	IoDeleteDevice(DeviceObj);
	PsRemoveLoadImageNotifyRoutine(ImageLoaded);
	Print("Unloaded");
	
}

NTSTATUS Create(PDEVICE_OBJECT DeviceObject, PIRP irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = 0;

	IoCompleteRequest(irp, IO_NO_INCREMENT);
	Print("Create Requested");
	return STATUS_SUCCESS;
}

NTSTATUS Close(PDEVICE_OBJECT DeviceObject, PIRP irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = 0;

	IoCompleteRequest(irp, IO_NO_INCREMENT);
	Print("Close Requested");
	return STATUS_SUCCESS;
}


NTSTATUS Control(PDEVICE_OBJECT DeviceObject, PIRP Irp) {
	UNREFERENCED_PARAMETER(DeviceObject);
	
	
	NTSTATUS status;
	ULONG bytes = 0;


	PIO_STACK_LOCATION idkWhatThisIs = IoGetCurrentIrpStackLocation(Irp);

	ULONG code = idkWhatThisIs->Parameters.DeviceIoControl.IoControlCode;

	if (code == READ)
	{
		Print("Read Requested");
		status = STATUS_SUCCESS;
		bytes = 0;
	}
	
	else if (code == DLL_ADDR_REQUEST) {
		PULONG addr = Irp->AssociatedIrp.SystemBuffer;
		*addr = DLLAdress;
		status = STATUS_SUCCESS;
		bytes = sizeof(*addr);
	}

	Irp->IoStatus.Information = bytes;
	Irp->IoStatus.Status = status;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return status;
}




NTSTATUS DriverEntry(IN PDRIVER_OBJECT driverObject, IN PCUNICODE_STRING registryPath) {
	
	UNREFERENCED_PARAMETER(registryPath);
	
	NTSTATUS status;


	status = IoCreateDevice(driverObject, 0, &DeviceName, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &DeviceObj);
	
	if (!NT_SUCCESS(status))
	{
		Print("Device Creation Failed");
		return status;
	}

	status = IoCreateSymbolicLink(&DeviceLink, &DeviceName);

	if (!NT_SUCCESS(status))
	{
		Print("Link Creation Failed");
		IoDeleteDevice(DeviceObj);
		return status;
	}


	PsSetLoadImageNotifyRoutine(ImageLoaded);

	driverObject->MajorFunction[IRP_MJ_CREATE] = Create;
	driverObject->MajorFunction[IRP_MJ_CLOSE]  = Close;
	driverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = Control;
	driverObject->DriverUnload = Unload;


	Print("Driver Loaded");
	return STATUS_SUCCESS;

}


