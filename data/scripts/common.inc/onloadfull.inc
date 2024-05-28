section.begin
   Name = OnLoadFull
   UsedFileName = 
   Code : struct.begin
      [*] = ;_scenario_AIRegionForceRescan;
      [*] = ;_misc_PreloadTextures(True, (not gScenario.bexists), False);
      [*] = ;
      [*] = ;if (gMapHistoricalBattle.bbattle) and (gMapHistoricalBattle.battlemap<>'') then
      [*] = ;begin
      [*] = ;   gMap := gMapHistoricalBattle; // do before _misc_ApplyKeyColorRecursiveChild : cause we change colors here
      [*] = ;   ExecuteState('InitMapHistoricalBattle');
      [*] = ;   var map : TMap;
      [*] = ;   gMapHistoricalBattle := map;
      [*] = ;end;
      [*] = ;
      [*] = ;if (GetCountOfPlayers>=gc_MaxPlayerCount) then
      [*] = ;begin
      [*] = ;   var i, j : Integer;
      [*] = ;   for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;   begin
      [*] = ;      var plHnd : Integer = GetPlayerHandleByIndex(i);
      [*] = ;      for j:=GetPlayerGameObjectsCountByHandle(plHnd)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var goHnd : Integer = GetGameObjectHandleByIndex(j, plHnd);
      [*] = ;         var pobj : Pointer = _unit_GetTObj(goHnd);
      [*] = ;         if (pobj<>nil) then
      [*] = ;         begin
      [*] = ;            _misc_ApplyKeyColorRecursiveChild(goHnd, gMap.players[TObj(pobj).pl].color);
      [*] = ;            if (not GetGameObjectVisibleByHandle(goHnd)) then
      [*] = ;            begin
      [*] = ;               var statetag : Integer = GetGameObjectStatesTagByHandle(goHnd);
      [*] = ;               if (statetag and gc_statetag_essential_none<>0) then
      [*] = ;               begin
      [*] = ;                  if (TObj(pobj).insideofuid=0) then
      [*] = ;                  begin
      [*] = ;                     if (statetag and gc_statetag_visual_hide<>0) then
      [*] = ;                     begin
      [*] = ;                        _unit_SetTagStates(goHnd, gc_statetag_visual_none);
      [*] = ;                        SetGameObjectVisibleByHandle(goHnd, True);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   var plHnd : Integer = GetPlayerHandleByIndex(gc_playerind_misc);
      [*] = ;   for i:=0 to GetPlayerGameObjectsCountByHandle(plHnd)-1 do
      [*] = ;   begin
      [*] = ;      var goHnd : Integer = GetGameObjectHandleByIndex(i, plHnd);
      [*] = ;      if (GetGameObjectStringPropertyTag(goHnd)=gc_properties_stringtag_fogreveal) then
      [*] = ;      AddFOWObjects(goHnd);
      [*] = ;   end;
      [*] = ;   var miscPlHnd : Integer = GetPlayerHandleByIndex(gc_playerind_misc);
      [*] = ;   for i:=GetPlayerGameObjectsCountByHandle(miscPlHnd)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var projHnd : Integer = GetGameObjectHandleByIndex(i, miscPlHnd);
      [*] = ;      if (_misc_GetBaseObjID(projhnd)=gc_baseid_prj) then
      [*] = ;      begin
      [*] = ;         var pproj : Pointer = _weapon_GetTProj(projHnd);
      [*] = ;         if TProj(pproj).weaponid>=0 then
      [*] = ;         begin
      [*] = ;            if (gWeapons[TProj(pproj).weaponid].volumeclippedfreq>0) then
      [*] = ;            GameObjectRequestToDestroyByHandle(projHnd);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if GetSeasonType=2 then begin
      [*] = ;   SetCurrentColorTableIndex(5); //winter- dark - 6 was too bright. Maybe this is a bit too 'blueish'
      [*] = ;   SetCurrentPHDRIndex(1);
      [*] = ;end;
      [*] = ;if GetSeasonType=1 then begin
      [*] = ;   SetCurrentColorTableIndex(8); //autumn - Used to be 2 (red) in beta version.
      [*] = ;end;
      [*] = ;if GetSeasonType=3 then begin
      [*] = ;   SetCurrentColorTableIndex(7); //spring
      [*] = ;end;
      [*] = ;if GetSeasonType=0 then begin
      [*] = ;   SetCurrentColorTableIndex(0); //summer
      [*] = ;   SetCurrentPHDRIndex(0);
      [*] = ;end;
      [*] = ;//Light presets in data\env\lights\light.presets // Maybe high sun for summer/desert maps. Mid low sun for spring. Very low for winter? (or) Enable 'time of day' as option in rnd map settings?
      [*] = ;if GetSeasonType=1 then begin // Autumn
      [*] = ;   SetLightPattern('LongShadow');
      [*] = ;end;
      [*] = ;//if (gc_christmas>0) then
      [*] = ;//SetCurrentColorTableIndex(5);
      [*] = ;{var irn : Integer = Floor(random*4);
      [*] = ;var lid : String = 'light'+IntToStr(irn);
      [*] = ;//SetLightPattern(lid);
      [*] = ;if (gc_halloween>0) then
      [*] = ;SetCurrentColorTableIndex(5)
      [*] = ;else begin
      [*] = ;   irn := Floor(random*5);
      [*] = ;   SetCurrentColorTableIndex(irn);
      [*] = ;end;
      [*] = ;Log('LightPattern: '+lid+'; 'CurrentColor: '+IntToStr(GetCurrentColorTableIndex));}
      [*] = ;if gScenario.bexists then
      [*] = ;begin
      [*] = ;   var i, j : Integer;
      [*] = ;   for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;   for j:=0 to gc_MaxPlayerCount-1 do
      [*] = ;   if i<>j then
      [*] = ;   if (gPlayer[i].enemyplmask and (1 shl j)<>0) then
      [*] = ;   begin
      [*] = ;      if GetIsFriendPlayersByHandle(GetPlayerHandleByIndex(i), GetPlayerHandleByIndex(j)) then
      [*] = ;      DeletePlayerFriendPlayerByHandle(GetPlayerHandleByIndex(i), GetPlayerHandleByIndex(j));
      [*] = ;      AddPlayerEnemyPlayerByHandle(GetPlayerHandleByIndex(i), GetPlayerHandleByIndex(j))
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if GetIsEnemyPlayersByHandle(GetPlayerHandleByIndex(i), GetPlayerHandleByIndex(j)) then
      [*] = ;      DeletePlayerEnemyPlayerByHandle(GetPlayerHandleByIndex(i), GetPlayerHandleByIndex(j));
      [*] = ;      AddPlayerFriendPlayerByHandle(GetPlayerHandleByIndex(i), GetPlayerHandleByIndex(j));
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_misc_FixCollisionInertiaObjectsInOnePoint;
      [*] = ;_misc_UpdateTopologyZoneSizeToMapSize(True);
      [*] = ;
      [*] = ;gfloat_gui_musiclastbattletimestart := 0;
      [*] = ;gfloat_gui_musiclastbattletimeend := 0;
      [*] = ;gfloat_gui_musiclastnationaltimestart := 0;
      [*] = ;gfloat_gui_musiclastnationaltimeend := 0;
      [*] = ;
      [*] = ;_control_SetGameSpeedByMode(gProfile.igamespeed, True);
      [*] = ;_misc_CalcPlayerZonesDist(-1);
      [*] = ;
      [*] = ;// gbool_use_collision support start
      [*] = ;_misc_SetUseCollision(gbool_use_collision);
      [*] = ;// gbool_use_collision support finish
      [*] = ;
      [*] = ;_misc_ResetProgressPlayer;
      [*] = ;
      [*] = ;//if (_net_IsReplay) then
      [*] = ;//ExecuteState('InitMapGen');
   struct.end
section.end

