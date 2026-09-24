module ClockTestbench();

logic clock;
logic reset_n;
logic [5:0] seconds;
logic [5:0] minutes;
logic [4:0] hours;

always begin
    clock = 1'b1;
    #5;
    clock = 1'b0;
    #5;
end

Clock #(.T('d5)) dut(
	.clock(clock),
	.reset_n(reset_n),
	.seconds(seconds),
	.minutes(minutes),
	.hours(hours)
);

initial begin
    $display("=== Start of Simulation ===");

    /* Set initial values of testbench-controlled signals. */
    reset_n = 1'b0;
	 #8;
	 reset_n = 1'b1;
	 #2;

    for(int h = 0; h < 24; h++) begin
		for(int m = 0; m < 60; m++) begin
			for(int s = 0; s < 60; s++)begin
				#20;
				if(seconds !== s || minutes !== m || hours !== h)
						$display("%0t ps: clock failed: expected=%2d:%2d:%2d  actual=%2d:%2d:%2d", $time, h,m,s, hours,minutes,seconds);
				#40;
			end
		end
	 end

    $display("=== End of Simulation ===");
    $stop();
end

endmodule