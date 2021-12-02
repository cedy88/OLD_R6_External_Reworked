#pragma once
#include "defs.hpp"
#include "overlay.hpp"

bool BoxESP = false;
bool headBox = false;
bool Noclip = false;

//Overlay
bool showmenu = true;
bool rendering = true;
int frame = 0;
FOverlay* g_overlay;

float ScreenCenterX;
float ScreenCenterY;

uint64_t gameManager;
uint64_t profileManager;
uint64_t entityList;
uint32_t entityCount;
uintptr_t camera;
uint64_t localPlayer;
uint64_t localPawn;
uint64_t localTeam;
uint64_t replicationinfo;


vec3 localPos;
//
uint64_t process_base = 0;
std::uint32_t process_id = 0;