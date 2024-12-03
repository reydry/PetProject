// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorators/PPBTDecorator_RandomLoop.h"
#include "Engine/World.h"
#include "BehaviorTree/BTCompositeNode.h"
#include "BehaviorTree/Composites/BTComposite_SimpleParallel.h"
#include "BehaviorTree/Decorators/BTDecorator_Loop.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(PPBTDecorator_RandomLoop)

UPPBTDecorator_RandomLoop::UPPBTDecorator_RandomLoop(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "RandomLoop";
	NumLoopsMin = 1;
	NumLoopsMax = 2;
	INIT_DECORATOR_NODE_NOTIFY_FLAGS();

	bAllowAbortNone = false;
	bAllowAbortLowerPri = false;
	bAllowAbortChildNodes = false;
}

void UPPBTDecorator_RandomLoop::OnNodeActivation(FBehaviorTreeSearchData& SearchData)
{
	FBTLoopDecoratorMemory* DecoratorMemory = GetNodeMemory<FBTLoopDecoratorMemory>(SearchData);
	FBTCompositeMemory* ParentMemory = GetParentNode()->GetNodeMemory<FBTCompositeMemory>(SearchData);
	const bool bIsSpecialNode = GetParentNode()->IsA(UBTComposite_SimpleParallel::StaticClass());

	if ((bIsSpecialNode && ParentMemory->CurrentChild == BTSpecialChild::NotInitialized) ||
		(!bIsSpecialNode && ParentMemory->CurrentChild != ChildIndex))
	{
		int32 NumLoops = FMath::RandRange(NumLoopsMin, NumLoopsMax);
		DecoratorMemory->RemainingExecutions = IntCastChecked<uint8>(NumLoops);
		DecoratorMemory->TimeStarted = GetWorld()->GetTimeSeconds();
	}

	bool bShouldLoop = false;

	if (DecoratorMemory->RemainingExecutions > 0)
	{
		DecoratorMemory->RemainingExecutions--;
	}

	bShouldLoop = DecoratorMemory->RemainingExecutions > 0;

	if (bShouldLoop)
	{
		GetParentNode()->SetChildOverride(SearchData, ChildIndex);
	}
}

FString UPPBTDecorator_RandomLoop::GetStaticDescription() const
{
	return FString::Printf(TEXT("%s: %d-%d loops"), *Super::GetStaticDescription(), NumLoopsMin, NumLoopsMax);
}

void UPPBTDecorator_RandomLoop::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);

	FBTLoopDecoratorMemory* DecoratorMemory = (FBTLoopDecoratorMemory*)NodeMemory;
	Values.Add(FString::Printf(TEXT("loops remainig: %d"), DecoratorMemory->RemainingExecutions));
}

uint16 UPPBTDecorator_RandomLoop::GetInstanceMemorySize() const
{
	return sizeof(FBTLoopDecoratorMemory);
}

void UPPBTDecorator_RandomLoop::InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const
{
	InitializeNodeMemory<FBTLoopDecoratorMemory>(NodeMemory, InitType);
}

void UPPBTDecorator_RandomLoop::CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const
{
	CleanupNodeMemory<FBTLoopDecoratorMemory>(NodeMemory, CleanupType);
}

#if WITH_EDITOR

FName UPPBTDecorator_RandomLoop::GetNodeIconName() const
{
	return FName("BTEditor.Graph.BTNode.Decorator.Loop.Icon");
}

#endif