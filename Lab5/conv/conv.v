
module CONV_MODULE(
    input wire [4:0] addr,
    output reg [7:0] rdata,
    input wire [7:0] wdata,
    input wire byteenable,
    input wire cs,
    input wire read,
    input wire write,

    input wire clk,
    input wire rst

);

reg [7:0] data00;
reg [7:0] data01;
reg [7:0] data02;
reg [7:0] data10;
reg [7:0] data11;
reg [7:0] data12;
reg [7:0] data20;
reg [7:0] data21;
reg [7:0] data22;

reg [7:0] filter00;
reg [7:0] filter01;
reg [7:0] filter02;
reg [7:0] filter10;
reg [7:0] filter11;
reg [7:0] filter12;
reg [7:0] filter20;
reg [7:0] filter21;
reg [7:0] filter22;


wire [16:0] conv_result = data00 * filter00 + data01 * filter01 + data02 * filter02 +
                          data10 * filter10 + data11 * filter11 + data12 * filter12 +
                          data20 * filter20 + data21 * filter21 + data22 * filter22;




always @ (posedge clk)
    if(cs & write & (addr == 5'd0)) begin
        if(byteenable ) data00[7:0] <= wdata[7:0];
    end

always @ (posedge clk)
    if(cs & write & (addr == 5'd1)) begin
        if(byteenable) data01[7:0] <= wdata[7:0];
    end
always @ (posedge clk)
    if(cs & write & (addr == 5'd2)) begin
        if(byteenable) data02[7:0] <= wdata[7:0];
    end
always @ (posedge clk)
    if(cs & write & (addr == 5'd3)) begin
        if(byteenable) data10[7:0] <= wdata[7:0];
    end
always @ (posedge clk)
    if(cs & write & (addr == 5'd4)) begin
        if(byteenable) data11[7:0] <= wdata[7:0];
    end
always @ (posedge clk)
    if(cs & write & (addr == 5'd5)) begin
        if(byteenable) data12[7:0] <= wdata[7:0];
    end
always @ (posedge clk)
    if(cs & write & (addr == 5'd6)) begin
        if(byteenable) data20[7:0] <= wdata[7:0];
    end
always @ (posedge clk)
    if(cs & write & (addr == 5'd7)) begin
        if(byteenable) data21[7:0] <= wdata[7:0];
    end
always @ (posedge clk)
    if(cs & write & (addr == 5'd8)) begin
        if(byteenable) data22[7:0] <= wdata[7:0];
    end
always @ (posedge clk)
    if(cs & write & (addr == 5'd9)) begin
        if(byteenable) filter00[7:0] <= wdata[7:0];
    end
always @ (posedge clk)
    if(cs & write & (addr == 5'd10)) begin
        if(byteenable) filter01[7:0] <= wdata[7:0];
    end
always @ (posedge clk)
    if(cs & write & (addr == 5'd11)) begin
        if(byteenable) filter02[7:0] <= wdata[7:0];
    end
always @ (posedge clk)
    if(cs & write & (addr == 5'd12)) begin
        if(byteenable) filter10[7:0] <= wdata[7:0];
    end
always @ (posedge clk)
    if(cs & write & (addr == 5'd13)) begin
        if(byteenable) filter11[7:0] <= wdata[7:0];
    end
always @ (posedge clk)
    if(cs & write & (addr == 5'd14)) begin
        if(byteenable) filter12[7:0] <= wdata[7:0];
    end
always @ (posedge clk)
    if(cs & write & (addr == 5'd15)) begin
        if(byteenable) filter20[7:0] <= wdata[7:0];
    end
always @ (posedge clk)
    if(cs & write & (addr == 5'd16)) begin
        if(byteenable) filter21[7:0] <= wdata[7:0];
    end
always @ (posedge clk)
    if(cs & write & (addr == 5'd17)) begin
        if(byteenable) filter22[7:0] <= wdata[7:0];
    end

always @ (posedge clk)
    if(cs & read)
            case(addr)
                5'd0 : rdata <= data00;
                5'd1 : rdata <= data01;
                5'd2 : rdata <= data02;
                5'd3 : rdata <= data10;
                5'd4 : rdata <= data11;
                5'd5 : rdata <= data12;
                5'd6 : rdata <= data20;
                5'd7 : rdata <= data21;
                5'd8 : rdata <= data22;
                5'd9 : rdata <= filter00;
                5'd10 : rdata <= filter01;
                5'd11 : rdata <= filter02;
                5'd12 : rdata <= filter10;
                5'd13 : rdata <= filter11;
                5'd14 : rdata <= filter12;
                5'd15 : rdata <= filter20;
                5'd16 : rdata <= filter21;
                5'd17 : rdata <= filter22;
                5'd18 : rdata <= conv_result[7:0];
                default: rdata <= 8'dx;
            endcase


endmodule