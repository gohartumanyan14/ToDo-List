#include "allCommands.h"
#include "TaskManager.h"
#include "commandparser.h"
#include <QFile>
#include <QTextStream>

QString AddTaskCommand::execute(TaskManager& tm) {
    return tm.addTask(name_);
}

QString RemoveTaskCommand::execute(TaskManager& tm) {
    return tm.removeTask(name_);
}

QString CompleteTaskCommand::execute(TaskManager& tm) {
    return tm.completeTask(name_);
}

QString ListTasksCommand::execute(TaskManager& tm) {
    auto tasks = tm.listTasks();
    if (tasks.isEmpty()) {
        QString msg = "No tasks.";
        return msg;
    }
    QString out;
    for (const Task& t : tasks) {
        out += QString("%1 %2\n").arg(t.isCompleted() ? QChar(0x2611) : QChar(0x2610)).arg(t.name());
    }
    out = out.trimmed();
    return out;
}

QString ExecuteFileCommand::execute(TaskManager& tm) {
    QFile f(path_);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return QString("Error: could not open file '%1'").arg(path_);
    }

    CommandParser parser(&tm);

    QTextStream in(&f);
    int lineNo = 0;
    QString combined;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        ++lineNo;
        if (line.isEmpty()) continue;
        parser.parseAndExecute(line);
    }
    f.close();

    combined = combined.trimmed();
    return combined;
}
