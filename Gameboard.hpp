#ifndef __GAMEBOARD_HPP__
#define __GAMEBOARD_HPP__

#include <QtCore/QMetaType>
#include <QtCore/QVector>

namespace QAwale {
    namespace Core {
        class Hole;
    }
}

namespace QAwale {
    namespace Core {
        class Gameboard {
        public:
            Gameboard();
            Gameboard(const Gameboard& source);

            virtual ~Gameboard();

            Gameboard& operator=(const Gameboard& source);
            bool operator ==(const Gameboard& other) const;
            bool operator !=(const Gameboard& other) const;

            bool isGameEnded() const;

            int simulate(int position, Gameboard finalState) const;

            int play(int position);

            inline int getHoleSeedCount(int holeNumber) const;

        private:
            QVector<Hole*> _holes;

            void clearHoles();

            static const unsigned int DEFAULT_HOLE_COUNT;
        };

        inline int Gameboard::getHoleSeedCount(int holeNumber) const {
            return _holes[holeNumber]->seedCount();
        }
    }
}

Q_DECLARE_METATYPE(Gameboard)

#endif // __GAMEBOARD_HPP__
