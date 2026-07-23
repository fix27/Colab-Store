"""Поиск треугольника со сторонами из последовательных цифр e и π.
Блоки цифр разного размера: a = block₁, b = block₂, c = block₃ из e или π.
"""
import math
import sys


# Первые 200 цифр e (2.71828...)
E_DIGITS = (
    "71828182845904523536028747135266249775724709369995"
    "95749669676277240766303535475945713821785251664274"
    "27466391932003059921817413596629043572900334295260"
    "59563073813232862794349076323382988075319525101901"
)

# Первые 200 цифр π (3.14159...)
PI_DIGITS = (
    "14159265358979323846264338327950288419716939937510"
    "58209749445923078164062862089986280348253421170679"
    "82148086513282306647093844609550582231725359408128"
    "48111745028410270193852110555964462294895493038196"
)


def is_perfect_square(n: int) -> bool:
    if n < 0:
        return False
    r = int(math.isqrt(n))
    return r * r == n


def medians_ok(a: int, b: int, c: int) -> bool:
    """Проверяет, что все три медианы целые."""
    if a + b <= c or a + c <= b or b + c <= a:
        return False

    d_a = 2 * b * b + 2 * c * c - a * a
    if d_a <= 0 or d_a % 4 != 0:
        return False
    if not is_perfect_square(d_a // 4):
        return False

    d_b = 2 * a * a + 2 * c * c - b * b
    if d_b <= 0 or d_b % 4 != 0:
        return False
    if not is_perfect_square(d_b // 4):
        return False

    d_c = 2 * a * a + 2 * b * b - c * c
    if d_c <= 0 or d_c % 4 != 0:
        return False
    if not is_perfect_square(d_c // 4):
        return False

    return True


def area_ok(a: int, b: int, c: int) -> bool:
    p2 = a + b + c
    s2_16 = p2 * (b + c - a) * (a + c - b) * (a + b - c)
    if s2_16 <= 0 or s2_16 % 16 != 0:
        return False
    return is_perfect_square(s2_16 // 16)


def test_blocks(digits: str, name: str, block_sizes: list[int]) -> None:
    """Тестирует треугольники из блоков цифр."""
    print(f"\n=== {name} ===")
    print(f"Всего цифр: {len(digits)}")
    
    for bs in block_sizes:
        # Разбиваем на блоки
        blocks = []
        for i in range(0, len(digits), bs):
            if i + bs <= len(digits):
                blocks.append(int(digits[i:i+bs]))
        
        print(f"  Блоки по {bs} цифр: {len(blocks)} блоков")
        
        if len(blocks) < 3:
            continue
        
        checked = med_ok = found = 0
        
        for i in range(len(blocks)):
            a = blocks[i]
            for j in range(i, len(blocks)):
                b = blocks[j]
                for k in range(j, len(blocks)):
                    c = blocks[k]
                    if a + b <= c:
                        continue
                    checked += 1
                    
                    if medians_ok(a, b, c):
                        med_ok += 1
                        if area_ok(a, b, c):
                            print(f"    *** НАЙДЕНО! *** Блоки {i},{j},{k}: ({a},{b},{c})")
                            found = 1
        
        print(f"    Проверено: {checked}, медианы: {med_ok}, найдено: {'ДА' if found else 'НЕТ'}")


def test_cross(e_blocks: list[int], pi_blocks: list[int], bs: int) -> None:
    """Тестирует треугольники, где каждая сторона может быть из e ИЛИ π."""
    all_blocks = e_blocks + pi_blocks
    print(f"\n=== e ∪ π (блоки {bs} цифр) ===")
    print(f"  Всего блоков: {len(all_blocks)} (e:{len(e_blocks)} + π:{len(pi_blocks)})")
    
    checked = med_ok = found = 0
    for i in range(len(all_blocks)):
        a = all_blocks[i]
        for j in range(i, len(all_blocks)):
            b = all_blocks[j]
            for k in range(j, len(all_blocks)):
                c = all_blocks[k]
                if a + b <= c:
                    continue
                checked += 1
                if medians_ok(a, b, c):
                    med_ok += 1
                    if area_ok(a, b, c):
                        print(f"    *** НАЙДЕНО! *** ({a},{b},{c})")
                        found = 1
    
    print(f"  Проверено: {checked}, медианы: {med_ok}, найдено: {'ДА' if found else 'НЕТ'}")


def main() -> None:
    block_sizes = [2, 3, 4, 5, 6, 7]
    
    for digits, name in [(E_DIGITS, "e"), (PI_DIGITS, "π")]:
        test_blocks(digits, name, block_sizes)
    
    # Перекрёстные: e + π вместе
    for bs in [3, 4, 5]:
        e_blocks = [int(E_DIGITS[i:i+bs]) for i in range(0, len(E_DIGITS), bs) if i+bs <= len(E_DIGITS)]
        pi_blocks = [int(PI_DIGITS[i:i+bs]) for i in range(0, len(PI_DIGITS), bs) if i+bs <= len(PI_DIGITS)]
        test_cross(e_blocks, pi_blocks, bs)


if __name__ == "__main__":
    main()
