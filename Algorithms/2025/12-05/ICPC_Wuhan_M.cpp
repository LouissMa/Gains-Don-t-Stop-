#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#include <set>
#include <map>
#include <list>
#include <bitset>
#include <random>
#include <ctime>
#include <chrono>
#include <numeric>
#include <functional>
#include <iomanip>
#include <cassert>
#include <fstream>

typedef long long ll;
typedef double lf;
typedef unsigned long long ull;
typedef unsigned int uint;

// #define DEBUG 1
struct IO
{
    #define MAXSIZE (1 << 20)
    #define isdigit(x) (x >= '0' && x <= '9')
    char buf[MAXSIZE], *p1, *p2;
    char pbuf[MAXSIZE], *pp;
    #if DEBUG
    #else
    IO() : p1(buf), p2(buf), pp(pbuf) {}
    ~IO() {fwrite(pbuf, 1, pp - pbuf, stdout);}
    #endif
    #define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin), p1 == p2) ? ' ' : *p1++)
    #define blank(x) (x == ' ' || x == '\n' || x == '\r' || x == '\t')

    template <typename T>
    void _read(T &x)
    {
        #if DEBUG
        std::cin >> x;
        #else
        bool sign = 0; char ch = gc(); x = 0;
        for (; !isdigit(ch); ch = gc())
            if (ch == '-') sign = 1;
        for (; isdigit(ch); ch = gc()) x = x * 10 + (ch ^ 48);
        if (sign) x = -x;
        #endif
    }
    void _read(char *s)
    {
        #if DEBUG
        std::cin >> s;
        #else
        char ch = gc();
        for (; blank(ch); ch = gc());
        for (; !blank(ch); ch = gc()) *s++ = ch;
        *s = 0;
        #endif
    }
    void _read(char &c) { for (c = gc(); blank(c); c = gc()); }

    void _push(const char &c)
    {
        #if DEBUG
        putchar(c);
        #else
        if (pp - pbuf == MAXSIZE) fwrite(pbuf, 1, MAXSIZE, stdout), pp = pbuf;
        *pp++ = c;
        #endif
    }
    template <typename T>
    void _write(T x)
    {
        if (x < 0) x = -x, _push('-');
        static T sta[35];
        int top = 0;
        do sta[top++] = x % 10, x /= 10; while (x);
        while (top) _push(sta[--top] ^ 48);
    }
    template <typename T>
    void _write(T x, char lst) { _write(x), _push(lst); }
} IO;
#define read(x) IO._read(x)
#define write(x, y) IO._write(x, y)
#define putc(x) IO._push(x)

using namespace std;

int a[20];

int main()
{
    #ifndef DEBUG
    ios::sync_with_stdio(0), cin.tie(0);
    #endif
    int n;
    read(n);
    for (int i = 1; i <= n; i++) read(a[i]);
    for (int i = 1; i <= n; i++, cout << '\n')
        for (int j = 1; j <= n; j++)
            cout << (a[i] + (i == j)) % 998244353 << ' ';
    return 0;
}