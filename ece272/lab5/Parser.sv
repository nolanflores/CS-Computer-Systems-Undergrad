module Parser #(parameter N = 6)(
	input logic [N-1:0] digits,
	output logic [3:0] ones,
	output logic [3:0] tens
);

assign ones = digits % 10;
assign tens = digits / 10;

endmodule