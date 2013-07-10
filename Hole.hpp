#ifndef __HOLE_HPP__
#define __HOLE_HPP__

#include <QtCore/QMetaType>

namespace QAwale {
    namespace Core {
        class Hole {
        public:
            Hole(int number = -1);
            Hole(const Hole& source);

            Hole& operator=(const Hole& source);

            inline int seedCount() const;
            inline int playerNumber() const;
            inline int number() const;

            inline void seedCount(int amount);

        private:
            int _number;
            int _seedCount;
        };

        inline int Hole::seedCount() const {
            return _seedCount;
        }

        inline int Hole::playerNumber() const {
            return _number < 6 ? 1 : 2;
        }

        inline int Hole::number() const {
            return _number;
        }

        inline void Hole::seedCount(int amount) {
            _seedCount = amount;
        }

        Q_DECLARE_METATYPE(Hole)
    }
}


#endif // __HOLE_HPP__
