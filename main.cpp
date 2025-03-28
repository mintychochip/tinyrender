#include <cmath>
#include "image.h"
#include "model.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor blue = TGAColor(0, 255, 0, 255);
const int width = 800;
const int height = 800;
Model *model = NULL;

void line1(int x0, int y0, int x1, int y1, TGAImage &img, TGAColor color)
{
    for (float t = 0.; t < 1.; t += .01)
    {
        int x = x0 + (x1 - x0) * t;
        int y = y0 + (y1 - y0) * t;
        img.set(x, y, color);
    }
}

void line2(int x0, int y0, int x1, int y1, TGAImage &img, TGAColor color)
{
    for (int x = x0; x <= x1; x++)
    {
        float t = (x - x0) / (float)(x1 - x0);
        int y = y0 * (1. - t) + y1 * t;
        img.set(x, y, color);
    }
}

void line3(int x0, int y0, int x1, int y1, TGAImage &img, TGAColor color)
{
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1))
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }

    if (x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    for (int x = x0; x <= x1; x++)
    {
        float t = (x - x0) / (float)(x1 - x0);
        int y = y0 * (1. - t) + y1 * t;
        if (steep)
        {
            img.set(y, x, color);
        }
        else
        {
            img.set(x, y, color);
        }
    }
}

void line4(int x0, int y0, int x1, int y1, TGAImage &img, TGAColor color)
{
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1))
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
        steep = true;
    }
    if (x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1 - x0;
    int dy = y1 - y0;
    float derror = std::abs(dy / float(dx));
    float error = 0;
    int y = y0;
    for (int x = x0; x <= x1; x++)
    {
        if (steep)
        {
            img.set(y, x, color);
        }
        else
        {
            img.set(x, y, color);
        }
        error += derror;
        if (error > .5)
        {
            y += (y1 > y0 ? 1 : -1);
            error -= 1.;
        }
    }
}

void line5(int x0, int y0, int x1, int y1, TGAImage &img, TGAColor color)
{
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1))
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror2 = std::abs(dy) * 2;
    int error2 = 0;
    int y = y0;
    for (int x = x0; x <= x1; x++)
    {
        if (steep)
        {
            img.set(y, x, color);
        }
        else
        {
            img.set(x, y, color);
        }
        error2 += derror2;
        if (error2 > dx)
        {
            y += (y1 > y0 ? 1 : -1);
            error2 -= dx * 2;
        }
    }
}

void line(Vec2i t0, Vec2i t1, TGAImage &img, TGAColor color)
{
    line5(t0.x, t0.y, t1.x, t1.y, img, color);
}

void triangle1(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &img, TGAColor color)
{
    if (t0.y > t1.y)
        std::swap(t0, t1);
    if (t0.y > t2.y)
        std::swap(t0, t2);
    if (t1.y > t2.y)
        std::swap(t1, t2);
    line(t0, t1, img, blue);
    line(t1, t2, img, blue);
    line(t2, t0, img, red);
}

void triangle2(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &img, TGAColor color)
{
    if (t0.y > t1.y)
        std::swap(t0, t1);
    if (t0.y > t2.y)
        std::swap(t0, t2);
    if (t1.y > t2.y)
        std::swap(t1, t2);
    int total_height = t2.y - t0.y;
    for (int y = t0.y; y <= t1.y; y++)
    {
        int segment_height = t1.y - t0.y + 1;
        float alpha = (float)(y - t0.y) / total_height;
        float beta = (float)(y - t0.y) / segment_height;
        Vec2i A = t0 + (t2 - t0) * alpha;
        Vec2i B = t0 + (t1 - t0) * beta;
        img.set(A.x, y, red);
        img.set(B.x, y, blue);
    }
}

void triangle3(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &img, TGAColor color)
{
    if (t0.y > t1.y)
        std::swap(t0, t1);
    if (t0.y > t2.y)
        std::swap(t0, t2);
    if (t1.y > t2.y)
        std::swap(t1, t2);
    int total_height = t2.y - t0.y;
    for (int y = t0.y; y <= t1.y; y++)
    {
        int segment_height = t1.y - t0.y + 1;
        float alpha = (float)(y - t0.y) / total_height;
        float beta = (float)(y - t0.y) / segment_height;
        Vec2i A = t0 + (t2 - t0) * alpha;
        Vec2i B = t0 + (t1 - t0) * beta;
        if (A.x > B.x) std::swap(A,B);
        for (int j = A.x; j < B.x; j++) {
            img.set(j,y,color);
        }
    }

    for (int y = t1.y; y <= t2.y; y++) 
    {
        int segment_height = t2.y - t1.y + 1;
        float alpha = (float) (y - t0.y) / total_height; // alpha def 
        float beta = (float) (y - t1.y) / segment_height;
        Vec2i A = t0 + (t2 - t0) * alpha;
        Vec2i B = t1 + (t2 - t1) * beta;
        if (A.x > B.x) std::swap(A,B);
        for (int j = A.x; j < B.x; j++) {
            img.set(j,y,color);
        }
    }
}

void lesson2_linesweep()
{
    int width = 500, height = 500;
    TGAImage image{width, height, TGAImage::RGB};
    Vec2i t0[3] = {Vec2i(10, 70), Vec2i(50, 160), Vec2i(70, 80)};
    Vec2i t1[3] = {Vec2i(180, 50), Vec2i(150, 1), Vec2i(70, 180)};
    Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)};
    triangle1(t0[0], t0[1], t0[2], image, red);
    triangle1(t1[0], t1[1], t1[2], image, white);
    triangle1(t2[0], t2[1], t2[2], image, blue);
    image.flip_vertically();
    image.write_tga_file("line_sweep.tga");
    image = TGAImage{width, height, TGAImage::RGB};
    Vec2i t3[3] = {Vec2i(10, 70), Vec2i(50, 160), Vec2i(70, 80)};
    Vec2i t4[3] = {Vec2i(180, 50), Vec2i(150, 1), Vec2i(70, 180)};
    Vec2i t5[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)};
    triangle2(t3[0], t3[1], t3[2], image, red);
    triangle2(t4[0], t4[1], t4[2], image, white);
    triangle2(t5[0], t5[1], t5[2], image, blue);
    image.flip_vertically();
    image.write_tga_file("line_sweep2.tga");
    image = TGAImage{width, height, TGAImage::RGB};
    Vec2i t6[3] = {Vec2i(10, 70), Vec2i(50, 160), Vec2i(70, 80)};
    Vec2i t7[3] = {Vec2i(180, 50), Vec2i(150, 1), Vec2i(70, 180)};
    Vec2i t8[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)};
    triangle3(t6[0], t6[1], t6[2], image, red);
    triangle3(t7[0], t7[1], t7[2], image, white);
    triangle3(t8[0], t8[1], t8[2], image, blue);
    image.flip_vertically();
    image.write_tga_file("line_sweep3.tga");
}

int point()
{
    return rand() % 255;
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    model = new Model{"head.obj"};
    TGAImage image(width, height, TGAImage::RGB);
    for (int i = 0; i < model->nfaces(); i++)
    {
        std::vector<int> face = model->face(i);
        for (int j = 0; j < 3; j++)
        {
            Vec3f v0 = model->vert(face[j]);
            Vec3f v1 = model->vert(face[(j + 1) % 3]);
            int x0 = (v0.x + 1.) * width / 2.;
            int y0 = (v0.y + 1.) * height / 2.;
            int x1 = (v1.x + 1.) * width / 2.;
            int y1 = (v1.y + 1.) * height / 2.;
            line5(x0, y0, x1, y1, image, white);
        }
    }
    lesson2_linesweep();
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}