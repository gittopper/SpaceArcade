#ifndef TIMER_H
#define TIMER_H
#include <string>
#include <time.h>
#include <logger.hpp>

class Timer
{
public:
    Timer(){}

    int getN() const { return n;}

    float getAvgTime() const { return n > 0 ? totalT / n : 0;}

    void start()
    {
        begin_time = clock();
        running = true;
    }
    float stop()
    {
        if (!running) return time();
        float curTime = clock();
        elapsedTime = (curTime - float(begin_time)) / CLOCKS_PER_SEC;
        running = false;
        n++;
        totalT += elapsedTime;
        return elapsedTime;
    }

    float time() const
    {
        if (running)
        {
            float curTime = clock();
            elapsedTime = (curTime - float(begin_time)) / CLOCKS_PER_SEC;
        }
        return elapsedTime;
    }
    void reset()
    {
        elapsedTime = 0;
        running = false;
    }

    static std::string asString(float t)
    {
        float s = t - int(t / 60) * 60;
        float m = t = (t - s) / 60;
        float h = t = (t - m) / 60;
        return getLogString(h, ":", m, ":", s );
    }

    std::string asString()
    {
        return asString(time());
    }

    ~Timer(){}
private:
    mutable clock_t begin_time = 0;
    mutable int n = 0;
    mutable float totalT = 0;
    mutable float elapsedTime = 0;
    mutable bool running = false;
};
inline std::string getTimeStamp()
{
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );

    return getLogString(now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec);
}

#endif // TIMER_H
