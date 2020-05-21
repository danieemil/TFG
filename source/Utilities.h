#ifndef _UTILITIES_
#define _UTILITIES_

#include <math.h>

using namespace std;
namespace utilities
{
    // PI DEFINITION
    const float PI_F = 3.14159265358979f;

    template <class C>
    C mapValue(const C& s, const C& a1, const C& a2, const C& b1, const C& b2)
    {
        return b1 + ( (s-a1) * (b2 - b1) / (a2 - a1));
    }

    template <class T>
    int sign(const T& v)
    {
        return (v > T(0)) - (v < T(0));
    }

    inline float clamp(const float& min, const float& max, float value)
    {
        if(value < min)
        {
            value = min;
        }else if(value > max)
        {
            value = max;
        }
        
        return value;
    }

    template <class T>
    class Vector2d
    {
        public:
        T x;
        T y;

        Vector2d<T>(T px, T py) : x(px), y(py) {};
        Vector2d<T>(const Vector2d<T>& v) : x(v.x), y(v.y) {};
        Vector2d<T>() : x(0), y(0){};

        Vector2d<T> Normal(){
            return Vector2d<T>(y, -x);
        }
        
        void Normalize(){ 
            float l = sqrt(x * x + y * y);
            x=x/l;
            y=y/l;
        }

        float Length() const
        {
            return sqrt((x * x) + (y * y));
        }

        float DotProduct(const Vector2d<T> & v) const
        {
            return x * v.x + y * v.y;
        }
        
        // The sign of the 2D cross product tells you whether the second vector is on the left or right
        // side of the first vector (the direction of the first vector being front)
        T CrossProduct(const Vector2d<T> &v) const
        {
                return x * v.y - y * v.x;
        }

        T AngleBetween(const Vector2d<T> &v) const
        {
            //The arc sine of the cross product would give you the angle in radians.
            T dot = this->CrossProduct(v);
            return asin(dot);
        }

        Vector2d<T> operator+(const Vector2d<T>& v) const{ return Vector2d<T>(x+v.x, y+v.y); }
        Vector2d<T> operator+(const float& f) const{ return Vector2d<T>(f+x, f+y); }
        void operator+=(const Vector2d<T>& v){ 
            x+=v.x;
            y+=v.y; 
        }
        Vector2d<T> operator-(const Vector2d<T>& v) const{ return Vector2d<T>(x-v.x, y-v.y); }
        Vector2d<T> operator-(const float& f) const{ return Vector2d<T>(x-f, y-f); }
        void operator-=(const Vector2d<T>& v){
            x-=v.x;
            y-=v.y;
        }
        Vector2d<T> operator*(const Vector2d<T>& v) const{ return Vector2d<T>(x*v.x,y*v.y); }
        Vector2d<T> operator*(const float& f) const{ return Vector2d<T>(f*x, f*y); }
        void operator*=(const Vector2d<T>& v){
            x = x*v.x;
            y = y*v.y;
        }
        void operator*=(const float& f){ 
            x = f*x;
            y = f*y;
        }
        Vector2d<T> operator/(const Vector2d<T>& v) const{ return Vector2d<T>(x/v.x, y/v.y); }
        Vector2d<T> operator/(const float& f) const{ return Vector2d<T>(x/f, y/f); }
        void operator/=(const Vector2d<T>& v){
            x = x/v.x;
            y = y/v.y;
        }
        void operator/=(const float& f){
            x = x/f;
            y = y/f;
        }
        Vector2d<T> operator=(const Vector2d<T> t){this->x = t.x; this->y = t.y;  return *this;}
        bool operator==(const Vector2d<T> t) const
        {
            if(this->x == t.x)
                if(this->y == t.y)
                    return true;
            return false;
        }

        ~Vector2d<T>(){};
        
    };
}

#endif