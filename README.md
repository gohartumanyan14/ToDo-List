Simple ToDo List application built with Qt and C++.

Features
- Add tasks: `add_task -name {task_name}`
- Remove tasks: `remove_task -name {task_name}`
- Complete tasks: `complete_task -name {task_name}`
- List tasks: `list_tasks`
- Execute commands from file: `execute_file -file_path {path}`
- Unicode checkboxes:
  - ☐ Task not completed
  - ☑ Task completed
- Error messages shown in red in log area

UI
- Left panel: Task list
- Right panel: Log area
- Bottom: Command input + Execute button
  
