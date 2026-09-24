module Vsync(
	input logic [9:0] vcount,
	output logic vsync,
	output logic vdisplay
);

always_comb begin
	if(vcount < 10'd2)
		vsync = 1'b0;
	else
		vsync = 1'b1;
	if(vcount < 10'd35 || vcount > 10'd514)
		vdisplay = 1'b0;
	else
		vdisplay = 1'b1;
end

endmodule