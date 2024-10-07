// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/PPAttributeSet.h"

UPPAttributeSet::UPPAttributeSet()
{
}

UWorld* UPPAttributeSet::GetWorld() const
{
	const UObject* Outer = GetOuter();
	
	if (!IsValid(Outer))
	{
		return nullptr;
	}

	return Outer->GetWorld();
}
