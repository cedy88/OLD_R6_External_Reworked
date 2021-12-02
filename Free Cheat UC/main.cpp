
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <random>
#include <stdint.h>
#include <list>
#include "overlay.hpp"
#include <thread>
#include "globals.h"
#include "defs.hpp"
#include "offsets.h"
#include <dwrite.h>
#include "ESP.h"
#include "Misc.h"
#include "BypassMain.h"

HWND hGameWnd;
HWND hOverlayWnd;
RECT wndRect;


void Update() {
	while (true) {
		gameManager = O::GameManagaganeger();
		entityList = O::EntityManager(gameManager).first;
		entityCount = O::EntityManager(gameManager).second;
		camera = O::GetCamera();
		localPlayer = O::GetLocalPlayer();
		localPawn = O::GetEntityPawn(localPlayer);
		replicationinfo = O::ReplicationInfo(localPlayer);
		localPos = O::GetEntPos(localPawn);
		profileManager = O::GetGamerProfileManager();

	if (showmenu && rendering) {
		if (GetAsyncKeyState(VK_F1) & 1)
			BoxESP = !BoxESP;

		if (GetAsyncKeyState(VK_F2) & 1)
			headBox = !headBox;

		if (GetAsyncKeyState(VK_F3) & 1)
			Noclip = !Noclip;
	}
	if (GetAsyncKeyState(VK_INSERT) & 1)
		showmenu = !showmenu;
	}
}

static void render(FOverlay* overlay) {
	while (rendering) {
		overlay->begin_scene();
		overlay->clear_scene();
		frame++;
		ESPLoop();
		RenderMenu();
		overlay->end_scene();
	}
}

static void _init(FOverlay* overlay) {
	if (!overlay->window_init()) {
		printf("[!] Error init overlay window\n");
		Sleep(5000);
		return;
	}
	else {
		printf("[+] init overlay window\n");
	}

	if (!overlay->init_d2d())
		return;

	std::thread r(render, overlay);
	std::thread up(Update);
	std::thread dscdsc(MiscThread);
	r.join();
	up.detach();
	dscdsc.detach();

	overlay->d2d_shutdown();

	return;
}

std::string username;
std::string password;

int main() {
	SetConsoleTitle("Free Cheat Rainbow Six | By cedy");
	
	FUCKBE();

	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	HDC monitor = GetDC(hDesktop);
	int current = GetDeviceCaps(monitor, VERTRES);
	int total = GetDeviceCaps(monitor, DESKTOPVERTRES);
	ScreenCenterX = GetSystemMetrics(SM_CXSCREEN) / 2;
	ScreenCenterY = GetSystemMetrics(SM_CYSCREEN) / 2;
	g_overlay = { 0 };
	_init(g_overlay);
}