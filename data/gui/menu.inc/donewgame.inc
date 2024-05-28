section.begin
   Name = DoNewGame
   Code : struct.begin
      [*] = ;Log('--- DoNewGame --- start');
      [*] = ;
      [*] = ;const cMapSize = 640;
      [*] = ;const cCells = 1;
      [*] = ;const cGuiCfgPath = '.\data\gui\menu.cfg';
      [*] = ;const cLightPreset = '';
      [*] = ;const cInitState = 'InitMapGen';
      [*] = ;
      [*] = ;if (not IsLanGame) then // if client, then gMap already syncronized from server pc
      [*] = ;begin
      [*] = ;   gMap.dlcs := gProfile.lastknowndlcs;
      [*] = ;   if (not gbool_gui_donewgamerestart) then
      [*] = ;   GenerateMapRandKey(gMap.settings.gen.randkey0, gMap.settings.gen.randkey1)
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var i : Integer;
      [*] = ;      for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;      gMap.players[i].bleave := False;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;gbool_gui_donewgamerestart := False;
      [*] = ;//gMap.settings.gen.randkey0:=0; gMap.settings.gen.randkey1:=1;
      [*] = ;//ExecuteState('InitMapSettings'); // done in custom game menu
      [*] = ;
      [*] = ;if (IsLanGame) then
      [*] = ;SetGUIEventStateOnLanChange('OnLanEventSession')
      [*] = ;else
      [*] = ;SetGUIEventStateOnLanChange('OnLanEvent');
      [*] = ;
      [*] = ;SetRandomExtKey64(gMap.settings.gen.randkey0, gMap.settings.gen.randkey1);
      [*] = ;SetMapGeneratorRandomKey(gMap.settings.gen.randkey0, gMap.settings.gen.randkey1);
      [*] = ;SetGlobalMapGeneratorRandomKey(gMap.settings.gen.randkey0, gMap.settings.gen.randkey1);
      [*] = ;
      [*] = ;var genMapName : String = 'game_v'+IntToStr(gDataVersion)+'k'+IntToStr(GetRandomKey)+'.map';
      [*] = ;var genZoneName : String = 'Default';
      [*] = ;var genPresetName : String = 'Default';
      [*] = ;var genCells : Integer = cCells;
      [*] = ;var genMapSize : Integer;
      [*] = ;case gMap.settings.gen.mapsize of
      [*] = ;   0 : genMapSize := 320; //normal
      [*] = ;   1 : genMapSize := 480; //large x2
      [*] = ;   2 : genMapSize := 640; //huge x4
      [*] = ;   3 : genMapSize := 256; //tiny
      [*] = ;   4 : genMapSize := 400; //medium/big x1.5
      [*] = ;   5 : genMapSize := 560; //big/very large x3
      [*] = ;   else
      [*] = ;   genMapSize := 320;
      [*] = ;end;
      [*] = ;
      [*] = ;SetCameraElasticDistance(100);
      [*] = ;SoundManagerUnloadAmbientThreads;
      [*] = ;gbool_gui_maxcameradist := True; // used in DoCreate to reset camera to default height
      [*] = ;gbool_editor_fogofwar := True;
      [*] = ;gInterface.gamemode := gc_gamemode_game;
      [*] = ;gMap.gamestage := gc_map_gamestage_waitingloading;
      [*] = ;gint_gui_achwinlose := 0;
      [*] = ;gfloat_gui_lanlastgametimesyncreceived := 0;
      [*] = ;gfloat_gui_onlinedoprogressstart := 0;
      [*] = ;gbool_gui_onlinedoreadysent := False;
      [*] = ;gfloat_gui_lanlastgametimesync := 0;
      [*] = ;var i : Integer;
      [*] = ;for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;gfloat_gui_lanlastaliveeventreceived[i] := 0;
      [*] = ;gfloat_lan_lastsyncrestime := 0;
      [*] = ;gfloat_lan_lastsyncstatstime := 0;
      [*] = ;gfloat_lan_lastsyncdatatime := 0;
      [*] = ;gint_count_pause := 0;
      [*] = ;gfloat_time_pause := 0;
      [*] = ;
      [*] = ;//if (_net_IsOnline) then
      [*] = ;begin
      [*] = ;   gInternetShell.prevstate := 5;
      [*] = ;   var str : String = 'www false';
      [*] = ;   _misc_ProcessMessage(str);
      [*] = ;   gProfile.bNoAchs := False;
      [*] = ;end;
      [*] = ;gint_gui_changeresolutionstage := 0;
      [*] = ;
      [*] = ;UnregisterGUIAllShortcuts;
      [*] = ;GUIExecuteState('RegisterShortcuts');
      [*] = ;
      [*] = ;if (GetLanMode=gc_lanmode_client) then
      [*] = ;_net_lanmode_last := gc_lanmode_client
      [*] = ;else
      [*] = ;if (GetLanMode>=gc_lanmode_server) then
      [*] = ;_net_lanmode_last := gc_lanmode_server
      [*] = ;else
      [*] = ;_net_lanmode_last := 0;
      [*] = ;
      [*] = ;gbool_gui_landoreadysent := False;
      [*] = ;
      [*] = ;StateMachineClearVariables(GetMapInitMachineHandle);
      [*] = ;_gui_ProcessProgressBar('Creating new map...', 0, 0, False);
      [*] = ;if gMap.settings.gen.season<0 then
      [*] = ;begin
      [*] = ;   var bAllowWinter : Boolean = True;
      [*] = ;   var bAllowSpring : Boolean = True;
      [*] = ;   var bAllowAutumn : Boolean = True;
      [*] = ;   if bAllowWinter and bAllowSpring and bAllowAutumn then
      [*] = ;   begin
      [*] = ;      if RandomExt>0.75 then
      [*] = ;      gMap.settings.gen.season := 3
      [*] = ;      else
      [*] = ;      if RandomExt>0.50 then
      [*] = ;      gMap.settings.gen.season := 2
      [*] = ;      else
      [*] = ;      if RandomExt>0.25 then
      [*] = ;      gMap.settings.gen.season := 1
      [*] = ;      else
      [*] = ;      gMap.settings.gen.season := 0;
      [*] = ;   end
      [*] = ;end;
      [*] = ;
      [*] = ;_profile_LoadAdviser;
      [*] = ;
      [*] = ;if _net_IsOnline then
      [*] = ;begin
      [*] = ;   for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;   begin
      [*] = ;      gPlayer[i].playeradviser.adviser.bavailable := (_net_IsOnline) and (gMap.settings.additional.adviserassistant=gc_mapsettings_adviserassistant_default);
      [*] = ;      gPlayer[i].playeradviser.adviser.benable := False;
      [*] = ;      gPlayer[i].playeradviser.adviser.bvisible := False;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;   begin
      [*] = ;      gPlayer[i].playeradviser.adviser.bavailable := (gPlayer[i].playeradviser.adviser.bavailable) and (gMap.settings.additional.adviserassistant=gc_mapsettings_adviserassistant_default);
      [*] = ;      if not gPlayer[i].playeradviser.adviser.bavailable then
      [*] = ;      gPlayer[i].playeradviser.adviser.benable := False;
      [*] = ;      gPlayer[i].playeradviser.adviser.bvisible := False;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var season : Integer = gMap.settings.gen.season;
      [*] = ;if (gMap.bbattle) and (gMap.battlemap<>'') then
      [*] = ;begin
      [*] = ;   Log(gMap.battlemap);
      [*] = ;   gbool_scenario_startneeded := True;
      [*] = ;   gMapHistoricalBattle := gMap;
      [*] = ;   LoadMapNeeded(gMap.battlemap);
      [*] = ;   Log('--- DoNewGame : LoadMapNeeded : Historical Battle --- finish');
      [*] = ;end
      [*] = ;else
      [*] = ;if (gMap.bbattle) and (gMap.battlemap='') then
      [*] = ;ErrorLog('DoNewGame : gMap.battlemap is empty when gMap.bbattle=True')
      [*] = ;else
      [*] = ;begin
      [*] = ;   LoadMapNeeded('');
      [*] = ;   GenerateMapNeededExtBorder(genMapName, genZoneName, genPresetName, genMapSize, genMapSize, genCells, gMap.settings.gen.randkey0, gMap.settings.gen.randkey1, 0, season, 0, '', '', '', '', '', '', cGuiCfgPath, '', 'light0', '', cInitState, false);
      [*] = ;   Log('--- DoNewGame --- finish');
      [*] = ;end;
   struct.end
section.end

