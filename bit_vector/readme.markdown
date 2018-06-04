*Битовый вектор* длины n &mdash;
 это строка из n единиц или нулей, кодирующая подмножество данного n-элементного множества: i-ое число говорит нам, присутствует ли i-ый элемент в подмножестве. 

Автор: Никита Карагодин.

OEIS: [A000079](https://oeis.org/A000079).

Ссылки:
[MathWorld](http://mathworld.wolfram.com/Subset.html),
[Википедия](https://en.wikipedia.org/wiki/Bit_array).

n = 62 &mdash; максимальное число,
для которого количество битовых векторов длины n помещается в `int64_t`.

Функция `total`: O(1).

Функция `generate_all`: O(n * 2^n).

Функция `is_valid`: O(n).

Функция `number_by_object`: O(n).

Функция `object_by_number`: O(n).

Функция `prev`: O(n).

Функция `next`: O(n).