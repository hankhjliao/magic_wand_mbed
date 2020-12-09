# Data Collection

## Getting Started

1. mbed OS Version: 5.14.0

## Usage
1. `$ sudo mbed compile -m K66F -t GCC_ARM -f`
2. `$ sudo python3 data_collect.py`
3. Hold the SW2 to record the gesture. Press the SW3 to delete the previous record.
4. Press 'Ctrl + C' to terminate the program, and the program will give you a text file starting with `gesture_`.
5. Rename the file to gesture_<label>.txt and move it to folder ../../data/raw.  
   `$ sudo mv gesture_<time>.txt ../data/raw/gesture_<label>.txt`  
   Note: `<time>` is like 202004081520; `<label>` is like ring.

<br>

BTW, I have already recorded two gestures in ../../data/raw.  
One is [ring](../../img/gesture_ring); the other is [slope](../../img/gesture_slope.png).

## Known Issues
1. If you release SW2 but the it is still recording, just press the SW2 several times until it stops.

