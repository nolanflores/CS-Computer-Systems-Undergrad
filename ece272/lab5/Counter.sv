module Counter #(parameter N = 6)(
	input logic clock,
	input logic clear_n,
	input logic reset_n,
	input logic enable_n,
	output logic [N-1:0] count
);

always_ff @(posedge clock or negedge reset_n) begin
	if (reset_n == 1'b0) begin//reset_n active low
		//asynchronous reset
		count <= '0;
	end else if (clear_n == 1'b0) begin
		count <= '0;
	end else if (enable_n == 1'b0) begin
		count <= count + 1'b1;
	end
end

endmodule