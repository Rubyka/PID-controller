#ifndef PID_H
#define PID_H

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;
  double prev_cte;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

  /*
   * Min and Max Steering
   */
  const double MAX_STEER = 1;
  const double MIN_STEER = -1;


  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
   * Computing the steering
   */
  double Steering();

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();
};

#endif /* PID_H */
