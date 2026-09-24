module ClockDisplay(
	input logic clock,
	input logic reset_n,
	output logic [6:0] Seg0,
	output logic [6:0] Seg1,
	output logic [6:0] Seg2,
	output logic [6:0] Seg3,
	output logic [6:0] Seg4,
	output logic [6:0] Seg5
);

logic [5:0] seconds;
logic [5:0] minutes;
logic [4:0] hours;

Clock clk(
	.clock(clock),
	.reset_n(reset_n),
	.hours(hours),
	.minutes(minutes),
	.seconds(seconds)
);

logic [4:0] secOnes;
logic [4:0] secTens;
logic [4:0] minOnes;
logic [4:0] minTens;
logic [4:0] hourOnes;
logic [4:0] hourTens;

Parser sec(
	.digits(seconds),
	.ones(secOnes),
	.tens(secTens)
);
Parser min(
	.digits(minutes),
	.ones(minOnes),
	.tens(minTens)
);
Parser hour(
	.digits(hours),
	.ones(hourOnes),
	.tens(hourTens)
);


SevenSegmentDecode secOnesDisplay(
	.digit(secOnes),
	.segments(Seg0)
);
SevenSegmentDecode secTensDisplay(
	.digit(secTens),
	.segments(Seg1)
);
SevenSegmentDecode minOnesDisplay(
	.digit(minOnes),
	.segments(Seg2)
);
SevenSegmentDecode minTensDisplay(
	.digit(minTens),
	.segments(Seg3)
);
SevenSegmentDecode hourOnesDisplay(
	.digit(hourOnes),
	.segments(Seg4)
);
SevenSegmentDecode hourTensDisplay(
	.digit(hoursTens),
	.segments(Seg5)
);

endmodule