#include "mbed.h"
#include "bbcar.h"

Ticker servo_ticker;
PwmOut pin8(D5), pin9(D9);

BBCar car(pin8, pin9, servo_ticker);

int main() {
    // please contruct you own calibration table with each servo
    double pwm_table0[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150};
    double speed_table0[] = {-16.906, -16.668, -15.870, -13.159, -6.938, 0.000, 5.582, 11.962, 15.471, 16.588, 17.066};
    double pwm_table1[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150};
    double speed_table1[] = {-17.302, -17.066, -16.109, -12.839, -6.141, 0.000, 6.380, 12.839, 16.189, 17.305, 17.704};

    // first and fourth argument : length of table
    car.setCalibTable(11, pwm_table0, speed_table0, 11, pwm_table1, speed_table1);

    while (1) {
        car.goStraightCalib(12);
        wait(5);
        car.stop();
        wait(5);
    }
}