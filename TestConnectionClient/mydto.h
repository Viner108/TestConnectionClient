#ifndef MYDTO_H
#define MYDTO_H

#include <QDataStream>

class MyDTO {
public:
    double x;
    double y;

    MyDTO() : x(0), y(0) {}
    MyDTO(double x, double y) : x(x), y(y) {}

    friend QDataStream& operator<<(QDataStream& out, const MyDTO& dto) {
        out << dto.x << dto.y;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, MyDTO& dto) {
        in >> dto.x >> dto.y;
        return in;
    }
};

#endif // MYDTO_H
