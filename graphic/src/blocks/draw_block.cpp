#include "draw_block.h"
#include "GL/glut.h"
#include <GL/gl.h>

struct CurrentPoints {
    GLdouble arr[8][3];
};

CurrentPoints& create_array(const Block &block, GLdouble height, GLdouble move) {
    static CurrentPoints arr;
    GLdouble x[8][3] = {
            {block.left_bottom.getX() + move,   0,              block.left_bottom.getZ() + move},
            {block.left_bottom.getX() + move,   height - move,  block.left_bottom.getZ() + move},
            {block.right_top.getX() - move,     0,              block.left_bottom.getZ() + move},
            {block.right_top.getX() - move,     height - move,  block.left_bottom.getZ() + move},
            {block.right_top.getX() - move,     0,              block.right_top.getZ() - move},
            {block.right_top.getX() - move,     height - move,  block.right_top.getZ() - move},
            {block.left_bottom.getX() + move,   0,              block.right_top.getZ() - move},
            {block.left_bottom.getX() + move,   height - move,  block.right_top.getZ() - move}
    };
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 3; j++)
            arr.arr[i][j] = x[i][j];
    return arr;
}

void draw::draw_floor(const Block &floor_block) {
    CurrentPoints &points = create_array(floor_block, -0.01, 0);
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_QUADS);
    glVertex3dv(points.arr[1]);
    glVertex3dv(points.arr[3]);
    glVertex3dv(points.arr[5]);
    glVertex3dv(points.arr[7]);
    glEnd();
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex3d(floor_block.left_bottom.getX(),    0,    floor_block.left_bottom.getZ());
    glVertex3d(floor_block.right_top.getX(),      0,    floor_block.left_bottom.getZ());
    glVertex3d(floor_block.right_top.getX(),      0,    floor_block.right_top.getZ());
    glVertex3d(floor_block.left_bottom.getX(),    0,    floor_block.right_top.getZ());
    glEnd();
}

void draw::draw_void(const Block &void_block) {
    GLfloat top_color[3] = {0.7, 0.7, 0.7};
    GLfloat bottom_color[3] = {0, 0, 0};

    CurrentPoints &points = create_array(void_block, -2, 0);
    glBegin(GL_QUAD_STRIP);

    for (int i = 0; i < 10; i++) {
        glColor3fv(i % 2 ? bottom_color : top_color);
        glVertex3dv(points.arr[i % 8]);
    }
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    for (int i = 1; i < 8; i+= 2)
        glVertex3dv(points.arr[i]);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex3d(void_block.left_bottom.getX(),    0,    void_block.left_bottom.getZ());
    glVertex3d(void_block.right_top.getX(),      0,    void_block.left_bottom.getZ());
    glVertex3d(void_block.right_top.getX(),      0,    void_block.right_top.getZ());
    glVertex3d(void_block.left_bottom.getX(),    0,    void_block.right_top.getZ());
    glEnd();
}

void draw::draw_small_wall(const Block &s_wall_block) {
    GLfloat bottom_color[3] = {0.8, 0.8, 0.8};
    GLfloat top_color[3] = {0.85, 0.85, 0.85};

    glBegin(GL_QUAD_STRIP);
    CurrentPoints &points = create_array(s_wall_block, 0.5, 0.01);

    for (int i = 0; i < 10; i++) {
        glColor3fv(i % 2 ? top_color : bottom_color);
        glVertex3dv(points.arr[i % 8]);
    }
    glEnd();

    glColor3fv(top_color);
    glBegin(GL_QUADS);
    for (int i = 1; i < 8; i+= 2)
        glVertex3dv(points.arr[i]);
    glEnd();

    points = create_array(s_wall_block, 0.5, 0);
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    for (auto & i : points.arr)
        glVertex3dv(i);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    for (int i = 1; i < 8; i+= 2)
        glVertex3dv(points.arr[i]);
    glEnd();
}

void draw::draw_wall(const Block &wall_block) {
    GLfloat bottom_color[3] = {0.8, 0.8, 0.8};
    GLfloat top_color[3] = {0.9, 0.9, 0.9};

    glBegin(GL_QUAD_STRIP);
    CurrentPoints &points = create_array(wall_block, 5, 0.01);

    for (int i = 0; i < 10; i++) {
        glColor3fv(i % 2 ? top_color : bottom_color);
        glVertex3dv(points.arr[i % 8]);
    }
    glEnd();

    glColor3fv(top_color);
    glBegin(GL_QUADS);
    for (int i = 1; i < 8; i+= 2)
        glVertex3dv(points.arr[i]);
    glEnd();

    points = create_array(wall_block, 5, 0);
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    for (auto & i : points.arr)
        glVertex3dv(i);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    for (int i = 1; i < 8; i+= 2)
        glVertex3dv(points.arr[i]);
    glEnd();
}


void draw::draw_block(const Block &block) {
    switch (block.block_type) {
        case Tile::Void:
            draw_void(block);
            break;
        case Tile::Floor:
            draw_floor(block);
            break;
        case Tile::Small_Wall:
            draw_small_wall(block);
            break;
        case Tile::Wall:
            draw_wall(block);
            break;
    }
}