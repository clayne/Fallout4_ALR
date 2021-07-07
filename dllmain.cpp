// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "PathBuilder.h"
#include "ImageConvert.h"

IDebugLog glog; 
PluginHandle g_pluginHandle = kPluginHandle_Invalid;
F4SEScaleformInterface* g_scaleform = nullptr;

__declspec(dllexport) PathBuilderParent* PathBuilderCreate()
{
	return new PathBuilder();
}
__declspec(dllexport) ImageConvertParent*  ImageConvertCreate(PathBuilderParent * PBinst)
{
	return new ImageConvert(PBinst);
}

extern "C"
{
	__declspec(dllexport) bool F4SEPlugin_Query(const F4SEInterface* f4se, PluginInfo* info)
	{
		char logPath[MAX_PATH];
		sprintf_s(logPath, MAX_PATH, "%s%s.log", "\\My Games\\Fallout4\\F4SE\\", PLUGIN_NAME);
		glog.OpenRelative(CSIDL_MYDOCUMENTS, logPath);

		_MESSAGE("%s", PLUGIN_NAME, PLUGIN_VERSION);

		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = PLUGIN_NAME;
		info->version = PLUGIN_VERSION;

		g_pluginHandle = f4se->GetPluginHandle();


		if (f4se->runtimeVersion < RUNTIME_VERSION_1_10_163) {
			_MESSAGE("ERROR: Version ", CURRENT_RELEASE_RUNTIME, " Required!");
			return false;
		}

		if (f4se->isEditor)
		{
			_MESSAGE("ERROR: isEditor Is True");
			return false;
		}

		g_scaleform = (F4SEScaleformInterface*)f4se->QueryInterface(kInterface_Scaleform);

		if (!g_scaleform) {
			_MESSAGE("ERROR: Scaleform Interface Failed To Load");
			return false;
		}

		return true;
	}

	__declspec(dllexport) bool F4SEPlugin_Load(const F4SEInterface* f4se)
	{
		_MESSAGE("%s loaded", PLUGIN_NAME);
		PathBuilderParent* PBinst = PathBuilderCreate();
		ImageConvertParent* IMinst = ImageConvertCreate(PBinst);
		delete PBinst;
		delete IMinst;

		return true;
	}
};