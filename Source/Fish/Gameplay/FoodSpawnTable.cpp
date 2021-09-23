#include "Fish/Gameplay/FoodSpawnTable.h"
#include "Fish/FishTypes.h"
#include "Fish/Waiter.h"
#include "BaseFood.h"

// Sets default values
AFoodSpawnTable::AFoodSpawnTable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFoodSpawnTable::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFoodSpawnTable::SpawnFood(const FDish& DishForSpawn)
{	
	
	int CurrentNumber = Queue.Find(DishForSpawn);
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FVector SpawnLocation = FVector(GetActorLocation().X + 100.f * CurrentNumber, GetActorLocation().Y, GetActorLocation().Z + 100.f);
	ABaseFood* SpawnedFood = GetWorld()->SpawnActor<ABaseFood>(DishForSpawn.ActForSpawn, SpawnLocation, FRotator(), SpawnParams);
	if (SpawnedFood)
	{
		SpawnedFood->CurrentDish = DishForSpawn;
	}
	if (Queue.Num() - 1 < CurrentNumber)
	{
		FTimerDelegate TD;
		FTimerHandle TH;
		const FDish& NextDish = Queue[CurrentNumber + 1];
		TD.BindUFunction(this, FName("SpawnFood"), NextDish);
		GetWorldTimerManager().SetTimer(TH, TD, NextDish.CookingTime, false);
	}
	else
	{
		bIsSpawnStarted = false;
	}
	Queue.Remove(DishForSpawn);
	
}

void AFoodSpawnTable::StartParseQueue()
{
	if (Queue.Num() > 0 && !bIsSpawnStarted)
	{
		bIsSpawnStarted = true;
		FTimerDelegate TD;
		FTimerHandle TH;
		const FDish& DishForSpawn = Queue[0];
		TD.BindUFunction(this, FName("SpawnFood"),DishForSpawn);
		GetWorldTimerManager().SetTimer(TH, TD, DishForSpawn.CookingTime, false);

	}
}

void AFoodSpawnTable::OnWaiterInteraction()
{
	AWaiter* Waiter = UHelper::GetWaiterCharacter(GetWorld());
	if (Waiter)
	{				
		Queue.Append(Waiter->GetCurrentOrder());
		StartParseQueue();
	}
}

// Called every frame
void AFoodSpawnTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFoodSpawnTable::MainAction(ECharacterTypes Type)
{
	switch (Type)
	{
		case ECharacterTypes::Waiter:
			OnWaiterInteraction();
			break;

	}
}

