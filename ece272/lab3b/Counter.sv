module Counter(
	input logic clock,
	input logic clear_n,
	input logic [3:0] addBy,
	output logic [3:0] count
);

logic [3:0] count_next;
assign count_next = count + addBy;

RegisterFourBit inst(
	.clock(clock),
	.clear_n(clear_n),
	.d(count_next),
	.q(count)
);

endmodule