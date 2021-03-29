#ifndef _UTILITIES_
#define _UTILITIES_

#include <math.h>

using namespace std;
namespace utilities
{
    // PI DEFINITION
    const float PI_F = 3.14159265358979f;

    template <class T>
    T mapValue(const T& s, const T& a1, const T& a2, const T& b1, const T& b2)
    {
        return b1 + ( (s-a1) * (b2 - b1) / (a2 - a1));
    }

    template <class T>
    int sign(const T& v)
    {
        return (v > T(0)) - (v < T(0));
    }

    template <class T>
    T clamp(const T& min, const T& max, T value)
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

    template<class T>
    T toRadians(const T& angle)
    {
        return angle * PI_F / 180.0f;
    }

    template<class T>
    T toDegrees(const T& radians)
    {
        return radians * 180.0f / PI_F;
    }

    template <class T>
    class Vector2d
    {
        public:
        T x;
        T y;

        Vector2d<T>(T px = 0, T py = 0) : x(px), y(py) {};
        Vector2d<T>(const Vector2d<T>& v) : x(v.x), y(v.y) {};

        Vector2d<T> Normal(){
            return Vector2d<T>(-y, x);
        }
        
        void Normalize(){ 
            float l = sqrt(x * x + y * y);
            x=x/l;
            y=y/l;
        }

        T Length() const
        {
            return sqrt((x * x) + (y * y));
        }

        T DotProduct(const Vector2d<T> & v) const
        {
            return x * v.x + y * v.y;
        }
        
        // The sign of the 2D cross product tells you whether the second vector is on the left or right
        // side of the first vector (the direction of the first vector being front)
        T CrossProduct(const Vector2d<T> &v) const
        {
                return v.x * y - x * v.y;
        }

        T AngleBetween(const Vector2d<T> &v) const
        {
            //The arc sine of the cross product would give you the angle in radians.
            T dot = this->CrossProduct(v);
            return asin(dot);
        }

        Vector2d<T> operator+(const Vector2d<T>& v) const{ return Vector2d<T>(x+v.x, y+v.y); }
        Vector2d<T> operator+(const T& f) const{ return Vector2d<T>(f+x, f+y); }
        void operator+=(const Vector2d<T>& v){ 
            x+=v.x;
            y+=v.y; 
        }
        Vector2d<T> operator-(const Vector2d<T>& v) const{ return Vector2d<T>(x-v.x, y-v.y); }
        Vector2d<T> operator-(const T& f) const{ return Vector2d<T>(x-f, y-f); }
        void operator-=(const Vector2d<T>& v){
            x-=v.x;
            y-=v.y;
        }
        Vector2d<T> operator*(const Vector2d<T>& v) const{ return Vector2d<T>(x*v.x,y*v.y); }
        Vector2d<T> operator*(const T& f) const{ return Vector2d<T>(f*x, f*y); }
        void operator*=(const Vector2d<T>& v){
            x = x*v.x;
            y = y*v.y;
        }
        void operator*=(const T& f){ 
            x = f*x;
            y = f*y;
        }
        Vector2d<T> operator/(const Vector2d<T>& v) const{ return Vector2d<T>(x/v.x, y/v.y); }
        Vector2d<T> operator/(const T& f) const{ return Vector2d<T>(x/f, y/f); }
        void operator/=(const Vector2d<T>& v){
            x = x/v.x;
            y = y/v.y;
        }
        void operator/=(const T& f){
            x = x/f;
            y = y/f;
        }
        Vector2d<T> operator=(const Vector2d<T>& t){this->x = t.x; this->y = t.y;  return *this;}
        bool operator==(const Vector2d<T>& t) const
        {
            if(this->x == t.x)
                if(this->y == t.y)
                    return true;
            return false;
        }

        bool operator!=(const Vector2d<T>& t) const
        {
            if(x != t.x || y != t.y)
                return true;
            return false;
        }

        ~Vector2d<T>(){};
        
    };
}

#endif