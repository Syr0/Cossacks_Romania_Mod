section.begin
   Name = LoadEnvironmentFromBitmap
   Code : struct.begin
      [*] = ;const cForestTypePineFirSpruce = 0;
      [*] = ;const cForestTypeMixed = 1;
      [*] = ;const cForestTypeLeaf = 2;
      [*] = ;var forestType : Integer = IntRegister0;
      [*] = ;
      [*] = ;var bitmap : Integer = IntRegister2;
      [*] = ;//var bitmap : Integer = CreateBitmap;
      [*] = ;//LoadBitmap(bitmap, '.\data\gen\bitmap\ext\tmp_env.bmp');
      [*] = ;
      [*] = ;var width, height : Integer;
      [*] = ;GetBitmapSize(bitmap, width, height);
      [*] = ;
      [*] = ;var x, y : Integer;
      [*] = ;for y:=0 to Min(GetMapHeight, height)-1 do
      [*] = ;for x:=0 to Min(GetMapWidth, width)-1 do
      [*] = ;begin
      [*] = ;   var fr, fg, fb, fa : Float;
      [*] = ;   GetBitmapPixel(bitmap, x, y, fr, fg, fb, fa);
      [*] = ;   var r : Integer = floor(fr*255);
      [*] = ;   var g : Integer = floor(fg*255);
      [*] = ;   var b : Integer = floor(fb*255);
      [*] = ;
      [*] = ;   var tile : String;// = 'grass1';
      [*] = ;   if (forestType=cForestTypePineFirSpruce) then
      [*] = ;   begin
      [*] = ;      case g of
      [*] = ;         0 : begin
      [*] = ;         end;
      [*] = ;         1..4 : begin
      [*] = ;            tile := 'grass1';
      [*] = ;         end;
      [*] = ;         5..7 : begin
      [*] = ;            tile := 'grass6';
      [*] = ;            tile := 'rock9'
      [*] = ;         end;
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if (RandomExt>0.25) then
      [*] = ;            tile := 'grass6'
      [*] = ;            else
      [*] = ;            tile := 'rock9';
      [*] = ;         end
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      case g of
      [*] = ;         0 : begin
      [*] = ;         end;
      [*] = ;         1..2 : begin
      [*] = ;            tile := 'grass1';
      [*] = ;         end;
      [*] = ;         3..3 : begin
      [*] = ;            tile := 'grass6';
      [*] = ;            tile := 'rock9'
      [*] = ;         end;
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if (RandomExt>0.25) then
      [*] = ;            tile := 'grass6'
      [*] = ;            else
      [*] = ;            tile := 'rock9';
      [*] = ;         end
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if (tile<>'') then
      [*] = ;   begin
      [*] = ;      if GetSeasonType=2 then
      [*] = ;      tile := tile+'_winter';
      [*] = ;      if GetSeasonType=1 then
      [*] = ;      tile := tile+'_autumn';
      [*] = ;      if GetSeasonType=3 then
      [*] = ;      tile := tile+'_spring';
      [*] = ;      var tex : Integer = MapGetTileIndexByTileBlock(tile);
      [*] = ;      if (tex>-1) then
      [*] = ;      SetTileIndex(x, y, tex);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;ApplicationProcessMessages;
      [*] = ;
      [*] = ;//FreeBitmap(bitmap);
      [*] = ;//DeleteFileStream('.\data\gen\bitmap\ext\tmp_env.bmp');
   struct.end
section.end

