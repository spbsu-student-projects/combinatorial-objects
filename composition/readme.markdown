*Слабые разбиения* (weak composition) числа n на n неотрицательных целых слагаемых с учетом порядка &mdash;
это количество кортежей из n неотрицательных целых чисел, в сумме дающих n, с учетом порядка их расстановки (так, например, расстановки 3=1+2 и 3=2+1 считаются различными).

Автор: Шестаков Семён.

OEIS: [A001700](http://oeis.org/A001700).

Ссылки:
[Wikipedia](https://en.wikipedia.org/wiki/Stars_and_bars_(combinatorics)) - общее описание,
[Wikipedia](https://en.wikipedia.org/wiki/Composition_(combinatorics)).

Предподсчёт: O(n), где n = 31 &mdash; максимальное число,
для которого количество разбиений числа n на n неотрицательных слагаемых с учетом порядка помещается в `int64_t`.

Функция `total`: O(1).

Функция `generate_all`: O(n).

Функция `is_valid`: O(n).

Функция `number_by_object`: O(n).

Функция `object_by_number`: O(n).

Функция `prev`: O(n).

Функция `next`: O(n).

