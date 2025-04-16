
# multithread-logger

A multithreaded logger in C++ intended as a refresher exercise.

## Running Basic Logger

 1. Compile it with `g++` or your favorite C++ compiler
`g++ -std=c++11 BasicLogger.cpp -o BasicLogger`
 2. Run it!
`./BasicLogger`
 3. Check the output!
`Thread 0 log entry 0
Thread 0 log entry 1
...
Thread 3 log entry 9`
Each line is written safely, without overlapping thanks to the `std::mutex`.
