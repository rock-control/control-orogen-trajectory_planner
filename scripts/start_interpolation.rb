require 'orocos'
require 'readline'
require 'matrix'
require 'rock/bundle'
require 'pry'

## Initialize orocos ##
Bundles.initialize
# Orocos.initialize
puts("starting")

Bundles.run 'trajectory_planner::JointsInterpolatorTask' => 'traj_gen' do
  #Bundles.log_all_ports
  puts("2")
  dummytraj=Bundles.get 'traj_gen'
  puts("configure")
  dummytraj.configure

  begin
    puts("3")
    dummytraj.start
   # Orocos.watch(dummytraj)
    
  ensure
    puts("4")
    dummytraj.stop
  end
  Readline::readline("Press ENTER to stop ...")
end
    
  
