#include "FishGameMode.h"
#include "FishPlayerController.h"
#include "FishCharacter.h"
#include "Engine/World.h"
#include "Fish/AI/FishChar.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "UObject/ConstructorHelpers.h"

AFishGameMode::AFishGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AFishPlayerController::StaticClass();

}

void AFishGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFishGameMode::StartSpawnBot, 2.f, true);
}

AFishChar* AFishGameMode::SpawnBot()
{
	AActor* SpawnPoint = UGameplayStatics::GetActorOfClass(this, APlayerStart::StaticClass());
	if (SpawnPoint)
	{
		return GetWorld()->SpawnActor<AFishChar>(BotClass, SpawnPoint->GetActorLocation(), SpawnPoint->GetActorRotation(), FActorSpawnParameters());
	}
	
	return nullptr;
}

void AFishGameMode::StartSpawnBot()
{
	AFishChar* SpawnedBot = SpawnBot();
	if (OnBotSpawned.IsBound())
	{
		OnBotSpawned.Broadcast(SpawnedBot);
	}
}
