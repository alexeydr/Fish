#include "Fish/FishTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Fish/FishGameMode.h"
#include "Fish/Waiter.h"
#include "Fish/Gameplay/FoodSpawnTable.h"

AFishGameMode* UHelper::GetGameMode()
{
	UWorld* World = GEngine->GetWorldContexts()[0].World();
	if (World)
	{
		return Cast<AFishGameMode>(UGameplayStatics::GetGameMode(World));
	}
	return nullptr;
}

AFoodSpawnTable* UHelper::GetSpawnTable()
{
	UWorld* World = GEngine->GetWorldContexts()[0].World();
	if (World)
	{
		return Cast<AFoodSpawnTable>(UGameplayStatics::GetActorOfClass(World, AFoodSpawnTable::StaticClass()));
	}
	return nullptr;
}

AWaiter* UHelper::GetWaiterCharacter(UWorld* World)
{
	if (World)
	{
		return Cast<AWaiter>(UGameplayStatics::GetPlayerCharacter(World, 0));
	}
	return nullptr;
}
