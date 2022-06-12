module DigitalClk(
input clk,   //时钟接入
   	input clr,	//异步清零
   	input setm,  //设定分钟，连续按住后每一秒分钟加一
   	input seth,  //设定小时，连续按住后每一秒时钟加一
  	output reg[3:0]secondL,//秒数的低位 //秒采用8421BCD码的形式输出
   	output reg[3:0]secondH,//秒数的高位  
   	output reg[7:0]atog1, 
   	output reg[7:0]atog2, //这两个对应分钟的十位与各位，用数码输出。      
 );
            reg [3:0]minuteL;//分钟数的低位
            reg [3:0]minuteH;//分钟数的高位
            reg [3:0]hourL;//小时数的低位
            reg [3:0]hourH;//小时数的高位
            reg [3:0]digit1; //数码管，对应分钟的个位
            reg [3:0]digit2; //数码管，对应分钟的十位
            reg [26:0] counter;
            reg [7:0]minute;//记录当前分钟
            reg [7:0]hour;//记录当前小时
            reg [7:0]sec;//记录当前秒数
            integer i;
            integer j;
            integer k;
            
always@(posedge clk or posedge clr)
begin
    if(clr==1) //清零键按下时将所有数据置零
        begin
       counter<=0;
         secondL<=0;
         secondH<=0;
         minuteL<=0;
         minuteH<=0;
         hourH<=0;
         hourL<=0;
         minute<=0;
         hour<=0;
         sec<=0;
         end 
      else if(counter==50000000)//时间达到1s，因为板子是50MHz的。
      begin
        counter<=0;
        if(setm==1)//如果设置分钟建按下（连续按，每按一秒分钟加一）
        begin
            if(minute==59)
            begin 
                minute<=0;
                if(hour==23)//23:59进位变为00:00
                begin
                    hour<=0;
                end
                else
                begin
                    hour<=hour+1;
                end
            end
            else
            begin
                minute<=minute+1;
            end
        end
        if(seth==1)//如果设置小时建按下（连续按，每按一秒分钟加一）
        begin
            if(hour==23)
            begin
                hour<=0;
                minute<=0;
                minuteH<=0;
                minuteL<=0;
            end
            else
            begin
                hour<=hour+1;
            end
        end
       
        if(sec==59)//秒针进位
        begin
            sec<=0;
            if(minute==59)
            begin
                minute<=0;
                if(hour==23)//23:59进位后变00：00
                begin
                    hour<=0;
                end
                else if(hour<23)
                begin
                    hour<=hour+1;
                end                 
            end
            else if(minute<59)//分钟数进位
            begin
            minute<=minute+1;
            end                 
        end
        else if(seth==0&&setm==0)//在调时，调分键没有按下的情况下，秒钟计数
        begin
            sec<=sec+1;
        end
        for(i=0;i<6;i=i+1)//分离出秒钟数的个位和十位
        begin
            if(sec[7:0]-i*10<10)
            begin
                secondH<=i;
                secondL<=sec[7:0]-i*10;
                //i=6;
            end
        end
        for(j=0;j<6;j=j+1)//分离出分钟数的个位和十位
        begin
            if(minute[7:0]-j*10<10)
            begin
                minuteH<=j;
                minuteL<=minute[7:0]-j*10;
                //j=6;
            end
        end
        for(k=0;k<3;k=k+1)//分离出十钟数的个位和十位
        begin
            if(hour[7:0]-k*10<10)
            begin
                hourH<=k;
                hourL<=hour[7:0]-k*10;
                //k=3;
            end
        end
      end
                    
      else
      begin
         counter<=counter+1;
      end
end
//数码管显示
always@(*)
   begin
        digit1<=minuteL[3:0];
        digit2<=minuteH[3:0];

      case(digit1)
       0:atog2=8'b0111_1110;
       1:atog2=8'b0001_0010;
       2:atog2=8'b1011_1100;    
       3:atog2=8'b1011_0110;
       4:atog2=8'b1101_0010;
       5:atog2=8'b1110_0110;
       6:atog2=8'b1110_1110;
       7:atog2=8'b0011_0010;
       8:atog2=8'b1111_1110;
       9:atog2=8'b1111_0110;
       default:atog1=8'b0000001;
     endcase
     
        case(digit2)
       0:atog1=8'b0111_1110;
       1:atog1=8'b0001_0010;
       2:atog1=8'b1011_1100;    
       3:atog1=8'b1011_0110;
       4:atog1=8'b1101_0010;
       5:atog1=8'b1110_0110;
       6:atog1=8'b1110_1110;
       7:atog1=8'b0011_0010;
       8:atog1=8'b1111_1110;
       9:atog1=8'b1111_0110;
       default:atog1=8'b0000001;
     endcase
    end
endmodule
