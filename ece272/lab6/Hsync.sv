module Hsync(
	input logic clock,
	input logic enable_n,
	input logic reset_n,
	output logic Hsync,
	output logic Hdisplay,
	output logic Hsync_clear
);

logic [9:0] count;
logic Hsync_ns;//next states
logic Hdisplay_ns;

always_comb begin
	Hsync_clear = ((count == 10'd799) & ~enable_n);//end of line
	Hsync_ns = Hsync;//states stay the same
	Hdisplay_ns = Hdisplay;
	if (enable_n == 1'b0) begin//enabled
		if (count == 10'd0)//start of sync
			Hsync_ns = 1'b0;
		else if (count == 10'd96)//end of sync
			Hsync_ns = 1'b1;
		else if(count == 10'd143)//start of display interval
			Hdisplay_ns = 1'b1;
		else if(count == 10'd783)//end of display interval
			Hdisplay_ns = 1'b0;
	end
end

Counter #(.N(10)) counter(//Going to move this higher in the next lab
	.clock(clock),
	.enable_n(enable_n),
	.reset_n(reset_n),
	.clear_n(~Hsync_clear),
	.count(count)
);

always_ff @(posedge clock or negedge reset_n) begin
	if(reset_n == 1'b0) begin
		Hsync <= 1'b0;
		Hdisplay <= 1'b0;
	end else begin
		Hsync <= Hsync_ns;//update the states
		Hdisplay <= Hdisplay_ns;
	end
end

endmodule
