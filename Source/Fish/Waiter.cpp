#include "Waiter.h"
#include "GameFramework/PlayerController.h"
#include "EngineUtils.h"
#include "Fish/Interfaces/InteractionInterface.h"
#include "Fish/AI/FishChar.h"

void AWaiter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (!PlayerInputComponent)
		return;

	PlayerInputComponent->BindKey(EKeys::RightMouseButton, IE_Pressed, this, &AWaiter::MainAction);
}

void AWaiter::MainAction()
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		FHitResult TraceHitResult;
		PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult); 		
		IInteractionInterface* Interface = Cast<IInteractionInterface>(TraceHitResult.Actor);
		if (Interface && FVector::Dist(GetActorLocation(), TraceHitResult.Actor->GetActorLocation()) <= 200.f)
		{
			Interface->MainAction(Type);
		}
	}
}

void AWaiter::SubmitOrder(TArray<FDish>& ClientOrderArr, AFishChar* Client)
{
	if (Client)
	{
		for (auto& Food: Dishes)
		{
			if (Client->CanTakeFood(Food))
			{
				ClientOrderArr.RemoveSingle(Food);
				RemoveDish(Food);
			}
		}
	}

}

void AWaiter::RemoveDish(const FDish& DishForRemove)
{
	Dishes.RemoveSingle(DishForRemove);
}
