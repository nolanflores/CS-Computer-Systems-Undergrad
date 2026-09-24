// Copyright (C) 2025  Altera Corporation. All rights reserved.
// Your use of Altera Corporation's design tools, logic functions 
// and other software and tools, and any partner logic 
// functions, and any output files from any of the foregoing 
// (including device programming or simulation files), and any 
// associated documentation or information are expressly subject 
// to the terms and conditions of the Altera Program License 
// Subscription Agreement, the Altera Quartus Prime License Agreement,
// the Altera IP License Agreement, or other applicable license
// agreement, including, without limitation, that your use is for
// the sole purpose of programming logic devices manufactured by
// Altera and sold by Altera or its authorized distributors.  Please
// refer to the Altera Software License Subscription Agreements 
// on the Quartus Prime software download page.

// PROGRAM		"Quartus Prime"
// VERSION		"Version 24.1std.0 Build 1077 03/04/2025 SC Lite Edition"
// CREATED		"Tue Apr 22 15:06:46 2025"

module SevenSegmentDisplay(
	digit,
	segments
);


input wire	[3:0] digit;
output wire	[6:0] segments;

wire	[3:0] Ndigit;
wire	[6:0] segments_ALTERA_SYNTHESIZED;
wire	SYNTHESIZED_WIRE_0;
wire	SYNTHESIZED_WIRE_1;
wire	SYNTHESIZED_WIRE_2;
wire	SYNTHESIZED_WIRE_3;
wire	SYNTHESIZED_WIRE_4;
wire	SYNTHESIZED_WIRE_5;
wire	SYNTHESIZED_WIRE_6;
wire	SYNTHESIZED_WIRE_7;
wire	SYNTHESIZED_WIRE_8;
wire	SYNTHESIZED_WIRE_9;
wire	SYNTHESIZED_WIRE_10;
wire	SYNTHESIZED_WIRE_11;
wire	SYNTHESIZED_WIRE_12;
wire	SYNTHESIZED_WIRE_13;
wire	SYNTHESIZED_WIRE_14;
wire	SYNTHESIZED_WIRE_15;
wire	SYNTHESIZED_WIRE_16;
wire	SYNTHESIZED_WIRE_17;
wire	SYNTHESIZED_WIRE_18;
wire	SYNTHESIZED_WIRE_19;
wire	SYNTHESIZED_WIRE_20;
wire	SYNTHESIZED_WIRE_21;
wire	SYNTHESIZED_WIRE_22;
wire	SYNTHESIZED_WIRE_23;
wire	SYNTHESIZED_WIRE_24;




assign	segments_ALTERA_SYNTHESIZED[5] = SYNTHESIZED_WIRE_0 | SYNTHESIZED_WIRE_1 | SYNTHESIZED_WIRE_2 | SYNTHESIZED_WIRE_3;

assign	Ndigit[0] =  ~digit[0];

assign	Ndigit[3] =  ~digit[3];

assign	segments_ALTERA_SYNTHESIZED[0] = SYNTHESIZED_WIRE_4 | SYNTHESIZED_WIRE_5 | SYNTHESIZED_WIRE_6 | SYNTHESIZED_WIRE_7;

assign	SYNTHESIZED_WIRE_4 = Ndigit[3] & Ndigit[2] & Ndigit[1] & digit[0];

assign	SYNTHESIZED_WIRE_21 = digit[3] & digit[2] & Ndigit[0];

assign	SYNTHESIZED_WIRE_7 = Ndigit[3] & digit[2] & Ndigit[1] & Ndigit[0];

assign	SYNTHESIZED_WIRE_5 = digit[3] & digit[2] & Ndigit[1] & digit[0];

assign	SYNTHESIZED_WIRE_6 = digit[3] & Ndigit[2] & digit[1] & digit[0];

assign	SYNTHESIZED_WIRE_17 = Ndigit[3] & digit[0];

assign	SYNTHESIZED_WIRE_24 = digit[3] & digit[1] & digit[0];

assign	segments_ALTERA_SYNTHESIZED[2] = SYNTHESIZED_WIRE_8 | SYNTHESIZED_WIRE_9 | SYNTHESIZED_WIRE_10;

assign	SYNTHESIZED_WIRE_10 = Ndigit[3] & Ndigit[2] & digit[1] & Ndigit[0];

assign	SYNTHESIZED_WIRE_22 = digit[2] & digit[1] & Ndigit[0];

assign	SYNTHESIZED_WIRE_9 = digit[3] & digit[2] & Ndigit[0];

assign	segments_ALTERA_SYNTHESIZED[3] = SYNTHESIZED_WIRE_11 | SYNTHESIZED_WIRE_12 | SYNTHESIZED_WIRE_13 | SYNTHESIZED_WIRE_14;

assign	SYNTHESIZED_WIRE_13 = Ndigit[2] & Ndigit[1] & digit[0];

assign	SYNTHESIZED_WIRE_12 = digit[2] & digit[1] & digit[0];

assign	SYNTHESIZED_WIRE_11 = Ndigit[3] & digit[2] & Ndigit[1] & Ndigit[0];

assign	segments_ALTERA_SYNTHESIZED[4] = SYNTHESIZED_WIRE_15 | SYNTHESIZED_WIRE_16 | SYNTHESIZED_WIRE_17;

assign	SYNTHESIZED_WIRE_16 = Ndigit[2] & Ndigit[1] & digit[0];

assign	SYNTHESIZED_WIRE_15 = Ndigit[3] & digit[2] & Ndigit[1];

assign	SYNTHESIZED_WIRE_1 = Ndigit[3] & Ndigit[2] & digit[1];

assign	segments_ALTERA_SYNTHESIZED[6] = SYNTHESIZED_WIRE_18 | SYNTHESIZED_WIRE_19 | SYNTHESIZED_WIRE_20;

assign	SYNTHESIZED_WIRE_2 = Ndigit[3] & digit[1] & digit[0];

assign	SYNTHESIZED_WIRE_0 = digit[3] & digit[2] & Ndigit[1] & digit[0];

assign	SYNTHESIZED_WIRE_20 = digit[3] & digit[2] & Ndigit[1] & Ndigit[0];

assign	SYNTHESIZED_WIRE_18 = Ndigit[3] & digit[2] & digit[1] & digit[0];

assign	SYNTHESIZED_WIRE_19 = Ndigit[3] & Ndigit[2] & Ndigit[1];

assign	SYNTHESIZED_WIRE_23 = Ndigit[3] & digit[2] & Ndigit[1] & digit[0];

assign	SYNTHESIZED_WIRE_8 = digit[3] & digit[2] & digit[1];

assign	SYNTHESIZED_WIRE_14 = digit[3] & Ndigit[2] & digit[1] & Ndigit[0];

assign	segments_ALTERA_SYNTHESIZED[1] = SYNTHESIZED_WIRE_21 | SYNTHESIZED_WIRE_22 | SYNTHESIZED_WIRE_23 | SYNTHESIZED_WIRE_24;

assign	SYNTHESIZED_WIRE_3 = Ndigit[3] & Ndigit[2] & digit[0];

assign	Ndigit[1] =  ~digit[1];

assign	Ndigit[2] =  ~digit[2];

assign	segments = segments_ALTERA_SYNTHESIZED;

endmodule
