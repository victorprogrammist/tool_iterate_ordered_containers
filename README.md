# tool_iterate_ordered_containers
Утилита для перебора объединений и пересечений упорядоченных контейнеров

Пример использования:

```cpp
    std::vector<int> list1 = {2,3,4,8,21,32,99};
    std::map<int,char> map2 = {{3,'a'},{8,'b'},{30,'c'},{32,'d'},{33,'e'}};
    using Tool = PairMap<decltype(list1),decltype(map2)>;

    Tool::run_union(list1, map2, [](auto *p1, auto *p2) {
        if (p2)
            qDebug() << "union" << p2->first << p2->second;
        else
            qDebug() << "union" << *p1;
    });

    Tool::run_diference(list1, map2, [](auto &p1) {
        qDebug() << "diference-1" << p1; });

    Tool::run_diference_2(list1, map2, [](auto &p1) {
        qDebug() << "diference-2" << p1.first << p1.second; });

    Tool::run_intersection(list1, map2, [](auto &p1, auto &p2) {
        qDebug() << "intersection" << p2.first << p2.second; });
```
В результате получится вывод:

```txt
union 2
union 3 a
union 4
union 8 b
union 21
union 30 c
union 32 d
union 33 e
union 99
diference-1 2
diference-1 4
diference-1 21
diference-1 99
diference-2 30 c
diference-2 33 e
intersection 3 a
intersection 8 b
intersection 32 d
```

Типы ключей у контейнеров не обязательно должны совпадать,
достаточно что бы был оператор сравнения для этих типов.

Если используются какие то свои контейнеры,
то для них нужно доопределить функцию get_key.

Текущие get_key использованные в примере выше (опеределены в pair_map.h):
```cpp
template <class T>
const T &get_key(const T &v) { return v; }

template <class A, class B>
const A &get_key(const std::pair<A,B> &pr) { return pr.first; }
```

