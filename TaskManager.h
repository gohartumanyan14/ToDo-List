#pragma once
#include <QObject>
#include <QVector>
#include <QString>
#include "task.h"

class TaskManager : public QObject {
    Q_OBJECT
public:
    explicit TaskManager(QObject* parent = nullptr);
    QString addTask(const QString& name);
    QString removeTask(const QString& name);
    QString completeTask(const QString& name);
    QVector<Task> listTasks() const;

signals:
    void tasksChanged();
    void logMessage(const QString& msg);

private:
    int findTaskIndex(const QString& name) const;
    QVector<Task> m_tasks;
};
