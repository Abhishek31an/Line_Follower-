A smart line follower robot built on the Arduino platform. It uses an array of five IR sensors to precisely track a black line on a white surface. 
The robot implements a PID (Proportional-Integral-Derivative) control algorithm for smooth and accurate steering corrections.

## 🤖 Hardware Connections

### Motor Driver (e.g., L298N)
* **Arduino Pin 5 (PWM)** -> Enable A (enA)
* **Arduino Pin 6 (PWM)** -> Enable B (enB)
* **Arduino Pin 2** -> Input 1 (in1)
* **Arduino Pin 3** -> Input 2 (in2)
* **Arduino Pin 4** -> Input 3 (in3)
* **Arduino Pin 7** -> Input 4 (in4)

### 5-Channel IR Sensor Array
* **Arduino Pin 12** -> Sensor 1 Output (out1)
* **Arduino Pin 11** -> Sensor 2 Output (out2)
* **Arduino Pin 10** -> Sensor 3 Output (out3)
* **Arduino Pin 9** -> Sensor 4 Output (out4)
* **Arduino Pin 8** -> Sensor 5 Output (out5)

### Other
* **Arduino Pin 13** -> On-board LED (used as an indicator)
