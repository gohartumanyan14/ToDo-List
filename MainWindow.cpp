#include "MainWindow.h"
#include "TaskManager.h"
#include "commandparser.h"
#include <QListWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      m_taskManager(new TaskManager(this)),
      m_parser(new CommandParser(m_taskManager))
{
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    m_taskListWidget = new QListWidget(this);
    m_logArea = new QTextEdit(this);
    m_logArea->setReadOnly(true);
    m_inputLine = new QLineEdit(this);
    m_execButton = new QPushButton("Execute", this);

    QLabel* tasksLabel = new QLabel("Tasks:");
    QLabel* logLabel = new QLabel("Log:");
    QLabel* cmdLabel = new QLabel("Command:");

    QVBoxLayout* left = new QVBoxLayout;
    left->addWidget(tasksLabel);
    left->addWidget(m_taskListWidget);

    QVBoxLayout* right = new QVBoxLayout;
    right->addWidget(logLabel);
    right->addWidget(m_logArea);

    QHBoxLayout* top = new QHBoxLayout;
    top->addLayout(left, 1);
    top->addLayout(right, 2);

    QHBoxLayout* bottom = new QHBoxLayout;
    bottom->addWidget(cmdLabel);
    bottom->addWidget(m_inputLine, 1);
    bottom->addWidget(m_execButton);

    QVBoxLayout* main = new QVBoxLayout(central);
    main->addLayout(top);
    main->addLayout(bottom);

    connect(m_execButton, &QPushButton::clicked, this, &MainWindow::onExecute);
    connect(m_inputLine, &QLineEdit::returnPressed, this, &MainWindow::onExecute);
    connect(m_taskManager, &TaskManager::tasksChanged, this, &MainWindow::onTasksChanged);
    connect(m_taskManager, &TaskManager::logMessage, this, &MainWindow::onLogMessage);

    setWindowTitle("ToDo List");
    resize(800, 480);

    onTasksChanged();
    m_logArea->append("Commands: add_task -name {name}, remove_task -name {name}, complete_task -name {name}, list_tasks, execute_file -file_path {path}");
}

void MainWindow::onExecute() {
    QString cmd = m_inputLine->text().trimmed();
    if (cmd.isEmpty()) return;
    m_parser->parseAndExecute(cmd);
    m_inputLine->clear();
}

void MainWindow::onTasksChanged() {
    refreshTaskList();
}

void MainWindow::onLogMessage(const QString& msg) {
    if (msg.startsWith("Error:")) {
        m_logArea->append("<span style='color:red;'>" + msg + "</span>");
    }
    else {
        m_logArea->append(msg);
    }
}

void MainWindow::refreshTaskList() {
    m_taskListWidget->clear();
    auto tasks = m_taskManager->listTasks();
    if (tasks.isEmpty()) {
        return;
    }
    for (const auto& t : tasks) {
        QString label = QString("%1 %2").arg(t.isCompleted() ? QChar(0x2611) : QChar(0x2610)).arg(t.name());
        m_taskListWidget->addItem(label);
    }
}
