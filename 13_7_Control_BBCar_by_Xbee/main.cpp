#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"

Ticker servo_ticker;
PwmOut pin9(D9), pin8(D5);
Serial xbee(D12, D11);
BBCar car(pin8, pin9, servo_ticker);

int main() {
    double pwm_table0[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150};
    
    //D9 blue
    double speed_table0[] = {-16.906, -16.668, -15.870, -13.159, -6.938, 0.000, 5.582, 11.962, 15.471, 16.588, 17.066};
    
    double pwm_table1[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150};
    double speed_table1[] = {-17.002, -16.766, -15.809, -12.539, -5.841, 0.000, 6.080, 12.539, 15.889, 17.005, 17.404};
    car.setCalibTable(11, pwm_table0, speed_table0, 11, pwm_table1, speed_table1);
    
    char buf[256], outbuf[256];
    while (1) {
        for( int i=0; ;i++ ) {
            buf[i] = xbee.getc();
            if(buf[i] == '\n') break;
        }

        RPC::call(buf, outbuf);
        xbee.printf("%s\r\n", outbuf);
    }
}