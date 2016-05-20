// Fill out your copyright notice in the Description page of Project Settings.

#include "PROJECTGAME.h"
#include "Trap_TripWire.h"


ATrap_TripWire::ATrap_TripWire(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

	//Asset, Reference Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshOb(TEXT("StaticMesh'/Game/ModelsAndTextures/Meshes/TripWire/TentPegTrap.TentPegTrap'"));
	StaticMesh = StaticMeshOb.Object;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshObj(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	CubeMesh = CubeMeshObj.Object; 

	static ConstructorHelpers::FObjectFinder<UMaterial> BuildableObj(TEXT("Material'/Game/ModelsAndTextures/Materials/Buildable.Buildable'"));
	BuildableMat = BuildableObj.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> NotBuildableObj(TEXT("Material'/Game/ModelsAndTextures/Materials/NON-Buildable.NON-Buildable'"));
	NotBuildableMat = NotBuildableObj.Object;

    static ConstructorHelpers::FObjectFinder<UMaterial> Material_Invis(TEXT("Material'/Game/ModelsAndTextures/Materials/Transparent.Transparent'"));
	CubeMaterial = Material_Invis.Object;	

	//Create
	StaticMeshComp = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("StaticMeshYay"));
	CubeMeshComp = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("CubeStaticMesh"));

	//Set Mesh
	StaticMeshComp->SetStaticMesh(StaticMesh);
	CubeMeshComp->SetStaticMesh(CubeMesh);

	//Setup
	SetupTrap(StaticMeshComp);
	SetupCube(CubeMeshComp);

    
	//Deferred Attachment
	//StaticMeshComponent->AttachParent = Mesh;
	//StaticMeshComp->AttachParent = StaticMeshComponent;	
	CubeMeshComp->AttachParent = RootComponent;
	StaticMeshComp->AttachParent = RootComponent;

	//CubeMeshComp->AttachTo(StaticMeshComp);

  // set up a notification for when this component overlaps something  
    CubeMeshComp->OnComponentBeginOverlap.AddDynamic(this, &ATrap_TripWire::OnActorBeginOverlap);  
	CubeMeshComp->OnComponentEndOverlap.AddDynamic(this, &ATrap_TripWire::OnActorEndOverlap); 


  myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
 
}

// Called when the game starts or when spawned
void ATrap_TripWire::BeginPlay()
{
	Super::BeginPlay();
	//StaticMeshComp->AttachParent = StaticMeshComponent;	

	//CubeMeshComp->AttachTo(StaticMeshComp);

	StaticMeshComp->SetMaterial(0, BuildableMat);
	InConstruction = true;
}

void ATrap_TripWire::OnActorBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{ 
	if(InConstruction)
	{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("U HIT"));
	//StaticMeshComp->SetMaterial(0, NotBuildableMat);
	}
}

void ATrap_TripWire::OnActorEndOverlap(class AActor * OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(InConstruction)
	{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("U left"));
	//StaticMeshComp->SetMaterial(0, BuildableMat);
	}
}



