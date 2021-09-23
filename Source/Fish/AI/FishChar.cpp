#include "Fish/AI/FishChar.h"
#include "Fish/AI/BotAIController.h"
#include "Fish/FishTypes.h"
#include "Fish/Waiter.h"
#include "Fish/UI/BotOrderWidget.h"
#include "Components/WidgetComponent.h"

// Sets default values
AFishChar::AFishChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Widget");
	WidgetComponent->SetupAttachment(GetMesh());
}

// Called when the game starts or when spawned
void AFishChar::BeginPlay()
{
	Super::BeginPlay();
	AiController = Cast<ABotAIController>(GetController());
	if (WidgetComponent)
		WidgetRef = Cast<UBotOrderWidget>(WidgetComponent->GetUserWidgetObject());
}

void AFishChar::WaiterMainAction()
{
	AWaiter* Waiter = UHelper::GetWaiterCharacter(GetWorld());
	WaiterTakeOrder(Waiter);
	Waiter->SubmitOrder(Order, this);
	UpdateOrderWidget();
}

void AFishChar::WaiterTakeOrder(AWaiter* InWaiter)
{
	if (InWaiter)
	{
		for (int i = 0; i < UnacceptedOrder.Num(); i++)
		{
			if (InWaiter->AddOrder(UnacceptedOrder[i]))
			{
				UnacceptedOrder.RemoveAt(i);
			}
		}
	}
}

bool AFishChar::CanTakeFood(const FDish& InFood)
{
	auto CopyOrder = Order;
	for (int i = 0; i < UnacceptedOrder.Num(); i++)
	{
		CopyOrder.RemoveAt(i);
	}
	return CopyOrder.Contains(InFood);
}

void AFishChar::UpdateOrderWidget()
{
	if (WidgetRef)
	{
		WidgetRef->ClearFoodContainer();
		for (auto& Dish: Order)
		{			
			WidgetRef->AddDishImage(Dish);
		}
	}
}

void AFishChar::AddFoodInOrder(const FDish& Dish)
{
	UnacceptedOrder.Add(Dish);
	Order.Add(Dish);
	Tips += Dish.Cost * 0.30;
}

void AFishChar::MainAction(ECharacterTypes Type)
{
	switch (Type)
	{
	case ECharacterTypes::Waiter:
		WaiterMainAction();
		break;
	}
}

// Called every frame
void AFishChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFishChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

