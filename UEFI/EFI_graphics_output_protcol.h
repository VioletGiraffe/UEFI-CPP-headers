#pragma once
#include "UEFI_types.h"

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID { 0x9042a9de,0x23dc,0x4a38, {0x96,0xfb,0x7a,0xde,0xd0,0x80,0x51,0x6a} }

struct EFI_GRAPHICS_OUTPUT_PROTOCOL;

struct EFI_PIXEL_BITMASK {
	UINT32            RedMask;
	UINT32            GreenMask;
	UINT32            BlueMask;
	UINT32            ReservedMask;
};

typedef enum {
	PixelRedGreenBlueReserved8BitPerColor,
	PixelBlueGreenRedReserved8BitPerColor,
	PixelBitMask,
	PixelBltOnly,
	PixelFormatMax
} EFI_GRAPHICS_PIXEL_FORMAT;

struct EFI_GRAPHICS_OUTPUT_MODE_INFORMATION {
	UINT32                     Version;
	UINT32                     HorizontalResolution;
	UINT32                     VerticalResolution;
	EFI_GRAPHICS_PIXEL_FORMAT  PixelFormat;
	EFI_PIXEL_BITMASK          PixelInformation;
	UINT32                     PixelsPerScanLine;
};

typedef
EFI_STATUS
(EFIAPI *EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE) (
	IN  EFI_GRAPHICS_OUTPUT_PROTOCOL          *This,
	IN  UINT32                                ModeNumber,
	OUT UINTN                                 *SizeOfInfo,
	OUT EFI_GRAPHICS_OUTPUT_MODE_INFORMATION  **Info
	);

typedef
EFI_STATUS
(EFIAPI *EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE) (
	IN  EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
	IN  UINT32                       ModeNumber
	);

typedef struct {
	UINT8 Blue;
	UINT8 Green;
	UINT8 Red;
	UINT8 Reserved;
} EFI_GRAPHICS_OUTPUT_BLT_PIXEL;

typedef union {
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL Pixel;
	UINT32                        Raw;
} EFI_GRAPHICS_OUTPUT_BLT_PIXEL_UNION;

typedef enum {
	EfiBltVideoFill,
	EfiBltVideoToBltBuffer,
	EfiBltBufferToVideo,
	EfiBltVideoToVideo,
	EfiGraphicsOutputBltOperationMax
} EFI_GRAPHICS_OUTPUT_BLT_OPERATION;

typedef
EFI_STATUS
(EFIAPI *EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT) (
	IN  EFI_GRAPHICS_OUTPUT_PROTOCOL            *This,
	IN  EFI_GRAPHICS_OUTPUT_BLT_PIXEL           *BltBuffer, OPTIONAL
	IN  EFI_GRAPHICS_OUTPUT_BLT_OPERATION       BltOperation,
	IN  UINTN                                   SourceX,
	IN  UINTN                                   SourceY,
	IN  UINTN                                   DestinationX,
	IN  UINTN                                   DestinationY,
	IN  UINTN                                   Width,
	IN  UINTN                                   Height,
	IN  UINTN                                   Delta       OPTIONAL
	);

struct EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE {
	UINT32                                 MaxMode;
	UINT32                                 Mode;
	EFI_GRAPHICS_OUTPUT_MODE_INFORMATION   *Info;
	UINTN                                  SizeOfInfo;
	EFI_PHYSICAL_ADDRESS                   FrameBufferBase;
	UINTN                                  FrameBufferSize;
};

struct EFI_GRAPHICS_OUTPUT_PROTOCOL {
	EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE  QueryMode;
	EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE    SetMode;
	EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT         Blt;
	EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE        *Mode;
};