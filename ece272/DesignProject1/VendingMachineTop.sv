module VendingMachineTop(
	input logic clk,
	input logic nickel,
	input logic dime,
	input logic refund,
	input logic reset,
	output logic vend,
	output logic nickel_out,
	output logic dime_out
);

logic [5:0] money;//six bit to store up to $0.63
logic refundEnable;//low while accepting coins, high while refunding coins

always_ff @(posedge clk or posedge reset) begin
	if(reset == 1'b1)begin//reset all values to zero on reset's rising edge
		money <= 6'b0;
		refundEnable <= 1'b0;
		vend <= 1'b0;
		nickel_out <= 1'b0;
		dime_out <= 1'b0;
	end else if(refundEnable == 1'b1)begin//refunding coins
		vend <= 1'b0;//vend is high for one cycle
		if(money >= 6'd10)begin//10 cents is owed
			money <= money - 6'd10;
			dime_out <= 1'b1;
			nickel_out <= 1'b0;
		end else if(money >= 6'd5) begin//5 cents is owed
			money <= money - 6'd5;
			dime_out <= 1'b0;
			nickel_out <= 1'b1;
		end else begin//no more money is owed
			dime_out <= 1'b0;
			nickel_out <= 1'b0;
			refundEnable <= 1'b0;
		end
	end else begin//accepting coins
		if(refund == 1'b1) begin//refund button pressed
			refundEnable <= 1'b1;
		end else if(money >= 6'd30) begin//30 cents has been inserted
			money <= money - 6'd30;
			refundEnable <= 1'b1;
			vend <= 1'b1;
		end else if(dime == 1'b1) begin//dime inserted
			money <= money + 6'd10;
		end else if(nickel == 1'b1) begin//nickel inserted
			money <= money + 6'd5;
		end
	end
end

endmodule