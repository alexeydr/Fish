#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FishGameMode.generated.h"

class AFishChar;
class UFoodDA;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBotSpawned, AFishChar*, SpawnedBot);

UCLASS(minimalapi)
class AFishGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFishGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	UPROPERTY(Transient);
	FOnBotSpawned OnBotSpawned;
	
	void StartSpawnBot();
	
	UPROPERTY(EditAnywhere);
	UFoodDA* Menu;

private:
	
	AFishChar* SpawnBot();

protected:

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFishChar> BotClass;


};



