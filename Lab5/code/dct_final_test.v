module dct_final_test;

reg clk;
reg reset;
reg data_rdy;

reg [16:0]im0;
reg [16:0]im1;
reg [16:0]im2;
reg [16:0]im3;
reg [16:0]im4;
reg [16:0]im5;
reg [16:0]im6;
reg [16:0]im7;

wire [16:0]c0;
wire [16:0]c1;
wire [16:0]c2;
wire [16:0]c3;
wire [16:0]c4;
wire [16:0]c5;
wire [16:0]c6;
wire [16:0]c7;

wire [16:0]c00;
wire [16:0]c11;
wire [16:0]c22;
wire [16:0]c33;
wire [16:0]c44;
wire [16:0]c55;
wire [16:0]c66;
wire [16:0]c77;
wire crdy;
wire rcrdy;

reg [31:0]tmc;

reg [31:0]addr,addr2;

reg [16:0]mem_img[0:65535];

reg [7:0]cnt2;

integer fid1,fid2;

final_dct_process inst_test(clk,
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
                         

final_idct_process inst_test2(clk,
                         reset,
                         data_rdy,
                         c0,
                         c4,
                         c6,
                         c2,
                         c7,
                         c3,
                         c5,
                         c1,
                         c00,
                         c11,
                         c22,
                         c33,
                         c44,
                         c55,
                         c66,
                         c77,
                         rcrdy);
                                                  
                         
initial
begin
    clk=0;
    reset=0;
    data_rdy=0;
    $readmemb("image_text.txt",mem_img);
    fid1=$fopen("dct_co.txt");
    fid2=$fopen("reimg.txt");
    
end

always 
#20 clk=~clk;

initial
begin
    #100; reset=1;
    
end
always @(negedge clk)
begin
    
if(crdy)
   begin
  $fdisplay(fid1,"%d",c0);
  $fdisplay(fid1,"%d",c1);
  $fdisplay(fid1,"%d",c2);
  $fdisplay(fid1,"%d",c3);
  $fdisplay(fid1,"%d",c4);
  $fdisplay(fid1,"%d",c5);
  $fdisplay(fid1,"%d",c6);
  $fdisplay(fid1,"%d",c7);
  $display("%d",c0);
  $display("%d",c1);
  $display("%d",c2);
  $display("%d",c3);
  $display("%d",c4);
  $display("%d",c5);
  $display("%d",c6);
  $display("%d",c7);
  tmc=tmc+32'd1;
  end
  
  if(rcrdy)
   begin
  $fdisplay(fid2,"%d",c00);
  $fdisplay(fid2,"%d",c11);
  $fdisplay(fid2,"%d",c22);
  $fdisplay(fid2,"%d",c33);
  $fdisplay(fid2,"%d",c44);
  $fdisplay(fid2,"%d",c55);
  $fdisplay(fid2,"%d",c66);
  $fdisplay(fid2,"%d",c77);
  $display("%d",c00);
  $display("%d",c11);
  $display("%d",c22);
  $display("%d",c33);
  $display("%d",c44);
  $display("%d",c55);
  $display("%d",c66);
  $display("%d",c77);
  
  end
  
  end
  
  
  
  
  
always @(negedge clk)
begin
    
    if(reset==1)
    begin
    data_rdy=1;
    im0=mem_img[addr];
    im1=mem_img[addr+1];
    im2=mem_img[addr+2];
    im3=mem_img[addr+3];
    im4=mem_img[addr+4];
    im5=mem_img[addr+5];
    im6=mem_img[addr+6];
    im7=mem_img[addr+7];
    
    
    if(cnt2==255)
    begin
    addr2=addr2+32'd8;
    addr=addr2;
    cnt2=8'd0;
    end

    else
    begin
    addr=addr+32'd256;
    cnt2=cnt2+8'd1;
    end

    if(addr2==32'd256 & addr==32'd5888)
      $finish;
    
    end

 else
    begin
    data_rdy=0;
    addr=32'd0;
    addr2=32'd0;
    cnt2=8'd0;
    im0={1'b0,16'd100};
    im1={1'b0,16'd120};
    im2={1'b0,16'd130};
    im3={1'b0,16'd140};
    im4={1'b0,16'd100};
    im5={1'b0,16'd120};
    im6={1'b0,16'd130};
    im7={1'b0,16'd140};
    tmc=32'd0;
    end    
    
end


endmodule 