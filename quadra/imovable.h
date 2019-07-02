#ifndef IMOVABLE_H
#define IMOVABLE_H

class IMovable{
public:
    enum Direction {
        kDirectionDown,
        kDirectionRight,
        kDirectionLeft,
        kDirectionUp
    };

public:
    virtual ~IMovable() {}
    virtual void move(Direction) = 0;
};

};

#endif // IMOVABLE_H
