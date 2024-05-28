section.begin
   Name = SmoothForestBorders
   Code : struct.begin
      [*] = ;const cForestTypePineFirSpruce = 0;
      [*] = ;const cForestTypeMixed = 1;
      [*] = ;const cForestTypeLeaf = 2;
      [*] = ;var forestType : Integer = IntRegister0;
      [*] = ;
      [*] = ;var grid : array [0..gc_scangrid_mapwidth-1] of array [0..gc_scangrid_mapheight-1] of Integer;
      [*] = ;//var pGrid : Pointer = grid;
      [*] = ;//FillMem(pGrid, gc_scangrid_mapwidth * gc_scangrid_mapheight * SizeOf(Integer), 0);
      [*] = ;
      [*] = ;var bitmap : Integer = IntRegister2;
      [*] = ;if bitmap=0 then
      [*] = ;begin
      [*] = ;   ErrorLog('bitmap=0 : exit');
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;// TODO : support non random gen
      [*] = ;//var bitmap : Integer = CreateBitmap;
      [*] = ;//LoadBitmap(bitmap, '.\data\gen\bitmap\ext\tmp_env.bmp');
      [*] = ;
      [*] = ;var width, height : Integer;
      [*] = ;GetBitmapSize(bitmap, width, height);
      [*] = ;
      [*] = ;ApplicationProcessMessages;
      [*] = ;var x, y : Integer;
      [*] = ;for y:=0 to Min(GetMapHeight, height)-1 do
      [*] = ;for x:=0 to Min(GetMapWidth, width)-1 do
      [*] = ;begin
      [*] = ;   var fr, fg, fb, fa : Float;
      [*] = ;   GetBitmapPixel(bitmap, x, y, fr, fg, fb, fa);
      [*] = ;   var r : Integer = floor(fr*255);
      [*] = ;   var g : Integer = floor(fg*255);
      [*] = ;   var b : Integer = floor(fb*255);
      [*] = ;   if ((g=2) or (g=3)) and (r=0) then
      [*] = ;   begin
      [*] = ;      var count : Integer;
      [*] = ;      var tmpfr, tmpfg, tmpfb, tmpfa : Float;
      [*] = ;      GetBitmapPixel(bitmap, x-1, y, tmpfr, tmpfg, tmpfb, tmpfa);
      [*] = ;      if (tmpfr>0) then
      [*] = ;      count := count+1;
      [*] = ;      //var bexists : Boolean = (count>0);
      [*] = ;      //if (not bexists) then
      [*] = ;      begin
      [*] = ;         GetBitmapPixel(bitmap, x+1, y, tmpfr, tmpfg, tmpfb, tmpfa);
      [*] = ;         if (tmpfr>0) then
      [*] = ;         count := count+1;
      [*] = ;         //bexists := True;
      [*] = ;      end;
      [*] = ;      //if (not bexists) then
      [*] = ;      begin
      [*] = ;         GetBitmapPixel(bitmap, x, y-1, tmpfr, tmpfg, tmpfb, tmpfa);
      [*] = ;         if (tmpfr>0) then
      [*] = ;         count := count+1;
      [*] = ;         //bexists := True;
      [*] = ;      end;
      [*] = ;      //if (not bexists) then
      [*] = ;      begin
      [*] = ;         GetBitmapPixel(bitmap, x, y+1, tmpfr, tmpfg, tmpfb, tmpfa);
      [*] = ;         if (tmpfr>0) then
      [*] = ;         count := count+1;
      [*] = ;         //bexists := True;
      [*] = ;      end;
      [*] = ;      if (count=1) then
      [*] = ;      //if (bexists) then
      [*] = ;      begin
      [*] = ;         grid[x, y] := g;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;ApplicationProcessMessages;
      [*] = ;var envPlHnd : Integer = GetPlayerHandleByIndex(gc_playerind_env);
      [*] = ;var lx, ty : Float;
      [*] = ;_misc_GetMapLeftTopPos(lx, ty);
      [*] = ;
      [*] = ;//ClearPlayerGameObjectsByHandle(envplHnd);
      [*] = ;
      [*] = ;var fbcount : Integer;
      [*] = ;var arrfb : array [0..63] of Integer;
      [*] = ;
      [*] = ;//var bitmapOut : Integer = CreateBitmap;
      [*] = ;//SetBitmapSize(bitmapOut, width, height);
      [*] = ;//SetBitmapFormat(bitmapOut, 24);
      [*] = ;for y:=0 to Min(GetMapHeight, height)-1 do
      [*] = ;for x:=0 to Min(GetMapWidth, width)-1 do
      [*] = ;begin
      [*] = ;   var fr, fg : Float;
      [*] = ;   if (grid[x, y]=3) then
      [*] = ;   fr := 255/255
      [*] = ;   else
      [*] = ;   if (grid[x, y]=2) then
      [*] = ;   fg := 255/255;
      [*] = ;   //if (grid[x, y]>0) then
      [*] = ;   //SetBitmapPixel(bitmapOut, x, y, fr, fg, 0, 0)
      [*] = ;   //else
      [*] = ;   //SetBitmapPixel(bitmapOut, x, y, 0, 0, 0, 0);
      [*] = ;
      [*] = ;   if (grid[x, y]=2) or ((grid[x, y]=3) and (RandomExt>0.975)) then
      [*] = ;   begin
      [*] = ;      var realx : Integer = floor(lx+x);
      [*] = ;      var realy : Integer = floor(ty+y);
      [*] = ;      var count : Integer = floor(1+RandomExt*16);
      [*] = ;      var i : Integer;
      [*] = ;      for i:=0 to count-1 do
      [*] = ;      begin
      [*] = ;         const rad = 1.5;
      [*] = ;         var pind : Integer;
      [*] = ;         var pname : String;
      [*] = ;         if (forestType=cForestTypePineFirSpruce) then
      [*] = ;         begin
      [*] = ;            pind := floor(1+RandomExt*53);
      [*] = ;            pname := 'fb_'+IntToStr(pind);
      [*] = ;         end;
      [*] = ;         if (pname<>'') then
      [*] = ;         begin
      [*] = ;            var placeX : Float = Clamp(realx-rad+RandomExt*rad*2, -width div 2, width div 2);
      [*] = ;            var placeZ : Float = Clamp(realy-rad+RandomExt*rad*2, -height div 2, height div 2);
      [*] = ;            //if (_misc_CheckStandPattern(pname, envPlHnd, placeX, placeZ, 0, False)) then
      [*] = ;            begin
      [*] = ;               //Log('forest border placed = '+pname+' x = '+FloatToStr(realx)+' y = '+FloatToStr(realy));
      [*] = ;               _misc_CheckStandPattern(pname, envPlHnd, placeX, placeZ, 0, True, False, 0);
      [*] = ;               fbcount := fbcount+1;
      [*] = ;               arrfb[pind] := arrfb[pind]+1;
      [*] = ;
      [*] = ;               var tilecount : Integer = floor(1+RandomExt*3);
      [*] = ;               var j : Integer;
      [*] = ;               for j:=0 to tilecount-1 do
      [*] = ;               begin
      [*] = ;                  var tile : String;
      [*] = ;                  var rndind : Integer = floor(RandomExt*3);
      [*] = ;                  case rndind of
      [*] = ;                     0 : tile := 'grass5';
      [*] = ;                     1 : tile := 'rock9';
      [*] = ;                     2 : tile := 'rock9';
      [*] = ;                  end;
      [*] = ;                  if GetSeasonType=2 then
      [*] = ;                  tile := tile+'_winter';
      [*] = ;                  if GetSeasonType=1 then
      [*] = ;                  tile := tile+'_autumn';
      [*] = ;                  if GetSeasonType=3 then
      [*] = ;                  tile := tile+'_spring';
      [*] = ;                  var tex : Integer = MapGetTileIndexByTileBlock(tile);
      [*] = ;                  if (tex>-1) then
      [*] = ;                  begin
      [*] = ;                     if (j=0) then
      [*] = ;                     SetTileIndex(_misc_ClampInt(round(placeX-lx), 0, width), _misc_ClampInt(round(placeZ-ty), 0, height), tex)
      [*] = ;                     else
      [*] = ;                     SetTileIndex(_misc_ClampInt(round(placeX-lx)+(-1+floor(RandomExt*3)), 0, width), _misc_ClampInt(round(placeZ-ty)+(-1+floor(RandomExt*3)), 0, height), tex);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               //if (tex>-1) then
      [*] = ;               //SetTileIndex(x, y, tex);
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;ApplicationProcessMessages;
      [*] = ;//SaveBitmap(bitmapOut, '.\data\gen\bitmap\ext\tmp_forest_border.bmp');
      [*] = ;
      [*] = ;//FreeBitmap(bitmap);
      [*] = ;//FreeBitmap(bitmapOut);
      [*] = ;
      [*] = ;{var i : Integer;
      [*] = ;for i:=0 to 63 do
      [*] = ;begin
      [*] = ;   Log('arrfb['+IntToStr(i)+'] = '+IntToStr(arrfb[i]));
      [*] = ;end;
      [*] = ;Log('SmoothForestBorders : fbcount = '+IntToStr(fbcount));}
   struct.end
section.end

