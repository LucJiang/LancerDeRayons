#include <vector>
#include <cmath>
#include "constante.hpp"
#include <SFML/Graphics.hpp>

#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

class Point
{
private:
    float x, y, z;

public:
    Point(float u, float v, float w) {x=u; y=v; z=w;}

    float getx() const {return x;}
    float gety() const {return y;}
    float getz() const {return z;}

    void setx(float a) {x=a;}
    void sety(float a) {y=a;}
    void setz(float a) {z=a;}

    Point operator + (const Point& aPoint) const
	{
        float rx = x + aPoint.getx();
        float ry = y + aPoint.gety();
        float rz = z + aPoint.getz();
        Point res(rx,ry,rz);
        return res;
	}

	Point operator - (const Point& aPoint) const
	{
        float rx = x - aPoint.getx();
        float ry = y - aPoint.gety();
        float rz = z - aPoint.getz();
        Point res(rx,ry,rz);
        return res;
	}

	Point operator * (const float& t) const
	{
	    Point res(x*t, y*t, z*t);
	    return res;
	}

	float operator * (const Point& aPoint) const
	{
	    float res = x*aPoint.getx() + y*aPoint.gety() + z*aPoint.getz();
	    return res;
	}

	float norm() const
	{
	    float res = sqrt(x*x + y*y + z*z);
	    return res;
	}

	void normalized()
	{
	    float norm = this->norm();
	    if (norm != 0)
            x /= norm; y /= norm; z /= norm;
	}

};

class Camera
{
private:
    Point loc;
    Point orientation;
    float dmin, dmax;

public:
    Camera(Point Loc, Point Orientation, float Dmin, float Dmax) : loc(Loc), orientation(Orientation), dmin(Dmin), dmax(Dmax) {}

    Point getloc() const {return loc;}
    Point getori() const {return orientation;}
    float getdmin() const {return dmin;}
    float getdmax() const {return dmax;}

};

class Object
{

};

class Sphere : public Object
{
private:
    Point loc;
    float radius;
    sf::Uint8 R,G,B;

public:
    Sphere(Point Loc, float R, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b) : loc(Loc), radius(R), R(r), G(g), B(b) {}

    Point getloc() const {return loc;}
    float getradius() const {return radius;}

    sf::Uint8 getR() const {return R;}
    sf::Uint8 getG() const {return G;}
    sf::Uint8 getB() const {return B;}

};

class Plan : public Object
{
private:
    Point loc;
    Point normale;

public:
    Plan(Point Loc, Point Normale) : loc(Loc), normale(Normale) {}

    Point getloc() const {return loc;}
    Point getnormale() const {return normale;}

};

class Light
{
private:
    Point loc;

public:
    Light(Point Loc) : loc(Loc) {}

    Point getloc() const {return loc;}
};

class World
{
private:
    Camera camera;
    std::vector<Sphere> objects;
    std::vector<Light> lights;
    sf::Uint8* pixels;

public:
    World(Camera Cam, std::vector<Sphere> obj, std::vector<Light> lit, sf::Uint8* pix) :
         camera(Cam), objects(obj), lights(lit), pixels(pix) {}

    sf::Uint8* getpixels() {return pixels;}
    void raytracing();
    bool ray(Point& position, Point& direction, float* tfinal, int* objseen);

};
#endif // OBJECT_H_INCLUDED
