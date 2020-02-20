#include "Timepoint.h"
#include "Unvisual_Engine.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Timepoint::Timepoint(u64 p)
{
    if(p==0)
    {
        point = svcGetSystemTick();
    }else
    {
        point = p;
    }

    unvisual::addTimepoint(this);
}

Timepoint::Timepoint(const Timepoint& t) : Timepoint(t.point)
{

}

Timepoint& Timepoint::operator= (const Timepoint& t)
{
    point = t.point;
    return *this;
}

Timepoint& Timepoint::operator+ (float duration)
{
    point = point + (u64(u64(duration)*u64(FREQUENCY)));

    return *this;
}

float Timepoint::operator- (const Timepoint& t)
{
    float res = (point - t.point)/FREQUENCY;

    return res;
}

bool Timepoint::operator<(const Timepoint& t)
{
    return point < t.point;
}

bool Timepoint::operator>(const Timepoint& t)
{
    return point > t.point;
}



//=========================================
//=               MÉTODOS   	    	  =
//=========================================




//=========================================
//=               SETTERS   	    	  =
//=========================================

void Timepoint::reset()
{
    point = svcGetSystemTick();
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

u64 Timepoint::getPoint() const
{
    return point;
}

float Timepoint::getElapsed()
{
    float res = (svcGetSystemTick() - point)/FREQUENCY;

    return res;
}

//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Timepoint::~Timepoint()
{
    unvisual::eraseTimepoint(this);
}