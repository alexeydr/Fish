#include "Fish/Gameplay/BaseFood.h"
#include "Fish/Waiter.h"
#include "Fish/FishTypes.h"

// Sets default values
ABaseFood::ABaseFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseFood::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseFood::WaiterAction()
{
	AWaiter* Char =  UHelper::GetWaiterCharacter(GetWorld());
	if (Char && Char->AddDish(CurrentDish))
	{
		Destroy();
	}
}

// Called every frame
void ABaseFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseFood::MainAction(ECharacterTypes Type)
{
	switch (Type)
	{
		case ECharacterTypes::Waiter:
			WaiterAction();
			break;
	}
}

