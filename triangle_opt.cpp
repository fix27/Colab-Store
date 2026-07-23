#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>
#include <cstring>

using namespace std;
using namespace chrono;

using ll = long long;
using ull = unsigned long long;

// Быстрая проверка на полный квадрат (через битсет)
// Проверка: n^2 == x для x до ~2e17, sqrt(x) до ~4.5e8
// Используем bitset на 128MB для O(1) проверки
const int MAX_SQRT = 490000000; // ~sqrt(2.4e17)
vector<bool> is_sq(MAX_SQRT + 1, false);

void init_squares() {
    for (ll i = 1; i <= MAX_SQRT; i++) {
        ll sq = i * i;
        if (sq <= MAX_SQRT) is_sq[sq] = true; // для малых значений
        // для больших значений используем проверку через sqrt
    }
}

inline bool is_perfect_square(ll n) {
    if (n < 0) return false;
    ll r = (ll)sqrtl((long double)n);
    // Корректировка из-за погрешностей double
    while ((r + 1) * (r + 1) <= n) r++;
    while (r * r > n) r--;
    return r * r == n;
}

inline bool check_heronian(ll a, ll b, ll c) {
    ll p2 = a + b + c;
    ll s2_16 = p2 * (b + c - a) * (a + c - b) * (a + b - c);
    if (s2_16 <= 0) return false;
    if (s2_16 % 16 != 0) return false;
    return is_perfect_square(s2_16 / 16);
}

inline bool check_medians(ll a, ll b, ll c) {
    ll d_a = 2LL * b * b + 2LL * c * c - a * a;
    ll d_b = 2LL * a * a + 2LL * c * c - b * b;
    ll d_c = 2LL * a * a + 2LL * b * b - c * c;

    if (d_a <= 0 || d_b <= 0 || d_c <= 0) return false;
    if (d_a % 4 != 0 || d_b % 4 != 0 || d_c % 4 != 0) return false;

    return is_perfect_square(d_a / 4) &&
           is_perfect_square(d_b / 4) &&
           is_perfect_square(d_c / 4);
}

void search_bruteforce(int max_side) {
    cout << "Полный перебор до " << max_side << "..." << endl;
    auto start = high_resolution_clock::now();

    ll total_checks = 0;
    int found = 0;
    int heronian_count = 0;

    for (int a = 1; a <= max_side && found == 0; a++) {
        if (a % 1000 == 0) {
            auto now = high_resolution_clock::now();
            auto sec = duration_cast<seconds>(now - start).count();
            cout << "  a=" << a << " (прошло " << sec << "с)" << endl;
        }

        for (int b = a; b <= max_side && found == 0; b++) {
            int max_c = min(max_side, a + b - 1);
            if (max_c < b) continue;

            // Оптимизация: для каждого (a,b) можно найти c через
            // условие пифагоровой тройки, но пока просто перебираем
            for (int c = b; c <= max_c; c++) {
                total_checks++;

                // Быстрый отсев: медиана к a целая => 2b^2+2c^2-a^2 делится на 4
                // и является полным квадратом
                ll d_a = 2LL * b * b + 2LL * c * c - a * a;
                if (d_a <= 0 || d_a % 4 != 0) continue;
                if (!is_perfect_square(d_a / 4)) continue;

                ll d_b = 2LL * a * a + 2LL * c * c - b * b;
                if (d_b <= 0 || d_b % 4 != 0) continue;
                if (!is_perfect_square(d_b / 4)) continue;

                ll d_c = 2LL * a * a + 2LL * b * b - c * c;
                if (d_c <= 0 || d_c % 4 != 0) continue;
                if (!is_perfect_square(d_c / 4)) continue;

                // Все три медианы целые! Проверяем площадь
                ll p2 = a + b + c;
                ll s2_16 = p2 * (b + c - a) * (a + c - b) * (a + b - c);
                if (s2_16 <= 0) continue;
                if (s2_16 % 16 != 0) continue;
                if (!is_perfect_square(s2_16 / 16)) continue;

                // НАЙДЕНО!
                ll s = (ll)sqrtl(s2_16 / 16);
                ll m_a = (ll)sqrtl(d_a / 4);
                ll m_b = (ll)sqrtl(d_b / 4);
                ll m_c = (ll)sqrtl(d_c / 4);

                cout << "\n*** НАЙДЕНО! ***" << endl;
                cout << "  Стороны: " << a << ", " << b << ", " << c << endl;
                cout << "  Площадь: " << s << endl;
                cout << "  Медианы: " << m_a << ", " << m_b << ", " << m_c << endl;
                found++;
            }
        }
    }

    auto end = high_resolution_clock::now();
    auto sec = duration_cast<seconds>(end - start).count();

    if (found == 0) {
        cout << "Не найдено до " << max_side << endl;
    }
    cout << "Проверено треугольников: " << total_checks << endl;
    cout << "Время: " << sec << " сек" << endl;
}

int main() {
    // Поиск до 5000 (медленнее, но тщательнее)
    search_bruteforce(5000);
    return 0;
}
