module signed_mult (a, b, out);

	output 		[17:0]	out;
	input signed	[8:0] 	a;
	input signed	[8:0] 	b;

	reg			[8:0] 	a_reg;
	reg	signed	[8:0] 	b_reg;
	reg	signed	[17:0]	out;

	wire 	signed	[17:0]	mult_out;

	assign mult_out = a_reg * b_reg;

	always@ *
	begin
		a_reg <= a;
		b_reg <= b;
		out <= mult_out;
	end

endmodule