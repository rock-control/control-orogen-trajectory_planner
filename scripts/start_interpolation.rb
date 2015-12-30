require 'orocos'
require 'readline'
require 'matrix'
require 'rock/bundle'
require 'pry'

## Initialize orocos ##
Bundles.initialize
# Orocos.initialize
puts("starting")

Bundles.run 'trajectory_planner::TrajGenTask' => 'traj_gen',
            'trajectory_planner::JointsInterpolatorTask' => 'traj_interpol','trajectory_planner::TrajExtractTask'=> 'traj_extract'  do
  #Bundles.log_all_ports
  dispatcher=Bundles.get 'kuka_lbr_dispatcher'  
  
  puts("2")
  dummytraj = Bundles.get 'traj_gen'
  interpol  = Bundles.get 'traj_interpol'
  extract   = Bundles.get 'traj_extract'
  
  Orocos.conf.apply( interpol, ['default'] )     
  
  dummytraj.out_joints_traj.connect_to interpol.in_joints_traj
  interpol.out_joints_traj.connect_to extract.in_joints_traj
  extract.out_joints_sample.connect_to dispatcher.all_command
  dispatcher.all_joint_state.connect_to dummytraj.in_joints_state
  
  puts("configure")
  dummytraj.configure
  interpol.configure
  extract.configure

  begin
    puts("3")
    dummytraj.start
    interpol.start
    extract.start
    Orocos.watch(dummytraj, interpol, extract)
    
  ensure
    puts("4")
    dummytraj.stop
    interpol.stop
    extract.stop
  end
  
end
    
  
