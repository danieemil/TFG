#ifndef _TIMPOINT_
#define _TIMPOINT_

#include "3ds.h"

#define MAX_TIME 18446744073709551615
#define FREQUENCY 268000000.0f


class Timepoint
{

public:
    // Constructores
    Timepoint(u64 p = 0);
    Timepoint(const Timepoint&);

    Timepoint& operator= (const Timepoint& t);
    void operator+ (float duration);
    void operator+ (u64 t_duration);
    float operator- (const Timepoint& t);
    bool operator<(const Timepoint& t);
    bool operator>(const Timepoint&);

    // Métodos


    // Setters
    void reset();

    // Getters
    u64 getPoint() const;
    float getElapsed();

    // Destructor
    ~Timepoint();

private:
    u64 point;

};

#endif