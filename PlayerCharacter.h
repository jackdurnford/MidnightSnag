/**
Game assets - Assignment 2
PlayerCharacter.h
Purpose: The purpose of this class, is to create all of the input functions, for movement and for "use". Additionally, the
raycasting is handled within this class. Ray casts are sent out of the player to detect nearby actors. The class communicates
with the character blueprint, which handles the pickup/drop functions once an actor has been successfully targetted.

@author Jack Durnford
@version 2.0
*/

#pragma once

/* Class includes */
#include "GameFramework/Character.h"
#include "FridgeFunctionLibrary.h"
#include "Engine/TargetPoint.h"
#include "InventoryItem.h"
#include "Engine.h"
#include "PlayerCharacter.generated.h"


class ULevel_BlueprintFunctionLibrary;

// Item Struct.. holds all the information of the item
USTRUCT(blueprintable)
struct PROJECTGAME_API FCraftingStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()



public:
	// Text that the item will display as its name
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemInfo)
		FName ReceipeName;

	// Item class, used to spawn the item in the world when its dropped
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemInfo)
		TSubclassOf<class AInventoryItem> CraftableItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemInfo)
		TSubclassOf<class AInventoryItem> CraftA;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemInfo)
		TSubclassOf<class AInventoryItem> CraftB;

	// Item Icon that will be displayed in the slot
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemInfo)
		UTexture2D* ItemThumb;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemInfo)
		FString ActionText;
	


	FName GetName() 
	{
		return ReceipeName;
	}

	//FCraftingStruct()
	//{
	//	ReceipeName = "Default";
	//	CraftableItem = nullptr;
	//	CraftA = nullptr;
	//	CraftB = nullptr;
	//	CraftB = nullptr;
	//	ItemThumb = nullptr;
	//	ActionText = nullptr;
	//}
	
	bool operator==(FCraftingStruct const& OtherI) const
	{

		if (ReceipeName != OtherI.ReceipeName)
		{

			return false;
		}
		if (CraftableItem != OtherI.CraftableItem)
		{

			return false;
		}
		if (CraftA != OtherI.CraftA)
		{

			return false;
		}
		if (CraftB != OtherI.CraftB)
		{

			return false;
		}
		if (ItemThumb != OtherI.ItemThumb)
		{

			return false;
		}
		if (ActionText != OtherI.ActionText)
		{

			return false;
		}
	

		return true;

	}



};


UCLASS()
class PROJECTGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()



public:

	/** team's AI director */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawner, meta = (AllowPrivateAccess = "true"))
		ULevel_BlueprintFunctionLibrary* AIDirector;
	/* Movement variables */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = HPEnergy)
	bool bIsSprinting;

	float OriginalWalkSpeed;
	float CurrentSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SprintingSpeed)
	float ConstSprintSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = HPEnergy)
		float HealthInt;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = HPEnergy)
		bool bHealthModDelay;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = HPEnergy)

		bool bCanSprint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = HPEnergy)
		float EnergyInt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemSpawnLocation)
		FVector SentryLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HPEnergy)
		float HPDamageRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HPEnergy)
		float HealthTickSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HPEnergy)
		float EnergyRegenerateSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HPEnergy)
		float EnergyDamageSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HPEnergy)
		bool HittingPlayer;
	/* Default functions */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	/* Called to bind functionality to input */
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	/* Called to move player actor */
	void MoveUpDown(float Value);
	void MoveLeftRight(float Value);
	void OnSprintStart();
	void OnSprintFinish();
	void OnJumpStart();
	void OnJumpFinish();
	void SetSpeed(float speed);


	/* Called when "E" pressed to read text from an actor */
	void Read();

	/* Raytrace method - returns true if hit */
	bool TraceFromSelf(FHitResult& OutResult, const float TractDistance, ECollisionChannel const CollisionChannel); 

	/* Use the actor currently in view (if derived from UsableActor) */
	UFUNCTION(BlueprintCallable, WithValidation, Server, Reliable, Category = PlayerAbility)
	virtual void Use();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Player Health & Energy", meta = (DisplayName = "UpdatePlayerHP"))
		float UpdateHP(float playerhp);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Player Health & Energy", meta = (DisplayName = "UpdatePlayerEnergy"))
		float UpdateEnergy(float PlayerEnergy);
	
	/* Get the actor currently being looked at by the player, which is also derived from UsableActor */
	class AUsableActor* GetUsableActorInView();

	/* Max distance to use/focus on actors. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float MaxUseDist;

	/* If a new focus target is made */
	bool bNewFocus;


	/* If a new focus target is made */
	

	/* Actor which is derived from the actor "UsableActor" within the players crosshairs center-view (center screen). */
	AUsableActor* UsableActorFocused;

	/********** TASK 3 - DYNAMIC ASSETS ************/

	/* Handle to manage the timer */
	FTimerHandle SpecialEffectTimer;

	/*	Skeletal mesh componenet, defined within Blueprints, used to change player character outfit (material) 	*/
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "StaticMesh Components")
	USkeletalMeshComponent* MeshHolder;

	/*	Used to check whether player can use increased speed buff. Used in blueprints.	*/	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool SpeedBoostActive;

	/*	Used to switch between outfits. Defined in blueprints within node dropdown menu */	
	UFUNCTION(BlueprintCallable, Category = SpecialAbility)
	void ChangeOutfit(UMaterialInterface* BodyOutfit, UMaterialInterface* HeadSkin);

	/*	Used to boost players speed. Called from within blueprints */
	UFUNCTION(BlueprintCallable, Category = SpecialAbility)
	void SpeedBoost();

	/*	Used to reset players speed, after a speedboost */
	UFUNCTION(BlueprintCallable, Category = SpecialAbility)
	void ResetAbilities();

	/* MakeNoise hook to trigger AI noise emitting (Loudness between 0.0-1.0)  */
	UFUNCTION(BlueprintCallable, Category = "AI")
		void MakePawnNoise(float Loudness);

	UFUNCTION()
		void OnStartOverlap(class AActor* OtherActor);
	UFUNCTION()
		void OnEndOverlap(class AActor* OtherActor);

	FTimerHandle EnergyAddTimer;
	FTimerHandle EnergyRemoveTimer;
	void EnergyAdd();
	void EnergyRemove();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "MessagePrinting", meta = (DisplayName = "PrintMessageToViewport"))
		void printMSG(const FString& msg, float TimeToDisplay);


	//void OnOverlap(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable, Category = "BurglarBehavior")
		void TakeDMGloop();

	//////
	/*	Used to enable instant build */
	void InstaBuild(bool IsActive);

	UFUNCTION(BlueprintCallable, Category = SpecialAbility)
		void AlterMouse(bool set);

	///////////////////////inventory////////////////////////////////

	//Inventory, Array of FInventoryItemStructs
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
		TArray<FInventoryItemStruct> ItemInventoryStructure;

	//Adds the item to the inventory given its FInventoryItemStruct or "data"
	UFUNCTION(BlueprintCallable, Category = SpecialAbility)
	void GiveItem(FInventoryItemStruct Item);

	//Drops the item
	UFUNCTION(BlueprintCallable, Category = Inventory)
		void DropItem(FInventoryItemStruct Item);

	//Uses the item and calls the blueprint event
	UFUNCTION(BlueprintCallable, Category = Inventory)
		void UseItem(FInventoryItemStruct Item, FInventoryItemStruct &InventoryItem);

	//Updates our Inventory UI
	UFUNCTION(BlueprintNativeEvent, Category = Inventory)
		void RefreshInventory(); // Dummy event that notifies the UI that our inventory has been updated

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Inventory)
		bool bIsWithinItemRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Inventory)
		AInventoryItem* FocusedItem; // Item that is within our radius

	 /* Actor which is derived from the actor "UsableActor" within the players crosshairs center-view (center screen). */
	AInventoryItem* UsableItemFocused;

	/* Get the actor currently being looked at by the player, which is also derived from UsableActor */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	class AInventoryItem* GetUsableItemInView();

	UFUNCTION(BlueprintCallable, Category = Inventory)
		void SetWithinItemRadius(bool bIsInRadius, AInventoryItem* Item);

	UFUNCTION(BlueprintCallable, Category = Inventory)
		void UpdateInventory();
	

	//Inventory, Array of FInventoryItemStructs
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
		TArray<FCraftingStruct> CraftItemArray;

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void CheckIfCanCraft(FCraftingStruct Item);

	UFUNCTION(BlueprintCallable, Category = Inventory)
		void CraftItem(FCraftingStruct Item, TSubclassOf<class AInventoryItem> &ItemClassA, TSubclassOf<class AInventoryItem> &ItemClassB);

	//void UpdateCraftingSlots(UDataTable* Crafting);
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Inventory)
	bool CraftAFound;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Inventory)
	bool CraftBFound;

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void CanCraft(FCraftingStruct Item, bool &CanCraftIt);

	//Variable to store item "in construction". Gets cleared when item is crafted. Is set when items "Used" function run". 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
	AInventoryItem* ItemBeingCrafted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
	bool TrapInConstruction;

	//UFUNCTION()
	//	void LoopRecipes(UDataTable* Crafting, uint8 index,  struct FCraftingStruct* ReturnedStruct);
	
	//UFUNCTION(BlueprintCallable, Category = Inventory)
	//void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);


	UFUNCTION(BlueprintCallable, Category = Inventory)
		uint8 AmountOfRecipes(UDataTable* Crafting);

	/* Handle to manage the timer */
	FTimerHandle DelayHandle;

	void HealthModDelay();


public: 
		//Gets called when we press the E button
		void PerformUsedAction();

		/** Returns AIDirector subobject **/
		//UFUNCTION(BlueprintCallable, Category = AIDIRECTOR)
		FORCEINLINE ULevel_BlueprintFunctionLibrary* GetAIDirector() const { return AIDirector; }
};
