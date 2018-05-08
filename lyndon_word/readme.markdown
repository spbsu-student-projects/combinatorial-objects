*Простая строка* (или *слово Линдона*) длины n &mdash;
это строка из n двоичных цифр, которая строго меньше
всех своих циклических суффиксов.

Автор: Иван Казменко.

OEIS: [A001037](https://oeis.org/A001037).

Ссылки:
[MathWorld](http://mathworld.wolfram.com/LyndonWord.html),
[Википедия](https://en.wikipedia.org/wiki/Lyndon_word).

Предподсчёта нет.

Функция `total`: O(2^n * n^2).

Функция `generate_all`: O(2^n * n^2).

Функция `is_valid`: O(n^2).

Функция `number_by_object`: O(2^n * n^2).

Функция `object_by_number`: O(2^n * n^2).

Функция `prev`: O(2^n * n^2).

Функция `next`: O(2^n * n^2).
