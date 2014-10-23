//
//  asteroid.h
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 20/10/14.
//
//

#ifndef Shader_asteroid_h
#define Shader_asteroid_h


#include "iobject.h"
#include <random>
#include <cmath>
using namespace std;


namespace Game
{

    class Asteroid: public IObject
    {
    public:
        struct AsteroidConfig
        {
            
            int asteroidExplosionSigma = 0.2;
        } conf;
        
        Asteroid();
        
        GAME_OBJECT(Asteroid)
        
        void visit(SpaceShip&s);
        
        void explode();
        
        virtual void accept(Visitor& visitor){ visitor.visit(*this);}

        static normal_distribution<float> partsDistrib;
        static normal_distribution<float> unevenDistrib;
        
        void setParted();
        bool isParted() { return piece;}
    protected:
        bool piece;
        
        static default_random_engine generator;
        static normal_distribution<float> colorDistrib;
        static uniform_real_distribution<float> explosionDistib;
        
        float getRandColorComponent();
        
        void getNormalizedRandArray(vector<float>& vals, int num);
    };
}

#endif
