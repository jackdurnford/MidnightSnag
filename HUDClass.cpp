/**
Dynamic Assets - Task 3
HUDClass.cpp
Purpose: Contains all of the components for Pawnsensing. Updates Blackboard through the BotAI controller.

@author Jack Durnford
@version 3.0
*/
#include "PROJECTGAME.h"
#include "HUDClass.h"
#include "Engine/Canvas.h"


AHUDClass::AHUDClass(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	/* Find texture file and store it within variable (eg HealthBar) */
	//static ConstructorHelpers::FObjectFinder<UTexture2D> HealthBar(TEXT("Texture2D'/Game/Textures/HealthBar.HealthBar'"));
	//static ConstructorHelpers::FObjectFinder<UTexture2D> HealthBG(TEXT("Texture2D'/Game/Textures/HealthBarBG.HealthBarBG'"));
	//static ConstructorHelpers::FObjectFinder<UTexture2D> EnergyBar(TEXT("Texture2D'/Game/Textures/Energy.Energy'"));
	//static ConstructorHelpers::FObjectFinder<UTexture2D> EnergyBG(TEXT("Texture2D'/Game/Textures/EnergyBar.EnergyBar'"));
	//static ConstructorHelpers::FObjectFinder<UTexture2D> TTBG(TEXT("Texture2D'/Game/Textures/ToolTip.ToolTip'"));


	//TooltipBG = TTBG.Object;

	/* Store the texture into an object variable */
	//healthBarTexture = HealthBar.Object;
	//HealthBarBG = HealthBG.Object;

	/* Store the texture into an object variable */
	//EnergyTexture = EnergyBar.Object;
	//EnergyBarBG = EnergyBG.Object;

	/* Setup default values for HP and energy */
	health = 600;
	Energy = 600;

	ConstructorHelpers::FObjectFinder<UFont> FontObject(TEXT("Font'/Game/Fonts/CanvasFontNew.CanvasFontNew'"));
	if (FontObject.Object)
	{
		MyFont = FontObject.Object;
	}

	//TheController = GetOwningPlayerController();

	ToolTipDraw = false;
	UpdatePosition = false;
}

// Colors
const FColor AHUDClass::FColorBlack = FColor(0, 0, 0, 255);
const FColor AHUDClass::FColorRed = FColor(255, 0, 0, 255);
const FColor AHUDClass::FColorYellow = FColor(255, 255, 0, 255);
const FColor AHUDClass::FColorBlue = FColor(0, 0, 255, 255);
const FColor AHUDClass::FColor_White = FColor(255, 255, 255, 255);

/* Setup default values for HP and energy backgrounds widths */
int32 HealthBarLength = 600;
int32 EnergyBarLength = 600;

/**
* Draw 2D canvas into game every frame.
*
* @param Pawn.
* @return N/A.
*/
void AHUDClass::DrawHUD()
{
	Super::DrawHUD();
	//drawHealthBar();

	
	//	DrawTooltip();

}

/**
* Draw health and energy bars, along with their background images.
* It first makes an icon, with a specific size, with the object defined in the constructor.
* Secondly it checks whether Health/Energy is more than 0. If it is, it will draw the health bar at the 
* Width of the "health" & "Energy" variables.
*
* @param Pawn.
* @return N/A.
*/
void AHUDClass::drawHealthBar()
{
	//float ScaleUI = Canvas->ClipY / Canvas->ClipX;
	//float HeightOfCanvas = Canvas->SizeY;
	//float WidthOfCanvas = 50;

	//FCanvasIcon HealthBarIconBG = UCanvas::MakeIcon(HealthBarBG, 100, 100, HealthBarLength, 100);
	//FCanvasIcon EnergyBarIconBG = UCanvas::MakeIcon(EnergyBarBG, 100, 100, EnergyBarLength, 100);

	//FCanvasIcon HealthBarIcon = UCanvas::MakeIcon(healthBarTexture, 100, 100, health, 100);
	//FCanvasIcon EnergyBarIcon = UCanvas::MakeIcon(EnergyTexture, 100, 100, Energy, 100);

	//if (health > 0)
	//{
	//	Canvas->DrawIcon(HealthBarIconBG, WidthOfCanvas, HeightOfCanvas - 170, ScaleUI);
	//	Canvas->DrawIcon(HealthBarIcon, WidthOfCanvas, HeightOfCanvas - 170, ScaleUI);
	//	//float HeightOfCanvas = Canvas->SizeY;
	//	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::FromInt(HeightOfCanvas));	// Display as debug message.
	//	//float Scaler = Canvas->ClipY / Canvas->ClipX;
	//	DrawTextToCanvas(MyFont, FString("Health & Energy"), WidthOfCanvas, HeightOfCanvas - 220, FColorBlue, 0.7, false, FLinearColor(0, 0, 0, 1));
	//}

	//if (Energy > 0)
	//{
	//	//Canvas->DrawIcon(EnergyBarIconBG, (Canvas->SizeX) / 2.5, 600, ScaleUI);
	//	Canvas->DrawIcon(EnergyBarIconBG, WidthOfCanvas, HeightOfCanvas - 100, ScaleUI);
	//	Canvas->DrawIcon(EnergyBarIcon, WidthOfCanvas, HeightOfCanvas - 100, ScaleUI);
	//}
}

/**
* Damage to player. Subtracts "damageDone" from health variable if health is more than 5.
*
* @param amount to subtract from health variable (int).
* @return N/A.
*/
void AHUDClass::TakeDmg(int damageDone)
{
	if (health > 5)
	{
		health -= damageDone;
	}
}

/**
* Adds "HPToAdd" amount to players health, by adding to "health" variable".
*
* @param amount to add to health variable (int).
* @return N/A.
*/
void AHUDClass::AddHealth(int32 HPToAdd)
{
	health += HPToAdd;
}
//UFont* TheFont, const FString& TheStr, const float& X, const float& Y, const FLinearColor& TheColor, const float& TheScale, bool DrawOutline = false, const FLinearColor OutlineColor = FLinearColor(0, 0, 0, 1)
void AHUDClass::DrawTextToCanvas(UFont* TheFont, const FString& TheStr, const float& X, const float& Y, const FLinearColor& TheColor, const float& TheScale, bool DrawOutline, const FLinearColor OutlineColor)
{
	//Text and Font
	FCanvasTextItem NewText(FVector2D(X, Y), FText::FromString(TheStr), TheFont, TheColor);

	//Text Scale
	NewText.Scale.Set(TheScale, TheScale);

	//Outline gets its alpha from the main color
	NewText.bOutlined = true;
	NewText.OutlineColor = OutlineColor;
	NewText.OutlineColor.A = TheColor.A * 2;

	//Draw
	Canvas->DrawItem(NewText);
}

void AHUDClass::DrawTooltip()
{

	//FVector2D MousePos;
	//TheController->GetMousePosition(MousePos.X, MousePos.Y);
	//FCanvasIcon HealthBarIconBG = UCanvas::MakeIcon(TooltipBG, 100, 100, HealthBarLength, 100);

	////FCanvasIcon ToolTip = UCanvas::MakeIcon(TooltipBG, 100, 100, 100, 100);

	////Canvas->DrawIcon(ToolTip, MousePos.X, MousePos.Y, 1);

	//float ScaleUI = Canvas->ClipY / Canvas->ClipX;
	//float HeightOfCanvas = Canvas->SizeY;
	//float WidthOfCanvas = 50;

	//if (ToolTipDraw)
	//{
	//	

	//	Canvas->DrawIcon(HealthBarIconBG, MousePos.X - 50, MousePos.Y - 50, ScaleUI);

	//	MousePosTemp = MousePos;
	//	UpdatePosition = true;
	//	ToolTipDraw = false;
	//}

	//if (UpdatePosition)
	//{
	//	Canvas->DrawIcon(HealthBarIconBG, MousePosTemp.X - 100, MousePosTemp.Y - 100, ScaleUI);

	//}
}



//void AHUDClass::StartTimer()
//{
//	GetWorld()->GetTimerManager().SetTimer(EnergyTicker, this, &AHUDClass::EnergyHandler, 1.0f, true);
//}





/* 
// Fill out your copyright notice in the Description page of Project Settings.

#include "PROJECTGAME.h"
#include "HUDClass.h"
#include "Engine/Canvas.h"

//
//Static Consts
//


const FString AHUDClass::S_Button_Exit = FString("Exit");

// Colors
const FColor AHUDClass::FColorBlack = FColor(0, 0, 0, 255);
const FColor AHUDClass::FColorRed = FColor(255, 0, 0, 255);
const FColor AHUDClass::FColorYellow = FColor(255, 255, 0, 255);
const FColor AHUDClass::FColorBlue = FColor(0, 0, 255, 255);
const FColor AHUDClass::FColor_White = FColor(255, 255, 255, 255);

// Backgrounds
const FLinearColor AHUDClass::LC_Black = FLinearColor(0, 0, 0, 1);
const FLinearColor AHUDClass::LC_Pink = FLinearColor(1, 0, 1, 1);
const FLinearColor AHUDClass::LC_Red = FLinearColor(1, 0, 0, 1);
const FLinearColor AHUDClass::LC_Yellow = FLinearColor(1, 1, 0, 1);


AHUDClass::AHUDClass(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

static ConstructorHelpers::FObjectFinder<UTexture2D> HealthBar(TEXT("Texture2D'/Game/Textures/HealthBar.HealthBar'"));
static ConstructorHelpers::FObjectFinder<UTexture2D> HealthBG(TEXT("Texture2D'/Game/Textures/HealthBarBG.HealthBarBG'"));
static ConstructorHelpers::FObjectFinder<UTexture2D> EnergyBar(TEXT("Texture2D'/Game/Textures/Energy.Energy'"));
static ConstructorHelpers::FObjectFinder<UTexture2D> EnergyBG(TEXT("Texture2D'/Game/Textures/EnergyBar.EnergyBar'"));

healthBarTexture = HealthBar.Object;
HealthBarBG = HealthBG.Object;

EnergyTexture = EnergyBar.Object;
EnergyBarBG = EnergyBG.Object;

health = 600;
Energy = 600;
}

int32 HealthBarLength = 600;
int32 EnergyBarLength = 600;

void AHUDClass::DrawHUD()
{
Super::DrawHUD();
drawHealthBar();


}

//=============================
// Draw Health and energy bars
//=============================
void AHUDClass::drawHealthBar()
{
float ScaleUI = Canvas->ClipY / Canvas->ClipX;

FCanvasIcon HealthBarIconBG = UCanvas::MakeIcon(HealthBarBG, 100, 100, HealthBarLength, 100);
FCanvasIcon EnergyBarIconBG = UCanvas::MakeIcon(EnergyBarBG, 100, 100, EnergyBarLength, 100);

FCanvasIcon HealthBarIcon = UCanvas::MakeIcon(healthBarTexture, 100, 100, health, 100);
FCanvasIcon EnergyBarIcon = UCanvas::MakeIcon(EnergyTexture, 100, 100, Energy, 100);

if (health > 0)
{
Canvas->DrawIcon(HealthBarIconBG, (Canvas->SizeX) / 2.5, 80, ScaleUI);
Canvas->DrawIcon(HealthBarIcon, (Canvas->SizeX) / 2.5, 80, ScaleUI);
}

if (Energy > 0)
{
Canvas->DrawIcon(EnergyBarIconBG, (Canvas->SizeX) / 2.5, 10, ScaleUI);
Canvas->DrawIcon(EnergyBarIcon, (Canvas->SizeX) / 2.5, 10, ScaleUI);
}

}


void AHUDClass::TakeDmg(int damageDone)
{
if (health > 5)
{
health -= damageDone;
}
}

void AHUDClass::AddHealth(int32 HPToAdd)
{
health += HPToAdd;
}

void AHUDClass::EnergyHandler()
{

UE_LOG(LogTemp, Warning, TEXT("IS IT WORKING?"));

}

void AHUDClass::StartTimer()
{
GetWorld()->GetTimerManager().SetTimer(EnergyTicker, this, &AHUDClass::EnergyHandler, 1.0f, true);
}

void AHUDClass::DrawSpecialAbilityText()
{
//	FText TextToPrint = "Something";
FLinearColor TheFontColour = FLinearColor(1.0f, 1.0f, 1.0f);
//	FCanvasTextItem NewText(FVector2D(XPosition, YPosition), TextToPrint, TheFont, TheFontColour);

//Text Scale
//NewText.Scale.Set(ScaleX, ScaleY);

//Draw
//Canvas->DrawItem(NewText);
}

//void AHUDClass::DrawTextToScreen(UFont*	TheFont,
//	const FString& TheStr,
//	const float& X, const float& Y,
//	const FLinearColor& TheColor,
//	const float& TheScale,
//	bool DrawOutline = false,
//	const FLinearColor OutlineColor = FLinearColor(0, 0, 0, 1))
//{
//	//Text and Font
//	FCanvasTextItem NewText(
//		FVector2D(X, Y),
//		FText::FromString(TheStr),
//		TheFont,
//		TheColor
//		);
//
//	//Text Scale
//	NewText.Scale.Set(TheScale, TheScale);
//
//	//Outline gets its alpha from the main color
//	NewText.bOutlined = true;
//	NewText.OutlineColor = OutlineColor;
//	NewText.OutlineColor.A = TheColor.A * 2;
//
//	//Draw
//	Canvas->DrawItem(NewText);
//}





*/