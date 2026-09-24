# restarts the simulation and destroys all previous waves.
restart -force -nowave
destroy wave *

#add in waves of interest
add wave sim:/TwoBitAdder/a
add wave sim:/TwoBitAdder/b
add wave sim:/TwoBitAdder/cin
add wave sim:/TwoBitAdder/s
add wave sim:/TwoBitAdder/cout

#Another way to make force commands that repeat
force sim:/TwoBitAdder/b[0] 0, 1 10ps -r 20ps
force sim:/TwoBitAdder/b[1] 0, 1 20ps -r 40ps
force sim:/TwoBitAdder/a[0] 0, 1 40ps -r 80ps
force sim:/TwoBitAdder/a[1] 0, 1 80ps -r 160ps
force sim:/TwoBitAdder/cin 0, 1 160ps -r 320ps


#run the simulation for 320 units (320pS)
run 320
