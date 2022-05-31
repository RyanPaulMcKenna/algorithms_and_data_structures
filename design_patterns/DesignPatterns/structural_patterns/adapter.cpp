#include <math.h>

class SquarePeg {
    private:
        int width;
    public:
        SquarePeg(int w): width(w) {}
        int getWidth() {
            return width;
        }
};
class RoundPeg {
    private:
        int radius;
    public:
        RoundPeg(): radius(0) {}
        RoundPeg(int r): radius(r) {}
        int getRadius() {
            return radius;
        }
};
class RoundHole {
    private:
        int radius;
    public:
        RoundHole(int r): radius(r) {}
        int getRadius() {
            return radius;
        }
        bool fits(RoundPeg peg) {
            return (peg.getRadius() <= radius);
        }
};

class SquarePegAdapter: public RoundPeg {
    private:
        SquarePeg peg;
    public:
        SquarePegAdapter(SquarePeg peg): peg(peg) {}
        int getRadius() {
            return peg.getWidth()*sqrt(2)/ 2;
        }
};

