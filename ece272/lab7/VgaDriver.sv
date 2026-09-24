module VgaDriver(
	input logic clock,
	input logic reset_n,
	input logic [11:0] display_color,
	output logic hsync,
	output logic vsync,
	output logic [11:0] rgb_out
);

logic hdisplay;
logic vdisplay;

logic display_image;
logic [9:0] hcount;
logic [9:0] vcount;
logic [15:0] pixel_address;
logic [15:0] pixel;

SyncCount sc(
	.clock(clock),
	.reset_n(reset_n),
	.hsync(hsync),
	.vsync(vsync),
	.hdisplay(hdisplay),
	.vdisplay(vdisplay),

	.hcount(hcount),
	.vcount(vcount)
);

AddressDecode ad(
	.row(hcount),
	.column(vcount),
	.display_image(display_image),
	.pixel_address(pixel_address)
);

rom r(
	.clock(clock),
	.address(pixel_address),
	.q(pixel)
);

always_comb begin
	if(hdisplay == 1'b1 & vdisplay == 1'b1)
		if(display_image)
			rgb_out = pixel[15:4];
		else
			rgb_out = display_color;
	else
		rgb_out = 12'd0;
end


endmodule