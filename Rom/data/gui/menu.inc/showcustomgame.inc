section.begin
   Name = ShowCustomGame
   Code : struct.begin
      [*] = ;if (gInterface.gamemode<>gc_gamemode_mainmenu) or ((_net_IsOnline) and (not gInternetShell.bshowroom)) then
      [*] = ;exit;
      [*] = ;
      [*] = ;procedure ValidateSpectatorCountries();
      [*] = ;begin
      [*] = ;   var totalplayers, totalnonspecplayers : Integer;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;   begin
      [*] = ;      if (gMap.players[i].bexists and gMap.players[i].cid<>gc_spectator_countryid) then
      [*] = ;      totalnonspecplayers := totalnonspecplayers+1;
      [*] = ;      if (gMap.players[i].bexists) then
      [*] = ;      totalplayers := totalplayers+1;
      [*] = ;   end;
      [*] = ;   if (totalnonspecplayers>gc_MaxNonSpectatorsCount) then
      [*] = ;   begin
      [*] = ;      var tmptotalnonspecplayers : Integer;
      [*] = ;      for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;      begin
      [*] = ;         if (gMap.players[i].bexists and gMap.players[i].cid<>gc_spectator_countryid) then
      [*] = ;         begin
      [*] = ;            if tmptotalnonspecplayers>=gc_MaxNonSpectatorsCount then
      [*] = ;            gMap.players[i].cid := gc_spectator_countryid;
      [*] = ;
      [*] = ;            tmptotalnonspecplayers := tmptotalnonspecplayers+1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;ValidateSpectatorCountries;
      [*] = ;
      [*] = ;var bOnline : Boolean = _net_IsOnline;//(gInternetShell.currentsessionid>0);
      [*] = ;var bOffline : Boolean = (not bOnline);
      [*] = ;var bServer : Boolean = _net_IsServer;//(gInternetShell.lanid>0) and (gInternetShell.currentsessionid=gInternetShell.lanid);
      [*] = ;var bClient : Boolean = (bOnline) and (not bServer);
      [*] = ;var bReady, bAllReady : Boolean;
      [*] = ;
      [*] = ;//gMap.settings.gen.season
      [*] = ;var bAllowChange : Boolean = (not bClient);
      [*] = ;var bAllowWinter : Boolean = true;
      [*] = ;var bAllowAutumn : Boolean = true;
      [*] = ;var bAllowSpring : Boolean = true;
      [*] = ;var bAllowDesert : Boolean = true;
      [*] = ;var bAllowChangeSeason : Boolean = (not bClient);
      [*] = ;var bAllowChangeAdviser : Boolean = bAllowChange and (gProfile.lastknowndlcs and gc_lastknowndlc_exp1<>0);
      [*] = ;
      [*] = ;var totalplayers, totalnonspecplayers : Integer;
      [*] = ;var i : Integer;
      [*] = ;for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;begin
      [*] = ;   if (gMap.players[i].bexists and gMap.players[i].cid<>gc_spectator_countryid) then
      [*] = ;   totalnonspecplayers := totalnonspecplayers+1;
      [*] = ;   if (gMap.players[i].bexists) then
      [*] = ;   totalplayers := totalplayers+1;
      [*] = ;end;
      [*] = ;
      [*] = ;if (_net_IsOnline) and (gInternetShell.bautosearch) and (not gInternetShell.bcustomautosearch) then
      [*] = ;begin
      [*] = ;   ErrorLog('ShowCustomGame when gInternetShell.bautosearch=True; set bShowRoom := False');
      [*] = ;   gInternetShell.bshowroom := False;
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure FillComboBoxAIs(elmHnd : Integer);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   if (GetGUIListBoxItemsCount(elmHnd)=0) then
      [*] = ;   begin
      [*] = ;      GUIListBoxAddItem(elmHnd, GetLocaleTableListItemByID('gui', 'difficulty.0'), 0);
      [*] = ;      for i:=1 to gc_MaxAIDifficultyCount do
      [*] = ;      begin
      [*] = ;         var text : String = GetLocaleTableListItemByID('gui', 'difficulty.'+IntToStr(i));
      [*] = ;         GUIListBoxAddItem(elmHnd, text, i);
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, 0);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;procedure FillComboBoxCountries(elmHnd, plInd : Integer; bAddRandom, bAddUnplayable, bAddSpectator, bAddSpectatorOnly : Boolean);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   if (GetGUIListBoxItemsCount(elmHnd)=0) then
      [*] = ;   begin
      [*] = ;      var csid : String;
      [*] = ;      if (not bAddSpectatorOnly) then
      [*] = ;      begin
      [*] = ;         if (bAddRandom) then
      [*] = ;         GUIListBoxAddItem(elmHnd, GetLocaleTableListItemByID('gui', 'text.random'), gc_MaxCountryCount);
      [*] = ;         for i:=0 to gc_MaxCountryCount-1 do
      [*] = ;         begin
      [*] = ;            var bVisibleInEditor, bVisibleInMultiplayer, bPlayable : Boolean;
      [*] = ;            _country_IsCountryAvailable(0, i, gProfile.lastknowndlcs, bVisibleInEditor, bVisibleInMultiplayer, bPlayable);
      [*] = ;            if (bPlayable) or (bVisibleInMultiplayer and bAddUnplayable) then
      [*] = ;            begin
      [*] = ;               _country_GetSIDByID(i, csid);
      [*] = ;               GUIListBoxAddItem(elmHnd, GetLocaleTableListItemByID(gc_loc_units, csid), i);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if (bAddSpectator) then
      [*] = ;      begin
      [*] = ;         var text : String;
      [*] = ;         _misc_GetNewTextLocale('text.spectator', text);
      [*] = ;         GUIListBoxAddItem(elmHnd, text, gc_spectator_countryid);
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, 0);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;procedure FillComboBoxTeams(elmHnd : Integer);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   if (GetGUIListBoxItemsCount(elmHnd)=0) then
      [*] = ;   begin
      [*] = ;      var csid : String;
      [*] = ;      GUIListBoxAddItem(elmHnd, '-', 0);
      [*] = ;      for i:=1 to 4 do
      [*] = ;      GUIListBoxAddItem(elmHnd, IntToStr(i), i);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, 0);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;procedure FillComboBoxColors(elmHnd : Integer);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   if (GetGUIListBoxItemsCount(elmHnd)=0) then
      [*] = ;   begin
      [*] = ;      //AddGUIListBoxTabProperty(elmHnd, 1, 0, 0, 1, 24, 'tsImage');
      [*] = ;      var text : String;
      [*] = ;      for i:=0 to gc_MaxColorCount-1 do
      [*] = ;      GUIListBoxAddItem(elmHnd, IntToStr(i+1), i);
      [*] = ;      //GUIListBoxAddItem(elmHnd, 'customgame.flag.1', i);//'icons.keycolor.'+IntToStr(i+1), i);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;procedure FillComboBoxTerrainTypes(elmHnd : Integer);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   if (GetGUIListBoxItemsCount(elmHnd)=0) then
      [*] = ;   begin
      [*] = ;      for i:=0 to gc_MaxTerrainTypeCount-1 do
      [*] = ;      begin
      [*] = ;         var text : String;
      [*] = ;         if (i<6) then
      [*] = ;         text := GetLocaleTableListItemByID('gui', 'randommap.terraintype.'+IntToStr(i))
      [*] = ;         else
      [*] = ;         _misc_GetNewTextLocale('randommap.terraintype.'+IntToStr(i), text);
      [*] = ;         GUIListBoxAddItem(elmHnd, text, i);
      [*] = ;      end;
      [*] = ;      GUIListBoxAddItem(elmHnd, GetLocaleTableListItemByID('gui', 'text.random'), gc_MaxTerrainTypeCount);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, 1);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;procedure FillComboBoxReliefTypes(elmHnd : Integer);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   if (GetGUIListBoxItemsCount(elmHnd)=0) then
      [*] = ;   begin
      [*] = ;      for i:=0 to gc_MaxReliefTypeCount-1 do
      [*] = ;      begin
      [*] = ;         var text : String = GetLocaleTableListItemByID('gui', 'randommap.relieftype.'+IntToStr(i));
      [*] = ;         GUIListBoxAddItem(elmHnd, text, i);
      [*] = ;      end;
      [*] = ;      GUIListBoxAddItem(elmHnd, GetLocaleTableListItemByID('gui', 'text.random'), gc_MaxReliefTypeCount);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, 1);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;procedure FillComboBoxForestsTypes(elmHnd : Integer);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   if (GetGUIListBoxItemsCount(elmHnd)=0) then
      [*] = ;   begin
      [*] = ;      for i:=0 to gc_MaxForestsTypeCount-1 do
      [*] = ;      begin
      [*] = ;         var text : String = GetLocaleTableListItemByID('gui', 'randommap.foreststype.'+IntToStr(i));
      [*] = ;         GUIListBoxAddItem(elmHnd, text, i);
      [*] = ;      end;
      [*] = ;      GUIListBoxAddItem(elmHnd, GetLocaleTableListItemByID('gui', 'text.random'), gc_MaxForestsTypeCount);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, 1);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;procedure FillComboBoxSeasons(elmHnd : Integer);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   if (GetGUIListBoxItemsCount(elmHnd)=0) then
      [*] = ;   begin
      [*] = ;      for i:=0 to gc_MaxSeasonCount-1 do
      [*] = ;      begin
      [*] = ;         var text : String = GetLocaleTableListItemByID('new', 'randommap.season.'+IntToStr(i));
      [*] = ;         GUIListBoxAddItem(elmHnd, text, i);
      [*] = ;      end;
      [*] = ;      GUIListBoxAddItem(elmHnd, GetLocaleTableListItemByID('gui', 'text.random'), -1);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, 0);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;procedure FillComboBoxResources(elmHnd : Integer);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   if (GetGUIListBoxItemsCount(elmHnd)=0) then
      [*] = ;   begin
      [*] = ;      for i:=0 to gc_MaxResourcesCount-1 do
      [*] = ;      begin
      [*] = ;         var text : String = GetLocaleTableListItemByID('gui', 'randommap.initialresources.'+IntToStr(i));
      [*] = ;         GUIListBoxAddItem(elmHnd, text, i);
      [*] = ;      end;
      [*] = ;      GUIListBoxAddItem(elmHnd, GetLocaleTableListItemByID('gui', 'text.random'), gc_MaxResourcesCount);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, 0);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;procedure FillComboBoxResourceMines(elmHnd : Integer);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   if (GetGUIListBoxItemsCount(elmHnd)=0) then
      [*] = ;   begin
      [*] = ;      for i:=0 to gc_MaxResourceMinesCount-1 do
      [*] = ;      begin
      [*] = ;         var text : String = GetLocaleTableListItemByID('gui', 'randommap.minerals.'+IntToStr(i));
      [*] = ;         GUIListBoxAddItem(elmHnd, text, i);
      [*] = ;      end;
      [*] = ;      GUIListBoxAddItem(elmHnd, GetLocaleTableListItemByID('gui', 'text.random'), gc_MaxResourceMinesCount);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, 1);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;procedure FillComboBoxMapSize(elmHnd : Integer);
      [*] = ;begin
      [*] = ;   var cTextSizeTiny, cTextSizeNormal, cTextSizeBig, cTextSizeLarge, cTextSizeVeryLarge, cTextSizeHuge : String;
      [*] = ;   _misc_GetNewTextLocale('map.size.tiny', cTextSizeTiny);
      [*] = ;   _misc_GetNewTextLocale('map.size.normal', cTextSizeNormal);
      [*] = ;   _misc_GetNewTextLocale('map.size.big', cTextSizeBig);
      [*] = ;   _misc_GetNewTextLocale('map.size.large', cTextSizeLarge);
      [*] = ;   _misc_GetNewTextLocale('map.size.verylarge', cTextSizeVeryLarge);
      [*] = ;   _misc_GetNewTextLocale('map.size.huge', cTextSizeHuge);
      [*] = ;   var i : Integer;
      [*] = ;   if (GetGUIListBoxItemsCount(elmHnd)=0) then
      [*] = ;   begin
      [*] = ;      GUIListBoxAddItem(elmHnd, cTextSizeTiny, 3);
      [*] = ;      GUIListBoxAddItem(elmHnd, cTextSizeNormal, 0);
      [*] = ;      GUIListBoxAddItem(elmHnd, cTextSizeBig, 4);
      [*] = ;      GUIListBoxAddItem(elmHnd, cTextSizeLarge, 1);
      [*] = ;      GUIListBoxAddItem(elmHnd, cTextSizeVeryLarge, 5);
      [*] = ;      GUIListBoxAddItem(elmHnd, cTextSizeHuge, 2);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, 1);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;const bupdate = True;
      [*] = ;const currentstatename = 'ShowCustomGame';
      [*] = ;var elmname, showstate, eventstate : String;
      [*] = ;_misc_GetGUIShowEventStateNames(currentstatename, elmname, showstate, eventstate);
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
      [*] = ;var cPlayerPanelAddHeight, maxplayercount : Integer;
      [*] = ;var cPanelAddHeight : Integer = 23;
      [*] = ;if (bOnline) then
      [*] = ;begin
      [*] = ;   cPlayerPanelAddHeight := 103;
      [*] = ;   maxplayercount := gc_MaxPlayerCount;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   maxplayercount := gc_MaxNonSpectatorsCount+1; // should be 1 more :(
      [*] = ;   cPlayerPanelAddHeight := cPanelAddHeight;
      [*] = ;end;
      [*] = ;
      [*] = ;if (bOnline) then
      [*] = ;begin
      [*] = ;   bAllReady := True;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=1 to maxplayercount-1 do
      [*] = ;   begin
      [*] = ;      if gMap.players[i].bexists and gMap.players[i].bhuman then
      [*] = ;      begin
      [*] = ;         if (LanMyInfoID=gMap.players[i].lanid) then
      [*] = ;         bReady := gMap.players[i].bready;
      [*] = ;         if (bAllReady) and (not gMap.players[i].bready) then
      [*] = ;         bAllReady := False;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;dbgstatename := showstate;
      [*] = ;
      [*] = ;const cTagBackToMainMenu = 101;
      [*] = ;const cTagSwitchToShell = 102;
      [*] = ;const cTagStartGame = 103;
      [*] = ;const cTagCloseRoom = 104;
      [*] = ;const cTagLeaveRoom = 105;
      [*] = ;const cTagReadyGame = 106;
      [*] = ;const cTagStartAutoSearch = 107;
      [*] = ;const cTagStopAutoSearch = 108;
      [*] = ;const cTagBaseTagChangeColor = 200;
      [*] = ;const cTagClose = 500;
      [*] = ;const cTagKick = 1000;
      [*] = ;
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
      [*] = ;
      [*] = ;//const cWidth = 1200; // 1018
      [*] = ;const cWidth = 1018+20; // 1018
      [*] = ;const cHeight = 750; // 624
      [*] = ;var elmMain : Integer = _gui_CreateMainWindow(elmname, 0, gc_halParentMiddle, gc_valParentMiddle, 0, 0, cWidth, cHeight, 1, bupdate);
      [*] = ;SetGUIElementPressState(elmMain, eventstate);
      [*] = ;var elmHead : Integer = GetGUIElementIndexByNameParent('head.head', elmMain);
      [*] = ;_gui_AbsScaleByDPI(elmMain);
      [*] = ;
      [*] = ;var color, tmpcolor : TColor;
      [*] = ;_gui_SetupTColorInteger(255, 220, 170, 255, 0.925, color);
      [*] = ;_gui_SetupTColorInteger(255, 220, 170, 255, 0.825, tmpcolor);
      [*] = ;var text : String;
      [*] = ;_misc_SwitchString(text, GetLocaleTableListItemByID('misc', 'menu.customgame'), GetLocaleTableListItemByID('misc', 'menu.multiplayerroom'), bOnline);
      [*] = ;var elmHnd : Integer = _gui_CreateText('thead', elmHead, text, gc_halParentMiddle, gc_valParentMiddle, 9, 3, 0, 28, gc_halMiddle, gc_valMiddle, gc_font_serif_16, color, bupdate);
      [*] = ;
      [*] = ;// bottom buttons
      [*] = ;var nul : String;
      [*] = ;var tag : Integer;
      [*] = ;tag := _misc_SwitchInt(cTagBackToMainMenu, cTagCloseRoom, bOnline and bServer);
      [*] = ;elmHnd := _gui_CreateButton('bback', elmMain, 'btn.close', gc_halParentRightWidth, gc_valParentTop, 4, -4, 0, 0, eventstate, nul, tag, bupdate);
      [*] = ;
      [*] = ;var btncount : Integer = _misc_SwitchInt(2, 3, bOnline);
      [*] = ;const btnwidth = 268;
      [*] = ;var posX : Integer = -floor(btnwidth*(btncount-1)/2);
      [*] = ;var posY : Integer = -43;
      [*] = ;tag := _misc_SwitchInt(cTagStartGame, cTagReadyGame, bOnline and bClient);
      [*] = ;if (bOnline) then
      [*] = ;begin
      [*] = ;   if bServer then
      [*] = ;   begin
      [*] = ;      tag := _misc_SwitchInt(cTagStartGame, cTagStartAutoSearch, gInternetShell.bratingroom);
      [*] = ;      if gInternetShell.bratingroom then
      [*] = ;      begin
      [*] = ;         tag := _misc_SwitchInt(cTagStartAutoSearch, cTagStopAutoSearch, gInternetShell.bautosearch);
      [*] = ;         if gInternetShell.bautosearch then
      [*] = ;         text := cTextStopAutoSearch
      [*] = ;         else
      [*] = ;         text := cTextStartAutoSearch
      [*] = ;      end
      [*] = ;      else
      [*] = ;      text := cTextStartGame;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if bReady then
      [*] = ;   text := cTextAlreadyReady
      [*] = ;   else
      [*] = ;   text := cTextReady;
      [*] = ;end
      [*] = ;else
      [*] = ;text := cTextStartGame;
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
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to maxplayercount-1 do
      [*] = ;   begin
      [*] = ;      if (i<>testplayer) and (gMap.players[i].bexists) and (gMap.players[i].color=newtestcolor) then
      [*] = ;      begin
      [*] = ;         Result := CheckDoubleColor(testplayer, newtestcolor, True, bDirectionForward);
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;for i:=0 to maxplayercount-1 do
      [*] = ;gMap.players[i].color := CheckDoubleColor(i, gMap.players[i].color, False, True);
      [*] = ;
      [*] = ;elmHnd := _gui_CreateButton('bstartgame', elmMain, 'btn.medium', gc_halParentMiddle, gc_valParentBottomHeight, posX, posY, 0, 0, eventstate, nul, tag, bupdate);
      [*] = ;_gui_CreateText('t1', elmHnd, text, gc_halParentMiddle, gc_valParentMiddle, 0, 0, 0, 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;SetGUIElementEnabled(elmHnd, bOffline or (((bClient and not bReady) or (bServer and bAllReady)) and (not gbool_modsyncparserwait)));
      [*] = ;SetGUIElementUserBlend(elmHnd, _misc_SwitchFloat(0.7, 1, GetGUIElementEnabled(elmHnd)));
      [*] = ;
      [*] = ;_misc_SwitchString(text, cTextBackToMainMenu, cTextSwitchToShell, bOnline);
      [*] = ;tag := _misc_SwitchInt(cTagBackToMainMenu, cTagSwitchToShell, bOnline);
      [*] = ;elmHnd := _gui_CreateButton('bbacktomainmenu', elmMain, 'btn.medium', gc_halParentMiddle, gc_valParentBottomHeight, posX+btnwidth, posY, 0, 0, eventstate, nul, tag, bupdate);
      [*] = ;_gui_CreateText('t1', elmHnd, text, gc_halParentMiddle, gc_valParentMiddle, 0, 0, 0, 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;SetGUIElementUserBlend(elmHnd, 0.7);
      [*] = ;
      [*] = ;if (bOnline) then
      [*] = ;begin
      [*] = ;   tag := _misc_SwitchInt(cTagLeaveRoom, cTagCloseRoom, bServer);
      [*] = ;   _misc_SwitchString(text, cTextLeaveRoom, cTextCloseRoom, bServer);
      [*] = ;   elmHnd := _gui_CreateButton('bleaveroom', elmMain, 'btn.medium', gc_halParentMiddle, gc_valParentBottomHeight, posX+btnwidth*2, posY, 0, 0, eventstate, nul, tag, bupdate);
      [*] = ;   _gui_CreateText('t1', elmHnd, text, gc_halParentMiddle, gc_valParentMiddle, 0, 0, 0, 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;   SetGUIElementUserBlend(elmHnd, 0.7);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   elmHnd := GetGUIElementIndexByNameParent('bleaveroom', elmMain);
      [*] = ;   if (elmHnd<>0) then
      [*] = ;   RemoveGUIElement(elmHnd);
      [*] = ;end;
      [*] = ;
      [*] = ;var bShowPingRank : Boolean = bOnline;
      [*] = ;
      [*] = ;var readyTabResize : Integer = _misc_SwitchInt(0, -50 div 2, bOnline);
      [*] = ;var pingrankTabResize : Integer = _misc_SwitchInt(0, 2*-50 div 2, bShowPingRank);
      [*] = ;var comboboxwidth : Integer = _misc_SwitchInt(222, 222+readyTabResize, bOnline);
      [*] = ;if bOnline and bShowPingRank then
      [*] = ;comboboxwidth := comboboxwidth+pingrankTabResize;
      [*] = ;
      [*] = ;// decorations
      [*] = ;elmHnd := _gui_CreateSkinHeadWindow('sh_0', elmMain, gc_halParentLeft, gc_valParentTop, 62, 57, 235+readyTabResize+pingrankTabResize, bupdate);
      [*] = ;_gui_SetupTColorInteger(255, 220, 170, 255, 1, color);
      [*] = ;text := cTextPlayers; _gui_CreateText('t0',  elmHnd, text, gc_halParentLeft, gc_valParentMiddle, 16, 0, GetGUIElementWidth(elmHnd), 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;
      [*] = ;var cAddOffsetL : Integer = 20;
      [*] = ;var cAddOffsetX : Integer = 20;
      [*] = ;var cAddParamY : Integer = 29;
      [*] = ;elmHnd := _gui_CreateSkinWindow('s_0', elmMain, gc_halParentLeft, gc_valParentTop, 62, 94, GetGUIElementWidth(elmHnd)+1, 222+cPlayerPanelAddHeight, 1, bupdate);
      [*] = ;elmHnd := _gui_CreateSkinHeadWindow('sh_1', elmMain, gc_halParentLeft, gc_valParentTop, 304+readyTabResize+pingrankTabResize, 57, 333-readyTabResize-pingrankTabResize, bupdate);
      [*] = ;_gui_CreateText('t1', elmHnd, cTextNation, gc_halParentLeft, gc_valParentMiddle, 16, 0, GetGUIElementWidth(elmHnd), 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;_gui_CreateText('t2', elmHnd, cTextTeam, gc_halParentLeft, gc_valParentMiddle, 245+readyTabResize+pingrankTabResize+2, 0, GetGUIElementWidth(elmHnd), 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;_gui_CreateText('t3', elmHnd, cTextColor, gc_halParentLeft, gc_valParentMiddle, 294+readyTabResize+pingrankTabResize-2, 0, GetGUIElementWidth(elmHnd), 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;var elmTmp : Integer = _gui_CreateText('t4', elmHnd, cTextWins, gc_halParentLeft, gc_valParentMiddle, 294+readyTabResize+2, 0, GetGUIElementWidth(elmHnd), 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;SetGUIElementVisible(elmTmp, bShowPingRank);
      [*] = ;elmTmp := _gui_CreateText('t5', elmHnd, cTextPing, gc_halParentLeft, gc_valParentMiddle, 294+readyTabResize-pingrankTabResize+1, 0, GetGUIElementWidth(elmHnd), 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;SetGUIElementVisible(elmTmp, bShowPingRank);
      [*] = ;elmTmp := _gui_CreateText('t6', elmHnd, cTextReadyTab, gc_halParentLeft, gc_valParentMiddle, 294-readyTabResize-pingrankTabResize-4, 0, GetGUIElementWidth(elmHnd), 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;SetGUIElementVisible(elmTmp, bOnline);
      [*] = ;elmHnd := _gui_CreateSkinWindow('s_1', elmMain, gc_halParentLeft, gc_valParentTop, 302+readyTabResize+pingrankTabResize, 94, 238+readyTabResize+pingrankTabResize, 222+cPlayerPanelAddHeight, 1, bupdate);
      [*] = ;elmHnd := _gui_CreateSkinWindow('s_2', elmMain, gc_halParentLeft, gc_valParentTop, 544+readyTabResize*2+pingrankTabResize*2, 94, 45+45+5, 222+cPlayerPanelAddHeight, 1, bupdate);
      [*] = ;if bShowPingRank then
      [*] = ;elmHnd := _gui_CreateSkinWindow('s_3', elmMain, gc_halParentLeft, gc_valParentTop, 593+readyTabResize*2+pingrankTabResize, 94, 45+45+5-pingrankTabResize, 222+cPlayerPanelAddHeight, 1, bupdate)
      [*] = ;else
      [*] = ;elmHnd := _gui_CreateSkinWindow('s_3', elmMain, gc_halParentLeft, gc_valParentTop, 593{readyTabResize*2}+pingrankTabResize, 94, 45+{45+5-}pingrankTabResize, 222+cPanelAddHeight, 1, bupdate);
      [*] = ;// Color //elmHnd := _gui_CreateSkinWindow('s_5', elmMain, gc_halParentLeft, gc_valParentTop, 642+readyTabResize*2+pingrankTabResize*2, 94, 45, 222+cPanelAddHeight, 1, bupdate);
      [*] = ;SetGUIElementVisible(elmHnd, bOnline);
      [*] = ;elmHnd := _gui_CreateSkinHeadWindow('sh_2', elmMain, gc_halParentLeft, gc_valParentTop, 674-cAddOffsetX+cAddOffsetL, 57, 283+cAddOffsetX, bupdate);
      [*] = ;text := GetLocaleTableListItemByID('gui', 'settings.text.header'); _gui_CreateText('t4', elmHnd, text, gc_halParentLeft, gc_valParentMiddle, 16, 0, GetGUIElementWidth(elmHnd), 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;elmHnd := _gui_CreateSkinWindow('s_4', elmMain, gc_halParentLeft, gc_valParentTop, 674-cAddOffsetX+cAddOffsetL, 94, GetGUIElementWidth(elmHnd), 250+cPanelAddHeight+cAddParamY, 1, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('mfl_0', elmMain, gc_halParentLeft, gc_valParentTop, 58, 54, 0, 262+cPlayerPanelAddHeight, True, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('mfl_1', elmMain, gc_halParentLeft, gc_valParentTop, 670-cAddOffsetX+cAddOffsetL, 54, 0, 290+cPanelAddHeight+cAddParamY, True, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('mfr_0', elmMain, gc_halParentLeft, gc_valParentTop, 298+readyTabResize+pingrankTabResize, 54, 0, 262+cPlayerPanelAddHeight, False, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('mfr_1', elmMain, gc_halParentLeft, gc_valParentTop, 540+readyTabResize*2+pingrankTabResize*2, 54, 0, 262+cPlayerPanelAddHeight, False, bupdate);
      [*] = ;// Team-Color //elmHnd := _gui_CreateMetalLine('mfr_2', elmMain, gc_halParentLeft, gc_valParentTop, 589+readyTabResize*2+pingrankTabResize*2, 54, 0, 262+cPanelAddHeight, False, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('mfr_4', elmMain, gc_halParentLeft, gc_valParentTop, 638+readyTabResize*2+pingrankTabResize*2, 54, 0, 262+cPlayerPanelAddHeight, False, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('mft_2', elmMain, gc_halParentLeft, gc_valParentTop, 61, 90, 578, 0, True, bupdate);
      [*] = ;//elmHnd := _gui_CreateMetalLine('mfr_3', elmMain, gc_halParentLeft, gc_valParentTop, 638, 54, 0, 262+cPanelAddHeight, False, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('mfr_3', elmMain, gc_halParentLeft, gc_valParentTop, 638+1, 54, 0, 262+cPlayerPanelAddHeight, True, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('mfr_5', elmMain, gc_halParentLeft, gc_valParentTop, 958+cAddOffsetL, 54, 0, 290+cPanelAddHeight+cAddParamY, False, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('mft_0', elmMain, gc_halParentLeft, gc_valParentTop, 60, 53, 580, 0, False, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('mft_1', elmMain, gc_halParentLeft, gc_valParentTop, 670-cAddOffsetX+cAddOffsetL, 53, 290+cAddOffsetX, 0, False, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('mfb_0', elmMain, gc_halParentLeft, gc_valParentTop, 58, 316+cPlayerPanelAddHeight, 583, 0, True, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('mfb_1', elmMain, gc_halParentLeft, gc_valParentTop, 671-cAddOffsetX+cAddOffsetL, 90, 287+cAddOffsetX, 0, True, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('mfb_2', elmMain, gc_halParentLeft, gc_valParentTop, 670-cAddOffsetX+cAddOffsetL, 344+cPanelAddHeight+cAddParamY, 291+cAddOffsetX, 0, True, bupdate);
      [*] = ;
      [*] = ;//elmHnd := _gui_CreateSkinHeadWindow('sh_3', elmMain, gc_halParentLeft, gc_valParentTop, 674, 57+dbgy, 283, bupdate);
      [*] = ;//text := 'Map Settings'; _gui_CreateText('t1', elmHnd, text, gc_halParentLeft, gc_valParentMiddle, 16, 0, GetGUIElementWidth(elmHnd), 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;{elmHnd := _gui_CreateSkinWindow('s_6', elmMain, gc_halParentLeft, gc_valParentTop, 674-cAddOffsetX+cAddOffsetL, 355+cAddParamY, 283+cAddOffsetX, 283-cAddParamY, 1, bupdate);
      [*] = ;//SetGUIElementUserBlend(elmHnd, 0.7); // while not implemented
      [*] = ;elmHnd := _gui_CreateMetalLine('pmfl_1', elmMain, gc_halParentLeft, gc_valParentTop, 670-cAddOffsetX+cAddOffsetL, 352+cAddParamY, 0, 264+cPanelAddHeight-cAddParamY, True, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('pmfr_5', elmMain, gc_halParentLeft, gc_valParentTop, 958+cAddOffsetL, 351+cAddParamY, 0, 266+cPanelAddHeight-cAddParamY, False, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('pmfb_1', elmMain, gc_halParentLeft, gc_valParentTop, 671-cAddOffsetX+cAddOffsetL, 351+cAddParamY, 289+cAddOffsetX, 0, True, bupdate);
      [*] = ;elmHnd := _gui_CreateMetalLine('pmfb_2', elmMain, gc_halParentLeft, gc_valParentTop, 670-cAddOffsetX+cAddOffsetL, 316+cPanelAddHeight+300, 291+cAddOffsetX, 0, True, bupdate);
      [*] = ;}
      [*] = ;var randkey : Integer = GetRandomKey;
      [*] = ;SetRandomKey(260); // used in combobox render
      [*] = ;
      [*] = ;var bRatingGame : Boolean;
      [*] = ;if (bOnline) then
      [*] = ;begin
      [*] = ;   bRatingGame := gInternetShell.bratingroom;
      [*] = ;   var playerind : Integer;
      [*] = ;   {for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;   begin
      [*] = ;      //gMap.players[i].lanid := 0;
      [*] = ;      //gMap.players[i].name := '';
      [*] = ;      //gMap.players[i].bexists := False;
      [*] = ;      //gMap.players[i].bhuman := False;
      [*] = ;   end;}
      [*] = ;   //_misc_InternetShellRefreshCurrentSession(gInternetShell, True);
      [*] = ;   for i:=0 to maxplayercount-1 do
      [*] = ;   begin
      [*] = ;      //gMap.players[i].lanid := gInternetShell.currentsession.list[playerind];
      [*] = ;      if (not gMap.players[i].bai) and (gMap.players[i].lanid>0) then
      [*] = ;      begin
      [*] = ;         var pclient : Pointer = gInternetShell.clients.GetByLanID(gMap.players[i].lanid);
      [*] = ;         if (pclient<>nil) then
      [*] = ;         begin
      [*] = ;            gMap.players[i].name := TInternetShellClient(pclient).nick;
      [*] = ;            gMap.players[i].bai := False;
      [*] = ;            gMap.players[i].bhuman := True;
      [*] = ;            playerind := playerind+1;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         gMap.players[i].bexists := False;
      [*] = ;      end;
      [*] = ;      gMap.players[i].bexists := (gMap.players[i].bai) or (gMap.players[i].bhuman);
      [*] = ;   end;
      [*] = ;   for i:=0 to maxplayercount-1 do
      [*] = ;   begin
      [*] = ;      elmHnd := GetGUIElementIndexByNameParent('name|'+IntToStr(i), elmMain);
      [*] = ;      if elmHnd<>0 then
      [*] = ;      RemoveGUIElement(elmHnd);
      [*] = ;      elmHnd := GetGUIElementIndexByNameParent('ai|'+IntToStr(i), elmMain);
      [*] = ;      if elmHnd<>0 then
      [*] = ;      RemoveGUIElement(elmHnd);
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;gMap.players[0].name := UserGetProfileName;
      [*] = ;
      [*] = ;const cOffY : Integer = 29;
      [*] = ;var curplayers : Integer;
      [*] = ;for i:=0 to maxplayercount-2 do
      [*] = ;begin
      [*] = ;   var posy : Integer = 103+i*cOffY;
      [*] = ;   const cminalpha = 0.3;
      [*] = ;   var bMaster : Boolean = (gInternetShell.currentsessionid=gMap.players[i].lanid);
      [*] = ;   {if (curplayers>=gc_MaxNonSpectatorsCount-1) then
      [*] = ;   begin
      [*] = ;      elmHnd := _gui_CreateComboBox('unused|'+IntToStr(i), elmMain, 2, 0, gc_halParentLeft, gc_valParentTop, 71, posy, comboboxwidth, gc_halLeft, gc_valMiddle, 5, 0, gc_font_serif_12, bServer, eventstate, bupdate, True);
      [*] = ;   end
      [*] = ;   else}
      [*] = ;   if (gMap.players[i].bexists) and (gMap.players[i].cid<>gc_spectator_countryid) then
      [*] = ;   curplayers := curplayers+1;
      [*] = ;
      [*] = ;   var bok : Boolean = (totalnonspecplayers<gc_MaxNonSpectatorsCount);
      [*] = ;   var bnearok : Boolean = (curplayers<=gc_MaxNonSpectatorsCount);
      [*] = ;   var baicountok : Boolean = (totalnonspecplayers<gc_MaxNonSpectatorsCount);
      [*] = ;   if ((gMap.players[i].bexists) and (not gMap.players[i].bai)) then
      [*] = ;   begin
      [*] = ;      var itemcount : Integer = 1;
      [*] = ;      if (not bMaster) then itemcount := itemcount+2;
      [*] = ;      elmHnd := _gui_CreateComboBox('name|'+IntToStr(i), elmMain, itemcount, 0, gc_halParentLeft, gc_valParentTop, 71, posy, comboboxwidth, gc_halLeft, gc_valMiddle, 5, 0, gc_font_serif_12, bServer, eventstate, bupdate, True);
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
      [*] = ;      SetGUIElementVisible(GetGUIElementIndexByNameParent('btn', elmHnd), not gInternetShell.bautosearch);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var itemcount : Integer = 5;
      [*] = ;      if (not bMaster) and (bServer) then itemcount := itemcount+1;
      [*] = ;
      [*] = ;      var bAllow : Boolean = (bOffline) or ((bServer) and (not bMaster));
      [*] = ;      bAllow := bAllow and ((not bRatingGame) or (i<(gint_quickplay_countofplayers div 2))) and (not gInternetShell.bautosearch);
      [*] = ;
      [*] = ;      // remove for unlimit 8 players
      [*] = ;      if (i=maxplayercount-1) then
      [*] = ;      elmHnd := _gui_CreateComboBox('ai|'+IntToStr(i), elmMain, 0, 0, gc_halParentLeft, gc_valParentTop, 71, posy, comboboxwidth, gc_halLeft, gc_valMiddle, 5, 0, gc_font_serif_12, False, eventstate, bupdate, True)
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if bRatingGame or (not baicountok and not gMap.players[i].bai) then
      [*] = ;         itemcount := 2;
      [*] = ;         elmHnd := _gui_CreateComboBox('ai|'+IntToStr(i), elmMain, itemcount, 0, gc_halParentLeft, gc_valParentTop, 71, posy, comboboxwidth, gc_halLeft, gc_valMiddle, 5, 0, gc_font_serif_12, (bOffline) or ((bServer) and ((not bRatingGame) or (i<(gint_quickplay_countofplayers div 2)))), eventstate, bupdate, True);
      [*] = ;
      [*] = ;         if (not bRatingGame) and (baicountok or (gMap.players[i].bai)) then
      [*] = ;         FillComboBoxAIs(elmHnd);
      [*] = ;
      [*] = ;         SetGUIElementUserColor(elmHnd, 1, 1, 1, _misc_SwitchFloat(cminalpha, 1, bAllow));
      [*] = ;         SetGUIElementVisible(GetGUIElementIndexByNameParent('btn', elmHnd), not gInternetShell.bautosearch);
      [*] = ;
      [*] = ;         if (bRatingGame) then
      [*] = ;         begin
      [*] = ;            if i<(gint_quickplay_countofplayers div 2) then
      [*] = ;            GUIListBoxAddItem(elmHnd, cTextOpen, -2)
      [*] = ;            else
      [*] = ;            if (i>=(gint_quickplay_countofplayers div 2)) and (i<gint_quickplay_countofplayers) then
      [*] = ;            GUIListBoxAddItem(elmHnd, cTextReserved, -2);
      [*] = ;            SetGUIListBoxItemIndexSilent(elmHnd, GetGUIListBoxItemIndexOfTag(elmHnd, -2));
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if (not baicountok) and (not gMap.players[i].bai) then
      [*] = ;         begin
      [*] = ;            GUIListBoxAddItem(elmHnd, cTextOpen, -2);
      [*] = ;            SetGUIListBoxItemIndexSilent(elmHnd, GetGUIListBoxItemIndexOfTag(elmHnd, -2));
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if (not bMaster) then
      [*] = ;      begin
      [*] = ;         GUIListBoxAddItem(elmHnd, cTextClose, cTagClose);
      [*] = ;         if (gMap.players[i].bclosed) then
      [*] = ;         begin
      [*] = ;            if (bRatingGame) and (i>=gint_quickplay_countofplayers div 2) then
      [*] = ;            SetGUIListBoxItemIndexSilent(elmHnd, 0)
      [*] = ;            else
      [*] = ;            SetGUIListBoxItemIndexSilent(elmHnd, GetGUIListBoxItemIndexOfTag(elmHnd, cTagClose));
      [*] = ;         end;
      [*] = ;         if (gMap.players[i].bai) then
      [*] = ;         SetGUIListBoxItemIndexSilent(elmHnd, gMap.players[i].aidifficulty+1);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (gMap.players[i].bai) then
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, gMap.players[i].aidifficulty+1);
      [*] = ;
      [*] = ;      SetGUIAllowEvents(elmHnd, bAllow, False, False);
      [*] = ;
      [*] = ;      // remove for unlimit 8 players
      [*] = ;      if (i=maxplayercount-1) then
      [*] = ;      SetGUIAllowEvents(elmHnd, False, False, False);
      [*] = ;
      [*] = ;      SetGUIElementUseUserColor(elmHnd, bClient or bRatingGame);
      [*] = ;      //SetGUIElementUserColor(elmHnd, 1, 1, 1, _misc_SwitchFloat(cminalpha, 1, (bOffline) or ((bServer) and (not bMaster))));
      [*] = ;      //SetGUIElementVisible(elmHnd, (bServer) or (gMap.players[i].bexists));
      [*] = ;   end;
      [*] = ;   var bAllowSpectator : Boolean = (_net_IsOnline and (not gMap.players[i].bai));
      [*] = ;
      [*] = ;   var bAllowChange : Boolean = (gMap.players[i].bexists) and (((bServer) and (gMap.players[i].bai)) or (LanMyInfoID=gMap.players[i].lanid)) and not bRatingGame;
      [*] = ;   var showcount : Integer = gint_maxcountrycountplayable+1;
      [*] = ;   if (not bok) and (gMap.players[i].cid=gc_spectator_countryid) then
      [*] = ;   showcount := 0;
      [*] = ;   if bAllowSpectator then
      [*] = ;   showcount := showcount+1;
      [*] = ;   elmHnd := _gui_CreateComboBox('country|'+IntToStr(i), elmMain, showcount, ((GetViewerHeight-14) div 50)+9-i, gc_halParentLeft, gc_valParentTop, 311+readyTabResize+pingrankTabResize, posy, comboboxwidth, gc_halLeft, gc_valMiddle, 5, 0, gc_font_serif_12, bAllowChange, eventstate, bupdate, True);
      [*] = ;   SetGUIElementVisible(elmHnd, gMap.players[i].bexists or (bRatingGame and (i>=(gint_quickplay_countofplayers div 2)) and i<gint_quickplay_countofplayers));
      [*] = ;   FillComboBoxCountries(elmHnd, i, True, not bAllowChange, bAllowSpectator, (not bok) and (gMap.players[i].cid=gc_spectator_countryid));
      [*] = ;
      [*] = ;   if (not bAllowSpectator) and (gMap.players[i].cid=gc_spectator_countryid) then
      [*] = ;   gMap.players[i].cid := gc_MaxCountryCount;
      [*] = ;   var tagind : Integer = GetGUIListBoxItemIndexOfTag(elmHnd, gMap.players[i].cid);
      [*] = ;   SetGUIListBoxItemIndexSilent(elmHnd, tagind);
      [*] = ;   SetGUIAllowEvents(elmHnd, bAllowChange, False, False);
      [*] = ;   SetGUIElementUseUserColor(elmHnd, True);
      [*] = ;   SetGUIElementUserColor(elmHnd, 1, 1, 1, _misc_SwitchFloat(cminalpha, 1, bAllowChange));
      [*] = ;
      [*] = ;   var bvisible : Boolean = gMap.players[i].bexists or ((bRatingGame) and (i>=0) and (i<gint_quickplay_countofplayers));
      [*] = ;
      [*] = ;   elmHnd := _gui_CreateComboBox('team|'+IntToStr(i), elmMain, 5, 0, gc_halParentLeft, gc_valParentTop, 548+readyTabResize*2+pingrankTabResize*2+3, posy, 37, gc_halMiddle, gc_valMiddle, 0, 0, gc_font_serif_12, False, eventstate, bupdate, True);
      [*] = ;   SetGUIElementVisible(elmHnd, bvisible);
      [*] = ;   SetGUIElementVisible(GetGUIElementIndexByNameParent('btn', elmHnd), False);
      [*] = ;   FillComboBoxTeams(elmHnd);
      [*] = ;   if (gMap.players[i].team>gc_MaxNonSpectatorsCount div 2) then
      [*] = ;   SetGUIListBoxItemIndexSilent(elmHnd, 0)
      [*] = ;   else
      [*] = ;   SetGUIListBoxItemIndexSilent(elmHnd, gMap.players[i].team);
      [*] = ;   SetGUIAllowEvents(elmHnd, bAllowChange, False, False);
      [*] = ;   SetGUIElementUseUserColor(elmHnd, True);
      [*] = ;   SetGUIElementUserColor(elmHnd, 1, 1, 1, _misc_SwitchFloat(cminalpha, 1, bAllowChange));
      [*] = ;
      [*] = ;   elmHnd := _gui_CreateImageActive('color|'+IntToStr(i), elmMain, 'customgame.flag.2', gc_halParentLeft, gc_valParentTop, 597+readyTabResize*2+pingrankTabResize*2+1, posy+2, 24+7, 0, cTagBaseTagChangeColor+i, eventstate, '', bupdate);
      [*] = ;   //elmHnd := _gui_CreateComboBox('color|'+IntToStr(i), elmMain, 8, 0, gc_halParentLeft, gc_valParentTop, 597+readyTabResize*2+pingrankTabResize*2, posy, 37, gc_halMiddle, gc_valMiddle, 0, 0, gc_font_serif_12, False, eventstate, bupdate, True);
      [*] = ;   SetGUIElementVisible(elmHnd, gMap.players[i].bexists);
      [*] = ;   //FillComboBoxColors(elmHnd);
      [*] = ;   //SetGUIListBoxItemIndexSilent(elmHnd, gMap.players[i].color);
      [*] = ;   SetGUIAllowEvents(elmHnd, bAllowChange, False, False);
      [*] = ;   SetGUIElementUseUserColor(elmHnd, True);
      [*] = ;   const brightness = 1.1;
      [*] = ;   SetGUIElementUserColor(elmHnd, gKeyColor[gMap.players[i].color][0]*brightness, gKeyColor[gMap.players[i].color][1]*brightness, gKeyColor[gMap.players[i].color][2]*brightness, _misc_SwitchFloat(1, 1, bAllowChange));
      [*] = ;
      [*] = ;   var pclient : Pointer = gInternetShell.clients.GetByLanID(gMap.players[i].lanid);
      [*] = ;   var score, ping, wins, games : Integer;
      [*] = ;
      [*] = ;   if (pclient<>nil) then
      [*] = ;   begin
      [*] = ;      var ps, pw, pg : Integer;
      [*] = ;      _misc_GetInfoFromCountry(TInternetShellClient(pclient).country, ps, pw, pg);
      [*] = ;      var nick : String = TInternetShellClient(pclient).nick;
      [*] = ;      score := TInternetShellClient(pclient).score+ps;
      [*] = ;      //ping := TInternetShellClient(pclient).ping;
      [*] = ;      ping := LanPublicServerGetClientPingtimeByClientID(gMap.players[i].lanid);
      [*] = ;      if ping>999 then ping := 999;
      [*] = ;      wins := TInternetShellClient(pclient).gameswin+pw;
      [*] = ;      games := TInternetShellClient(pclient).gamesplayed+pg;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var rank : Integer = _misc_GetRankByScoreELO(score);
      [*] = ;   var srank : String = 'net.client.rank.'+IntToStr(rank+1);
      [*] = ;   var swins : String = IntToStr(wins);
      [*] = ;   //_misc_IntToRoman(rank, srank);
      [*] = ;   // rank
      [*] = ;   elmHnd := _gui_CreateText('rank|'+IntToStr(i), elmMain, swins, gc_halParentLeft, gc_valParentTop, 597+readyTabResize*2+pingrankTabResize*1, posy+2, 24+7, 0, gc_halMiddle, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;   //elmHnd := _gui_CreateImageActive('rank|'+IntToStr(i), elmMain, srank, gc_halParentLeft, gc_valParentTop, 597+readyTabResize*2+pingrankTabResize*1+7, posy-1, 0, 0, 0, '', 'misc|inet.rank.'+IntToStr(rank), bupdate);
      [*] = ;   SetGUIElementVisible(elmHnd, (wins>0) and (bOnline) and (gMap.players[i].bexists) and (gMap.players[i].bhuman));
      [*] = ;   // ping
      [*] = ;   var sping : String;
      [*] = ;   if ping>999 then
      [*] = ;   sping := '999+'
      [*] = ;   else
      [*] = ;   if ping>0 then
      [*] = ;   sping := IntToStr(ping);
      [*] = ;   elmHnd := _gui_CreateText('ping|'+IntToStr(i), elmMain, sping, gc_halParentLeft, gc_valParentTop, 597+pingrankTabResize*1, posy+2, 24+7, 0, gc_halMiddle, gc_valMiddle, gc_font_serif_12, tmpcolor, bupdate);
      [*] = ;   SetGUIElementVisible(elmHnd, (bOnline) and (gMap.players[i].bexists) and (gMap.players[i].bhuman));
      [*] = ;
      [*] = ;   // ready
      [*] = ;   elmHnd := _gui_CreateComboBox('ready|'+IntToStr(i), elmMain, 2, 0, gc_halParentLeft, gc_valParentTop, 646+readyTabResize*2-2, posy, 37, gc_halMiddle, gc_valMiddle, 0, 0, gc_font_serif_12, False, eventstate, bupdate, True);
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
      [*] = ;end;
      [*] = ;
      [*] = ;if bAllowChange and (not bAllowChangeAdviser) then
      [*] = ;gMap.settings.additional.adviserassistant := gc_mapsettings_adviserassistant_without;
      [*] = ;
      [*] = ;var ind : Integer;
      [*] = ;_gui_CreateText('t1', elmMain, cTextSeason, gc_halParentLeft, gc_valParentTop, 686-cAddOffsetX+cAddOffsetL, 103+ind*cOffY, 0, 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;var seasoncount : Integer = 1;
      [*] = ;if bAllowWinter then
      [*] = ;seasoncount := seasoncount+1;
      [*] = ;if bAllowAutumn then
      [*] = ;seasoncount := seasoncount+1;
      [*] = ;if bAllowSpring then
      [*] = ;seasoncount := seasoncount+1;
      [*] = ;elmHnd := _gui_CreateComboBox('season', elmMain, seasoncount+1, 0, gc_halParentLeft, gc_valParentTop, 805+cAddOffsetL, 103+ind*cOffY, 145, gc_halLeft, gc_valMiddle, 5, 0, gc_font_serif_12, bAllowChangeSeason and (not gInternetShell.bautosearch), eventstate, bupdate, True);
      [*] = ;FillComboBoxSeasons(elmHnd);
      [*] = ;SetGUIListBoxItemIndexSilent(elmHnd, GetGUIListBoxItemIndexOfTag(elmHnd, gMap.settings.gen.season));
      [*] = ;SetGUIAllowEvents(elmHnd, bAllowChangeSeason and (not gInternetShell.bautosearch), False, False);
      [*] = ;SetGUIElementUseUserColor(elmHnd, not bAllowChangeSeason or gInternetShell.bautosearch);
      [*] = ;SetGUIElementUserColor(elmHnd, 1, 1, 1, _misc_SwitchFloat(cminalpha, 1, bAllowChangeSeason and not gInternetShell.bautosearch));
      [*] = ;SetGUIElementVisible(GetGUIElementIndexByNameParent('btn', elmHnd), bAllowChangeSeason and (not gInternetShell.bautosearch));
      [*] = ;
      [*] = ;bAllowChange := bAllowChange and (not bRatingGame);
      [*] = ;
      [*] = ;//gMap.settings.gen.terraintype
      [*] = ;ind := ind+1;
      [*] = ;_gui_CreateText('t2', elmMain, cTextTerrainType, gc_halParentLeft, gc_valParentTop, 686-cAddOffsetX+cAddOffsetL, 103+ind*cOffY, 0, 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;elmHnd := _gui_CreateComboBox('terraintype', elmMain, gc_MaxTerrainTypeCount+1, 0, gc_halParentLeft, gc_valParentTop, 805+cAddOffsetL, 103+ind*cOffY, 145, gc_halLeft, gc_valMiddle, 5, 0, gc_font_serif_12, bAllowChange, eventstate, bupdate, True);
      [*] = ;FillComboBoxTerrainTypes(elmHnd);
      [*] = ;SetGUIListBoxItemIndexSilent(elmHnd, gMap.settings.gen.terraintype);
      [*] = ;SetGUIAllowEvents(elmHnd, bAllowChange, False, False);
      [*] = ;SetGUIElementUseUserColor(elmHnd, not bAllowChange);
      [*] = ;SetGUIElementUserColor(elmHnd, 1, 1, 1, _misc_SwitchFloat(cminalpha, 1, bAllowChange));
      [*] = ;
      [*] = ;//gMap.settings.gen.relieftype
      [*] = ;ind := ind+1;
      [*] = ;_gui_CreateText('t3', elmMain, cTextRelief, gc_halParentLeft, gc_valParentTop, 686-cAddOffsetX+cAddOffsetL, 103+ind*cOffY, 0, 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;elmHnd := _gui_CreateComboBox('relieftype', elmMain, gc_MaxReliefTypeCount+1, 0, gc_halParentLeft, gc_valParentTop, 805+cAddOffsetL, 103+ind*cOffY, 145, gc_halLeft, gc_valMiddle, 5, 0, gc_font_serif_12, bAllowChange, eventstate, bupdate, True);
      [*] = ;FillComboBoxReliefTypes(elmHnd);
      [*] = ;SetGUIListBoxItemIndexSilent(elmHnd, gMap.settings.gen.relieftype);
      [*] = ;SetGUIAllowEvents(elmHnd, bAllowChange, False, False);
      [*] = ;SetGUIElementUseUserColor(elmHnd, not bAllowChange);
      [*] = ;SetGUIElementUserColor(elmHnd, 1, 1, 1, _misc_SwitchFloat(cminalpha, 1, bAllowChange));
      [*] = ;
      [*] = ;//gMap.settings.gen.foreststype
      [*] = ;ind := ind+1;
      [*] = ;_gui_CreateText('t4', elmMain, cTextForestsType, gc_halParentLeft, gc_valParentTop, 686-cAddOffsetX+cAddOffsetL, 103+ind*cOffY, 0, 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;elmHnd := _gui_CreateComboBox('foreststype', elmMain, gc_MaxForestsTypeCount+1, 0, gc_halParentLeft, gc_valParentTop, 805+cAddOffsetL, 103+ind*cOffY, 145, gc_halLeft, gc_valMiddle, 5, 0, gc_font_serif_12, bAllowChange, eventstate, bupdate, True);
      [*] = ;FillComboBoxForestsTypes(elmHnd);
      [*] = ;SetGUIListBoxItemIndexSilent(elmHnd, gMap.settings.gen.foreststype);
      [*] = ;SetGUIAllowEvents(elmHnd, bAllowChange, False, False);
      [*] = ;SetGUIElementUseUserColor(elmHnd, not bAllowChange);
      [*] = ;SetGUIElementUserColor(elmHnd, 1, 1, 1, _misc_SwitchFloat(cminalpha, 1, bAllowChange));
      [*] = ;
      [*] = ;//gMap.settings.gen.resourcestart
      [*] = ;ind := ind+1;
      [*] = ;//cTextResources := 'Ресурсы';
      [*] = ;_gui_CreateText('t5', elmMain, cTextResources, gc_halParentLeft, gc_valParentTop, 686-cAddOffsetX+cAddOffsetL, 103+ind*cOffY, 0, 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;elmHnd := _gui_CreateComboBox('resourcestart', elmMain, gc_MaxResourcesCount+1, 0, gc_halParentLeft, gc_valParentTop, 805+cAddOffsetL, 103+ind*cOffY, 145, gc_halLeft, gc_valMiddle, 5, 0, gc_font_serif_12, bAllowChange, eventstate, bupdate, True);
      [*] = ;FillComboBoxResources(elmHnd);
      [*] = ;SetGUIListBoxItemIndexSilent(elmHnd, gMap.settings.gen.resourcestart);
      [*] = ;SetGUIAllowEvents(elmHnd, bAllowChange, False, False);
      [*] = ;SetGUIElementUseUserColor(elmHnd, not bAllowChange);
      [*] = ;SetGUIElementUserColor(elmHnd, 1, 1, 1, _misc_SwitchFloat(cminalpha, 1, bAllowChange));
      [*] = ;
      [*] = ;//gMap.settings.gen.resourcemines
      [*] = ;ind := ind+1;
      [*] = ;//cTextResourceDeposits := 'Ресурсы';
      [*] = ;_gui_CreateText('t6', elmMain, cTextResourceDeposits, gc_halParentLeft, gc_valParentTop, 686-cAddOffsetX+cAddOffsetL, 103+ind*cOffY, 0, 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;elmHnd := _gui_CreateComboBox('resourcemines', elmMain, gc_MaxResourceMinesCount+1, 0, gc_halParentLeft, gc_valParentTop, 805+cAddOffsetL, 103+ind*cOffY, 145, gc_halLeft, gc_valMiddle, 5, 0, gc_font_serif_12, bAllowChange, eventstate, bupdate, True);
      [*] = ;FillComboBoxResourceMines(elmHnd);
      [*] = ;SetGUIListBoxItemIndexSilent(elmHnd, gMap.settings.gen.resourcemines);
      [*] = ;SetGUIAllowEvents(elmHnd, bAllowChange, False, False);
      [*] = ;SetGUIElementUseUserColor(elmHnd, not bAllowChange);
      [*] = ;SetGUIElementUserColor(elmHnd, 1, 1, 1, _misc_SwitchFloat(cminalpha, 1, bAllowChange));
      [*] = ;
      [*] = ;ind := ind+1;
      [*] = ;_gui_CreateText('t8', elmMain, cTextMapSize, gc_halParentLeft, gc_valParentTop, 686-cAddOffsetX+cAddOffsetL, 103+ind*cOffY, 0, 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;elmHnd := _gui_CreateComboBox('mapsize', elmMain, 6, 0, gc_halParentLeft, gc_valParentTop, 805+cAddOffsetL, 103+ind*cOffY, 145, gc_halLeft, gc_valMiddle, 5, 0, gc_font_serif_12, bAllowChange, eventstate, bupdate, True);
      [*] = ;FillComboBoxMapSize(elmHnd);
      [*] = ;var mapsizeind : Integer = GetGUIListBoxItemIndexOfTag(elmHnd, gMap.settings.gen.mapsize);
      [*] = ;SetGUIListBoxItemIndexSilent(elmHnd, mapsizeind);
      [*] = ;SetGUIAllowEvents(elmHnd, bAllowChange, False, False);
      [*] = ;SetGUIElementUseUserColor(elmHnd, not bAllowChange);
      [*] = ;SetGUIElementUserColor(elmHnd, 1, 1, 1, _misc_SwitchFloat(cminalpha, 1, bAllowChange));
      [*] = ;
      [*] = ;//gMap.settings.additional
      [*] = ;ind := ind+1;
      [*] = ;_gui_CreateText('t7', elmMain, cTextAdditional, gc_halParentLeft, gc_valParentTop, 686-cAddOffsetX+cAddOffsetL, 103+ind*cOffY+3, 0, 0, gc_halLeft, gc_valMiddle, gc_font_serif_12, color, bupdate);
      [*] = ;
      [*] = ;ind := ind+1;
      [*] = ;var cAdditionalSettingsCount : Integer;
      [*] = ;if _net_IsClient or ((gProfile.lastknowndlcs and gc_lastknowndlc_exp1)<>0) then
      [*] = ;cAdditionalSettingsCount := 12
      [*] = ;else
      [*] = ;cAdditionalSettingsCount := 11;
      [*] = ;elmHnd := _gui_CreateComboBox('additional', elmMain, cAdditionalSettingsCount, 0, gc_halParentLeft, gc_valParentTop, 683-cAddOffsetX+cAddOffsetL, 103+ind*cOffY, 267+cAddOffsetX, gc_halLeft, gc_valMiddle, 5, 0, gc_font_serif_12, True, eventstate, bupdate, True);
      [*] = ;for i:=0 to cAdditionalSettingsCount-1 do
      [*] = ;begin
      [*] = ;   var textid : String;
      [*] = ;   case i of
      [*] = ;      0 : textid := 'randommap.settings.startingunits';
      [*] = ;      1 : textid := 'randommap.settings.balloon';
      [*] = ;      2 : textid := 'randommap.settings.cannons';
      [*] = ;      3 : textid := 'randommap.settings.peacetime';
      [*] = ;      4 : textid := 'randommap.settings.century18';
      [*] = ;      5 : textid := 'randommap.settings.capture';
      [*] = ;      6 : textid := 'randommap.settings.marketdip';
      [*] = ;      7 : textid := 'randommap.settings.limitwarship';
      [*] = ;      8 : textid := 'randommap.settings.teams';
      [*] = ;      9 : textid := 'randommap.settings.limit';
      [*] = ;      10 : textid := 'CFG.VALUE.GAMESPEED';
      [*] = ;      11 : textid := 'randommap.settings.adviserassistant';
      [*] = ;   end;
      [*] = ;   var s2 : String;
      [*] = ;   case i of
      [*] = ;      0 : begin
      [*] = ;         case gMap.settings.additional.startingunits of
      [*] = ;            gc_mapsettings_startingunits_default : s2 := 'default';
      [*] = ;            gc_mapsettings_startingunits_armysmall : s2 := 'armysmall';
      [*] = ;            gc_mapsettings_startingunits_armymedium : s2 := 'armymedium';
      [*] = ;            gc_mapsettings_startingunits_armylarge : s2 := 'armylarge';
      [*] = ;            gc_mapsettings_startingunits_peasantslot : s2 := 'peasantslot';
      [*] = ;            gc_mapsettings_startingunits_differentnations : s2 := 'differentnations';
      [*] = ;            gc_mapsettings_startingunits_towers : s2 := 'towers';
      [*] = ;            gc_mapsettings_startingunits_cannons : s2 := 'cannons';
      [*] = ;            gc_mapsettings_startingunits_cannonsandhowitzers : s2 := 'cannonsandhowitzers';
      [*] = ;            gc_mapsettings_startingunits_barrack18 : s2 := 'barrack18';
      [*] = ;            gc_mapsettings_startingunits_barrack17 : s2 := 'barrack17';
      [*] = ;            gc_mapsettings_startingunits_village : s2 := 'village';
      [*] = ;            gc_mapsettings_startingunits_logcabins : s2 := 'logcabins';
      [*] = ;            gc_mapsettings_startingunits_union : s2 := 'union';
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      1 : begin
      [*] = ;         case gMap.settings.additional.balloon of
      [*] = ;            gc_mapsettings_balloon_default : s2 := 'default';
      [*] = ;            gc_mapsettings_balloon_no : s2 := 'no';
      [*] = ;            gc_mapsettings_balloon_with : s2 := 'with';
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      2 : begin
      [*] = ;         case gMap.settings.additional.cannons of
      [*] = ;            gc_mapsettings_cannons_default : s2 := 'default';
      [*] = ;            gc_mapsettings_cannons_nocannonstowerswalls : s2 := 'nocannonstowerswalls';
      [*] = ;            gc_mapsettings_cannons_expensivecannons : s2 := 'expensivecannons';
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      3 : begin
      [*] = ;         case gMap.settings.additional.peacetime of
      [*] = ;            gc_mapsettings_peacetime_default : s2 := 'default';
      [*] = ;            gc_mapsettings_peacetime_5 : s2 := '5';
      [*] = ;            gc_mapsettings_peacetime_10 : s2 := '10';
      [*] = ;            gc_mapsettings_peacetime_15 : s2 := '15';
      [*] = ;            gc_mapsettings_peacetime_20 : s2 := '20';
      [*] = ;            gc_mapsettings_peacetime_30 : s2 := '30';
      [*] = ;            gc_mapsettings_peacetime_45 : s2 := '45';
      [*] = ;            gc_mapsettings_peacetime_60 : s2 := '60';
      [*] = ;            gc_mapsettings_peacetime_90 : s2 := '90';
      [*] = ;            gc_mapsettings_peacetime_120 : s2 := '120';
      [*] = ;            gc_mapsettings_peacetime_180 : s2 := '180';
      [*] = ;            gc_mapsettings_peacetime_240 : s2 := '240';
      [*] = ;            gc_mapsettings_peacetime_15 : s2 := '15';
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      4 : begin
      [*] = ;         case gMap.settings.additional.century18 of
      [*] = ;            gc_mapsettings_century18_default : s2 := 'default';
      [*] = ;            gc_mapsettings_century18_no : s2 := 'no';
      [*] = ;            gc_mapsettings_century18_with : s2 := 'with';
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      5 : begin
      [*] = ;         case gMap.settings.additional.capture of
      [*] = ;            gc_mapsettings_capture_default : s2 := 'default';
      [*] = ;            gc_mapsettings_capture_nopeasants : s2 := 'nopeasants';
      [*] = ;            gc_mapsettings_capture_nocenterspeasants : s2 := 'nocenterspeasants';
      [*] = ;            gc_mapsettings_capture_onlyartillery : s2 := 'onlyartillery';
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      6 : begin
      [*] = ;         case gMap.settings.additional.marketdip of
      [*] = ;            gc_mapsettings_marketdip_default : s2 := 'default';
      [*] = ;            gc_mapsettings_marketdip_nodip : s2 := 'nodip';
      [*] = ;            gc_mapsettings_marketdip_nomarket : s2 := 'nomarket';
      [*] = ;            gc_mapsettings_marketdip_noboth : s2 := 'noboth';
      [*] = ;            gc_mapsettings_marketdip_expensivemercs : s2 := 'expensivemercs';
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      7 : begin
      [*] = ;         case gMap.settings.additional.limitwarship of
      [*] = ;            gc_mapsettings_limitwarship_default : s2 := 'default';
      [*] = ;            gc_mapsettings_limitwarship_nowarship : s2 := 'nowarship';
      [*] = ;            gc_mapsettings_limitwarship_transportonly : s2 := 'transportonly';
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      8 : begin
      [*] = ;         case gMap.settings.additional.teams of
      [*] = ;            gc_mapsettings_teams_default : s2 := 'default';
      [*] = ;            gc_mapsettings_teams_nearby : s2 := 'nearby';
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      9 : begin
      [*] = ;         s2 := GetLocaleTableListItemByID('gui', 'randommap.settings.limit.custom');
      [*] = ;         case gMap.settings.additional.limit of
      [*] = ;            0 : s2 := 'default';
      [*] = ;            1 : s2 := StrReplace(s2, '%value%', IntToStr(gc_mapsettings_limit_1));
      [*] = ;            2 : s2 := StrReplace(s2, '%value%', IntToStr(gc_mapsettings_limit_2));
      [*] = ;            3 : s2 := StrReplace(s2, '%value%', IntToStr(gc_mapsettings_limit_3));
      [*] = ;            4 : s2 := StrReplace(s2, '%value%', IntToStr(gc_mapsettings_limit_4));
      [*] = ;            5 : s2 := StrReplace(s2, '%value%', IntToStr(gc_mapsettings_limit_5));
      [*] = ;            6 : s2 := StrReplace(s2, '%value%', IntToStr(gc_mapsettings_limit_6));
      [*] = ;            7 : s2 := StrReplace(s2, '%value%', IntToStr(gc_mapsettings_limit_7));
      [*] = ;            8 : s2 := StrReplace(s2, '%value%', IntToStr(gc_mapsettings_limit_8));
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      10 : begin
      [*] = ;         case gMap.settings.additional.gamespeed of
      [*] = ;            0 : s2 := '0';
      [*] = ;            1 : s2 := '1';
      [*] = ;            2 : s2 := '2';
      [*] = ;            -1 : s2 := '-1';
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      11 : begin
      [*] = ;         case gMap.settings.additional.adviserassistant of
      [*] = ;            gc_mapsettings_adviserassistant_default : s2 := 'default';
      [*] = ;            gc_mapsettings_adviserassistant_without : s2 := 'without';
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if (s2='') then
      [*] = ;   ErrorLog('ShowCustomGame unknown additional map setting');
      [*] = ;
      [*] = ;   var settingtext : String;
      [*] = ;   if ((i=9) and (s2 <> 'default')) then
      [*] = ;   settingtext := s2
      [*] = ;   else
      [*] = ;   if (i=10) then
      [*] = ;   settingtext := GetLocaleTableListItemByID('tools', textid+'.'+s2)
      [*] = ;   else
      [*] = ;   settingtext := GetLocaleTableListItemByID('gui', textid+'.'+s2);
      [*] = ;
      [*] = ;   if (i=6) and (gMap.settings.additional.marketdip=gc_mapsettings_marketdip_expensivemercs) then
      [*] = ;   _misc_GetNewTextLocale('randommap.settings.marketdip.expensivemercs', settingtext);
      [*] = ;
      [*] = ;   if (i=0) and (gMap.settings.additional.startingunits>=gc_mapsettings_startingunits_barrack17) then
      [*] = ;   _misc_GetNewTextLocale(textid+'.'+s2, settingtext);
      [*] = ;
      [*] = ;   var font : String = GetGUIElementFont(elmHnd);
      [*] = ;   var text : String = GetLocaleTableListItemByID('gui', textid)+': '+settingtext;
      [*] = ;   if (i=10) then
      [*] = ;   text := GetLocaleTableListItemByID('tools', 'CFG.PROFILE.GAMESPEED')+': '+settingtext;
      [*] = ;   var textw, texth : Integer;
      [*] = ;   GetGUIElementFontTextFormatRect(font, text, textw, texth);
      [*] = ;
      [*] = ;   const ctextdots = '...';
      [*] = ;   var textdotsw, textdotsh : Integer;
      [*] = ;   GetGUIElementFontTextFormatRect(font, ctextdots, textdotsw, textdotsh);
      [*] = ;   var elmw : Integer = GetGUIElementWidth(elmHnd);
      [*] = ;   const cpadding = 32;
      [*] = ;   if (textw>(elmw-cpadding+textdotsw)) then
      [*] = ;   begin
      [*] = ;      while textw>(elmw-cpadding) do
      [*] = ;      begin
      [*] = ;         var length : Integer = StrLength(text);
      [*] = ;         text := SubStr(text, 1, length-1);
      [*] = ;         GetGUIElementFontTextFormatRect(font, text, textw, texth);
      [*] = ;      end;
      [*] = ;      text := text+'...';
      [*] = ;   end;
      [*] = ;   GUIListBoxAddItem(elmHnd, text, i);
      [*] = ;
      [*] = ;   {var textw, texth : Integer;
      [*] = ;   GetGUIElementFontTextFormatRect(gUIConst.font[gc_font_serif_12], text, textw, texth);
      [*] = ;   var tmpHnd : Integer = GetGUIComboBoxListBoxHandle(elmHnd);
      [*] = ;   if tmpHnd<>0 then
      [*] = ;   begin
      [*] = ;      SetGUIElementWidth(tmpHnd, Max(GetGUIElementWidth(tmpHnd), textw+10));
      [*] = ;      SetGUIElementLogicWidth(tmpHnd, Max(GetGUIElementWidth(tmpHnd), textw+10));
      [*] = ;   end;}
      [*] = ;end;
      [*] = ;SetGUIListBoxItemIndexSilent(elmHnd, gMap.settings.additional.activeoption);
      [*] = ;
      [*] = ;var textid : String;
      [*] = ;var count : Integer;
      [*] = ;case gMap.settings.additional.activeoption of
      [*] = ;   0 : begin
      [*] = ;      textid := 'randommap.settings.startingunits';
      [*] = ;      count := gc_mapsettings_startingunits_union+1;
      [*] = ;   end;
      [*] = ;   1 : begin
      [*] = ;      textid := 'randommap.settings.balloon';
      [*] = ;      count := gc_mapsettings_balloon_with+1;
      [*] = ;   end;
      [*] = ;   2 : begin
      [*] = ;      textid := 'randommap.settings.cannons';
      [*] = ;      count := gc_mapsettings_cannons_expensivecannons+1;
      [*] = ;   end;
      [*] = ;   3 : begin
      [*] = ;      textid := 'randommap.settings.peacetime';
      [*] = ;      count := gc_mapsettings_peacetime_240+1;
      [*] = ;   end;
      [*] = ;   4 : begin
      [*] = ;      textid := 'randommap.settings.century18';
      [*] = ;      count := gc_mapsettings_century18_with+1;
      [*] = ;   end;
      [*] = ;   5 : begin
      [*] = ;      textid := 'randommap.settings.capture';
      [*] = ;      count := gc_mapsettings_capture_onlyartillery+1;
      [*] = ;   end;
      [*] = ;   6 : begin
      [*] = ;      textid := 'randommap.settings.marketdip';
      [*] = ;      count := gc_mapsettings_marketdip_expensivemercs+1;
      [*] = ;   end;
      [*] = ;   7 : begin
      [*] = ;      textid := 'randommap.settings.limitwarship';
      [*] = ;      count := gc_mapsettings_limitwarship_transportonly+1;
      [*] = ;   end;
      [*] = ;   8 : begin
      [*] = ;      textid := 'randommap.settings.teams';
      [*] = ;      count := gc_mapsettings_teams_nearby+1;
      [*] = ;   end;
      [*] = ;   9 : begin
      [*] = ;      textid := 'randommap.settings.limit';
      [*] = ;      count := gc_mapsettings_limit_count+1;
      [*] = ;   end;
      [*] = ;   10 : begin
      [*] = ;      textid := 'CFG.VALUE.GAMESPEED';
      [*] = ;      if _net_IsOnline then
      [*] = ;      count := gc_settings_gamespeed_count+1
      [*] = ;      else
      [*] = ;      count := gc_settings_gamespeed_count;
      [*] = ;   end;
      [*] = ;   11 : begin
      [*] = ;      textid := 'randommap.settings.adviserassistant';
      [*] = ;      count := gc_mapsettings_adviserassistant_without+1;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;ind := ind+1;
      [*] = ;elmHnd := _gui_CreateComboBox('additional_options', elmMain, count, 0, gc_halParentLeft, gc_valParentTop, 705-cAddOffsetX+cAddOffsetL, 103+ind*cOffY, 245+cAddOffsetX, gc_halLeft, gc_valMiddle, 5, 0, gc_font_serif_12, bAllowChange, eventstate, bupdate, True);
      [*] = ;var s2 : String;
      [*] = ;case gMap.settings.additional.activeoption of
      [*] = ;   0 : begin
      [*] = ;      for i:=0 to gc_mapsettings_startingunits_union do
      [*] = ;      begin
      [*] = ;         case i of
      [*] = ;            gc_mapsettings_startingunits_default : s2 := 'default';
      [*] = ;            gc_mapsettings_startingunits_armysmall : s2 := 'armysmall';
      [*] = ;            gc_mapsettings_startingunits_armymedium : s2 := 'armymedium';
      [*] = ;            gc_mapsettings_startingunits_armylarge : s2 := 'armylarge';
      [*] = ;            gc_mapsettings_startingunits_peasantslot : s2 := 'peasantslot';
      [*] = ;            gc_mapsettings_startingunits_differentnations : s2 := 'differentnations';
      [*] = ;            gc_mapsettings_startingunits_towers : s2 := 'towers';
      [*] = ;            gc_mapsettings_startingunits_cannons : s2 := 'cannons';
      [*] = ;            gc_mapsettings_startingunits_cannonsandhowitzers : s2 := 'cannonsandhowitzers';
      [*] = ;            gc_mapsettings_startingunits_barrack18 : s2 := 'barrack18';
      [*] = ;            gc_mapsettings_startingunits_barrack17 : s2 := 'barrack17';
      [*] = ;            gc_mapsettings_startingunits_village : s2 := 'village';
      [*] = ;            gc_mapsettings_startingunits_logcabins : s2 := 'logcabins';
      [*] = ;            gc_mapsettings_startingunits_union : s2 := 'union';
      [*] = ;         end;
      [*] = ;         var text : String;
      [*] = ;         if (i<=gc_mapsettings_startingunits_barrack18) then
      [*] = ;         text := GetLocaleTableListItemByID('gui', textid+'.'+s2)
      [*] = ;         else
      [*] = ;         _misc_GetNewTextLocale(textid+'.'+s2, text);
      [*] = ;         GUIListBoxAddItem(elmHnd, text, i);
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, gMap.settings.additional.startingunits);
      [*] = ;   end;
      [*] = ;   1 : begin
      [*] = ;      for i:=0 to gc_mapsettings_balloon_with do
      [*] = ;      begin
      [*] = ;         case i of
      [*] = ;            gc_mapsettings_balloon_default : s2 := 'default';
      [*] = ;            gc_mapsettings_balloon_no : s2 := 'no';
      [*] = ;            gc_mapsettings_balloon_with : s2 := 'with';
      [*] = ;         end;
      [*] = ;         var text : String = GetLocaleTableListItemByID('gui', textid+'.'+s2);
      [*] = ;         GUIListBoxAddItem(elmHnd, text, i);
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, gMap.settings.additional.balloon);
      [*] = ;   end;
      [*] = ;   2 : begin
      [*] = ;      for i:=0 to gc_mapsettings_cannons_expensivecannons do
      [*] = ;      begin
      [*] = ;         case i of
      [*] = ;            gc_mapsettings_cannons_default : s2 := 'default';
      [*] = ;            gc_mapsettings_cannons_nocannonstowerswalls : s2 := 'nocannonstowerswalls';
      [*] = ;            gc_mapsettings_cannons_expensivecannons : s2 := 'expensivecannons';
      [*] = ;         end;
      [*] = ;         var text : String = GetLocaleTableListItemByID('gui', textid+'.'+s2);
      [*] = ;         GUIListBoxAddItem(elmHnd, text, i);
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, gMap.settings.additional.cannons);
      [*] = ;   end;
      [*] = ;   3 : begin
      [*] = ;      for i:=0 to gc_mapsettings_peacetime_240 do
      [*] = ;      begin
      [*] = ;         case i of
      [*] = ;            gc_mapsettings_peacetime_default : s2 := 'default';
      [*] = ;            gc_mapsettings_peacetime_5 : s2 := '5';
      [*] = ;            gc_mapsettings_peacetime_10 : s2 := '10';
      [*] = ;            gc_mapsettings_peacetime_20 : s2 := '20';
      [*] = ;            gc_mapsettings_peacetime_30 : s2 := '30';
      [*] = ;            gc_mapsettings_peacetime_45 : s2 := '45';
      [*] = ;            gc_mapsettings_peacetime_60 : s2 := '60';
      [*] = ;            gc_mapsettings_peacetime_90 : s2 := '90';
      [*] = ;            gc_mapsettings_peacetime_120 : s2 := '120';
      [*] = ;            gc_mapsettings_peacetime_180 : s2 := '180';
      [*] = ;            gc_mapsettings_peacetime_240 : s2 := '240';
      [*] = ;         end;
      [*] = ;         var text : String = GetLocaleTableListItemByID('gui', textid+'.'+s2);
      [*] = ;         GUIListBoxAddItem(elmHnd, text, i);
      [*] = ;
      [*] = ;         if (i=gc_mapsettings_peacetime_10) then // insert 15 minute after 10
      [*] = ;         begin
      [*] = ;            var text : String = GetLocaleTableListItemByID('gui', textid+'.15');
      [*] = ;            GUIListBoxAddItem(elmHnd, text, gc_mapsettings_peacetime_15);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //SetGUIListBoxItemIndexSilent(elmHnd, gMap.settings.additional.peacetime);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, GetGUIListBoxItemIndexOfTag(elmHnd, gMap.settings.additional.peacetime));
      [*] = ;   end;
      [*] = ;   4 : begin
      [*] = ;      for i:=0 to gc_mapsettings_century18_with do
      [*] = ;      begin
      [*] = ;         case i of
      [*] = ;            gc_mapsettings_century18_default : s2 := 'default';
      [*] = ;            gc_mapsettings_century18_no : s2 := 'no';
      [*] = ;            gc_mapsettings_century18_with : s2 := 'with';
      [*] = ;         end;
      [*] = ;         var text : String = GetLocaleTableListItemByID('gui', textid+'.'+s2);
      [*] = ;         GUIListBoxAddItem(elmHnd, text, i);
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, gMap.settings.additional.century18);
      [*] = ;   end;
      [*] = ;   5 : begin
      [*] = ;      for i:=0 to gc_mapsettings_capture_onlyartillery do
      [*] = ;      begin
      [*] = ;         case i of
      [*] = ;            gc_mapsettings_capture_default : s2 := 'default';
      [*] = ;            gc_mapsettings_capture_nopeasants : s2 := 'nopeasants';
      [*] = ;            gc_mapsettings_capture_nocenterspeasants : s2 := 'nocenterspeasants';
      [*] = ;            gc_mapsettings_capture_onlyartillery : s2 := 'onlyartillery';
      [*] = ;         end;
      [*] = ;         var text : String = GetLocaleTableListItemByID('gui', textid+'.'+s2);
      [*] = ;         GUIListBoxAddItem(elmHnd, text, i);
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, gMap.settings.additional.capture);
      [*] = ;   end;
      [*] = ;   6 : begin
      [*] = ;      for i:=0 to gc_mapsettings_marketdip_expensivemercs do
      [*] = ;      begin
      [*] = ;         case i of
      [*] = ;            gc_mapsettings_marketdip_default : s2 := 'default';
      [*] = ;            gc_mapsettings_marketdip_nodip : s2 := 'nodip';
      [*] = ;            gc_mapsettings_marketdip_nomarket : s2 := 'nomarket';
      [*] = ;            gc_mapsettings_marketdip_noboth : s2 := 'noboth';
      [*] = ;            gc_mapsettings_marketdip_expensivemercs : s2 := 'expensivemercs';
      [*] = ;         end;
      [*] = ;         var text : String;
      [*] = ;         if (i<=gc_mapsettings_marketdip_noboth) then
      [*] = ;         text := GetLocaleTableListItemByID('gui', textid+'.'+s2)
      [*] = ;         else
      [*] = ;         _misc_GetNewTextLocale(textid+'.'+s2, text);
      [*] = ;         GUIListBoxAddItem(elmHnd, text, i);
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, gMap.settings.additional.marketdip);
      [*] = ;   end;
      [*] = ;   7 : begin
      [*] = ;      for i:=0 to gc_mapsettings_limitwarship_transportonly do
      [*] = ;      begin
      [*] = ;         case i of
      [*] = ;            gc_mapsettings_limitwarship_default : s2 := 'default';
      [*] = ;            gc_mapsettings_limitwarship_nowarship : s2 := 'nowarship';
      [*] = ;            gc_mapsettings_limitwarship_transportonly : s2 := 'transportonly';
      [*] = ;         end;
      [*] = ;         var text : String = GetLocaleTableListItemByID('gui', textid+'.'+s2);
      [*] = ;         GUIListBoxAddItem(elmHnd, text, i);
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, gMap.settings.additional.limitwarship);
      [*] = ;   end;
      [*] = ;   8 : begin
      [*] = ;      for i:=0 to gc_mapsettings_teams_nearby do
      [*] = ;      begin
      [*] = ;         case i of
      [*] = ;            gc_mapsettings_teams_default : s2 := 'default';
      [*] = ;            gc_mapsettings_teams_nearby : s2 := 'nearby';
      [*] = ;         end;
      [*] = ;         var text : String = GetLocaleTableListItemByID('gui', textid+'.'+s2);
      [*] = ;         GUIListBoxAddItem(elmHnd, text, i);
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, gMap.settings.additional.teams);
      [*] = ;   end;
      [*] = ;   9 : begin
      [*] = ;      for i:=0 to gc_mapsettings_limit_count do
      [*] = ;      begin
      [*] = ;         case i of
      [*] = ;            0 : s2 := 'default';
      [*] = ;            1 : s2 := IntToStr(gc_mapsettings_limit_1);
      [*] = ;            2 : s2 := IntToStr(gc_mapsettings_limit_2);
      [*] = ;            3 : s2 := IntToStr(gc_mapsettings_limit_3);
      [*] = ;            4 : s2 := IntToStr(gc_mapsettings_limit_4);
      [*] = ;            5 : s2 := IntToStr(gc_mapsettings_limit_5);
      [*] = ;            6 : s2 := IntToStr(gc_mapsettings_limit_6);
      [*] = ;            7 : s2 := IntToStr(gc_mapsettings_limit_7);
      [*] = ;            8 : s2 := IntToStr(gc_mapsettings_limit_8);
      [*] = ;         end;
      [*] = ;
      [*] = ;         var text : String = GetLocaleTableListItemByID('gui', 'randommap.settings.limit.custom');
      [*] = ;         if (s2 <> 'default') then
      [*] = ;         text := StrReplace(text, '%value%', s2)
      [*] = ;         else
      [*] = ;         text := GetLocaleTableListItemByID('gui', textid+'.'+s2);
      [*] = ;
      [*] = ;         GUIListBoxAddItem(elmHnd, text, i);
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, gMap.settings.additional.limit);
      [*] = ;   end;
      [*] = ;   10 : begin
      [*] = ;      var count : Integer;
      [*] = ;      if _net_IsOnline then
      [*] = ;      count := gc_settings_gamespeed_count
      [*] = ;      else
      [*] = ;      count := gc_settings_gamespeed_count-1;
      [*] = ;      for i:=0 to count do
      [*] = ;      begin
      [*] = ;         case i of
      [*] = ;            0 : s2 := '0';
      [*] = ;            1 : s2 := '1';
      [*] = ;            2 : s2 := '2';
      [*] = ;            3 : s2 := '-1';
      [*] = ;         end;
      [*] = ;         var text : String = GetLocaleTableListItemByID('tools', textid+'.'+s2);
      [*] = ;         if (i=count) and (_net_IsOnline) then
      [*] = ;         GUIListBoxAddItem(elmHnd, text, -1)
      [*] = ;         else
      [*] = ;         GUIListBoxAddItem(elmHnd, text, i);
      [*] = ;      end;
      [*] = ;      if _net_IsOffline and (gMap.settings.additional.gamespeed<0) then
      [*] = ;      tag := 2
      [*] = ;      else
      [*] = ;      tag := gMap.settings.additional.gamespeed;
      [*] = ;      var ind : Integer = GetGUIListBoxItemIndexOfTag(elmHnd, gMap.settings.additional.gamespeed);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, ind);
      [*] = ;   end;
      [*] = ;   11 : begin
      [*] = ;      for i:=0 to gc_mapsettings_adviserassistant_without do
      [*] = ;      begin
      [*] = ;         case i of
      [*] = ;            gc_mapsettings_adviserassistant_default : s2 := 'default';
      [*] = ;            gc_mapsettings_adviserassistant_without : s2 := 'without';
      [*] = ;         end;
      [*] = ;         var text : String = GetLocaleTableListItemByID('gui', textid+'.'+s2);
      [*] = ;         GUIListBoxAddItem(elmHnd, text, i);
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, gMap.settings.additional.adviserassistant);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;SetGUIAllowEvents(elmHnd, bAllowChange, False, False);
      [*] = ;SetGUIElementUseUserColor(elmHnd, not bAllowChange);
      [*] = ;SetGUIElementUserColor(elmHnd, 1, 1, 1, _misc_SwitchFloat(cminalpha, 1, bAllowChange));
      [*] = ;if (s2='') then
      [*] = ;ErrorLog('ShowCustomGame unknown additional map setting');
      [*] = ;
      [*] = ;// chat
      [*] = ;if bOnline then
      [*] = ;begin
      [*] = ;   const cSessionsMarginLeft = 62;
      [*] = ;   const cChatMarginBottom = 63;
      [*] = ;   var chatW : Integer = GetGUIElementWidth(GetGUIElementIndexByNameParent('mft_2t_0', elmMain))+8;
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
      [*] = ;SetRandomKey(floor(Abs(randkey))); // if randkey<0 function set key0 to -1 and randomext start to provide negative values
   struct.end
section.end

