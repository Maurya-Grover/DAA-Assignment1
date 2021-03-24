/// \file measure.cpp
/// @brief Computation of the measure for a set of iso rectangles using divide-and-conquer

#include <bits/stdc++.h>
#define tplate template <typename T = long double>
using namespace std;

/// Constant to represent infinity
tplate const T inf = numeric_limits<T>::infinity();

/// \class Point
/// @brief A simple class to represent a point in a two dimensional space
tplate class Point
{
public:
    /// x-coordinate of the point represented by the object
    T x;
    /// y-coordinate of the point represented by the object
    T y;
    /// @brief This constructor is used to initialise the object with given x and y coordinates
    /// @param x x-coordinate
    /// @param y y-coordinate
    /// @return The object initialised with the given coordinates
    Point(T x, T y)
    {
        this->x = x;
        this->y = y;
    }
    /// @brief Defines the less-than operator for set insertion and comparision
    /// @param other object with which comparision needs to be done
    /// @return true if object less than other, else false
    bool operator<(const Point &other) const
    {
        return this->x < other.x or (this->x == other.x and this->y < other.y);
    }
};

/// \class Interval
/// @brief A class to represent an interval between two lines in the 2D plane
tplate class Interval
{
public:
    /// upper limit of the interval
    T top;
    /// lower limit of the interval
    T bottom;
    /// @brief Default constructor for creating an empty Interval type object
    /// @return An empty Interval type object
    Interval() {}
    /// @brief Constructor for creating an Interval type object
    /// @param bottom Value for bottom
    /// @param top Value for top
    /// @return An empty Interval type object
    Interval(T bottom, T top)
    {
        this->bottom = bottom;
        this->top = top;
    }
    /// @brief Defines the less-than operator for set insertion and comparision
    /// @param other object with which comparision needs to be done
    /// @return true if object less than other, else false
    bool operator<(const Interval &other) const
    {
        return this->bottom < other.bottom or (this->bottom == other.bottom and this->top < other.top);
    }
    /// @brief Defines the equals-to operator for comparision
    /// @param other object with which comparision needs to be done
    /// @return true if object is equal to the other, else false
    bool operator==(const Interval &other) const
    {
        return this->bottom == other.bottom and this->top == other.top;
    }
};

/// \class LineSegment
/// @brief A class to represent a Line Segment between the given interval of two points with coord as the offset from the axes
tplate class LineSegment
{
public:
    /// interval between the two end points of the Line Segment
    Interval<T> interval;
    /// coordinate that remains constant between the endpoints of the line segment
    T coord;
    /// @brief Constructor for creating an LineSegment type object
    /// @param interval Value for bottom
    /// @param coord Value for coord
    /// @return An empty Interval type object
    LineSegment(Interval<T> interval, T coord)
    {
        this->interval = interval;
        this->coord = coord;
    }
    /// @brief Defines the less-than operator for set insertion and comparision
    /// @param other object with which comparision needs to be done
    /// @return true if object less than other, else false
    bool operator<(const LineSegment &other) const
    {
        return this->coord < other.coord or (this->coord == other.coord and this->interval < other.interval);
    }
};

/// \class Rectangle
/// @brief A class to represent a rectangle in a two dimensional space
tplate class Rectangle
{
public:
    /// x-coordinate of left side
    T x_left;
    /// x-coordinate of right side
    T x_right;
    /// y-coordinate of left side
    T y_bottom;
    /// y-coordinate of right side
    T y_top;
    /// Interval on x-axis
    Interval<T> x_interval;
    /// Interval on y-axis
    Interval<T> y_interval;
    /// @brief This is the default constructor for creating an empty Interval type object
    /// @return An empty Interval type object
    Rectangle() {}
    /// @brief This constructor is used to initialise the object with given x and y coordinates
    /// @param x1 Value for x_left
    /// @param x2 Value for x_right
    /// @param y1 Value for y_bottom
    /// @param y2 Value for y_top
    /// @return The object initialised with the given coordinates
    Rectangle(T x1, T x2, T y1, T y2)
    {
        x_left = min(x1, x2);
        x_right = max(x1, x2);
        y_bottom = min(y1, y2);
        y_top = max(y1, y2);
        x_interval = Interval<T>(x_left, x_right);
        y_interval = Interval<T>(y_bottom, y_top);
    }
    /// @brief Defines the less-than operator for set insertion and comparision
    /// @param other object with which comparision needs to be done
    /// @return true if object less than other, else false
    bool operator<(const Rectangle &other) const
    {
        return this->x_left < other.x_left or (this->x_left == other.x_left and this->x_right < other.x_right) or (this->x_left == other.x_left and this->x_right == other.x_right and this->y_bottom < other.y_bottom) or (this->x_left == other.x_left and this->x_right == other.x_right and this->y_bottom == other.y_bottom and this->y_top < other.y_top);
    }
};

/// \class Edge
/// @brief A class to represent an edge in two dimensional space
tplate class Edge
{
public:
    /// Interval of the edge
    Interval<T> interval;
    /// coordinate of the edge that remains constant between the Interval of the edge
    T coord;
    /// Represents what side of the figure the edge is - {'left', 'right', 'top', 'bottom'}
    string side;
    /// @brief Constructor for creating an Edge type object
    /// @param interval Value for interval
    /// @param coord Value for coord
    /// @param side Value for side
    /// @return An empty Interval type object
    Edge(Interval<T> interval, T coord, string side)
    {
        this->interval = interval;
        this->coord = coord;
        this->side = side;
    }
    /// @brief Defines the less-than operator for set insertion and comparision
    /// @param other object with which comparision needs to be done
    /// @return true if object less than other, else false
    bool operator<(const Edge &other) const
    {
        return this->coord < other.coord or (this->coord == other.coord and this->side > other.side) or (this->coord == other.coord and this->side == other.side and this->interval < other.interval);
    }
};



/// \class Stripe
/// @brief A class to represent a horizontal stripe in two dimensions
tplate class Stripe
{
public:
    /// Interval of the stripe on the x-axis
    Interval<T> x_interval;
    /// Interval of the stripe on the y-axis
    Interval<T> y_interval;
    /// Total length of intervals contained in stripes on x-axis 
    T x_measure;
    /// @brief Default constructor to create a Stripe object
    /// @return Empty object of class Stripe
    Stripe() {}
    /// @brief Constructor to create a Stripe object with given initialisation values
    /// @param x_interval Value for x_interval
    /// @param y_interval Value for y_interval
    /// @param x_measure Value for x_measure
    /// @return Object of class Stripe initialised with given values
    Stripe(Interval<T> x_interval, Interval<T> y_interval, T x_measure)
    {
        this->x_interval = x_interval;
        this->y_interval = y_interval;
        this->x_measure = x_measure;
    }
    /// @brief Defines the less-than operator for set insertion and comparision
    /// @param other object with which comparision needs to be done
    /// @return true if object less than other, else false
    bool operator<(const Stripe &other) const
    {
        return this->x_interval < other.x_interval or (this->x_interval == other.x_interval and this->y_interval < other.y_interval);
    }
};


/// @brief Defines the minus operator for computing set difference of set A and set B
/// @param a the set from which to elements are to be removed
/// @param b the set of items to be removed
/// @return a set with items of set b removed
template <class T>
set<T> operator-(set<T> a, set<T> b)
{
    set<T> result;
    std::set_difference(
        a.begin(), a.end(),
        b.begin(), b.end(),
        std::inserter(result, result.end()));
    return result;
}

/// @brief Defines the plus operator for computing union of set A and set B
/// @param a set a
/// @param b set b
/// @return a set with the union of set a and set b
template <class T>
set<T> operator+(set<T> a, set<T> b)
{
    set<T> result;
    std::set_union(
        a.begin(), a.end(),
        b.begin(), b.end(),
        std::inserter(result, result.end()));
    return result;
}

/// @brief Defines the intersection operator for computing set intersection of two sets
/// @param a set a
/// @param b set b
/// @return intersection of set a and set b
template <class T>
set<T> operator^(set<T> a, set<T> b)
{
    set<T> result;
    std::set_intersection(
        a.begin(), a.end(),
        b.begin(), b.end(),
        std::inserter(result, result.end()));
    return result;
}


/// @brief Finds intervals created by a set of coordinates
/// @param Y set of y-coordinates
/// @return A set of intervals
tplate set<Interval<T>> partition(set<T> Y)
{
    set<Interval<T>> result;
    vector<T> Y_vec(Y.begin(), Y.end());
    for (int i = 1; i < Y_vec.size(); i++)
        result.insert(Interval<T>(Y_vec[i - 1], Y_vec[i]));
    return result;
}

/// @brief Copies a set of stripes into the stripes created by partitions
/// @param S Set of stripes
/// @param P Set of coordinates
/// @param x_int Interval of stripes on x-axis
/// @return A set of stripes
tplate set<Stripe<T>> Copy(set<Stripe<T>> S, set<T> P, Interval<T> x_int)
{
    set<Stripe<T>> S2, S_;
    auto i_x = x_int;
    for (auto i_y : partition(P))
        S2.insert({i_x, i_y, 0});
    for (Stripe<T> s2 : S2)
    {
        for (Stripe<T> s : S)
            if (s.y_interval.bottom <= s2.y_interval.bottom and s.y_interval.top >= s2.y_interval.top)
                s2.x_measure = s.x_measure;
        S_.insert(s2);
    }
    return S_;
}

/// @brief Removes the edges that are covered by other rectangles for a particular stripe
/// @param S Set of stripes
/// @param J Set of Intervals
tplate void Blacken(set<Stripe<T>> &S, set<Interval<T>> J)
{
    set<Stripe<T>> S_;
    for (Stripe<T> s : S)
    {
        for (Interval<T> i : J)
            if (s.y_interval.bottom >= i.bottom and s.y_interval.top <= i.top)
                if (s.x_interval.bottom != -inf<long double> and s.x_interval.top != inf<long double>)
                {
                    s.x_measure = s.x_interval.top - s.x_interval.bottom;

                }
        S_.insert(s);
    }
    S.clear();
    S.insert(S_.begin(), S_.end());
}

/// @brief Combine the results from two sets of stripes
/// @param S1 First set of stripes
/// @param S2 Second set of stripes
/// @param P Set of coordinates
/// @param x_int Interval on x-axis for both sets of stripes
/// @return A set of stripes after concatenation
tplate set<Stripe<T>> Concat(set<Stripe<T>> S1, set<Stripe<T>> S2, set<T> P, Interval<T> x_int)
{
    set<Stripe<T>> S;
    auto i_x = x_int;
    set<Interval<T>> part = partition(P);
    for (auto i_y : part)
        S.insert({i_x, i_y, 0});

    set<Stripe<T>> S_;
    Stripe<T> s1_, s2_;
    for (Stripe<T> s : S)
    {
        s1_.x_measure = s2_.x_measure = 0;
        for (Stripe<T> s1 : S1)
            if (s1.y_interval == s.y_interval)
                s1_ = s1;
        for (Stripe<T> s2 : S2)
            if (s2.y_interval == s.y_interval)
                s2_ = s2;
        s.x_measure = s1_.x_measure + s2_.x_measure;
        S_.insert(s);

        // if(s.x_measure == 2)
        //     cout << "@@@@@@@@@" << s1_.x_measure << "+" << s2_.x_measure << "\n";
    }
    //         for(Stripe<T> s : S_)
    // deb(s.y_interval.bottom),deb(s.x_measure);

    return S_;
}

/// @brief Creates the stripes required for finding the contour
/// @param V Set of edges
/// @param x_ext Interval on x-axis for set of stripes
/// @param L Intervals consisting of 'left' edges
/// @param R Intervals consisting of 'right' edges
/// @param P Set of coordinates
/// @return A set of stripes
tplate set<Stripe<T>> STRIPES(vector<Edge<T>> &V, Interval<T> &x_ext, set<Interval<T>> &L, set<Interval<T>> &R, set<T> &P)
{
    set<Stripe<T>> S, S_;
    if (V.size() == 1)
    {
        Edge<T> v = *(V.begin());
        P = {{-inf<T>, v.interval.bottom, v.interval.top, inf<T>}};
        auto i_x = x_ext;

        for (auto i_y : partition(P))
            S.insert({i_x, i_y, 0});

        if (v.side == "left")
            L.insert(v.interval);
        else
            R.insert(v.interval);

        for (Stripe<T> s : S)
        {
            if (s.y_interval == v.interval)
                if (v.side == "left")
                    s.x_measure = x_ext.top - v.coord;
                else
                    s.x_measure = v.coord - x_ext.bottom;
            S_.insert(s);
        }

        // cout << "### ";
        // for (Edge<T> v : V)
        //     cout << v.coord << v.side[0] << " ";
        // cout << ": ";
        // for (Stripe<T> s : S_)
        //     cout << "(" << s.y_interval.bottom << "," << s.y_interval.top << "," << s.x_measure << ") ";
        // cout << "\n";
        // cout << x_ext.bottom << ","
        //      << "-"
        //      << "," << x_ext.top << "\n";
        // cout << "L: ";
        // for (Interval<T> i : L)
        //     cout << i.bottom << "," << i.top << " ";
        // cout << "R: ";
        // for (Interval<T> i : R)
        //     cout << i.bottom << "," << i.top << " ";
        // cout << "\n\n\n";

        return S_;
    }
    else
    {
        // Divide
        auto ptr = V.begin() + V.size() / 2;
        while(ptr-1 != V.begin() and (*ptr).coord == (*(ptr-1)).coord and (*ptr).side == "left")
            ptr--;
        while(ptr+1 != V.end() and (*ptr).coord == (*(ptr+1)).coord and (*ptr).side == "right")
            ptr++;
        vector<Edge<T>> V1(V.begin(), ptr);
        vector<Edge<T>> V2(ptr, V.end());
        T x_m = (*ptr).coord;

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

        Blacken(S_left, R2 - LR);
        Blacken(S_right, L1 - LR);

        S = Concat(S_left, S_right, P, x_ext);


        // DEBUGGING
        // for (Edge<T> v : V)
        //     cout << v.coord << v.side[0] << " ";
        // cout << ": ";
        // for (Stripe<T> s : S)
        //     cout << "(" << s.y_interval.bottom << "," << s.y_interval.top << "," << s.x_measure << ") ";
        // cout << "\n";
        // cout << x_ext.bottom << "," << x_m << "," << x_ext.top << "\n";
        // cout << "L1: ";
        // for (Interval<T> i : L1)
        //     cout << i.bottom << "," << i.top << " ";
        // cout << "R1: ";
        // for (Interval<T> i : R1)
        //     cout << i.bottom << "," << i.top << " ";
        // cout << "L2: ";
        // for (Interval<T> i : L2)
        //     cout << i.bottom << "," << i.top << " ";
        // cout << "R2: ";
        // for (Interval<T> i : R2)
        //     cout << i.bottom << "," << i.top << " ";
        // cout << "\n\n\n";
    }
    return S;
}

/// @brief A helper function that converts the Rectangle into edges and calls the STRIPES function on those intervals
/// @param RECT A set of Rectangles
/// @return A set of stripes
tplate set<Stripe<T>> RECTANGLE_DAC(set<Rectangle<T>> RECT)
{
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
    // Interval<T> x_ext((*(VRX.begin())).coord, (*(VRX.end()-1)).coord);
    // cout << "LOLOLOLOL" << (*(VRX.begin())).coord << "," << (*(VRX.end()-1)).coord << "\n";
    set<Interval<T>> L, R;
    set<T> P;
    
    return STRIPES(VRX, x_ext, L, R, P);
}

int main(int argc, char const *argv[])
{
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
    }
    fin.close();

    set<Stripe<long double>> S = RECTANGLE_DAC(input);
    long double area = 0;
    ofstream fout2;
    fout2.open("stripes.txt");
    for (Stripe<long double> s : S)
    {
        if (s.y_interval.bottom != -inf<long double> and s.y_interval.top != inf<long double>)
            area += s.x_measure * (s.y_interval.top - s.y_interval.bottom);
        // cout << s.x_measure << "\n";
        fout2 << s.x_interval.bottom << " " << s.x_interval.top
              << " " << s.y_interval.bottom << " " << s.y_interval.top
              << " " << s.x_measure << "\n";
    }
    fout2.close();

    cout << "Area = " << area;

    char cmd[] = "python measure_visual.py ";
    strcat(cmd, argv[1]);

    system(cmd);

    return 0;
}