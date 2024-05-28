section.begin
   Name = EventCreateJoinRoom
   Code : struct.begin
      [*] = ;procedure GetInputBoxValueToVar(elmpath, elmname : String; var value : String);
      [*] = ;begin
      [*] = ;   var parent : Integer = GetGUIElementIndexByNameParent(elmpath, _gui_GetTop);
      [*] = ;   if (parent<>0) then
      [*] = ;   begin
      [*] = ;      var childHnd : Integer = _gui_FindChildHandleByName(parent, elmname);
      [*] = ;      if (childHnd<>0) and GetGUIElementVisible(childHnd) then
      [*] = ;      begin
      [*] = ;         var inputboxHnd : Integer = GetGUIElementIndexByNameParent('text', childHnd);
      [*] = ;         var className : String = GetObjectClassNameByHandle(inputboxHnd);
      [*] = ;         //if (SameText(className, 'TXEditControl')) then
      [*] = ;         value := GetGUIElementText(inputboxHnd);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;const cEscChar    = 27; // Escape
      [*] = ;const cReturnChar = 13; // Enter or Return
      [*] = ;
      [*] = ;var elmHnd : Integer = GetIntValueByName('ElementHandle');
      [*] = ;var press : String = GetValueByName('Press');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;
      [*] = ;var status : String = GetValueByName('Status');
      [*] = ;if (status='shortcut') or (status='key') then // to prevent invalid handle here
      [*] = ;elmHnd := 0;
      [*] = ;
      [*] = ;const currentstatename = 'EventCreateJoinRoom';
      [*] = ;var elmname, showstate, eventstate : String;
      [*] = ;_misc_GetGUIShowEventStateNames(currentstatename, elmname, showstate, eventstate);
      [*] = ;
      [*] = ;const cTagCreate = 101;
      [*] = ;const cTagJoin = 102;
      [*] = ;const cTagAddPass = 103;
      [*] = ;const cTagRatingRoom = 104;
      [*] = ;const cTagCreateBattle = 105;
      [*] = ;
      [*] = ;if (GetGUIFocusedElementHandle<>0) then
      [*] = ;SetGUIEventStateOnKeyDown(eventstate)
      [*] = ;else
      [*] = ;SetGUIEventStateOnKeyDown('');
      [*] = ;
      [*] = ;case status of
      [*] = ;   'key' : begin
      [*] = ;      if (press='d') then
      [*] = ;      begin
      [*] = ;         case tag of
      [*] = ;            cReturnChar : begin
      [*] = ;               status := 'shortcut';
      [*] = ;               press := 'c';
      [*] = ;               //gInternetShell.bhistoricalbattle := False;
      [*] = ;               if (gInternetShell.bjoin) then
      [*] = ;               tag := cTagJoin
      [*] = ;               else
      [*] = ;               tag := cTagCreate;
      [*] = ;            end;
      [*] = ;            cEscChar : begin
      [*] = ;               //gInternetShell.bhistoricalbattle := False;
      [*] = ;               _gui_SetGUIElementVisibleByName(elmname, False);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (press='c') then
      [*] = ;begin
      [*] = ;   case tag of
      [*] = ;      gc_gui_event_tagShow : ExecuteState(showstate);
      [*] = ;      gc_gui_event_tagHide : begin
      [*] = ;         _gui_SetGUIElementVisibleByName(elmname, False);
      [*] = ;         //gInternetShell.bhistoricalbattle := False;
      [*] = ;      end;
      [*] = ;      gc_gui_event_tagClose, gc_gui_hotkey_btnEscape : begin
      [*] = ;         _gui_SetGUIElementVisibleByName(elmname, False);
      [*] = ;         //gInternetShell.bhistoricalbattle := False;
      [*] = ;      end;
      [*] = ;      cTagCreate : begin
      [*] = ;         if (gInternetShell.currentsessionid<=0) then
      [*] = ;         begin
      [*] = ;            var elmPath : String = elmname+'.main';
      [*] = ;            var gamename, pass : String;
      [*] = ;            GetInputBoxValueToVar(elmPath, 'gamename', gamename);
      [*] = ;
      [*] = ;            var elmMain : Integer = GetGUIElementIndexByNameParent(elmname+'.main', _gui_GetTop);
      [*] = ;            GetInputBoxValueToVar(elmPath, 'pass', pass);
      [*] = ;
      [*] = ;            if (gamename<>'') then
      [*] = ;            begin
      [*] = ;               //gInternetShell.currentsessionid := LanMyInfoID;
      [*] = ;
      [*] = ;               //reset map settings start
      [*] = ;               _map_ResetMapSettings(gMap, False, not gInternetShell.bratingroom, False, gInternetShell.bratingroom, False, False);
      [*] = ;               gMap.bbattle := gInternetShell.bhistoricalbattle;
      [*] = ;               //reset map settings finish
      [*] = ;
      [*] = ;               var checksum : String;
      [*] = ;               if gbool_modsscript then
      [*] = ;               begin
      [*] = ;                  checksum := gstring_checksum;
      [*] = ;                  if (gInternetShell.bhistoricalbattle) then
      [*] = ;                  checksum := 'h'+checksum;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if (gInternetShell.bhistoricalbattle) then
      [*] = ;                  checksum := 'h'+gstring_checksum
      [*] = ;                  else
      [*] = ;                  if gInternetShell.bratingroom then
      [*] = ;                  checksum := 'r'+gstring_checksum
      [*] = ;                  else
      [*] = ;                  checksum := '0'+gstring_checksum;
      [*] = ;               end;
      [*] = ;
      [*] = ;               LanCreateGame('', #34+gamename+#34+#9+#34+pass+#34+#9+checksum, '0', gc_MaxPlayerCount-1);
      [*] = ;               var team : Integer = _misc_GetClLanTeamByLanID(LanMyInfoID);
      [*] = ;               LanClSetMyTeam(gc_MaxPlayerCount+1);
      [*] = ;               Log('LanClSetMyTeam('+IntToStr(gc_MaxPlayerCount+1)+')');
      [*] = ;               _gui_SetGUIElementVisibleByName(elmname, False);
      [*] = ;               LanPublicServerUpdateClientInfo(LanMyInfoID);
      [*] = ;               LanPublicServerUpdateInfo; // shut down if srv version is different than client
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               _gui_ShowModalMessage('gui|internet.error', 'gui|internet.incorrectgamename', GetLocaleTableListItemByID('misc', 'btn.closewindow'), '', gc_gui_event_tagClose, 0);
      [*] = ;               SetGUIElementFocusedHandle(0);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cTagJoin : begin
      [*] = ;         if gInternetShell.selsessionid>0 then
      [*] = ;         begin
      [*] = ;            var bEnabled : Boolean;
      [*] = ;            if (gInternetShell.selsessionid>0) then
      [*] = ;            begin
      [*] = ;               var psessions : Pointer = gInternetShell.sessions.GetByMasterID(gInternetShell.selsessionid);
      [*] = ;               if (psessions<>nil) then
      [*] = ;               begin
      [*] = ;                  var bclosed : Boolean = TInternetShellSession(psessions).bclosed;
      [*] = ;                  var blocked : Boolean = TInternetShellSession(psessions).blocked;
      [*] = ;                  bEnabled := (not bclosed) and (not blocked);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            if (bEnabled) then
      [*] = ;            begin
      [*] = ;               var pclient : Pointer = gInternetShell.clients.GetByLanID(gInternetShell.selsessionid);
      [*] = ;               if pclient<>nil then
      [*] = ;               begin
      [*] = ;                  var elmPath : String = elmname+'.main';
      [*] = ;                  var inputpass : String;
      [*] = ;                  GetInputBoxValueToVar(elmPath, 'pass', inputpass);
      [*] = ;                  var visiblename, pass, roomchecksum : String;
      [*] = ;                  var psessions : Pointer = gInternetShell.sessions.GetByMasterID(gInternetShell.selsessionid);
      [*] = ;                  if (psessions<>nil) and (not gbool_modsyncparserwait) then
      [*] = ;                  begin
      [*] = ;                     _misc_GetGameNameAndPasswordBySession(psessions, visiblename, pass, roomchecksum);
      [*] = ;                     if SameText(pass, inputpass) then
      [*] = ;                     begin
      [*] = ;                        //gInternetShell.currentsessionid := gInternetShell.selsessionid;
      [*] = ;                        var selsessionid : Integer = gInternetShell.selsessionid;
      [*] = ;                        gInternetShell.selsessionid := 0;
      [*] = ;                        //LanSetMyNick(TInternetShellClient(pclient).nick);
      [*] = ;                        var i : Integer;
      [*] = ;                        for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;                        _map_ResetMapPlayer(gMap.players[i], i, False);
      [*] = ;                        gstring_roomchecksum := roomchecksum;
      [*] = ;                        if (StrLength(roomchecksum)=5) and (SubStr(roomchecksum, 1, 1)='r') then
      [*] = ;                        gInternetShell.bratingroom := True
      [*] = ;                        else
      [*] = ;                        gInternetShell.bratingroom := False;
      [*] = ;                        if (StrLength(roomchecksum)=5) and (SubStr(roomchecksum, 1, 1)='h') then
      [*] = ;                        gInternetShell.bhistoricalbattle := True
      [*] = ;                        else
      [*] = ;                        gInternetShell.bhistoricalbattle := False;
      [*] = ;                        gint_gui_lanrequestjoinsessionid := selsessionid;
      [*] = ;                        LanJoinGame('', IntToStr(selsessionid), False);
      [*] = ;                        _gui_SetGUIElementVisibleByName(elmname, False);
      [*] = ;                        LanPublicServerUpdateInfo; // shut down if srv version is different than client
      [*] = ;                        LanPublicServerUpdateClientInfo(LanMyInfoID);
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     _gui_ShowConnectStateMessage(gc_ConnectState_InvalidPass);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cTagAddPass : begin
      [*] = ;         gInternetShell.bprivate := True;
      [*] = ;         ExecuteState(showstate);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var pressedelmname : String;
      [*] = ;if (elmHnd<>0) then pressedelmname := GetGUIElementNameByIndex(elmHnd);
      [*] = ;if (press='d') then
      [*] = ;begin
      [*] = ;   if (pressedelmname='bratingroom') then
      [*] = ;   begin
      [*] = ;      SetGUIElementChecked(elmHnd, not GetGUIElementChecked(elmHnd));
      [*] = ;      gInternetShell.bratingroom := GetGUIElementChecked(elmHnd);
      [*] = ;      ExecuteState(showstate);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (pressedelmname='bhistorical') then
      [*] = ;   begin
      [*] = ;      SetGUIElementChecked(elmHnd, not GetGUIElementChecked(elmHnd));
      [*] = ;      gInternetShell.bhistoricalbattle := not gInternetShell.bhistoricalbattle;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

