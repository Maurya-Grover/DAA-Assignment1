#include <bits/stdc++.h>
#define newline cout << "\n"
#define pb push_back
#define mp make_pair
#define mod 1000000007
#define all(a) a.begin(), a.end()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define sinput cin.ignore(numeric_limits<streamsize>::max(), '\n')
#define tplate template <typename T = long double>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> pi;

tplate
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

tplate
class Interval
{
public:
    T top, bottom;
    Interval(T t, T b)
    {
        top = t;
        bottom = b;
    }
    bool operator<(const Interval &other) const
    {
        return this->top < other.top;
    }
};

tplate
class LineSegment
{
public:
    Interval<T> interval;
    T coord;
    LineSegment(Interval<T> inter, T co)
    {
        interval = inter;
        coord = co;
    }
};

tplate
class Rectangle
{
public:
    T x_left, x_right, y_bottom, y_top;
    Interval<T> x_interval, y_interval;
    Rectangle(){};
    Rectangle(T x1, T x2, T y1, T y2)
    {
        x_left = min(x1, x2);
        x_right = max(x1, x2);
        y_bottom = min(y1, y2);
        y_top = max(y1, y2);
        x_interval = Interval<T>(x_right, x_left);
        y_interval = Interval<T>(y_top, y_bottom);
    }
    Rectangle(Interval<T> x, Interval<T> y)
    {
        x_left = min(x.top, x.bottom);
        x_right = max(x.top, x.bottom);
        y_bottom = min(y.top, y.bottom);
        y_top = max(y.top, y.bottom);
        x_interval = Interval<T>(x_right, x_left);
        y_interval = Interval<T>(y_top, y_bottom);
        // x_interval = x;
        // y_interval = y;
    }
    bool operator<(const Rectangle &other) const
    {
        return this->x_left < other.x_left;
    }
};

tplate
class Edge
{
public:
    Interval<T> interval;
    T coord;
    string side;
    Edge(Interval<T> inter, T co, string sid)
    {
        interval = inter;
        coord = co;
        side = sid;
    }
};

tplate
class Stripe
{
public:
    Interval<T> x_interval, y_interval;
    set<Interval<T>> x_union;
    Stripe(Interval<T> x, Interval<T> y, set<Interval<T>> uni)
    {
        x_interval = x;
        y_interval = y;
        x_union = uni;
    }
};

tplate
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

tplate
set<T> y_set(set<Rectangle<T>> R)
{
    set<T> coord;
    for (auto r : R)
    {
        coord.insert(r.y_top);
        coord.insert(r.y_bottom);
    }
}

tplate
set<Interval<T>> partition(set<T> Y)
{
    set<Interval<T>> result;
    vector<T> Y_vec(Y.begin(), Y.end());

    // Our  Interpretation
    // There does not exist a y belong to Y such that (y1 < y and  y < y2) is true
    // So we'll take only consecutive pairs
    for (int i = 1; i < Y_vec.size(); i++)
        result.insert(Interval<T>(Y_vec[i - 1], Y_vec[i]));
    return result;
}

tplate
set<T> x_proj(set<Point<T>> P)
{
    set<T> coord;
    for(auto p: P)
        coord.insert(p.x);
    return coord;
}

tplate
set<Interval<T>> intervals(set<T> Coord)
{}

tplate
set<Stripe<T>> stripes(set<Rectangle<T>> R, Rectangle<T> f)
{
    set<T> Y = y_set(R);
    Y.insert(f.y_bottom);
    Y.insert(f.y_top);
    auto i_x = f.x_interval;
    set<Interval<T>> y_part = partition(Y);
    for(auto i_y: y_part)
    {
        set<Point<T>> intersect;
        auto i_set = intervals(x_proj(intersect));
        tuple<Interval<T>, Interval<T>, set<Interval<T>>> t;
    }
}


string edgetype[] = {"top", "bottom", "left", "right"};

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