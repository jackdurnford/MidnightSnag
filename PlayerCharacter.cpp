/**
Game assets - Assignment 2
PlayerCharacter.cpp
Purpose: The purpose of this class, is to create all of the input functions, for movement and for "use". Additionally, the 
raycasting is handled within this class. Ray casts are sent out of the player to detect nearby actors. The class communicates 
with the character blueprint, which handles the pickup/drop functions once an actor has been successfully targetted.

@author Jack Durnford
@version 2.0
*/

/* Class Includes */
#include "PROJECTGAME.h"
#include "FridgeFunctionLibrary.h"
#include "Timer.h"
#include "PlayerCharacter.h"
#include "BotCharacter.h"
#include "InventoryItem.h"
#include "Level_BlueprintFunctionLibrary.h"
#include "Sign.h"
#include "UsableActor.h"

APlayerCharacter::APlayerCharacter(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true; // Allow this actor to tick each frame. 
	
	//static ConstructorHelpers::FObjectFinder<UDataTable> RecipeDataTable(TEXT("DataTable'/Game/Blueprints/DataTables/CraftingRecipes.CraftingRecipes'"));
	//CraftingRecipes = RecipeDataTable.Object;

	MeshHolder = PCIP.CreateAbstractDefaultSubobject<USkeletalMeshComponent>(this, TEXT("Block"));



	//this->OnActorHit.AddDynamic(this, &APlayerCharacter::OnHit);
	//this->OnActorBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlap);
	//IDirector = PCIP.CreateDefaultSubobject<ULevel_BlueprintFunctionLibrary>(this, TEXT("AIDirectorComp"));
	OnActorBeginOverlap.AddDynamic(this, &APlayerCharacter::OnStartOverlap);
	OnActorEndOverlap.AddDynamic(this, &APlayerCharacter::OnEndOverlap);

	//if(AIDirector)
	//{
	//	AIDirector->ChildActorClass = ULevel_BlueprintFunctionLibrary::StaticClass();
	//	AIDirector->CreateChildActor();
	//	AIDirector->RegisterComponent();
	//}

	AIDirector = CreateDefaultSubobject<ULevel_BlueprintFunctionLibrary>(TEXT("AIDirectorComp"));
}

/**
* Called when the game starts or when spawned
* If the movement controller exists on the player, the default walk speed is placed into a new variable.
*
* @param N/A.
* @return N/A.
*/
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	AlterMouse(false);
	
	MaxUseDist = 800;
	bNewFocus = true;

	/* Set */
	SpeedBoostActive = false;

	TrapInConstruction = false;

	if (GetCharacterMovement()) 
	{
		OriginalWalkSpeed = GetCharacterMovement()->MaxWalkSpeed; // Assigns the currect walk speed into Original walkspeed.
	}

	HealthInt = 0.0;
    EnergyInt = 0.4;
	HealthTickSpeed = 1.0f;
	bCanSprint = true;
}

/**
* INPUT KEY BINDINGS.
*/
void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent); // Allows for me to setup custom input bindings.

	// Action mappings
	InputComponent->BindAction("Read", EInputEvent::IE_Pressed, this, &APlayerCharacter::Read); // Key name - Enum Einputevent - pressed down - current class is owner - address of use function
	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &APlayerCharacter::OnJumpStart);
	InputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &APlayerCharacter::OnJumpFinish);
	InputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &APlayerCharacter::OnSprintStart);
	InputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &APlayerCharacter::OnSprintFinish);
	InputComponent->BindAction("Use", EInputEvent::IE_Pressed, this, &APlayerCharacter::Use); 

	// Axis mappings
	InputComponent->BindAxis("MoveFrontBack", this, &APlayerCharacter::MoveUpDown);
	InputComponent->BindAxis("MoveLeftRight", this, &APlayerCharacter::MoveLeftRight); 
	InputComponent->BindAxis("LookUpDown", this, &APlayerCharacter::AddControllerPitchInput); 
	InputComponent->BindAxis("LookLeftRight", this, &APlayerCharacter::AddControllerYawInput); 

}

/**
*	MOVEMENT FUNCTION
*	First checks if playercharacter exists.
*	Gets the current rotation of player.
*	Ignores changes in pitch if player is on ground or falling.
*	Gets rotation matrix to move.
*	Move in direction with Value speed.
*	
*	@param Value (rate to move).
*	@return void
**/
void APlayerCharacter::MoveUpDown(float Value)
{
	if (Controller && Value != 0.0f) 
	{
		FRotator Rotation = GetActorRotation(); // Adds a rotation container, gets its rotation in degrees and stores it.

		if (GetCharacterMovement())
		{
			if (bIsSprinting && CurrentSpeed != ConstSprintSpeed && !SpeedBoostActive)
			{
				SetSpeed(ConstSprintSpeed);
			}
			else if (!bIsSprinting && CurrentSpeed != OriginalWalkSpeed && !SpeedBoostActive)
			{
				SetSpeed(OriginalWalkSpeed);
			}
		}

		/* Get rotation to move */
		FVector const Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X); 

		AddMovementInput(Direction, Value);
	}
}

/**
*	Update the default max speed rate with new rate.
*
*	@param Speed to move
*	@return void
**/
void APlayerCharacter::SetSpeed(float speed)
{
	if(!SpeedBoostActive)
	{
	GetCharacterMovement()->MaxWalkSpeed = speed;
	}
}

/**
*	MOVEMENT FUNCTION
*	Check If player exists, get rotation value of player. Gets direction to move in.
*	Move in direction by Value passed in.
*
*	@param Rate to move
*	@return void
**/
void APlayerCharacter::MoveLeftRight(float Value)
{
	if (Value != 0.0f)
	{
		FRotator const Rotation = GetActorRotation();
		FVector const Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

/**
*	Get location and rotation of camera. Sets players view point to camera location and rotation.
*	Sets where the trace will start, which direction, and where it ends. Traceparms setup to return details of whats collided.
*	Traces a ray against the world, returning the first blocking hit.
*
*	@params location to store hit info, distance of trace ray, the collision channel 
*	@return return the hit actor.
**/
bool APlayerCharacter::TraceFromSelf(FHitResult& OutResult, const float TraceDistance, ECollisionChannel const CollisionChannel)
{
	if (Controller)
	{
		FVector CameraLoc; 
		FRotator CameraRot;
		Controller->GetPlayerViewPoint(CameraLoc, CameraRot); //Location to cast ray (from player)

		FVector const BeginTrace = CameraLoc;
		FVector const ShootDir = CameraRot.Vector();
		FVector const TraceEnd = BeginTrace + ShootDir * TraceDistance;

		FCollisionQueryParams TraceParms(FName(TEXT("TraceFromSelf")), true, this); //returns what collided

		bool bHitReturned = false; //to determine if anything hit
		UWorld* const World = GetWorld(); 
		if (World)
		{
			bHitReturned = World->LineTraceSingleByChannel(OutResult, BeginTrace, TraceEnd, CollisionChannel, TraceParms); 
		}

		TraceParms.bTraceAsyncScene = true; //Whether we should perform the trace in the asynchronous scene.Default is false.
		TraceParms.bReturnPhysicalMaterial = false;  //Only fill in the PhysMaterial field 
		TraceParms.bTraceComplex = true; //Whether we should trace against complex collision

		return bHitReturned;
	}
	return false; //if there is no controller, nothing traced.
} 

/**
*	Read actor method
*	Sets up structure, which contains information about a trace hit. Point of impact and surface normal at that point.
*	Runs the ray trace method, firing a ray out infront of the character upon keypress of "read".
*
*	@params N/A
*	@return N/A	
**/
void APlayerCharacter::Read()
{
	FHitResult HitResult(EForceInit::ForceInit);

	bool bSuccessTrace = TraceFromSelf(HitResult, 150.0f, ECollisionChannel::ECC_EngineTraceChannel1); // Fire ray trace.
	if (bSuccessTrace)
	{
		AActor* const HitActor = HitResult.GetActor(); 
		if (HitActor)
		{ 
			ASign* SignActor = Cast<class ASign>(HitActor); // Get actor collided with.
			if (SignActor)
			{
				FString const SignMessage = SignActor->GetMessage();  // Take message from Sig
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, SignMessage);	// Display as debug message.
			}
		}
	}
}

/* Set sprinting */
void APlayerCharacter::OnSprintStart()
{
	if (!SpeedBoostActive & bCanSprint)
	{
		bIsSprinting = true;
		GetWorld()->GetTimerManager().ClearTimer(EnergyAddTimer);
		GetWorld()->GetTimerManager().SetTimer(EnergyRemoveTimer, this, &APlayerCharacter::EnergyRemove, 0.1, true);
	}
}
void APlayerCharacter::OnSprintFinish()
{
	if (!SpeedBoostActive)
	{
	GetWorld()->GetTimerManager().ClearTimer(EnergyRemoveTimer);
	GetWorld()->GetTimerManager().SetTimer(EnergyAddTimer, this, &APlayerCharacter::EnergyAdd, 0.1, true);
	bIsSprinting = false;
	}
}

void APlayerCharacter::EnergyAdd()
{
	if (EnergyInt < 0.5)
	{
		EnergyInt += EnergyRegenerateSpeed;
		UpdateEnergy(EnergyInt);
	}
}

void APlayerCharacter::EnergyRemove()
{
	if (EnergyInt > 0.0001)
	{
		EnergyInt -= EnergyDamageSpeed;
		UpdateEnergy(EnergyInt);
	}
}

/* Set Jumping */
void APlayerCharacter::OnJumpStart()
{
	bPressedJump = true;
}
void APlayerCharacter::OnJumpFinish()
{
	bPressedJump = false;
}

/*
*   Ray trace to find the  closest Usable Actor.
*	(look at previous ray trace function for more details)
*
*   @params N/A
*	@return the hit actor of the ray trace.
*/
//AUsableActor* APlayerCharacter::GetUsableActorInView()
//{
//	FVector camLoc;
//	FRotator camRot;

//	if (Controller == NULL)
//		return NULL;

//	Controller->GetPlayerViewPoint(camLoc, camRot);
//	const FVector start_trace = camLoc;
//	const FVector direction = camRot.Vector();
//	const FVector end_trace = start_trace + (direction * MaxUseDist);

//	FCollisionQueryParams TraceParams(FName(TEXT("")), true, this);
//	TraceParams.bTraceAsyncScene = true;
//	TraceParams.bReturnPhysicalMaterial = false;
//	TraceParams.bTraceComplex = true;

//	FHitResult Hit(ForceInit);
//	GetWorld()->LineTraceSingleByChannel(Hit, start_trace, end_trace, ECollisionChannel::ECC_EngineTraceChannel1, TraceParams);

//	return Cast<AUsableActor>(Hit.GetActor());
//}

/*
*   Update actor currently being looked at by player.
*	If the player is looking at an actor, it will be focused, otherwise it will be unfocused.
*
*   @params the frame ticks per second
*	@return N/A
*/

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CurrentSpeed = GetCharacterMovement()->MaxWalkSpeed;
	if (Controller)
	{

		AInventoryItem* Isusable = GetUsableItemInView();

		/* If actor is not in view, end focus */
		if (UsableItemFocused != Isusable)
		{
			if (UsableItemFocused)
			{
				UsableItemFocused->EndFocusItem();
			}
			bNewFocus = true;
		}

		UsableItemFocused = Isusable; // Assign new Focus

		 /* If actor is in view, start focus */
		if (Isusable)
		{
			if (bNewFocus)
			{
				Isusable->StartFocusItem();
				bNewFocus = false;
			}
		}

		//Limit energy from 0-1.0f, and reset run speed
		if(EnergyInt <= 0.001f)
		{
			bCanSprint = false;
			SetSpeed(150);
		}




		if ((EnergyInt >= 0.01f) & (EnergyInt < 0.5f))
		{
			bCanSprint = true;
		}

		//if (bIsSprinting & (EnergyInt <= 0.51f) & (EnergyInt > 0.01f))
		//{
		//	EnergyInt -= EnergyDamageSpeed;
		//	UpdateEnergy(EnergyInt);
		//}
		//if (!bIsSprinting & (EnergyInt < 0.5f))
		//{
		//	EnergyInt += EnergyRegenerateSpeed;
		//	UpdateEnergy(EnergyInt);
		//}

	}
}

/*
*   Use implementation method.
*	Sends an "OnUsed" method to blueprint, where behaviors for pickup/drop are defined.
* 
*   @params N/A
*	@return N/A
*/

void APlayerCharacter::Use_Implementation()
{
	AInventoryItem* Isusable = GetUsableItemInView();
	if(Isusable)
	{
		if (ItemInventoryStructure.Num() < 5)
		{
			if (!ItemInventoryStructure.Contains(Isusable->ItemInfo))
			{
				GiveItem(Isusable->ItemInfo); // Add the item to our inventory
								  //Isusable->ItemUsed(this);
				Isusable->Destroy(); // Destroy the physical version of the item
			}
			else
			{
				printMSG(TEXT("You Already Have This Item!"), 2.0);
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("You already have this item.")));
			}
		}else
		{
			printMSG(TEXT("Your Inventory Is Full"), 2.0);
		}
	}
	
}

AInventoryItem* APlayerCharacter::GetUsableItemInView()
{
	FVector camLoc;
	FRotator camRot;

	if (Controller == NULL)
		return NULL;

	Controller->GetPlayerViewPoint(camLoc, camRot);
	const FVector start_trace = camLoc;
	const FVector direction = camRot.Vector();
	const FVector end_trace = start_trace + (direction * MaxUseDist);

	FCollisionQueryParams TraceParams(FName(TEXT("")), true, this);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.bTraceComplex = true;

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, start_trace, end_trace, ECollisionChannel::ECC_EngineTraceChannel1, TraceParams);

	//DrawDebugLine(GetWorld(), start_trace, end_trace, FColor(255, 0, 0), false, -1, 0, 12.333);

	return Cast<AInventoryItem>(Hit.GetActor());
}

/*
*   Validation method for "Use", required, not used.
*
*   @params N/A
*	@return N/A
*/
bool APlayerCharacter::Use_Validate()
{
	// No special server-side validation performed.
	return true;
}

/*
*   Checks if Speedboost is active, if it is, it will set the player characters speed to 2000,
*	it then runs a timer function, which runs "ResetAbilities" function, which resets the speed 
*	to normal speed after 10 seconds.
*	if speedboost is false, it will keep the speed at normal (450).
*
*   @params N/A
*	@return N/A
*/
void APlayerCharacter::SpeedBoost()
{ 
	if (SpeedBoostActive)
	{
		GetCharacterMovement()->MaxWalkSpeed = 2000;
		GetWorld()->GetTimerManager().SetTimer(SpecialEffectTimer, this, &APlayerCharacter::ResetAbilities, 10.0f, false);
	}else
	{
		GetCharacterMovement()->MaxWalkSpeed = 450;
	}
}

/*
*   Called to reset the characters speed to normal pace.
*
*   @params N/A
*	@return N/A
*/
void APlayerCharacter::ResetAbilities()
{
	GetCharacterMovement()->MaxWalkSpeed = 500;
	SpeedBoostActive = false;
}

/*
*   Used to change the player characters skin to anything defined in the parameters.
*	Used within Blueprints to easily switch between transparent and normal outfit.
*
*   @params Material (defined in blueprints)
*	@return N/A
*/
void APlayerCharacter::ChangeOutfit(UMaterialInterface* BodyOutfit, UMaterialInterface* HeadSkin)
{
	MeshHolder->SetMaterial(0, BodyOutfit);
	MeshHolder->SetMaterial(1, HeadSkin);
}

/*
*   Used to check whether the player can instantly build or not.
*	Searches through the game world for SentryGuns, and checks whether they are craftable or not.
*
*   @params True/false
*	@return N/A
*/
void APlayerCharacter::InstaBuild(bool IsActive)
{
	if(IsActive)
	{
		TSubclassOf<AActor> SentryGun; 
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), SentryGun, FoundActors);
	}
}

void APlayerCharacter::MakePawnNoise(float Loudness)
{
	if (Role == ROLE_Authority)
	{
		/* Make noise to be picked up by PawnSensingComponent by the enemy pawns */
		MakeNoise(Loudness, this, GetActorLocation());
	}
}

void APlayerCharacter::AlterMouse(bool set)
{
	APlayerController* CharController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if(set)
	{
			CharController->bShowMouseCursor = true;
			CharController->bEnableClickEvents = true;
			CharController->bEnableMouseOverEvents = true;
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("True"));
	}else
	{
			CharController->bShowMouseCursor = false;
			CharController->bEnableClickEvents = false;
			CharController->bEnableMouseOverEvents = false;
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("False"));
	}
}

/////////////////////////INVENTORY////////////////////////////////////
void APlayerCharacter::GiveItem(FInventoryItemStruct Item)
{

	int32 idx = ItemInventoryStructure.Find(Item); // Grab the index of the item

	if (!ItemInventoryStructure.IsValidIndex(idx)) // If the index is NOT valid it means the item isnt in our inventory / array
	{
		//Then the item can be added!
		ItemInventoryStructure.Add(Item);
		RefreshInventory(); // Update our Ui

	} 

}

void APlayerCharacter::DropItem(FInventoryItemStruct Item)
{

	AInventoryItem* WorldItem = GetWorld()->SpawnActor<AInventoryItem>(Item.ItemClass, FVector(SentryLocation.X, SentryLocation.Y,SentryLocation.Z), FRotator(0, 0, 0)); // Spawn the item in the world
	WorldItem->ItemInfo = Item; // Assign the item info of the newly spawned item in the world to the one we dropped
	int32 idx = ItemInventoryStructure.Find(Item); // Grab the index of the item we want to drop


	if (ItemInventoryStructure.IsValidIndex(idx)) // Make sure its valid
	{
		if (ItemInventoryStructure[idx] == Item) // Make sure the item in our inventory matches the one we want to drop
		{
			ItemInventoryStructure.Remove(Item); // Remove it from the array
			RefreshInventory(); // Update our UI
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Removed item from player inventory")));
		}
	}

}

void APlayerCharacter::UseItem(FInventoryItemStruct Item, FInventoryItemStruct &InventoryItem)
{
	if (!TrapInConstruction)
	{
	AInventoryItem* WorldItem = GetWorld()->SpawnActor<AInventoryItem>(Item.ItemClass, GetActorLocation(), FRotator(0, 0, 0)); // Spawn the item in the world
	WorldItem->UseItem(this, InventoryItem); // call the blueprint event
	//ItemInventoryStructure.Remove(Item); // Remove it from the array
	ItemInventoryStructure.Remove(Item);

		ItemBeingCrafted = WorldItem;
		TrapInConstruction = true;
		printMSG(TEXT("Hold X to place trap"), 5.0);
		RefreshInventory(); // Update our UI
	}
}

void APlayerCharacter::PerformUsedAction()
{
	if (bIsWithinItemRange && FocusedItem != nullptr) // If we are within the pickup range of an item and we are focused on a item
	{
		GiveItem(FocusedItem->ItemInfo); // Add the item to our inventory
		FocusedItem->Destroy(); // Destroy the physical version of the item
		bIsWithinItemRange = false;
		FocusedItem = nullptr;
	}
}

void APlayerCharacter::RefreshInventory_Implementation()
{

}

void APlayerCharacter::UpdateInventory()
{
	RefreshInventory();
}

void APlayerCharacter::SetWithinItemRadius(bool bIsInRadius, AInventoryItem* Item)
{
	if (bIsInRadius == true) // if we are in the radius
	{
		FocusedItem = Item; // assign our focused item to the one in the radius
		bIsWithinItemRange = true;
	}
	else
	{
		FocusedItem = nullptr; // we are not on the item radius and we dont have a focused item
		bIsWithinItemRange = false; // 
	}
}


void APlayerCharacter::CheckIfCanCraft(FCraftingStruct Item)
{
	TSubclassOf<AInventoryItem> AItem;
	TSubclassOf<AInventoryItem> BItem;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("checking...")));

		uint8 NumbInventoryItems = ItemInventoryStructure.Num(); //Gets number of items within data table.
		for (uint8 i = 0; i < NumbInventoryItems; i++)
		{
			if (ItemInventoryStructure[i].ItemClass == Item.CraftA) {
				CraftAFound = true;

				AItem = ItemInventoryStructure[i].ItemClass;
			}
			if (ItemInventoryStructure[i].ItemClass == Item.CraftB) {
				CraftBFound = true;

				BItem = ItemInventoryStructure[i].ItemClass;
			}
			if(CraftAFound && CraftBFound)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Item is craftable")));
				ItemInventoryStructure.RemoveAt(i);
				UpdateInventory();
			}else
			{

			}
			CraftAFound = false;
			CraftBFound = false;
		}
}

void APlayerCharacter::CanCraft(FCraftingStruct Item, bool &CanCraftIt)
{

	TSubclassOf<AInventoryItem> AItem;
	TSubclassOf<AInventoryItem> BItem;

	CanCraftIt = false;
	CraftAFound = false;
	CraftBFound = false;
	
	uint8 NumbInventoryItems = ItemInventoryStructure.Num(); //Gets number of items within data table.
	for (uint8 i = 0; i < NumbInventoryItems; i++)
	{
		if (ItemInventoryStructure[i].ItemClass == Item.CraftA) {
			CraftAFound = true;

			AItem = ItemInventoryStructure[i].ItemClass;
		}
		if (ItemInventoryStructure[i].ItemClass == Item.CraftB) {
			CraftBFound = true;

			BItem = ItemInventoryStructure[i].ItemClass;
		}
	}

	if (CraftAFound && CraftBFound)
	{
		CanCraftIt = true;
	}
	else
	{
		CanCraftIt = false;
	}
}


void APlayerCharacter::CraftItem(FCraftingStruct Item, TSubclassOf<class AInventoryItem> &ItemClassA, TSubclassOf<class AInventoryItem> &ItemClassB)
{
	//FCraftingStruct* GOLookupRow = RecipeData->FindRow<FCraftingStruct>(FName("CraftB"), TEXT("GENERAL"), true);

	TSubclassOf<AInventoryItem> AItem;
	TSubclassOf<AInventoryItem> BItem;

	CraftAFound = false;
	CraftBFound = false;

	uint8 NumbInventoryItems = ItemInventoryStructure.Num(); //Gets number of items within data table.
	for (uint8 i = 0; i < NumbInventoryItems; i++)
	{
		if (ItemInventoryStructure[i].ItemClass == Item.CraftA) {
			CraftAFound = true;

			ItemClassA = ItemInventoryStructure[i].ItemClass;
		}
		if (ItemInventoryStructure[i].ItemClass == Item.CraftB) {
			CraftBFound = true;

			ItemClassB = ItemInventoryStructure[i].ItemClass;
		}
	}
}

uint8 APlayerCharacter::AmountOfRecipes(UDataTable* Crafting)
{
#if WITH_EDITOR

	static const FString ContextString(TEXT("GENERAL")); //Required to use FDataTableRowHandle. 
	uint8 NumberOfRecipes = Crafting->GetTableData().Num(); //Gets number of items within data table.

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Added to array")));

	return NumberOfRecipes;
#else 
	return 1;
#endif

}

void APlayerCharacter::OnStartOverlap(class AActor* OtherActor)
{

	if(!bHealthModDelay && OtherActor)
	{
		if (OtherActor->IsA(ABotCharacter::StaticClass()))
		{
			ABotCharacter* Bot = Cast<ABotCharacter>(OtherActor);

			bool disabled = Bot->BurglarDisabled;
			bool holdingtrap = Bot->HoldingValuableCode;
			if (!disabled && !holdingtrap)
			{
				HittingPlayer = true;
				GetWorld()->GetTimerManager().SetTimer(DelayHandle, this, &APlayerCharacter::TakeDMGloop, HealthTickSpeed, true);
			}
		}
	}
		/*if (OtherActor)
		{
			if (OtherActor->IsA(ABotCharacter::StaticClass()) && !bHealthModDelay)
			{
				if(HealthInt < 0.5)
				{
					HealthInt += HPDamageRate;
				}

				bHealthModDelay = true;
				GetWorld()->GetTimerManager().SetTimer(DelayHandle, this, &APlayerCharacter::HealthModDelay, HealthTickSpeed, false);
				UpdateHP(HealthInt);
			}
		}*/
	
}

void APlayerCharacter::OnEndOverlap(class AActor* OtherActor)
{
	if (OtherActor)
	{
		if (OtherActor->IsA(ABotCharacter::StaticClass()) && !bHealthModDelay)
		{
			HittingPlayer = false;
		}
	}

}

void APlayerCharacter::TakeDMGloop()
{
	//UE_LOG(LogTemp, Warning, TEXT("MyCharacter's Health is %d"), HealthInt);

	if (HittingPlayer)
	{
		if (HealthInt < 0.5)
		{
			HealthInt += HPDamageRate;
			UpdateHP(HealthInt);

		}
	}
	if(!HittingPlayer)
	{
		HittingPlayer = false;
		GetWorldTimerManager().ClearTimer(DelayHandle);
	}
}


void APlayerCharacter::HealthModDelay()
{
	bHealthModDelay = false;
}

/////////////////
//FCraftingStruct* GOLookupRow = CraftingRecipes->FindRow<FCraftingStruct>(FName("CraftB"), TEXT("GENERAL"), true);

//	int32 idx = CraftItemArray.Find(Item); // Grab the index of the item

//	if (!CraftItemArray.IsValidIndex(idx)) // If the index is NOT valid it means the item isnt in our inventory / array
//	{
//bool ItemB = ItemInventoryStructure.Contains(Item.CraftB);

//bool ItemA = ItemInventoryStructure.Contains(Item.CraftA);
//bool ItemB = ItemInventoryStructure.Contains(Item.CraftB);
//	FFridgeStruct* GOLookupRow = Fridge->FindRow<FFridgeStruct>(FName(*FString::FromInt(i)), TEXT("GENERAL"), true); //Get item in data table with FName (Name collumn in data table) same as "i" (from loop).
//	if (GOLookupRow)
//	{
//	}

/* if (ItemA && ItemB)
{

RefreshInventory(); // Update our Ui
GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ITEMS MATCH")));
} */

//	}