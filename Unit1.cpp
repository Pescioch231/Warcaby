//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include<assert.h>

#include "Unit1.h"
#include "kolejkaPrio2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGRID"
#pragma resource "*.dfm"
TForm1 *Form1;
//tablica z informacja o stanie pola 0-puste b-czarny w-bialy e-damaCzarna g-damaBiala d-pionDoZbicia h-polePoBiciu m-mozliwyRuch
char state[32]={'b','b','b','b','b','b','b','b','b','b','b','b','0','0','0','0',
'0','0','0','0','w','w','w','w','w','w','w','w','w','w','w','w'};
//tablica sasiadow
int borders[32][4]={{4,5,-1,-1},{5,6,-1,-1},{6,7,-1,-1},{7,-1,-1,-1},
{0,8,-1,-1},{0,1,8,9},{1,2,9,10},{2,3,10,11},
{4,5,12,13},{5,6,13,14},{6,7,14,15},{7,15,-1,-1},
{8,16,-1,-1},{8,16,9,17},{9,17,10,18},{10,18,11,19},
{12,20,13,21},{13,21,14,22},{14,22,15,23},{15,23,-1,-1},
{16,24,-1,-1},{16,24,17,25},{17,25,18,26},{18,26,19,27},
{20,28,21,29},{21,29,22,30},{22,30,23,31},{23,31,-1,-1},
{24,-1,-1,-1},{24,25,-1,-1},{25,26,-1,-1},{26,27,-1,-1}};
int click, prev; // zmienna przechowuje poprzednie klikniecie, najlepszy ruch, oraz najlepszy profit
prioQueue indexHeap(100); //kopiec ruchów 0
bool again=0 , againAI=0;
#define howDeep 2

//zmienia obraz pola (index pola, pilk obrazu)
void TForm1::changeImage(int index, char* file)
{
        if(index==0)
        b8->Picture->LoadFromFile(file);
        else if(index==1)
        d8->Picture->LoadFromFile(file);
        else if(index==2)
        f8->Picture->LoadFromFile(file);
        else if(index==3)
        h8->Picture->LoadFromFile(file);
        else if(index==4)
        a7->Picture->LoadFromFile(file);
        else if(index==5)
        c7->Picture->LoadFromFile(file);
        else if(index==6)
        e7->Picture->LoadFromFile(file);
        else if(index==7)
        g7->Picture->LoadFromFile(file);
        else if(index==8)
        b6->Picture->LoadFromFile(file);
        else if(index==9)
        d6->Picture->LoadFromFile(file);
        else if(index==10)
        f6->Picture->LoadFromFile(file);
        else if(index==11)
        h6->Picture->LoadFromFile(file);
        else if(index==12)
        a5->Picture->LoadFromFile(file);
        else if(index==13)
        c5->Picture->LoadFromFile(file);
        else if(index==14)
        e5->Picture->LoadFromFile(file);
        else if(index==15)
        g5->Picture->LoadFromFile(file);
        else if(index==16)
        b4->Picture->LoadFromFile(file);
        else if(index==17)
        d4->Picture->LoadFromFile(file);
        else if(index==18)
        f4->Picture->LoadFromFile(file); 
        else if(index==19)
        h4->Picture->LoadFromFile(file);
	else if(index==20)
        a3->Picture->LoadFromFile(file);
        else if(index==21)
        c3->Picture->LoadFromFile(file);
        else if(index==22)
        e3->Picture->LoadFromFile(file);
        else if(index==23)
        g3->Picture->LoadFromFile(file);
        else if(index==24)
	b2->Picture->LoadFromFile(file);
        else if(index==25)
        d2->Picture->LoadFromFile(file);
        else if(index==26)
        f2->Picture->LoadFromFile(file);
        else if(index==27)
        h2->Picture->LoadFromFile(file);
        else if(index==28)
        a1->Picture->LoadFromFile(file);
        else if(index==29)
        c1->Picture->LoadFromFile(file);
        else if(index==30)
        e1->Picture->LoadFromFile(file);
        else if(index==31)
        g1->Picture->LoadFromFile(file);

}

//na podstawie (index nasz, index wroga) zwraca index pola za bitym pionem
int backHit(int our, int enemy)
{
        int back;
        int minus=our-enemy;
        if(minus<0)
                minus=enemy-our;
        if (enemy<=4 || enemy>=27 || enemy==12 || enemy==20
        || enemy==11  || enemy==19)
                back=-1;
        else if(minus==4 && our%8>3 && our>enemy)
                back=enemy-3;
        else if(minus==5 && our%8>3 && our>enemy)
                back=enemy-4;
        else if(minus==3 && our%8>3 && our<enemy)
                back=enemy+4;
        else if(minus==4 && our%8>3 && our<enemy)
                back=enemy+5;
        else if(minus==4 && our%8<=3 && our>enemy)
                back=enemy-5;
        else if(minus==3 && our%8<=3 && our>enemy)
                back=enemy-4;
        else if(minus==4 && our%8<=3  && our<enemy)
                back=enemy+3;
        else if(minus==5 && our%8<=3  && our<enemy)
                back=enemy+4;

        return back;
}


   bool anyHit(char* state2, char player, char ennemyPlayer)
{
        bool check=0;
        int enemy, back;
        for(int i=0; i<32; i++)
                if(state[i]==player)
                        for(int j=0; j<4;j++)
                        {
                                enemy=borders[i][j];
                                if(enemy!=-1 && state2[enemy]==ennemyPlayer)
                                {
                                back=backHit(i,enemy);
                                        if(back!=-1 && state2[back]=='0')
                                        {
                                                check=1;
                                        }
                                }
                        }
        return check;

}


bool anyH(char* state2)
{
        bool check=0;
        int enemy, back;
        for(int i=0; i<32; i++)
                if(state[i]=='h')
                        check=1;
        return check;
}

bool anyD(char* state2)
{
        bool check=0;
        int enemy, back;
        for(int i=0; i<32; i++)
                if(state[i]=='d')
                        check=1;
        return check;
}
///////////////////////////////////////////////////////////////////
// resetuje wirtualne mozliwe bicia
void resetHitAI(char* stateAI)
{
        for(int i=0; i<32;i++)
                if(state[i]=='h')
                        stateAI[i]='0';
}

// resetuje wirtualne mozliwosci ruchu
void resetMoveAI(char* stateAI)
{
        for(int i=0; i<32;i++)
                if(stateAI[i]=='m')
                        stateAI[i]='0';
}

//symuluje gre wirtualnie w poszukiwniu najlepszego ruchu
void AI(char* state2, int indexPS, int indexMS, int indexP, int indexM, char player, int profit, int deep)
{
        char stateAI[32];
        for(int i=0; i<32; i++)
                stateAI[i]=state2[i];
        if(indexP!=-1 && indexM!=-1)
        {
                if(player=='b')
                {
                        stateAI[indexM]='b';
                        player='w';
                }

                if(player=='w')
                {
                        stateAI[indexM]='w';
                        player='b';
                }
                stateAI[indexP]='0';
                if(deep==0)
                {
                        indexPS=indexP;
                        indexMS=indexM;
                }
                deep++;
                if(deep==howDeep)
                        indexHeap.push(indexPS, indexMS, profit);
        }
        if(deep<howDeep)
        {
        if(player=='w')
        {
        for(int i=0; i<32; i++)
                if(stateAI[i]=='w')
        for(int j=0; j<4; j++)
        {
                int border=borders[i][j];
                if(border!=-1)
                if(stateAI[border]=='0' && border<i)
                {
                        AI(stateAI, indexPS, indexMS, i, border, player, profit-1, deep);
                }

        }
        for(int i=0; i<32; i++)
                if(stateAI[i]=='w')
        for(int j=0; j<4;j++)
        {
                int border=borders[j][i];
                if(border!=-1)
                        if(stateAI[border]=='b')
                        {
                                int enemy=backHit(i,border);
                                if(enemy!=-1)
                                if(stateAI[enemy]=='0')
                                {
                                        AI(stateAI, indexPS, indexMS, i, enemy, player, profit-3, deep);
                                        stateAI[border]='0';
                                }
                        }
        }
        }
        if(player=='b')
        {
        for(int i=0; i<32; i++)
                if(stateAI[i]=='b')
        for(int j=0; j<4; j++)
        {
                int border=borders[i][j];
                if(border!=-1)
                if(stateAI[border]=='0' && border>i)
                {
                        AI(stateAI, indexPS, indexMS, i, border, player, profit+1, deep);
                }
        }
        for(int i=0; i<32; i++)
                if(stateAI[i]=='b')
        for(int j=0; j<4;j++)
        {
                int border=borders[j][i];
                if(border!=-1)
                        if(stateAI[border]=='w')
                        {
                                int enemy=backHit(i,border);
                                if(enemy!=-1)
                                if(stateAI[enemy]=='0')
                                {
                                        AI(stateAI, indexPS, indexMS, i, enemy, player, profit+3, deep);
                                        stateAI[border]='0';
                                }
                        }
        }

        }
        }

}

// komputer wykonuje swoj ruch
void moveAI()
{
        int index, a;
        AI(state, -1, -1,  -1, -1, 'b', 0, 0);
        index=indexHeap.indexMove();
        click=indexHeap.indexPown();
        indexHeap.popAll();
        if(click<0 || click>31 || index<0 || index>31)  
              assert(!"AI wyszedl poza plansze!");
        state[click]='0';
        Form1->changeImage(click, "img/none.bmp");
        state[index]='b';
        Form1->changeImage(index, "img/pawnB.bmp");
        Form1->Label1->Visible=!(Form1->Label1->Visible);

}
///////////////////////////////////////////////////////////////////////

// usuwa zbitego piona (aktualny index)
void makeHit(int our, char playerEnemy)
{
        int border;
        for(int i=0; i<4;i++)
        {
                border=borders[our][i];
                if(border!=-1 && state[border]=='d')
                {
                        state[border]='0';
                        Form1->changeImage(border, "img/none.bmp");
                }
        }
        for(int i=0; i<32; i++)
                if(state[i]=='d')
                        state[i]=playerEnemy;
}

// ustawia i wyswietla mozliwe bicia
void setHit(int our)
{
        int enemy, back;
        for(int i=0; i<4;i++)
        {
        enemy=borders[our][i];
        if(enemy!=-1 && state[enemy]=='b')
        {
                back=backHit(our,enemy);
                if(back!=-1 && state[back]=='0')
                {
                        state[back]='h';
                        state[enemy]='d';
                        Form1->changeImage(back, "img/here.bmp");
                }
        }
        }

}
// restetuje mozliwe bicia
void resetHit()
{
        for(int i=0; i<32;i++)
        {
                if(state[i]=='h')
                {
                        state[i]='0';
                        Form1->changeImage(i, "img/none.bmp");
                }
        }
}

void end()
{
        bool check=0;
        for(int i=0; i<32;i++)
                if(state[i]=='b' && state[i]=='d')
                        check=1;
        if(check==0)
        if(Application->MessageBox("Od nowa?",
        "Koniec!", MB_YESNO | MB_ICONQUESTION) == IDYES)
        {
                for(int i=0; i<12; i++)
                {
                Form1->changeImage(i, "img/pawnB.bmp");
                Form1->changeImage(i+20, "img/pawnW.bmp");
                }
                for(int i=0; i<32; i++)
                {
                        if(i<12)
                        {
                                state[i]='b';
                                Form1->changeImage(i, "img/pawnB.bmp");
                        }
                        if(i>=12 && i<20)
                        {
                                state[i]='0';
                                Form1->changeImage(i, "img/none.bmp");
                        }
                        if(i>=20 && i<32)
                        {
                                state[i]='w';
                                Form1->changeImage(i, "img/pawnW.bmp");
                        }
                }
        }else
        Application->Terminate();

}

// ustawia i wyswietla mozliwe ruchy
void setMove(int index)
{
        for(int i=0; i<4;i++)
        {
        int border=borders[index][i];
        if(border!=-1)
                if(state[border]=='0' && border<index)
                {
                        state[border]='m';
                        Form1->changeImage(border, "img/here.bmp");
                }
        }
}

// restetuje mozliwe ruchy
void resetMove()
{
        for(int i=0; i<32;i++)
        {
                if(state[i]=='m')
                {
                        state[i]='0';
                        Form1->changeImage(i, "img/none.bmp");
                }
        }
}

//gracz wykonuje ruch pionkem (indeks pola)
void move(int index)
{
        bool checkHit;
        //end();
        checkHit=anyHit(state, 'w','b');
        if(anyD(state))
                again=1;
        else
                again=0;
        if(state[index]=='w' && again==0)
        {
                resetMove();
                resetHit();
                click=index;
                if(checkHit==0)
                        setMove(index);
                else
                        setHit(index);
        }
        else if(state[index]=='h')
        {
                resetHit();
                state[index]='w';
                Form1->changeImage(index, "img/pawnW.bmp");
                state[click]='0';
                Form1->changeImage(click, "img/none.bmp");
                makeHit(index, 'b');
                setHit(index);
                click=index;
                if(again==0)
                        Form1->Label1->Visible=!(Form1->Label1->Visible);
        }
        else if(state[index]=='m')
        {
                state[index]='w';
                state[click]='0';
                Form1->changeImage(index, "img/pawnW.bmp");
                Form1->changeImage(click, "img/none.bmp");
                resetMove();
                Form1->Label1->Visible=!(Form1->Label1->Visible);

        }
        if(!Form1->Label1->Visible)
        {
                moveAI();
        }
}
//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
        for(int i=0; i<12; i++)
        {
                changeImage(i, "img/pawnB.bmp");
                changeImage(i+20, "img/pawnW.bmp");
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::a1Click(TObject *Sender)
{
        int index=28;

        move(index);
        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::a3Click(TObject *Sender)
{
        int index=20;
        
        move(index);
        
        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::a5Click(TObject *Sender)
{
        int index=12;
        
        move(index);

        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::a7Click(TObject *Sender)
{
        int index=4;
        
        move(index);
        
        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::b2Click(TObject *Sender)
{
        int index=24;
        
        move(index);
        

}
//---------------------------------------------------------------------------

void __fastcall TForm1::b4Click(TObject *Sender)
{
        int index=16;

        move(index);
        

}
//---------------------------------------------------------------------------

void __fastcall TForm1::b6Click(TObject *Sender)
{
        int index=8;
        
        move(index);
        
        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::b8Click(TObject *Sender)
{
        int index=0;
        
        move(index);

        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::c1Click(TObject *Sender)
{
        int index=29;
        
        move(index);
        

}
//---------------------------------------------------------------------------

void __fastcall TForm1::c3Click(TObject *Sender)
{
        int index=21;
        
        move(index);

        

}
//---------------------------------------------------------------------------

void __fastcall TForm1::c5Click(TObject *Sender)
{
        int index=13;
        
        move(index);

        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::c7Click(TObject *Sender)
{
        int index=5;
        
        move(index);

        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::d2Click(TObject *Sender)
{
        int index=25;
        
        move(index);

        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::d4Click(TObject *Sender)
{
        int index=17;
        
        move(index);


}
//---------------------------------------------------------------------------

void __fastcall TForm1::d6Click(TObject *Sender)
{
        int index=9;

        move(index);
        
        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::d8Click(TObject *Sender)
{
        int index=1;

        move(index);
        

}
//---------------------------------------------------------------------------

void __fastcall TForm1::e1Click(TObject *Sender)
{
        int index=30;

        move(index);
        

}
//---------------------------------------------------------------------------

void __fastcall TForm1::e3Click(TObject *Sender)
{
        int index=22;

        move(index);
        

}
//---------------------------------------------------------------------------

void __fastcall TForm1::e5Click(TObject *Sender)
{
        int index=14;

        move(index);


}
//---------------------------------------------------------------------------

void __fastcall TForm1::e7Click(TObject *Sender)
{
        int index=6;

        move(index);


}
//---------------------------------------------------------------------------

void __fastcall TForm1::f2Click(TObject *Sender)
{
        int index=26;

        move(index);


}
//---------------------------------------------------------------------------

void __fastcall TForm1::f4Click(TObject *Sender)
{
        int index=18;
        
        move(index);


}
//---------------------------------------------------------------------------

void __fastcall TForm1::f6Click(TObject *Sender)
{
        int index=10;
        
        move(index);
        
        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::f8Click(TObject *Sender)
{
        int index=2;

        move(index);
        
        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::g1Click(TObject *Sender)
{
        int index=31;

        move(index);
        

}
//---------------------------------------------------------------------------

void __fastcall TForm1::g3Click(TObject *Sender)
{
        int index=23;

        move(index);
        
        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::g5Click(TObject *Sender)
{
        int index=15;

        move(index);
        

}
//---------------------------------------------------------------------------

void __fastcall TForm1::g7Click(TObject *Sender)
{
        int index=7;

        move(index);
        
        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::h2Click(TObject *Sender)
{
        int index=27;

        move(index);
        

}
//---------------------------------------------------------------------------

void __fastcall TForm1::h4Click(TObject *Sender)
{
        int index=19;

        move(index);
        

}
//---------------------------------------------------------------------------

void __fastcall TForm1::h6Click(TObject *Sender)
{
        int index=11;

        move(index);

        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::h8Click(TObject *Sender)
{
        int index=3;

        move(index);


}
//---------------------------------------------------------------------------



