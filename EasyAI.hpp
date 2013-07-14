#ifndef __EASYAI_HPP__
#define __EASYAI_HPP__

#include "APlayer.hpp"

namespace QAwale {
    namespace Core {
        class EasyAI : public APlayer {
            Q_OBJECT

        public:
            EasyAI(unsigned int number, const QString& name);

            virtual int play(const Gameboard &state);

        private:
            static const unsigned int DEPTH;

            unsigned int _firstHoleNumber;
            unsigned int _lastHoleNumber;

            int min(const Gameboard& state, unsigned int depth, int playerTaking, int opponentTaking) const;
            int max(const Gameboard& state, int depth, int playerTaking, int opponentTaking) const;
        };
    }
}
#endif // __EASYAI_HPP__
