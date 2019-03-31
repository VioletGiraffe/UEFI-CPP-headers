#pragma once
#include "UEFI_types.h"
#include "EFI_device_path.h"

//
// Data types definitions
//

//*******************************************************
// EFI_LOCATE_SEARCH_TYPE
//*******************************************************
enum EFI_LOCATE_SEARCH_TYPE {
	AllHandles,
	ByRegisterNotify,
	ByProtocol
};

//*******************************************************
//EFI_ALLOCATE_TYPE
//*******************************************************
// These types are discussed in the “Description” section below.
typedef enum {
	AllocateAnyPages,
	AllocateMaxAddress,
	AllocateAddress,
	MaxAllocateType
} EFI_ALLOCATE_TYPE;

//*******************************************************
//EFI_MEMORY_TYPE
//*******************************************************
// These type values are discussed in Table 28 and Table 29.
typedef enum {
	EfiReservedMemoryType,
	EfiLoaderCode,
	EfiLoaderData,
	EfiBootServicesCode,
	EfiBootServicesData,
	EfiRuntimeServicesCode,
	EfiRuntimeServicesData,
	EfiConventionalMemory,
	EfiUnusableMemory,
	EfiACPIReclaimMemory,
	EfiACPIMemoryNVS,
	EfiMemoryMappedIO,
	EfiMemoryMappedIOPortSpace,
	EfiPalCode,
	EfiPersistentMemory,
	EfiMaxMemoryType
} EFI_MEMORY_TYPE;

//*******************************************************
//EFI_PHYSICAL_ADDRESS
//*******************************************************
typedef UINT64 EFI_PHYSICAL_ADDRESS;
typedef UINT64 EFI_VIRTUAL_ADDRESS;


//*******************************************************
//EFI_MEMORY_DESCRIPTOR
//*******************************************************
typedef struct {
	UINT32                          Type;           // Field size is 32 bits followed by 32 bit pad
	UINT32                          Pad;
	EFI_PHYSICAL_ADDRESS            PhysicalStart;  // Field size is 64 bits
	EFI_VIRTUAL_ADDRESS             VirtualStart;   // Field size is 64 bits
	UINT64                          NumberOfPages;  // Field size is 64 bits
	UINT64                          Attribute;      // Field size is 64 bits
} EFI_MEMORY_DESCRIPTOR;


//*******************************************************
//EFI_OPEN_PROTOCOL_INFORMATION_ENTRY
//*******************************************************

typedef struct {
	EFI_HANDLE                  AgentHandle;
	EFI_HANDLE                  ControllerHandle;
	UINT32                      Attributes;
	UINT32                      OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;


//*******************************************************

struct EFI_BOOT_SERVICES;

//
// EFI Memory
//

typedef
EFI_STATUS
(EFIAPI *EFI_ALLOCATE_PAGES) (
	IN EFI_ALLOCATE_TYPE            Type,
	IN EFI_MEMORY_TYPE              MemoryType,
	IN UINTN                        NoPages,
	OUT EFI_PHYSICAL_ADDRESS        *Memory
	);

typedef
EFI_STATUS
(EFIAPI *EFI_FREE_PAGES) (
	IN EFI_PHYSICAL_ADDRESS         Memory,
	IN UINTN                        NoPages
	);

typedef
EFI_STATUS
(EFIAPI *EFI_GET_MEMORY_MAP) (
	IN OUT UINTN                    *MemoryMapSize,
	IN OUT EFI_MEMORY_DESCRIPTOR    *MemoryMap,
	OUT UINTN                       *MapKey,
	OUT UINTN                       *DescriptorSize,
	OUT UINT32                      *DescriptorVersion
	);

typedef
EFI_STATUS
(EFIAPI *EFI_ALLOCATE_POOL) (
	IN EFI_MEMORY_TYPE              PoolType,
	IN UINTN                        Size,
	OUT VOID                        **Buffer
	);

typedef
EFI_STATUS
(EFIAPI *EFI_FREE_POOL) (
	IN VOID                         *Buffer
	);

typedef
EFI_STATUS
(EFIAPI *EFI_SET_VIRTUAL_ADDRESS_MAP) (
	IN UINTN                        MemoryMapSize,
	IN UINTN                        DescriptorSize,
	IN UINT32                       DescriptorVersion,
	IN EFI_MEMORY_DESCRIPTOR        *VirtualMap
	);

typedef
EFI_STATUS
(EFIAPI *EFI_CONVERT_POINTER) (
	IN UINTN                        DebugDisposition,
	IN OUT VOID                     **Address
	);


//
// EFI Events
//


typedef
VOID
(EFIAPI *EFI_EVENT_NOTIFY) (
	IN EFI_EVENT                Event,
	IN VOID                     *Context
	);

typedef
EFI_STATUS
(EFIAPI *EFI_CREATE_EVENT) (
	IN UINT32                       Type,
	IN EFI_TPL                      NotifyTpl,
	IN EFI_EVENT_NOTIFY             NotifyFunction,
	IN VOID                         *NotifyContext,
	OUT EFI_EVENT                   *Event
	);

enum EFI_TIMER_DELAY {
	TimerCancel,
	TimerPeriodic,
	TimerRelative,
	TimerTypeMax
};

typedef
EFI_STATUS
(EFIAPI *EFI_SET_TIMER) (
	IN EFI_EVENT                Event,
	IN EFI_TIMER_DELAY          Type,
	IN UINT64                   TriggerTime
	);

typedef
EFI_STATUS
(EFIAPI *EFI_SIGNAL_EVENT) (
	IN EFI_EVENT                Event
	);

typedef
EFI_STATUS
(EFIAPI *EFI_WAIT_FOR_EVENT) (
	IN UINTN                    NumberOfEvents,
	IN EFI_EVENT                *Event,
	OUT UINTN                   *Index
	);

typedef
EFI_STATUS
(EFIAPI *EFI_CLOSE_EVENT) (
	IN EFI_EVENT                Event
	);

typedef
EFI_STATUS
(EFIAPI *EFI_CHECK_EVENT) (
	IN EFI_EVENT                Event
	);

//
// Task priority level
//

typedef
EFI_TPL
(EFIAPI *EFI_RAISE_TPL) (
	IN EFI_TPL      NewTpl
	);

typedef
VOID
(EFIAPI *EFI_RESTORE_TPL) (
	IN EFI_TPL      OldTpl
	);

//
// Protocol handler functions
//

enum EFI_INTERFACE_TYPE {
	EFI_NATIVE_INTERFACE,
	EFI_PCODE_INTERFACE
};

typedef
EFI_STATUS
(EFIAPI *EFI_INSTALL_PROTOCOL_INTERFACE) (
	IN OUT EFI_HANDLE           *Handle,
	IN EFI_GUID                 *Protocol,
	IN EFI_INTERFACE_TYPE       InterfaceType,
	IN VOID                     *Interface
	);

typedef
EFI_STATUS
(EFIAPI *EFI_REINSTALL_PROTOCOL_INTERFACE) (
	IN EFI_HANDLE               Handle,
	IN EFI_GUID                 *Protocol,
	IN VOID                     *OldInterface,
	IN VOID                     *NewInterface
	);

typedef
EFI_STATUS
(EFIAPI *EFI_UNINSTALL_PROTOCOL_INTERFACE) (
	IN EFI_HANDLE               Handle,
	IN EFI_GUID                 *Protocol,
	IN VOID                     *Interface
	);

typedef
EFI_STATUS
(EFIAPI *EFI_HANDLE_PROTOCOL) (
	IN EFI_HANDLE               Handle,
	IN EFI_GUID                 *Protocol,
	OUT VOID                    **Interface
	);

typedef
EFI_STATUS
(EFIAPI *EFI_REGISTER_PROTOCOL_NOTIFY) (
	IN EFI_GUID                 *Protocol,
	IN EFI_EVENT                Event,
	OUT VOID                    **Registration
	);

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_HANDLE) (
	IN EFI_LOCATE_SEARCH_TYPE   SearchType,
	IN EFI_GUID                 *Protocol OPTIONAL,
	IN VOID                     *SearchKey OPTIONAL,
	IN OUT UINTN                *BufferSize,
	OUT EFI_HANDLE              *Buffer
	);

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_DEVICE_PATH) (
	IN EFI_GUID                 *Protocol,
	IN OUT EFI_DEVICE_PATH      **DevicePath,
	OUT EFI_HANDLE              *Device
	);

typedef
EFI_STATUS
(EFIAPI *EFI_INSTALL_CONFIGURATION_TABLE) (
	IN EFI_GUID                 *Guid,
	IN VOID                     *Table
	);

typedef
EFI_STATUS
(EFIAPI *EFI_RESERVED_SERVICE) (
	);

//
// Image functions
//

typedef
EFI_STATUS
(EFIAPI *EFI_IMAGE_LOAD) (
	IN BOOLEAN                      BootPolicy,
	IN EFI_HANDLE                   ParentImageHandle,
	IN EFI_DEVICE_PATH              *FilePath,
	IN VOID                         *SourceBuffer   OPTIONAL,
	IN UINTN                        SourceSize,
	OUT EFI_HANDLE                  *ImageHandle
	);

typedef
EFI_STATUS
(EFIAPI *EFI_IMAGE_START) (
	IN EFI_HANDLE                   ImageHandle,
	OUT UINTN                       *ExitDataSize,
	OUT CHAR16                      **ExitData  OPTIONAL
	);

typedef
EFI_STATUS
(EFIAPI *EFI_EXIT) (
	IN EFI_HANDLE                   ImageHandle,
	IN EFI_STATUS                   ExitStatus,
	IN UINTN                        ExitDataSize,
	IN CHAR16                       *ExitData OPTIONAL
	);

typedef
EFI_STATUS
(EFIAPI *EFI_IMAGE_UNLOAD) (
	IN EFI_HANDLE                   ImageHandle
	);

typedef
EFI_STATUS
(EFIAPI *EFI_EXIT_BOOT_SERVICES) (
	IN EFI_HANDLE                   ImageHandle,
	IN UINTN                        MapKey
	);

//
// Misc
//

typedef
EFI_STATUS
(EFIAPI *EFI_STALL) (
	IN UINTN                    Microseconds
	);

typedef
EFI_STATUS
(EFIAPI *EFI_GET_NEXT_MONOTONIC_COUNT) (
	OUT UINT64                  *Count
	);

typedef
EFI_STATUS
(EFIAPI *EFI_SET_WATCHDOG_TIMER) (
	IN UINTN                    Timeout,
	IN UINT64                   WatchdogCode,
	IN UINTN                    DataSize,
	IN CHAR16                   *WatchdogData OPTIONAL
	);

//
// DriverSupport Services
//

typedef
EFI_STATUS
(EFIAPI *EFI_CONNECT_CONTROLLER) (
	IN EFI_HANDLE               ControllerHandle,
	IN EFI_HANDLE               *DriverImageHandle OPTIONAL,
	IN EFI_DEVICE_PATH          *RemainingDevicePath OPTIONAL,
	IN BOOLEAN                  Recursive
	);

typedef
EFI_STATUS
(EFIAPI *EFI_DISCONNECT_CONTROLLER) (
	IN EFI_HANDLE               ControllerHandle,
	IN EFI_HANDLE               DriverImageHandle OPTIONAL,
	IN EFI_HANDLE               ChildHandle OPTIONAL
	);


//
// Open and Close Protocol Services
//

typedef
EFI_STATUS
(EFIAPI *EFI_OPEN_PROTOCOL) (
	IN EFI_HANDLE               Handle,
	IN EFI_GUID                 *Protocol,
	OUT VOID                    **Interface OPTIONAL,
	IN EFI_HANDLE               AgentHandle,
	IN EFI_HANDLE               ControllerHandle,
	IN UINT32                   Attributes
	);

typedef
EFI_STATUS
(EFIAPI *EFI_CLOSE_PROTOCOL) (
	IN EFI_HANDLE               Handle,
	IN EFI_GUID                 *Protocol,
	IN EFI_HANDLE               AgentHandle,
	IN EFI_HANDLE               ControllerHandle
	);

typedef
EFI_STATUS
(EFIAPI *EFI_OPEN_PROTOCOL_INFORMATION) (
	IN EFI_HANDLE               Handle,
	IN EFI_GUID                 *Protocol,
	OUT EFI_OPEN_PROTOCOL_INFORMATION_ENTRY **EntryBuffer,
	OUT UINTN                   *EntryCount
	);

//
// Library Services
//

typedef
EFI_STATUS
(EFIAPI *EFI_PROTOCOLS_PER_HANDLE) (
	IN EFI_HANDLE               Handle,
	OUT EFI_GUID                ***ProtocolBuffer,
	OUT UINTN                   *ProtocolBufferCount
	);

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_HANDLE_BUFFER) (
	IN EFI_LOCATE_SEARCH_TYPE   SearchType,
	IN EFI_GUID                 *Protocol OPTIONAL,
	IN VOID                     *SearchKey OPTIONAL,
	IN OUT UINTN                *NoHandles,
	OUT EFI_HANDLE              **Buffer
	);

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_PROTOCOL) (
	IN EFI_GUID                 *Protocol,
	IN VOID                     *Registration OPTIONAL,
	OUT VOID                    **Interface
	);

typedef
EFI_STATUS
(EFIAPI *EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES) (
	IN OUT EFI_HANDLE           *Handle,
	...
	);

typedef
EFI_STATUS
(EFIAPI *EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES) (
	IN OUT EFI_HANDLE           Handle,
	...
	);


//
// 32-bit CRC Services
//

typedef
EFI_STATUS
(EFIAPI *EFI_CALCULATE_CRC32) (
	IN VOID                     *Data,
	IN UINTN                    DataSize,
	OUT UINT32                  *Crc32
	);

//
// Misc Services
//

typedef
VOID
(EFIAPI *EFI_COPY_MEM) (
	IN VOID                     *Destination,
	IN VOID                     *Source,
	IN UINTN                    Length
	);

typedef
VOID
(EFIAPI *EFI_SET_MEM) (
	IN VOID                     *Buffer,
	IN UINTN                    Size,
	IN UINT8                    Value
	);

typedef
EFI_STATUS
(EFIAPI *EFI_CREATE_EVENT_EX) (
	IN UINT32                   Type,
	IN EFI_TPL                  NotifyTpl,
	IN EFI_EVENT_NOTIFY         NotifyFunction OPTIONAL,
	IN const VOID               *NotifyContext OPTIONAL,
	IN const EFI_GUID           EventGroup OPTIONAL,
	OUT EFI_EVENT               *Event
	);

struct EFI_BOOT_SERVICES {

	EFI_TABLE_HEADER                Hdr;

	//
	// Task priority functions
	//

	EFI_RAISE_TPL                   RaiseTPL;
	EFI_RESTORE_TPL                 RestoreTPL;

	//
	// Memory functions
	//

	EFI_ALLOCATE_PAGES              AllocatePages;
	EFI_FREE_PAGES                  FreePages;
	EFI_GET_MEMORY_MAP              GetMemoryMap;
	EFI_ALLOCATE_POOL               AllocatePool;
	EFI_FREE_POOL                   FreePool;

	//
	// Event & timer functions
	//

	EFI_CREATE_EVENT                CreateEvent;
	EFI_SET_TIMER                   SetTimer;
	EFI_WAIT_FOR_EVENT              WaitForEvent;
	EFI_SIGNAL_EVENT                SignalEvent;
	EFI_CLOSE_EVENT                 CloseEvent;
	EFI_CHECK_EVENT                 CheckEvent;

	//
	// Protocol handler functions
	//

	EFI_INSTALL_PROTOCOL_INTERFACE  InstallProtocolInterface;
	EFI_REINSTALL_PROTOCOL_INTERFACE ReinstallProtocolInterface;
	EFI_UNINSTALL_PROTOCOL_INTERFACE UninstallProtocolInterface;
	EFI_HANDLE_PROTOCOL             HandleProtocol;
	EFI_HANDLE_PROTOCOL             PCHandleProtocol;
	EFI_REGISTER_PROTOCOL_NOTIFY    RegisterProtocolNotify;
	EFI_LOCATE_HANDLE               LocateHandle;
	EFI_LOCATE_DEVICE_PATH          LocateDevicePath;
	EFI_INSTALL_CONFIGURATION_TABLE InstallConfigurationTable;

	//
	// Image functions
	//

	EFI_IMAGE_LOAD                  LoadImage;
	EFI_IMAGE_START                 StartImage;
	EFI_EXIT                        Exit;
	EFI_IMAGE_UNLOAD                UnloadImage;
	EFI_EXIT_BOOT_SERVICES          ExitBootServices;

	//
	// Misc functions
	//

	EFI_GET_NEXT_MONOTONIC_COUNT    GetNextMonotonicCount;
	EFI_STALL                       Stall;
	EFI_SET_WATCHDOG_TIMER          SetWatchdogTimer;

	//
	// DriverSupport Services
	//

	EFI_CONNECT_CONTROLLER          ConnectController;
	EFI_DISCONNECT_CONTROLLER       DisconnectController;

	//
	// Open and Close Protocol Services
	//
	EFI_OPEN_PROTOCOL               OpenProtocol;
	EFI_CLOSE_PROTOCOL              CloseProtocol;
	EFI_OPEN_PROTOCOL_INFORMATION   OpenProtocolInformation;

	//
	// Library Services
	//
	EFI_PROTOCOLS_PER_HANDLE        ProtocolsPerHandle;
	EFI_LOCATE_HANDLE_BUFFER        LocateHandleBuffer;
	EFI_LOCATE_PROTOCOL             LocateProtocol;
	EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES InstallMultipleProtocolInterfaces;
	EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES UninstallMultipleProtocolInterfaces;

	//
	// 32-bit CRC Services
	//
	EFI_CALCULATE_CRC32             CalculateCrc32;

	//
	// Misc Services
	//
	EFI_COPY_MEM                    CopyMem;
	EFI_SET_MEM                     SetMem;
	EFI_CREATE_EVENT_EX             CreateEventEx;

};