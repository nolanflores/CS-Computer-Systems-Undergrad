/*
 * ECE 272 Lab 3b
 * Seven Segment Decoder Skeleton File
 *
 * Adapted from Harris & Harris "Digital Design and Computer Achitecture"
 * Example 4.25 "Seven-Segment Display Decoder" (Page 198)
 *
 * Author(s): Quinn Yockey
 * Last Modified: 21 February 2025
 */

/* IMPORTANT!  Read the comments carefully.  They are included to help you!  */

/*
 * Instructions:
 *     Tasks are marked with a number in brackets (e.g., [1]). Each has a
 *     corresponding TODO comment to replace with SystemVerilog code.
 */

/*
 * Declare a module named `SevenSegmentDecode` to convert a 4-bit hexadecimal
 * number to a 7-bit binary value to output on a 7 segment display.
 *
 * [1] Add a 7-bit logic output named `segments` to the `SevenSegmentDecode`
 *     module.
 */
module SevenSegmentDecode(
    input logic [3:0] digit,
    output logic [6:0] segments
);

/*
 * Using the `always_comb` keyword, create a block that only allows
 * combinational logic.  This is necessary for the `case` statement used within.
 *
 * Like a `switch` statement in C and other programming languages, the `case`
 * statement in SystemVerilog matches the value of the argument to determine
 * what happens next.  In the given branch, if the value of `digit` is 0x0, then
 * use non-blocking assignment to set the value of `segments` to 0b100_0000.
 *
 * Remember that the seven segment displays on the DE10-lite FPGA are active
 * low, so a segment set to 1 will be off and a 0 will be on.  Also, the
 * `segments` has segment a as bit 0 (rightmost) and segment g as bit
 * 6 (leftmost).
 *
 * Refresher on numerical prefixes in SystemVerilog:
 * - 4'h: number is 4 bits wide and formatted in hexadecimal.
 *       (e.g.: 4'h5 = 0x5 = 0b0101 = 5; 4'hC = 0xC = 0b1100 = 12)
 * - 7'b: number is 7 bits wide and formatted in binary.
 *
 * [2] Add branches for the remaining values from 0x1 to 0xF using the values
 *     you listed in figure 3.3 in Lab 3.
 */
always_comb begin
    case (digit)
        //                   gfe_dcba
        4'h0: segments <= 7'b100_0000;
		  4'h1: segments <= 7'b111_1001;
		  4'h2: segments <= 7'b010_0100;
		  4'h3: segments <= 7'b011_0000;
		  4'h4: segments <= 7'b001_1001;
		  4'h5: segments <= 7'b001_0010;
		  4'h6: segments <= 7'b000_0010;
		  4'h7: segments <= 7'b111_1000;
		  4'h8: segments <= 7'b000_0000;
		  4'h9: segments <= 7'b001_1000;
		  4'hA: segments <= 7'b000_1000;
		  4'hB: segments <= 7'b000_0011;
		  4'hC: segments <= 7'b100_0110;
		  4'hD: segments <= 7'b010_0001;
		  4'hE: segments <= 7'b000_0110;
        4'hF: segments <= 7'b000_1110;
    endcase
end

endmodule

