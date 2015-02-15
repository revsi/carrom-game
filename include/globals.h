#ifndef _Globals_h_included_
#define _Globals_h_included_

//Globals
bool flag=0; //For striker;
bool Instruction=0; // Displaying Help;
float InVelx=5.0f; // Initial X-Vel of striker; default,min : 5; max:15;
float InVely=5.0f; // Initial Y-Vel of striker; default,min : 5; max:15;
float StrikeAngle=90.0f; // Direction of striking;
int score=30; // Score;
int MyCoins; // Either White/Black;
int Timer=0; // count to update score(1s -> score-=1);
int GameEnd=0; // Flag to take care of end;

#endif