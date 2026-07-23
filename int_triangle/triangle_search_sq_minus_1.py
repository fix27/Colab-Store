"""Поиск треугольников a = x^2 - 1, b = y^2 - 1, c = z^2 - 1
с целыми медианами.
"""
import math
import sys


def is_perfect_square(n: int) -> bool:
    if n < 0:
        return False
    r = int(math.isqrt(n))
    return r * r == n


def main() -> None:
    max_x = int(sys.argv[1]) if len(sys.argv) > 1 else 1000

    xs = list(range(1, max_x + 1, 2))
    print(f"x^2-1, x <= {max_x}, нечётные x: {len(xs)}")
    print()

    found_medians = []
    found_full = []

    for xi in xs:
        a = xi * xi - 1
        if a <= 0:
            continue
        for yi in xs:
            if yi < xi:
                continue
            b = yi * yi - 1

            # (x^2-1) + (y^2-1) > z^2-1 => z^2 < x^2 + y^2 - 1 => z^2 <= x^2 + y^2 - 2
            max_zz = xi * xi + yi * yi - 2
            if max_zz <= 0:
                continue
            max_z = int(math.isqrt(max_zz))

            for zi in xs:
                if zi < yi or zi > max_z:
                    continue
                c = zi * zi - 1

                d_a = 2 * b * b + 2 * c * c - a * a
                if d_a <= 0 or d_a % 4 != 0:
                    continue
                if not is_perfect_square(d_a // 4):
                    continue

                d_b = 2 * a * a + 2 * c * c - b * b
                if d_b <= 0 or d_b % 4 != 0:
                    continue
                if not is_perfect_square(d_b // 4):
                    continue

                d_c = 2 * a * a + 2 * b * b - c * c
                if d_c <= 0 or d_c % 4 != 0:
                    continue
                if not is_perfect_square(d_c // 4):
                    continue

                m_a = int(math.isqrt(d_a // 4))
                m_b = int(math.isqrt(d_b // 4))
                m_c = int(math.isqrt(d_c // 4))

                found_medians.append((xi, yi, zi, a, b, c, m_a, m_b, m_c))

                p2 = a + b + c
                s2_16 = p2 * (b + c - a) * (a + c - b) * (a + b - c)
                if s2_16 > 0 and s2_16 % 16 == 0 and is_perfect_square(s2_16 // 16):
                    s = int(math.isqrt(s2_16 // 16))
                    found_full.append((xi, yi, zi, a, b, c, s, m_a, m_b, m_c))

    print(f"С целыми медианами: {len(found_medians)}")
    if found_medians:
        print(f"\nПервые 20 (x,y,z → a,b,c → медианы):")
        for i, (xi, yi, zi, a, b, c, m_a, m_b, m_c) in enumerate(found_medians[:20]):
            print(f"  {xi:3d},{yi:3d},{zi:3d} → {a:8d},{b:8d},{c:8d} → m=({m_a},{m_b},{m_c})")

    if found_full:
        print(f"\nС целыми медианами И площадью: {len(found_full)}")
        for xi, yi, zi, a, b, c, s, m_a, m_b, m_c in found_full:
            print(f"  x={xi}, y={yi}, z={zi}: a={a}, b={b}, c={c}, S={s}")
    else:
        print("\nС целыми медианами И площадью: 0")


if __name__ == "__main__":
    main()
