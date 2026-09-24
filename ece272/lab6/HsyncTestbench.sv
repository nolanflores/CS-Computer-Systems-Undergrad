module HsyncTestbench();

//This file was just so I could make sure the prelab files worked

logic clock;
logic reset_n;
logic Hsync;
logic Vsync;
logic Hdisplay;
logic Vdisplay;

logic [1:0] redControl;
logic [1:0] greenControl;
logic [1:0] blueControl;

logic [3:0] redDisplay;
logic [3:0] greenDisplay;
logic [3:0] blueDisplay;

always begin
	clock = 1'b1;
	#5;
	clock = 1'b0;
	#5;
end

VgaDriver dut(
	.clock(clock),
	.reset_n(reset_n),
	.Vsync(Vsync),
	.Hsync(Hsync),
	.Hdisplay(Hdisplay),
	.Vdisplay(Vdisplay),
	.redDisplay(redDisplay),
	.greenDisplay(greenDisplay),
	.blueDisplay(blueDisplay),
	.redControl(redControl),
	.greenControl(greenControl),
	.blueControl(blueControl)
);

initial begin
    $display("=== Start of Simulation ===");

    /* Set initial values of testbench-controlled signals. */
    reset_n = 1'b0;
	 #10;
	 reset_n = 1'b1;

    for(int cycles = 0; cycles < 525; cycles++) begin
		for(int i = 0; i < 800; i++) begin
			if(i < 96 && Hsync == 1'b1)begin
				//$display("%0t ps: invalid Hsync value at count=%0d: expected=0  actual=%0b", $time, count, Hsync);
			end
			if(i >= 96 && Hsync == 1'b0) begin
				//$display("%0t ps: invalid Hsync value at count=%0d: expected=1  actual=%0b", $time, count, Hsync);
			end
			#20;
		end
	 end

    $display("=== End of Simulation ===");
    $stop();
end

endmodule