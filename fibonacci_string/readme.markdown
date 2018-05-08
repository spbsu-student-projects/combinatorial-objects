*Строка Фибоначчи* длины n &mdash; это строка из n цифр,
каждая из которых равна 0 или 1, и в которой нет двух единиц подряд.

Автор: Иван Казменко

OEIS: [A000045](https://oeis.org/A000045)

Ссылки:
[MathWorld](http://mathworld.wolfram.com/FibonacciNumber.html),
[Википедия](https://en.wikipedia.org/wiki/Fibonacci_number#Use_in_mathematics).

Предподсчёт: O(n), где n = 90 &mdash; максимальное число,
для которого количество строк Фибоначчи длины n помещается в `int64_t`.

Функция `total`: O(1).

Функция `generate_all`: O(n * answer).

Функция `is_valid`: O(n).

Функция `number_by_object`: O(n).

Функция `object_by_number`: O(n).

Функция `prev`: O(n), амортизированно за O(1).

Функция `next`: O(n), амортизированно за O(1).
