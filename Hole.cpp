#include "Hole.hpp"

namespace QAwale {
    namespace Core {
        Hole::Hole(int number) : _number(number), _seedCount(4) {}

        Hole::Hole(const Hole &source) {
            _seedCount = source._seedCount;
            _number = source._number;
        }

        Hole& Hole::operator =(const Hole& source) {
            _seedCount = source._seedCount;
            _number = source._number;
            return *this;
        }
    }
}
