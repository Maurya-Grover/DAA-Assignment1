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

#define deb(x) cout << #x << "=" << x << endl

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
        return this->x < other.x or (this->x == other.x and this->y < other.y);
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
        return this->bottom < other.bottom or (this->bottom == other.bottom and this->top < other.top);
    }
    bool operator==(const Interval &other) const
    {
        return this->bottom == other.bottom and this->top == other.top;
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
    bool operator<(const LineSegment &other) const
    {
        return this->coord < other.coord or (this->coord == other.coord and this->interval < other.interval);
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
    }
    bool operator<(const Rectangle &other) const
    {
        return this->x_left < other.x_left 
        or (this->x_left == other.x_left and this->x_right < other.x_right)
        or (this->x_left == other.x_left and this->x_right == other.x_right and this->y_bottom < other.y_bottom)
        or (this->x_left == other.x_left and this->x_right == other.x_right and this->y_bottom == other.y_bottom and this->y_top < other.y_top);
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
        return this->coord < other.coord or (this->coord == other.coord and this->side < other.side)
        or (this->coord == other.coord and this->side == other.side and this->interval < other.interval);
    }
};

tplate class ctree
{
    public:
        T x; string side; ctree* lson; ctree* rson;
        ctree()
        {

        }
        ctree(T x, string side, ctree* lson, ctree* rson)
        {
            this->x = x;
            this->side = side;
            this->lson = lson;
            this->rson = rson;
        }
};

tplate class Stripe
{
public:
    Interval<T> x_interval, y_interval;
    ctree<T>* tree;
    Stripe(){}
    Stripe(Interval<T> x, Interval<T> y, ctree<T>* t)
    {
        x_interval = x;
        y_interval = y;
        tree = t;
    }
    bool operator<(const Stripe &other) const
    {
        return this->x_interval < other.x_interval or (this->x_interval == other.x_interval and this->y_interval < other.y_interval);
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


tplate void inorder(ctree<T>* root)
{
    if(!root)
        return;
    inorder(root->lson);
    cout << root->x << root->side << " ";
    inorder(root->rson);
}

tplate void getNodes(ctree<T>* root, vector<Edge<T>> &v, T start, T end)
{
    if(!root)
        return;
    getNodes(root->lson, v, start, end);
    if((root->side == "left" or root->side == "right") and root->x > start and root->x < end)
        v.push_back(Edge<T>(Interval<T>(0,0), root->x, root->side));
    getNodes(root->rson, v, start, end);
}

tplate set<LineSegment<T>> intervals(Edge<T> h, ctree<T>* tree)
{
    vector<Edge<T>> v;
    v.push_back(Edge<T>(Interval<T>(0,0), h.interval.bottom, "start"));
    getNodes(tree, v, h.interval.bottom, h.interval.top);
    v.push_back(Edge<T>(Interval<T>(0,0), h.interval.top, "end"));

    // cout << "\nINTERVALS\n";
    // for(Edge<T> i : v)
    //     cout << i.coord << i.side << " ";
    // cout << "\nINTERVALS\n";
    // cout << "\n";

    char state = 's';
    set<LineSegment<T>> pieces;
    for(int i = 1; i < v.size(); i++)
    {
        if(v[i].side[0] == 'l')         //comparing side
        {
            pieces.insert(LineSegment<T>(Interval<T>(v[i-1].coord, v[i].coord), h.coord));
            state = 'l';
        }
        else if(v[i].side[0] == 'r')
        {
            state = 'r';
        }
        else if((state == 's' or state == 'r') and v[i].side[0] == 'e')
        {
            pieces.insert(LineSegment<T>(Interval<T>(v[i-1].coord, v[i].coord), h.coord));
            state = 'e';
        }
        else
        {
            state = 'e';
        }
    }
    return pieces;
}

tplate set<LineSegment<T>> contour_pieces(Edge<T> h, set<Stripe<T>> S)
{
    Stripe<T> s_;
    s_.tree = NULL;
    if(h.side == "bottom")
    {
        for(Stripe<T> s:S)
            if(s.y_interval.top == h.coord)
                s_ = s;
    }
    else
    {
        for(Stripe<T> s:S)
            if(s.y_interval.bottom == h.coord)
                s_ = s;
    }
    set<LineSegment<T>> J = intervals(h, s_.tree);     //changed set<Interval> to vector<Interval>
    return J;
}

tplate set<LineSegment<T>> contour(vector<Edge<T>> H, set<Stripe<T>> S)
{
    set<LineSegment<T>> cont;
    for(Edge<T> h : H)
        cont = cont + contour_pieces(h, S);
    return cont;
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

// tplate
//     set<Interval<T>>
//     intervals(set<T> Coord)
// {
// }

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
    // cout << "Enter Copy\n";
    set<Stripe<T>> S2, S_;
    auto i_x = x_int;
    // set<Interval<T>> part = partition(P);
    for (auto i_y : partition(P))
        S2.insert({i_x, i_y, 0});
    for(Stripe<T> s2 : S2)
    {
        s2.tree = NULL;
        for(Stripe<T> s : S)
            if(s.y_interval.bottom <= s2.y_interval.bottom 
            and s.y_interval.top >= s2.y_interval.top)
                s2.tree = s.tree;
        S_.insert(s2);
        // inorder(s2.tree);
        // cout << "\n";
    }
    return S_;
}

tplate 
void Blacken(set<Stripe<T>> &S, set<Interval<T>> J)
{
    // cout << "Enter Blacken\n";
    // for(auto i : J)
    //     cout << i.bottom << "," << i.top << " ";
    // cout << "\n";
    set<Stripe<T>> S_;
    for(Stripe<T> s : S)
    {
        for(Interval<T> i : J)
            if(s.y_interval.bottom >= i.bottom 
            and s.y_interval.top <= i.top)
                if(s.x_interval.bottom != -inf<long double> and s.x_interval.top != inf<long double>)
                {
                    // cout << s.y_interval.bottom << "," << s.y_interval.top << " " << i.bottom << "," << i.top << " ";
                    // inorder(s.tree);
                    // cout << "\n";
                    s.tree = NULL;
                }
        S_.insert(s);
    }
    S.clear();
    S.insert(S_.begin(), S_.end());
}

tplate 
set<Stripe<T>> Concat(set<Stripe<T>> S1, set<Stripe<T>> S2, 
            set<T> P, Interval<T> x_int)
{
    // cout << "Enter Concat\n";
    set<Stripe<T>> S;
    auto i_x = x_int;
    set<Interval<T>> part = partition(P);
    for (auto i_y : part)
        S.insert({i_x, i_y, 0});

    set<Stripe<T>> S_;
    Stripe<T> s1_, s2_;
    for(Stripe<T> s : S)
    {
        s1_.tree = NULL;
        s2_.tree = NULL;
        for(Stripe<T> s1 : S1)
            if(s1.y_interval == s.y_interval)
                s1_ = s1;
        for(Stripe<T> s2 : S2)
            if(s2.y_interval == s.y_interval)
                s2_ = s2;
        if(s1_.tree and s2_.tree)
            s.tree = new ctree<T>(s1_.x_interval.top, "undef", s1_.tree, s2_.tree);
        else if(s1_.tree and !(s2_.tree))
            s.tree = s1_.tree;
        else if(!(s1_.tree) and s2_.tree)
            s.tree = s2_.tree;
        else if(!(s1_.tree) and !(s2_.tree))
            s.tree = NULL;

        // inorder(s.tree);
        // cout << "\n";

        S_.insert(s);
    }
            //         for(Stripe<T> s : S_)
            // deb(s.y_interval.bottom),deb(s.x_measure);

    return S_;
}

tplate
set<Stripe<T>> STRIPES(vector<Edge<T>> &V, Interval<T> &x_ext,
            set<Interval<T>> &L, set<Interval<T>> &R, set<T> &P)
{
    // cout << "Enter STRIPES\n";
    // cout << x_ext.bottom << ", " << x_ext.top << "\n";
    set<Stripe<T>> S, S_;
    if (V.size() == 1)
    {
        Edge<T> v = *(V.begin());
     
        // cout << x_ext.bottom << ", " << x_ext.top << ", " << v.coord << "\n";
     
        P = {{-inf<T>, v.interval.bottom, v.interval.top, inf<T>}};

        auto i_x = x_ext;
        
        // set<Interval<T>> part = partition(P);
        for (auto i_y : partition(P))
            S.insert({i_x, i_y, 0});

        if (v.side == "left")
            L.insert(v.interval);
        else
            R.insert(v.interval);

        for(Stripe<T> s : S)
        {
            if(s.y_interval == v.interval)
                if(v.side == "left")
                    s.tree = new ctree<T>(v.coord, "left", NULL, NULL);
                else
                    s.tree = new ctree<T>(v.coord, "right", NULL, NULL);
            S_.insert(s);
        }

        return S_;
    }
    else
    {
        // Divide
        vector<Edge<T>> V1(V.begin(), V.begin() + V.size()/2);
        vector<Edge<T>> V2(V.begin() + V.size()/2, V.end());
        T x_m = (*(V2.begin())).coord;

        // for(Edge<T> v : V)
        //     cout << v.coord;
        // cout << "\n";

        // Conquer
        Interval<T> x_ext1(x_ext.bottom, x_m);
        set<Interval<T>> L1, R1;
        set<T> P1;
        set<Stripe<T>> S1 = STRIPES(V1, x_ext1, L1, R1, P1);
        
        Interval<T> x_ext2(x_m, x_ext.top);
        set<Interval<T>> L2, R2;
        set<T> P2;
        set<Stripe<T>> S2 = STRIPES(V2, x_ext2, L2, R2, P2);

        // Merge
        auto LR = L1 ^ R2;
        L = (L1 - LR) + L2;
        R = R1 + (R2 - LR);
        P = P1 + P2;

        set<Stripe<T>> S_left = Copy(S1, P, x_ext1);
        set<Stripe<T>> S_right = Copy(S2, P, x_ext2);

        Blacken(S_left, R2-LR);
        Blacken(S_right, L1-LR);

        S = Concat(S_left, S_right, P, x_ext);
        // for(Stripe<T> s : S)
        // {
        //     // cout << s.y_interval.bottom << "," << s.y_interval.top << "\n";
        //     inorder(s.tree);
        //     cout << "\n";
        // }
        // cout << "\n";
    }
    return S;
}

tplate
set<Stripe<T>> RECTANGLE_DAC(set<Rectangle<T>> RECT)
{
    // cout << "Enter DAC\n";
    vector<Edge<T>> VRX;
    for (Rectangle<T> R : RECT)
    {
        Edge<T> leftVerticalEdge(R.y_interval, R.x_left, "left");
        Edge<T> rightVerticalEdge(R.y_interval, R.x_right, "right");
        VRX.push_back(leftVerticalEdge);
        VRX.push_back(rightVerticalEdge);
    }
    sort(VRX.begin(), VRX.end());
    Interval<T> x_ext(-inf<T>, inf<T>);
    set<Interval<T>> L, R;
    set<T> P;
    return STRIPES(VRX, x_ext, L, R, P);
}

int main(int argc, char const *argv[])
{
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    set<Rectangle<long double>> input;
    int n;
    ifstream fin;
    fin.open(argv[1]);
    fin >> n;
    while (n--)
    {
        long double x1, x2, y1, y2;
        fin >> x1 >> x2 >> y1 >> y2;
        Rectangle<long double> r(x1, x2, y1, y2);
        input.insert(r);
        // fout1 << x1 << " " << x2 << " " << y1 << " " << y2 << "\n";
    }
    fin.close();

    // set<Point<long double>> output = unionArea(input);
    // for (auto p : output)
    //     cout << p.x << " - " << p.y << "\n";

    set<Stripe<long double>> S = RECTANGLE_DAC(input);
    long double area = 0;
    ofstream fout2;
    fout2.open("stripes.txt");
    int count = 0;
    for(Stripe<long double> s : S)
    {
        inorder(s.tree);
        cout << "\n";
        fout2 << s.x_interval.bottom << " " << s.x_interval.top 
        << " " << s.y_interval.bottom << " " << s.y_interval.top 
        << " " << 0 << "\n";
    }
    fout2.close();
    
    vector<Edge<long double>> H;
    for (Rectangle<long double> R : input)
    {
        Edge<long double> bottomHorizontalEdge(R.x_interval, R.y_bottom, "bottom");
        Edge<long double> topHorizontalEdge(R.x_interval, R.y_top, "top");
        H.push_back(bottomHorizontalEdge);
        H.push_back(topHorizontalEdge);
    }

    set<LineSegment<long double>> contour_horizontal = contour(H, S);

    ofstream fout3;
    fout3.open("contour.txt");
    
    for(LineSegment<long double> i : contour_horizontal)
        fout3 << i.interval.bottom << " " << i.interval.top << " " << i.coord << " " << i.coord << "\n";
    
    for(Stripe<long double> s : S)
    {
        vector<Edge<long double>> edges;
        getNodes(s.tree, edges, -inf<long double>, inf<long double>);
        for(Edge<long double> e : edges)
            fout3 << e.coord << " " << e.coord << " " << s.y_interval.bottom << " " << s.y_interval.top << "\n";
    }

    fout3.close();

    system("python contour_visual.py");
    
    return 0;
}