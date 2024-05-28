section.begin
   Name = ProgressEconomicAI
   Code : struct.begin
      [*] = ;gPlayer[GetPlayerIndexByHandle(GetPlayerCurrentPlHandle)].aidata.ailist.Clear;
      [*] = ;
      [*] = ;//nation's consts
      [*] = ;const cid_aus = 0;
      [*] = ;const cid_fra = 1;
      [*] = ;const cid_eng = 2;
      [*] = ;const cid_spa = 3;
      [*] = ;const cid_rus = 4;
      [*] = ;const cid_ukr = 5;
      [*] = ;const cid_pol = 6;
      [*] = ;const cid_swe = 7;
      [*] = ;const cid_pru = 8;
      [*] = ;const cid_ven = 9;
      [*] = ;const cid_tur = 10;
      [*] = ;const cid_alg = 11;
      [*] = ;const cid_mis = 12;
      [*] = ;const cid_net = 13;
      [*] = ;const cid_den = 14;
      [*] = ;const cid_por = 15;
      [*] = ;const cid_pie = 16;
      [*] = ;const cid_sax = 17;
      [*] = ;const cid_bav = 18;
      [*] = ;const cid_hun = 19;
      [*] = ;const cid_swi = 20;
      [*] = ;const cid_sco = 21;
      [*] = ;const cid_rom = 22;
      [*] = ;const cid_lit = 23;
      [*] = ;
      [*] = ;const ai_st_res_normal = 0;
      [*] = ;const ai_st_res_thousands = 2;
      [*] = ;const ai_st_res_millions = 3; //
      [*] = ;
      [*] = ;var ordered_cannon_count, ordered_mortar_count, ordered_howitzer_count, ordered_storehouse_count : Integer;
      [*] = ;var countofficers17, countofficers18, countdrummers17, countdrummers18 : Integer;
      [*] = ;var plhnd : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var plind : Integer = GetPlayerIndexByHandle(plhnd);
      [*] = ;var bai : Boolean = gPlayer[plInd].bai;
      [*] = ;var difficulty : Integer;
      [*] = ;if bai then
      [*] = ;difficulty := gPlayer[plInd].difficulty
      [*] = ;else
      [*] = ;difficulty := gc_player_difficulty_impossible;
      [*] = ;var bAdviseProduceOfficers : Boolean = ((not bai) and gPlayer[plind].playeradviser.adviser.benable and gPlayer[plind].playeradviser.adviser.bquartermaster and gPlayer[plind].playeradviser.adviser.bproduceofficers);
      [*] = ;gbool_gui_updateadviseradvice := True;
      [*] = ;gPlayer[plind].playeradviser.buildings.Clear;
      [*] = ;gPlayer[plind].playeradviser.upgradeseconomy.Clear;
      [*] = ;gPlayer[plind].playeradviser.upgradesmilitary.Clear;
      [*] = ;
      [*] = ;// Need Lan Client Execute, cause of Advicer advices
      [*] = ;var bprocess : Boolean = (not _net_IsClient) and (not _net_IsReplay);
      [*] = ;
      [*] = ;var bIsWaterMap : Boolean = _misc_IsWaterMap;
      [*] = ;var bWaterScenario : Boolean;
      [*] = ;if (gScenario.bactive) then
      [*] = ;begin
      [*] = ;   case gMap.name of
      [*] = ;      'scemis10', 'netmis2', 'netmis5' : begin // hard code
      [*] = ;         bWaterScenario := True;
      [*] = ;         bIsWaterMap := True;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_GetRandomEnemy(const plIndex : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := -1;
      [*] = ;   var count : Integer;
      [*] = ;   var i, b : Integer;
      [*] = ;   for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;   begin
      [*] = ;      var enemymask : Integer = gPlayer[i].myplmask;
      [*] = ;      if ((i <> plIndex) and (gPlayer[i].bExists) and (((enemymask and gPlayer[plIndex].enemyplmask)<>0))) then
      [*] = ;      count := count+1;
      [*] = ;   end;
      [*] = ;   var rndind : Integer = floor(RandomExt*count);
      [*] = ;   count := 0;
      [*] = ;   for i := 0 to gc_MaxPlayerCount-1 do
      [*] = ;   begin
      [*] = ;      var enemymask : Integer = gPlayer[i].myplmask;
      [*] = ;      if ((i <> plIndex) and (gPlayer[i].bExists) and (((enemymask and gPlayer[plIndex].enemyplmask)<>0))) then
      [*] = ;      begin
      [*] = ;         if (count=rndind) then
      [*] = ;         begin
      [*] = ;            Result := i;
      [*] = ;            break;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         count := count+1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_GetUnitCountAnyFaction(plindex, airole : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var i : Integer;
      [*] = ;   for i := 0 to gc_MaxCountryCount-1 do
      [*] = ;   Result := Result+gPlayer[plindex].aidata.unitsamount[i, airole];
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_GetTowerPos(const plIndex : Integer; var xpos, zpos : Float);
      [*] = ;begin
      [*] = ;   var enemyid : Integer = _ai_GetRandomEnemy(plIndex);
      [*] = ;   if (enemyid<>-1) then
      [*] = ;   begin
      [*] = ;      var dst : Float = Min(60, 25+_ai_GetUnitCountAnyFaction(plindex, gc_ai_unit_tower)*7);
      [*] = ;      _misc_GetPositionOnLine(gPlayer[plIndex].aidata.centerx, gPlayer[plIndex].aidata.centerz, gMap.players[enemyid].startx, gMap.players[enemyid].starty, dst, xpos, zpos);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      xpos := gPlayer[plIndex].aidata.centerx;
      [*] = ;      zpos := gPlayer[plIndex].aidata.centerz;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// _ai_GetOldPortPos
      [*] = ;//
      [*] = ;function _ai_GetOldPortPos(plInd : Integer; stX, stZ : Float; var resX, resZ : Float) : Boolean;
      [*] = ;begin
      [*] = ;   Result := false;
      [*] = ;   resX := 0;
      [*] = ;   resZ := 0;
      [*] = ;
      [*] = ;   var cx : Float = gPlayer[plInd].aiData.centerX;
      [*] = ;   var cz : Float = gPlayer[plInd].aiData.centerZ;
      [*] = ;   var island : Integer = _misc_GetIsland(cx, cz);
      [*] = ;   if island >= 0 then
      [*] = ;   begin
      [*] = ;      var allowDist : Float;
      [*] = ;      if (stX <> cx) or (stZ <> cz) then
      [*] = ;      allowDist := VectorDistance(stX, 0, stZ, cx, 0, cz) + 10;
      [*] = ;
      [*] = ;      var minDist : Float = gc_MaxFloat;
      [*] = ;      var i, j : Integer;
      [*] = ;      var x, z : Float;
      [*] = ;
      [*] = ;      for i := 0 to gc_MaxColMapWidth-1 do
      [*] = ;      for j := 0 to gc_MaxColMapHeight-1 do
      [*] = ;      if (gIslands.grid[i, j].index = island) and gIslands.grid[i, j].shore then
      [*] = ;      begin
      [*] = ;         _misc_ColGridIndicesToPos(i, j, x, z);
      [*] = ;         x := x+0.25;
      [*] = ;         z := z+0.25;
      [*] = ;         var dist : Float = VectorDistance(cx, 0, cz, x, 0, z);
      [*] = ;         if (dist > allowDist) and (dist < minDist) then
      [*] = ;         begin
      [*] = ;            minDist := dist;
      [*] = ;            resX := x;
      [*] = ;            resZ := z;
      [*] = ;            Result := true;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// _ai_GetPortPos
      [*] = ;//
      [*] = ;function _ai_GetPortPos(plInd : Integer; stX, stZ : Float; var resX, resZ : Float) : Boolean;
      [*] = ;begin
      [*] = ;   Result := false;
      [*] = ;   resX := 0;
      [*] = ;   resZ := 0;
      [*] = ;
      [*] = ;   var cx : Float = gPlayer[plInd].aiData.centerX;
      [*] = ;   var cz : Float = gPlayer[plInd].aiData.centerZ;
      [*] = ;   var island : Integer = _misc_GetIsland(cx, cz);
      [*] = ;   if island >= 0 then
      [*] = ;   begin
      [*] = ;      var allowDist : Float;
      [*] = ;      if (stX <> cx) or (stZ <> cz) then
      [*] = ;      allowDist := VectorDistance(stX, 0, stZ, cx, 0, cz) + 10;
      [*] = ;
      [*] = ;      var minDist : Float = gc_MaxFloat;
      [*] = ;      var i, j : Integer;
      [*] = ;      var x, z : Float;
      [*] = ;
      [*] = ;      var iSt, jSt, iCen, jCen : Integer;
      [*] = ;      _misc_PosToColGridIndices(stX, stZ, iSt, jSt);
      [*] = ;      _misc_PosToColGridIndices(cx, cz, iCen, jCen);
      [*] = ;      var iRes, jRes : Integer;
      [*] = ;
      [*] = ;      function Check(iCheck, jCheck : Integer) : Boolean;
      [*] = ;      begin
      [*] = ;         if IsInRangeInt(iCheck, 0, gc_MaxColMapWidth-1) and IsInRangeInt(jCheck, 0, gc_MaxColMapHeight-1)
      [*] = ;         and (gIslands.grid[iCheck, jCheck].index = island) then
      [*] = ;         begin
      [*] = ;            Result := true;
      [*] = ;            if gIslands.grid[iCheck, jCheck].shore then
      [*] = ;            begin
      [*] = ;               var dist : Float = VectorDistance(iCen, 0, jCen, iCheck, 0, jCheck)/2;
      [*] = ;               if (dist > allowDist) and (dist < minDist) then
      [*] = ;               begin
      [*] = ;                  minDist := dist;
      [*] = ;                  iRes := iCheck;
      [*] = ;                  jRes := jCheck;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         Result := false;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var maxRad : Integer = Max(Max(Max(iSt, jSt), gc_MaxColMapWidth-iSt), gc_MaxColMapHeight-jSt);
      [*] = ;      var r : Integer;
      [*] = ;      for r := Floor(Sqrt(Sqr(allowDist)/2)) to maxRad-1 do
      [*] = ;      begin
      [*] = ;         var isIsland : Boolean;
      [*] = ;         for i := -r to r do
      [*] = ;         begin
      [*] = ;            isIsland := isIsland or Check(iCen-r, jCen+i);
      [*] = ;            isIsland := isIsland or Check(iCen+r, jCen+i);
      [*] = ;            isIsland := isIsland or Check(iCen+i, jCen-r);
      [*] = ;            isIsland := isIsland or Check(iCen+i, jCen+r);
      [*] = ;         end;
      [*] = ;
      [*] = ;         if not isIsland then
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;
      [*] = ;      Result := (minDist < gc_MaxFloat);
      [*] = ;      if Result then
      [*] = ;      begin
      [*] = ;         _misc_ColGridIndicesToPos(iRes, jRes, resX, resZ);
      [*] = ;         resX := resX + 0.25;
      [*] = ;         resZ := resZ + 0.25;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// _ai_GetNewPortPos
      [*] = ;//
      [*] = ;function _ai_GetNewPortPos(plInd : Integer; stX, stZ : Float; var resX, resZ : Float; var curRad, curInd : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   Result := false;
      [*] = ;   resX := 0;
      [*] = ;   resZ := 0;
      [*] = ;
      [*] = ;   var cx : Float = gPlayer[plInd].aiData.centerX;
      [*] = ;   var cz : Float = gPlayer[plInd].aiData.centerZ;
      [*] = ;   var island : Integer = _misc_GetIsland(cx, cz);
      [*] = ;   if island >= 0 then
      [*] = ;   begin
      [*] = ;      var i, j : Integer;
      [*] = ;      var x, z : Float;
      [*] = ;
      [*] = ;      var iSt, jSt, iCen, jCen : Integer;
      [*] = ;      _misc_PosToColGridIndices(stX, stZ, iSt, jSt);
      [*] = ;      _misc_PosToColGridIndices(cx, cz, iCen, jCen);
      [*] = ;      var iRes, jRes : Integer;
      [*] = ;      iRes := -1;
      [*] = ;      jRes := -1;
      [*] = ;
      [*] = ;      function Check(iCheck, jCheck : Integer) : Boolean;
      [*] = ;      begin
      [*] = ;         if IsInRangeInt(iCheck, 0, gc_MaxColMapWidth-1) and IsInRangeInt(jCheck, 0, gc_MaxColMapHeight-1)
      [*] = ;         and (gIslands.grid[iCheck, jCheck].index = island) then
      [*] = ;         begin
      [*] = ;            Result := true;
      [*] = ;            if (gIslands.grid[iCheck, jCheck].shore) then
      [*] = ;            begin
      [*] = ;               iRes := iCheck;
      [*] = ;               jRes := jCheck;
      [*] = ;            end
      [*] = ;         end
      [*] = ;         else
      [*] = ;         Result := false;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var maxRad : Integer = Max(Max(Max(iSt, jSt), gc_MaxColMapWidth-iSt), gc_MaxColMapHeight-jSt);
      [*] = ;      var r : Integer;
      [*] = ;      var startInd : Integer = curInd;
      [*] = ;
      [*] = ;      for r := curRad to maxRad-1 do
      [*] = ;      begin
      [*] = ;         var isIsland : Boolean;
      [*] = ;         for i := startInd to r do
      [*] = ;         begin
      [*] = ;            isIsland := isIsland or Check(iCen-r, jCen+i);
      [*] = ;            isIsland := isIsland or Check(iCen+r, jCen+i);
      [*] = ;            isIsland := isIsland or Check(iCen+i, jCen-r);
      [*] = ;            isIsland := isIsland or Check(iCen+i, jCen+r);
      [*] = ;
      [*] = ;            if iRes >= 0 then
      [*] = ;            begin
      [*] = ;               curRad := r;
      [*] = ;               curInd := i+1;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (curInd = -r) and (not isIsland) then
      [*] = ;         break;
      [*] = ;
      [*] = ;         if iRes >=0 then
      [*] = ;         break;
      [*] = ;
      [*] = ;         startInd := -r-1;
      [*] = ;      end;
      [*] = ;
      [*] = ;      Result := (iRes >= 0);
      [*] = ;      if Result then
      [*] = ;      begin
      [*] = ;         _misc_ColGridIndicesToPos(iRes, jRes, resX, resZ);
      [*] = ;         resX := resX + 0.25;
      [*] = ;         resZ := resZ + 0.25;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_NationIsEurope(cid : integer) : boolean;
      [*] = ;begin
      [*] = ;   Result := not ((cid=cid_ukr) or (cid=cid_tur) or (cid=cid_alg) or (cid=cid_sco));
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_DoArmor(cid : integer) : boolean;
      [*] = ;begin
      [*] = ;   Result := not ((cid=cid_ukr) or (cid=cid_tur) or (cid=cid_alg) or (cid=cid_sco) or (cid=cid_pol)); //poland is exception preffered to do it in 18century
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_DoTowers(cid : integer) : boolean;
      [*] = ;begin
      [*] = ;   Result := ((cid=cid_aus) or (cid=cid_fra) or (cid=cid_eng) or (cid=cid_spa) or
      [*] = ;   (cid=cid_rus) or (cid=cid_swe) or (cid=cid_pru) or (cid=cid_ven) or (cid=cid_pol) or (cid=cid_tur) or (cid=cid_alg) or (cid=cid_den) or (cid=cid_net));
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_BuildBarracks17(cid : integer) : boolean;
      [*] = ;begin
      [*] = ;   Result := ((cid=cid_ukr) or (cid=cid_rus) or (cid=cid_tur) or (cid=cid_alg));
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_EnemyHasNoArmor(enemycid : integer) : boolean;
      [*] = ;begin
      [*] = ;   Result := ((enemycid=cid_ukr) or (enemycid=cid_pol) or (enemycid=cid_tur) or (enemycid=cid_alg) or (enemycid=cid_sco));
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_GetTimeFromStart(plind : Integer) : integer;
      [*] = ;begin
      [*] = ;   Result :=  floor(GetGameTime-gPlayer[plind].aidata.inittime) div 60;
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_UpgradeIsDoneById(plind, cid, aiupgrade : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   var id : Integer = gPlayer[plind].aidata.upgradeid[cid][aiupgrade];
      [*] = ;   Result := gPlayer[plInd].upgstate[cid][id].done;
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_BuildMines(plind, cid, onFood, onWood, onStone : Integer) : boolean;
      [*] = ;begin
      [*] = ;   //var reqCount : Integer = (_ai_GetTimeFromStart() div 3)+10;
      [*] = ;   var reqCount : Integer;
      [*] = ;   Result := ((gMap.settings.gen.resourcestart=ai_st_res_millions) and (_ai_GetTimeFromStart(plind)>10)) or
      [*] = ;   ((gMap.settings.gen.resourcestart<>ai_st_res_millions) and _ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_food140) and (onFood>11) and ((onWood+onStone)>reqCount) and (onWood>0) and (onStone>0));
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_GetInf17Unit(plind, cid : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result :=  gc_ai_unit_infantry17;
      [*] = ;   if (cid=cid_alg) and ((gPlayer[plind].aidata.bFlags[gc_ai_flag_uniq_inf17]) or (bIsWaterMap)) then
      [*] = ;   Result :=  gc_ai_unit_uniq_inf17
      [*] = ;   else
      [*] = ;   if ((cid=cid_aus) or (cid=cid_tur)) and ((gPlayer[plind].aidata.bFlags[gc_ai_flag_uniq_inf17]) and (not bIsWaterMap)) then
      [*] = ;   Result :=  gc_ai_unit_uniq_inf17;
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_GetCav17Unit(plind, cid : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result :=  gc_ai_unit_reitar;
      [*] = ;   if (_ai_NationIsEurope(cid) and (gPlayer[plind].aidata.bFlags[gc_ai_flag_drag_cav17])) then
      [*] = ;   Result := gc_ai_unit_dragoon17;
      [*] = ;   if ((cid=cid_ukr) or (cid=cid_aus) or (cid=cid_pol) or (cid=cid_rus) or (cid=cid_tur)) and (gPlayer[plind].aidata.bFlags[gc_ai_flag_uniq_cav17]) then
      [*] = ;   Result := gc_ai_unit_uniq_cav17;
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_GetInf18Unit(plind, cid : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := gc_ai_unit_musk18;
      [*] = ;   if gPlayer[plind].aidata.bFlags[gc_ai_flag_grenadier] then
      [*] = ;   Result :=  gc_ai_unit_grenadier;
      [*] = ;   if ((cid=cid_aus) or (cid=cid_fra) or (cid=cid_eng) or (cid=cid_sco)) and (gPlayer[plind].aidata.bFlags[gc_ai_flag_uniq_inf18]) then
      [*] = ;   Result :=  gc_ai_unit_uniq_inf18;
      [*] = ;   if (cid=cid_pru) then
      [*] = ;   Result := gc_ai_unit_musk18;
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_GetCav18Unit(plind, cid : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := gc_ai_unit_dragun18;
      [*] = ;   if (gPlayer[plind].aidata.bFlags[gc_ai_flag_cuirassiers]) then Result := gc_ai_unit_cuirassier;
      [*] = ;   if (gPlayer[plind].aidata.bFlags[gc_ai_flag_hussar]) then Result := gc_ai_unit_hussar;
      [*] = ;   if cid=cid_pru then Result := gc_ai_unit_hussar;
      [*] = ;   //specific for poland:
      [*] = ;   if ((cid=cid_pol) and (_ai_GetCav17Unit(plind, cid) = gc_ai_unit_reitar) and ((gPlayer[plind].aidata.bFlags[gc_ai_flag_hussar]) or (gPlayer[plind].aidata.bFlags[gc_ai_flag_cuirassiers]))) then
      [*] = ;   Result := gc_ai_unit_reitar;
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_GetCountProduced(plind, cid, airole : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var unitid : Integer = gPlayer[plind].aidata.aiunit[cid][airole];
      [*] = ;   if (unitid<>-1) then
      [*] = ;   Result := gPlayer[plind].stat.produced[cid][unitid]
      [*] = ;   else
      [*] = ;   Result := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_DoUnit18cGrade(plind, cid : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   Result := (_ai_GetUnitCount(plind, cid, gc_ai_unit_ba18)>0);
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_TestPowderUpgradeCondition(plind, cid : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   Result := False;
      [*] = ;   //Ukraine:
      [*] = ;   if (cid=cid_ukr) then
      [*] = ;   Result := (_ai_GetUnitCurrentUpgLevel(plind, cid, gc_ai_unit_musk17, 1)>=5); // decreased upg count
      [*] = ;   if (cid=cid_tur) or (cid=cid_sco) then
      [*] = ;   Result := ((_ai_GetUnitCurrentUpgLevel(plind, cid, gc_ai_unit_musk17, 1)>=3) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_musk17)>=50));
      [*] = ;   if (_ai_NationIsEurope(cid) and (_ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_century))) then
      [*] = ;   begin
      [*] = ;      if (_ai_GetInf18Unit(plind, cid)=gc_ai_unit_uniq_inf18) and (_ai_GetCav18Unit(plind, cid)=gc_ai_unit_dragun18) then
      [*] = ;      Result := (_ai_GetUnitCurrentUpgLevel(plind, cid, gc_ai_unit_uniq_inf18, 1)>=6) and (_ai_GetUnitCurrentUpgLevel(plind, cid, gc_ai_unit_dragun18, 1)>=6);
      [*] = ;
      [*] = ;      if (_ai_GetInf18Unit(plind, cid)<>gc_ai_unit_uniq_inf18) and (_ai_GetCav18Unit(plind, cid)=gc_ai_unit_dragun18) then
      [*] = ;      Result := (_ai_GetUnitCurrentUpgLevel(plind, cid, gc_ai_unit_dragun18, 1)>=6);
      [*] = ;
      [*] = ;      if (_ai_GetInf18Unit(plind, cid)=gc_ai_unit_uniq_inf18) and (_ai_GetCav18Unit(plind, cid)<>gc_ai_unit_dragun18) then
      [*] = ;      Result := (_ai_GetUnitCurrentUpgLevel(plind, cid, gc_ai_unit_uniq_inf18, 1)>=6);
      [*] = ;
      [*] = ;      if (not (_ai_GetInf18Unit(plind, cid)=gc_ai_unit_uniq_inf18)) and (_ai_GetCav18Unit(plind, cid)<>gc_ai_unit_dragun18) then
      [*] = ;      Result := (_ai_GetUnitCount(plind, cid, gc_ai_unit_ba18)>=3);
      [*] = ;
      [*] = ;      if (cid=cid_pru) or (cid=cid_den) then
      [*] = ;      Result := (_ai_GetUnitCount(plind, cid, gc_ai_unit_ba18)>=2);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_FindBestPlaceForStorehouse(plHnd : Integer; var gridx, gridy : Float; centerx, centerz : Float) : Boolean;
      [*] = ;begin
      [*] = ;   _misc_ProfilerBegin('_ai_FindBestPlaceForStorehouse');
      [*] = ;   Result := False;
      [*] = ;   const cminfactor = 12;
      [*] = ;   const cmindst = 8;
      [*] = ;   const crescountWeight = 4;
      [*] = ;   const cdstWeight = 3;
      [*] = ;   const cworkerCount = 20;
      [*] = ;   var reldst : Float;
      [*] = ;   var minrelgridx, minrelgridy : Integer = -1;
      [*] = ;   var factor, maxfactor : Float;
      [*] = ;   var testD : Float;
      [*] = ;   var plInd : Integer = GetPlayerIndexByHandle(plHnd);
      [*] = ;   var cHalfMapW : Integer = GetMapWidth div 2;
      [*] = ;   var cHalfMapH : Integer = GetMapHeight div 2;
      [*] = ;   var myisland : Integer = _misc_GetIsland(centerx, centerz);
      [*] = ;   var i, j, k : Integer;
      [*] = ;   for i:=0 to gc_resgrid_countx-1 do
      [*] = ;   for j:=0 to gc_resgrid_county-1 do
      [*] = ;   begin
      [*] = ;      var posX : Float = (i+0.5)*gc_resgrid_size-(GetMapWidth div 2);
      [*] = ;      var posZ : Float = (j+0.5)*gc_resgrid_size-(GetMapHeight div 2);
      [*] = ;      if _misc_IsCorrectIslandPosition(plInd, posX, posZ) then
      [*] = ;      begin
      [*] = ;         var bskip : Boolean;
      [*] = ;         var mindst : Float = -1;
      [*] = ;         //var rescount : Integer = gResGrid[i,j].fResCount[gc_resource_type_wood]*gc_gameplay_resource_maxattackers_wood+(gResGrid[i,j].fResCount[gc_resource_type_stone]*gc_gameplay_resource_maxattackers_stone div 3);
      [*] = ;         var rescount : Integer = gResGrid[i,j].fResCount[gc_resource_type_wood]+(gResGrid[i,j].fResCount[gc_resource_type_stone]);
      [*] = ;         if (rescount>1) then
      [*] = ;         begin
      [*] = ;            var storecount : Integer = gPlayer[plInd].aidata.storelist.GetCount;
      [*] = ;            var workercount : Integer = gResGrid[i,j].fWorkerCount[plInd][gc_resource_type_wood]+gResGrid[i,j].fWorkerCount[plInd][gc_resource_type_stone];
      [*] = ;            if (workercount>0) or ((rescount>4) and (storecount<=5)) then
      [*] = ;            begin
      [*] = ;               //var pathDist : Float = _unit_GetPathDistanceByCoord(centerx, centerz, posX, posZ, false);
      [*] = ;               var zone : Integer = TopologyGetZoneIndex(posX, posZ);
      [*] = ;               var pBuffer : Pointer = TopologyGetZoneBufferByIndex(zone);
      [*] = ;               var pathdist : Integer = gc_MaxInt;
      [*] = ;               if (pBuffer <> nil) then
      [*] = ;               pathdist := TTopZone(pBuffer).centerDist[plInd];
      [*] = ;
      [*] = ;               if (rescount>4) and (storecount<=5) then
      [*] = ;               workercount := workercount+Max(0, floor(cworkerCount/(pathDist*4+1)-10));
      [*] = ;
      [*] = ;               if (workercount>0) then
      [*] = ;               begin
      [*] = ;                  for k:=storecount-1 downto 0 do
      [*] = ;                  begin
      [*] = ;                     var trgHnd : Integer = gPlayer[plInd].aidata.storelist.Get(k);
      [*] = ;                     var vecdst : Float;
      [*] = ;                     if (mindst>=0) then
      [*] = ;                     vecdst := VectorDistance(posX, 0, posZ, GetGameObjectPositionXByHandle(trgHnd), 0, GetGameObjectPositionZByHandle(trgHnd));
      [*] = ;                     if (mindst<0) or (vecdst<mindst) then
      [*] = ;                     begin
      [*] = ;                        var dst : Float = _unit_GetPathDistanceByCoord(posX, posZ, GetGameObjectPositionXByHandle(trgHnd), GetGameObjectPositionZByHandle(trgHnd), false);
      [*] = ;                        if (mindst<0) or (dst<mindst) then
      [*] = ;                        begin
      [*] = ;                           mindst := dst;
      [*] = ;                           if (dst<=gc_ai_MinStoreHouseDist) then
      [*] = ;                           begin
      [*] = ;                              bskip := True;
      [*] = ;                              break;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  if (not bskip) then
      [*] = ;                  begin
      [*] = ;                     if (mindst=-1) then
      [*] = ;                     mindst := pathDist;
      [*] = ;                     if (mindst>gc_ai_MinStoreHouseDist) then
      [*] = ;                     begin
      [*] = ;                        var deltadst : Float = mindst-cmindst;
      [*] = ;                        if (deltadst>cdstWeight*3) then
      [*] = ;                        deltadst := cdstWeight*3;
      [*] = ;                        factor := (workercount+rescount/crescountweight)*(1+(round(deltadst) div cdstWeight));
      [*] = ;                        if (factor>cminfactor) then
      [*] = ;                        begin
      [*] = ;                           if (minrelgridx=-1) or (factor>maxfactor) then
      [*] = ;                           begin
      [*] = ;                              minrelgridx := i;
      [*] = ;                              minrelgridy := j;
      [*] = ;                              maxfactor := factor;
      [*] = ;                              testD := mindst;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if (minrelgridx<>-1) then
      [*] = ;   begin
      [*] = ;      Result := True;
      [*] = ;      gridx := (minrelgridx+0.5)*gc_resgrid_size-(GetMapWidth div 2);
      [*] = ;      gridy := (minrelgridy+0.5)*gc_resgrid_size-(GetMapHeight div 2);
      [*] = ;   end;
      [*] = ;   _misc_ProfilerEnd('_ai_FindBestPlaceForStorehouse');
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_GetInsideCount(goHnd : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var pobjinside : Pointer = _misc_GetObjectArgData(goHnd, gc_argunit_inside);
      [*] = ;   if (pobjinside<>nil) then
      [*] = ;   Result := TIntegerList(pobjinside).GetCount;
      [*] = ;end;
      [*] = ;
      [*] = ;//fix on commit
      [*] = ;function WriteOrderObjects(plhnd : Integer; var list : TIntegerList; ordertype, trghnd : Integer; clearorders : Boolean): Boolean;
      [*] = ;begin
      [*] = ;   // network
      [*] = ;   if (list.GetCount>0) and (_net_IsOnline or _net_IsRecord) then begin
      [*] = ;      var parg: Pointer = StateMachineGetArgDataByInd(GetPlayerStateMachineHandle(plhnd), gc_argPlayer_plr);
      [*] = ;      if parg<>nil then begin
      [*] = ;         TPlayerArgs(parg).fordtyp := ordertype;
      [*] = ;         TPlayerArgs(parg).ftarget := trghnd;
      [*] = ;         TPlayerArgs(parg).fclrord := clearorders;
      [*] = ;         TPlayerArgs(parg).fintlst := list;
      [*] = ;         PlayerExecuteStateByHandle(plhnd, 'WriteOrder');
      [*] = ;         Result := True;
      [*] = ;         end else begin
      [*] = ;         Result := False;
      [*] = ;         _misc_ErrorLog('WriteOrderObjects: parg = nil');
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   Result := False;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _order_OrderUnitsToGainResource(var list : TIntegerList; plHnd, resHnd : Integer; bClearOrders : Boolean);
      [*] = ;begin
      [*] = ;   var count : Integer;
      [*] = ;   var resX : Float = GetGameObjectPositionXByHandle(resHnd);
      [*] = ;   var resZ : Float = GetGameObjectPositionZByHandle(resHnd);
      [*] = ;   var i : Integer;
      [*] = ;   for i:=list.GetCount-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var goHnd : Integer = list.Get(i);
      [*] = ;      if (bClearOrders) then
      [*] = ;      _unit_ClearOrders(goHnd);
      [*] = ;      _unit_OrderGainResource(goHnd, resHnd, resX, resZ);
      [*] = ;   end;
      [*] = ;   // network
      [*] = ;   WriteOrderObjects(plHnd, list, gc_obj_order_type_gainres, resHnd, bClearOrders);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_SetResouceBalance(plind, resid, a0, a1, a2 : Integer);
      [*] = ;begin
      [*] = ;   gPlayer[plind].aidata.resbalance[resid][0] := a0;
      [*] = ;   gPlayer[plind].aidata.resbalance[resid][1] := a1;
      [*] = ;   gPlayer[plind].aidata.resbalance[resid][2] := a2;
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_GetMineIdByResType(plind, cid, restype : Integer) : Integer;
      [*] = ;begin
      [*] = ;   case restype of
      [*] = ;      gc_resource_type_gold : Result := gPlayer[plind].aidata.aiunit[cid][gc_ai_unit_minegold];
      [*] = ;      gc_resource_type_iron : Result := gPlayer[plind].aidata.aiunit[cid][gc_ai_unit_mineiron];
      [*] = ;      gc_resource_type_coal : Result := gPlayer[plind].aidata.aiunit[cid][gc_ai_unit_minecoal];
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_GetResByMineAiRole(airole : Integer) : Integer;
      [*] = ;begin
      [*] = ;   case airole of
      [*] = ;      gc_ai_unit_minegold : Result := gc_resource_type_gold;
      [*] = ;      gc_ai_unit_mineiron : Result := gc_resource_type_iron;
      [*] = ;      gc_ai_unit_minecoal : Result := gc_resource_type_coal;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_SelectBuildingsWithId(plind, cid, buildingid : Integer);
      [*] = ;begin
      [*] = ;   _misc_ProfilerBegin('(!)_ai_SelectBuildingsWithId');
      [*] = ;   //var buildingid : Integer = gPlayer[plind].aidata.buildlink[cid][id];
      [*] = ;   gPlayer[plind].aidata.ailist.Clear;
      [*] = ;   if (_ai_GetUnitCount(plind, cid, gObjProp[cid][buildingid].airole)>0) then
      [*] = ;   begin
      [*] = ;      var i : Integer;
      [*] = ;      for i:=0 to gPlayer[plind].aidata.buildingslist.GetCount-1 do
      [*] = ;      begin
      [*] = ;         var goHnd : Integer = gPlayer[plind].aidata.buildingslist.Get(i);
      [*] = ;         var pobj : Pointer = _unit_GetTObj(goHnd);
      [*] = ;         if (pobj<>nil) and (TObj(pobj).id=buildingid) and (TObj(pobj).cid=cid) then
      [*] = ;         gPlayer[plind].aidata.ailist.Add(goHnd);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   _misc_ProfilerEnd('(!)_ai_SelectBuildingsWithId');
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_TryUpgradeMineEx(gohnd, cid, id, curlevel : Integer) : boolean;
      [*] = ;begin
      [*] = ;   var plHnd : Integer = GetGameObjectPlayerHandleByHandle(goHnd);
      [*] = ;   var plInd : Integer = GetPlayerIndexByHandle(plHnd);
      [*] = ;   Result := False;
      [*] = ;   var p : Pointer = gPlayer[plind].aidata.uniqupg[cid].GetById(id);
      [*] = ;   if (p<>nil) then
      [*] = ;   begin
      [*] = ;      var level : Integer = curlevel+1;
      [*] = ;      var sid : String = TUniqUpgrade(p).levelsid[level];
      [*] = ;      if sid<>'' then
      [*] = ;      begin
      [*] = ;         var upgid : Integer = TUniqUpgrade(p).levelid[level];
      [*] = ;         var pobj : Pointer =  _unit_GetTObj(gohnd);
      [*] = ;         if (pobj<>nil) and (TObj(pobj).orders[0].itype<>gc_obj_order_type_performupgrade) then
      [*] = ;         begin
      [*] = ;            if (_player_CheckAccessControlRequirements(plHnd, cid, sid)=gc_result_checkaccesscontrolreq_ok) then
      [*] = ;            begin
      [*] = ;               if (_unit_CanApplyUpgradeCostBySID(plHnd, cid, sid)) then
      [*] = ;               begin
      [*] = ;                  if (bai) then
      [*] = ;                  begin
      [*] = ;                     gTmpIntList.Clear;
      [*] = ;                     gTmpIntList.Add(gohnd);
      [*] = ;                     _unit_MakeUpgrade(plHnd, gTmpIntList, upgid, True, True);
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     if (gPlayer[plind].playeradviser.adviser.benable and gPlayer[plind].playeradviser.adviser.bupgrades) then
      [*] = ;                     begin
      [*] = ;                        var val : Integer = _misc_TwoIntToOne(cid, id);
      [*] = ;                        if (gPlayer[plind].playeradviser.upgradeseconomy.IndexOf(val)<0) then
      [*] = ;                        begin
      [*] = ;                           gPlayer[plind].playeradviser.upgradeseconomy.Add(val);
      [*] = ;                           gbool_gui_updateadviseradvice := True;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  Result := True;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_CalculateCurrentResourceCollection(plind : Integer; var onFood, onWood, onStone : Integer);
      [*] = ;begin
      [*] = ;   _misc_ProfilerBegin('_ai_CalculateCurrentResourceCollection');
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to gPlayer[plind].aidata.peasantlist.GetCount-1 do
      [*] = ;   begin
      [*] = ;      var pobj : Pointer = _unit_GetTObj(gPlayer[plind].aidata.peasantlist.Get(i));
      [*] = ;      if (pobj<>nil) then
      [*] = ;      begin
      [*] = ;         var porder : Pointer = TObj(pobj).orders[0];
      [*] = ;         var porderinfo : Pointer = TObj(pobj).orders[0].info;
      [*] = ;         if (TOrder(porder).itype=gc_obj_order_type_gainres) then
      [*] = ;         begin
      [*] = ;            case TOrderInfo(porderinfo).restype of
      [*] = ;               gc_resource_type_food : onFood := onFood+1;
      [*] = ;               gc_resource_type_wood : onWood := onWood+1;
      [*] = ;               gc_resource_type_stone : onStone := onStone+1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   gPlayer[plind].aidata.onFood := onFood;
      [*] = ;   gPlayer[plind].aidata.onWood := onWood;
      [*] = ;   gPlayer[plind].aidata.onStone := onStone;
      [*] = ;   _misc_ProfilerEnd('_ai_CalculateCurrentResourceCollection');
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_SendFreePeasantsToGainFood(plind, count : Integer; var onFood : Integer);
      [*] = ;begin
      [*] = ;   if (gPlayer[plind].aidata.milllist.GetCount>0) then
      [*] = ;   begin
      [*] = ;      gIntegerList.Clear;
      [*] = ;      //var goHnd : Integer = gPlayer[plind].aidata.milllist.Get(gPlayer[plind].aidata.milllist.GetCount-1);
      [*] = ;      var myisland : Integer = _misc_GetIsland(gPlayer[plind].aidata.centerx, gPlayer[plind].aidata.centerz);
      [*] = ;      var goHnd : Integer;
      [*] = ;      var pX, pZ : Float;
      [*] = ;      var i : Integer;
      [*] = ;      for i:=0 to gPlayer[plind].aidata.milllist.GetCount-1 do
      [*] = ;      begin
      [*] = ;         goHnd := gPlayer[plind].aidata.milllist.Get(0);
      [*] = ;         pX := GetGameObjectPositionXByHandle(goHnd);
      [*] = ;         pZ := GetGameObjectPositionZByHandle(goHnd);
      [*] = ;         if _misc_IsCorrectIslandPosition(plInd, pX, pZ) then
      [*] = ;         break
      [*] = ;         else
      [*] = ;         goHnd := 0;
      [*] = ;      end;
      [*] = ;      if (goHnd<>0) then
      [*] = ;      begin
      [*] = ;         var pX : Float = GetGameObjectPositionXByHandle(goHnd);
      [*] = ;         var pZ : Float = GetGameObjectPositionZByHandle(goHnd);
      [*] = ;         _misc_MakeListEnvironmentInRadius(pX, pZ, 30, True, true, false, false, False, gIntegerList);
      [*] = ;         //clean up
      [*] = ;         for i:=gIntegerList.GetCount-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pres : Pointer = _res_GetTRes(gIntegerList.Get(i));
      [*] = ;            if (pres<>nil) and (not TRes(pres).brised) then
      [*] = ;            gIntegerList.Delete(i);
      [*] = ;         end;
      [*] = ;         if (gIntegerList.GetCount>0) then
      [*] = ;         begin
      [*] = ;            var plHnd : Integer = GetPlayerHandleByIndex(plInd);
      [*] = ;            var trgHnd : Integer = gIntegerList.Get(floor(gIntegerList.GetCount*random));
      [*] = ;            gTmpIntList.Clear;
      [*] = ;            _misc_CopyIntListRange(gTmpIntList, gPlayer[plind].aidata.freepeasant, 0, Min(count, gPlayer[plind].aidata.freepeasant.GetCount), true);
      [*] = ;            _order_OrderUnitsToGainResource(gTmpIntList, plHnd, trgHnd, true);
      [*] = ;            onFood := onFood+gTmpIntList.GetCount();
      [*] = ;            //Critical problem send more pe
      [*] = ;            if (gPlayer[plind].bfamine) then
      [*] = ;            begin
      [*] = ;               var mmask : Integer = (1 shl gc_obj_material_body);
      [*] = ;               _misc_MakeListObjectsInRadius(gPlayer[plind].aidata.centerx, gPlayer[plind].aidata.centerz, 25, true, mmask, 0, false, gIntegerList);
      [*] = ;               gTmpIntList.Clear;
      [*] = ;               var j : Integer;
      [*] = ;               for j:=gIntegerList.GetCount-1 downto 0 do
      [*] = ;               begin
      [*] = ;                  var unitHnd : Integer = gIntegerList.Get(j);
      [*] = ;                  var pobj : Pointer = _unit_GetTObj(unitHnd);
      [*] = ;                  if (pobj<>nil) then
      [*] = ;                  begin
      [*] = ;                     var porder : Pointer = TObj(pobj).orders[0];
      [*] = ;                     var porderinfo : Pointer = TObj(pobj).orders[0].info;
      [*] = ;                     if (TObj(pobj).pl=plind) and (gObjProp[TObj(pobj).cid][TObj(pobj).id].usage=gc_obj_usage_peasant) and
      [*] = ;                     ((TOrder(porder).itype=gc_obj_order_type_gainres) and (TOrderInfo(porderinfo).restype<>gc_resource_type_food) and (TObj(pObj).squad=-1)) then
      [*] = ;                     gTmpIntList.Add(unitHnd);
      [*] = ;                     if (gTmpIntList.GetCount>onFood*1.1) then
      [*] = ;                     break;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               if (gTmpIntList.GetCount>0) then
      [*] = ;               _order_OrderUnitsToGainResource(gTmpIntList, plHnd, trgHnd, true);
      [*] = ;               onFood := onFood+gTmpIntList.GetCount();
      [*] = ;            end;
      [*] = ;            //critical reassign peasants to gain food
      [*] = ;            if (onFood<count) and (bai) then
      [*] = ;            begin
      [*] = ;               var mmask : Integer = (1 shl gc_obj_material_body);
      [*] = ;               _misc_MakeListObjectsInRadius(gPlayer[plind].aidata.centerx, gPlayer[plind].aidata.centerz, 25, true, mmask, 0, false, gIntegerList);
      [*] = ;               gTmpIntList.Clear;
      [*] = ;               var j : Integer;
      [*] = ;               for j:=gIntegerList.GetCount-1 downto 0 do
      [*] = ;               begin
      [*] = ;                  var unitHnd : Integer = gIntegerList.Get(j);
      [*] = ;                  var pobj : Pointer = _unit_GetTObj(unitHnd);
      [*] = ;                  if (pobj<>nil) then
      [*] = ;                  begin
      [*] = ;                     var porder : Pointer = TObj(pobj).orders[0];
      [*] = ;                     var porderinfo : Pointer = TObj(pobj).orders[0].info;
      [*] = ;                     if (TObj(pobj).pl=plind) and (gObjProp[TObj(pobj).cid][TObj(pobj).id].usage=gc_obj_usage_peasant) and
      [*] = ;                     ((TOrder(porder).itype=gc_obj_order_type_gainres) and (TOrderInfo(porderinfo).restype<>gc_resource_type_food) and (TObj(pObj).squad=-1)) then
      [*] = ;                     gTmpIntList.Add(unitHnd);
      [*] = ;                     if (gTmpIntList.GetCount>onFood*1.1) then
      [*] = ;                     break;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               if (gTmpIntList.GetCount>4) then
      [*] = ;               begin
      [*] = ;                  gTmpIntList.SetCount(gTmpIntList.GetCount-4); // always have 4 peasants for wood and stone
      [*] = ;                  _order_OrderUnitsToGainResource(gTmpIntList, plHnd, trgHnd, true);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_FindResourceToExtract(plInd : Integer; px, py : Float; var resHnd : Integer; var resx, resy : Float; filterres : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   Result := False;
      [*] = ;   var gridx : Integer = floor(px+(GetMapWidth div 2)) div gc_resgrid_size;
      [*] = ;   var gridy : Integer = floor(py+(GetMapHeight div 2)) div gc_resgrid_size;
      [*] = ;   var mingridx, mingridy : Integer = -1;
      [*] = ;
      [*] = ;   var woodcount, stonecount : Integer;
      [*] = ;   var woodworker, stoneworker : Integer;
      [*] = ;   var dstfactor : Float;
      [*] = ;   var dst, reldst, minreldst : Float;
      [*] = ;
      [*] = ;   var testW, testS, testWW, testWS : Integer;
      [*] = ;   var testD : Float;
      [*] = ;   var myisland : Integer = _misc_GetIsland(px, py);
      [*] = ;   if (myisland<0) then
      [*] = ;   begin
      [*] = ;      ErrorLog('_ai_FindResourceToExtract : plInd = '+IntToStr(plInd)+' : _misc_GetIsland = -1');
      [*] = ;      exit;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var cHalfMapW : Integer = GetMapWidth div 2;
      [*] = ;   var cHalfMapH : Integer = GetMapHeight div 2;
      [*] = ;
      [*] = ;   var scanDist : Integer;
      [*] = ;   if (gScenario.bactive) then
      [*] = ;   scanDist := 25
      [*] = ;   else
      [*] = ;   scanDist := 40;
      [*] = ;   var scanDistSqr : Integer = scanDist*scanDist;
      [*] = ;   var i, j, k : Integer;
      [*] = ;   for i:=0 to gc_resgrid_countx-1 do
      [*] = ;   begin
      [*] = ;      if (Abs(gridx-i)<scanDist) then
      [*] = ;      for j:=0 to gc_resgrid_county-1 do
      [*] = ;      begin
      [*] = ;         var dstsqr : Float = Sqr(gridx-i)+Sqr(gridy-j);
      [*] = ;         //VectorDistance(gridx, 0, gridy, i, 0, j);
      [*] = ;         if (dstsqr<=scanDistSqr) then
      [*] = ;         begin
      [*] = ;            var posX : Float = i*gc_resgrid_size-cHalfMapW;
      [*] = ;            var posZ : Float = j*gc_resgrid_size-cHalfMapH;
      [*] = ;            if _misc_IsCorrectIslandPosition(plInd, posX, posZ) then
      [*] = ;            begin
      [*] = ;               if (filterres<>gc_resource_type_stone) then
      [*] = ;               woodcount := gResGrid[i,j].fResCount[gc_resource_type_wood]*gc_gameplay_resource_maxattackers_wood;
      [*] = ;               if (filterres<>gc_resource_type_wood) then
      [*] = ;               stonecount := gResGrid[i,j].fResCount[gc_resource_type_stone]*gc_gameplay_resource_maxattackers_stone;
      [*] = ;
      [*] = ;               //if ((woodcount+stonecount)>9) then
      [*] = ;               if ((woodcount+stonecount)>4) then
      [*] = ;               begin
      [*] = ;                  woodworker := gResGrid[i,j].fWorkerCount[plInd][gc_resource_type_wood];
      [*] = ;                  stoneworker := gResGrid[i,j].fWorkerCount[plInd][gc_resource_type_stone];
      [*] = ;                  dst := Sqrt(dstsqr);
      [*] = ;                  dstfactor := 2+Round(dst);
      [*] = ;
      [*] = ;                  if (not bai) then
      [*] = ;                  begin
      [*] = ;                     woodworker := woodworker*2 div 3;
      [*] = ;                     stoneworker := stoneworker*2 div 3;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  var freewood : Integer = woodcount-woodworker;
      [*] = ;                  if (freewood<0) then freewood := 0;
      [*] = ;                  var freestone : Integer = stonecount-stoneworker;
      [*] = ;                  if (freestone<0) then freestone := 0;
      [*] = ;
      [*] = ;                  reldst := dstfactor/(1+(freewood/2+freestone/2)/40);
      [*] = ;                  if (freewood+freestone>1) and ((reldst<minreldst) or (minreldst=0)) then
      [*] = ;                  begin
      [*] = ;                     minreldst := reldst;
      [*] = ;                     mingridx := i;
      [*] = ;                     mingridy := j;
      [*] = ;                     testD := dst;
      [*] = ;                     testW := freewood;
      [*] = ;                     testS := freestone;
      [*] = ;                     testWW := woodworker;
      [*] = ;                     testWS := stoneworker;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var newind : Integer;
      [*] = ;   var rndind : Integer;
      [*] = ;   if (mingridx>=0) and (mingridy>=0) then
      [*] = ;   begin
      [*] = ;      var maxind : Integer = gResGrid[mingridx,mingridy].GetCount-1;
      [*] = ;      if (maxind>0) then
      [*] = ;      rndind := floor(random*maxind+1);
      [*] = ;      for i:=0 to maxind do
      [*] = ;      begin
      [*] = ;         newind := rndind+i;
      [*] = ;         if (newind>maxind) then
      [*] = ;         newind := newind-maxind-1;
      [*] = ;         var goHnd : Integer = gResGrid[mingridx,mingridy].Get(newind);
      [*] = ;         var pres : Pointer = _res_GetTRes(goHnd);
      [*] = ;         if (pres<>nil) then
      [*] = ;         begin
      [*] = ;            var tmpfilterres : Integer = filterres;
      [*] = ;            if (filterres=gc_resource_type_none) then
      [*] = ;            begin
      [*] = ;               if (random<(testW/(testW+testS))) then
      [*] = ;               tmpfilterres := gc_resource_type_wood
      [*] = ;               else
      [*] = ;               tmpfilterres := gc_resource_type_stone;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if (tmpfilterres=gc_resource_type_none) or
      [*] = ;            ((tmpfilterres=gc_resource_type_wood) and (TRes(pres).itype=gc_resource_type_wood)) or
      [*] = ;            ((tmpfilterres=gc_resource_type_stone) and (TRes(pres).itype=gc_resource_type_stone)) then
      [*] = ;            begin
      [*] = ;               resHnd := goHnd;
      [*] = ;               resx := GetGameObjectPositionXByHandle(goHnd);
      [*] = ;               resy := GetGameObjectPositionZByHandle(goHnd);
      [*] = ;               Result := True;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // debug
      [*] = ;   {var sfilterres : String;
      [*] = ;   case filterres of
      [*] = ;      gc_resource_type_wood : sfilterres := 'wood';
      [*] = ;      gc_resource_type_stone : sfilterres := 'stone';
      [*] = ;      else
      [*] = ;      sfilterres := 'none';
      [*] = ;   end;
      [*] = ;
      [*] = ;   log('filterres='+sfilterres);
      [*] = ;   log('minreldst='+FloatToStr(minreldst));
      [*] = ;   log('minx='+IntToStr(mingridx*gc_resgrid_size-(GetMapWidth div 2)+(gc_resgrid_size div 2)));
      [*] = ;   log('miny='+IntToStr(mingridy*gc_resgrid_size-(GetMapWidth div 2)+(gc_resgrid_size div 2)));
      [*] = ;   log('dst='+FloatToStr(testD));
      [*] = ;   log('woodcounter='+IntToStr(testW));
      [*] = ;   log('stonecounter='+IntToStr(testS));
      [*] = ;   log('woodworker='+IntToStr(testWW));
      [*] = ;   log('stoneworker='+IntToStr(testWS));
      [*] = ;   log('============='); }
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_SendFreePeasantsToGainRes(plind, count, restype : Integer);
      [*] = ;begin
      [*] = ;   gTmpIntList.Clear;
      [*] = ;   _misc_CopyIntListRange(gTmpIntList, gPlayer[plind].aidata.freepeasant, 0, Min(count, gPlayer[plind].aidata.freepeasant.GetCount), true);
      [*] = ;   if (gTmpIntList.GetCount>0) then
      [*] = ;   begin
      [*] = ;      var resHnd : Integer;
      [*] = ;      var resX, resZ : Float;
      [*] = ;      if (_ai_FindResourceToExtract(plind, gPlayer[plind].aidata.centerx, gPlayer[plind].aidata.centerz, resHnd, resX, resZ, restype)) then
      [*] = ;      begin
      [*] = ;         var plHnd : Integer = GetPlayerHandleByIndex(plInd);
      [*] = ;         _order_OrderUnitsToGainResource(gTmpIntList, plHnd, resHnd, true);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_GainResourcesByPeasants(plind : Integer; onFood, onWood, onStone : Integer);
      [*] = ;begin
      [*] = ;   _misc_ProfilerBegin('_ai_GainResourcesByPeasants');
      [*] = ;   var requiredFood : Integer = gPlayer[plind].aidata.resbalance[gc_resource_type_food][0];
      [*] = ;   //population muktiplicator:
      [*] = ;   requiredFood := requiredFood+(gPlayer[plInd].counter.farmused div 350)*5;
      [*] = ;
      [*] = ;   if (onFood<requiredFood) or (gPlayer[plind].bfamine) then
      [*] = ;   _ai_SendFreePeasantsToGainFood(plind, requiredFood-onFood, onFood);
      [*] = ;   if (gPlayer[plind].aidata.freepeasant.GetCount>0) then
      [*] = ;   begin
      [*] = ;      var woodProportion : Integer = gPlayer[plind].aidata.resbalance[gc_resource_type_wood][0];
      [*] = ;      var stoneProportion : Integer = gPlayer[plind].aidata.resbalance[gc_resource_type_stone][0];
      [*] = ;      var newWood : Integer = (onWood+onStone+gPlayer[plind].aidata.freepeasant.GetCount)*woodProportion div 100;
      [*] = ;      var newStone : Integer = (onWood+onStone+gPlayer[plind].aidata.freepeasant.GetCount)*stoneProportion div 100;
      [*] = ;      if (newWood>onWood) then
      [*] = ;      _ai_SendFreePeasantsToGainRes(plind, Min(newWood-onWood, 10), gc_resource_type_wood);
      [*] = ;      if (newStone>onStone) then
      [*] = ;      _ai_SendFreePeasantsToGainRes(plind, Min(newStone-onStone, 10), gc_resource_type_stone);
      [*] = ;      if gPlayer[plind].aidata.freepeasant.GetCount>0 then
      [*] = ;      _ai_SendFreePeasantsToGainRes(plind, Min(gPlayer[plind].aidata.freepeasant.GetCount, 2), gc_resource_type_wood);
      [*] = ;   end;
      [*] = ;   _misc_ProfilerEnd('_ai_GainResourcesByPeasants');
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_ProgressMinesUpgradeByResId(plind, cid, resid : Integer) : boolean;
      [*] = ;begin
      [*] = ;   Result := False;
      [*] = ;   var id : Integer = _ai_GetMineIdByResType(plind, cid, resid);
      [*] = ;   _ai_SelectBuildingsWithId(plind, cid, id);
      [*] = ;   //sort list
      [*] = ;   var i : Integer;
      [*] = ;   for i:=gPlayer[plind].aidata.ailist.GetCount-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var goHnd : Integer = gPlayer[plind].aidata.ailist.Get(i);
      [*] = ;      var goX : Float = GetGameObjectPositionXByHandle(goHnd);
      [*] = ;      var goZ : Float = GetGameObjectPositionZByHandle(goHnd);
      [*] = ;      var dist : Float = VectorDistance(goX, 0, goZ, gPlayer[plind].aidata.centerx, 0, gPlayer[plind].aidata.centerz);
      [*] = ;      SetGameObjectTagFloatByHandle(goHnd, dist);
      [*] = ;   end;
      [*] = ;   _misc_SortListByTagFloat(gPlayer[plind].aidata.ailist, 0, gPlayer[plind].aidata.ailist.GetCount-1);
      [*] = ;   for i:=0 to gPlayer[plind].aidata.ailist.GetCount-1 do
      [*] = ;   begin
      [*] = ;      var reqlevel : Integer;
      [*] = ;      //lookup by dist not by index:
      [*] = ;      //if (i<1) then reqlevel := gPlayer[plind].aidata.resbalance[resid][0];
      [*] = ;      //if ((i>=2) and (i<3)) then reqlevel := gPlayer[plind].aidata.resbalance[resid][1];
      [*] = ;      //if (i>=3) then reqlevel := gPlayer[plind].aidata.resbalance[resid][2];
      [*] = ;      var goHnd : Integer = gPlayer[plind].aidata.ailist.Get(i);
      [*] = ;      var dist : Float = GetGameObjectTagFloatByHandle(goHnd);
      [*] = ;      if dist>gc_ai_dist_mines_lvl2 then
      [*] = ;      reqlevel := gPlayer[plind].aidata.resbalance[resid][2]
      [*] = ;      else
      [*] = ;      if dist>gc_ai_dist_mines_lvl1 then
      [*] = ;      reqlevel := gPlayer[plind].aidata.resbalance[resid][1]
      [*] = ;      else
      [*] = ;      reqlevel := gPlayer[plind].aidata.resbalance[resid][0];
      [*] = ;      var pobj : Pointer = _unit_GetTObj(goHnd);
      [*] = ;      if (pobj<>nil) and (TObj(pobj).individual.upglevel<reqlevel) then
      [*] = ;      if _ai_TryUpgradeMineEx(goHnd, cid, id, TObj(pobj).individual.upglevel) then
      [*] = ;      begin
      [*] = ;         Result := True;
      [*] = ;         Break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_ProgressMinesUpgrades(plind : Integer);
      [*] = ;begin
      [*] = ;   _misc_ProfilerBegin('_ai_ProgressMinesUpgrades');
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to gPlayer[plind].aidata.buildingslist.GetCount-1 do
      [*] = ;   begin
      [*] = ;      var goHnd : Integer = gPlayer[plind].aidata.buildingslist.Get(i);
      [*] = ;      var pobj : Pointer = _unit_GetTObj(goHnd);
      [*] = ;      if (pobj<>nil) and (TObj(pobj).orders[0].itype=gc_obj_order_type_performupgrade) then
      [*] = ;      begin
      [*] = ;         _misc_ProfilerEnd('_ai_ProgressMinesUpgrades');
      [*] = ;         exit;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   _misc_ProfilerEnd('_ai_ProgressMinesUpgrades');
      [*] = ;   var cid : Integer;
      [*] = ;   for cid:=0 to gc_MaxCountryCount-1 do
      [*] = ;   begin
      [*] = ;      if (gPlayer[plind].aidata.controllednations[cid]) then
      [*] = ;      begin
      [*] = ;         if not _ai_ProgressMinesUpgradeByResId(plind, cid, gc_resource_type_gold) then
      [*] = ;         if not _ai_ProgressMinesUpgradeByResId(plind, cid, gc_resource_type_iron) then
      [*] = ;         _ai_ProgressMinesUpgradeByResId(plind, cid, gc_resource_type_coal);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_GetBuildingIdByBaseSID(plind, cid : Integer; var sid : String) : Integer;
      [*] = ;begin
      [*] = ;   var s : String = SubStr(sid, 4, 3);
      [*] = ;   var airole : Integer;
      [*] = ;   case s of
      [*] = ;      'aca' : airole := gc_ai_unit_academi;
      [*] = ;      'bla' : airole := gc_ai_unit_smith;
      [*] = ;      'mil' : airole := gc_ai_unit_mill;
      [*] = ;      'cen' : airole := gc_ai_unit_center;
      [*] = ;      'sta' : airole := gc_ai_unit_stable;
      [*] = ;      'art' : airole := gc_ai_unit_artdepo;
      [*] = ;      'bar' : airole := gc_ai_unit_ba17;
      [*] = ;      'ba2' : airole := gc_ai_unit_ba18;
      [*] = ;   end;
      [*] = ;   Result := gPlayer[plind].aidata.aiunit[cid][airole];
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_CheckIdeaIsAlreadyInProgress(plind, cid, id : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to gc_ai_max_construction_sites-1 do
      [*] = ;   begin
      [*] = ;      if ((gPlayer[plind].aidata.buildprojects[i].used) and (gPlayer[plind].aidata.buildprojects[i].cid=cid) and (gPlayer[plind].aidata.buildprojects[i].id=id)) then
      [*] = ;      Result := Result+1;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;//_ai_lib
      [*] = ;const gc_ai_idea_type_unit = 1;
      [*] = ;const gc_ai_idea_type_upgrade = 2;
      [*] = ;
      [*] = ;function _ai_CreateMineSettlers(plind : Integer; var list : TIntegerList; armyType : Integer) : Pointer;
      [*] = ;begin
      [*] = ;   Result := nil;
      [*] = ;   var plHnd : Integer = GetPlayerHandleByIndex(plInd);
      [*] = ;   var pArmy : Pointer = gPlayer[plInd].aiData.armyList.AddSetup(plInd);
      [*] = ;   var pSquad : Pointer = _player_WriteSquadNew(plHnd, -1, 0, 0, list, false, false);
      [*] = ;   if (pArmy<>nil) and (pSquad<>nil) then
      [*] = ;   begin
      [*] = ;      TArmy(pArmy).Add(pSquad);
      [*] = ;      TSquad(pSquad).fType := armyType;
      [*] = ;      TArmy(pArmy).fSpec := gc_ai_armyspec_default;
      [*] = ;      var i : Integer;
      [*] = ;      for i:=TArmy(pArmy).fSquadList.GetCount-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pSquad : Pointer = TArmy(pArmy).fSquadList.GetPointer(i);
      [*] = ;         if pSquad<>nil then
      [*] = ;         _player_SetSquadFormation(plHnd, TSquad(pSquad).fIndex, TSquad(pSquad).fFormation, false, false);
      [*] = ;      end;
      [*] = ;      var sqCount : Integer = TArmy(pArmy).fSquadList.GetCount;
      [*] = ;      if sqCount = 0 then
      [*] = ;      begin
      [*] = ;         gPlayer[plInd].aiData.armyList.Remove(pArmy);
      [*] = ;         ErrorLog('MineSettlers army not created');
      [*] = ;      end;
      [*] = ;      Result := pArmy;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_TryMine(plind, cid, airole, count : Integer);
      [*] = ;begin
      [*] = ;   var restype : Integer = _ai_GetResByMineAiRole(airole);
      [*] = ;   var id : Integer = gPlayer[plind].aidata.aiunit[cid][airole];
      [*] = ;   //armiees in progress count:
      [*] = ;   var inProgressMines : Integer;
      [*] = ;   var armyCount : Integer = gPlayer[plInd].aiData.armyList.GetCount;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to armyCount-1 do
      [*] = ;   begin
      [*] = ;      var pArmy : Pointer = gPlayer[plInd].aiData.armyList.Get(i);
      [*] = ;      if (pArmy <> nil) and (TArmy(pArmy).fOrder.iType=gc_ai_armyorder_buildmine) then
      [*] = ;      begin
      [*] = ;         var mineHnd : Integer;
      [*] = ;         var mineUID : Integer = TArmy(pArmy).fOrder.targetUID;
      [*] = ;         if (mineUID<>0) then
      [*] = ;         begin
      [*] = ;            mineHnd := GetGameObjectHandleByUniqueId(mineUID);
      [*] = ;            if (mineHnd<>0) then
      [*] = ;            begin
      [*] = ;               var pres : Pointer = _res_GetTRes(mineHnd);
      [*] = ;               if (pres<>nil) and (TRes(pres).itype=restype) then
      [*] = ;               inProgressMines := inProgressMines+1
      [*] = ;               else
      [*] = ;               if (pres=nil) then
      [*] = ;               ErrorLog('_ai_TryMine : TArmy(pArmy).fOrder.targetUID contains deleted mine and invalid handle');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               ErrorLog('_ai_TryMine : TArmy(pArmy).fOrder.targetUID contains deleted mine and invalid handle = 0');
      [*] = ;               _unit_SetArmyOrderTarget(pArmy, 0);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if (_ai_GetUnitCount(plind, cid, airole)+_ai_CheckIdeaIsAlreadyInProgress(plind, cid, id)+inProgressMines<count) and (_unit_CanApplyCostByID(cid, id, plind)) and (inProgressMines<1) then
      [*] = ;   begin
      [*] = ;      var oreHnd : Integer = _ai_GetClosestOrePlaceWithRes(plind, restype);
      [*] = ;      if (oreHnd<>0) then
      [*] = ;      begin
      [*] = ;         var posx : Float = GetGameObjectPositionXByHandle(oreHnd);
      [*] = ;         var posz : Float = GetGameObjectPositionZByHandle(oreHnd);
      [*] = ;         var dist : Float = VectorDistance(posx, 0, posz, gPlayer[plind].aidata.centerx, 0, gPlayer[plind].aidata.centerz);
      [*] = ;         if (bai) then
      [*] = ;         begin
      [*] = ;            if (dist>30) then
      [*] = ;            begin
      [*] = ;               //if gPlayer[plind].aidata.freewarriors.GetCount<3 then
      [*] = ;               //exit;
      [*] = ;               //collecting army:
      [*] = ;               //freepeasants shouldn't be at this point, using grid
      [*] = ;               gIntegerList.Clear;
      [*] = ;               var bAllowFood : Boolean;
      [*] = ;               _ai_MakeListObjectsInRadiusByUsageBySpiral(plind, gc_obj_usage_peasant, 5, gPlayer[plind].aidata.centerx, gPlayer[plind].aidata.centerz, 50, bAllowFood, false, 1 shl gc_obj_material_body, gIntegerList, false);
      [*] = ;               if gIntegerList.GetCount>=5 then
      [*] = ;               begin
      [*] = ;                  var pikeCount : Integer;
      [*] = ;                  for i:=gPlayer[plind].aidata.freewarriors.GetCount-1 downto 0 do
      [*] = ;                  begin
      [*] = ;                     var goHnd : Integer = gPlayer[plind].aidata.freewarriors.get(i);
      [*] = ;                     var essentialtag : Integer = GetGameObjectStatesTagByHandle(goHnd) and gc_statetag_essential;
      [*] = ;                     if (essentialtag=gc_statetag_essential_none) then
      [*] = ;                     begin
      [*] = ;                        gIntegerList.add(goHnd);
      [*] = ;                        gPlayer[plind].aidata.freewarriors.delete(i);
      [*] = ;                        pikeCount := pikeCount+1;
      [*] = ;                        if pikeCount>=2 then
      [*] = ;                        break;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  //getting mine pos:
      [*] = ;                  //var pArmy : Pointer = _ai_CreateMinimalArmy(plInd, gc_ai_armytype_peasant, gIntegerList);
      [*] = ;                  var pArmy : Pointer = _ai_CreateMineSettlers(plind, gIntegerList, gc_ai_armytype_peasant);
      [*] = ;                  if (pArmy<>nil) then
      [*] = ;                  begin
      [*] = ;                     _unit_SetArmyOrderTarget(pArmy, oreHnd);
      [*] = ;
      [*] = ;                     TArmy(pArmy).fOrder.iType := gc_ai_armyorder_buildmine;
      [*] = ;                     TArmy(pArmy).fOrder.tag := cid;
      [*] = ;                     TArmy(pArmy).fOrder.tag2 := id;
      [*] = ;                     //var posx : Float = GetGameObjectPositionXByHandle(oreHnd);
      [*] = ;                     //var posz : Float = GetGameObjectPositionZByHandle(oreHnd);
      [*] = ;                     //TODO: inset
      [*] = ;                     //function _misc_TopZonePathLerp(endInd : Integer; dist : Float; flip : Boolean; var x, z : Float) : Boolean;
      [*] = ;                     //_ai_SetArmyPosition(plHnd, pArmy, posX-2, posZ-2, 0, 0, gc_obj_order_move_mode_default);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            //oldstyle creating mines with no armies:
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               gPlayer[plind].aidata.ailist.Clear;
      [*] = ;               var index : Integer = _ai_GetFreeBuildingIndex(plind);
      [*] = ;               if (index<>-1) then
      [*] = ;               begin
      [*] = ;                  var miscPlHnd : Integer = GetPlayerHandleByIndex(gc_playerind_misc);
      [*] = ;                  var sid : String = gObjProp[cid][id].sid;
      [*] = ;                  var goHnd : Integer = _player_CreateConstructionDummyBySID(miscPlHnd, cid, sid, posx, posz);
      [*] = ;                  if (goHnd<>0) then
      [*] = ;                  begin
      [*] = ;                     var canplace : Boolean = _misc_CanPlaceBuilding(goHnd, plind, gObjProp[cid][id].usage, posx, posz, 0, 0.26, 0, -1, True);
      [*] = ;                     if (canplace) then
      [*] = ;                     begin
      [*] = ;                        gPlayer[plind].aidata.buildprojects[index].SetupBuildingProject(cid, id, sid, gPlayer[plind].aidata.centerx, gPlayer[plind].aidata.centerz, 0);
      [*] = ;                        gPlayer[plind].aidata.ailist.Clear;
      [*] = ;                        var plHnd : Integer = GetPlayerHandleByIndex(plInd);
      [*] = ;                        var trgHnd : Integer = _player_ConstructBuildingList(plHnd, cid, sid, posx, posz, gPlayer[plind].aidata.ailist, false, True);
      [*] = ;                        gPlayer[plind].aidata.buildprojects[index].gohnd := trgHnd;
      [*] = ;                        gPlayer[plind].aidata.buildprojects[index].placefound := true;
      [*] = ;                        gPlayer[plind].aidata.buildprojects[index].minpeasants := 5;
      [*] = ;                        //if (gCustomObjPoints[cid, id].buildercount=0) then
      [*] = ;                        //_unit_CalcBuilderPoints(goHnd, gc_BuilderDist);
      [*] = ;                        //var bCount : Integer = Max(5, gCustomObjPoints[cid, id].builderCount div 2);
      [*] = ;                        gPlayer[plind].aidata.buildprojects[index].maxpeasants := 5;
      [*] = ;                        gPlayer[plind].aidata.unbuildhouses.Add(trgHnd);
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        var mmask : Integer = (1 shl gc_obj_material_body) or (1 shl gc_obj_material_iron);
      [*] = ;                        _misc_MakeListObjectsInRadius(posx, posz, 3, true, mmask, 0, True, gIntegerList);
      [*] = ;                        var i : Integer;
      [*] = ;                        for i:=gIntegerList.GetCount-1 downto 0 do
      [*] = ;                        begin
      [*] = ;                           var unitHnd : Integer = gIntegerList.Get(i);
      [*] = ;                           var pobj : Pointer = _unit_GetTObj(unitHnd);
      [*] = ;                           if (pobj<>nil) then
      [*] = ;                           begin
      [*] = ;                              if (TObj(pobj).pl=plind) and (not _unit_IsRunAway(unitHnd)) then
      [*] = ;                              _unit_DoRunAway(unitHnd, posx, posz);
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                     GameObjectDestroyByHandle(goHnd);
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  ErrorLog('_ai_TryMine : goHnd=0');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if (gPlayer[plind].playeradviser.adviser.benable and gPlayer[plind].playeradviser.adviser.bconstruct) and (dist<40) then
      [*] = ;         begin
      [*] = ;            if (not bai) and (airole<>gc_ai_unit_minegold) then
      [*] = ;            id := gPlayer[plind].aidata.aiunit[cid][gc_ai_unit_minegold];
      [*] = ;            var val : Integer = _misc_TwoIntToOne(cid, id);
      [*] = ;            if (gPlayer[plind].playeradviser.buildings.IndexOf(val)<0) then
      [*] = ;            begin
      [*] = ;               gPlayer[plind].playeradviser.buildings.Add(val);
      [*] = ;               gbool_gui_updateadviseradvice := True;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_GetIdleMinesList(plind : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   Result := False;
      [*] = ;   gPlayer[plind].aidata.ailist.Clear;
      [*] = ;   var myisland : Integer = _misc_GetIsland(gPlayer[plind].aidata.centerx, gPlayer[plind].aidata.centerz);
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to gPlayer[plind].aidata.mines.GetCount-1 do
      [*] = ;   begin
      [*] = ;      var goHnd : Integer = gPlayer[plind].aidata.mines.Get(i);
      [*] = ;      var pobj : Pointer = _unit_GetTObj(goHnd);
      [*] = ;      if (pobj<>nil) then
      [*] = ;      begin
      [*] = ;         var usage : Integer = gObjProp[TObj(pobj).cid][TObj(pobj).id].usage;
      [*] = ;         if (usage=gc_obj_usage_mine) and ((_ai_GetInsideCount(goHnd)+TObj(pobj).insidereserved)<(gObjProp[TObj(pobj).cid][TObj(pobj).id].peasantabsorber+TObj(pobj).individual.addpeasantabsorber)) then
      [*] = ;         begin
      [*] = ;            var posX : Float = GetGameObjectPositionXByHandle(goHnd);
      [*] = ;            var posZ : Float = GetGameObjectPositionZByHandle(goHnd);
      [*] = ;            if _misc_IsCorrectIslandPosition(plInd, posX, posZ) then
      [*] = ;            gPlayer[plind].aidata.ailist.Add(goHnd);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if (gPlayer[plind].aidata.ailist.GetCount>0)then
      [*] = ;   Result := True;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_FillMines(plind : Integer);
      [*] = ;begin
      [*] = ;   _misc_ProfilerBegin('_ai_FillMines');
      [*] = ;   if (_ai_GetIdleMinesList(plind)) then
      [*] = ;   begin
      [*] = ;      var i, j : Integer;
      [*] = ;      for i:=0 to gPlayer[plind].aidata.ailist.GetCount-1 do
      [*] = ;      begin
      [*] = ;         var goHnd : Integer = gPlayer[plind].aidata.ailist.Get(i);
      [*] = ;         var pobj : Pointer = _unit_GetTObj(goHnd);
      [*] = ;         if (pobj<>nil) then
      [*] = ;         begin
      [*] = ;            var reqpeasants : Integer = (gObjProp[TObj(pobj).cid][TObj(pobj).id].peasantabsorber+TObj(pobj).individual.addpeasantabsorber)-(_ai_GetInsideCount(goHnd)+TObj(pobj).insidereserved);
      [*] = ;            //fill with idle peasants first
      [*] = ;            if (reqpeasants>0) then
      [*] = ;            begin
      [*] = ;               gTmpIntList.Clear;
      [*] = ;               _misc_CopyIntListRange(gTmpIntList, gPlayer[plind].aidata.freepeasant, 0, Min(reqpeasants, gPlayer[plind].aidata.freepeasant.GetCount), True);
      [*] = ;               if (gTmpIntList.GetCount<reqpeasants) then
      [*] = ;               begin
      [*] = ;                  reqpeasants := reqpeasants-gTmpIntList.GetCount;
      [*] = ;                  var mmask : Integer = (1 shl gc_obj_material_body);
      [*] = ;                  _misc_MakeListObjectsInRadius(gPlayer[plind].aidata.centerx, gPlayer[plind].aidata.centerz, 25, true, mmask, 0, True, gIntegerList);
      [*] = ;                  for j:=gIntegerList.GetCount-1 downto 0 do
      [*] = ;                  begin
      [*] = ;                     var unitHnd : Integer = gIntegerList.Get(j);
      [*] = ;                     var pobj2 : Pointer = _unit_GetTObj(unitHnd);
      [*] = ;                     if (pobj2<>nil) then
      [*] = ;                     begin
      [*] = ;                        var porder : Pointer = TObj(pobj2).orders[0];
      [*] = ;                        var porderinfo : Pointer = TObj(pobj2).orders[0].info;
      [*] = ;                        if (TObj(pobj2).pl=plind) and (gObjProp[TObj(pobj2).cid][TObj(pobj2).id].usage=gc_obj_usage_peasant) and
      [*] = ;                        (TOrder(porder).itype=gc_obj_order_type_gainres) and (TOrderInfo(porderinfo).restype<>gc_resource_type_food) and (TObj(pobj2).squad=-1) then
      [*] = ;                        begin
      [*] = ;                           var essentialtag : Integer = GetGameObjectStatesTagByHandle(unitHnd) and gc_statetag_essential;
      [*] = ;                           if (essentialtag=gc_statetag_essential_none) then
      [*] = ;                           //ErrorLog('!!!Tried essentialtag<>gc_statetag_essential_none to go inside mine!!!');
      [*] = ;                           gTmpIntList.Add(unitHnd);
      [*] = ;                           if gTmpIntList.GetCount>=reqpeasants then
      [*] = ;                           break;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               gPtrList.Clear;
      [*] = ;               _player_OrderUnitsToGoInside(plInd, gTmpIntList, gPtrList, goHnd, true, true);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   _misc_ProfilerEnd('_ai_FillMines');
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_GetMineUpgrade();
      [*] = ;begin
      [*] = ;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_UpgradeMine();
      [*] = ;begin
      [*] = ;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_TryUnit(plind : Integer; cid, airole, count : Integer; ballowhuman : Boolean);
      [*] = ;begin
      [*] = ;   var id : Integer = gPlayer[plind].aidata.aiunit[cid][airole];
      [*] = ;   if (id<>-1) and (count<>0) then
      [*] = ;   begin
      [*] = ;      var plHnd : Integer = GetPlayerHandleByIndex(plInd);
      [*] = ;      var sid : String = gObjProp[cid][id].sid;
      [*] = ;      var p : pointer;
      [*] = ;      //log('cid:'+IntToStr(cid)+' id:'+IntToStr(id)+' sid:'+sid);
      [*] = ;      if (gObjProp[cid][id].bbuilding) then
      [*] = ;      begin
      [*] = ;         if ((_unit_CanApplyCostByID(cid, id, plind)) and
      [*] = ;         (_player_CheckAccessControlRequirements(plHnd, cid, sid)=gc_result_checkaccesscontrolreq_ok) and
      [*] = ;         ((((_ai_GetUnitCount(plind, cid, airole)+_ai_CheckIdeaIsAlreadyInProgress(plind, cid, id)<count)) and (airole<>gc_ai_unit_house)) or
      [*] = ;         ((_ai_CheckIdeaIsAlreadyInProgress(plind, cid, id)<3) and (airole=gc_ai_unit_house)))) then
      [*] = ;         begin
      [*] = ;            if ((airole<>gc_ai_unit_minegold) and (airole<>gc_ai_unit_mineiron) and (airole<>gc_ai_unit_minecoal)) then
      [*] = ;            begin
      [*] = ;               p := gPlayer[plind].aidata.bestprojects.Add;
      [*] = ;               TAiIdea(p).cid := cid;
      [*] = ;               //TAiIdea(p).sid := sid;
      [*] = ;               TAiIdea(p).id := id;
      [*] = ;               TAiIdea(p).airole := airole;
      [*] = ;               TAiIdea(p).ideatype := gc_ai_idea_type_unit;
      [*] = ;               //log(sid+' count_list: '+IntToStr(_ai_GetUnitCount(plind, cid, airole))+' in progress: '+IntToStr(_ai_CheckIdeaIsAlreadyInProgress(plind, cid, id))+' count: '+IntToStr(count));
      [*] = ;            end else
      [*] = ;            begin
      [*] = ;               //if (airole=gc_ai_unit_tower) then
      [*] = ;               //begin
      [*] = ;                  //   _ai_TryTower
      [*] = ;               //end else
      [*] = ;               _misc_ProfilerBegin('_ai_TryMine');
      [*] = ;               _ai_TryMine(plind, cid, airole, count);
      [*] = ;               _misc_ProfilerEnd('_ai_TryMine');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else //it is unit try to build it
      [*] = ;      begin
      [*] = ;         if ((_unit_CanApplyCountCostByID(cid, id, plind, count))
      [*] = ;         and (_player_CheckAccessControlRequirements(plHnd, cid, sid)=gc_result_checkaccesscontrolreq_ok))
      [*] = ;         and (bai or ballowhuman) then
      [*] = ;         begin
      [*] = ;            p := gPlayer[plind].aidata.bestprojects.Add;
      [*] = ;            TAiIdea(p).cid := cid;
      [*] = ;            //TAiIdea(p).sid := sid;
      [*] = ;            TAiIdea(p).id := id;
      [*] = ;            TAiIdea(p).ideatype := gc_ai_idea_type_unit;
      [*] = ;            TAiIdea(p).airole := airole;
      [*] = ;            TAiIdea(p).count := count;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_TryUnitExt(plind : Integer; cid, producerairole, airole, neededTotalCount : Integer);
      [*] = ;begin
      [*] = ;   var producercount : Integer = _ai_GetUnitCount(plind, cid, producerairole);
      [*] = ;   var have : Integer = _ai_GetUnitCount(plind, cid, airole);
      [*] = ;   if (have<neededTotalCount) then
      [*] = ;   _ai_TryUnit(plind, cid, airole, Min(producercount, neededTotalCount-have), False);
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_IsUpgradeInProgressOrDone(plind, cid : Integer; upgind : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   Result := False;
      [*] = ;   if ((gPlayer[plInd].upgstate[cid][upgind].done) or (gPlayer[plInd].upgstate[cid][upgind].inprogress)) then
      [*] = ;   Result := True;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_TryUpgrade(plind, cid, aiupgrade : Integer);
      [*] = ;begin
      [*] = ;   var plHnd : Integer = GetPlayerHandleByIndex(plInd);
      [*] = ;   var id : Integer = gPlayer[plind].aidata.upgradeid[cid][aiupgrade];
      [*] = ;   var sid : String = gCountry[cid].upgrade[id].id;
      [*] = ;   if ((not bai) or (not _ai_IsUpgradeInProgressOrDone(plind, cid, id))) and (_player_CheckAccessControlRequirements(plHnd, cid, sid)=gc_result_checkaccesscontrolreq_ok) and (_unit_CanApplyUpgradeCostBySID(plHnd, cid, sid)) then
      [*] = ;   begin
      [*] = ;      var buildingid : Integer = _ai_GetBuildingIdByBaseSID(plind, cid, sid);
      [*] = ;      _ai_SelectBuildingsWithId(plind, cid, buildingid);
      [*] = ;      if (gPlayer[plind].aidata.ailist.GetCount>0) then
      [*] = ;      begin
      [*] = ;         if (bai) then
      [*] = ;         _unit_MakeUpgrade(plHnd, gPlayer[plind].aidata.ailist, id, True, True)
      [*] = ;         else
      [*] = ;         if (gPlayer[plind].playeradviser.adviser.benable and gPlayer[plind].playeradviser.adviser.bupgrades) then
      [*] = ;         begin
      [*] = ;            var val : Integer = _misc_TwoIntToOne(cid, id);
      [*] = ;            if (gPlayer[plind].playeradviser.upgradeseconomy.IndexOf(val)<0) then
      [*] = ;            begin
      [*] = ;               gPlayer[plind].playeradviser.upgradeseconomy.Add(val);
      [*] = ;               gbool_gui_updateadviseradvice := True;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_TryUnitUpgradeEx(plind, cid, id : Integer; var sid : String; bprocesshuman : Boolean);
      [*] = ;begin
      [*] = ;   //var bai : Boolean = gPlayer[plInd].bai;
      [*] = ;   if bai or bprocesshuman then
      [*] = ;   begin
      [*] = ;      var plHnd : Integer = GetPlayerHandleByIndex(plInd);
      [*] = ;      if ((not bai) or (not _ai_IsUpgradeInProgressOrDone(plind, cid, id))) and (_player_CheckAccessControlRequirements(plHnd, cid, sid)=gc_result_checkaccesscontrolreq_ok) then
      [*] = ;      begin
      [*] = ;         var food, wood, stone, gold, iron, coal : Integer;
      [*] = ;         _country_GetUpgradeCostBySID(cid, sid, food, wood, stone, gold, iron, coal);
      [*] = ;         if (bai) then
      [*] = ;         begin
      [*] = ;            if (food>0) then
      [*] = ;            food := food+1100;
      [*] = ;            if (gold>0) then
      [*] = ;            gold := gold+150;
      [*] = ;         end;
      [*] = ;         if ((not gPlayer[plInd].res[gc_resource_type_food]>=food)
      [*] = ;         and (not gPlayer[plInd].res[gc_resource_type_wood]>=wood)
      [*] = ;         and (not gPlayer[plInd].res[gc_resource_type_stone]>=stone)
      [*] = ;         and (not gPlayer[plInd].res[gc_resource_type_gold]>=gold)
      [*] = ;         and (not gPlayer[plInd].res[gc_resource_type_iron]>=iron)
      [*] = ;         and (not gPlayer[plInd].res[gc_resource_type_coal]>=coal)) then
      [*] = ;         begin
      [*] = ;            var buildingid : Integer = _ai_GetBuildingIdByBaseSID(plind, cid, sid);
      [*] = ;            _ai_SelectBuildingsWithId(plind, cid, buildingid);
      [*] = ;            if (gPlayer[plind].aidata.ailist.GetCount>0) then
      [*] = ;            begin
      [*] = ;               if (bai) then
      [*] = ;               _unit_MakeUpgrade(plHnd, gPlayer[plind].aidata.ailist, id, True, True)
      [*] = ;               else
      [*] = ;               if (gPlayer[plind].playeradviser.adviser.benable and gPlayer[plind].playeradviser.adviser.bupgrades) then
      [*] = ;               begin
      [*] = ;                  var val : Integer = _misc_TwoIntToOne(cid, id);
      [*] = ;                  if (gPlayer[plind].playeradviser.upgradesmilitary.IndexOf(val)<0) then
      [*] = ;                  begin
      [*] = ;                     gPlayer[plind].playeradviser.upgradesmilitary.Add(val);
      [*] = ;                     gbool_gui_updateadviseradvice := True;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_TryUnitUpgrade(plind, cid, airole, node, maxlevel : Integer; bprocesshuman : Boolean);
      [*] = ;begin
      [*] = ;   //var bai : Boolean = gPlayer[plInd].bai;
      [*] = ;   if (bai or bprocesshuman) and (maxlevel>0) then
      [*] = ;   begin
      [*] = ;      //getting current level:
      [*] = ;      var i : Integer;
      [*] = ;      var currentlevel : Integer = -1;
      [*] = ;      var id : Integer;
      [*] = ;      var sid : String;
      [*] = ;      if (node=1) then
      [*] = ;      begin
      [*] = ;         for i:=gPlayer[plind].aidata.unitupg[cid][airole].attackupgrade-1 downto 0 do
      [*] = ;         begin
      [*] = ;            id := gPlayer[plind].aidata.unitupg[cid][airole].attackupgradeid[i];
      [*] = ;            if (not bai and gPlayer[plInd].upgstate[cid][id].done) or (bai and _ai_IsUpgradeInProgressOrDone(plind, cid, id)) then
      [*] = ;            begin
      [*] = ;               currentlevel := i;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if ((currentlevel<gPlayer[plind].aidata.unitupg[cid][airole].attackupgrade) and (currentlevel<maxlevel))  then
      [*] = ;         begin
      [*] = ;            if (currentlevel=-1) then currentlevel := 1 else currentlevel := currentlevel+1;
      [*] = ;            id := gPlayer[plind].aidata.unitupg[cid][airole].attackupgradeid[currentlevel];
      [*] = ;            sid := gCountry[cid].upgrade[id].id;
      [*] = ;            _ai_TryUnitUpgradeEx(plind, cid, id, sid, bprocesshuman);
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         for i:=gPlayer[plind].aidata.unitupg[cid][airole].defenceupgrade-1 downto 0 do
      [*] = ;         begin
      [*] = ;            id := gPlayer[plind].aidata.unitupg[cid][airole].defenceupgradeid[i];
      [*] = ;            if (not bai and gPlayer[plInd].upgstate[cid][id].done) or (bai and _ai_IsUpgradeInProgressOrDone(plind, cid, id)) then
      [*] = ;            begin
      [*] = ;               currentlevel := i;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if ((currentlevel<gPlayer[plind].aidata.unitupg[cid][airole].attackupgrade) and (currentlevel<maxlevel)) then
      [*] = ;         begin
      [*] = ;            if (currentlevel=-1) then
      [*] = ;            currentlevel := 1
      [*] = ;            else
      [*] = ;            currentlevel := currentlevel+1;
      [*] = ;            id := gPlayer[plind].aidata.unitupg[cid][airole].defenceupgradeid[currentlevel];
      [*] = ;            sid := gCountry[cid].upgrade[id].id;
      [*] = ;            _ai_TryUnitUpgradeEx(plind, cid, id, sid, bprocesshuman);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function CheckHumanUpgradeRecommend(plind, cid, airole, mincount : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   Result := _ai_GetUnitCount(plind, cid, airole)>=mincount;
      [*] = ;   if (Result) then
      [*] = ;   begin
      [*] = ;      _ai_TryUnitUpgrade(plind, cid, airole, 1, 7, True);
      [*] = ;      _ai_TryUnitUpgrade(plind, cid, airole, 2, 7, True);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_FindCenter(var x, y : Float; plHnd : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   //Result := False;
      [*] = ;   Result := True;
      [*] = ;   x := 0;
      [*] = ;   y := 0;
      [*] = ;   var count : Integer;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=GetPlayerGameObjectsCountByHandle(plHnd)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var goHnd : Integer = GetGameObjectHandleByIndex(i, plHnd);
      [*] = ;      if (GetGameObjectPlayableObjectByHandle(goHnd)) and (GetGameObjectVisibleByHandle(goHnd)) then
      [*] = ;      begin
      [*] = ;         var pobj : Pointer = _misc_GetObjectArgData(goHnd, gc_argunit_obj);
      [*] = ;         if (pobj<>nil) then
      [*] = ;         begin
      [*] = ;            if (gObjProp[TObj(pobj).cid][TObj(pobj).id].usage=gc_obj_usage_peasant) then
      [*] = ;            begin
      [*] = ;               x := x+GetGameObjectPositionXByHandle(goHnd);
      [*] = ;               y := y+GetGameObjectPositionZByHandle(goHnd);
      [*] = ;               count := count+1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if (count>0) then
      [*] = ;   begin
      [*] = ;      x := x/count;
      [*] = ;      y := y/count;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_EnumUnits(plind : Integer);
      [*] = ;begin
      [*] = ;   var bAdviserRepair : Boolean = ((not bai) and gPlayer[plind].playeradviser.adviser.benable and ((gPlayer[plind].playeradviser.adviser.beconomy and gPlayer[plind].playeradviser.adviser.brepairbuildings) or gPlayer[plind].playeradviser.adviser.bconstruct));
      [*] = ;   //enum units by type for ai
      [*] = ;   gPlayer[plind].aidata.peasantlist.Clear;
      [*] = ;   gPlayer[plind].aidata.freepeasant.Clear;
      [*] = ;   gPlayer[plind].aidata.buildingslist.Clear;
      [*] = ;   gPlayer[plind].aidata.mines.Clear;
      [*] = ;   gPlayer[plind].aidata.storelist.Clear;
      [*] = ;   gPlayer[plind].aidata.milllist.Clear;
      [*] = ;   gPlayer[plind].aidata.unbuildhouses.Clear;
      [*] = ;   gPlayer[plind].aidata.towers.Clear;
      [*] = ;   gPlayer[plind].aidata.damagedBuildings.Clear;
      [*] = ;   var goHnd, smhnd, essentialtag, airole, cid, id, squad, statetag, usage : Integer;
      [*] = ;   var pobj, pobjprop, pSquad, pArmy : Pointer;
      [*] = ;   var goX, goZ : Float;
      [*] = ;   var i, j : Integer;
      [*] = ;   for i:=0 to gc_MaxCountryCount-1 do
      [*] = ;   gPlayer[plind].aidata.controllednations[i] := False;
      [*] = ;
      [*] = ;   for i:=gPlayer[plInd].squads.GetCount-1 downto 0 do
      [*] = ;   begin
      [*] = ;      pSquad := gPlayer[plInd].squads.Get(i);
      [*] = ;      TSquad(pSquad).fMoveCount := 0;
      [*] = ;      TSquad(pSquad).fAttackCount := 0;
      [*] = ;      TSquad(pSquad).fDelayCount := 0;
      [*] = ;      TSquad(pSquad).fCurX := 0;
      [*] = ;      TSquad(pSquad).fCurZ := 0;
      [*] = ;      TSquad(pSquad).fTag := 0;
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i:=gPlayer[plInd].aiData.armyList.GetCount-1 downto 0 do
      [*] = ;   begin
      [*] = ;      pArmy := gPlayer[plInd].aiData.armyList.Get(i);
      [*] = ;      if pArmy<>nil then
      [*] = ;      begin
      [*] = ;         TArmy(pArmy).fTag := 0;
      [*] = ;         TArmy(pArmy).fCurTopZone := -1;
      [*] = ;         TArmy(pArmy).fCurX := 0;
      [*] = ;         TArmy(pArmy).fCurZ := 0;
      [*] = ;         TArmy(pArmy).fSquadsCurX := 0;
      [*] = ;         TArmy(pArmy).fSquadsCurZ := 0;
      [*] = ;         TArmy(pArmy).fForce := 0;
      [*] = ;         TArmy(pArmy).fRegion := -1;
      [*] = ;         TArmy(pArmy).fOnEnemyLand := false;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i:=0 to gc_MaxCountryCount-1 do
      [*] = ;   begin
      [*] = ;      gPlayer[plInd].aiData.officer17[i] := 0;
      [*] = ;      gPlayer[plInd].aiData.drummer17[i] := 0;
      [*] = ;      gPlayer[plInd].aiData.officer18[i] := 0;
      [*] = ;      gPlayer[plInd].aiData.drummer18[i] := 0;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //TODO: replace it with FillMem (?)
      [*] = ;   for i:=0 to gc_ai_unit_max_unit do
      [*] = ;   for j:=0 to gc_MaxCountryCount-1 do
      [*] = ;   gPlayer[plind].aidata.unitsamount[j][i] := 0;
      [*] = ;
      [*] = ;   var bfreepeasantlongidle : Boolean = not bai and (GetGameTime<90);
      [*] = ;   var plHnd : Integer = GetPlayerHandleByIndex(plInd);
      [*] = ;   for i:=GetPlayerGameObjectsCountByHandle(plHnd)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      goHnd := GetGameObjectHandleByIndex(i, plHnd);
      [*] = ;      statetag := GetGameObjectStatesTagByHandle(goHnd);
      [*] = ;      if ((statetag and gc_statetag_essential_none)<>0) then
      [*] = ;      begin
      [*] = ;         smhnd := GetGameObjectStateMachineHandle(goHnd); // Optimization : pobj := _misc_GetObjectArgData(goHnd, gc_argunit_obj);
      [*] = ;         if (smhnd<>0) then
      [*] = ;         pobj := StateMachineGetArgDataByInd(smhnd, gc_argunit_obj)
      [*] = ;         else
      [*] = ;         pobj := nil;
      [*] = ;
      [*] = ;         if (pobj<>nil) and (not TObj(pobj).bdead) then
      [*] = ;         begin
      [*] = ;            cid := TObj(pobj).cid;
      [*] = ;            id := TObj(pobj).id;
      [*] = ;            pobjprop := gObjProp[cid][id];
      [*] = ;            airole := TObjProp(pobjprop).airole;
      [*] = ;            squad := TObj(pObj).squad;
      [*] = ;            if (airole<>gc_ai_unit_none) then
      [*] = ;            begin
      [*] = ;               gPlayer[plind].aidata.unitsamount[cid][airole] := gPlayer[plind].aidata.unitsamount[cid][airole]+1;
      [*] = ;               //adding military
      [*] = ;               if (not TObjProp(pobjprop).bbuilding) then
      [*] = ;               begin
      [*] = ;                  if (airole=gc_ai_unit_peasant) and (TObj(pobj).insideofuid=0) then
      [*] = ;                  begin
      [*] = ;                     gPlayer[plind].aidata.controllednations[cid] := true;
      [*] = ;                     gPlayer[plind].aidata.peasantlist.Add(goHnd);
      [*] = ;                     if (TObj(pobj).orders[0].itype=gc_obj_order_type_none) and (squad=-1) and ((not bfreepeasantlongidle and (TObj(pobj).standtime>0.5)) or (bfreepeasantlongidle and (TObj(pobj).standtime>3))) then
      [*] = ;                     gPlayer[plind].aidata.freepeasant.Add(goHnd);
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               if (TObj(pobj).bbuilt) then
      [*] = ;               begin
      [*] = ;                  if (TObjProp(pobjprop).usage=gc_obj_usage_mine) then
      [*] = ;                  gPlayer[plind].aidata.mines.Add(goHnd)
      [*] = ;                  else
      [*] = ;                  case airole of
      [*] = ;                     gc_ai_unit_center : begin
      [*] = ;                        gPlayer[plind].aidata.controllednations[cid] := true;
      [*] = ;                        gPlayer[plind].aidata.storelist.Add(goHnd);
      [*] = ;                     end;
      [*] = ;                     gc_ai_unit_tower : gPlayer[plind].aidata.towers.Add(goHnd);
      [*] = ;                     gc_ai_unit_store : gPlayer[plind].aidata.storelist.Add(goHnd);
      [*] = ;                     gc_ai_unit_mill : gPlayer[plind].aidata.milllist.Add(goHnd);
      [*] = ;                  end;
      [*] = ;                  if (airole<>gc_ai_unit_house) then
      [*] = ;                  begin
      [*] = ;                     if (TObj(pObj).hp<gPlayer[plInd].objbase[TObj(pobj).cid][TObj(pobj).id].maxhp) then
      [*] = ;                     gPlayer[plind].aidata.damagedBuildings.Add(goHnd);
      [*] = ;                     //houses not used and not couted any way:
      [*] = ;                     gPlayer[plind].aidata.buildingslist.Add(goHnd);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if squad < 0 then
      [*] = ;            begin
      [*] = ;               case aiRole of
      [*] = ;                  gc_ai_unit_officer17 : begin
      [*] = ;                     if bAdviseProduceOfficers then
      [*] = ;                     countofficers17 := countofficers17+1;
      [*] = ;                     if gPlayer[plInd].aiData.officer17[cid] = 0 then
      [*] = ;                     gPlayer[plInd].aiData.officer17[cid] := goHnd;
      [*] = ;                  end;
      [*] = ;                  gc_ai_unit_drummer17 : begin
      [*] = ;                     if bAdviseProduceOfficers then
      [*] = ;                     countdrummers17 := countdrummers17+1;
      [*] = ;                     if gPlayer[plInd].aiData.drummer17[cid] = 0 then
      [*] = ;                     gPlayer[plInd].aiData.drummer17[cid] := goHnd;
      [*] = ;                  end;
      [*] = ;                  gc_ai_unit_officer18 : begin
      [*] = ;                     if bAdviseProduceOfficers then
      [*] = ;                     countofficers18 := countofficers18+1;
      [*] = ;                     if gPlayer[plInd].aiData.officer18[cid] = 0 then
      [*] = ;                     gPlayer[plInd].aiData.officer18[cid] := goHnd;
      [*] = ;                  end;
      [*] = ;                  gc_ai_unit_drummer18 : begin
      [*] = ;                     if bAdviseProduceOfficers then
      [*] = ;                     countdrummers18 := countdrummers18+1;
      [*] = ;                     if gPlayer[plInd].aiData.drummer18[cid] = 0 then
      [*] = ;                     gPlayer[plInd].aiData.drummer18[cid] := goHnd;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if not TObjProp(pobjprop).bbuilding then
      [*] = ;            begin
      [*] = ;               pSquad := _misc_GetTSquad(plInd, squad);
      [*] = ;               goX := GetGameObjectPositionXByHandle(goHnd);
      [*] = ;               goZ := GetGameObjectPositionZByHandle(goHnd);
      [*] = ;               var goRegion : Integer = _misc_GetRegionByPos(goX, goZ);
      [*] = ;
      [*] = ;               TSquad(pSquad).fCurX := TSquad(pSquad).fCurX+goX;
      [*] = ;               TSquad(pSquad).fCurZ := TSquad(pSquad).fCurZ+goZ;
      [*] = ;               TSquad(pSquad).fTag := TSquad(pSquad).fTag+1;
      [*] = ;
      [*] = ;               if ((statetag and gc_statetag_move_walk)<>0) then
      [*] = ;               TSquad(pSquad).fMoveCount := TSquad(pSquad).fMoveCount+1
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if (TObjProp(pobjprop).bArtillery) then
      [*] = ;                  begin
      [*] = ;                     usage := TObjProp(pobjprop).usage;
      [*] = ;                     if (usage = gc_obj_usage_cannon) or (usage = gc_obj_usage_mortar) or (usage = gc_obj_usage_supermortar) then
      [*] = ;                     begin
      [*] = ;                        var curOrder : Integer = -1;
      [*] = ;                        if TObj(pObj).orders[0].iType = gc_obj_order_type_move then
      [*] = ;                        curOrder := 0
      [*] = ;                        else
      [*] = ;                        if ((TObj(pObj).orders[0].iType = gc_obj_order_type_attackobj) or (TObj(pObj).orders[0].iType = gc_obj_order_type_attackpoint)) and
      [*] = ;                        (TObj(pObj).orders[1].iType = gc_obj_order_type_move) then
      [*] = ;                        curOrder := 1;
      [*] = ;
      [*] = ;                        if curOrder >= 0 then
      [*] = ;                        begin
      [*] = ;                           var ordX : Float = TObj(pObj).orders[curOrder].info.x;
      [*] = ;                           var ordZ : Float = TObj(pObj).orders[curOrder].info.y;
      [*] = ;                           var goX : Float = GetGameObjectPositionXByHandle(goHnd);
      [*] = ;                           var goZ : Float = GetGameObjectPositionZByHandle(goHnd);
      [*] = ;                           if ((Sqr(ordX-goX)+Sqr(ordZ-goZ))>gc_objectEpsilonDistSqr) then
      [*] = ;                           TSquad(pSquad).fMoveCount := TSquad(pSquad).fMoveCount+1;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  if TObjProp(pObjProp).transport > 0 then
      [*] = ;                  begin
      [*] = ;                     if statetag and gc_statetag_move = gc_statetag_move_turn then
      [*] = ;                     TSquad(pSquad).fMoveCount := TSquad(pSquad).fMoveCount+1;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if (not TObjProp(pobjprop).bpriest) then
      [*] = ;               begin
      [*] = ;                  if ((statetag and gc_statetag_action_none)<>0) then
      [*] = ;                  begin
      [*] = ;                     if (TObj(pObj).attackDelay > 0) then
      [*] = ;                     TSquad(pSquad).fDelayCount := TSquad(pSquad).fDelayCount+1
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  if ((statetag and gc_statetag_action_attack)<>0) then
      [*] = ;                  TSquad(pSquad).fAttackCount := TSquad(pSquad).fAttackCount+1;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if TSquad(pSquad).fArmy >= 0 then
      [*] = ;               begin
      [*] = ;                  pArmy := gPlayer[plInd].aiData.armyList.Get(TSquad(pSquad).fArmy);
      [*] = ;                  if pArmy <> nil then
      [*] = ;                  begin
      [*] = ;                     TArmy(pArmy).fTag := TArmy(pArmy).fTag+1;
      [*] = ;                     TArmy(pArmy).fCurX := TArmy(pArmy).fCurX+goX;
      [*] = ;                     TArmy(pArmy).fCurZ := TArmy(pArmy).fCurZ+goZ;
      [*] = ;                     TArmy(pArmy).fForce := TArmy(pArmy).fForce+TObjProp(pobjprop).aiForce;
      [*] = ;                     if (TArmy(pArmy).fRegion < 0) and (goRegion >= 0) then
      [*] = ;                     TArmy(pArmy).fRegion := goRegion;
      [*] = ;
      [*] = ;                     if gbool_peacemode and _unit_IsOnEnemyTerritory(goHnd, pObj)
      [*] = ;                     and (_unit_GetTagStateByType(goHnd, gc_statetag_move) <> gc_statetag_move_walk) then
      [*] = ;                     TArmy(pArmy).fOnEnemyLand := true;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if (pobj=nil) then
      [*] = ;         ErrorLog('ProgressAI EnumUnits pobj=nil')
      [*] = ;         else
      [*] = ;         if (TObj(pobj).bdead) then
      [*] = ;         ErrorLog('ProgressAI EnumUnits bdead');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if ((statetag and gc_statetag_essential_birth)<>0) then
      [*] = ;      begin
      [*] = ;         pobj := _misc_GetObjectArgData(goHnd, gc_argunit_obj);
      [*] = ;         if (pobj<>nil) then
      [*] = ;         begin
      [*] = ;            cid := TObj(pobj).cid;
      [*] = ;            id := TObj(pobj).id;
      [*] = ;            pobjprop := gObjProp[cid][id];
      [*] = ;            airole := TObjProp(pobjprop).airole;
      [*] = ;            if (not TObjProp(pobjprop).bbuilding) then
      [*] = ;            begin
      [*] = ;               if (airole<>gc_ai_unit_none) and (airole<>gc_ai_unit_peasant) then
      [*] = ;               gPlayer[plind].aidata.unitsamount[cid][airole] := gPlayer[plind].aidata.unitsamount[cid][airole]+1;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if bAdviserRepair and not TObj(pobj).bbuilt and not TObjProp(pobjprop).bwall then
      [*] = ;            begin
      [*] = ;               var index : Integer = -1;
      [*] = ;               for j:=0 to gc_ai_max_construction_sites-1 do
      [*] = ;               begin
      [*] = ;                  if (gPlayer[plind].aidata.buildprojects[j].used) and (gPlayer[plind].aidata.buildprojects[j].gohnd=goHnd) then
      [*] = ;                  begin
      [*] = ;                     index := j;
      [*] = ;                     break;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               if (index=-1) then
      [*] = ;               _unit_AIAddToBuildProjects(plind, goHnd);
      [*] = ;            end;
      [*] = ;
      [*] = ;            gPlayer[plind].aidata.unbuildhouses.Add(goHnd);
      [*] = ;            if (airole=gc_ai_unit_store) then
      [*] = ;            gPlayer[plind].aidata.storelist.Add(goHnd);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i:=gPlayer[plInd].squads.GetCount-1 downto 0 do
      [*] = ;   begin
      [*] = ;      pSquad := gPlayer[plInd].squads.Get(i);
      [*] = ;      if TSquad(pSquad).fTag > 0 then
      [*] = ;      begin
      [*] = ;         TSquad(pSquad).fCurX := TSquad(pSquad).fCurX / TSquad(pSquad).fTag;
      [*] = ;         TSquad(pSquad).fCurZ := TSquad(pSquad).fCurZ / TSquad(pSquad).fTag;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i:=gPlayer[plInd].aiData.armyList.GetCount-1 downto 0 do
      [*] = ;   begin
      [*] = ;      pArmy := gPlayer[plInd].aiData.armyList.Get(i);
      [*] = ;      if (pArmy<>nil) then
      [*] = ;      begin
      [*] = ;         if not TArmy(pArmy).fActive then
      [*] = ;         begin
      [*] = ;            var active : Boolean = true;
      [*] = ;            for j := TArmy(pArmy).fSquadList.GetCount-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var pSquad : Pointer = TArmy(pArmy).fSquadList.GetPointer(j);
      [*] = ;               if TSquad(pSquad).GetCount <> TSquad(pSquad).fTag then
      [*] = ;               begin
      [*] = ;                  active := false;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            TArmy(pArmy).fActive := active;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var active : Boolean = true;
      [*] = ;         var sqCount : Integer = TArmy(pArmy).fSquadList.GetCount;
      [*] = ;         if sqCount > 0 then
      [*] = ;         begin
      [*] = ;            for j := TArmy(pArmy).fSquadList.GetCount-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var pSquad : Pointer = TArmy(pArmy).fSquadList.GetPointer(j);
      [*] = ;               if TSquad(pSquad).GetCount <> TSquad(pSquad).fTag then
      [*] = ;               begin
      [*] = ;                  active := false;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;
      [*] = ;               TArmy(pArmy).fSquadsCurX := TArmy(pArmy).fSquadsCurX + TSquad(pSquad).fCurX;
      [*] = ;               TArmy(pArmy).fSquadsCurZ := TArmy(pArmy).fSquadsCurZ + TSquad(pSquad).fCurZ;
      [*] = ;            end;
      [*] = ;
      [*] = ;            TArmy(pArmy).fSquadsCurX := TArmy(pArmy).fSquadsCurX / sqCount;
      [*] = ;            TArmy(pArmy).fSquadsCurZ := TArmy(pArmy).fSquadsCurZ / sqCount;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if not TArmy(pArmy).fActive then
      [*] = ;         TArmy(pArmy).fActive := active;
      [*] = ;
      [*] = ;         if TArmy(pArmy).fTag = 0 then
      [*] = ;         begin
      [*] = ;            if TArmy(pArmy).fActive then
      [*] = ;            gPlayer[plInd].aiData.armyList.Delete(i);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            TArmy(pArmy).fCurX := TArmy(pArmy).fCurX / TArmy(pArmy).fTag;
      [*] = ;            TArmy(pArmy).fCurZ := TArmy(pArmy).fCurZ / TArmy(pArmy).fTag;
      [*] = ;            var topZone : Integer = TopologyGetZoneIndex(TArmy(pArmy).fCurX, TArmy(pArmy).fCurZ);
      [*] = ;            if topZone >= 0 then
      [*] = ;            TArmy(pArmy).fCurTopZone := topZone;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_ResourcesDistributionScript(plind, cid, onFood, onWood, onStone : Integer);
      [*] = ;begin
      [*] = ;   if (gPlayer[plind].aidata.developmentera[cid]=gc_ai_era_wood) then
      [*] = ;   begin
      [*] = ;      //testing code
      [*] = ;      _ai_SetResouceBalance(plind, gc_resource_type_gold, 1, 1, 0);
      [*] = ;      _ai_SetResouceBalance(plind, gc_resource_type_iron, 1, 0, 0);
      [*] = ;      _ai_SetResouceBalance(plind, gc_resource_type_coal, 1, 0, 0);
      [*] = ;
      [*] = ;      if ((cid<>cid_ukr) and (cid<>cid_rus) and (cid<>cid_alg) and (cid<>cid_tur)) then
      [*] = ;      begin
      [*] = ;         _ai_SetResouceBalance(plind, gc_resource_type_wood, 60, -1, -1);
      [*] = ;         _ai_SetResouceBalance(plind, gc_resource_type_stone, 40, -1, -1);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (cid=cid_ukr) then
      [*] = ;         begin
      [*] = ;            _ai_SetResouceBalance(plind, gc_resource_type_wood, 80, -1, -1);
      [*] = ;            _ai_SetResouceBalance(plind, gc_resource_type_stone, 20, -1, -1);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if ((cid=cid_alg) or (cid=cid_tur)) and (gMap.settings.gen.resourcestart=ai_st_res_normal) then
      [*] = ;         begin
      [*] = ;            _ai_SetResouceBalance(plind, gc_resource_type_wood, 50, -1, -1);
      [*] = ;            _ai_SetResouceBalance(plind, gc_resource_type_stone, 50, -1, -1);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            _ai_SetResouceBalance(plind, gc_resource_type_wood, 75, -1, -1);
      [*] = ;            _ai_SetResouceBalance(plind, gc_resource_type_stone, 25, -1, -1);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if ((cid=cid_rus) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_ba17)>=4) and gMap.settings.gen.resourcestart<>ai_st_res_millions) then
      [*] = ;      begin
      [*] = ;         _ai_SetResouceBalance(plind, gc_resource_type_wood, 60, -1, -1);
      [*] = ;         _ai_SetResouceBalance(plind, gc_resource_type_stone, 40, -1, -1);
      [*] = ;      end;
      [*] = ;
      [*] = ;      var pikemanUnit : Integer = _ai_GetInf17Unit(plind, cid);
      [*] = ;      var bPikemanUpgraded : Boolean = (_ai_GetCountProduced(plind, cid, pikemanUnit)>20) and (_ai_GetUnitCurrentUpgLevel(plInd, cid, pikemanUnit, 1)>=3) and (_ai_GetUnitCurrentUpgLevel(plInd, cid, pikemanUnit, 2)>=3);
      [*] = ;      var modifier : Float;
      [*] = ;      if (bPikemanUpgraded) or (not bai) then
      [*] = ;      modifier := 1
      [*] = ;      else
      [*] = ;      modifier := 1.3;
      [*] = ;
      [*] = ;      //setting resource balance
      [*] = ;      var peacount : Integer = _ai_GetUnitCountAnyFaction(plind, gc_ai_unit_peasant);
      [*] = ;      if (cid<>cid_rus) and (cid<>cid_pol) then
      [*] = ;      begin
      [*] = ;         if (peacount<30) then
      [*] = ;         _ai_SetResouceBalance(plind, gc_resource_type_food, round(12*modifier), -1, -1)
      [*] = ;         else
      [*] = ;         if (peacount<45) then
      [*] = ;         _ai_SetResouceBalance(plind, gc_resource_type_food, round(21*modifier), -1, -1)
      [*] = ;         else
      [*] = ;         if (peacount<85) then
      [*] = ;         _ai_SetResouceBalance(plind, gc_resource_type_food, round(27*modifier), -1, -1)
      [*] = ;         else
      [*] = ;         if (peacount<120) then
      [*] = ;         _ai_SetResouceBalance(plind, gc_resource_type_food, round(36*modifier), -1, -1)
      [*] = ;         else
      [*] = ;         _ai_SetResouceBalance(plind, gc_resource_type_food, round(45*modifier), -1, -1);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (peacount<30) then
      [*] = ;         _ai_SetResouceBalance(plind, gc_resource_type_food, round(16*modifier), -1, -1)
      [*] = ;         else
      [*] = ;         if (peacount<45) then
      [*] = ;         _ai_SetResouceBalance(plind, gc_resource_type_food, round(24*modifier), -1, -1)
      [*] = ;         else
      [*] = ;         if (peacount<85) then
      [*] = ;         _ai_SetResouceBalance(plind, gc_resource_type_food, round(31*modifier), -1, -1)
      [*] = ;         else
      [*] = ;         if (peacount<120) then
      [*] = ;         _ai_SetResouceBalance(plind, gc_resource_type_food, round(40*modifier), -1, -1)
      [*] = ;         else
      [*] = ;         _ai_SetResouceBalance(plind, gc_resource_type_food, round(49*modifier), -1, -1);
      [*] = ;      end;
      [*] = ;
      [*] = ;      //_ai_SetResouceBalance(plind, gc_resource_type_wood, 60, -1, -1);
      [*] = ;      //_ai_SetResouceBalance(plind, gc_resource_type_stone, 40, -1, -1);
      [*] = ;
      [*] = ;      if ((_ai_GetUnitCount(plind, cid, gc_ai_unit_ba17)>=2) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_center)>=4) and (cid<>cid_ukr)) or
      [*] = ;      ((cid=cid_ukr) and (_ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_horse))) then
      [*] = ;      begin
      [*] = ;         _ai_SetResouceBalance(plind, gc_resource_type_gold, 1, 1, 0);
      [*] = ;         _ai_SetResouceBalance(plind, gc_resource_type_iron, 1, 0, 0);
      [*] = ;         _ai_SetResouceBalance(plind, gc_resource_type_coal, 1, 0, 0);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if ((_ai_GetUnitCount(plind, cid, gc_ai_unit_center)>=3) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_ba17)>=2) and (gMap.settings.gen.resourcestart<>ai_st_res_millions)) then
      [*] = ;      begin
      [*] = ;         if (peacount>150) then
      [*] = ;         _ai_SetResouceBalance(plind, gc_resource_type_food, 65, -1, -1);
      [*] = ;         _ai_SetResouceBalance(plind, gc_resource_type_wood, 50, -1, -1);
      [*] = ;         _ai_SetResouceBalance(plind, gc_resource_type_stone, 50, -1, -1);
      [*] = ;         if ((_ai_GetUnitCount(plind, cid, gc_ai_unit_ba17)>=2) and (cid<>cid_ukr) and (_ai_DoUnit18cGrade(plind, cid)) and (_ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_century))) then
      [*] = ;         begin
      [*] = ;            _ai_SetResouceBalance(plind, gc_resource_type_gold, 7, 1, 1);
      [*] = ;            _ai_SetResouceBalance(plind, gc_resource_type_iron, 1, 1, 0);
      [*] = ;            _ai_SetResouceBalance(plind, gc_resource_type_coal, 1, 1, 0);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if ((cid=cid_ukr) or (cid=cid_tur) or (cid=cid_alg)) and (_ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_horse)) and (_ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_horseswords)) then
      [*] = ;         begin
      [*] = ;            _ai_SetResouceBalance(plind, gc_resource_type_gold, 7, 1, 1);
      [*] = ;            _ai_SetResouceBalance(plind, gc_resource_type_iron, 1, 1, 0);
      [*] = ;            _ai_SetResouceBalance(plind, gc_resource_type_coal, 1, 1, 0);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if (_ai_GetUnitCountAnyFaction(plind, gc_ai_unit_center)>3) then
      [*] = ;      begin
      [*] = ;         if (peacount>250) then
      [*] = ;         _ai_SetResouceBalance(plind, gc_resource_type_food, 85, -1, -1);
      [*] = ;         if (_ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_century) and (_ai_DoUnit18cGrade(plind, cid))) then
      [*] = ;         begin
      [*] = ;            if _ai_GetUnitCount(plind, cid, gc_ai_unit_ba18)>0 then
      [*] = ;            _ai_SetResouceBalance(plind, gc_resource_type_gold, 7, 7, 1);
      [*] = ;            _ai_SetResouceBalance(plind, gc_resource_type_iron, 7, 1, 1);
      [*] = ;            _ai_SetResouceBalance(plind, gc_resource_type_coal, 7, 1, 1);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if (gMap.settings.gen.resourcestart=ai_st_res_millions) then
      [*] = ;      begin
      [*] = ;         _ai_SetResouceBalance(plind, gc_resource_type_food, 60, -1, -1);
      [*] = ;         _ai_SetResouceBalance(plind, gc_resource_type_wood, 15, -1, -1);
      [*] = ;         _ai_SetResouceBalance(plind, gc_resource_type_stone, 25, -1, -1);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_RequestUnitsProduction(plind, cid : Integer);
      [*] = ;begin
      [*] = ;   var numpeasants : Integer = _ai_GetUnitCount(plind, cid, gc_ai_unit_center)*2;
      [*] = ;   if (_ai_GetUnitCountAnyFaction(plind, gc_ai_unit_peasant)<400) or (_ai_GetUnitCount(plind, cid, gc_ai_unit_peasant)<30) then
      [*] = ;   begin
      [*] = ;      if not bai then
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_peasant, -1, (gPlayer[plind].playeradviser.adviser.benable) and (gPlayer[plind].playeradviser.adviser.beconomy) and (gPlayer[plind].playeradviser.adviser.bproducepeasants))
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (not gPlayer[plind].res[gc_resource_type_food]>700) then
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_peasant, numpeasants, False)
      [*] = ;         else
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_peasant, 1, False);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   _ai_TryUnit(plind, cid, gc_ai_unit_priest, 1, False);
      [*] = ;
      [*] = ;   var pikemanUnit : Integer = _ai_GetInf17Unit(plind, cid);
      [*] = ;   var pikemanCount : Integer = _ai_GetUnitCount(plind, cid, pikemanUnit);
      [*] = ;   var numOfficers : Integer = pikemanCount div 36;
      [*] = ;   if (numOfficers=0) and (pikemanCount>28) then
      [*] = ;   numOfficers := 1;
      [*] = ;   var numReiters : Integer = _ai_GetUnitCount(plind, cid, gc_ai_unit_stable)*2;
      [*] = ;   var numInf18 : Integer = _ai_GetUnitCount(plind, cid, gc_ai_unit_ba18)*2;
      [*] = ;
      [*] = ;   var bar_count : Integer = _ai_GetUnitCount(plind, cid, gc_ai_unit_ba17)*2;
      [*] = ;   if (cid<>cid_ukr) then
      [*] = ;   begin
      [*] = ;      if bAdviseProduceOfficers then
      [*] = ;      begin
      [*] = ;         if countofficers17=0 then
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_officer17, 1, (gPlayer[plind].playeradviser.adviser.benable) and (gPlayer[plind].playeradviser.adviser.bquartermaster) and gPlayer[plind].playeradviser.adviser.bproduceofficers);
      [*] = ;         if countdrummers17=0 then
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_drummer17, 1, (gPlayer[plind].playeradviser.adviser.benable) and (gPlayer[plind].playeradviser.adviser.bquartermaster) and gPlayer[plind].playeradviser.adviser.bproduceofficers);
      [*] = ;         if countofficers18=0 then
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_officer18, 1, (gPlayer[plind].playeradviser.adviser.benable) and (gPlayer[plind].playeradviser.adviser.bquartermaster) and gPlayer[plind].playeradviser.adviser.bproduceofficers);
      [*] = ;         if countdrummers18=0 then
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_drummer18, 1, (gPlayer[plind].playeradviser.adviser.benable) and (gPlayer[plind].playeradviser.adviser.bquartermaster) and gPlayer[plind].playeradviser.adviser.bproduceofficers);
      [*] = ;      end;
      [*] = ;      if (bai) and (((_ai_GetUnitCount(plind, cid, gc_ai_unit_drummer17)<numOfficers) or (_ai_GetUnitCount(plind, cid, gc_ai_unit_officer17)<numOfficers)) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_academi)>0) and (not gPlayer[plind].res[gc_resource_type_gold]>300)) then
      [*] = ;      begin
      [*] = ;         if (_ai_GetUnitCount(plind, cid, gc_ai_unit_drummer17)<numOfficers) then
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_drummer17, 1, False);
      [*] = ;         if (_ai_GetUnitCount(plind, cid, gc_ai_unit_officer17)<numOfficers) then
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_officer17, 1, False);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (pikemanCount>=36*4) or (cid=cid_alg) then
      [*] = ;         begin
      [*] = ;            if (cid=cid_alg) then
      [*] = ;            begin
      [*] = ;               _ai_TryUnit(plind, cid, pikemanUnit, bar_count, False);
      [*] = ;               if (not bIsWaterMap) then
      [*] = ;               begin
      [*] = ;                  if (_ai_GetUnitCount(plind, cid, gc_ai_unit_archer)<gPlayer[plInd].counter.farmused div 3) then
      [*] = ;                  _ai_TryUnit(plind, cid, gc_ai_unit_archer, bar_count, False);
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if (_ai_GetUnitCount(plind, cid, gc_ai_unit_archer)<gPlayer[plInd].counter.farmused div 5) then
      [*] = ;                  _ai_TryUnit(plind, cid, gc_ai_unit_archer, bar_count, False);
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (pikemanCount<=(36*7+gc_ai_max_guards)) then
      [*] = ;               begin
      [*] = ;                  _ai_TryUnit(plind, cid, gc_ai_unit_musk17, 1, False);
      [*] = ;                  _ai_TryUnit(plind, cid, pikemanUnit, bar_count, False);
      [*] = ;               end
      [*] = ;               else
      [*] = ;               _ai_TryUnit(plind, cid, gc_ai_unit_musk17, bar_count, False);
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         _ai_TryUnit(plind, cid, pikemanUnit, bar_count, False);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (cid<>cid_ukr) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_academi)>0) then
      [*] = ;      begin
      [*] = ;         if (bai) then
      [*] = ;         begin
      [*] = ;            if (_ai_GetUnitCurrentUpgLevel(plInd, cid, pikemanUnit, 1)>=3) and (_ai_GetUnitCurrentUpgLevel(plInd, cid, pikemanUnit, 2)>=3) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_officer17)>9) then
      [*] = ;            begin
      [*] = ;               _ai_TryUnitUpgrade(plind, cid, gc_ai_unit_officer17, 1, 2, False);
      [*] = ;               _ai_TryUnitUpgrade(plind, cid, gc_ai_unit_officer17, 2, 2, False);
      [*] = ;               //_ai_TryUnitUpgrade(plind, cid, gc_ai_unit_drummer17, 2, 2); // annoys player
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if (_ai_GetUnitCount(plind, cid, gc_ai_unit_officer17)>9) then
      [*] = ;            begin
      [*] = ;               _ai_TryUnitUpgrade(plind, cid, gc_ai_unit_officer17, 1, 2, False);
      [*] = ;               _ai_TryUnitUpgrade(plind, cid, gc_ai_unit_officer17, 2, 2, False);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      //ukrainian infantry
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_musk17, bar_count, False);
      [*] = ;      _ai_TryUnitUpgrade(plind, cid, gc_ai_unit_musk17, 1, 7, False);
      [*] = ;      _ai_TryUpgrade(plind, cid, gc_ai_upg_quickshot1);
      [*] = ;   end;
      [*] = ;
      [*] = ;   //cav17 unit:
      [*] = ;   var cav17unit : Integer = _ai_GetCav17Unit(plind, cid);
      [*] = ;   if _ai_NationIsEurope(cid) and (not _ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_century)) then
      [*] = ;   _ai_TryUnit(plind, cid, cav17unit, numReiters, False)
      [*] = ;   else
      [*] = ;   if not _ai_NationIsEurope(cid) then
      [*] = ;   _ai_TryUnit(plind, cid, cav17unit, numReiters, False);
      [*] = ;
      [*] = ;   var maxLevelAtt : Integer = 7;
      [*] = ;   var maxLevelDef : Integer = 7;
      [*] = ;   case difficulty of
      [*] = ;      gc_player_difficulty_easy : begin
      [*] = ;         maxLevelAtt := 0;
      [*] = ;         maxLevelDef := 0;
      [*] = ;      end;
      [*] = ;      gc_player_difficulty_normal : begin
      [*] = ;         maxLevelAtt := 2;
      [*] = ;         maxLevelDef := 3;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if _ai_NationIsEurope(cid) then
      [*] = ;   begin
      [*] = ;      if (_ai_GetCountProduced(plind, cid, cav17unit)>5) then
      [*] = ;      begin
      [*] = ;         if (cav17unit=gc_ai_unit_dragoon17) then
      [*] = ;         _ai_TryUnitUpgrade(plind, cid, cav17unit, 1, Min(3, maxLevelAtt), False);
      [*] = ;         if (cav17unit=gc_ai_unit_reitar) then
      [*] = ;         begin
      [*] = ;            _ai_TryUnitUpgrade(plind, cid, cav17unit, 1, Min(3, maxLevelAtt-1), False);
      [*] = ;            _ai_TryUnitUpgrade(plind, cid, cav17unit, 2, Min(3, maxLevelAtt-1), False);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if _ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_horse) then
      [*] = ;   begin
      [*] = ;      if _ai_NationIsEurope(cid) then
      [*] = ;      begin
      [*] = ;         if (_ai_GetCountProduced(plind, cid, cav17unit)>5) then
      [*] = ;         begin
      [*] = ;            if (cav17unit=gc_ai_unit_reitar) then
      [*] = ;            _ai_TryUnitUpgrade(plind, cid, cav17unit, 1, Min(3, maxLevelAtt-1), False)
      [*] = ;            else
      [*] = ;            _ai_TryUnitUpgrade(plind, cid, cav17unit, 1, maxLevelAtt, False);
      [*] = ;            if (cav17unit=gc_ai_unit_dragoon17) then
      [*] = ;            _ai_TryUnitUpgrade(plind, cid, cav17unit, 2, 1, False)
      [*] = ;            else
      [*] = ;            if (cav17unit=gc_ai_unit_reitar) then
      [*] = ;            _ai_TryUnitUpgrade(plind, cid, cav17unit, 2, Min(5, maxLevelAtt-1), False)
      [*] = ;            else
      [*] = ;            _ai_TryUnitUpgrade(plind, cid, cav17unit, 2, maxLevelDef, False)
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (_ai_GetCountProduced(plind, cid, cav17unit)>5) then
      [*] = ;         begin
      [*] = ;            _ai_TryUnitUpgrade(plind, cid, cav17unit, 1, maxLevelAtt, False);
      [*] = ;            _ai_TryUnitUpgrade(plind, cid, cav17unit, 2, maxLevelDef, False);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var inf18unit : Integer = _ai_GetInf18Unit(plind, cid);
      [*] = ;   var cav18unit : Integer = _ai_GetCav18Unit(plind, cid);
      [*] = ;
      [*] = ;   var inf18Count : Integer = _ai_GetUnitCount(plind, cid, inf18Unit);
      [*] = ;   var numOfficers18 : Integer = inf18Count div 36;
      [*] = ;   if (cid=cid_sco) then
      [*] = ;   begin
      [*] = ;      _ai_TryUnit(plind, cid, inf18unit, numInf18, False);
      [*] = ;      if (inf18Count>40) then
      [*] = ;      begin
      [*] = ;         _ai_TryUnitUpgrade(plind, cid, inf18unit, 1, maxLevelAtt, False);
      [*] = ;         _ai_TryUnitUpgrade(plind, cid, inf18unit, 2, maxLevelDef, False)
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if _ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_century) then
      [*] = ;   begin
      [*] = ;      _ai_TryUnit(plind, cid, cav18unit, numReiters, False);
      [*] = ;      _ai_TryUnit(plind, cid, inf18unit, numInf18, False);
      [*] = ;      if ((inf18Count>40) and (_ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_food250))) then
      [*] = ;      begin
      [*] = ;         _ai_TryUnitUpgrade(plind, cid, inf18unit, 1, maxLevelAtt, False);
      [*] = ;         if (inf18unit<>gc_ai_unit_uniq_inf18) then
      [*] = ;         _ai_TryUnitUpgrade(plind, cid, inf18unit, 2, maxLevelDef, False)
      [*] = ;         else
      [*] = ;         _ai_TryUnitUpgrade(plind, cid, inf18unit, 2, 1, False);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (_ai_GetUnitCount(plind, cid, gc_ai_unit_drummer18)<numOfficers18) then
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_drummer18, 1, False);
      [*] = ;      if (_ai_GetUnitCount(plind, cid, gc_ai_unit_officer18)<numOfficers18) then
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_officer18, 1, False);
      [*] = ;
      [*] = ;      if ((_ai_GetUnitCount(plind, cid, cav18unit)>40) and (_ai_DoUnit18cGrade(plind, cid)) and (_ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_food250))) then
      [*] = ;      begin
      [*] = ;         _ai_TryUnitUpgrade(plind, cid, cav18unit, 1, maxLevelAtt, False);
      [*] = ;         if cav18unit=gc_ai_unit_dragun18 then
      [*] = ;         _ai_TryUnitUpgrade(plind, cid, cav18unit, 2, 2, False)
      [*] = ;         else
      [*] = ;         _ai_TryUnitUpgrade(plind, cid, cav18unit, 2, maxLevelDef, False)
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //mercenaries
      [*] = ;   if (cid=cid_ukr) and ((gPlayer[plind].aidata.guardsCount>0) or (gPlayer[plind].aidata.guardsTotal>0)) and (gPlayer[plind].aiData.guards.GetCount < gc_ai_max_guards) then
      [*] = ;   _ai_TryUnit(plind, cid, gc_ai_unit_light_dip, 5, False);
      [*] = ;
      [*] = ;   if gMap.settings.gen.resourcestart<>ai_st_res_millions then
      [*] = ;   begin
      [*] = ;      if difficulty>gc_player_difficulty_normal then
      [*] = ;      begin
      [*] = ;         if ((not gPlayer[plind].res[gc_resource_type_gold]>3600) and
      [*] = ;         (_ai_GetUnitCount(plind, cid, gc_ai_unit_dragundip)=0)) then
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_dragundip, 32{36}, False);
      [*] = ;      end;
      [*] = ;      if ((not gPlayer[plind].res[gc_resource_type_gold]>1000) and
      [*] = ;      (_ai_GetUnitCount(plind, cid, gc_ai_unit_grendip)<16) and
      [*] = ;      ((cid<>cid_alg) or (_ai_GetUnitCount(plind, cid, gc_ai_unit_archer)<16))) then
      [*] = ;      begin
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_archer, 36, False);
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_grendip, 36, False);
      [*] = ;      end;
      [*] = ;      if (_ai_GetUnitCount(plind, cid,  gc_ai_unit_cossackdip)<6) then
      [*] = ;      begin
      [*] = ;         var numdiver : Integer;
      [*] = ;         case difficulty of
      [*] = ;            gc_player_difficulty_normal : numdiver := 0;
      [*] = ;            gc_player_difficulty_hard : numdiver := 2;
      [*] = ;            gc_player_difficulty_veryhard : numdiver := 4;
      [*] = ;            gc_player_difficulty_impossible : numdiver := 4;
      [*] = ;         end;
      [*] = ;         if (numdiver>0) then
      [*] = ;         numdiver := numdiver+_ai_GetDiverArmiesCount(plInd);
      [*] = ;         if (numdiver>0) then
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_cossackdip, 10*numdiver, False);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (_ai_GetUnitCount(plind, cid, gc_ai_unit_dragundip)=0) then
      [*] = ;   if _ai_NationIsEurope(cid) then
      [*] = ;   _ai_TryUnit(plind, cid, gc_ai_unit_dragundip, 200, False)
      [*] = ;   else
      [*] = ;   if (cid=cid_ukr) then
      [*] = ;   _ai_TryUnit(plind, cid, gc_ai_unit_dragundip, 800, False)
      [*] = ;   else
      [*] = ;   _ai_TryUnit(plind, cid, gc_ai_unit_dragundip, 600, False);
      [*] = ;
      [*] = ;   var num_depo : integer = _ai_GetUnitCountAnyFaction(plind, gc_ai_unit_artdepo);
      [*] = ;   var num_depo_my_cid : integer = _ai_GetUnitCount(plind, cid, gc_ai_unit_artdepo);
      [*] = ;   //var gun_count : Integer = num_depo*5;
      [*] = ;   var cannon_count : integer = ClampInt(num_depo*6, 6, 30);
      [*] = ;   var howitzer_count, mortar_count : Integer;
      [*] = ;   if (difficulty>gc_player_difficulty_easy) then
      [*] = ;   begin
      [*] = ;      howitzer_count := ClampInt(num_depo*2, 2, 8);
      [*] = ;      mortar_count := ClampInt(num_depo*8, 8, 40);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   cannon_count := cannon_count div 2;
      [*] = ;   if (num_depo>1) then
      [*] = ;   begin
      [*] = ;      var curcount : Integer = _ai_GetUnitCountAnyFaction(plind, gc_ai_unit_mortar);
      [*] = ;      var ordercount : Integer = Min(num_depo_my_cid, mortar_count-curcount-ordered_mortar_count);
      [*] = ;      ordercount := Max(ordercount, 0);
      [*] = ;      ordered_mortar_count := ordered_mortar_count+ordercount;
      [*] = ;      if (curcount<mortar_count) then
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_mortar, ordercount, False);
      [*] = ;
      [*] = ;      curcount := _ai_GetUnitCountAnyFaction(plind, gc_ai_unit_cannon);
      [*] = ;      ordercount := Min(num_depo_my_cid*2, cannon_count-curcount-ordered_cannon_count);
      [*] = ;      ordercount := Max(ordercount, 0);
      [*] = ;      ordered_cannon_count := ordered_cannon_count+ordercount;
      [*] = ;      if (curcount<cannon_count) then
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_cannon, ordercount, False);
      [*] = ;
      [*] = ;      curcount := _ai_GetUnitCountAnyFaction(plind, gc_ai_unit_howitzer);
      [*] = ;      ordercount := Min(2, howitzer_count-curcount-ordered_howitzer_count);
      [*] = ;      ordercount := Max(ordercount, 0);
      [*] = ;      ordered_howitzer_count := ordered_howitzer_count+ordercount;
      [*] = ;      if (curcount<howitzer_count) then
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_howitzer, ordercount, False);
      [*] = ;      //if _ai_NationIsEurope(cid) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_mbarrel)<5) then
      [*] = ;      //_ai_TryUnit(plind, cid, gc_ai_unit_mbarrel, 1);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_MakeUpgrades(plind, cid : Integer);
      [*] = ;begin
      [*] = ;   //millions:
      [*] = ;   if (gMap.settings.gen.resourcestart=ai_st_res_millions) then
      [*] = ;   _ai_TryUpgrade(plind, cid, gc_ai_upg_builders);
      [*] = ;
      [*] = ;   _ai_TryUpgrade(plind, cid, gc_ai_upg_food140);
      [*] = ;
      [*] = ;   if (_ai_GetUnitCount(plind, cid, gc_ai_unit_ba17)>=1) and _ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_food140) then
      [*] = ;   _ai_TryUpgrade(plind, cid, gc_ai_upg_reaper);
      [*] = ;
      [*] = ;   var pikemanUnit : Integer = _ai_GetInf17Unit(plind, cid);
      [*] = ;
      [*] = ;   var maxLevelAtt : Integer = 7;
      [*] = ;   var maxLevelDef : Integer = 7;
      [*] = ;   case difficulty of
      [*] = ;      gc_player_difficulty_easy : begin
      [*] = ;         maxLevelAtt := 1;
      [*] = ;         maxLevelDef := 2;
      [*] = ;      end;
      [*] = ;      gc_player_difficulty_normal : begin
      [*] = ;         maxLevelAtt := 2;
      [*] = ;         maxLevelDef := 3;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // making resource upgrades:
      [*] = ;   if _ai_GetUnitCount(plind, cid, gc_ai_unit_academi)>0 then
      [*] = ;   begin
      [*] = ;      _ai_TryUpgrade(plind, cid, gc_ai_upg_whead1);
      [*] = ;      if not bai then
      [*] = ;      begin
      [*] = ;         _ai_TryUpgrade(plind, cid, gc_ai_upg_wood);
      [*] = ;         if bai or (not bai and _ai_GetUnitCount(plind, cid, gc_ai_unit_stable)>=2) then
      [*] = ;         _ai_TryUpgrade(plind, cid, gc_ai_upg_horse);
      [*] = ;         if (_ai_GetUnitCount(plind, cid, gc_ai_unit_ba17)>=2) then
      [*] = ;         begin
      [*] = ;            _ai_TryUpgrade(plind, cid, gc_ai_upg_stone200);
      [*] = ;            _ai_TryUpgrade(plind, cid, gc_ai_upg_stone100);
      [*] = ;         end;
      [*] = ;         _ai_TryUpgrade(plind, cid, gc_ai_upg_feelds);
      [*] = ;         if _ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_horse) then
      [*] = ;         _ai_TryUpgrade(plind, cid, gc_ai_upg_horseswords);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if ((_ai_GetUnitCurrentUpgLevel(plInd, cid, pikemanUnit, 1)>=Min(3, maxLevelAtt)) and (_ai_GetUnitCurrentUpgLevel(plInd, cid, pikemanUnit, 2)>=Min(3, maxLevelAtt)) or (cid=cid_ukr)) then
      [*] = ;         begin
      [*] = ;            _ai_TryUpgrade(plind, cid, gc_ai_upg_feelds);
      [*] = ;            _ai_TryUpgrade(plind, cid, gc_ai_upg_wood);
      [*] = ;            _ai_TryUpgrade(plind, cid, gc_ai_upg_horse);
      [*] = ;         end;
      [*] = ;         if _ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_horse) then
      [*] = ;         begin
      [*] = ;            if (difficulty>gc_player_difficulty_easy) then
      [*] = ;            _ai_TryUpgrade(plind, cid, gc_ai_upg_horseswords);
      [*] = ;            if (_ai_GetUnitCount(plind, cid, gc_ai_unit_ba17)>=2) then
      [*] = ;            begin
      [*] = ;               _ai_TryUpgrade(plind, cid, gc_ai_upg_stone200);
      [*] = ;               _ai_TryUpgrade(plind, cid, gc_ai_upg_stone100);
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if _ai_NationIsEurope(cid) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_ba17)>=2) then
      [*] = ;         _ai_TryUpgrade(plind, cid, gc_ai_upg_stone100);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (bai) and ((difficulty>gc_player_difficulty_easy) and (_ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_horse) and (cid=cid_ukr)) or (cid<>cid_ukr))  then
      [*] = ;      begin
      [*] = ;         if (difficulty>gc_player_difficulty_normal) then
      [*] = ;         _ai_TryUpgrade(plind, cid, gc_ai_upg_bricks1);
      [*] = ;         _ai_TryUpgrade(plind, cid, gc_ai_upg_bricks2);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if _ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_whead2) and (_ai_NationIsEurope(cid) or (cid=cid_ukr)) then
      [*] = ;      //new food
      [*] = ;      _ai_TryUpgrade(plind, cid, gc_ai_upg_whead3)
      [*] = ;      else
      [*] = ;      _ai_TryUpgrade(plind, cid, gc_ai_upg_whead2);
      [*] = ;      if (cid=cid_tur) or (cid=cid_alg) then
      [*] = ;      begin
      [*] = ;         _ai_TryUpgrade(plind, cid, gc_ai_upg_whead2);
      [*] = ;         //check for dip house built:
      [*] = ;         if (_ai_GetUnitCount(plind, cid, gc_ai_unit_dipcenter)>0) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_center)>=3) then
      [*] = ;         _ai_TryUpgrade(plind, cid, gc_ai_upg_whead3);
      [*] = ;      end;
      [*] = ;      //make upg for mbarrel TODO: add support for mbarrel guns
      [*] = ;      //if _ai_NationIsEurope(cid) then
      [*] = ;      //_ai_TryUpgrade(plind, cid, gc_ai_upg_mbarrel);
      [*] = ;
      [*] = ;      if (bai) and (difficulty>gc_player_difficulty_easy) and (cid<>cid_ukr) then
      [*] = ;      _ai_TryUpgrade(plind, cid, gc_ai_upg_fort);
      [*] = ;
      [*] = ;      if (((_ai_GetUnitCurrentUpgLevel(plind, cid, gc_ai_unit_musk18, 1)>=6) or (_ai_GetUnitCurrentUpgLevel(plind, cid, gc_ai_unit_grenadier, 1)>=6)) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_ba18)>4)) then
      [*] = ;      _ai_TryUpgrade(plind, cid, gc_ai_upg_newsteel);
      [*] = ;
      [*] = ;      if (difficulty>gc_player_difficulty_easy) and _ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_horse) then
      [*] = ;      begin
      [*] = ;         if _ai_DoArmor(cid) then
      [*] = ;         _ai_TryUpgrade(plind, cid, gc_ai_upg_armor1);
      [*] = ;      end;
      [*] = ;      if (difficulty>gc_player_difficulty_easy) and ((cid=cid_pol) and (_ai_GetUnitCount(plind, cid,  gc_ai_unit_ba18)>=1)) then
      [*] = ;      _ai_TryUpgrade(plind, cid, gc_ai_upg_armor1);
      [*] = ;
      [*] = ;      //artillery  TODO : include checks
      [*] = ;      if (difficulty>gc_player_difficulty_easy) and ((_ai_GetUnitCount(plind, cid, gc_ai_unit_cannon)+_ai_GetUnitCount(plind, cid, gc_ai_unit_howitzer))>=5) then
      [*] = ;      begin
      [*] = ;         _ai_TryUpgrade(plind, cid, gc_ai_upg_accurency1);
      [*] = ;         _ai_TryUpgrade(plind, cid, gc_ai_upg_artlife);
      [*] = ;         if (_ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_century) or (cid=cid_ukr) or (cid=cid_tur) or (cid=cid_alg)) then
      [*] = ;         begin
      [*] = ;            //if _ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_accurency1) then // ai dont do accuracy2, it is OP with their microcontrol
      [*] = ;            //_ai_TryUpgrade(plind, cid, gc_ai_upg_accurency2);
      [*] = ;            if _ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_art10) then
      [*] = ;            _ai_TryUpgrade(plind, cid, gc_ai_upg_art5) else
      [*] = ;            _ai_TryUpgrade(plind, cid, gc_ai_upg_art10);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (bai) then
      [*] = ;   begin
      [*] = ;      if (_ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_horse) and ((_ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_stone200)) or (_ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_stone100)))) then
      [*] = ;      begin
      [*] = ;         if ((cid<>cid_ukr) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_artdepo)>0)) then
      [*] = ;         begin
      [*] = ;            _ai_TryUnitUpgrade(plind, cid, gc_ai_unit_howitzer, 2, 2, False);
      [*] = ;            _ai_TryUnitUpgrade(plind, cid, gc_ai_unit_cannon, 2, 2, False);
      [*] = ;         end;
      [*] = ;         //ukr - coal&iron more needed for unit grades:
      [*] = ;         if ((cid=cid_ukr) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_artdepo)>0) and (_ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_horse))) then
      [*] = ;         begin
      [*] = ;            _ai_TryUnitUpgrade(plind, cid, gc_ai_unit_howitzer, 2, 2, False);
      [*] = ;            _ai_TryUnitUpgrade(plind, cid, gc_ai_unit_cannon, 2, 2, False);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if((_ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_stone200)) or (_ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_stone100))) then
      [*] = ;      begin
      [*] = ;         if ((cid<>cid_ukr) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_artdepo)>0)) then
      [*] = ;         begin
      [*] = ;            _ai_TryUnitUpgrade(plind, cid, gc_ai_unit_howitzer, 2, 2, False);
      [*] = ;            _ai_TryUnitUpgrade(plind, cid, gc_ai_unit_cannon, 2, 2, False);
      [*] = ;         end;
      [*] = ;         if ((cid=cid_ukr) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_artdepo)>0)) then
      [*] = ;         begin
      [*] = ;            _ai_TryUnitUpgrade(plind, cid, gc_ai_unit_howitzer, 2, 2, False);
      [*] = ;            _ai_TryUnitUpgrade(plind, cid, gc_ai_unit_cannon, 2, 2, False);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //ukr specific grade:
      [*] = ;   if (cid=cid_ukr) or (cid=cid_sco) then
      [*] = ;   _ai_TryUpgrade(plind, cid, gc_ai_upg_food250);
      [*] = ;
      [*] = ;   //if (cid<>cid_ukr) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_artdepo)>2) then
      [*] = ;   if (bai) then
      [*] = ;   _ai_TryUpgrade(plind, cid, gc_ai_upg_fort);
      [*] = ;
      [*] = ;   //if century
      [*] = ;   var centercount : Integer = _ai_GetUnitCount(plind, cid, gc_ai_unit_center);
      [*] = ;   if (_ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_century) or cid=cid_sco) and (centercount>=2) then
      [*] = ;   begin
      [*] = ;      _ai_TryUpgrade(plind, cid, gc_ai_upg_food250);
      [*] = ;      _ai_TryUpgrade(plind, cid, gc_ai_upg_cheapmusk);
      [*] = ;      if _ai_GetTimeFromStart(plInd)>25 then //fix for millions res
      [*] = ;      begin
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_ba18, 10, False);
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_stable, 10, False);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if cid=cid_sco then
      [*] = ;      begin
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_ba18, 4, False);
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_stable, 7, False);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_ba18, 5, False);
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_stable, 7, False);
      [*] = ;      end;
      [*] = ;      _ai_TryUpgrade(plind, cid, gc_ai_upg_builders);
      [*] = ;      //18c's grades
      [*] = ;      if (_ai_GetUnitCount(plind, cid, gc_ai_unit_ba18)>2) then
      [*] = ;      begin
      [*] = ;         _ai_TryUpgrade(plind, cid, gc_ai_upg_armor2);
      [*] = ;         _ai_TryUpgrade(plind, cid, gc_ai_upg_baginet);
      [*] = ;      end;
      [*] = ;      _ai_TryUpgrade(plind, cid, gc_ai_upg_inf18);
      [*] = ;   end;
      [*] = ;   if (_ai_GetUnitCount(plind, cid, gc_ai_unit_center)>=2) then
      [*] = ;   _ai_TryUpgrade(plind, cid, gc_ai_upg_century);
      [*] = ;
      [*] = ;   if _ai_TestPowderUpgradeCondition(plind, cid) then
      [*] = ;   begin
      [*] = ;      if _ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_powder15) then
      [*] = ;      _ai_TryUpgrade(plind, cid, gc_ai_upg_powder10);
      [*] = ;      if _ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_powder20) then
      [*] = ;      _ai_TryUpgrade(plind, cid, gc_ai_upg_powder15);
      [*] = ;      if _ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_powder30) then
      [*] = ;      _ai_TryUpgrade(plind, cid, gc_ai_upg_powder20);
      [*] = ;      _ai_TryUpgrade(plind, cid, gc_ai_upg_powder30);
      [*] = ;   end;
      [*] = ;   //unit grades:
      [*] = ;
      [*] = ;   if (_ai_GetUnitCount(plind, cid, gc_ai_unit_ba17)>=1) and (_ai_GetCountProduced(plind, cid, pikemanUnit)>10) then
      [*] = ;   begin
      [*] = ;      _ai_TryUnitUpgrade(plind, cid, pikemanUnit, 1, Min(maxLevelAtt, 2), False);
      [*] = ;      _ai_TryUnitUpgrade(plind, cid, pikemanUnit, 2, Min(maxLevelDef, 2), False);
      [*] = ;   end;
      [*] = ;   var testcount : Integer = 40;
      [*] = ;   if (cid=cid_alg) or (cid=cid_tur) then
      [*] = ;   testcount := 20;
      [*] = ;   if (_ai_GetUnitCount(plind, cid, pikemanUnit)>=testcount) and (cid<>cid_ukr) then
      [*] = ;   begin
      [*] = ;      if (_ai_GetCountProduced(plind, cid, gc_ai_unit_officer17)>1) then
      [*] = ;      begin
      [*] = ;         _ai_TryUnitUpgrade(plind, cid, pikemanUnit, 1, maxLevelAtt, False);
      [*] = ;         _ai_TryUnitUpgrade(plind, cid, pikemanUnit, 2, maxLevelDef, False);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         _ai_TryUnitUpgrade(plind, cid, pikemanUnit, 1, Min(maxLevelAtt, 3), False);
      [*] = ;         _ai_TryUnitUpgrade(plind, cid, pikemanUnit, 2, Min(maxLevelDef, 3), False);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if ((_ai_GetUnitCount(plind, cid, gc_ai_unit_musk17)>20) and (cid<>cid_ukr)) or (gMap.settings.gen.resourcestart=ai_st_res_millions) then
      [*] = ;   begin
      [*] = ;      _ai_TryUnitUpgrade(plind, cid, gc_ai_unit_musk17, 1, 4, False);
      [*] = ;      _ai_TryUnitUpgrade(plind, cid, gc_ai_unit_musk17, 2, 3, False);
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (_ai_GetCountProduced(plind, cid, gc_ai_unit_musk17)>20) or (_ai_GetCountProduced(plind, cid, gc_ai_unit_musk18)>20)
      [*] = ;   or (_ai_GetCountProduced(plind, cid, gc_ai_unit_dragoon17)>20) or (_ai_GetCountProduced(plind, cid, gc_ai_unit_dragun18)>20) then
      [*] = ;   begin
      [*] = ;      _ai_TryUpgrade(plind, cid, gc_ai_upg_quickshot1);
      [*] = ;      _ai_TryUpgrade(plind, cid, gc_ai_upg_quickshot2);
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (_ai_GetCountProduced(plind, cid, gc_ai_unit_archer)>35) then
      [*] = ;   begin
      [*] = ;      if (_ai_GetUnitCurrentUpgLevel(plInd, cid, pikemanUnit, 1)>=Min(3, maxLevelAtt)) and (_ai_GetUnitCurrentUpgLevel(plInd, cid, pikemanUnit, 2)>=Min(3, maxLevelAtt)) then
      [*] = ;      _ai_TryUnitUpgrade(plind, cid, gc_ai_unit_archer, 1, maxLevelAtt, False);
      [*] = ;      //_ai_TryUnitUpgrade(plind, cid, gc_ai_unit_archer, 2, maxLevelDef, False); // too expensive
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (_ai_GetUnitCount(plind, cid, gc_ai_unit_port)>=1) then
      [*] = ;   begin
      [*] = ;      _ai_TryUpgrade(plind, cid, gc_ai_upg_shipbuild);
      [*] = ;      if (_ai_GetUnitCount(plind, cid, gc_ai_unit_artdepo)>=4) then
      [*] = ;      _ai_TryUpgrade(plind, cid, gc_ai_upg_shipspeed);
      [*] = ;      if (_ai_GetUnitCount(plind, cid, gc_ai_unit_artdepo)>=3) then
      [*] = ;      begin
      [*] = ;         _ai_TryUpgrade(plind, cid, gc_ai_upg_frigate);
      [*] = ;         _ai_TryUpgrade(plind, cid, gc_ai_upg_battleship);
      [*] = ;      end
      [*] = ;   end;
      [*] = ;   //fish boats grades:
      [*] = ;   if (_ai_GetUnitCount(plind, cid, gc_ai_unit_port)>=1) then
      [*] = ;   begin
      [*] = ;      _ai_TryUpgrade(plind, cid, gc_ai_upg_boats);
      [*] = ;      if (_ai_GetCountProduced(plind, cid, gc_ai_unit_boat)>20) then
      [*] = ;      _ai_TryUpgrade(plind, cid, gc_ai_upg_fish);
      [*] = ;   end;
      [*] = ;   if (not bai) and (gPlayer[plind].playeradviser.adviser.benable) and (gPlayer[plind].playeradviser.adviser.bupgrades) then // adviser
      [*] = ;   begin
      [*] = ;      const mincount = 36;
      [*] = ;      CheckHumanUpgradeRecommend(plind, cid, gc_ai_unit_infantry17, mincount);
      [*] = ;      CheckHumanUpgradeRecommend(plind, cid, gc_ai_unit_musk17, mincount);
      [*] = ;      CheckHumanUpgradeRecommend(plind, cid, gc_ai_unit_archer, mincount);
      [*] = ;      CheckHumanUpgradeRecommend(plind, cid, gc_ai_unit_reitar, mincount);
      [*] = ;      CheckHumanUpgradeRecommend(plind, cid, gc_ai_unit_hussar, mincount);
      [*] = ;      CheckHumanUpgradeRecommend(plind, cid, gc_ai_unit_cuirassier, mincount);
      [*] = ;      CheckHumanUpgradeRecommend(plind, cid, gc_ai_unit_dragoon17, mincount);
      [*] = ;      CheckHumanUpgradeRecommend(plind, cid, gc_ai_unit_uniq_inf17, mincount);
      [*] = ;      CheckHumanUpgradeRecommend(plind, cid, gc_ai_unit_uniq_cav17, mincount);
      [*] = ;      CheckHumanUpgradeRecommend(plind, cid, gc_ai_unit_uniq_inf18, mincount);
      [*] = ;      CheckHumanUpgradeRecommend(plind, cid, gc_ai_unit_uniq_cav18, mincount);
      [*] = ;      CheckHumanUpgradeRecommend(plind, cid, gc_ai_unit_dragun18, mincount);
      [*] = ;      CheckHumanUpgradeRecommend(plind, cid, gc_ai_unit_grenadier, mincount);
      [*] = ;      CheckHumanUpgradeRecommend(plind, cid, gc_ai_unit_musk18, mincount);
      [*] = ;      CheckHumanUpgradeRecommend(plind, cid, gc_ai_unit_officer17, 6);
      [*] = ;      CheckHumanUpgradeRecommend(plind, cid, gc_ai_unit_drummer17, 6);
      [*] = ;      CheckHumanUpgradeRecommend(plind, cid, gc_ai_unit_cannon, mincount);
      [*] = ;      CheckHumanUpgradeRecommend(plind, cid, gc_ai_unit_howitzer, mincount);
      [*] = ;      //CheckHumanUpgradeRecommend(plind, cid, gc_ai_unit_officer18, 6);
      [*] = ;      //CheckHumanUpgradeRecommend(plind, cid, gc_ai_unit_drummer18, 6);
      [*] = ;      CheckHumanUpgradeRecommend(plind, cid, gc_ai_unit_pikeman18, mincount);
      [*] = ;   end
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_BuildHouses(plind, cid, onFood, onWood, onStone : Integer);
      [*] = ;begin
      [*] = ;   if (gMap.settings.gen.resourcestart=ai_st_res_millions) then
      [*] = ;   begin
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_store, 1, False);
      [*] = ;   end;
      [*] = ;   var centercount : Integer = _ai_GetUnitCount(plind, cid, gc_ai_unit_center);
      [*] = ;
      [*] = ;   if (_ai_GetUnitCount(plind, cid, gc_ai_unit_mill)>0) then
      [*] = ;   gPlayer[plind].aidata.developmentera[cid] := gc_ai_era_wood;
      [*] = ;   if (gPlayer[plind].aidata.developmentera[cid]=gc_ai_era_food) then
      [*] = ;   begin
      [*] = ;      if (_ai_GetUnitCount(plind, cid, gc_ai_unit_mill)=0) then
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_mill, 1, False);
      [*] = ;      if (centercount=0) then
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_center, 1, False)
      [*] = ;      else
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_center, 2, False);
      [*] = ;   end;
      [*] = ;   if (gPlayer[plind].aidata.developmentera[cid]=gc_ai_era_wood) then
      [*] = ;   begin
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_mill, 1, False);
      [*] = ;      if (centercount=0) then
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_center, 1, False)
      [*] = ;      else
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_center, 2, False);
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_market, 1, False);
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_mill, 1, False);
      [*] = ;
      [*] = ;      //alg and tur spec
      [*] = ;      if ((cid=cid_tur) or (cid=cid_alg)) and (gMap.settings.gen.resourcestart=ai_st_res_normal) then
      [*] = ;      if (_ai_GetUnitCount(plind, cid, gc_ai_unit_smith)>=1) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_store)>=1) and
      [*] = ;      (_ai_GetUnitCount(plind, cid,  gc_ai_unit_market)>=1) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_ba17)>=1) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_house)=0) then
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_house, 1, false);
      [*] = ;
      [*] = ;      if (onFood>20) and (centercount>=2) and (cid<>cid_ukr) and (_ai_BuildMines(plind, cid, onFood, onWood, OnStone)) then
      [*] = ;      begin
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_minegold, 2, False);
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_mineiron, 1, False);
      [*] = ;      end;
      [*] = ;      if (_ai_GetUnitCount(plind, cid, gc_ai_unit_ba17)>=1) and (_ai_BuildMines(plind, cid, onFood, onWood, OnStone)) then
      [*] = ;      begin
      [*] = ;         if (not gPlayer[plind].res[gc_resource_type_gold] < 400) then
      [*] = ;         begin
      [*] = ;            if _ai_NationIsEurope(cid) then
      [*] = ;            _ai_TryUnit(plind, cid, gc_ai_unit_minegold, 2, False)
      [*] = ;            else
      [*] = ;            _ai_TryUnit(plind, cid, gc_ai_unit_minegold, 1, False);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_minegold, 1, False);
      [*] = ;         if not gPlayer[plind].res[gc_resource_type_iron] < 300 then
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_mineiron, 1, False);
      [*] = ;         if not gPlayer[plind].res[gc_resource_type_coal] < 300 then
      [*] = ;         begin
      [*] = ;            if (_ai_GetUnitCount(plind, cid, gc_ai_unit_mineiron)>=1) then
      [*] = ;            _ai_TryUnit(plind, cid, gc_ai_unit_minecoal, 1, False)
      [*] = ;            else
      [*] = ;            if not gPlayer[plind].res[gc_resource_type_iron] < 1000 then
      [*] = ;            _ai_TryUnit(plind, cid, gc_ai_unit_mineiron, 1, False);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (cid=cid_ukr) and ((onWood+OnFood+onStone)>45) and (_ai_BuildMines(plind, cid, onFood, onWood, OnStone)) then
      [*] = ;      begin
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_minegold, 1, False);
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_mineiron, 1, False);
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_minecoal, 1, False);
      [*] = ;      end;
      [*] = ;
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_smith, 1, False);
      [*] = ;      if (centercount>=3) then
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_ba17, 3, False)
      [*] = ;      else
      [*] = ;      if (centercount>=2) then
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_ba17, 2, False)
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (not _unit_CanApplyCountCostByID(cid, gPlayer[plind].aidata.aiunit[cid][gc_ai_unit_center], plind, 1)) then
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_ba17, 2, False)
      [*] = ;         else
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_ba17, 1, False);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (centercount>=2) then
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_center, 5, False);
      [*] = ;
      [*] = ;      if ((_ai_BuildBarracks17(cid)) and (centercount>=2)) then
      [*] = ;      begin
      [*] = ;         if (bIsWaterMap) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_port)=0) then
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_ba17, 3, False)
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if ((cid=cid_rus) and (gMap.settings.gen.resourcestart<>ai_st_res_millions)) or (cid<>cid_rus) then
      [*] = ;            _ai_TryUnit(plind, cid, gc_ai_unit_ba17, 8, False) else
      [*] = ;            _ai_TryUnit(plind, cid, gc_ai_unit_ba17, 6, False);
      [*] = ;         end;
      [*] = ;         if ((cid=cid_ukr) or (cid=cid_tur) or (cid=cid_alg)) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_ba17)>=2) then
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_stable, 5, False);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if ((cid=cid_ukr) or (cid=cid_alg) or (cid=cid_tur)) and (centercount>=2) then
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_center, 5, False);
      [*] = ;
      [*] = ;      if (cid=cid_sco) then
      [*] = ;      begin
      [*] = ;         if (_ai_GetUnitCount(plind, cid, gc_ai_unit_ba18)>=3) and (gMap.settings.gen.resourcestart<>ai_st_res_millions) then
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_center, 6, False);
      [*] = ;         if (_ai_GetUnitCount(plind, cid, gc_ai_unit_ba18)>=2) then
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_ba17, 3, False);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (_ai_GetUnitCount(plind, cid, gc_ai_unit_ba18)>=5) then
      [*] = ;      begin
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_ba17, 3, False);
      [*] = ;         if gMap.settings.gen.resourcestart<>ai_st_res_millions then
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_center, 6, False);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if ((_ai_GetUnitCount(plind, cid, gc_ai_unit_ba17)>=2) and (centercount>=2) and (cid<>cid_ukr) and (cid<>cid_rus)) then
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_academi, 1, False)
      [*] = ;      else
      [*] = ;      if (_ai_GetUnitCount(plind, cid, gc_ai_unit_ba17)>=3) and ((cid=cid_ukr) or (cid=cid_rus)) and (centercount>=2) then
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_academi, 1, False);
      [*] = ;
      [*] = ;      if (bIsWaterMap) and ((_ai_GetUnitCount(plind, cid, gc_ai_unit_ba17)>=2) and (centercount>=2) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_academi)>0)) then
      [*] = ;      begin
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_stable, 1, False);
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_artdepo, 1, False);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if ((_ai_GetUnitCount(plind, cid, gc_ai_unit_ba17)>=2) and (centercount>=2) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_academi)>0)) then
      [*] = ;      begin
      [*] = ;         if ((not bIsWaterMap) or (_ai_GetUnitCount(plind, cid, gc_ai_unit_port)>0)) then
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_dipcenter, 1, False);
      [*] = ;         var dipid : Integer = gPlayer[plind].aidata.aiunit[cid][gc_ai_unit_dipcenter];
      [*] = ;         if (_ai_GetUnitCount(plind, cid, gc_ai_unit_dipcenter)>0) or (not gPlayer[plInd].objbase[cid, dipid].bproduceenabled) then
      [*] = ;         begin
      [*] = ;            _ai_TryUnit(plind, cid, gc_ai_unit_stable, 1, False);
      [*] = ;            if (cid<>cid_rus) and _ai_NationIsEurope(cid) then
      [*] = ;            _ai_TryUnit(plind, cid, gc_ai_unit_stable, 4, False)
      [*] = ;            else
      [*] = ;            if (cid=cid_rus) then
      [*] = ;            _ai_TryUnit(plind, cid, gc_ai_unit_stable, 3, False);
      [*] = ;            _ai_TryUnit(plind, cid, gc_ai_unit_artdepo, 2, False);
      [*] = ;            if ((not bIsWaterMap) or (_ai_GetUnitCount(plind, cid, gc_ai_unit_port)>0)) then
      [*] = ;            _ai_TryUnit(plind, cid, gc_ai_unit_temple, 1, False);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if ((cid=cid_ukr) or (cid=cid_tur) or (cid=cid_alg)) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_ba17)>=2) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_stable)>=2) then
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_artdepo, 2, False);
      [*] = ;
      [*] = ;      var curnumstore : Integer = _ai_GetUnitCountAnyFaction(plInd, gc_ai_unit_store);
      [*] = ;      var numstore : Integer = Min(25, (onWood+onStone) div 25);
      [*] = ;      if not bai and numstore>10 then
      [*] = ;      numstore := 10;
      [*] = ;      if (numstore>0) then
      [*] = ;      begin
      [*] = ;         if (curnumstore<numstore) and (ordered_storehouse_count=0) then
      [*] = ;         begin
      [*] = ;            ordered_storehouse_count := ordered_storehouse_count+1;
      [*] = ;            _ai_TryUnit(plind, cid, gc_ai_unit_store, curnumstore+1, False);
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_store, 1, False);
      [*] = ;
      [*] = ;      if ((_ai_GetTimeFromStart(plind)>3) and (centercount>0)) then
      [*] = ;      begin
      [*] = ;         var farmlimit : Integer;
      [*] = ;         case gMap.settings.additional.limit of
      [*] = ;            0 : farmlimit := gc_MaxObjCount;
      [*] = ;            1 : farmlimit := gc_mapsettings_limit_1;
      [*] = ;            2 : farmlimit := gc_mapsettings_limit_2;
      [*] = ;            3 : farmlimit := gc_mapsettings_limit_3;
      [*] = ;            4 : farmlimit := gc_mapsettings_limit_4;
      [*] = ;            5 : farmlimit := gc_mapsettings_limit_5;
      [*] = ;            6 : farmlimit := gc_mapsettings_limit_6;
      [*] = ;            7 : farmlimit := gc_mapsettings_limit_7;
      [*] = ;            8 : farmlimit := gc_mapsettings_limit_8;
      [*] = ;         end;
      [*] = ;         farmlimit := Min(farmlimit, gPlayer[plInd].farm);
      [*] = ;
      [*] = ;         if (farmlimit-gPlayer[plInd].counter.farmused<20) then
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_house, 400, False);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (bai) then
      [*] = ;      begin
      [*] = ;         if (centercount>=3) and (_ai_BuildMines(plind, cid, onFood, onWood, OnStone)) then
      [*] = ;         begin
      [*] = ;            if _ai_GetUnitCount(plind, cid, gc_ai_unit_stable)>1 then
      [*] = ;            begin
      [*] = ;               _ai_TryUnit(plind, cid, gc_ai_unit_minegold, 7, False);
      [*] = ;               _ai_TryUnit(plind, cid, gc_ai_unit_mineiron, 6, False);
      [*] = ;               _ai_TryUnit(plind, cid, gc_ai_unit_minecoal, 6, False);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               _ai_TryUnit(plind, cid, gc_ai_unit_minegold, 5, False);
      [*] = ;               _ai_TryUnit(plind, cid, gc_ai_unit_mineiron, 4, False);
      [*] = ;               _ai_TryUnit(plind, cid, gc_ai_unit_minecoal, 4, False);
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if ((_ai_GetUnitCount(plind, cid, gc_ai_unit_academi)>0) and ((onWood+onStone)>25) and (_ai_BuildMines(plind, cid, onFood, onWood, OnStone))) then
      [*] = ;         begin
      [*] = ;            _ai_TryUnit(plind, cid, gc_ai_unit_minegold, 3, False);
      [*] = ;            _ai_TryUnit(plind, cid, gc_ai_unit_mineiron, 3, False);
      [*] = ;            _ai_TryUnit(plind, cid, gc_ai_unit_minecoal, 3, False);
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var minescount, rounds : Integer;
      [*] = ;         case gMap.settings.gen.resourcemines of
      [*] = ;            0 : rounds := 3;
      [*] = ;            1 : rounds := 4;
      [*] = ;            2 : rounds := 5;
      [*] = ;            else
      [*] = ;            rounds := 4;
      [*] = ;         end;
      [*] = ;         minescount := rounds-1;
      [*] = ;
      [*] = ;         if ((centercount>=3) and (gMap.settings.gen.resourcestart<>ai_st_res_millions)) or ((centercount>=5) and (gMap.settings.gen.resourcestart=ai_st_res_millions)) then
      [*] = ;         begin
      [*] = ;            _ai_TryUnit(plind, cid, gc_ai_unit_minegold, minescount, False);
      [*] = ;            _ai_TryUnit(plind, cid, gc_ai_unit_mineiron, minescount, False);
      [*] = ;            _ai_TryUnit(plind, cid, gc_ai_unit_minecoal, minescount, False);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if ((_ai_GetUnitCount(plind, cid, gc_ai_unit_academi)>0) and ((onWood+onStone)>25)) and (gMap.settings.gen.resourcestart<>ai_st_res_millions) then
      [*] = ;         begin
      [*] = ;            _ai_TryUnit(plind, cid, gc_ai_unit_minegold, minescount, False);
      [*] = ;            _ai_TryUnit(plind, cid, gc_ai_unit_mineiron, minescount, False);
      [*] = ;            _ai_TryUnit(plind, cid, gc_ai_unit_minecoal, minescount, False);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (_ai_GetUnitCount(plind, cid,  gc_ai_unit_artdepo)>0) then
      [*] = ;      _ai_TryUnit(plind, cid, gc_ai_unit_mill, 2, False);
      [*] = ;
      [*] = ;      if (gPlayer[plind].bfamine) then
      [*] = ;      begin
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_market, 1, False);
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_store, 1, False);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (bai) and (difficulty>gc_player_difficulty_easy) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_academi)>0) and (gPlayer[plInd].aidata.bprogressWar) then
      [*] = ;      begin
      [*] = ;         var numTowers : Integer = Min(3, _ai_GetUnitCount(plind, cid, gc_ai_unit_peasant) div 75);
      [*] = ;         if ((_ai_GetUnitCount(plind, cid, gc_ai_unit_peasant) > 50) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_peasant) < 75)) then
      [*] = ;         numTowers := 1;
      [*] = ;         if (numTowers>0) then
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_tower, Min(numTowers, _ai_GetUnitCount(plind, cid, gc_ai_unit_tower)+1), False);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (cid=cid_ukr) then
      [*] = ;      begin
      [*] = ;         if (_ai_GetUnitCount(plind, cid, gc_ai_unit_artdepo)>=2) then
      [*] = ;         begin
      [*] = ;            if (not gPlayer[plind].res[gc_resource_type_iron]>8200) then
      [*] = ;            _ai_TryUnit(plind, cid, gc_ai_unit_artdepo, 3, False);
      [*] = ;            if not gPlayer[plind].res[gc_resource_type_iron]>10000 then
      [*] = ;            _ai_TryUnit(plind, cid, gc_ai_unit_artdepo, 4, False);
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (not gPlayer[plind].res[gc_resource_type_iron]>200000) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_artdepo)>=7) then
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_artdepo, 8, False)
      [*] = ;         else
      [*] = ;         if (not gPlayer[plind].res[gc_resource_type_iron]>150000) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_artdepo)>=6) then
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_artdepo, 7, False)
      [*] = ;         else
      [*] = ;         if (not gPlayer[plind].res[gc_resource_type_iron]>100000) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_artdepo)>=5) then
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_artdepo, 6, False)
      [*] = ;         else
      [*] = ;         if (not gPlayer[plind].res[gc_resource_type_iron]>50000) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_artdepo)>=4) then
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_artdepo, 5, False)
      [*] = ;         else
      [*] = ;         if not gPlayer[plind].res[gc_resource_type_iron]>20000 then
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_artdepo, 4, False)
      [*] = ;         else
      [*] = ;         if (not gPlayer[plind].res[gc_resource_type_iron]>9000) then
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_artdepo, 3, False);
      [*] = ;      end;
      [*] = ;
      [*] = ;      // port
      [*] = ;      var artdepo : Integer = _ai_GetUnitCount(plind, cid, gc_ai_unit_artdepo);
      [*] = ;      var port : Integer = _ai_GetUnitCount(plind, cid, gc_ai_unit_port);
      [*] = ;      if (not gScenario.bactive) or (bWaterScenario) then // to stop ai from building ports on scenario maps cause it is bad idea
      [*] = ;      begin
      [*] = ;         if (artdepo>0) and (bIsWaterMap) then
      [*] = ;         if (gMap.settings.gen.resourcestart=ai_st_res_millions) then
      [*] = ;         _ai_TryUnit(plind, cid, gc_ai_unit_port, 8, false)
      [*] = ;         else
      [*] = ;         case artdepo of
      [*] = ;            1 : _ai_TryUnit(plind, cid, gc_ai_unit_port, 1, False);
      [*] = ;            2 : _ai_TryUnit(plind, cid, gc_ai_unit_port, 3, False);
      [*] = ;            3 : _ai_TryUnit(plind, cid, gc_ai_unit_port, 5, False);
      [*] = ;            else
      [*] = ;            _ai_TryUnit(plind, cid, gc_ai_unit_port, 8, False);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if (port>0) and (artdepo>0) then
      [*] = ;      case artdepo of
      [*] = ;         1, 2 : begin
      [*] = ;            if (port>0) then
      [*] = ;            _ai_TryUnitExt(plind, cid, gc_ai_unit_port, gc_ai_unit_ferry, port+2); //for better landing operation
      [*] = ;            _ai_TryUnitExt(plind, cid, gc_ai_unit_port, gc_ai_unit_yacht, port*3);
      [*] = ;            _ai_TryUnitExt(plind, cid, gc_ai_unit_port, gc_ai_unit_galley, port*2);
      [*] = ;            _ai_TryUnitExt(plind, cid, gc_ai_unit_port, gc_ai_unit_frigate, artdepo);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            _ai_TryUnitExt(plind, cid, gc_ai_unit_port, gc_ai_unit_ferry, 6);
      [*] = ;            _ai_TryUnitExt(plind, cid, gc_ai_unit_port, gc_ai_unit_yacht, port*2);
      [*] = ;            _ai_TryUnitExt(plind, cid, gc_ai_unit_port, gc_ai_unit_galley, port*2);
      [*] = ;            _ai_TryUnitExt(plind, cid, gc_ai_unit_port, gc_ai_unit_frigate, port);
      [*] = ;            _ai_TryUnitExt(plind, cid, gc_ai_unit_port, gc_ai_unit_lineship, port div 2);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if (port>0) and _ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_boats) then
      [*] = ;      _ai_TryUnitExt(plind, cid, gc_ai_unit_port, gc_ai_unit_boat, port*6);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_DoTrade(plind, cid : integer);  //TODO: redone this for very late game
      [*] = ;begin
      [*] = ;   //intial trading options:
      [*] = ;   var plHnd : Integer = GetPlayerHandleByIndex(plInd);
      [*] = ;   if (not gPlayer[plind].aidata.bFlags[gc_ai_flag_trade_coal_once])  then
      [*] = ;   begin
      [*] = ;      if (gMap.settings.gen.resourcestart=ai_st_res_thousands) then
      [*] = ;      begin
      [*] = ;         if (cid=cid_rus) or (cid=cid_alg) then
      [*] = ;         begin
      [*] = ;            _res_MarketTradeResources(plHnd, gc_resource_type_coal, gc_resource_type_wood, 3000);
      [*] = ;            _res_MarketTradeResources(plHnd, gc_resource_type_coal, gc_resource_type_stone, 1500);
      [*] = ;            _res_MarketTradeResources(plHnd, gc_resource_type_gold, gc_resource_type_food, 1500);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if (cid<>cid_ukr) then
      [*] = ;         begin
      [*] = ;            _res_MarketTradeResources(plHnd, gc_resource_type_coal, gc_resource_type_wood, 3000);
      [*] = ;            _res_MarketTradeResources(plHnd, gc_resource_type_coal, gc_resource_type_stone, 1500);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if (cid=cid_ukr) then
      [*] = ;         _res_MarketTradeResources(plHnd, gc_resource_type_gold, gc_resource_type_wood, 2500);
      [*] = ;         gPlayer[plind].aidata.bFlags[gc_ai_flag_trade_coal_once] := True;
      [*] = ;      end;
      [*] = ;      if (gMap.settings.gen.resourcestart=ai_st_res_normal) then
      [*] = ;      begin
      [*] = ;         if (cid<>cid_ukr) then
      [*] = ;         _res_MarketTradeResources(plHnd, gc_resource_type_coal, gc_resource_type_food, 1000)
      [*] = ;         else
      [*] = ;         _res_MarketTradeResources(plHnd, gc_resource_type_coal, gc_resource_type_food, 500);
      [*] = ;         gPlayer[plind].aidata.bFlags[gc_ai_flag_trade_coal_once] := True;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if ((not gPlayer[plind].res[gc_resource_type_stone]>220000) and (not gPlayer[plind].res[gc_resource_type_gold]<100000) and (cid<>cid_ukr)) then
      [*] = ;   _res_MarketTradeResources(plHnd, gc_resource_type_stone, gc_resource_type_gold, 220000);
      [*] = ;   if ((not gPlayer[plind].res[gc_resource_type_gold]<50000) and (cid<>cid_ukr)) then
      [*] = ;   begin
      [*] = ;      if (not gPlayer[plind].res[gc_resource_type_wood]>300000) then
      [*] = ;      _res_MarketTradeResources(plHnd, gc_resource_type_wood, gc_resource_type_gold, 200000);
      [*] = ;      if (not gPlayer[plind].res[gc_resource_type_food]>300000) then
      [*] = ;      _res_MarketTradeResources(plHnd, gc_resource_type_food, gc_resource_type_gold, 200000);
      [*] = ;   end;
      [*] = ;   var stoneamount : Integer;
      [*] = ;   if (bIsWaterMap) then
      [*] = ;   stoneamount := 65000
      [*] = ;   else
      [*] = ;   stoneamount := 30000;
      [*] = ;   if ((not gPlayer[plind].res[gc_resource_type_stone]>stoneamount) and (_ai_NationIsEurope(cid)) and (not _ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_century))) then
      [*] = ;   _res_MarketTradeResources(plHnd, gc_resource_type_stone, gc_resource_type_gold, stoneamount);
      [*] = ;   if ((not gPlayer[plind].res[gc_resource_type_wood]>35000) and (_ai_NationIsEurope(cid)) and (not _ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_century))) then
      [*] = ;   _res_MarketTradeResources(plHnd, gc_resource_type_wood, gc_resource_type_gold, 35000);
      [*] = ;   if (gPlayer[plind].bfamine) then
      [*] = ;   begin
      [*] = ;      if (not gPlayer[plind].res[gc_resource_type_wood]>5000) then
      [*] = ;      _res_MarketTradeResources(plHnd, gc_resource_type_wood, gc_resource_type_food, 5000);
      [*] = ;      if (not gPlayer[plind].res[gc_resource_type_stone]>5000) then
      [*] = ;      _res_MarketTradeResources(plHnd, gc_resource_type_stone, gc_resource_type_food, 5000);
      [*] = ;   end;
      [*] = ;   //nation specific fast development grades:
      [*] = ;   if (cid=cid_ukr) and (_ai_GetUnitCurrentUpgLevel(plind, cid, gc_ai_unit_musk17, 1)=5) and (not gPlayer[plind].res[gc_resource_type_gold]>40000) and (not gPlayer[plind].res[gc_resource_type_coal]<40000) then
      [*] = ;   _res_MarketTradeResources(plHnd, gc_resource_type_gold, gc_resource_type_coal, 10000);
      [*] = ;   if ((cid=cid_ukr) or (cid=cid_tur) or (cid=cid_alg)) and ((_ai_GetUnitCurrentUpgLevel(plind, cid, gc_ai_unit_musk17, 1)<6) or (_ai_GetUnitCurrentUpgLevel(plind, cid, gc_ai_unit_reitar, 1)<6)) and (not gPlayer[plind].res[gc_resource_type_gold]>40000) and (not gPlayer[plind].res[gc_resource_type_iron]<20000) then
      [*] = ;   _res_MarketTradeResources(plHnd, gc_resource_type_gold, gc_resource_type_iron, 10000);
      [*] = ;   if ((cid=cid_ukr) or (cid=cid_tur) or (cid=cid_alg)) and (not gPlayer[plind].res[gc_resource_type_food]>100000) and ((not _ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_horse)) or (not _ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_horseswords))) then
      [*] = ;   begin
      [*] = ;      _res_MarketTradeResources(plHnd, gc_resource_type_food, gc_resource_type_gold, 20000);
      [*] = ;      _res_MarketTradeResources(plHnd, gc_resource_type_food, gc_resource_type_iron, 30000);
      [*] = ;      _res_MarketTradeResources(plHnd, gc_resource_type_food, gc_resource_type_coal, 50000);
      [*] = ;   end;
      [*] = ;   if ((cid=cid_ukr) or (cid=cid_tur) or (cid=cid_alg)) and (not gPlayer[plind].res[gc_resource_type_stone]>100000) and ((not _ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_horse)) or (not _ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_horseswords))) then
      [*] = ;   begin
      [*] = ;      _res_MarketTradeResources(plHnd, gc_resource_type_stone, gc_resource_type_gold, 25000);
      [*] = ;      _res_MarketTradeResources(plHnd, gc_resource_type_stone, gc_resource_type_iron, 30000);
      [*] = ;      _res_MarketTradeResources(plHnd, gc_resource_type_stone, gc_resource_type_coal, 45000);
      [*] = ;   end;
      [*] = ;   if (not gPlayer[plind].res[gc_resource_type_food]>150000) then
      [*] = ;   _res_MarketTradeResources(plHnd, gc_resource_type_food, gc_resource_type_gold, 100000);
      [*] = ;   if _ai_NationIsEurope(cid) then
      [*] = ;   begin
      [*] = ;      if (not gPlayer[plind].res[gc_resource_type_stone]>500000) then
      [*] = ;      _res_MarketTradeResources(plHnd, gc_resource_type_stone, gc_resource_type_gold, 400000);
      [*] = ;      if (not gPlayer[plind].res[gc_resource_type_wood]>200000) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_ba18)<3) then
      [*] = ;      _res_MarketTradeResources(plHnd, gc_resource_type_wood, gc_resource_type_gold, 200000);
      [*] = ;   end;
      [*] = ;   if _ai_GetTimeFromStart(plind) > 15 then
      [*] = ;   begin
      [*] = ;      //century grade:
      [*] = ;      if ((gMap.settings.gen.resourcestart=ai_st_res_thousands) and _ai_NationIsEurope(cid) and (not gPlayer[plind].res[gc_resource_type_gold]>20000) and (not _ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_century))) then
      [*] = ;      begin
      [*] = ;         if (not gPlayer[plind].res[gc_resource_type_food]<60000) then
      [*] = ;         _res_MarketTradeResources(plHnd, gc_resource_type_gold, gc_resource_type_food, 5000);
      [*] = ;         if (not gPlayer[plind].res[gc_resource_type_iron]<19000) and (cid=cid_eng) then
      [*] = ;         _res_MarketTradeResources(plHnd, gc_resource_type_gold, gc_resource_type_iron, 5000);
      [*] = ;      end;
      [*] = ;
      [*] = ;      var reqGold : Integer = (_ai_GetTimeFromStart(plind) div 10)*1000+1000;
      [*] = ;      var reqIron : Integer = (_ai_GetTimeFromStart(plind) div 10)*1000+1000;
      [*] = ;      var reqCoal : Integer = (_ai_GetTimeFromStart(plind) div 10)*1000+1000;
      [*] = ;      if not gPlayer[plind].res[gc_resource_type_gold] < reqGold then
      [*] = ;      begin
      [*] = ;         if (not gPlayer[plind].res[gc_resource_type_stone]>10000) then
      [*] = ;         _res_MarketTradeResources(plHnd, gc_resource_type_stone, gc_resource_type_gold, 5000)
      [*] = ;         else
      [*] = ;         if (not gPlayer[plind].res[gc_resource_type_wood]>10000) then
      [*] = ;         _res_MarketTradeResources(plHnd, gc_resource_type_wood, gc_resource_type_gold, 5000);
      [*] = ;      end;
      [*] = ;      if not gPlayer[plind].res[gc_resource_type_iron] < reqIron then
      [*] = ;      begin
      [*] = ;         if (not gPlayer[plind].res[gc_resource_type_stone]>10000) then
      [*] = ;         _res_MarketTradeResources(plHnd, gc_resource_type_stone, gc_resource_type_iron, 5000)
      [*] = ;         else
      [*] = ;         if (not gPlayer[plind].res[gc_resource_type_wood]>10000) then
      [*] = ;         _res_MarketTradeResources(plHnd, gc_resource_type_wood, gc_resource_type_iron, 5000);
      [*] = ;      end;
      [*] = ;      if not gPlayer[plind].res[gc_resource_type_coal] < reqCoal then
      [*] = ;      begin
      [*] = ;         if (not gPlayer[plind].res[gc_resource_type_stone]>10000) then
      [*] = ;         _res_MarketTradeResources(plHnd, gc_resource_type_stone, gc_resource_type_coal, 5000)
      [*] = ;         else
      [*] = ;         if (not gPlayer[plind].res[gc_resource_type_wood]>10000) then
      [*] = ;         _res_MarketTradeResources(plHnd, gc_resource_type_wood, gc_resource_type_coal, 5000);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (not gPlayer[plind].res[gc_resource_type_stone]>200000) then
      [*] = ;      begin
      [*] = ;         reqGold := Min(65000, 5*(_ai_GetTimeFromStart(plind) div 10)*1000+1000);
      [*] = ;         reqIron := Min(65000, 5*(_ai_GetTimeFromStart(plind) div 10)*1000+1000);
      [*] = ;         reqCoal := Min(65000, 5*(_ai_GetTimeFromStart(plind) div 10)*1000+1000);
      [*] = ;         var deltaGold : Integer = Max(0, (reqGold-not gPlayer[plind].res[gc_resource_type_gold]));
      [*] = ;         var deltaIron : Integer = Max(0, (reqIron-not gPlayer[plind].res[gc_resource_type_iron]));
      [*] = ;         var deltaCoal : Integer = Max(0, (reqCoal-not gPlayer[plind].res[gc_resource_type_coal]));
      [*] = ;         var totalRnd : Integer = deltaGold*2+deltaIron+deltaCoal;
      [*] = ;         if (totalRnd>0) then
      [*] = ;         begin
      [*] = ;            var rnd : Integer = floor(RandomExt*totalRnd);
      [*] = ;            if (rnd<(deltaGold*2)) then
      [*] = ;            _res_MarketTradeResources(plHnd, gc_resource_type_stone, gc_resource_type_gold, 150000)
      [*] = ;            else
      [*] = ;            if (rnd<(deltaGold*2+deltaIron)) then
      [*] = ;            _res_MarketTradeResources(plHnd, gc_resource_type_stone, gc_resource_type_iron, 150000)
      [*] = ;            else
      [*] = ;            _res_MarketTradeResources(plHnd, gc_resource_type_stone, gc_resource_type_coal, 150000);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   // do not starve
      [*] = ;   if not gPlayer[plind].res[gc_resource_type_food] < 100 then
      [*] = ;   begin
      [*] = ;      var i, bestRes : Integer;
      [*] = ;      bestRes := gc_resource_type_wood;
      [*] = ;      for i:=gc_resource_type_wood to gc_resource_type_coal do
      [*] = ;      if not gPlayer[plind].res[i]>not gPlayer[plind].res[bestRes] then
      [*] = ;      bestRes := i;
      [*] = ;      _res_MarketTradeResources(plHnd, bestRes, gc_resource_type_food, not gPlayer[plind].res[bestRes] div 3);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_MainConstructionIdeasScript(plind, cid, onFood, onWood, onStone : Integer);
      [*] = ;begin
      [*] = ;   _misc_ProfilerBegin('_ai_MainConstructionIdeasScript');
      [*] = ;   _ai_BuildHouses(plind, cid, onFood, onWood, onStone);
      [*] = ;   _ai_MakeUpgrades(plind, cid);
      [*] = ;   if (bprocess) and ((not bai) or _ai_UpgradeIsDoneById(plind, cid, gc_ai_upg_food140)) then
      [*] = ;   _ai_RequestUnitsProduction(plind, cid);
      [*] = ;   //special boost for start:
      [*] = ;   var needpeasants : Integer;
      [*] = ;   if not bai then
      [*] = ;   needpeasants := -1
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (not gPlayer[plind].res[gc_resource_type_food]<700) then
      [*] = ;      needpeasants := 1
      [*] = ;      else
      [*] = ;      needpeasants := _ai_GetUnitCount(plind, cid, gc_ai_unit_center)*2;
      [*] = ;   end;
      [*] = ;   if (_ai_GetUnitCount(plind, cid, gc_ai_unit_peasant)<25) and (_ai_GetTimeFromStart(plind)<4) then
      [*] = ;   _ai_TryUnit(plind, cid, gc_ai_unit_peasant, needpeasants, (gPlayer[plind].playeradviser.adviser.benable) and (gPlayer[plind].playeradviser.adviser.beconomy) and gPlayer[plind].playeradviser.adviser.bproducepeasants);
      [*] = ;
      [*] = ;   //_ai_ResourcesDistributionScript(plind, cid, onFood, onWood, onStone);
      [*] = ;   if ((_ai_GetUnitCount(plind, cid, gc_ai_unit_market)>0) and (gMap.settings.gen.resourcestart<>ai_st_res_millions)) or
      [*] = ;   ((_ai_GetUnitCount(plind, cid, gc_ai_unit_market)>0) and (gMap.settings.gen.resourcestart=ai_st_res_millions) and (_ai_GetTimeFromStart(plind)>30)) then
      [*] = ;   begin
      [*] = ;      if (bai) or (not bai and gPlayer[plind].playeradviser.adviser.benable and gPlayer[plind].playeradviser.adviser.beconomy and gPlayer[plind].playeradviser.adviser.bmarketadvises and False {till advicer not available}) then
      [*] = ;      if (bprocess) then
      [*] = ;      _ai_DoTrade(plind, cid);
      [*] = ;   end;
      [*] = ;
      [*] = ;   //specific for ai_millions
      [*] = ;   if (bai) and (bprocess) then
      [*] = ;   if _ai_NationIsEurope(cid) and (gMap.settings.gen.resourcestart=ai_st_res_millions) and (_ai_GetTimeFromStart(plind)<10) and _ai_GetUnitCount(plind, cid, gc_ai_unit_market)>0 then
      [*] = ;   begin
      [*] = ;      var plHnd : Integer = GetPlayerHandleByIndex(plInd);
      [*] = ;      if (not gPlayer[plind].res[gc_resource_type_iron]>900000) then
      [*] = ;      if _ai_NationIsEurope(cid) then
      [*] = ;      _res_MarketTradeResources(plHnd, gc_resource_type_iron, gc_resource_type_gold, 600000)
      [*] = ;      else
      [*] = ;      _res_MarketTradeResources(plHnd, gc_resource_type_iron, gc_resource_type_stone, 600000);
      [*] = ;      if (not gPlayer[plind].res[gc_resource_type_coal]>900000) then
      [*] = ;      if _ai_NationIsEurope(cid) then
      [*] = ;      _res_MarketTradeResources(plHnd, gc_resource_type_coal, gc_resource_type_gold, 600000)
      [*] = ;      else
      [*] = ;      _res_MarketTradeResources(plHnd, gc_resource_type_coal, gc_resource_type_wood, 600000);
      [*] = ;      if (_ai_GetTimeFromStart(plInd)<7) and (not gPlayer[plind].res[gc_resource_type_stone]>500000) then
      [*] = ;      _res_MarketTradeResources(plHnd, gc_resource_type_stone, gc_resource_type_gold, 400000);
      [*] = ;   end;
      [*] = ;
      [*] = ;   _misc_ProfilerEnd('_ai_MainConstructionIdeasScript');
      [*] = ;end;
      [*] = ;
      [*] = ;function _ai_GetUnitCountInProduce(plind, cid, id : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var i, j : Integer;
      [*] = ;   for i:=0 to gPlayer[plind].aidata.ailist.GetCount-1 do
      [*] = ;   begin
      [*] = ;      var goHnd : Integer = gPlayer[plind].aidata.ailist.Get(i);
      [*] = ;      var pobj : Pointer = _misc_GetObjectArgData(goHnd, gc_argunit_obj);
      [*] = ;      if (pobj<>nil) then
      [*] = ;      begin
      [*] = ;         for j:=gc_obj_MaxOrderCount-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var porder : Pointer = TObj(pobj).orders[j]; //if (gc_debug_pointernil) then _init_DebugPointerNil(porder);
      [*] = ;            if (porder<>nil) then
      [*] = ;            begin
      [*] = ;               if ((TOrder(porder).itype=gc_obj_order_type_produce) and
      [*] = ;               (TOrder(porder).info.amount<>gc_obj_order_produce_infinite) and
      [*] = ;               (TOrder(porder).info.produceid=id)) then
      [*] = ;               Result := Result+TOrder(porder).info.amount
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_ProduceUnits(plind, cid, airole : Integer; var sid : String; count : Integer);
      [*] = ;begin
      [*] = ;   var buildid : Integer = gPlayer[plind].aidata.buildlink[cid][airole];
      [*] = ;   var id : Integer = gPlayer[plind].aidata.aiunit[cid][airole];
      [*] = ;   _ai_SelectBuildingsWithId(plind, cid, buildid);
      [*] = ;   var i : Integer;
      [*] = ;   for i:=gPlayer[plind].aidata.ailist.GetCount-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var goHnd : Integer = gPlayer[plind].aidata.ailist.Get(i);
      [*] = ;      var pobj : Pointer = _unit_GetTObj(goHnd);
      [*] = ;      if (pobj<>nil) and (TObj(pobj).orders[0].itype=gc_obj_order_type_produce) and (TObj(pobj).orders[0].info.amount<>gc_obj_order_produce_infinite) then
      [*] = ;      gPlayer[plind].aidata.ailist.Delete(i);
      [*] = ;   end;
      [*] = ;   if (gPlayer[plind].aidata.ailist.GetCount>0) then
      [*] = ;   begin
      [*] = ;      var binfinite : Boolean = count<0;
      [*] = ;      var inProduce : Integer = _ai_GetUnitCountInProduce(plind, cid, id);
      [*] = ;      count := count-inProduce;
      [*] = ;      if binfinite or ((count>0) and (inProduce<gPlayer[plind].aidata.ailist.GetCount)) then
      [*] = ;      begin
      [*] = ;         var plHnd : Integer = GetPlayerHandleByIndex(plInd);
      [*] = ;         _unit_ProduceUnit(plHnd, gPlayer[plind].aidata.ailist, cid, id, count, true, true, true);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_ProcessIdeas(plind : Integer);
      [*] = ;begin
      [*] = ;   _misc_ProfilerBegin('_ai_ProcessIdeas');
      [*] = ;   var cid, id, ideatype, airole : Integer;
      [*] = ;   var sid : String;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=gPlayer[plind].aidata.bestprojects.GetCount-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var p : Pointer = gPlayer[plind].aidata.bestprojects.Get(i);
      [*] = ;      if (p<>nil) then
      [*] = ;      begin
      [*] = ;         ideatype := TAiIdea(p).ideatype;
      [*] = ;         if (ideatype=gc_ai_idea_type_unit) then
      [*] = ;         begin
      [*] = ;            id := TAiIdea(p).id;
      [*] = ;            cid := TAiIdea(p).cid;
      [*] = ;            sid := gObjProp[cid][id].sid;
      [*] = ;            airole := TAiIdea(p).airole;
      [*] = ;            //processing buildings
      [*] = ;            if (gObjProp[cid][id].bbuilding) then
      [*] = ;            begin
      [*] = ;               var index : Integer = _ai_GetFreeBuildingIndex(plind);
      [*] = ;               if (index<>-1) then
      [*] = ;               begin
      [*] = ;                  var bskip : Boolean;
      [*] = ;                  var centerx : Float = gPlayer[plind].aidata.centerx;
      [*] = ;                  var centerz : Float = gPlayer[plind].aidata.centerz;
      [*] = ;                  if (airole=gc_ai_unit_center) or (airole=gc_ai_unit_store) then
      [*] = ;                  begin
      [*] = ;                     var tmpcenterx : Float = centerx;
      [*] = ;                     var tmpcenterz : Float = centerz;
      [*] = ;                     var plHnd : Integer = GetPlayerHandleByIndex(plInd);
      [*] = ;                     if (_ai_FindBestPlaceForStorehouse(plHnd, tmpcenterx, tmpcenterz, gPlayer[plind].aidata.centerx, gPlayer[plind].aidata.centerz)) then
      [*] = ;                     begin
      [*] = ;                        if ((not bai) and gPlayer[plind].playeradviser.adviser.benable and gPlayer[plind].playeradviser.adviser.bconstruct) then
      [*] = ;                        bskip := not ((airole<>gc_ai_unit_store) or ((airole=gc_ai_unit_store) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_store)<2)));
      [*] = ;                        centerx := tmpcenterx;
      [*] = ;                        centerz := tmpcenterz;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        if ((airole=gc_ai_unit_store) and (_ai_GetUnitCount(plind, cid, gc_ai_unit_store)>0)) or ((airole=gc_ai_unit_center) and ((_ai_GetUnitCount(plind, cid, gc_ai_unit_center)>2) and (random>0.1))) then
      [*] = ;                        index := -1;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  if ((not bai) and gPlayer[plind].playeradviser.adviser.benable and gPlayer[plind].playeradviser.adviser.bconstruct) then
      [*] = ;                  begin
      [*] = ;                     if (not bskip) and (cid=gPlayer[plind].cid) then
      [*] = ;                     begin
      [*] = ;                        var val : Integer = _misc_TwoIntToOne(cid, id);
      [*] = ;                        if (gPlayer[plind].playeradviser.buildings.IndexOf(val)<0) then
      [*] = ;                        begin
      [*] = ;                           gPlayer[plind].playeradviser.buildings.Add(val);
      [*] = ;                           gbool_gui_updateadviseradvice := True;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  if (bai) and (index<>-1) then
      [*] = ;                  begin
      [*] = ;                     var curRad : Integer = 0;
      [*] = ;                     var curInd : Integer = 0;
      [*] = ;
      [*] = ;                     case aiRole of
      [*] = ;                        gc_ai_unit_tower : _ai_GetTowerPos(plInd, centerx, centerz);
      [*] = ;                        //gc_ai_unit_port : _ai_GetPortPos(plInd, centerX, centerZ, centerX, centerZ);
      [*] = ;                        gc_ai_unit_port : _ai_GetNewPortPos(plInd, centerX, centerZ, centerX, centerZ, curRad, curInd);
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     gPlayer[plind].aidata.buildprojects[index].SetupBuildingProject(cid, id, sid, centerx, centerz, 0);
      [*] = ;                     gPlayer[plind].aidata.buildprojects[index].curRad := curRad;
      [*] = ;                     gPlayer[plind].aidata.buildprojects[index].curInd := curInd;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               var count : Integer = TAiIdea(p).count;
      [*] = ;               _ai_ProduceUnits(plind, cid, airole, sid, count);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         gPlayer[plind].aidata.bestprojects.Delete(i);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      log('Error: null Pointer at _ai_ProcessIdeas');
      [*] = ;   end;
      [*] = ;   _misc_ProfilerEnd('_ai_ProcessIdeas');
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_GetConstructionSite(plind, index : Integer);
      [*] = ;begin
      [*] = ;   _misc_ProfilerBegin('_ai_ProcessConstruction._ai_GetConstructionSite');
      [*] = ;   gPlayer[plind].aidata.ailist.Clear;
      [*] = ;   //create check dummy:
      [*] = ;   var cid : Integer = gPlayer[plind].aidata.buildprojects[index].cid;
      [*] = ;   var sid : String = gPlayer[plind].aidata.buildprojects[index].sid;
      [*] = ;   var id : Integer = gPlayer[plind].aidata.buildprojects[index].id;
      [*] = ;   var miscPlHnd : Integer = GetPlayerHandleByIndex(gc_playerind_misc);
      [*] = ;   var attemptstostand : Integer = gPlayer[plind].aidata.buildprojects[index].attemptstostand;
      [*] = ;   var goHnd : Integer = _player_CreateConstructionDummyBySID(miscPlHnd, cid, sid, 0, 0);
      [*] = ;   if (goHnd<>0) then
      [*] = ;   begin
      [*] = ;      var nearX : Float = gPlayer[plind].aidata.buildprojects[index].nearX;
      [*] = ;      var nearZ : Float = gPlayer[plind].aidata.buildprojects[index].nearZ;
      [*] = ;      var curRad : Integer = gPlayer[plind].aidata.buildprojects[index].curRad;
      [*] = ;      var curInd : Integer = gPlayer[plind].aidata.buildprojects[index].curInd;
      [*] = ;      var usage : Integer = gObjProp[cid, id].usage;
      [*] = ;      if (usage = gc_obj_usage_port) and (attemptsToStand>=20) then
      [*] = ;      begin
      [*] = ;         var x, z : Float;
      [*] = ;         if _ai_GetNewPortPos(plInd, nearX, nearZ, x, z, curRad, curInd) then
      [*] = ;         begin
      [*] = ;            gPlayer[plind].aiData.buildProjects[index].nearX := x;
      [*] = ;            gPlayer[plind].aiData.buildProjects[index].nearZ := z;
      [*] = ;            gPlayer[plind].aiData.buildProjects[index].curRad := curRad;
      [*] = ;            gPlayer[plind].aiData.buildProjects[index].curInd := curInd;
      [*] = ;            gPlayer[plind].aiData.buildProjects[index].attemptsToStand := 0;
      [*] = ;            gPlayer[plind].aiData.buildProjects[index].maxTryDist := -1;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         gPlayer[plind].aidata.buildprojects[index].ResetBuildingProject;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var myisland : Integer = _misc_GetIsland(gPlayer[plind].aidata.centerx, gPlayer[plind].aidata.centerz);
      [*] = ;      var numtries : Integer;
      [*] = ;      for numtries:=0 to 10 do
      [*] = ;      begin
      [*] = ;         var maxRad : Integer = attemptsToStand + numTries;
      [*] = ;         var shiftx : Float = -maxRad + random*maxRad*2;
      [*] = ;         var shiftz : Float = -maxRad + random*maxRad*2;
      [*] = ;         var posx : Float = floor(shiftx+nearX)+0.25;
      [*] = ;         var posz : Float = floor(shiftz+nearZ)+0.25;
      [*] = ;         var zone : Integer = TopologyGetZoneIndex(posX, posZ);
      [*] = ;         var pBuffer : Pointer = TopologyGetZoneBufferByIndex(zone);
      [*] = ;
      [*] = ;         if (posx>(-GetMapWidth div 2)) and (posz>(-GetMapHeight div 2)) and (posx<(GetMapWidth div 2)) and (posz<(GetMapHeight div 2))
      [*] = ;         and (pBuffer <> nil) then
      [*] = ;         begin
      [*] = ;            var dist : Integer = TTopZone(pBuffer).centerDist[plInd];
      [*] = ;            var maxDist : Integer = gPlayer[plind].aidata.buildprojects[index].maxTryDist;
      [*] = ;            var delta : Integer = MathCeil(2 + maxRad / 30);
      [*] = ;
      [*] = ;            if (maxDist < 0) then
      [*] = ;            gPlayer[plind].aidata.buildprojects[index].maxTryDist := dist
      [*] = ;            else
      [*] = ;            if (attemptsToStand >= GetMapWidth) or (dist <= maxDist+delta) then
      [*] = ;            begin
      [*] = ;               if _misc_IsCorrectIslandPosition(plInd, posX, posZ) then
      [*] = ;               begin
      [*] = ;                  if maxDist < dist then
      [*] = ;                  gPlayer[plind].aidata.buildprojects[index].maxTryDist := dist;
      [*] = ;
      [*] = ;                  var plHnd : Integer = GetPlayerHandleByIndex(plInd);
      [*] = ;                  SetGameObjectPositionByHandle(goHnd, posx, 0, posz);
      [*] = ;
      [*] = ;                  var eCount : Integer = gCustomObjPoints[cid][id].exitCount;
      [*] = ;                  var onEnemy : Boolean;
      [*] = ;                  if eCount > 0 then
      [*] = ;                  begin
      [*] = ;                     var ex : Float = gCustomObjPoints[cid][id].exitPoints[eCount-1].x;
      [*] = ;                     var ez : Float = gCustomObjPoints[cid][id].exitPoints[eCount-1].z;
      [*] = ;                     onEnemy := _misc_IsEnemyTerritory(plInd, posX+ex, posZ+ez);
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if not onEnemy then
      [*] = ;                  begin
      [*] = ;                     var canplace : Boolean = _misc_CanPlaceBuilding(goHnd, plind, gObjProp[cid][id].usage, posx, posz, gc_path_mincoldist, 0.26, 0.5, gc_path_minemincoldist, usage<>gc_obj_usage_port) and (_player_GetTopologyZoneDanger(plhnd, zone)<1);
      [*] = ;                     if (canplace) then
      [*] = ;                     begin
      [*] = ;                        var trgHnd : Integer = _player_ConstructBuildingList(plHnd, cid, sid, posx, posz, gPlayer[plind].aidata.ailist, false, True);
      [*] = ;                        if (trgHnd<>0) then
      [*] = ;                        begin
      [*] = ;                           gPlayer[plind].aidata.buildprojects[index].gohnd := trgHnd;
      [*] = ;                           gPlayer[plind].aidata.buildprojects[index].placefound := true;
      [*] = ;                           if (gCustomObjPoints[cid, id].builderCount=0) then
      [*] = ;                           _unit_CalcBuilderPoints(goHnd, gc_BuilderDist);
      [*] = ;                           var bCount : Integer = gCustomObjPoints[cid, id].builderCount;
      [*] = ;                           if (gObjProp[cid][id].usage=gc_obj_usage_farm) then
      [*] = ;                           begin
      [*] = ;                              gPlayer[plind].aidata.buildprojects[index].minpeasants := 2;
      [*] = ;                              gPlayer[plind].aidata.buildprojects[index].maxpeasants := 3;
      [*] = ;                           end
      [*] = ;                           else
      [*] = ;                           begin
      [*] = ;                              gPlayer[plind].aidata.buildprojects[index].minpeasants := bcount div 2;
      [*] = ;                              //if gPlayer[plind].objbase[cid][id].buildtime > 1000 then
      [*] = ;                              //else bCount := Max(5, gCustomObjPoints[cid, id].builderCount div 2);
      [*] = ;                              if (gPlayer[plind].objbase[cid][id].buildtime < 1000) and (gPlayer[plind].aidata.freepeasant.GetCount<5) then
      [*] = ;                              bCount := bCount*2 div 3;
      [*] = ;                              gPlayer[plind].aidata.buildprojects[index].maxpeasants := bCount;
      [*] = ;                           end;
      [*] = ;                        end
      [*] = ;                        else
      [*] = ;                        gPlayer[plind].aidata.buildprojects[index].ResetBuildingProject;
      [*] = ;
      [*] = ;                        break;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      GameObjectDestroyByHandle(goHnd);
      [*] = ;   end;
      [*] = ;   //else
      [*] = ;   //ErrorLog('_ai_GetConstructionSite : goHnd=0 sid='+sid);
      [*] = ;   gPlayer[plind].aidata.buildprojects[index].attemptstostand := Min(GetMapWidth, gPlayer[plind].aidata.buildprojects[index].attemptstostand+10);
      [*] = ;   //if gPlayer[plind].aidata.buildprojects[index].attemptstostand = GetMapWidth then
      [*] = ;   //gPlayer[plind].aidata.buildprojects[index].attemptstostand := 0;
      [*] = ;
      [*] = ;   _misc_ProfilerEnd('_ai_ProcessConstruction._ai_GetConstructionSite');
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_CallPeasantsToBuildProject(plind, index, onFood, onWood, onStone : Integer);
      [*] = ;begin
      [*] = ;   _misc_ProfilerBegin('_ai_ProcessConstruction._ai_CallPeasantsToBuildProject');
      [*] = ;   var minpeasants : Integer = gPlayer[plind].aidata.buildprojects[index].minpeasants;
      [*] = ;   var maxpeasants : Integer = gPlayer[plind].aidata.buildprojects[index].maxpeasants;
      [*] = ;   var trgHnd : Integer = gPlayer[plind].aidata.buildprojects[index].gohnd;
      [*] = ;   var reqpeasants : Integer = maxpeasants-gPlayer[plind].aidata.buildprojects[index].npeasantscalled;;
      [*] = ;   var bAllowFood : Boolean = (onWood+onStone<reqpeasants);
      [*] = ;
      [*] = ;   gPlayer[plind].aidata.ailist.Clear;
      [*] = ;   if (reqpeasants>0) then
      [*] = ;   begin
      [*] = ;      if gPlayer[plind].aidata.freepeasant.GetCount>0 then
      [*] = ;      begin
      [*] = ;         _misc_CopyIntListRange(gPlayer[plind].aidata.ailist, gPlayer[plind].aidata.freepeasant, 0, Min(reqpeasants, gPlayer[plind].aidata.freepeasant.GetCount), true);
      [*] = ;         reqpeasants := reqpeasants-Min(reqpeasants, gPlayer[plind].aidata.freepeasant.GetCount);
      [*] = ;      end;
      [*] = ;      if (reqpeasants>0) then
      [*] = ;      begin
      [*] = ;         var mmask : Integer = (1 shl gc_obj_material_body);
      [*] = ;         var dist : Float = VectorDistance(GetGameObjectPositionXByHandle(trgHnd), 0, GetGameObjectPositionZByHandle(trgHnd), gPlayer[plind].aidata.centerx, 0, gPlayer[plind].aidata.centerz);
      [*] = ;         if dist > 30 then
      [*] = ;         _ai_MakeListObjectsInRadiusByUsageBySpiral(plind, gc_obj_usage_peasant, reqpeasants, gPlayer[plind].aidata.centerx, gPlayer[plind].aidata.centerz, 50, bAllowFood, false, 1 shl gc_obj_material_body, gPlayer[plind].aidata.ailist, false)
      [*] = ;         else
      [*] = ;         _ai_MakeListObjectsInRadiusByUsageBySpiral(plind, gc_obj_usage_peasant, reqpeasants, GetGameObjectPositionXByHandle(trgHnd), GetGameObjectPositionZByHandle(trgHnd), 50, bAllowFood, false, 1 shl gc_obj_material_body, gPlayer[plind].aidata.ailist, false);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if gPlayer[plind].aidata.ailist.GetCount>0 then
      [*] = ;   begin
      [*] = ;      gPlayer[plind].aidata.buildprojects[index].npeasantscalled := gPlayer[plind].aidata.buildprojects[index].npeasantscalled+gPlayer[plind].aidata.ailist.GetCount;
      [*] = ;      _player_OrderUnitsToBuild(gPlayer[plind].aidata.ailist, trgHnd, true, false, true);
      [*] = ;      gPlayer[plind].aidata.buildprojects[index].peasantscalled := true;
      [*] = ;   end;
      [*] = ;
      [*] = ;   _misc_ProfilerEnd('_ai_ProcessConstruction._ai_CallPeasantsToBuildProject');
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_ControlConstruction(plind, index : Integer);
      [*] = ;begin
      [*] = ;   //check if unit is build
      [*] = ;   var trgHnd : Integer = gPlayer[plind].aidata.buildprojects[index].gohnd;
      [*] = ;   var p : Pointer = _unit_GetTObj(trgHnd);
      [*] = ;   if (p<>nil) and (TObj(p).bbuilt) then
      [*] = ;   gPlayer[plind].aidata.buildprojects[index].ResetBuildingProject;
      [*] = ;   //check if enough peasants
      [*] = ;   var pordlist : Pointer = _misc_GetObjectArgData(trgHnd, gc_argunit_ordlist);
      [*] = ;   if TIntegerList(pordlist).GetCount<gPlayer[plind].aidata.buildprojects[index].maxpeasants then
      [*] = ;   begin
      [*] = ;      gPlayer[plind].aidata.buildprojects[index].peasantscalled := false;
      [*] = ;      gPlayer[plind].aidata.buildprojects[index].npeasantscalled := TIntegerList(pordlist).GetCount;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_RemoveProjectIfInvalid(plind, index : Integer);
      [*] = ;begin
      [*] = ;   var trgHnd : Integer = gPlayer[plind].aidata.buildprojects[index].gohnd;
      [*] = ;   var found : Boolean;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to gPlayer[plind].aidata.unbuildhouses.GetCount-1 do
      [*] = ;   begin
      [*] = ;      var goHnd : Integer = gPlayer[plind].aidata.unbuildhouses.Get(i);
      [*] = ;      if (trgHnd=goHnd) then
      [*] = ;      begin
      [*] = ;         found := true;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if (not found) then
      [*] = ;   gPlayer[plind].aidata.buildprojects[index].ResetBuildingProject;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_ProcessConstruction(plind, onFood, onWood, onStone : Integer);
      [*] = ;begin
      [*] = ;   _misc_ProfilerBegin('_ai_ProcessConstruction');
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to gc_ai_max_construction_sites-1 do
      [*] = ;   begin
      [*] = ;      if (gPlayer[plind].aidata.buildprojects[i].used) and (gPlayer[plind].aidata.buildprojects[i].placefound) then
      [*] = ;      _ai_RemoveProjectIfInvalid(plind, i);
      [*] = ;      if (bprocess) then
      [*] = ;      if (gPlayer[plind].aidata.buildprojects[i].used) then
      [*] = ;      begin
      [*] = ;         //place found?
      [*] = ;         if (not gPlayer[plind].aidata.buildprojects[i].placefound) then
      [*] = ;         _ai_GetConstructionSite(plind, i);
      [*] = ;         if (gPlayer[plind].aidata.buildprojects[i].placefound) then
      [*] = ;         begin
      [*] = ;            if (gPlayer[plind].aidata.buildprojects[i].used) then
      [*] = ;            begin
      [*] = ;               if ((not gPlayer[plind].aidata.buildprojects[i].peasantscalled) or
      [*] = ;               ((gPlayer[plind].aidata.buildprojects[i].peasantscalled) and
      [*] = ;               (gPlayer[plind].aidata.buildprojects[i].npeasantscalled<gPlayer[plind].aidata.buildprojects[i].maxpeasants))) and
      [*] = ;               (gPlayer[plind].aidata.peasantlist.GetCount>0) then
      [*] = ;               if bai or (not bai and gPlayer[plind].playeradviser.adviser.benable and gPlayer[plind].playeradviser.adviser.beconomy and gPlayer[plind].playeradviser.adviser.brepairbuildings) then
      [*] = ;               _ai_CallPeasantsToBuildProject(plind, i, onFood, onWood, onStone);
      [*] = ;               if (gPlayer[plind].aidata.buildprojects[i].peasantscalled) then
      [*] = ;               _ai_ControlConstruction(plind, i);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            log('_ai_ProcessConstruction : used=false after _ai_GetConstructionSite');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   _misc_ProfilerEnd('_ai_ProcessConstruction');
      [*] = ;end;
      [*] = ;
      [*] = ;//only one tower at time variant:
      [*] = ;{ procedure _ai_ProgressTowersUpgrades(plind : Integer);
      [*] = ;begin
      [*] = ;   if gPlayer[plind].aidata.towers.GetCount > 0 then
      [*] = ;   begin
      [*] = ;      var i : Integer;
      [*] = ;      var isPerfUpgrade : Boolean;
      [*] = ;      var pobj : Pointer;
      [*] = ;      for i:=0 to gPlayer[plind].aidata.towers.GetCount-1 do
      [*] = ;      begin
      [*] = ;         pobj :=  _unit_GetTObj(gPlayer[plind].aidata.towers.get(i));
      [*] = ;         if (TObj(pobj).orders[0].itype=gc_obj_order_type_performupgrade) then
      [*] = ;         begin
      [*] = ;            isPerfUpgrade:=True;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if not(isPerfUpgrade) then
      [*] = ;      begin
      [*] = ;         var index : Integer = floor(gPlayer[plind].aidata.towers.GetCount*random);
      [*] = ;         var goHnd : Integer = gPlayer[plind].aidata.towers.get(index);
      [*] = ;         pobj :=  _unit_GetTObj(goHnd);
      [*] = ;         var upglevel : Integer = TObj(pobj).individual.upglevel;
      [*] = ;         if (pobj<>nil) and (upglevel<6) then
      [*] = ;         begin
      [*] = ;            var reqlevel : Integer = upglevel+1;
      [*] = ;            var cid : Integer = TObj(pobj).cid;
      [*] = ;            var id : Integer = TObj(pobj).id;
      [*] = ;            var p : Pointer = gPlayer[plind].aidata.uniqupg[cid].GetById(id);
      [*] = ;            if (p<>nil) then
      [*] = ;            begin
      [*] = ;               var sid : String = TUniqUpgrade(p).levelsid[reqlevel];
      [*] = ;               var upgid : Integer = TUniqUpgrade(p).levelid[reqlevel];
      [*] = ;               var plHnd : Integer = GetPlayerHandleByIndex(plInd);
      [*] = ;               if (_player_CheckAccessControlRequirements(plHnd, cid, sid)) and (_unit_CanApplyUpgradeCostBySID(plHnd, cid, sid)) then
      [*] = ;               begin
      [*] = ;                  gTmpIntList.Clear;
      [*] = ;                  gTmpIntList.Add(gohnd);
      [*] = ;                  _unit_MakeUpgrade(plHnd, gTmpIntList, upgid, True, True);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end; }
      [*] = ;
      [*] = ;//new:
      [*] = ;
      [*] = ;procedure _ai_ProgressTowersUpgrades(plind : Integer);
      [*] = ;begin
      [*] = ;   if (gPlayer[plInd].aidata.bprogressUpgrades) then
      [*] = ;   begin
      [*] = ;      _misc_ProfilerBegin('_ai_ProgressTowersUpgrades');
      [*] = ;      if gPlayer[plind].aidata.towers.GetCount > 0 then
      [*] = ;      begin
      [*] = ;         var i : Integer;
      [*] = ;         var pobj : Pointer;
      [*] = ;         for i:=0 to gPlayer[plind].aidata.towers.GetCount-1 do
      [*] = ;         begin
      [*] = ;            var goHnd : Integer = gPlayer[plind].aidata.towers.Get(i);
      [*] = ;            pobj := _unit_GetTObj(goHnd);
      [*] = ;            if (pobj<>nil) and (TObj(pobj).orders[0].itype<>gc_obj_order_type_performupgrade) then
      [*] = ;            begin
      [*] = ;               var upglevel : Integer = TObj(pobj).individual.upglevel;
      [*] = ;               var maxlevel : Integer = 6;
      [*] = ;               case difficulty of
      [*] = ;                  gc_player_difficulty_easy : maxlevel := 2;
      [*] = ;                  gc_player_difficulty_normal : maxlevel := 3;
      [*] = ;                  gc_player_difficulty_hard : maxlevel := 4;
      [*] = ;                  gc_player_difficulty_veryhard : maxlevel := 5;
      [*] = ;                  gc_player_difficulty_impossible : maxlevel := 5;
      [*] = ;               end;
      [*] = ;               if (maxlevel>2) and (not _ai_UpgradeIsDoneById(plind, TObj(pobj).cid, gc_ai_upg_stone200)) then
      [*] = ;               maxlevel := 2;
      [*] = ;               if (upglevel<maxlevel) then
      [*] = ;               begin
      [*] = ;                  var reqlevel : Integer = upglevel+1;
      [*] = ;                  var cid : Integer = TObj(pobj).cid;
      [*] = ;                  var id : Integer = TObj(pobj).id;
      [*] = ;                  var p : Pointer = gPlayer[plind].aidata.uniqupg[cid].GetById(id);
      [*] = ;                  if (p<>nil) then
      [*] = ;                  begin
      [*] = ;                     var sid : String = TUniqUpgrade(p).levelsid[reqlevel];
      [*] = ;                     var upgid : Integer = TUniqUpgrade(p).levelid[reqlevel];
      [*] = ;                     var plHnd : Integer = GetPlayerHandleByIndex(plInd);
      [*] = ;                     if (_player_CheckAccessControlRequirements(plHnd, cid, sid)=gc_result_checkaccesscontrolreq_ok) and (_unit_CanApplyUpgradeCostBySID(plHnd, cid, sid)) then
      [*] = ;                     begin
      [*] = ;                        gTmpIntList.Clear;
      [*] = ;                        gTmpIntList.Add(gohnd);
      [*] = ;                        _unit_MakeUpgrade(plHnd, gTmpIntList, upgid, True, True);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      _misc_ProfilerEnd('_ai_ProgressTowersUpgrades');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_DoSeedWheat(plind :Integer);
      [*] = ;begin
      [*] = ;   _misc_ProfilerBegin('_ai_DoSeedWheat');
      [*] = ;   var i : integer;
      [*] = ;   for i:=0 to gPlayer[plind].aidata.milllist.GetCount-1 do
      [*] = ;   begin
      [*] = ;      var goHnd : Integer = gPlayer[plind].aidata.milllist.Get(i);
      [*] = ;      _unit_DoSeedWheat(goHnd, True);
      [*] = ;   end;
      [*] = ;   _misc_ProfilerEnd('_ai_DoSeedWheat');
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_RepairHouses(plind : Integer);
      [*] = ;begin
      [*] = ;   const max_repair_dist = 150;
      [*] = ;   var myisland : Integer = _misc_GetIsland(gPlayer[plind].aidata.centerX, gPlayer[plind].aidata.centerZ);
      [*] = ;   var bcheckdeluids : Boolean = (gPlayer[plind].lists.deluids.GetCount>0);
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to gPlayer[plind].aidata.damagedBuildings.GetCount-1 do
      [*] = ;   begin
      [*] = ;      var goHnd : Integer = gPlayer[plind].aidata.damagedBuildings.Get(i);
      [*] = ;      var posx : Float = GetGameObjectPositionXByHandle(goHnd);
      [*] = ;      var posz : Float = GetGameObjectPositionZByHandle(goHnd);
      [*] = ;      var island : Integer = _misc_GetIsland(posx, posz);
      [*] = ;      if _misc_IsCorrectIslandPosition(plInd, posX, posZ) and (VectorDistance(posx, 0 posz, gPlayer[plind].aidata.centerX, 0 gPlayer[plind].aidata.centerZ)<max_repair_dist) then
      [*] = ;      begin
      [*] = ;         var pObj : pointer = _unit_GetTObj(goHnd);
      [*] = ;         if (pObj<>nil) and (bai or (not bai and not gObjProp[TObj(pobj).cid, TObj(pobj).id].bwall and (not bcheckdeluids or (gPlayer[plind].lists.deluids.IndexOf(GetGameObjectUniqueIdByHandle(gohnd))=-1)))) then
      [*] = ;         begin
      [*] = ;            var pordlist : Pointer = _misc_GetObjectArgData(goHnd, gc_argunit_ordlist);
      [*] = ;            var count : Integer;
      [*] = ;            var j : Integer;
      [*] = ;            for j:=0 to TIntegerList(pordlist).GetCount-1 do
      [*] = ;            begin
      [*] = ;               var pUnitObj : Pointer = _unit_GetTObj(TIntegerList(pordlist).Get(j));
      [*] = ;               if (pUnitObj<>nil) and (gObjProp[TObj(pUnitObj).cid][TObj(pUnitObj).id].usage=gc_obj_usage_peasant){and (TObj(pUnitObj).pl=plind)} then
      [*] = ;               count := count+1;
      [*] = ;            end;
      [*] = ;            if gCustomObjPoints[TObj(pObj).cid, TObj(pObj).id].builderCount=0 then
      [*] = ;            _unit_CalcBuilderPoints(goHnd, gc_BuilderDist);
      [*] = ;            var reqCount : Integer = (Max(5, gCustomObjPoints[TObj(pObj).cid, TObj(pObj).id].builderCount div 3))-count;
      [*] = ;            if (reqCount>0) then
      [*] = ;            begin
      [*] = ;               var mmask : Integer = (1 shl gc_obj_material_body);
      [*] = ;               _misc_MakeListObjectsInRadius(posx, posz, 25, true, mmask, 0, false, gIntegerList);
      [*] = ;               gTmpIntList.Clear;
      [*] = ;               for j:=gIntegerList.GetCount-1 downto 0 do
      [*] = ;               begin
      [*] = ;                  var unitHnd : Integer = gIntegerList.Get(j);
      [*] = ;                  var pobj : Pointer = _unit_GetTObj(unitHnd);
      [*] = ;                  if (pobj<>nil) then
      [*] = ;                  begin
      [*] = ;                     var porder : Pointer = TObj(pobj).orders[0];
      [*] = ;                     var porderinfo : Pointer = TObj(pobj).orders[0].info;
      [*] = ;                     if (TObj(pobj).pl=plind) and (gObjProp[TObj(pobj).cid][TObj(pobj).id].usage=gc_obj_usage_peasant) and
      [*] = ;                     ((TOrder(porder).itype=gc_obj_order_type_gainres) and (TOrderInfo(porderinfo).restype<>gc_resource_type_food) and (TObj(pObj).squad=-1)) then
      [*] = ;                     gTmpIntList.Add(unitHnd);
      [*] = ;                     if (gTmpIntList.GetCount>reqCount) then
      [*] = ;                     break;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               if (gTmpIntList.GetCount>0) then
      [*] = ;               _player_OrderUnitsToBuild(gTmpIntList, goHnd, true, true, true)
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  _misc_MakeListObjectsInRadius(gPlayer[plind].aidata.centerx, gPlayer[plind].aidata.centerz, 25, true, mmask, 0, false, gIntegerList);
      [*] = ;                  gTmpIntList.Clear;
      [*] = ;                  for j:=gIntegerList.GetCount-1 downto 0 do
      [*] = ;                  begin
      [*] = ;                     var unitHnd : Integer = gIntegerList.Get(j);
      [*] = ;                     var essentialtag : Integer = GetGameObjectStatesTagByHandle(unitHnd) and gc_statetag_essential;
      [*] = ;                     if (essentialtag=gc_statetag_essential_none) then
      [*] = ;                     begin
      [*] = ;                        var pobj : Pointer = _unit_GetTObj(unitHnd);
      [*] = ;                        if (pobj<>nil) then
      [*] = ;                        begin
      [*] = ;                           var porder : Pointer = TObj(pobj).orders[0];
      [*] = ;                           var porderinfo : Pointer = TObj(pobj).orders[0].info;
      [*] = ;                           if (TObj(pobj).pl=plind) and (gObjProp[TObj(pobj).cid][TObj(pobj).id].usage=gc_obj_usage_peasant) and
      [*] = ;                           ((TOrder(porder).itype=gc_obj_order_type_gainres) and (TOrderInfo(porderinfo).restype<>gc_resource_type_food) and (TObj(pObj).squad=-1)) then
      [*] = ;                           gTmpIntList.Add(unitHnd);
      [*] = ;                           if (gTmpIntList.GetCount>reqCount) then
      [*] = ;                           break;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  if (gTmpIntList.GetCount>0) then
      [*] = ;                  _player_OrderUnitsToBuild(gTmpIntList, goHnd, true, true, true)
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _ai_SetupDevelopingStrategy(plind : Integer);
      [*] = ;begin
      [*] = ;   var rnd : Float;
      [*] = ;   rnd := random;
      [*] = ;   gPlayer[plind].aidata.bFlags[gc_ai_flag_economic_exp] := (rnd>0.9);
      [*] = ;   //use uniq inf17 instead of usual:
      [*] = ;   rnd := random;
      [*] = ;   gPlayer[plind].aidata.bFlags[gc_ai_flag_uniq_inf17] := (rnd>0.6);
      [*] = ;   //use uniq cav17 instead of usual:
      [*] = ;   rnd := random;
      [*] = ;   if rnd<0.3 then gPlayer[plind].aidata.bFlags[gc_ai_flag_uniq_cav17] := true
      [*] = ;   else
      [*] = ;   if rnd<0.5 then gPlayer[plind].aidata.bFlags[gc_ai_flag_drag_cav17] := true;
      [*] = ;   //define infrantry to build:
      [*] = ;   rnd := random;
      [*] = ;   if rnd<0.4 then gPlayer[plind].aidata.bFlags[gc_ai_flag_uniq_inf18] := true
      [*] = ;   else
      [*] = ;   if (gPlayer[plind].cid=cid_sco) and (rnd<0.6) then gPlayer[plind].aidata.bFlags[gc_ai_flag_grenadier] := true;
      [*] = ;   //do cavalry:
      [*] = ;   rnd := random;
      [*] = ;   if (rnd<0.3) then gPlayer[plind].aidata.bFlags[gc_ai_flag_hussar] := true
      [*] = ;   else
      [*] = ;   if (rnd<0.6) then gPlayer[plind].aidata.bFlags[gc_ai_flag_cuirassiers] := true;
      [*] = ;   //
      [*] = ;   //test code:
      [*] = ;   {gPlayer[plind].aidata.bFlags[gc_ai_flag_economic_exp] := True;
      [*] = ;   gPlayer[plind].aidata.bFlags[gc_ai_flag_uniq_inf17]   := True;
      [*] = ;   gPlayer[plind].aidata.bFlags[gc_ai_flag_uniq_cav17]   := True;
      [*] = ;   gPlayer[plind].aidata.bFlags[gc_ai_flag_drag_cav17]   := not True;
      [*] = ;   gPlayer[plind].aidata.bFlags[gc_ai_flag_uniq_inf18]   := not True;
      [*] = ;   gPlayer[plind].aidata.bFlags[gc_ai_flag_hussar]       := not True;
      [*] = ;   gPlayer[plind].aidata.bFlags[gc_ai_flag_cuirassiers]  := True;
      [*] = ;   gPlayer[plind].aidata.bFlags[gc_ai_flag_grenadier]    := True;}
      [*] = ;
      [*] = ;   //log current settings:
      [*] = ;   {log('plind: '+inttostr(plind));
      [*] = ;   log('gc_ai_flag_economic_exp: '+BoolToStr(gPlayer[plind].aidata.bFlags[gc_ai_flag_economic_exp]));
      [*] = ;   log('gc_ai_flag_uniq_inf17:   '+BoolToStr(gPlayer[plind].aidata.bFlags[gc_ai_flag_uniq_inf17]));
      [*] = ;   log('gc_ai_flag_uniq_cav17:   '+BoolToStr(gPlayer[plind].aidata.bFlags[gc_ai_flag_uniq_cav17]));
      [*] = ;   log('gc_ai_flag_drag_cav17:   '+BoolToStr(gPlayer[plind].aidata.bFlags[gc_ai_flag_drag_cav17]));
      [*] = ;   log('gc_ai_flag_uniq_inf18:   '+BoolToStr(gPlayer[plind].aidata.bFlags[gc_ai_flag_uniq_inf18]));
      [*] = ;   log('gc_ai_flag_hussar:       '+BoolToStr(gPlayer[plind].aidata.bFlags[gc_ai_flag_hussar]));
      [*] = ;   log('gc_ai_flag_cuirassiers:  '+BoolToStr(gPlayer[plind].aidata.bFlags[gc_ai_flag_cuirassiers]));
      [*] = ;   log('gc_ai_flag_grenadier:    '+BoolToStr(gPlayer[plind].aidata.bFlags[gc_ai_flag_grenadier]));}
      [*] = ;end;
      [*] = ;
      [*] = ;if (gPlayer[plind].aidata.centerfound) then
      [*] = ;begin
      [*] = ;   const cProgressAITick = 16;
      [*] = ;   const cProgressSeedWheat = 15;
      [*] = ;   var progressTick : Integer = gPlayer[plInd].progressTick;
      [*] = ;
      [*] = ;   var zone : Integer = TopologyGetZoneIndex(gPlayer[plInd].aiData.centerX, gPlayer[plInd].aiData.centerZ);
      [*] = ;   var pBuffer : Pointer = TopologyGetZoneBufferByIndex(zone);
      [*] = ;   if pBuffer <> nil then
      [*] = ;   begin
      [*] = ;      if TTopZone(pBuffer).centerDist[plInd] <> 0 then
      [*] = ;      _misc_CalcPlayerZonesDist(plInd);
      [*] = ;   end;
      [*] = ;
      [*] = ;   _misc_ProfilerBegin('EconomicAI.EnumUnits');
      [*] = ;   _ai_EnumUnits(plind);
      [*] = ;   _misc_ProfilerEnd('EconomicAI.EnumUnits');
      [*] = ;
      [*] = ;   _misc_ProfilerBegin('EconomicAI.Progress');
      [*] = ;   //main ai progress
      [*] = ;   var onFood, onWood, onStone : Integer;
      [*] = ;   _ai_CalculateCurrentResourceCollection(plind, onFood, onWood, onStone);
      [*] = ;
      [*] = ;   var maincid : Integer = -1;
      [*] = ;   var maxcount : Integer;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to gc_MaxCountryCount-1 do
      [*] = ;   if (gPlayer[plind].aidata.controllednations[i]) and (_ai_GetUnitCount(plind, i, gc_ai_unit_peasant)>maxcount) then
      [*] = ;   begin
      [*] = ;      maincid := i;
      [*] = ;      maxcount := _ai_GetUnitCount(plind, i, gc_ai_unit_peasant);
      [*] = ;   end;
      [*] = ;   if (bprocess) and (maincid>=0) then
      [*] = ;   _ai_ResourcesDistributionScript(plind, maincid, onFood, onWood, onStone);
      [*] = ;
      [*] = ;   for i:=0 to gc_MaxCountryCount-1 do
      [*] = ;   if (gPlayer[plind].aidata.controllednations[i]) then
      [*] = ;   _ai_MainConstructionIdeasScript(plind, i, onFood, onWood, onStone);
      [*] = ;   //TimeLog('_ai_MainConstructionIdeasScript(plhnd, plind);');
      [*] = ;   //process ideas
      [*] = ;   _ai_ProcessIdeas(plind);
      [*] = ;   //TimeLog('_ai_ProcessIdeas(plhnd, plind);');
      [*] = ;   //process buildings
      [*] = ;   if (bai) or ((not bai) and gPlayer[plind].playeradviser.adviser.benable and (gPlayer[plind].playeradviser.adviser.bconstruct or (gPlayer[plind].playeradviser.adviser.beconomy and gPlayer[plind].playeradviser.adviser.brepairbuildings))) then
      [*] = ;   _ai_ProcessConstruction(plind, onFood, onWood, onStone);
      [*] = ;   //TimeLog('_ai_ProcessConstruction(plhnd, plind);');
      [*] = ;   //reasign peasants
      [*] = ;   if (bai) or ((not bai) and gPlayer[plind].playeradviser.adviser.benable and gPlayer[plind].playeradviser.adviser.beconomy and gPlayer[plind].playeradviser.adviser.bcontrolpeasants and (gPlayer[plind].aidata.storelist.GetCount>0) and (gPlayer[plind].aidata.milllist.GetCount>0)) then
      [*] = ;   if (bprocess) then
      [*] = ;   _ai_GainResourcesByPeasants(plind, onFood, onWood, onStone);
      [*] = ;   //upgrade mines if needed
      [*] = ;   if (not bai) then
      [*] = ;   begin
      [*] = ;      if (not bai and gPlayer[plind].playeradviser.adviser.benable and gPlayer[plind].playeradviser.adviser.beconomy and gPlayer[plind].playeradviser.adviser.bfillmines) then
      [*] = ;      if (bprocess) and (_ai_GetUnitCountAnyFaction(plind, gc_ai_unit_center)>=1) then
      [*] = ;      _ai_FillMines(plind);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (_ai_GetUnitCountAnyFaction(plind, gc_ai_unit_center)>=2) and (_ai_GetUnitCountAnyFaction(plind, gc_ai_unit_ba17)>=2) then
      [*] = ;   begin
      [*] = ;      _ai_ProgressMinesUpgrades(plind);
      [*] = ;      _ai_FillMines(plind);
      [*] = ;   end;
      [*] = ;   //ai_upgrade_towers
      [*] = ;   if (bai) {or ((not bai) and gPlayer[plind].playeradviser.adviser.benable and gPlayer[plind].playeradviser.adviser.bupgrades)} then
      [*] = ;   _ai_ProgressTowersUpgrades(plind);
      [*] = ;
      [*] = ;   if (bprocess) and (_player_CheckProgressLastTimeAndIncrease(gPlayer[plInd].lastseedwheattime, 3, gc_global_TimeSeedWheat+plInd*3)) then
      [*] = ;   begin
      [*] = ;      _misc_ProfilerBegin('_ai_DoSeedWheat');
      [*] = ;      if (bai) or (not bai and gPlayer[plind].playeradviser.adviser.benable and gPlayer[plind].playeradviser.adviser.beconomy) then
      [*] = ;      _ai_DoSeedWheat(plind);
      [*] = ;      _misc_ProfilerEnd('_ai_DoSeedWheat');
      [*] = ;   end;
      [*] = ;   _misc_ProfilerEnd('EconomicAI.Progress');
      [*] = ;   _misc_ProfilerBegin('EconomicAI.RepairHouses');
      [*] = ;   if (bai) or (not bai and gPlayer[plind].playeradviser.adviser.benable and gPlayer[plind].playeradviser.adviser.beconomy and gPlayer[plind].playeradviser.adviser.brepairbuildings) then
      [*] = ;   if (bprocess) then
      [*] = ;   _ai_RepairHouses(plind);
      [*] = ;   _misc_ProfilerEnd('EconomicAI.RepairHouses');
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   //means ai not inited yet
      [*] = ;   gPlayer[plind].aidata.centerfound := true;
      [*] = ;   _ai_FindCenter(gPlayer[plind].aidata.centerx, gPlayer[plind].aidata.centerz, plhnd);
      [*] = ;   _misc_CalcPlayerZonesDist(plInd);
      [*] = ;   _ai_InitInitialLists(plind);
      [*] = ;   _ai_SetupDevelopingStrategy(plind);
      [*] = ;   gPlayer[plind].aidata.inittime := GetGameTime;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Progress');
   struct.end
section.end

