#ifndef AYAKAPATHTRACER_FRAME_BUFFER_H
#define AYAKAPATHTRACER_FRAME_BUFFER_H

#include <vector>

template<typename Vector>
struct FrameBufferT
{
    FrameBufferT(int width, int height);
    void resize(int width, int height);
    void set_clear_color(const Vector &color);
    void set_pixel(int row, int col, const Vector &color);
    void clear();
    void *data();

    std::vector<Vector> _buffer;
    Vector CLEAR_COLOR;
    int _width;
    int _height;
};

template<typename Vector>
FrameBufferT<Vector>::FrameBufferT(int width, int height):_width(width), _height(height)
{ _buffer.resize(_width * _height); }

template<typename Vector>
void FrameBufferT<Vector>::resize(int width, int height)
{
    this->_width = width;
    this->_height = height;
    _buffer.resize(_width * _height);
}

template<typename Vector>
void FrameBufferT<Vector>::set_clear_color(const Vector &color)
{ CLEAR_COLOR = color; }

template<typename Vector>
void FrameBufferT<Vector>::set_pixel(int row, int col, const Vector &color)
{ _buffer[row * _width + col] = color; }

template<typename Vector>
void FrameBufferT<Vector>::clear()
{ std::fill(_buffer.begin(), _buffer.end(), CLEAR_COLOR); }

template<typename Vector>
void *FrameBufferT<Vector>::data()
{ return static_cast<void *>(_buffer.data()); }

#endif //AYAKAPATHTRACER_FRAME_BUFFER_H
