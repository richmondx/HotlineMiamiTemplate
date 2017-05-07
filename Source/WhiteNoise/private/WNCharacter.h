// Copyright 2016 Carsten Zarbock / Rebound-Software
#pragma once
#include "GameFramework/Character.h"
#include "Engine.h" //todo: Change to IWYU System
#include "Weapon.h"
#include "NPC.h"
#include "WhiteNoiseCharacter.generated.h"

UCLASS(Blueprintable)
class AWhiteNoiseCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	/* Actor Components */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* WeaponThrowArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* WeaponGripPoint;

	/* Inventory */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float WeaponPickupDistance = 500.0f;
	AWeapon* CurrentWeapon;
	bool bIsFiring;

	/* Movement & Camera */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MaxFreeCamDistance = 2000.0f;
	bool bIsCameraFreeMovement;
	ETargetAnimation CurrentAnimation;
	FRotator UpperBodyRotation;

	/* Actions */
	ANPC* LockedEnemy;

public:
	AWhiteNoiseCharacter();

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/* Animation */
	UFUNCTION(BlueprintCallable, Category = "Animations")
		ETargetAnimation GetCurrentAnimation() const;

	UFUNCTION(BlueprintCallable, Category = "Animations")
		FRotator GetUpperBodyRotation() const;

	/* Movement & Camera */
	void HandleMovement(FVector worldDirection, float fRate);
	void HandleRotation(FVector worldPosition);
	void CameraFreeMove(FVector worldDirection, float fRate);
	void ResetFreeCam();
	FVector GetMouseCursorPosition() const;

	/* Inventory */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		AWeapon* GetCurrentWeapon() const;

	void Input_Pickup();
	bool WeaponPickup(AWeapon* weaponActor);
	void WeaponThrow();
	void WeaponDrop();
	void WeaponFire();
	void WeaponFire_Stop();
	void WeaponFire_Execute();

	/* Actions */
	UFUNCTION(BlueprintCallable, Category = "Actions")
	ANPC* GetLockedEnemy() const;

	void LockEnemy(ANPC* enemyActor);
	void HandleEnemyLock();

	/* */
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
