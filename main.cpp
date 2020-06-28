#include "mbed.h"

#include "bbcar.h"


Ticker servo_ticker;

Ticker encoder_ticker;
DigitalInOut pin10(D10);   //ping
PwmOut pin8(D8), pin9(D9);  // servo

DigitalIn pin3(D3);  // encodera
Serial pc(USBTX,USBRX); 
Serial uart(D1,D0); // OpenMV
Serial xbee(D12, D11); // Xbee

float info[50];


BBCar car(pin8, pin9, servo_ticker);


int main() {
    
    parallax_encoder encoder0(pin3, encoder_ticker);
    parallax_ping  ping1(pin10);
    encoder0.reset();
    xbee.printf("connected!\r\n"); 
// straight 150cm
    car.goStraight(100);

    while(ping1>19) wait_ms(50);
    xbee.printf("goStraight!\r\n"); 
    car.stop();
    wait_ms(50);
// turn left
    car.turn(90,-0.5);
    wait_ms(1000);
    xbee.printf("left!\r\n");
    car.stop();
    wait_ms(50);

//        mission 1
// straight to 3
    car.goStraight(100);
    while(ping1>16) wait_ms(50);
    xbee.printf("goStraight!\r\n");
    car.stop();
    wait_ms(50);
// turn right
    car.turn(120,0.5);
    wait_ms(1000);
    xbee.printf("right!\r\n");
    car.stop();
    wait_ms(50);
// spot
    car.goStraight(-100);
    wait_ms(2200);
    xbee.printf("back!\r\n");
    car.stop();
    wait_ms(1000);
// get away the spot
    car.goStraight(100);
    while(ping1>18) wait_ms(50);
    xbee.printf("goStraight!\r\n");
    car.stop();
    wait_ms(50);
//turn right
    car.turn(120,0.5);
    wait_ms(1000);
    xbee.printf("right!\r\n");
    car.stop();
    wait_ms(1000);
// go stright
    car.goStraight(100);           
    wait_ms(2800);
    xbee.printf("goStraight!\r\n");
    car.stop();
    wait_ms(50);
 // turn left
    car.turn(90,-0.5);
    wait_ms(1000);
    xbee.printf("left!\r\n");
    car.stop();
    wait_ms(50);   
// take picture
    car.stop();
    wait_ms(1000);
    xbee.printf("picture!\r\n");
    wait_ms(1000);
    char s[21];
    sprintf(s,"image_classification"); // sent the command to OpenMV for taking picture
    uart.puts(s); // sent the command by UART
    wait_ms(1000);
//turn right
    car.turn(120,0.5);
    wait_ms(1000);
    xbee.printf("right!\r\n");
    car.stop();
    wait_ms(50);
// go stright
    car.goStraight(100);
    xbee.printf("goStraight!\r\n");           
    wait_ms(1900);
    car.stop();
    wait_ms(50);

// straight way
//turn right
    car.turn(120,0.5);
    wait_ms(1000);
    xbee.printf("right!\r\n");
    car.stop();
    wait_ms(50);
// go stright
    car.goStraight(100);           
    while(ping1>20) wait_ms(50);
    xbee.printf("goStraight!\r\n");
    car.stop();
    wait_ms(50);

// mission 2
//turn right
    car.turn(120,0.5);
    wait_ms(1000);
    xbee.printf("right!\r\n");
    car.stop();
    wait_ms(50);
// go stright
    car.goStraight(100);           
    wait_ms(3800);
    xbee.printf("goStraight!\r\n");
    car.stop();
    wait_ms(50);
//turn right
    car.turn(120,0.5);
    wait_ms(1000);
    xbee.printf("right!\r\n");
    car.stop();
    wait_ms(500);
// go stright
    car.goStraight(100);           
    wait_ms(1800);
    xbee.printf("goStraight!\r\n");
    car.stop();
    wait_ms(50);
// turn left mission2 target
    car.turn(90,-0.5);
    wait_ms(1000);
    car.stop();
     wait_ms(1000);
    xbee.printf("left!\r\n");
    xbee.printf("scan!\r\n");
    // save the ping data
    for(int i=0;i<50;i++)
    {
        info[i] = ping1;
        wait_ms(50);
    }
    xbee.printf("exit!\r\n");
// exit
//turn right
    car.turn(120,0.5);
    wait_ms(1000);xbee.printf("right!\r\n");
    car.stop();
    wait_ms(50);
// go stright back
    car.goStraight(-100);           
    wait_ms(1650);xbee.printf("back!\r\n");
    car.stop();
    wait_ms(1000);
// turn left
    car.turn(90,-0.5);
    wait_ms(1000);xbee.printf("left!\r\n");
    car.stop();
    wait_ms(1000);
// go stright
    car.goStraight(100);           
    while(ping1>15) wait_ms(50);
    xbee.printf("goStraight!\r\n");
    car.stop();
    wait_ms(500);
//turn right
    car.turn(90,0.5);
    wait_ms(1300);
    xbee.printf("right!\r\n");
    car.stop();
    wait_ms(500);
// go stright 
    car.goStraight(100);           
    while(ping1>22) wait_ms(50);
    xbee.printf("goStraight!\r\n");
    car.stop();
    wait_ms(50);
// ping data
    int flag = 0;

    for(int i=0;i<50;i++)

    {
        wait_ms(100);
        if(info[i]>10) flag=3;
        else if(info[i]<10) flag=1;
        else if(info[i]<8) flag=2;
        else (info[i]<10) flag=0;       
    }   
    if(flag==3) xbee.printf("object 3."); 
    else if(flag==1) xbee.printf("object 1."); 
    else if(flag==2) xbee.printf("object 2."); 
    else (flag==0) xbee.printf("object 0.");  
}