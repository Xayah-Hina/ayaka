#ifndef AYAKAPATHTRACER_FRAME_BUFFER_H
#define AYAKAPATHTRACER_FRAME_BUFFER_H

#include <vector>

template<typename Vector>
struct FrameBufferT
{
    FrameBufferT(int _width, int _height);
    void resize(int _width, int _height);
    void set_clear_color(const Vector &color);
    void set_pixel(int row, int col, const Vector &color);
    void clear();
    void *data();

    std::vector<Vector> buffer;
    Vector CLEAR_COLOR;
    int width;
    int height;
};

template<typename Vector>
FrameBufferT<Vector>::FrameBufferT(int _width, int _height):width(_width), height(_height)
{ buffer.resize(width * height); }

template<typename Vector>
void FrameBufferT<Vector>::resize(int _width, int _height)
{
    this->width = _width;
    this->height = _height;
    buffer.resize(width * height);
}

template<typename Vector>
void FrameBufferT<Vector>::set_clear_color(const Vector &color)
{ CLEAR_COLOR = color; }

template<typename Vector>
void FrameBufferT<Vector>::set_pixel(int row, int col, const Vector &color)
{ buffer[row * width + col] = color; }

template<typename Vector>
void FrameBufferT<Vector>::clear()
{ std::fill(buffer.begin(), buffer.end(), CLEAR_COLOR); }

template<typename Vector>
void *FrameBufferT<Vector>::data()
{ return static_cast<void *>(buffer.data()); }

template<typename Vector>
void for_each_FB(FrameBufferT<Vector> FB)
{
    // TODO: create utility functions
}

#endif //AYAKAPATHTRACER_FRAME_BUFFER_H
