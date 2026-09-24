module Decimal14Segment #(parameter N = 6)(
	input logic [N-1:0] digits,
	output logic [6:0] segTens,
	output logic [6:0] segOnes
);

always_comb begin
	case (digits/10)
		4'd0: segTens = 7'b100_0000;
		4'd1: segTens = 7'b111_1001;
		4'd2: segTens = 7'b010_0100;
		4'd3: segTens = 7'b011_0000;
		4'd4: segTens = 7'b001_1001;
		4'd5: segTens = 7'b001_0010;
		4'd6: segTens = 7'b000_0010;
		4'd7: segTens = 7'b111_1000;
		4'd8: segTens = 7'b000_0000;
		4'd9: segTens = 7'b001_1000;
		default: segTens = 7'b111_1111; // blank
	endcase
	
	case (digits%10)
		4'd0: segOnes = 7'b100_0000;
		4'd1: segOnes = 7'b111_1001;
		4'd2: segOnes = 7'b010_0100;
		4'd3: segOnes = 7'b011_0000;
		4'd4: segOnes = 7'b001_1001;
		4'd5: segOnes = 7'b001_0010;
		4'd6: segOnes = 7'b000_0010;
		4'd7: segOnes = 7'b111_1000;
		4'd8: segOnes = 7'b000_0000;
		4'd9: segOnes = 7'b001_1000;
		default: segOnes = 7'b111_1111; // blank
	endcase
end

endmodule