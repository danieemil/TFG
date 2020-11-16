#include "main.h"


// Gráficos
static int** lvl = nullptr;
static int height = 0;
static int width = 0;
static int tile_height = 0;
static int tile_width = 0;


// Físicas
struct point
{
    float x, y;
};


// AABB
// float X, Y -> Collider position
// float X, Y -> Min
// float X, Y -> Max
struct AABB
{
    point p;
    point min, max;
};

// Circle
// float X, Y -> Collider position
// float X, Y -> Center
// float R    -> Radius
struct Circle
{
    point p;
    point c;
    float radius;
};

// Convex
// float X, Y -> Collider position
// size_t S   -> Número de vértices
// S * float X, Y -> Vértice
struct Convex
{
    point p;
    std::vector<point> vertices;
};

std::vector<AABB> aabbs;
std::vector<Circle> circles;
std::vector<Convex> convexs;


// Entidades
enum entity_type
{
    player = 1,
    enemy,
    interactable,
};


struct Player
{
    point p;
    int weapon;
};

struct Enemy
{
    point p;
    int type;
    int weapon;
};

struct Interactable
{
    point p;
    int type;
    int value;
};


Player pl;
std::vector<Enemy> enemies;
std::vector<Interactable> interactables;


int charToInt(const char* c)
{

    stringstream ss;
    ss << c;
    int meh;
    ss >> meh;

    return meh;

}

int readLevelXML(const char* level_path)
{

    XMLDocument doc;
	if(doc.LoadFile(level_path)== XMLError::XML_SUCCESS)
    {

        XMLNode* n_map = doc.FirstChildElement("map");
        XMLElement* map = n_map->ToElement();

        width = map->IntAttribute("width");
        height = map->IntAttribute("height");
        tile_width = map->IntAttribute("tilewidth");
        tile_height = map->IntAttribute("tileheight");

        XMLNode* n_tilemap = nullptr;   // Datos de los gráficos del nivel
        XMLNode* n_physics = nullptr;   // Datos de las físicas del nivel
        XMLNode* n_entities = nullptr;  // Datos de todas las entidades del nivel


        // Asignar los diferentes grupos de datos(gráficos, físicas y entidades)
        XMLNode* n_layer = n_map->FirstChild();

        while (n_layer!=nullptr)
        {
            std::string n_value = n_layer->Value();

            if(n_value==std::string("layer"))
            {
                n_tilemap = n_layer;
            }

            if(n_value == std::string("objectgroup"))
            {
                // El primero son las físicas y el siguiente son las entidades
                n_physics = n_layer;
                n_layer = n_layer->NextSibling();
                if(n_layer == nullptr) break;

                n_entities = n_layer;
            }

            n_layer = n_layer->NextSibling();
        }

        // Gráficos
        if(n_tilemap!=nullptr)
        {

            // Reservar tilemap en memoria
            lvl = new int*[height];
            for (int i = 0; i < height; i++)
            {
                lvl[i] = new int[width];
            }

            XMLNode* data = n_tilemap->FirstChild();

            XMLElement* tile = data->FirstChildElement();
            
            int column = 0;
            int row = 0;


            while (tile!=nullptr)
            {
                const XMLAttribute* gid = tile->FirstAttribute();
                int value = 0;

                if(gid!=nullptr)
                {
                    value = gid->IntValue();
                }


                lvl[row][column] = value;


                column++;
                if(column>=width)
                {
                    column = 0;
                    row++;
                    if(row>=height)
                    {
                        row = 0;
                    }
                }

                tile = tile->NextSiblingElement();
            }
        }

        // Físicas
        if(n_physics!=nullptr)
        {
            XMLElement* collider = n_physics->FirstChildElement();

            while (collider!=nullptr)
            {

                point posit;

                posit.x = collider->FloatAttribute("x");
                posit.y = collider->FloatAttribute("y");

                XMLElement* poly = collider->FirstChildElement();

                if(poly!=nullptr)
                {
                    
                    if (poly->FirstAttribute()!=nullptr)
                    {
                        // Convex
                        Convex c;

                        c.p = posit;

                        const XMLAttribute* points = poly->FirstAttribute();
                        std::string vertices = points->Value();
                        std::string splitter = ",";
                        std::string splitter2 = " ";
                        std::size_t pos = 0U;

                        point value;

                        while (pos != std::string::npos)
                        {
                            pos = vertices.find(splitter);
                            value.x = (float)std::stoi(vertices.substr(0,pos));
                            vertices.erase(0, pos + splitter.size());

                            pos = vertices.find(splitter2);
                            value.y = (float)std::stoi(vertices.substr(0,pos));
                            vertices.erase(0, pos + splitter2.size());

                            c.vertices.emplace_back(value);
                            
                        }

                        convexs.push_back(c);
                    }
                    else
                    {
                        // Circle
                        Circle c;
                        c.p.x = posit.x;
                        c.p.y = posit.y;
                        c.radius = collider->FloatAttribute("width") / 2.0f;
                        c.c.x = c.radius;
                        c.c.y = c.radius;

                        circles.push_back(c);
                    }
                }
                else
                {
                    // AABB
                    AABB ab;

                    ab.p = posit;

                    ab.min.x = 0.0f;
                    ab.min.y = 0.0f;

                    ab.max.x = collider->FloatAttribute("width");
                    ab.max.y = collider->FloatAttribute("height");

                    aabbs.push_back(ab);

                }

                collider = collider->NextSiblingElement();
            }
        }

        // Entidades
        if(n_entities!=nullptr)
        {
            XMLElement* entity = n_entities->FirstChildElement();

            while (entity!=nullptr)
            {
                point posit;

                posit.x = entity->FloatAttribute("x");
                posit.y = entity->FloatAttribute("y");

                XMLElement* properties = entity->FirstChildElement();

                if (properties!=nullptr)
                {
                    XMLElement* type = properties->FirstChildElement();

                    while(type!=nullptr)
                    {
                        const XMLAttribute* attr = type->FindAttribute("name");
                        if(std::string(attr->Value()) == std::string("Type"))
                        {
                            break;
                        }
                        type = type->NextSiblingElement();
                    }

                    if(type!=nullptr)
                    {
                        const XMLAttribute* t_val = type->FindAttribute("value");

                        if(t_val!=nullptr)
                        {
                            int value = t_val->IntValue();

                            if(value == entity_type::player)
                            {
                                // Datos del jugador
                                pl.p = posit;
                                XMLElement* property = properties->FirstChildElement();
                                while(property!=nullptr)
                                {
                                    const XMLAttribute* attr = property->FindAttribute("name");
                                    if(attr!=nullptr)
                                    {
                                        std::string prop_name = attr->Value();
                                        if(prop_name == std::string("Weapon"))
                                        {
                                            t_val = property->FindAttribute("value");
                                            if(t_val!=nullptr)
                                            {
                                                pl.weapon = t_val->IntValue();
                                            }
                                        }
                                    }
                                    
                                    property = property->NextSiblingElement();
                                }
                            }
                            else if(value == entity_type::enemy)
                            {
                                // Datos del enemigo
                                Enemy e;
                                e.p = posit;
                                e.type = 0;
                                e.weapon = -1;

                                XMLElement* property = properties->FirstChildElement();
                                while(property!=nullptr)
                                {
                                    const XMLAttribute* attr = property->FindAttribute("name");
                                    if(attr!=nullptr)
                                    {
                                        std::string prop_name = attr->Value();
                                        if(prop_name == std::string("Weapon"))
                                        {
                                            t_val = property->FindAttribute("value");
                                            if(t_val!=nullptr)
                                            {
                                                e.weapon = t_val->IntValue();
                                            }
                                        }
                                        else if(prop_name == std::string("EnemyType"))
                                        {
                                            t_val = property->FindAttribute("value");
                                            if(t_val!=nullptr)
                                            {
                                                e.type = t_val->IntValue();
                                            }
                                        }
                                    }
                                    property = property->NextSiblingElement();
                                }
                                enemies.push_back(e);
                            }
                            else if(value == entity_type::interactable)
                            {
                                // Datos del interactuable
                                Interactable i;
                                i.p = posit;
                                i.type = -1;
                                i.value = 0;

                                XMLElement* property = properties->FirstChildElement();
                                while(property!=nullptr)
                                {
                                    const XMLAttribute* attr = property->FindAttribute("name");
                                    if(attr!=nullptr)
                                    {
                                        std::string prop_name = attr->Value();
                                        if(prop_name == std::string("InteractableType"))
                                        {
                                            t_val = property->FindAttribute("value");
                                            if(t_val!=nullptr)
                                            {
                                                i.type = t_val->IntValue();
                                            }
                                        }
                                        else if(prop_name == std::string("Value"))
                                        {
                                            t_val = property->FindAttribute("value");
                                            if(t_val!=nullptr)
                                            {
                                                i.value = t_val->IntValue();
                                            }
                                        }
                                    }
                                    property = property->NextSiblingElement();
                                }
                                interactables.push_back(i);
                            }
                        }
                    }
                }
                entity = entity->NextSiblingElement();
            }
        }

    }else
    {
        return -1;
    }
    
    return 0;
}


void dumpBin(const char* file_path)
{

    // Identificadores de tiles
    ofstream out;
    out.open(file_path, std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
    
    mem2file(out, width);
    mem2file(out, height);

    mem2file(out, tile_width);
    mem2file(out, tile_height);
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            mem2file(out, lvl[i][j]);
        }
    }

    // Físicas
        // AABBs
    mem2file(out, (int)aabbs.size());
    for (auto &&aabb : aabbs)
    {
        mem2file(out, aabb.p.x);
        mem2file(out, aabb.p.y);

        mem2file(out, aabb.min.x);
        mem2file(out, aabb.min.y);

        mem2file(out, aabb.max.x);
        mem2file(out, aabb.max.y);
    }

        // Círculos
    mem2file(out, (int)circles.size());
    for (auto &&circle : circles)
    {
        mem2file(out, circle.p.x);
        mem2file(out, circle.p.y);

        mem2file(out, circle.c.x);
        mem2file(out, circle.c.y);

        mem2file(out, circle.radius);
    }
    
        // Convexos
    mem2file(out, (int)convexs.size());
    for (auto &&convex : convexs)
    {
        mem2file(out, convex.p.x);
        mem2file(out, convex.p.y);

        mem2file(out, (int)convex.vertices.size());
        for (auto &&vertex : convex.vertices)
        {
            mem2file(out, vertex.x);
            mem2file(out, vertex.y);
        }
    }


    // Entidades

        // Jugador
    mem2file(out, pl.p.x);
    mem2file(out, pl.p.y);

    mem2file(out, pl.weapon);

        // Enemigos
    mem2file(out, (int)enemies.size());
    for (auto &&enemy : enemies)
    {
        mem2file(out, enemy.p.x);
        mem2file(out, enemy.p.y);

        mem2file(out, enemy.weapon);

        mem2file(out, enemy.type);
    }
    enemies.clear();

        // Interactuables
    mem2file(out, (int)interactables.size());
    for (auto &&interactable : interactables)
    {
        mem2file(out, interactable.p.x);
        mem2file(out, interactable.p.y);

        mem2file(out, interactable.type);

        mem2file(out, interactable.value);
    }
    interactables.clear();
    


    out.close();

}


void readBin(const char* file_path)
{
    ifstream in(file_path, std::ios::binary | std::ios::ate);
    in.seekg(0, std::ios::beg);

    int width2;
    int height2;
    int tile_width2;
    int tile_height2;

    int** lvl2;

    file2mem(in, &width2);
    file2mem(in, &height2);

    file2mem(in, &tile_width2);
    file2mem(in, &tile_height2);

    std::cout<<"Width: "<<width2<<std::endl;
    std::cout<<"Height: "<<height2<<std::endl;
    std::cout<<"T_Width: "<<tile_width2<<std::endl;
    std::cout<<"T_Height: "<<tile_height2<<std::endl;



    lvl2 = new int*[height2];

    for (int i = 0; i < height2; i++)
    {
        lvl2[i] = new int[width2];
        for (int j = 0; j < width2; j++)
        {
            file2mem(in, &lvl2[i][j]);
            std::cout<<lvl2[i][j]<<" ";
        }
        std::cout<<std::endl;
    }

    // Leer físicas

    int number = 0;

    float p_x, p_y;

    // Rectángulos
    file2mem(in, &number);

    std::cout<<"Rectangles: "<<number<<std::endl;

    for (int i = 0; i < number; i++)
    {
        float min_x, min_y;
        float max_x, max_y;

        file2mem(in, &p_x);
        file2mem(in, &p_y);

        file2mem(in, &min_x);
        file2mem(in, &min_y);

        file2mem(in, &max_x);
        file2mem(in, &max_y);
        
    }
        
    

    // Círculos
    file2mem(in, &number);

    std::cout<<"Circles: "<<number<<std::endl;

    for (int i = 0; i < number; i++)
    {

        float center_x, center_y;
        float radius;

        file2mem(in, &p_x);
        file2mem(in, &p_y);

        file2mem(in, &center_x);
        file2mem(in, &center_y);

        file2mem(in, &radius);

    }


    // Convexos
    file2mem(in, &number);

    std::cout<<"Convex: "<<number<<std::endl;

    for (int i = 0; i < number; i++)
    {
        file2mem(in, &p_x);
        file2mem(in, &p_y);

        int s_number = 0;
        file2mem(in, &s_number);


        for (int j = 0; j < s_number; j++)
        {
            point vert;

            file2mem(in, &vert.x);
            file2mem(in, &vert.y);
            
        }
    }


    // Entidades

        // Jugador
    file2mem(in, &pl.p.x);
    file2mem(in, &pl.p.y);

    file2mem(in, &pl.weapon);


        // Enemigos
    file2mem(in, &number);

    std::cout<<"Enemigos: "<<number<<std::endl;

    for (int i = 0; i < number; i++)
    {
        Enemy e;

        file2mem(in, &e.p.x);
        file2mem(in, &e.p.y);

        file2mem(in, &e.weapon);

        file2mem(in, &e.type);
    }

        // Interactables
    file2mem(in, &number);

    std::cout<<"Interactuables: "<<number<<std::endl;

    for (int i = 0; i < number; i++)
    {
        Interactable inter;

        file2mem(in, &inter.p.x);
        file2mem(in, &inter.p.y);

        file2mem(in, &inter.type);

        file2mem(in, &inter.value);
    }


    in.close();

}


int main(int argc, char* argv[])
{

    if(argc==3)
    {
        
        //Archivo origen
        const char* path = "/home/tuba/Escritorio/project3ds/TFG/gfx/maps/testMap.tmx";
        path = argv[1];

        //Archivo destino
        const char* path2 = "/home/tuba/Escritorio/project3ds/TFG/romfs/maps/testMap.mp";
        path2 = argv[2];

        int result = readLevelXML(path);

        if(result==-1)
        {
            std::cout<<"Invalid path or file: ";
            std::cout<<path<<std::endl;
            return 0;
        }

        dumpBin(path2);

        std::cout<<"Converted : ";
        std::cout<<path2<<std::endl;

        readBin(path2);
    }
    else
    {
        std::cout<<"Parameters not found"<<std::endl;
    }
    


    return 0;
}