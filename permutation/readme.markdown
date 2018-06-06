Перестановка длины n &mdash; это последовательность из n чисел, каждое из которых встречается в ней ровно один раз.

Автор: Павел Гранин.

OEIS: [A000142](http://oeis.org/A000142).

Ссылки:
[MathWorld](http://mathworld.wolfram.com/Permutation.html),
[Википедия](https://en.wikipedia.org/wiki/Permutation).

Предподсчёт: O(N), где N = 20 &mdash; максимальное число,
для которого количество перестановок длины N помещается в `int64_t`.

Функция `total`: O(1).

Функция `generate_all`: O(n * n!).

Функция `is_valid`: O(n).

Функция `number_by_object`: O(n * n).

Функция `object_by_number`: O(n * n).

Функция `prev`: O(n * n).

Функция `next`: O(n * n).
