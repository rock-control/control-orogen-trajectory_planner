/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "TrajGenOnlineTask.hpp"
#include<trajectory_planner/joints_traj/Utils.hpp>

using namespace trajectory_planner;

TrajGenOnlineTask::TrajGenOnlineTask(std::string const& name)
    : TrajGenOnlineTaskBase(name)
{
}

TrajGenOnlineTask::TrajGenOnlineTask(std::string const& name, RTT::ExecutionEngine* engine)
    : TrajGenOnlineTaskBase(name, engine)
{
}

TrajGenOnlineTask::~TrajGenOnlineTask()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See TrajGenOnlineTask.hpp for more detailed
// documentation about them.

bool TrajGenOnlineTask::configureHook()
{
    if (! TrajGenOnlineTaskBase::configureHook())
        return false;
    
    limits=utils::initFromURDF(_robot_urdf_filepath.value());
    jointsTrajOut.names=limits.names;
    trajGenState=GENERATION_READY;
    
    useActualPosition=_use_actual_position_starting.value();
    singlePointTrajectory=_single_trajectory_point.value();
    
    if(singlePointTrajectory)
    {
      jointsTrajOut.resize(limits.size(), 4);
      useActualPosition=1;
    }
    else
      jointsTrajOut.resize(limits.size(),10);
    
    if( state() != READY)
      state( READY );
    
    return true;
}
bool TrajGenOnlineTask::startHook()
{
    if (! TrajGenOnlineTaskBase::startHook())
        return false;
    return true;
}
void TrajGenOnlineTask::updateHook()
{
    TrajGenOnlineTaskBase::updateHook();
    
    base::samples::Joints jointState;
    base::commands::Joints jointCommand;
    base::JointsTrajectory jointsTrajectory;
    
    if(_in_joints_state.readNewest(jointState)==RTT::NewData)
      _out_joints_state.write(jointState);
    
    if(trajGenState==GENERATION_READY)
    {
      
            
      if(singlePointTrajectory)
      {	
	if(_in_joints_command.readNewest(jointCommand)==RTT::NewData)
	{
	  if( state() != GENERATING)
	    state( GENERATING );
	  
	  trajGenState=GENERATION_ONGOING;
	  
	  for(unsigned i=0; i<jointsTrajOut.getNumberOfJoints();i++)
	  {
	    jointsTrajOut.elements[i][0].position=jointState.elements[i].position;
	    jointsTrajOut.elements[i][1].position=0.67*jointState.elements[i].position+0.33*jointCommand.elements[i].position;
	    jointsTrajOut.elements[i][2].position=0.33*jointState.elements[i].position+0.67*jointCommand.elements[i].position;
	    jointsTrajOut.elements[i][3].position=jointCommand.elements[i].position;
	  }
	  
	  _out_joints_traj.write(jointsTrajOut);
	  trajGenState=GENERATION_FINISHED;
	}
      }
      
      else
      {
	if(_in_joints_trajectory.readNewest(jointsTrajectory)==RTT::NewData)
	{
	  if( state() != GENERATING)
	    state( GENERATING );
	  
	  trajGenState=GENERATION_ONGOING;
	  
	  if(useActualPosition)
	  {
	    jointsTrajOut.resize(limits.size(), jointsTrajectory.size()+1);
	    
	    for(unsigned i=0; i<jointsTrajOut.getNumberOfJoints();i++)
	    {
	      for(unsigned j=0; j<jointsTrajOut.names.size();j++)
	      {
		if(j==0)
		{
		  jointsTrajOut.elements[i][j].position=jointState.elements[i].position;
		}
		else
		{
		  jointsTrajOut.elements[i][j].position= jointsTrajectory.elements[i][j-1].position;
		}
	      }
	    }
	  }
	  
	  else
	  {
	    jointsTrajOut=jointsTrajectory;
	  }
	  
	  _out_joints_traj.write(jointsTrajOut);
	  trajGenState=GENERATION_READY;
	}
      }
    }
    
    if( trajGenState==GENERATION_READY && state() != READY)
      state( READY );
    
    
}
void TrajGenOnlineTask::errorHook()
{
    TrajGenOnlineTaskBase::errorHook();
}
void TrajGenOnlineTask::stopHook()
{
    TrajGenOnlineTaskBase::stopHook();
}
void TrajGenOnlineTask::cleanupHook()
{
    TrajGenOnlineTaskBase::cleanupHook();
}
