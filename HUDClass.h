/**
Dynamic Assets - Task 3
HUDClass.h
Purpose: Purpose: Heading file for the HUDClass. 

@author Jack Durnford
@version 3.0
*/
#pragma once

#include "GameFramework/HUD.h"
#include "HUDClass.generated.h"

UCLASS()
class PROJECTGAME_API AHUDClass : public AHUD
{
	/* Macro to allow building without constructor defined */
	GENERATED_UCLASS_BODY()

	/* Overrides the DrawHUD function, so that it can be used within our cpp */
	virtual void DrawHUD() override; 


		//Colors
		static const FColor	FColorBlack;
		static const FColor	FColorRed;
		static const FColor	FColorYellow;
		static const FColor	FColorBlue;
		static const FColor	FColor_White;
	
		static const FLinearColor LC_Black;
		static const FLinearColor LC_Pink;
		static const FLinearColor LC_Red;
		static const FLinearColor LC_Yellow;

		/** Verdana */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FontStuff)
			UFont* MyFont;
	
		/** Default fonts */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FontStuff)
			UFont* UE4Font;

	/* Used to store player HP value */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int32 health;

	/* Used to store player Energy value */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int32 Energy;

	/* Function used to draw and updates the health and energy bars */
	void drawHealthBar();

	/* Function for SUBTRACTING from the health variable */
	UFUNCTION(BlueprintCallable, Category = SpecialAbility)
	void TakeDmg(int32 damageDone);

	/* Function for ADDING from the health variable */
	UFUNCTION(BlueprintCallable, Category = SpecialAbility)
	void AddHealth(int32 HPToAdd);

	//UFont* TheFont, const FString& TheStr, const float& X, const float& Y, const FLinearColor& TheColor, const float& TheScale, bool DrawOutline = false, const FLinearColor OutlineColor = FLinearColor(0, 0, 0, 1)
	void DrawTextToCanvas(UFont* TheFont, const FString& TheStr, const float& X, const float& Y, const FLinearColor& TheColor, const float& TheScale, bool DrawOutline, const FLinearColor OutlineColor);

	/* TO BE IMPLEMENTED - Will draw text to display which special effect is in use */
	//void DrawSpecialAbilityText();
	//void EnergyHandler();
	//UFUNCTION(BlueprintCallable, Category = SpecialAbility)
	//void StartTimer();
	
	/* Pointer to 2d texture of each energy & health bar */
	UTexture2D* healthBarTexture;
	UTexture2D* HealthBarBG;
	UTexture2D* EnergyTexture;
	UTexture2D* EnergyBarBG;
	UTexture2D* TooltipBG;


	/* Handle to manage the timer */
	FTimerHandle EnergyTicker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ControllerStuff)
	APlayerController* TheController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ControllerStuff)
	FVector2D MousePos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ControllerStuff)
		FVector2D MousePosTemp;

	UFUNCTION(BlueprintCallable, Category = Tooltip)
	void DrawTooltip();

	/** Verdana */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tooltip)
		bool ToolTipDraw;

	/** Verdana */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tooltip)
		bool UpdatePosition;
};





//UCLASS()
//class PROJECTGAME_API AHUDClass : public AHUD
//{
//	GENERATED_UCLASS_BODY()
//
//		virtual void DrawHUD() override;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
//		int32 health;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
//		int32 Energy;
//
//	void DrawSpecialAbilityText();
//	void drawHealthBar();
//	UFUNCTION(BlueprintCallable, Category = SpecialAbility)
//		void TakeDmg(int32 damageDone);
//	UFUNCTION(BlueprintCallable, Category = SpecialAbility)
//		void AddHealth(int32 HPToAdd);
//	void EnergyHandler();
//	UFUNCTION(BlueprintCallable, Category = SpecialAbility)
//		void StartTimer();
//
//	UTexture2D* healthBarTexture;
//	UTexture2D* HealthBarBG;
//	UTexture2D* EnergyTexture;
//	UTexture2D* EnergyBarBG;
//
//	FTimerHandle EnergyTicker;
//
//
//	//Colors
//public:
//	const FLinearColor * ColorPtr;
//
//	//Colors
//	static const FColor		FColorBlack;
//	static const FColor		FColorRed;
//	static const FColor		FColorYellow;
//	static const FColor		FColorBlue;
//	static const FColor		FColor_White;
//
//	static const FLinearColor LC_Black;
//	static const FLinearColor LC_Pink;
//	static const FLinearColor LC_Red;
//	static const FLinearColor LC_Yellow;
//	//FString
//public:
//
//	static const FString S_Button_Exit;
//
//
//	/** Verdana */
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FontStuff)
//		UFont* VerdanaFont;
//
//	/** Default fonts */
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FontStuff)
//		UFont* UE4Font;
//
//	/** The default font size to be used by HUD */
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FontStuff)
//		float DefaultFontSize;
//
//	/** The HUD scale */
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FontStuff)
//		float GlobalHUDScale;
//
//	/** Cursor */
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FontStuff)
//		UTexture2D* MainCursor;
//
//	/** Cursor hovering */
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FontStuff)
//		UTexture2D* CursorHoveringButton;
//
//	/** Button BG */
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FontStuff)
//		UTexture2D* ButtonBG;
//
//	/** Materials interface */
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FontStuff)
//		UMaterialInterface* MaterialBG;
//
//	/* Draw Hud? */
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FontStuff)
//		bool DontDrawHUD;
//};
