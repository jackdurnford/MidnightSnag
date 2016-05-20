/**
Dynamic Game Assets - Task 3
FridgeFunctionLibrary.h
Purpose: The purpose of this class, is to setup a data structure for the imported fridge items CSV, and also to 
provide the nessesary core functions to the Fridge UMG blueprints in order to control the fridge functionality.

@author Jack Durnford
@version 2.0
*/
#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "FridgeFunctionLibrary.generated.h"


/* Structure that defines a fridge item table entry */
USTRUCT()
struct PROJECTGAME_API FFridgeStruct : public FTableRowBase
{
	/* Macro to allow building without constructor defined */
	GENERATED_USTRUCT_BODY()

public:
	/** Name of item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemCategoriz")
		FName ItemName;

	/** Item thumbnail */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemCategoriz")
		TAssetPtr<UTexture> ItemImage;

	/* Required - Do not remove */
	FFridgeStruct()
	{}
};


UCLASS()
class PROJECTGAME_API UFridgeFunctionLibrary : public UBlueprintFunctionLibrary
{
	/* Macro to allow building without constructor defined */
	GENERATED_BODY()

public: 
	UFridgeFunctionLibrary(const FObjectInitializer& ObjectInitializer);

	/* Retrieves all images from each item in the data table. To be used within Blueprints. */
	UFUNCTION(BlueprintCallable, Category = PlayerAbility)
		static void RetrieveItemImages(UDataTable* Fridge, TAssetPtr<UTexture> &Itemone,
			TAssetPtr<UTexture> &Itemtwo, TAssetPtr<UTexture> &Itemthree, TAssetPtr<UTexture> &Itemfour, TAssetPtr<UTexture> &Itemfive,
			TAssetPtr<UTexture> &Itemsix, TAssetPtr<UTexture> &Itemseven, TAssetPtr<UTexture> &Itemeight, TAssetPtr<UTexture> &Itemnine);

	/* Handle structure to provide helper functions to retrieve struct filled with data. */
	FDataTableRowHandle GameObjectLookupTable;
};
