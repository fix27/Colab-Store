#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

using ll = long long;

ll gcd(ll a, ll b) {
    while (b) { ll t = b; b = a % b; a = t; }
    return a;
}

bool is_perfect_square(ll n) {
    if (n < 0) return false;
    ll r = (ll)sqrtl((long double)n);
    while ((r + 1) * (r + 1) <= n) r++;
    while (r * r > n) r--;
    return r * r == n;
}

struct Triple {
    ll leg1, leg2, hyp; // leg1^2 + leg2^2 = hyp^2
};

// Проверка: треугольник (a,b,c) имеет целые медианы и площадь
bool check_triangle(ll a, ll b, ll c) {
    if (a + b <= c || a + c <= b || b + c <= a) return false;

    // Площадь (Герон)
    ll p2 = a + b + c;
    ll s2_16 = p2 * (b + c - a) * (a + c - b) * (a + b - c);
    if (s2_16 <= 0) return false;
    if (s2_16 % 16 != 0) return false;
    if (!is_perfect_square(s2_16 / 16)) return false;

    // Медианы
    ll d_a = 2LL * b * b + 2LL * c * c - a * a;
    ll d_b = 2LL * a * a + 2LL * c * c - b * b;
    ll d_c = 2LL * a * a + 2LL * b * b - c * c;

    if (d_a <= 0 || d_b <= 0 || d_c <= 0) return false;
    if (d_a % 4 != 0 || d_b % 4 != 0 || d_c % 4 != 0) return false;
    if (!is_perfect_square(d_a / 4)) return false;
    if (!is_perfect_square(d_b / 4)) return false;
    if (!is_perfect_square(d_c / 4)) return false;

    return true;
}

int main() {
    auto start = high_resolution_clock::now();

    const int MAX_HYP = 10000;
    const int MAX_SIDE = 10000;

    cout << "Генерация пифагоровых троек (гипотенуза <= " << MAX_HYP << ")..." << endl;

    vector<Triple> triples;

    // Генерация всех пифагоровых троек
    for (int m = 2; m * m + 1 <= MAX_HYP; m++) {
        for (int n = 1; n < m; n++) {
            if (gcd(m, n) != 1) continue;
            if ((m - n) % 2 == 0) continue;

            // Примитивная тройка
            ll a_base = (ll)m * m - (ll)n * n;
            ll b_base = 2LL * m * n;
            ll c_base = (ll)m * m + (ll)n * n;

            // Масштабирование
            for (ll k = 1; k * c_base <= MAX_HYP; k++) {
                triples.push_back({k * a_base, k * b_base, k * c_base});
                // Также сохраняем с переставленными катетами для группировки
            }
        }
    }

    cout << "Всего троек: " << triples.size() << endl;

    // Группировка по каждому катету
    unordered_map<ll, vector<pair<ll, ll>>> groups; // leg -> [(other_leg, hyp)]

    for (const auto& t : triples) {
        groups[t.leg1].push_back({t.leg2, t.hyp});
        groups[t.leg2].push_back({t.leg1, t.hyp});
    }

    cout << "Всего групп: " << groups.size() << endl;

    ll heronian_count = 0;
    int found = 0;

    // Для каждой группы — комбинируем пары
    for (auto& [leg, vec] : groups) {
        if (vec.size() < 2) continue;

        // Убираем дубликаты
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());

        for (size_t i = 0; i < vec.size(); i++) {
            for (size_t j = i + 1; j < vec.size(); j++) {
                auto [a1, c1] = vec[i];
                auto [a2, c2] = vec[j];

                // Случай суммы
                ll base = a1 + a2;
                if (base <= MAX_SIDE) {
                    ll sides[3] = {c1, c2, base};
                    sort(sides, sides + 3);
                    if (sides[0] + sides[1] > sides[2] && sides[2] <= MAX_SIDE) {
                        heronian_count++;
                        if (check_triangle(sides[0], sides[1], sides[2])) {
                            cout << "\n*** НАЙДЕНО! ***" << endl;
                            cout << "Стороны: " << sides[0] << ", " << sides[1] << ", " << sides[2] << endl;
                            cout << "Leg: " << leg << ", a1=" << a1 << ", a2=" << a2 << " (sum)" << endl;
                            found++;
                        }
                    }
                }

                // Случай разности
                if (a1 != a2) {
                    base = abs(a1 - a2);
                    if (base <= MAX_SIDE && base > 0) {
                        ll sides[3] = {c1, c2, base};
                        sort(sides, sides + 3);
                        if (sides[0] + sides[1] > sides[2] && sides[2] <= MAX_SIDE) {
                            heronian_count++;
                            if (check_triangle(sides[0], sides[1], sides[2])) {
                                cout << "\n*** НАЙДЕНО! ***" << endl;
                                cout << "Стороны: " << sides[0] << ", " << sides[1] << ", " << sides[2] << endl;
                                cout << "Leg: " << leg << ", a1=" << a1 << ", a2=" << a2 << " (diff)" << endl;
                                found++;
                            }
                        }
                    }
                }
            }
        }
    }

    // Также проверяем масштабирования найденных треугольников
    // (для проверки, не пропустили ли мы случай с общим множителем)

    auto end = high_resolution_clock::now();
    auto sec = duration_cast<seconds>(end - start).count();

    cout << "\n--- Результаты ---" << endl;
    if (found > 0) {
        cout << "Найдено треугольников: " << found << endl;
    } else {
        cout << "Треугольников с целыми сторонами, медианами и площадью" << endl;
        cout << "не найдено при максимальной стороне до " << MAX_SIDE << "." << endl;
    }
    cout << "Проверено героновых треугольников: " << heronian_count << endl;
    cout << "Время: " << sec << " сек" << endl;

    return 0;
}
