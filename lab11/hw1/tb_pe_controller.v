`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/28/2017 02:11:52 PM
// Design Name: 
// Module Name: tb_pe_controller
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module tb_con ();
// parameter L_RAM_SIZE = 4;
parameter L_RAM_SIZE = 6;
parameter CLK_PERIOD = 10;

reg aclk;
reg aresetn;
reg start;
reg [31:0] din;
wire done;
wire [2*L_RAM_SIZE:0] rdaddr;

//input data 
reg [31:0] din_mem [2**(L_RAM_SIZE*2) + 2**(L_RAM_SIZE) - 1:0];

// integer i;
initial begin
    aclk <= 0;
    start <= 0;
    aresetn<=0;
    
    #(CLK_PERIOD*5);
    aresetn<=1;
    
    #(CLK_PERIOD*5);
    start = 1;
    #(CLK_PERIOD);
    start = 0;
    
end

initial 
	$readmemh("din2.mem", din_mem);

always @(posedge aclk) 
    din <= din_mem[rdaddr];

always #(CLK_PERIOD/2) aclk = ~aclk;


pe_controller #(2**L_RAM_SIZE,L_RAM_SIZE) UUT(
    .start(start),
    .aclk(aclk),
    .aresetn(aresetn),
    .rddata(din),
    .done(done),
    .rdaddr(rdaddr)
);
    
endmodule
    
