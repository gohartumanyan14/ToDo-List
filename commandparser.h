#pragma once
#include <QString>
#include "command.h"
#include <memory>

class TaskManager;

class CommandParser {
public:
    explicit CommandParser(TaskManager* tm = nullptr);
    void setTaskManager(TaskManager* tm) { m_tm = tm; }
    CommandPtr parseCommand(const QString& input, QString& outError) const;
    QString parseAndExecute(const QString& input);

private:
    static QString extractBraceValue(const QString& input, const QString& option);
    TaskManager* m_tm{nullptr};
};
