// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseCube.generated.h"

UCLASS()
class HELLOCUBE_API ABaseCube : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	//The Cube Mesh and be the rootcomp
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* CubeMesh;

	

	//SpringArm With Forward Decleration
	UPROPERTY(EditDefaultsOnly)
	class USpringArmComponent *SpringArm;

	//Camera with Forward Decleration
	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* Camera;

	
	//How Fast The Cube is Variable and can be edited from the blueprints and editor

	UPROPERTY(EditAnywhere,Category="Movement")
	float Speed;

	//How Powrfull The TurnRat is Variable and can be edited from the blueprints and editor

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate;

	//How Powrfull The Jump is Variable and can be edited from the blueprints and editor
	UPROPERTY(EditAnywhere, Category = "Movement")
	float JumpForce;
public:

	//Moving Forward/Backward Function 
	void Move(float Value);
	
	//Rotating Left/Right Function
	void Turn(float Value);

	//Drift Movement Function
	void Drift(float Value);

	//Jump Function
	void Jump();
};
