section.begin
   Name = InitMapSettings
   Code : struct.begin
      [*] = ;ErrorLog('InitMapSettings state not needed');
      [*] = ;
      [*] = ;procedure InitMapSettings();
      [*] = ;begin
      [*] = ;   GenerateMapRandKey(gMap.settings.gen.randkey0, gMap.settings.gen.randkey1);
      [*] = ;
      [*] = ;   gMap.settings.gen.mapsize := 0;
      [*] = ;   gMap.settings.gen.terraintype := 0;
      [*] = ;   gMap.settings.gen.relieftype := 0;
      [*] = ;   gMap.settings.gen.foreststype := 0;
      [*] = ;   gMap.settings.gen.resourcestart := 0;
      [*] = ;   gMap.settings.gen.resourcemines := 0;
      [*] = ;   gMap.settings.gen.season := 0;
      [*] = ;
      [*] = ;   gMap.settings.additional.activeoption := 0;
      [*] = ;   gMap.settings.additional.startingunits := 0;
      [*] = ;   gMap.settings.additional.balloon := 0;
      [*] = ;   gMap.settings.additional.cannons := 0;
      [*] = ;   gMap.settings.additional.peacetime := 0;
      [*] = ;   gMap.settings.additional.century18 := 0;
      [*] = ;   gMap.settings.additional.capture := 0;
      [*] = ;   gMap.settings.additional.marketdip := 0;
      [*] = ;   gMap.settings.additional.limitwarship := 0;
      [*] = ;   gMap.settings.additional.teams := 0;
      [*] = ;   gMap.settings.additional.autosave := 0;
      [*] = ;   gMap.settings.additional.limit := 0;
      [*] = ;   gMap.settings.additional.gamespeed := 0;
      [*] = ;   gMap.settings.additional.adviserassistant := 0;
      [*] = ;
      [*] = ;   var ccsid : String = 'pol';
      [*] = ;   var ccid : Integer = _country_GetIDBySID(ccsid);
      [*] = ;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;   begin
      [*] = ;      gMap.players[i].id := i;
      [*] = ;      gMap.players[i].cid := ccid;
      [*] = ;      gMap.players[i].csid := ccsid;
      [*] = ;      gMap.players[i].name := 'player'+IntToStr(i);
      [*] = ;      gMap.players[i].team := 0;
      [*] = ;      gMap.players[i].color := i;
      [*] = ;      gMap.players[i].lanid := 0;
      [*] = ;      gMap.players[i].bexists := False;
      [*] = ;   end;
      [*] = ;   gMap.players[gc_player_mercenaryind].color := gc_MaxColorCount-1;
      [*] = ;
      [*] = ;   gMap.players[0].bexists := True;
      [*] = ;   gMap.players[1].bexists := True;
      [*] = ;end;
      [*] = ;
      [*] = ;InitMapSettings;
   struct.end
section.end

