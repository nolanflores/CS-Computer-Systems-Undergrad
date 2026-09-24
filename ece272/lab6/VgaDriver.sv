module VgaDriver(
	input logic clock,
	input logic reset_n,
	input logic [1:0] redControl,
	input logic [1:0] greenControl,
	input logic [1:0] blueControl,
	output logic Hsync,
	output logic Vsync,
	output logic [3:0] redDisplay,
	output logic [3:0] greenDisplay,
	output logic [3:0] blueDisplay
);

logic Hdisplay;//high when displaying colors
logic Vdisplay;

logic enable_n;//active low every other clock cycle
logic Hsync_clear;//high at the end of every horizontal line

ToggleClock tc(
	.clock(clock),
	.reset_n(reset_n),
	.enable_n(enable_n)
);

Hsync hs(
	.clock(clock),
	.enable_n(enable_n),
	.reset_n(reset_n),
	.Hsync_clear(Hsync_clear),
	.Hsync(Hsync),
	.Hdisplay(Hdisplay)
);

Vsync vs(
	.clock(clock),
	.enable_n(enable_n),
	.reset_n(reset_n),
	.Hsync_clear(Hsync_clear),
	.Vsync(Vsync),
	.Vdisplay(Vdisplay)
);

ColorDriver red(
	.control(redControl),
	.Hdisplay(Hdisplay),
	.Vdisplay(Vdisplay),
	.display(redDisplay)
);

ColorDriver green(
	.control(greenControl),
	.Hdisplay(Hdisplay),
	.Vdisplay(Vdisplay),
	.display(greenDisplay)
);

ColorDriver blue(
	.control(blueControl),
	.Hdisplay(Hdisplay),
	.Vdisplay(Vdisplay),
	.display(blueDisplay)
);


endmodule