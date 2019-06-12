//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "CGRID.h"
#include <Grids.hpp>
#include "kolejkaPrio2.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TShape *Shape1;
        TShape *Shape2;
        TShape *Shape3;
        TShape *Shape4;
        TShape *Shape5;
        TShape *Shape6;
        TShape *Shape7;
        TShape *Shape8;
        TShape *Shape9;
        TShape *Shape10;
        TShape *Shape11;
        TShape *Shape12;
        TShape *Shape13;
        TShape *Shape14;
        TShape *Shape15;
        TShape *Shape16;
        TShape *Shape17;
        TShape *Shape18;
        TShape *Shape19;
        TShape *Shape20;
        TShape *Shape21;
        TShape *Shape22;
        TShape *Shape23;
        TShape *Shape24;
        TShape *Shape25;
        TShape *Shape26;
        TShape *Shape27;
        TShape *Shape28;
        TShape *Shape29;
        TShape *Shape30;
        TShape *Shape31;
        TShape *Shape32;
        TImage *b8;
        TImage *d8;
        TImage *f8;
        TImage *c7;
        TImage *a7;
        TImage *e7;
        TImage *g7;
        TImage *h8;
        TImage *c5;
        TImage *a5;
        TImage *b6;
        TImage *d6;
        TImage *e5;
        TImage *f6;
        TImage *g5;
        TImage *h6;
        TImage *c3;
        TImage *a3;
        TImage *b4;
        TImage *d4;
        TImage *e3;
        TImage *f4;
        TImage *g3;
        TImage *h4;
        TImage *c1;
        TImage *a1;
        TImage *b2;
        TImage *d2;
        TImage *e1;
        TImage *f2;
        TImage *g1;
        TImage *h2;
        TShape *Shape33;
        TShape *Shape34;
        TLabel *Label1;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall c3Click(TObject *Sender);
        void __fastcall d4Click(TObject *Sender);
        void __fastcall a1Click(TObject *Sender);
        void __fastcall a3Click(TObject *Sender);
        void __fastcall a5Click(TObject *Sender);
        void __fastcall a7Click(TObject *Sender);
        void __fastcall b2Click(TObject *Sender);
        void __fastcall b4Click(TObject *Sender);
        void __fastcall b6Click(TObject *Sender);
        void __fastcall b8Click(TObject *Sender);
        void __fastcall c1Click(TObject *Sender);
        void __fastcall c5Click(TObject *Sender);
        void __fastcall c7Click(TObject *Sender);
        void __fastcall d2Click(TObject *Sender);
        void __fastcall d6Click(TObject *Sender);
        void __fastcall d8Click(TObject *Sender);
        void __fastcall e1Click(TObject *Sender);
        void __fastcall e3Click(TObject *Sender);
        void __fastcall e5Click(TObject *Sender);
        void __fastcall e7Click(TObject *Sender);
        void __fastcall f2Click(TObject *Sender);
        void __fastcall f4Click(TObject *Sender);
        void __fastcall f6Click(TObject *Sender);
        void __fastcall f8Click(TObject *Sender);
        void __fastcall g1Click(TObject *Sender);
        void __fastcall g3Click(TObject *Sender);
        void __fastcall g5Click(TObject *Sender);
        void __fastcall g7Click(TObject *Sender);
        void __fastcall h2Click(TObject *Sender);
        void __fastcall h4Click(TObject *Sender);
        void __fastcall h6Click(TObject *Sender);
        void __fastcall h8Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        void changeImage(int index, char* file);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
