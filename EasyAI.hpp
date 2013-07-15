#ifndef __EASYAI_HPP__
#define __EASYAI_HPP__

#include "AI.hpp"

namespace QAwale {
    namespace Core {
        class EasyAI : public AI {
            Q_OBJECT

        public:
            EasyAI(unsigned int number, const QString& name);

            virtual int play(const Gameboard &state);

        private:
            static const unsigned int EASY_AI_DEPTH = 6;

            virtual int min(Gameboard state, unsigned int depth, unsigned int playerTaking, unsigned int opponentTaking) const;
            virtual int max(Gameboard state, unsigned int depth, unsigned int playerTaking, unsigned int opponentTaking) const;
        };
    }
}
#endif // __EASYAI_HPP__
