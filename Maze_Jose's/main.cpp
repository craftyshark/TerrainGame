/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */

 //JOSE'S

#include <string.h>
#include <CommonThings.h>
#include <Maze.h>
#include <iostream>
#include <Timer.h>
#include <player.h>
#include <cmath>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

#include <wall.h>

#include <math.h>
#include <bits/stdc++.h>
#include <mapAtGen.h>
#include <time.h>




/* GLUT callback Handlers */

using namespace std;

const int S = 16;                                   //grid size, got tired of rewriting.
Maze *M = new Maze(16);                      // Set Maze grid size

Player *P = new Player();

Player *Player1 = new Player();                    // create player
Player *Fish= new Player();                  // Fish
Player *Frog = new Player();                //Frog
Player *Bird = new Player();                //



int MAPIE[16][16];                          // our sad grid we made because we couldn't figure out how to fill quad trees
int dice = rand() % 8 + 1;                  // random number 1-8



int seed = 0;
int reseed = 0;


int d4 = rand() % 4 + 1;


string grid[S][S];                        // later on find a varaable to set to the grid size so we can change it on the fly

wall W[100];                                 // wall with number of bricks

wall HighM[100];                            //High Mountains
wall MiddleM[100];                          //middle mountains
wall FHills[100];                           //FootHills
wall Plain[100];                            // Plain Jane
wall Forest[100];                           //Forests
wall Desert[100];                           //Desert
wall Beach[100];                            // Beach
wall Ocean[100];                            //Ocean

int totHM = 0;                              //keeps track of total High Mountains.
int totMM = 0;                              // keep's track of how many Middle Mountains
int totFH = 0;                              // keep's track of how many FootHills
int totPL = 0;                              // keep's track of how many Plains
int totFOR = 0;                             // keep's track of how many Forests
int totDES = 0;                             // keep's track of how many Deserts
int totB = 0;                               // keep's track of how many Beaches
int totO = 0;                               // keep's track of how many Oceans




wall H[100];                                 //we'll modify this to show where we've already stepped, lmao no were not
//

Timer *T0 = new Timer();                     // animation timer

Timer *T1 = new Timer();                     // animation timer


float wWidth, wHeight;                       // display window width and Height
int xPos,yPos;                               // Viewport mapping
string dir[100];                              // this is our array where we will store stepped
int counter = 0;                             // a county boi

int desX, desY;                              //a destination on the matrix we plan to go to
int startX, startY;                          // we use this to help determine which Character is being selected
int steps = 0;
bool playerSelected = false;                 //player we are selecting, set this to true for one char at a time.



void display(void);                          // Main Display : this runs in a loop
void playerActions();                        // ?

//struct Point{       //holds the position data of a point.
//    int x;
//    int y;
//    Point(int X, int Y){
//        x = X;
//        y = Y;
//    }
//    Point(){
//        x=0;
//        y=0;
//    }
// };

/* struct Node{
    Point pos;
    string data;
    Node(Point Pos, string Data){
        pos = Pos;
        data = Data;
    }
    Node(){
        data="empty";
    }
}; */


void resize(int width, int height)           // resizing case on the window
{
    wWidth = width;
    wHeight = height;

    if(width<=height)
        glViewport(0,(GLsizei) (height-width)/2,(GLsizei) width,(GLsizei) width);
    else
        glViewport((GLsizei) (width-height)/2 ,0 ,(GLsizei) height,(GLsizei) height);
}

void init()
{
    glEnable(GL_COLOR_MATERIAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.0,0.0,0.0,0.0);

    glEnable(GL_COLOR_MATERIAL);
    gluOrtho2D(0, wWidth, 0, wHeight);

    T0->Start();                                        // set timer to 0

    T1->Start();                                        // set timer to 0


    glEnable(GL_BLEND);                                 //display images with transparent
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //M->loadBackgroundImage("images/bak.jpg");           // this is no longer needed

    Player1->initPlayer(M->getGridSize(),"images/p.png",6);   // initialize player pass grid size,image and number of frames
    Player1->placePlayer(6,0);                                // Place player

    Fish->initPlayer(M->getGridSize(),"images/fish.png",4);   // initialize player pass grid size,image and number of frames
    Fish->placePlayer(0,0);                                   // Place player

    Frog->initPlayer(M->getGridSize(), "images/frog.png",6);  // initialize player pass grid size,image and number of frames
    Frog->placePlayer(7,7);                                   // Place player

    Bird->initPlayer(M->getGridSize(), "images/bird.png", 4);   // initialize player pass grid size,image and number of frames
    Bird->placePlayer(12,12);                                   // Place player


    //Node a(Point(0,0), 1);
    //Tree->insert(&a);
    //Node b(Point(8,8), 2);
    //Tree->insert(&b);
    //cout << Tree->search(Point(0,0))->data << endl;

    mapAtGen *Tree = new mapAtGen(Point (0,0), Point(15,15));       // set quad size, this is my failed quad trees. It's trash.
    //Tree->fillItBoys();


    cout << "pls pick a seed number 1-8" << endl;  // this allows for 8 different seeds and technically infinite maps?
    cin >> seed;                                    // seed go here
    reseed = seed;

    //loops through all points and based on starting seed randomly generates terrain. Not procedurally :(
    for(int i = 0; i < 16; i++){
            seed = reseed;
        for(int j = 0; j < 16; j++){


            //remeber that dice roll? This will be come important.
            //dice selects a random number between 1-8
            dice = rand() % 8 + 1;
            d4 = rand() % 4 + 1;


            //then there is a dice roll of a 4 sided dice. If it's 1, then we change the seed to whatever the dice was
            //this means there's a 75% chance that we will get the same seed, meaning if we had set up quad trees to use this
            // we would have been able to make terrain that looked nice, usually with groups of 4-6 pieces of the same kind of land.
            if(d4 == 1){
                seed = dice;
            }

            //this is just a sanity check. Helps debug when when of the terrain tiles doesn't want to display.
            cout << i << "," << j << " " << seed << endl;
            MAPIE[i][j] = seed;





            //Node g(Point(i,j), seed);
            //Tree->insert(&g);
            //n = &g;

            //cout << i << "," << j << seed << endl;
        }

    }




    //SO, after giving a value to each point in a 2d matrix, we use that matrix to initialize where the different pieces of land goes.
    // go to glScene Display to see how they're then drawn.
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            switch(MAPIE[i][j])
            {
            case 1:
                HighM[totHM].wallInit(M->getGridSize(),"images/high_m.png");  // load terrain
                HighM[totHM].placeWall(i,j);                                 // place terrain
                totHM++;                                                    // add to how many of this kind of terrain we have. This will be important when we draw all of this.
            break;
            case 2:
                MiddleM[totMM].wallInit(M->getGridSize(), "images/middle_m.png");   // load terrain
                MiddleM[totMM].placeWall(i,j);                                     // place terrain
                totMM++;                                                          // add to how many of this kind of terrain we have. This will be important when we draw all of this.
            break;
            case 3:
                FHills[totFH].wallInit(M->getGridSize(), "images/foot_hills.png");  // load terrain
                FHills[totFH].placeWall(i,j);                                      // place terrain
                totFH++;                                                          // add to how many of this kind of terrain we have. This will be important when we draw all of this.
            break;
            case 4:
                Plain[totPL].wallInit(M->getGridSize(), "images/plains.png");      // load terrain
                Plain[totPL].placeWall(i,j);                                      // place terrain
                totPL++;                                                         // add to how many of this kind of terrain we have. This will be important when we draw all of this.
            break;
            case 5:
                Forest[totFOR].wallInit(M->getGridSize(), "images/forest.png");     // load terrain
                Forest[totFOR].placeWall(i,j);                                     // place terrain
                totFOR++;                                                         // add to how many of this kind of terrain we have. This will be important when we draw all of this.
            break;
            case 6:
                Desert[totDES].wallInit(M->getGridSize(), "images/desert.png");     // load terrain
                Desert[totDES].placeWall(i,j);                                     // place terrain
                totDES++;                                                         // add to how many of this kind of terrain we have. This will be important when we draw all of this.
            break;
            case 7:
                Beach[totB].wallInit(M->getGridSize(), "images/beach.png");      // load terrain
                Beach[totB].placeWall(i,j);                                     // place terrain
                totB++;                                                        // add to how many of this kind of terrain we have. This will be important when we draw all of this.
            break;
            case 8:
                Ocean[totO].wallInit(M->getGridSize(), "images/ocean.png");      // load terrain
                Ocean[totO].placeWall(i,j);                                     // place terrain
                totO++;                                                        // add to how many of this kind of terrain we have. This will be important when we draw all of this.
            break;

            default:
            break;
            }

            //cout << i << "," << j << seed << endl;
        }

    }




    /*
    for(int i=0; i< M->getGridSize(); i++)
    {
      HighM[i].wallInit(M->getGridSize(),"images/high_m.png");// Load wall
      HighM[i].placeWall(i,6);                              // place each brick

      //H[i].wallInit(M->getGridSize(),"images/wall.png");// Load walls

      //H[i].placeWall(-1,-1);
    }
    HighM[5].placeWall(0,2);                                // moved 5th brick away
    */

}

void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT);        // clear display screen

        glPushMatrix();
         M->drawBackground();           // Display Background
        glPopMatrix();



        for(int i=0; i<M->getGridSize();i++)
        {
           W[i].drawWall();
           //H[i].drawWall();
        }


        /*
        So here's how the next few lines of .drawWall work
        First we create a for loop, looping through the total number number of tiles we have for the
        specified type of terrain
        then, we draw each wall, one by one, which should already have a specified location on the grid at this point.
        rinse and repeat for the other 7 types of terrain.
        */

        for(int i = 0; i < totHM; i++){
            HighM[i].drawWall();

        }

        for(int i = 0; i < totHM; i++){

            MiddleM[i].drawWall();
        }

        for(int i = 0; i < totFH; i++){
            FHills[i].drawWall();
        }

        for(int i = 0; i < totPL; i++){
            Plain[i].drawWall();
        }

        for(int i = 0; i < totFOR; i++){
            Forest[i].drawWall();
        }

        for(int i = 0; i < totDES; i++){
            Desert[i].drawWall();

        }

        for(int i = 0; i < totB; i++){
            Beach[i].drawWall();
        }

        for(int i = 0; i < totO; i++){
            Ocean[i].drawWall();
        }



        glPushMatrix();
            M->drawGrid();              // Draw the grid
        glPopMatrix();

        glPushMatrix();
             P->drawArrow();           // Draw Player move actions? , I don't think so
        glPopMatrix();

        glPushMatrix();
             Player1->drawplayer();           // drawplayer here.
        glPopMatrix();

        glPushMatrix();
             Fish->drawplayer();            // draw fish
        glPopMatrix();

        glPushMatrix();
            Frog->drawplayer();             // draw frogy
        glPopMatrix();

        glPushMatrix();
            Bird->drawplayer();             // draw a bird.
        glPopMatrix();

        /*
        glPushMatrix();
            playerActions();
        glPushMatrix();
        */

    glutSwapBuffers();
}

void playerActions()
{
     // Your path code is here
     // here is player moving example
     if(Player1->action ==1)
     {Player1->movePlayer("up",6);
    // Sample of how to get player location
    //(remove this after you figure it out)
    // print only when you moving up
   // cout<<"Player Location  :  "<<P->getPlayerLoc().x<< "    "<<P->getPlayerLoc().y<<endl;
     }
     else if(Player1->action ==2)Player1->movePlayer("down",6);
     else if(Player1->action ==3)Player1->movePlayer("left",6);
     else if(Player1->action ==4)Player1->movePlayer("right",6);
     else Player1->movePlayer("stand",6);
}

void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case ' ':
             P->shootArrow();           // Shoot (optional )
        break;
        case 27 :                       // esc key to exit
        case 'q':
            exit(0);
            break;
    }
    glutPostRedisplay();
}


 void GetOGLPos(int x, int y)          // Mouse map coordinates
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );

    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

    xPos =(int) (posX *M->getGridSize()/2 +M->getGridSize()/2); // update mouse position X
    yPos =(int) (posY *M->getGridSize()/2 +M->getGridSize()/2); // updoot mouse pos y, these let the program know where our mouse is


    cout<<"Mouse Click location : "<< xPos<<" "<<yPos <<endl;   // print out grid value
}


void movePlayer(Player *ply, string dir, int frames)
{
    char *buf = new char[dir.length()];
    strcpy(buf, dir.c_str());

    if(ply->steps > ply->unitWidth)
    {
        ply->steps =0;
        strcpy(buf,"stand");
        ply->placePlayer(ply->getPlayerLoc().x,ply->getPlayerLoc().y);

        if( T1->GetTicks()>500)
        {
            counter++;
            T1->Reset();
        }


    }
    else
        {if(ply->activePlayer)
            ply->movePlayer(buf, frames);

        delete []buf;

        }

}

 void idle(void)
{
   //Your Code in this section
    if(T0->GetTicks()>30 && counter < 40)
      {

          //IF AND ONLY IF a player is selected, after we generate steps for a player down there a few lines in void mouse
          //those steps are then sent here
          // we pass through the player, the steps and how many, and the frames each sprite needs.
          movePlayer(Player1,dir[counter],6);
          movePlayer(Fish,dir[counter],4);
          movePlayer(Frog, dir[counter], 6);
          movePlayer(Bird, dir[counter], 4);

         T0->Reset();
      }
    glutPostRedisplay();
}


void mouse(int btn, int state, int x, int y){

    switch(btn){
        case GLUT_LEFT_BUTTON:
                // yeet the array into this area somewhere after the path is built
        if(state==GLUT_DOWN){


              // we did PLAN on making shortest path happen but I got bogged down trying to make quadtrees work right
              // so instead we opped to make a very very simple movement pattern
              GetOGLPos(x,y);
              // so first thing's first we select a player here. If there's a char under the mouse coursor when we left click, that one becomes active.
              // obviously that also means we have to make the rest inactive.
              // rise and repeat for each player.
              // "Jose, why didn't try to automate this?" I spent 4 entire days trying to get quad trees to be automated.
              // sometimes it's best to just do things yourself.
              if(xPos==Player1->getPlayerLoc().x && yPos== Player1->getPlayerLoc().y) // select player?, specifically P
              {
                  Player1->activePlayer=true;
                  Fish->activePlayer= false;
                  Frog->activePlayer = false;
                  Bird->activePlayer = false;
                  playerSelected = true;
              }
              if(xPos==Fish->getPlayerLoc().x && yPos== Fish->getPlayerLoc().y) // select player?, specifically P1?
              {
                  Fish->activePlayer=true;
                  Player1->activePlayer= false;
                  Frog->activePlayer=false;
                  Bird->activePlayer = false;
                  playerSelected = true;
              }
              if(xPos==Frog->getPlayerLoc().x && yPos== Frog->getPlayerLoc().y) // select player?, specifically P1?
              {
                  Frog->activePlayer=true;
                  Player1->activePlayer= false;
                  Fish->activePlayer = false;
                  Bird->activePlayer = false;
                  playerSelected = true;
              }
              if(xPos==Bird->getPlayerLoc().x && yPos== Bird->getPlayerLoc().y){
                  Bird->activePlayer = true;
                  Player1->activePlayer = false;
                  Fish->activePlayer = false;
                  Frog->activePlayer = false;
                  playerSelected = true;
              }

             }
            break;


      case GLUT_RIGHT_BUTTON:

        if(state==GLUT_DOWN){

              GetOGLPos(x,y);

              //ALRIGHTY THEN. So if a player is selected, when you right click, we'll save those coordinates
              if(playerSelected){
              desX = xPos;  //destination select, clearly
              desY = yPos;



              //we save the starting location of whatever character we are about to move.
              //this will be used to direct movement.
              if(Fish->activePlayer == true){           //fish moves
                startX = Fish->getPlayerLoc().x;
                startY = Fish->getPlayerLoc().y;
              }else if(Player1->activePlayer == true){      // player1 moves
                startX = Player1->getPlayerLoc().x;
                startY = Player1->getPlayerLoc().y;
              }else if(Frog->activePlayer == true){         // Frogy moves
                startX = Frog->getPlayerLoc().x;
                startY = Frog->getPlayerLoc().y;
              }else if(Bird->activePlayer == true){        //Bird moves
                startX = Bird->getPlayerLoc().x;
                startY = Bird->getPlayerLoc().y;
              }


                //steps needs to be reset to 0 everytime,
                //otherwise you get really weird movement
              steps = 0;




              while((desX != startX) || (desY != startY) ){         // if we are not yet at the correct x or y, generate steps for dir
                  //just set up basic + and - to get things going
                  //cout << "here" << endl;

                  cout << startX << "," << startY << endl;
                  if(desX < startX){                // if the final x is smaller than the current x
                      dir[steps] = "left";          // move to the left
                      startX--;                     // change current x pos
                      cout << dir[steps] << endl;
                      steps++;                         // add to how many steps will be made
                  }else if(desX > startX){            // if the final y is larger than the current y
                      dir[steps] = "right";          // move to the right
                      startX++;                      // change current x pos
                      cout << dir[steps] << endl;
                      steps++;                         // add to how many steps will be made
                  }


                  if (desY < startY){               // if the final y is smaller than the current y
                    dir[steps] = "down";            // move down
                    startY--;                       // change current y  position
                    //cout << dir[steps] << endl;
                    steps++;                        // add to how many steps will be made
                  }else if(desY > startY){          // if the final y is larger than the current y
                    dir[steps] = "up";             // move up
                    //cout << dir[steps] << endl;
                    startY++;                      // change current y pos
                    steps++;                        // add to how many steps will be made
                  }

              }


              // once we are done generating steps, clear out what is beyond that number of steps in dir
              // left overs from the last movement will cause unexpected movement otherwise.
              for(int i = (steps); i < 100; i++){
                    //cout << "here" << endl;
                dir[i] = "";
              }




                /*
              dir[0] = "up";
              dir[1] = "up";
              dir[2] = "up";
              dir[3] = "right";
              dir[4] = "right";
              dir[5] = "down";
              dir[6] = "left";
              dir[7] = "stand";
            */

                //reset counter to zero.
              counter = 0;

              // playerSelected = false;
              }
            }
            break;
    }
     glutPostRedisplay();
};

void Specialkeys(int key, int x, int y)
{
     // cout<<"Player Location  :  "<<P->getPlayerLoc().x<< "    "<<P->getPlayerLoc().y<<endl;
    switch(key)
    {
        
    case GLUT_KEY_UP:
        P->action =1;
         break;

    case GLUT_KEY_DOWN:
        P->action =2;
         break;

    case GLUT_KEY_LEFT:
        P->action =3;
         break;

    case GLUT_KEY_RIGHT:
        P->action =4;
         break;
         
   }

   // comment this after you debug


  glutPostRedisplay();

}


/* Program entry point */

int main(int argc, char *argv[])
{
    //time to comment, literally disgustingly. Here basic time counter. glutInit seems to start 
    //a glut sesh with argc and argv as start? 
    srand(time(NULL));
   glutInit(&argc, argv);


   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize (800, 800);                //window screen
   glutInitWindowPosition (100, 100);            //window position
   glutCreateWindow ("Maze");                    //program title
   init();

   glutDisplayFunc(display);                     //callback function for display
   glutReshapeFunc(resize);                      //callback for reshape
   glutKeyboardFunc(key);                        //callback function for keyboard
   glutSpecialFunc(Specialkeys);
   glutMouseFunc(mouse);
   glutIdleFunc(idle);
   glutMainLoop();

   return EXIT_SUCCESS;
}
