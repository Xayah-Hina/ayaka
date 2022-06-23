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
    void gamma_correct(float gamma);
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
void FrameBufferT<Vector>::gamma_correct(float gamma)
{
    for (auto &c : _buffer)
    {
        c.x() = std::pow(c.x(), gamma);
        c.y() = std::pow(c.y(), gamma);
        c.z() = std::pow(c.z(), gamma);
    }
}

template<typename Vector>
void FrameBufferT<Vector>::clear()
{ std::fill(_buffer.begin(), _buffer.end(), CLEAR_COLOR); }

template<typename Vector>
void *FrameBufferT<Vector>::data()
{ return static_cast<void *>(_buffer.data()); }

#endif //AYAKAPATHTRACER_FRAME_BUFFER_H
