#ifndef MAPATGEN_H
#define MAPATGEN_H




//in my mapAtGen, I will randomly create attributes for each node.
//First, we fill them with BS such that we can create the structure for the quad tree.
// then, we'll seed the TL and BR corners to fill each node with the actual data.

struct Point{       //holds the position data of a point.
    int x;
    int y;
    Point(int X, int Y){
        x = X;
        y = Y;
    }
    Point(){
        x=0;
        y=0;
    }
};

struct Node{
    Point pos;
    int data;
    Node(Point Pos, int Data){
        pos = Pos;
        data = Data;
    }
    Node(){
        data=0;
    }
};

class mapAtGen
{
    public:
        mapAtGen();
        mapAtGen(Point botL, Point topR);            //el constructor
        virtual ~mapAtGen();

        //For now we're going to implement the most critical parts of a quadtree, May9th. If there's time we'll implement shortest path alg.
        void insert(Node*);
        Node* search(Point);
        bool inBounds(Point);
        void insertMod(int seed);
        void finalInsert(int seed);
        bool inQuad();

        void fillItBoys();
        void fillItBoys(mapAtGen(Point botL, Point topR));
        // this, this right here is where the magic happens.
        // This project might be trash, but I want to be proud of this.






    protected:

    private:

        // our BL and TR bounds for the grid.
        // "Jose, don't most Quadtrees use the top left and bottom right points for the bounds?"

        /*
        Yes
        but our graph is like this
                8,8

        0,0
        instead of this
        0,0

                8,8
        I'm incredibly behind and couldn't be bothered to figure out how to flip it.

        */

        Point BL;
        Point TR;

        //declaration for Node, here's where the data of what kind of terrain this point is
        Node *n;
        //these little guys here are the children of the current tree we're on.
        //They'll be useful in a sec during procedural gen
        mapAtGen *TLT;
        mapAtGen *TRT;
        mapAtGen *BLT;
        mapAtGen *BRT;
};



#endif // MAPATGEN_H
