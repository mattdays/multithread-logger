/* 
 * Advanced Multithreaded Logger
 * - Background writer thread: Centralize file IO
 * - Thread-safe Message Queue: Avoid blocking worker threads
 */

#ifndef ADVANCED_LOGGER_H_
#define ADVANCED_LOGGER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <iomanip>
#include <sstream>

class AdvancedLogger {
public:
    AdvancedLogger(const std::string& filename);

    ~AdvancedLogger();

    void log(const std::string& message);
private:
    void processLogs(); // background thread loop

    std::ofstream logfile_;
    std::thread logThread_;

    std::queue<std::string> logQueue_;
    std::mutex queueMutex_;
    std::condition_variable cv_;

    std::atomic<bool> isRunning_;
};
#endif // ADVANCED_LOGGER_H_