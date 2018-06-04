Количество слов Дика для ПСП длины n.
Автор: Константин Челпанов.

OEIS: [A000108] (https://oeis.org/A000108) Catalan numbers.

n-ое число Каталана равно количеству правильных скобочных последовательностей длины 2*n (состоящих из n открывающих и n закрывающих скобок,
при этом в любом префиксе количество закрывающих скобок не превосходит количества закрывающих).

Ссылки:

[Wikipedia] https://en.wikipedia.org/wiki/Catalan_number
[MathWorld] http://mathworld.wolfram.com/CatalanNumber.html

Предподсчёт: O(N^2), N=25 - максимальное число, для которого N-ое число Каталана вмещается в int64_max.

Функция 'total':  O(1).

Функция 'generate_all': O(n * answer).

Функция 'is_valid': O(n).

Функция 'number_by_object': O(n).

Функция 'object_by_number': O(n).

Функция 'next': O(n).

Функция 'prev': O(n).


