# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

## Reflection
A PID controller is relatively simple to implement, the challenging part is choosing proper coefficients (Kp, Ki, Kd) that stabilize the system as a whole.

* P = Proportional (I like to think of it as the Present)
* I = Integral (I like to think of it as the past)
* D = Derivative (I like to think of it as the future)
Each time step, the simulator gives you CTE (cross track error), speed, and steering angle. The CTE is how far the car drifts from the center of the road. The mission was to adjust the coefficients `(Kp, Ki, Kd)` so that it minimized the CTE.

I've only implemented a controller for the steering angle and kept the speed constant. Hence my controller would calculate the steering angle as follows:
```
double PID::steering() {
  double steer = -Kp*p_error - Ki*i_error  - Kd*d_error;

  if (steer < MIN_STEER)
    steer = MIN_STEER; //-1

  if (steer > MAX_STEER)
    steer = MAX_STEER; //1

  return steer;
}
```
-`Kp*p_error` is responsible for keeping track of the present error. It responds in proportion to the CTE.

-`Ki*i_error` is the past, this is responsible for correcting system biases.

- `Kd*d_error` is responsible for keeping track of the future. How will the error change in the future? This is needed mostly to reduce oscillation that is usually caused by having just a P controller with high Kp gain.

Since the simulator calculates the CTE for me, I can handle the rest and compute the needed errors as follows:
```
void PID::UpdateError(double cte) {
  p_error = cte;
  if (prev_cte == numeric_limits<double>().max())
    prev_cte = cte;

  d_error = cte - prev_cte;
  prev_cte = cte;

  i_error += cte;
}
```
## How the hyperparameters were chosen.
The coefficients where chosen using a manual twiddle algorithm. I first started with just the Kp. I reduced the speed and set Kp such that I had min zig-zag. Then I introduced Kd to reduce the zig-zag even more. At this point, I'd slowly bump the speed and observe the car. If it starts to zig-zag, I'd repeat the process. Ki seems to only make the stability worse, do I left it at zero. This in essentially made my PID controller a PD controller!
---

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).

