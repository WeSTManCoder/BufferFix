#include "serverplugin.h"

#include "subhook/subhook_unix.c"
using namespace subhook;

Hook g_memcpy_hook;

CBufferFix g_ServerPlugin;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CBufferFix, IServerPluginCallbacks, INTERFACEVERSION_ISERVERPLUGINCALLBACKS, g_ServerPlugin);

CBufferFix::CBufferFix() {}

CBufferFix::~CBufferFix() {}

void memcpy_Hook(void *dest, const void* src, size_t count) {
	memmove(dest, src, count);
}

bool CBufferFix::Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory) {
	ConMsg(0, "----------\nBufferFix loaded!\n----------\n");
	
	g_memcpy_hook.Install((void *)memcpy, (void *)memcpy_Hook);
	
	return true;
}

void CBufferFix::Unload(void) {
	if (g_memcpy_hook.IsInstalled()) g_memcpy_hook.Remove();
}

void CBufferFix::Pause(void) { }

void CBufferFix::UnPause(void) {}

const char *CBufferFix::GetPluginDescription(void) {
	return "Buffer Fix [1.0.0]";
}

void CBufferFix::LevelInit(char const *pMapName) {}

void CBufferFix::ServerActivate( edict_t *pEdictList, int edictCount, int clientMax ) {}

void CBufferFix::GameFrame(bool simulating) {}
void CBufferFix::LevelShutdown(void) {}

void CBufferFix::ClientActive(edict_t *pEntity) {}

void CBufferFix::ClientDisconnect(edict_t *pEntity) {}

void CBufferFix::ClientPutInServer(edict_t *pEntity, char const *playername) {}

void CBufferFix::SetCommandClient(int index) {}

void CBufferFix::ClientSettingsChanged(edict_t *pEdict) {}

PLUGIN_RESULT CBufferFix::ClientConnect(bool *bAllowConnect, edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen) {
	return PLUGIN_CONTINUE;
}

PLUGIN_RESULT CBufferFix::ClientCommand(edict_t *pEntity) {
	return PLUGIN_CONTINUE;
}

PLUGIN_RESULT CBufferFix::NetworkIDValidated(const char *pszUserName, const char *pszNetworkID) {
	return PLUGIN_CONTINUE;
}