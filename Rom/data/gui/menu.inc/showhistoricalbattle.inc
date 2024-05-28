section.begin
   Name = ShowHistoricalBattle
   Code : struct.begin
      [*] = ;const bupdate = True;
      [*] = ;const currentstatename = 'ShowHistoricalBattle';
      [*] = ;var elmname, showstate, eventstate : String;
      [*] = ;_misc_GetGUIShowEventStateNames(currentstatename, elmname, showstate, eventstate);
      [*] = ;
      [*] = ;const cTagBackToMainMenu = 101;
      [*] = ;const cTagSwitchToShell = 102;
      [*] = ;const cTagStartGame = 103;
      [*] = ;const cTagCloseRoom = 104;
      [*] = ;const cTagLeaveRoom = 105;
      [*] = ;const cTagReadyGame = 106;
      [*] = ;const cTagStartAutoSearch = 107;
      [*] = ;const cTagStopAutoSearch = 108;
      [*] = ;const cTagGoPickPositions = 109;
      [*] = ;const cTagBaseTagChangeColor = 200;
      [*] = ;const cTagClose = 500;
      [*] = ;const cTagChangePosition = 501;
      [*] = ;const cTagChangeTeam = 502;
      [*] = ;const cTagKick = 1000;
      [*] = ;
      [*] = ;var randkey : Integer = GetRandomKey;
      [*] = ;SetRandomKey(260); // used in combobox render
      [*] = ;
      [*] = ;var bOnline : Boolean = _net_IsOnline;//(gInternetShell.currentsessionid>0);
      [*] = ;var bOffline : Boolean = (not bOnline);
      [*] = ;var bServer : Boolean = _net_IsServer;//(gInternetShell.lanid>0) and (gInternetShell.currentsessionid=gInternetShell.lanid);
      [*] = ;var bClient : Boolean = (bOnline) and (not bServer);
      [*] = ;var bReady, bAllReady, bAllowReady, bAllowNextStage, bTeam1, bTeam2, bSamePos, bTeamUnknown : Boolean;
      [*] = ;var bFirstTeamIsFull, bSecondTeamIsFull : Boolean;
      [*] = ;var countofavailableteams : Integer;
      [*] = ;var countteam1, countteam2 : Integer;
      [*] = ;
      [*] = ;function CheckDoubleColor(testplayer, testcolor : Integer; bAdjust, bDirectionForward : Boolean) : Integer;
      [*] = ;begin
      [*] = ;   var newtestcolor : Integer = testcolor;
      [*] = ;   if (bAdjust) then
      [*] = ;   begin
      [*] = ;      if (bDirectionForward) then
      [*] = ;      newtestcolor := ((newtestcolor+1) mod (gc_MaxColorCount-1))
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         newtestcolor := newtestcolor-1;
      [*] = ;         if newtestcolor<0 then newtestcolor := gc_MaxColorCount-2;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   Result := newtestcolor;
      [*] = ;   var bDoubleColor : Boolean;
      [*] = ;   var i, j : Integer;
      [*] = ;   for i:=0 to gc_MaxNonSpectatorsCount-1 do
      [*] = ;   begin
      [*] = ;      if (i<>testplayer) and (gMap.players[i].bexists) and (gMap.players[i].color=newtestcolor) then
      [*] = ;      begin
      [*] = ;         Result := CheckDoubleColor(testplayer, newtestcolor, True, bDirectionForward);
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;function CheckDoublePosition(testplayer, testposition : Integer; bAdjust, bDirectionForward : Boolean) : Integer;
      [*] = ;begin
      [*] = ;   var countteam1, countteam2 : Integer;
      [*] = ;   var i: Integer;
      [*] = ;   for i:=0 to gc_MaxNonSpectatorsCount-1 do
      [*] = ;   begin
      [*] = ;      if gMap.players[i].bexists and gMap.players[i].bhuman then
      [*] = ;      begin
      [*] = ;         if (gMap.players[i].team=1) then
      [*] = ;         countteam1 := countteam1+1
      [*] = ;         else
      [*] = ;         if (gMap.players[i].team=2) then
      [*] = ;         countteam2 := countteam2+1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   const cmaxteamcount = 4;
      [*] = ;   var minind, maxind : Integer;
      [*] = ;   var defind : Integer = gc_MaxCountryCount;
      [*] = ;   if (gMap.players[testplayer].team=1) then
      [*] = ;   begin
      [*] = ;      minind := 0;
      [*] = ;      maxind := minind+countteam1-1;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      minind := cmaxteamcount{cteamposcount};
      [*] = ;      maxind := minind+countteam2-1;
      [*] = ;   end;
      [*] = ;   var newtestposition : Integer = testposition;
      [*] = ;   if (bAdjust) then
      [*] = ;   begin
      [*] = ;      if (bDirectionForward) then
      [*] = ;      begin
      [*] = ;         if newtestposition=defind then
      [*] = ;         newtestposition := minind
      [*] = ;         else
      [*] = ;         if newtestposition>(maxind-1) then
      [*] = ;         newtestposition := defind
      [*] = ;         else
      [*] = ;         newtestposition := newtestposition+1;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (newtestposition=defind) then
      [*] = ;         newtestposition := maxind
      [*] = ;         else
      [*] = ;         if newtestposition<=minind then
      [*] = ;         newtestposition := defind
      [*] = ;         else
      [*] = ;         newtestposition := newtestposition-1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   Result := newtestposition;
      [*] = ;   var bDoubleColor : Boolean;
      [*] = ;   var j : Integer;
      [*] = ;   for i:=0 to gc_MaxNonSpectatorsCount-1 do
      [*] = ;   begin
      [*] = ;      if (i<>testplayer) and (gMap.players[i].bexists) and (Result<>gc_MaxCountryCount) and (gMap.players[i].cid=newtestposition) then
      [*] = ;      begin
      [*] = ;         Result := CheckDoublePosition(testplayer, newtestposition, True, bDirectionForward);
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;var i : Integer;
      [*] = ;for i:=0 to gc_MaxNonSpectatorsCount-1 do
      [*] = ;begin
      [*] = ;   gMap.players[i].color := CheckDoubleColor(i, gMap.players[i].color, False, True);
      [*] = ;   if (gMap.players[i].cid<>gc_MaxCountryCount) then
      [*] = ;   gMap.players[i].cid := CheckDoublePosition(i, gMap.players[i].cid, False, True);
      [*] = ;end;
      [*] = ;
      [*] = ;if (IsLanPublicServerMode) and (not _net_IsOnline) then
      [*] = ;begin
      [*] = ;   gInternetShell.currentsessionid := 0;
      [*] = ;   gInternetShell.roomdata := '';
      [*] = ;   gInternetShell.selsessionid := 0;
      [*] = ;   _gui_SetGUIElementVisibleByName(elmname, False);
      [*] = ;   gInternetShell.bshowroom := False;
      [*] = ;   gInternetShell.bshowranking := False;
      [*] = ;   ExecuteState('ShowInternetShell');
      [*] = ;   _gui_SetShellChatInputBoxFocused;
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;if (bOnline) then
      [*] = ;begin
      [*] = ;   bAllReady := True;
      [*] = ;   bAllowNextStage := True;
      [*] = ;   bAllowReady := True;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to gc_MaxNonSpectatorsCount-1 do
      [*] = ;   if gMap.players[i].bexists and gMap.players[i].bhuman then
      [*] = ;   if (gMap.players[i].team=0) then
      [*] = ;   begin
      [*] = ;      bTeamUnknown := True;
      [*] = ;      if (not gMap.players[i].bready) then
      [*] = ;      bAllowNextStage := False;
      [*] = ;   end;
      [*] = ;   if gMap.players[0].team=1 then
      [*] = ;   bTeam1 := True
      [*] = ;   else
      [*] = ;   if gMap.players[0].team=2 then
      [*] = ;   bTeam2 := True;
      [*] = ;   for i:=1 to gc_MaxNonSpectatorsCount-1 do
      [*] = ;   begin
      [*] = ;      if gMap.players[i].bexists and gMap.players[i].bhuman then
      [*] = ;      begin
      [*] = ;         if (LanMyInfoID=gMap.players[i].lanid) then
      [*] = ;         begin
      [*] = ;            bReady := gMap.players[i].bready;
      [*] = ;            if (bAllowReady) and (not gMap.players[i].bready) and (gMap.players[i].team=0) then
      [*] = ;            bAllowReady := False;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if bAllReady and (not gMap.players[i].bready) then
      [*] = ;         bAllReady := False;
      [*] = ;         if gMap.players[i].team=1 then
      [*] = ;         bTeam1 := True
      [*] = ;         else
      [*] = ;         if gMap.players[i].team=2 then
      [*] = ;         bTeam2 := True;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if not bTeam1 or not bTeam2 then
      [*] = ;   bAllowNextStage := False;
      [*] = ;end;
      [*] = ;
      [*] = ;if (bOnline) then
      [*] = ;begin
      [*] = ;   var i, k, n: Integer;
      [*] = ;   for i:=0 to gc_MaxNonSpectatorsCount-1 do
      [*] = ;   begin
      [*] = ;      if gMap.players[i].bexists and gMap.players[i].bhuman then
      [*] = ;      begin
      [*] = ;         if (gMap.players[i].team = 1) then
      [*] = ;         k := k + 1;
      [*] = ;         if (gMap.players[i].team = 2) then
      [*] = ;         n := n + 1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if (k=4) then
      [*] = ;   bFirstTeamIsFull := True
      [*] = ;   else
      [*] = ;   countofavailableteams := countofavailableteams + 1;
      [*] = ;   if (n=4) then
      [*] = ;   bSecondTeamIsFull := True
      [*] = ;   else
      [*] = ;   countofavailableteams := countofavailableteams + 1;
      [*] = ;end;
      [*] = ;
      [*] = ;if (bOnline) then
      [*] = ;begin
      [*] = ;   var i: Integer;
      [*] = ;   for i:=0 to gc_MaxNonSpectatorsCount-1 do
      [*] = ;   begin
      [*] = ;      if gMap.players[i].bexists and gMap.players[i].bhuman then
      [*] = ;      begin
      [*] = ;         if (gMap.players[i].team=1) then
      [*] = ;         countteam1 := countteam1+1
      [*] = ;         else
      [*] = ;         if (gMap.players[i].team=2) then
      [*] = ;         countteam2 := countteam2+1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var color : TColor;
      [*] = ;_gui_SetupTColorInteger(255, 220, 170, 255, 0.925, color);
      [*] = ;procedure FillComboBoxTeams(elmHnd : Integer);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   if (GetGUIListBoxItemsCount(elmHnd)=0) then
      [*] = ;   begin
      [*] = ;      var csid : String;
      [*] = ;      GUIListBoxAddItem(elmHnd, '-', 0);
      [*] = ;      for i:=1 to 2 do
      [*] = ;      begin
      [*] = ;         if (((i=1) and (not bFirstTeamIsFull)) or ((i=2) and (not bSecondTeamIsFull))) then
      [*] = ;         GUIListBoxAddItem(elmHnd, IntToStr(i), i);
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, 0);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure FillComboBoxPositions(elmHnd, plInd : Integer; bAddRandom, bAddUnplayable : Boolean);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   if (GetGUIListBoxItemsCount(elmHnd)=0) then
      [*] = ;   begin
      [*] = ;      var csid : String;
      [*] = ;      if (bAddRandom) then
      [*] = ;      GUIListBoxAddItem(elmHnd, GetLocaleTableListItemByID('gui', 'text.random'), gc_MaxCountryCount);
      [*] = ;      for i:=0 to gc_MaxNonSpectatorsCount-1 do
      [*] = ;      begin
      [*] = ;         var k : Integer;
      [*] = ;         var bdelitem : Boolean;
      [*] = ;         for k:=0 to gc_MaxNonSpectatorsCount-1 do
      [*] = ;         begin
      [*] = ;            if(gMap.players[i].cid = k) then
      [*] = ;            bdelitem := True;
      [*] = ;         end;
      [*] = ;         if(not bdelitem) then
      [*] = ;         GUIListBoxAddItem(elmHnd, 'pos_'+inttostr(i), i);
      [*] = ;      end;
      [*] = ;      GUIListBoxAddItem(elmHnd, 'pos_'+inttostr(i), i);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, 0);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;//GETTING TEXTS FROM TABLE
      [*] = ;var cTextHeader : String = GetLocaleTableListItemByID('gui', 'menu.btn.historicalbattle');
      [*] = ;var cTextPosCol : String = GetLocaleTableListItemByID('gui', 'pos.col.historicalbattle');
      [*] = ;var cTextCustomGame : String = GetLocaleTableListItemByID('gui', 'menu.btn.randommap');
      [*] = ;var cTextBackToMainMenu : String = GetLocaleTableListItemByID('gui', 'menu.btn.backtomainmenu');
      [*] = ;var cTextSwitchToShell : String = GetLocaleTableListItemByID('gui', 'customgame.btn.switchtoshell');
      [*] = ;var cTextCloseRoom : String = GetLocaleTableListItemByID('gui', 'customgame.btn.closeroom');
      [*] = ;var cTextLeaveRoom : String = GetLocaleTableListItemByID('gui', 'customgame.btn.leaveroom');
      [*] = ;var cTextStartGame : String = GetLocaleTableListItemByID('gui', 'customgame.btn.startgame');
      [*] = ;var cTextAlreadyReady : String = GetLocaleTableListItemByID('gui', 'customgame.btn.alreadyready');
      [*] = ;var cTextReady : String = GetLocaleTableListItemByID('gui', 'customgame.btn.ready');
      [*] = ;var cTextKick : String = GetLocaleTableListItemByID('gui', 'customgame.kick');
      [*] = ;var cTextClose : String = GetLocaleTableListItemByID('gui', 'customgame.closed');
      [*] = ;var cTextPlayers : String = GetLocaleTableListItemByID('gui', 'customgame.text.player');
      [*] = ;var cTextNation : String  = GetLocaleTableListItemByID('gui', 'customgame.text.nation');
      [*] = ;var cTextTeam : String  = GetLocaleTableListItemByID('gui', 'customgame.text.team');
      [*] = ;var cTextColor : String  = GetLocaleTableListItemByID('gui', 'customgame.text.color');
      [*] = ;var cTextPing : String  = GetLocaleTableListItemByID('gui', 'internet.ping');
      [*] = ;var cTextRank : String  = GetLocaleTableListItemByID('gui', 'internet.rank');
      [*] = ;var cTextReadyTab : String  = GetLocaleTableListItemByID('gui', 'customgame.text.ready');
      [*] = ;var cTextTerrainType : String = GetLocaleTableListItemByID('gui', 'customgame.text.terraintype');
      [*] = ;var cTextRelief : String = GetLocaleTableListItemByID('gui', 'customgame.text.relieftype');
      [*] = ;var cTextForestsType : String = GetLocaleTableListItemByID('gui', 'customgame.text.foreststype');
      [*] = ;var cTextResources : String = GetLocaleTableListItemByID('gui', 'customgame.text.initialresources');
      [*] = ;var cTextResourceDeposits : String = GetLocaleTableListItemByID('gui', 'customgame.text.minerals');
      [*] = ;var cTextAdditional : String = GetLocaleTableListItemByID('gui', 'customgame.text.additional');
      [*] = ;var cTextSeason : String; _misc_GetNewTextLocale('customgame.text.season', cTextSeason);
      [*] = ;var cTextMapSize : String; _misc_GetNewTextLocale('map.size', cTextMapSize);
      [*] = ;//var cTextOpen : String; _misc_GetNewTextLocale('customgame.ratinggame.open', cTextOpen);
      [*] = ;var cTextOpen : String = GetLocaleTableListItemByID('gui', 'difficulty.0');
      [*] = ;var cTextReserved : String; _misc_GetNewTextLocale('customgame.ratinggame.reserved', cTextReserved);
      [*] = ;var cTextStartAutoSearch : String; _misc_GetNewTextLocale('internetshell.btn.autosearch', cTextStartAutoSearch);
      [*] = ;var cTextStopAutoSearch : String; _misc_GetNewTextLocale('internetshell.btn.stopautosearch', cTextStopAutoSearch);
      [*] = ;var cTextWins : String; _misc_GetNewTextLocale('internetshell.text.wins', cTextWins);
      [*] = ;//...
      [*] = ;
      [*] = ;//creating window of historical battles
      [*] = ;const cWidth = 1018+20;
      [*] = ;const cHeight = 750;
      [*] = ;var elmMain : Integer = _gui_CreateMainWindow(elmname, 0, gc_halParentMiddle, gc_valParentMiddle, 0, 0, cWidth, cHeight, 1, bupdate);
      [*] = ;SetGUIElementPressState(elmMain, eventstate);
      [*] = ;var elmHead : Integer = GetGUIElementIndexByNameParent('head.head', elmMain);
      [*] = ;var elmHnd : Integer = _gui_CreateText('thead', elmHead, cTextHeader, gc_halParentMiddle, gc_valParentMiddle, 9, 3, 0, 28, gc_halMiddle, gc_valMiddle, gc_font_serif_16, color, bupdate);
      [*] = ;_gui_AbsScaleByDPI(elmMain);
      [*] = ;//...
      [*] = ;//creating close button
      [*] = ;var nul : String;
      [*] = ;elmHnd := _gui_CreateButton('bback', elmMain, 'btn.close', gc_halParentRightWidth, gc_valParentTop, 4, -4, 0, 0, eventstate, nul, cTagCloseRoom, bupdate);
      [*] = ;
      [*] = ;//...
      [*] = ;//creating bottom buttons
      [*] = ;var btncount : Integer = _misc_SwitchInt(2, 3, bOnline);
      [*] = ;const btnwidth = 268;
      [*] = ;var posX : Integer = -floor(btnwidth*(btncount-1)/2);
      [*] = ;var posY : Integer = -43;
      [*] = ;//_misc_SwitchString(text, GetLocaleTableListItemByID('misc', 'menu.customgame'), GetLocaleTableListItemByID('misc', 'menu.multiplayerroom'), bOnline);
      [*] = ;var cAddOffsetL : Integer = 20;
      [*] = ;var cAddOffsetX : Integer = 20;
      [*] = ;var cAddParamY : Integer = 29-11;
      [*] = ;
      [*] = ;var text : String;
      [*] = ;_misc_SwitchString(text, cTextBackToMainMenu, cTextSwitchToShell, bOnline);
      [*] = ;var tag : Integer = _misc_SwitchInt(cTagBackToMainMenu, cTagSwitchToShell, bOnline);
      [*] = ;elmHnd := _gui_CreateButton('bbacktomainmenu', elmMain, 'btn.medium', gc_halParentMiddle, gc_valParentBottomHeight, posX+btnwidth, posY, 0, 0, eventstate, nul, tag, bupdate);
      [*] = ;_gui_CreateText('t1', elmHnd, text, gc_halParentMiddle, gc_valParentMiddle, 0, 0, 0, 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;SetGUIElementUserBlend(elmHnd, 0.7);
      [*] = ;
      [*] = ;if (bOnline) then
      [*] = ;begin
      [*] = ;   _misc_SwitchString(text, cTextLeaveRoom, cTextCloseRoom, bServer);
      [*] = ;   elmHnd := _gui_CreateButton('bleaveroom', elmMain, 'btn.medium', gc_halParentMiddle, gc_valParentBottomHeight, posX+btnwidth*2, posY, 0, 0, eventstate, nul, cTagCloseRoom, bupdate);
      [*] = ;   _gui_CreateText('t1', elmHnd, text, gc_halParentMiddle, gc_valParentMiddle, 0, 0, 0, 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;   SetGUIElementUserBlend(elmHnd, 0.7);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   elmHnd := GetGUIElementIndexByNameParent('bleaveroom', elmMain);
      [*] = ;   if (elmHnd<>0) then
      [*] = ;   RemoveGUIElement(elmHnd);
      [*] = ;end;
      [*] = ;// ...
      [*] = ;//creating decorations
      [*] = ;var cPanelAddHeight : Integer = 23;
      [*] = ;var readyTabResize : Integer = 0;
      [*] = ;var pingrankTabResize : Integer = -50;
      [*] = ;var readyTabAdd : Integer = 34;
      [*] = ;var comboboxwidth : Integer = _misc_SwitchInt(222, 222+readyTabResize-readyTabAdd div 2-3, bOnline);
      [*] = ;var shrinkpos : Integer = 30+40;
      [*] = ;
      [*] = ;//PLAYERS
      [*] = ;elmHnd := _gui_CreateSkinHeadWindow('players_topline', elmMain, gc_halParentLeft, gc_valParentTop, 62, 57, 235-readyTabAdd div 2-shrinkpos, bupdate);
      [*] = ;_gui_SetupTColorInteger(255, 220, 170, 255, 1, color);
      [*] = ;text := cTextPlayers; _gui_CreateText('t0',  elmHnd, text, gc_halParentLeft, gc_valParentMiddle, 16, 0, GetGUIElementWidth(elmHnd), 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;// creating players_container
      [*] = ;elmHnd := _gui_CreateSkinWindow('players_container', elmMain, gc_halParentLeft, gc_valParentTop, 62, 90, GetGUIElementWidth(elmHnd)+1, 250, 1, bupdate);
      [*] = ;
      [*] = ;//Position and color TOPLINE
      [*] = ;elmHnd := _gui_CreateSkinHeadWindow('position_team_side_topline', elmMain, gc_halParentLeft, gc_valParentTop, 299-readyTabAdd div 2-shrinkpos, 57, 333+readyTabAdd div 2+shrinkpos, bupdate);
      [*] = ;
      [*] = ;var elmPosText : Integer =_gui_CreateText('t1', elmHnd, cTextPosCol, gc_halParentLeft, gc_valParentMiddle, 16, 0, GetGUIElementWidth(elmHnd), 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;var elmTeamText : Integer = _gui_CreateText('t2', elmHnd, cTextTeam, gc_halParentLeft, gc_valParentMiddle, 245-readyTabAdd+6+shrinkpos, 0, GetGUIElementWidth(elmHnd), 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;var elmColorText : Integer = _gui_CreateText('t3', elmHnd, cTextColor, gc_halParentLeft, gc_valParentMiddle, 294-readyTabAdd+2+shrinkpos, 0, GetGUIElementWidth(elmHnd), 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;var elmReadyText : Integer = _gui_CreateText('t4', elmHnd, cTextReadyTab, gc_halParentLeft, gc_valParentMiddle, 294+45-readyTabAdd+2+shrinkpos, 0, GetGUIElementWidth(elmHnd), 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;// creating position_container
      [*] = ;elmHnd := _gui_CreateSkinWindow('position_container', elmMain, gc_halParentLeft, gc_valParentTop, GetGUIElementPositionX(elmHnd), 90, 238-readyTabAdd+shrinkpos, 250, 1, bupdate);
      [*] = ;// creating team_color_container
      [*] = ;elmHnd := _gui_CreateSkinWindow('team_color_container', elmMain, gc_halParentLeft, gc_valParentTop, 538-readyTabAdd-readyTabAdd div 2, 90, 95+readyTabAdd+readyTabAdd div 2, 250, 1, bupdate);
      [*] = ;// creating map_choose_topline
      [*] = ;elmHnd := _gui_CreateSkinHeadWindow('map_choose_topline', elmMain, gc_halParentLeft, gc_valParentTop, 674-cAddOffsetX+cAddOffsetL, 57, 283+cAddOffsetX, bupdate);
      [*] = ;// creating map_choose_combobox
      [*] = ;var posName : String;
      [*] = ;var pBattles : Integer = _parser_ParserBattles(False);
      [*] = ;if (pBattles=0) then
      [*] = ;exit;
      [*] = ;
      [*] = ;var count : Integer = ParserGetCountByHandle(pBattles);
      [*] = ;var elmComboChooseMap : Integer = _gui_CreateComboBox('mapchooser', elmHnd, count, 0, gc_halParentLeft, gc_valParentTop, 3, 3, GetGUIElementWidth(elmHnd)-6, gc_halLeft, gc_valMiddle, 5, 0, gc_font_serif_12, True, eventstate, bupdate, True);
      [*] = ;SetGUIElementEnabled(elmComboChooseMap, gMap.battlestage=0);
      [*] = ;SetGUIElementUserBlend(elmComboChooseMap, _misc_SwitchFloat(1, 0.7, gMap.battlestage=1));
      [*] = ;SetGUIAllowEvents(elmComboChooseMap, (bServer) and (gMap.battlestage=0), False, False);
      [*] = ;SetGUIElementVisible(GetGUIElementIndexByNameParent('btn', elmComboChooseMap), (gMap.battlestage=0) and bServer);
      [*] = ;//texttmp:='Война за территории Йетти';
      [*] = ;//GUIListBoxAddItem(elmComboChooseMap, texttmp, 0);
      [*] = ;//texttmp:='Война за северные королевства';
      [*] = ;//GUIListBoxAddItem(elmComboChooseMap, texttmp, 1);
      [*] = ;
      [*] = ;const cBattlesLocaleTable = '_battles';
      [*] = ;var activeLocalePath, activePosLocale, activePosLocalePath : String;
      [*] = ;var pPositions : Integer;
      [*] = ;var activepreview, activedescription : String;
      [*] = ;for i:=0 to count-1 do
      [*] = ;begin
      [*] = ;   var pBattle : Integer = ParserSelectByHandleByIndex(pBattles, i);
      [*] = ;   if (pBattle<>0) then
      [*] = ;   begin
      [*] = ;      var name : String = ParserGetValueByKeyByHandle(pBattle, 'Name');
      [*] = ;      var localeName : String = ParserGetValueByKeyByHandle(pBattle, 'LocaleName');
      [*] = ;      var localeDescr : String = ParserGetValueByKeyByHandle(pBattle, 'LocaleDescr');
      [*] = ;      var localePath : String = ParserGetValueByKeyByHandle(pBattle, 'LocalePath');
      [*] = ;      var LocalePositions : String = ParserGetValueByKeyByHandle(pBattle, 'LocalePositions');
      [*] = ;      var LocalePositionsPath : String = ParserGetValueByKeyByHandle(pBattle, 'LocalePositionsPath');
      [*] = ;      var preview : String = ParserGetValueByKeyByHandle(pBattle, 'Preview');
      [*] = ;      var mapPath : String = ParserGetValueByKeyByHandle(pBattle, 'MapPath');
      [*] = ;      var maxPlayers : Integer = ParserGetIntValueByKeyByHandle(pBattle, 'MaxPlayers');
      [*] = ;      if (i=gMap.battleind) then
      [*] = ;      begin
      [*] = ;         pPositions := ParserSelectByHandleByKey(pBattle, 'Positions');
      [*] = ;         activepreview := preview;
      [*] = ;         activedescription := localeDescr;
      [*] = ;         activeLocalePath := localePath;
      [*] = ;         activePosLocale := LocalePositions;
      [*] = ;         activePosLocalePath := LocalePositionsPath;
      [*] = ;         gMap.battlemap := mapPath;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var locInd : Integer = -1;
      [*] = ;      var locale : String;
      [*] = ;      _profile_ConvertConfigValueToLocale(gProfile.lang, locale);
      [*] = ;      localePath := StrReplace(localePath, '%lang%', locale);
      [*] = ;      localePath := StrReplace(localePath, '%locale%', locale);
      [*] = ;      //if (IsFileExists(localePath)) then
      [*] = ;      begin
      [*] = ;         locInd := IndexOfLocaleTableListByFile(localePath);
      [*] = ;         if (locInd<0) and (IsFileExists(localePath)) then
      [*] = ;         locInd := AddLocaleTableList(cBattlesLocaleTable, localePath);
      [*] = ;      end;
      [*] = ;      if (locInd>=0) then
      [*] = ;      begin
      [*] = ;         var locale : String = GetLocaleTableListItemByIndex(locInd, localeName);
      [*] = ;         if locale='' then
      [*] = ;         locale := localeName;
      [*] = ;         GUIListBoxAddItem(elmComboChooseMap, locale, i)
      [*] = ;      end;
      [*] = ;
      [*] = ;      LocalePositionsPath := StrReplace(LocalePositionsPath, '%lang%', locale);
      [*] = ;      LocalePositionsPath := StrReplace(LocalePositionsPath, '%locale%', locale);
      [*] = ;
      [*] = ;      //if (IsFileExists(LocalePositionsPath)) then
      [*] = ;      begin
      [*] = ;         var locPosInd : Integer = IndexOfLocaleTableListByFile(LocalePositionsPath);
      [*] = ;         if (locPosInd<0) and (IsFileExists(LocalePositionsPath)) then
      [*] = ;         locPosInd := AddLocaleTableList(LocalePositions, LocalePositionsPath);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;SetGUIListBoxItemIndexSilent(elmComboChooseMap, gMap.battleind);
      [*] = ;
      [*] = ;//creating map_preview_container
      [*] = ;var elmPreviewHnd : Integer = _gui_CreateSkinWindow('map_preview_container', elmMain, gc_halParentLeft, gc_valParentTop, 674-cAddOffsetX+cAddOffsetL, 57+GetGUIElementHeight(elmHnd), 283+cAddOffsetX, 283-29, 1, bupdate);
      [*] = ;const cpaddingx = 0;
      [*] = ;const cpaddingy = 4;
      [*] = ;
      [*] = ;elmHnd := _gui_CreateImage('preview', elmPreviewHnd, activepreview, gc_halParentLeft, gc_valParentTop, cpaddingx div 2, -1+cpaddingy div 2, GetGUIElementWidth(elmPreviewHnd)-cpaddingx, GetGUIElementHeight(elmPreviewHnd)-cpaddingy, 0, bupdate);
      [*] = ;SetGUIElementVisible(elmHnd, activepreview<>'');
      [*] = ;
      [*] = ;// creating map_description_container
      [*] = ;elmHnd := _gui_CreateSkinWindow('map_description_container', elmMain, gc_halParentLeft, gc_valParentTop, 674-cAddOffsetX+cAddOffsetL, 355+cAddParamY, 283+cAddOffsetX, 283-cAddParamY, 1, bupdate);
      [*] = ;var descriptionparent : Integer;
      [*] = ;if (activepreview<>'') then
      [*] = ;descriptionparent := elmHnd
      [*] = ;else
      [*] = ;descriptionparent := elmPreviewHnd;
      [*] = ;var elmDescriptionScroller : Integer = _gui_CreateScrollLayer('_scrolllayer', descriptionparent, gc_halParentLeft, gc_valParentTop, 0, 2, GetGUIElementWidth(elmHnd), GetGUIElementHeight(elmHnd)-2, 4, 0, 0, 0, True, bupdate);
      [*] = ;SetGUIElementPressState(elmDescriptionScroller, eventstate);
      [*] = ;SetGUIElementCursorByIndex(elmDescriptionScroller, 1);
      [*] = ;activedescription := GetLocaleTableListItemByID('missions', activedescription);
      [*] = ;activedescription := GetGUIWrappedTextFormatByFont(gUIConst.font[gc_font_serif_11], activedescription, GetGUIElementWidth(elmHnd)-30);
      [*] = ;var descrheight : Integer = _gui_GetFontTextHeight(activedescription, gc_font_serif_11);
      [*] = ;_gui_CreateText('tmapdescription', elmDescriptionScroller, activedescription, gc_halParentLeft, gc_valParentTop, 8, 3, 0, 0, gc_halLeft, gc_valMiddle, gc_font_serif_11, color, bupdate);
      [*] = ;SetGUIAllowEvents(elmDescriptionScroller, True, False, False);
      [*] = ;SetGUIElementHeight(elmDescriptionScroller, descrheight);
      [*] = ;var bNeedScroll : Boolean = descrheight>GetGUIElementHeight(elmHnd);
      [*] = ;var scrollHnd : Integer = _gui_AddScroller(elmDescriptionScroller, gc_halParentRightWidth, gc_valParentTop, 0, 20, 0, GetGUIElementHeight(elmHnd), bNeedScroll);
      [*] = ;
      [*] = ;//if bOnline and bShowPingRank then
      [*] = ;//comboboxwidth := comboboxwidth+pingrankTabResize;
      [*] = ;var previewHeight : Integer = GetGUIElementHeight(elmPreviewHnd);
      [*] = ;elmHnd := _gui_CreateMetalLine('mfl_0', elmMain, gc_halParentLeft, gc_valParentTop, 58, 54, 0, 262+cPanelAddHeight, True, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('mfl_1', elmMain, gc_halParentLeft, gc_valParentTop, 670-cAddOffsetX+cAddOffsetL, 54, 0, previewHeight+cPanelAddHeight+11, True, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('mfr_0', elmMain, gc_halParentLeft, gc_valParentTop, 298-readyTabAdd div 2-shrinkpos, 54, 0, 262+cPanelAddHeight, False, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('mfr_1', elmMain, gc_halParentLeft, gc_valParentTop, 540-4-readyTabAdd-readyTabAdd div 2, 54, 0, 262+cPanelAddHeight, False, bupdate);
      [*] = ;//elmHnd := _gui_CreateMetalLine('mfr_4', elmMain, gc_halParentLeft, gc_valParentTop, 638+readyTabResize*2+pingrankTabResize*2, 54, 0, 262+cPanelAddHeight, False, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('mft_2', elmMain, gc_halParentLeft, gc_valParentTop, 61, 90, 578, 0, True, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('mfr_3', elmMain, gc_halParentLeft, gc_valParentTop, 638-5, 54, 0, 262+cPanelAddHeight, True, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('mfr_5', elmMain, gc_halParentLeft, gc_valParentTop, 958+cAddOffsetL, 54, 0, previewHeight+cPanelAddHeight+11, False, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('mft_0', elmMain, gc_halParentLeft, gc_valParentTop, 60, 53, 573, 0, False, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('mft_1', elmMain, gc_halParentLeft, gc_valParentTop, 670-cAddOffsetX+cAddOffsetL, 53, 290+cAddOffsetX, 0, False, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('mfb_0', elmMain, gc_halParentLeft, gc_valParentTop, 58, 316+cPanelAddHeight, 579, 0, True, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('mfb_1', elmMain, gc_halParentLeft, gc_valParentTop, 671-cAddOffsetX+cAddOffsetL, 90-1, 287+cAddOffsetX, 0, True, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('mfb_2', elmMain, gc_halParentLeft, gc_valParentTop, 670-cAddOffsetX+cAddOffsetL, 51+previewHeight+cPanelAddHeight+12, 291+cAddOffsetX, 0, True, bupdate);
      [*] = ;
      [*] = ;elmHnd := _gui_CreateMetalLine('pmfl_1', elmMain, gc_halParentLeft, gc_valParentTop, 670-cAddOffsetX+cAddOffsetL, 352+cAddParamY, 0, 264+cPanelAddHeight-cAddParamY, True, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('pmfr_5', elmMain, gc_halParentLeft, gc_valParentTop, 958+cAddOffsetL, 351+cAddParamY, 0, 266+cPanelAddHeight-cAddParamY, False, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('pmfb_1', elmMain, gc_halParentLeft, gc_valParentTop, 671-cAddOffsetX+cAddOffsetL, 351+cAddParamY, 289+cAddOffsetX, 0, True, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('pmfb_2', elmMain, gc_halParentLeft, gc_valParentTop, 670-cAddOffsetX+cAddOffsetL, 316+cPanelAddHeight+300, 291+cAddOffsetX, 0, True, bupdate);
      [*] = ;
      [*] = ;//...
      [*] = ;// creating players list
      [*] = ;const cOffY : Integer = 29;
      [*] = ;var bRatingGame : Boolean = False;
      [*] = ;// Allow or not allow?
      [*] = ;//...
      [*] = ;for i:=0 to gc_MaxNonSpectatorsCount-1 do
      [*] = ;begin
      [*] = ;   var bAllowChange : Boolean = (gMap.players[i].bexists) and (((bServer) and (gMap.players[i].bai)) or (LanMyInfoID=gMap.players[i].lanid)) and (not bRatingGame) and (gMap.battlestage=0);
      [*] = ;   var bAllowChangePositions : Boolean = (gMap.players[i].bexists) and (LanMyInfoID=gMap.players[i].lanid) and (gMap.battlestage=1);
      [*] = ;   var posy : Integer = 100+i*cOffY;
      [*] = ;   const cminalpha = 0.3;
      [*] = ;   var bMaster : Boolean = (gInternetShell.currentsessionid=gMap.players[i].lanid);
      [*] = ;   if (gMap.players[i].bexists) and (not gMap.players[i].bai) then
      [*] = ;   begin
      [*] = ;      var itemcount : Integer = 1;
      [*] = ;      if (not bMaster) then itemcount := itemcount+2;
      [*] = ;      elmHnd := _gui_CreateComboBox('name|'+IntToStr(i), elmMain, itemcount, 0, gc_halParentLeft, gc_valParentTop, 71, posy, comboboxwidth-shrinkpos, gc_halLeft, gc_valMiddle, 5, 0, gc_font_serif_12, bServer, eventstate, bupdate, True);
      [*] = ;
      [*] = ;      if (gMap.players[i].name<>'') then
      [*] = ;      GUIListBoxAddItem(elmHnd, gMap.players[i].name, i)
      [*] = ;      else
      [*] = ;      GUIListBoxAddItem(elmHnd, UserGetProfileName, -1); // 'Player', {gMap.players[0].name}{
      [*] = ;      if (not bMaster) then
      [*] = ;      begin
      [*] = ;         GUIListBoxAddItem(elmHnd, cTextKick, cTagKick);
      [*] = ;         GUIListBoxAddItem(elmHnd, cTextClose, cTagClose);
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, 0);
      [*] = ;      SetGUIAllowEvents(elmHnd, ((bServer) and (not bMaster) and (not gInternetShell.bautosearch)), False, False);
      [*] = ;      SetGUIElementVisible(GetGUIElementIndexByNameParent('btn', elmHnd), (itemcount>1));
      [*] = ;      SetGUIElementUseUserColor(elmHnd, bClient or gInternetShell.bautosearch);
      [*] = ;      SetGUIElementUserColor(elmHnd, 1, 1, 1, _misc_SwitchFloat(cminalpha, 1, (bOffline) or ((bServer) and (not bMaster) and (not gInternetShell.bautosearch))));
      [*] = ;      SetGUIElementVisible(GetGUIElementIndexByNameParent('btn', elmHnd), False);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      elmHnd := _gui_CreateComboBox('name|'+IntToStr(i), elmMain, 2, 0, gc_halParentLeft, gc_valParentTop, 71, posy, comboboxwidth-shrinkpos, gc_halLeft, gc_valMiddle, 5, 0, gc_font_serif_12, bServer, eventstate, bupdate, True);
      [*] = ;      GUIListBoxAddItem(elmHnd, cTextOpen, -2);
      [*] = ;      GUIListBoxAddItem(elmHnd, cTextClose, cTagClose);
      [*] = ;      if (gMap.players[i].bclosed) then
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, GetGUIListBoxItemIndexOfTag(elmHnd, cTagClose))
      [*] = ;      else
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, 0);
      [*] = ;      SetGUIAllowEvents(elmHnd, ((bServer) and (not bMaster) and (not gInternetShell.bautosearch)), False, False);
      [*] = ;      SetGUIElementVisible(GetGUIElementIndexByNameParent('btn', elmHnd), False);
      [*] = ;      SetGUIElementUseUserColor(elmHnd, bClient or gInternetShell.bautosearch);
      [*] = ;      SetGUIElementUserColor(elmHnd, 1, 1, 1, _misc_SwitchFloat(cminalpha, 1, (bOffline) or ((bServer) and (not bMaster) and (not gInternetShell.bautosearch))));
      [*] = ;      SetGUIElementVisible(GetGUIElementIndexByNameParent('btn', elmHnd), False);
      [*] = ;   end;
      [*] = ;
      [*] = ;   // creating nation picking elements
      [*] = ;   //var bAllowChange : Boolean = (LanMyInfoID=gMap.players[i].lanid) and (gMap.battlestage=0);
      [*] = ;   if (bAllowChange) then
      [*] = ;   gint_net_myindex := i;
      [*] = ;   var elmComboBoxPos : Integer = _gui_CreateComboBox('position|'+IntToStr(i), elmMain, 1, ((GetViewerHeight-14) div 50)+9-i, gc_halParentLeft, gc_valParentTop, 311-readyTabAdd div 2-3-shrinkpos, posy, comboboxwidth-readyTabAdd div 2+shrinkpos, gc_halLeft, gc_valMiddle, 5, 0, gc_font_serif_12, bAllowChange, eventstate, bupdate, True);
      [*] = ;   SetGUIElementFont(elmComboBoxPos, gUIConst.font[gc_font_serif_11]);
      [*] = ;   SetGUIElementVisible(elmComboBoxPos, gMap.players[i].bexists);
      [*] = ;   SetGUIAllowEvents(elmComboBoxPos, False, False, False);
      [*] = ;   SetGUIElementVisible(GetGUIElementIndexByNameParent('btn', elmComboBoxPos), False);
      [*] = ;   if (gMap.battlestage=0) then
      [*] = ;   SetGUIElementUserBlend(elmComboBoxPos, 0.5)
      [*] = ;   else
      [*] = ;   SetGUIElementUserBlend(elmComboBoxPos, _misc_SwitchFloat(1, 0.7, not bAllowChangePositions));
      [*] = ;   if (gMap.players[i].cid<>gc_MaxCountryCount) then
      [*] = ;   begin
      [*] = ;      var posName : String;
      [*] = ;      if (pPositions<>0) then
      [*] = ;      begin
      [*] = ;         var pTeams : Integer;
      [*] = ;         var count : Integer;
      [*] = ;         if (gMap.players[i].team=1) then
      [*] = ;         begin
      [*] = ;            pTeams := ParserSelectByHandleByKey(pPositions, 'Team1');
      [*] = ;            count := countteam1;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            pTeams := ParserSelectByHandleByKey(pPositions, 'Team2');
      [*] = ;            count := countteam2;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var ind : Integer;
      [*] = ;         if (gMap.players[i].team=1) then
      [*] = ;         ind := gMap.players[i].cid
      [*] = ;         else
      [*] = ;         ind := gMap.players[i].cid-4;
      [*] = ;
      [*] = ;         var pPlayersCounts : Integer = ParserSelectByHandleByKey(pTeams, 'PlayersCounts');
      [*] = ;         var pPlayersCount : Integer = ParserSelectByHandleByIndex(pPlayersCounts, count-1);
      [*] = ;         var pPosList : Integer = ParserSelectByHandleByKey(pPlayersCount, 'PosList');
      [*] = ;         var pPosition : Integer = ParserSelectByHandleByIndex(pPosList, ind);
      [*] = ;         if (pPosition<>0) then
      [*] = ;         begin
      [*] = ;            var locInd : Integer = -1;
      [*] = ;            var locale : String;
      [*] = ;            _profile_ConvertConfigValueToLocale(gProfile.lang, locale);
      [*] = ;            activePosLocalePath := StrReplace(activePosLocalePath, '%lang%', locale);
      [*] = ;            activePosLocalePath := StrReplace(activePosLocalePath, '%locale%', locale);
      [*] = ;            //if (IsFileExists(activeLocalePath)) then
      [*] = ;            begin
      [*] = ;               locInd := IndexOfLocaleTableListByFile(activePosLocalePath);
      [*] = ;               if (locInd<0) then
      [*] = ;               locInd := AddLocaleTableList(activePosLocale, activePosLocalePath);
      [*] = ;            end;
      [*] = ;            if (locInd>=0) then
      [*] = ;            begin
      [*] = ;               var localeName : String = ParserGetValueByKeyByHandle(pPosition, 'LocaleName');
      [*] = ;               var locale : String = GetLocaleTableListItemByIndex(locInd, localeName);
      [*] = ;               if locale='' then
      [*] = ;               locale := localeName;
      [*] = ;               GUIListBoxAddItem(elmComboBoxPos, locale, gMap.players[i].cid);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   GUIListBoxAddItem(elmComboBoxPos, GetLocaleTableListItemByID('gui', 'text.random'), 0);
      [*] = ;
      [*] = ;   var j : Integer;
      [*] = ;   for j:=0 to gc_MaxNonSpectatorsCount-1 do
      [*] = ;   if (i<>j) and (gMap.players[i].cid<>gc_MaxCountryCount) and (gMap.players[j].cid<>gc_MaxCountryCount) and (gMap.players[i].cid=gMap.players[j].cid) then
      [*] = ;   begin
      [*] = ;      bSamePos := True;
      [*] = ;      break;
      [*] = ;   end;
      [*] = ;
      [*] = ;   SetGUIListBoxItemIndexSilent(elmComboBoxPos, 0);
      [*] = ;   var elmPosPicker : Integer = _gui_CreateButton('bchangeposition|'+IntToStr(i), elmComboBoxPos, gc_gui_material_blank, gc_halParentLeft, gc_valParentTop, 0, 0, GetGUIElementWidth(elmComboBoxPos), GetGUIElementHeight(elmComboBoxPos), eventstate, nul, cTagChangePosition, bupdate);
      [*] = ;   //SetGUIElementUserBlend(elmPosPicker, 0.1);
      [*] = ;   SetGUIElementEnabled(elmPosPicker, bAllowChangePositions);
      [*] = ;   //...
      [*] = ;   //creating team color active image
      [*] = ;   elmHnd := _gui_CreateImageActive('color|'+IntToStr(i), elmMain, 'customgame.flag.2', gc_halParentLeft, gc_valParentTop, 597-readyTabAdd-readyTabAdd div 2, posy+2, 24+7, 0, cTagBaseTagChangeColor+i, eventstate, '', bupdate);
      [*] = ;   //elmHnd := _gui_CreateComboBox('color|'+IntToStr(i), elmMain, 8, 0, gc_halParentLeft, gc_valParentTop, 597+readyTabResize*2+pingrankTabResize*2, posy, 37, gc_halMiddle, gc_valMiddle, 0, 0, gc_font_serif_12, False, eventstate, bupdate, True);
      [*] = ;   SetGUIElementVisible(elmHnd, gMap.players[i].bexists);
      [*] = ;   //FillComboBoxColors(elmHnd);
      [*] = ;   //SetGUIListBoxItemIndexSilent(elmHnd, gMap.players[i].color);
      [*] = ;   SetGUIAllowEvents(elmHnd, bAllowChange, False, False);
      [*] = ;   SetGUIElementUseUserColor(elmHnd, True);
      [*] = ;   const brightness = 1.1;
      [*] = ;   SetGUIElementUserColor(elmHnd, gKeyColor[gMap.players[i].color][0]*brightness, gKeyColor[gMap.players[i].color][1]*brightness, gKeyColor[gMap.players[i].color][2]*brightness, _misc_SwitchFloat(1, 1, bAllowChange));
      [*] = ;   //...
      [*] = ;   // creating teams picking elements
      [*] = ;   elmHnd := _gui_CreateComboBox('team|'+IntToStr(i), elmMain, countofavailableteams+1, 0, gc_halParentLeft, gc_valParentTop, 548-readyTabAdd-readyTabAdd div 2, posy, 37, gc_halMiddle, gc_valMiddle, 0, 0, gc_font_serif_12, False, eventstate, bupdate, True);
      [*] = ;   SetGUIElementVisible(elmHnd, gMap.players[i].bexists);
      [*] = ;   SetGUIElementVisible(GetGUIElementIndexByNameParent('btn', elmHnd), False);
      [*] = ;   if (gMap.players[i].team=0) then
      [*] = ;   GUIListBoxAddItem(elmHnd, '-', 0)
      [*] = ;   else
      [*] = ;   GUIListBoxAddItem(elmHnd, inttostr(gMap.players[i].team), 0);
      [*] = ;   SetGUIListBoxItemIndexSilent(elmHnd, 0);
      [*] = ;   SetGUIAllowEvents(elmHnd, False, False, False);
      [*] = ;   SetGUIElementUseUserColor(elmHnd, True);
      [*] = ;   SetGUIElementUserColor(elmHnd, 1, 1, 1, _misc_SwitchFloat(cminalpha, 1, bAllowChange));
      [*] = ;   var elmTeamPicker : Integer = _gui_CreateButton('bchangeteam|'+IntToStr(i), elmHnd, gc_gui_material_blank, gc_halParentLeft, gc_valParentTop, 0, 0, GetGUIElementWidth(elmHnd), GetGUIElementHeight(elmHnd), eventstate, nul, cTagChangeTeam, bupdate);
      [*] = ;   //SetGUIElementUserBlend(elmPosPicker, 0.1);
      [*] = ;   SetGUIElementEnabled(elmTeamPicker, bAllowChange);
      [*] = ;
      [*] = ;   // ready
      [*] = ;   elmHnd := _gui_CreateComboBox('ready|'+IntToStr(i), elmMain, 2, 0, gc_halParentLeft, gc_valParentTop, 646+readyTabResize*2-6-readyTabAdd-readyTabAdd div 2, posy, 37, gc_halMiddle, gc_valMiddle, 0, 0, gc_font_serif_12, False, eventstate, bupdate, True);
      [*] = ;   SetGUIElementVisible(elmHnd, (bOnline) and (gMap.players[i].bexists) and (gMap.players[i].bhuman));
      [*] = ;   if (GetGUIListBoxItemsCount(elmHnd)=0) then
      [*] = ;   begin
      [*] = ;      GUIListBoxAddItem(elmHnd, '-', 0);
      [*] = ;      GUIListBoxAddItem(elmHnd, '+', 1);
      [*] = ;   end;
      [*] = ;   var iready : Integer = _misc_SwitchInt(0, 1, (i=0) or ((gMap.players[i].bexists) and (gMap.players[i].bhuman) and (gMap.players[i].bready)));
      [*] = ;   SetGUIListBoxItemIndexSilent(elmHnd, iready);
      [*] = ;   SetGUIAllowEvents(elmHnd, False, False, False);
      [*] = ;   SetGUIElementUseUserColor(elmHnd, True);
      [*] = ;   SetGUIElementUserColor(elmHnd, 1, 1, 1, _misc_SwitchFloat(cminalpha, 1, False));
      [*] = ;   //...
      [*] = ;end;
      [*] = ;
      [*] = ;if (gMap.battlestage=0) then
      [*] = ;begin
      [*] = ;   SetGUIElementUserBlend(elmPosText, 0.5);
      [*] = ;   SetGUIElementUserBlend(elmTeamText, 1);
      [*] = ;   SetGUIElementUserBlend(elmColorText, 1);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   SetGUIElementUserBlend(elmPosText, 1);
      [*] = ;   SetGUIElementUserBlend(elmTeamText, 0.5);
      [*] = ;   SetGUIElementUserBlend(elmColorText, 0.5);
      [*] = ;end;
      [*] = ;
      [*] = ;if bOnline then
      [*] = ;begin
      [*] = ;   const cSessionsMarginLeft = 62;
      [*] = ;   const cChatMarginBottom = 63;
      [*] = ;   //var chatW : Integer = 500;
      [*] = ;   var chatW : Integer = GetGUIElementWidth(GetGUIElementIndexByNameParent('mfb_0t_0', elmMain));
      [*] = ;   var elmChatPlace : Integer = _gui_CreateParent('chatplace', elmMain, gc_halParentLeft, gc_valParentBottomHeight, cSessionsMarginLeft, -cChatMarginBottom-36-48, chatW, 0, bupdate);
      [*] = ;   IntRegister0 := elmChatPlace;
      [*] = ;   IntRegister1 := chatW;
      [*] = ;   ExecuteState('ShowMultiplayerChat');
      [*] = ;   var elmChat : Integer = IntRegister2;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   var elmChatPlace : Integer = GetGUIElementIndexByNameParent('chatplace', elmMain);
      [*] = ;   if (elmChatPlace<>0) then
      [*] = ;   RemoveGUIElement(elmChatPlace);
      [*] = ;end;
      [*] = ;
      [*] = ;var tagstagebtn : Integer;
      [*] = ;if (bOnline and bServer and (gMap.battlestage<>1)) then
      [*] = ;begin
      [*] = ;   tagstagebtn := cTagGoPickPositions;
      [*] = ;   text := GetLocaleTableListItemByID('gui', 'menu.btn.historicalbattle.tostage');
      [*] = ;end
      [*] = ;else
      [*] = ;if (bOnline and bServer and (gMap.battlestage=1)) then
      [*] = ;begin
      [*] = ;   tagstagebtn := cTagStartGame;
      [*] = ;   text := GetLocaleTableListItemByID('gui', 'menu.btn.historicalbattle.startgame');
      [*] = ;end
      [*] = ;else
      [*] = ;if (bOnline and  _net_IsClient and (gMap.battlestage=1)) then
      [*] = ;begin
      [*] = ;   tagstagebtn := cTagReadyGame;
      [*] = ;   text := cTextReady;
      [*] = ;end
      [*] = ;else
      [*] = ;if (bOnline and _net_IsClient and (gMap.battlestage=0)) then
      [*] = ;begin
      [*] = ;   tagstagebtn := cTagReadyGame;
      [*] = ;   text := GetLocaleTableListItemByID('gui', 'menu.btn.historicalbattle.readytostage');
      [*] = ;end;
      [*] = ;
      [*] = ;elmHnd := _gui_CreateButton('bstartgame', elmMain, 'btn.medium', gc_halParentMiddle, gc_valParentBottomHeight, posX, posY, 0, 0, eventstate, nul, tagstagebtn, bupdate);
      [*] = ;_gui_CreateText('t1', elmHnd, text, gc_halParentMiddle, gc_valParentMiddle, 0, 0, 0, 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;var benabled : Boolean = bOffline or (((bClient and bAllowReady and (not bReady)) or (bServer and ((gMap.battlestage=0) or (not bSamePos)) and bAllowNextStage and bAllReady)) and (not gbool_modsyncparserwait));
      [*] = ;SetGUIElementEnabled(elmHnd, benabled);
      [*] = ;SetGUIElementUserBlend(elmHnd, _misc_SwitchFloat(0.7, 1, benabled));
      [*] = ;if not benabled then
      [*] = ;begin
      [*] = ;   if bServer then
      [*] = ;   begin
      [*] = ;      if not bAllReady then
      [*] = ;      SetGUIElementHint(elmHnd, GetLocaleTableListItemByID('gui', 'historicalbattle.warning.notallready'))
      [*] = ;      else
      [*] = ;      if (bTeamUnknown) then
      [*] = ;      SetGUIElementHint(elmHnd, GetLocaleTableListItemByID('gui', 'historicalbattle.warning.notallchooseteam'))
      [*] = ;      else
      [*] = ;      if (gMap.battlestage<>0) and (bSamePos) then
      [*] = ;      SetGUIElementHint(elmHnd, GetLocaleTableListItemByID('gui', 'historicalbattle.warning.playersonepos'))
      [*] = ;      else
      [*] = ;      if (not bTeam1) or (not bTeam2) then
      [*] = ;      SetGUIElementHint(elmHnd, GetLocaleTableListItemByID('gui', 'historicalbattle.warning.playersinoneteam'))
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (not bReady) then
      [*] = ;   SetGUIElementHint(elmHnd, GetLocaleTableListItemByID('gui', 'historicalbattle.warning.chooseteam'));
      [*] = ;end;
      [*] = ;
      [*] = ;SetRandomKey(randkey);
   struct.end
section.end

