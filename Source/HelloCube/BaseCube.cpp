// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCube.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/PrimitiveComponent.h"


// Sets default values
ABaseCube::ABaseCube()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize the Static Mesh Component and make moveable
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	RootComponent = CubeMesh;
	CubeMesh->SetSimulatePhysics(true);

	//Setting the Spring Arm and attach it to the RootComponent
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	
	//Setting The Camera and Attach it to The SpringArm
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	//Set Default Values
	Speed = 600.f;
	TurnRate = 100.f;
	JumpForce = 400.f;

}

// Called when the game starts or when spawned
void ABaseCube::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABaseCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Shows Messages to The screen
	GEngine->AddOnScreenDebugMessage(-1, -1.f, FColor::Blue,
		FString::Printf(TEXT("Hello Cube Project\nPress W,A,S, And D for Movement,\n And Q, And E for Drift Movement,\n And The Spacebar to Jump,\nor Double Jump to Fly")));
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green, FString::Printf(TEXT("Player Location is %s"), *GetActorLocation().ToString()));

}

// Called to bind functionality to input
void ABaseCube::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Sets the Move Function to MoveForward Input
	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCube::Move);
	//Sets the Turn Function to The Turn Input
	PlayerInputComponent->BindAxis("Turn", this, &ABaseCube::Turn);
	//Sets the Drift Function to The Drift Input
	PlayerInputComponent->BindAxis("Drift", this, &ABaseCube::Drift);
	//Sets the Jump function to The Jump Input
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABaseCube::Jump);
}

//Defining The Move Function
void ABaseCube::Move(float Value)
{
	//Checks if Value is 0 the it does Nothing
	if (Value != 0.0f)
	{
		//Stores The Current Forward Vector of The Actor to NewLocation Vector
		FVector NewLocation = GetActorForwardVector();

		//Changing the Cube World Offset by Multiplying the Value and Speed and The Current Location
		CubeMesh->AddWorldOffset(NewLocation * Value * Speed * GetWorld()->GetDeltaSeconds());
	}
	return;
}

//Defining The Turning Function
void ABaseCube::Turn(float Value)
{
	//Stores The Current Actor Rotation to Rotation Rotator
	FRotator Rotation = GetActorRotation();

	//Adds The Rotation Yaw To the Value and  Multiplies it to The TurnRate
	Rotation.Yaw += Value*GetWorld()->GetDeltaSeconds()*TurnRate;

	//Rotates the Actor
	SetActorRotation(Rotation);
}

//Defining the Drift Function
void ABaseCube::Drift(float Value)
{
	//Stores The Actor RightVector to Drift Vector
	FVector Drift = GetActorRightVector();
	//Moves The Actor by an Offset of Speed and The Value
	AddActorWorldOffset(Drift * Value * Speed * GetWorld()->GetDeltaSeconds());
}

//Defining the Jump Function
void ABaseCube::Jump()
{
	//Stores The JumpForce to Z Axis in Jump Vector
	FVector Jump = FVector(0.f, 0.f, JumpForce);

	//Checks if CubeMesh is Not Null and is Simulating Physics
	if(CubeMesh&&CubeMesh->IsSimulatingPhysics())

	//Does the Impulse to The CubeMesh
	CubeMesh->AddImpulse(Jump, NAME_None, true);
}