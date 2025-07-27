#include "graph/graph.h"

#include <GL/glu.h>

#include <core/error.h>

namespace graph
{
    GLvoid Perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
    {
        e(gluPerspective(fovy, aspect, zNear, zFar));
    }
}