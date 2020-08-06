#include "Collider.h"
#include "Physics_Engine.h"


using namespace physics;

//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Collider::Collider(const Vector2d<float>& pos, Shape* s, const CollisionFlag& f, const CollisionType& t, void* c, int i, float a, const Vector2d<float>& rot_cent, const Vector2d<float>& vel)
: shape(nullptr), position(pos), previous_position(pos), flags(f), type(t), creator(c), index(i), angle(a), rotation_center(rot_cent), velocity(vel)
{

    setShape(s);

    if(flags != CollisionFlag::none)
    {
        addCollider(this);
    }
    
    if (type == CollisionType::col_static)
    {
        addStatic(this);
        velocity = Vector2d<float>();
    }
    else if (type == CollisionType::col_dynamic)
    {
        addDynamic(this);
    }
}

Collider::Collider(const Collider& c)
: shape(nullptr), position(c.position), previous_position(c.previous_position), bounds(c.bounds), flags(c.flags), creator(nullptr), index(-1), angle(c.angle), rotation_center(c.rotation_center), velocity(c.velocity)
{
    setShape(c.shape);

    if(flags != CollisionFlag::none)
    {
        addCollider(this);
    }
    
    if (type == CollisionType::col_static)
    {
        addStatic(this);
        velocity = Vector2d<float>();
    }
    else if (type == CollisionType::col_dynamic)
    {
        addDynamic(this);
    }

}

Collider& Collider::operator= (const Collider& c)
{
    setShape(c.shape);

    position = c.position;
    previous_position = c.previous_position;
    bounds = c.bounds;
    creator = nullptr;
    index = -1;
    angle = c.angle;
    rotation_center = c.rotation_center;
    velocity = c.velocity;

    setFlags(c.flags);
    setType(c.type);

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

// Detecta si los bounds intersectan con los de "c"
bool Collider::intersectBounds(Collider* c)
{
    if(c!=nullptr)
    {
        return bounds.intersects(c->bounds);
    }
    return false;
}

// Detecta y corrige si las figuras(shapes) intersectan con las de "c".
Intersection* Collider::intersectShapes(Collider* c)
{
    if (c!=nullptr)
    {
        Shape* s = c->getShape();
        if(shape!=nullptr && s!=nullptr)
        {
            Intersection* inter = shape->intersect(s);

            if(inter!=nullptr)
            {
                return inter;
            }
        }
    }
    return nullptr;
}

void Collider::intersectFix(Intersection* inter)
{
    if(inter!=nullptr && inter->intersects)
    {
        position = inter->fixed_position;
        
        // Si se choca, su velocidad se reduce en función de la intersección producida.
        /*
        Vector2d<float> o = inter->overlap;
        o.Normalize();
        o = o * velocity.Length();
        Vector2d<float> r_vel = velocity + o;

        if(sign(r_vel.x)!=sign(velocity.x)) velocity.x = 0.0f;
        else velocity.x = r_vel.x;

        if(sign(r_vel.y)!=sign(velocity.y)) velocity.y = 0.0f;
        else velocity.y = r_vel.y;
        */
    }
}

Intersection* Collider::intersectSegment(const Vector2d<float>& a, const Vector2d<float>& b)
{
    if(bounds.intersects(Bounding_Box(Vector2d<float>(std::min(a.x,b.x),std::min(a.y,b.y)),Vector2d<float>(std::max(a.x,b.x),std::max(a.y,b.y)))))
    {
        if(bounds.intersects(a, b))
        {
            Intersection* i = nullptr;

            if(shape!=nullptr)
            {
                i = shape->intersect(a, b);

                if(i!=nullptr)
                {
                    return i;
                }
            }
        }
    }
    return nullptr;
}

bool Collider::isStatic() const
{
    return (type == CollisionType::col_static);
}

void Collider::update(float dt)
{
    previous_position = position;
    position = position + velocity * dt;

    calculateValues();
}


//=========================================
//=               SETTERS   	    	  =
//=========================================

void Collider::setShape(Shape* s)
{
    if(shape!=nullptr)
    {
        delete shape;
    }
    shape = s;

    if(shape!=nullptr)
    {
        shape->setCollider(this);
        calculateValues();
    }
}

void Collider::setPosition(const Vector2d<float>& pos)
{
    previous_position = position;
    position = pos;

    calculateValues();
}

void Collider::setFlags(const CollisionFlag& f)
{

    if(flags != CollisionFlag::none)
    {
        removeCollider(this);
    }

    flags = f;

    if(flags != CollisionFlag::none)
    {
        addCollider(this);
    }

}

void Collider::setType(const CollisionType& t)
{

    if (type == CollisionType::col_static)
    {
        removeStatic(this);
    }
    else if (type == CollisionType::col_dynamic)
    {
        removeDynamic(this);
    }

    type = t;

    if (type == CollisionType::col_static)
    {
        addStatic(this);
        velocity = Vector2d<float>();
    }
    else if (type == CollisionType::col_dynamic)
    {
        addDynamic(this);
    }
}

void Collider::setCreator(void* c)
{
    creator = c;
}

void Collider::setIndex(int i)
{
    index = i;
}

void Collider::setGlobalRotation(float a)
{
    angle = a;
    if (shape!=nullptr)
    {
        shape->setGlobalRotation();
    }
    calculateValues();
}

void Collider::setLocalsRotation(float a)
{
    if (shape!=nullptr)
    {
        shape->setLocalRotation(a);
    }
    calculateValues();
}

void Collider::setRotationCenter(const Vector2d<float>& rot_cent)
{
    rotation_center = rot_cent;
}

void Collider::setVelocity(const Vector2d<float>& vel)
{
    velocity = vel;
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

Shape* Collider::getShape() const
{
    return shape;
}

const Vector2d<float>& Collider::getPosition() const
{
    return position;
}

const Vector2d<float>& Collider::getPreviousPosition() const
{
    return previous_position;
}

const Bounding_Box& Collider::getBounds() const
{
    return bounds;
}

const CollisionFlag& Collider::getFlags() const
{
    return flags;
}

const CollisionType& Collider::getType() const
{
    return type;
}

void* Collider::getCreator() const
{
    return creator;
}

int Collider::getIndex() const
{
    return index;
}

float Collider::getRotation() const
{
    return angle;
}

const Vector2d<float>& Collider::getRotationCenter() const
{
    return rotation_center;
}

const Vector2d<float>& Collider::getVelocity() const
{
    return velocity;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Collider::~Collider()
{

    if(shape!=nullptr)
    {
        delete shape;
        shape = nullptr;
    }

    if(flags != CollisionFlag::none)
    {
        removeCollider(this);
    }
    
    if (type == CollisionType::col_static)
    {
        removeStatic(this);
    }
    else if (type == CollisionType::col_dynamic)
    {
        removeDynamic(this);
    }
}


//=========================================
//=               PRIVATE   	    	  =
//=========================================

// Recalcula los datos de la bounding box
void Collider::calculateValues()
{
    if(shape!=nullptr)
    {
        bounds = Bounding_Box(shape->getMin(), shape->getMax());
    }

}