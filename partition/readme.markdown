������������� n � ���� ����� ������������� ���������.
�����: ������ �����.

OEIS: [A000041](https://oeis.org/A000041) Number of partitions of n (the partition numbers).

������������� � ���� ����� ������������� ��������� ���� �� �� �����, ��� � ������������� n � ���� ����� n ��������������� ���������.

������:
[MathWorld](http://mathworld.wolfram.com/Partition.html),
[���������](https://en.wikipedia.org/wiki/Partition_(number_theory)).

�����������: O(n), ��� n = 405 &mdash; ������������ �����,
��� �������� ���������� ��������� ����� n ���������� � `int64_t`.

������� `total`: O(1).

������� `generate_all`: O(n * total(n)).

������� `is_valid`: O(n).

������� `number_by_object`: O(n^3).

������� `object_by_number`: O(n^4).

������� `prev`: O(n).

������� `next`: O(n).