/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "DummyTask.hpp"
#include<iostream>
#include<math.h>
#include <boost/iterator/iterator_concepts.hpp>
#include <algorithm>  
#include<utils/MyMath.hpp>
#include<utils/ReadJointLimits.hpp>
#include <stdlib.h> 

using namespace trajectory_planner;
using namespace utils;

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
{    std::cout<<"configureHook start"<<std::endl;
    if (! DummyTaskBase::configureHook())
        return false;
    std::cout<<"configureHook start 2"<<std::endl;
    limits=utils::initFromURDF("/home/dfki.uni-bremen.de/rmenon/software/rock_traj/bundles/kuka_lbr/data/urdf/kuka_lbr_left_arm.urdf");
    jointsTrajOut.resize(limits.size(),10);
    jointsTrajOut.names=limits.names;
    trajGenState=GENERATION_READY;
    userResponse=-1;
    
    std::cout<<"configureHook stop"<<std::endl;
    
    return true;
}
bool DummyTask::startHook()
{
    if (! DummyTaskBase::startHook())
        return false;
    std::cout<<"startHook"<<std::endl;
    return true;
}
void DummyTask::updateHook()
{
    DummyTaskBase::updateHook();
    int noPoints;
    
    std::cout<<"Entering updateHook"<<std::endl;
   
    if(trajGenState==GENERATION_READY)
    {
      std::cout<<"Enter number of trajectory points to be created"<<std::endl;
      std::cin>>noPoints;
      noPoints=std::min(noPoints,10);
      jointsTrajOut.resize(limits.size(), noPoints);
      for(unsigned i=0; i<jointsTrajOut.getNumberOfJoints();i++)
      {
	for(unsigned j=0; j<noPoints;j++)
	{
	  jointsTrajOut.elements[i][j].position=getRandom(limits.elements[i].min.position, limits.elements[i].max.position);
	}
      }
      _out_joint_traj.write(jointsTrajOut);
      
      trajGenState=GENERATION_FINISHED;
      bool continueGen;
      _in_user_response.readNewest(continueGen);
    }
    bool continueGen;
    if(trajGenState==GENERATION_FINISHED && _in_user_response.readNewest(continueGen)== RTT::NewData)
    {
      if(continueGen)
      {
	trajGenState=GENERATION_READY;
	std::cout<<"Entering trajectory generation phase"<<std::endl;
      }
      else
      {
	std::cout<<"Exiting"<<std::endl;
	exit(0);
      }
    }
   
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
