#ifndef Renderer_H
#define Renderer_H

#include "ofMain.h"

#include "Vector2.h"
#include "PointMass.h"
/*
#include <vector>
#include <windows.h>

#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
*/


/**
* Debug renderer for OpenGL
* replace with oF function
*/
class Renderer
{
public :

	static inline void RenderNormalLine(PointMass* b, PointMass* a)
	{
		ofLine( 0.5*(a->Position.X+b->Position.X), 0.5*(a->Position.Y+b->Position.Y), 
			0.5*(a->Position.X+b->Position.X) + (b->Position.Y - a->Position.Y),
			0.5*(a->Position.Y+b->Position.Y) - (b->Position.X - a->Position.X) );
	}

	static void RenderShapeNormal(std::vector<PointMass*> &mPointMasses,float R,float G,float B)
	{
		ofSetColor(ofFloatColor(R, G, B));

        for (unsigned int i = 0; i < mPointMasses.size()-1; i++)
        {
			RenderNormalLine((PointMass*)mPointMasses.at(i), (PointMass*)mPointMasses.at(i+1));
        }
		if ( mPointMasses.size() >= 2 )
		{
			RenderNormalLine((PointMass*)mPointMasses.back(), (PointMass*)mPointMasses.at(0));
		}
	}


	static void RenderGlobalShapeLine(std::vector<PointMass*> &mPointMasses,float R,float G,float B)
    {
		ofNoFill();
		ofSetColor(ofFloatColor(R, G, B));

		ofBeginShape();

        for (unsigned int i = 0; i < mPointMasses.size(); i++)
        {
			ofVertex(((PointMass*)mPointMasses.at(i))->Position.X, ((PointMass*)mPointMasses.at(i))->Position.Y);
        }
		//ofVertex(((PointMass*)mPointMasses.at(0))->Position.X, ((PointMass*)mPointMasses.at(0))->Position.Y);

		ofEndShape(true);

     }

	static void RenderLine(Vector2 start,Vector2 stop,float R,float G,float B)
    {
		ofSetColor(ofFloatColor(R, G, B));
		ofLine(start.X, start.Y, stop.X, stop.Y);
     }

	static void RenderGlobalShapeLine(Vector2 *Vertices,int num,float R,float G,float B)
    {
		ofNoFill();
		ofSetColor(ofFloatColor(R, G, B));

		ofBeginShape();

        for (int i = 0; i < num; i++)
        {
			ofVertex(Vertices[i].X, Vertices[i].Y);
        }
		//ofVertex(Vertices[0].X, Vertices[0].Y);

		ofEndShape(true);

     }

	static void FillBlobShape(Vector2 *vertexArray,int count,float R,float G,float B)
    {
		ofFill();
        ofSetColor(ofFloatColor(R, G, B));
		ofBeginShape();

        for(int i = 0;i < count;i++)
        {
			ofVertex(vertexArray[i].X, vertexArray[i].Y);
        }
		ofEndShape(true);
    }

    static void RenderPoints(std::vector<PointMass*> &mPointMasses,float R,float G,float B)
    {
       ofSetColor(ofFloatColor(R, G, B));

        for (unsigned int i = 0; i < mPointMasses.size(); i++)
        {
			ofCircle(((PointMass*)mPointMasses.at(i))->Position.X, ((PointMass*)mPointMasses.at(i))->Position.Y, 5.0f);
        }
    }

	static void FillSpringShape(std::vector<PointMass*> &mPointMasses, int *mIndices,int mIndicesCount,float  R,float  G,float B)
    {
		ofFill();
        ofSetColor(ofFloatColor(R, G, B));
        for (int i = 0; i < mIndicesCount; i += 3)
        {
			ofBeginShape();

            ofVertex(((PointMass*)mPointMasses.at(mIndices[i]))->Position.X, ((PointMass*)mPointMasses.at(mIndices[i]))->Position.Y);
            ofVertex(((PointMass*)mPointMasses.at(mIndices[i+1]))->Position.X, ((PointMass*)mPointMasses.at(mIndices[i+1]))->Position.Y);
            ofVertex(((PointMass*)mPointMasses.at(mIndices[i+2]))->Position.X, ((PointMass*)mPointMasses.at(mIndices[i+2]))->Position.Y);

			ofEndShape(true);
        }
    }
};


#endif