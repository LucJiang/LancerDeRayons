#include "object.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>


float lighthandler(Point obj, Point cam, Point light) //vecteurs
{
    float objnorm = sqrt(obj*obj);
}

bool World::ray(Point& position, Point& direction, float* tfinal, int* objseen)
{
    *tfinal = -1;
    *objseen = -1;

    //On parcourt la liste des sph�res
    for (unsigned int itobj = 0; itobj<objects.size(); ++itobj)
    {
        Sphere* obj = &objects[itobj];
        Point objpos = obj->getloc();
        float radius = obj->getradius();
        float t = -1;

        float tc = (objpos - position)*direction;
        float D = (objpos - position).norm();

        if (D < radius) //Dans la sph�re
        {
            t = sqrt(radius*radius - D*D + tc*tc) + tc;
        } else
        {
            float h = sqrt(D*D - tc*tc);
            if (tc >= 0 && h <= radius)
            {
                t = tc - sqrt(radius*radius - h*h);
            }
        }

        if (*tfinal == -1)
        {
            if (t>0)
            {*tfinal = t; *objseen = itobj;}
        }
        else
        {
            if (0<t && t<*tfinal)
            {*tfinal = t; *objseen = itobj;}
        }
    }
/*
    //On parcourt les plans
    for (unsigned int itobj = 0; itobj<objects.size(); ++itobj)
    {
        Plan* obj = &objects[itobj];
        Point objpos = obj->getloc();
        Point n = obj->getnormale();
        float t = -1;

        t = (objpos - position)*n/(direction*n);

        if (*tfinal == -1)
        {
            if (t>0)
            {*tfinal = t; *objseen = itobj;}
        }
        else
        {
            if (0<t && t<*tfinal)
            {*tfinal = t; *objseen = itobj;}
        }
    }
    */

    if (*tfinal == -1)
        return false;
    else
        return true;
}

void World::raytracing()
{
    //Init
    Point camloc = camera.getloc();
    //Point camori = camera.getori(); plus complexe

    Point pixori(0, dcam, 0);
    //pixori.sety(400);

    int objseen;
    float tfinal;

    std::cout << "init" << std::endl;

    for (int i=0; i<height; ++i)
    {
        for (int j=0; j<width; ++j)
        {
            pixori.setx(-width/2 + j);
            pixori.setz(height/2 - i);
            pixori.sety(dcam);

            //std::cout << pixori.getx() << ", " << pixori.gety() << std::endl;

            pixori.normalized();
            //std::cout << pixori.norm() << std::endl;

            tfinal = -1;
            objseen = -1;

            //std::cout << i << ", " << j << std::endl;

            if (this->ray(camloc, pixori, &tfinal, &objseen))
            {
                Sphere* obj = &objects[objseen];
                Point touch = camloc + pixori*tfinal;
                Point normale = (touch - obj->getloc());
                normale.normalized();

                std::cout << "touched" << std::endl;

                for (unsigned int itlight = 0; itlight < lights.size(); ++itlight)
                {
                    Light* lit = &lights[itlight];

                    Point lightray = (lit->getloc() - touch);
                    lightray.normalized();
                    float intensity = lightray*normale;

                    if (intensity > 0)
                    {

                        pixels[i*j*4] = intensity*obj->getR();//mettre la couleur. RGBa
                        pixels[i*j*4+1] = intensity*obj->getG();
                        pixels[i*j*4+2] = intensity*obj->getB();
                        pixels[i*j*4+3] = 1;

                        std::cout << (int)pixels[i*j*4] << std::endl;
                    }
                }

            }
            //transparency of the pixel
            pixels[i*j*4+3] = 1;

        }
    }
    std::cout << pixels[width/2*height/2*4] << std::endl;

}
