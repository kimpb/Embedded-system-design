module d1_dct_process_final(x0,
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

wire [16:0]y0;
wire [16:0]y1;
wire [16:0]y2;
wire [16:0]y3;
wire [16:0]y4;
wire [16:0]y5;
wire [16:0]y6;
wire [16:0]y7;

assign s01=butterfly_process_add(x0,x7);
assign s71=butterfly_process_sub(x0,x7);

assign s11=butterfly_process_add(x1,x6);
assign s61=butterfly_process_sub(x1,x6);

assign s21=butterfly_process_add(x2,x5);
assign s51=butterfly_process_sub(x2,x5);

assign s31=butterfly_process_add(x3,x4);
assign s41=butterfly_process_sub(x3,x4);



assign s02=butterfly_process_add(s01,s31);
assign s32=butterfly_process_sub(s01,s31);

assign s12=butterfly_process_add(s11,s21);
assign s22=butterfly_process_sub(s11,s21);


assign s42=butterfly_process_add({s41[16],u1(s41[15:0])},{s71[16],u2(s71[15:0])});
assign s72=butterfly_process_sub({s71[16],u7(s71[15:0])},{s41[16],u8(s41[15:0])});


assign s52=butterfly_process_add({s51[16],u3(s51[15:0])},{s61[16],u4(s61[15:0])});
assign s62=butterfly_process_sub({s61[16],u5(s61[15:0])},{s51[16],u6(s51[15:0])});


assign s03=butterfly_process_add(s02,s12);
assign s13=butterfly_process_sub(s02,s12);


assign s23=butterfly_process_add(s22,{s32[16],v1(s32[15:0])});
assign s33=butterfly_process_add({s22[16],v3(s22[15:0])},{s32[16],v2(s32[15:0])});


assign s43=butterfly_process_add(s42,s62);
assign s63=butterfly_process_sub(s42,s62);

assign s53=butterfly_process_add(s52,s72);
assign s73=butterfly_process_sub(s52,s72);


//assign s74=butterfly_process_add(s43,s73);
//assign s44=butterfly_process_add(s74,s43);

assign y0={s03[16],s0(s03[15:0])};
assign y4={s13[16],s0(s13[15:0])};

assign y6={s23[16],(s23[15:0]>>1)};
assign y2={s33[16],(s33[15:0]>>1)};


assign y7={s43[16],s0(s43[15:0])};
assign y3={s53[16],(s53[15:0]>>1)};

assign y5={s63[16],(s63[15:0]>>1)};
assign y1={s73[16],s0(s73[15:0])};



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

function [15:0]v1;
    
 input [15:0]data;
  
 v1=(data>>2)+(data>>3)+(data>>5);
 
 endfunction 
 
 
 function [15:0]v2;
    
 input [15:0]data;
  
 v2=(data>>1)+(data>>2)+(data>>3)+(data>>5)+(data>>6);
 
 endfunction 
 
 
 function [15:0]v3;
    
 input [15:0]data;
  
 v3=(data>>2)+(data>>6)+(data>>4)+(data>>5);
 
 endfunction 
 
 
 function [15:0]u1;
    
 input [15:0]data;
  
 u1=(data>>1)+(data>>2)+(data>>5);
 
 endfunction 
 
 
 function [15:0]u2;
    
 input [15:0]data;
  
 u2=(data>>1)+(data>>5)+(data>>6);
 
 endfunction 
 
 
 function [15:0]u3;
    
 input [15:0]data;
  
 u3=(data>>1)+(data>>2)+(data>>3)+(data>>4)+(data>>5)+(data>>6);
 
 endfunction 
 
 
 function [15:0]u4;
    
 input [15:0]data;
  
 u4=(data>>3)+(data>>4);
 
 endfunction
 
 function [15:0]u5;
    
 input [15:0]data;
  
 u5=(data>>1)+(data>>2)+(data>>3)+(data>>4)+(data>>5)+(data>>6);
 
 endfunction 
 
 
 function [15:0]u6;
    
 input [15:0]data;
  
 u6=(data>>3)+(data>>4)+(data>>7)+(data>>8);
 
 endfunction 
 
 function [15:0]u7;
    
 input [15:0]data;
 
 u7=(data>>1)+(data>>2)+(data>>5);
 
 endfunction 
 
 function [15:0]u8;
    
 input [15:0]data;
  
 u8=(data>>1)+(data>>4);
 
 endfunction 
 
 

     
function [15:0]s0;
    
 input [15:0]data;
  
 s0=(data>>2)+(data>>6)+(data>>4)+(data>>5);
 
 endfunction 
      
      
      
 
 
               
endmodule 
               