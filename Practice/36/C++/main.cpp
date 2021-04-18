#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

#include <cmath>

const auto PI = 3.141592653589793;

enum coord_system{
    Cartesian,
    Polar
};

class Point{
private:
    double x, y;
public:
    Point (double x, double y, coord_system system){

    }

    bool operator==(const Point& other) const {
       return abs(x - other.x) < 1e-10
         && abs(y - other.y) < 1e-10;
      }

    bool operator!=(const Point& other) const {
        return !(*this == other);
      }

    double get_x(){
        return this->x;
    }
    double get_y(){
        return this->y;
    }
    double get_r(){
        return sqrt((pow(this->x,2) + pow(this->y, 2)));
    }
    double get_phi(){
        return atan2(this->y, this->x);
    }
    void set_x(double a){
        this->x = a;
        return;
    }
    void set_y(double a){
        this->y = a;
    }
    void set_r(double r){
        double f = get_phi();
        this->x = r * cos(f);
        this->y = r * sin(f);
    }
    void set_phi(double phi){
        double r = get_r();
        this->x = cos(phi) * r;
        this->y = sin(phi) * r;
    }

    friend std::ostream& operator <<(std::ostream& out, Point& p){
        return out << '(' << p.get_x() << ',' << p.get_y() << ')';
    }

    friend std::istream& operator >>(std::istream& in, Point& p){
        double a;
        in.ignore(20, '(');
        in >> a;
        p.set_x(a);
        in.ignore(20, ',');
        in >> a;
        p.set_y(a);
        in.ignore(20, ')');
        return in;
    }
};





int main() {
    std::vector<Point> original;
    std::ifstream fin("data.txt");
    if (!fin.is_open()) {
        std::cout << "Can't open file" << std::endl;
        return 1;
    } else {
        while (!fin.eof()) {
            Point p;
            fin >> p;
            fin.ignore(2); // Точки разделены двумя символами ", "
            original.push_back(p);
        }
        fin.close();
    }

    std::vector<Point> simulacrum(original);
    for (auto& p : simulacrum) {
        std::cout << p;
        p.set_x(p.get_x() + 10);
        p.set_phi(p.get_phi() + 180*PI/180);
        p.set_y(-p.get_y());
        p.set_x(-p.get_x() - 10);
        std::cout << p << std::endl;
    }

    if (std::equal(original.begin(), original.end(), simulacrum.begin()))
        std::cout << "\nIt works!\n";
    else
        std::cout << "\nIt not works!\n";
}
