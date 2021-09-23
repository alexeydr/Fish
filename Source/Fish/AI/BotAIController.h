#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BotAIController.generated.h"

class AFishChar;
class AFishGameMode;

UENUM()
enum class ETasks : uint8 
{
	None,
    GoToTable,
	MakeOrder,
	GoToExit
};

UCLASS()
class FISH_API ABotAIController : public AAIController
{
	GENERATED_BODY()

private:
	
	UPROPERTY(Transient)
	AFishChar* ControlledPawn;

	UPROPERTY(Transient)
	AFishGameMode* GameMode;

	UPROPERTY(Transient)
	uint8 OrderRecived : 1;

	FPathFollowingRequestResult MoveResult;

protected:

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void OnBotSpawned(AFishChar* SpawnedBot);

	UPROPERTY(Transient)
	ETasks CurrentTask;

public:

	void GoToExit();

	void GoToTable();

	void MakeOrder();

	UFUNCTION()
	void ChangeMood();
	
};
