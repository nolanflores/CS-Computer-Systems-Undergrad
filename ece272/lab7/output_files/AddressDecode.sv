module AddressDecode(
	input logic [9:0] row,
	input logic [9:0] column,
	output logic display_image,
	output logic [15:0] pixel_address
);

always_comb begin
	pixel_address = 16'b0;
	display_image = 1'b0;
	if(row >= 144 && row < 400)begin
		if(column >= 35 && column < 291)begin
			display_image = 1'b1;
			pixel_address = ((column - 35)*256)+(row-144);
		end
	end
end

endmodule