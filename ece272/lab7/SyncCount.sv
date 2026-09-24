module SyncCount(
	input logic clock,
	input logic reset_n,
	output logic hsync,
	output logic vsync,
	output logic hdisplay,
	output logic vdisplay,
	
	output logic [9:0] hcount,
	output logic [9:0] vcount
);

logic enable_n;

//logic [9:0] hcount;
logic hclear;
assign hclear = (hcount == 799) & ~enable_n;

//logic [9:0] vcount;
logic vclear;
assign vclear = (vcount == 524) & hclear;

ToggleClock enable_clk(
	.clock(clock),
	.reset_n(reset_n),
	.enable_n(enable_n)
);

Counter #(.N(10)) hcounter(
	.clock(clock),
	.enable_n(enable_n),
	.reset_n(reset_n),
	.count(hcount),
	.clear_n(~hclear)
);

Counter #(.N(10)) vcounter(
	.clock(clock),
	.enable_n(~hclear),
	.reset_n(reset_n),
	.count(vcount),
	.clear_n(~vclear)
);

Hsync h(
	.hcount(hcount),
	.hsync(hsync),
	.hdisplay(hdisplay)
);

Vsync v(
	.vcount(vcount),
	.vsync(vsync),
	.vdisplay(vdisplay)
);



endmodule