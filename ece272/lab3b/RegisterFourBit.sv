module RegisterFourBit(
	input logic clock,
	input logic clear_n,
	input logic [3:0] d,
	output logic [3:0] q
);

always_ff @(posedge clock) begin
    if (clear_n == 1'b0) begin
        // Set `q` to 0 when `clear_n` is low (active)
        q <= 4'b0000;
    end else begin
        // Set `q` to `d` on `clock` rising edge
        q <= d;
    end
end

endmodule