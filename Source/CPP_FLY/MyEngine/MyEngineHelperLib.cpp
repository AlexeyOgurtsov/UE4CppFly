#include "MyEngineHelperLib.h"
#include "IGlobSingletonInterface.h"
#include "Engine.h"

TScriptInterface<IGlobSingletonInterface> UGlobSingletonHelperLib::Get()
{
	return TScriptInterface<IGlobSingletonInterface>(GEngine->GameSingleton);
}