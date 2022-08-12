#include "entity/entity_handler.h"

int EntityHandler::currentId = 0;

int EntityHandler::spawnEntity() {
    EntityHandler::currentId++;
}
