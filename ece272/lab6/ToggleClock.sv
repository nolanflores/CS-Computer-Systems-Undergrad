module ToggleClock(
	input logic clock,
	input logic reset_n,
	output logic enable_n
);

always_ff @(posedge clock or negedge reset_n) begin
	if(reset_n == 1'b0) begin
		enable_n <= 1'b1;
	end else begin
		enable_n <= ~enable_n;//goes high and low every other rising edge
	end
end

endmodule