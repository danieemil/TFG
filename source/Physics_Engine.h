#ifndef _PHYSICS_ENGINE_
#define _PHYSICS_ENGINE_

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <vector>
#include "Collider.h"


namespace physics
{
    // Inicializar
    void init();

    // Añadir colisiones
    void addCollider(Collider* c);
    void addStatic(Collider* c);
    void addDynamic(Collider* c);

    // Quitar colisiones
    bool removeCollider(Collider* c);
    bool removeStatic(Collider* c);
    bool removeDynamic(Collider* c);

    // Actualizar valores de los cuerpos que se mueven
    void update(float dt);

    // Mostrar las bounding boxes de los colliders(al menos de los que están colisionando)
    void render(const Vector2d<float>& view_pos = Vector2d<float>());

    // Comprobar y corregir colisiones
    void step(float dt);

    // Rayos contra las colisiones
    std::vector<Intersection*> rayTestStatics(const Vector2d<float>& a, const Vector2d<float>& b);
    Intersection* rayTestFirstStatic(const Vector2d<float>& a, const Vector2d<float>& b);
    bool rayTestStatic(const Vector2d<float>& a, const Vector2d<float>& b);

    std::vector<Intersection*> rayTestFlag(const Vector2d<float>& a, const Vector2d<float>& b, const CollisionFlag& f);
    std::vector<Intersection*> rayTestAll(const Vector2d<float>& a, const Vector2d<float>& b);

    void setManager(void (*manager)(Collider* colliderA, Collider* colliderB));

    const std::vector<Collider*>& getColliders();

    Shape* getSpriteShape(std::string tileset_path, int sprite_id);

    void deInit();
}

#endif