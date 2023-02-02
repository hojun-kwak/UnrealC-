#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CActionData.generated.h"

USTRUCT(BlueprintType)
struct FEquipmentData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
        class UAnimMontage* AnimMontage;

    UPROPERTY(EditAnywhere)
        float PlayRatio = 1.0f;

    UPROPERTY(EditAnywhere)
        FName StartSection;

    UPROPERTY(EditAnywhere)
        bool bCanMove = true;
};

USTRUCT(BlueprintType)
struct FDoActionData : public FEquipmentData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
        float Power = 5.0f;

    UPROPERTY(EditAnywhere)
        float HitStop;

    UPROPERTY(EditAnywhere)
        class UParticleSystem* Effect;

    UPROPERTY(EditAnywhere)
        FTransform EffectTransform;

    UPROPERTY(EditAnywhere)
        TSubclassOf<class UCameraShakeBase> ShakeClass;
};

UCLASS()
class U05_ACTION_API UCActionData : public UDataAsset
{
	GENERATED_BODY()

public:
    FORCEINLINE class ACEquipment* GetEquipment() { return Equipment; }
	
public:
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        TSubclassOf<class ACAttachment> AttachmentClass;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        TSubclassOf<class ACEquipment> EquipmentClass;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
        FEquipmentData EquipmentData;

public:
    void BeginPlay(class ACharacter* InOwnerCharacter);

private:
    class ACEquipment* Equipment;
    class ACAttachment* Attachment;

};
