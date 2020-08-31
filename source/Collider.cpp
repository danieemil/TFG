#include "Collider.h"
#include "Physics_Engine.h"


using namespace physics;

//=========================================
//=             CONSTRUCTORES	    	  =
//=========================================

Collider::Collider(const Vector2d<float>& pos, Shape* s,
const CollisionFlag& ft, const CollisionFlag& fi,
const CollisionType& t, void* c, Callback cb, int i, float a,
const Vector2d<float>& rot_cent,
const Vector2d<float>& vel, bool act,
const Vector2d<float>& m_vel,
const Vector2d<float>& accel,
const Vector2d<float>& m_accel,
const Vector2d<float>& frict,
const Vector2d<float>& imp)
: position(pos), previous_position(pos),
type_flags(ft), interested_flags(fi),
type(t), creator(c), callback(cb), index(i), angle(a),
rotation_center(rot_cent),
velocity(vel), active(act),
max_velocity(m_vel),
acceleration(accel),
max_acceleration(m_accel),
friction(frict),
impulse(imp)
{
    if(s!=nullptr)
    {
        addShape(s);
    }

    if((type_flags != CollisionFlag::none)||(interested_flags != CollisionFlag::none))
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
: position(c.position), previous_position(c.previous_position), bounds(c.bounds),
type_flags(c.type_flags), interested_flags(c.interested_flags),
creator(c.creator), callback(c.callback), index(-1), angle(c.angle),
rotation_center(c.rotation_center),
velocity(c.velocity), active(c.active),
max_velocity(c.max_velocity),
acceleration(c.acceleration),
max_acceleration(c.max_acceleration),
friction(c.friction),
impulse(c.impulse)

{
    for (auto it = c.shapes.begin(); it!=c.shapes.end(); it++)
    {
        Shape* s = (*it);

        if(s!=nullptr)
        {
            addShape(s);
        }
    }

    if((type_flags != CollisionFlag::none)||(interested_flags != CollisionFlag::none))
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
    for (auto it = c.shapes.begin(); it!=c.shapes.end(); it++)
    {
        Shape* s = (*it);

        if(s!=nullptr)
        {
            addShape(s);
        }
    }

    position = c.position;
    previous_position = c.previous_position;
    bounds = c.bounds;
    creator = c.creator;
    callback = c.callback;
    index = -1;
    angle = c.angle;
    rotation_center = c.rotation_center;
    velocity = c.velocity;
    active = c.active;
    max_velocity = c.max_velocity;
    acceleration = c.acceleration;
    max_acceleration = c.max_acceleration;
    friction = c.friction;
    impulse = c.impulse;

    setTypeFlags(c.type_flags);
    setIntersetedFlags(c.interested_flags);

    setType(c.type);

    return *this;
}


//=========================================
//=               MÉTODOS   	    	  =
//=========================================

void Collider::addShape(Shape* s)
{
    if(s!=nullptr)
    {
        for(auto it = shapes.begin(); it!=shapes.end(); it++)
        {
            if((*it)==s)
            {
                return;
            }
        }
        shapes.push_back(s);
        s->setCollider(this);
        calculateValues();
    }
}

void Collider::delShape(Shape* s)
{
    if(s!=nullptr)
    {
        for (auto it = shapes.begin(); it!=shapes.end(); it++)
        {
            if((*it)==s)
            {
                delete s;
                shapes.erase(it);
                calculateValues();
                return;
            }
        }
    }
}

// Detecta si los bounds intersectan con los de "c"
bool Collider::intersectBounds(Collider* c)
{
    if(c!=nullptr)
    {
        return bounds.intersects(c->bounds);
    }
    return false;
}

// Detecta si las figuras(shapes) intersectan con las de "c".
Intersection* Collider::intersectShapes(Collider* c)
{
    if (c!=nullptr)
    {
        for (auto it = shapes.begin(); it!=shapes.end(); it++)
        {
            Shape* sA = (*it);

            for (auto it2 = c->shapes.begin(); it2!=c->shapes.end(); it2++)
            {
                Shape* sB = (*it2);

                Intersection* inter = sA->intersect(sB);

                if(inter!=nullptr)
                {
                    return inter;
                }
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

            for (auto &&shape : shapes)
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

bool Collider::isColliding() const
{
    for (auto &&shape : shapes)
    {
        if(shape!=nullptr && shape->hasIntersected())
        {
            return true;
        }
    }
    return false;
}

void Collider::update(float dt)
{
    previous_position = position;

    Vector2d<int> ori = Vector2d<int>(sign(velocity.x),sign(velocity.y));
    Vector2d<float> v_abs = Vector2d<float>(velocity.x * ori.x, velocity.y * ori.y);

    Vector2d<float> s_frict;

    // Aplicar fricción
    s_frict.x = utilities::clamp(0.0f, friction.x, v_abs.x) * ori.x * (-1);
    s_frict.y = utilities::clamp(0.0f, friction.y, v_abs.y) * ori.y * (-1);

    Vector2d<float> accel = acceleration + s_frict + impulse;

    // El impulso solo se aplica una vez
    impulse = Vector2d<float>();

    Vector2d<int> a_ori = Vector2d<int>(sign(accel.x),sign(accel.y));
    Vector2d<float> a_abs = Vector2d<float>(accel.x * a_ori.x, accel.y * a_ori.y);

    // No sobrepasar la aceleración máxima permitida, también conocida fuerza total máxima permitida
    if(a_abs.x > max_acceleration.x)
    {
        accel.x = max_acceleration.x * a_ori.x;
        a_abs.x = accel.x * a_ori.x;
    }
    if(a_abs.y > max_acceleration.y)
    {
        accel.y = max_acceleration.y * a_ori.y;
        a_abs.y = accel.y * a_ori.y;
    }

    // Aplicar fuerzas
    velocity = velocity + accel;


    ori = Vector2d<int>(sign(velocity.x),sign(velocity.y));
    v_abs = Vector2d<float>(velocity.x * ori.x, velocity.y * ori.y);

    // No sobrepasar la velocidad máxima permitida(como en los coches)
    
    if(v_abs.x > max_velocity.x)
    {
        velocity.x = max_velocity.x * ori.x;
        v_abs.x = velocity.x * ori.x;
    }
    if(v_abs.y > max_velocity.y)
    {
        velocity.y = max_velocity.y * ori.y;
        v_abs.y = velocity.y * ori.y;
    }

    // Aplicar velocidad
    position = position + velocity * dt;

    for (auto &&shape : shapes)
    {
        if(shape!=nullptr)
        {
            shape->update(dt);
        }
    }

    calculateValues();
}

void Collider::render(const Vector2d<float>& view_pos)
{
    if(isColliding())
    {
        // Renderizar la bounding box que engloba sus figuras
        bounds.render(view_pos);

        // Renderizar sus figuras
        for (auto &&shape : shapes)
        {
            shape->render(view_pos);
        }
    }
}

void Collider::callBack(void* e)
{
    if(callback!=nullptr)
    {
        callback(e);
    }
}

//=========================================
//=               SETTERS   	    	  =
//=========================================

void Collider::setPosition(const Vector2d<float>& pos)
{
    previous_position = position;
    position = pos;

    calculateValues();
}

void Collider::setTypeFlags(const CollisionFlag& f)
{
    if(interested_flags == CollisionFlag::none)
    {
        if(type_flags == CollisionFlag::none)
        {
            if(f != CollisionFlag::none)
            {
                addCollider(this);
            }
        }else
        {
            if(f == CollisionFlag::none)
            {
                removeCollider(this);
            }
        }
    }
    type_flags = f;
}

void Collider::setIntersetedFlags(const CollisionFlag& f)
{
    if(type_flags == CollisionFlag::none)
    {
        if(interested_flags == CollisionFlag::none)
        {
            if(f != CollisionFlag::none)
            {
                addCollider(this);
            }
        }else
        {
            if(f == CollisionFlag::none)
            {
                removeCollider(this);
            }
        }
    }
    interested_flags = f;
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

void Collider::setCallback(Callback c)
{
    callback = c;
}

void Collider::setIndex(int i)
{
    index = i;
}

void Collider::setGlobalRotation(float a)
{
    angle = a;
    for (auto &&shape : shapes)
    {
        if (shape!=nullptr)
        {
            shape->setGlobalRotation();
        }
    }
    calculateValues();
}

void Collider::setLocalsRotation(float a)
{
    for (auto &&shape : shapes)
    {
        if (shape!=nullptr)
        {
            shape->setLocalRotation(a);
        }
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

void Collider::setActive(bool a)
{
    active = a;
}

void Collider::setMaxVelocity(const Vector2d<float>& m_vel)
{
    max_velocity = m_vel;
}

void Collider::setAcceleration(const Vector2d<float>& accel)
{
    acceleration = accel;
}

void Collider::setMaxAcceleration(const Vector2d<float>& m_accel)
{
    max_acceleration = m_accel;
}

void Collider::setFriction(const Vector2d<float>& frict)
{
    friction = frict;
}

void Collider::setImpulse(const Vector2d<float>& force)
{
    impulse = force;
}


//=========================================
//=               GETTERS   	    	  =
//=========================================

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

const CollisionFlag& Collider::getTypeFlags() const
{
    return type_flags;
}

const CollisionFlag& Collider::getInterestedFlags() const
{
    return interested_flags;
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

bool Collider::getActive() const
{
    return active;
}

const Vector2d<float>& Collider::getMaxVelocity() const
{
    return max_velocity;
}
const Vector2d<float>& Collider::getAcceleration() const
{
    return acceleration;
}
const Vector2d<float>& Collider::getMaxAcceleration() const
{
    return max_acceleration;
}
const Vector2d<float>& Collider::getFriction() const
{
    return friction;
}


//=========================================
//=              DESTRUCTOR   	    	  =
//=========================================

Collider::~Collider()
{

    auto it = shapes.begin();

    while (it!=shapes.end())
    {
        Shape* s = (*it);
        if(s!=nullptr)
        {
            delete s;
        }
        shapes.erase(it);
    }

    if((type_flags != CollisionFlag::none)||(interested_flags != CollisionFlag::none))
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

// Recalcula los datos de la bounding box que contiene a todas las figuras
void Collider::calculateValues()
{
    Vector2d<float> min;    // La menor X y la menor Y de todas las figuras
    Vector2d<float> max;    // La mayor X y la mayor Y de todas las figuras
    bool first = true;

    for(auto it = shapes.begin(); it!=shapes.end(); it++)
    {
        Shape* s = (*it);
        Vector2d<float> smin = s->getMin() + position;
        Vector2d<float> smax = s->getMax() + position;

        if(s!=nullptr)
        {
            if(first)
            {
                min = smin;
                max = smax;
                first = false;
            }else
            {
                if(min.x > smin.x) min.x = smin.x;
                if(min.y > smin.y) min.y = smin.y;
                if(max.x < smax.x) max.x = smax.x;
                if(max.y < smax.y) max.y = smax.y;
            }
        }
    }
    if(!first)
    {
        bounds = Bounding_Box(min, max);
    }

}