#include "Physics_Engine.h"
#include "Unvisual_Engine.h"

#include "Entity.h"

namespace physics
{

    namespace
    {

        std::size_t sz = 1000;

        std::vector<Collider*> colliders;
        std::vector<Collider*> dynamics;
        std::vector<Collider*> statics;

        // Función que trata con los elementos que han colisionado
        void manifold(Collider* colliderA, Collider* colliderB)
        {
            if (colliderA!=nullptr && colliderB!=nullptr)
            {
                CollisionFlag At = colliderA->getTypeFlags();
                CollisionFlag Bt = colliderB->getTypeFlags();
                CollisionFlag Ai = colliderA->getInterestedFlags();
                CollisionFlag Bi = colliderB->getInterestedFlags();

                if((Ai & Bt) != CollisionFlag::none)
                {
                    // A reaciona al colisionar con B.
                    colliderA->callBack(colliderB->getCreator());
                }

                if((Bi & At) != CollisionFlag::none)
                {
                    // B reaciona al colisionar con A.
                    colliderB->callBack(colliderA->getCreator());
                }

            }
        }

        void (*collision_manager)(Collider* colliderA, Collider* colliderB){manifold};



        // Relacionando sprites con sus colisiones
        std::map<std::string, std::map<int, Shape*>> tilesets_colliders;
    }

    void init()
    {
        // Vamos almacenando las colisiones de los sprites de cada tileset
        // Junto con la id del sprite al que corresponde
        std::map<int, Shape*> tileset_colliders;
        std::string tileset_route;
        std::vector<Vector2d<float>> vertices;
        Shape* s;
        float sizeX, sizeY; // Dimensiones del sprite 
        float sX, sY;           // Dimensiones del collider

    
        // Tileset de los sprites de prueba
        tileset_route = "romfs:/gfx/sprites.t3x";
        tileset_colliders.clear();
        sizeX = 10;
        sizeY = 15;
        sX = sizeX;
        sY = sizeY;

        // Letra "P"
        vertices = {
            Vector2d<float>(0,0),
            Vector2d<float>(sX,0),
            Vector2d<float>(sX,sY/2.5f),
            //Vector2d<float>(sX/5.0f,sY/2.5f),
            Vector2d<float>(sX/5.0f,sY),
            Vector2d<float>(0,sY)
        };
        s = new Convex(vertices);
        tileset_colliders.insert(pair<int, Shape*>(0,s));

        // Arma temporal
        s = new AABB(Vector2d<float>(-15,-20), Vector2d<float>(15,1));
        tileset_colliders.insert(pair<int, Shape*>(1,s));

        // Letra "E"
        s = new AABB(Vector2d<float>(0,0), Vector2d<float>(sX, sY));
        tileset_colliders.insert(pair<int, Shape*>(2,s));

        tilesets_colliders.insert(pair<string, std::map<int, Shape*>>(tileset_route, tileset_colliders));

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

    // Actualizamos los valores de todos los cuerpos que se muevan
    void update(float dt)
    {
        for(auto it = colliders.begin(); it!=colliders.end(); it++)
        {
            Collider* collider = (*it);
            if(collider!=nullptr)
            {
                collider->update(dt);
            }
        }

        for (auto it = dynamics.begin(); it!=dynamics.end(); it++)
        {
            Collider* collider = (*it);
            if (collider!=nullptr)
            {
                collider->update(dt);
            }
        }

        for (auto it = statics.begin(); it!=statics.end(); it++)
        {
            Collider* collider = (*it);
            if (collider!=nullptr)
            {
                collider->update(dt);
            }
        }
        
    }

    void render(const Vector2d<float>& view_pos)
    {
        for (auto &&col : colliders)
        {
            col->render(view_pos);
        }

        for (auto &&sta : statics)
        {
            sta->render(view_pos);
        }
        
    }

    // En esta función se analizan y resuelven todas las colisiones
    void step(float dt)
    {

        update(dt);

        // Todos los colliders neutros se comprueban entre sí SOLO UNA VEZ
        for(auto it = colliders.begin(); it!=colliders.end(); it++)
        {
            Collider* colliderA = (*it);

            if(!colliderA->getActive()) continue;

            for (auto it2 = it+1; it2!=colliders.end(); it2++)
            {
                Collider* colliderB = (*it2);

                if(!colliderB->getActive()) continue;

                if(colliderA->intersectShapes(colliderB)!=nullptr)
                {
                    collision_manager(colliderA, colliderB);
                }
            }
        }

        // Los cuerpos dinámicos comprueban con los estáticos si colisionan o no
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
                            Intersection* i = colliderA->intersectShapes(colliderB);
                            colliderA->intersectFix(i);
                            if(i!=nullptr && i->intersects)
                            {
                                static_cast<Entity*>(colliderA->getCreator())->updateFromCollider();
                            }
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
            if((col->getTypeFlags() & f) != CollisionFlag::none)
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

    Shape* getSpriteShape(std::string tileset_path, int sprite_id)
    {
        auto tileset = tilesets_colliders.find(tileset_path);

        if(tileset != tilesets_colliders.end())
        {
            auto sprite = tileset->second.find(sprite_id);

            if(sprite != tileset->second.end())
            {
                Shape* s = sprite->second;
                if(s!=nullptr)
                {
                    if(s->getType()==Shape_Type::AABB)
                    {
                        return new AABB(*(static_cast<AABB*>(s)));
                    }
                    if(s->getType()==Shape_Type::Circle)
                    {
                        return new Circle(*(static_cast<Circle*>(s)));
                    }
                    if(s->getType()==Shape_Type::Convex)
                    {
                        return new Convex(*(static_cast<Convex*>(s)));
                    }
                }
            }
        }

        return nullptr;
    }

    void deInit()
    {
        for (auto &&tileset : tilesets_colliders)
        {
            for (auto &&sprite : tileset.second)
            {
                Shape* s = sprite.second;

                if(s!=nullptr)
                {
                    delete s;
                }
            }
            tileset.second.clear();
        }
        tilesets_colliders.clear();
    }
}
