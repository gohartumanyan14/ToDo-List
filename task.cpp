#include "task.h"

Task::Task() = default;

Task::Task(const QString &name, bool completed)
    : m_name(name), m_completed(completed) {}

const QString& Task::name() const {
    return m_name;
}

bool Task::isCompleted() const {
    return m_completed;
}

void Task::setCompleted(bool a) {
    m_completed = a;
}
