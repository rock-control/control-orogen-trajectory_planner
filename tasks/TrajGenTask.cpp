/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "TrajGenTask.hpp"
#include<iostream>
#include<math.h>
#include <boost/iterator/iterator_concepts.hpp>
#include <algorithm>  
#include<trajectory_planner/joints_traj/Utils.hpp>
#include <stdlib.h> 
#include<fstream>
#include<stdio.h>

using namespace trajectory_planner;
using namespace utils;

TrajGenTask::TrajGenTask(std::string const& name)
    : TrajGenTaskBase(name)
{
}

TrajGenTask::TrajGenTask(std::string const& name, RTT::ExecutionEngine* engine)
    : TrajGenTaskBase(name, engine)
{
}

TrajGenTask::~TrajGenTask()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See TrajGenTask.hpp for more detailed
// documentation about them.

bool TrajGenTask::configureHook()
{
  std::cout<<"configureHook start"<<std::endl;
  
    if (! TrajGenTaskBase::configureHook())
        return false;
    limits=utils::initFromURDF(_robot_urdf_filepath.value());
    jointsTrajOut.resize(limits.size(),10);
    jointsTrajOut.names=limits.names;
    trajGenState=GENERATION_READY;
    userResponse=-1;
    if( state() != READY)
      state( READY );
    
    return true;
}
bool TrajGenTask::startHook()
{
    if (! TrajGenTaskBase::startHook())
        return false;
    return true;
}
void TrajGenTask::updateHook()
{
   
    int noPoints;
    base::samples::Joints jointState;
    if(_in_joints_state.readNewest(jointState)==RTT::NewData)
      _out_joints_state.write(jointState);
    
        
    if(trajGenState==GENERATION_READY)
    {
      
      if( state() != GENERATING)
	state( GENERATING );
      
      trajGenState=GENERATION_ONGOING;
      
      noPoints = _number_points.value();
      noPoints = std::min(noPoints,10);
      noPoints = std::max(noPoints, 3);
      
    
      jointsTrajOut.resize(limits.size(), noPoints);
      for(unsigned i=0; i<jointsTrajOut.getNumberOfJoints();i++)
      {
	for(unsigned j=0; j<noPoints;j++)
	{
	  if(j==0)
	  {
	    jointsTrajOut.elements[i][j].position=jointState.elements[i].position;
	  }
	  else
	  {
	    jointsTrajOut.elements[i][j].position=getRandom(limits.elements[i].min.position, limits.elements[i].max.position);
	  }
	}
      }
    
      _out_joints_traj.write(jointsTrajOut);
      
      trajGenState=GENERATION_FINISHED;
      if( trajGenState==GENERATION_FINISHED && state() != RUNNING)
	state( FINISHED );
      
      bool continueGen;
      _in_user_response.readNewest(continueGen);
    }
    bool continueGen;
    if(trajGenState==GENERATION_FINISHED && _in_user_response.readNewest(continueGen)== RTT::NewData)
    {
      //jointsTrajOut.clear();
      if(continueGen)
      {
	trajGenState=GENERATION_READY;
	if( state() != READY)
	  state( READY );
      }
      else
      {
	this->stopHook();
      }
      
    }
    
    TrajGenTaskBase::updateHook();
}
void TrajGenTask::errorHook()
{
    TrajGenTaskBase::errorHook();
}
void TrajGenTask::stopHook()
{
    TrajGenTaskBase::stopHook();
}
void TrajGenTask::cleanupHook()
{
    TrajGenTaskBase::cleanupHook();
}
