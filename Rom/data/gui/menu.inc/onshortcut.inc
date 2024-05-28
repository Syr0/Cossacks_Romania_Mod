section.begin
   Name = OnShortcut
   Code : struct.begin
      [*] = ;if (gbool_gui_ignoreonshortcut) then
      [*] = ;exit;
      [*] = ;
      [*] = ;type TOfficerFormationMask = class
      [*] = ;   count : array [0..gc_country_maxofficersformationmask-1] of Integer;
      [*] = ;   bexists : array [0..gc_country_maxofficersformationmask-1] of Boolean;
      [*] = ;end;
      [*] = ;type TOfficerFormation = class
      [*] = ;   units : array [0..gc_country_maxformationunitcount-1] of TOfficerFormationMask;
      [*] = ;end;
      [*] = ;var arrOfficerFormation : array [0..gc_country_maxformationunitcount-1] of TOfficerFormation;
      [*] = ;//var arrOfficerUnitsCount : array [0..gc_country_maxformationunitcount-1] of Integer;
      [*] = ;// arrOfficerFormation finish
      [*] = ;
      [*] = ;function GetFormationInfo(plHnd, formtype : Integer; var stag : String) : Boolean;
      [*] = ;begin
      [*] = ;   var plInd : Integer = GetPlayerIndexByHandle(plHnd);
      [*] = ;   var goHnd : Integer = GetGameObjectHandleByUniqueId(gint_gui_unitcontroluid);
      [*] = ;   if (goHnd<>0) then
      [*] = ;   begin
      [*] = ;      var pobj : Pointer = _unit_GetTObj(goHnd);
      [*] = ;      if (pobj<>nil) then
      [*] = ;      begin
      [*] = ;         var psquad : Pointer;
      [*] = ;         if (gint_gui_unitcontrolsquadind>-1) then
      [*] = ;         psquad := gPlayer[plInd].squads.Get(gint_gui_unitcontrolsquadind);
      [*] = ;
      [*] = ;         var cid : Integer = TObj(pobj).cid;
      [*] = ;
      [*] = ;         var officersid : String;
      [*] = ;         if (psquad=nil) then
      [*] = ;         officersid := GetGameObjectBaseNameByHandle(goHnd)
      [*] = ;         else
      [*] = ;         _unit_ConvertObjIDToSID(cid, TSquad(psquad).fOfficerID, officersid);
      [*] = ;
      [*] = ;         var ind : Integer = _country_GetOfficersIndexByOfficerSID(cid, officersid);
      [*] = ;         if (ind>-1) then
      [*] = ;         begin
      [*] = ;            var i, j, k : Integer;
      [*] = ;            for i:=0 to gc_country_maxformationcount-1 do
      [*] = ;            begin
      [*] = ;               //gCountry[cid].officers[ind].formations[i].stype;
      [*] = ;               for j:=0 to gc_country_maxofficersformationmask-1 do
      [*] = ;               begin
      [*] = ;                  if (gCountry[cid].officers[ind].formations[i].masks[j]<>'') then
      [*] = ;                  begin
      [*] = ;                     var maskid : Integer = _misc_GetFormationIndexBySID(gCountry[cid].officers[ind].formations[i].masks[j]);
      [*] = ;                     for k:=0 to gc_country_maxformationunitcount-1 do
      [*] = ;                     arrOfficerFormation[i].units[k].count[j] := gFormation[maskid].countunits;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (psquad<>nil) then
      [*] = ;         begin
      [*] = ;            var formmaskindmax : Integer;
      [*] = ;            var formmaskind : Integer = -1;
      [*] = ;            var j : Integer;
      [*] = ;            for j:=0 to gc_country_maxformationunitcount-1 do
      [*] = ;            begin
      [*] = ;               var k : Integer;
      [*] = ;               for k:=0 to gc_country_maxofficersformationmask-1 do
      [*] = ;               begin
      [*] = ;                  if (arrOfficerFormation[formtype].units[j].count[k]>0) then
      [*] = ;                  if (TSquad(psquad).fBaseCount>=arrOfficerFormation[formtype].units[j].count[k]) then
      [*] = ;                  formmaskind := k;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if (formmaskind>formmaskindmax) then
      [*] = ;               formmaskindmax := formmaskind;
      [*] = ;               var formmaskshowind : Integer = formmaskind;
      [*] = ;               if (formmaskshowind>=0) then
      [*] = ;               formmaskshowind := formmaskshowind-gint_gui_officer_formationsizedecrease;
      [*] = ;               if (formmaskshowind<0) and (formmaskind>=0) then
      [*] = ;               formmaskshowind := 0;
      [*] = ;               var ind : Integer = _country_GetOfficersIndexByOfficerSID(cid, officersid);
      [*] = ;               if (ind>-1) then
      [*] = ;               begin
      [*] = ;                  if (gCountry[cid].officers[ind].formations[formtype].masks[j]<>'') then
      [*] = ;                  begin
      [*] = ;                     stag := gCountry[cid].officers[ind].units[j];
      [*] = ;                     if (formmaskshowind>=0) then
      [*] = ;                     stag := stag+gc_gui_delimitercharstr+gCountry[cid].officers[ind].formations[formtype].masks[formmaskshowind];
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function UnitsListCanAttackPoint(const plInd : Integer; var list : TIntegerList) : Boolean;
      [*] = ;begin
      [*] = ;   Result := False;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=list.GetCount-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var goHnd : Integer = list.Get(i);
      [*] = ;      var pobj : Pointer = _unit_GetTObj(goHnd);
      [*] = ;      if (pobj<>nil) and (gObjProp[TObj(pobj).cid][TObj(pobj).id].bartprepare) then
      [*] = ;      begin
      [*] = ;         Result := True;
      [*] = ;         exit;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i:=gPlayer[plInd].squads.GetCount-1 downto 0 do
      [*] = ;   if TSquad(gPlayer[plInd].squads.Get(i)).fSelected then
      [*] = ;   begin
      [*] = ;      var psquad : Pointer = gPlayer[plInd].squads.Get(i);
      [*] = ;      var j : Integer;
      [*] = ;      for j:=TSquad(psquad).GetCount-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var goHnd : Integer = TSquad(psquad).Get(j);
      [*] = ;         var pobj : Pointer = _unit_GetTObj(goHnd);
      [*] = ;         if (pobj<>nil) and (gObjProp[TObj(pobj).cid][TObj(pobj).id].bartprepare) then
      [*] = ;         begin
      [*] = ;            Result := True;
      [*] = ;            exit;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var name : String = GetValueByName('Name');
      [*] = ;var bCtrl : Boolean = (StrExists(name, 'Ctrl'));
      [*] = ;var bShift : Boolean = (StrExists(name, 'Shift'));
      [*] = ;var bAlt : Boolean = (StrExists(name, 'Alt'));
      [*] = ;var bDouble : Boolean = GetBoolValueByName('Double');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;var bDoubleAlternative : Boolean = GetGUIShiftStateDouble;
      [*] = ;if (not bDouble) and (bDoubleAlternative) then
      [*] = ;begin
      [*] = ;   bDouble := bDoubleAlternative;
      [*] = ;   //log('bDouble=bDoubleAlternative')
      [*] = ;end;
      [*] = ;
      [*] = ;var hotkeytag : Integer;
      [*] = ;case name of
      [*] = ;   'Escape' : hotkeytag := gc_gui_hotkey_btnEscape;
      [*] = ;   'Return' : hotkeytag := gc_gui_hotkey_btnEnter;
      [*] = ;   'F10' : hotkeytag := gc_gui_hotkey_btnF10;
      [*] = ;   'F4' : hotkeytag := gc_gui_hotkey_btnF4;
      [*] = ;   'Back' : hotkeytag := gc_gui_hotkey_btnBackSpace;
      [*] = ;   'Alt+F4' : begin
      [*] = ;      _misc_Surrender(True);
      [*] = ;      _profile_SaveAdviser; // check if it is different inside
      [*] = ;      LanShutdown;
      [*] = ;      CloseQuery;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (tag<>-1) and (name<>'Ctrl+Return') then // ctrl+return, force chat
      [*] = ;begin
      [*] = ;   var bEventHandled : Boolean;
      [*] = ;   var elmTop : Integer = _gui_GetTop;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=GetGUIElementChildrenCount(elmTop)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var elmHnd : Integer = GetGUIElementChildrenByIndex(elmTop, i);
      [*] = ;      if (elmHnd<>0) and (GetGUIElementVisible(elmHnd)) then
      [*] = ;      begin
      [*] = ;         var eventstate : String = GetGUIElementPressState(elmHnd);
      [*] = ;         if (eventstate<>'') then
      [*] = ;         begin
      [*] = ;            if (hotkeytag<>0) then
      [*] = ;            begin
      [*] = ;               //Log('_gui_SendTagToState('+eventstate+', '+name+')');
      [*] = ;               _gui_SendTagToState(eventstate, hotkeytag);
      [*] = ;            end;
      [*] = ;            bEventHandled := True;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if (bEventHandled) then
      [*] = ;   begin
      [*] = ;      ExecuteState('OnShortcut1');
      [*] = ;      exit;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (gInterface.gamemode=gc_gamemode_mainmenu) or (GetPlayerHandleInterfaceIO=0) then
      [*] = ;   begin
      [*] = ;      ExecuteState('OnShortcut1');
      [*] = ;      exit;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var plHnd : Integer = GetPlayerHandleInterfaceIO;
      [*] = ;var plInd : Integer = GetPlayerIndexByHandle(plHnd);
      [*] = ;var bProcess : Boolean = (not gbool_gui_bspectator) and ((((_net_IsOffline) or (LanGetClientsCount<=1)) and (not _net_IsReplay)) or ((_net_IsOnline) and (gMap.gamestage=gc_map_gamestage_started)));
      [*] = ;
      [*] = ;if (tag=-1) then // custom hotkeys
      [*] = ;begin
      [*] = ;   var category, action, eventelm : String;
      [*] = ;   var count : Integer = GetDelimiterStringCount(name, gc_gui_delimiterchar, gc_gui_quotechar);
      [*] = ;   if (IsDelimiterCharExists(name, gc_gui_delimiterchar)) and (count>1) then
      [*] = ;   begin
      [*] = ;      category := GetDelimiterStringByIndex(name, gc_gui_delimiterchar, gc_gui_quotechar, 0);
      [*] = ;      action := GetDelimiterStringByIndex(name, gc_gui_delimiterchar, gc_gui_quotechar, 1);
      [*] = ;      if (category='event') then
      [*] = ;      begin
      [*] = ;         if (count>2) then
      [*] = ;         eventelm := GetDelimiterStringByIndex(name, gc_gui_delimiterchar, gc_gui_quotechar, 2)
      [*] = ;         else
      [*] = ;         ErrorLog('Shortcut category = event, but not enough params. check .data\game\var\hotkeys.cfg');
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   action := name;
      [*] = ;
      [*] = ;   case category of
      [*] = ;      'event' : begin
      [*] = ;         if (count>2) then
      [*] = ;         begin
      [*] = ;            var state : String = action;
      [*] = ;            var elmname, showstate, eventstate : String;
      [*] = ;            _misc_GetGUIShowEventStateNames(state, elmname, showstate, eventstate);
      [*] = ;            var parentElm : Integer = GetGUIElementIndexByNameParent(elmname, _gui_GetTop);
      [*] = ;            if (parentElm<>0) and GetGUIElementVisible(parentElm) then
      [*] = ;            begin
      [*] = ;               var elm : Integer = _gui_FindChildHandleByName(parentElm, eventelm);
      [*] = ;               if (elm<>0) and (_gui_GetGUIElementVisibleInherited(elm)) and (GetGUIElementEnabled(elm)) then
      [*] = ;               begin
      [*] = ;                  var tag : Integer = GetGUIElementTag(elm);
      [*] = ;                  if (tag<>0) then
      [*] = ;                  _gui_SendTagToState(eventstate, tag);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      'build' : begin
      [*] = ;         if (bProcess) and (gInterface.control.bshowproduce) then
      [*] = ;         begin
      [*] = ;            var goHnd : Integer = GetGameObjectHandleByUniqueId(gint_gui_unitcontroluid);
      [*] = ;            if (goHnd<>0) then
      [*] = ;            begin
      [*] = ;               var pobj : Pointer = _unit_GetTObj(goHnd);
      [*] = ;               if (pobj<>nil) then
      [*] = ;               begin
      [*] = ;                  var cid : Integer = TObj(pobj).cid;
      [*] = ;
      [*] = ;                  var sid : String;
      [*] = ;                  _country_GetUnitSIDBySIDMask(action, cid, sid);
      [*] = ;
      [*] = ;                  // dublicate from event unit control
      [*] = ;                  var id : Integer = _unit_ConvertObjSIDToID(gint_gui_pickedbldcid, sid);
      [*] = ;                  var bbuilding : Boolean = gObjProp[gint_gui_pickedbldcid][id].bbuilding;
      [*] = ;                  if (bbuilding) then
      [*] = ;                  begin
      [*] = ;                     var bctrlunitcanbuild : Boolean;
      [*] = ;                     var controlsid : String = gObjProp[cid][TObj(pobj).id].sid;
      [*] = ;                     var fpind : Integer = _country_GetFixedProduceIndexBySID(cid, controlsid, False);
      [*] = ;                     if (fpind>=0) then
      [*] = ;                     begin
      [*] = ;                        var i : Integer;
      [*] = ;                        for i:=0 to gc_country_fixedproduce_maxcount-1 do
      [*] = ;                        begin
      [*] = ;                           if (sid=gCountry[cid].fixedproduce[fpind].build[i].id) then
      [*] = ;                           begin
      [*] = ;                              bctrlunitcanbuild := True;
      [*] = ;                              break;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                     if (bctrlunitcanbuild) then
      [*] = ;                     begin
      [*] = ;                        if (gint_gui_pickedbldhnd<>0) then
      [*] = ;                        _misc_GUICancelBuilding(True, False);
      [*] = ;                        if (_player_CheckAccessControlRequirements(plHnd, cid, sid)=gc_result_checkaccesscontrolreq_ok) then
      [*] = ;                        begin
      [*] = ;                           if (_unit_CanApplyCostByID(gint_gui_pickedbldcid, id, plInd)) then
      [*] = ;                           begin
      [*] = ;                              if (GetCountOfPlayers>=gc_playerind_misc) then
      [*] = ;                              begin
      [*] = ;                                 var miscplhnd : Integer = GetPlayerHandleByIndex(gc_playerind_misc);
      [*] = ;                                 var mx, my, mz : Float;
      [*] = ;                                 GetCurrentMouseWorldCoord(mx, my, mz);
      [*] = ;                                 gint_gui_pickedbldhnd := _player_CreateConstructionDummyBySID(miscplhnd, gint_gui_pickedbldcid, sid, mx, mz);
      [*] = ;                                 if (gint_gui_pickedbldhnd<>0) then
      [*] = ;                                 begin
      [*] = ;                                    _unit_DoConstructionBlinkGameObject(gint_gui_pickedbldhnd, gc_gui_blinkmode_canbuild, False, False);
      [*] = ;                                    _misc_GUIProgressPickedBldUID;
      [*] = ;                                 end;
      [*] = ;                              end;
      [*] = ;                           end
      [*] = ;                           else
      [*] = ;                           begin
      [*] = ;                              var text, s2 : String;
      [*] = ;                              var food, wood, stone, gold, iron, coal : Integer;
      [*] = ;                              _unit_GetCostByID(gint_gui_pickedbldcid, id, plInd, food, wood, stone, gold, iron, coal);
      [*] = ;                              _misc_PrepareLogMessageNotEnoughResourcesText(text, food, wood, stone, gold, iron, coal);
      [*] = ;                              _misc_ShowLogMessage(gc_logmessagesid_notenoughres, text, s2, False);
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      'unit' : begin
      [*] = ;         if (bProcess) then
      [*] = ;         case action of
      [*] = ;            'attack' : begin // 'A'
      [*] = ;               gbool_gui_goinattackmode := True;
      [*] = ;               gbool_gui_update_cursor := True;
      [*] = ;            end;
      [*] = ;            'stop' : begin // 'Ctrl+S'
      [*] = ;               _player_StopSelectedUnits(plInd, gSelectedObjects, gSelectedSquads, True);
      [*] = ;            end;
      [*] = ;            'attackpoint' : begin
      [*] = ;               if UnitsListCanAttackPoint(plInd, gSelectedObjects) then
      [*] = ;               begin
      [*] = ;                  gbool_gui_attackpointmode := True;
      [*] = ;                  gbool_gui_update_cursor := True;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            'unloadall' : begin
      [*] = ;               var i : Integer;
      [*] = ;               for i:=gSelectedSquads.GetCount-1 downto 0 do
      [*] = ;               begin
      [*] = ;                  var psquad : Pointer = gSelectedSquads.GetPointer(i);
      [*] = ;                  if (psquad<>nil) and (TSquad(psquad).GetCount>0) then
      [*] = ;                  begin
      [*] = ;                     var goHnd : Integer = TSquad(psquad).Get(0);
      [*] = ;                     if (goHnd<>0) then
      [*] = ;                     begin
      [*] = ;                        var pobj : Pointer = _unit_GetTObj(goHnd);
      [*] = ;                        if (pobj<>nil) and (TObj(pobj).brally) and (gObjProp[TObj(pobj).cid][TObj(pobj).id].usage=gc_obj_usage_transport) then
      [*] = ;                        begin
      [*] = ;                           var pinside : Pointer = _misc_GetObjectArgData(goHnd, gc_argunit_inside);
      [*] = ;                           if (pinside<>nil) and (TIntegerList(pinside).GetCount>0) then
      [*] = ;                           begin
      [*] = ;                              gIntegerList.Clear;
      [*] = ;                              gIntegerList := TIntegerList(pinside);
      [*] = ;                              _unit_DoUnitsGoOutside(gIntegerList, False, True);
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            'guard', 'cancelguard'{, 'patrol'} : begin
      [*] = ;               if ((action='guard') and (gInterface.buttons.bguard))
      [*] = ;               or ((action='cancelguard') and (gInterface.buttons.bcancelguard)) then
      [*] = ;               begin
      [*] = ;                  var i : Integer;
      [*] = ;                  for i := gSelectedObjects.GetCount-1 downto 0 do
      [*] = ;                  begin
      [*] = ;                     var goHnd : Integer = gSelectedObjects.Get(i);
      [*] = ;                     if (not _unit_IsGuard(goHnd)) then
      [*] = ;                     begin
      [*] = ;                        gbool_gui_guardmode := True;
      [*] = ;                        gbool_gui_update_cursor := True;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     _unit_ClearOrders(goHnd);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            'standground', 'nostandground', 'enableattack', 'disableattack' : begin
      [*] = ;               if ((action='standground') and (gInterface.buttons.bstandground))
      [*] = ;               or ((action='nostandground') and (gInterface.buttons.bnostandground))
      [*] = ;               or ((action='enableattack') and (gInterface.buttons.benableattack))
      [*] = ;               or ((action='disableattack') and (gInterface.buttons.bdisableattack)) then
      [*] = ;               begin
      [*] = ;                  gIntegerList.Clear;
      [*] = ;                  var i : Integer;
      [*] = ;                  for i:=0 to gPlayer[plInd].squads.GetCount-1 do
      [*] = ;                  begin
      [*] = ;                     var psquad : Pointer = gPlayer[plInd].squads.Get(i);
      [*] = ;                     if (TSquad(psquad).fSelected) then
      [*] = ;                     gIntegerList.Add(i);
      [*] = ;                  end;
      [*] = ;                  if (gIntegerList.GetCount>0) then
      [*] = ;                  begin
      [*] = ;                     case action of
      [*] = ;                        'standground' : _unit_SetSquadsStandGround(plHnd, gIntegerList, True, True);
      [*] = ;                        'nostandground' : _unit_SetSquadsStandGround(plHnd, gIntegerList, False, True);
      [*] = ;                        'disableattack' : _unit_SetSquadsSearchEnemy(plHnd, gIntegerList, False, True);
      [*] = ;                        'enableattack' : _unit_SetSquadsSearchEnemy(plHnd, gIntegerList, True, True);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  if (gSelectedObjects.GetCount>0) then
      [*] = ;                  begin
      [*] = ;                     case action of
      [*] = ;                        'standground' : _unit_ListSetStandGround(plHnd, gSelectedObjects, True, True);
      [*] = ;                        'nostandground' : _unit_ListSetStandGround(plHnd, gSelectedObjects, False, True);
      [*] = ;                        'disableattack' : _unit_ListSetSearchEnemy(plHnd, gSelectedObjects, False, True);
      [*] = ;                        'enableattack' : _unit_ListSetSearchEnemy(plHnd, gSelectedObjects, True, True);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            'patrol' : begin
      [*] = ;               if (gSelectedObjects.GetCount > 0) then
      [*] = ;               begin
      [*] = ;                 gbool_gui_patrolmode := True;
      [*] = ;                 gbool_gui_update_cursor := True;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      'squad' : begin
      [*] = ;         if (bProcess) then
      [*] = ;         case action of
      [*] = ;            'rank', 'column', 'square' : begin
      [*] = ;               if (action='rank' and (gInterface.buttons.bsquadrank))
      [*] = ;               or (action='column' and (gInterface.buttons.bsquadcolumn))
      [*] = ;               or (action='square' and (gInterface.buttons.bsquadsquare)) then
      [*] = ;               begin
      [*] = ;                  var psquad : Pointer;
      [*] = ;                  if (gint_gui_unitcontrolsquadind>-1) then
      [*] = ;                  psquad := gPlayer[plInd].squads.Get(gint_gui_unitcontrolsquadind);
      [*] = ;
      [*] = ;                  if (psquad=nil) then
      [*] = ;                  begin
      [*] = ;                     case action of
      [*] = ;                        'rank' : gint_gui_officer_selectedformation := 0;
      [*] = ;                        'column' : gint_gui_officer_selectedformation := 1;
      [*] = ;                        'square' : gint_gui_officer_selectedformation := 2;
      [*] = ;                     end;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     var formtype : Integer;
      [*] = ;                     case action of
      [*] = ;                        'rank' : formtype := 0;
      [*] = ;                        'column' : formtype := 1;
      [*] = ;                        'square' : formtype := 2;
      [*] = ;                     end;
      [*] = ;                     var stag : String;
      [*] = ;                     GetFormationInfo(plHnd, formtype, stag);
      [*] = ;                     var s1, s2, s3, s4 : String;
      [*] = ;                     _misc_GetDelimiterString(stag, gc_gui_delimiterchar, s1, s2, s3, s4);
      [*] = ;                     if s2<>'' then
      [*] = ;                     begin
      [*] = ;                        var formName : String = s2;
      [*] = ;                        var formInd : Integer = _misc_GetFormationIndexBySID(formName);
      [*] = ;                        var i : Integer;
      [*] = ;                        for i:=0 to gPlayer[plInd].squads.GetCount-1 do
      [*] = ;                        begin
      [*] = ;                           var ptmpsquad : Pointer = gPlayer[plInd].squads.Get(i);
      [*] = ;                           if (ptmpsquad<>nil) then
      [*] = ;                           begin
      [*] = ;                              if (TSquad(ptmpsquad).fSelected) then
      [*] = ;                              begin
      [*] = ;                                 _player_SetSquadFormation(plHnd, i, formInd, True, true);
      [*] = ;                                 {var posX, posZ : Float;
      [*] = ;                                 _squad_GetSquadPosition(plHnd, pTmpSquad, posX, posZ);
      [*] = ;                                 var dirX : Float = TSquad(ptmpsquad).fDirX;
      [*] = ;                                 var dirZ : Float = TSquad(ptmpsquad).fDirZ;
      [*] = ;                                 _player_SetSquadPosition(plHnd, i, posX, posZ, dirX, dirZ, false, false, gc_obj_order_move_mode_default, false);}
      [*] = ;
      [*] = ;                                 psquad := ptmpsquad;
      [*] = ;                              end;
      [*] = ;                           end
      [*] = ;                           else
      [*] = ;                           ErrorLog('OnShortcut : ptmpsquad=nil');
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            'fill' : begin
      [*] = ;               if (gInterface.buttons.bsquadfill) then
      [*] = ;               begin
      [*] = ;                  var pSquad : Pointer = _player_GetFirstSelectedSquad(plInd);
      [*] = ;                  if (pSquad<>nil) then
      [*] = ;                  begin
      [*] = ;                     _player_FillSquad(plHnd, TSquad(pSquad).fIndex, true, true);
      [*] = ;                     _control_SelectOnlySquad(pSquad);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            'disband' : begin
      [*] = ;               if (bProcess) and (not ((gScenario.bactive) and (gScenario.campname='tutcam') and (gScenario.missname='tutmis2'))) then
      [*] = ;               if (gInterface.buttons.bsquaddisband) then
      [*] = ;               begin
      [*] = ;                  var pSquad : Pointer = _player_GetFirstSelectedSquad(plInd);
      [*] = ;                  if (pSquad<>nil) then
      [*] = ;                  begin
      [*] = ;                     gIntegerList.Clear;
      [*] = ;                     var i : Integer;
      [*] = ;                     for i:=0 to TSquad(pSquad).GetCount-1 do
      [*] = ;                     begin
      [*] = ;                        var goHnd : Integer = TSquad(pSquad).Get(i);
      [*] = ;                        gIntegerList.Add(goHnd);
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     _misc_DisbandSquad(plHnd, TSquad(pSquad).fIndex, true);
      [*] = ;                     _misc_AddUnitsToSelection(gIntegerList);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            'groupunits' : begin
      [*] = ;               if (gProfile.bdevmode) then
      [*] = ;               _player_WriteSquadNew(GetPlayerHandleInterfaceIO, -1, 0, 0, gSelectedObjects, False, False);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      'interface' : begin
      [*] = ;         case action of
      [*] = ;            'minimap' : begin // 'Alt+M'
      [*] = ;               _misc_SetMinimapVisible(not GetGUIMiniMapVisible);
      [*] = ;            end;
      [*] = ;            'viewcollision' : begin
      [*] = ;               var bEnable : Boolean = not EditorGetWorldViewerCollisionVisible;
      [*] = ;               EditorSetWorldViewerCollisionVisible(bEnable);
      [*] = ;               EditorSetWorldViewerCollisionColor(0.5, 0.5, 0.5, 1);
      [*] = ;               EditorSetWorldViewerVisible(bEnable);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      'select' : begin
      [*] = ;         case action of
      [*] = ;            'allunits' : begin
      [*] = ;               _control_SelectAllUnits(False, False);
      [*] = ;               _gui_UpdateHighlights(False);
      [*] = ;            end;
      [*] = ;            'militaryunits' : begin
      [*] = ;               _control_SelectAllUnits(False, True);
      [*] = ;               _gui_UpdateHighlights(False);
      [*] = ;            end;
      [*] = ;            'allbuildings' : begin
      [*] = ;               _control_SelectAllUnits(True, False);
      [*] = ;               _gui_UpdateHighlights(False);
      [*] = ;            end;
      [*] = ;            'idlepeasants' : begin
      [*] = ;               gbool_gui_requestsoundonunitcontrol := True;
      [*] = ;               if (not bDouble) then
      [*] = ;               _control_SelectIdlePeasants
      [*] = ;               else
      [*] = ;               _control_MoveCameraToUnitsListCenter(gSelectedObjects);
      [*] = ;               _gui_UpdateHighlights(False);
      [*] = ;            end;
      [*] = ;            'allpeasants' : begin
      [*] = ;               gbool_gui_requestsoundonunitcontrol := True;
      [*] = ;               _control_SelectAllPeasants();
      [*] = ;               _gui_UpdateHighlights(False);
      [*] = ;            end;
      [*] = ;            'idlemines' : begin
      [*] = ;               if (not bDouble) then
      [*] = ;               _control_SelectIdleMines
      [*] = ;               else
      [*] = ;               _control_MoveCameraToUnitsListCenter(gSelectedObjects);
      [*] = ;               _gui_UpdateHighlights(False);
      [*] = ;            end;
      [*] = ;            'allships' : begin
      [*] = ;               _control_SelectAllShips;
      [*] = ;               _gui_UpdateHighlights(False);
      [*] = ;            end;
      [*] = ;            'unitsofsametype', 'allunitsofsametype', 'addunitsofsametype', 'addallunitsofsametype' : begin
      [*] = ;               gIntegerList.Clear;
      [*] = ;               var bCtrl : Boolean = (action='allunitsofsametype') or (action='addallunitsofsametype');
      [*] = ;               var bShift : Boolean = (action='addunitsofsametype') or (action='addallunitsofsametype');
      [*] = ;               var squadSel : Boolean;
      [*] = ;               var goHnd : Integer;
      [*] = ;               var i : Integer;
      [*] = ;               if (gProfile.bselectallunitsonz) then
      [*] = ;               begin
      [*] = ;                  for i:=gPlayer[plInd].squads.GetCount-1 downto 0 do
      [*] = ;                  begin
      [*] = ;                     var psquad : Pointer = TSquad(gPlayer[plInd].squads.Get(i));
      [*] = ;                     if (psquad<>nil) then
      [*] = ;                     begin
      [*] = ;                        if (TSquad(psquad).fSelected) then
      [*] = ;                        begin
      [*] = ;                           goHnd := _unit_GetSquadUnit(psquad);
      [*] = ;                           if goHnd<>0 then
      [*] = ;                           begin
      [*] = ;                              var pobj : Pointer = _unit_GetTObj(goHnd);
      [*] = ;                              var tag : Integer = TObj(pobj).cid*gc_country_maxmembers+TObj(pobj).id;
      [*] = ;                              if (gIntegerList.IndexOf(tag)<0) then
      [*] = ;                              gIntegerList.Add(tag);
      [*] = ;                              squadSel := True;
      [*] = ;                              //break;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     ErrorLog('OnShortcut : psquad=nil - 2');
      [*] = ;                  end;
      [*] = ;                  for i:=0 to gSelectedObjects.GetCount-1 do
      [*] = ;                  begin
      [*] = ;                     var goHnd : Integer = gSelectedObjects.Get(i);
      [*] = ;                     var pobj : Pointer = _unit_GetTObj(goHnd);
      [*] = ;                     if (pobj<>nil) then
      [*] = ;                     begin
      [*] = ;                        var tag : Integer = TObj(pobj).cid*gc_country_maxmembers+TObj(pobj).id;
      [*] = ;                        if (gIntegerList.IndexOf(tag)<0) then
      [*] = ;                        gIntegerList.Add(tag);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  if (not bShift) then
      [*] = ;                  _control_DeselectAllUnits(gIntegerList.GetCount=0);
      [*] = ;                  for i:=0 to gIntegerList.GetCount-1 do
      [*] = ;                  begin
      [*] = ;                     var tag : Integer = gIntegerList.Get(i);
      [*] = ;                     var cid : Integer = tag div gc_country_maxmembers;
      [*] = ;                     var id : Integer = tag mod gc_country_maxmembers;
      [*] = ;                     _misc_SelectAllUnitsOfType(cid, id, True, bCtrl, {bShift}True, squadSel);
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  for i:=gPlayer[plInd].squads.GetCount-1 downto 0 do
      [*] = ;                  begin
      [*] = ;                     var psquad : Pointer = TSquad(gPlayer[plInd].squads.Get(i));
      [*] = ;                     if (psquad<>nil) then
      [*] = ;                     begin
      [*] = ;                        if (TSquad(psquad).fSelected) then
      [*] = ;                        begin
      [*] = ;                           goHnd := _unit_GetSquadUnit(psquad);
      [*] = ;                           if (goHnd<>0) then
      [*] = ;                           begin
      [*] = ;                              squadSel := True;
      [*] = ;                              break;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     ErrorLog('OnShortcut : psquad=nil - 2');
      [*] = ;                  end;
      [*] = ;                  if (goHnd=0) then
      [*] = ;                  if (gSelectedObjects.GetCount>0) then
      [*] = ;                  begin
      [*] = ;                     goHnd := gSelectedObjects.Get(0);
      [*] = ;                     if (not bShift) then
      [*] = ;                     _control_DeselectAllUnits(goHnd=0);
      [*] = ;                  end;
      [*] = ;                  if (goHnd<>0) then
      [*] = ;                  begin
      [*] = ;                     var squadSel : Boolean = _unit_IsSelectSquad(goHnd);
      [*] = ;                     var goHnd1 : Integer = _unit_GetUnitForSelectionByType(goHnd);
      [*] = ;                     var pobj : Pointer = _unit_GetTObj(goHnd1);
      [*] = ;                     if (pobj<>nil) then
      [*] = ;                     _misc_SelectAllUnitsOfType(TObj(pObj).cid, TObj(pObj).id, True, bCtrl, bShift, squadSel);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               _gui_UpdateHighlights(True);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      'upgrade' : begin
      [*] = ;         if (bProcess) and (gInterface.control.bshowupgrade) then
      [*] = ;         begin
      [*] = ;            var goHnd : Integer = GetGameObjectHandleByUniqueId(gint_gui_unitcontroluid);
      [*] = ;            if (goHnd<>0) and (_unit_GetUsage(goHnd)=gc_obj_usage_mine) then
      [*] = ;            begin
      [*] = ;               var pobj : Pointer = _unit_GetTObj(goHnd);
      [*] = ;               if (pobj<>nil) then
      [*] = ;               begin
      [*] = ;                  // check if individual upgrade is available in this building and order available one
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;case name of
      [*] = ;   '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' : begin
      [*] = ;      var num : Integer = StrToInt(name);
      [*] = ;      var pobj : Pointer;
      [*] = ;      var goHnd, squad : Integer;
      [*] = ;      var i, j : Integer;
      [*] = ;      _control_DeselectAllUnits(False);
      [*] = ;      for i:=gCtrlGroups[plInd][num].GetCount-1 downto 0 do
      [*] = ;      begin
      [*] = ;         goHnd := gCtrlGroups[plInd][num].Get(i);
      [*] = ;         pobj := _unit_GetTObj(goHnd);
      [*] = ;         if (pobj<>nil) then
      [*] = ;         begin
      [*] = ;            squad := TObj(pobj).squad;
      [*] = ;            if (squad>-1) then
      [*] = ;            begin
      [*] = ;               var psquad : Pointer = gPlayer[plInd].squads.Get(squad);
      [*] = ;               if (psquad<>nil) then
      [*] = ;               begin
      [*] = ;                  TSquad(psquad).fSelected := True;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               gSelectedObjects.Add(goHnd);
      [*] = ;               SetGameObjectPickedByHandle(goHnd, True);
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         gCtrlGroups[plInd][num].Delete(i);
      [*] = ;      end;
      [*] = ;      _misc_SetUnitsToSelection(plInd, gCtrlGroups[plInd][num]);
      [*] = ;
      [*] = ;      if (bDouble) then
      [*] = ;      _control_MoveCameraToUnitsListCenter(gCtrlGroups[plInd][num]);
      [*] = ;
      [*] = ;      _gui_ForceShowUnitControl(True);
      [*] = ;   end;
      [*] = ;   'Ctrl+1', 'Ctrl+2', 'Ctrl+3', 'Ctrl+4', 'Ctrl+5', 'Ctrl+6', 'Ctrl+7', 'Ctrl+8', 'Ctrl+9', 'Ctrl+0' : begin
      [*] = ;      var sub : String = SubStr(name, 6, 1);
      [*] = ;      var num : Integer = StrToInt(sub);
      [*] = ;      var goHnd : Integer;
      [*] = ;      var pobj : Pointer;
      [*] = ;
      [*] = ;      var mask : Integer = 1 shl num;
      [*] = ;
      [*] = ;      var i, j : Integer;
      [*] = ;      for i:=gCtrlGroups[plInd][num].GetCount-1 downto 0 do
      [*] = ;      begin
      [*] = ;         goHnd := gCtrlGroups[plInd][num].Get(i);
      [*] = ;         pobj := _unit_GetTObj(goHnd);
      [*] = ;         if (pobj<>nil) then
      [*] = ;         TObj(pobj).ctrlgroupmask := TObj(pobj).ctrlgroupmask xor mask;
      [*] = ;      end;
      [*] = ;      gCtrlGroups[plInd][num].Clear;
      [*] = ;      for i:=gPlayer[plInd].squads.GetCount-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var psquad : Pointer = TSquad(gPlayer[plInd].squads.Get(i));
      [*] = ;         if (psquad<>nil) then
      [*] = ;         begin
      [*] = ;            if (TSquad(psquad).fSelected) then
      [*] = ;            begin
      [*] = ;               for j:=TSquad(psquad).GetCount-1 downto 0 do
      [*] = ;               begin
      [*] = ;                  goHnd := TSquad(psquad).Get(j);
      [*] = ;                  pobj := _unit_GetTObj(goHnd);
      [*] = ;                  if (pobj<>nil) then
      [*] = ;                  begin
      [*] = ;                     TObj(pobj).ctrlgroupmask := TObj(pobj).ctrlgroupmask or mask;
      [*] = ;                     gCtrlGroups[plInd][num].Add(goHnd);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if (gSelectedObjects.GetCount>0) then
      [*] = ;      begin
      [*] = ;         for i:=gSelectedObjects.GetCount-1 downto 0 do
      [*] = ;         begin
      [*] = ;            goHnd := gSelectedObjects.Get(i);
      [*] = ;            pobj := _unit_GetTObj(goHnd);
      [*] = ;            if (pobj<>nil) then
      [*] = ;            begin
      [*] = ;               TObj(pobj).ctrlgroupmask := TObj(pobj).ctrlgroupmask or mask;
      [*] = ;               gCtrlGroups[plInd][num].Add(goHnd);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //log(IntToStr(gCtrlGroups[plInd][num].GetCount));
      [*] = ;   end;
      [*] = ;   'Shift+1', 'Shift+2', 'Shift+3', 'Shift+4', 'Shift+5', 'Shift+6', 'Shift+7', 'Shift+8', 'Shift+9', 'Shift+0' : begin
      [*] = ;      var sub : String = SubStr(name, 7, 1);
      [*] = ;      var num : Integer = StrToInt(sub);
      [*] = ;      var goHnd : Integer;
      [*] = ;      var pobj : Pointer;
      [*] = ;
      [*] = ;      var mask : Integer = 1 shl num;
      [*] = ;
      [*] = ;      var i, j : Integer;
      [*] = ;      for i:=gPlayer[plInd].squads.GetCount-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var psquad : Pointer = TSquad(gPlayer[plInd].squads.Get(i));
      [*] = ;         if (psquad<>nil) then
      [*] = ;         begin
      [*] = ;            if (TSquad(psquad).fSelected) then
      [*] = ;            begin
      [*] = ;               for j:=TSquad(psquad).GetCount-1 downto 0 do
      [*] = ;               begin
      [*] = ;                  goHnd := TSquad(psquad).Get(j);
      [*] = ;                  pobj := _unit_GetTObj(goHnd);
      [*] = ;                  if (pobj<>nil) then
      [*] = ;                  begin
      [*] = ;                     if (TObj(pobj).ctrlgroupmask and mask)=0 then // should be same as IndexOf=-1
      [*] = ;                     begin
      [*] = ;                        TObj(pobj).ctrlgroupmask := TObj(pobj).ctrlgroupmask or mask;
      [*] = ;                        gCtrlGroups[plInd][num].Add(goHnd);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if (gSelectedObjects.GetCount>0) then
      [*] = ;      begin
      [*] = ;         for i:=gSelectedObjects.GetCount-1 downto 0 do
      [*] = ;         begin
      [*] = ;            goHnd := gSelectedObjects.Get(i);
      [*] = ;            pobj := _unit_GetTObj(goHnd);
      [*] = ;            if (pobj<>nil) then
      [*] = ;            begin
      [*] = ;               if (TObj(pobj).ctrlgroupmask and mask)=0 then // should be same as IndexOf=-1
      [*] = ;               begin
      [*] = ;                  TObj(pobj).ctrlgroupmask := TObj(pobj).ctrlgroupmask or mask;
      [*] = ;                  gCtrlGroups[plInd][num].Add(goHnd);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //log(IntToStr(gCtrlGroups[plInd][num].GetCount));
      [*] = ;   end;
      [*] = ;   {'S', 'V', 'D', 'E', 'G'{, 'P'}{ : begin
      [*] = ;      var i, j : Integer;
      [*] = ;      for i := gSelectedObjects.GetCount-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var goHnd : Integer = gSelectedObjects.Get(i);
      [*] = ;         if not _unit_IsBuilding(goHnd) then
      [*] = ;         UnitSetupFlag(goHnd, name);
      [*] = ;      end;
      [*] = ;
      [*] = ;      for i := gPlayer[plInd].squads.GetCount-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pSquad : Pointer = gPlayer[plInd].squads.Get(i);
      [*] = ;         if (TSquad(pSquad).fSelected) then
      [*] = ;         begin
      [*] = ;            SquadSetupFlag(pSquad, name);
      [*] = ;            for j := TSquad(pSquad).GetCount-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var goHnd : Integer = TSquad(pSquad).Get(j);
      [*] = ;               UnitSetupFlag(goHnd, name);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;}
      [*] = ;   {'M' : begin
      [*] = ;      var bVisible : Boolean = (not GetGUIMiniMapVisible);
      [*] = ;      SetGUIMiniMapVisible(bVisible);
      [*] = ;      var minimapHnd : Integer = GetGUIElementIndexByNameParent('minimap', _gui_GetTop)
      [*] = ;      if (minimapHnd<>0) then
      [*] = ;      SetGUIElementVisible(minimapHnd, bVisible);
      [*] = ;   end;}
      [*] = ;   'Space', 'SpaceD', 'F9' : begin
      [*] = ;      if (gint_editor_selectedunitid>0) then
      [*] = ;      begin
      [*] = ;         gbool_editor_placeunits := True;
      [*] = ;         gstring_editor_selectedunitsid := '';
      [*] = ;         gint_editor_selectedunitid := 0;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (name='SpaceD') then
      [*] = ;      _control_MoveCameraToSelectedUnits;
      [*] = ;   end;
      [*] = ;   'F5' : begin
      [*] = ;      if ((_net_IsOffline) or (LanGetClientsCount<=1)) and (not gbool_gui_querywindow) and (gPlayer[plind].victorystate=gc_player_victorystate_none) then
      [*] = ;      begin
      [*] = ;         gbool_gui_quicksave := True;
      [*] = ;         ExecuteState('DoAutoSave');
      [*] = ;         gbool_gui_quicksave := False;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'P' : begin
      [*] = ;      if (gProfile.bCheatPlaceUnits) or (gInterface.gamemode=gc_gamemode_editor) then
      [*] = ;      begin
      [*] = ;         gbool_editor_placeunits := True;
      [*] = ;         gbool_editor_placeunitsmaximized := not gbool_editor_placeunitsmaximized;
      [*] = ;         gstring_editor_selectedunitsid := '';
      [*] = ;         gint_editor_selectedunitid := 0;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'Escape' : begin
      [*] = ;      if GetProgressingPauseMode and (not gbool_gui_goinattackmode) and (not gbool_gui_attackpointmode) and (not gbool_gui_guardmode) and (gint_editor_selectedunitid=0) and (gint_gui_pickedbldhnd=0) and (not gbool_gui_querywindow) then
      [*] = ;      if ((_net_IsOffline) or (LanGetClientsCount<=1)) or (gMap.gamestage>=gc_map_gamestage_started) then
      [*] = ;      ExecuteState('WritePause');
      [*] = ;
      [*] = ;      gbool_gui_goinattackmode := False;
      [*] = ;      gbool_gui_attackpointmode := False;
      [*] = ;      gbool_gui_guardmode := False;
      [*] = ;      gbool_gui_update_cursor := True;
      [*] = ;      if (gint_editor_selectedunitid>0) then
      [*] = ;      begin
      [*] = ;         gbool_editor_placeunits := True;
      [*] = ;         gstring_editor_selectedunitsid := '';
      [*] = ;         gint_editor_selectedunitid := 0;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (gint_gui_pickedbldhnd<>0) then
      [*] = ;      _misc_GUICancelBuilding(True, False);
      [*] = ;   end;
      [*] = ;   'Return', 'Ctrl+Return' : begin
      [*] = ;      if (_net_IsOnline) and (gMap.gamestage>=gc_map_gamestage_started) and (name='Ctrl+Return') then
      [*] = ;      gint_gui_chatmessagemode := gc_chatmessage_mode_ally
      [*] = ;      else
      [*] = ;      gint_gui_chatmessagemode := gc_chatmessage_mode_all;
      [*] = ;      const cElmName = 'chatconsole';
      [*] = ;      var elmParent : Integer = GetGUIElementIndexByNameParent(cElmName, _gui_GetTop);
      [*] = ;      if (elmParent=0) or (not GetGUIElementVisible(elmParent)) then
      [*] = ;      _gui_SendTagToState('EventChatConsole', gc_gui_event_tagShow)
      [*] = ;      else
      [*] = ;      _gui_SendTagToState('EventChatConsole', gc_gui_event_tagClose);
      [*] = ;   end;
      [*] = ;   'PrintScreen0' : CreateSnapShot(True);
      [*] = ;   'PrintScreen1', 'PrintScreen2' : CreateSnapShot(False);
      [*] = ;   'Ctrl+Shift+M' : begin
      [*] = ;      if (EditorGetCaptureMode=0) then
      [*] = ;      EditorStartCapture
      [*] = ;      else
      [*] = ;      EditorStopCapture;
      [*] = ;   end;
      [*] = ;   'F10' : begin
      [*] = ;      gbool_gui_goinattackmode := False;
      [*] = ;      gbool_gui_attackpointmode := False;
      [*] = ;      gbool_gui_guardmode := False;
      [*] = ;      gbool_gui_update_cursor := True;
      [*] = ;      if (gint_editor_selectedunitid>0) then
      [*] = ;      begin
      [*] = ;         gbool_editor_placeunits := True;
      [*] = ;         gstring_editor_selectedunitsid := '';
      [*] = ;         gint_editor_selectedunitid := 0;
      [*] = ;      end;
      [*] = ;      if (gint_gui_pickedbldhnd<>0) then
      [*] = ;      _misc_GUICancelBuilding(True, True);
      [*] = ;      const cElmName = 'menu';
      [*] = ;      var elmParent : Integer = GetGUIElementIndexByNameParent(cElmName, _gui_GetTop);
      [*] = ;      if (elmParent=0) or (not GetGUIElementVisible(elmParent)) then begin
      [*] = ;         if (not gbool_gui_querywindow) then
      [*] = ;         _gui_SendTagToState('EventMenu', gc_gui_event_tagShow);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      _gui_SendTagToState('EventMenu', gc_gui_event_tagClose);
      [*] = ;      gbool_gui_update_cursor := True;
      [*] = ;   end;
      [*] = ;   'F11' : begin
      [*] = ;      gScenario.bexists := gScenario.triggers[0].bexists;
      [*] = ;      gScenario.ui.bshowui := True;
      [*] = ;
      [*] = ;      var i : Integer;
      [*] = ;      for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;      gScenario.players[i].bai := gPlayer[i].bai;
      [*] = ;      {const cElmName = 'scenarioeditor';
      [*] = ;      var elmParent : Integer = GetGUIElementIndexByNameParent(cElmName, _gui_GetTop);
      [*] = ;      if (elmParent=0) or (not GetGUIElementVisible(elmParent)) then
      [*] = ;      begin}
      [*] = ;         _gui_SendTagToState('EventScenarioUI', gc_gui_event_tagShow);
      [*] = ;         _gui_SendTagToState('EventScenarioEditor', gc_gui_event_tagShow);
      [*] = ;      {end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         _gui_SendTagToState('EventScenarioUI', gc_gui_event_tagHide);
      [*] = ;         _gui_SendTagToState('EventScenarioEditor', gc_gui_event_tagHide);
      [*] = ;      end;}
      [*] = ;   end;
      [*] = ;   //'A' : begin
      [*] = ;      //   gbool_gui_goinattackmode := True;
      [*] = ;      //   gbool_gui_update_cursor := True;
      [*] = ;   //end;
      [*] = ;   'Pause', 'Ctrl+Shift+P' : begin
      [*] = ;      // pause
      [*] = ;      if ((_net_IsOffline) or (LanGetClientsCount<=1)) or (gMap.gamestage>=gc_map_gamestage_started) then
      [*] = ;      begin
      [*] = ;         if (not gbool_gui_querywindow) then
      [*] = ;         begin
      [*] = ;            if (_net_IsOffline) then
      [*] = ;            ExecuteState('WritePause')
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (GetProgressingPauseMode) then
      [*] = ;               ExecuteState('WritePause')
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if (_misc_GetRealTime-gfloat_time_pause>gc_pause_timelimit) then
      [*] = ;                  begin
      [*] = ;                     gfloat_time_pause := _misc_GetRealTime;
      [*] = ;                     gint_count_pause := 1;
      [*] = ;                     ExecuteState('WritePause');
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  if (gint_count_pause<gc_pause_countlimit) then
      [*] = ;                  begin
      [*] = ;                     gfloat_time_pause := _misc_GetRealTime;
      [*] = ;                     gint_count_pause := gint_count_pause+1;
      [*] = ;                     ExecuteState('WritePause');
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     var s1 : String = GetLocaleTableListItemByID('gui', 'pause.limit');
      [*] = ;                     var s2 : String = FloatToStr(Round(gc_pause_timelimit-(_misc_GetRealTime-gfloat_time_pause)));
      [*] = ;                     s1 := StrReplace(s1, '%value%', s2);
      [*] = ;                     s2 := '';
      [*] = ;                     _misc_ShowLogMessage(gc_logmessagesid_custom, s1, s2, False);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'Home', 'Ctrl+Home' : begin
      [*] = ;      // Set camera to default height and angle
      [*] = ;      if (not gbool_gui_screenshotcamera) then
      [*] = ;      begin
      [*] = ;         var time : Float;
      [*] = ;         if (bCtrl) then
      [*] = ;         time := 0
      [*] = ;         else
      [*] = ;         time := 1500;
      [*] = ;         _control_MoveCameraToPosition(gMap.players[plind].startx, gMap.players[plind].starty, time, (bCtrl));
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         gfloat_gui_screenshotcamerafov := 0;
      [*] = ;         var focal : Float = 400+gfloat_gui_screenshotcamerafov*5;
      [*] = ;         SetCameraFocalLengthInfo(focal, focal, 0.5);
      [*] = ;         log('focal='+FloatToStr(focal));
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   '[', 'Ctrl+Sub' : begin
      [*] = ;      if ((_net_IsOffline) or (LanGetClientsCount<=1)) or (gMap.gamestage>=gc_map_gamestage_started) then
      [*] = ;      if (gProfile.bCheatNoSpeedLimit) or (gInterface.gamemode=gc_gamemode_editor) then
      [*] = ;      begin
      [*] = ;         // decrease game speed debug mode
      [*] = ;         //var speed : Float = GetTimeSpeedFactor/2;
      [*] = ;         //SetTimeSpeedFactor(speed);
      [*] = ;         FloatRegister0 := GetTimeSpeedFactor/2;
      [*] = ;         if (not gProfile.bdevmode) then
      [*] = ;         FloatRegister0 := Clamp(FloatRegister0, 0, 100);
      [*] = ;         IntRegister0 := gProfile.igamespeed;
      [*] = ;         ExecuteState('WriteTimeSpeed');
      [*] = ;         log('gProfile.igamespeed='+IntToStr(gProfile.igamespeed)+' TimeSpeedFactor='+FloatToStr(GetTimeSpeedFactor));
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   ']', 'Ctrl+Add' : begin
      [*] = ;      if ((_net_IsOffline) or (LanGetClientsCount<=1)) or (gMap.gamestage>=gc_map_gamestage_started) then
      [*] = ;      if (gProfile.bCheatNoSpeedLimit) or (gInterface.gamemode=gc_gamemode_editor) then
      [*] = ;      begin
      [*] = ;         // increase game speed debug mode
      [*] = ;         //var speed : Float = GetTimeSpeedFactor*2;
      [*] = ;         //SetTimeSpeedFactor(speed);
      [*] = ;         FloatRegister0 := GetTimeSpeedFactor*2;
      [*] = ;         if (not gProfile.bdevmode) then
      [*] = ;         FloatRegister0 := Clamp(FloatRegister0, 0, 100);
      [*] = ;         IntRegister0 := gProfile.igamespeed;
      [*] = ;         ExecuteState('WriteTimeSpeed');
      [*] = ;         log('gProfile.igamespeed='+IntToStr(gProfile.igamespeed)+' TimeSpeedFactor='+FloatToStr(GetTimeSpeedFactor));
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'Sub', '-' : begin
      [*] = ;      // decrease game speed
      [*] = ;      if (not gbool_gui_querywindow) then
      [*] = ;      if ((_net_IsOffline) or (LanGetClientsCount<=1) or ((_net_IsOnline) and (gMap.settings.additional.gamespeed<0) and (gMap.gamestage>=gc_map_gamestage_started)))  then
      [*] = ;      begin
      [*] = ;         if (gProfile.igamespeed=0) then
      [*] = ;         begin
      [*] = ;            if (not GetProgressingPauseMode) then
      [*] = ;            begin
      [*] = ;               SetValueByName('Name', 'Pause');
      [*] = ;               ExecuteState('OnShortcut');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         gProfile.igamespeed := _misc_ClampInt(gProfile.igamespeed-1, 0, gc_settings_gamespeed_count-1);
      [*] = ;         _control_SetGameSpeedByMode(gProfile.igamespeed, True);
      [*] = ;         log('gProfile.igamespeed='+IntToStr(gProfile.igamespeed)+' TimeSpeedFactor='+FloatToStr(GetTimeSpeedFactor));
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'Add', '=' : begin
      [*] = ;      // increase game speed
      [*] = ;      if (not gbool_gui_querywindow) then
      [*] = ;      if (((_net_IsOffline) or (LanGetClientsCount<=1)) or ((_net_IsOnline) and (gMap.settings.additional.gamespeed<0) and (gMap.gamestage>=gc_map_gamestage_started)))  then
      [*] = ;      begin
      [*] = ;         if (gProfile.igamespeed=0) and (GetProgressingPauseMode) then
      [*] = ;         begin
      [*] = ;            SetValueByName('Name', 'Pause');
      [*] = ;            ExecuteState('OnShortcut');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            gProfile.igamespeed := _misc_ClampInt(gProfile.igamespeed+1, 0, gc_settings_gamespeed_count-1);
      [*] = ;            _control_SetGameSpeedByMode(gProfile.igamespeed, True);
      [*] = ;            log('gProfile.igamespeed='+IntToStr(gProfile.igamespeed)+' TimeSpeedFactor='+FloatToStr(GetTimeSpeedFactor));
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'Ctrl+PGUP' : begin
      [*] = ;      gfloat_gui_screenshotcamerafov := gfloat_gui_screenshotcamerafov+1;
      [*] = ;      var focal : Float = 400+gfloat_gui_screenshotcamerafov*5;
      [*] = ;      SetCameraFocalLengthInfo(focal, focal, 0.5);
      [*] = ;      log('focal='+FloatToStr(focal));
      [*] = ;   end;
      [*] = ;   'Ctrl+PGDN' : begin
      [*] = ;      gfloat_gui_screenshotcamerafov := gfloat_gui_screenshotcamerafov-1;
      [*] = ;      var focal : Float = 400+gfloat_gui_screenshotcamerafov*5;
      [*] = ;      SetCameraFocalLengthInfo(focal, focal, 0.5);
      [*] = ;      log('focal='+FloatToStr(focal));
      [*] = ;   end;
      [*] = ;   'PGUP' : begin
      [*] = ;      var dist : Float = GetCameraElasticDistance;
      [*] = ;      var step : Float;
      [*] = ;      if (gbool_gui_screenshotcamera) then
      [*] = ;      step := 0.25
      [*] = ;      else
      [*] = ;      step := 5;
      [*] = ;      SetCameraElasticDistance(dist+step);
      [*] = ;   end;
      [*] = ;   'PGDN' : begin
      [*] = ;      var dist : Float = GetCameraElasticDistance;
      [*] = ;      var step : Float;
      [*] = ;      if (gbool_gui_screenshotcamera) then
      [*] = ;      step := 0.25
      [*] = ;      else
      [*] = ;      step := 5;
      [*] = ;      SetCameraElasticDistance(dist-step);
      [*] = ;   end;
      [*] = ;   'Del', 'Ctrl+Del' : begin
      [*] = ;      if (bProcess) and (not ((gScenario.bactive) and (gScenario.campname='tutcam'))) then
      [*] = ;      begin
      [*] = ;         gDeathUnits.Clear;
      [*] = ;         var mode : Integer;
      [*] = ;         if (name='Ctrl+Del') then
      [*] = ;         mode := 1;
      [*] = ;         var j : Integer;
      [*] = ;         for j:=GetPlayerGameObjectsCountByHandle(plHnd)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var goHnd : Integer = GetGameObjectHandleByIndex(j, plHnd);
      [*] = ;            if (GetGameObjectPickedByHandle(goHnd)) and (_unit_IsBuilding(goHnd) or ((GetGameObjectStatesTagByHandle(goHnd) and gc_statetag_essential_none)<>0)) then
      [*] = ;            gDeathUnits.Add(goHnd);
      [*] = ;         end;
      [*] = ;         if (gDeathUnits.GetCount>0) then
      [*] = ;         begin
      [*] = ;            var randkey : Integer = GetRandomKey;
      [*] = ;            var goHnd : Integer = gDeathUnits.Get(0);
      [*] = ;            var phnd: Integer = GetGameObjectPlayerHandleByHandle(goHnd);
      [*] = ;            var parg: Pointer = StateMachineGetArgDataByInd(GetPlayerStateMachineHandle(phnd), gc_argplayer_plr);
      [*] = ;            if parg<>nil then
      [*] = ;            begin
      [*] = ;               TPlayerArgs(parg).fmode:=mode;
      [*] = ;               TPlayerArgs(parg).frnd:=randkey;
      [*] = ;               TPlayerArgs(parg).fintlst:=gDeathUnits;
      [*] = ;               PlayerExecuteStateByHandle(phnd, 'WriteDeath');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            _net_ErrorLog('invalid pointer, parg=nil');
      [*] = ;            SetRandomKey(floor(Abs(randkey)));
      [*] = ;            GUIExecuteState('DoUpdateSelection');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'NUM0', 'NUM1', 'NUM2', 'NUM3', 'NUM4', 'NUM5', 'NUM6', 'NUM7', 'NUM8', 'NUM9', 'Mul', 'Shift+Alt+I' : begin
      [*] = ;      if (gbool_gui_bspectator) or (gProfile.bCheatSwitchPlayer) or (gInterface.gamemode=gc_gamemode_editor) or (_net_IsReplay) then
      [*] = ;      begin
      [*] = ;         var num : Integer;
      [*] = ;         if (name='Mul') then
      [*] = ;         num := gc_MaxPlayerCount-1
      [*] = ;         else
      [*] = ;         num := StrToInt(SubStr(name, 4, 1));
      [*] = ;         var plInd : Integer;
      [*] = ;         if (num=0) then
      [*] = ;         plInd := 10-1
      [*] = ;         else
      [*] = ;         plInd := num-1;
      [*] = ;         var bPrimitives : Boolean = (GetGUIMiniMapPrimitivesCount>0); // should be above SetPlayer, cause after SetPlayer primitive count = 0
      [*] = ;         _control_SetPlayer(plInd);
      [*] = ;         if (bPrimitives) then
      [*] = ;         _misc_UpdateMiniMapPrimitives(False);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'Alt+1', 'Alt+2', 'Alt+3', 'Alt+4', 'Alt+5', 'Alt+6', 'Alt+7', 'Alt+8'
      [*] = ;   ,'Shift+Alt+1', 'Shift+Alt+2', 'Shift+Alt+3', 'Shift+Alt+4', 'Shift+Alt+5', 'Shift+Alt+6', 'Shift+Alt+7', 'Shift+Alt+8' : begin
      [*] = ;      if (gbool_gui_bspectator) or (gProfile.bCheatSwitchPlayer) or (gInterface.gamemode=gc_gamemode_editor) or (_net_IsReplay) then
      [*] = ;      begin
      [*] = ;         var plInd : Integer;
      [*] = ;         if StrExists(name, 'Shift') then
      [*] = ;         plInd := StrToInt(SubStr(name, 11, 1))
      [*] = ;         else
      [*] = ;         plInd := StrToInt(SubStr(name, 5, 1));
      [*] = ;         var bPrimitives : Boolean = (GetGUIMiniMapPrimitivesCount>0); // should be above SetPlayer, cause after SetPlayer primitive count = 0
      [*] = ;         _control_SetPlayer(plInd-1);
      [*] = ;         if (bPrimitives) then
      [*] = ;         _misc_UpdateMiniMapPrimitives(False);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   // editor shortcuts start
      [*] = ;   'Ctrl+W' : begin // peace mode
      [*] = ;      if (gProfile.bCheatPeaceMode) or (gInterface.gamemode=gc_gamemode_editor) then
      [*] = ;      begin
      [*] = ;         ExecuteState('WritePeacemode');
      [*] = ;
      [*] = ;         if gbool_editor_peacemode then
      [*] = ;         Log('Peace mode on')
      [*] = ;         else
      [*] = ;         Log('Peace mode off');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'Ctrl+F' : begin // fog of war
      [*] = ;      if (gbool_gui_bspectator) or (gProfile.bCheatNoFogOfWar) or (gInterface.gamemode=gc_gamemode_editor) then
      [*] = ;      begin
      [*] = ;         gbool_editor_fogofwar := not gbool_editor_fogofwar;
      [*] = ;         gbool_gui_update_editorinfo := True;
      [*] = ;         _player_UpdateFOW(plInd);
      [*] = ;         if gbool_editor_fogofwar then
      [*] = ;         Log('Fog of war on')
      [*] = ;         else
      [*] = ;         Log('Fog of war off');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   //'Ctrl+S' : begin // stop units
      [*] = ;      //   _player_StopSelectedUnits(plInd, gSelectedObjects);
      [*] = ;   //end;
      [*] = ;   'Ctrl' : begin
      [*] = ;      //if (bProcess) then
      [*] = ;      //gbool_gui_goinattackmode := True;
      [*] = ;   end;
      [*] = ;   'CtrlUp' : begin
      [*] = ;      //if (bProcess) then
      [*] = ;      //gbool_gui_goinattackmode := False;
      [*] = ;   end;
      [*] = ;   'Alt' : begin
      [*] = ;   end;
      [*] = ;   'AltUp' : begin
      [*] = ;   end;
      [*] = ;   'Shift' : begin
      [*] = ;   end;
      [*] = ;   'ShiftUp' : begin
      [*] = ;      if (gbool_gui_shifticonsselection) then
      [*] = ;      begin
      [*] = ;         var cid, id : Integer;
      [*] = ;         _misc_GetUnitsFromSelection(plInd, gIntegerList);
      [*] = ;         _misc_SetSquadsSelection(plInd, False);
      [*] = ;         var i : Integer;
      [*] = ;         for i:=gIntegerList.GetCount-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var goHnd : Integer = gIntegerList.Get(i);
      [*] = ;            var pobj : Pointer = _unit_GetTObj(goHnd);
      [*] = ;            if (pobj<>nil) then
      [*] = ;            begin
      [*] = ;               var squad : Integer = TObj(pobj).squad;
      [*] = ;
      [*] = ;               if (squad<0) and (not gSelection[TObj(pobj).cid][TObj(pobj).id].bshiftsel) then
      [*] = ;               gIntegerList.Delete(i)
      [*] = ;               else
      [*] = ;               if (squad>=0) then
      [*] = ;               begin
      [*] = ;                  if (gSelectionSquads[squad].bshiftsel) then
      [*] = ;                  begin
      [*] = ;                     var psquad : Pointer = gPlayer[TObj(pobj).pl].squads.Get(squad);
      [*] = ;                     if (psquad<>nil) then
      [*] = ;                     TSquad(psquad).fSelected := True;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  gIntegerList.Delete(i);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         _misc_SetUnitsToSelection(plInd, gIntegerList);
      [*] = ;         gbool_gui_shifticonsselection := False;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   {'C' : begin
      [*] = ;      var count : Integer = GameObjectRayCastMouseRay;
      [*] = ;      GameObjectSortRayCastList;
      [*] = ;      var goHnd : Integer;
      [*] = ;      var i : Integer;
      [*] = ;      for i:=0 to count-1 do
      [*] = ;      begin
      [*] = ;         var tmpHnd : Integer = GetGameObjectRayCastByIndex(i);
      [*] = ;         if (tmpHnd<>0) and (GetGameObjectPlayerHandleByHandle(tmpHnd)=GetPlayerHandleInterfaceIO) then
      [*] = ;         begin
      [*] = ;            goHnd := tmpHnd;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      var fcx, fcy, fcz : Float;
      [*] = ;      var fgx : Float = GetGameObjectPositionXByHandle(goHnd);
      [*] = ;      var fgy : Float = GetGameObjectPositionYByHandle(goHnd);
      [*] = ;      var fgz : Float = GetGameObjectPositionZByHandle(goHnd);
      [*] = ;      if (IsPositionInMapWorld(fgx, fgy, fgz)) then
      [*] = ;      begin
      [*] = ;         //SetCameraElasticTargetObject(0);
      [*] = ;         SetCameraElasticTargetObject(goHnd);
      [*] = ;         SetCameraElasticTargetDistance(2);
      [*] = ;         var fcdist : Float;
      [*] = ;
      [*] = ;         AddCameraInfo('@cameraGrLook');
      [*] = ;         AddCameraInfo('@tempcamera');
      [*] = ;
      [*] = ;         var FreeMode : Boolean = GetCameraFreeRotationMode;
      [*] = ;         //SetCameraControlMode('ccmNone');
      [*] = ;         CameraInfoSaveFromCurrentView('@cameraGrLook');
      [*] = ;         if FreeMode = false then
      [*] = ;         CameraInfoNormalizeToElastic('@cameraGrLook');
      [*] = ;
      [*] = ;         var fdx, fdz, flen : Float;
      [*] = ;
      [*] = ;         GetCameraAbsolutePosition(fcx, fcy, fcz);
      [*] = ;         fgy := GetCameraAbsoluteHeightByXZ(fgx, fgz) + GetCameraHeightTarget;
      [*] = ;
      [*] = ;         if FreeMode = false then
      [*] = ;         begin
      [*] = ;            fcx := fgx - fcx;
      [*] = ;            fcy := fgy - fcy;
      [*] = ;            fcz := fgz - fcz;
      [*] = ;            flen := 2 / sqrt(fcx * fcx + fcy * fcy + fcz * fcz);
      [*] = ;            fcx := fgx - fcx * flen;
      [*] = ;            fcy := fgy - fcy * flen;
      [*] = ;            fcz := fgz - fcz * flen;
      [*] = ;
      [*] = ;            fcy := GetCameraAbsoluteHeightByXZ(fcx, fcz) + 2;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var length : Float = GetCameraDistanceToTargetObject;
      [*] = ;            fcx := fgx - fcx;
      [*] = ;            fcy := fgy - fcy;
      [*] = ;            fcz := fgz - fcz;
      [*] = ;            flen := length / sqrt(fcx * fcx + fcy * fcy + fcz * fcz);
      [*] = ;            fcx := fgx - fcx * flen;
      [*] = ;            fcy := fgy - fcy * flen;
      [*] = ;            fcz := fgz - fcz * flen;
      [*] = ;         end;
      [*] = ;
      [*] = ;         SetCameraInfoSmoothingTime(3000);
      [*] = ;         if (not CameraInfoSaveWithProperties('@tempcamera', fgx, fgy, fgz, fcx, fcy, fcz) ) then
      [*] = ;         begin
      [*] = ;            SetCameraControlMode('ccmRTS');
      [*] = ;            end else begin
      [*] = ;            if FreeMode = true then
      [*] = ;            CameraInfoNormalizeToFreeRotation('@tempcamera')
      [*] = ;            else
      [*] = ;            CameraInfoNormalizeToElastic('@tempcamera');
      [*] = ;            CameraInfoLoadToCurrentView('@tempcamera');
      [*] = ;
      [*] = ;            SetCameraInfoSmoothingTime(1500);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;}
      [*] = ;end;
      [*] = ;
      [*] = ;ExecuteState('OnShortcut1');
   struct.end
section.end

