/**********************************************
 * Self-Driving Car Nano-degree - Udacity
 *  Created on: December 11, 2020
 *      Author: Mathilde Badoual
 **********************************************/

#include "pid_controller.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kpi, double Kii, double Kdi, double output_lim_maxi, double output_lim_mini) {
   /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   **/
   Kp = Kpi;
   Kd = Kdi;
   Ki = Kii;
  
   output_lim_max = output_lim_maxi;
   output_lim_min = output_lim_mini;
}


void PID::UpdateError(double cte) {
   /**
   * TODO: Update PID errors based on cte.
   **/
   //first calculate differential term, being sure to not divide by 0
   if (delta_time == 0) {
     diff_err = 0;
   }
   else {
     diff_err = (cte - err) / delta_time;
   }
   
   //then integral term
   sum_err += (cte - err) * delta_time;
  
   //finally update error term itself
   err = cte;   
}

double PID::TotalError() {
   /**
   * TODO: Calculate and return the total error
   * The code should return a value in the interval [output_lim_mini, output_lim_maxi]
   */
   double control;
   
   // use errors to calculate control value
   control = -Kp * err - Kd * diff_err - Ki * sum_err;
   
   //ensure outpud is within defined limits
   control = max(control, output_lim_min);
   control = min(control, output_lim_max);
   
   std::cout << "Cte " << err << " Control: " << control << " P: " << -Kp * err << " I: " << - Ki * sum_err << " D: " << - Kd * diff_err << " T: " << delta_time << std::endl;
   
   return control;
}

double PID::UpdateDeltaTime(double new_delta_time) {
   /**
   * TODO: Update the delta time with new value
   */
   delta_time = new_delta_time;
}