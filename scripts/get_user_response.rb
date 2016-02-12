require 'orocos'
require 'readline'
require 'rock/bundle'

Bundles.initialize
dummytraj= Bundles.get 'traj_gen'
writer = dummytraj.in_user_response.writer
while true
  puts "Enter y/n for continuing or stopping resp."
  STDOUT.flush
  val = gets.chomp
  if val == "y" || val == "Y" 
    puts "Accepting exp"
    writer.write true
  elsif val == "n" || val == "N"
    puts "Rejecting exp"
    writer.write false
  else
    puts "Not valid input. Try again "
  end
end
