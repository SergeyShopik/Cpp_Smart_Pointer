#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
using std::string;
using std::vector;
class Point2D
{
public:
    Point2D(double _x = 0, double _y = 0);
    ~Point2D();
    virtual void  print(std::ostream&);
    virtual void  read(std::istream&);
    const Point2D operator+(const Point2D&) const;
    double get_x()const { return x; }
    double get_y()const { return y; }
private:
    double x, y;
};

Point2D::Point2D(double _x, double _y) :x(_x), y(_y)
{
    std::cout << "Constructor Point2D\n";
}

Point2D::~Point2D()
{
    std::cout << "Distructor Point2D\n";
}
void Point2D::print(std::ostream& out)
{
    out << x << "," << y;
}
void Point2D::read(std::istream& in)
{
    in >> x >> y;
}

const Point2D Point2D:: operator+(const Point2D& p) const
{
    Point2D sum(x + p.x, y + p.y);
    return sum;
}
class Point3D : public Point2D
{
public:
    Point3D(double _x = 0, double _y = 0, double _z = 0);
    ~Point3D();
    Point3D& operator=(const Point2D&);
    void  print(std::ostream&) override;
    void  read(std::istream&) override;
    const Point3D operator+(const Point3D&) const;
private:
    double z;
};
Point3D::Point3D(double _x, double _y, double _z) :Point2D(_x, _y), z(_z)
{
    std::cout << " Constructor Point3D\n";
}
Point3D::~Point3D()
{
    std::cout << "Distructor Point3D\n";
}
Point3D& Point3D:: operator=(const Point2D& p2D)
{
    this->Point2D::operator=(p2D);
    return *this;
}
void Point3D::print(std::ostream& out)
{
    Point2D::print(out);
    out << "," << z;
}
void Point3D::read(std::istream& in)
{
    Point2D::read(in);
    in >> z;
}
const Point3D Point3D:: operator+(const Point3D& p) const
{
    Point3D sum(get_x() + p.get_x(), get_y() + p.get_y(), z + p.z);
    return sum;
}
std::shared_ptr<Point2D> get_ptr(string str)
{
    size_t count = 0;
    int pos = 0;
    while (pos != string::npos)
    {
        pos = str.find(" ", pos);
        if (pos == string::npos) break;
        count++;
        pos++;
    }
    if (count == 1) return std::make_shared<Point2D>();
    else return std::make_shared<Point3D>();
}
int main()
{
    {
        vector<std::shared_ptr<Point2D>> points;

        std::ifstream in("Text.txt");

        while (!in.eof())
        {
            string str;
            getline(in, str);
            points.push_back(get_ptr(str));
            std::istringstream line(str);
            points.back()->read(line);
            points.back()->print(std::cout);
            std::cout << "\n";
        }
    }

    system("pause");
    return 0;
}