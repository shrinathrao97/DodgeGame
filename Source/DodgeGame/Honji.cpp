// Fill out your copyright notice in the Description page of Project Settings.


#include "Honji.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/CapsuleComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneComponent.h"
#include "Math/Vector.h"

// Sets default values
AHonji::AHonji()
{
	
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//Setup the objects
	skeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletal Mesh");
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	collider = CreateDefaultSubobject<UCapsuleComponent>("Collider");
	springArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	pointLightSignal = CreateDefaultSubobject<UPointLightComponent>("Point Light");
	movement = CreateDefaultSubobject<UFloatingPawnMovement>("Character Move Pawn");

	//Rotate Collider to +X
	collider->AddLocalRotation(FRotator(0, 0, 0));

	//Setup the attachments
	SetRootComponent(collider);
	skeletalMesh->SetupAttachment(collider);
	springArm->SetupAttachment(collider);
	camera->SetupAttachment(springArm);
	pointLightSignal->SetupAttachment(skeletalMesh);
	
	//Do use the controller's Yaw
	bUseControllerRotationYaw = true;

	//Setup Camera to use controller's rotation
	camera->bUsePawnControlRotation = true;
	springArm->bUsePawnControlRotation = true;

	//Don't use controllers rotaions and roll etc..
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	
	//You can move!!!
	canMove = true;

	//Attacking Animation Vars
	attackComboCounter = 0;
	isAttacking = false;
	saveAttackCounter = false;
	resetAttackCounter = true;

	attackingForwardAmount = 1;

}



// Called when the game starts or when spawned
void AHonji::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHonji::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Be able to view character
	if (movement->Velocity.Size() == 0) {
	
		bUseControllerRotationYaw = false;
	
	}

	else {
	
		bUseControllerRotationYaw = true;
	}

}

// Called to bind functionality to input
void AHonji::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Axis Binding
	InputComponent->BindAxis("MoveForward", this, &AHonji::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AHonji::MoveRight);
	InputComponent->BindAxis("LookUp", this, &AHonji::LookUp);
	InputComponent->BindAxis("Turn", this, &AHonji::Turn); 

	//Action Binding
	InputComponent->BindAction("Attack", IE_Pressed, this, &AHonji::Attack);
	InputComponent->BindAction("Dodge", IE_Pressed, this, &AHonji::Dodge);
	InputComponent->BindAction("CastYellow", IE_Pressed, this, &AHonji::CastYellow);
	InputComponent->BindAction("CastRed", IE_Pressed, this, &AHonji::CastRed);
	InputComponent->BindAction("CastBlue", IE_Pressed, this, &AHonji::CastBlue);
}

//Move Left and Right
void AHonji::MoveRight(float amount)
{
	
	if (canMove) {
	
		movement->AddInputVector(GetActorRightVector() * amount * moveSpeedModifier);

	}


}

//Move Forwards and Backwards
void AHonji::MoveForward(float amount)
{
	if (canMove) {
		
		movement->AddInputVector(GetActorForwardVector() * amount * moveSpeedModifier);

	}
}

void AHonji::LookUp(float amount)
{
	AddControllerPitchInput(amount);
}

void AHonji::Turn(float amount)
{
	AddControllerYawInput(amount);
}

void AHonji::Attack()
{
	

	//If we're already attacking, and we haven't initiated a combo yet...
	if (isAttacking == true) {
	
		saveAttackCounter = true;
	}

	//Its our first hit! Let everyone know we're trying to hit something!

	else {
		canMove = false;

		isAttacking = true;
	}
	
}


void AHonji::Dodge()
{
	isDodging = true;
	moveSpeedModifier = 1.0f;
}

void AHonji::CastYellow()
{
}

void AHonji::CastRed()
{
}

void AHonji::CastBlue()
{
}

