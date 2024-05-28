section.begin
   Name = ShowMainMenu
   Code : struct.begin
      [*] = ;const bupdate = True;
      [*] = ;const currentstatename = 'ShowMainMenu';
      [*] = ;var elmname, showstate, eventstate : String;
      [*] = ;_misc_GetGUIShowEventStateNames(currentstatename, elmname, showstate, eventstate);
      [*] = ;
      [*] = ;var ui : TUI;
      [*] = ;ui.SetContainerMaxWidthType(0);
      [*] = ;ui.SetDebug(True);
      [*] = ;
      [*] = ;var nul : String;
      [*] = ;var btncolor : TColor;
      [*] = ;_gui_SetupTColorInteger(255, 220, 170, 255, 0.9, btncolor);
      [*] = ;function ShowButton(const elmName : String; elmHnd, parentHnd : Integer; btnMaterial : String; var text : String; margin, tag : Integer; bEnabled : Boolean) : Integer;
      [*] = ;begin
      [*] = ;   //_gui_HighlightTextHotkey(text, eventstate, elmName, text, False);
      [*] = ;   Result := _gui_CreateButton(elmName, parentHnd, btnMaterial, gc_halParentMiddle, gc_valParentTop, 0, _gui_GetBottomPos(elmHnd)+margin, 0, 0, eventstate, nul, tag, bupdate);
      [*] = ;   SetGUIElementEnabled(Result, bEnabled);
      [*] = ;   _gui_CreateText('txtbtn', Result, text, gc_halParentMiddle, gc_valParentMiddle, 0, 0, 0, 0, gc_halLeft, gc_valMiddle, gc_font_serif_15, btncolor, bupdate);
      [*] = ;   SetGUIElementUseUserColor(Result, True);
      [*] = ;   SetGUIElementUserColor(Result, 1, 0.85, 0.75, 1);
      [*] = ;end;
      [*] = ;
      [*] = ;const cmargin = 7;
      [*] = ;const cmargin1 = cmargin;
      [*] = ;var cmargin2 : Integer = cmargin*2;
      [*] = ;
      [*] = ;const cBtnOffset = 64;
      [*] = ;const cTagUnitsStats = 100;
      [*] = ;const cTagCampaign = 101;
      [*] = ;const cTagRandomMap = 102;
      [*] = ;const cTagMultiplayer = 103;
      [*] = ;const cTagSettings = 104;
      [*] = ;const cTagLoadGame = 105;
      [*] = ;const cTagLoadReplay = 106;
      [*] = ;const cTagEditor = 107;
      [*] = ;const cTagModManager = 108;
      [*] = ;const cTagExit = 109;
      [*] = ;const cTagTutorial = 110;
      [*] = ;const cTagCredits = 111;
      [*] = ;
      [*] = ;var dpiscale : Float = _gui_GetAbsScaleByDPI(0, 0);
      [*] = ;
      [*] = ;var w : Integer = GetViewerWidth;
      [*] = ;var h : Integer = GetViewerHeight;
      [*] = ;var artW : Integer = GetGUITextureWidth('mainmenu_art');
      [*] = ;var a : Integer = 290;
      [*] = ;var xaperc : Float = 0.89;
      [*] = ;var xa : Integer = floor((xaperc*w)-dpiscale*a/2);
      [*] = ;if (w<xa+(a+60)*dpiscale) then
      [*] = ;xa := w-round((a+60)*dpiscale);
      [*] = ;
      [*] = ;var cMinYArt : Integer = round(902*dpiscale);
      [*] = ;//const cMinYLogo = 902+100+160;
      [*] = ;var cMinYLogo : Integer = round(902*dpiscale);
      [*] = ;const cMinB = 58;
      [*] = ;var b : Integer = floor(w-xa-a);
      [*] = ;if (b<cMinB) then
      [*] = ;xa := xa+b-cMinB;
      [*] = ;
      [*] = ;var yArt : Integer;
      [*] = ;var yLogo : Integer;
      [*] = ;if (h<cMinYArt) then
      [*] = ;yArt := (cMinYArt-h) div 2;
      [*] = ;
      [*] = ;if (h<cMinYLogo) then
      [*] = ;yLogo := (cMinYLogo-h) div 2;
      [*] = ;
      [*] = ;var cTextCampaign : String = GetLocaleTableListItemByID('gui', 'menu.btn.campaign');
      [*] = ;var cTextRandomMap : String = GetLocaleTableListItemByID('gui', 'menu.btn.randommap');
      [*] = ;var cTextSettings : String = GetLocaleTableListItemByID('gui', 'menu.btn.settings');
      [*] = ;var cTextSingleplayer : String = GetLocaleTableListItemByID('gui', 'menu.btn.singleplayer');
      [*] = ;var cTextMultiplayer : String = GetLocaleTableListItemByID('gui', 'menu.btn.multiplayer');
      [*] = ;var cTextLoadGame : String = GetLocaleTableListItemByID('gui', 'menu.btn.loadgame');
      [*] = ;var cTextLoadReplay : String = GetLocaleTableListItemByID('misc', 'loadgame.loadreplay');
      [*] = ;var cTextOptions : String = GetLocaleTableListItemByID('gui', 'menu.btn.options');
      [*] = ;var cTextEditor : String = GetLocaleTableListItemByID('gui', 'menu.btn.editor');
      [*] = ;var cTextCredits : String; _misc_GetNewTextLocale('menu.btn.credits', cTextCredits);
      [*] = ;var cTextModManager : String; _misc_GetNewTextLocale('mods.workshop', cTextModManager);
      [*] = ;var cTextTutorial : String; _misc_GetNewTextLocale('btn.tutorial', cTextTutorial);
      [*] = ;var cTextExit : String = GetLocaleTableListItemByID('gui', 'menu.btn.exit');
      [*] = ;
      [*] = ;var elmParent : Integer = _ui_CreateCol(ui, elmname, 0, gc_halLeft, 0, 12/dpiscale, 0, 0, round(GetViewerHeight/dpiscale), bupdate);
      [*] = ;_gui_AbsScaleByDPI(elmParent);
      [*] = ;SetGUIElementPressState(elmParent, eventstate);
      [*] = ;var elmBlackMask : Integer = _gui_CreateImageActive('blmask', elmParent, gc_gui_material_black, gc_halLeft, gc_valTop, 0, 0, GetViewerWidth, GetViewerHeight, 0, '', '', bupdate);
      [*] = ;var elmBackground : Integer = _gui_CreateImage('bcg', elmParent, 'mainmenu_art', gc_halMiddle, gc_valMiddle, -90, yArt, 0, 0, 0, bupdate);
      [*] = ;var elmLeft : Integer = _ui_CreateCustomContainer(ui, 'col1', elmParent, gc_halParentLeft, gc_valParentTop, round(xa/dpiscale), 0, a, GetViewerHeight, bupdate);
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('debug', elmLeft), 0.75);
      [*] = ;var elmLeftRow : Integer = _ui_CreateRow(ui, 'row1', elmLeft, gc_valParentMiddle, 0, GetViewerHeight-20*2*0, bupdate);
      [*] = ;var elmLeftFrame : Integer = _ui_CreateFrame(ui, 'wnewgame', elmLeftRow, gc_halParentLeft, gc_valParentTop, 0, 0, 0, round(GetViewerHeight/dpiscale), ui.frame1.fborder, 'decor', 0, bupdate);
      [*] = ;
      [*] = ;var ind : Integer;
      [*] = ;var cAddOffset : Integer = cBtnOffset-yLogo-22;
      [*] = ;var cLogoBaseOffset : Integer = -yLogo+round(234/2)-74;
      [*] = ;if (GetViewerHeight/dpiscale)<700 then
      [*] = ;cLogoBaseOffset := cLogoBaseOffset-32;
      [*] = ;var cBaseOffset : Integer = cLogoBaseOffset+GetGUITextureHeight('logo_small')-30;
      [*] = ;var cMarginAdd : Integer;
      [*] = ;var cveroffset : Integer;
      [*] = ;if (GetViewerHeight>1060) then
      [*] = ;begin
      [*] = ;   cBaseOffset := cBaseOffset+64-32+12;
      [*] = ;   cMarginAdd := cmargin2*2;;
      [*] = ;   cveroffset := 10;
      [*] = ;end
      [*] = ;else
      [*] = ;if (GetViewerHeight>899) then
      [*] = ;begin
      [*] = ;   cBaseOffset := cBaseOffset;
      [*] = ;   cMarginAdd := cmargin2*1-12;;
      [*] = ;   cveroffset := 10;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   cmargin2 := cmargin1+3;
      [*] = ;   cBaseOffset := cBaseOffset-10;
      [*] = ;   cveroffset := 16;
      [*] = ;end;
      [*] = ;
      [*] = ;var elmHnd : Integer;
      [*] = ;const cbtnbigmat = 'btn.large';
      [*] = ;const cbtnmat = 'btn.medium';
      [*] = ;elmHnd := ShowButton('bcampaign', elmHnd, elmLeftFrame, cbtnbigmat, cTextCampaign, cBaseOffset, cTagCampaign, gbool_gui_isfileexists_campaigns);
      [*] = ;SetGUIElementUseUserColor(elmHnd, True);
      [*] = ;SetGUIElementUserColor(elmHnd, 1, 0.7, 0.5, 1);
      [*] = ;SetGUIElementColor(GetGUIElementIndexByNameParent('txtbtn', elmHnd), 1, 0.9, 0.7, 1);
      [*] = ;elmHnd := ShowButton('bmultiplayer', elmHnd, elmLeftFrame, cbtnbigmat, cTextMultiplayer, cmargin2, cTagMultiplayer, IsEngine);
      [*] = ;SetGUIElementUseUserColor(elmHnd, True);
      [*] = ;SetGUIElementUserColor(elmHnd, 1, 0.7, 0.5, 1);
      [*] = ;SetGUIElementColor(GetGUIElementIndexByNameParent('txtbtn', elmHnd), 1, 0.9, 0.7, 1);
      [*] = ;elmHnd := ShowButton('brandommap', elmHnd, elmLeftFrame, cbtnmat, cTextRandomMap, cmargin2+cMarginAdd, cTagRandomMap, True);
      [*] = ;elmHnd := ShowButton('btutorial', elmHnd, elmLeftFrame, cbtnmat, cTextTutorial, cmargin2, cTagTutorial, gbool_gui_isfileexists_campaigns);
      [*] = ;elmHnd := ShowButton('bloadgame', elmHnd, elmLeftFrame, cbtnmat, cTextLoadGame, cmargin2, cTagLoadGame, True);
      [*] = ;elmHnd := ShowButton('bloadreplay', elmHnd, elmLeftFrame, cbtnmat, cTextLoadReplay, cmargin2, cTagLoadReplay, True);
      [*] = ;var cTextEncyclopedia : String; _misc_GetNewTextLocale('menu.encyclopedia', cTextEncyclopedia);
      [*] = ;elmHnd := ShowButton('bencyclopedia', elmHnd, elmLeftFrame, cbtnmat, cTextEncyclopedia, cmargin2+cMarginAdd, cTagUnitsStats, True);
      [*] = ;elmHnd := ShowButton('bsettings', elmHnd, elmLeftFrame, cbtnmat, cTextSettings, cmargin2, cTagSettings, True);
      [*] = ;elmHnd := ShowButton('bmodman', elmHnd, elmLeftFrame, cbtnmat, cTextModManager, cmargin2, cTagModManager, True);
      [*] = ;elmHnd := ShowButton('beditor', elmHnd, elmLeftFrame, cbtnmat, cTextEditor, cmargin2, cTagEditor, True);
      [*] = ;//elmHnd := ShowButton('bcredits', elmHnd, elmLeftFrame, cbtnmat, cTextCredits, cmargin2, cTagCredits, True);
      [*] = ;elmHnd := ShowButton('bexit', elmHnd, elmLeftFrame, cbtnbigmat, cTextExit, cmargin2+cMarginAdd*2, cTagExit, True);
      [*] = ;SetGUIElementUseUserColor(elmHnd, True);
      [*] = ;SetGUIElementUserColor(elmHnd, 1, 0.8, 0.7, 1);
      [*] = ;
      [*] = ;var elmLogo : Integer = _gui_CreateImage('ilogo', elmLeftRow, 'logo_small', gc_halParentMiddle, gc_valParentTop, 0, cLogoBaseOffset, 0, 0, 0, bupdate);
      [*] = ;
      [*] = ;var color : TColor; _gui_ConvertHexToTColor('ffffff', color);
      [*] = ;var cTextVersion : String = GetLocaleTableListItemByID('misc', 'version');
      [*] = ;cTextVersion := StrReplace(cTextVersion, '%ver%', GetBuildVersion);
      [*] = ;cTextVersion := StrReplace(cTextVersion, '%dataver%', '.'+IntToStr(gDataVersion));
      [*] = ;cTextVersion := cTextVersion+'.'+IntToStr(gSVNVersion);
      [*] = ;if (gProfile.lastknowndlcs<>0) then
      [*] = ;begin
      [*] = ;   {var dlctext : String = ' (';
      [*] = ;   if ((gProfile.lastknowndlcs and gc_lastknowndlc_earlybird<>0))
      [*] = ;   or ((gProfile.purchaseunixtime>0) and (gProfile.purchaseunixtime<=gc_unixtime_earlybirdend)) then
      [*] = ;   dlctext := dlctext+'early bird';
      [*] = ;   if (gProfile.lastknowndlcs and gc_lastknowndlc_deluxe<>0) then
      [*] = ;   begin
      [*] = ;      if (dlctext<>' (') then
      [*] = ;      dlctext := dlctext+' + ';
      [*] = ;      dlctext := dlctext+'deluxe';
      [*] = ;   end;
      [*] = ;   dlctext := dlctext+')';}
      [*] = ;   var dlctext : String;
      [*] = ;   if gstring_checksum<>'' then
      [*] = ;   dlctext :=  '%color(999999)%'+' ('+gstring_checksum+')';
      [*] = ;   cTextVersion := cTextVersion+dlctext;
      [*] = ;end;
      [*] = ;_gui_CreateText('ver', elmLeftFrame, cTextVersion, gc_halParentRightWidth, gc_valParentBottomHeight, -4-4, -GetGUIElementFontHeight(gUIConst.font[gc_font_serif_12])+cveroffset, GetGUIElementWidth(elmLeftFrame), 0, gc_halRight, gc_valMiddle, gc_font_serif_10, color, True);
      [*] = ;var text : String = 'Ebel''s New Terrain Mod '+gc_ntmodversion;
      [*] = ;_gui_CreateText('NT', elmLeftFrame, text, gc_halParentRightWidth, gc_valParentBottomHeight, 0, -GetGUIElementFontHeight(gUIConst.font[gc_font_serif_12])-20, GetGUIElementWidth(elmLeftFrame), 0, gc_halRight, gc_valMiddle, gc_font_serif_10, color, True);
      [*] = ;var modscount : Integer = ModLibraryGetCount;
      [*] = ;//if modscount>0 then
      [*] = ;begin
      [*] = ;   var cTextMods : String;
      [*] = ;   if (gbool_modsactive) then
      [*] = ;   cTextMods := GetLocaleTableListItemByID('new', 'mods.modslist');
      [*] = ;   var libind, enum : Integer;
      [*] = ;   var tag, dir, last, tit, ownid, desc, tags, url, note: string;
      [*] = ;   var numf, vis: integer;
      [*] = ;   var dis, acc, ban, root: boolean;
      [*] = ;   for libind:=0 to modscount-1 do
      [*] = ;   begin
      [*] = ;      ModLibraryGetData(libind, tag, dir, last, tit, ownid, desc, tags, url, note, numf, vis, dis, acc, ban, root);
      [*] = ;      if (not dis) then
      [*] = ;      begin
      [*] = ;         var modname : String;
      [*] = ;         if tag='0' then
      [*] = ;         begin
      [*] = ;            if last<>'' then
      [*] = ;            modname := '*'+last
      [*] = ;            else
      [*] = ;            modname := '*'+dir;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if tit<>'' then
      [*] = ;         modname := tit
      [*] = ;         else
      [*] = ;         if last<>'' then
      [*] = ;         modname := '*'+last
      [*] = ;         else
      [*] = ;         modname := GetLocaleTableListItemByID('new', 'mods.unknown');
      [*] = ;
      [*] = ;         cTextMods := cTextMods+gc_gui_breakline+modname;
      [*] = ;         enum := enum+1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   var dpiscale : Float = _gui_GetAbsScaleByDPI(0, 0);
      [*] = ;   cTextMods := GetGUIWrappedTextByFont(gUIConst.font[gc_font_serif_10], cTextMods, round(GetViewerWidth/(dpiscale*3)));
      [*] = ;   //cTextMods := cTextMods+gc_gui_breakline+'('+gstring_checksum+')';
      [*] = ;   if (not _misc_IsWindows) then
      [*] = ;   cTextMods := cTextMods+gc_gui_breakline+gc_gui_breakline+'%color(BBBBBB)%'+'Linux version is in Beta'+gc_gui_breakline+'Known problems'+gc_gui_breakline+'- steam achievements, workshop and resolution change may not work'+gc_gui_breakline+'- special characters may not appear correctly on input from keyboard';
      [*] = ;
      [*] = ;   // here will be btn for modworkshop
      [*] = ;   //elmHnd := _gui_CreateButton('bmodman', elmLeftFrame, cbtnmat, gc_halLeft, gc_valParentTop, 5, 5, 0, 0, eventstate, nul, cTagModManager, bupdate);
      [*] = ;   //_gui_CreateText('txtbtn', elmHnd, cTextModManager, gc_halParentMiddle, gc_valParentMiddle, 0, 0, 0, 0, gc_halLeft, gc_valMiddle, gc_font_serif_15, btncolor, bupdate);
      [*] = ;   var elmHnd : Integer = _gui_CreateText('mod', elmLeftFrame, cTextMods, gc_halLeft, gc_valParentTop, 15, 54{GetGUIElementFontHeight(gUIConst.font[gc_font_serif_12])}, 0, 0, gc_halLeft, gc_valTop, gc_font_serif_10, color, True);
      [*] = ;
      [*] = ;   gbool_modsactive := enum>0;
      [*] = ;   SetGUIElementVisible(elmHnd, (not _misc_IsWindows) or gbool_modsactive);
      [*] = ;end;
      [*] = ;dbgstatename := 'ShowMainMenu';
   struct.end
section.end

