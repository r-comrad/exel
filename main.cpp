#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::vector<int>> a, b;

using funkI  = std::function<int(int, int)>;
using checkD = std::function<bool(double, double)>;

bool
OnBoard(int x, int y)
{
    return x >= 0 && x < a.size() && y >= 0 && y < a[0].size();
}

void
foo(std::vector<int> st, std::vector<int> en, funkI aCond)
{
    if (!OnBoard(en[0], en[1])) return;
    int sum = b[st[0]][st[1]];
    if (a[st[0]][st[1]] < a[en[0]][en[1]])
    {
        sum += a[en[0]][en[1]];
    }
    if (b[en[0]][en[1]] == 0) b[en[0]][en[1]] = sum;
    else b[en[0]][en[1]] = aCond(sum, b[en[0]][en[1]]);
}

void
print()
{
    for (auto& i : b)
    {
        for (auto j : i)
        {
            std::cout << std::setw(5) << j << " ";
        }
        std::cout << "\n";
    }
}

void
A(std::vector<int> dir,
  void lambda(std::vector<int> st, std::vector<int> en, funkI), funkI aCond)
{
    std::string s;
    while (std::getline(std::cin, s))
    {
        std::stringstream ss;
        ss << s;

        a.emplace_back();
        int num;
        while (ss >> num)
        {
            a.back().emplace_back(num);
        }
    }

    int x = dir[0], y = dir[1];
    int n = x > 0 ? 0 : a.size() - 1, m = y > 0 ? 0 : a[0].size() - 1;

    b.resize(a.size(), std::vector<int>(a[0].size()));
    b[n][m] = a[n][m];

    for (int i = n; OnBoard(i, 0); i += x)
    {
        for (int j = m; OnBoard(0, j); j += y)
        {
            int new_x = i + x;
            int new_y = j + y;

            lambda({i, j}, {new_x, j}, aCond);
            lambda({i, j}, {i, new_y}, aCond);
        }
    }

    print();
}

void
B(checkD aComp, double aVal, checkD aResComp)
{
    std::vector<double> v(1);
    while (std::cin >> v.back())
    {
        v.emplace_back();
    }
    v.pop_back();

    std::vector<double> d(v.size());
    d[0] = v[0];
    for (int i = 0; i < v.size() - 1; ++i)
    {
        d[i + 1] = v[i + 1];
        if (aComp(v[i], v[i + 1]) && std::abs(v[i] - v[i + 1]) <= aVal)
        {
            d[i + 1] += d[i];
        }
    }

    std::cout << *std::max_element(d.begin(), d.end(), aResComp);
}

void
fooC(std::vector<int> st, std::vector<int> en, funkI aCond)
{
    if (!OnBoard(en[0], en[1])) return;
	if (en[0] == 0 && en[1] == 0)
	{
        int yy = 0;
        ++yy;
    }
    // if (b[st[0]][st[1]] < 0)
    // {
    //     b[st[0]][st[1]] = -1000;
    // }
    int sum = b[st[0]][st[1]] + a[en[0]][en[1]];
    if (b[en[0]][en[1]] == 0) b[en[0]][en[1]] = sum;
    else b[en[0]][en[1]] = aCond(sum, b[en[0]][en[1]]);
}

int
main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);

    A({ 1, 1 }, foo, [](int a, int b) {return std::min(a, b); });
    // B(std::greater<double>(), 8, std::less<double>());
    // A({-1, -1}, fooC, [](int a, int b) { return std::max(a, b); });
}
