#include "CityWorker.h"
#include "TimerManager.h"
#include "JobManager.h"

ACityWorker::ACityWorker()
{
    PrimaryActorTick.bCanEverTick = false;
    JobManager = nullptr;
}

void ACityWorker::SetJobManager(AJobManager* Manager)
{
    JobManager = Manager;
}

void ACityWorker::StartJob()
{
    if (GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(WorkTimerHandle, this, &ACityWorker::CompleteJob, 5.0f, false);
    }
}

void ACityWorker::CompleteJob()
{
    if (JobManager)
    {
        JobManager->OnJobCompleted(this);
    }
}
