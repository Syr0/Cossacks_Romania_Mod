section.begin
   Name = DoUpdateCursor
   Code : struct.begin
      [*] = ;var cursor : String = 'crDefault';
      [*] = ;
      [*] = ;if (GetGUIElementUnderMouse=0) then
      [*] = ;begin
      [*] = ;   var myPlHnd : Integer = GetPlayerHandleInterfaceIO;
      [*] = ;   if (myPlHnd=0) then
      [*] = ;   begin
      [*] = ;      SetGUICursorByName(cursor);
      [*] = ;      exit;
      [*] = ;   end;
      [*] = ;   var myPlInd : Integer = GetPlayerIndexByHandle(myPlHnd);
      [*] = ;   if (gint_gui_pickedbldhnd<>0) then
      [*] = ;   cursor := 'crConstruct'
      [*] = ;   else
      [*] = ;   if (gbool_gui_goinattackmode) then
      [*] = ;   begin
      [*] = ;      if (_unit_SelectedUnitsCanMove(myPlInd, gSelectedObjects)) then
      [*] = ;      cursor := 'crAttack'
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (gbool_gui_setrallypointmode) then
      [*] = ;   cursor := 'crSetRallyPoint'
      [*] = ;   else
      [*] = ;   if (gbool_gui_attackpointmode) then
      [*] = ;   cursor := 'crArtillery'
      [*] = ;   else
      [*] = ;   if (gbool_gui_guardmode) then
      [*] = ;   begin
      [*] = ;      var goHnd : Integer = _control_GetUnitUnderCursor(False);
      [*] = ;      if (goHnd<>0) then
      [*] = ;      begin
      [*] = ;         var pobj : Pointer = nil;
      [*] = ;         if (_misc_GetBaseObjID(goHnd)=gc_baseid_obj) then
      [*] = ;         pobj := _unit_GetTObj(goHnd);
      [*] = ;         if (pobj<>nil) and ((gPlayer[myPlInd].myplmask and gPlayer[TObj(pobj).pl].enemyplmask)=0) then
      [*] = ;         cursor := 'crGuard'
      [*] = ;         else
      [*] = ;         cursor := 'crNotGuard'
      [*] = ;      end
      [*] = ;      else
      [*] = ;      cursor := 'crNotGuard'
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (gbool_gui_attackpointmode) then
      [*] = ;   cursor := 'crAttackPoint'
      [*] = ;   else
      [*] = ;   if (gbool_gui_patrolmode) then
      [*] = ;   begin
      [*] = ;     if (_unit_SelectedUnitsCanMove(myPlInd, gSelectedObjects)) then
      [*] = ;     begin
      [*] = ;        cursor := 'crPatrol'
      [*] = ;     end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var goHnd : Integer = _control_GetUnitUnderCursor(False);
      [*] = ;      if (goHnd<>0) then
      [*] = ;      begin
      [*] = ;         var pobj, pres : Pointer;
      [*] = ;         var baseid : Integer = _misc_GetBaseObjID(goHnd);
      [*] = ;         case baseid of
      [*] = ;            gc_baseid_obj : pobj := _unit_GetTObj(goHnd);
      [*] = ;            gc_baseid_res : pres := _res_GetTRes(goHnd);
      [*] = ;         end;
      [*] = ;         if (pobj<>nil) or (pres<>nil) then
      [*] = ;         begin
      [*] = ;            if (baseid=gc_baseid_obj) and ((gPlayer[myPlInd].myplmask and gPlayer[TObj(pobj).pl].enemyplmask)<>0) and
      [*] = ;            (_unit_IsUnitsCanCapture(gSelectedObjects, goHnd)) and (_unit_TestCapture(goHnd)) then
      [*] = ;            begin
      [*] = ;               if (baseid=gc_baseid_obj) and ((gPlayer[myPlInd].myplmask and gPlayer[TObj(pobj).pl].enemyplmask)<>0) and (_unit_SelectedUnitsCanAttack(myPlInd, goHnd, gSelectedObjects)) then
      [*] = ;               cursor := 'crCaptureAttack'
      [*] = ;               else
      [*] = ;               cursor := 'crCapture'
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if (baseid=gc_baseid_obj) and ((gPlayer[myPlInd].myplmask and gPlayer[TObj(pobj).pl].enemyplmask)<>0) and (_unit_SelectedUnitsCanAttack(myPlInd, goHnd, gSelectedObjects)) then
      [*] = ;            cursor := 'crAttack'
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (gbool_gui_peasantselected) and (baseid=gc_baseid_res) then
      [*] = ;               begin
      [*] = ;                  if (GetMapCollisionTag(GetGameObjectPositionXByHandle(goHnd), GetGameObjectPositionZByHandle(goHnd), True)=0) then
      [*] = ;                  case TRes(pres).itype of
      [*] = ;                     gc_resource_type_food : cursor := 'crGainFood';
      [*] = ;                     gc_resource_type_wood : cursor := 'crGainWood';
      [*] = ;                     gc_resource_type_stone : cursor := 'crGainStone';
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  var plHnd : Integer = GetGameObjectPlayerHandleByHandle(goHnd);
      [*] = ;                  if (plHnd=myPlHnd) then
      [*] = ;                  begin
      [*] = ;                     if (gbool_gui_peasantselected) and (gObjProp[TObj(pobj).cid][TObj(pobj).id].bbuilding)
      [*] = ;                     and (_unit_UnitsCanBuild(goHnd, gSelectedObjects)) and ((not TObj(pobj).bbuilt) or (TObj(pobj).hp<gPlayer[TObj(pobj).pl].objbase[TObj(pobj).cid][TObj(pobj).id].maxhp)) then
      [*] = ;                     cursor := 'crConstruct'
      [*] = ;                     else
      [*] = ;                     if (_unit_UnitsCanGoInside(goHnd, gSelectedObjects, gSelectedSquads)) then
      [*] = ;                     cursor := 'crGoInside';
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SetGUICursorByName(cursor);
   struct.end
section.end

