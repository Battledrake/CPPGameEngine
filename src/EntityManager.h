#ifndef ENTITYMANAGER
#define ENTITYMANAGER

#include <vector>
#include "./Entity.h"

class EntityManager {
   public:
    void ClearData();
    void Update(float deltaTime);
    void Render();
    bool HasNoEntities();
    Entity &AddEntity(std::string entityName, LayerType layer);
    std::vector<Entity *> GetEntities() const;
    std::vector<Entity*> GetEntitiesByLayer(LayerType layer) const;
    unsigned int GetEntityCount();
    void ListAllEntities() const;

   private:
    std::vector<Entity *> entities;
};

#endif