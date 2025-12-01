#pragma once
#include <QMainWindow>

class TaskManager;
class CommandParser;
class QListWidget;
class QTextEdit;
class QLineEdit;
class QPushButton;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override = default;

private slots:
    void onExecute();
    void onTasksChanged();
    void onLogMessage(const QString& msg);

private:
    void refreshTaskList();

private:
    TaskManager* m_taskManager;
    CommandParser* m_parser;

    QListWidget* m_taskListWidget;
    QTextEdit* m_logArea;
    QLineEdit* m_inputLine;
    QPushButton* m_execButton;
};
