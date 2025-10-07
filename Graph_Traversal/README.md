# Task 3: Graph Traversal (BFS and DFS)

**Реализация обхода графа в ширину (BFS) и глубину (DFS) для ориентированных и неориентированных графов.**

## 📋 Требования

Программа должна поддерживать:
- **Типы графов**: ориентированные ('d') и неориентированные ('u')
- **Типы обхода**: в ширину ('b') и в глубину ('d') 
- **Формат ввода**: ребра графа как пары вершин
- **Порядок обхода**: вывод посещенных вершин по одной в строке

## 🏗️ Архитектура решения

### Файловая структура:
```
Graph_Traversal/
├── graph.h                 # Заголовочный файл с классом Graph
├── graph.cc                # Реализация методов графа
├── prog.cc                 # Основная программа
├── oneFileProg.cc          # Однофайловая версия
└── README.md               # Описание задачи
```

### Ключевые особенности:
- **Представление графа**: матрица смежности
- **Обработка типов графов**: автоматическое добавление обратных ребер для неориентированных
- **Лексикографический порядок**: сортировка смежных вершин
- **Проверка посещенных вершин**: использование unordered_set

## 🛠 Компиляция и запуск

**С раздельной компиляцией:**
```bash
cd Graph_Traversal
g++ -std=c++17 graph.cc prog.cc -o graph_traversal
./graph_traversal
```

**Однофайловая версия:**
```bash
cd Graph_Traversal
g++ -std=c++17 oneFileProg.cc -o graph_traversal
./graph_traversal
```

## 📝 Формат ввода/вывода

### Входные данные:
```
graph_type start_vertex search_type  # Первая строка
vertex1 vertex2                       # Ребра графа
vertex3 vertex4
...
```

**Параметры:**
- `graph_type`: 'd' (ориентированный) или 'u' (неориентированный)
- `start_vertex`: начальная вершина обхода
- `search_type`: 'b' (BFS) или 'd' (DFS)

### Выходные данные:
Последовательность вершин в порядке обхода (по одной в строке).

## 🧪 Примеры работы

### Пример 1: DFS для неориентированного графа
```bash
# Ввод:
u 1 d
1 3
1 2
1 5
2 3
2 4
5 4

# Вывод:
1
2
3
4
5
```

### Пример 2: DFS для неориентированного графа (начало с вершины 2)
```bash
# Ввод:
u 2 d
1 3
1 2
1 5
2 3
2 4
5 4

# Вывод:
2
1
3
5
4
```

### Пример 3: BFS для ориентированного графа
```bash
# Ввод:
d 1 b
1 2
1 3
2 4
3 4
4 5

# Вывод:
1
2
3
4
5
```

## 🔍 Алгоритмы реализации

### BFS (обход в ширину):
```cpp
std::queue<int> Graph::bfs(int start) {
    std::queue<int> bfs_queue;
    std::queue<int> vertex_queue;
    std::vector<bool> visited(vertex_count, 0);
    vertex_queue.push(start);
    visited[start] = 1;
    while(!vertex_queue.empty()) {
        int cur_vertex = vertex_queue.front();
        vertex_queue.pop();
        for (int vertex = 0; vertex < vertex_count; ++vertex)
            if (adjacency_matrix[cur_vertex][vertex] && !visited[vertex]) {
                vertex_queue.push(vertex);
                visited[vertex] = 1;
            }
        bfs_queue.push(cur_vertex + 1);
    }
    return bfs_queue;
}
```

### DFS (обход в глубину):
```cpp
std::queue<int> Graph::dfs(int start) {
    std::queue<int> dfs_queue;
    std::stack<int> vertex_queue;
    std::vector<bool> visited(vertex_count, 0);
    vertex_queue.push(start);
    while(!vertex_queue.empty()) {
        int cur_vertex = vertex_queue.top();
        vertex_queue.pop();
        if (visited[cur_vertex]) continue;
        visited[cur_vertex] = 1;
        for (int vertex = 0; vertex < vertex_count; ++vertex)
            if (adjacency_matrix[cur_vertex][vertex])
                vertex_queue.push(vertex);
        dfs_queue.push(cur_vertex + 1);
    }
    return dfs_queue;
}
```

## ⚠️ Особенности реализации

- **Лексикографический порядок**: смежные вершины сортируются для сохранения порядка
- **Универсальные идентификаторы**: вершины - числа
- **Эффективное хранение**: матрица смежности для оптимального обхода
- **Обработка всех случаев**: изолированные вершины, циклы, несвязные графы

## 🎯 Тестовые сценарии

Программа тестируется на:
1. **Неориентированные графы** с DFS/BFS
2. **Ориентированные графы** с DFS/BFS  
3. **Разные начальные вершины**
4. **Графы с циклами**
5. **Несвязные графы** (обход только достижимых вершин)

---

*Реализация гарантирует корректный обход согласно заданному порядку и типу графа*