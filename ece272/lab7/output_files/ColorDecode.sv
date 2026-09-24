module ColorDecode(
	input [1:0] r_in,
	input [1:0] g_in,
	input [1:0] b_in,
	output logic [11:0] rgb_out
);

always_comb begin
	case (r_in)
		2'b00: rgb_out[11:8] = 4'b0000;
		2'b01: rgb_out[11:8] = 4'b0101;
		2'b10: rgb_out[11:8] = 4'b1010;
		2'b11: rgb_out[11:8] = 4'b1111;
	endcase
	case (g_in)
		2'b00: rgb_out[7:4] = 4'b0000;
		2'b01: rgb_out[7:4] = 4'b0101;
		2'b10: rgb_out[7:4] = 4'b1010;
		2'b11: rgb_out[7:4] = 4'b1111;
	endcase
	case (b_in)
		2'b00: rgb_out[3:0] = 4'b0000;
		2'b01: rgb_out[3:0] = 4'b0101;
		2'b10: rgb_out[3:0] = 4'b1010;
		2'b11: rgb_out[3:0] = 4'b1111;
	endcase
end

endmodule