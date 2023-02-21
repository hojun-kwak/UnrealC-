#include "CTargetComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

UCTargetComponent::UCTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CHelpers::GetAsset<UParticleSystem>(&Particle, "ParticleSystem'/Game/Effects/P_Enrage_Base.P_Enrage_Base'");

	

}


void UCTargetComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

// 누를떄마다 달라져야 하기 때문에 토글을 사용한다.
void UCTargetComponent::ToggleTarget()
{
	if (!!Target)
	{
		EndTargeting();

		return;
	}

	StartTargeting();
}

void UCTargetComponent::ChangeTargetLeft()
{
	ChangeTarget(false);
}

void UCTargetComponent::ChangeTargetRight()
{
	ChangeTarget(true);
}

void UCTargetComponent::StartTargeting()
{
	SetTraceTargets();
	SetTarget();
}

void UCTargetComponent::EndTargeting()
{
	Target = NULL;
	TraceTargets.Empty();

	if (!!Attached)
		Attached->DestroyComponent();
}

void UCTargetComponent::SetTraceTargets()
{
	FVector start = OwnerCharacter->GetActorLocation();
	FVector end = FVector(start.X, start.Y, start.Z + 1);

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(OwnerCharacter);

	TArray<FHitResult> hitResults;
	UKismetSystemLibrary::SphereTraceMultiByProfile(GetWorld(), start, end, TraceRadius, "Pawn", false, ignoreActors, Debug, hitResults, true, FLinearColor::Green, FLinearColor::Red, 1.0f);

	for (const FHitResult& result : hitResults)
	{
		if (result.GetActor()->GetClass() == OwnerCharacter->GetClass())
			continue;


		ACharacter* character = Cast<ACharacter>(result.GetActor());

		if (!!character)
			TraceTargets.AddUnique(character);
	}

	/*for (const ACharacter* character : TraceTargets)
	{
		CLog::Print(character->GetActorLabel());
	}*/
}

void UCTargetComponent::SetTarget()
{
	float angle = -2.0f;
	ACharacter* target = NULL;

	for (ACharacter* character : TraceTargets)
	{
		FVector direction = FQuat(OwnerCharacter->GetControlRotation()).GetForwardVector();
		FVector offset = character->GetActorLocation() - OwnerCharacter->GetActorLocation();
		offset = offset.GetSafeNormal(); // Normalize == safeNormal

		float temp = direction | offset; // | dot product
		if (temp < angle)
			continue;

		angle = temp;
		target = character;
	}

	//CLog::Print(target->GetActorLabel());

	ChangeCursor(target);

}

void UCTargetComponent::ChangeTarget(bool InRight)
{
	CheckNull(Target);

	TMap<float, ACharacter*> map;
	for (ACharacter* character : TraceTargets)
	{
		if (Target == character)
			continue;

		FVector targetLocation = character->GetActorLocation();
		FVector ownerLocation = OwnerCharacter->GetActorLocation();
		FVector ownerToTarget = targetLocation - ownerLocation; // 플레이어와 타겟된위치를 뺴서 음수나 양수에 따라 왼쪽 오른쪽을 정함

		FQuat quat = FQuat(OwnerCharacter->GetControlRotation()); // 전방 벡터
		FVector forward = quat.GetForwardVector();
		FVector up = quat.GetUpVector();

		FVector cross = forward ^ ownerToTarget;
		float dot = cross | up;

		map.Add(dot, character);
	}


	float minimum = FLT_MAX;
	ACharacter* target = NULL;

	TArray<float> keys;
	map.GetKeys(keys); // Keys -> 거리가 들어감
	for (float key : keys)
	{
		if (InRight == true)
		{
			if (key < 0.0f)
				continue;
		}
		else
		{
			if (key > 0.0f)
				continue;
		}

		if (FMath::Abs(key) > minimum)
			continue;

		minimum = FMath::Abs(key);
		target = *map.Find(key); // value가 반환된다
	}

	ChangeCursor(target);
}

void UCTargetComponent::ChangeCursor(ACharacter* InTarget)
{
	if (!!InTarget)
	{
		if (!!Attached)
			Attached->DestroyComponent();
		
		Attached = UGameplayStatics::SpawnEmitterAttached(Particle, InTarget->GetMesh(), "Spine_Target");
		Target = InTarget;

		return;
	}

	EndTargeting();
}

void UCTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckNull(Target);

	if (Target->GetDistanceTo(OwnerCharacter) >= TraceRadius)
	{
		EndTargeting();

		return;
	}

	FVector start = OwnerCharacter->GetActorLocation();
	FVector target = Target->GetActorLocation();

	FRotator rotator = UKismetMathLibrary::FindLookAtRotation(start, target);
	FRotator current = OwnerCharacter->GetControlRotation();

	rotator = UKismetMathLibrary::RInterpTo(current, rotator, DeltaTime, InteropSpeed); // 카메라 부드럽게 하기


	OwnerCharacter->GetController()->SetControlRotation(rotator);

}

