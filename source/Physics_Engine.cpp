#include "Physics_Engine.h"


namespace physics
{

    namespace
    {
        std::vector<Collider*> statics;
        std::vector<Collider*> cinematics;
        std::vector<Collider*> dynamics;
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
            statics.emplace_back(c);
        }
    }

    void addCinematic(Collider* c)
    {
        if(c!=nullptr)
        {
            for (auto it = cinematics.begin(); it!=cinematics.end(); it++)
            {
                Collider* col = (*it);
                if(c==col)
                {
                    return;
                }
            }
            cinematics.emplace_back(c);
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
            dynamics.emplace_back(c);
        }
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

    bool removeCinematic(Collider* c)
    {
        if(c!=nullptr)
        {
            for (auto it = cinematics.begin(); it!=cinematics.end(); it++)
            {
                Collider* col = (*it);
                if(c==col)
                {
                    cinematics.erase(it);
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

    // Removes a collider without knowing in which vector it is.
    bool removeCollider(Collider* c)
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
            
            for (auto it = cinematics.begin(); it!=cinematics.end(); it++)
            {
                Collider* col = (*it);
                if(c==col)
                {
                    cinematics.erase(it);
                    return true;
                }
            }

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

    // Dado un collisionable, resuelve las colisiones con el escenerio
    void collideWithStatics(Collider* c)
    {
        // c vs Estáticos
        if(c!=nullptr)
        {
            for(auto st = statics.begin(); st!=statics.end(); st++)
            {
                Collider* col = (*st);
                if(c!=col)
                {
                    if(c->intersectBounds(col))
                    {
                        c->intersectShapes(col);
                    }
                }
            }
        }
    }

    void collideWithCinematics(Collider* c)
    {
        // c vs Cinemáticos
        if(c!=nullptr)
        {
            for(auto cin = cinematics.begin(); cin!=cinematics.end(); cin++)
            {
                Collider* col = (*cin);
                if(c!=col)
                {
                    if(c->intersectBounds(col))
                    {
                        c->intersectShapes(col);
                    }
                }
            }
        }
    }

    void collideWithDynamics(Collider* c)
    {
        // c vs Dinámicos
        if(c!=nullptr)
        {
            for(auto dyn = dynamics.begin(); dyn!=dynamics.end(); dyn++)
            {
                Collider* col = (*dyn);
                if(c!=col)
                {
                    if(c->intersectBounds(col))
                    {
                        c->intersectShapes(col);
                    }
                }
            }
        }
    }

    // En esta función se analizan y resuelven todas las colisiones
    void step()
    {
        for(auto dyn = dynamics.begin(); dyn!=dynamics.end(); dyn++)
        {
            Collider* c = (*dyn);
            if(c!=nullptr)
            {
                // Dinámico vs Estáticos
                for(auto st = statics.begin(); st!=statics.end(); st++)
                {
                    Collider* col = (*st);
                    if(c->intersectBounds(col))
                    {
                        c->intersectShapes(col);
                    }
                }

                // Dinámico vs Cinemáticos
                for(auto cin = cinematics.begin(); cin!=cinematics.end(); cin++)
                {
                    Collider* col = (*cin);
                    if(c->intersectBounds(col))
                    {
                        c->intersectShapes(col);
                    }
                }

                // Dinámico vs Dinámico ¿Cuál se corrige?(¿Resolución por impulso?, ¿Alternativas?)
                for(auto dyn2 = dynamics.begin(); dyn2!=dynamics.end(); dyn2++)
                {
                    Collider* col = (*dyn2);
                    if(c!=col)
                    {
                        if(c->intersectBounds(col))
                        {
                            c->intersectShapes(col);
                        }
                    }
                }
            }
        }
    }
}
