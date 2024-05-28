section.begin
   Name = DoGenerate
   Code : struct.begin
      [*] = ;var bDesert : Boolean = (gMap.settings.gen.relieftype=5); //moving desert to Relief , rather than having it under 'seasons' -Ebel
      [*] = ;var foreststype : Integer = gMap.settings.gen.foreststype; //Actually using this now, previously it was always foreststype: 0
      [*] = ;if (foreststype>3) then // random
      [*] = ;foreststype := floor(RandomExt*4);
      [*] = ;
      [*] = ;function IsDotInElipse(x0, y0, x, y, rx, ry : Float) : Boolean;
      [*] = ;begin
      [*] = ;   var val : Float = sqr(x-x0)/sqr(rx)+sqr(y-y0)/sqr(ry);
      [*] = ;   Result := (val<=1);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _misc_FillPatternMaskElipse(x, y, rx, ry : Float);
      [*] = ;begin
      [*] = ;   var mapW : Integer = GetMapWidth;
      [*] = ;   var mapH : Integer = GetMapHeight;
      [*] = ;   var i, j : Integer;
      [*] = ;
      [*] = ;   for i:=-round(ry) to floor(ry*2)-1 do
      [*] = ;   for j:=-round(rx) to floor(rx*2)-1 do
      [*] = ;   begin
      [*] = ;      var binside : Boolean = IsDotInElipse(0, 0, j, i, rx, ry);
      [*] = ;      if (binside) then
      [*] = ;      begin
      [*] = ;         var indx : Integer = floor(x+(mapW div 2)+j);
      [*] = ;         var indy : Integer = floor(y+(mapH div 2)+i);
      [*] = ;         if (indx>=0) and (indx<mapW) and (indy>=0) and (indy<mapH) then
      [*] = ;         gPatternMask[indx, indy] := True;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _misc_FillPatternMaskCircle(x, y, r : Float);
      [*] = ;begin
      [*] = ;   var mapW : Integer = GetMapWidth;
      [*] = ;   var mapH : Integer = GetMapHeight;
      [*] = ;   var i, j : Integer;
      [*] = ;   for i:=-round(r) to floor(r*2)-1 do
      [*] = ;   for j:=-round(r) to floor(r*2)-1 do
      [*] = ;   begin
      [*] = ;      if (VectorDistance(x, 0, y, x+j, 0, y+i)<r) then
      [*] = ;      begin
      [*] = ;         var indx : Integer = floor(x+(mapW div 2)+j);
      [*] = ;         var indy : Integer = floor(y+(mapH div 2)+i);
      [*] = ;         if (indx>=0) and (indx<mapW) and (indy>=0) and (indy<mapH) then
      [*] = ;         gPatternMask[indx, indy] := True;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _misc_FillPatternMaskRectangle(x, y, w, h : Float);
      [*] = ;begin
      [*] = ;   var mapW : Integer = GetMapWidth;
      [*] = ;   var mapH : Integer = GetMapHeight;
      [*] = ;   var i, j : Integer;
      [*] = ;   for i:=0 to floor(w)-1 do
      [*] = ;   for j:=0 to floor(h)-1 do
      [*] = ;   begin
      [*] = ;      var indx : Integer = floor(x+(mapW div 2)+j);
      [*] = ;      var indy : Integer = floor(y+(mapH div 2)+i);
      [*] = ;      if (indx>=0) and (indx<mapW) and (indy>=0) and (indy<mapH) then
      [*] = ;      gPatternMask[indx, indy] := True;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _misc_FillPatternMaskMapBorder(r : Integer);
      [*] = ;begin
      [*] = ;   var mapW : Integer = GetMapWidth;
      [*] = ;   var mapH : Integer = GetMapHeight;
      [*] = ;   var indx, indy : Integer;
      [*] = ;   for indy:=0 to mapH-1 do
      [*] = ;   for indx:=0 to mapW-1 do
      [*] = ;   begin
      [*] = ;      if (indx<r) or (indx>(mapW-r)) or (indy<r) or (indy>(mapH-r)) then
      [*] = ;      gPatternMask[indx, indy] := True;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CreateUnit(plInd, cid, unitid : Integer; x, z, dir : Float);
      [*] = ;begin
      [*] = ;   var plHnd : Integer = GetPlayerHandleByIndex(plInd);
      [*] = ;   var j, k : Integer;
      [*] = ;   var unitradius : Float = gc_obj_radius_default*gc_tiles_to_pixels*4;
      [*] = ;   var dispradius : Float = gc_obj_radius_default*gc_tiles_to_pixels*1.1+gc_objectEpsilonDist/2;
      [*] = ;   var goHnd : Integer;
      [*] = ;   var dispx : Float = (0.5-RandomExt)*dispradius;
      [*] = ;   var dispy, dispz : Float;
      [*] = ;   VectorRotateY(dispx, dispy, dispz, RandomExt*360);
      [*] = ;   var newx : Float = x+dispx;
      [*] = ;   var newz : Float = z+dispz;
      [*] = ;   if (gObjProp[cid][unitid].bbuilding) then
      [*] = ;   begin
      [*] = ;      newx := floor(x*2)/2+0.25;
      [*] = ;      newz := floor(z*2)/2+0.25;
      [*] = ;   end;
      [*] = ;   gint_unit_parentcid := cid;
      [*] = ;   var racename : String;
      [*] = ;   if (gObjProp[cid][unitid].bbuilding) then
      [*] = ;   racename := gc_racename_buildings
      [*] = ;   else
      [*] = ;   racename := gc_racename_units;
      [*] = ;   goHnd := CreatePlayerGameObjectHandleByHandle(plHnd, racename, gObjProp[cid][unitid].sid, newx, RayCastHeight(newx, newz), newz); // No need to do write new on generation phase.
      [*] = ;   if (goHnd<>0) then
      [*] = ;   begin
      [*] = ;      if (gObjProp[cid][unitid].bbuilding) then
      [*] = ;      begin
      [*] = ;         var pobj : Pointer = _unit_GetTObj(goHnd);
      [*] = ;         if (pobj<>nil) then
      [*] = ;         begin
      [*] = ;            // for offline or server it will be fixed in Nothing.
      [*] = ;            TObj(pobj).bbuilt := False;
      [*] = ;            TObj(pobj).buildprogress := 0;
      [*] = ;            TObj(pobj).hp := gPlayer[TObj(pobj).pl].objbase[TObj(pobj).cid][TObj(pobj).id].maxhp;
      [*] = ;            if ((_net_IsClient and IsLanReady) or _net_IsReplay) then
      [*] = ;            begin
      [*] = ;               GameObjectExecuteStateByHandle(goHnd, 'Nothing');
      [*] = ;               GameObjectSwitchToStateByHandle(goHnd, 'Nothing');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      GameObjectRollByHandle(goHnd, dir);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CreateFormations(plInd, cid, unitid : Integer; x, z, dir : Float; amount, formationid : Integer; bCreateSquad : Boolean);
      [*] = ;begin
      [*] = ;   gIntegerList.Clear;
      [*] = ;   var plHnd : Integer = GetPlayerHandleByIndex(plInd);
      [*] = ;   var minx : Integer = 100;
      [*] = ;   var miny : Integer = 100;
      [*] = ;   var maxx : Integer;
      [*] = ;   var maxy : Integer;
      [*] = ;   var j, k : Integer;
      [*] = ;   for j:=0 to gc_formation_maskmaxheight-1 do
      [*] = ;   for k:=0 to gc_formation_maskmaxwidth-1 do
      [*] = ;   begin
      [*] = ;      if (gFormation[formationid].mask[j][k]) then
      [*] = ;      begin
      [*] = ;         if (j<miny) then miny := j;
      [*] = ;         if (j>maxy) then maxy := j;
      [*] = ;         if (k<minx) then minx := k;
      [*] = ;         if (k>maxx) then maxx := k;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   var width : Integer = maxx-minx;
      [*] = ;   var height : Integer = maxy-miny;
      [*] = ;   var unitradius, dispradius : Float;
      [*] = ;   if (bCreateSquad) then
      [*] = ;   begin
      [*] = ;      unitradius:= gc_obj_radius_formation_default*gc_tiles_to_pixels*4;
      [*] = ;      dispradius := unitradius*0.35;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      unitradius:= gc_obj_radius_default*gc_tiles_to_pixels*4;
      [*] = ;      dispradius := gc_obj_radius_default*gc_tiles_to_pixels*1.1+gc_objectEpsilonDist/2;
      [*] = ;   end;
      [*] = ;   var midx : Float = -(width div 2)*unitradius;
      [*] = ;   var midy : Float;
      [*] = ;   var midz : Float = -(height div 2)*unitradius;
      [*] = ;   VectorRotateY(midx, midy, midz, dir);
      [*] = ;   var test : Integer;
      [*] = ;   var ind : Integer;
      [*] = ;   while ind<amount do
      [*] = ;   begin
      [*] = ;      for [MAIN]j:=miny to maxy do
      [*] = ;      for k:=minx to maxx do
      [*] = ;      begin
      [*] = ;         test := test+1;
      [*] = ;         if (ind>=amount) then
      [*] = ;         break(MAIN);
      [*] = ;         if (gFormation[formationid].mask[j][k]) then
      [*] = ;         begin
      [*] = ;            ind := ind+1;
      [*] = ;            var goHnd : Integer;
      [*] = ;            var dirx : Float = k*unitradius;
      [*] = ;            var diry : Float;
      [*] = ;            var dirz : Float = j*unitradius;
      [*] = ;            VectorRotateY(dirx, diry, dirz, dir);
      [*] = ;            var newx : Float = x+midx+dirx;
      [*] = ;            var newz : Float = z+midz+dirz;
      [*] = ;
      [*] = ;            var dispx : Float = (0.5-random)*dispradius;
      [*] = ;            var dispy, dispz : Float;
      [*] = ;            VectorRotateY(dispx, dispy, dispz, random*360);
      [*] = ;            newx := newx+dispx;
      [*] = ;            newz := newz+dispz;
      [*] = ;            if (gObjProp[cid][unitid].bbuilding) then
      [*] = ;            begin
      [*] = ;               newx := floor(x*2)/2+0.25;
      [*] = ;               newz := floor(z*2)/2+0.25;
      [*] = ;            end;
      [*] = ;            gint_unit_parentcid := cid;
      [*] = ;            var racename : String;
      [*] = ;            if (gObjProp[cid][unitid].bbuilding) then
      [*] = ;            racename := gc_racename_buildings
      [*] = ;            else
      [*] = ;            racename := gc_racename_units;
      [*] = ;            goHnd := CreatePlayerGameObjectHandleByHandle(plHnd, racename, gObjProp[cid][unitid].sid, newx, RayCastHeight(newx, newz), newz); // No need to do write new on generation phase.
      [*] = ;            if (goHnd<>0) then
      [*] = ;            begin
      [*] = ;               gIntegerList.Add(goHnd);
      [*] = ;               if (gObjProp[cid][unitid].bbuilding) then
      [*] = ;               begin
      [*] = ;                  var pobj : Pointer = _unit_GetTObj(goHnd);
      [*] = ;                  if (pobj<>nil) then
      [*] = ;                  begin
      [*] = ;                     TObj(pobj).bbuilt := False;
      [*] = ;                     TObj(pobj).buildprogress := 0;
      [*] = ;                     TObj(pobj).hp := gPlayer[TObj(pobj).pl].objbase[TObj(pobj).cid][TObj(pobj).id].maxhp;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               GameObjectRollByHandle(goHnd, dir);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if (test>10000) then
      [*] = ;      begin
      [*] = ;         ErrorLog('Scenario : perpetum cycle');
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if (bCreateSquad) then
      [*] = ;   _player_CreateSquad(plHnd, formationid, 0, 0, gIntegerList, False, False);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CreateUniqueStartingUnits(plind : Integer; bOnlyModifyPatternMask : Boolean);
      [*] = ;begin
      [*] = ;   if (gMap.settings.additional.startingunits>gc_mapsettings_startingunits_default) then
      [*] = ;   begin
      [*] = ;      var curver : Integer;
      [*] = ;      if (gInterface.gamemode=gc_gamemode_replay) then
      [*] = ;      curver := gRecordGeneratorVersion
      [*] = ;      else
      [*] = ;      curver := gDataVersion;
      [*] = ;      var csid : String = gMap.players[plind].csid;
      [*] = ;      var cid : Integer = _country_GetIDBySID(csid);
      [*] = ;      var pStartingSettings : Integer = _parser_ParserTemporary(True);
      [*] = ;      ParserLoadFromFileByHandle(pStartingSettings, gc_filepath_startingsettings);
      [*] = ;      var i, j, k, m, n, o : Integer;
      [*] = ;      for i:=0 to ParserGetCountByHandle(pStartingSettings)-1 do
      [*] = ;      begin
      [*] = ;         var pStartingSetting : Integer = ParserSelectByHandleByIndex(pStartingSettings, i);
      [*] = ;         if (pStartingSetting<>0) then
      [*] = ;         begin
      [*] = ;            var startid : Integer = ParserGetIntValueByKeyByHandle(pStartingSetting, 'startid');
      [*] = ;            var dataversionmin : Integer = ParserGetIntValueByKeyByHandle(pStartingSetting, 'dataversionmin');
      [*] = ;            var dataversionmax : Integer = ParserGetIntValueByKeyByHandle(pStartingSetting, 'dataversionmax');
      [*] = ;            if (startid=gMap.settings.additional.startingunits) then
      [*] = ;            if (((dataversionmin=0) and (dataversionmax=0)) or ((curver>=dataversionmin) and (curver<=dataversionmax))) then
      [*] = ;            begin
      [*] = ;               var pAddResources : Integer = ParserSelectByHandleByKey(pStartingSetting, 'addresources');
      [*] = ;               if (pAddResources<>0) and (not bOnlyModifyPatternMask) then
      [*] = ;               begin
      [*] = ;                  _res_AddResToPlayerByIndex(plind, gc_resource_type_food, ParserGetIntValueByKeyByHandle(pAddResources, 'food'));
      [*] = ;                  _res_AddResToPlayerByIndex(plind, gc_resource_type_wood, ParserGetIntValueByKeyByHandle(pAddResources, 'wood'));
      [*] = ;                  _res_AddResToPlayerByIndex(plind, gc_resource_type_stone, ParserGetIntValueByKeyByHandle(pAddResources, 'stone'));
      [*] = ;                  _res_AddResToPlayerByIndex(plind, gc_resource_type_gold, ParserGetIntValueByKeyByHandle(pAddResources, 'gold'));
      [*] = ;                  _res_AddResToPlayerByIndex(plind, gc_resource_type_iron, ParserGetIntValueByKeyByHandle(pAddResources, 'iron'));
      [*] = ;                  _res_AddResToPlayerByIndex(plind, gc_resource_type_coal, ParserGetIntValueByKeyByHandle(pAddResources, 'coal'));
      [*] = ;               end;
      [*] = ;               var pCountries : Integer = ParserSelectByHandleByKey(pStartingSetting, 'countries');
      [*] = ;               if (pCountries<>0) then
      [*] = ;               begin
      [*] = ;                  for j:=0 to ParserGetCountByHandle(pCountries)-1 do
      [*] = ;                  begin
      [*] = ;                     var pCountry : Integer = ParserSelectByHandleByIndex(pCountries, j);
      [*] = ;                     if (pCountry<>0) then
      [*] = ;                     begin
      [*] = ;                        var pAllowedCountries : Integer = ParserSelectByHandleByKey(pCountry, 'allowedcountries');
      [*] = ;                        if (pAllowedCountries<>0) then
      [*] = ;                        begin
      [*] = ;                           for [ALLOWEDCOUNTRIES]k:=0 to ParserGetCountByHandle(pAllowedCountries)-1 do
      [*] = ;                           begin
      [*] = ;                              //var countrysid : String = ParserGetValueByKeyByHandle(pCountry, 'countrysid');
      [*] = ;                              var allowedcountrysid : String = ParserGetValueByIndexByHandle(pAllowedCountries, k);
      [*] = ;                              var allowedcountryid : Integer = _country_GetIDBySID(allowedcountrysid);
      [*] = ;                              if (allowedcountryid=cid) then
      [*] = ;                              begin
      [*] = ;                                 var pCountryAddResources : Integer = ParserSelectByHandleByKey(pStartingSetting, 'addresources');
      [*] = ;                                 if (pCountryAddResources<>0) and (not bOnlyModifyPatternMask) then
      [*] = ;                                 begin
      [*] = ;                                    _res_AddResToPlayerByIndex(plind, gc_resource_type_food, ParserGetIntValueByKeyByHandle(pCountryAddResources, 'food'));
      [*] = ;                                    _res_AddResToPlayerByIndex(plind, gc_resource_type_wood, ParserGetIntValueByKeyByHandle(pCountryAddResources, 'wood'));
      [*] = ;                                    _res_AddResToPlayerByIndex(plind, gc_resource_type_stone, ParserGetIntValueByKeyByHandle(pCountryAddResources, 'stone'));
      [*] = ;                                    _res_AddResToPlayerByIndex(plind, gc_resource_type_gold, ParserGetIntValueByKeyByHandle(pCountryAddResources, 'gold'));
      [*] = ;                                    _res_AddResToPlayerByIndex(plind, gc_resource_type_iron, ParserGetIntValueByKeyByHandle(pCountryAddResources, 'iron'));
      [*] = ;                                    _res_AddResToPlayerByIndex(plind, gc_resource_type_coal, ParserGetIntValueByKeyByHandle(pCountryAddResources, 'coal'));
      [*] = ;                                 end;
      [*] = ;                                 var arrLegendKeyIndexes : array [0..15] of String;
      [*] = ;                                 var arrLegendRoleIndexes : array [0..15] of Integer;
      [*] = ;                                 var arrLegendCountrySIDIndexes : array [0..15] of String;
      [*] = ;                                 var arrLegendBaseNameIndexes : array [0..15] of String;
      [*] = ;                                 var pLegends : Integer = ParserSelectByHandleByKey(pCountry, 'legends');
      [*] = ;                                 if (pLegends<>0) then
      [*] = ;                                 begin
      [*] = ;                                    var iLastLegendIndex : Integer;
      [*] = ;                                    for m:=0 to ParserGetCountByHandle(pLegends)-1 do
      [*] = ;                                    begin
      [*] = ;                                       var pLegend : Integer = ParserSelectByHandleByIndex(pLegends, m);
      [*] = ;                                       if (pLegend<>0) then
      [*] = ;                                       begin
      [*] = ;                                          var key : String = ParserGetValueByKeyByHandle(pLegend, 'key');
      [*] = ;                                          var role : Integer = ParserGetIntValueByKeyByHandle(pLegend, 'role');
      [*] = ;                                          var countrysid : String = ParserGetValueByKeyByHandle(pLegend, 'countrysid');
      [*] = ;                                          var basename : String = ParserGetValueByKeyByHandle(pLegend, 'basename');
      [*] = ;                                          arrLegendKeyIndexes[iLastLegendIndex] := key;
      [*] = ;                                          arrLegendRoleIndexes[iLastLegendIndex] := role;
      [*] = ;                                          arrLegendCountrySIDIndexes[iLastLegendIndex] := countrysid;
      [*] = ;                                          arrLegendBaseNameIndexes[iLastLegendIndex] := basename;
      [*] = ;                                          iLastLegendIndex := iLastLegendIndex+1;
      [*] = ;                                       end
      [*] = ;                                    end;
      [*] = ;                                 end;
      [*] = ;                                 var pMasks : Integer = ParserSelectByHandleByKey(pCountry, 'mask');
      [*] = ;                                 if (pMasks<>0) then
      [*] = ;                                 begin
      [*] = ;                                    var maskwidth : Integer;
      [*] = ;                                    var maskheight : Integer = ParserGetCountByHandle(pMasks);
      [*] = ;                                    for m:=0 to maskheight-1 do
      [*] = ;                                    begin
      [*] = ;                                       var row : String = ParserGetValueByIndexByHandle(pMasks, m);
      [*] = ;                                       var length : Integer = StrLength(row);
      [*] = ;                                       if (length>maskwidth) then
      [*] = ;                                       maskwidth := length;
      [*] = ;                                    end;
      [*] = ;                                    const unitradius = gc_obj_radius_default*gc_tiles_to_pixels*4;//0.75;
      [*] = ;                                    var lx : Float = gMap.players[plind].startx-(maskwidth*unitradius/2);
      [*] = ;                                    var ty : Float = gMap.players[plind].starty-(maskheight*unitradius/2);
      [*] = ;                                    for m:=0 to maskheight-1 do
      [*] = ;                                    begin
      [*] = ;                                       var row : String = ParserGetValueByIndexByHandle(pMasks, m);
      [*] = ;                                       for n:=1 to StrLength(row) do
      [*] = ;                                       begin
      [*] = ;                                          var schar : String = SubStr(row, n, 1);
      [*] = ;                                          if (schar<>'.') and (schar<>' ') then
      [*] = ;                                          begin
      [*] = ;                                             var keyind : Integer = -1;
      [*] = ;                                             for o:=0 to 15 do
      [*] = ;                                             begin
      [*] = ;                                                if (arrLegendKeyIndexes[o]=schar) then
      [*] = ;                                                begin
      [*] = ;                                                   keyind := o;
      [*] = ;                                                   var role : Integer = arrLegendRoleIndexes[o];
      [*] = ;                                                   var countrysid : String = arrLegendCountrySIDIndexes[o];
      [*] = ;                                                   var basename : String = arrLegendBaseNameIndexes[o];
      [*] = ;                                                   var unitid, countryid : Integer;
      [*] = ;                                                   if (countrysid<>'') then
      [*] = ;                                                   countryid := _country_GetIDBySID(countrysid)
      [*] = ;                                                   else
      [*] = ;                                                   countryid := cid;
      [*] = ;                                                   if (role>0) then
      [*] = ;                                                   unitid := _country_GetMemberIDByAIRole(countryid, role)
      [*] = ;                                                   else
      [*] = ;                                                   if (basename<>'') then
      [*] = ;                                                   unitid := _unit_ConvertObjSIDToID(countryid, basename);
      [*] = ;                                                   if (unitid<>0) then
      [*] = ;                                                   begin
      [*] = ;                                                      var x : Float = lx+n*unitradius;
      [*] = ;                                                      var z : Float = ty+m*unitradius;
      [*] = ;                                                      var dir : Float = -90;
      [*] = ;                                                      if (bOnlyModifyPatternMask) then
      [*] = ;                                                      begin
      [*] = ;                                                         var r : Integer;
      [*] = ;                                                         if (gObjProp[countryid][unitid].bbuilding) then
      [*] = ;                                                         r := 5
      [*] = ;                                                         else
      [*] = ;                                                         r := 1;
      [*] = ;                                                         _misc_FillPatternMaskCircle(x, z, r)
      [*] = ;                                                         //gPatternMask[floor(x+(GetMapWidth div 2))][floor(z+(GetMapHeight div 2))] := True;
      [*] = ;                                                      end
      [*] = ;                                                      else
      [*] = ;                                                      CreateUnit(plind, countryid, unitid, x, z, dir);
      [*] = ;                                                   end;
      [*] = ;                                                   break;
      [*] = ;                                                end;
      [*] = ;                                             end;
      [*] = ;                                          end;
      [*] = ;                                       end;
      [*] = ;                                    end;
      [*] = ;                                 end;
      [*] = ;                                 break(ALLOWEDCOUNTRIES);
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var envplhnd : Integer = GetPlayerHandleByName(gc_racename_env);
      [*] = ;
      [*] = ;TimeLogReset;
      [*] = ;
      [*] = ;var x0 : Integer = -(GetMapWidth div 2);
      [*] = ;var y0 : Integer = -(GetMapHeight div 2);
      [*] = ;var x1 : Integer = (GetMapWidth div 2);
      [*] = ;var y1 : Integer = (GetMapHeight div 2);
      [*] = ;
      [*] = ;const cCircle1MaskX = 5;
      [*] = ;const cCircle1MaskY = 7;
      [*] = ;
      [*] = ;const cCircle2MaskX = 12;
      [*] = ;const cCircle2MaskY = 15;
      [*] = ;
      [*] = ;const cCircle3MaskX = 22;
      [*] = ;const cCircle3MaskY = 18;
      [*] = ;
      [*] = ;const cBorderObjDist = 1;
      [*] = ;
      [*] = ;// _misc_UnitCreateMiniMapPrimitive
      [*] = ;//
      [*] = ;function _misc_MineCreateMiniMapPrimitive(goHnd : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var primHnd : Integer = CreateGUIMiniMapPrimitive('pl2x2.4');
      [*] = ;   SetGUIMiniMapPrimitivePosition(primHnd, GetGameObjectPositionXByHandle(goHnd), GetGameObjectPositionZByHandle(goHnd));
      [*] = ;end;
      [*] = ;
      [*] = ;// _misc_GetPatternName
      [*] = ;//
      [*] = ;procedure _misc_GetPatternName(var name : String; prefix : String; count : Integer);
      [*] = ;begin
      [*] = ;   var rndind : Integer = 1+floor(RandomExt*count);
      [*] = ;   name := prefix+IntToStr(rndind);
      [*] = ;end;
      [*] = ;
      [*] = ;// vars
      [*] = ;var mapW : Integer = GetMapWidth;
      [*] = ;var mapH : Integer = GetMapHeight;
      [*] = ;var maphW : Integer = mapW div 2;
      [*] = ;var maphH : Integer = mapH div 2;
      [*] = ;
      [*] = ;gSelectedObjects.Clear;
      [*] = ;gGuiUpdateHighlights.Clear;
      [*] = ;GUIMiniMapPrimitivesClear;
      [*] = ;
      [*] = ;procedure ClearMapMaskAndObjects();
      [*] = ;begin
      [*] = ;   var i, j : Integer;
      [*] = ;   const cMapSize = 640;
      [*] = ;   for i:=0 to cMapSize-1 do
      [*] = ;   for j:=0 to cMapSize-1 do
      [*] = ;   gPatternMask[i, j] := False;
      [*] = ;   ResetPatternMap(False);
      [*] = ;
      [*] = ;   for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;   begin
      [*] = ;      var plhnd : Integer = GetPlayerHandleByIndex(i);
      [*] = ;      for j:=GetPlayerGameObjectsCountByHandle(plHnd)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var goHnd : Integer = GetGameObjectHandleByIndex(j, plhnd);
      [*] = ;         _misc_UnitRemoveMiniMapPrimitive(goHnd);
      [*] = ;         BehaviourClear(goHnd);
      [*] = ;         EffectClear(goHnd);
      [*] = ;         GameObjectRequestToDestroyByHandle(goHnd);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   // clear terrain
      [*] = ;   var r : Integer = (GetMapHeight div 2)-1;
      [*] = ;   {if BoolRegister5 then
      [*] = ;   begin
      [*] = ;      ClearPlayerGameObjectsByHandle(envplhnd);
      [*] = ;      PlateauTerrain(0, 0, False, r, True);
      [*] = ;      BoolRegister5 := not BoolRegister5;
      [*] = ;      TimeLog('Clear finished');
      [*] = ;      exit;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if not BoolRegister5 then
      [*] = ;   PaintTerrain(0, 0, 0, -1, -1, false, -1, -1, r, false, True);
      [*] = ;   BoolRegister5 := not BoolRegister5;}
      [*] = ;   MapDrawCollision(0, 0, 0, r*2-2, False);
      [*] = ;end;
      [*] = ;ClearMapMaskAndObjects;
      [*] = ;ApplicationProcessMessages;
      [*] = ;
      [*] = ;const cstartoffset = 60;
      [*] = ;const cstartoffsetrnd = 25;
      [*] = ;var arrStartPos : array [0..7] of TPos2f;
      [*] = ;var arrStartPosBusy : array [0..7] of Integer;
      [*] = ;
      [*] = ;var i : Integer;
      [*] = ;for i := 0 to 7 do
      [*] = ;arrStartPosBusy[i] := -1;
      [*] = ;
      [*] = ;var pGenerator : Integer = _misc_GetOrCreateGeneratorParser(True);
      [*] = ;var pRecordManager : Integer = ParserSelectRecordManager;
      [*] = ;var bGenRecordManager : Boolean = (ParserGetCountByHandle(pRecordManager)>0);
      [*] = ;var pRecordManagerPatternList : Integer = _misc_SelectRecordManagerPatternListParser(not bGenRecordManager);
      [*] = ;
      [*] = ;// setup tiled patterns on map
      [*] = ;procedure SetupTiles(freq : Float);
      [*] = ;begin
      [*] = ;   var needed : Integer = floor(mapW*mapH*freq);
      [*] = ;   var trycount : Integer = 64;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to needed-1 do
      [*] = ;   begin
      [*] = ;      var name : String;
      [*] = ;      _misc_GetPatternName(name, 'tls_', 4);
      [*] = ;      var j : Integer;
      [*] = ;      for j:=0 to trycount-1 do
      [*] = ;      begin
      [*] = ;         //if (j=(trycount-1)) then log('trycount '+name);
      [*] = ;         var x : Float = floor(x0+RandomExt*mapW);
      [*] = ;         var y : Float = floor(y0+RandomExt*mapH);
      [*] = ;         if (name<>'tls_3') then // hack
      [*] = ;         if (_misc_CheckStandPatternExt(envplHnd, name, x, y, True, pRecordManagerPatternList)) then
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// random starting positions
      [*] = ;procedure SetupMines(pointx, pointy : Float; minround, maxround, minesdensity, spcount : Integer);
      [*] = ;begin
      [*] = ;   var i, j, k : Integer;
      [*] = ;   var trycount : Integer = 256;
      [*] = ;   var bstand : Boolean;
      [*] = ;   var rounds : Integer;
      [*] = ;   case minesdensity of
      [*] = ;      0 : rounds := 3;
      [*] = ;      1 : rounds := 4;
      [*] = ;      2 : rounds := 5;
      [*] = ;   end;
      [*] = ;   if (maxround>0) and (rounds>maxround) then
      [*] = ;   rounds := maxround;
      [*] = ;   for i:=minround to rounds-1 do // rounds
      [*] = ;   begin
      [*] = ;      var dst : Float;
      [*] = ;      {case i of
      [*] = ;         0 : dst := 18+RandomExt*10;
      [*] = ;         1 : dst := 40+RandomExt*10;
      [*] = ;         2 : dst := 130+RandomExt*40;
      [*] = ;         3 : dst := 60+RandomExt*20;
      [*] = ;      end;}
      [*] = ;      for j:=0 to 2 do // restypes
      [*] = ;      begin
      [*] = ;         var str, name : String;
      [*] = ;         case j of
      [*] = ;            0 : str := 'mng';
      [*] = ;            1 : str := 'mni';
      [*] = ;            2 : str := 'mnc';
      [*] = ;         end;
      [*] = ;         if (bDesert) then
      [*] = ;         str := 'desert_'+str;
      [*] = ;         var pPatternList : Integer = _misc_SelectPatternListParser(pGenerator, str);
      [*] = ;         for k:=0 to trycount-1 do // mines
      [*] = ;         begin
      [*] = ;            _misc_GetPatternNameByParser(name, pPatternList);
      [*] = ;
      [*] = ;            if (gRecordGeneratorVersion<70) then
      [*] = ;            begin
      [*] = ;               case i of
      [*] = ;                  0 : dst := 14+RandomExt*8;
      [*] = ;                  1 : dst := 38+RandomExt*8;
      [*] = ;                  2 : dst := 130+RandomExt*40;
      [*] = ;                  3 : dst := 52+RandomExt*8;
      [*] = ;                  4 : dst := 26+RandomExt*5;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (gMap.settings.gen.mapsize=3) then // tiny
      [*] = ;               begin
      [*] = ;                  if (gRecordGeneratorVersion<77) then
      [*] = ;                  begin
      [*] = ;                     case i of
      [*] = ;                        0 : dst := 14+RandomExt*8;
      [*] = ;                        1 : dst := 36+RandomExt*12;
      [*] = ;                        2 : dst := 50+RandomExt*12;
      [*] = ;                        3 : dst := 22+RandomExt*16;
      [*] = ;                        4 : continue;
      [*] = ;                     end;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  if (gRecordGeneratorVersion<80) then
      [*] = ;                  begin
      [*] = ;                     case i of
      [*] = ;                        0 : dst := 14+RandomExt*8;
      [*] = ;                        1 : dst := 32+RandomExt*10;
      [*] = ;                        2 : dst := 50+RandomExt*12;
      [*] = ;                        3 : dst := 22+RandomExt*16;
      [*] = ;                        4 : continue;
      [*] = ;                     end;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  case i of
      [*] = ;                     0 : dst := 14+RandomExt*8;
      [*] = ;                     1 : dst := 32+RandomExt*10;
      [*] = ;                     2 : dst := 70+RandomExt*12;
      [*] = ;                     3 : dst := 22+RandomExt*16;
      [*] = ;                     4 : continue;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               if (spcount<=4) then
      [*] = ;               begin
      [*] = ;                  if (gRecordGeneratorVersion<75) then
      [*] = ;                  begin
      [*] = ;                     case i of
      [*] = ;                        0 : dst := 14+RandomExt*8;
      [*] = ;                        1 : dst := 36+RandomExt*12;
      [*] = ;                        2 : dst := 88+RandomExt*18;
      [*] = ;                        3 : dst := 50+RandomExt*12;
      [*] = ;                        4 : dst := 24+RandomExt*9;
      [*] = ;                     end;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  if (gRecordGeneratorVersion<77) then
      [*] = ;                  begin
      [*] = ;                     case i of
      [*] = ;                        0 : dst := 14+RandomExt*8;
      [*] = ;                        1 : dst := 36+RandomExt*12;
      [*] = ;                        3 : dst := 50+RandomExt*12;
      [*] = ;                        4 : dst := 22+RandomExt*16;
      [*] = ;                        5 : continue;
      [*] = ;                     end;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  if (gRecordGeneratorVersion<80) then
      [*] = ;                  begin
      [*] = ;                     case i of
      [*] = ;                        0 : dst := 14+RandomExt*8;
      [*] = ;                        1 : dst := 32+RandomExt*10;
      [*] = ;                        3 : dst := 50+RandomExt*12;
      [*] = ;                        4 : dst := 22+RandomExt*16;
      [*] = ;                        5 : continue;
      [*] = ;                     end;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  case i of
      [*] = ;                     0 : dst := 14+RandomExt*8;
      [*] = ;                     1 : dst := 32+RandomExt*10;
      [*] = ;                     3 : dst := 70+RandomExt*12;
      [*] = ;                     4 : dst := 22+RandomExt*16;
      [*] = ;                     5 : continue;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               case i of
      [*] = ;                  0 : dst := 14+RandomExt*6;
      [*] = ;                  1 : dst := 23+RandomExt*10;
      [*] = ;                  2 : dst := 39+RandomExt*9;
      [*] = ;                  3 : dst := 33+RandomExt*9;
      [*] = ;                  4 : continue;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            var newpointx, newpointy : Float;
      [*] = ;            if (i=2) and (spcount<=4) and (gMap.settings.gen.mapsize>2) then
      [*] = ;            begin
      [*] = ;               if (gRecordGeneratorVersion<90) then
      [*] = ;               begin
      [*] = ;                  newpointx := pointx;
      [*] = ;                  newpointy := pointy;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if (pointx<=0) and (pointy<=0) then
      [*] = ;                  begin
      [*] = ;                     newpointx := -maphW+24;
      [*] = ;                     newpointy := -maphH+24;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  if (pointx<=0) and (pointy>0) then
      [*] = ;                  begin
      [*] = ;                     newpointx := -maphW+24;
      [*] = ;                     newpointy := maphH-24;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  if (pointx>=0) and (pointy<=0) then
      [*] = ;                  begin
      [*] = ;                     newpointx := maphW-24;
      [*] = ;                     newpointy := -maphH+24;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  if (pointx>=0) and (pointy>0) then
      [*] = ;                  begin
      [*] = ;                     newpointx := maphW-24;
      [*] = ;                     newpointy := maphH-24;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     ErrorLog('SetupMines wrong position. check it');
      [*] = ;                     newpointx := pointx;
      [*] = ;                     newpointy := pointy;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               newpointx := pointx;
      [*] = ;               newpointy := pointy;
      [*] = ;            end;
      [*] = ;
      [*] = ;            var angle : Float = RandomExt*360;
      [*] = ;            var px : Float = dst;
      [*] = ;            var py : Float;
      [*] = ;            var pz : Float;
      [*] = ;            VectorRotateY(px, py, pz, angle);
      [*] = ;            if (_misc_CheckStandPatternExt(envplHnd, name, round(newpointx+px), round(newpointy+pz), True, pRecordManagerPatternList)) then
      [*] = ;            begin
      [*] = ;               _misc_PatternIncreaseFreq(pGenerator, str, name);
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// random starting positions
      [*] = ;procedure SetupStartingResources(pointx, pointy : Float);
      [*] = ;begin
      [*] = ;   var num, needcount : Integer;
      [*] = ;   var i, j : Integer;
      [*] = ;   var trycount : Integer = 128;
      [*] = ;   var trycount2 : Integer = 3;
      [*] = ;   var smalltry : Integer = 4;
      [*] = ;   var bstand : Boolean;
      [*] = ;   var name, prevname : String;
      [*] = ;   var dst : Float;
      [*] = ;   var mindst : Float = Min(cCircle1MaskX, cCircle1MaskY);
      [*] = ;
      [*] = ;   var str : String;
      [*] = ;   if (bDesert) then
      [*] = ;   begin
      [*] = ;      if (gRecordGeneratorVersion<77) then
      [*] = ;      str := 'desert_stoneforests'
      [*] = ;      else
      [*] = ;      str := 'desert_forests_big';
      [*] = ;   end
      [*] = ;   else
      [*] = ;      case foreststype of
      [*] = ;         0 : str := 'nt_mixed_stones_med'; // Default (Temperate Mixed)
      [*] = ;         1 : str := 'stoneforests'; // Taiga (Boreal/vanilla)
      [*] = ;         2 : str := 'nt_mixed_stones_med'; // Blackforest (Dense mixed)
      [*] = ;         3 : str := 'nt_mixed_stones_med'; // CountrySide (Rural)
      [*] = ;      end;
      [*] = ;   var pPatternList : Integer = _misc_SelectPatternListParser(pGenerator, str);
      [*] = ;   _misc_GetPatternNameByParser(name, pPatternList);
      [*] = ;   if (name<>'') then
      [*] = ;   begin
      [*] = ;      //_misc_GetPatternName(name, 'stf_', 3);
      [*] = ;      needcount := 1;
      [*] = ;      for num:=0 to needcount-1 do
      [*] = ;      for [MAIN]i:=0 to trycount-1 do
      [*] = ;      begin
      [*] = ;         var angle : Float = RandomExt*360;
      [*] = ;         for j:=0 to trycount2-1 do
      [*] = ;         begin
      [*] = ;            var dst : Float = mindst+RandomExt*3+((i+j)*0.5);
      [*] = ;            var px : Float = dst;
      [*] = ;            var py : Float;
      [*] = ;            var pz : Float;
      [*] = ;            VectorRotateY(px, py, pz, angle);
      [*] = ;            if (_misc_CheckStandPatternExt(envplHnd, name, round(pointx+px), round(pointy+pz), True, pRecordManagerPatternList)) then
      [*] = ;            begin
      [*] = ;               _misc_PatternIncreaseFreq(pGenerator, str, name);
      [*] = ;               prevname := name;
      [*] = ;               break(MAIN);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   _misc_FillPatternMaskElipse(pointx, pointy+2, cCircle2MaskX, cCircle2MaskY);
      [*] = ;
      [*] = ;   mindst := Min(cCircle2MaskX, cCircle2MaskY)+21; // medium far from base
      [*] = ;   if (bDesert) then
      [*] = ;   begin
      [*] = ;      if (gRecordGeneratorVersion<77) then
      [*] = ;      str := 'desert_stoneforests'
      [*] = ;      else
      [*] = ;      str := 'desert_stones';
      [*] = ;   end
      [*] = ;   else
      [*] = ;      case foreststype of
      [*] = ;         0 : str := 'nt_stones_med'; // Default (Temperate Mixed)
      [*] = ;         1 : str := 'stones'; // Taiga (Boreal/vanilla)
      [*] = ;         2 : str := 'nt_stones_med'; // Blackforest (Dense mixed)
      [*] = ;         3 : str := 'nt_stones_med'; // CountrySide (Rural)
      [*] = ;      end;
      [*] = ;   pPatternList := _misc_SelectPatternListParser(pGenerator, str);
      [*] = ;   _misc_GetPatternNameByParser(name, pPatternList);
      [*] = ;   if (name<>'') then
      [*] = ;   begin
      [*] = ;      //_misc_GetPatternName(name, 'stn_', 5);
      [*] = ;      needcount := 1;
      [*] = ;      for num:=0 to needcount-1 do
      [*] = ;      for [MAIN]i:=0 to trycount-1 do
      [*] = ;      begin
      [*] = ;         var angle : Float = RandomExt*360;
      [*] = ;         for j:=0 to trycount2-1 do
      [*] = ;         begin
      [*] = ;            var dst : Float = mindst+RandomExt*3+((i+j)*0.5);
      [*] = ;            var px : Float = dst;
      [*] = ;            var py : Float;
      [*] = ;            var pz : Float;
      [*] = ;            VectorRotateY(px, py, pz, angle);
      [*] = ;            if (_misc_CheckStandPatternExt(envplHnd, name, round(pointx+px), round(pointy+pz), True, pRecordManagerPatternList)) then
      [*] = ;            begin
      [*] = ;               _misc_PatternIncreaseFreq(pGenerator, str, name);
      [*] = ;               break(MAIN);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var rnd : Integer;
      [*] = ;   needcount := 2;
      [*] = ;   for num:=0 to needcount-1 do
      [*] = ;   begin
      [*] = ;      if (bDesert) then
      [*] = ;      begin
      [*] = ;         rnd := floor(RandomExt*2);
      [*] = ;         case rnd of
      [*] = ;            0 : str := 'desert_forests_medium';
      [*] = ;            1 : str := 'desert_forests_big';
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      case foreststype of
      [*] = ;         0 : str := 'nt_mixed_large'; // Default (Temperate Mixed)
      [*] = ;         1 : begin                    // Taiga (Boreal/vanilla)
      [*] = ;            rnd := floor(RandomExt*7);
      [*] = ;            case rnd of
      [*] = ;               0 : str := 'forests_pinefir_medium';
      [*] = ;               1 : str := 'forests_spruce_medium';
      [*] = ;               2 : str := 'forests_pine_medium';
      [*] = ;               3 : str := 'forests_pinefir_big';
      [*] = ;               4 : str := 'forests_spruce_big';
      [*] = ;               5 : str := 'forests_pine_big';
      [*] = ;               6 : str := 'forests_pine_big_2';
      [*] = ;               else
      [*] = ;               str := 'forests_pinefir_medium';
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         2 : str := 'nt_oak_bush_large'; // Blackforest (Dense mixed)
      [*] = ;         3 : str := 'nt_mixed_large';      // CountrySide (Rural)
      [*] = ;      end;
      [*] = ;      pPatternList := _misc_SelectPatternListParser(pGenerator, str);
      [*] = ;      _misc_GetPatternNameByParser(name, pPatternList);
      [*] = ;      if (name<>'') then
      [*] = ;      begin
      [*] = ;         //_misc_GetPatternName(name, 'frt_', 11);
      [*] = ;         for [MAIN]i:=0 to trycount-1 do
      [*] = ;         begin
      [*] = ;            var angle : Float = RandomExt*360;
      [*] = ;            for j:=0 to trycount2-1 do
      [*] = ;            begin
      [*] = ;               var dst : Float = mindst+RandomExt*3+((i+j)*0.5);
      [*] = ;               var px : Float = dst;
      [*] = ;               var py : Float;
      [*] = ;               var pz : Float;
      [*] = ;               VectorRotateY(px, py, pz, angle);
      [*] = ;               if (_misc_CheckStandPatternExt(envplHnd, name, round(pointx+px), round(pointy+pz), True, pRecordManagerPatternList)) then
      [*] = ;               begin
      [*] = ;                  _misc_PatternIncreaseFreq(pGenerator, str, name);
      [*] = ;                  break(MAIN);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   mindst := Min(cCircle2MaskX, cCircle2MaskY)+7; //close to base
      [*] = ;   if (bDesert) then
      [*] = ;   str := 'desert_stones'
      [*] = ;   else
      [*] = ;      case foreststype of
      [*] = ;         0 : str := 'nt_stones_med'; // Default (Temperate Mixed)
      [*] = ;         1 : str := 'stones'; // Taiga (Boreal/vanilla)
      [*] = ;         2 : str := 'nt_stones_med'; // Blackforest (Dense mixed)
      [*] = ;         3 : str := 'nt_stones_med'; // CountrySide (Rural)
      [*] = ;      end;
      [*] = ;   pPatternList := _misc_SelectPatternListParser(pGenerator, str);
      [*] = ;   _misc_GetPatternNameByParser(name, pPatternList);
      [*] = ;   if (name<>'') then
      [*] = ;   begin
      [*] = ;      //_misc_GetPatternName(name, 'stn_', 5);
      [*] = ;      needcount := 2;
      [*] = ;      for num:=0 to needcount-1 do
      [*] = ;      for [MAIN]i:=0 to trycount-1 do
      [*] = ;      begin
      [*] = ;         var angle : Float = RandomExt*360;
      [*] = ;         for j:=0 to trycount2-1 do
      [*] = ;         begin
      [*] = ;            var dst : Float = mindst+RandomExt*2+((i+j)*0.5);
      [*] = ;            var px : Float = dst;
      [*] = ;            var py : Float;
      [*] = ;            var pz : Float;
      [*] = ;            VectorRotateY(px, py, pz, angle);
      [*] = ;            if (_misc_CheckStandPatternExt(envplHnd, name, round(pointx+px), round(pointy+pz), True, pRecordManagerPatternList)) then
      [*] = ;            begin
      [*] = ;               _misc_PatternIncreaseFreq(pGenerator, str, name);
      [*] = ;               break(MAIN);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (bDesert) then
      [*] = ;   begin
      [*] = ;      rnd := floor(RandomExt*2);
      [*] = ;      case rnd of
      [*] = ;         0 : str := 'desert_forests_medium';
      [*] = ;         1 : str := 'desert_forests_big';
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   case foreststype of
      [*] = ;      0 : str := 'nt_mixed_large'; // Default (Temperate Mixed)
      [*] = ;      1 : begin                  // Taiga (Boreal/vanilla)
      [*] = ;         rnd := floor(RandomExt*7);
      [*] = ;         case rnd of
      [*] = ;            0 : str := 'forests_pinefir_medium';
      [*] = ;            1 : str := 'forests_spruce_medium';
      [*] = ;            2 : str := 'forests_pine_medium';
      [*] = ;            3 : str := 'forests_pinefir_big';
      [*] = ;            4 : str := 'forests_spruce_big';
      [*] = ;            5 : str := 'forests_pine_big';
      [*] = ;            6 : str := 'forests_pine_big_2';
      [*] = ;            else
      [*] = ;            str := 'forests_pinefir_medium';
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      2 : str := 'nt_oak_bush_large'; // Blackforest (Dense mixed)
      [*] = ;      3 : str := 'nt_mixed_large';      // CountrySide (Rural)
      [*] = ;   end;
      [*] = ;   pPatternList := _misc_SelectPatternListParser(pGenerator, str);
      [*] = ;   _misc_GetPatternNameByParser(name, pPatternList);
      [*] = ;   if (name<>'') then
      [*] = ;   begin
      [*] = ;      //_misc_GetPatternName(name, 'frt_', 11);
      [*] = ;      needcount := 1;
      [*] = ;      for num:=0 to needcount-1 do
      [*] = ;      for [MAIN]i:=0 to trycount-1 do
      [*] = ;      begin
      [*] = ;         var angle : Float = RandomExt*360;
      [*] = ;         for j:=0 to trycount2-1 do
      [*] = ;         begin
      [*] = ;            var dst : Float = mindst+RandomExt*2+((i+j)*0.5);
      [*] = ;            var px : Float = dst;
      [*] = ;            var py : Float;
      [*] = ;            var pz : Float;
      [*] = ;            VectorRotateY(px, py, pz, angle);
      [*] = ;            if (_misc_CheckStandPatternExt(envplHnd, name, round(pointx+px), round(pointy+pz), True, pRecordManagerPatternList)) then
      [*] = ;            begin
      [*] = ;               _misc_PatternIncreaseFreq(pGenerator, str, name);
      [*] = ;               break(MAIN);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   mindst := Min(cCircle2MaskX, cCircle2MaskY)+26; // furthest from base
      [*] = ;   if (bDesert) then
      [*] = ;   str := 'desert_stones'
      [*] = ;   else
      [*] = ;      case foreststype of
      [*] = ;         0 : str := 'nt_stones_med'; // Default (Temperate Mixed)
      [*] = ;         1 : str := 'stones'; // Taiga (Boreal/vanilla)
      [*] = ;         2 : str := 'nt_stones_med'; // Blackforest (Dense mixed)
      [*] = ;         3 : str := 'nt_stones_med'; // CountrySide (Rural)
      [*] = ;      end;
      [*] = ;   pPatternList := _misc_SelectPatternListParser(pGenerator, str);
      [*] = ;   _misc_GetPatternNameByParser(name, pPatternList);
      [*] = ;   if (name<>'') then
      [*] = ;   begin
      [*] = ;      needcount := 1;
      [*] = ;      for num:=0 to needcount-1 do
      [*] = ;      for [MAIN]i:=0 to trycount-1 do
      [*] = ;      begin
      [*] = ;         var angle : Float = RandomExt*360;
      [*] = ;         for j:=0 to trycount2-1 do
      [*] = ;         begin
      [*] = ;            var dst : Float = mindst+RandomExt*2+((i+j)*0.5);
      [*] = ;            var px : Float = dst;
      [*] = ;            var py : Float;
      [*] = ;            var pz : Float;
      [*] = ;            VectorRotateY(px, py, pz, angle);
      [*] = ;            if (_misc_CheckStandPatternExt(envplHnd, name, round(pointx+px), round(pointy+pz), True, pRecordManagerPatternList)) then
      [*] = ;            begin
      [*] = ;               _misc_PatternIncreaseFreq(pGenerator, str, name);
      [*] = ;               break(MAIN);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   _misc_FillPatternMaskElipse(pointx, pointy+2, cCircle3MaskX, cCircle3MaskY);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CreateStartPoint(plInd : Integer; pointx, pointy : Float; minesdensity, spcount : Integer);
      [*] = ;begin
      [*] = ;   if (not bGenRecordManager) then
      [*] = ;   begin
      [*] = ;      _misc_FillPatternMaskElipse(pointx, pointy+2, cCircle1MaskX, cCircle1MaskY);
      [*] = ;      SetupMines(pointx, pointy, 0, 1, minesdensity, spcount);
      [*] = ;      SetupStartingResources(pointx, pointy);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetRandom(const n : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := floor(RandomExt * n);
      [*] = ;end;
      [*] = ;function GetRandomRange(const min, max : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := min + floor(RandomExt * (max - min + 1));
      [*] = ;end;
      [*] = ;//Формируем список ближайших точек points в количестве count, исключая точки pointsbusy
      [*] = ;procedure GenerateTeamStartingPoints(const count : Integer; var pointsbusy, points : TIntegerList);
      [*] = ;begin
      [*] = ;   var i, j : Integer;
      [*] = ;   var pointlast : Integer = 8;//Последняя доступная точка
      [*] = ;   //Находим последнюю доступную точку
      [*] = ;   for i := 0 to 7 do
      [*] = ;   begin
      [*] = ;      if (arrStartPos[i].x=0) and (arrStartPos[i].y=0) then
      [*] = ;      begin
      [*] = ;         pointlast := i;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //Формируем список оставшихся точек
      [*] = ;   var pointsremained : TIntegerList;
      [*] = ;   for i:=0 to pointlast-1 do
      [*] = ;   if (pointsbusy.IndexOf(i)=-1) then
      [*] = ;   pointsremained.Add(i);
      [*] = ;
      [*] = ;   points.Add(pointsremained.Get(GetRandom(pointsremained.GetCount)));//Выбираем первую случайную точку
      [*] = ;
      [*] = ;   //Ищем остальные точки
      [*] = ;   var point1, point2 : Integer;
      [*] = ;   var dist : Float;
      [*] = ;   var c : Integer;
      [*] = ;   for c:=2 to count do
      [*] = ;   begin
      [*] = ;      var pointsnearest : TIntegerList;//Список ближайших точек к найденным точкам
      [*] = ;      var pointsnearestcount : array [0..7] of Integer;//Список количества ближайших точек к найденным точкам
      [*] = ;      var pointsnearestdist : array [0..7] of Float;//Список расстояний ближайших точек к найденным точкам
      [*] = ;
      [*] = ;      //Для каждой уже найденной точке, находим ближайшую точку именно к ней
      [*] = ;      for i:=0 to points.GetCount-1 do
      [*] = ;      begin
      [*] = ;         point1 := points.Get(i);
      [*] = ;         dist := 0;
      [*] = ;
      [*] = ;         var x1 : Float = arrStartPos[point1].x;
      [*] = ;         var y1 : Float = arrStartPos[point1].y;
      [*] = ;
      [*] = ;         for j:=0 to pointlast-1 do
      [*] = ;         begin
      [*] = ;            if (pointsbusy.IndexOf(j) > -1) or (points.IndexOf(j) > -1) then //Исключаем занятые точки и найденные новые точки
      [*] = ;            continue;
      [*] = ;
      [*] = ;            var x2 : Float = arrStartPos[j].x;
      [*] = ;            var y2 : Float = arrStartPos[j].y;
      [*] = ;
      [*] = ;            var d : Float = VectorDistance(x1, y1, 0, x2, y2, 0);
      [*] = ;
      [*] = ;            if (dist = 0) or (dist > d) then
      [*] = ;            begin
      [*] = ;               point2 := j;
      [*] = ;               dist := d;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var pointindex : Integer = pointsnearest.IndexOf(point2);//Получаем индекс точки
      [*] = ;         if (pointindex=-1) then //Если точки ещё нет в списке
      [*] = ;         begin
      [*] = ;            pointsnearest.Add(point2);
      [*] = ;            pointindex := pointsnearest.IndexOf(point2);
      [*] = ;            pointsnearestcount[pointindex] := 1;
      [*] = ;            pointsnearestdist[pointindex] := dist;
      [*] = ;         end
      [*] = ;         else //Иначе если точка уже есть в списке, увеличиваем счетчик  и суммируем расстояние
      [*] = ;         begin
      [*] = ;            pointsnearestcount[pointindex] := pointsnearestcount[pointindex] + 1;
      [*] = ;            pointsnearestdist[pointindex] := pointsnearestdist[pointindex] + dist;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      //Выбираем наиближайшую точку
      [*] = ;      var pointindex, pointcount : Integer;
      [*] = ;      for i:=0 to pointsnearest.GetCount-1 do
      [*] = ;      begin
      [*] = ;         if (pointcount<pointsnearestcount[i]) then
      [*] = ;         begin
      [*] = ;            pointindex := i;
      [*] = ;            pointcount := pointsnearestcount[i];
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if (pointcount=pointsnearestcount[i]) and (pointsnearestdist[pointindex] > pointsnearestdist[i]) then
      [*] = ;         pointindex := i;
      [*] = ;      end;
      [*] = ;
      [*] = ;      points.Add(pointsnearest.Get(pointindex));
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure RandomStartingPoints(plcount, minesdensity : Integer);
      [*] = ;begin
      [*] = ;   var i, j : Integer;
      [*] = ;   if gRecordGeneratorVersion<61 then // preserve compatibility with old replays
      [*] = ;   begin
      [*] = ;      var maxind : Integer = plcount-1;
      [*] = ;      for i:=0 to gc_MaxPlayerCount-1 do // fix with gDataVersion=44
      [*] = ;      begin
      [*] = ;         if (gMap.players[i].bexists) and (gMap.players[i].cid<>gc_spectator_countryid) then
      [*] = ;         begin
      [*] = ;            SetRandomKey(gMap.settings.gen.randkey1);
      [*] = ;            for j:=0 to i-1 do
      [*] = ;            RandomExt;
      [*] = ;            var newind : Integer;
      [*] = ;            var rndind : Integer = floor(RandomExt*(maxind+1));
      [*] = ;            var j : Integer;
      [*] = ;            for j:=0 to maxind do
      [*] = ;            begin
      [*] = ;               newind := rndind+j;
      [*] = ;               if (newind>maxind) then
      [*] = ;               newind := newind-maxind-1;
      [*] = ;               if (arrStartPosBusy[newind] = -1) then
      [*] = ;               begin
      [*] = ;                  ApplicationProcessMessages;
      [*] = ;                  CreateStartPoint(i, arrStartPos[newind].x, arrStartPos[newind].y, minesdensity, plcount);
      [*] = ;                  arrStartPosBusy[newind] := i;
      [*] = ;                  gMap.players[i].startx := arrStartPos[newind].x;
      [*] = ;                  gMap.players[i].starty := arrStartPos[newind].y;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else // support spawn allies nearby option
      [*] = ;   begin
      [*] = ;      //Создаем массив команд, где 0 это команда для безкомандных игроков, а с 1 по 4 включительно это уже команды
      [*] = ;      var teams : array [0..4] of TIntegerList;
      [*] = ;      var pointsbusy : TIntegerList;//Список занятых точек
      [*] = ;
      [*] = ;      //Если выбрана опция расположения союзников рядом
      [*] = ;      if (gMap.settings.additional.teams=gc_mapsettings_teams_nearby) then
      [*] = ;      begin
      [*] = ;         //Запоминаем какой игрок в какой команде
      [*] = ;         for i := 0 to gc_MaxPlayerCount - 1 do
      [*] = ;         if (gMap.players[i].bexists) and (gMap.players[i].cid<>gc_spectator_countryid) then
      [*] = ;         begin
      [*] = ;            if gMap.players[i].team>4 then
      [*] = ;            teams[0].Add(i)
      [*] = ;            else
      [*] = ;            teams[gMap.players[i].team].Add(i);
      [*] = ;         end;
      [*] = ;
      [*] = ;         //Формируем список команд, где есть хоть 2 человек в команде, исключая игроков не в команде
      [*] = ;         var teamlist : TIntegerList;
      [*] = ;         for i := 1 to 4 do
      [*] = ;         begin
      [*] = ;            if (teams[i].GetCount>1) then
      [*] = ;            teamlist.Add(i)
      [*] = ;            else
      [*] = ;            if (teams[i].GetCount=1) then //Если в команде только 1 игрок, тогда запихиваем его в команду для без командных игроков
      [*] = ;            begin
      [*] = ;               teams[0].Add(teams[i].Get(0));
      [*] = ;               teams[i].Clear();
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         //Теперь для каждой команды находим ближайшие точки и раздаем их игрокам
      [*] = ;         var teamscount : Integer = teamlist.GetCount;
      [*] = ;         for i:=1 to teamscount do
      [*] = ;         begin
      [*] = ;            SetRandomKey(gMap.settings.gen.randkey1);
      [*] = ;            for j:=0 to i-1 do
      [*] = ;            RandomExt;
      [*] = ;            var teamindex : Integer = GetRandom(teamlist.GetCount);//Получаем случайный индекс команды
      [*] = ;            var team : Integer = teamlist.Get(teamindex);//Получаем номер команды
      [*] = ;            teamlist.Delete(teamindex);//Удаляем команду из списка
      [*] = ;            var teamcount : Integer = teams[team].GetCount;//Получаем количество игроков в команде
      [*] = ;            var points : TIntegerList;//Список ближайших точек для команды
      [*] = ;            GenerateTeamStartingPoints(teamcount, pointsbusy, points);//Получаем ближайшие точки для команды
      [*] = ;            //Количество найденных точек должно ровняться количеству игроков в команде, т.е. teamcount = points.GetCount
      [*] = ;
      [*] = ;            //В случайном порядке раздаем точки игрокам команды
      [*] = ;            for j:=0 to teamcount-1 do
      [*] = ;            begin
      [*] = ;               if gRecordGeneratorVersion>77 then
      [*] = ;               begin
      [*] = ;                  SetRandomKey(gMap.settings.gen.randkey1);
      [*] = ;                  var k : Integer;
      [*] = ;                  for k:=0 to j do
      [*] = ;                  RandomExt;
      [*] = ;               end;
      [*] = ;               var pointindex : Integer = GetRandom(points.GetCount);//Получаем случайный индекс точки
      [*] = ;               var point : Integer = points.Get(pointindex);//Получаем точку
      [*] = ;               pointsbusy.Add(point);//Полученную точку заносим в список занятых точек
      [*] = ;               points.Delete(pointindex);//Удаляем точку из списка
      [*] = ;
      [*] = ;               var player : Integer = teams[team].Get(j);//Получаем игрока
      [*] = ;               //Устанавливаем игроку стартовую точку, а в точке сохроняем за каким игроком она занята
      [*] = ;               ApplicationProcessMessages;
      [*] = ;               CreateStartPoint(player, arrStartPos[point].x, arrStartPos[point].y, minesdensity, plcount);
      [*] = ;               arrStartPosBusy[point] := player;
      [*] = ;               gMap.players[player].startx := arrStartPos[point].x;
      [*] = ;               gMap.players[player].starty := arrStartPos[point].y;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else //Если игроков раскидываем по разным точкам, тогда всех игроков запихиваем в безкомандную команду
      [*] = ;      begin
      [*] = ;         for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;         if (gMap.players[i].bexists) and (gMap.players[i].cid<>gc_spectator_countryid) then
      [*] = ;         teams[0].Add(i);
      [*] = ;      end;
      [*] = ;
      [*] = ;      //Формируем список оставшихся точек
      [*] = ;      var pointsremained : TIntegerList;
      [*] = ;      for i := 0 to plcount - 1 do
      [*] = ;      if (pointsbusy.IndexOf(i)=-1) then
      [*] = ;      pointsremained.Add(i);
      [*] = ;
      [*] = ;      //Теперь оставшиеся точки раздаем игрокам без команды
      [*] = ;      for i := 0 to teams[0].GetCount - 1 do
      [*] = ;      begin
      [*] = ;         SetRandomKey(gMap.settings.gen.randkey1);
      [*] = ;         for j:=0 to i+8 do
      [*] = ;         RandomExt;
      [*] = ;         var pointindex : Integer = GetRandom(pointsremained.GetCount);//Получаем случайный индекс точки
      [*] = ;         var point : Integer = pointsremained.Get(pointindex);//Получаем точку
      [*] = ;         pointsremained.Delete(pointindex);//Удаляем точку из списка
      [*] = ;
      [*] = ;         var player : Integer = teams[0].Get(i);//Получаем игрока
      [*] = ;         //Устанавливаем игроку стартовую точку, а в точке сохроняем за каким игроком она занята
      [*] = ;         ApplicationProcessMessages;
      [*] = ;         CreateStartPoint(player, arrStartPos[point].x, arrStartPos[point].y, minesdensity, plcount);
      [*] = ;         arrStartPosBusy[point] := player;
      [*] = ;         gMap.players[player].startx := arrStartPos[point].x;
      [*] = ;         gMap.players[player].starty := arrStartPos[point].y;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CreateStartPointPeasants(plInd : Integer; pointx, pointy : Float);
      [*] = ;begin
      [*] = ;   var cid : Integer = gMap.players[plInd].cid;
      [*] = ;   if (cid>=0) and (gMap.players[plInd].bexists) then
      [*] = ;   begin
      [*] = ;      var peasantBaseName : String;
      [*] = ;      var id : Integer;
      [*] = ;      for id:=1 to gc_country_maxmembers-1 do
      [*] = ;      begin
      [*] = ;         var member : String = gCountry[cid].members[id];
      [*] = ;         if (member<>'') then
      [*] = ;         begin
      [*] = ;            if (gObjProp[cid][id].usage=gc_obj_usage_peasant) then
      [*] = ;            begin
      [*] = ;               peasantBaseName := member;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if (peasantBaseName<>'') then
      [*] = ;      begin
      [*] = ;         var plHnd : Integer = GetPlayerHandleByIndex(plInd);
      [*] = ;         var goHnd : Integer;
      [*] = ;         var px, py, pz : Float;
      [*] = ;         var count : Integer = 18;
      [*] = ;         px := pointx;
      [*] = ;         pz := pointy;
      [*] = ;         const cUnitR = 0.75;
      [*] = ;         var i : Integer;
      [*] = ;         for i:=0 to count-1 do
      [*] = ;         begin
      [*] = ;            px := pointx+(i div 3)*cUnitR+(0.5-RandomExt)*0.25-(((count div 3)*cUnitR)/2);
      [*] = ;            pz := pointy+(i mod 3)*cUnitR+(0.5-RandomExt)*0.25-(((count mod 3)*cUnitR)/2);
      [*] = ;            gint_unit_parentcid := cid;
      [*] = ;            goHnd := CreatePlayerGameObjectHandleByHandle(plHnd, gc_racename_units, peasantBaseName, px, py, pz);
      [*] = ;            SetGameObjectRollAngleByHandle(goHnd, 180);
      [*] = ;         end;
      [*] = ;         for i:=GetGameObjectCountChildByHandle(goHnd)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var childHnd : Integer = GetGameObjectGOHandleChildByHandle(goHnd, i);
      [*] = ;            if (childHnd<>0) then
      [*] = ;            begin
      [*] = ;               var lodactor : String = GetGameObjectLODActorNameByHandle(childHnd);
      [*] = ;               ProjectLoadLodActor(lodactor);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      Log(GetCurrentStateName+' peasantBaseName=none');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;//setup mines / forest / stone near start point
      [*] = ;_gui_ProcessProgressBar(GetLocaleTableListItemByID('misc', 'progressbar.loadingenvironment'), 0, 0, True);
      [*] = ;
      [*] = ;LoadPatterns(True, False);
      [*] = ;ApplicationProcessMessages;
      [*] = ;LoadPatterns(True, True);
      [*] = ;ApplicationProcessMessages;
      [*] = ;
      [*] = ;var plcount : Integer;
      [*] = ;for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;begin
      [*] = ;   if (gMap.players[i].bexists) and (gMap.players[i].cid<>gc_spectator_countryid) then
      [*] = ;   plcount := plcount+1;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetupCollisionInertiaObjects(bBuildings : Boolean);
      [*] = ;begin
      [*] = ;   var tag : Integer;
      [*] = ;   if (bBuildings) then
      [*] = ;   tag := 80
      [*] = ;   else
      [*] = ;   tag := 101;
      [*] = ;   var i, j : Integer;
      [*] = ;   if (GetCountOfPlayers>=gc_playerind_misc) then
      [*] = ;   begin
      [*] = ;      var plHnd : Integer = GetPlayerHandleByIndex(gc_playerind_misc);
      [*] = ;      for i:=-GetMapWidth to GetMapWidth do
      [*] = ;      for j:=-GetMapHeight to GetMapHeight do
      [*] = ;      begin
      [*] = ;         var x : Float = i/2;
      [*] = ;         var z : Float = j/2;
      [*] = ;         if (GetMapCollisionTag(x, z, bBuildings)=tag) then
      [*] = ;         begin
      [*] = ;            x := x+0.25;
      [*] = ;            z := z+0.25;
      [*] = ;            var goHnd : Integer = CreatePlayerGameObjectHandleByHandle(plHnd, gc_racename_misc, 'collision', x, 0, z);
      [*] = ;            SetGameObjectCIIntersectRadiusByHandle(goHnd, 0);
      [*] = ;            SetGameObjectPositionByHandle(goHnd, x, 0, z);
      [*] = ;            var scale : Float = GetGameObjectScaleXByHandle(goHnd)*0.001;
      [*] = ;            SetGameObjectScaleByHandle(goHnd, scale, scale, 0.1*scale);
      [*] = ;            SetGameObjectCIIntersectRadiusByHandle(goHnd, 0.2);
      [*] = ;            SetGameObjectCIMassByHandle(goHnd, 1);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetupTiledPatterns(const str : String);
      [*] = ;begin
      [*] = ;   var pPatternList : Integer = _misc_SelectPatternListParser(pGenerator, str);
      [*] = ;   if (pPatternList<>0) then
      [*] = ;   begin
      [*] = ;      const cSize = 25;
      [*] = ;      var wcount : Integer = floor(mapW/cSize);
      [*] = ;      var hcount : Integer = floor(mapH/cSize);
      [*] = ;      var x, y : Integer;
      [*] = ;      for y:=0 to hcount do
      [*] = ;      for x:=0 to wcount do
      [*] = ;      begin
      [*] = ;         var name : String;
      [*] = ;         _misc_GetPatternNameByParser(name, pPatternList);
      [*] = ;         var realx : Float = round((x*cSize)+(cSize div 2)-(GetMapWidth div 2)-1);
      [*] = ;         var realy : Float = round((y*cSize)+(cSize div 2)-(GetMapHeight div 2)-1);
      [*] = ;         if (name<>'') then
      [*] = ;         begin
      [*] = ;            //_misc_CheckStandPattern(name, envplHnd, realx, realy, 0, True, True, pRecordManagerPatternList);
      [*] = ;            _misc_CheckStandPattern(name, envplHnd, realx, realy, 0, True, False, 0);
      [*] = ;            //if (_misc_CheckStandPatternExt(name, realx, realy)) then
      [*] = ;            _misc_PatternIncreaseFreq(pGenerator, str, name);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         ErrorLog('name='+name+' realx='+FloatToStr(realx)+' realy='+FloatToStr(realy));
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   Log('SetupTiledPatterns : wrong str = '+str);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CheckOwnerDist(i, j, dist, owner : Integer);
      [*] = ;begin
      [*] = ;   if gScanGrid[i, j].dist < 0 then
      [*] = ;   begin
      [*] = ;      gScanGrid[i, j].dist := dist+1;
      [*] = ;      gScanGrid[i, j].owner := owner;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure FillOwnerMap(const spCount : Integer);
      [*] = ;begin
      [*] = ;   var i, j, i1, j1 : Integer;
      [*] = ;   for i := 0 to gc_scangrid_countx-1 do
      [*] = ;   for j := 0 to gc_scangrid_county-1 do
      [*] = ;   begin
      [*] = ;      gScanGrid[i, j].fChecked := false;
      [*] = ;      gScanGrid[i, j].owner := -1;
      [*] = ;      gScanGrid[i, j].dist := -1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i := 0 to spCount-1 do
      [*] = ;   begin
      [*] = ;      var gridX, gridY : Integer;
      [*] = ;      if _misc_PosToScanGridIndices(arrStartPos[i].x, arrStartPos[i].y, gridX, gridY) then
      [*] = ;      begin
      [*] = ;         gScanGrid[gridX, gridY].owner := arrStartPosBusy[i];
      [*] = ;         gScanGrid[gridX, gridY].dist := 0;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var f : Boolean = true;
      [*] = ;   var minI, maxI : Integer;
      [*] = ;   var minJ, maxJ : Integer;
      [*] = ;   var dist, owner : Integer;
      [*] = ;   while f do
      [*] = ;   begin
      [*] = ;      f := false;
      [*] = ;      for i := 0 to gc_scangrid_countx-1 do
      [*] = ;      for j := 0 to gc_scangrid_county-1 do
      [*] = ;      if (gScanGrid[i, j].dist = dist) and (not gScanGrid[i, j].fChecked) then
      [*] = ;      begin
      [*] = ;         owner := gScanGrid[i, j].owner;
      [*] = ;
      [*] = ;         if i > 0 then
      [*] = ;         CheckOwnerDist(i-1, j, dist, owner);
      [*] = ;         if i < gc_scangrid_countx-1 then
      [*] = ;         CheckOwnerDist(i+1, j, dist, owner);
      [*] = ;
      [*] = ;         if j > 0 then
      [*] = ;         CheckOwnerDist(i, j-1, dist, owner);
      [*] = ;         if j < gc_scangrid_county-1 then
      [*] = ;         CheckOwnerDist(i, j+1, dist, owner);
      [*] = ;
      [*] = ;         gScanGrid[i, j].fChecked := true;
      [*] = ;         f := true;
      [*] = ;      end;
      [*] = ;
      [*] = ;      dist := dist+1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   {for i := 0 to gc_scangrid_countx-1 do
      [*] = ;   begin
      [*] = ;      gScanGrid[i, 0].owner := -2;
      [*] = ;      gScanGrid[i, gc_scangrid_county-1].owner := -2;
      [*] = ;      gScanGrid[0, i].owner := -2;
      [*] = ;      gScanGrid[gc_scangrid_county-1, i].owner := -2;
      [*] = ;   end;{}
      [*] = ;end;
      [*] = ;//Peace Time Borders
      [*] = ;procedure SetupBorderObjects;
      [*] = ;begin
      [*] = ;   var i, j, k : Integer;
      [*] = ;   var plHnd : Integer = GetPlayerHandleByIndex(gc_playerind_misc);
      [*] = ;   for i := 0 to gc_scangrid_countx-1 do
      [*] = ;   for j := 0 to gc_scangrid_county-1 do
      [*] = ;   begin
      [*] = ;      if (i < gc_scangrid_countx-1) and (gScanGrid[i, j].owner <> gScanGrid[i+1, j].owner) then
      [*] = ;      begin
      [*] = ;         var x, z0, z1 : Float;
      [*] = ;         _misc_ScanGridIndicesToPos(i+0.5, j-0.5, x, z0);
      [*] = ;         _misc_ScanGridIndicesToPos(i+0.5, j+0.5, x, z1);
      [*] = ;
      [*] = ;         var count : Integer = MathCeil(Abs(z1-z0) / cBorderObjDist);
      [*] = ;         var dist : Float = (z1-z0) / count;
      [*] = ;
      [*] = ;         var minInd, maxInd : Integer;
      [*] = ;         if j = 0 then
      [*] = ;         minInd := 1
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if gScanGrid[i, j-1].owner <> gScanGrid[i+1, j-1].owner then
      [*] = ;            minInd := 1
      [*] = ;            else
      [*] = ;            minInd := 0;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if j = gc_scangrid_county-1 then
      [*] = ;         maxInd := count-1
      [*] = ;         else
      [*] = ;         maxInd := count;
      [*] = ;
      [*] = ;         for k := minInd to maxInd do
      [*] = ;         begin
      [*] = ;            var z : Float = z0 + k * dist;
      [*] = ;            if (Abs(x)<(GetMapWidth div 2)) and (Abs(z)<(GetMapHeight div 2)) then
      [*] = ;            begin
      [*] = ;               var hnd : Integer;
      [*] = ;               if GetMapCollisionTag(x, z, false) = gc_collisiontag_water then
      [*] = ;               hnd := CreatePlayerGameObjectHandleByHandle(plHnd, gc_racename_misc, gc_basename_ptborderwater, x, 0, z)
      [*] = ;               else
      [*] = ;               hnd := CreatePlayerGameObjectHandleByHandle(plHnd, gc_racename_misc, gc_basename_ptborder, x, 0, z);
      [*] = ;               GameObjectMakeUniqId(hnd);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (j < gc_scangrid_county-1) and (gScanGrid[i, j].owner <> gScanGrid[i, j+1].owner) then
      [*] = ;      begin
      [*] = ;         var x0, x1, z : Float;
      [*] = ;         _misc_ScanGridIndicesToPos(i-0.5, j+0.5, x0, z);
      [*] = ;         _misc_ScanGridIndicesToPos(i+0.5, j+0.5, x1, z);
      [*] = ;
      [*] = ;         var count : Integer = MathCeil(Abs(x1-x0) / cBorderObjDist);
      [*] = ;         var dist : Float = (x1-x0) / count;
      [*] = ;
      [*] = ;         var minInd, maxInd : Integer;
      [*] = ;         if i = 0 then
      [*] = ;         minInd := 1
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if gScanGrid[i-1, j].owner <> gScanGrid[i-1, j+1].owner then
      [*] = ;            minInd := 1
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (gScanGrid[i-1, j].owner <> gScanGrid[i, j].owner) or (gScanGrid[i-1, j+1].owner <> gScanGrid[i, j+1].owner) then
      [*] = ;               minInd := 1
      [*] = ;               else
      [*] = ;               minInd := 0;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if i = gc_scangrid_countx-1 then
      [*] = ;         maxInd := count-1
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if (gScanGrid[i, j].owner <> gScanGrid[i+1, j].owner) or (gScanGrid[i, j+1].owner <> gScanGrid[i+1, j+1].owner) then
      [*] = ;            maxInd := count-1
      [*] = ;            else
      [*] = ;            maxInd := count;
      [*] = ;         end;
      [*] = ;
      [*] = ;         for k := minInd to maxInd do
      [*] = ;         begin
      [*] = ;            var x : Float = x0 + k * dist;
      [*] = ;            if (Abs(x)<(GetMapWidth div 2)) and (Abs(z)<(GetMapHeight div 2)) then
      [*] = ;            begin
      [*] = ;               var hnd : Integer;
      [*] = ;               if GetMapCollisionTag(x, z, false) = gc_collisiontag_water then
      [*] = ;               hnd := CreatePlayerGameObjectHandleByHandle(plHnd, gc_racename_misc, gc_basename_ptborderwater, x, 0, z)
      [*] = ;               else
      [*] = ;               hnd := CreatePlayerGameObjectHandleByHandle(plHnd, gc_racename_misc, gc_basename_ptborder, x, 0, z);
      [*] = ;               GameObjectMakeUniqId(hnd);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;//if (not bGenRecordManager) then
      [*] = ;begin
      [*] = ;   ApplicationProcessMessages;
      [*] = ;   if (bDesert) then
      [*] = ;   SetupTiledPatterns('desert_tiles')
      [*] = ;   else
      [*] = ;   SetupTiledPatterns('tiles');
      [*] = ;end;
      [*] = ;//RELIEF GENERATION
      [*] = ;SetRandomKey(gMap.settings.gen.randkey1);
      [*] = ;
      [*] = ;_gui_ProcessProgressBar(GetLocaleTableListItemByID('misc', 'progressbar.generatingterrain'), 0, 0, True);
      [*] = ;
      [*] = ;var relieftype : Integer = gMap.settings.gen.relieftype;
      [*] = ;var terraintype : Integer = gMap.settings.gen.terraintype;
      [*] = ;var minesdensity : Integer = gMap.settings.gen.resourcemines;
      [*] = ;
      [*] = ;var pTerrainTypes : Integer;
      [*] = ;if (gRecordGeneratorVersion<91) then
      [*] = ;begin
      [*] = ;   pTerrainTypes := ParserSelectByHandleByKey(pGenerator, 'TerrainTypes');
      [*] = ;   if (terraintype>gc_MaxTerrainTypeCount-1) then // random
      [*] = ;   terraintype := floor(RandomExt*6);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   pTerrainTypes := ParserSelectByHandleByKey(pGenerator, 'TerrainTypesDLC5');
      [*] = ;   if (terraintype>gc_MaxTerrainTypeCount-1) then // random
      [*] = ;   terraintype := floor(RandomExt*gc_MaxTerrainTypeCount);
      [*] = ;end;
      [*] = ;
      [*] = ;var pTerrainType : Integer = ParserSelectByHandleByIndex(pTerrainTypes, terraintype);
      [*] = ;var path : String = ParserGetValueByKeyByHandle(pTerrainType, 'path');
      [*] = ;
      [*] = ;BoolRegister0 := True;
      [*] = ;StringRegister0 := path;
      [*] = ;ExecuteState('GenerateMap');
      [*] = ;ApplicationProcessMessages;
      [*] = ;
      [*] = ;var x, y : Integer;
      [*] = ;for y:=0 to mapH-1 do
      [*] = ;for x:=0 to mapW-1 do
      [*] = ;begin
      [*] = ;   if (not gPatternMask[x, y]) then
      [*] = ;   begin
      [*] = ;      var realx : Integer = floor(x0+x);
      [*] = ;      var realy : Integer = floor(y0+y);
      [*] = ;      const cWaterShoreHeight = -0.1;
      [*] = ;      var height : Float = GetHeightData(realx, realy);
      [*] = ;      if (height<cWaterShoreHeight) then
      [*] = ;      gPatternMask[x, y] := True; // bWaterShore := True;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// PATTERN MODIFIER VARS - moved these all together here so its more clear.
      [*] = ;ApplicationProcessMessages;
      [*] = ;var probsmall, probmid, problarge, probhuge : Float;
      [*] = ;var pln_small, pln_mid, pln_large, pln_huge : Float;
      [*] = ;var swamp_big, swamp_medium, swamp_small, lake_big, lake_small : Float;
      [*] = ;var plt, mnt, hil, plain : Float;
      [*] = ;var frs_big : Float;
      [*] = ;var frs_mid : Float;
      [*] = ;var frs_small : Float;
      [*] = ;var dcr : Float;
      [*] = ;var stn1 : Float;
      [*] = ;var stn2 : Float;
      [*] = ;var nt_mixed_small : Float;
      [*] = ;var nt_mixed_med : Float;
      [*] = ;var nt_mixed_large : Float;
      [*] = ;var nt_oak_bush_small : Float;
      [*] = ;var nt_oak_bush_med : Float;
      [*] = ;var nt_oak_bush_large : Float;
      [*] = ;var nt_dcr_med : Float;
      [*] = ;var nt_plain_large : Float;
      [*] = ;var nt_plain_med : Float;
      [*] = ;var nt_plain_small : Float;
      [*] = ;var nt_hill_light_med : Float;
      [*] = ;var nt_hill_dark_small : Float;
      [*] = ;var nt_plat_dark_small : Float;
      [*] = ;var nt_plat_high_large : Float;
      [*] = ;var nt_plat_high_med : Float;
      [*] = ;var nt_plat_dark_med : Float;
      [*] = ;var nt_dark_for_large : Float;
      [*] = ;var nt_farm_small : Float;
      [*] = ;var nt_rav_med : Float;
      [*] = ;var nt_dcr_rubble : Float; 
      [*] = ;var nt_dcr_var : Float; //various: graveyards,churches & castles
      [*] = ;var nt_birds : Float; 
      [*] = ;_misc_GetFreePatternMaskModifier(probsmall, probmid, problarge, probhuge);
      [*] = ;// SEE MISC.SCRIPT 3844
      [*] = ;if (mapW<>640) or (mapH<>640) then
      [*] = ;begin
      [*] = ;   var modifier : Float = (640/((mapW+mapH)/2));
      [*] = ;   probsmall := probsmall*modifier;
      [*] = ;   probmid := probmid*modifier;
      [*] = ;   problarge := problarge*modifier;
      [*] = ;   probhuge := probhuge*modifier;
      [*] = ;end;
      [*] = ;// MINES
      [*] = ;if (minesdensity>2) then // random
      [*] = ;minesdensity := floor(RandomExt*3);
      [*] = ;
      [*] = ;if (bDesert) then
      [*] = ;_misc_SetDesert(False, False); // bRemoveEnv, bModifyHeight
      [*] = ;
      [*] = ;//if (not bGenRecordManager) then;
      [*] = ;//SetupTiles(0.002);
      [*] = ;_gui_ProcessProgressBar(GetLocaleTableListItemByID('misc', 'progressbar.setupstartingpoints'), 0, 0, True);
      [*] = ;
      [*] = ;//START UNITS
      [*] = ;var spcount : Integer;
      [*] = ;for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;begin
      [*] = ;   if (gMap.players[i].startx>=(-GetMapWidth div 2)) and (gMap.players[i].starty>=(-GetMapHeight div 2)) then
      [*] = ;   begin
      [*] = ;      arrStartPos[i].x := gMap.players[i].startx;
      [*] = ;      arrStartPos[i].y := gMap.players[i].starty;
      [*] = ;      spcount := spcount+1;
      [*] = ;
      [*] = ;      if (gMap.settings.additional.startingunits>gc_mapsettings_startingunits_default) then
      [*] = ;      begin
      [*] = ;         CreateUniqueStartingUnits(i, True);
      [*] = ;         ApplicationProcessMessages;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_misc_FillPatternMaskMapBorder(3);
      [*] = ;ApplicationProcessMessages;
      [*] = ;RandomStartingPoints(spcount, minesdensity);
      [*] = ;SetRandomKey(gMap.settings.gen.randkey1);
      [*] = ;
      [*] = ;// cache common content
      [*] = ;_gui_ProcessProgressBar(GetLocaleTableListItemByID('misc', 'progressbar.preparingstartingpoints'), 0, 0, True);
      [*] = ;
      [*] = ;if (relieftype>4) then // random
      [*] = ;relieftype := floor(RandomExt*5);
      [*] = ;// Changed this to have better control over each relieftype -Ebel
      [*] = ;case relieftype of
      [*] = ;   0 : begin // PLAINS
      [*] = ;      //ForestsType:1 - Taiga (Vanilla)
      [*] = ;      plain := 0.0001/2;
      [*] = ;      pln_small := 0.00005*6*probsmall;
      [*] = ;      pln_mid := 0.00005*2*probmid;
      [*] = ;      pln_large := 0.00005*problarge;
      [*] = ;      pln_huge := 0.00005*probhuge;
      [*] = ;      swamp_big := 0.00005*problarge;
      [*] = ;      swamp_medium := 0.00005*2*probmid;
      [*] = ;      swamp_small := 0.00005*6*probsmall;
      [*] = ;      frs_big := 0.0005*probsmall; // reduced amt of trees on plains a bit, giving more space for mills, buildings, etc
      [*] = ;      frs_mid := 0.0005*probmid;
      [*] = ;      frs_small := 0.00022*problarge;
      [*] = ;      stn1 := 0.00002*probsmall; // not too much random stones,else it leads to one player have much more stone than another. I put more in the 'fixed' gen in procedure SetupStartingResources
      [*] = ;      stn2 := 0.00003*probsmall;
      [*] = ;      dcr := 0.0005*probsmall;
      [*] = ;      //ForestsType:0 - Temperate Mixed (Default)
      [*] = ;      nt_plain_large := 0.0009*probsmall;
      [*] = ;      nt_plain_med := 0.00080*problarge;
      [*] = ;      nt_mixed_small := 0.0005*probsmall; // new nt mix trees
      [*] = ;      nt_mixed_med := 0.0005*probmid;
      [*] = ;      nt_mixed_large := 0.00075*probmid;
      [*] = ;      nt_oak_bush_small := 0.0005*probsmall;
      [*] = ;      nt_oak_bush_med := 0.0005*probmid;
      [*] = ;      nt_oak_bush_large := 0.00072*probmid;
      [*] = ;      nt_dcr_med := 0.0009*probsmall;
      [*] = ;      //ForestsType:2 - DarkForest (Dense)
      [*] = ;      nt_dark_for_large := 0.00105*problarge;
      [*] = ;      nt_plain_small := 0.00060*problarge;
      [*] = ;      //ForestsType:3 - CountrySide (Farms)
      [*] = ;      nt_farm_small := 0.00070*problarge;
      [*] = ;      nt_dcr_rubble := 0.00050*probsmall;
      [*] = ;      nt_dcr_var := 0.00050*probsmall;
      [*] = ;      nt_birds := 0.00015*probmid;
      [*] = ;   end;
      [*] = ;   1 : begin // LOW MOUNTAINS (Hills)
      [*] = ;      //ForestsType:1 - Taiga (Vanilla)
      [*] = ;      //plt := 0.000020*problarge;
      [*] = ;      //mnt := 0.000002*problarge;
      [*] = ;      hil := 0.00125*problarge;
      [*] = ;      plain := 0.0001/2;
      [*] = ;      pln_small := 0.00005*6*probsmall;
      [*] = ;      pln_mid := 0.00005*2*probmid;
      [*] = ;      pln_large := 0.00005*problarge;
      [*] = ;      pln_huge := 0.00005*probhuge;
      [*] = ;      swamp_big := 0.00005*problarge;
      [*] = ;      swamp_medium := 0.00005*2*probmid;
      [*] = ;      swamp_small := 0.00005*6*probsmall;
      [*] = ;      frs_big := 0.0006*probsmall;
      [*] = ;      frs_mid := 0.0006*probmid;
      [*] = ;      frs_small := 0.00032*problarge;
      [*] = ;      stn1 := 0.00002*probsmall;
      [*] = ;      stn2 := 0.00003*probsmall;
      [*] = ;      dcr := 0.0005*probsmall;
      [*] = ;      //ForestsType:0 - Temperate Mixed (Default)
      [*] = ;      nt_hill_light_med := 0.00125*probmid;
      [*] = ;      nt_hill_dark_small := 0.00125*probmid;
      [*] = ;      nt_mixed_small := 0.0005*probsmall; // new nt mix trees
      [*] = ;      nt_mixed_med := 0.0005*probmid;
      [*] = ;      nt_mixed_large := 0.00075*probmid;
      [*] = ;      nt_oak_bush_small := 0.0005*probsmall;
      [*] = ;      nt_oak_bush_med := 0.0005*probmid;
      [*] = ;      nt_oak_bush_large := 0.00072*probmid;
      [*] = ;      nt_dcr_med := 0.0009*probsmall;
      [*] = ;      //ForestsType:2 - DarkForest (Dense)
      [*] = ;      nt_dark_for_large := 0.00105*probmid;
      [*] = ;      //ForestsType:3 - CountrySide (Farms)
      [*] = ;      nt_farm_small := 0.00060*problarge;
      [*] = ;      nt_dcr_rubble := 0.00040*probsmall;
      [*] = ;      nt_dcr_var := 0.00040*probsmall;
      [*] = ;      nt_birds := 0.000015*probmid;
      [*] = ;   end;
      [*] = ;   2 : begin // HIGH MOUNTAINS
      [*] = ;      //ForestsType:1 - Taiga (Vanilla)
      [*] = ;      plt := 0.000075*problarge;
      [*] = ;      mnt := 0.000075*problarge;
      [*] = ;      hil := 0.000030*problarge;
      [*] = ;      plain := 0.0001/2;
      [*] = ;      pln_small := 0.00005*6*probsmall;
      [*] = ;      pln_mid := 0.00005*2*probmid;
      [*] = ;      pln_large := 0.00005*problarge;
      [*] = ;      pln_huge := 0.00005*probhuge;
      [*] = ;      frs_big := 0.0009*probsmall;
      [*] = ;      frs_mid := 0.0009*probmid;
      [*] = ;      frs_small := 0.00054*problarge;
      [*] = ;      stn1 := 0.00002*probsmall;
      [*] = ;      stn2 := 0.00003*probsmall;
      [*] = ;      dcr := 0.0005*probsmall;
      [*] = ;      //ForestsType:0 - Temperate Mixed (Default)
      [*] = ;      nt_plat_high_large := 0.00090*problarge;
      [*] = ;      nt_plat_high_med := 0.00095*probmid;
      [*] = ;      nt_hill_light_med := 0.000105*probmid;
      [*] = ;      nt_plat_dark_small := 0.00105*probsmall;
      [*] = ;      nt_plat_dark_med := 0.00105*probmid;
      [*] = ;      nt_mixed_small := 0.0005*probsmall; // new nt mix trees
      [*] = ;      nt_mixed_med := 0.0005*probmid;
      [*] = ;      nt_mixed_large := 0.00075*probmid;
      [*] = ;      nt_oak_bush_small := 0.0005*probsmall;
      [*] = ;      nt_oak_bush_med := 0.0005*probmid;
      [*] = ;      nt_oak_bush_large := 0.00072*probmid;
      [*] = ;      nt_dcr_med := 0.0009*probsmall;
      [*] = ;      //ForestsType:2 - DarkForest (Dense)
      [*] = ;      nt_dark_for_large := 0.00105*probmid;
      [*] = ;      //ForestsType:3 - CountrySide (Farms)
      [*] = ;      nt_farm_small := 0.00050*problarge;
      [*] = ;      nt_dcr_rubble := 0.00040*probsmall;
      [*] = ;      nt_dcr_var := 0.00040*probsmall;
      [*] = ;      nt_birds := 0.000015*probmid;
      [*] = ;   end;
      [*] = ;   3 : begin // HIGHLANDS
      [*] = ;      //ForestsType:1 - Taiga (Vanilla)
      [*] = ;      plt := 0.000055*problarge;
      [*] = ;      mnt := 0.000120*problarge;
      [*] = ;      hil := 0.000050*problarge;
      [*] = ;      plain := 0.0001/2;
      [*] = ;      pln_small := 0.00005*6*probsmall;
      [*] = ;      pln_mid := 0.00005*2*probmid;
      [*] = ;      pln_large := 0.00005*problarge;
      [*] = ;      pln_huge := 0.00005*probhuge;
      [*] = ;      swamp_big := 0.00003*problarge;
      [*] = ;      swamp_medium := 0.00003*2*probmid;
      [*] = ;      swamp_small := 0.00003*6*probsmall;
      [*] = ;      frs_big := 0.0009*probsmall;
      [*] = ;      frs_mid := 0.0009*probmid;
      [*] = ;      frs_small := 0.00054*problarge;
      [*] = ;      stn1 := 0.00002*probsmall;
      [*] = ;      stn2 := 0.00003*probsmall;
      [*] = ;      dcr := 0.0005*probsmall;
      [*] = ;      //ForestsType:0 - Temperate Mixed (Default)
      [*] = ;      nt_rav_med := 0.00090*problarge;
      [*] = ;      nt_plat_high_med := 0.00060*probmid;
      [*] = ;      nt_hill_dark_small := 0.00090*probmid;
      [*] = ;      nt_plat_dark_small := 0.00090*probsmall;
      [*] = ;      nt_mixed_small := 0.0005*probsmall; // new nt mix trees
      [*] = ;      nt_mixed_med := 0.0005*probmid;
      [*] = ;      nt_mixed_large := 0.00075*probmid;
      [*] = ;      nt_oak_bush_small := 0.0005*probsmall;
      [*] = ;      nt_oak_bush_med := 0.0005*probmid;
      [*] = ;      nt_oak_bush_large := 0.00072*probmid;
      [*] = ;      nt_dcr_med := 0.0009*probsmall;
      [*] = ;      //ForestsType:2 - DarkForest (Dense)
      [*] = ;      nt_dark_for_large := 0.00105*probmid;
      [*] = ;      //ForestsType:3 - CountrySide (Farms)
      [*] = ;      nt_farm_small := 0.00050*problarge;
      [*] = ;      nt_dcr_rubble := 0.00040*probsmall;
      [*] = ;      nt_dcr_var := 0.00040*probsmall;
      [*] = ;      nt_birds := 0.000015*probmid;
      [*] = ;   end;
      [*] = ;   4 : begin // PLATEAUS
      [*] = ;      //ForestsType:1 - Taiga (Vanilla)
      [*] = ;      plt := 0.00090*problarge;
      [*] = ;      //mnt := 0.000035*problarge;
      [*] = ;      hil := 0.000035*problarge;
      [*] = ;      plain := 0.0001/2;
      [*] = ;      pln_small := 0.00005*3*probsmall;
      [*] = ;      pln_mid := 0.00005*2*probmid;
      [*] = ;      pln_large := 0.00005*problarge;
      [*] = ;      pln_huge := 0.00003*probhuge;
      [*] = ;      frs_big := 0.0009*probsmall;
      [*] = ;      frs_mid := 0.0009*probmid;
      [*] = ;      frs_small := 0.00054*problarge;
      [*] = ;      stn1 := 0.00002*probsmall;
      [*] = ;      stn2 := 0.00003*probsmall;
      [*] = ;      dcr := 0.0005*probsmall;
      [*] = ;      //ForestsType:0 - Temperate Mixed (Default)
      [*] = ;      nt_plat_high_large := 0.00090*probmid;
      [*] = ;      nt_plat_high_med := 0.00090*probmid;
      [*] = ;      nt_hill_light_med := 0.000090*probmid;
      [*] = ;      nt_plat_dark_small := 0.00090*probsmall;
      [*] = ;      nt_plat_dark_med := 0.00080*probmid;
      [*] = ;      nt_mixed_small := 0.0005*probsmall; // new nt mix trees
      [*] = ;      nt_mixed_med := 0.0005*probmid;
      [*] = ;      nt_mixed_large := 0.00075*probmid;
      [*] = ;      nt_oak_bush_small := 0.0005*probsmall;
      [*] = ;      nt_oak_bush_med := 0.0006*probmid;
      [*] = ;      nt_oak_bush_large := 0.00072*probmid;
      [*] = ;      nt_dcr_med := 0.0009*probsmall;
      [*] = ;      //ForestsType:2 - DarkForest (Dense)
      [*] = ;      nt_dark_for_large := 0.00105*probmid;
      [*] = ;      //ForestsType:3 - CountrySide (Farms)
      [*] = ;      nt_farm_small := 0.00050*problarge;
      [*] = ;      nt_dcr_rubble := 0.00040*probsmall;
      [*] = ;      nt_dcr_var := 0.00030*probsmall;
      [*] = ;      nt_birds := 0.000015*probmid;
      [*] = ;   end;
      [*] = ;   5 : begin // Desert
      [*] = ;      plain := 0.0001/2;
      [*] = ;      lake_big := plain*2;
      [*] = ;      lake_small := plain*0.01;
      [*] = ;      frs_big := 0.0005*probsmall/2;
      [*] = ;      frs_mid := 0.0005*probmid/2;
      [*] = ;      frs_small := frs_small/2;
      [*] = ;      mnt := 0.000010*problarge;
      [*] = ;      plt := 0.000030*problarge;
      [*] = ;      pln_small := 0.00005*6*probsmall;
      [*] = ;      pln_mid := 0.00005*2*probmid;
      [*] = ;      pln_large := 0.00005*problarge;
      [*] = ;      pln_huge := 0.00005*probhuge;
      [*] = ;      hil := 0.000125*problarge;
      [*] = ;      stn1 := 0.00003*probsmall;
      [*] = ;      stn2 := 0.00004*probsmall;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;ApplicationProcessMessages;
      [*] = ;
      [*] = ;var maxProgress : Integer;
      [*] = ;var curprogress : Integer;
      [*] = ;if (not bGenRecordManager) then
      [*] = ;begin
      [*] = ;   _gui_ProcessProgressBar(GetLocaleTableListItemByID('misc', 'progressbar.generatingmountainsandhills'), 0, 0, True);
      [*] = ;
      [*] = ;   if bDesert then
      [*] = ;   begin
      [*] = ;      _misc_SetupPatternsByType(pGenerator, envplHnd, 'desert_mountains', mnt);
      [*] = ;      _misc_SetupPatternsByType(pGenerator, envplHnd, 'desert_plateau_big', plt/3);
      [*] = ;      _misc_SetupPatternsByType(pGenerator, envplHnd, 'desert_plain_big', pln_huge);
      [*] = ;      _misc_SetupPatternsByType(pGenerator, envplHnd, 'desert_plateau', plt/3);
      [*] = ;      _misc_SetupPatternsByType(pGenerator, envplHnd, 'desert_plateau_small', plt/3);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      case foreststype of
      [*] = ;         0 : begin // Default (Temperate Mixed)
      [*] = ;           //_misc_SetupPatternsByType(pGenerator, envplHnd, 'mountains', mnt); //todo for highlands
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_plain_large', nt_plain_large); //plains
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_rav_med', nt_rav_med); //highlands
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_plat_high_large', nt_plat_high_large/1.5); //plateaus
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_plat_dark_med', nt_plat_dark_med/1.5); //plateaus/higlands
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_plat_dark_small', nt_plat_dark_small/1.5); //plateaus
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_plat_high_med', nt_plat_high_med/1.5); //plateaus
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_hill_light_med', nt_hill_light_med); //low mountains
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_hill_dark_small', nt_hill_dark_small); //low mountains/higlands
      [*] = ;           //_misc_SetupPatternsByType(pGenerator, envplHnd, 'ravine_big', plt/1.5); //Need to redo these with larger patternmask or conditional to not spawn on river/lake maps. Water placement is terrible!
      [*] = ;         end;
      [*] = ;         1 : begin // Taiga (Boreal/vanilla)
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'mountains', mnt);
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'plateau_big', plt/3);
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'plain_huge', pln_huge);
      [*] = ;           //_misc_SetupPatternsByType(pGenerator, envplHnd, 'ravine_medium'{'ravine_big'}, plt/3); // sand ravine
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'ravine_big', plt/1.5);
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'plateau', plt/3);
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'plateau_small', plt/3);
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'hills_dark', hil/2);
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'hills_light', hil/2);
      [*] = ;         end;
      [*] = ;         2 : begin // Blackforest (Dense mixed)
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_rav_med', nt_rav_med/3); //highlands
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_plat_dark_med', nt_plat_dark_med/3); //plateaus/higlands
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_plat_dark_small', nt_plat_dark_small/3); //plateaus
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_plat_high_med', nt_plat_high_med/3); //plateaus
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_dark_for_hill_med', nt_hill_light_med/3); //low mountains - has more trees
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_dark_for_large', nt_dark_for_large);
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_dark_for_med_ani', nt_oak_bush_med/1.5); 
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_hill_dark_small', nt_hill_dark_small/3); //low mountains/higlands
      [*] = ;         end;
      [*] = ;         3 : begin // CountrySide (Rural)
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_plain_large', nt_plain_large); //plains
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_rav_med', nt_rav_med/2); //highlands
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_plat_high_large', nt_plat_high_large/2); //plateaus
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_plat_dark_med', nt_plat_dark_med/2); //plateaus+higlands
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_plat_dark_small', nt_plat_dark_small/2); //plateaus
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_plat_high_med', nt_plat_high_med/2); //plateaus
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_hill_light_med', nt_hill_light_med); //low mountains
      [*] = ;           _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_hill_dark_small', nt_hill_dark_small/2); //low mountains/higlands
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   _gui_ProcessProgressBar(GetLocaleTableListItemByID('misc', 'progressbar.generatingmines'), 0, 0, True);
      [*] = ;   for i:=0 to spcount-1 do
      [*] = ;   SetupMines(arrStartPos[i].x, arrStartPos[i].y, 1, 0, minesdensity, spcount);
      [*] = ;end;
      [*] = ;SetRandomKey(gMap.settings.gen.randkey1);
      [*] = ;
      [*] = ;_gui_ProcessProgressBar(GetLocaleTableListItemByID('misc', 'progressbar.generatingforestsandstones'), 0, 0, True);
      [*] = ;if (bGenRecordManager) then
      [*] = ;begin
      [*] = ;   for i:=0 to ParserGetCountByHandle(pRecordManagerPatternList)-1 do
      [*] = ;   begin
      [*] = ;      var pPattern : Integer = ParserSelectByHandleByIndex(pRecordManagerPatternList, i);
      [*] = ;      var name : String = ParserGetValueByKeyByHandle(pPattern, 'n');
      [*] = ;      var x : Float = ParserGetFloatValueByKeyByHandle(pPattern, 'x');
      [*] = ;      var y : Float = ParserGetFloatValueByKeyByHandle(pPattern, 'y');
      [*] = ;      _misc_CheckStandPattern(name, envplHnd, x, y, 0, True, False, 0);
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if bDesert then
      [*] = ;   begin
      [*] = ;      _misc_SetupPatternsByType(pGenerator, envplHnd, 'desert_forests_big', frs_big/4);
      [*] = ;      _misc_SetupPatternsByType(pGenerator, envplHnd, 'desert_forests_medium', frs_big/4);
      [*] = ;      _misc_SetupPatternsByType(pGenerator, envplHnd, 'desert_stones', stn1);
      [*] = ;      _misc_SetupPatternsByType(pGenerator, envplHnd, 'desert_lake', lake_big);
      [*] = ;      _misc_SetupPatternsByType(pGenerator, envplHnd, 'desert_plain_big', pln_large);
      [*] = ;      _misc_SetupPatternsByType(pGenerator, envplHnd, 'desert_plain_medium', pln_mid); //desert_plain_medium was a non existant pattern group. Fixed in generator.cfg -Ebel.
      [*] = ;      _misc_SetupPatternsByType(pGenerator, envplHnd, 'desert_forests_big', frs_mid/6);
      [*] = ;      _misc_SetupPatternsByType(pGenerator, envplHnd, 'desert_forests_medium', frs_mid/6);
      [*] = ;      _misc_SetupPatternsByType(pGenerator, envplHnd, 'desert_forests_unique', frs_mid/6);
      [*] = ;      _misc_SetupPatternsByType(pGenerator, envplHnd, 'desert_stones', stn2);
      [*] = ;      _misc_SetupPatternsByType(pGenerator, envplHnd, 'desert_plain_big', pln_large);
      [*] = ;      _misc_SetupPatternsByType(pGenerator, envplHnd, 'desert_plain_medium', pln_mid);
      [*] = ;      _misc_SetupPatternsByType(pGenerator, envplHnd, 'desert_forests_small', frs_small/2);
      [*] = ;      _misc_SetupPatternsByType(pGenerator, envplHnd, 'desert_plain_small', pln_small);
      [*] = ;      _misc_SetupPatternsByType(pGenerator, envplHnd, 'desert_forests_big', frs_big/8);
      [*] = ;      _misc_SetupPatternsByType(pGenerator, envplHnd, 'desert_forests_medium', frs_big/8);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      case foreststype of
      [*] = ;         0 : begin // Default (Temperate Mixed)
      [*] = ;            if (gc_halloween>0) and (GetSeasonType<>2) then // not winter
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'pump', pln_small*4);
      [*] = ;            if gc_christmas>0 then
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'christmas', pln_small*2);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_plain_large', pln_large);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_plain_med', pln_mid);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_plain_small', pln_small);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_stones_med', stn1);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_stones_small', stn2);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_plain_large', pln_large);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_plain_med', pln_mid);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_mixed_small', nt_mixed_small/6);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_mixed_med', nt_mixed_med/6);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_mixed_large', nt_mixed_med);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_oak_bush_small', nt_oak_bush_small/6);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_oak_bush_med', nt_oak_bush_med/6);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_oak_bush_large', nt_oak_bush_med/2);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_dcr_med', nt_dcr_med/2);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_dcr_rubble', nt_dcr_rubble);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_birds', nt_birds*2);
      [*] = ;         end;
      [*] = ;         1 : begin // Taiga (Boreal/vanilla)
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'forests_pinefir_big', frs_big/8);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'forests_spruce_big', frs_big/8);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'forests_pine_big', frs_big/8);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'forests_pine_big_2', frs_big/8);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'stones', stn1);
      [*] = ;            if (gc_halloween>0) and (GetSeasonType<>2) then // not winter
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'pump', pln_small*4);
      [*] = ;            if gc_christmas>0 then
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'christmas', pln_small*2);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'plain_big', pln_large);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'plain_medium', pln_mid);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'plain_small', pln_small);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'forests_spruce_medium', frs_mid/6);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'forests_pinefir_medium', frs_mid/6);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'forests_pine_medium', frs_mid/6);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'stones', stn2);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'plain_big', pln_large);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'plain_medium', pln_mid);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'forests_pinefir_small', frs_small/4);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'forests_pine_small', frs_small/4);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'swamp_big', swamp_big);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'swamp_medium', swamp_medium);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'swamp_small', swamp_small);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_birds', nt_birds*2);
      [*] = ;         end;
      [*] = ;         2 : begin // Blackforest (Dense mixed)
      [*] = ;            if (gc_halloween>0) and (GetSeasonType<>2) then // not winter
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'pump', pln_small*4);
      [*] = ;            if gc_christmas>0 then
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'christmas', pln_small*2);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_dark_for_large', nt_dark_for_large);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_stones_med', stn1/2);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_dark_for_large', nt_dark_for_large);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_dark_for_med_ani', nt_oak_bush_med/1.5);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_mixed_small', nt_mixed_small/3);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_mixed_med', nt_mixed_med/3);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_mixed_large', nt_mixed_med/1.5);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_dark_for_large', nt_dark_for_large);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_oak_bush_small', nt_oak_bush_small);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_birds', nt_birds*2);
      [*] = ;         end;
      [*] = ;         3 : begin // CountrySide (Rural)
      [*] = ;            if (gc_halloween>0) and (GetSeasonType<>2) then // not winter
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'pump', pln_small*4);
      [*] = ;            if gc_christmas>0 then
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'christmas', pln_small*2);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_farm_small', nt_farm_small);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_dcr_var', nt_dcr_var);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_plain_large', pln_large);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_plain_med', pln_mid);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_plain_small', pln_small);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_stones_med', stn1);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_stones_small', stn2);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_farm_small', nt_farm_small);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_dcr_rubble', nt_dcr_rubble);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_mixed_small', nt_mixed_small/6);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_mixed_med', nt_mixed_med/2);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_dcr_med', nt_dcr_med/2);
      [*] = ;            _misc_SetupPatternsByType(pGenerator, envplHnd, 'nt_birds', nt_birds*1.5);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;SetRandomKey(gMap.settings.gen.randkey1);
      [*] = ;
      [*] = ;gMap.lastenvuid := GetMapNextUniqId-1;
      [*] = ;
      [*] = ;ApplicationProcessMessages;
      [*] = ;for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;begin
      [*] = ;   if (gMap.players[i].bexists) and (gMap.players[i].cid>=0) then
      [*] = ;   begin
      [*] = ;      if (gMap.settings.additional.startingunits>gc_mapsettings_startingunits_default) then
      [*] = ;      CreateUniqueStartingUnits(i, False)
      [*] = ;      else
      [*] = ;      CreateStartPointPeasants(i, gMap.players[i].startx, gMap.players[i].starty);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;ApplicationProcessMessages;
      [*] = ;_misc_PreloadTextures(True, True, True);
      [*] = ;ApplicationProcessMessages;
      [*] = ;SetRandomKey(gMap.settings.gen.randkey1);
      [*] = ;
      [*] = ;//SetupCollisionInertiaObjects(False); // Optimize. Check FPS on map with this objects and without. you'll find difference. try to setup collision properties to get better performance}
      [*] = ;
      [*] = ;gbool_gui_mapgenerationfinished := True;
      [*] = ;
      [*] = ;{
      [*] = ;// _misc_UnitCreateMiniMapPrimitive
      [*] = ;//
      [*] = ;function _misc_MineCreateMiniMapPrimitive(goHnd : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var primHnd : Integer = CreateGUIMiniMapPrimitive('pl2x2.4');
      [*] = ;   SetGUIMiniMapPrimitivePosition(primHnd, GetGameObjectPositionXByHandle(goHnd), GetGameObjectPositionZByHandle(goHnd));
      [*] = ;end;
      [*] = ;}
      [*] = ;ApplicationProcessMessages;
      [*] = ;{if (GetSeasonType=2) then // winter
      [*] = ;begin
      [*] = ;   var tile : Integer = MapGetTileIndexByTileBlock('grass1_winter');
      [*] = ;   var alpha : Integer = MapGetTileIndexByTileBlock('alpha0b');
      [*] = ;   var x, y : Integer;
      [*] = ;   for y:=0 to GetMapHeight do
      [*] = ;   for x:=0 to GetMapWidth do
      [*] = ;   begin
      [*] = ;      var name : String = GetTileName(x, y);
      [*] = ;      if (StrPos('_winter', name)=0) then
      [*] = ;      begin
      [*] = ;         if (StrPos('alpha', name)>0) then
      [*] = ;         SetTileIndex(x, y, alpha)
      [*] = ;         else
      [*] = ;         SetTileIndex(x, y, tile);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;}
      [*] = ;
      [*] = ;ApplicationProcessMessages;
      [*] = ;for i:=GetPlayerGameObjectsCountByHandle(envplhnd)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var goHnd : Integer = GetGameObjectHandleByIndex(i, envplhnd);
      [*] = ;   var basename : String = GetGameObjectBaseNameByHandle(goHnd);
      [*] = ;   if (GetSeasonType=2) then // winter
      [*] = ;   begin
      [*] = ;      if StrExists(basename, 'leaftree') then
      [*] = ;      begin
      [*] = ;         GameObjectRequestToDestroyByHandle(goHnd);
      [*] = ;         continue;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if StrExists(basename, 'terrainmesh') or (StrExists(basename, 'stones')) then
      [*] = ;   continue;
      [*] = ;   var scale : Float = GetGameObjectScaleXByHandle(goHnd);
      [*] = ;
      [*] = ;   var x, y, z, minfact, maxfact, deffact : Float;
      [*] = ;   var rand : Boolean;
      [*] = ;   GetGameObjectDefScalePropsByHandle(goHnd, x, y, z, rand, minfact, maxfact, deffact);
      [*] = ;   var scaleMid, scaleMin, scaleMax : Float;
      [*] = ;   if (rand) then
      [*] = ;   begin
      [*] = ;      scaleMin := x*minfact;
      [*] = ;      scaleMid := x*((minfact+maxfact)/2);
      [*] = ;      scaleMax := x*maxfact;
      [*] = ;
      [*] = ;      if ((Abs(scaleMax-scaleMin))>scaleMid*0.05) then
      [*] = ;      begin
      [*] = ;         if (scale<scaleMin) then
      [*] = ;         begin
      [*] = ;            {const cDiffKoefMin = 0.875;
      [*] = ;            const cDiffKoefMax = 0.95;
      [*] = ;            var koef : Float = (scaleMin/scaleMid)*(cDiffKoefMin+random*(cDiffKoefMax-cDiffKoefMin));
      [*] = ;            var newscale : Float = scaleMid*koef;}
      [*] = ;            var newscale : Float = scaleMin+(scaleMid-scaleMin)*random;
      [*] = ;            if (newscale<scale) then
      [*] = ;            newscale := scale;
      [*] = ;            SetGameObjectScaleByHandle(goHnd, newscale, newscale, newscale);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if (scale>scaleMax) then
      [*] = ;         begin
      [*] = ;            {const cDiffKoefMin = 1.04;
      [*] = ;            const cDiffKoefMax = 1.08;
      [*] = ;            var koef : Float = (scaleMax/scaleMid)*(cDiffKoefMin+random*(cDiffKoefMax-cDiffKoefMin));
      [*] = ;            var newscale : Float = scaleMid*koef;}
      [*] = ;            var newscale : Float = scaleMid+(scaleMax-scaleMid)*random;
      [*] = ;            if (newscale>scale) then
      [*] = ;            newscale := scale;
      [*] = ;            SetGameObjectScaleByHandle(goHnd, newscale, newscale, newscale);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if (z<>x) then
      [*] = ;   SetGameObjectScaleByHandle(goHnd, GetGameObjectScaleXByHandle(goHnd), GetGameObjectScaleYByHandle(goHnd), GetGameObjectScaleZByHandle(goHnd)*(z/x));
      [*] = ;end;
      [*] = ;ApplicationProcessMessages;
      [*] = ;
      [*] = ;// setup AI params
      [*] = ;var ind : Integer;
      [*] = ;var count : Integer = 1;
      [*] = ;for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;if (gMap.players[i].bai) then
      [*] = ;count := count+1;
      [*] = ;
      [*] = ;for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;begin
      [*] = ;   gPlayer[i].bai := gMap.players[i].bai;
      [*] = ;   gPlayer[i].aidata.centerfound := false;
      [*] = ;   gPlayer[i].aidata.basenation := gMap.players[i].cid;
      [*] = ;   const cProgressAITick = 16;
      [*] = ;   if (i=0) or (gPlayer[i].bai) then
      [*] = ;   begin
      [*] = ;      gPlayer[i].progressTick := (cProgressAITick div count)*ind;
      [*] = ;      ind := ind+1;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   gPlayer[i].progressTick := i*2;
      [*] = ;end;
      [*] = ;
      [*] = ;_player_SetupTeams(true);
      [*] = ;
      [*] = ;gbool_editor_peacemode := False;
      [*] = ;//_misc_FixEnvironmentObjectsScales(False); // optimize first
      [*] = ;//ParserSaveToFileByHandle(pGenerator, 'lastgen');
      [*] = ;
      [*] = ;//_misc_CreateBorders;
      [*] = ;gfloat_peacetime := _misc_GetPeaceTime(gMap.settings.additional.peacetime);
      [*] = ;gbool_peacemode := (gMap.settings.additional.peacetime<>gc_mapsettings_peacetime_default);
      [*] = ;ApplicationProcessMessages;
      [*] = ;FillOwnerMap(spcount);
      [*] = ;ApplicationProcessMessages;
      [*] = ;if (gbool_peacemode) then
      [*] = ;SetupBorderObjects;
      [*] = ;
      [*] = ;ApplicationProcessMessages;
      [*] = ;_misc_SetShoresCollision;
      [*] = ;ApplicationProcessMessages;
      [*] = ;_misc_FixCollisionInertiaObjectsInOnePoint;
      [*] = ;ApplicationProcessMessages;
      [*] = ;
      [*] = ;_gui_ProcessProgressBar(GetLocaleTableListItemByID('misc', 'progressbar.lastpreparations'), 0, 0, True);
      [*] = ;//Colour Tables in data\env\colors\colors.lib - Also see docreate.inc & onloadfull.inc
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
      [*] = ;
      [*] = ;//if (gc_christmas>0) then
      [*] = ;//SetCurrentColorTableIndex(5);
      [*] = ;{
      [*] = ;var irn : Integer = Floor(random*4);
      [*] = ;var lid : String = 'light'+IntToStr(irn);
      [*] = ;//SetLightPattern(lid);
      [*] = ;if (gc_halloween>0) then
      [*] = ;SetCurrentColorTableIndex(5)
      [*] = ;else begin
      [*] = ;   irn := Floor(random*5);
      [*] = ;   SetCurrentColorTableIndex(irn);
      [*] = ;end;
      [*] = ;Log('LightPattern: '+lid+'; 'CurrentColor: '+IntToStr(GetCurrentColorTableIndex));
      [*] = ;//SetCloudsVisible(False);}
      [*] = ;
      [*] = ;TimeLog('Generation finished. EbelsTestv1.6.0.3 - Seasontype='+IntToStr(GetSeasonType)+ ' relieftype='+IntToStr(relieftype)+' minesdensity='+IntToStr(minesdensity)+' foreststype='+IntToStr(foreststype)+ ' terraintype='+IntToStr(terraintype));
   struct.end
section.end

