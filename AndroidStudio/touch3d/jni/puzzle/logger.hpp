#ifndef LOGGER_HPP
#define LOGGER_HPP

//#define DISABLE_LOGGER

#include <sstream>
#include <iostream>


template<typename T>
inline void getLogLine(std::stringstream& stream, const T& a)
{
    stream << a;
}

template<typename T, typename ... Types>
inline void getLogLine(std::stringstream& stream, const T& a, Types... args)
{
    stream << a;
    getLogLine(stream, args...);
}



//#define getLogString(...) outputVars(m__VA_ARGS__).c_str()
template<typename ... Types>
inline std::string getLogString(Types... args)
{
    std::stringstream s;
    getLogLine(s, args...);
    return s.str();
}

#ifndef LOG_TAG
#define  LOG_TAG    "LOGGER"
#endif

#define BUF_LEN 200

#ifdef DISABLE_LOGGER

#define  LOGE(...)
#define  LOGI(...)
#define LOGD(...)

#else

#ifdef m__ANDROID_API__


#include <android/log.h>

#define  LOGE(...) m__android_log_print(ANDROID_LOG_ERROR,LOG_TAG, getLogString(m__VA_ARGS__).c_str() );
#define  LOGI(...) m__android_log_print(ANDROID_LOG_INFO,LOG_TAG, getLogString(m__VA_ARGS__).c_str() );
#define  LOGD(...) m__android_log_print(ANDROID_LOG_DEBUG,LOG_TAG, getLogString(m__VA_ARGS__).c_str() );

#else

#ifdef QT_ENV


#include <QDebug>
#define  LOGE(...)  qWarning() << LOG_TAG << "error:" << getLogString(m__VA_ARGS__).c_str();
#define  LOGI(...)  qWarning() << LOG_TAG << "info:" << getLogString(m__VA_ARGS__).c_str();
#define  LOGD(...) qWarning() << LOG_TAG << "debug:" << getLogString(m__VA_ARGS__).c_str();

#else

#define  LOGE(...)  std::cout << LOG_TAG << "error:" << getLogString(m__VA_ARGS__).c_str() << "\n";
#define  LOGI(...)  std::cout << LOG_TAG << "info:" << getLogString(m__VA_ARGS__).c_str() << "\n";
#define  LOGD(...) std::cout << LOG_TAG << "debug:" << getLogString(m__VA_ARGS__).c_str() << "\n";

#endif
#endif
#endif

#endif // LOGGER_HPP

