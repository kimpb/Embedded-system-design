module final_dct_process(clk,
                         reset,
                         data_rdy,
                         im0,
                         im1,
                         im2,
                         im3,
                         im4,
                         im5,
                         im6,
                         im7,
                         c0,
                         c1,
                         c2,
                         c3,
                         c4,
                         c5,
                         c6,
                         c7,
                         crdy);
                         
input clk;
input reset;
input data_rdy;

input [16:0]im0;
input [16:0]im1;
input [16:0]im2;
input [16:0]im3;
input [16:0]im4;
input [16:0]im5;
input [16:0]im6;
input [16:0]im7;                         

output [16:0]c0;
output [16:0]c1;
output [16:0]c2;
output [16:0]c3;
output [16:0]c4;
output [16:0]c5;
output [16:0]c6;
output [16:0]c7;

output crdy;

wire [16:0]c0;
wire [16:0]c1;
wire [16:0]c2;
wire [16:0]c3;
wire [16:0]c4;
wire [16:0]c5;
wire [16:0]c6;
wire [16:0]c7;

reg [16:0]tim0;
reg [16:0]tim1;
reg [16:0]tim2;
reg [16:0]tim3;
reg [16:0]tim4;
reg [16:0]tim5;
reg [16:0]tim6;
reg [16:0]tim7;

wire [16:0]dim0;
wire [16:0]dim1;
wire [16:0]dim2;
wire [16:0]dim3;
wire [16:0]dim4;
wire [16:0]dim5;
wire [16:0]dim6;
wire [16:0]dim7;

reg [16:0]cim0;
reg [16:0]cim1;
reg [16:0]cim2;
reg [16:0]cim3;
reg [16:0]cim4;
reg [16:0]cim5;
reg [16:0]cim6;
reg [16:0]cim7;

reg [16:0]mem0[0:15];
reg [16:0]mem1[0:15];
reg [16:0]mem2[0:15];
reg [16:0]mem3[0:15];
reg [16:0]mem4[0:15];
reg [16:0]mem5[0:15];
reg [16:0]mem6[0:15];
reg [16:0]mem7[0:15];

reg [7:0]cnt;
reg [3:0]addr;
reg [2:0]addr2;
reg [3:0]md;
reg [31:0]tcnt;
wire crdy;

assign crdy=tcnt>=32'd10 & tcnt<=32'd8201;

always @(posedge clk)
begin
    if(~reset)
    begin
        tim0<=16'd0;
        tim1<=16'd0;
        tim2<=16'd0;
        tim3<=16'd0;
        tim4<=16'd0;
        tim5<=16'd0;
        tim6<=16'd0;
        tim7<=16'd0;
        cnt<=8'd0;
        tcnt<=32'd0; 
    end
    
    else if(data_rdy & cnt>=8'd0)
    begin
        tim0<=im0;
        tim1<=im1;
        tim2<=im2;
        tim3<=im3;
        tim4<=im4;
        tim5<=im5;
        tim6<=im6;
        tim7<=im7;
               
        cnt<=cnt+8'd1;
        if(tcnt>=32'd10)
        tcnt<=tcnt+32'd1;
        else
        tcnt<=tcnt+32'd1;
        
   end

end


always @(posedge clk)
begin
    if(~reset)
     begin
         addr<=4'd0;
         addr2<=3'd0;
         md<=4'd0;
     end
     
     //else if(cnt>=8'd1 & addr>=4'd0 & addr<=4'd7)
//     begin
//         mem0[addr]<=dim0;
//         mem1[addr]<=dim1;
//         mem2[addr]<=dim2;
//         mem3[addr]<=dim3;
//         mem4[addr]<=dim4;
//         mem5[addr]<=dim5;
//         mem6[addr]<=dim6;
//         mem7[addr]<=dim7;
//         addr<=addr+4'd1;
//          md<=md+4'd1;      
//          
//     end
     
     else if(cnt>=8'd1 & addr2==3'd0) 
     begin
         cim0<=mem0[md];
         cim1<=mem0[md+1];
         cim2<=mem0[md+2];
         cim3<=mem0[md+3];
         cim4<=mem0[md+4];
         cim5<=mem0[md+5];
         cim6<=mem0[md+6];
         cim7<=mem0[md+7];
         
         mem0[addr]<=dim0;
         mem1[addr]<=dim1;
         mem2[addr]<=dim2;
         mem3[addr]<=dim3;
         mem4[addr]<=dim4;
         mem5[addr]<=dim5;
         mem6[addr]<=dim6;
         mem7[addr]<=dim7;
         addr2<=addr2+8'd1;
         addr<=addr+8'd1;
         //md<=md+4'd1;
     end
     
     else if(cnt>=8'd1 & addr2==3'd1) 
     begin
         cim0<=mem1[md];
         cim1<=mem1[md+1];
         cim2<=mem1[md+2];
         cim3<=mem1[md+3];
         cim4<=mem1[md+4];
         cim5<=mem1[md+5];
         cim6<=mem1[md+6];
         cim7<=mem1[md+7];
         
         mem0[addr]<=dim0;
         mem1[addr]<=dim1;
         mem2[addr]<=dim2;
         mem3[addr]<=dim3;
         mem4[addr]<=dim4;
         mem5[addr]<=dim5;
         mem6[addr]<=dim6;
         mem7[addr]<=dim7;
         addr2<=addr2+3'd1;
         addr<=addr+4'd1;
        // md<=md+4'd1;
     end
     
     else if(cnt>=8'd1 & addr2==3'd2) 
     begin
         cim0<=mem2[md];
         cim1<=mem2[md+1];
         cim2<=mem2[md+2];
         cim3<=mem2[md+3];
         cim4<=mem2[md+4];
         cim5<=mem2[md+5];
         cim6<=mem2[md+6];
         cim7<=mem2[md+7];
         
         mem0[addr]<=dim0;
         mem1[addr]<=dim1;
         mem2[addr]<=dim2;
         mem3[addr]<=dim3;
         mem4[addr]<=dim4;
         mem5[addr]<=dim5;
         mem6[addr]<=dim6;
         mem7[addr]<=dim7;
         addr2<=addr2+3'd1;
         addr<=addr+4'd1;
         //md<=md+4'd1;
     end
     
     else if(cnt>=8'd1 & addr2==3'd3) 
     begin
         cim0<=mem3[md];
         cim1<=mem3[md+1];
         cim2<=mem3[md+2];
         cim3<=mem3[md+3];
         cim4<=mem3[md+4];
         cim5<=mem3[md+5];
         cim6<=mem3[md+6];
         cim7<=mem3[md+7];
         
         mem0[addr]<=dim0;
         mem1[addr]<=dim1;
         mem2[addr]<=dim2;
         mem3[addr]<=dim3;
         mem4[addr]<=dim4;
         mem5[addr]<=dim5;
         mem6[addr]<=dim6;
         mem7[addr]<=dim7;
         addr2<=addr2+3'd1;
         addr<=addr+4'd1;
         //md<=md+4'd1;
     end
     
     else if(cnt>=8'd1 & addr2==3'd4) 
     begin
         cim0<=mem4[md];
         cim1<=mem4[md+1];
         cim2<=mem4[md+2];
         cim3<=mem4[md+3];
         cim4<=mem4[md+4];
         cim5<=mem4[md+5];
         cim6<=mem4[md+6];
         cim7<=mem4[md+7];
         
         mem0[addr]<=dim0;
         mem1[addr]<=dim1;
         mem2[addr]<=dim2;
         mem3[addr]<=dim3;
         mem4[addr]<=dim4;
         mem5[addr]<=dim5;
         mem6[addr]<=dim6;
         mem7[addr]<=dim7;
         addr2<=addr2+3'd1;
         addr<=addr+4'd1;
        // md<=md+4'd1;
     end
     
     else if(cnt>=8'd1 & addr2==3'd5) 
     begin
         cim0<=mem5[md];
         cim1<=mem5[md+1];
         cim2<=mem5[md+2];
         cim3<=mem5[md+3];
         cim4<=mem5[md+4];
         cim5<=mem5[md+5];
         cim6<=mem5[md+6];
         cim7<=mem5[md+7];
         
         mem0[addr]<=dim0;
         mem1[addr]<=dim1;
         mem2[addr]<=dim2;
         mem3[addr]<=dim3;
         mem4[addr]<=dim4;
         mem5[addr]<=dim5;
         mem6[addr]<=dim6;
         mem7[addr]<=dim7;
         addr2<=addr2+3'd1;
         addr<=addr+4'd1;
        // md<=md+4'd1;
     end
     else if(cnt>=8'd1 & addr2==3'd6) 
     begin
         cim0<=mem6[md];
         cim1<=mem6[md+1];
         cim2<=mem6[md+2];
         cim3<=mem6[md+3];
         cim4<=mem6[md+4];
         cim5<=mem6[md+5];
         cim6<=mem6[md+6];
         cim7<=mem6[md+7];
         
         mem0[addr]<=dim0;
         mem1[addr]<=dim1;
         mem2[addr]<=dim2;
         mem3[addr]<=dim3;
         mem4[addr]<=dim4;
         mem5[addr]<=dim5;
         mem6[addr]<=dim6;
         mem7[addr]<=dim7;
         addr2<=addr2+3'd1;
         addr<=addr+4'd1;
         //md<=md+4'd1;
     end
     
     else if(cnt>=8'd1 & addr2==3'd7) 
     begin
         cim0<=mem7[md];
         cim1<=mem7[md+1];
         cim2<=mem7[md+2];
         cim3<=mem7[md+3];
         cim4<=mem7[md+4];
         cim5<=mem7[md+5];
         cim6<=mem7[md+6];
         cim7<=mem7[md+7];
         
         mem0[addr]<=dim0;
         mem1[addr]<=dim1;
         mem2[addr]<=dim2;
         mem3[addr]<=dim3;
         mem4[addr]<=dim4;
         mem5[addr]<=dim5;
         mem6[addr]<=dim6;
         mem7[addr]<=dim7;
         addr2<=addr2+3'd1;
         addr<=addr+4'd1;
         cnt<=8'd1;
         if(addr==7)
         md<=0;
         else
         md<=8;
         
     end
     
     
     
 end
 
 
         

d1_dct_process_final inst_dct1(.x0(tim0),
                               .x1(tim1),
                               .x2(tim2),
                               .x3(tim3),
                                .x4(tim4),
                                .x5(tim5),
                                 .x6(tim6),
                                 .x7(tim7),
                                 .y0(dim0),
                                 .y1(dim1),
                                 .y2(dim2),
                                 .y3(dim3),
                                 .y4(dim4),
                                 .y5(dim5),
                                 .y6(dim6),
                                 .y7(dim7));
                                 
                                 
                                 
d1_dct_process_final inst_dct2(.x0(cim0),
                               .x1(cim1),
                               .x2(cim2),
                               .x3(cim3),
                                .x4(cim4),
                                .x5(cim5),
                                 .x6(cim6),
                                 .x7(cim7),
                                 .y0(c0),
                                 .y1(c1),
                                 .y2(c2),
                                 .y3(c3),
                                 .y4(c4),
                                 .y5(c5),
                                 .y6(c6),
                                 .y7(c7));
                                 
                                                         
                        
 endmodule                           