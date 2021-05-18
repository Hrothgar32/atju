#ifndef __RBTREE_H_
#define __RBTREE_H_
#include "node.hpp"
#include <memory>
#include <vector>

///Nagyjából standard és általános piros-fekete fa implementáció.
class RbTree{
    private:
        Node* root;
        Node* minNode;

        /**
         * @brief Privát rekurzív bináris keresőfa beszúrás.
         *
         * A szülőt azért térítjük vissza, hogy meg tudjuk hívni a piros-fekete
         * tulajdonság kijavítására szolgáló fixTreeAfterInsert függvényt.
         *
         * @returns Visszatéríti az újonnan beszúrt csomópont szülőjét.
         **/
        Node* insert(Node* root, Node* newNode);

        /**
         * @brief Kijavítja beszúrás után a piros-fekete tulajdonságot.
         *
         * A kijavítási folyamat tartalmazhat forgatásokat és átszínezéseket,
         * és rotációkat.
         * Mivel minden beszúrt új csomópont piros, ezért leredukálható a probléma az egymást
         * követő piros eset kijavítására.
        * Ha a nagybácsi (a newNode szülőjének testvére) piros, akkor egyszerűen a szülő s a nagybácsi
         * színét feketére állítjuk és a nagyszülőjét pedig pirosra.
         * Fekete esetben 4 eset fordulhat elő:
         * 1. Bal-bal(a szülő a nagyszülő bal gyermeke és a newNode a szülő bal gyermeke):
         *    Végrehajtunk egy jobb forgatást a nagyszülőn, kicseréljük a szülő és nagyszülő színét.
         * 2. Bal-jobb:
         *    Végrehajtunk egy bal forgatást a szülőn, ezután visszatértünk a bal-bal esethez.
         * 3. Jobb-jobb:
         *    Végrehajtunk egy bal forgatást a nagyszülőn, kicseréljük a szülő és a nagyszülő színét.
         * 4. Jobb-bal:
         *    Végrehajtunk egy jobb forgatást a szülőn, ezután visszatértünk a jobb-jobb esethez.
         * A fenti eseteket addig folytatjuk, amíg a newNode paraméter fekete nem lesz, vagy
         * pedig a szülő fekete lesz.
         *
         * @param root A fa gyökere
         * @param newNode Az új beszúrt csomópont.
         **/
        void fixTreeAfterInsert(Node* &root, Node* newNode);

        /**
         * @brief Végrehajt egy bal forgatást a megadott csomóponton.
         *
         * @param root A fa gyökere.
         * @param nodePtr A "megforgatott" csomópont.
         **/
        void rotateLeft(Node*& root, Node*& nodePtr);

        /**
         * @brief Végrehajt egy jobb forgatást a megadott csomóponton.
         *
         * @param root A fa gyökere.
         * @param nodePtr A "megforgatott" csomópont.
         * */
        void rotateRight(Node*& root, Node*& nodePtr);

        /**
         * @brief Megkeresi az x csomópont utódját BST törlés esetén.
         * @param x A csomópont aminek a "leváltóját" keressük.
         * @returns Az x csomópont "leváltója".
         **/
        Node* replacementSearch(Node* x);

        /**
         * @brief Visszatéríti az x csomópont által jelzett al-fa legkisebb elemét.
         * @param x Az x csomópont.
         * @returns Az al-fa legbaloldalibb vagy legkisebb nem-nullptr eleme.
         **/
        Node* successor(Node* x);

        /**
         * @brief Kijavítja a megadott x csúcs "duplafeketeségét".
         *
         * A dupla-fekete javításnál főleg a testvér színét figyeljük.
         * a) Ha a testvér fekete, és van legalább egy piros gyermeke, akkor maximum két
         * forgatással ki lehet javítani a fekete magasságot.
         * b) Ha a testvér fekete és mindkét gyermeke fekete, akkor átszínezzük a testvért
         * pirosra, a szülőt feketére, s ha a szülő duplafekete lesz, meghívjuk rá is
         * a függvényt.
         * c) Ha a testvér piros, akkor átszínezzük feketére, a szülőt pirosra, forgatunk
         * egyet a szülőn attól függően, hogy hol van a testvér, és visszatérünk az
         * a) vagy b) esetre.
         *
         * @param x A csúcs amit "megjavítunk".
         * */
        void fixDoubleBlack(Node* x);
    public:
        RbTree();
        ~RbTree();

        /**
        * @brief Behelyez egy új csomópontot a piros-fekete fába, és frissíti a minimális csomópontot.
        *
        * Az rbInsert függvény először létrehoz egy új csomópontot,
        * majd végrehajt egy standard bináris-keresőfa beszúrást az insert metódussal.
        * utána pedig (ha szükséges) kijavítja az esetleges piros-fekete tulajdonság
        * megsértését a fixTreeAfterInsert privát metódussal.
        *
        * @param key A kulcs, ami alapjan el lesz rendezve a csomópont a keresőfában.
        *
        * @returns Az újonnan létrehozott csomópont.
        * 
        */
        Node* rbInsert(const int& key);

        /**
         * @brief Kivesz egy csomópontot a piros-fekete fából.
         *
         * Először kitörli egy standard BST törléssel, utána pedig,
         * ha fennáll az eset, kijavítja a dupla fekete hibát a fixDoubleBlack
         * függvénnyel.
         * Hívjuk v-nek a törölt csúcsot és u-nak a csúcsot, amivel lecseréljük ezt a
         * törölt csúcsot.
         * A legegyszerűbb eset akkor áll fenn, ha vagy u vagy v piros, ekkor egyszerűen
         * az u csúcsot átszínezzük pirosra.
         * Ha mindkettő csúcs fekete, akkor törlés után (vagy előtt, ha a leváltó nullptr)
         * meghívjuk a fixDoubleBlack függvényt.
         *
         * @param node A törlendő csomópontra mutató pointer.
         */
        void rbDelete(Node* node);

        /**
         * @brief Visszatéríti a fa csomópontjait szint szerinti sorrendben.
         *
         * A getLevelOrder függvény egy várakozási sor segítségével bejárja
         * a piros-fekete fát, szintről-szintre haladva.
         *
         * @returns A fa csomópontjait tartalmazó vektor.
        */
        std::vector<Node*> getLevelOrder();

        /**
         * @brief Visszatéríti a piros-fekete fa gyökerét.
         * @returns A fa gyökerét tartalmazó csomópont.
         * */
        Node* getRoot();

        /**
         * @brief Visszatéríti a fa "key" kulcsú csomópontját, ha létezik.
         * @param key A keresett csomópont kulcsa.
         * @returns A kulcsot tartalmazó csomópont, másképp egy nullptr.
         **/
        Node* search(const int& key);

        /**
         * @brief Kitörli a minimális csomópontot, és visszatéríti a benne levő adatot.
         *
         * @returns A csomópontban levő adatra mutató megosztott mutató.
         * */
        std::shared_ptr<void> popMin();
};

#endif // __RBTREE_H_
