#include "./Entity.h"
#include "./Components/Component.h"
// #include "./EntityManager.h"
#include <iostream>
#include <cxxabi.h>

Entity::Entity(EntityManager &manager) : manager(manager) {
    this->isActive = true;
}

Entity::Entity(EntityManager &manager, std::string name, LayerType layer)
    : manager(manager), name(name), layer(layer) {
    this->isActive = true;
}

void Entity::Update(float deltaTime) {
    for (auto &component : components) {
        component->Update(deltaTime);
    }
}

void Entity::Render() {
    for (auto &component : components) {
        component->Render();
    }
}

void Entity::ListAllComponents() const {
    int status = -1;
    for (auto &mapElement : componentTypeMap) {
        std::cout << " Component<" << abi::__cxa_demangle(mapElement.first->name(), 0, 0, &status) << ">" << std::endl;
    }
}

void Entity::Destroy() { this->isActive = false; }