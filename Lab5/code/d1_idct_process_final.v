module d1_idct_process_final(x0,
                        x1,
                        x2,
                        x3,
                        x4,
                        x5,
                        x6,
                        x7,
                        y0,
                        y1,
                        y2,
                        y3,
                        y4,
                        y5,
                        y6,
                        y7);
    
    
input   [16:0] x0;  
input   [16:0] x1;  
input   [16:0] x2;  
input   [16:0] x3;  
input   [16:0] x4;  
input   [16:0] x5;  
input   [16:0] x6;  
input   [16:0] x7;  

output [16:0]y0;
output [16:0]y1;
output [16:0]y2;
output [16:0]y3;
output [16:0]y4;
output [16:0]y5;
output [16:0]y6;
output [16:0]y7;
    
    
wire [16:0]s01;
wire [16:0]s11;
wire [16:0]s21;
wire [16:0]s31;
wire [16:0]s41;
wire [16:0]s51;
wire [16:0]s61;
wire [16:0]s71;


wire [16:0]s02;
wire [16:0]s12;
wire [16:0]s22;
wire [16:0]s32;
wire [16:0]s42;
wire [16:0]s52;
wire [16:0]s62;
wire [16:0]s72;

wire [16:0]s03;
wire [16:0]s13;
wire [16:0]s23;
wire [16:0]s33;
wire [16:0]s43;
wire [16:0]s53;
wire [16:0]s63;
wire [16:0]s73;

wire [16:0]s44;
wire [16:0]s74;

wire [16:0]s02t;
wire [16:0]s32t;
wire [16:0]s12t;
wire [16:0]s22t;



wire [16:0]y0;
wire [16:0]y1;
wire [16:0]y2;
wire [16:0]y3;
wire [16:0]y4;
wire [16:0]y5;
wire [16:0]y6;
wire [16:0]y7;

wire [16:0]y0t;
wire [16:0]y1t;
wire [16:0]y2t;
wire [16:0]y3t;
wire [16:0]y4t;
wire [16:0]y5t;
wire [16:0]y6t;
wire [16:0]y7t;


wire [16:0]ix0;
wire [16:0]ix1;
wire [16:0]ix2;
wire [16:0]ix3;
wire [16:0]ix4;
wire [16:0]ix5;
wire [16:0]ix6;
wire [16:0]ix7;

wire [16:0]ts41;
wire [16:0]ts51;
wire [16:0]ts61;
wire [16:0]ts71;

wire [16:0]s01t;
wire [16:0]s11t;

assign ix0={x0[16],m0(x0[15:0])};
assign ix1={x1[16],m0(x1[15:0])};

assign ix2={x2[16],(x2[15:0]<<1)};
assign ix3={x3[16],(x3[15:0]<<1)};

assign ix4={x4[16],m0(x4[15:0])};
assign ix5={x5[16],(x5[15:0]<<1)};

assign ix6={x6[16],(x6[15:0]<<1)};
assign ix7={x7[16],m0(x7[15:0])};


assign s01t=butterfly_process_add(ix0,ix1);
assign s11t=butterfly_process_sub(ix0,ix1);


assign s01={s01t[16],s01t[15:0]>>1};
assign s11={s11t[16],s11t[15:0]>>1};


assign s21=butterfly_process_sub(p1f(ix3),p2f(ix2));
assign s31=butterfly_process_add({ix3[16],ptf(ix3[15:0])},p3f(ix2));


assign ts41=butterfly_process_add(ix6,ix4);
assign ts61=butterfly_process_sub(ix4,ix6);
assign ts51=butterfly_process_add(ix7,ix5);
assign ts71=butterfly_process_sub(ix5,ix7);


assign s51={ts51[16],ts51[15:0]>>1};
assign s71={ts71[16],ts71[15:0]>>1};
assign s41={ts41[16],ts41[15:0]>>1};
assign s61={ts61[16],ts61[15:0]>>1};



assign s02t=butterfly_process_add(s01,s31);
assign s32t=butterfly_process_sub(s01,s31);
assign s12t=butterfly_process_add(s11,s21);
assign s22t=butterfly_process_sub(s11,s21);


assign s02={s02t[16],s02t[15:0]>>1};
assign s32={s32t[16],s32t[15:0]>>1};
assign s12={s12t[16],s12t[15:0]>>1};
assign s22={s22t[16],s22t[15:0]>>1};





assign s42=butterfly_process_sub({s41[16],p4(s41[15:0])},{s71[16],p5(s71[15:0])});
assign s72=butterfly_process_add({s41[16],p9(s41[15:0])},{s71[16],p10(s71[15:0])});


assign s52=butterfly_process_sub({s51[16],p11(s51[15:0])},{s61[16],p12(s61[15:0])});
assign s62=butterfly_process_add({s61[16],p13(s61[15:0])},{s51[16],p14(s51[15:0])});



assign y0t=butterfly_process_add(s02,s72);
assign y7t=butterfly_process_sub(s02,s72);

assign y1t=butterfly_process_add(s12,s62);
assign y6t=butterfly_process_sub(s12,s62);

assign y2t=butterfly_process_add(s22,s52);
assign y5t=butterfly_process_sub(s22,s52);


assign y3t=butterfly_process_add(s32,s42);
assign y4t=butterfly_process_sub(s32,s42);



assign y0={y0t[16],y0t[15:0]>>1};
assign y7={y7t[16],y7t[15:0]>>1};

assign y1={y1t[16],y1t[15:0]>>1};
assign y6={y6t[16],y6t[15:0]>>1};

assign y2={y2t[16],y2t[15:0]>>1};
assign y5={y5t[16],y5t[15:0]>>1};

assign y3={y3t[16],y3t[15:0]>>1};
assign y4={y4t[16],y4t[15:0]>>1};



function [16:0]butterfly_process_add;
    
        
input [16:0]a;
input [16:0]b;

reg signa;
reg signb;

reg [15:0]vala;
reg [15:0]valb;

reg outsign;

reg [15:0]outval;


begin
    


signa=a[16];    
signb=b[16];

vala=a[15:0];
valb=b[15:0];




outsign=(signa & signb)?1'b1:
               ((signa & ~signb) & (vala>=valb))?1'b1:
               ((signa & ~signb) & (vala<valb))?1'b0:
               ((~signa & signb) & (valb>vala))?1'b1:
               ((~signa & signb) & (valb<=vala))?1'b0:
               (~signa & ~signb)?1'b0:1'b0;
               
outval=(signa & signb)?vala+valb:
               ((signa & ~signb) & (vala>=valb))?vala-valb:
               ((signa & ~signb) & (vala<valb))?valb-vala:
               ((~signa & signb) & (valb>vala))?valb-vala:
               ((~signa & signb) & (valb<=vala))?vala-valb:
               (~signa & ~signb)?vala+valb:16'd0;

butterfly_process_add={outsign,outval};
            
end

                              
endfunction



function [16:0]butterfly_process_sub;
    
        
input [16:0]a;
input [16:0]b;
reg signa;
reg signb;
reg [15:0]vala;
reg [15:0]valb;
reg outsign;
reg [15:0]outval;


begin
    


signa=a[16];    
signb=b[16];
vala=a[15:0];
valb=b[15:0];


outval=((~signa & ~signb)& (vala>=valb))?vala-valb:
        ((~signa & ~signb)& (valb>vala))?valb-vala:
         ((~signa & signb))?vala+valb:
         ((signa & ~signb))?vala+valb:
         ((signa & signb)& (vala>valb))?vala-valb:
         ((signa & signb)& (valb>=vala))?valb-vala:16'd0;
        
outsign=((~signa & ~signb)& (vala>=valb))?1'b0:
        ((~signa & ~signb)& (valb>vala))?1'b1:
         ((~signa & signb))?1'b0:
         ((signa & ~signb))?1'b1:
         ((signa & signb)& (vala>valb))?1'b1:
         ((signa & signb)& (valb>=vala))?1'b0:16'd0;
        
                 
         
         
butterfly_process_sub={outsign,outval};
            
end

                              
endfunction


      
 
      
 
  
 function [15:0]m0;
    
 input [15:0]data;
  
 m0=(data<<1)+(data>>1)+(data>>2)+(data>>5);
 
 endfunction 
   
   
   
       
      
 
 
 
 function [16:0]p1f;
    
 input [16:0]data;
  
  p1f={~data[16],(data[15:0]>>1)+(data[15:0]>>6)+(data[15:0]>>7)};
 
 
 endfunction 
 
 function [16:0]p2f;
   
 input [16:0]data;
  
  p2f={~data[16],(data[15:0])+(data[15:0]>>3)+(data[15:0]>>4)};
 
 
 endfunction 
 
 function [16:0]p3f;
   
 input [16:0]data;
  
  p3f={~data[16],(data[15:0]>>2)+(data[15:0]>>3)+(data[15:0]>>4)+(data[15:0]>>6)+(data[15:0]>>7)};
 
 
 endfunction 
 
 
 function [15:0]ptf;
   
 input [15:0]data;
  
  ptf={(data[15:0])+(data[15:0]>>2)+(data[15:0]>>5)+(data[15:0]>>8)};
 
 
 endfunction 
 
 
 function [15:0]p4;
   
 input [15:0]data;
  
 p4={(data[15:0]>>1)+(data[15:0]>>2)+(data[15:0]>>5)+(data[15:0]>>6)+(data[15:0]>>8)};
  
 endfunction 


function [15:0]p5;
   
 input [15:0]data;
  
  p5={(data[15:0]>>1)+(data[15:0]>>4)+(data[15:0]>>5)};
 
 
 endfunction 
 
 
 function [15:0]p9;
   
 input [15:0]data;
  
  p9={(data[15:0]>>1)+(data[15:0]>>4)+(data[15:0]>>5)+(data[15:0]>>6)};
 
 
 endfunction 
 
 
 function [15:0]p10;
   
 input [15:0]data;
  
 p10={(data[15:0]>>1)+(data[15:0]>>2)+(data[15:0]>>5)+(data[15:0]>>6)+(data[15:0]>>8)};
  
 endfunction 
 
function [15:0]p11;
   
 input [15:0]data;
  
 p11={(data[15:0]>>1)+(data[15:0]>>2)+(data[15:0]>>3)+(data[15:0]>>4)+(data[15:0]>>5)+(data[15:0]>>7)};
  
 endfunction 
                

function [15:0]p12;
   
 input [15:0]data;
  
 p12={(data[15:0]>>3)+(data[15:0]>>5)+(data[15:0]>>6)+(data[15:0]>>7)+(data[15:0]>>8)};
  
 endfunction 
 

function [15:0]p14;
   
 input [15:0]data;
  
 p14={(data[15:0]>>3)+(data[15:0]>>4)+(data[15:0]>>7)+(data[15:0]>>8)};
  
 endfunction 
                 

function [15:0]p13;
   
 input [15:0]data;
  
 p13={(data[15:0]>>1)+(data[15:0]>>2)+(data[15:0]>>3)+(data[15:0]>>4)+(data[15:0]>>5)+(data[15:0]>>7)};
  
 endfunction 
                
endmodule 
               