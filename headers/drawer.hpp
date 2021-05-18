#ifndef __DRAWER_H_
#define __DRAWER_H_
#include <graphics.h>
#include "rbtree.hpp"
#include <memory>
#include <mutex>
#include <task.hpp>
#define HEIGHT 768
#define WIDTH 1024

/// Az információk megjelenítésért felelős osztály.
class Drawer{
    private:
        RbTree* tree;
        std::mutex* mutex;
        /// Az éppen háttérben futó folyamat.
        std::shared_ptr<Task> currentTask;
        int gd;
        int gm;
        int window;
        bool shouldDraw;
        bool reDraw;
        /**
         * @brief A rajzolómetódus.
         *
         * Lerajzolja a piros-fekete aktuális állapotát jelezve a csomópontokban
         * az eltelt időt amennyit futott a jelzett folyamat, és a folyamat PID-jét.
         * A képernyő alján ugyanakkor kiírja, hogy éppen melyik folyamat fut.
         **/
        void draw();

        /**
         * @brief Átkonvertálja az almtree névtérben levő színt a graphics.h színére.
         * @param color Egy szín az almtree névtérből (vagy piros vagy fekete).
         * @returns A graphics.h COLOR enumjának egy tagja (vagy piros vagy fekete).
         **/
        int treeCToGraphicsC(almtree::COLOR color);
    public:
        Drawer(RbTree* tree, std::mutex* mutex);
        ~Drawer();

        /**
         * @brief Inicializálja a rajzolási felületet.
         **/
        void init();

        /**
         * @brief A rajzolást vezérlő runnable függvény.
         *
         * Addig fut, amíg a shouldDraw változó értéke true.
         * Akkor rajzoltat, ha a reDraw értéke true.
         **/
        void drawRunnable();

        /**
         * @brief Megállítja a rajzolási folyamatot.
         **/
        void disableDraw();

        /**
         * @brief Újrarajzolja a piros-fekete fa állapotát.
         **/
        void callReDraw();

        /**
         * @brief Beállítja az éppen futó folyamatot.
         **/
        void setRunningTask(std::shared_ptr<Task> currentTask);
};


#endif // __DRAWER_H_
