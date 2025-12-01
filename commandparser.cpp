#include "commandparser.h"
#include "TaskManager.h"
#include "allCommands.h"
#include <QRegularExpression>
#include <QFile>
#include <QTextStream>

CommandParser::CommandParser(TaskManager* tm) : m_tm(tm) {}

QString CommandParser::extractBraceValue(const QString& input, const QString& option) {
    QRegularExpression re(QStringLiteral("%1\\s*\\{([^}]*)\\}").arg(QRegularExpression::escape(option)));
    auto m = re.match(input);
    if (m.hasMatch()) return m.captured(1).trimmed();
    return {};
}

CommandPtr CommandParser::parseCommand(const QString& input, QString& outError) const {
    QString line = input.trimmed();
    if (line.isEmpty()) {
        outError = "Empty command.";
        return nullptr;
    }

    QStringList parts = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    QString cmd = parts.value(0);

    if (cmd == "add_task") {
        QString name = extractBraceValue(line, "-name");
        if (name.isEmpty()) { outError = "Usage: add_task -name {task_name}"; return nullptr; }
        return std::make_unique<AddTaskCommand>(name);
    }
    if (cmd == "remove_task") {
        QString name = extractBraceValue(line, "-name");
        if (name.isEmpty()) { outError = "Usage: remove_task -name {task_name}"; return nullptr; }
        return std::make_unique<RemoveTaskCommand>(name);
    }
    if (cmd == "complete_task") {
        QString name = extractBraceValue(line, "-name");
        if (name.isEmpty()) { outError = "Usage: complete_task -name {task_name}"; return nullptr; }
        return std::make_unique<CompleteTaskCommand>(name);
    }
    if (cmd == "list_tasks") {
        return std::make_unique<ListTasksCommand>();
    }
    if (cmd == "execute_file") {
        QString path = extractBraceValue(line, "-file_path");
        if (path.isEmpty()) { outError = "Usage: execute_file -file_path {path}"; return nullptr; }
        return std::make_unique<ExecuteFileCommand>(path);
    }

    outError = QString("Unknown command: %1").arg(cmd);
    return nullptr;
}

QString CommandParser::parseAndExecute(const QString& input) {
    if (!m_tm) return QString("Error: TaskManager not set on parser.");

    QString perr;
    CommandPtr cmd = parseCommand(input, perr);

    if (!cmd) {
        emit m_tm->logMessage(perr);
        return perr;
    }

    QString result = cmd->execute(*m_tm);
    if (!result.isEmpty()) {
        emit m_tm->logMessage(result);
    }
    return result;
}
