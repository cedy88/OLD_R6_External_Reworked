#pragma once
#include "globals.h"
#include "offsets.h"
#include "PastedBypass/baseadress.h"
#include <d2d1helper.h>

HWND hwnd = NULL;
HWND hwnd_active = NULL;
HWND OverlayWindow = NULL;

void ESPLoop() {

	hwnd = FindWindowA("R6Game", NULL);
	OverlayWindow = FindWindow("CEF-OSC-WIDGET", "NVIDIA GeForce Overlay");
	hwnd_active = GetForegroundWindow();

	if (hwnd_active == hwnd) {

		ShowWindow(OverlayWindow, SW_SHOW);
	}
	else
	{
		ShowWindow(OverlayWindow, SW_HIDE);
	}

	if (!FindWindowA("R6Game", NULL))
	{
		rendering = false;
		showmenu = false;
		Sleep(1000);
		MessageBoxA(NULL, "Bye", "Cheat", MB_OK);
		exit(0);
	}

	for (int i = 0; i < entityCount; i++)
	{
		if (entityCount > 50 || entityCount < 0) break;

		uint64_t player = read<uintptr_t>(entityList + (i * sizeof(uint64_t)));

		localTeam = O::get_team_id(replicationinfo);
		uint64_t replicationInfo = O::ReplicationInfo(player);
		if (O::get_team_id(replicationInfo) == localTeam) continue;

		player = O::GetEntityPawn(player);
		vec3 pos = O::GetEntPos(player);
		vec3 headPos = O::get_bone_pos_by_id(player, 11);
		vec3 neckPos = O::get_bone_pos_by_id(player, 10);
		vec2 screenPos;
		vec2 screenHead;
		vec2 screenNeck;

		if (!O::WorldToScreen(pos, screenPos)) continue;
		if (!O::WorldToScreen(headPos, screenHead)) continue;
		if (!O::WorldToScreen(neckPos, screenNeck)) continue;

		auto BoxColor = D2D1::ColorF(255, 0, 0, 255);
		auto FillBoxColor = D2D1::ColorF(0, 0, 0, 0.6);

		float top = screenHead.y;
		float bottom = screenPos.y;
		float width = abs(top - bottom) / 2.f;
		float left = screenPos.x - width / 2.f;
		float right = screenPos.x + width / 2.f;
		float neckHeadDistance = screenNeck.Dist2D(screenHead);
		float height = abs(abs(screenHead.y) - abs(screenPos.y));

		if (BoxESP)
		{
			auto extend = + 10;
			g_overlay->draw_line(left, top - extend, right, top - extend, BoxColor); // bottom
			g_overlay->draw_line(left, bottom, right, bottom, BoxColor); // up
			g_overlay->draw_line(left, top - extend, left, bottom, BoxColor); // left
			g_overlay->draw_line(right, top - extend, right, bottom, BoxColor); // right

			auto rect = D2D1_RECT_F();
			rect.bottom = bottom;
			rect.top = top - extend;
			rect.right = right;
			rect.left = left;

			g_overlay->draw_box(rect, FillBoxColor);
		
		}
		if (headBox)
		{
			g_overlay->draw_boxnew(screenHead.x, screenHead.y, neckHeadDistance, neckHeadDistance, BoxColor);
		}
	}
}

void RenderMenu()
{
	if (showmenu && rendering)
	{
		g_overlay->draw_text(5, 5, D2D1::ColorF(255, 20, 20, 255), "Rainbow Six by Cedy [INSERT]");

		if (BoxESP)
			g_overlay->draw_text(5, 20, D2D1::ColorF(0, 255, 0, 255), "F1 Box : ON");
		else
			g_overlay->draw_text(5, 20, D2D1::ColorF(255, 0, 0, 255), "F1 Box : OFF");

		if (headBox)
			g_overlay->draw_text(5, 40, D2D1::ColorF(0, 255, 0, 255), "F2 headBox : ON");
		else
			g_overlay->draw_text(5, 40, D2D1::ColorF(255, 0, 0, 255), "F2 headBox : OFF");

		if (Noclip)
			g_overlay->draw_text(5, 60, D2D1::ColorF(0, 255, 0, 255), "F3 Noclip : ON");
		else
			g_overlay->draw_text(5, 60, D2D1::ColorF(255, 0, 0, 255), "F3 Noclip : OFF");
	}
}

