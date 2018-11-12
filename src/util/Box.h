#ifndef __BOX_H__
#define __BOX_H__

#include <string>
#include <sstream>
#include "global/namespace.h"
#include "XY.h"

PROJECT_NAMESPACE_BEGIN

template<typename T>
class Box
{
public:
    explicit Box() = default;
    explicit Box(const XY<T> &p) : _ll(p), _ur(p) {}
    explicit Box(const XY<T> &ll, const XY<T> &ur) : _ll(ll), _ur(ur) {}
    explicit Box(T xLo, T yLo, T xHi, T yHi) : _ll(xLo, yLo), _ur(xHi, yHi) {}

    // Getters
    T                xLo() const                     { return _ll.x(); }
    T                yLo() const                     { return _ll.y(); }
    T                xHi() const                     { return _ur.x(); }
    T                yHi() const                     { return _ur.y(); }
    T                xLen() const                    { return _ur.x() - _ll.x(); }
    T                yLen() const                    { return _ur.y() - _ll.y(); }
    const XY<T> &    ll() const                      { return _ll; }
    const XY<T> &    ur() const                      { return _ur; }
    bool             valid() const                   { return _ll.x() <= _ur.x() && _ll.y() <= _ur.y(); }
    T                area() const                    { return (_ur.x() - _ll.x()) * (_ur.y() - _ll.y()); }

    // Setters
    void            set(T xLo, T yLo, T xHi, T yHi)  { _ll.setXY(xLo, yLo); _ur.setXY(xHi, yHi); }
    void            setXLo(T xLo)                    { _ll.setX(xLo); }
    void            setYLo(T yLo)                    { _ll.setY(yLo); }
    void            setXHi(T xHi)                    { _ur.setX(xHi); }
    void            setYHi(T yHi)                    { _ur.setY(yHi); }
    void            join(const XY<T> &pt);

    /// String conversion
    operator std::string() const {
        std::ostringstream oss;
        oss <<"Box"<<":";
        oss << "x = [" << xLo() << "," << xHi() << "];";
        oss << "y = [" << yLo() << "," << yHi() << "]:";
        return oss.str();
    }

    // Check if this box contains a given (x, y) coordinate
    template <typename U>
    bool            contain(U x, U y) const          { return ((T)x >= _ll.x() && (T)x <= _ur.x() && (T)y >= _ll.y() && (T)y <= _ur.y()); }

    // Check if this box contains a given point
    template <typename U>
    bool            contain(const XY<U> &p) const    { return ((T)p.x() >= _ll.x() && (T)p.x() <= _ur.x() && (T)p.y() >= _ll.y() && (T)p.y() <= _ur.y()); }

    T               hpwl() const                     { return xHi() - xLo() + yHi() - yLo(); }

    /// Check if this Box is overlapped with another Box
    bool            overlap(const Box<T> &other) const;
    
    /// Make this Box become the union of the original and another box
    void          unionBox(const Box<T> &other); 

    /// Return the offset box
    Box<T>          offsetBox(const XY<T> &origin) const { return Box<T>(xLo() + origin.x(), yLo() + origin.y(), xHi() + origin.x(), yHi() + origin.y()); }
    void            offsetBy(const XY<T> &origin) { setXLo(xLo() + origin.x()); setYLo(yLo() + origin.y()); setXHi(xHi() + origin.x()); setYHi(yHi() + origin.y()); }

    ///Enlarge box
    /// @brief Enlarge the boundary of the box by a number
    /// @param The distance for enlarging
    void        enlargeBy(T dis) { setXLo(xLo() - dis); setYLo(yLo() - dis); setXHi(xHi() + dis); setYHi(yHi() + dis); }
private:
    XY<T>  _ll; // Lower left corner of this box
    XY<T>  _ur; // Upper right corner of this box
};

/// Extend the box to cover the given point
template <typename T>
inline void Box<T>::join(const XY<T> &pt)
{
    _ll.setX(std::min(pt.x(), _ll.x()));
    _ll.setY(std::min(pt.y(), _ll.y()));
    _ur.setX(std::max(pt.x(), _ur.x()));
    _ur.setY(std::max(pt.y(), _ur.y()));
}

template <typename T>
inline bool Box<T>::overlap(const Box<T> &other) const
{
    if (_ll.x() >= other.xHi() || other.xLo() >= _ur.x())
    {
        return false;
    }
    if (_ll.y() >= other.yHi() || other.yLo() >= _ur.y())
    {
        return false;
    }
    return true;
}

template <typename T>
inline void Box<T>::unionBox(const Box<T> &other)
{
    this->setXLo(std::min(this->xLo(), other.xLo()));
    this->setYLo(std::min(this->yLo(), other.yLo()));
    this->setXHi(std::max(this->xHi(), other.xHi()));
    this->setYHi(std::max(this->yHi(), other.yHi()));
}

PROJECT_NAMESPACE_END


#endif // __BOX_H__
