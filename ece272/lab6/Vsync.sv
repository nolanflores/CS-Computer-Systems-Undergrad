module Vsync(
    input logic clock,
    input logic enable_n,
    input logic reset_n,
    input logic Hsync_clear,//high at the end of every horizontal line
    output logic Vsync,
	 output logic Vdisplay
);

//there are a couple of inconsistencies with Hsync, but it works, and I don't want to break it :)

logic clear_n;

logic Vsync_ns;//next states
logic Vdisplay_ns;

logic [9:0] Vcount;

Counter #(.N(10)) vcounter (//also going to move this upward next lab
    .clock(clock),
    .enable_n(~Hsync_clear),//count every line(is incrementing when enable_n goes high)
    .reset_n(reset_n),
    .clear_n(clear_n),
    .count(Vcount)
);

always_comb begin
	clear_n = ~((Vcount == 10'd524) & Hsync_clear);//end of lines
	Vsync_ns = Vsync;//states stay the same
	Vdisplay_ns = Vdisplay;
	if(Vcount == 10'd524)//start of sync(end of lines)
		Vsync_ns = 1'b0;
	else if(Vcount == 10'd1)//end of sync
		Vsync_ns = 1'b1;
	else if(Vcount == 10'd35)//start of display interval
		Vdisplay_ns = 1'b1;
	else if(Vcount == 10'd515)//end of display interval
		Vdisplay_ns = 1'b0;
end

always_ff @(posedge clock or negedge reset_n) begin
	if(reset_n == 1'b0)begin
		Vsync <= 1'b0;
		Vdisplay <= 1'b0;
	end else begin
		Vsync <= Vsync_ns;//update the states
		Vdisplay <= Vdisplay_ns;
	end
end

endmodule
