/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "JointsInterpolatorTask.hpp"

using namespace trajectory_planner;
using namespace std;

JointsInterpolatorTask::JointsInterpolatorTask(std::string const& name)
    : JointsInterpolatorTaskBase(name)
{
}

JointsInterpolatorTask::JointsInterpolatorTask(std::string const& name, RTT::ExecutionEngine* engine)
    : JointsInterpolatorTaskBase(name, engine)
{
}

JointsInterpolatorTask::~JointsInterpolatorTask()
{
}

/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See JointsInterpolatorTask.hpp for more detailed
// documentation about them.

bool JointsInterpolatorTask::configureHook()
{
    if (! JointsInterpolatorTaskBase::configureHook())
        return false;
    
    base::JointLimits limits=utils::initFromURDF("/home/dfki.uni-bremen.de/rmenon/software/rock_traj/bundles/kuka_lbr/data/urdf/kuka_lbr_left_arm.urdf");
    trajIn.resize(limits.size());
    trajIn.names=limits.names;
    
    trajOut.resize(limits.size());
    trajOut.names =limits.names;
    
    jointsTrajCurve.initialise_data(limits,_cycle_time.value(),_acc_max.value(),_speed_level.value(), _end_condition.value());
    
    return true;
}
bool JointsInterpolatorTask::startHook()
{
    if (! JointsInterpolatorTaskBase::startHook())
        return false;
    return true;
}
void JointsInterpolatorTask::updateHook()
{
    JointsInterpolatorTaskBase::updateHook();
    
    
}
void JointsInterpolatorTask::errorHook()
{
    JointsInterpolatorTaskBase::errorHook();
}
void JointsInterpolatorTask::stopHook()
{
    JointsInterpolatorTaskBase::stopHook();
}
void JointsInterpolatorTask::cleanupHook()
{
    JointsInterpolatorTaskBase::cleanupHook();
}
