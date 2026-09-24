module DisplayClock(
	input logic clock,
	input logic reset_n,
	output logic [6:0] Seg0,
	output logic [6:0] Seg1,
	output logic [6:0] Seg2,
	output logic [6:0] Seg3,
	output logic [6:0] Seg4,
	output logic [6:0] Seg5,
	output logic [1:0] decimals
);

assign decimals = 2'b00;

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

Decimal14Segment secondDisplay(
	.digits(seconds),
	.segOnes(Seg0),
	.segTens(Seg1)
);

Decimal14Segment minuteDisplay(
	.digits(minutes),
	.segOnes(Seg2),
	.segTens(Seg3)
);

Decimal14Segment #(.N(5)) hourDisplay(
	.digits(hours),
	.segOnes(Seg4),
	.segTens(Seg5)
);

endmodule