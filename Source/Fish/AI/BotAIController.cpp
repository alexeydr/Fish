#include "Fish/AI/BotAIController.h"
#include "Fish/AI/FishChar.h"
#include "Kismet/GameplayStatics.h"
#include "Fish/FishGameMode.h"
#include "Fish/Gameplay/Table.h"
#include "Navigation/PathFollowingComponent.h"

void ABotAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	
	switch (CurrentTask)
	{
	case ETasks::GoToExit:
		ControlledPawn->Destroy();
		break;
	case ETasks::GoToTable:
		MakeOrder();
		break;
	}
	Super::OnMoveCompleted(RequestID,Result);
}

void ABotAIController::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AFishGameMode>(UGameplayStatics::GetGameMode(this));
	OrderRecived = false;
	if (GameMode)
	{
		GameMode->OnBotSpawned.AddDynamic(this, &ABotAIController::OnBotSpawned);
	}
}

void ABotAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (GameMode)
	{
		GameMode->OnBotSpawned.RemoveAll(this);
	}

	Super::EndPlay(EndPlayReason);
}

void ABotAIController::OnBotSpawned(AFishChar* SpawnedBot)
{
	if (!ControlledPawn)
	{	
		ControlledPawn = SpawnedBot;
		GoToTable();
	}
}

void ABotAIController::GoToExit()
{
}

void ABotAIController::GoToTable()
{
	if (ATable* TargetTable = ATable::GetRandomTable())
	{
		if (AActor* Chair = TargetTable->GetEmptyChair())
		{			
			FAIMoveRequest MoveRequest;
			MoveRequest.SetGoalActor(Chair);
			MoveRequest.SetUsePathfinding(true);
			TargetTable->AddClient(ControlledPawn);
			CurrentTask = ETasks::GoToTable;
			MoveResult = MoveTo(MoveRequest);
		}
	}
}

void ABotAIController::MakeOrder()
{
	if (GameMode && GameMode->Menu && ControlledPawn)
	{
		float Time = 0.f;
		for (int i = 0; i < FMath::RandRange(1,3); i++)
		{
			const FDish& Dish =	GameMode->Menu->GetRandomDish();
			ControlledPawn->AddFoodInOrder(Dish);
			Time += Dish.CookingTime;
			FTimerHandle TimerHandle;
			GetWorldTimerManager().SetTimer(TimerHandle,this, &ABotAIController::ChangeMood, Time + 10.f, false);
		}
	}
}

void ABotAIController::ChangeMood()
{
	if (!OrderRecived && ControlledPawn)
	{
		ControlledPawn->Tips *= 0.5f;
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ABotAIController::ChangeMood, 10.f, false);
	}
}

