/**
Dynamic Game Assets - Task 3
FridgeFunctionLibrary.cpp
Purpose: The purpose of this class, is to setup a data structure for the imported fridge items CSV, and also to
provide the nessesary core functions to the Fridge UMG blueprints in order to control the fridge functionality.

@author Jack Durnford
@version 2.0
*/
#include "PROJECTGAME.h"
#include "FridgeFunctionLibrary.h"


UFridgeFunctionLibrary::UFridgeFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	/* Create a data table, and assign it to one created within the Editor (FridgeDataTable) */
//	UDataTable* FridgeData;
	//static ConstructorHelpers::FObjectFinder<UDataTable> FridgeDataTable(TEXT("DataTable'/Game/Blueprints/FridgeDataTable.FridgeDataTable'"));
	//FridgeData = FridgeDataTable.Object;
}

/**
*	Used as node from within Blueprints, and allows you to get the thumbnail images from each item from 
*	within the data table. The images are then used to set the fridge slot images.
*	It will get how many items are stored within the data table, and then loops each item to 
*	retrieve its image. 
*
*	@params Data table which is defined within Blueprints.
*	@return returns the images from every item from within the data table.
**/
void UFridgeFunctionLibrary::RetrieveItemImages(UDataTable* Fridge, TAssetPtr<UTexture> &Itemone, 
	TAssetPtr<UTexture> &Itemtwo, TAssetPtr<UTexture> &Itemthree, TAssetPtr<UTexture> &Itemfour, TAssetPtr<UTexture> &Itemfive,
	TAssetPtr<UTexture> &Itemsix, TAssetPtr<UTexture> &Itemseven, TAssetPtr<UTexture> &Itemeight, TAssetPtr<UTexture> &Itemnine)
{
		static const FString ContextString(TEXT("GENERAL")); //Required to use FDataTableRowHandle.
//#if WITH_EDITOR
		//int32 Count = Fridge->RowMap.Num();
		//for (int32 i = 0; i < Count; i++)
		for (auto it : Fridge->RowMap)
		{
			//FFridgeStruct* GOLookupRow = (FFridgeStruct*)(it.Value[1]);
			//FFridgeStruct* GOLookupRowTwo = (FFridgeStruct*)(it.Value[2]);
			//Itemone = GOLookupRow->ItemImage;
			//Itemtwo = GOLookupRowTwo->ItemImage;

			FFridgeStruct* GOLookupRow = (FFridgeStruct*)(it.Value);

			FString TempDT = it.Key.ToString();
			int32 MyShinyNewInt = FCString::Atoi(*TempDT);


			switch (MyShinyNewInt) //Run case for each item in data table, return item iamge. 
						  	{
						  	case 0:
						  		Itemone = GOLookupRow->ItemImage;
						  		break;
						  	case 1:
						  		Itemtwo = GOLookupRow->ItemImage;
						  		break;
						  	case 2:
						  		Itemthree = GOLookupRow->ItemImage;
						  		break;
						  	case 3:
						  		Itemfour = GOLookupRow->ItemImage;
						  		break;
						  	case 4:
						  		Itemfive = GOLookupRow->ItemImage;
						  		break;
						  	case 5:
						  		Itemsix = GOLookupRow->ItemImage;
						  		break;
						  	case 6:
						  		Itemseven = GOLookupRow->ItemImage;
						  		break;
						  	case 7:
						  		Itemeight = GOLookupRow->ItemImage;
						  		break;
						  	case 8:
						  		Itemnine = GOLookupRow->ItemImage;
						  		break;
						  	}

			//UE_LOG(LogTemp, Warning, TEXT("Data table stuff!: %s"), *it.Key.ToString());

		}	//for (uint8 i = 0; i < NumbFridgeItems; i++)

		//for (auto it : Fridge->RowMap)
	//	{
	//	

			//if (GOLookupRow)
		//	{

				//	Itemone = GOLookupRow->ItemImage;
				////UE_LOG(LogTemp, Warning, TEXT("Data table stuff!:  %d") it.Key);
				//	int32 aNum = it.Key().GetNumber();
				//	switch (aNum) //Run case for each item in data table, return item iamge. 
				//	{
				//	case 0:
				//		Itemone = GOLookupRow->ItemImage;
				//		break;
				//	case 1:
				//		Itemtwo = GOLookupRow->ItemImage;
				//		break;
				//	case 2:
				//		Itemthree = GOLookupRow->ItemImage;
				//		break;
				//	case 3:
				//		Itemfour = GOLookupRow->ItemImage;
				//		break;
				//	case 4:
				//		Itemfive = GOLookupRow->ItemImage;
				//		break;
				//	case 5:
				//		Itemsix = GOLookupRow->ItemImage;
				//		break;
				//	case 6:
				//		Itemseven = GOLookupRow->ItemImage;
				//		break;
				//	case 7:
				//		Itemeight = GOLookupRow->ItemImage;
				//		break;
				//	case 8:
				//		Itemnine = GOLookupRow->ItemImage;
				//		break;
				//	}
		//	}
		
		
		//uint8 NumbFridgeItems = Fridge->GetTableData().Num(); //Gets number of items within data table.
		//for (uint8 i = 0; i < NumbFridgeItems; i++)
		//{
		//	FFridgeStruct* GOLookupRow = Fridge->FindRow<FFridgeStruct>(FName(*FString::FromInt(i)), ContextString, true); //Get item in data table with FName (Name collumn in data table) same as "i" (from loop).
		//	if (GOLookupRow)
		//	{
		//		switch (i) //Run case for each item in data table, return item iamge. 
		//		{
		//		case 0: 
		//			Itemone = GOLookupRow->ItemImage; 
		//			break;
		//		case 1:
		//			Itemtwo = GOLookupRow->ItemImage;
		//			break;
		//		case 2:
		//			Itemthree = GOLookupRow->ItemImage;
		//			break;
		//		case 3:
		//			Itemfour = GOLookupRow->ItemImage;
		//			break;
		//		case 4:
		//			Itemfive = GOLookupRow->ItemImage;
		//			break;
		//		case 5:
		//			Itemsix = GOLookupRow->ItemImage;
		//			break;
		//		case 6:
		//			Itemseven = GOLookupRow->ItemImage;
		//			break;
		//		case 7:
		//			Itemeight = GOLookupRow->ItemImage;
		//			break;
		//		case 8:
		//			Itemnine = GOLookupRow->ItemImage;
		//			break;
		//		}
		//	}
		//}
//#endif
}




//for (int32 i = 1; i < maxItems; i++)
//{
//	GameDataTable.RowName = FName(*FString::FromInt(i));
//	FGameData*  MyData = GameDataTable.GetRow<FGameData>();
//
	// Do some Stuff with MyData
//}