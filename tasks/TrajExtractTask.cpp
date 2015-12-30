/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "TrajExtractTask.hpp"
#include <base/JointLimits.hpp>
#include<utils/ReadJointLimits.hpp>

using namespace trajectory_planner;

TrajExtractTask::TrajExtractTask(std::string const& name)
    : TrajExtractTaskBase(name)
{
}

TrajExtractTask::TrajExtractTask(std::string const& name, RTT::ExecutionEngine* engine)
    : TrajExtractTaskBase(name, engine)
{
}

TrajExtractTask::~TrajExtractTask()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See TrajExtractTask.hpp for more detailed
// documentation about them.

bool TrajExtractTask::configureHook()
{
    if (! TrajExtractTaskBase::configureHook())
        return false;
    currTimeStep=0;
    totalTimeStep=0;
    extractState=WAITING_FOR_DATA;
    
    base::JointLimits limits= utils::initFromURDF("/home/dfki.uni-bremen.de/rmenon/software/rock_traj/bundles/kuka_lbr/data/urdf/kuka_lbr_left_arm.urdf");
    jointSamples.resize(limits.size());
    
    if( state() != WAITING_FOR_TRAJ)
      state( WAITING_FOR_TRAJ );
    return true;
}
bool TrajExtractTask::startHook()
{
    if (! TrajExtractTaskBase::startHook())
        return false;
    return true;
}
void TrajExtractTask::updateHook()
{   
    
  if(extractState==WAITING_FOR_DATA && _in_joints_traj.readNewest(jointsTraj)==RTT::NewData)
  {
    if( state() != EXTRACTING_TRAJ)
      state(EXTRACTING_TRAJ);
    extractState=EXTRACTING;
    totalTimeStep=jointsTraj.getTimeSteps();
  }
  if(extractState==EXTRACTING)
  {
    if(currTimeStep<totalTimeStep)
    {
      jointsTraj.getJointsAtTimeStep(currTimeStep,jointSamples);
      _out_joints_sample.write(jointSamples);
      _out_time_step.write(currTimeStep);
      currTimeStep++;
    }
    else
    {
      extractState=WAITING_FOR_DATA;
      if( state() != WAITING_FOR_TRAJ)
	state( WAITING_FOR_TRAJ );
      
      currTimeStep=0;
    }
  }
    TrajExtractTaskBase::updateHook();
}
void TrajExtractTask::errorHook()
{
    TrajExtractTaskBase::errorHook();
}
void TrajExtractTask::stopHook()
{
    TrajExtractTaskBase::stopHook();
}
void TrajExtractTask::cleanupHook()
{
    TrajExtractTaskBase::cleanupHook();
}
