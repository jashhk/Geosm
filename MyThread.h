#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
public:
    static void sleep( unsigned long _sec ) { QThread::sleep( _sec ); }
};

#endif // MYTHREAD_H
