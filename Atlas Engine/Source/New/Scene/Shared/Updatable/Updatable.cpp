#include "Updatable.h"

bool Atlas::Updatable::ShouldUpdate()
{
    if (currentFrame >= framesBetweenUpdates) {
        currentFrame = 0;
        return true;
    }
    return false;
}

Atlas::Updatable::Updatable(int framesUntilUpdate)
    : framesBetweenUpdates(framesUntilUpdate), currentFrame(0)
{

}

Atlas::Updatable::Updatable(int framesUntilUpdate, int startingFrame)
    : framesBetweenUpdates(framesUntilUpdate), currentFrame(startingFrame)
{
    
}

Atlas::Updatable::~Updatable()
{

}

void Atlas::Updatable::Update(float deltaTime)
{
    currentFrame++;
}
