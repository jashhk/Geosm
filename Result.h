#ifndef RESULT_H
#define RESULT_H

#include <string>

using namespace std;

class Result
{
private:
    bool stable;
    double EHP;
    string* msg;

public:
    Result( bool _stable , double _EHP , string* _msg )
    {
        stable = _stable;
        EHP = _EHP;
        msg = _msg;
    }

    bool isStable() { return  stable; }
    double get_EHP() { return  EHP; }
    string get_msg( int _pos ) { return  msg[_pos]; }
};

#endif // RESULT_H
