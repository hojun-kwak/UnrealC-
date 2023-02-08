#include "CAnimNotifyState_ComboEnable.h"
#include "Global.h"
#include "DataAsset/CEquipment.h"
#include "DataAsset/CDoAction_Melee.h"
#include "Components/CActionComponent.h"

FString UCAnimNotifyState_ComboEnable::GetNotifyName_Implementation() const
{
	return "EnableCombo";
}

void UCAnimNotifyState_ComboEnable::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* action = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(action);

	ACDoAction_Melee* melee = Cast<ACDoAction_Melee>(action->GetCurrent()->GetDoAction());
	CheckNull(melee);

	melee->EnableCombo();
}

void UCAnimNotifyState_ComboEnable::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* action = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(action);

	ACDoAction_Melee* melee = Cast<ACDoAction_Melee>(action->GetCurrent()->GetDoAction());
	CheckNull(melee);

	melee->DisableCombo();
}


