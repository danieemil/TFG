#ifndef _UTILITIES_
#define _UTILITIES_

namespace utilities
{
    // PI DEFINITION
    const float  PI_F = 3.14159265358979f;

    template <class C>
    C mapValue(C s, C a1, C a2, C b1, C b2)
    {
        return b1 + ( (s-a1) * (b2 - b1) / (a2 - a1));
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
        
        void Normalize(){ 
            float l = sqrt(x * x + y * y);
            x=x/l;
            y=y/l;
        }

        float Length()
        {
            return sqrt((x * x) + (y * y));
        }
        
        // The sign of the 2D cross product tells you whether the second vector is on the left or right
        // side of the first vector (the direction of the first vector being front)
        T CrossProduct(const Vector2d<T> &v)
        {
                return x * v.y - y * v.x;
        }

        float AngleBetween(const Vector2d<T> &v)
        {
            //The arc sine of the cross product would give you the angle in radians.
            float dot = this->CrossProduct(v);
            return asin(dot);
        }

        Vector2d<T> operator+(const Vector2d<T>& v){ return Vector2d<T>(x+v.x, y+v.y); }
        Vector2d<T> operator+(float f){ return Vector2d<T>(f+x, f+y); }
        void operator+=(const Vector2d<T>& v){ 
            x+=v.x;
            y+=v.y; 
        }
        Vector2d<T> operator-(const Vector2d<T>& v){ return Vector2d<T>(x-v.x, y-v.y); }
        Vector2d<T> operator-(float f){ return Vector2d<T>(x-f, y-f); }
        Vector2d<T> operator*(float f){ return Vector2d<T>(f*x, f*y); }
        void operator*=(float f){ 
            x = f*x;
            y = f*y;
        }
        Vector2d<T> operator/(float f){ return Vector2d<T>(x/f, y/f); }
        Vector2d<T> operator=(const Vector2d<T> t){this->x = t.x; this->y = t.y;  return *this;}
        bool         operator==(const Vector2d<T> t) const
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