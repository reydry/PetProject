// Fill out your copyright notice in the Description page of Project Settings.

#include "Utils/PPUtils.h"
#include "Kismet/KismetMathLibrary.h"

FVector UPPUtils::CalculateEndLine(const APlayerController* InController)
{
    if (!IsValid(InController))
    {
        return FVector();
    }

    APawn* Pawn = InController->GetPawn();

    if (!IsValid(Pawn))
    {
        return FVector();
    }

    FVector NewVector;
    FVector ActorLocation = Pawn->GetActorLocation();
    FVector CursorLocation = GetLocationUnderCursor(InController);
    FVector CameraLocation = GetCameraLocation(InController);

    float Alpha = (ActorLocation.Z - CursorLocation.Z) / (CameraLocation.Z - CursorLocation.Z);

    NewVector.X = FMath::Lerp(CursorLocation.X, CameraLocation.X, Alpha);
    NewVector.Y = FMath::Lerp(CursorLocation.Y, CameraLocation.Y, Alpha);
    NewVector.Z = ActorLocation.Z;

    NewVector = UKismetMathLibrary::FindLookAtRotation(ActorLocation, NewVector).Vector();

    return NewVector;
}

FVector UPPUtils::GetLocationUnderCursor(const APlayerController* InController)
{
    if (!IsValid(InController))
    {
        return FVector();
    }

    FHitResult HitResult;
    InController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, HitResult);

    return HitResult.ImpactPoint;
}

FVector UPPUtils::GetCameraLocation(const APlayerController* InController)
{
    if (!IsValid(InController))
    {
        return FVector();
    }

    APlayerCameraManager* CameraManager = InController->PlayerCameraManager.Get();

    if (IsValid(CameraManager))
    {
        return CameraManager->GetCameraLocation();
    }


    return FVector();
}
