module ColorDriver(
	input logic [1:0] control,
	input logic Hdisplay,
	input logic Vdisplay,
	output logic [3:0] display
);

logic [3:0] d;//color to be output

always_comb begin
	//Decoder
	case(control)
		2'b00: d = 4'b0000;
		2'b01: d = 4'b0101;
		2'b10: d = 4'b1010;
		2'b11: d = 4'b1111;
	endcase
	
	//Mux
	if(Hdisplay == 1'b1 && Vdisplay == 1'b1)
		display = d;
	else
		display = 4'b0000;
end

endmodule