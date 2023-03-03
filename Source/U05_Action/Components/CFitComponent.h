#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CFitComponent.generated.h"

USTRUCT(BlueprintType)
struct FFitData
{
	GENERATED_BODY()

public:
	// mesh�� ���带 �������� �����ֱ⶧����
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector LeftDistance; //X�ุ ���

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector RightDistance; //X�ุ ���

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector PelvisDistance; //Z�ุ ���

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FRotator LeftRotation;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FRotator RightRotation;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class U05_ACTION_API UCFitComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InverseKinemetics")
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType = EDrawDebugTrace::None;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InverseKinemetics")
		FName LeftSocket = "Foot_L";

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InverseKinemetics")
		FName RightSocket = "Foot_R";

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InverseKinemetics")
		float TraceDistance = 55;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InverseKinemetics")
		float InterpSpeed = 17;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InverseKinemetics")
		float OffsetDistance = 5;

public:
	FORCEINLINE const FFitData& GetData() { return Data; }
		

public:	
	UCFitComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Trace(FName InSocket, float& OutDistance, FRotator& OutRotator);

private:
	class ACharacter* OwnerCharacter;

	FFitData Data;
		
};
