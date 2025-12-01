#pragma once
#include <QString>

class Task {
public:
    Task();
    Task(const QString &name, bool completed = false);
    const QString& name() const;
    bool isCompleted() const;
    void setCompleted(bool a);

private:
    QString m_name;
    bool m_completed = false;
};
