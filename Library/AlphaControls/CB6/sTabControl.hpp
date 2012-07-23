// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sTabControl.pas' rev: 6.00

#ifndef sTabControlHPP
#define sTabControlHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Types.hpp>	// Pascal unit
#include <sUpDown.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <sCommonData.hpp>	// Pascal unit
#include <CommCtrl.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <ImgList.hpp>	// Pascal unit
#include <acSBUtils.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Stabcontrol
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TsTabControl;
class PASCALIMPLEMENTATION TsTabControl : public Comctrls::TTabControl 
{
	typedef Comctrls::TTabControl inherited;
	
protected:
	Acsbutils::TacSpinWnd* BtnSW;
	int CurItem;
	Scommondata::TsCommonData* FCommonData;
	AnsiString ChangedSkinSection;
	Types::TRect __fastcall GetClRect();
	Types::TRect __fastcall TabsRect();
	int __fastcall TabRow(int TabIndex);
	void __fastcall CheckUpDown(void);
	
public:
	Types::TRect __fastcall PageRect();
	Types::TRect __fastcall SkinTabRect(int Index, bool Active);
	int __fastcall GetTabUnderMouse(const Types::TPoint &p);
	void __fastcall DrawSkinTabs(const Sconst::TCacheInfo &CI);
	void __fastcall DrawSkinTab(int Index, int State, Graphics::TBitmap* Bmp, const Types::TPoint &OffsetPoint)/* overload */;
	void __fastcall DrawSkinTab(int Index, int State, HDC DC)/* overload */;
	void __fastcall RepaintTab(int i, int State, HDC TabDC = (HDC)(0x0));
	void __fastcall AC_WMPaint(Messages::TWMPaint &Message);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall AfterConstruction(void);
	__fastcall virtual TsTabControl(Classes::TComponent* AOwner);
	__fastcall virtual ~TsTabControl(void);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	
__published:
	__property Scommondata::TsCommonData* SkinData = {read=FCommonData, write=FCommonData};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsTabControl(HWND ParentWindow) : Comctrls::TTabControl(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Stabcontrol */
using namespace Stabcontrol;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sTabControl
