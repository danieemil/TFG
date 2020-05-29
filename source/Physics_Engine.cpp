#include "Physics_Engine.h"
#include "Unvisual_Engine.h"


namespace physics
{

    namespace
    {

        std::size_t sz = 1000;

        std::vector<Collider*> colliders;
        std::vector<Collider*> dynamics;
        std::vector<Collider*> statics;

        void manifold(Collider* colliderA, Collider* colliderB)
        {
            if (colliderA!=nullptr && colliderB!=nullptr)
            {
                CollisionFlag flagsA = colliderA->getFlags();
                CollisionFlag flagsB = colliderB->getFlags();
            }
        }

        void (*collision_manager)(Collider* colliderA, Collider* colliderB){manifold};
    }


    void addCollider(Collider* c)
    {
        if(colliders.size()< sz)
        {
            if(c!=nullptr)
            {
                for (auto it = colliders.begin(); it!=colliders.end(); it++)
                {
                    Collider* col = (*it);
                    if(c==col)
                    {
                        return;
                    }
                }
                colliders.push_back(c);
            }
        }
    }

    void addStatic(Collider* c)
    {
        if(c!=nullptr)
        {
            for (auto it = statics.begin(); it!=statics.end(); it++)
            {
                Collider* col = (*it);
                if(c==col)
                {
                    return;
                }
            }
            statics.push_back(c);
        }
    }

    void addDynamic(Collider* c)
    {
        if(c!=nullptr)
        {
            for (auto it = dynamics.begin(); it!=dynamics.end(); it++)
            {
                Collider* col = (*it);
                if(c==col)
                {
                    return;
                }
            }
            dynamics.push_back(c);
        }
    }

    // Removes a collider from the vector
    bool removeCollider(Collider* c)
    {
        if(c!=nullptr)
        {
            for (auto it = colliders.begin(); it!=colliders.end(); it++)
            {
                Collider* col = (*it);
                if(c==col)
                {
                    colliders.erase(it);
                    return true;
                }
            }
        }
        return false;
    }

    bool removeStatic(Collider* c)
    {
        if(c!=nullptr)
        {
            for (auto it = statics.begin(); it!=statics.end(); it++)
            {
                Collider* col = (*it);
                if(c==col)
                {
                    statics.erase(it);
                    return true;
                }
            }
        }
        return false;
    }

    bool removeDynamic(Collider* c)
    {
        if(c!=nullptr)
        {
            for (auto it = dynamics.begin(); it!=dynamics.end(); it++)
            {
                Collider* col = (*it);
                if(c==col)
                {
                    dynamics.erase(it);
                    return true;
                }
            }
        }
        return false;
    }

    // En esta función se analizan y resuelven todas las colisiones
    void step()
    {
        // Todos los colliders neutros se comprueban entre sí SOLO UNA VEZ
        for(auto it = colliders.begin(); it!=colliders.end(); it++)
        {
            Collider* colliderA = (*it);

            for (auto it2 = it+1; it2!=colliders.end(); it2++)
            {
                Collider* colliderB = (*it2);

                if(colliderA!=colliderB)
                {
                    collision_manager(colliderA, colliderB);
                }
            }
        }

        for (auto it = dynamics.begin(); it!=dynamics.end(); it++)
        {
            Collider* colliderA = (*it);
            if (colliderA!=nullptr)
            {
                for (auto it2 = statics.begin(); it2!=statics.end(); it2++)
                {
                    Collider* colliderB = (*it2);
                    if(colliderB!=nullptr)
                    {
                        if(colliderA->intersectBounds(colliderB))
                        {
                            colliderA->intersectFix(colliderA->intersectShapes(colliderB));
                        }
                    }
                }
            }
        }
    }

    std::vector<Intersection*> rayTestStatics(const Vector2d<float>& a, const Vector2d<float>& b)
    {
        std::vector<Intersection*> intersections;

        Intersection* i = nullptr;

        for (auto &&c_static : statics)
        {
            i = c_static->intersectSegment(a, b);
            if (i!=nullptr)
            {
                intersections.push_back(i);
            }
        }

        return intersections;
    }
    
    // Mayor coste computacional de los estáticos
    Intersection* rayTestFirstStatic(const Vector2d<float>& a, const Vector2d<float>& b)
    {

        Intersection* i = nullptr;

        float dist = (b - a).Length();

        for (auto &&c_static : statics)
        {
            Intersection* i2 = c_static->intersectSegment(a, b);
            if (i2!=nullptr)
            {
                float dist2 = (i2->position - a).Length();
                if (dist2 < dist)
                {
                    dist = dist2;
                    i = i2;
                }
            }
        }

        return i;
    }
    
    // Menor coste computacional de los estáticos
    bool rayTestStatic(const Vector2d<float>& a, const Vector2d<float>& b)
    {
        for (auto &&c_static : statics)
        {
            if (c_static->intersectSegment(a, b)!=nullptr)
            {
                return true;
            }
        }
        return false;
    }
    
    // Costoso dependiendo de las flags activas que se pasen por parámetro
    std::vector<Intersection*> rayTestFlag(const Vector2d<float>& a, const Vector2d<float>& b, const CollisionFlag& f)
    {
        std::vector<Intersection*> intersections;

        for (auto &&col : colliders)
        {
            if((col->getFlags() & f) != CollisionFlag::none)
            {
                Intersection* i = col->intersectSegment(a, b);
                if(i!=nullptr)
                {
                    intersections.push_back(i);
                }
            }
        }
        return intersections;
    }
    
    std::vector<Intersection*> rayTestAll(const Vector2d<float>& a, const Vector2d<float>& b)
    {
        std::vector<Intersection*> intersections = rayTestStatics(a, b);

        for (auto &&col : colliders)
        {
            Intersection* i = col->intersectSegment(a, b);
            if (i!=nullptr)
            {
                intersections.push_back(i);
            }
        }

        return intersections;
    }

    void setManager(void (*manager)(Collider* colliderA, Collider* colliderB))
    {
        collision_manager = manager;
    }

    const std::vector<Collider*>& getColliders()
    {
        return colliders;
    }
}
