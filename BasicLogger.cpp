#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>
#include <vector>

class BasicLogger {
public:
    BasicLogger(const std::string& filename) {
        logfile_.open(filename, std::ios::app);
    }

    ~BasicLogger() {
        logfile_.close();
    }

    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(logMutex_);
        logfile_ << message << std::endl;
    }

private:
    std::ofstream logfile_;
    std::mutex logMutex_;
};

int main() {
    BasicLogger basicLogger("log.txt");

    std::vector<std::thread> threads;

    for (int i = 0; i < 4; ++i) {
        threads.emplace_back([&basicLogger, i]() {
            for (int j = 0; j < 10; ++j) {
                basicLogger.log("Thread " + std::to_string(i) + " log entry " + std::to_string(j));
            }
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Logging done. Check 'log.txt'." << std::endl;
    return 0;
}