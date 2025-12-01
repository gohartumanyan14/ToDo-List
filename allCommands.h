#pragma once
#include "command.h"
#include <QString>

class AddTaskCommand : public Command {
public:
    explicit AddTaskCommand(QString name) : name_(std::move(name)) {}
    QString execute(TaskManager& tm) override;
private:
    QString name_;
};

class RemoveTaskCommand : public Command {
public:
    explicit RemoveTaskCommand(QString name) : name_(std::move(name)) {}
    QString execute(TaskManager& tm) override;
private:
    QString name_;
};

class CompleteTaskCommand : public Command {
public:
    explicit CompleteTaskCommand(QString name) : name_(std::move(name)) {}
    QString execute(TaskManager& tm) override;
private:
    QString name_;
};

class ListTasksCommand : public Command {
public:
    QString execute(TaskManager& tm) override;
};

class ExecuteFileCommand : public Command {
public:
    ExecuteFileCommand(QString path) : path_(std::move(path)) {}
    QString execute(TaskManager& tm) override;
private:
    QString path_;
};
