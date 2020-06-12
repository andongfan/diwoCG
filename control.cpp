#include "control.h"

#include <cmath>
#ifndef M_PI
#define M_PI 3.1415926535
#endif

#include "engine.h"

bool orbit_control::motion(int mx, int my) {
    int dx = mx - down_x;
    int dy = my - down_y;
    float sx = 110.0f / (float)w_width;
    float sy = 110.0f / (float)w_height;
    alpha = down_alpha - (float)dx * sx;
    beta  = down_beta  - (float)dy * sy;
    if (beta < -90.0f) beta = -90.0f;
    if (beta > +90.0f) beta = +90.0f;
    return false;
}

bool orbit_control::mouse(int button, int state, int mx, int my) {
    down_x = mx;
    down_y = my;
    down_alpha = alpha;
    down_beta = beta;
    return false;
}

bool orbit_control::keyboard(unsigned char key, int mx, int my) {
    switch (key) {
        case 'w': w_down = true; break;
        case 's': s_down = true; break;
        case 'a': a_down = true; break;
        case 'd': d_down = true; break;
        case 'c': c_down = true; break;
        case 'z': z_down = true; break;
        case 'g': {
            g_down = true;
            down_node = sg.selected;
            if (down_node) {
                down_ray = get_ray();
                down_mat = down_node->rotate_mat;
                down_pos[0] = down_node->translate[0];
                down_pos[1] = down_node->translate[1];
                down_pos[2] = down_node->translate[2];
                g_down_alpha = alpha;
                g_down_beta = beta;
            }
            break;
        }
    }
    return false;
}

bool orbit_control::keyboard_up(unsigned char key, int mx, int my) {
    switch (key) {
        case 'w': w_down = false; break;
        case 's': s_down = false; break;
        case 'a': a_down = false; break;
        case 'd': d_down = false; break;
        case 'c': c_down = false; break;
        case 'z': z_down = false; break;
        case 'r': {
            // center selection
            if (!sg.selected) break;
            auto a = sg.selected->get_aabb();
            float dx = a.x1 - a.x0;
            float dy = a.y1 - a.y0;
            float dz = a.z1 - a.z0;
            float size = (std::max)(dx, (std::max)(dy, dz));
            float dist = size * 2.6f;
            ray r = get_ray();
            x = (a.x0 + a.x1) / 2 - r.xd * dist;
            y = (a.y0 + a.y1) / 2 - r.yd * dist;
            z = (a.z0 + a.z1) / 2 - r.zd * dist;
            break;
        }
        case 'g': g_down = false; break;
        case ' ': {
            sg.selected = sg.hovered;
            break;
        }
    }
    return false;
}

void orbit_control::move(float angle, float dist) {
    float rad = (angle - alpha) / 180.0f * (float)M_PI;
    x += dist * cosf(rad);
    z -= dist * sinf(rad);
}

void orbit_control::update() {
    if (w_down) move( 90.0f, 0.1f);
    if (s_down) move(270.0f, 0.1f);
    if (a_down) move(180.0f, 0.1f);
    if (d_down) move(  0.0f, 0.1f);
    if (c_down) y += 0.1f;
    if (z_down) y -= 0.1f;

    if (g_down && down_node) {
        ray r = get_ray();
        // world -> ray
        auto ro = mat3::rotate(g_down_beta, 1.0f, 0.0f, 0.0f) * mat3::rotate(g_down_alpha, 0.0f, 1.0f, 0.0f);
        auto rn = mat3::rotate(beta, 1.0f, 0.0f, 0.0f) * mat3::rotate(alpha, 0.0f, 1.0f, 0.0f);
        // dp in world
        vec3 dpo = {
                down_pos[0] - down_ray.x0,
                down_pos[1] - down_ray.y0,
                down_pos[2] - down_ray.z0
        };
        vec3 dpn = ~rn * ro * dpo;
        // back to node
        down_node->translate[0] = r.x0 + dpn.data[0];
        down_node->translate[1] = r.y0 + dpn.data[1];
        down_node->translate[2] = r.z0 + dpn.data[2];
        down_node->rotate_mat = (~rn * ro) * down_mat;
    }

    glMatrixMode(GL_PROJECTION);
    // no load identity! we transform directly on the projection matrix generated
    // by gluPerspective(), in order to make lighting operate in world coordinates correctly.
    glRotatef(beta, 1.0f, 0.0f, 0.0f);
    glRotatef(alpha, 0.0f, 1.0f, 0.0f);
    glTranslatef(-x, -y, -z);

    glMatrixMode(GL_MODELVIEW);
}

ray orbit_control::get_ray() {
    float alpha_rad = alpha / 180.0f * (float)M_PI;
    float beta_rad = beta / 180.0f * (float)M_PI;
    return {
        x, y, z,
        +1.0f * sinf(alpha_rad) * cosf(beta_rad),
        -1.0f                   * sinf(beta_rad),
        -1.0f * cosf(alpha_rad) * cosf(beta_rad)
    };
}