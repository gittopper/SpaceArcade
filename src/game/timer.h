#pragma once

#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

using Clock = std::chrono::system_clock;

class Timer {
  public:
    Timer() {}

    double totalTime() const {
        return total_time_;
    }

    int getN() const {
        return n_;
    }

    double getAvgTime() const {
        return n_ > 0 ? total_time_ / n_ : time();
    }

    void start() {
        begin_time_ = now();
        is_running_ = true;
    }
    double stop() {
        std::chrono::duration<double> diff = now() - begin_time_;
        elapsed_time_ = diff.count();
        ++n_;
        total_time_ += elapsed_time_;
        is_running_ = false;
        return elapsed_time_;
    }

    double time() const {
        if (!is_running_) {
            return total_time_;
        }
        std::chrono::duration<double> diff = now() - begin_time_;
        return total_time_ + diff.count();
    }
    void reset() {
        total_time_ = 0;
        elapsed_time_ = 0;
        n_ = 0;
    }

    bool isRunning() const {
        return is_running_;
    }

    static std::string asString(float t, bool with_ms = true) {
        int ms = int(t * 1000) % 1000;
        auto time_int = static_cast<int>(t);
        int s = time_int % 60;
        int m = time_int / 60;
        int h = time_int / 3600;
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << h << ":";
        ss << std::setw(2) << std::setfill('0') << m << ":";
        ss << std::setw(2) << std::setfill('0') << s;
        if (with_ms) {
            ss << "." << ms;
        }
        return ss.str();
    }

    std::string elapsedAsString(bool with_ms = true) const {
        return asString(time(), with_ms);
    }

    ~Timer() {}

    // in seconds
    static Clock::time_point now() {
        return Clock::now();
    }

  private:
    Clock::time_point begin_time_;
    int n_ = 0;
    double total_time_ = 0;
    double elapsed_time_ = 0;
    bool is_running_;
};

inline std::string getTimestamp() {
    auto time = Clock::now();
    auto timestamp_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                            time.time_since_epoch())
                            .count();
    auto t = std::chrono::system_clock::to_time_t(time);
    struct tm* tm = localtime(&t);
    char buf[100] = {};
    strftime(buf, 100, "%Y.%m.%d %H:%M:%S.", tm);
    std::stringstream ss;
    ss << buf;
    ss << std::setw(3) << std::setfill('0') << (timestamp_ms) % 1000;
    return ss.str();
}
