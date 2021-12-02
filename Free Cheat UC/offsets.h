#pragma once
#include "defs.hpp"
#include <emmintrin.h>
#include <Windows.h>
#include <TlHelp32.h>
#include <PsApi.h>
#include <string>
#include <stdint.h>
#include <cmath>
#include <math.h>
#include "globals.h"
#include "PastedBypass/baseadress.h"

#define GameManager 0x7430278
#define CameraManager 0x6241A58
#define ProfileManager 0x71A1DA0
namespace O
{
	uint64_t GameManagaganeger()
	{
		return ((((read<uint64_t>)(process_base + GameManager) ^ 0xA64036C3D7DADA08ui64) - 2) ^ 0x1FC105FFDB02702Di64);
	}

	uint64_t GetGamerProfileManager()
	{
		return __ROL8__(read<uint64_t>(process_base + ProfileManager) ^ 0xE3B642AEA4F7DC0Aui64, 12) ^ 0x93C4ED5B9A1A2780ui64;
	}

	uintptr_t GetCamera()
	{
		uintptr_t cameraManager = read<uintptr_t>(process_base + CameraManager);
		cameraManager = read<uintptr_t>(cameraManager + 0x40);
		cameraManager = read<uintptr_t>(cameraManager + 0x0);
		return cameraManager;
	}

	uintptr_t GetLocalPlayer()
	{
		return ((read<uintptr_t>(read<uintptr_t>(__ROL8__(read<uintptr_t>(profileManager + 0x18) - 98i64, 46) ^ 0x75A2059DFCFFA4AEi64) + 0x38) ^ 0x49) + 7301305760360871833 ^ 0xB1954139F4DA145Cui64);
	}

	static std::pair<uint64_t, uint32_t> EntityManager(const uint64_t game_manager)
	{
		const auto decryption = [&game_manager](const uint32_t offset = 0) -> uint64_t
		{
			const auto temp = read<uint64_t>(game_manager + offset + 0x68);

			return __ROL8__((temp ^ 0x501C99FA5BADC9AA), 56);
		};

		return { decryption(), static_cast<uint32_t>(decryption(8) & 0x3FFFFFFF) };
	}

	static uintptr_t Skeleton(const uint64_t pawn)
	{
		return _rotl64(read<uint64_t>(pawn + 0x9A0) + 7405000852998969040i64, 50) - 1594732191723392772i64;
	}

	uint64_t GetEntityPawn(uint64_t address)
	{
		return (((read<uintptr_t>(address + 0x38) ^ 0x9450ED0F3BBB636D) - 0x57) ^ 0x29621A04BD7BFD64);
	}

	uint64_t component(uint64_t pawn)
	{
		return (read<uint64_t>(pawn + 0x18));
	}

	float GetHealth(uintptr_t pawn)
	{
		uintptr_t entity_actor = component(pawn);
		uintptr_t entity_info = read<uintptr_t>(entity_actor + 0xD8);
		uintptr_t main_component = read<uintptr_t>(entity_info + 0x8);
		return read<int>(main_component + 0x1BC);
	}

	vec3 GetEntPos(uint64_t entPawn)
	{
		entPawn = read<uint64_t>(entPawn + 0x18);
		return read<vec3>(entPawn + 0x50);
	}

	void TransformsCalculation(__int64 pBones, __m128* ResultPosition, __m128* BoneInfo) //23.10.2021
	{
		__m128 v5; // xmm2
		__m128 v6; // xmm3
		__m128 v7; // xmm0
		__m128 v8; // xmm4
		__m128 v9; // xmm1

		__m128 v10 = { 0.500f, 0.500f, 0.500f, 0.500f };
		__m128 v11 = { 2.000f, 2.000f, 2.000f, 0.000f };

		__m128 v12 = read<__m128>(pBones);
		__m128 v13 = read<__m128>(pBones + 0x10);

		v5 = v13;

		v6 = _mm_mul_ps(*(__m128*)BoneInfo, v5);
		v6.m128_f32[0] = v6.m128_f32[0]
			+ (float)(_mm_cvtss_f32(_mm_shuffle_ps(v6, v6, 0x55)) + _mm_cvtss_f32(_mm_shuffle_ps(v6, v6, 0xAA)));
		v7 = _mm_shuffle_ps(v13, v5, 0xFF);
		v8 = _mm_sub_ps(
			_mm_mul_ps(_mm_shuffle_ps(v5, v5, 0xD2), *(__m128*)BoneInfo),
			_mm_mul_ps(_mm_shuffle_ps(*(__m128*)BoneInfo, *(__m128*)BoneInfo, 0xD2), v5));
		v9 = _mm_shuffle_ps(v12, v12, 0x93);
		v9.m128_f32[0] = 0.0;
		*(__m128*)ResultPosition = _mm_add_ps(
			_mm_shuffle_ps(v9, v9, 0x39),
			_mm_mul_ps(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_shuffle_ps(v8, v8, 0xD2), v7),
						_mm_mul_ps(_mm_shuffle_ps(v6, v6, 0), v5)),
					_mm_mul_ps(
						_mm_sub_ps(_mm_mul_ps(v7, v7), (__m128)v10),
						*(__m128*)BoneInfo)),
				(__m128)v11));
	}

	vec3 get_bone_pos_by_id(std::uintptr_t playerpawn, int index)
	{
		__m128 Output{};

		std::uintptr_t pBonesChain2 = Skeleton(playerpawn);
		pBonesChain2 = read<std::uintptr_t>(pBonesChain2);

		std::uintptr_t pBones = read<std::uintptr_t>(pBonesChain2 + 0x250);

		std::uintptr_t pBonesData = read<std::uintptr_t>(pBones + 0x58);
	
		std::uintptr_t idarray = read<std::uintptr_t>(pBonesChain2 + 0xB8);
		
		index = read<int>(idarray + index * 0x4);

		__m128 BoneInfo = read<__m128>((0x20 * index) + pBonesData);
		TransformsCalculation(pBones, &Output, &BoneInfo);

		return { Output.m128_f32[0], Output.m128_f32[1], Output.m128_f32[2] };
	}

	vec3 DecryptCamera(__m128i address)
	{
		__m128i vector = _mm_load_si128(&address);

		vector.m128i_u64[0] = ((vector.m128i_u64[0] - 74) ^ 0x14) + 0xB6EE60C4C14D9D2A;
		vector.m128i_u64[1] = ((vector.m128i_u64[1] - 74) ^ 0x14) + 0xB6EE60C4C14D9D2A;

		return *reinterpret_cast<vec3*>(&vector);
	}

	uint64_t ReplicationInfo(uint64_t controller)
	{
		return  __ROL8__(read<uint64_t>(controller + 0xA8) - 0x61736EF72943DB24i64, 44) - 118i64;
	}

	static uint32_t get_team_id(const uint64_t replicationinfo) 
	{
		return (__ROL4__(read<uintptr_t>((read<uintptr_t>(replicationinfo + 0x6F8) ^ 0xECEBEC05F6304F95ui64) + 0xA0), 2) ^ 0x27) - 2129313830;
	}

	bool WorldToScreen(vec3 world, vec2& screen)
	{
		vec3 temp = world - O::DecryptCamera(read<__m128i>(camera + 0x190)); // translation
		float x, y, z = { };
		x = temp.Dot(O::DecryptCamera(read<__m128i>(camera + 0x160))); //right
		y = temp.Dot(O::DecryptCamera(read<__m128i>(camera + 0x170))); // up
		z = temp.Dot(O::DecryptCamera(read<__m128i>(camera + 0x180)) * -1.f); // forward

		int width = GetSystemMetrics(SM_CXSCREEN);
		int height = GetSystemMetrics(SM_CYSCREEN);

		screen.x = (width / 2.f) * (1.f + x / -read<float>(camera + 0x360) / z); // fovx
		screen.y = (height / 2.f) * (1.f - y / -read<float>(camera + 0x364) / z); // fovy

		if (screen.x < 0.0f || screen.x > width)
			return false;
		return z >= 1.0f;
	}

}