#include "geometries.h"

void box::drawBox(GLfloat size) {
    static GLfloat n[6][3] =
            {
                    {-1.0, 0.0,  0.0},
                    {0.0,  1.0,  0.0},
                    {1.0,  0.0,  0.0},
                    {0.0,  -1.0, 0.0},
                    {0.0,  0.0,  1.0},
                    {0.0,  0.0,  -1.0}
            };
    static GLint faces[6][4] =
            {
                    {0, 1, 2, 3},
                    {3, 2, 6, 7},
                    {7, 6, 5, 4},
                    {4, 5, 1, 0},
                    {5, 6, 2, 1},
                    {7, 4, 0, 3}
            };
    GLfloat v[8][3];
    GLint i;

    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

    glBegin(GL_QUADS);
    for (i = 5; i >= 0; i--) {
        glNormal3fv(&n[i][0]);
        glTexCoord2d(1, 0);
        glVertex3fv(&v[faces[i][0]][0]);
        glTexCoord2d(1, 1);
        glVertex3fv(&v[faces[i][1]][0]);
        glTexCoord2d(0, 1);
        glVertex3fv(&v[faces[i][2]][0]);
        glTexCoord2d(0, 0);
        glVertex3fv(&v[faces[i][3]][0]);
    }
    glEnd();
}

void prism::drawPrism() {
    // back endcap
    glBegin(GL_TRIANGLES);
	glTexCoord2d(1, 0);
    glVertex3f(1.0f, 0.0f, 0.0f);
	glTexCoord2d(0, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2d(0, 1);
    glVertex3f(0.0f, 1.0f, 0.0f);
//    glEnd();

    // front endcap
//    glBegin(GL_TRIANGLES);
	glTexCoord2d(1, 0);
    glVertex3f(1.0f, 0.0f, 1.0f);
	glTexCoord2d(0, 0);
    glVertex3f(0.0f, 0.0f, 1.0f);
	glTexCoord2d(0, 1);
    glVertex3f(0.0f, 1.0f, 1.0f);
    glEnd();

    // bottom
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord2d(1, 0);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glTexCoord2d(1, 1);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glTexCoord2d(0, 1);
    glVertex3f(0.0f, 0.0f, 1.0f);
//    glEnd();

    // back
//    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord2d(0, 1);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glTexCoord2d(1, 1);
    glVertex3f(0.0f, 1.0f, 1.0f);
    glTexCoord2d(1, 0);
    glVertex3f(0.0f, 0.0f, 1.0f);
//    glEnd();

    // top
//    glBegin(GL_QUADS);
    glTexCoord2d(0, 1);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glTexCoord2d(1, 1);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glTexCoord2d(1, 0);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glTexCoord2d(0, 0);
    glVertex3f(0.0f, 1.0f, 1.0f);
    glEnd();
}

void frustum::drawFrustum() {
	// back endcap
	glBegin(GL_TRIANGLES);
	glTexCoord2d(1, 0);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glTexCoord2d(0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2d(0, 1);
	glVertex3f(0.0f, 1.0f, 0.0f);
	//    glEnd();

		// front endcap
	//    glBegin(GL_TRIANGLES);
	glTexCoord2d(1, 0);
	glVertex3f(0.5f, 0.0f, 1.0f);
	glTexCoord2d(0, 0);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glTexCoord2d(0, 1);
	glVertex3f(0.0f, 0.5f, 1.0f);
	glEnd();

	// bottom
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2d(0, 1);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glTexCoord2d(1, 0);
	glVertex3f(0.5f, 0.0f, 1.0f);
	glTexCoord2d(1, 1);
	glVertex3f(0.0f, 0.0f, 1.0f);
	//    glEnd();

		// back
	//    glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2d(0, 1);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(1, 0);
	glVertex3f(0.0f, 0.5f, 1.0f);
	glTexCoord2d(1, 1);
	glVertex3f(0.0f, 0.0f, 1.0f);
	//    glEnd();

		// top
	//    glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0, 1);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glTexCoord2d(1, 0);
	glVertex3f(0.5f, 0.0f, 1.0f);
	glTexCoord2d(1, 1);
	glVertex3f(0.0f, 0.5f, 1.0f);
	glEnd();
}