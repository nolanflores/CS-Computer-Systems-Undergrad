module Hsync(
	input logic [9:0] hcount,
	output logic hsync,
	output logic hdisplay
);

always_comb begin
	if(hcount < 10'd96)
		hsync = 1'b0;
	else
		hsync = 1'b1;
	if(hcount < 10'd144 || hcount > 10'd783)
		hdisplay = 1'b0;
	else
		hdisplay = 1'b1;
end

endmodule