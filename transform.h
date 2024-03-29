#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "engine.h"
#include "listener.h"
#include "mat.h"

extern std::shared_ptr<control> ctrl;

class transformation : public listener, public actor {
    bool front_down = false;
    bool back_down  = false;
    bool left_down  = false;
    bool right_down = false;
    bool up_down    = false;
    bool down_down  = false;
    bool add_down   = false;
    bool sub_down   = false;
    bool xrot_down  = false;
    bool yrot_down  = false;
    bool zrot_down  = false;
    bool v_down     = false;
    bool b_down     = false;
    bool n_down     = false;
    bool m_down     = false;
    bool h_down     = false;
    bool j_down     = false;
    
public:
    void update() override {
        if (!sg.selected) return;
        ray r = ctrl->get_ray();
        float sinb = -r.yd;
        float cosb = sqrtf(1 - sinb * sinb);
        float sina = r.xd / cosb; // WHAT IF cosb = 0 ???
        float cosa = -r.zd / cosb;
        float nx[3] = {cosa, 0, sina};
        float ny[3] = {sina * sinb, cosb, -cosa * sinb};
        float nz[3] = {
            ny[1] * nx[2] - ny[2] * nx[1],
            ny[2] * nx[0] - ny[0] * nx[2],
            ny[0] * nx[1] - ny[1] * nx[0]
        };
        auto selected = sg.selected;
        std::vector<float*> vecs;
        std::vector<float> coefs;
        if (front_down) {
            vecs.push_back(nz);
            coefs.push_back(0.05f);
        }
        if (back_down) {
            vecs.push_back(nz);
            coefs.push_back(-0.05);
        }
        if (left_down) {
            vecs.push_back(nx);
            coefs.push_back(-0.05f);
        }
        if (right_down) {
            vecs.push_back(nx);
            coefs.push_back(0.05f);
        }
        if (up_down) {
            vecs.push_back(ny);
            coefs.push_back(0.05f);
        }
        if (down_down) {
            vecs.push_back(ny);
            coefs.push_back(-0.05f);
        }
        if (! vecs.empty()) {
            for (int t = 0; t <  vecs.size();++t){
                for (int i = 0; i < 3; ++i) {
                    selected->translate[i] += vecs[t][i] * coefs[t];
                }
            }
        }
        if (add_down) {
            selected->scale[0] += 0.005f;
            selected->scale[1] += 0.005f;
            selected->scale[2] += 0.005f;
        }
        if (sub_down) {
            selected->scale[0] -= 0.005f;
            if (selected->scale[0] < 1e-5) selected->scale[0] = 0;
            selected->scale[1] -= 0.005f;
            if (selected->scale[1] < 1e-5) selected->scale[1] = 0;
            selected->scale[2] -= 0.005f;
            if (selected->scale[2] < 1e-5) selected->scale[2] = 0;
        }
        if (xrot_down) {
            mat3 rot = mat3::rotate(5, nz[0], nz[1], nz[2]);
            selected->rotate_mat = rot * selected->rotate_mat;
        }
        if (yrot_down) {
            mat3 rot = mat3::rotate(5, ny[0], ny[1], ny[2]);
            selected->rotate_mat = rot * selected->rotate_mat;
        }
        if (zrot_down) {
            mat3 rot = mat3::rotate(5, nx[0], nx[1], nx[2]);
            selected->rotate_mat = rot * selected->rotate_mat;
        }
        if (v_down)  {
            GLfloat *d = selected->mtrl->diffuse;
            for (int i = 0; i < 3; ++i) {
                d[i] = (std::min)(d[i] + 0.05f, 1.0f);
            }
        }
        if (b_down) {
            GLfloat *d = selected->mtrl->diffuse;
            for (int i = 0; i < 3; ++i) {
                d[i] = (std::max)(d[i] - 0.05f, 0.0f);
            }
        }
        if (n_down) {
            GLfloat *d = selected->mtrl->ambient;
            for (int i = 0; i < 3; ++i) {
                d[i] = (std::max)(d[i] + 0.05f, 0.0f);
            }
        }
        if (m_down) {
            GLfloat *d = selected->mtrl->ambient;
            for (int i = 0; i < 3; ++i) {
                d[i] = (std::max)(d[i] - 0.05f, 0.0f);
            }
        }
        if (h_down) {
            GLfloat *d = selected->mtrl->specular;
            for (int i = 0; i < 3; ++i) {
                d[i] = (std::max)(d[i] + 0.05f, 0.0f);
            }
        }
        if (h_down) {
            GLfloat *d = selected->mtrl->specular;
            for (int i = 0; i < 3; ++i) {
                d[i] = (std::max)(d[i] - 0.05f, 0.0f);
            }
        }
    }

    bool keyboard(unsigned char key, int x, int y) override {
        switch (key) {
            case ',':
                front_down = true;
                break;
            case '.':
                back_down = true;
                break;
            case '=':
            case '+':
                add_down = true;
                break;
            case '-':
            case '_':
                sub_down = true;
                break;
            case 'u':
                xrot_down = true;
                break;
            case 'i':
                yrot_down = true;
                break;
            case 'o':
                zrot_down = true;
                break;
            case 'v':
                v_down = true;
                break;
            case 'b':
                b_down = true;
                break;
            case 'n':
                n_down = true;
                break;
            case 'm':
                m_down = true;
                break;
            case 'h':
                h_down = true;
                break;
            case 'j':
                j_down = true;
                break;
            default:
                break;
        }
        return false;
    }

    bool keyboard_up(unsigned char key, int x, int y) override {
        switch (key) {
            case ',':
                front_down = false;
                break;
            case '.':
                back_down = false;
                break;
            case '=':
            case '+':
                add_down = false;
                break;
            case '-':
            case '_':
                sub_down = false;
                break;
            case 'u':
                xrot_down = false;
                break;
            case 'i':
                yrot_down = false;
                break;
            case 'o':
                zrot_down = false;
                break;
            case 'v':
                v_down = false;
                break;
            case 'b':
                b_down = false;
                break;
            case 'n':
                n_down = false;
                break;
            case 'm':
                m_down = false;
                break;
            case 'h':
                h_down = false;
                break;
            case 'j':
                j_down = false;
                break;
            default:
                break;
        }
        return false;
    }

    bool special_key(int key, int x, int y) override {
        switch (key) {
            case GLUT_KEY_UP:
                up_down = true;
                break;
            case GLUT_KEY_DOWN:
                down_down = true;
                break;
            case GLUT_KEY_LEFT:
                left_down = true;
                break;
            case GLUT_KEY_RIGHT:
                right_down = true;
                break;
            default:
                break;
        }
        return false;
    }

    bool special_key_up(int key, int x, int y) override {
        switch (key) {
            case GLUT_KEY_UP:
                up_down = false;
                break;
            case GLUT_KEY_DOWN:
                down_down = false;
                break;
            case GLUT_KEY_LEFT:
                left_down = false;
                break;
            case GLUT_KEY_RIGHT:
                right_down = false;
                break;
            default:
                break;
        }
        return false;
    }
};

#endif
