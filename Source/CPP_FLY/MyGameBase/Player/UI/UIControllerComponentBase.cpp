#include "UIControllerComponentBase.h"
#include "UIControllerComponentEnvBase.h"
#include "MySys/HelperLib.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

UUIControllerComponentBase::UUIControllerComponentBase()
{
	EnvClass = UUIControllerComponentEnvBase::StaticClass();

	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bTickEvenWhenPaused = true;
	PrimaryComponentTick.TickGroup = TG_PostPhysics;
	
	bWantsInitializeComponent = true;
	bAutoActivate = true;
	bAutoRegister = true;
}

void UUIControllerComponentBase::PostInitProperties()
{
	UE_LOG(MyLog, Log, TEXT("UUIControllerComponentBase::PostInitProperties..."));
	Super::PostInitProperties();
}

void UUIControllerComponentBase::BindOwner_Implementation(AActor* InOwner)
{
	check(InOwner);
	check(InOwner->IsA(APlayerController::StaticClass()));
	PC = Cast<APlayerController>(InOwner);
}

void UUIControllerComponentBase::OwnerReady_Implementation(AActor* InOwner)
{
	InitPlayerController(Cast<APlayerController>(InOwner));
}

void UUIControllerComponentBase::InitPlayerController(APlayerController* InPC)
{
	UE_LOG(MyLog, Log, TEXT("UUIControllerComponentBase::InitPlayerController..."));
	InitializeEnvironment();

	if(GetEnvBase())
	{
		UE_LOG(MyLog, Log, TEXT("UIControllerComponentBase: Calling MyBeginPlay of EnvBase"));
		GetEnvBase()->MyBeginPlay();
	}
	else
	{
		UE_LOG(MyLog, Log, TEXT("UIControllerComponentBase: Skipping calling MyBeginPlay of EnvBase: environment is nullptr"));
	}
	UE_LOG(MyLog, Log, TEXT("UIControllerComponentBase::BeginPlay DONE"));
}

void UUIControllerComponentBase::InitializeEnvironment()
{
	UE_LOG(MyLog, Log, TEXT("Initializing UI Controller environment..."));
	// Initializing environment
	checkf(EnvClass, TEXT("Environment class must be set!"));
	UE_LOG(MyLog, Log, TEXT("Creating UI Controller environment of class \"%s\"..."), *EnvClass->GetName());
	Env = NewObject<UUIControllerComponentEnvBase>(this, EnvClass, FName(TEXT("Env")));
	UE_LOG(MyLog, Log, TEXT("Binding UI controller to environment..."));
	Env->BindController(this);
}

void UUIControllerComponentBase::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UUIControllerComponentBase::InitializeComponent()
{
	UE_LOG(MyLog, Log, TEXT("UIControllerComponentBase::InitializeComponent"));

	// NOTE: InitializeComponent is called BEFORE BeginPlay() of both UActorComponent and the Actor itself,
	// but only if bWantsInitializeComponent = true;
	Super::InitializeComponent();
}

void UUIControllerComponentBase::Activate(bool bReset)
{
	UE_LOG(MyLog, Log, TEXT("UIControllerComponentBase::Activate"));
	Super::Activate(bReset);
	if(AreGameWidgetsRelevant())
	{
		ShowWidgetCanvas();
	}	
	else
	{
		UE_LOG(MyLog, Log, TEXT("Skipping showing widgets - irrelevant for current world"));
	}
}

void UUIControllerComponentBase::Deactivate() 
{
	UE_LOG(MyLog, Log, TEXT("UIControllerComponentBase::Deactivate"));
	if(AreGameWidgetsRelevant())
	{
		HideWidgetCanvas();
	}
	else
	{
		UE_LOG(MyLog, Log, TEXT("Skipping hiding widgets - irrelevant for current world"));
	}
}

bool UUIControllerComponentBase::AreGameWidgetsRelevant() const
{
	return GetWorld()->IsGameWorld();
}

void UUIControllerComponentBase::BeginPlay()
{
	UE_LOG(MyLog, Log, TEXT("UIControllerComponentBase::BeginPlay"));
	Super::BeginPlay();
	// WARNING!!! Stop when adding functionality here - rather use the InitPlayerController!!
}

void UUIControllerComponentBase::EndPlay(const EEndPlayReason::Type InReason)
{
	Super::EndPlay(InReason);
}

UUserWidget* UUIControllerComponentBase::CreateAndRegisterWidget(TSubclassOf<UUserWidget> InWidgetClass, const FString& InWidgetName)
{
	UE_LOG(MyLog, Log, TEXT("CreateAndRegisterWidget: Name=%s"), *InWidgetName);
	if(InWidgetClass == nullptr)
	{
		UE_LOG(MyLog, Warning, TEXT("Skipping widget creation: Widget Class: nullptr"));
		return nullptr;	
	}
	else
	{
		if(AreGameWidgetsRelevant())
		{
			UE_LOG(MyLog, Log, TEXT("Class Name: %s"), *InWidgetClass->GetName());
			UUserWidget* W = CreateWidget<UUserWidget>(GetController(), InWidgetClass);
			if(nullptr == W)
			{
				UE_LOG(MyLog, Warning, TEXT("CreateWidget returned nullptr!"));
				return nullptr;
			}
			RegisterWidget(W);
			return W;
		}
		else
		{
			UE_LOG(MyLog, Log, TEXT("Skipping widget creation - irrelevant for current world"));
			return nullptr;
		}
	}
}

void UUIControllerComponentBase::RegisterWidget(UUserWidget* InWidget)
{
	check(InWidget);
	AllWidgets.Add(InWidget);
}

void UUIControllerComponentBase::ShowWidget(UUserWidget* InWidget)
{
	check(InWidget);
	DoShowWidget(InWidget);
	// @TODO: Mark as visible
}

void UUIControllerComponentBase::HideWidget(UUserWidget* InWidget)
{
	check(InWidget);
	DoHideWidget(InWidget);
	// @TODO: Mark as invisible
}

bool UUIControllerComponentBase::IsWidgetVisible(UUserWidget* InWidget) const
{
	// @TODO: return REAL status;
	return true;
}

void UUIControllerComponentBase::ShowWidgetCanvas()
{
	for(UUserWidget* W : AllWidgets)
	{
		if(IsWidgetVisible(W))
		{
			DoShowWidget(W);
		}
	}
}

void UUIControllerComponentBase::HideWidgetCanvas()
{
	for(UUserWidget* W : AllWidgets)
	{	
		if(IsWidgetVisible(W))
		{
			DoHideWidget(W);
		}
	}
}

void UUIControllerComponentBase::DoShowWidget(UUserWidget* InWidget)
{
	if(false == InWidget->IsInViewport())
	{
		InWidget->AddToViewport();
	}
	else
	{
		UE_LOG(MyLog, Log, TEXT("Widget \"%s\" of class \"%s\"is already in viewport"), *InWidget->GetName(), *InWidget->GetClass()->GetName());
	}
}

void UUIControllerComponentBase::DoHideWidget(UUserWidget* InWidget)
{
	if(InWidget->IsInViewport())	
	{
		InWidget->RemoveFromViewport();
	}
}

APlayerController* UUIControllerComponentBase::GetController() const
{
	return GetPC();
}

APlayerController* UUIControllerComponentBase::GetPC() const
{
	return PC;
}
