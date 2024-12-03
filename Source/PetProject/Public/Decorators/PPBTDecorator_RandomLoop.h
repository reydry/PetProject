// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "BehaviorTree/BTDecorator.h"
#include "PPBTDecorator_RandomLoop.generated.h"

UCLASS()
class PETPROJECT_API UPPBTDecorator_RandomLoop : public UBTDecorator
{
	GENERATED_UCLASS_BODY()
	
	UPROPERTY(Category = Decorator, EditAnywhere, meta = (ClampMin = "1", ClampMax = "255"))
	int32 NumLoopsMin;
	
	UPROPERTY(Category = Decorator, EditAnywhere, meta = (ClampMin = "1", ClampMax = "255"))
	int32 NumLoopsMax;
	
	virtual uint16 GetInstanceMemorySize() const override;
	virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;
	virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
	virtual FString GetStaticDescription() const override;

#if WITH_EDITOR
	virtual FName GetNodeIconName() const override;
#endif

protected:
	virtual void OnNodeActivation(FBehaviorTreeSearchData& SearchData) override;
};
