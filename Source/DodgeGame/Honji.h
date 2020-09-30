// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Honji.generated.h"

UCLASS()
class DODGEGAME_API AHonji : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHonji();
	void MoveRight(float amount);
	void MoveForward(float amount);
	void LookUp(float amount);
	void Turn(float amount);
	void Attack();
	void Dodge();
	void CastYellow();
	void CastRed();
	void CastBlue();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		bool isAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool saveAttackCounter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool resetAttackCounter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		bool isDodging;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		bool isCasting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		bool canCast;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		int attackComboCounter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		float attackingForwardAmount;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Visuals")
		class USkeletalMeshComponent* skeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
		class UCameraComponent* camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
		class UCapsuleComponent* collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
		class USpringArmComponent* springArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		class UFloatingPawnMovement* movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
		class UPointLightComponent* pointLightSignal;


	//Vars
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool canMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		float moveSpeedModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool perfectDodge;

};
