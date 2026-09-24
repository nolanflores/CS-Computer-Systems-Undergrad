/*
 * ECE 272 Lab 3b
 * Seven Segment Testbench Skeleton File
 *
 * Adapted from Harris & Harris "Digital Design and Computer Achitecture"
 * Example 4.38 "Self-Checking Testbench" (Page 215)
 *
 * Author(s): Quinn Yockey
 * Last Modified: 21 February 2025
 */

/* IMPORTANT!  Read the comments carefully.  They are included to help you! */

/*
 * Instructions:
 *     1. Open the course textbook.  This file is based on Example 4.38,
 *        which will help you complete this exercise.
 *     2. Tasks are marked with a number in brackets (e.g., [1]). Each has a
 *        corresponding TODO comment to replace with SystemVerilog code.
 */

module SevenSegmentTestbench();

    /*
     * Create signals to connect to the SevenSegmentDecode module:
     *
     * - `digitTest`: Drives the `digit` input in SevenSegmentDecode.
     * - `segmentsMeasured`: Captures the `segments` output of SevenSegmentDecode.
     *
     * [1] Define the width of the `segmentsMeasured` signal.  Match the width
     *     of the `segments` output from SevenSegmentDecode.
     */
    logic [3:0] digitTest; // Input digit to test
    logic [6:0] segmentsMeasured; // Output measured in simulation

    /*
     * Create instance of the device under test (DUT): SevenSegmentDecode.
     *
     * The `digitTest` signal is connected to the DUT `digit` input.  This
     * allows the testbench to control the `digit` value in SevenSegmentDecode
     * by changing the value of `digitTest`.
     *
     * A signal can be connected to a module input or output port by specifying
     * the module port (ex: `digit`) and then stating the connected signal
     * (ex: `digitTest`) in parenthesis. Note that the syntax used here differs
     * from syntax used in the textbook.
     *
     * [2] Connect `segmentsMeasured` to `segments` output. This allows the
     *     testbench to read the `segments` value of SevenSegmentDecode by
     *     checking the `segmentsMeasured` signal.
     *
     * Note: For those who have taken CS classes, the syntax is similar to
     *       passing arguments in a function call.
     */
    SevenSegmentDecode dut(
        .digit(digitTest),
        .segments(segmentsMeasured)
    );

    /*
     * Testbench Overview:
     *
     * A testbench operates through a series of tests.  The idea is to validate
     * that for a given input, a module yields the correct output.
     *
     * In this case, the testbench will check each 4-bit number from 0x0 to 0xF
     * and confirm that SevenSegmentDecode module outputs the correct signals to
     * light up the 7-segment display.
     *
     * Each test has the following structure:
     *     [3] Assign a test value to `digitTest`.
     *     [4] Delay for 10 ps to allow the output to update.
     *     [5] Compare `segmentsMeasured` to the expected value of `segments`.
     *         This expected value should be hard-coded into the program.
     *     [6] Print an error message if the output is incorrect.
     *
     * Execute this process for all possible inputs 0x0 though 0xF.
     */

    // The `initial` block runs once at the start of simulation.
    initial begin

        /* === Test Case 0x0 === */

        // Assign test input value 0x0 to `digitTest`.
        // Use non-blocking assignment (`<=`).
        digitTest <= 4'h0;

        // Delay for 10 ps.  Use `#` command.
        #10;

        // Check if module output is incorrect.
        if (segmentsMeasured !== 7'b100_0000) begin

            // Display error message with test case number.
            $display("ERROR: 0 failed.");

        end


        /* === Test Case 0x1 === */

        // Assign test input value 0x1 to `digitTest`.
        digitTest <= 4'h1;

        // Delay for 10 ps.
        #10;

        // Check if module output is incorrect.
        if (segmentsMeasured !== 7'b111_1001) begin

            // Display error message with test case number.
            $display("ERROR: 1 failed.");

        end
		  
		  
		  /* === Test Case 0x2 === */
		  
        digitTest <= 4'h2;
        #10;
        if (segmentsMeasured !== 7'b010_0100) begin
            $display("ERROR: 2 failed.");
        end
		  		  
		  
		  /* === Test Case 0x3 === */
		  
        digitTest <= 4'h3;

        #10;

        if (segmentsMeasured !== 7'b011_0000) begin

            $display("ERROR: 3 failed.");

        end
		  		  
		  
		  /* === Test Case 0x4 === */
		  
        digitTest <= 4'h4;

        #10;

        if (segmentsMeasured !== 7'b001_1001) begin

            $display("ERROR: 4 failed.");

        end
		  		  
		  
		  /* === Test Case 0x5 === */
		  
        digitTest <= 4'h5;

        #10;

        if (segmentsMeasured !== 7'b001_0010) begin

            $display("ERROR: 5 failed.");

        end
		  		  
		  
		  /* === Test Case 0x6 === */
		  
        digitTest <= 4'h6;

        #10;

        if (segmentsMeasured !== 7'b000_0010) begin

            $display("ERROR: 6 failed.");

        end
		  		  
		  
		  /* === Test Case 0x7 === */
		  
        digitTest <= 4'h7;

        #10;

        if (segmentsMeasured !== 7'b111_1000) begin

            $display("ERROR: 7 failed.");

        end
		  		  
		  
		  /* === Test Case 0x8 === */
		  
        digitTest <= 4'h8;

        #10;

        if (segmentsMeasured !== 7'b000_0000) begin

            $display("ERROR: 8 failed.");

        end
		  		  
		  
		  /* === Test Case 0x9 === */
		  
        digitTest <= 4'h9;

        #10;

        if (segmentsMeasured !== 7'b001_1000) begin

            $display("ERROR: 9 failed.");

        end
		  		  
		  
		  /* === Test Case 0xA === */
		  
        digitTest <= 4'hA;

        #10;

        if (segmentsMeasured !== 7'b000_1000) begin

            $display("ERROR: A failed.");

        end
		  		  
		  
		  /* === Test Case 0xB === */
		  
        digitTest <= 4'hB;

        #10;

        if (segmentsMeasured !== 7'b000_0011) begin

            $display("ERROR: B failed.");

        end
		  		  
		  
		  /* === Test Case 0xC === */
		  
        digitTest <= 4'hC;

        #10;

        if (segmentsMeasured !== 7'b100_0110) begin

            $display("ERROR: C failed.");

        end
		  		  
		  
		  /* === Test Case 0xD === */
		  
        digitTest <= 4'hD;

        #10;

        if (segmentsMeasured !== 7'b010_0001) begin

            $display("ERROR: D failed.");

        end
		  		  
		  
		  /* === Test Case 0xE === */
		  
        digitTest <= 4'hE;

        #10;

        if (segmentsMeasured !== 7'b000_0110) begin

            $display("ERROR: E failed.");

        end
		  		  
		  
		  /* === Test Case 0xF === */
		  
        digitTest <= 4'hF;

        #10;

        if (segmentsMeasured !== 7'b000_1110) begin

            $display("ERROR: F failed.");

        end
		  
        /* === End of Simulation === */
        $stop;
    end

endmodule

