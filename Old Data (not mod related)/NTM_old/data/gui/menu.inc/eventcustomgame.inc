section.begin
   Name = EventCustomGame
   Code : struct.begin
      [*] = ;procedure DoStartGame;
      [*] = ;begin
      [*] = ;   //Log('DoStartGame');
      [*] = ;   //LanSrvSetMapFile(''); // use LoadMapNeeded(''); instead
      [*] = ;   LanDoStart();
      [*] = ;end;
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
      [*] = ;
      [*] = ;var elmHnd : Integer = GetIntValueByName('ElementHandle');
      [*] = ;var press : String = GetValueByName('Press');
      [*] = ;var status : String = GetValueByName('Status');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;
      [*] = ;const currentstatename = 'EventCustomGame';
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
      [*] = ;const cTagBaseTagChangeColor = 200;
      [*] = ;const cTagClose = 500;
      [*] = ;const cTagKick = 1000;
      [*] = ;
      [*] = ;if (status='select') then
      [*] = ;begin
      [*] = ;   tag := GetGUIListBoxItemTag(elmHnd, GetGUIListBoxItemIndex(elmHnd));
      [*] = ;   var elmname : String = GetGUIElementNameByIndex(elmHnd);
      [*] = ;   case elmname of
      [*] = ;      'season' : gMap.settings.gen.season := tag;
      [*] = ;      'terraintype' : gMap.settings.gen.terraintype := tag;
      [*] = ;      'relieftype' : gMap.settings.gen.relieftype := tag;
      [*] = ;      'foreststype' : gMap.settings.gen.foreststype := tag;
      [*] = ;      'resourcestart' : gMap.settings.gen.resourcestart := tag;
      [*] = ;      'resourcemines' : gMap.settings.gen.resourcemines := tag;
      [*] = ;      'mapsize' : gMap.settings.gen.mapsize := tag;
      [*] = ;      'additional' : begin
      [*] = ;         gMap.settings.additional.activeoption := tag;
      [*] = ;         ExecuteState(showstate);
      [*] = ;      end;
      [*] = ;      'additional_options' : begin
      [*] = ;         case gMap.settings.additional.activeoption of
      [*] = ;            0 : gMap.settings.additional.startingunits := tag;
      [*] = ;            1 : gMap.settings.additional.balloon := tag;
      [*] = ;            2 : gMap.settings.additional.cannons := tag;
      [*] = ;            3 : gMap.settings.additional.peacetime := tag;
      [*] = ;            4 : gMap.settings.additional.century18 := tag;
      [*] = ;            5 : gMap.settings.additional.capture := tag;
      [*] = ;            6 : gMap.settings.additional.marketdip := tag;
      [*] = ;            7 : gMap.settings.additional.limitwarship := tag;
      [*] = ;            8 : gMap.settings.additional.teams := tag;
      [*] = ;            9 : gMap.settings.additional.limit := tag;
      [*] = ;            10 : gMap.settings.additional.gamespeed := tag;
      [*] = ;            11 : gMap.settings.additional.adviserassistant := tag;
      [*] = ;         end;
      [*] = ;         ExecuteState(showstate);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   var bshow : Boolean;
      [*] = ;   var ind : Integer = -1;
      [*] = ;   if (IsDelimiterCharExists(elmname, gc_gui_delimiterchar)) then
      [*] = ;   begin
      [*] = ;      var s1, s2, s3, s4 : String;
      [*] = ;      _misc_GetDelimiterString(elmname, gc_gui_delimiterchar, s1, s2, s3, s4);
      [*] = ;      //log('comboname='+s1+'['+s2+'] := '+IntToStr(tag));
      [*] = ;      ind := StrToInt(s2);
      [*] = ;      var totalplayers : Integer = 0;
      [*] = ;      var i : Integer;
      [*] = ;      for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;      begin
      [*] = ;         if (gMap.players[i].bexists and gMap.players[i].cid<>gc_spectator_countryid) then
      [*] = ;         totalplayers := totalplayers+1;
      [*] = ;      end;
      [*] = ;      case s1 of
      [*] = ;         'name' : begin
      [*] = ;            if (tag=cTagKick) or (tag=cTagClose) then
      [*] = ;            begin
      [*] = ;               var lanid : Integer = gMap.players[ind].lanid;
      [*] = ;               if (lanid<>0) then
      [*] = ;               LanKillClient(lanid);
      [*] = ;               gMap.players[ind].bexists := False;
      [*] = ;               gMap.players[ind].bai := False;
      [*] = ;               gMap.players[ind].bhuman := False;
      [*] = ;               gMap.players[ind].bclosed := False;
      [*] = ;               gMap.players[ind].aidifficulty := 0;
      [*] = ;               gMap.players[ind].color := ind;
      [*] = ;               gMap.players[ind].bclosed := (tag=cTagClose);
      [*] = ;               bshow := True;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'ai' : begin
      [*] = ;            if (tag=cTagClose) then
      [*] = ;            _map_ResetMapPlayer(gMap.players[ind], ind, (gInternetShell.bratingroom or gInternetShell.bautosearch))
      [*] = ;            else
      [*] = ;            if (tag>0) then
      [*] = ;            begin
      [*] = ;               if (totalplayers<gc_MaxNonSpectatorsCount) then
      [*] = ;               begin
      [*] = ;                  if (not gMap.players[ind].bexists) then
      [*] = ;                  begin
      [*] = ;                     gMap.players[ind].bexists := True;
      [*] = ;                     gMap.players[ind].bai := True;
      [*] = ;                     gMap.players[ind].bhuman := False;
      [*] = ;                     gMap.players[ind].aidifficulty := tag-1;
      [*] = ;                     gMap.players[ind].color := ind;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  gMap.players[ind].aidifficulty := tag-1;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            _map_ResetMapPlayer(gMap.players[ind], ind, (gInternetShell.bratingroom or gInternetShell.bautosearch));
      [*] = ;            gMap.players[ind].bclosed := (tag=cTagClose);
      [*] = ;            bshow := True;
      [*] = ;         end;
      [*] = ;         'country' : begin
      [*] = ;            if (totalplayers>=gc_MaxNonSpectatorsCount)  then
      [*] = ;            begin
      [*] = ;               if (gMap.players[ind].cid<>gc_spectator_countryid) then
      [*] = ;               begin
      [*] = ;                  gMap.players[ind].cid := tag;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               gMap.players[ind].cid := gc_spectator_countryid;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            gMap.players[ind].cid := tag;
      [*] = ;            if (tag<gc_MaxCountryCount-1) then
      [*] = ;            begin
      [*] = ;               var csid : String;
      [*] = ;               _country_GetSIDByID(tag, csid);
      [*] = ;               gMap.players[ind].csid := csid;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            gMap.players[ind].csid := '';
      [*] = ;            bshow := True;
      [*] = ;            ValidateSpectatorCountries;
      [*] = ;         end;
      [*] = ;         'team' : begin
      [*] = ;            _misc_SetClLanTeamByIndex(ind, tag);
      [*] = ;         end;
     [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if (_net_IsOnline) then
      [*] = ;   begin
      [*] = ;      if (_net_IsServer) then
      [*] = ;      _misc_InternetShellUpdateCurrentSessionName(gInternetShell, True)
      [*] = ;      else
      [*] = ;      if (_net_IsClient) and (ind>=0) and (ind<gc_MaxPlayerCount-1) then
      [*] = ;      begin
      [*] = ;         var pLan : Integer = _parser_ParserTemporary(True);
      [*] = ;         ParserSetValueByKeyByHandle(pLan, 's', IntToStr(gMap.players[ind].cid)+gc_gui_delimitercharstr+IntToStr(gMap.players[ind].team)+gc_gui_delimitercharstr+IntToStr(gMap.players[ind].color));
      [*] = ;         LanPublicServerSendSessionParser(gLanHostID, gc_LAN_ROOM_CLIENT_DATACHANGE, pLan);
      [*] = ;         //Log('EventCustomGame:LanSendParser:gc_LAN_ROOM_CLIENT_CHANGES');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if (bshow) then
      [*] = ;   ExecuteState(showstate);
      [*] = ;end
      [*] = ;else
      [*] = ;if (press='d') then
      [*] = ;begin
      [*] = ;   if (tag>=cTagBaseTagChangeColor) and (tag<cTagBaseTagChangeColor+gc_MaxPlayerCount) then
      [*] = ;   begin
      [*] = ;      var pl : Integer = tag-cTagBaseTagChangeColor;
      [*] = ;      var key : String = GetValueByName('Key');
      [*] = ;      function CheckDoubleColor(testplayer, testcolor : Integer; bAdjust, bDirectionForward : Boolean) : Integer;
      [*] = ;      begin
      [*] = ;         var newtestcolor : Integer = testcolor;
      [*] = ;         if (bAdjust) then
      [*] = ;         begin
      [*] = ;            if (bDirectionForward) then
      [*] = ;            newtestcolor := ((newtestcolor+1) mod (gc_MaxColorCount-1))
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               newtestcolor := newtestcolor-1;
      [*] = ;               if newtestcolor<0 then newtestcolor := gc_MaxColorCount-2;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         Result := newtestcolor;
      [*] = ;         var bDoubleColor : Boolean;
      [*] = ;         var i, j : Integer;
      [*] = ;         for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;         begin
      [*] = ;            if (i<>testplayer) and (gMap.players[i].bexists) and (gMap.players[i].color=newtestcolor) then
      [*] = ;            begin
      [*] = ;               Result := CheckDoubleColor(testplayer, newtestcolor, bAdjust, bDirectionForward);
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      gMap.players[pl].color := CheckDoubleColor(pl, gMap.players[pl].color, True, (key='LButton'));
      [*] = ;
      [*] = ;      if (_net_IsOnline) then
      [*] = ;      begin
      [*] = ;         if (_net_IsServer) then
      [*] = ;         _misc_InternetShellUpdateCurrentSessionName(gInternetShell, True)
      [*] = ;         else
      [*] = ;         if (_net_IsClient) and (pl>=0) and (pl<gc_MaxPlayerCount-1) then
      [*] = ;         begin
      [*] = ;            var pLan : Integer = _parser_ParserTemporary(True);
      [*] = ;            ParserSetValueByKeyByHandle(pLan, 's', IntToStr(gMap.players[pl].cid)+gc_gui_delimitercharstr+IntToStr(gMap.players[pl].team)+gc_gui_delimitercharstr+IntToStr(gMap.players[pl].color));
      [*] = ;            LanPublicServerSendSessionParser(gLanHostID, gc_LAN_ROOM_CLIENT_DATACHANGE, pLan);
      [*] = ;            //Log('EventCustomGame:LanSendParser:gc_LAN_ROOM_CLIENT_CHANGES');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      ExecuteState(showstate);
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;if (press='c') then
      [*] = ;begin
      [*] = ;   case tag of
      [*] = ;      gc_gui_event_tagShow : ExecuteState(showstate);
      [*] = ;      gc_gui_event_tagHide : begin
      [*] = ;         _gui_SetGUIElementVisibleByName(elmname, False);
      [*] = ;         _gui_SetShellChatInputBoxFocused;
      [*] = ;      end;
      [*] = ;      cTagReadyGame : begin
      [*] = ;         LanSendParser(gc_LAN_ROOM_READY, _parser_ParserEmpty);
      [*] = ;         if (gInternetShell.bratingroom) then
      [*] = ;         begin
      [*] = ;            gInternetShell.bautosearch := True;
      [*] = ;            gInternetShell.bcustomautosearch := True;
      [*] = ;         end;
      [*] = ;         //Log('EventCustomGame:LanSendParser:gc_LAN_ROOM_READY');
      [*] = ;      end;
      [*] = ;      cTagLeaveRoom, cTagCloseRoom : begin
      [*] = ;         //LanPublicServerSendSessionParser(gLanHostID, gc_LAN_ROOM_CLIENT_LEAVE, _parser_ParserEmpty);
      [*] = ;         gInternetShell.autosearchrealstarttime := 0;
      [*] = ;         gInternetShell.ClearQuickPlay;
      [*] = ;         gInternetShell.rankingslastupdate := 0;
      [*] = ;
      [*] = ;         gInternetShell.currentsessionid := 0;
      [*] = ;         gInternetShell.roomdata := '';
      [*] = ;         gInternetShell.selsessionid := 0;
      [*] = ;         LanTerminateGame;
      [*] = ;         var elm : Integer = GetGUIElementIndexByNameParent(elmname, _gui_GetTop);
      [*] = ;         if elm<>0 then
      [*] = ;         RemoveGUIChildren(elm);
      [*] = ;      end;
      [*] = ;      cTagSwitchToShell : begin
      [*] = ;         _gui_SetGUIElementVisibleByName(elmname, False);
      [*] = ;         gInternetShell.bshowroom := False;
      [*] = ;         gInternetShell.bshowranking := False;
      [*] = ;         gint_gui_updatesessionlist := (1 shl 0);
      [*] = ;         gint_gui_updateclientlist := (1 shl 0);
      [*] = ;         gbool_gui_showinternetshell := True; //ExecuteState('ShowInternetShell');
      [*] = ;         gbool_gui_setshellchatinputfocused := True;
      [*] = ;         //ExecuteState('ShowInternetShell');
      [*] = ;         //_gui_SetShellChatInputBoxFocused;
      [*] = ;      end;
      [*] = ;      cTagBackToMainMenu, gc_gui_hotkey_btnEscape : begin
      [*] = ;         if (tag=gc_gui_hotkey_btnEscape) and (_net_IsOnline) then
      [*] = ;         exit;
      [*] = ;         _gui_SetGUIElementVisibleByName(elmname, False);
      [*] = ;         if (_net_IsOnline) then
      [*] = ;         begin
      [*] = ;            gInternetShell.currentsessionid := 0;
      [*] = ;            gInternetShell.roomdata := '';
      [*] = ;            gInternetShell.selsessionid := 0;
      [*] = ;            LanTerminateGame;
      [*] = ;            ExecuteState('ShowInternetShell');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            ExecuteState('ShowMainMenu');
      [*] = ;            gint_gui_newsshowvisible := 0;
      [*] = ;            ExecuteState('ShowNews');
      [*] = ;         end
      [*] = ;      end;
      [*] = ;      cTagStartGame, gc_gui_hotkey_btnEnter : begin
      [*] = ;         if (tag=gc_gui_hotkey_btnEnter) and (_net_IsOnline) then
      [*] = ;         exit;
      [*] = ;
      [*] = ;         var i : Integer;
      [*] = ;         var humancount : Integer;
      [*] = ;         for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;         if (gMap.players[i].bexists) and (gMap.players[i].lanid>0) then
      [*] = ;         humancount := humancount+1;
      [*] = ;
      [*] = ;         for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;         if (gMap.players[i].bexists) and (gMap.players[i].cid=gc_spectator_countryid) then
      [*] = ;         begin
      [*] = ;            gMap.players[i].team := 0;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (_net_IsServer) then
      [*] = ;         begin
      [*] = ;            gMap.gamestage := gc_map_gamestage_waitingloading;
      [*] = ;            // save multiplayer room settings start part 1
      [*] = ;            gProfileUserStruct.custommap := gMap;
      [*] = ;            gProfileUserStruct.custommap.bbattle := false;
      [*] = ;            gProfileUserStruct.custommap.battlestage := 0;
      [*] = ;            // save multiplayer room settings finish part 1
      [*] = ;            if (humancount>1) then
      [*] = ;            begin
      [*] = ;               //ExecuteState('InitMapSettings');
      [*] = ;               var pLan : Integer = _parser_ParserTemporary(True);
      [*] = ;               gMap.dlcs := gProfile.lastknowndlcs;
      [*] = ;               if gMap.settings.gen.season<0 then
      [*] = ;               begin
      [*] = ;                  var bAllowWinter : Boolean = True;
      [*] = ;                  var bAllowAutumn : Boolean = True;
      [*] = ;                  var bAllowSpring : Boolean = True;
      [*] = ;                  if bAllowWinter and bAllowSpring and bAllowAutumn then
      [*] = ;                  begin
      [*] = ;                     if RandomExt>0.75 then
      [*] = ;                     gMap.settings.gen.season := 3
      [*] = ;                     else
      [*] = ;                     if RandomExt>0.50 then
      [*] = ;                     gMap.settings.gen.season := 2
      [*] = ;                     else
      [*] = ;                     if RandomExt>0.25 then
      [*] = ;                     gMap.settings.gen.season := 1
      [*] = ;                     else
      [*] = ;                     gMap.settings.gen.season := 0;
      [*] = ;                  end
      [*] = ;               end;
      [*] = ;               gMap.brating := False;
      [*] = ;               gbool_gui_hidenicks := False;
      [*] = ;
      [*] = ;               _misc_SetupMapPlayersInfo();
      [*] = ;               StateMachineGlobalVariablesSaveToParser(pLan, 'gMap', False, False);
      [*] = ;               LanSendParser(gc_LAN_GENERATE, pLan);
      [*] = ;               //Log('EventCustomGame:LanSendParser:gc_LAN_GENERATE');
      [*] = ;            end;
      [*] = ;            LanLockServer;
      [*] = ;            DoStartGame();
      [*] = ;
      [*] = ;            // save multiplayer room settings start part 2
      [*] = ;            gProfileUserStruct.custommap.settings.gen.randkey0 := 0;
      [*] = ;            gProfileUserStruct.custommap.settings.gen.randkey1 := 0;
      [*] = ;            _profile_SaveStructToUserProfileParser('gProfileUserStruct');
      [*] = ;            // save multiplayer room settings finish part 2
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            _gui_SetGUIElementVisibleByName(elmname, False);
      [*] = ;            if (_net_IsOffline) then
      [*] = ;            begin
      [*] = ;               gProfileUserStruct.custommap := gMap;
      [*] = ;               gProfileUserStruct.custommap.bbattle := false;
      [*] = ;               gProfileUserStruct.custommap.battlestage := 0;
      [*] = ;               gProfileUserStruct.custommap.settings.gen.randkey0 := 0;
      [*] = ;               gProfileUserStruct.custommap.settings.gen.randkey1 := 0;
      [*] = ;               _profile_SaveStructToUserProfileParser('gProfileUserStruct');
      [*] = ;            end;
      [*] = ;            ExecuteState('DoNewGame');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cTagStartAutoSearch : begin
      [*] = ;         if gInternetShell.qprequeststart=0 then
      [*] = ;         gInternetShell.qprequeststart := _misc_GetRealTime;
      [*] = ;         gInternetShell.qprequeststop := 0;
      [*] = ;      end;
      [*] = ;      cTagStopAutoSearch : begin
      [*] = ;         if gInternetShell.qprequeststop=0 then
      [*] = ;         gInternetShell.qprequeststop := _misc_GetRealTime;
      [*] = ;         gInternetShell.qprequeststart := 0;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

