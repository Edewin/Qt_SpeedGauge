#ifndef DELAYCLASS
#define DELAYCLASS

#include <QThread>

class Delay : public QThread{
public:
    static void sleep(unsigned long seconds)       {QThread::sleep(seconds);}
    static void msleep(unsigned long milliSeconds) {QThread::msleep(milliSeconds);}
    static void usleep(unsigned long microSeconds) {QThread::usleep(microSeconds);}
};

#endif // DELAYCLASS

