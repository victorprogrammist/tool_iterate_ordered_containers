
#ifndef PAIR_MAP_H
#define PAIR_MAP_H

#include <utility>
#include <type_traits>
#include <functional>


template <class T>
const T &get_key(const T &v) { return v; }

template <class A, class B>
const A &get_key(const std::pair<A,B> &pr) { return pr.first; }

template <class C1, class C2>
struct PairMap {

    using Cont1 = C1;
    using Cont2 = C2;

    using Itr1 = decltype(std::declval<Cont1>().begin());
    using Itr2 = decltype(std::declval<Cont2>().begin());

    using UnItr1 = typename std::remove_reference<decltype(*std::declval<Itr1>())>::type;
    using UnItr2 = typename std::remove_reference<decltype(*std::declval<Itr2>())>::type;

    using Task1 = function<void(const UnItr1 &v1)>;
    using Task2 = function<void(const UnItr2 &v2)>;
    using TaskPair = function<void(const UnItr1 *v1, const UnItr2 *v2)>;

    static void run_diference_2(Cont1 &c1, Cont2 &c2, const Task2 &task) {
        PairMap<Cont2,Cont1>::run_diference(c2, c1, task); }

    static void run_diference(Cont1 &c1, Cont2 &c2, const Task1 &task) {

        Itr1 be1 = c1.begin();
        Itr1 en1 = c1.end();
        Itr2 be2 = c2.begin();
        Itr2 en2 = c2.end();

        while (be1 != en1 && be2 != en2) {
            if (get_key(*be1) < get_key(*be2)) {
                task(*be1);
                ++be1;
            } else if (get_key(*be2) < get_key(*be1))
                ++be2;
            else {
                ++be1;
                ++be2;
            }
        }
        std::for_each(be1, en1, task);
    }

    static void run_union(Cont1 &c1, Cont2 &c2, const TaskPair &task) {

        Itr1 be1 = c1.begin();
        Itr1 en1 = c1.end();
        Itr2 be2 = c2.begin();
        Itr2 en2 = c2.end();

        while (true) {

            if (be1 == en1) {
                for (; be2 != en2; ++be2) task(nullptr, &*be2);
                return;
            } else if (be2 == en2) {
                for (; be1 != en1; ++be1) task(&*be1, nullptr);
                return;
            }

            if (get_key(*be1) < get_key(*be2)) {
                task(&*be1, nullptr);
                ++be1;
            } else if (get_key(*be2) < get_key(*be1)) {
                task(nullptr, &*be2);
                ++be2;
            } else {
                task(&*be1, &*be2);
                ++be1;
                ++be2;
            }
        }
    }
};


#endif // PAIR_MAP_H
