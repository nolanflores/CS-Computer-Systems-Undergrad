module ImageDriver(
	input logic clock,
	input logic reset_n,
	input logic [1:0] r_in,
	input logic [1:0] g_in,
	input logic [1:0] b_in,
	output logic hsync,
	output logic vsync,
	output logic [11:0] rgb_out
);

logic [11:0] display_color;

ColorDecode cd(
	.r_in(r_in),
	.g_in(g_in),
	.b_in(b_in),
	.rgb_out(display_color)
);

VgaDriver vga(
	.clock(clock),
	.reset_n(reset_n),
	.display_color(display_color),
	.hsync(hsync),
	.vsync(vsync),
	.rgb_out(rgb_out)
);


endmodule