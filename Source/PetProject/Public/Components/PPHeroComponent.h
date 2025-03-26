// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnhancedInputComponent.h"
#include "Utils/PPUtils.h"
#include "PPHeroComponent.generated.h"

class UPPAbilityInputConfig;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PETPROJECT_API UPPHeroComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPPHeroComponent();

	UFUNCTION(BlueprintPure)
	static UPPHeroComponent* GetHeroComponent(const AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void AddAdditionalInputConfig(UPPAbilityInputConfig* InputConfig);
	
	UFUNCTION(BlueprintCallable)
	void RemoveInputConfig(UPPAbilityInputConfig* InputConfig);

	void InitializePlayerInput(UInputComponent* PlayerInputComponent);

	void AbilityInputPressed(int32 InputID);
	void AbilityInputReleased(int32 InputID);

	UPROPERTY(EditDefaultsOnly)
	UPPAbilityInputConfig* InputConfig;

protected:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	TArray<FInputBindingHandle> BindAbilityAction(const FPPAbilityInput InInputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, UInputComponent* PlayerInputComponent);


	TMap<EPPAbilityInputID, TArray<FInputBindingHandle>> TemporaryBindings;
};
