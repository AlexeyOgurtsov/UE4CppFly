#include "SaveLoadLib.h"
#include "MySaveGame.h"
#include "MySys/HelperLib.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"

namespace
{
	/**
	* Helper utils for implementation.
	*/
	class FImpl
	{
	public:
		/**
		* Class used for the USaveGame object;
		*/
		static UClass* const SAVEGAME_CLASS; 

		/**
		* Returns current user name for the SaveLoad system
		*/
		static FString GetUserName()
		{
			return FString(TEXT("DEFAULT_USER"));
		}

		/**
		* QuickSave slot Id
		*/
		static constexpr int32 QUICKSAVE_SLOT = 0;
	};
	UClass* const FImpl::SAVEGAME_CLASS = UMySaveGame::StaticClass(); 
} // anonymous

void USaveLoadLib::QuickSave()
{
	UE_LOG(MyLog, Log, TEXT("USaveLoadLib::QuickSave..."));
	UE_LOG(MyLog, Error, TEXT("NotYetImpl"));
	UE_LOG(MyLog, Log, TEXT("USaveLoadLib::QuickSave DONE"));
}

void USaveLoadLib::QuickLoad()
{
	UE_LOG(MyLog, Log, TEXT("USaveLoadLib::QuickLoad..."));
	UE_LOG(MyLog, Error, TEXT("NotYetImpl"));
	UE_LOG(MyLog, Log, TEXT("USaveLoadLib::QuickLoad DONE"));
}