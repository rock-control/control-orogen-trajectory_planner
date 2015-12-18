/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "DummyTask.hpp"

using namespace trajectory_planner;

DummyTask::DummyTask(std::string const& name)
    : DummyTaskBase(name)
{
}

DummyTask::DummyTask(std::string const& name, RTT::ExecutionEngine* engine)
    : DummyTaskBase(name, engine)
{
}

DummyTask::~DummyTask()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See DummyTask.hpp for more detailed
// documentation about them.

bool DummyTask::configureHook()
{
    if (! DummyTaskBase::configureHook())
        return false;
    return true;
}
bool DummyTask::startHook()
{
    if (! DummyTaskBase::startHook())
        return false;
    return true;
}
void DummyTask::updateHook()
{
    DummyTaskBase::updateHook();
}
void DummyTask::errorHook()
{
    DummyTaskBase::errorHook();
}
void DummyTask::stopHook()
{
    DummyTaskBase::stopHook();
}
void DummyTask::cleanupHook()
{
    DummyTaskBase::cleanupHook();
}
