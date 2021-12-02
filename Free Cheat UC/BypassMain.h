#pragma once
#include <Windows.h>
#include <iostream>
#include "globals.h"
#include "PastedBypass/mhyprot.hpp"
#include "PastedBypass/baseadress.h"

#define max11(a,b)            (((a) > (b)) ? (a) : (b))
#define min11(a,b)            (((a) < (b)) ? (a) : (b))

LONG WINAPI SimplestCrashHandler(EXCEPTION_POINTERS* ExceptionInfo)
{
	std::cout << "[!!] Crash at addr 0x" << ExceptionInfo->ExceptionRecord->ExceptionAddress << " by 0x" << std::hex << ExceptionInfo->ExceptionRecord->ExceptionCode << std::endl;

	return EXCEPTION_EXECUTE_HANDLER;
}

void FUCKBE() {
	SetUnhandledExceptionFilter(SimplestCrashHandler);
	system("sc stop mhyprot2");
	system("cls");

	process_id = GetProcessId("RainbowSix.exe");
	if (!process_id) {
		printf("[!] process \"%s\ was not found\n", "RainbowSix.exe");
		Sleep(5000);
		return;
	}
	if (!mhyprot::init()) {
		printf("[!] failed to initialize vulnerable driver\n");
		Sleep(5000);
		return;
	}
	if (!mhyprot::driver_impl::driver_init(false/*debug*/, false /*seedmap*/)) {
		printf("[!] failed to initialize driver properly\n");
		mhyprot::unload();
		Sleep(5000);
		return;
	}
	process_base = GetProcessBase(process_id);
	if (!process_base) {
		printf("[!] failed to get baseadress\n");
		Sleep(5000);
		mhyprot::unload();
		return;
	}
	std::cout << "Base Adress : " << std::hex << process_base << std::endl;
	IMAGE_DOS_HEADER dos_header = read<IMAGE_DOS_HEADER>(process_base);
	if (dos_header.e_magic != 0x5A4D) {}
	Sleep(2000);
	system("cls");
}