#include <iostream>
#include <limits>
#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {

    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;

    p_error = 0;
    i_error = 0;
    d_error = 0;

    ///* Intialize the previous cte to maximum double
    prev_cte = numeric_limits<double>().max();
}

double PID::Steering() {
    double steer = -TotalError();

    if (steer < MIN_STEER)
        steer = MIN_STEER;

    if (steer > MAX_STEER)
        steer = MAX_STEER;

    return steer;
}

void PID::UpdateError(double cte) {
    p_error = cte;
    if (prev_cte == numeric_limits<double>().max())
        prev_cte = cte;

    d_error = cte - prev_cte;
    prev_cte = cte;

    i_error += cte;
}

double PID::TotalError() {
    return Kp*p_error + Ki*i_error  + Kd*d_error;
}

