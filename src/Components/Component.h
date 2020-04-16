#ifndef COMPONENT
#define COMPONENT

#include "../Entity.h"

class Component {
   public:
    virtual ~Component() {}
    Entity *owner;
    virtual void Initialize() {}
    virtual void Update(float deltaTime) {}
    virtual void Render() {}
};

#endif