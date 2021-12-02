#pragma once
#include <cstdint>
#include "PastedBypass/baseadress.h"
#include "globals.h"

#define NoClipOffset 0x06130EE0

void SetNoClip(float value)
{
	uintptr_t NoClip = read<uintptr_t>(process_base + NoClipOffset);
	NoClip = read<uintptr_t>(NoClip + 0x98);
	NoClip = read<uintptr_t>(NoClip + 0x10);
	write<float>(NoClip + 0x5D4, value);
}

float GetNoClip() //updated
{
	uintptr_t NoClip = read<uintptr_t>(process_base + NoClipOffset);
	NoClip = read<uintptr_t>(NoClip + 0x98);
	NoClip = read<uintptr_t>(NoClip + 0x10);
	return read<float>(NoClip + 0x5D4);
}


void MiscThread() {
	while (true) {

		if (Noclip && GetNoClip() != -1.f) {
			SetNoClip(-1.f);
		}
		else if (!Noclip && GetNoClip() != 0.0003051850945f) {
			SetNoClip(0.0003051850945f);
		}
		Sleep(10);
	}
}