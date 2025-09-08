#include "CityWorker.h"
#include "Job.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NavigationSystem.h"
#include "TimerManager.h"
#include "JobManager.h"
#include "Engine/World.h"

ACityWorker::ACityWorker()
{
    PrimaryActorTick.bCanEverTick = false;
    JobManager = nullptr;
    IdleLocation = FVector::ZeroVector;
}

void ACityWorker::BeginPlay()
{
    Super::BeginPlay();
    IdleLocation = GetActorLocation();
}

void ACityWorker::SetJobManager(AJobManager* Manager)
{
    JobManager = Manager;
}

void ACityWorker::StartJob(FVector JobLocation)
{
    // Start job logic here, e.g. move to JobLocation

    if (GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(WorkTimerHandle, this, &ACityWorker::CompleteJob, 5.0f, false);
    }
}

void ACityWorker::CompleteJob()
{
    // Job completion logic here
}

void ACityWorker::GoToIdleLocation()
{
    UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
    if (NavSys)
    {
        AController* MyController = GetController();
        if (MyController)
        {
            UAIBlueprintHelperLibrary::SimpleMoveToLocation(MyController, IdleLocation);
        }
    }
}

void ACityWorker::EquipTool(AToolBase* Tool)
{
    this->EquippedTool = Tool;
    if (Tool)
    {
        Tool->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("ToolSocket"));
    }
}

