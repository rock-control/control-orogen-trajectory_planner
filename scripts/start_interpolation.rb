require 'orocos'
require 'readline'
require 'matrix'
require 'rock/bundle'
require 'pry'

  ## Initialize orocos ##
  Bundles.initialize
 # Orocos.initialize
  puts("starting")

  Bundles.run'trajectory_planner::DummyTask'=>'traj_gen' do

    dummytraj=Bundles.get'traj_gen'
    puts("configure")
    dummytraj.configure

    begin
      
      dummytraj.start
      Orocos.watch(dummytraj)
      
    ensure
      dummytraj.stop
    end
  
  end
    
  
