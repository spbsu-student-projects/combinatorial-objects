Представление n в виде суммы положительных слагаемых.
Автор: Матвей Жуков.

OEIS: [A000041](https://oeis.org/A000041)  Number of partitions of n (the partition numbers).

Представление в виде суммы положительных слагаемых есть то же самое, что и представление n в виде суммы n неотрицательных слагаемых.

Ссылки:
[MathWorld](http://mathworld.wolfram.com/Partition.html),
[Википедия](https://en.wikipedia.org/wiki/Partition_(number_theory)).

Предподсчёт: O(n), где n = 405 &mdash; максимальное число,
для которого количество разбиений длины n помещается в `int64_t`.

Функция `total`: O(1).

Функция `generate_all`: O(n * answer).

Функция `is_valid`: O(n).	

Функция `number_by_object`: O(n^3).

Функция `object_by_number`: O(n*total(n)).

Функция `prev`: O(n).

Функция `next`: O(n).