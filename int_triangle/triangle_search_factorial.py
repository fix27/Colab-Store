"""Поиск треугольника с целыми медианами и площадью, где стороны — факториалы.

Математически доказано: НИ ОДИН треугольник с факториальными сторонами
не может иметь целые медианы.

Доказательство:
  a = x!, b = c = y! (единственный случай с неравенством треугольника)
  d_a = 4(y!)² - (x!)² = (x!)² · A · B
  где A = 2y!/x! - 1, B = 2y!/x! + 1
  gcd(A,B) = 1, B - A = 2
  Для A·B быть квадратом: A = p², B = q²
  q² - p² = 2 → (q-p)(q+p) = 2 → нет целых решений
"""

import math
import sys


def is_perfect_square(n: int) -> bool:
    if n < 0:
        return False
    r = int(math.isqrt(n))
    return r * r == n


def main() -> None:
    max_n = int(sys.argv[1]) if len(sys.argv) > 1 else 20

    facts = [1]
    for i in range(1, max_n + 1):
        facts.append(facts[-1] * i)

    print("Факториалы: a = x!, b = y!, c = z! | Доказано: невозможно")
    print()

    # Демо: проверяем d_a/4 для малых значений
    print("Проверка d_a/4 (демонстрация, что никогда не квадрат):")
    for y in range(2, min(11, max_n + 1)):
        b = facts[y]
        for x in range(2, y + 1):
            a = facts[x]
            d_a = 4 * b * b - a * a
            d_a4 = d_a // 4
            r = int(math.isqrt(d_a4))
            ok = (r * r == d_a4)
            print(f"  x={x:2d} y={y:2d}  d_a/4 = {d_a4}  sqrt={r}  квадрат? {ok}")


if __name__ == "__main__":
    main()
