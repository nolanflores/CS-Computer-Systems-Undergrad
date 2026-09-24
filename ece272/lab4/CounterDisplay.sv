module CounterDisplay(
	input logic clock,
	input logic clear_n,
	input logic [3:0] addBy,
	output logic [6:0] Seg0
);

logic [3:0] count;

Counter(
	.clock(clock),
	.clear_n(clear_n),
	.addBy(addBy),
	.count(count)
);

SevenSegmentDecode(
	.digit(count),
	.segments(Seg0)
);


endmodule