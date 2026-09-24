# Clear any current simulations
restart -force -nowave
delete wave *

# Add in waveforms
add wave clk
add wave reset
add wave nickel
add wave dime
add wave quarter
add wave refund
add wave vend
add wave nickel_out
add wave dime_out
add wave quarter_out
add wave money

#Create a repeating clock of 1S
force sim:/VendingMachineTop/clk 0 0, 1 500ms -repeat 1000ms

#Set initial input values
force sim:/VendingMachineTop/nickel 0
force sim:/VendingMachineTop/dime 0
force sim:/VendingMachineTop/quarter 0
force sim:/VendingMachineTop/refund 0

# Force asynchronous reset for 10pS and run for 100ps more. 
# This should be wait for 3 cycles before moving to TB direction
force sim:/VendingMachineTop/reset 1
run 250 mS
force sim:/VendingMachineTop/reset 0
run 1000ms

# This sequence deposits 10 nickels so we should see a vend activation at the end
force sim:/VendingMachineTop/nickel 1
run 10000ms
force sim:/VendingMachineTop/nickel 0
run 1000ms
run 1000ms
run 1000ms

# This sequence deposits 5 nickels then a refund activation. We should see a refund totaling $0.25
force sim:/VendingMachineTop/nickel 1
run 1000ms
force sim:/VendingMachineTop/nickel 0
run 1000ms
force sim:/VendingMachineTop/nickel 1
run 1000ms
force sim:/VendingMachineTop/nickel 0
run 1000ms
force sim:/VendingMachineTop/nickel 1
run 1000ms
force sim:/VendingMachineTop/nickel 0
run 1000ms
force sim:/VendingMachineTop/nickel 1
run 1000ms
force sim:/VendingMachineTop/nickel 0
run 1000ms
force sim:/VendingMachineTop/nickel 1
run 1000ms
force sim:/VendingMachineTop/nickel 0
run 1000ms

force sim:/VendingMachineTop/refund 1
run 1000ms
force sim:/VendingMachineTop/refund 0
run 6000ms