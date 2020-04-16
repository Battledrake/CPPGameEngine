#ifndef ENTITY
#define ENTITY
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "./Constants.h"

class Component;
class EntityManager;

class Entity {
   public:
    std::string name;
    LayerType layer;
    Entity(EntityManager &manager);
    Entity(EntityManager &manager, std::string name, LayerType layer);
    void Update(float deltaTime);
    void Render();
    void Destroy();
    void ListAllComponents() const;
    inline bool IsActive() const { return this->isActive; }
    inline std::vector<std::shared_ptr<Component>> GetComponents() const { return this->components; }

    template <typename T, typename... TArgs>
    std::shared_ptr<T> AddComponent(TArgs &&... args) {
        std::shared_ptr<T> newComponent(new T(std::forward<TArgs>(args)...));
        newComponent->owner = this;
        components.emplace_back(newComponent);
        componentTypeMap[&typeid(*newComponent)] = newComponent;
        newComponent->Initialize();
        return newComponent;
    }

    template <typename T>
    std::shared_ptr<T> GetComponent() {
        // return static_cast<std::shared_ptr<T>>(componentTypeMap[&typeid(T)]);
        return std::static_pointer_cast<T>(componentTypeMap[&typeid(T)]);
    }

    template <typename T>
    bool HasComponent() const {
        if (componentTypeMap.count(&typeid(T))) {
            return true;
        }
        std::cout << "Component<" << typeid(T).name() << "> does not exist" << std::endl;
        return false;
    }

   private:
    EntityManager &manager;
    bool isActive;
    std::vector<std::shared_ptr<Component>> components;
    std::map<const std::type_info *, std::shared_ptr<Component>> componentTypeMap;
};

#endif