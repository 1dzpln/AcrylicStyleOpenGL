#ifndef SIMPLEMESHDATA_H
#define SIMPLEMESHDATA_H
#include <QOpenGLBuffer>

static unsigned int g_quadVerticesCount = 4;

static GLfloat g_quadData[] = {
    // Positions  // Texture Coords
     1.0f,  1.0f, 1.0f, 1.0f,
     1.0f, -1.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f, 0.0f,
    -1.0f,  1.0f, 0.0f, 1.0f
};
static GLuint g_quadIndices[] = {
    0, 1, 3,
    1, 2, 3
};

#endif // SIMPLEMESHDATA_H
