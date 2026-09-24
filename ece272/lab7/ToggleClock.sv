module ToggleClock(
	input logic clock,
	input logic reset_n,
	output logic enable_n
);

always_ff @(posedge clock or negedge reset_n) begin
	if(!reset_n)
		enable_n <= 1'b1;
	else
		enable_n <= ~enable_n;
end

endmodule