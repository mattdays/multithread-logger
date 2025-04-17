
  

# multithread-logger
A multithreaded logger in C++ intended as a refresher exercise.

## Running Basic Logger
1. Compile it with `g++` or your favorite C++ compiler
`g++ -std=c++11 BasicLogger.cpp -o BasicLogger`

2. Run it!
`./BasicLogger`

3. Check the output!
```
Thread 0 log entry 0
Thread 0 log entry 1
...
Thread 3 log entry 9
```
Each line is written safely, without overlapping thanks to the `std::mutex`.

## Running Advanced Logger
1. Compile it with `g++` or your favorite C++ compiler
`g++ -std=c++11 AdvancedLogger.cpp -o advanced_logger -pthread`
2. Run it!
`./AdvancedLogger`
3. Check the output! It should look something like this:
```
[2025-04-17 15:50:55.103] Thread 0: Log 0
[2025-04-17 15:50:55.103] Thread 3: Log 0
[2025-04-17 15:50:55.104] Thread 0: Log 1
...
[2025-04-17 15:50:55.104] Thread 1: Log 9
```
Each thread logs 10 messages, and you spawn 4 threads, so you’ll see 40 lines total in `advanced_log.txt`. But since threads run concurrently and queue up messages at different rates, the order will be mixed. What IS guaranteed via the thread-safe queue and background writer thread:

* No logs should be missing

* No logs should be corrupted or interleaved mid-line

* Every message should be complete and appear on own line