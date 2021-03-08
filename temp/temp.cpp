#include <bits/stdc++.h>
#define newline cout << "\n"
#define pb push_back
#define mp make_pair
#define mod 1000000007
#define all(a) a.begin(), a.end()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define sinput cin.ignore(numeric_limits<streamsize>::max(), '\n')
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> pi;

template <typename T = long double>
class Point
{
public:
    T x, y;
    Point(T a, T b)
    {
        x = a;
        y = b;
    }
    bool operator<(const Point &other) const
    {
        return this->x < other.x or this->y < other.y;
    }
};

template <typename T = long double>
class Interval
{
public:
    T top, bottom;
    bool operator<(const Interval &other) const
    {
        return this->top < other.top;
    }
};

template <typename T = long double>
class LineSegment
{
public:
    Interval<T> interval;
    T coord;
};

template <typename T = long double>
class Rectangle
{
public:
    T x_left, x_right, y_bottom, y_top;
    // Interval<T> x_interval, y_interval;
    Rectangle(){};
    Rectangle(T x1, T x2, T y1, T y2)
    {
        x_left = min(x1, x2);
        x_right = max(x1, x2);
        y_bottom = min(y1, y2);
        y_top = max(y1, y2);
    }
    Rectangle(Interval<T> x, Interval<T> y)
    {
        x_left = min(x.top, x.bottom);
        x_right = max(x.top, x.bottom);
        y_bottom = min(y.top, y.bottom);
        y_top = max(y.top, y.bottom);
    }
    bool operator<(const Rectangle &other) const
    {
        return this->x_left < other.x_left;
    }
};

template <typename T = long double>
class Edge
{
public:
    Interval<T> interval;
    T coord;
    string side;
};

string edgetype[] = {"top", "bottom", "left", "right"};

template <typename T = long double>
class Stripe
{
public:
    Interval<T> x_interval, y_interval;
    set<Interval<T>> x_union;
};

template <typename T = long double>
set<Point<T>> unionArea(set<Rectangle<T>> r)
{
    set<Point<T>> result;
    for (auto e : r)
    {
        //cout << e.x_left << " " << e.x_right << " " << e.y_bottom << " " << e.y_top; 
        newline;
        result.insert(Point<T>(e.x_left, e.y_top));
        result.insert(Point<T>(e.x_right, e.y_top));
        result.insert(Point<T>(e.x_right, e.y_bottom));
        result.insert(Point<T>(e.x_left, e.y_bottom));
    }
    return result;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    set<Rectangle<long double>> input;
    int n;
    cin >> n;
    while (n--)
    {
        long double x1, x2, y1, y2;
        cin >> x1 >> x2 >> y1 >> y2;
        Rectangle<long double> r(x1, x2, y1, y2);
        input.insert(r);
    }
    set<Point<long double>> output = unionArea(input);
    for (auto p : output)
        cout << p.x << " - " << p.y << "\n";
    return 0;
}