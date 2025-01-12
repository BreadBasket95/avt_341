
#include "avt_341/control/pid_controller.h"

namespace avt_341 {
namespace control{
  
PidController::PidController(){
  kp_ = 0.3;
  ki_ = 0.0;
  kd_ = 0.05;
  setpoint_ = 0.0;
  previous_error_ = 0.0;
  integral_ = 0.0;
  overshoot_limiter_ = true;
  crossed_setpoint_ = false;
}

// see: https://en.wikipedia.org/wiki/PID_controller
double PidController::GetControlVariable(double measured_value, double dt){
  double error = setpoint_ - measured_value;

  // if overshoot limiter turned on, set integral to zero each time it crosses the setpoint
  // see: https://en.wikipedia.org/wiki/Integral_windup
  if (overshoot_limiter_){
    if (error*previous_error_<0.0){
      integral_ = 0.0;
      crossed_setpoint_ = true;
    }
  }
  // if overshoot limiter turned on, set ki to zero until it crosses the setpoint the first time
  double ki = ki_;
  if ((!crossed_setpoint_) && overshoot_limiter_){
    ki = 0.0;
  }

  integral_ += error*dt;
  double derivative = (error - previous_error_)/dt;
  double output = kp_*error + ki*integral_ + kd_*derivative;
  previous_error_ = error;
  return output;
}

} // namespace control
} // namespace avt_341