#pragma once

#include "CoreMinimal.h"
#include "DataAsset/CDoAction.h"
#include "CDoAction_Melee.generated.h"

UCLASS()
class U05_ACTION_API ACDoAction_Melee : public ACDoAction
{
	GENERATED_BODY()

public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;
	
};
