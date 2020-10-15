#define CATCH_CONFIG_MAIN
#include "catch2\catch.hpp"
#include <iostream>
#include <cmath>
#include "../src/geometry.hpp"

using namespace std;
using namespace geometry;

TEST_CASE("Example 1", "Example 1") {
    INFO( "TEST_CASE:sq_ae.area() == sq_ae.area()");
    
    Point a(1, -1),  e(1, 6);
    
    REQUIRE(a != e);
    REQUIRE(a == a);
    REQUIRE(a == e);
}

/*
int main() {
    const double pi = 4*atan(1);

    
    Point a(1, -1),  e(1, 6);
    Rectangle rec_ae1(e, a, 1);
    Square sq_ae(a, e);
    Square sq_ea(e, a);
    cout << rec_ae1 << endl;
    cout << "(rec_ae1 == sq_ae): " << (rec_ae1 == sq_ae) << endl;
    Polygon poly1(rec_ae1.getVertices());
    cout << "(rec_ae1 == poly1): " << (rec_ae1 == poly1) << endl;
    cout << "(sq_ae == rec_ae1): " << (sq_ae == rec_ae1) << endl;
    cout << sq_ae << endl;
    cout << sq_ea << endl;
    poly1.isCongruentTo(rec_ae1);
    rec_ae1.isCongruentTo(poly1);
    rec_ae1.isSimilarTo(poly1);

 

//P((1,-1),(4,-1),(-2,2),(-5,2)) 9 | 19.416
//P((-2,2),(-2,5),(1,-1),(1,-4)) 9 | 19.416
//!found -> False

    Polygon p1(Point(-2, 2), Point(1, 2), Point(6, 1), Point(3, -1), Point(1, -1), Point(-1, -2)); // | S = 18.5 | P = 20.0637 | is_convex = 0
    Polygon p2(Point(-2, 2), Point(1, 2), Point(6, 1), Point(3, -1), Point(1, -1), Point(-1, -2));
    
    // cout << p1 << endl;
    p2.rotate(Point(0, 0), 50);

    //cout << p2 << endl;
    p1.isCongruentTo(p2);
    p1.isSimilarTo(p2);

    p2.scale(Point(0, 0), 3);
    //cout << p2 << endl;
    p1.isCongruentTo(p2);
    p1.isSimilarTo(p2);

    p2.scale((-2.00,2.00), 0.3333333333);
    //cout << p2 << endl;
    p1.isCongruentTo(p2);
    p1.isSimilarTo(p2);

    //cout << p2 << endl;
    p2.reflex(Line(3, 5));
    p1.isCongruentTo(p2);

    

    Rectangle rect1(Point(-2,2), Point(1,-1), 1);
    // Rectangle rect2(Point(1,-1), Point(-2,2), 1);
    //cout << rect1 << endl;
    // cout << rect2 << endl;
    //cout << "rect1 contains " << Point(0) << ": \n" << rect1.containsPoint(0);
    //cout << "rect1 contains " << Point(10) << ": \n" << rect1.containsPoint(10);
    
    //Triangle t1(Point(-2,2), Point(1,2), Point(-1,-2));
    //cout << t1.containsPoint(Point(0, 1)) << endl;
    
    Ellipse el1(Point(3, -1), Point(6, 1), 5);
    el1.eccentricity();

    Ellipse el2(Point(6, 1), Point(3, -1), 5);
    el2.eccentricity();

    Ellipse el3(Point(-14, 0), Point(-6, 0), 10);
    el3.eccentricity();

// E:scale (5,5)0.5E((3,-1),(6,1),5) e=0.563856, a=3.19722, b=2.6405, c=1.80278, p=2.18072
    el3.scale((5,5), 0.5);
    cout << el3 << endl;
    
    Point a(1, 1), b(1, 5);

    Line line1 = Line(a, b);

    cout << line1 << endl;
    cout << line1.perpendicular(Point(1, 2));   
    

    Ellipse e1(Point(-5, 0), Point(5, 0), 14);
    cout << e1 << endl;
    e1.directrices();

    e1.rotate(0, 45);
    e1.directrices();

    Triangle t1(Point(-1,-2), Point(1,2), Point(-2,2));
    cout << t1.inscribedCircle() << endl;
    cout << t1.circumscribedCircle() << endl;
    cout << t1.EulerLine() << endl;
    cout << t1.ninePointsCircle() << endl;

    //T:inscribedCircle() Triangle((-1,-2), (1,2), (-2,2)) | S = 6 | P = 11.5952
//T:circumscribedCircle() Triangle((-1,-2), (1,2), (-2,2)) | S = 6 | P = 11.5952
//Test 17.0 failed. (https://en.wikipedia.org/wiki/Euler's_theorem_in_geometry)


    
    Point a(3, 1);
    Point b(2, 4);
    Point c(3, 7);
    Point d(7, 4);
    Point e(11, 1);
    Point f(7, 0);

    
    Triangle t1(Point(0, 0), Point(0, 3), Point(4, 0));
    Triangle t2(Point(3, 1), Point(3, 7), Point(11, 1));
    Triangle t3(Point(1, -11), Point(7, -3), Point(1, -3));

    cout << Point(3, 7) << -Point(3,7) << endl;

    Polygon poly1(Point(3, 1), Point(2, 4), Point(3, 7), Point(7, 4), Point(11, 1));
    Polygon poly2(a, b, c, d, e);

    cout << t1 << endl;
    cout << t2 << endl;

    ((Polygon &)t2).rotate(Point(0, 0), pi / 2);

    cout << t2 << endl;

    ((Polygon &)t2).rotate(Point(0, 0), pi / 3);
    cout << t2 << endl;

    cout << poly1 << endl;
    cout << poly2 << endl;

    cout << "poly1 == poly2 is ";
    cout << (poly1 == poly2) << endl;

    poly1.reflex(Point(0));
    cout << poly1 << endl;
    cout << "poly1 == poly2 is " << (poly1 == poly2) << endl;
    cout << "poly1.isCongruentTo(poly2) is " << poly1.isCongruentTo(poly2) << endl;

    cout << "poly1 != poly2 is " << (poly1 != poly2) << endl;
    

    Polygon poly3(Point(0), Point(0, 2), Point(4, 2), Point(4, 0));
    Polygon poly4(poly3);

    poly4.reflex(Point(0));
    cout << endl << poly3 << endl;
    cout << "poly3 == poly4 is " << (poly3 == poly4) << endl;
    cout << "poly3.isCongruentTo(poly4)\n" << poly3.isCongruentTo(poly4) << endl;

    Polygon poly5(Point(0), Point(0, 2), Point(2, 3), Point(4, 2), Point(4, 0));
    Polygon poly6(Point(-4, 0), Point(-4, 2), Point(-2, 3), Point(0, 2), Point(0));

    cout << endl << poly5 << endl;
    cout << "poly5.isCongruentTo(poly6)\n" << poly5.isCongruentTo(poly6) << endl;
    
    Triangle abd(a, b, d);
    Triangle bda(b, d, a);
    Triangle abc(a, b, c);
    

    if (abd.isSimilarTo(abc)) {
        cout << abd << endl;
        cout << abc << endl; 
        cout << "abd is Similar To (abc)" << endl;
    } else {
        cout << abd << endl;
        cout << abc << endl; 
        cout << "abd is NOT Similar To (abc)" << endl;
    }

    if (abd.isSimilarTo(bda)) {
        cout << abd << endl;
        cout << bda << endl;

        cout << "abd is Similar To (bda)" << endl;
    } else {
        cout << abd << endl;
        cout << bda << endl;

        cout << "abd is NOT Similar To (bda)" << endl;
    }

    abd.scale(0, 2);
    if (abd.isSimilarTo(bda)) {
        cout << abd << endl;
        cout << bda << endl;

        cout << "abd is Similar To (bda)" << endl;
    } else {
        cout << abd << endl;
        cout << bda << endl;

        cout << "abd is NOT Similar To (bda)" << endl;
    }

    
    Polygon abcdef(Point(-3.33333, 1.83333), Point(-0.333333, 1.83333), Point(4.66667, 0.833333), Point(1.66667, -1.16667), Point(-0.333333, -1.16667), Point(-2.33333, -2.16667));
    // | S = 18.5 | P = 20.0637 | is_convex = 0
    Polygon abcdeg(Point(4.28453, 2.02855), Point(-0.802676, 1.68165), Point(-3.69757, 0.894522), Point(-1.68311, -2.70297), Point(-0.0155513, -1.21325), Point(1.91438, -0.688502));
    // | S = 18.5 | P = 20.0637 | is_convex = 0

    if (abcdef.isSimilarTo(abcdeg)) {
        cout << abcdef << endl;
        cout << abcdeg << endl;

        cout << "abcdef is Similar To (abcdeg)" << endl;
    } else {
        cout << abcdef << endl;
        cout << abcdeg << endl;

        cout << "abcdef is NOT Similar To (babcdegda)" << endl;
    }



    newAbfced.reflex(0);
    
    if (!abfced.isCongruentTo(newAbfced)) {
        cout << 2 << endl;
    }
    
    vector<Shape *> shapes;

    shapes.push_back(&abd);

    if (!abd.containsPoint(Point(0,1))) {
        cout << 3 << endl;
    }

    Ellipse cf5 = Ellipse(f, c, 5);

    Point orc = abd.orthocenter();

    Circle eulerCircle = abd.ninePointsCircle();
    Line eulerLine = abd.EulerLine();

    bool ok = Line(eulerCircle.center(), abd.centroid()) == eulerLine;
    
    error: ‘Polygon’ is not an accessible base of ‘Triangle’
    error: ‘class Polygon’ has no member named ‘isCongruentTo’


    if (abd.isSimilarTo(abfced)) {

    if (!abfced.isCongruentTo(newAbfced)) {

    shapes.push_back(&abd);

    if (!abd.containsPoint(Point(0,1))) {}

    cf5 = Ellipse(f, c, 5);

    Point orc = abd.orthocenter();

    ok = Line(eulerCircle.center(), abd.centroid()) == eulerLine;

      
      double eccentri() {
          double c = focuses_pair.first.distance(p: center());
          double a = dist / 2;
          return c / a;
      }
    
    return 0;
}
*/