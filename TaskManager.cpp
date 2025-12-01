#include "TaskManager.h"

TaskManager::TaskManager(QObject* parent) : QObject(parent) {}

int TaskManager::findTaskIndex(const QString& name) const {
    for (int i = 0; i < m_tasks.size(); ++i) {
        if (m_tasks[i].name() == name) return i;
    }
    return -1;
}

QString TaskManager::addTask(const QString& name) {
    QString n = name.trimmed();
    if (n.isEmpty()) {
        QString msg = "Error: Task name cannot be empty.";
        return msg;
    }
    if (findTaskIndex(n) != -1) {
        QString msg = QString("Error: Task '%1' already exists.").arg(n);
        return msg;
    }
    m_tasks.append(Task(n));
    QString msg = QString("Task '%1' added.").arg(n);
    emit tasksChanged();
    return msg;
}

QString TaskManager::removeTask(const QString& name) {
    QString n = name.trimmed();
    int idx = findTaskIndex(n);
    if (idx == -1) {
        QString msg = QString("Error: Task '%1' not found.").arg(n);
        return msg;
    }
    m_tasks.removeAt(idx);
    QString msg = QString("Task '%1' removed.").arg(n);
    emit tasksChanged();
    return msg;
}

QString TaskManager::completeTask(const QString& name) {
    QString n = name.trimmed();
    int idx = findTaskIndex(n);
    if (idx == -1) {
        QString msg = QString("Error: Task '%1' not found.").arg(n);
        return msg;
    }
    if (m_tasks[idx].isCompleted()) {
        QString msg = QString("Task '%1' is already completed.").arg(n);
        return msg;
    }
    m_tasks[idx].setCompleted(true);
    QString msg = QString("Task '%1' marked completed.").arg(n);
    emit tasksChanged();
    return msg;
}

QVector<Task> TaskManager::listTasks() const {
    return m_tasks;
}

