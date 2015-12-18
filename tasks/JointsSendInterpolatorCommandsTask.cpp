/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "JointsSendInterpolatorCommandsTask.hpp"

using namespace trajectory_planner;

JointsSendInterpolatorCommandsTask::JointsSendInterpolatorCommandsTask(std::string const& name)
    : JointsSendInterpolatorCommandsTaskBase(name)
{
}

JointsSendInterpolatorCommandsTask::JointsSendInterpolatorCommandsTask(std::string const& name, RTT::ExecutionEngine* engine)
    : JointsSendInterpolatorCommandsTaskBase(name, engine)
{
}

JointsSendInterpolatorCommandsTask::~JointsSendInterpolatorCommandsTask()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See JointsSendInterpolatorCommandsTask.hpp for more detailed
// documentation about them.

bool JointsSendInterpolatorCommandsTask::configureHook()
{
    if (! JointsSendInterpolatorCommandsTaskBase::configureHook())
        return false;
    return true;
}
bool JointsSendInterpolatorCommandsTask::startHook()
{
    if (! JointsSendInterpolatorCommandsTaskBase::startHook())
        return false;
    return true;
}
void JointsSendInterpolatorCommandsTask::updateHook()
{
    JointsSendInterpolatorCommandsTaskBase::updateHook();
}
void JointsSendInterpolatorCommandsTask::errorHook()
{
    JointsSendInterpolatorCommandsTaskBase::errorHook();
}
void JointsSendInterpolatorCommandsTask::stopHook()
{
    JointsSendInterpolatorCommandsTaskBase::stopHook();
}
void JointsSendInterpolatorCommandsTask::cleanupHook()
{
    JointsSendInterpolatorCommandsTaskBase::cleanupHook();
}
