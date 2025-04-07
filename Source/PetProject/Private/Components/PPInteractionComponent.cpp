// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/PPInteractionComponent.h"
#include "Components/PPHeroComponent.h"
#include "PPInteractionInterface.h"

UPPInteractionComponent::UPPInteractionComponent()
{

}

TArray<AActor*> UPPInteractionComponent::GetObjectsArray()
{
	return ObjectsArray;
}

void UPPInteractionComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UPPHeroComponent* HeroComponent = UPPHeroComponent::GetHeroComponent(GetOwner());

	if (OtherActor && HeroComponent)
	{
		if (OtherActor->Implements<UPPInteractionInterface>())
		{
			HeroComponent->AddAdditionalInputConfig(InputConfig);
			ObjectsArray.Add(OtherActor);
		}
	}
}

void UPPInteractionComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UPPHeroComponent* HeroComponent = UPPHeroComponent::GetHeroComponent(GetOwner());

	if (OtherActor && HeroComponent)
	{
		if (OtherActor->Implements<UPPInteractionInterface>())
		{
			HeroComponent->RemoveInputConfig(InputConfig);
			ObjectsArray.Remove(OtherActor);
		}
	}
}

UPPInteractionComponent* UPPInteractionComponent::GetInteractionComponentFromActor(AActor* InActor)
{
	return InActor ? InActor->FindComponentByClass<UPPInteractionComponent>() : nullptr;
}
