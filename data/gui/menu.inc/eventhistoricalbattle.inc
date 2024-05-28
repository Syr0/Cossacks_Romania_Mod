section.begin
   Name = EventHistoricalBattle
   Code : struct.begin
      [*] = ;procedure DoStartGame;
      [*] = ;begin
      [*] = ;   LanDoStart();
      [*] = ;end;
      [*] = ;var elmHnd : Integer = GetIntValueByName('ElementHandle');
      [*] = ;var press : String = GetValueByName('Press');
      [*] = ;var status : String = GetValueByName('Status');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;var key : String = GetValueByName('Key');
      [*] = ;
      [*] = ;const currentstatename = 'EventHistoricalBattle';
      [*] = ;var elmname, showstate, eventstate : String;
      [*] = ;_misc_GetGUIShowEventStateNames(currentstatename, elmname, showstate, eventstate);
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
      [*] = ;if (status='select') then
      [*] = ;begin
      [*] = ;   tag := GetGUIListBoxItemTag(elmHnd, GetGUIListBoxItemIndex(elmHnd));
      [*] = ;   var elmname : String = GetGUIElementNameByIndex(elmHnd);
      [*] = ;   case elmname of
      [*] = ;      'mapchooser' : begin
      [*] = ;         gMap.battleind := tag;
      [*] = ;         ExecuteState(showstate);
      [*] = ;      end;
      [*] = ;      'season' : gMap.settings.gen.season := tag;
      [*] = ;      'terraintype' : gMap.settings.gen.terraintype := tag;
      [*] = ;      'relieftype' : gMap.settings.gen.relieftype := tag;
      [*] = ;      'foreststype' : gMap.settings.gen.relieftype := tag;
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
      [*] = ;            7 : gMap.settings.additional.teams := tag;
      [*] = ;            8 : gMap.settings.additional.limit := tag;
      [*] = ;            9 : gMap.settings.additional.gamespeed := tag;
      [*] = ;            10 : gMap.settings.additional.adviserassistant := tag;
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
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if tag<0 then
      [*] = ;            begin
      [*] = ;               _map_ResetMapPlayer(gMap.players[ind], ind, (gInternetShell.bratingroom or gInternetShell.bautosearch));
      [*] = ;               gMap.players[ind].bclosed := False;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'position' : begin
      [*] = ;            gMap.players[ind].cid := tag;
      [*] = ;         end;
      [*] = ;         'team' : begin
      [*] = ;            _misc_SetClLanTeamByIndex(ind, tag)
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
      [*] = ;         var humancount : Integer;
      [*] = ;         var i : Integer;
      [*] = ;         for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;         if (gMap.players[i].bexists) and (gMap.players[i].lanid>0) then
      [*] = ;         humancount := humancount+1;
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
      [*] = ;               var clean : TMapSettingsAdditional;
      [*] = ;               gMap.settings.additional := clean;
      [*] = ;               //gProfile.igamespeed := 1;
      [*] = ;               if gMap.settings.gen.season<0 then
      [*] = ;               begin
      [*] = ;                  var bAllowWinter : Boolean = True;
      [*] = ;                  var bAllowSpring : Boolean = True;
      [*] = ;                  var bAllowAutumn : Boolean = True;
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
      [*] = ;
      [*] = ;               //if (gProfile.bdevmode) then
      [*] = ;               //_misc_SaveVariableToFileName('gMap', 'gMap1');
      [*] = ;
      [*] = ;               // prepare gMap players order to correspond selected teams and pos
      [*] = ;               // counting teams
      [*] = ;               var i : Integer;
      [*] = ;               var countteam1 : Integer;
      [*] = ;               var countteam2 : Integer;
      [*] = ;               for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;               begin
      [*] = ;                  var lanid : Integer = gMap.players[i].lanid;
      [*] = ;                  if (lanid<>0) then
      [*] = ;                  begin
      [*] = ;                     var team : Integer = gMap.players[i].team;
      [*] = ;                     if team=1 then
      [*] = ;                     countteam1 := countteam1+1
      [*] = ;                     else
      [*] = ;                     if team=2 then
      [*] = ;                     countteam2 := countteam2+1;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               // look for free pos
      [*] = ;               var freeposteam1 : TIntegerList;
      [*] = ;               var freeposteam2 : TIntegerList;
      [*] = ;               for i:=0 to countteam1-1 do
      [*] = ;               freeposteam1.Add(i);
      [*] = ;               for i:=0 to countteam2-1 do
      [*] = ;               freeposteam2.Add(4+i);
      [*] = ;               // delete used pos from freepos list
      [*] = ;               for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;               if (gMap.players[i].lanid<>0) then
      [*] = ;               case gMap.players[i].team of
      [*] = ;                  1 : begin
      [*] = ;                     if (gMap.players[i].cid>countteam1) then // reset if invalid team
      [*] = ;                     gMap.players[i].cid := gc_MaxCountryCount;
      [*] = ;                     if (gMap.players[i].cid<gc_MaxCountryCount) then
      [*] = ;                     begin
      [*] = ;                        var ind : Integer = freeposteam1.IndexOf(gMap.players[i].cid);
      [*] = ;                        if (ind>=0) then
      [*] = ;                        freeposteam1.Delete(ind);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  2 : begin
      [*] = ;                     if (gMap.players[i].cid>(countteam2+4)) or (gMap.players[i].cid<4) then // reset if invalid team
      [*] = ;                     gMap.players[i].cid := gc_MaxCountryCount;
      [*] = ;                     if (gMap.players[i].cid<gc_MaxCountryCount) then
      [*] = ;                     begin
      [*] = ;                        var ind : Integer = freeposteam2.IndexOf(gMap.players[i].cid);
      [*] = ;                        if (ind>=0) then
      [*] = ;                        freeposteam2.Delete(ind);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               // give free pos to players without pos
      [*] = ;               for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;               if (gMap.players[i].lanid<>0) and (gMap.players[i].cid=gc_MaxCountryCount) then
      [*] = ;               begin
      [*] = ;                  case gMap.players[i].team of
      [*] = ;                     1 : begin
      [*] = ;                        if (freeposteam1.GetCount>0) then
      [*] = ;                        begin
      [*] = ;                           var newind : Integer = Floor(Random*freeposteam1.GetCount);
      [*] = ;                           var newpos : Integer = freeposteam1.Get(newind);
      [*] = ;                           gMap.players[i].cid := newpos;
      [*] = ;                           freeposteam1.Delete(newind);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                     2 : begin
      [*] = ;                        if (freeposteam2.GetCount>0) then
      [*] = ;                        begin
      [*] = ;                           var newind : Integer = Floor(Random*freeposteam2.GetCount);
      [*] = ;                           var newpos : Integer = freeposteam2.Get(newind);
      [*] = ;                           gMap.players[i].cid := newpos;
      [*] = ;                           freeposteam2.Delete(newind);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               var mainlistteam1 : TIntegerList;
      [*] = ;               var seclistteam1 : TIntegerList;
      [*] = ;               var mainlistteam2 : TIntegerList;
      [*] = ;               var seclistteam2 : TIntegerList;
      [*] = ;               for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;               begin
      [*] = ;                  var lanid : Integer = gMap.players[i].lanid;
      [*] = ;                  if (lanid<>0) then
      [*] = ;                  begin
      [*] = ;                     var team : Integer = gMap.players[i].team;
      [*] = ;                     if (team=1) then
      [*] = ;                     begin
      [*] = ;                        var pos : Integer = gMap.players[i].cid;
      [*] = ;                        mainlistteam1.Add(pos);
      [*] = ;                        seclistteam1.Add(i);
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     if (team=2) then
      [*] = ;                     begin
      [*] = ;                        var pos : Integer = gMap.players[i].cid;
      [*] = ;                        mainlistteam2.Add(pos);
      [*] = ;                        seclistteam2.Add(i);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               _misc_SortIntegerLists2D(mainlistteam1, seclistteam1, False);
      [*] = ;               _misc_SortIntegerLists2D(mainlistteam2, seclistteam2, False);
      [*] = ;               var maptmp : TMap;
      [*] = ;               for i:=0 to seclistteam1.GetCount-1 do
      [*] = ;               maptmp.players[i] := gMap.players[seclistteam1.Get(i)];
      [*] = ;               for i:=0 to seclistteam2.GetCount-1 do
      [*] = ;               maptmp.players[i+4] := gMap.players[seclistteam2.Get(i)];
      [*] = ;               for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;               begin
      [*] = ;                  gMap.players[i] := maptmp.players[i];
      [*] = ;                  gMap.players[i].id := i;
      [*] = ;               end;
      [*] = ;               for i:=0 to 3 do
      [*] = ;               gMap.players[i].team := 1;
      [*] = ;               for i:=4 to 7 do
      [*] = ;               gMap.players[i].team := 2;
      [*] = ;               //if (gProfile.bdevmode) then
      [*] = ;               //_misc_SaveVariableToFileName('gMap', 'gMap2');
      [*] = ;               gMap.settings.additional.gamespeed := 0;
      [*] = ;
      [*] = ;               _misc_SetupMapPlayersInfo();
      [*] = ;               StateMachineGlobalVariablesSaveToParser(pLan, 'gMap', False, False);
      [*] = ;               gbool_gui_hidenicks := False;
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
      [*] = ;      cTagGoPickPositions : begin
      [*] = ;         gMap.battlestage := 1;
      [*] = ;         var i : Integer;
      [*] = ;         for i:=1 to gc_MaxPlayerCount-2 do
      [*] = ;         begin
      [*] = ;            var lanid : Integer = gMap.players[i].lanid;
      [*] = ;            if (lanid=0) then
      [*] = ;            begin
      [*] = ;               gMap.players[i].bexists := False;
      [*] = ;               gMap.players[i].bai := False;
      [*] = ;               gMap.players[i].bhuman := False;
      [*] = ;               gMap.players[i].aidifficulty := 0;
      [*] = ;               gMap.players[i].color := i;
      [*] = ;               gMap.players[i].bclosed := True;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if gMap.players[i].bexists and gMap.players[i].bhuman then
      [*] = ;            gMap.players[i].bready := False;
      [*] = ;         end;
      [*] = ;         if (_net_IsOnline) and (_net_IsServer) then
      [*] = ;         _misc_InternetShellUpdateCurrentSessionName(gInternetShell, True);
      [*] = ;         ExecuteState(showstate);
      [*] = ;      end;
      [*] = ;      cTagChangeTeam : begin
      [*] = ;         var bFirstTeamIsFull, bSecondTeamIsFull : Boolean;
      [*] = ;         var i, k, n: Integer;
      [*] = ;         for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;         begin
      [*] = ;            if gMap.players[i].bexists and gMap.players[i].bhuman then
      [*] = ;            begin
      [*] = ;               if (gMap.players[i].team = 1) then
      [*] = ;               k := k + 1;
      [*] = ;               if (gMap.players[i].team = 2) then
      [*] = ;               n := n + 1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if (k=4) then
      [*] = ;         bFirstTeamIsFull := True;
      [*] = ;         if (n=4) then
      [*] = ;         bSecondTeamIsFull := True;
      [*] = ;         if (gMap.players[gint_net_myindex].team=1) then
      [*] = ;         begin
      [*] = ;            if (not bSecondTeamIsFull) then
      [*] = ;            begin
      [*] = ;               if (key='LButton') then
      [*] = ;               gMap.players[gint_net_myindex].team := 2
      [*] = ;               else
      [*] = ;               gMap.players[gint_net_myindex].team := 0;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            gMap.players[gint_net_myindex].team := 0;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if (gMap.players[gint_net_myindex].team=2) then
      [*] = ;         begin
      [*] = ;            if (key='LButton') then
      [*] = ;            gMap.players[gint_net_myindex].team := 0
      [*] = ;            else
      [*] = ;            if (not bFirstTeamIsFull) then
      [*] = ;            gMap.players[gint_net_myindex].team := 1
      [*] = ;            else
      [*] = ;            gMap.players[gint_net_myindex].team := 0;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if (gMap.players[gint_net_myindex].team=0) then
      [*] = ;         begin
      [*] = ;            if (not bFirstTeamIsFull) then
      [*] = ;            begin
      [*] = ;               if (key='LButton') then
      [*] = ;               gMap.players[gint_net_myindex].team := 1
      [*] = ;               else
      [*] = ;               if (not bSecondTeamIsFull) then
      [*] = ;               gMap.players[gint_net_myindex].team := 2
      [*] = ;               else
      [*] = ;               gMap.players[gint_net_myindex].team := 1;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if (not bSecondTeamIsFull) then
      [*] = ;            begin
      [*] = ;               if (key='LButton') then
      [*] = ;               gMap.players[gint_net_myindex].team := 2
      [*] = ;               else
      [*] = ;               if (not bFirstTeamIsFull) then
      [*] = ;               gMap.players[gint_net_myindex].team := 1
      [*] = ;               else
      [*] = ;               gMap.players[gint_net_myindex].team := 2;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         _misc_SetClLanTeamByIndex(gint_net_myindex, gMap.players[gint_net_myindex].team);
      [*] = ;
      [*] = ;         var ind : Integer = gint_net_myindex;
      [*] = ;         if (_net_IsOnline) then
      [*] = ;         begin
      [*] = ;            if (_net_IsServer) then
      [*] = ;            _misc_InternetShellUpdateCurrentSessionName(gInternetShell, True)
      [*] = ;            else
      [*] = ;            if (_net_IsClient) and (ind>=0) and (ind<gc_MaxPlayerCount-1) then
      [*] = ;            begin
      [*] = ;               var pLan : Integer = _parser_ParserTemporary(True);
      [*] = ;               ParserSetValueByKeyByHandle(pLan, 's', IntToStr(gMap.players[ind].cid)+gc_gui_delimitercharstr+IntToStr(gMap.players[ind].team)+gc_gui_delimitercharstr+IntToStr(gMap.players[ind].color));
      [*] = ;               LanPublicServerSendSessionParser(gLanHostID, gc_LAN_ROOM_CLIENT_DATACHANGE, pLan);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         ExecuteState(showstate);
      [*] = ;      end;
      [*] = ;      cTagChangePosition : begin
      [*] = ;         function CheckDoublePosition(testplayer, testposition : Integer; bAdjust, bDirectionForward : Boolean) : Integer;
      [*] = ;         begin
      [*] = ;            var countteam1, countteam2 : Integer;
      [*] = ;            var i: Integer;
      [*] = ;            for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;            begin
      [*] = ;               if gMap.players[i].bexists and gMap.players[i].bhuman then
      [*] = ;               begin
      [*] = ;                  if (gMap.players[i].team=1) then
      [*] = ;                  countteam1 := countteam1+1
      [*] = ;                  else
      [*] = ;                  if (gMap.players[i].team=2) then
      [*] = ;                  countteam2 := countteam2+1;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            const cmaxteamcount = 4;
      [*] = ;            var minind, maxind : Integer;
      [*] = ;            var defind : Integer = gc_MaxCountryCount;
      [*] = ;            if (gMap.players[testplayer].team=1) then
      [*] = ;            begin
      [*] = ;               minind := 0;
      [*] = ;               maxind := minind+countteam1-1;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               minind := cmaxteamcount{cteamposcount};
      [*] = ;               maxind := minind+countteam2-1;
      [*] = ;            end;
      [*] = ;            var newtestposition : Integer = testposition;
      [*] = ;            if (bAdjust) then
      [*] = ;            begin
      [*] = ;               if (bDirectionForward) then
      [*] = ;               begin
      [*] = ;                  if newtestposition=defind then
      [*] = ;                  newtestposition := minind
      [*] = ;                  else
      [*] = ;                  if newtestposition>(maxind-1) then
      [*] = ;                  newtestposition := defind
      [*] = ;                  else
      [*] = ;                  newtestposition := newtestposition+1;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if (newtestposition=defind) then
      [*] = ;                  newtestposition := maxind
      [*] = ;                  else
      [*] = ;                  if newtestposition<=minind then
      [*] = ;                  newtestposition := defind
      [*] = ;                  else
      [*] = ;                  newtestposition := newtestposition-1;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            Result := newtestposition;
      [*] = ;            var bDoubleColor : Boolean;
      [*] = ;            var j : Integer;
      [*] = ;            for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;            begin
      [*] = ;               if (i<>testplayer) and (gMap.players[i].bexists) and (Result<>gc_MaxCountryCount) and (gMap.players[i].cid=newtestposition) then
      [*] = ;               begin
      [*] = ;                  Result := CheckDoublePosition(testplayer, newtestposition, bAdjust, bDirectionForward);
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var ind : Integer = -1;
      [*] = ;         var key : String = GetValueByName('Key');
      [*] = ;         var s1, s2, s3, s4 : String;
      [*] = ;         _misc_GetDelimiterString(elmname, gc_gui_delimiterchar, s1, s2, s3, s4);
      [*] = ;         //log('comboname='+s1+'['+s2+'] := '+IntToStr(tag));
      [*] = ;         ind := gint_net_myindex;
      [*] = ;         gMap.players[ind].cid := CheckDoublePosition(ind, gMap.players[ind].cid, True, (key='LButton'));
      [*] = ;         if (_net_IsOnline) then
      [*] = ;         begin
      [*] = ;            if (_net_IsServer) then
      [*] = ;            _misc_InternetShellUpdateCurrentSessionName(gInternetShell, True)
      [*] = ;            else
      [*] = ;            if (_net_IsClient) and (ind>=0) and (ind<gc_MaxPlayerCount-1) then
      [*] = ;            begin
      [*] = ;               var pLan : Integer = _parser_ParserTemporary(True);
      [*] = ;               ParserSetValueByKeyByHandle(pLan, 's', IntToStr(gMap.players[ind].cid)+gc_gui_delimitercharstr+IntToStr(gMap.players[ind].team)+gc_gui_delimitercharstr+IntToStr(gMap.players[ind].color));
      [*] = ;               LanPublicServerSendSessionParser(gLanHostID, gc_LAN_ROOM_CLIENT_DATACHANGE, pLan);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         ExecuteState(showstate);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

