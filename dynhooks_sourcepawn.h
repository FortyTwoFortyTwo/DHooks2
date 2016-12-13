#ifndef _INCLUDE_DYNHOOKS_SP_H_
#define _INCLUDE_DYNHOOKS_SP_H_

#include "manager.h"
#include "vhook.h"
#include <am-vector.h>
#include <am-hashmap.h>

class CDynamicHooksSourcePawn;
typedef ke::HashMap<IPluginFunction *, CDynamicHooksSourcePawn *, ke::PointerPolicy<IPluginFunction>> CallbackMap;
typedef ke::Vector<CDynamicHooksSourcePawn *> PluginCallbackList;
typedef ke::HashMap<CHook *, PluginCallbackList *, ke::PointerPolicy<CHook>> DetourMap;

//extern ke::Vector<CHook *> g_pDetours;
// Keep a list of plugin callback -> Hook wrapper for easily removing plugin hooks
//extern CallbackMap g_pPluginPreDetours;
//extern CallbackMap g_pPluginPostDetours;
// Keep a list of hook -> callbacks for calling in the detour handler
extern DetourMap g_pPreDetours;
extern DetourMap g_pPostDetours;

class CDynamicHooksSourcePawn : public DHooksInfo {
public:
	CDynamicHooksSourcePawn(HookSetup *setup, CHook *pDetour, IPluginFunction *pCallback, bool post);

	HookReturnStruct *GetReturnStruct();
	HookParamsStruct *CDynamicHooksSourcePawn::GetParamStruct();
	void UpdateParamsFromStruct(HookParamsStruct *params);

public:
	CHook *m_pDetour;
	CallingConvention callConv;
};

ICallingConvention *ConstructCallingConvention(HookSetup *setup);
bool HandleDetour(HookType_t hookType, CHook* pDetour);
bool AddDetourPluginHook(HookType_t hookType, CHook *pDetour, HookSetup *setup, IPluginFunction *pCallback);
bool RemoveDetourPluginHook(HookType_t hookType, CHook *pDetour, IPluginFunction *pCallback);
void RemoveAllCallbacksForContext(IPluginContext *pContext);
void CleanupDetours();

#endif