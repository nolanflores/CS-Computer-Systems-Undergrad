module Clock #(parameter T = 'h2FAF080)(
    input  logic clock,
    input  logic reset_n,
    output logic [5:0] seconds,
    output logic [5:0] minutes,
    output logic [4:0] hours
);

logic [25:0] ticks;
logic secClear;
logic minClear;
logic hourClear;
assign secClear = (ticks == T-1) && (seconds == 6'd59);
assign minClear = secClear && (minutes == 6'd59);
assign hourClear = minClear && (hours == 5'd23);


Counter #(.N(26)) tick_counter (
    .clock(clock),
    .reset_n(reset_n),
    .enable_n(1'b0),
    .clear_n(ticks !== T-1),
    .count(ticks)
);


Counter #(.N(6)) second_counter (
    .clock(clock),
    .reset_n(reset_n),
    .enable_n(ticks !== T-1),
    .clear_n(~secClear),
    .count(seconds)
);


Counter #(.N(6)) minute_counter (
    .clock(clock),
    .reset_n(reset_n),
    .enable_n(~secClear),
    .clear_n(~minClear),
    .count(minutes)
);


Counter #(.N(5)) hour_counter (
    .clock(clock),
    .reset_n(reset_n),
    .enable_n(~minClear),
    .clear_n(~hourClear),
    .count(hours)
);

endmodule