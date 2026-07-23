# Поиск целых медиан в Heronian треугольниках (все целочисленные треугольники с целой площадью)
# Генерация через склейку пифагоровых троек по общему катету (алгоритм Шуберта)
import math
import time

MAX_LEG = 5000   # максимальный катет (высота) 
MAX_HYP = 10000  # максимальная гипотенуза

def gen_pythagorean_pairs(limit_hyp=10000):
    """Генерирует все пифагоровы тройки (leg, other_leg, hyp) и группирует по общему катету."""
    triples_by_leg = {}
    max_m = int(math.isqrt(limit_hyp)) + 1
    
    for m in range(2, max_m + 1):
        for n in range(1, m):
            if (m - n) % 2 == 0:
                continue  # примитивная тройка требует m-n нечетное
            if math.gcd(m, n) != 1:
                continue
            
            a0 = m*m - n*n
            b0 = 2*m*n
            c0 = m*m + n*n
            
            if c0 > limit_hyp:
                continue
            
            k = 1
            while k * c0 <= limit_hyp:
                a = k * a0
                b = k * b0
                c = k * c0
                
                for leg, other, hyp in [(a, b, c), (b, a, c)]:
                    if leg not in triples_by_leg:
                        triples_by_leg[leg] = []
                    triples_by_leg[leg].append((other, hyp))
                
                k += 1
    
    return triples_by_leg


def medians_count(a, b, c):
    """Возвращает количество целых медиан (0-3) и False если треугольник невалидный."""
    if a + b <= c or a + c <= b or b + c <= a:
        return -1
    
    cnt = 0
    # медиана к a
    d_a = 2*b*b + 2*c*c - a*a
    if d_a > 0 and d_a % 4 == 0 and math.isqrt(d_a // 4) ** 2 == d_a // 4:
        cnt += 1
    
    d_b = 2*a*a + 2*c*c - b*b
    if d_b > 0 and d_b % 4 == 0 and math.isqrt(d_b // 4) ** 2 == d_b // 4:
        cnt += 1
    
    d_c = 2*a*a + 2*b*b - c*c
    if d_c > 0 and d_c % 4 == 0 and math.isqrt(d_c // 4) ** 2 == d_c // 4:
        cnt += 1
    
    return cnt


def main():
    print(f"=== Генерация Heronian треугольников (макс. катет={MAX_LEG}, макс. гипотенуза={MAX_HYP}) ===")
    print("Склейка пифагоровых троек по общему катету...")
    
    t0 = time.time()
    triples = gen_pythagorean_pairs(MAX_HYP)
    print(f"Сгенерировано {len(triples)} значений катетов за {time.time()-t0:.1f}c")
    
    stats = [0, 0, 0, 0]  # 0,1,2,3 целых медиан
    total = 0
    best_examples = []
    
    t1 = time.time()
    
    # Перебираем общие катеты (высоты)
    for h, pairs in triples.items():
        if len(pairs) < 2:
            continue
        
        # Все тройки (катет h, другой катет p, гипотенуза b)
        # Для каждой пары троек с этим h склеиваем:
        for i in range(len(pairs)):
            p, b = pairs[i]
            for j in range(i, len(pairs)):
                q, c = pairs[j]
                a = p + q  # основание разбито высотой на отрезки p и q
                
                # Треугольное неравенство
                if a <= 0:
                    continue
                if a >= b + c or b >= a + c or c >= a + b:
                    continue
                
                total += 1
                cnt = medians_count(a, b, c)
                if cnt >= 0:
                    stats[cnt] += 1
                
                if cnt >= 2 and len(best_examples) < 20:
                    d_a = 2*b*b + 2*c*c - a*a
                    m_a = int(math.isqrt(d_a//4)) if d_a > 0 and d_a % 4 == 0 and math.isqrt(d_a//4)**2 == d_a//4 else None
                    d_b = 2*a*a + 2*c*c - b*b
                    m_b = int(math.isqrt(d_b//4)) if d_b > 0 and d_b % 4 == 0 and math.isqrt(d_b//4)**2 == d_b//4 else None
                    d_c = 2*a*a + 2*b*b - c*c
                    m_c = int(math.isqrt(d_c//4)) if d_c > 0 and d_c % 4 == 0 and math.isqrt(d_c//4)**2 == d_c//4 else None
                    best_examples.append((a, b, c, m_a, m_b, m_c, h, p, q))
    
    elapsed = time.time() - t1
    print(f"Проверено треугольников: {total} за {elapsed:.1f}c")
    print(f"Статистика медиан: 0={stats[0]}, 1={stats[1]}, 2={stats[2]}, 3={stats[3]}")
    print()
    
    if best_examples:
        print("Примеры с 2+ целыми медианами:")
        for a, b, c, m_a, m_b, m_c, h, p, q in best_examples:
            mids = f"m_a={m_a}" if m_a else "m_a=?"
            if m_b: mids += f", m_b={m_b}"
            if m_c: mids += f", m_c={m_c}"
            print(f"  ({a}, {b}, {c}) h={h} [{mids}]")
    
    # Дополнительно: проверяем все треугольники с 1 целой медианой на паттерны
    print()
    print("=== АНАЛИЗ ПАТТЕРНОВ ===")
    if stats[2] > 0 or stats[3] > 0:
        print("Есть треугольники с 2+ медианами — подробный анализ выше.")
    else:
        print("Все 2-медианные треугольники в этом наборе оказались с 0-1 целой медианой.")


if __name__ == "__main__":
    main()
