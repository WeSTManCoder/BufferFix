#include "serverplugin.h"

#include "subhook/subhook_unix.c"
using namespace subhook;

Hook g_memcpy_hook;

CServerPlugin g_ServerPlugin;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CServerPlugin, IServerPluginCallbacks, INTERFACEVERSION_ISERVERPLUGINCALLBACKS, g_ServerPlugin);

CServerPlugin::CServerPlugin() {}

CServerPlugin::~CServerPlugin() {}

void memcpy_Hook(void *dest, const void* src, size_t count) {
	memmove(dest, src, count);
}

bool CServerPlugin::Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory) {
	ConMsg(0, "----------\nBufferFix loaded!\n----------\n");
	
	g_memcpy_hook.Install((void *)memcpy, (void *)memcpy_Hook);
	
	return true;
}

void CServerPlugin::Unload(void) {
	if (g_memcpy_hook.IsInstalled()) g_memcpy_hook.Remove();
}

void CServerPlugin::Pause(void) { }

void CServerPlugin::UnPause(void) {}

const char *CServerPlugin::GetPluginDescription(void) {
	return "Buffer Fix [1.0.0]";
}

void CServerPlugin::LevelInit(char const *pMapName) {}

void CServerPlugin::ServerActivate( edict_t *pEdictList, int edictCount, int clientMax ) {}

void CServerPlugin::GameFrame(bool simulating) {}
void CServerPlugin::LevelShutdown(void) {}

void CServerPlugin::ClientActive(edict_t *pEntity) {}

void CServerPlugin::ClientDisconnect(edict_t *pEntity) {}

void CServerPlugin::ClientPutInServer(edict_t *pEntity, char const *playername) {}

void CServerPlugin::SetCommandClient(int index) {}

void CServerPlugin::ClientSettingsChanged(edict_t *pEdict) {}

PLUGIN_RESULT CServerPlugin::ClientConnect(bool *bAllowConnect, edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen) {
	return PLUGIN_CONTINUE;
}

PLUGIN_RESULT CServerPlugin::ClientCommand(edict_t *pEntity) {
	return PLUGIN_CONTINUE;
}

PLUGIN_RESULT CServerPlugin::NetworkIDValidated(const char *pszUserName, const char *pszNetworkID) {
	return PLUGIN_CONTINUE;
}