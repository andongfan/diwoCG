#include "control.h"

#include <cmath>
#ifndef M_PI
#define M_PI 3.1415926535
#endif // !M_PI


orbit_control* instance;

void orbit_control::motion_static(int x, int y) {
    if (instance) instance -> motion(x, y);
}

void orbit_control::mouse_static(int button, int state, int x, int y) {
    if (instance) instance -> mouse(button, state, x, y);
}

void orbit_control::keyboard_static(unsigned char key, int x, int y) {
    if (instance) instance -> keyboard(key, x, y);
}

void orbit_control::keyboard_up_static(unsigned char key, int x, int y) {
    if (instance) instance -> keyboard_up(key, x, y);
}

void orbit_control::motion(int x, int y) {
    int dx = x - down_x;
    int dy = y - down_y;
    alpha = down_alpha + dx * -0.23f;
    beta = down_beta + dy * -0.23f;
    if (beta < -90.0f) beta = -90.0f;
    if (beta > +90.0f) beta = +90.0f;
}

void orbit_control::mouse(int button, int state, int x, int y) {
    down_x = x;
    down_y = y;
    down_alpha = alpha;
    down_beta = beta;
}

void orbit_control::keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': w_down = true; break;
        case 's': s_down = true; break;
        case 'a': a_down = true; break;
        case 'd': d_down = true; break;
    }
}

void orbit_control::keyboard_up(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': w_down = false; break;
        case 's': s_down = false; break;
        case 'a': a_down = false; break;
        case 'd': d_down = false; break;
    }
}

orbit_control::orbit_control() {
    // TODO: register glut event listeners
    instance = this;
    glutMotionFunc(&motion_static);
    glutMouseFunc(&mouse_static);
    glutKeyboardFunc(&keyboard_static);
    glutKeyboardUpFunc(&keyboard_up_static);
    glutIgnoreKeyRepeat(true);
}

void orbit_control::move(float angle, float dist) {
    float rad = (angle - alpha) / 180.0f * M_PI;
    x += dist * cos(rad);
    z -= dist * sin(rad);
}

void orbit_control::update() {
    if (w_down) move( 90.0f, 0.1f);
    if (s_down) move(270.0f, 0.1f);
    if (a_down) move(180.0f, 0.1f);
    if (d_down) move(  0.0f, 0.1f);
    glRotatef(beta, 1.0f, 0.0f, 0.0f);
    glRotatef(alpha, 0.0f, 1.0f, 0.0f);
    glTranslatef(-x, -y, -z);
}

ray orbit_control::get_ray() {
    float alpha_rad = alpha / 180.0f * M_PI;
    float beta_rad = beta / 180.0f * M_PI;
    return ray(
        x, y, z,
        +1.0f * sin(alpha_rad) * cos(beta_rad),
        -1.0f                  * sin(beta_rad),
        -1.0f * cos(alpha_rad) * cos(beta_rad)
    );
}
