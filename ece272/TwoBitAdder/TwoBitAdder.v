module TwoBitAdder(
a,b,cin,s,cout
);

input wire [1:0] a;
input wire [1:0] b;
input wire cin;

output wire [1:0] s;
output wire cout;

assign cout = (a[1] & b[1]) | (a[1] & b[1] & cin) | (a[1] & b[1] & b[0]) | (a[1] & b[0] & cin) | (~a[1] & a[0] & b[1] & cin) | (~a[1] & a[0] & b[1] & b[0]) | (~a[1] & b[1] & b[0] & cin);

endmodule