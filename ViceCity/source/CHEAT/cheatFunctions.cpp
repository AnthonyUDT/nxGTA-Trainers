#include "cheatFunctions.h"

DmntCheatProcessMetadata metadata;
int Read16;
int Read32;
int MathOutput;

//                   M E M O R Y      M A N I P U L A T I O N      //////////////////////////////////////////

u32 util::CopyHeapMemory(u32 read, u32 write)
{
    int ValueToCopy;

    dmntchtGetCheatProcessMetadata(&metadata);
	
	dmntchtReadCheatProcessMemory(metadata.heap_extents.base + read, &ValueToCopy, sizeof(4));
	dmntchtWriteCheatProcessMemory(metadata.heap_extents.base + write, &ValueToCopy, sizeof(4));
	return true;
}

//                A R I T H M A T I C      O P E R A T I O N S    //////////////////////////////////////////

u32 util::AddToOffset(u8 region, u32 Address, u32 Input)
{
    dmntchtGetCheatProcessMetadata(&metadata);
	
	if (region == 0x00)
	{
		dmntchtReadCheatProcessMemory(metadata.main_nso_extents.base + Address, &Read32, sizeof(4));
		MathOutput = Read32 + Input;
		dmntchtWriteCheatProcessMemory(metadata.main_nso_extents.base + Address, &MathOutput, sizeof(4));
	}
	else if (region == 0x01)
	{
		dmntchtReadCheatProcessMemory(metadata.heap_extents.base + Address, &Read32, sizeof(4));
		MathOutput = Read32 + Input;
		dmntchtWriteCheatProcessMemory(metadata.heap_extents.base + Address, &MathOutput, sizeof(4));
	}
	return true;
}

u32 util::SubFromOffset(u8 region, u32 Address, u32 Input)
{
    dmntchtGetCheatProcessMetadata(&metadata);
	
	if (region == 0x00)
	{
		dmntchtReadCheatProcessMemory(metadata.main_nso_extents.base + Address, &Read32, sizeof(4));
		MathOutput = Read32 - Input;
		dmntchtWriteCheatProcessMemory(metadata.main_nso_extents.base + Address, &MathOutput, sizeof(4));
	}
	else if (region == 0x01)
	{
		dmntchtReadCheatProcessMemory(metadata.heap_extents.base + Address, &Read32, sizeof(4));
		MathOutput = Read32 - Input;
		dmntchtWriteCheatProcessMemory(metadata.heap_extents.base + Address, &MathOutput, sizeof(4));
	}
	return true;
}

u32 util::ConvertToMOV(u32 Address, u8 Register, u16 Value)
{
	uint32_t M0VV = 0x52800000 + Register;
	uint32_t M0VVPlus = 0x52900000 + Register;
    dmntchtGetCheatProcessMetadata(&metadata);
	
	if (Value <= 0x7FFF) 
	{
		uint16_t MathDo = (Value * 2) & 0xFFFF;
		uint32_t Result = M0VV + (((MathDo << 4) & 0xFFFFF));
		dmntchtWriteCheatProcessMemory(metadata.main_nso_extents.base + Address, &Result, sizeof(4));
	}
	else if (Value >= 0x8000)
	{
		uint16_t MathDo = (Value * 2) & 0xFFFF;
		uint32_t Result = M0VVPlus + (((MathDo << 4) & 0xFFFFF));
		dmntchtWriteCheatProcessMemory(metadata.main_nso_extents.base + Address, &Result, sizeof(4));
	}
	return true;
}

u32 util::CheckIDRange(u16 Value, u16 min, u16 max, u32 offset, u16 reset)
{
    dmntchtGetCheatProcessMetadata(&metadata);
    
    if (Value <= min || Value >= max) 
    {
        dmntchtWriteCheatProcessMemory(metadata.heap_extents.base + offset, &reset, sizeof(2));
    }
    return true;
}
