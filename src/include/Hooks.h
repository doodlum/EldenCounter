#pragma once
#include "SKSE/Trampoline.h"


class Hook_MeleeHit
{
public:
	static void install() {
		auto& trampoline = SKSE::GetTrampoline();
		REL::Relocation<uintptr_t> hook{ REL::RelocationID(37673, 38627) }; //628c20
		_ProcessHit = trampoline.write_call<5>(hook.address() + REL::Relocate(0x3C0, 0x4a8), processHit);
		logger::info("Melee Hit hook installed.");
	}
private:
    static void processHit(RE::Actor* victim, RE::HitData& hitData);
    static inline REL::Relocation<decltype(processHit)> _ProcessHit;

};

class Hook_MainUpdate
{
public:
	static void install() {
		auto& trampoline = SKSE::GetTrampoline();
		REL::Relocation<uintptr_t> hook{ REL::RelocationID(35551, 36544) };  // 5AF3D0, main loop
		_Update = trampoline.write_call<5>(hook.address() + REL::Relocate(0x11F, 0x160), Update);
		logger::info("Main Update hook installed.");
	}

private:
	static void Update(RE::Main* a_this, float a2);
	static inline REL::Relocation<decltype(Update)> _Update;

};

class Hook_PlayerUpdate
{
public:
	static void install() {
		REL::Relocation<std::uintptr_t> PlayerCharacterVtbl{ RE::VTABLE_PlayerCharacter[0] };	
		_Update = PlayerCharacterVtbl.write_vfunc(0xAD, Update);
		logger::info("Player update hook installed");
	}
private:
	static void Update(RE::PlayerCharacter* a_this, float a_delta);
	static inline REL::Relocation<decltype(Update)> _Update;
};

class Hooks {
public:
	static void install() {
		SKSE::AllocTrampoline(1 << 4);
		Hook_MeleeHit::install();
		//Hook_MainUpdate::install();
		Hook_PlayerUpdate::install();
	}
};

