#include "Fish/Gameplay/Table.h"
#include "Components/ChildActorComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATable::ATable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATable::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> AllChildActors;
	GetAllChildActors(AllChildActors,false);
	MaxSeats = AllChildActors.Num();
}

// Called every frame
void ATable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AActor* ATable::GetEmptyChair()
{
	TArray<AActor*> AllChildActors;
	GetAllChildActors(AllChildActors,false);
	if (AllChildActors.Num() > Clients.Num())
	{
		return AllChildActors[Clients.Num()];
	}
	return nullptr;
}

ATable* ATable::GetRandomTable()
{
	TArray<APlayerController*> AllControllers;
	GEngine->GetAllLocalPlayerControllers(AllControllers);
	if (AllControllers.Num() > 0)
	{
		TArray<AActor*> AllTables;
		UGameplayStatics::GetAllActorsOfClass(AllControllers[0], ATable::StaticClass(), AllTables);

		auto FiltredArray = AllTables.FilterByPredicate([](AActor* Act) {
			ATable* Table = Cast<ATable>(Act);
			return Table && Table->Clients.Num() < Table->MaxSeats;			
			});

		if (FiltredArray.Num() > 0)
		{
			return Cast<ATable>(FiltredArray[FMath::RandRange(0, FiltredArray.Num() - 1)]);
		}
	}

	return nullptr;
}

