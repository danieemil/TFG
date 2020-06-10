#include "Timepoint.h"
#include "Unvisual_Engine.h"


//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Timepoint::Timepoint(u64 p)
{
    // P es la posición absoluta en el tiempo en el que se crea, si es cero se coge el momento actual
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

void Timepoint::operator+ (float duration)
{
    point = point + (u64(u64(duration)*u64(FREQUENCY)));
}

void Timepoint::operator+ (u64 t_duration)
{
    point = point + t_duration;
}

float Timepoint::operator- (const Timepoint& t)
{
    float res = 0;
    
    if(t.point < point)
    {
        res = (point - t.point)/FREQUENCY;
    }

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
    point = unvisual::getPausedPoint();
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

    float res = -1;
    
    u64 now = unvisual::getPausedPoint();

    if(now > point)
    {
        res = (now - point)/FREQUENCY;
    }

    return res;
}

//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Timepoint::~Timepoint()
{
    unvisual::eraseTimepoint(this);
}