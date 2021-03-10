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

tplate const T inf = numeric_limits<T>::infinity();

tplate class Point
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

tplate class Interval
{
public:
    T top, bottom;
    Interval() {}
    Interval(T b, T t)
    {
        bottom = b;
        top = t;
    }
    bool operator<(const Interval &other) const
    {
        return this->bottom < other.bottom;
    }
};

tplate class LineSegment
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

tplate class Rectangle
{
public:
    T x_left, x_right, y_bottom, y_top;
    Interval<T> x_interval, y_interval;
    Rectangle() {}
    Rectangle(T x1, T x2, T y1, T y2)
    {
        x_left = min(x1, x2);
        x_right = max(x1, x2);
        y_bottom = min(y1, y2);
        y_top = max(y1, y2);
        x_interval = Interval<T>(x_left, x_right);
        y_interval = Interval<T>(y_bottom, y_top);
    }
    Rectangle(Interval<T> x, Interval<T> y)
    {
        x_left = min(x.top, x.bottom);
        x_right = max(x.top, x.bottom);
        y_bottom = min(y.top, y.bottom);
        y_top = max(y.top, y.bottom);
        x_interval = Interval<T>(x_left, x_right);
        y_interval = Interval<T>(y_bottom, y_top);
        // x_interval = x;
        // y_interval = y;
    }
    bool operator<(const Rectangle &other) const
    {
        return this->x_left < other.x_left;
    }
};

tplate class Edge
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
    bool operator<(const Edge &other) const
    {
        return this->coord < other.coord;
    }
    bool operator==(const Edge &other) const
    {
        return this->interval.bottom == other.interval.bottom and this->interval.top == other.interval.top;
    }
};

tplate class Stripe
{
public:
    Interval<T> x_interval, y_interval;
    T x_measure;
    Stripe(){}
    Stripe(Interval<T> x, Interval<T> y, T m)
    {
        x_interval = x;
        y_interval = y;
        x_measure = m;
    }
};

// Set difference
template<class T>
set<T> operator -(set<T> reference, set<T> items_to_remove)
{
    set<T> result;
    std::set_difference(
        reference.begin(), reference.end(),
        items_to_remove.begin(), items_to_remove.end(),
        std::inserter(result, result.end()));
    return result;
}

// Set union
template<class T>
set<T> operator +(set<T> reference, set<T> items_to_remove)
{
    set<T> result;
    std::set_union(
        reference.begin(), reference.end(),
        items_to_remove.begin(), items_to_remove.end(),
        std::inserter(result, result.end()));
    return result;
}

// Set intersection
template<class T>
set<T> operator ^(set<T> reference, set<T> items_to_remove)
{
    set<T> result;
    std::set_intersection(
        reference.begin(), reference.end(),
        items_to_remove.begin(), items_to_remove.end(),
        std::inserter(result, result.end()));
    return result;
}

tplate
    set<Point<T>>
    unionArea(set<Rectangle<T>> r)
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
    set<T>
    y_set(set<Rectangle<T>> R)
{
    set<T> coord;
    for (auto r : R)
    {
        coord.insert(r.y_top);
        coord.insert(r.y_bottom);
    }
}

tplate
    set<Interval<T>>
    partition(set<T> Y)
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
    set<T>
    x_proj(set<Point<T>> P)
{
    set<T> coord;
    for (auto p : P)
        coord.insert(p.x);
    return coord;
}

tplate
    set<Interval<T>>
    intervals(set<T> Coord)
{
}

tplate
    set<Stripe<T>>
    stripes(set<Rectangle<T>> R, Rectangle<T> f)
{
    set<T> Y = y_set(R);
    Y.insert(f.y_bottom);
    Y.insert(f.y_top);
    auto i_x = f.x_interval;
    set<Interval<T>> y_part = partition(Y);
    for (auto i_y : y_part)
    {
        set<Point<T>> intersect;
        auto i_set = intervals(x_proj(intersect));
        tuple<Interval<T>, Interval<T>, set<Interval<T>>> t;
    }
}

string edgetype[] = {"top", "bottom", "left", "right"};


tplate 
set<Stripe<T>> Copy(set<Stripe<T>> S, set<T> P, Interval<T> x_int)
{
    set<Stripe<T>> S2;
    auto i_x = x_int;
    set<Interval<T>> part = partition(P);
    for (auto i_y : part)
    {
        S2.insert({i_x, i_y, 0});
    }
    for(Stripe<T> s2 : S2)
    {
        for(Stripe<T> s : S)
        {
            if(s.y_interval.bottom <= s2.y_interval.bottom 
            and s.y_interval.top >= s2.y_interval.top)
                s2.x_measure = s.x_measure;
        }
    }
    return S2;
}

tplate 
void Blacken(set<Stripe<T>> S, set<Interval<T>> J)
{
    for(Stripe<T> s : S)
    {
        for(Interval<T> i : J)
        {
            if(s.y_interval.bottom >= i.bottom 
            and s.y_interval.top <= i.top)
                s.x_measure = s.x_interval.top - s.x_interval.bottom;
        }
    }
}

tplate 
set<Stripe<T>> Concat(set<Stripe<T>> S1, set<Stripe<T>> S2, 
            set<T> P, Interval<T> x_int)
{
    set<Stripe<T>> S;
    auto i_x = x_int;
    set<Interval<T>> part = partition(P);
    for (auto i_y : part)
    {
        S2.insert({i_x, i_y, 0});
    }
    for(Stripe<T> s : S)
    {
        for(Stripe<T> s1 : S1)
        {
            if(s1.y_interval == s.y_interval)
                for(Stripe<T> s2 : S2)
                {
                    if(s2.y_interval == s.y_interval)
                        s.x_measure = s1.x_measure + s2.x_measure;
                }
        }
    }
    return S;
}

tplate
    set<Stripe<T>>
    STRIPES(set<Edge<T>> V, Interval<T> x_ext,
            set<Interval<T>> L, set<Interval<T>> R,
            set<T> P)
{
    set<Stripe<T>> S;
    if (V.size() == 1)
    {
        Edge<T> v = *(V.begin());
        Stripe<T> s;
        P = {{-inf<T>, v.interval.bottom, v.interval.top, inf<T>}};

        S.clear();
        auto i_x = x_ext;
        set<Interval<T>> part = partition(P);
        for (auto i_y : part)
        {
            S.insert({i_x, i_y, 0});
        }

        if (v.side == "left")
        {
            L.clear();
            L.insert(v.interval);
            R.clear();
        }
        else
        {
            L.clear();
            R.clear();
            R.insert(v.interval);
        }

        for(Stripe<T> s : S)
        {
            if(s.y_interval == v.interval)
                if(v.side == "left")
                    s.x_measure = x_ext.top - v.coord;
                else
                    s.x_measure = v.coord - x_ext.bottom;
        }

        return S;
    }
    else
    {
        // Divide
        vector<Edge<T>> V1(V.begin(), V.begin() + V.size()/2);
        vector<Edge<T>> V2(V.begin() + V.size()/2 + 1, V.end());
        T x_m = *(V.begin() + V.size()/2 + 1);

        // Conquer
        Interval<T> x_ext1(x_ext.bottom, x_m);
        set<Edge<T>> L1, R1;
        set<T> P1;
        Stripe<T> S1 = STRIPES(V1, x_ext1, L1, R1, P1);

        Interval<T> x_ext2(x_m, x_ext.top);
        set<Edge<T>> L2, R2;
        set<T> P2;
        Stripe<T> S2 = STRIPES(V1, x_ext2, L2, R2, P2);

        // Merge
        auto LR = L1 ^ R2;
        L = (L1 - LR) + L2;
        R = R1 + (R2 - LR);
        P = P1 + P2;

        set<Stripe<T>> S_left = Copy(S1, P, x_ext1);
        set<Stripe<T>> S_right = Copy(S2, P, x_ext2);

        Blacken(S_left, R2-LR);
        Blacken(S_right, L1-LR);

        S = Concat(S_left, S_right, x_ext);
    }
}

tplate
    set<Stripe<T>>
    RECTANGLE_DAC(set<Rectangle<T>> RECT)
{
    vector<Edge<T>> VRX;
    for (Rectangle<T> R : RECT)
    {
        Edge<T> leftVerticalEdge(R.x_left, R.y_interval, "left");
        Edge<T> rightVerticalEdge(R.x_right, R.y_interval, "right");
        VRX.push_back(leftVerticalEdge);
        VRX.push_back(rightVerticalEdge);
    }
    sort(VRX);
    Interval<T> x_ext(-inf<T>, inf<T>);
    set<Edge<T>> L, R;
    set<T> P;
    return STRIPES(VRX, x_ext, L, R, P);
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