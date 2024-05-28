section.begin
   Name = TextureMap
   Code : struct.begin
      [*] = ;const cRNone = 0;
      [*] = ;const cRPlateau = 1;
      [*] = ;const cRHill = 2;
      [*] = ;const cRRavine = 3;
      [*] = ;const cGNone = 0;
      [*] = ;const cGForest = 1;
      [*] = ;const cGGenForest = 2;
      [*] = ;const cGStone = 3;
      [*] = ;const cGForestStone = 4;
      [*] = ;const cBNone = 0;
      [*] = ;const cBWater = 1;
      [*] = ;
      [*] = ;const cRColorPlateau = 255;
      [*] = ;const cRColorHill = 96;
      [*] = ;const cRColorRavine = 48;
      [*] = ;const cRColorSmooth = 128 div 2;
      [*] = ;const cRColorPlateauSmooth = ((cRColorPlateau div 2)+cRColorSmooth);
      [*] = ;const cRColorHillSmooth = ((cRColorHill div 2)+cRColorSmooth);
      [*] = ;const cRColorRavineSmooth = ((cRColorRavine div 2)+cRColorSmooth);
      [*] = ;const cGColorForest = 255;
      [*] = ;const cGColorGenForest = 64;
      [*] = ;const cGColorStone = 128;
      [*] = ;const cGColorForestStone = 192;
      [*] = ;const cBColorWater = 255;
      [*] = ;
      [*] = ;const cMaxHeight = 2.96;
      [*] = ;const cWaterHeight = -0.25;
      [*] = ;const cWaterShoreHeight = -0.1;
      [*] = ;
      [*] = ;const cUpdateCollision = True;
      [*] = ;const cPlaceForest = True;
      [*] = ;const cFixPlaceForestsObjSizes = True;
      [*] = ;const cPaintEnvironmentTextures = True;
      [*] = ;const cSmoothForestBorders = True;
      [*] = ;const cTextureTerrain = True;
      [*] = ;const cPlaceRoads = True;
      [*] = ;
      [*] = ;const cForestTypePineFirSpruce = 0;
      [*] = ;const cForestTypeMixed = 1;
      [*] = ;const cForestTypeLeaf = 2;
      [*] = ;var forestType : Integer = IntRegister0;
      [*] = ;
      [*] = ;var mapwidth : Integer = GetMapWidth;
      [*] = ;var mapheight : Integer = GetMapHeight;
      [*] = ;var lx, ty : Float;
      [*] = ;_misc_GetMapLeftTopPos(lx, ty);
      [*] = ;var i : Integer;
      [*] = ;var x, y : Integer;
      [*] = ;
      [*] = ;if (cUpdateCollision) then
      [*] = ;begin
      [*] = ;   ApplicationProcessMessages;
      [*] = ;   for y:=0 to GetMapHeight do
      [*] = ;   for x:=0 to GetMapWidth do
      [*] = ;   begin
      [*] = ;      var ix : Integer = ClampInt(x, 0, mapwidth-1);
      [*] = ;      var iy : Integer = ClampInt(y, 0, mapheight-1);
      [*] = ;      var realx : Integer = floor(lx+x);
      [*] = ;      var realy : Integer = floor(ty+y);
      [*] = ;      const cDiff1 = 0.5;
      [*] = ;      const cDiff2 = 0.55;
      [*] = ;
      [*] = ;      var height : Float = GetHeightData(realx, realy);
      [*] = ;      var bWater, bWaterShore : Boolean;
      [*] = ;      if (gMapMask[ix,iy].b>0) then
      [*] = ;      begin
      [*] = ;         if (height<cWaterHeight) then
      [*] = ;         bWater := True
      [*] = ;         else
      [*] = ;         if (height<cWaterShoreHeight) then
      [*] = ;         bWaterShore := True;
      [*] = ;      end;
      [*] = ;      var lh : Float = GetHeightData(realx-1, realy);
      [*] = ;      var rh : Float = GetHeightData(realx+1, realy);
      [*] = ;      var th : Float = GetHeightData(realx, realy-1);
      [*] = ;      var bh : Float = GetHeightData(realx, realy+1);
      [*] = ;      var rbh : Float = GetHeightData(realx+1, realy+1);
      [*] = ;      if (bWater) then
      [*] = ;      begin
      [*] = ;         MapDrawCollision(realx, realy, gc_collisiontag_water, 1, True);
      [*] = ;         MapDrawCollision(realx-0.5, realy-0.5, gc_collisiontag_water, 1, True);
      [*] = ;         MapDrawCollision(realx-0.5, realy, gc_collisiontag_water, 1, True);
      [*] = ;         MapDrawCollision(realx, realy-0.5, gc_collisiontag_water, 1, True);
      [*] = ;      end;
      [*] = ;      if (Abs(height-lh)>cDiff1) then
      [*] = ;      begin
      [*] = ;         MapDrawCollision(realx, realy, gc_collisiontag_terrain, 1, True);
      [*] = ;         MapDrawCollision(realx-0.5, realy-0.5, gc_collisiontag_terrain, 1, True);
      [*] = ;         MapDrawCollision(realx-0.5, realy, gc_collisiontag_terrain, 1, True);
      [*] = ;         MapDrawCollision(realx, realy-0.5, gc_collisiontag_terrain, 1, True);
      [*] = ;      end;
      [*] = ;      if (Abs(height-rh)>cDiff1) then
      [*] = ;      begin
      [*] = ;         MapDrawCollision(realx, realy, gc_collisiontag_terrain, 1, True);
      [*] = ;         MapDrawCollision(realx-0.5, realy-0.5, gc_collisiontag_terrain, 1, True);
      [*] = ;         MapDrawCollision(realx-0.5, realy, gc_collisiontag_terrain, 1, True);
      [*] = ;         MapDrawCollision(realx, realy-0.5, gc_collisiontag_terrain, 1, True);
      [*] = ;      end;
      [*] = ;      if (Abs(height-bh)>cDiff1) then
      [*] = ;      begin
      [*] = ;         MapDrawCollision(realx, realy, gc_collisiontag_terrain, 1, True);
      [*] = ;         MapDrawCollision(realx-0.5, realy, gc_collisiontag_terrain, 1, True);
      [*] = ;         MapDrawCollision(realx, realy-0.5, gc_collisiontag_terrain, 1, True);
      [*] = ;         MapDrawCollision(realx-0.5, realy-0.5, gc_collisiontag_terrain, 1, True);
      [*] = ;      end;
      [*] = ;      if (Abs(height-th)>cDiff1) then
      [*] = ;      begin
      [*] = ;         MapDrawCollision(realx-0.5, realy-0.5, gc_collisiontag_terrain, 1, True);
      [*] = ;         MapDrawCollision(realx, realy-0.5, gc_collisiontag_terrain, 1, True);
      [*] = ;         MapDrawCollision(realx, realy, gc_collisiontag_terrain, 1, True);
      [*] = ;         MapDrawCollision(realx-0.5, realy, gc_collisiontag_terrain, 1, True);
      [*] = ;      end;
      [*] = ;      if (Abs(bh-rh)>cDiff2) then
      [*] = ;      begin
      [*] = ;         MapDrawCollision(realx, realy, gc_collisiontag_terrain, 1, True);
      [*] = ;         MapDrawCollision(realx+0.5, realy+0.5, gc_collisiontag_terrain, 1, True);
      [*] = ;         MapDrawCollision(realx+0.5, realy, gc_collisiontag_terrain, 1, True);
      [*] = ;         MapDrawCollision(realx, realy+0.5, gc_collisiontag_terrain, 1, True);
      [*] = ;      end;
      [*] = ;      if (Abs(height-rbh)>cDiff2) then
      [*] = ;      begin
      [*] = ;         MapDrawCollision(realx, realy, gc_collisiontag_terrain, 1, True);
      [*] = ;         MapDrawCollision(realx+0.5, realy+0.5, gc_collisiontag_terrain, 1, True);
      [*] = ;         MapDrawCollision(realx+0.5, realy, gc_collisiontag_terrain, 1, True);
      [*] = ;         MapDrawCollision(realx, realy+0.5, gc_collisiontag_terrain, 1, True);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   ApplicationProcessMessages;
      [*] = ;   for y:=0 to GetMapHeight*2 do
      [*] = ;   for x:=0 to GetMapWidth*2 do
      [*] = ;   begin
      [*] = ;      var realx : Float = lx+x/2+0.25;
      [*] = ;      var realy : Float = ty+y/2+0.25;
      [*] = ;      if (GetMapCollisionTag(realx, realy, False)=0) then
      [*] = ;      begin
      [*] = ;         var count : Integer;
      [*] = ;         if (GetMapCollisionTag(realx-0.5, realy, False)<>0) then
      [*] = ;         count := count+1;
      [*] = ;         if (GetMapCollisionTag(realx+0.5, realy, False)<>0) then
      [*] = ;         count := count+1;
      [*] = ;         if (GetMapCollisionTag(realx, realy-0.5, False)<>0) then
      [*] = ;         count := count+1;
      [*] = ;         if (GetMapCollisionTag(realx, realy+0.5, False)<>0) then
      [*] = ;         count := count+1;
      [*] = ;         if count>=3 then
      [*] = ;         MapDrawCollision(realx, realy, gc_collisiontag_terrain, 0, False);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   // backward
      [*] = ;   ApplicationProcessMessages;
      [*] = ;   for y:=GetMapHeight*2 downto 0 do
      [*] = ;   for x:=GetMapWidth*2 downto 0 do
      [*] = ;   begin
      [*] = ;      var realx : Float = lx+x/2+0.25;
      [*] = ;      var realy : Float = ty+y/2+0.25;
      [*] = ;      if (GetMapCollisionTag(realx, realy, False)=0) then
      [*] = ;      begin
      [*] = ;         var count : Integer;
      [*] = ;         if (GetMapCollisionTag(realx-0.5, realy, False)<>0) then
      [*] = ;         count := count+1;
      [*] = ;         if (GetMapCollisionTag(realx+0.5, realy, False)<>0) then
      [*] = ;         count := count+1;
      [*] = ;         if (GetMapCollisionTag(realx, realy-0.5, False)<>0) then
      [*] = ;         count := count+1;
      [*] = ;         if (GetMapCollisionTag(realx, realy+0.5, False)<>0) then
      [*] = ;         count := count+1;
      [*] = ;         if count>=3 then
      [*] = ;         MapDrawCollision(realx, realy, gc_collisiontag_terrain, 0, False);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   ApplicationProcessMessages;
      [*] = ;end;
      [*] = ;
      [*] = ;var envPlHnd : Integer = GetPlayerHandleByIndex(gc_playerind_env);
      [*] = ;var lastenvcount : Integer = GetPlayerGameObjectsCountByHandle(envPlHnd);
      [*] = ;if (cPlaceForest) then
      [*] = ;begin
      [*] = ;   ApplicationProcessMessages;
      [*] = ;   LoadPatterns(True, True);
      [*] = ;   for y:=0 to gc_terraindata_mapwidth-1 do
      [*] = ;   for x:=0 to gc_terraindata_mapheight-1 do
      [*] = ;   gPatternMask[x, y] := False;
      [*] = ;
      [*] = ;   ApplicationProcessMessages;
      [*] = ;   for y:=0 to (GetMapHeight-1)*2 do
      [*] = ;   for x:=0 to (GetMapWidth-1)*2 do
      [*] = ;   begin
      [*] = ;      var realx : Float = lx+x/2+0.25;
      [*] = ;      var realy : Float = ty+y/2+0.25;
      [*] = ;      if (GetMapCollisionTag(realx, realy, False)<>0) then
      [*] = ;      gPatternMask[x div 2, y div 2] := True;
      [*] = ;   end;
      [*] = ;
      [*] = ;   for y:=0 to mapheight-1 do
      [*] = ;   for x:=0 to mapwidth-1 do
      [*] = ;   begin
      [*] = ;      //if ((gMapMask[x,y].forest<>cGGenForest) and (gMapMask[x,y].forest<>cGForest) and (gMapMask[x,y].forest<>cGStone) and (gMapMask[x,y].forest<>cGForestStone)) then
      [*] = ;      //gPatternMask[x, y] := True;
      [*] = ;   end;
      [*] = ;
      [*] = ;   ApplicationProcessMessages;
      [*] = ;   for y:=0 to mapheight-1 do
      [*] = ;   for x:=0 to mapwidth-1 do
      [*] = ;   begin
      [*] = ;      if (not gPatternMask[x, y]) and ((gMapMask[x,y].forest=cGStone) or (gMapMask[x,y].forest=cGForestStone)) then
      [*] = ;      begin
      [*] = ;         var realx : Integer = floor(lx+x);
      [*] = ;         var realy : Integer = floor(ty+y);
      [*] = ;
      [*] = ;         // TODO Place stone and forest stone patterns
      [*] = ;         var pname : String = 'n_small_frt_'+IntToStr(1);
      [*] = ;         _misc_CheckStandPattern(pname, envPlHnd, realx, realy, 0, True, False, 0);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var try0, try1, try2, try3 : Integer;
      [*] = ;   const cCatergoryCount = 3;
      [*] = ;   for [MAIN]try0:=1 to 1 do
      [*] = ;   begin
      [*] = ;      for try1:=0 to cCatergoryCount-1 do
      [*] = ;      begin
      [*] = ;         ApplicationProcessMessages;
      [*] = ;         for y:=0 to mapheight-1 do
      [*] = ;         for x:=0 to mapwidth-1 do
      [*] = ;         begin
      [*] = ;            if (not gPatternMask[x, y]) then
      [*] = ;            begin
      [*] = ;               var realx : Integer = floor(lx+x);
      [*] = ;               var realy : Integer = floor(ty+y);
      [*] = ;               if (gMapMask[x,y].forest=cGForest) then
      [*] = ;               begin
      [*] = ;                  var pname : String;
      [*] = ;                  var ind : Integer = -1;
      [*] = ;                  if (try0=0) then
      [*] = ;                  begin
      [*] = ;                     //try2 := 16;
      [*] = ;                     {var arrcost : array [0..cCatergoryCount-1] of Float;
      [*] = ;                     arrcost[0] := 16;
      [*] = ;                     arrcost[1] := 16;
      [*] = ;                     arrcost[2] := 4;
      [*] = ;                     arrcost[3] := 1;
      [*] = ;                     var costsum : Float;
      [*] = ;                     var k : Integer;
      [*] = ;                     for k:=0 to cCatergoryCount-1 do
      [*] = ;                     costsum := costsum+arrcost[k];
      [*] = ;                     var j : Integer;}
      [*] = ;                     for [SECOND]try2:=0 to 7 do
      [*] = ;                     begin
      [*] = ;                        var arrind : Integer = -1;
      [*] = ;                        {var rnd : Float = RandomExt*costsum;
      [*] = ;                        var sum : Float;
      [*] = ;                        for k:=0 to cCatergoryCount-1 do
      [*] = ;                        begin
      [*] = ;                           sum := sum+arrcost[k];
      [*] = ;                           if (rnd<=sum) then
      [*] = ;                           begin
      [*] = ;                              arrind := k;
      [*] = ;                              break;
      [*] = ;                           end;
      [*] = ;                        end;}
      [*] = ;                        case try1 of
      [*] = ;                           0 : arrind := _misc_SwitchInt(0, 1, RandomExt<0.375);
      [*] = ;                           1 : arrind := 2;
      [*] = ;                           2 : arrind := _misc_SwitchInt(2, 3, RandomExt<0.5);
      [*] = ;                        end;
      [*] = ;                        for try3:=0 to 15 do
      [*] = ;                        begin
      [*] = ;                           case arrind of
      [*] = ;                              0 : pname := 'b_frt_b_p_'+IntToStr(floor(1+3*RandomExt));
      [*] = ;                              1 : pname := 'frt_b_p_'+IntToStr(floor(1+8*RandomExt));
      [*] = ;                              2 : pname := 'frt_m_p_'+IntToStr(floor(1+10*RandomExt));
      [*] = ;                              3 : pname := 'frt_s_p_'+IntToStr(floor(1+6*RandomExt));
      [*] = ;                              else
      [*] = ;                              ErrorLog('Unknown arrind in common.aix:TextureMap');
      [*] = ;                           end;
      [*] = ;                           if (pname='frt_s_p_6') or (pname='frt_s_p_4') or (pname='frt_s_p_2') then
      [*] = ;                           continue;
      [*] = ;                           if (pname<>'') then
      [*] = ;                           begin
      [*] = ;                              if (_misc_CheckStandPattern(pname, envPlHnd, realx, realy, 0, False, False, 0)) then
      [*] = ;                              begin
      [*] = ;                                 //Log('pattern placed ['+IntToStr(arrind)+'] = '+pname+' x = '+FloatToStr(realx)+' y = '+FloatToStr(realy));
      [*] = ;                                 _misc_CheckStandPattern(pname, envPlHnd, realx, realy, 0, True, False, 0);
      [*] = ;                                 break(SECOND);
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     case forestType of
      [*] = ;                        cForestTypePineFirSpruce : begin
      [*] = ;                           ind := 1+floor(17*RandomExt);
      [*] = ;                        end;
      [*] = ;                        cForestTypeMixed : begin
      [*] = ;                           ind := 18+floor(7*RandomExt);
      [*] = ;                        end;
      [*] = ;                        cForestTypeLeaf : begin
      [*] = ;                           ind := 18+floor(7*RandomExt);
      [*] = ;                           if (ind=22) or (ind=23) then // mixed
      [*] = ;                           ind := 18+floor(5*RandomExt);
      [*] = ;                           if (ind=22) then ind := 24;
      [*] = ;                        end;
      [*] = ;                        else
      [*] = ;                        ErrorLog('TextureMap : PlaceForest : unknown forestType');
      [*] = ;                     end;
      [*] = ;                     const cLiteProb = 0.6;
      [*] = ;
      [*] = ;                     if (ind>=0) then
      [*] = ;                     begin
      [*] = ;                        if (RandomExt<cLiteProb) then
      [*] = ;                        pname := 'n_small_frt_lite_'+IntToStr(ind)
      [*] = ;                        else
      [*] = ;                        pname := 'n_small_frt_'+IntToStr(ind);
      [*] = ;                        if (_misc_CheckStandPattern(pname, envPlHnd, realx, realy, 0, False, False, 0)) then
      [*] = ;                        begin
      [*] = ;                           //Log('pattern placed [simple] = '+pname+' x = '+FloatToStr(realx)+' y = '+FloatToStr(realy));
      [*] = ;                           _misc_CheckStandPattern(pname, envPlHnd, realx, realy, 0, True, False, 0);
      [*] = ;                           //break(SECOND);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  //var ind : Integer = 1+floor(24*RandomExt);
      [*] = ;                  //var ind : Integer = 18+floor(7*RandomExt); // leaf
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if (try0=1) then
      [*] = ;         break(MAIN);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var envbitmap : Integer;
      [*] = ;if (cPaintEnvironmentTextures) then
      [*] = ;begin
      [*] = ;   ApplicationProcessMessages;
      [*] = ;   IntRegister0 := forestType;
      [*] = ;   ExecuteState('SaveEnvironmentToBitmap');
      [*] = ;   envbitmap := IntRegister2;
      [*] = ;
      [*] = ;   if (envbitmap<>0) then
      [*] = ;   begin
      [*] = ;      ApplicationProcessMessages;
      [*] = ;      IntRegister0 := forestType;
      [*] = ;      IntRegister2 := envbitmap;
      [*] = ;      ExecuteState('LoadEnvironmentFromBitmap');
      [*] = ;      ApplicationProcessMessages;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (cSmoothForestBorders) and (envbitmap<>0) then // requires envbitmap
      [*] = ;   begin
      [*] = ;      IntRegister0 := forestType;
      [*] = ;      IntRegister2 := envbitmap;
      [*] = ;      ExecuteState('SmoothForestBorders');
      [*] = ;   end;
      [*] = ;   FreeBitmap(envbitmap);
      [*] = ;end;
      [*] = ;
      [*] = ;if (cFixPlaceForestsObjSizes) then
      [*] = ;begin
      [*] = ;   var envplhnd : Integer = GetPlayerHandleByName(gc_racename_env);
      [*] = ;   var i : Integer;
      [*] = ;   for i:=GetPlayerGameObjectsCountByHandle(envplhnd)-1 downto lastenvcount do
      [*] = ;   begin
      [*] = ;      var goHnd : Integer = GetGameObjectHandleByIndex(i, envplhnd);
      [*] = ;      var basename : String = GetGameObjectBaseNameByHandle(goHnd);
      [*] = ;      if StrExists(basename, 'terrainmesh') or (StrExists(basename, 'stones')) then
      [*] = ;      continue;
      [*] = ;      var scale : Float = GetGameObjectScaleXByHandle(goHnd);
      [*] = ;
      [*] = ;      var x, y, z, minfact, maxfact, deffact : Float;
      [*] = ;      var rand : Boolean;
      [*] = ;      GetGameObjectDefScalePropsByHandle(goHnd, x, y, z, rand, minfact, maxfact, deffact);
      [*] = ;      var scaleMid, scaleMin, scaleMax : Float;
      [*] = ;      if (rand) then
      [*] = ;      begin
      [*] = ;         scaleMin := x*minfact;
      [*] = ;         scaleMid := x*((minfact+maxfact)/2);
      [*] = ;         scaleMax := x*maxfact;
      [*] = ;
      [*] = ;         if ((Abs(scaleMax-scaleMin))>scaleMid*0.05) then
      [*] = ;         begin
      [*] = ;            if (scale<scaleMin) then
      [*] = ;            begin
      [*] = ;               const cDiffKoefMin = 0.875;
      [*] = ;               const cDiffKoefMax = 0.95;
      [*] = ;               var koef : Float = (scaleMin/scaleMid)*(cDiffKoefMin+random*(cDiffKoefMax-cDiffKoefMin));
      [*] = ;               var newscale : Float = scaleMid*koef;
      [*] = ;               if (newscale<scale) then
      [*] = ;               newscale := scale;
      [*] = ;               SetGameObjectScaleByHandle(goHnd, newscale, newscale, newscale);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if (scale>scaleMax) then
      [*] = ;            begin
      [*] = ;               const cDiffKoefMin = 1.04;
      [*] = ;               const cDiffKoefMax = 1.08;
      [*] = ;               var koef : Float = (scaleMax/scaleMid)*(cDiffKoefMin+random*(cDiffKoefMax-cDiffKoefMin));
      [*] = ;               var newscale : Float = scaleMid*koef;
      [*] = ;               if (newscale>scale) then
      [*] = ;               newscale := scale;
      [*] = ;               SetGameObjectScaleByHandle(goHnd, newscale, newscale, newscale);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (cTextureTerrain) then
      [*] = ;begin
      [*] = ;   //var il, it, ib, ir, irb, ilb : Integer;
      [*] = ;   ApplicationProcessMessages;
      [*] = ;   var lower, upper1, upper2, middle : Integer;
      [*] = ;   for y:=0 to GetMapHeight do
      [*] = ;   for x:=0 to GetMapWidth do
      [*] = ;   begin
      [*] = ;      var realx : Integer = floor(lx+x);
      [*] = ;      var realy : Integer = floor(ty+y);
      [*] = ;
      [*] = ;      var height : Float = GetHeightData(realx, realy);
      [*] = ;      {var bWater, bWaterShore : Boolean;
      [*] = ;      if (height<cWaterHeight) then
      [*] = ;      bWater := True
      [*] = ;      else
      [*] = ;      if (height<cWaterShoreHeight) then
      [*] = ;      bWaterShore := True;}
      [*] = ;      var lh : Float = GetHeightData(Max(round(lx), realx-1), realy);
      [*] = ;      var rh : Float = GetHeightData(Min(GetMapWidth div 2, realx+1), realy);
      [*] = ;      var th : Float = GetHeightData(realx, Max(round(ty), realy-1));
      [*] = ;      var bh : Float = GetHeightData(realx, Min(GetMapHeight div 2, realy+1));
      [*] = ;      var rbh : Float = GetHeightData(Min(GetMapWidth div 2, realx+1), Min(GetMapHeight div 2, realy+1));
      [*] = ;      var dirX : Float = lh-rh;
      [*] = ;      var dirY : Float = th-bh;
      [*] = ;      var dirN : Float;
      [*] = ;      var len : Float = VectorLength(dirX, dirN, dirY);
      [*] = ;      if (len>0.01) then
      [*] = ;      begin
      [*] = ;         VectorNormalize(dirX, dirN, dirY);
      [*] = ;         var vecangle : Float = VectorAngle(1, 0, 0, dirX, 0, dirY);
      [*] = ;         if (dirY<0) then
      [*] = ;         vecangle := -vecangle;
      [*] = ;
      [*] = ;         {if (bRB) then irb := irb+1;
      [*] = ;         if (bLB) then ilb := ilb+1;
      [*] = ;         if (bL) then il := il+1;
      [*] = ;         if (bR) then ir := ir+1;
      [*] = ;         if (bT) then it := it+1;
      [*] = ;         if (bB) then ib := ib+1;}
      [*] = ;
      [*] = ;         var ix : Integer = ClampInt(x, 0, mapwidth-1);
      [*] = ;         var iy : Integer = ClampInt(y, 0, mapheight-1);
      [*] = ;         //if (bWater) or (bWaterShore) then
      [*] = ;         {if (gMapMask[ix,iy].b>0) then
      [*] = ;         begin
      [*] = ;         end
      [*] = ;         else}
      [*] = ;         var bWater, bWaterShore : Boolean;
      [*] = ;         if (gMapMask[ix,iy].b>0) then
      [*] = ;         begin
      [*] = ;            if (height<cWaterHeight) then
      [*] = ;            bWater := True
      [*] = ;            else
      [*] = ;            if (height<cWaterShoreHeight) then
      [*] = ;            bWaterShore := True;
      [*] = ;         end;
      [*] = ;         if (bWater) or (bWaterShore) then
      [*] = ;         begin
      [*] = ;            const cAngle = 45;
      [*] = ;            //const baseangle = cAngle/2;
      [*] = ;            vecangle := vecangle+180;
      [*] = ;            //vecangle := vecangle+180;
      [*] = ;            var bL, bR, bT, bB, bLB, bRB, bLT, bRT : Boolean;
      [*] = ;            if (vecangle>=(0*cAngle-(cAngle/2))) and (vecangle<(1*cAngle-(cAngle/2))) then
      [*] = ;            bR := True
      [*] = ;            else
      [*] = ;            if (vecangle>=(1*cAngle-(cAngle/2))) and (vecangle<(2*cAngle-(cAngle/2))) then
      [*] = ;            bRB := True
      [*] = ;            else
      [*] = ;            if (vecangle>=(2*cAngle-(cAngle/2))) and (vecangle<(3*cAngle-(cAngle/2))) then
      [*] = ;            bB := True
      [*] = ;            else
      [*] = ;            if (vecangle>=(3*cAngle-(cAngle/2))) and (vecangle<(4*cAngle-(cAngle/2))) then
      [*] = ;            bLB := True
      [*] = ;            else
      [*] = ;            if (vecangle>=(4*cAngle-(cAngle/2))) and (vecangle<(5*cAngle-(cAngle/2))) then
      [*] = ;            bL := True
      [*] = ;            else
      [*] = ;            if (vecangle>=(5*cAngle-(cAngle/2))) and (vecangle<(6*cAngle-(cAngle/2))) then
      [*] = ;            bLT := True
      [*] = ;            else
      [*] = ;            if (vecangle>=(6*cAngle-(cAngle/2))) and (vecangle<(7*cAngle-(cAngle/2))) then
      [*] = ;            bT := True
      [*] = ;            else
      [*] = ;            //if (vecangle>=(7*cAngle-(cAngle/2)+cAngle)) then
      [*] = ;            bRT := True;
      [*] = ;
      [*] = ;            var newtile : String;
      [*] = ;            if (bLB) then newtile := 'sandsea5';//'sandsea4';
      [*] = ;            if (bRB) then newtile := 'sandsea6';//'sandsea3';
      [*] = ;            if (bB) then newtile := 'sandsea1';
      [*] = ;            if (bL) then newtile := 'sandsea6';//'sandsea2';
      [*] = ;            if (bR) then newtile := 'sandsea6';//'sandsea2';
      [*] = ;            if (bT) then newtile := 'sandsea1';
      [*] = ;            if (bRT) then newtile := 'sandsea5';//'sandsea4';
      [*] = ;            if (bLT) then newtile := 'sandsea6';//'sandsea3';
      [*] = ;            if (newtile<>'') then
      [*] = ;            begin
      [*] = ;               {if (Abs(height)>2.7) then
      [*] = ;               newtile := 'rock8'
      [*] = ;               else
      [*] = ;               if (Abs(height)>2.4) then
      [*] = ;               newtile := 'rock4'
      [*] = ;               else}
      [*] = ;               //if (Abs(height)>0.1) then
      [*] = ;               //newtile := '';
      [*] = ;
      [*] = ;               if (newtile<>'') then
      [*] = ;               begin
      [*] = ;                  if GetSeasonType=2 then
      [*] = ;                  newtile := newtile+'_winter';
      [*] = ;                  if GetSeasonType=1 then
      [*] = ;                  newtile := newtile+'_autumn';
      [*] = ;                  if GetSeasonType=3 then
      [*] = ;                  newtile := newtile+'_spring';
      [*] = ;                  var newtex : Integer = MapGetTileIndexByTileBlock(newtile);
      [*] = ;                  SetTileIndex(x, y, newtex)
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            {var bL, bR, bT, bB, bLB, bRB, bLT, bRT : Boolean;
      [*] = ;            if (vecangle>=30+7.5) and (vecangle<=60-7.5) then
      [*] = ;            bRB := True
      [*] = ;            else
      [*] = ;            if (vecangle>=120) and (vecangle<=150+20) then
      [*] = ;            bLB := True
      [*] = ;            else
      [*] = ;            if (vecangle>=-45) and (vecangle<=45) then
      [*] = ;            bR := True
      [*] = ;            else
      [*] = ;            if (vecangle>=45) and (vecangle<=135) then
      [*] = ;            bB := True
      [*] = ;            else
      [*] = ;            if (vecangle>=-135) and (vecangle<=-45) then
      [*] = ;            bT := True
      [*] = ;            else
      [*] = ;            bL := True;
      [*] = ;
      [*] = ;            if (vecangle>=37.5) and (vecangle<=52.5) then
      [*] = ;            bRB := True
      [*] = ;            else
      [*] = ;            if (vecangle>=120) and (vecangle<=170) then
      [*] = ;            bLB := True
      [*] = ;            else}
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if (x=GetMapWidth) or (y=GetMapHeight) or (GetMapCollisionTagInRadius(realx, realy, 0, False)>0) then
      [*] = ;         begin
      [*] = ;            var bL, bR, bT, bB, bLB, bRB : Boolean;
      [*] = ;            if (vecangle>=30-7.5) and (vecangle<=60+7.5) then
      [*] = ;            bRB := True
      [*] = ;            else
      [*] = ;            if (vecangle>=120) and (vecangle<=150+20) then
      [*] = ;            bLB := True
      [*] = ;            else
      [*] = ;            if (vecangle>=-45) and (vecangle<=45) then
      [*] = ;            bR := True
      [*] = ;            else
      [*] = ;            if (vecangle>=45) and (vecangle<=135) then
      [*] = ;            bB := True
      [*] = ;            else
      [*] = ;            if (vecangle>=-135) and (vecangle<=-45) then
      [*] = ;            bT := True
      [*] = ;            else
      [*] = ;            bL := True;
      [*] = ;
      [*] = ;            var newtile : String;
      [*] = ;            if (bLB) then newtile := 'rock7';
      [*] = ;            //if (bRB) then newtile := 'rock6';
      [*] = ;            if (bB) then newtile := 'rock1';
      [*] = ;            if (bL) then newtile := 'rock3';
      [*] = ;            //if (bR) then newtile := 'rock2';
      [*] = ;            if (bR) then newtile := 'rock4';
      [*] = ;            {if (bR) then begin
      [*] = ;               if (random>0.35) and (height<2) and (height>0.5) then
      [*] = ;               newtile := 'rock2'
      [*] = ;               else
      [*] = ;               newtile := 'rock4';
      [*] = ;            end;}
      [*] = ;            if (bT) then newtile := 'rock4';
      [*] = ;            if (bRB) then newtile := 'rock4';
      [*] = ;            if (newtile<>'') then
      [*] = ;            begin
      [*] = ;               if (Abs(height)>2.7) {or (height<-2.7)} then
      [*] = ;               newtile := 'rock8'
      [*] = ;               else
      [*] = ;               if (Abs(height)>2.4) {or (height<-2.4)} then
      [*] = ;               newtile := 'rock4'
      [*] = ;               else
      [*] = ;               if (Abs(height)<0.1) then
      [*] = ;               newtile := '';
      [*] = ;
      [*] = ;               if (newtile<>'') then
      [*] = ;               begin
      [*] = ;                  if GetSeasonType=2 then
      [*] = ;                  newtile := newtile+'_winter';
      [*] = ;                  if GetSeasonType=1 then
      [*] = ;                  newtile := newtile+'_autumn';
      [*] = ;                  if GetSeasonType=3 then
      [*] = ;                  newtile := newtile+'_spring';
      [*] = ;                  var newtex : Integer = MapGetTileIndexByTileBlock(newtile);
      [*] = ;                  SetTileIndex(x, y, newtex);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   ApplicationProcessMessages;
      [*] = ;end;
      [*] = ;
      [*] = ;if (cPlaceRoads) then
      [*] = ;begin
      [*] = ;   for y:=0 to GetMapHeight-1 do
      [*] = ;   for x:=0 to GetMapWidth-1 do
      [*] = ;   begin
      [*] = ;      if (gMapMask[x,y].broad) then
      [*] = ;      begin
      [*] = ;         var realx : Integer = floor(lx+x);
      [*] = ;         var realy : Integer = floor(ty+y);
      [*] = ;         var newtile : String;
      [*] = ;         if (RandomExt>0.5) then
      [*] = ;         newtile := 'ground1'
      [*] = ;         else
      [*] = ;         //if (RandomExt>0.4) then
      [*] = ;         //newtile := 'sand7'
      [*] = ;         //else
      [*] = ;         if (RandomExt>0.25) then
      [*] = ;         newtile := 'test2'
      [*] = ;         else
      [*] = ;         newtile := 'test3';
      [*] = ;         if (newtile<>'') then
      [*] = ;         begin
      [*] = ;            if GetSeasonType=2 then
      [*] = ;            newtile := newtile+'_winter';
      [*] = ;            if GetSeasonType=1 then
      [*] = ;            newtile := newtile+'_autumn';
      [*] = ;            if GetSeasonType=3 then
      [*] = ;            newtile := newtile+'_autumn';
      [*] = ;            var newtex : Integer = MapGetTileIndexByTileBlock(newtile);
      [*] = ;            SetTileIndex(x, y, newtex)
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;//var stage : Integer = 6;
      [*] = ;//for istage:=0 to stage do
      [*] = ;begin
      [*] = ;   var istage : Integer;
      [*] = ;   exit;
      [*] = ;   {if (istage=0) then
      [*] = ;   for y:=0 to GetMapHeight do
      [*] = ;   for x:=0 to GetMapWidth do
      [*] = ;   SetTileIndex(x, y, 0);
      [*] = ;
      [*] = ;   if (istage=0) then
      [*] = ;   for y:=0 to GetMapHeight-1 do
      [*] = ;   for x:=0 to GetMapWidth-1 do
      [*] = ;   begin
      [*] = ;      var realx : Integer = floor(lx+x);
      [*] = ;      var realy : Integer = floor(ty+y);
      [*] = ;      MapDrawCollision(realx+0.5, realy+0.5, 0, 2, True); // clear
      [*] = ;   end;}
      [*] = ;
      [*] = ;   {if (istage=1) then
      [*] = ;   for y:=0 to GetMapHeight do
      [*] = ;   for x:=0 to GetMapWidth do
      [*] = ;   begin
      [*] = ;      var ix : Integer = ClampInt(x, 0, mapwidth-1);
      [*] = ;      var iy : Integer = ClampInt(y, 0, mapheight-1);
      [*] = ;      var realx : Integer = floor(lx+x);
      [*] = ;      var realy : Integer = floor(ty+y);
      [*] = ;      const cDiff1 = 0.5;
      [*] = ;      const cDiff2 = 0.55;
      [*] = ;
      [*] = ;      var height : Float = GetHeightData(realx, realy);
      [*] = ;      var bWater, bWaterShore : Boolean;
      [*] = ;      if (gMapMask[ix,iy].b>0) then
      [*] = ;      begin
      [*] = ;         if (height<cWaterHeight) then
      [*] = ;         bWater := True
      [*] = ;         else
      [*] = ;         if (height<cWaterShoreHeight) then
      [*] = ;         bWaterShore := True;
      [*] = ;      end;
      [*] = ;      var lh : Float = GetHeightData(realx-1, realy);
      [*] = ;      var rh : Float = GetHeightData(realx+1, realy);
      [*] = ;      var th : Float = GetHeightData(realx, realy-1);
      [*] = ;      var bh : Float = GetHeightData(realx, realy+1);
      [*] = ;      var rbh : Float = GetHeightData(realx+1, realy+1);
      [*] = ;      if (bWater) then
      [*] = ;      begin
      [*] = ;         MapDrawCollision(realx, realy, gc_collisiontag_water, 1, True);
      [*] = ;         MapDrawCollision(realx-0.5, realy-0.5, gc_collisiontag_water, 1, True);
      [*] = ;         MapDrawCollision(realx-0.5, realy, gc_collisiontag_water, 1, True);
      [*] = ;         MapDrawCollision(realx, realy-0.5, gc_collisiontag_water, 1, True);
      [*] = ;      end;
      [*] = ;      if (Abs(height-lh)>cDiff1) then
      [*] = ;      begin
      [*] = ;         MapDrawCollision(realx, realy, gc_collisiontag_water, 1, True);
      [*] = ;         MapDrawCollision(realx-0.5, realy-0.5, gc_collisiontag_water, 1, True);
      [*] = ;         MapDrawCollision(realx-0.5, realy, gc_collisiontag_water, 1, True);
      [*] = ;         MapDrawCollision(realx, realy-0.5, gc_collisiontag_water, 1, True);
      [*] = ;      end;
      [*] = ;      if (Abs(height-rh)>cDiff1) then
      [*] = ;      begin
      [*] = ;         MapDrawCollision(realx, realy, gc_collisiontag_water, 1, True);
      [*] = ;         MapDrawCollision(realx-0.5, realy-0.5, gc_collisiontag_water, 1, True);
      [*] = ;         MapDrawCollision(realx-0.5, realy, gc_collisiontag_water, 1, True);
      [*] = ;         MapDrawCollision(realx, realy-0.5, gc_collisiontag_water, 1, True);
      [*] = ;      end;
      [*] = ;      if (Abs(height-bh)>cDiff1) then
      [*] = ;      begin
      [*] = ;         MapDrawCollision(realx, realy, gc_collisiontag_water, 1, True);
      [*] = ;         MapDrawCollision(realx-0.5, realy, gc_collisiontag_water, 1, True);
      [*] = ;         MapDrawCollision(realx, realy-0.5, gc_collisiontag_water, 1, True);
      [*] = ;         MapDrawCollision(realx-0.5, realy-0.5, gc_collisiontag_water, 1, True);
      [*] = ;      end;
      [*] = ;      if (Abs(height-th)>cDiff1) then
      [*] = ;      begin
      [*] = ;         MapDrawCollision(realx-0.5, realy-0.5, gc_collisiontag_water, 1, True);
      [*] = ;         MapDrawCollision(realx, realy-0.5, gc_collisiontag_water, 1, True);
      [*] = ;         MapDrawCollision(realx, realy, gc_collisiontag_water, 1, True);
      [*] = ;         MapDrawCollision(realx-0.5, realy, gc_collisiontag_water, 1, True);
      [*] = ;      end;
      [*] = ;      if (Abs(bh-rh)>cDiff2) then
      [*] = ;      begin
      [*] = ;         MapDrawCollision(realx, realy, gc_collisiontag_water, 1, True);
      [*] = ;         MapDrawCollision(realx+0.5, realy+0.5, gc_collisiontag_water, 1, True);
      [*] = ;         MapDrawCollision(realx+0.5, realy, gc_collisiontag_water, 1, True);
      [*] = ;         MapDrawCollision(realx, realy+0.5, gc_collisiontag_water, 1, True);
      [*] = ;      end;
      [*] = ;      if (Abs(height-rbh)>cDiff2) then
      [*] = ;      begin
      [*] = ;         MapDrawCollision(realx, realy, gc_collisiontag_water, 1, True);
      [*] = ;         MapDrawCollision(realx+0.5, realy+0.5, gc_collisiontag_water, 1, True);
      [*] = ;         MapDrawCollision(realx+0.5, realy, gc_collisiontag_water, 1, True);
      [*] = ;         MapDrawCollision(realx, realy+0.5, gc_collisiontag_water, 1, True);
      [*] = ;      end;
      [*] = ;   end;}
      [*] = ;
      [*] = ;   if (istage=1) then
      [*] = ;   begin
      [*] = ;      // forward
      [*] = ;      {for y:=0 to GetMapHeight*2 do
      [*] = ;      for x:=0 to GetMapWidth*2 do
      [*] = ;      begin
      [*] = ;         var realx : Float = lx+x/2+0.25;
      [*] = ;         var realy : Float = ty+y/2+0.25;
      [*] = ;         if (GetMapCollisionTag(realx, realy, False)=0) then
      [*] = ;         begin
      [*] = ;            var count : Integer;
      [*] = ;            if (GetMapCollisionTag(realx-0.5, realy, False)<>0) then
      [*] = ;            count := count+1;
      [*] = ;            if (GetMapCollisionTag(realx+0.5, realy, False)<>0) then
      [*] = ;            count := count+1;
      [*] = ;            if (GetMapCollisionTag(realx, realy-0.5, False)<>0) then
      [*] = ;            count := count+1;
      [*] = ;            if (GetMapCollisionTag(realx, realy+0.5, False)<>0) then
      [*] = ;            count := count+1;
      [*] = ;            if count>=3 then
      [*] = ;            MapDrawCollision(realx, realy, gc_collisiontag_terrain, 0, False);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      // backward
      [*] = ;      for y:=GetMapHeight*2 downto 0 do
      [*] = ;      for x:=GetMapWidth*2 downto 0 do
      [*] = ;      begin
      [*] = ;         var realx : Float = lx+x/2+0.25;
      [*] = ;         var realy : Float = ty+y/2+0.25;
      [*] = ;         if (GetMapCollisionTag(realx, realy, False)=0) then
      [*] = ;         begin
      [*] = ;            var count : Integer;
      [*] = ;            if (GetMapCollisionTag(realx-0.5, realy, False)<>0) then
      [*] = ;            count := count+1;
      [*] = ;            if (GetMapCollisionTag(realx+0.5, realy, False)<>0) then
      [*] = ;            count := count+1;
      [*] = ;            if (GetMapCollisionTag(realx, realy-0.5, False)<>0) then
      [*] = ;            count := count+1;
      [*] = ;            if (GetMapCollisionTag(realx, realy+0.5, False)<>0) then
      [*] = ;            count := count+1;
      [*] = ;            if count>=3 then
      [*] = ;            MapDrawCollision(realx, realy, gc_collisiontag_terrain, 0, False);
      [*] = ;         end;
      [*] = ;      end;}
      [*] = ;   end;
      [*] = ;
      [*] = ;   // Place Forest
      [*] = ;   if (istage=1) then
      [*] = ;   begin
      [*] = ;      {var envPlHnd : Integer = GetPlayerHandleByIndex(gc_playerind_env);
      [*] = ;      LoadPatterns(True, True);
      [*] = ;      for y:=0 to gc_terraindata_mapwidth-1 do
      [*] = ;      for x:=0 to gc_terraindata_mapheight-1 do
      [*] = ;      gPatternMask[x, y] := False;
      [*] = ;
      [*] = ;      for y:=0 to (GetMapHeight-1)*2 do
      [*] = ;      for x:=0 to (GetMapWidth-1)*2 do
      [*] = ;      begin
      [*] = ;         var realx : Float = lx+x/2+0.25;
      [*] = ;         var realy : Float = ty+y/2+0.25;
      [*] = ;         if (GetMapCollisionTag(realx, realy, False)<>0) then
      [*] = ;         gPatternMask[x div 2, y div 2] := True;
      [*] = ;      end;
      [*] = ;
      [*] = ;      for y:=0 to mapheight-1 do
      [*] = ;      for x:=0 to mapwidth-1 do
      [*] = ;      begin
      [*] = ;         if (not gMapMask[x,y].forest=cGForest) then
      [*] = ;         gPatternMask[x, y] := True;
      [*] = ;      end;
      [*] = ;
      [*] = ;      for y:=0 to mapheight-1 do
      [*] = ;      for x:=0 to mapwidth-1 do
      [*] = ;      begin
      [*] = ;         if (not gPatternMask[x, y]) then
      [*] = ;         for i:=0 to 0 do
      [*] = ;         begin
      [*] = ;            var realx : Integer = floor(lx+x);
      [*] = ;            var realy : Integer = floor(ty+y);
      [*] = ;            if (gMapMask[x,y].forest=cGForest) then
      [*] = ;            begin
      [*] = ;               //var ind : Integer = 18+floor(7*RandomExt); // leaf
      [*] = ;               var ind : Integer = 1+floor(17*RandomExt);
      [*] = ;               if (ind=3) or (ind=7) or (ind=8) or (ind=9) then // have spruce
      [*] = ;               continue;
      [*] = ;
      [*] = ;               var pname : String = 'n_small_frt_'+IntToStr(ind);
      [*] = ;               if (_common_CheckStandPattern(pname, envPlHnd, realx, realy, 0, False)) then
      [*] = ;               begin
      [*] = ;                  _common_CheckStandPattern(pname, envPlHnd, realx, realy, 0, True);
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;}
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (istage=2) then
      [*] = ;   begin
      [*] = ;      {ExecuteState('SaveEnvironmentToBitmap');
      [*] = ;      ExecuteState('LoadEnvironmentFromBitmap');}
      [*] = ;   end;
      [*] = ;
      [*] = ;   var il, it, ib, ir, irb, ilb : Integer;
      [*] = ;   var lower, upper1, upper2, middle : Integer;
      [*] = ;   if (istage=3) then
      [*] = ;   for y:=0 to GetMapHeight do
      [*] = ;   for x:=0 to GetMapWidth do
      [*] = ;   begin
      [*] = ;      var realx : Integer = floor(lx+x);
      [*] = ;      var realy : Integer = floor(ty+y);
      [*] = ;
      [*] = ;      var height : Float = GetHeightData(realx, realy);
      [*] = ;      var bWater, bWaterShore : Boolean;
      [*] = ;      if (height<cWaterHeight) then
      [*] = ;      bWater := True
      [*] = ;      else
      [*] = ;      if (height<cWaterShoreHeight) then
      [*] = ;      bWaterShore := True;
      [*] = ;      var lh : Float = GetHeightData(Max(round(lx), realx-1), realy);
      [*] = ;      var rh : Float = GetHeightData(Min(GetMapWidth div 2, realx+1), realy);
      [*] = ;      var th : Float = GetHeightData(realx, Max(round(ty), realy-1));
      [*] = ;      var bh : Float = GetHeightData(realx, Min(GetMapHeight div 2, realy+1));
      [*] = ;      var rbh : Float = GetHeightData(Min(GetMapWidth div 2, realx+1), Min(GetMapHeight div 2, realy+1));
      [*] = ;      var dirX : Float = lh-rh;
      [*] = ;      var dirY : Float = th-bh;
      [*] = ;      var dirN : Float;
      [*] = ;      var len : Float = VectorLength(dirX, dirN, dirY);
      [*] = ;      if (len>0.01) then
      [*] = ;      begin
      [*] = ;         VectorNormalize(dirX, dirN, dirY);
      [*] = ;         var vecangle : Float = VectorAngle(1, 0, 0, dirX, 0, dirY);
      [*] = ;         if (dirY<0) then
      [*] = ;         vecangle := -vecangle;
      [*] = ;
      [*] = ;         var bL, bR, bT, bB, bLB, bRB : Boolean;
      [*] = ;         if (vecangle>=30+7.5) and (vecangle<=60-7.5) then
      [*] = ;         bRB := True
      [*] = ;         else
      [*] = ;         if (vecangle>=120) and (vecangle<=150+20) then
      [*] = ;         bLB := True
      [*] = ;         else
      [*] = ;         if (vecangle>=-45) and (vecangle<=45) then
      [*] = ;         bR := True
      [*] = ;         else
      [*] = ;         if (vecangle>=45) and (vecangle<=135) then
      [*] = ;         bB := True
      [*] = ;         else
      [*] = ;         if (vecangle>=-135) and (vecangle<=-45) then
      [*] = ;         bT := True
      [*] = ;         else
      [*] = ;         bL := True;
      [*] = ;
      [*] = ;         if (bRB) then irb := irb+1;
      [*] = ;         if (bLB) then ilb := ilb+1;
      [*] = ;         if (bL) then il := il+1;
      [*] = ;         if (bR) then ir := ir+1;
      [*] = ;         if (bT) then it := it+1;
      [*] = ;         if (bB) then ib := ib+1;
      [*] = ;
      [*] = ;         if (x=GetMapWidth) or (y=GetMapHeight) or (GetMapCollisionTagInRadius(realx, realy, 0, False)>0) then
      [*] = ;         begin
      [*] = ;            var newtile : String;
      [*] = ;            if (bLB) then newtile := 'rock7';
      [*] = ;            if (bRB) then newtile := 'rock6';
      [*] = ;            if (bB) then newtile := 'rock1';
      [*] = ;            if (bL) then newtile := 'rock3';
      [*] = ;            if (bR) then newtile := 'rock2';
      [*] = ;            if (bT) then newtile := 'rock4';
      [*] = ;            if (bRB) then newtile := 'rock2';
      [*] = ;            if (newtile<>'') then
      [*] = ;            begin
      [*] = ;               if (height>2.7) then
      [*] = ;               newtile := 'rock8'
      [*] = ;               else
      [*] = ;               if (height>2.4) then
      [*] = ;               newtile := 'rock4'
      [*] = ;               else
      [*] = ;               if (height<0.1) then
      [*] = ;               newtile := '';
      [*] = ;
      [*] = ;               if (newtile<>'') then
      [*] = ;               begin
      [*] = ;                  if GetSeasonType=2 then
      [*] = ;                  newtile := newtile+'_winter';
      [*] = ;                  if GetSeasonType=1 then
      [*] = ;                  newtile := newtile+'_autumn';
      [*] = ;                  if GetSeasonType=3 then
      [*] = ;                  newtile := newtile+'_autumn';
      [*] = ;                  var newtex : Integer = MapGetTileIndexByTileBlock(newtile);
      [*] = ;                  SetTileIndex(x, y, newtex)
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if (bWater) or (bWaterShore) then
      [*] = ;         begin
      [*] = ;            {var newtile : String;
      [*] = ;            if (bWaterShore) then
      [*] = ;            begin
      [*] = ;               newtile := 'rock9';
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (RandomExt>0.25) then
      [*] = ;               newtile := 'sand1'
      [*] = ;               else
      [*] = ;               newtile := 'sand2';
      [*] = ;            end;
      [*] = ;            if (newtile<>'') then
      [*] = ;            begin
      [*] = ;               if GetSeasonType=2 then
      [*] = ;               newtile := newtile+'_winter';
      [*] = ;               var newtex : Integer = MapGetTileIndexByTileBlock(newtile);
      [*] = ;               SetTileIndex(x, y, newtex)
      [*] = ;            end;}
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   //Log('il='+IntToStr(il)+' '+'it='+IntToStr(it)+' '+'ib='+IntToStr(ib)+' '+'ir='+IntToStr(ir)+' '+'irb='+IntToStr(irb)+' '+'ilb='+IntToStr(ilb));
      [*] = ;end;
      [*] = ;//Log('lower='+IntToStr(lower)+' '+'upper1='+IntToStr(upper1)+' '+'upper2='+IntToStr(upper2)+' '+'middle='+IntToStr(middle));
   struct.end
section.end

