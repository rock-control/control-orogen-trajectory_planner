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
   
    if( state() != READY)
      state( READY );
    base::JointLimits limits=utils::initFromURDF(_robot_urdf_filepath.value());
    trajIn.resize(limits.size());
    trajIn.names=limits.names;
    
    trajOut.resize(limits.size());
    trajOut.names =limits.names;
    
    jointsTrajCurve.initialise_data(limits,_cycle_time.value(),_acc_max.value(),_speed_level.value(), _end_condition.value());
    //jointsTrajCurve.initialise_data(limits,0.005,5, 80, 0);
    
   
    
    if( state() != WAITING_FOR_SPARSE_TRAJ)
      state( WAITING_FOR_SPARSE_TRAJ );
    
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
  
  
    if(_in_joints_traj.readNewest(trajIn)==RTT::NewData)
    {
      if( state() != INTERPOLATING)
	state(INTERPOLATING);
      
      _out_time_step_sparse.write(trajIn.getTimeSteps());
      
      trajOut=jointsTrajCurve.calc_joint_traj_bezier(trajIn);
      trajOut.names=trajIn.names;
      
      _out_joints_traj.write(trajOut);
      _out_joints_traj2.write(trajIn);
      
      _out_time_step_inter.write(trajOut.getTimeSteps());
      
      if( state() != WAITING_FOR_SPARSE_TRAJ)
	state( WAITING_FOR_SPARSE_TRAJ );
    }
    
    
    
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
