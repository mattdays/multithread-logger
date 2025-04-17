#include "AdvancedLogger.h"

AdvancedLogger::AdvancedLogger(const std::string& filename) : isRunning_(true) {
        logfile_.open(filename, std::ios::app);
        logThread_ = std::thread(&AdvancedLogger::processLogs, this);
}

AdvancedLogger::~AdvancedLogger() {
    isRunning_ = false;
    cv_.notify_all();
    if (logThread_.joinable()) {
        logThread_.join();
    }
    logfile_.close();
}

void AdvancedLogger::log(const std::string& message) {
    auto now = std::chrono::system_clock::now();
    auto now_time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    
    std::ostringstream timestamped;
    timestamped << "[" << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S")
    << "." << std::setfill('0') << std::setw(3) << ms.count() << "] " 
    << message;
    
    //Ensure that lock goes out of scope with curly braces
    {
        std::lock_guard<std::mutex> lk(queueMutex_);
        logQueue_.push(timestamped.str());
    }

    cv_.notify_one();
}

void AdvancedLogger::processLogs() {    
    while (isRunning_ || !logQueue_.empty()) {
        std::unique_lock<std::mutex> lock(queueMutex_);
        cv_.wait(lock, [this]() {
            return isRunning_ || !logQueue_.empty();
        });

        while (!logQueue_.empty()) {
            logfile_ << logQueue_.front() << std::endl;
            logQueue_.pop();
        }
    }
}

int main() {
    AdvancedLogger logger("advanced_log.txt");

    std::vector<std::thread> threads;
    for (auto i = 0u; i < 4; ++i) {
        threads.emplace_back(
            [&logger, i] {
                for (auto j = 0u; j < 10; ++j) {
                    logger.log("Thread " + std::to_string(i) + ": Log " + std::to_string(j));
                }
            }
        );
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Finished logging. Check 'advanced_log.txt'" << std::endl;
    return 0;
}