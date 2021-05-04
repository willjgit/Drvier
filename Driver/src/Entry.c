#pragma warning (disable : 4047 4024)

#include "../include/Entry.h"
#include "../include/events.h"

VOID Unload(IN PDRIVER_OBJECT driverObject) {
	IoDeleteSymbolicLink(&DeviceLink);
	IoDeleteDevice(DeviceObj);
	PsRemoveLoadImageNotifyRoutine(ImageLoaded);
	DbgPrint("Unloaded");
	
}

NTSTATUS Create(PDEVICE_OBJECT DeviceObject, PIRP irp)
{
	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = 0;

	IoCompleteRequest(irp, IO_NO_INCREMENT);
	KdPrint(("Create Requested"));
	return STATUS_SUCCESS;
}

NTSTATUS Close(PDEVICE_OBJECT DeviceObject, PIRP irp)
{
	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = 0;

	IoCompleteRequest(irp, IO_NO_INCREMENT);
	KdPrint(("Close Requested"));
	return STATUS_SUCCESS;
}


NTSTATUS Control(PDEVICE_OBJECT DeviceObj, PIRP Irp) {
	NTSTATUS status = STATUS_SUCCESS;
	PIO_STACK_LOCATION idkWhatThisIs = IoGetCurrentIrpStackLocation(Irp);

	ULONG code = idkWhatThisIs->Parameters.DeviceIoControl.IoControlCode;



	Irp->IoStatus.Information = 0;
	Irp->IoStatus.Status = status;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return status;
}




NTSTATUS DriverEntry(IN PDRIVER_OBJECT driverObject, IN PCUNICODE_STRING registryPath) {
	NTSTATUS status;


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


	//PsSetLoadImageNotifyRoutine(ImageLoaded);

	driverObject->MajorFunction[IRP_MJ_CREATE] = Create;
	driverObject->MajorFunction[IRP_MJ_CLOSE]  = Close;
	driverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = Control;
	driverObject->DriverUnload = Unload;


	KdPrint(("Driver Loaded"));
	return STATUS_SUCCESS;

}


