#pragma once
#include <QString>
class TaskManager;

struct Command {
    virtual ~Command() = default;
    virtual QString execute(TaskManager& tm) = 0;
};
using CommandPtr = std::unique_ptr<Command>;
