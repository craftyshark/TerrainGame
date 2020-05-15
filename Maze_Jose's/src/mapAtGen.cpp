#include "mapAtGen.h"
#include <CommonThings.h>
#include<string.h>
#include<gl/gl.h>
#include<GL/glut.h>
#include<SOIL.h>
#include<iostream>
#include <Timer.h>
#include <math.h>       /* ceil */
#include <time.h>

//mapAtGen::mapAtGen()
//{
//    //ctor
//}

mapAtGen::~mapAtGen()
{
    //dtor
}


mapAtGen::mapAtGen(){
    BL = Point(0,0);
    TR = Point(0,0);
    n = NULL;
    TLT = NULL;
    TRT = NULL;
    //ayyyeee BLT
    BLT = NULL;
    BRT = NULL;

}

mapAtGen::mapAtGen(Point botL, Point topR){
    n = NULL;

    TLT = NULL;
    TRT = NULL;
    BLT = NULL;
    BRT = NULL;
    BL = botL;
    TR = topR;
}

/*
void mapAtGen::fillItBoys(){

    // we initialize an N but this till change.
    //first things first, house rules
    //okay, we're gonna modify the insert function. You see the insert function has this little inBounds check.
    // if we remove that, once we arrive at a place that has a single unit area, we can add our data, which till be a number which determines what we
    //want a certain tile to be. Oh my god I may have figured this out.


    BLT = new mapAtGen(Point(BL.x, BL.y), Point( ((BL.x + TR.x) / 2) , ( (BL.y + TR.y) / 2) ) );
    TLT = new mapAtGen(Point(BL.x, ((BL.y + TR.y ) / 2)), Point( ((BL.x + TR.x) / 2),TR.y) );
    BRT = new mapAtGen(Point (((BL.x + TR.x) / 2), BL.y), Point ( TR.x, ( (BL.y + TR.y) / 2 ) ) );
    TRT = new mapAtGen(Point ( ((BL.x + TR.x) / 2) , ((BL.y + TR.y) / 2) ), Point ( TR.x , TR.y));
    //we're gonna send these trees off to new places
    //we're gonna go through each and every one of them, seeding each area of the map, you'll see what I mean.


    BLT->insertMod(1);

    TLT->insertMod(2);
    BRT->insertMod(3);
    TRT->insertMod(4);

}

bool mapAtGen::inQuad(){

}

*/

/*
void mapAtGen::finalInsert(int seed, Point(x,y)){

    //if ( abs(BL.x - TR.x) < 1 && abs(BL.y - TR.y) < 1){

        //                  ^                           ^ the only times these are at or less than 1, is if theres only one leaf that which we are on.
        //if(n == NULL)
        //{


            int dice = rand() % 8 + 1;
            //int dicey = rand() % 4 + 1;

            if(dice != seed){
                seed = dice;
            }

            Node g(Point(BL.x,BL.y), seed);

            n = &g;
            cout << n->data << endl;


        //} // is this the correct way to indent here?, it's a mysteryyyy
        //return;

       // }
   // }
}
*/

/*
void mapAtGen::insertMod(int seed){

    cout << BL.x << "," << BL.y << endl;
    cout << TR.x << "," << TR.y << endl;

    if(n != NULL){
        return;
    }

    //if (!inBounds(Point (0,0))){
    //    return; // = yeet
    //}


    //int d = n->data;

    /*
    if ( abs(BL.x - TR.x) < 1 && abs(BL.y - TR.y) < 1){

        //                  ^                           ^ the only times these are at or less than 1, is if theres only one leaf that which we are on.
        if(n == NULL)
        {


            int dice = rand() % 8 + 1;
            //int dicey = rand() % 4 + 1;

            if(dice != seed){
                seed = dice;
            }

            Node g(Point(BL.x,BL.y), seed);

            n = &g;
            cout << n->data << endl;


        //} // is this the correct way to indent here?, it's a mysteryyyy
        return;

        }
    }



    if(BLT == NULL){
        cout << "i ran this many" << endl;
        if(abs(BL.x - TR.x) <= 1 && abs(BL.y - TR.y) <= 1){
            BLT = new mapAtGen(Point (BL.x, BL.y), Point(BL.x,BL.y));
            TLT = new mapAtGen (Point (BL.x, (TR.y)), Point (BL.x, TR.y)) ;
            BRT = new mapAtGen(Point (TR.x, BL.y), Point(TR.x, BL.y));
            TRT = new mapAtGen(Point (TR.x, TR.y), Point (TR.x, TR.y));
            BLT->finalInsert(seed);
            TLT->finalInsert(seed);
            BRT->finalInsert(seed);
            TRT->finalInsert(seed);


            return;
        }else{
            BLT = new mapAtGen(Point(BL.x, BL.y), Point( ((BL.x + TR.x) / 2) , ( (BL.y, TR.y) / 2) ) );
            BLT->insertMod(seed);
        }



    }

    cout << "blt done" << endl;
    cout << BL.x << "," << BL.y << endl;
    cout << TR.x << "," << TR.y << endl;

    if(TLT == NULL){

        if(abs(BL.x - TR.x) <= 1 && abs(BL.y - TR.y) <= 1){
            BLT = new mapAtGen(Point (BL.x, BL.y), Point(BL.x,BL.y));
            TLT = new mapAtGen (Point (BL.x, (TR.y)), Point (BL.x, TR.y)) ;
            BRT = new mapAtGen(Point (TR.x, BL.y), Point(TR.x, BL.y));
            TRT = new mapAtGen(Point (TR.x, TR.y), Point (TR.x, TR.y));
            BLT->finalInsert(seed);
            TLT->finalInsert(seed);
            BRT->finalInsert(seed);
            TRT->finalInsert(seed);


            return;
        }else{
            TLT = new mapAtGen(Point(BL.x, ((BL.y + TR.y ) / 2)), Point( ((BL.x + TR.x) / 2),TR.y) );
            TLT->insertMod(seed);
        }
    }

    cout << "tlt done" << endl;

    if(BRT == NULL){

        if(abs(BL.x - TR.x) <= 1 && abs(BL.y - TR.y) <= 1){
            BLT = new mapAtGen(Point (BL.x, BL.y), Point(BL.x,BL.y));
            TLT = new mapAtGen (Point (BL.x, (TR.y)), Point (BL.x, TR.y)) ;
            BRT = new mapAtGen(Point (TR.x, BL.y), Point(TR.x, BL.y));
            TRT = new mapAtGen(Point (TR.x, TR.y), Point (TR.x, TR.y));
            BLT->finalInsert(seed);
            TLT->finalInsert(seed);
            BRT->finalInsert(seed);
            TRT->finalInsert(seed);


            return;
        }else{
            BRT = new mapAtGen(Point (((BL.x + TR.x) / 2), BL.y), Point ( TR.x, ( (BL.y + TR.y) / 2 ) ) );
            BRT->insertMod(seed);
        }
    }

    if(TRT == NULL){



        if(abs(BL.x - TR.x) <= 1 && abs(BL.y - TR.y) <= 1){
            BLT = new mapAtGen(Point (BL.x, BL.y), Point(BL.x,BL.y));
            TLT = new mapAtGen (Point (BL.x, (TR.y)), Point (BL.x, TR.y)) ;
            BRT = new mapAtGen(Point (TR.x, BL.y), Point(TR.x, BL.y));
            TRT = new mapAtGen(Point (TR.x, TR.y), Point (TR.x, TR.y));
            BLT->finalInsert(seed);
            TLT->finalInsert(seed);
            BRT->finalInsert(seed);
            TRT->finalInsert(seed);


            return;
        }else{
            TRT = new mapAtGen(Point ( ((BL.x + TR.x) / 2) , ((BL.y + TR.y) / 2) ), Point ( TR.x , TR.y));
            TRT->insertMod(seed);
        }
    }





i hate myself, so much, for not figuring out how this works.












}

*/



void mapAtGen::insert(Node *node){
    //Don't submit empty nodes, obviously.
    if(node == NULL){
        return;
    }


    //if there isn't enough space in this Quad Tree, this little function right here will yeet it.
    if (!inBounds(node->pos)){
        return; // = yeet
    }

    //we're at the single quads with no kids
    // basically see these 1's right here?                v
    if ( (abs(BL.x - TR.x) <= 1) && (abs(BL.x - TR.y)) <= 1 ){
        //                  ^                           ^ the only times these are at or less than 1, is if theres only one leaf that which we are on.
        if(n == NULL){
            n = node;
        } // is this the correct way to indent here?, it's a mysteryyyy
        return;
    }

    //first we check if we are on the left or right, if left we take the if, if right we take the else.
    if ( ( (BL.x + TR.x) / 2 ) >= node->pos.x ){
        //then we'll check if it's on the top or bottom. if statement is for BL else is for TL
        if ( ((BL.y + TR.y ) / 2) >= node->pos.y ){
            if (BLT == NULL){
                BLT = new mapAtGen(Point(BL.x, BL.y), Point( ((BL.x + TR.x) / 2) , ( (BL.y + TR.y) / 2) ) );

            }
            BLT->insert(node);
        }else{
            if(TLT == NULL){
                TLT = new mapAtGen(Point(BL.x, ((BL.y + TR.y ) / 2)), Point( ((BL.x + TR.x) / 2),TR.y) );
            }
            TLT->insert(node);
        }

    }else{
        //guess were on the right side bois, now we check if it's a top or bottom
        if( ( (BL.y + TR.y) / 2) >= node->pos.y){
            if(BRT == NULL){
                BRT = new mapAtGen(Point (((BL.x + TR.x) / 2), BL.y), Point ( TR.x, ( (BL.y + TR.y) / 2 ) ) );
            }
            BRT->insert(node);
        }else{
            if(TRT == NULL){
                TRT = new mapAtGen(Point ( ((BL.x + TR.x) / 2) , ((BL.y + TR.y) / 2) ), Point ( TR.x , TR.y));
            }TRT->insert(node);
        }
    }
}

bool mapAtGen::inBounds(Point p){
    return (p.x >= BL.x && p.x <= TR.x && p.y >= BL.y && p.y <= TR.y);

}

Node* mapAtGen::search(Point p){

    //not in here, YEET
    if (!inBounds(p)){
        return NULL;
    }

    //I GOT UR NODE
    if ( n != NULL){
        return n;
    }

    //ight my dude, check it. First thing's first we're gonna decide if we're dealing with the left or right side of the quad
    if ( ((BL.x + TR.x) / 2) >= p.x){
        //then, we decide if it's a top or bottom.
        //this guy's a bottom
        if ( ((BL.y + TR.y) / 2 ) >= p.y){
            if(BLT == NULL){
                return NULL;
            }
            return BLT->search(p);
        }

        //this guy here's a top
        else
        {
            if(TLT == NULL){
                return NULL;
            }
            return TLT->search(p);
        }
        //flipy flopy, you get it. BRT and TRT below
    }else{
        if( ((BL.y + TR.y) / 2) >= p.y){
            if(BRT == NULL){
                return NULL;
            }
            return BRT->search(p);
           }else{
                if(TRT == NULL){
                    return NULL;
                }
                return TRT->search(p);
           }
    }

}



