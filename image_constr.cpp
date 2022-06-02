#include "head.h"
#include <stdio.h>
#include <string.h>
#include <chrono>

const vecops BACKGROUND_COLOUR(10.0,10.0,10.0);

bool scene_intersect(const vecops& begin, const vecops& vec, const std::vector<box*>& objects, vecops& point, vecops& N, vecops& colour, double limit) {
    double nearest_dist = std::numeric_limits<double>::max();

    bool intersect = 0;

    for(size_t i = 0; i < objects.size(); ++i) {
        double CurrentDist = objects[i]->ray_intersect(begin, vec);
        if(CurrentDist == -1 || CurrentDist > limit) continue;

        intersect = 1;

        if(CurrentDist < nearest_dist) {
            nearest_dist = CurrentDist;

            point = begin + vec*CurrentDist;
            N = (point - objects[i]->center()).normalize();
            colour = objects[i]->colour();
        }
    }

    return intersect;
}

vecops cast_ray(const vecops& begin, const vecops& vec, const std::vector<box*>& objects, const Light& light, double limit) {
    vecops point, N;
    vecops colour;

    if (!scene_intersect(begin, vec, objects, point, N, colour, limit)) {
        return BACKGROUND_COLOUR;
    }



    vecops light_vec = (light._position - point).normalize();

    double diffuse_light_intensity = light._intensity * std::max(0.0, light_vec*N);

    return colour*diffuse_light_intensity;
}

void render(const std::vector<box*>& objects, Parametrs& param) {
    std::vector<std::vector<vecops>> canvas(param.height, std::vector<vecops>(param.width, BACKGROUND_COLOUR));

    size_t m = param.height;
    size_t k = param.width;

    vecops t = param.normal.normalize();
    vecops b = cross(param.up, t).normalize();
    vecops v = cross(t, b);

    double gx = param.screen*tan((param.alpha/180 * PI)/2.);
    double gy = gx*(static_cast<double>(m)/static_cast<double>(k));

    auto start = std::chrono::steady_clock::now();

#pragma omp parallel for
    for(int j = 0; j < param.height; ++j) {
        for(int i = 0; i < param.width; ++i) {
            vecops vec;
            for(int l = 0; l < 3; ++l) {
                vec[l] = t[l]*param.screen - gx*b[l] - gy*v[l] + (i*2*gx)*b[l]/(k-1) + ((m-j)*2*gy)*v[l]/(m-1);
            }
            vec = vec.normalize();

            canvas[j][i] = cast_ray(param.cam, vec, objects, param.light, param.limit);
        }
    }

    auto end = std::chrono::steady_clock::now();

    std::cout << "work time: " << std::chrono::duration<double, std::milli>(end - start).count() << " ms" << "\n";

    for(size_t i = 0; i < param.height; ++i) {
        for(size_t j = 0; j < param.width; ++j) {
            for(size_t l = 0; l < 3; ++l) {
                canvas[i][j][l] = std::min(1.0, canvas[i][j][l]);
                canvas[i][j][l] *= 255.0;
            }
        }
    }


    // bmp
    int w = param.width;
    int h = param.height;

    unsigned char* img = NULL;
    int filesize = 54 + 3*w*h;

    img = (unsigned char*)malloc(3*w*h);
    memset(img, 0, 3*w*h);

    for(int i = 0; i < h; ++i) {
        for(int j = 0; j < w; ++j) {
            unsigned char r = static_cast<unsigned char>(canvas[i][j][0]);
            unsigned char g = static_cast<unsigned char>(canvas[i][j][1]);
            unsigned char b = static_cast<unsigned char>(canvas[i][j][2]);
            img[(j+i*w)*3+2] = r;
            img[(j+i*w)*3+1] = g;
            img[(j+i*w)*3+0] = b;
        }
    }

    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
    unsigned char bmppad[3] = {0,0,0};

    bmpfileheader[2] = (unsigned char)(filesize);
    bmpfileheader[3] = (unsigned char)(filesize>>8);
    bmpfileheader[4] = (unsigned char)(filesize>>16);
    bmpfileheader[5] = (unsigned char)(filesize>>24);

    bmpinfoheader[4] = (unsigned char)(w);
    bmpinfoheader[5] = (unsigned char)(w>>8);
    bmpinfoheader[6] = (unsigned char)(w>>16);
    bmpinfoheader[7] = (unsigned char)(w>>24);
    bmpinfoheader[8] = (unsigned char)(h);
    bmpinfoheader[9] = (unsigned char)(h>>8);
    bmpinfoheader[10] = (unsigned char)(h>>16);
    bmpinfoheader[11] = (unsigned char)(h>>24);

    FILE *f = fopen("img.bmp","wb");
    fwrite(bmpfileheader, 1, 14, f);
    fwrite(bmpinfoheader, 1, 40, f);
    for(int i = 0; i < h; ++i) {
        fwrite(img  +(w*(h-1-i)*3), 3, w, f);
        fwrite(bmppad, 1, (4-(w*3)%4)%4, f);
    }

    free(img);
    fclose(f);
}