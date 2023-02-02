#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAttachment.generated.h"

UCLASS()
class U05_ACTION_API ACAttachment : public AActor
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
		void AttachTo(FName InSocketName);
	
public:	
	ACAttachment();

public:
	UFUNCTION(BlueprintImplementableEvent)
		void OnEquip();

	UFUNCTION(BlueprintImplementableEvent)
		void OnUnequip();

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* State;

	UPROPERTY(BlueprintReadOnly)
		class UCStatusComponent* Status;

protected:
	virtual void BeginPlay() override;

};
