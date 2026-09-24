/*
 * Author: Nolan Flores
 * ECE 271 Design Project 2
 * Oregon State University
 * 6/9/2025
*/


module VendingMachineTop(
	input  logic clk,
	input  logic nickel,
	input  logic dime,
	input  logic quarter,
	input  logic refund,
	input  logic reset,
	output logic vend,
	output logic nickel_out,
	output logic dime_out,
	output logic quarter_out
);

logic [6:0] money;//stores up to $1.27
logic refundEnable;//low while accepting coins, high while refunding coins

always_ff @(posedge clk or posedge reset) begin
	if (reset) begin//initial state
		money <= 7'd0;
		refundEnable <= 1'b0;
		vend <= 1'b0;
		nickel_out <= 1'b0;
		dime_out <= 1'b0;
		quarter_out <= 1'b0;
	end else begin//--------------------------------------------------------------------Logic
		//default values
		vend <= 1'b0;//vends for one cycle
		nickel_out <= 1'b0;
		dime_out <= 1'b0;
		quarter_out <= 1'b0;
		if(refundEnable)begin//---------------------------------Refund Coins
			if(money >= 7'd25) begin//quarter
				money <= money - 7'd25;
				quarter_out <= 1'b1;
			end else if(money >= 7'd10) begin//dime
				money <= money - 7'd10;
				dime_out <= 1'b1;
			end else if(money >= 7'd5) begin//nickel
				money <= money - 7'd5;
				nickel_out <= 1'b1;
			end else begin
				refundEnable <= 1'b0;//done refunding
			end
		end else begin//----------------------------------------Accept Coins
			if(refund) begin//refund button
				refundEnable <= 1'b1;
			end else if (money >= 7'd50) begin
				money <= money - 7'd50;//take payment
				vend <= 1'b1;
				refundEnable <= 1'b1;
			end else begin//handle inserted coins
				if(quarter)
					money <= money + 7'd25;
				else if(dime)
					money <= money + 7'd10;
				else if(nickel)
					money <= money + 7'd5;
			end
		end
	end
end

endmodule
