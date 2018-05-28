*Беспорядок* длины n &mdash;
перестановка чисел от 1 до n, в которой ни одно число не стоит на своём месте.

Автор: Иван Казменко.

OEIS: [A000166](http://oeis.org/A000166).

Ссылки:
[MathWorld](http://mathworld.wolfram.com/Derangement.html),
[Википедия](https://en.wikipedia.org/wiki/Derangement).

Предподсчёт: нет.

Функция `total`: O(n * answer).

Функция `generate_all`: O(n * answer).

Функция `is_valid`: O(n).

Функция `number_by_object`: O(n * answer).

Функция `object_by_number`: O(n * answer).

Функция `prev`: O(n * answer).

Функция `next`: O(n * answer).
