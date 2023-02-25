#include "include/guardCounter.h"

#include <SimpleIni.h>

void guardCounter::update() {
	//DEBUG(gc_Timer);
	if (gc_Timer > 0) {
		static float* g_deltaTime = (float*)REL::RelocationID(523660, 410199).address();
		gc_Timer -= *g_deltaTime;
		if (gc_Timer <= 0) {
			auto pc = RE::PlayerCharacter::GetSingleton();
			if (pc) {
				pc->RemoveSpell(gc_triggerSpell);
				pc->SetGraphVariableBool("Val_GuardCounter", false);
			}
		}
	}
}

void guardCounter::registerBlock() {
	//DEBUG("registering block");
	auto pc = RE::PlayerCharacter::GetSingleton();
	if (pc) {
		pc->AddSpell(gc_triggerSpell);
		pc->SetGraphVariableBool("Val_GuardCounter", true);
		gc_Timer = gc_Time;
	}
	//RE::DebugNotification("guard counter start!");
}

void guardCounter::readSettings() {
	logger::info("Loading settings...");
	CSimpleIniA ini;
#define SETTINGFILE_PATH "Data\\SKSE\\Plugins\\EldenCounter.ini"
	ini.LoadFile(SETTINGFILE_PATH);
	gc_Time = std::stof(ini.GetValue("General", "Time"));
	logger::info("Settings loaded.");
}

void guardCounter::loadData() {
	logger::info("Loading data...");
	gc_triggerSpell = RE::TESDataHandler::GetSingleton()->LookupForm<RE::SpellItem>(0x801, "EldenCounter.esp");
	if (!gc_triggerSpell) {
		logger::error("Error: spell not found! Enable EldenCounter.esp");
		RE::DebugMessageBox("Error: spell not found! Enable EldenCounter.esp");
	}
}