module SevenSegmentDecimalDecode #(parameter N = 6) (
    input  logic [N-1:0] value,              // Input: 0 to 63
    output logic [6:0] seg_high,           // Tens digit (MSD)
    output logic [6:0] seg_low             // Ones digit (LSD)
);

    logic [3:0] tens, ones;

    // Convert binary to decimal digits
    always_comb begin
        tens = value / 10;
        ones = value % 10;
    end

    // Decode each digit to 7-segment
    always_comb begin
        case (tens)
            4'd0: seg_high = 7'b100_0000;
            4'd1: seg_high = 7'b111_1001;
            4'd2: seg_high = 7'b010_0100;
            4'd3: seg_high = 7'b011_0000;
            4'd4: seg_high = 7'b001_1001;
            4'd5: seg_high = 7'b001_0010;
            4'd6: seg_high = 7'b000_0010;
            4'd7: seg_high = 7'b111_1000;
            4'd8: seg_high = 7'b000_0000;
            4'd9: seg_high = 7'b001_1000;
            default: seg_high = 7'b111_1111; // blank
        endcase

        case (ones)
            4'd0: seg_low = 7'b100_0000;
            4'd1: seg_low = 7'b111_1001;
            4'd2: seg_low = 7'b010_0100;
            4'd3: seg_low = 7'b011_0000;
            4'd4: seg_low = 7'b001_1001;
            4'd5: seg_low = 7'b001_0010;
            4'd6: seg_low = 7'b000_0010;
            4'd7: seg_low = 7'b111_1000;
            4'd8: seg_low = 7'b000_0000;
            4'd9: seg_low = 7'b001_1000;
            default: seg_low = 7'b111_1111;
        endcase
    end

endmodule