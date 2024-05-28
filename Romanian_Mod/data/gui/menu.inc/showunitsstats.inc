section.begin
   Name = ShowUnitsStats
   Code : struct.begin
      [*] = ;const bupdate = False;
      [*] = ;const currentstatename = 'ShowUnitsStats';
      [*] = ;var elmname, showstate, eventstate : String;
      [*] = ;_misc_GetGUIShowEventStateNames(currentstatename, elmname, showstate, eventstate);
      [*] = ;
      [*] = ;const plInd = gc_MaxPlayerCount-1;
      [*] = ;
      [*] = ;dbgstatename := showstate;
      [*] = ;
      [*] = ;const cmargin = 6;
      [*] = ;const cMinWidth = 300;
      [*] = ;const cMinHeight = 140;
      [*] = ;
      [*] = ;const cTagBackToGame = 101;
      [*] = ;const cTagReplay = 102;
      [*] = ;const cTagSaveReplay = 103;
      [*] = ;const cTagExitToMenu = 104;
      [*] = ;const cTagPrev = 105;
      [*] = ;const cTagNext = 106;
      [*] = ;
      [*] = ;var lastScrollPos : Float;
      [*] = ;var topIndex : Integer;
      [*] = ;var elmScrollLayer : Integer = GetGUIElementIndexByNameParent(elmname+'.produce.list', _gui_GetTop);
      [*] = ;if (elmScrollLayer<>0) then
      [*] = ;begin
      [*] = ;   var elmVScroll : Integer = GetGUIListBoxScrollerHandle(elmScrollLayer);
      [*] = ;   if (elmVScroll<>0) then
      [*] = ;   begin
      [*] = ;      topIndex := GetGUIListBoxTopIndex(elmScrollLayer);
      [*] = ;      lastScrollPos := GetGUIScrollBarPosition(elmVScroll);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// common variables
      [*] = ;var elmHnd : Integer;
      [*] = ;var nul, text : String;
      [*] = ;var w, h : Integer;
      [*] = ;var color : TColor;
      [*] = ;var blackcolor : TColor;
      [*] = ;_gui_SetupTColorInteger(255, 220, 170, 255, 0.9, color);
      [*] = ;_gui_SetupTColorInteger(28, 28, 28, 255, 1, blackcolor);
      [*] = ;var maxwidth : Integer = cMinWidth;
      [*] = ;var maxheight : Integer = cMinHeight;
      [*] = ;
      [*] = ;//initing sarrBuildingsAll. Attention : code dublicate country script start
      [*] = ;var sarrBuildingsAll : array [0..gc_MaxUnitsArr-1] of String;
      [*] = ;var commonName : String;
      [*] = ;var csid : String;
      [*] = ;_country_GetSIDByID(gint_gui_encyclopedia_cid, csid);
      [*] = ;if (csid='rus') or (csid='ukr') then
      [*] = ;commonName := 'rus'
      [*] = ;else
      [*] = ;if (csid='tur') or (csid='alg') then
      [*] = ;commonName := 'tur'
      [*] = ;else
      [*] = ;commonName := 'eur';
      [*] = ;
      [*] = ;var commonNameStorehouse : String;
      [*] = ;var commonNameMarket : String;
      [*] = ;var commonNamePort : String;
      [*] = ;if (csid='pol') then
      [*] = ;commonNameStorehouse := 'russto'
      [*] = ;else
      [*] = ;commonNameStorehouse := commonName+'sto';
      [*] = ;if (csid='spa') or (csid='por') then
      [*] = ;begin
      [*] = ;   commonNameMarket := 'spamar';
      [*] = ;   commonNameStorehouse := 'spasto';
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   commonNameMarket := commonName+'mar';
      [*] = ;   commonNameStorehouse := commonName+'sto';
      [*] = ;end;
      [*] = ;if (csid='por') then
      [*] = ;commonNamePort := 'porpor'
      [*] = ;else
      [*] = ;if (csid='ukr') then
      [*] = ;commonNamePort := 'ukrpor'
      [*] = ;else
      [*] = ;commonNamePort := commonName+'por';
      [*] = ;
      [*] = ;var k : Integer = 0; sarrBuildingsAll[k] := csid+'cen';
      [*] = ;k := k+1; sarrBuildingsAll[k] := csid+'hou';
      [*] = ;k := k+1; sarrBuildingsAll[k] := csid+'bla';
      [*] = ;k := k+1; sarrBuildingsAll[k] := csid+'sta';
      [*] = ;k := k+1; sarrBuildingsAll[k] := csid+'tem';
      [*] = ;k := k+1; sarrBuildingsAll[k] := csid+'aca';
      [*] = ;k := k+1; sarrBuildingsAll[k] := csid+'dip';
      [*] = ;k := k+1; sarrBuildingsAll[k] := csid+'bar';
      [*] = ;k := k+1; sarrBuildingsAll[k] := csid+'ba2';
      [*] = ;k := k+1; sarrBuildingsAll[k] := csid+'art';
      [*] = ;k := k+1; sarrBuildingsAll[k] := commonName+'mil';
      [*] = ;k := k+1; sarrBuildingsAll[k] := commonNameStorehouse;
      [*] = ;k := k+1; sarrBuildingsAll[k] := 'eurgol';
      [*] = ;k := k+1; sarrBuildingsAll[k] := 'euriro';
      [*] = ;k := k+1; sarrBuildingsAll[k] := 'eurcoa';
      [*] = ;k := k+1; sarrBuildingsAll[k] := commonNameMarket;
      [*] = ;k := k+1; sarrBuildingsAll[k] := commonNamePort;
      [*] = ;//initing sarrBuildingsAll. Attention : code dublicate country script finish
      [*] = ;
      [*] = ;function ShowButton(const elmName : String; elmHnd, parentHnd : Integer; btnMaterial : String; var text : String; margin, tag : Integer; bEnabled : Boolean) : Integer;
      [*] = ;begin
      [*] = ;   Result := _gui_CreateButton(elmName, parentHnd, btnMaterial, gc_halParentMiddle, gc_valParentTop, 0, _gui_GetBottomPos(elmHnd)+margin, 0, 0, eventstate, nul, tag, bupdate);
      [*] = ;   SetGUIElementEnabled(Result, bEnabled);
      [*] = ;   _gui_CreateText('txtbtn', Result, text, gc_halParentMiddle, gc_valParentMiddle, 0, 0, 0, 0, gc_halLeft, gc_valMiddle, gc_font_serif_15, color, bupdate);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetUpgradeIndBySIDExt(cid : Integer; sid : String) : Integer;
      [*] = ;begin
      [*] = ;   var i, j : Integer;
      [*] = ;   for i:=0 to gc_country_maxupgradecount-1 do
      [*] = ;   begin
      [*] = ;      if (gCountry[cid].upgrade[i].id=sid) then
      [*] = ;      begin
      [*] = ;         Result := i;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// have some unique upgrades
      [*] = ;function GetUnitMask(sid : String): Word;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var i, j : Integer;
      [*] = ;   for i:=0 to gc_MaxUnitsArr-1 do
      [*] = ;   garr_Temporary[i] := '';
      [*] = ;   for i:=0 to 9 do
      [*] = ;   begin
      [*] = ;      case i of
      [*] = ;         0 : garr_Temporary := garr_UnitsShooters18;
      [*] = ;         1 : garr_Temporary := garr_UnitsShooters;
      [*] = ;         2 : garr_Temporary := garr_UnitsCavalry;
      [*] = ;         3 : garr_Temporary := garr_UnitsCavalryMelee;
      [*] = ;         4 : garr_Temporary := garr_UnitsArmored;
      [*] = ;         5 : garr_Temporary := garr_UnitsBayonet;
      [*] = ;         6 : garr_Temporary := garr_ShipsCannon;
      [*] = ;         7 : garr_Temporary := sarrBuildingsAll;
      [*] = ;         8 : garr_Temporary := garr_BuildingsTowerWall;
      [*] = ;         9 : garr_Temporary := garr_UnitsArtillery;
      [*] = ;      end;
      [*] = ;      for j:=0 to gc_MaxUnitsArr-1 do
      [*] = ;      begin
      [*] = ;         // create a break if we hit empty place
      [*] = ;         if (garr_Temporary[j]='') then
      [*] = ;         break
      [*] = ;         else
      [*] = ;         if (sid=garr_Temporary[j]) then
      [*] = ;         Result := Result or (1 shl i);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   // adding broadsword upgrade
      [*] = ;   if (sid='swordsmansco') then
      [*] = ;   Result := Result or (1 shl 3);
      [*] = ;   // unique units
      [*] = ;   if (sid='fishboat') then
      [*] = ;   Result := Result or (1 shl 10);
      [*] = ;   {if (sid='multicannon') then
      [*] = ;   Result := Result or (1 shl 11);}
      [*] = ;end;
      [*] = ;
      [*] = ;const cMaxUnitUpgrades = 30;
      [*] = ;procedure GetUnitUpgradeIndexes(cid : Integer; sid: String; var resultarr: array[0..cMaxUnitUpgrades-1] of Integer);
      [*] = ;begin
      [*] = ;   var mask : Integer = GetUnitMask(sid);
      [*] = ;   var i: Integer;
      [*] = ;   var csid : String;
      [*] = ;   _country_GetSIDByID(cid, csid);
      [*] = ;   if ((mask and (1 shl 0))<>0) then
      [*] = ;   begin
      [*] = ;      resultarr[0] := GetUpgradeIndBySIDExt(cid, csid+'aca.'+'32'); // flintlock
      [*] = ;   end;
      [*] = ;   if ((mask and (1 shl 1))<>0) then
      [*] = ;   begin
      [*] = ;      resultarr[1] := GetUpgradeIndBySIDExt(cid, csid+'aca.'+'12'); // rifle+gunpowder
      [*] = ;      resultarr[2] := GetUpgradeIndBySIDExt(cid, csid+'aca.'+'13');
      [*] = ;      resultarr[3] := GetUpgradeIndBySIDExt(cid, csid+'aca.'+'14');
      [*] = ;      resultarr[4] := GetUpgradeIndBySIDExt(cid, csid+'aca.'+'15');
      [*] = ;      resultarr[5] := GetUpgradeIndBySIDExt(cid, csid+'aca.'+'31'); //+30% att speed
      [*] = ;      resultarr[6] := GetUpgradeIndBySIDExt(cid, csid+'aca.'+'33'); //+30% att speed
      [*] = ;   end;
      [*] = ;   if ((mask and (1 shl 2))<>0) then
      [*] = ;   begin
      [*] = ;      resultarr[7] := GetUpgradeIndBySIDExt(cid, csid+'bla.'+'3'); // horseshoe
      [*] = ;   end;
      [*] = ;   if ((mask and (1 shl 3))<>0) then
      [*] = ;   begin
      [*] = ;      resultarr[8] := GetUpgradeIndBySIDExt(cid, csid+'bla.'+'5'); // broadsword
      [*] = ;   end;
      [*] = ;   if ((mask and (1 shl 4))<>0) then
      [*] = ;   begin
      [*] = ;      resultarr[9] := GetUpgradeIndBySIDExt(cid, csid+'bla.'+'6'); // cuirass-bla
      [*] = ;      resultarr[10] := GetUpgradeIndBySIDExt(cid, csid+'aca.'+'34'); // cuirass-aca
      [*] = ;   end;
      [*] = ;   if ((mask and (1 shl 5))<>0) then
      [*] = ;   begin
      [*] = ;      resultarr[11] := GetUpgradeIndBySIDExt(cid, csid+'bla.'+'4'); // bayonet-bla
      [*] = ;      resultarr[12] := GetUpgradeIndBySIDExt(cid, csid+'aca.'+'35'); // bayonet-aca+5
      [*] = ;      resultarr[13] := GetUpgradeIndBySIDExt(cid, csid+'aca.'+'36'); // bayonet-aca+25%
      [*] = ;   end;
      [*] = ;   if ((mask and (1 shl 6))<>0) then
      [*] = ;   begin
      [*] = ;      resultarr[14] := GetUpgradeIndBySIDExt(cid, csid+'aca.'+'16'); // +5% range
      [*] = ;      resultarr[15] := GetUpgradeIndBySIDExt(cid, csid+'aca.'+'17'); // +10% range
      [*] = ;      resultarr[16] := GetUpgradeIndBySIDExt(cid, csid+'aca.'+'30'); // x10 faster build time
      [*] = ;   end;
      [*] = ;   if ((mask and (1 shl 7))<>0) then
      [*] = ;   begin
      [*] = ;      resultarr[17] := GetUpgradeIndBySIDExt(cid, csid+'bla.'+'2'); // 50 shield
      [*] = ;      if (sid<>commonNamePort) then
      [*] = ;      resultarr[18] := GetUpgradeIndBySIDExt(cid, csid+'aca.'+'9'); // 85 shield
      [*] = ;      resultarr[19] := GetUpgradeIndBySIDExt(cid, csid+'aca.'+'10'); // -75% build time
      [*] = ;   end;
      [*] = ;   if ((mask and (1 shl 8))<>0) then
      [*] = ;   begin
      [*] = ;      resultarr[20] := GetUpgradeIndBySIDExt(cid, csid+'aca.'+'11'); // 80 shield
      [*] = ;      resultarr[21] := GetUpgradeIndBySIDExt(cid, csid+'aca.'+'16'); // +5% range
      [*] = ;      resultarr[22] := GetUpgradeIndBySIDExt(cid, csid+'aca.'+'17'); // +10% range
      [*] = ;   end;
      [*] = ;   if ((mask and (1 shl 9))<>0) then
      [*] = ;   begin
      [*] = ;      resultarr[23] := GetUpgradeIndBySIDExt(cid, csid+'aca.'+'16'); // +5% range
      [*] = ;      resultarr[24] := GetUpgradeIndBySIDExt(cid, csid+'aca.'+'17'); // +10% range
      [*] = ;      resultarr[25] := GetUpgradeIndBySIDExt(cid, csid+'aca.'+'18'); // doubles hp
      [*] = ;   end;
      [*] = ;   if ((mask and (1 shl 10))<>0) then
      [*] = ;   begin
      [*] = ;      resultarr[26] := GetUpgradeIndBySIDExt(cid, csid+'aca.'+'7'); // -85% price
      [*] = ;      resultarr[27] := GetUpgradeIndBySIDExt(cid, csid+'aca.'+'30'); // x10 faster build time
      [*] = ;   end;
      [*] = ;   {if ((mask and (1 shl 11))<>0) then
      [*] = ;   begin
      [*] = ;      //resultarr[28] := GetUpgradeIndBySIDExt(cid, csid+'aca.'+'18'); // doubles hp
      [*] = ;   end;}
      [*] = ;end;
      [*] = ;
      [*] = ;procedure FillComboBoxCountries(elmHnd, plInd : Integer; bAddRandom, bAddUnplayable, bAddSpectator : Boolean);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   if (GetGUIListBoxItemsCount(elmHnd)=0) then
      [*] = ;   begin
      [*] = ;      var csid : String;
      [*] = ;      if (bAddRandom) then
      [*] = ;      GUIListBoxAddItem(elmHnd, GetLocaleTableListItemByID('gui', 'text.random'), gc_MaxCountryCount);
      [*] = ;      for i:=0 to gc_MaxCountryCount-1 do
      [*] = ;      begin
      [*] = ;         var bVisibleInEditor, bVisibleInMultiplayer, bPlayable : Boolean;
      [*] = ;         _country_IsCountryAvailable(0, i, gProfile.lastknowndlcs, bVisibleInEditor, bVisibleInMultiplayer, bPlayable);
      [*] = ;         if (bPlayable) or (bVisibleInMultiplayer and bAddUnplayable) then
      [*] = ;         begin
      [*] = ;            _country_GetSIDByID(i, csid);
      [*] = ;            GUIListBoxAddItem(elmHnd, GetLocaleTableListItemByID(gc_loc_units, csid), i);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if (bAddSpectator) then
      [*] = ;      begin
      [*] = ;         var text : String;
      [*] = ;         _misc_GetNewTextLocale('text.spectator', text);
      [*] = ;         GUIListBoxAddItem(elmHnd, text, gc_spectator_countryid);
      [*] = ;      end;
      [*] = ;      var sid : String;
      [*] = ;      _country_GetSIDByID(gint_gui_encyclopedia_cid, sid);
      [*] = ;      sid := GetLocaleTableListItemByID(gc_loc_units, sid);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmHnd, GetGUIListBoxItemIndexOfValue(elmHnd, sid));
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure GetUpgradeIndBySID(var ind : Integer; cid : Integer; sid : String);
      [*] = ;begin
      [*] = ;   var i, j : Integer;
      [*] = ;   for i:=0 to gc_country_maxupgradecount-1 do
      [*] = ;   begin
      [*] = ;      if (gCountry[cid].upgrade[i].id=sid) then
      [*] = ;      begin
      [*] = ;         ind := i;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _unit_GetUnitProducePlace(cid : Integer; insid : String; var prodplace : String);
      [*] = ;begin
      [*] = ;   prodplace := '';
      [*] = ;   var sid : String = insid;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to gc_country_maxfixedproduce-1 do
      [*] = ;   begin
      [*] = ;      var prdind : Integer = _country_GetFixedProduceBuildIndexBySID(cid, i, sid);
      [*] = ;      if (prdind<>-1) then
      [*] = ;      begin
      [*] = ;         prodplace := gCountry[cid].fixedproduce[i].id;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var cTextEncyclopedia : String; _misc_GetNewTextLocale('menu.encyclopedia', cTextEncyclopedia);
      [*] = ;var cTextInfo : String; _misc_GetNewTextLocale('encyclopedia.info', cTextInfo);
      [*] = ;var cTextBasic : String; _misc_GetNewTextLocale('encyclopedia.basic', cTextBasic);
      [*] = ;var cTextUpgraded : String; _misc_GetNewTextLocale('encyclopedia.upgraded', cTextUpgraded);
      [*] = ;var cTextAdditional : String; _misc_GetNewTextLocale('encyclopedia.additional', cTextAdditional);
      [*] = ;var cTextPopulAndUpgrades : String = GetLocaleTableListItemByID('misc', 'endgamestatistics.population');
      [*] = ;var cTextScoreDynamics : String = GetLocaleTableListItemByID('misc', 'endgamestatistics.scores');
      [*] = ;var cTextPlayers : String = GetLocaleTableListItemByID('misc', 'endgamestatistics.players');
      [*] = ;var cTextPlayer : String = GetLocaleTableListItemByID('misc', 'endgamestatistics.player');
      [*] = ;var cTextBackToGame : String = GetLocaleTableListItemByID('misc', 'endgamestatistics.backtogame');
      [*] = ;var cTextRestart : String = GetLocaleTableListItemByID('misc', 'endgamestatistics.restart');
      [*] = ;var cTextReplay : String = GetLocaleTableListItemByID('misc', 'endgamestatistics.replay');
      [*] = ;var cTextSaveReplay : String = GetLocaleTableListItemByID('misc', 'endgamestatistics.savereplay');
      [*] = ;var cTextExitToMenu : String = GetLocaleTableListItemByID('misc', 'endgamestatistics.exittomenu');
      [*] = ;var cTextExit : String = GetLocaleTableListItemByID('misc', 'endgamestatistics.exit');
      [*] = ;
      [*] = ;// parent
      [*] = ;const cWidth = 1018+220; // +220 // 1018
      [*] = ;const cHeight = 750; // 624
      [*] = ;
      [*] = ;var elmParent : Integer = _gui_CreateParent(elmname, 0, gc_halMiddle, gc_valMiddle, 0, 0, cWidth, cHeight, bupdate);
      [*] = ;_gui_AbsScaleByDPI(elmParent);
      [*] = ;var elmMask : Integer = _gui_CreateImageActive('blackmask', elmParent, gc_gui_material_black, gc_halLeft, gc_valTop, 0, 0, GetViewerWidth, GetViewerHeight, 0, '', '', bupdate);
      [*] = ;var elmBackgroundParent : Integer = _gui_CreateImageActive('backgroundparent', elmParent, gc_gui_material_blank, gc_halMiddle, gc_valMiddle, 0, 0, cWidth, cHeight, 0, '', '', bupdate);
      [*] = ;SetGUIElementPressState(elmParent, eventstate);
      [*] = ;SetGUIElementUserBlend(elmMask, 0.65);
      [*] = ;// body
      [*] = ;var elmSkinHead, elmChart : Integer;
      [*] = ;var i, j, plcount : Integer;
      [*] = ;for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;begin
      [*] = ;   if (gPlayer[i].bexists) or ((gMap.players[i].cid<>gc_spectator_countryid) and (gPlayer[i].victorystate<>gc_player_victorystate_none)) then
      [*] = ;   plcount := plcount+1;
      [*] = ;end;
      [*] = ;// units table
      [*] = ;var elmTableSkinHead : Integer = _gui_CreateImage('_img_skinhead', elmParent, 'skinhead.large', gc_halParentLeft, gc_valParentTop, 45, 95, cWidth-92, 0, 0, True);
      [*] = ;
      [*] = ;var cTextCategoryUnits : String = GetLocaleTableListItemByID('misc', 'endgamestatistics.listunits');
      [*] = ;var cTextCategoryShips : String = GetLocaleTableListItemByID('misc', 'endgamestatistics.listships');
      [*] = ;var cTextCategoryArtillery : String = GetLocaleTableListItemByID('misc', 'endgamestatistics.listartillery');
      [*] = ;var cTextCategoryBuildings : String = GetLocaleTableListItemByID('misc', 'endgamestatistics.listbuildings');
      [*] = ;var cTextProducedList : String = GetLocaleTableListItemByID('misc', 'endgamestatistics.listunitscreated');
      [*] = ;var cTextKilledList : String = GetLocaleTableListItemByID('misc', 'endgamestatistics.listunitslost');
      [*] = ;
      [*] = ;if (gint_gui_encyclopediapage>=1) then
      [*] = ;begin
      [*] = ;   // created
      [*] = ;   const cBaseWidth = 432+680+3+40;
      [*] = ;   var tw : Integer = _gui_GetFontTextWidth(cTextProducedList, gc_font_serif_12);
      [*] = ;   var elmProduce : Integer = _gui_CreateParent('produce', elmParent, gc_halParentLeft, gc_valParentTop, 56, 100, cBaseWidth, {23*25}550, False);
      [*] = ;
      [*] = ;   var offsetY : Integer = 34-16-32-10;
      [*] = ;   {if (gint_gui_encyclopediapage<>3) then
      [*] = ;   offsetY := 34-16-32-10
      [*] = ;   else
      [*] = ;   offsetY := 34-16-32;}
      [*] = ;
      [*] = ;   // top text
      [*] = ;   var elmTabList : Integer = _gui_CreateListBox('tab', elmProduce, gc_halParentLeft, gc_valParentTop, -16, offsetY, cBaseWidth+8, {23*26}550, gc_halLeft, gc_valMiddle, 0, 0, gc_font_serif_12, eventstate, True, bupdate);
      [*] = ;   SetGUIListBoxMouseTrack(elmTabList, 1); // 1 - only text change color on hover, 2 - only material appears, 3 - text and material on hover
      [*] = ;   SetGUIListBoxSelectedMaterialName(elmTabList, gc_gui_material_blank); // selected
      [*] = ;   GUIListBoxClearSilent(elmTabList);
      [*] = ;
      [*] = ;   // bottom text
      [*] = ;   var elmTabListBottom : Integer = _gui_CreateListBox('tab_bottom', elmProduce, gc_halParentLeft, gc_valParentTop, -16, 34-16-20, cBaseWidth+8, {23*26}550, gc_halLeft, gc_valMiddle, 0, 0, gc_font_serif_11, eventstate, True, bupdate);
      [*] = ;   SetGUIListBoxMouseTrack(elmTabListBottom, 1); // 1 - only text change color on hover, 2 - only material appears, 3 - text and material on hover
      [*] = ;   SetGUIListBoxSelectedMaterialName(elmTabListBottom, gc_gui_material_blank); // selected
      [*] = ;   GUIListBoxClearSilent(elmTabListBottom);
      [*] = ;
      [*] = ;   var elmList : Integer = _gui_CreateListBox('list', elmProduce, gc_halParentLeft, gc_valParentTop, -16, 34-16+26*2-16, cBaseWidth+8+10, 550, gc_halLeft, gc_valMiddle, 0, 0, gc_font_serif_12, eventstate, True, bupdate);
      [*] = ;   SetGUIListBoxMouseTrack(elmList, 1); // 1 - only text change color on hover, 2 - only material appears, 3 - text and material on hover
      [*] = ;   SetGUIListBoxSelectedMaterialName(elmList, gc_gui_material_blank); // selected
      [*] = ;   GUIListBoxClearSilent(elmList);
      [*] = ;
      [*] = ;   var stext, stextbottom : String;
      [*] = ;   const fontsize = gc_font_serif_11;
      [*] = ;   //var cTextTab1 : String; _misc_GetNewTextLocale('encyclopedia.nation', cTextTab1);
      [*] = ;   var cTextTab2 : String; _misc_GetNewTextLocale('encyclopedia.unit', cTextTab2);
      [*] = ;
      [*] = ;   // page 1,2
      [*] = ;   var cTextTab3 : String; _misc_GetNewTextLocale('encyclopedia.hp', cTextTab3);
      [*] = ;   var cTextTab4 : String; _misc_GetNewTextLocale('encyclopedia.time', cTextTab4);
      [*] = ;   var cTextTab5 : String; _misc_GetNewTextLocale('encyclopedia.protection', cTextTab5);
      [*] = ;   var cTextTab6 : String; _misc_GetNewTextLocale('encyclopedia.vision', cTextTab6);
      [*] = ;   var cTextTab7 : String; _misc_GetNewTextLocale('encyclopedia.aggrorange', cTextTab7);
      [*] = ;   var cTextTab8 : String; _misc_GetNewTextLocale('encyclopedia.melee', cTextTab8);
      [*] = ;   var cTextTab9 : String; _misc_GetNewTextLocale('encyclopedia.ranged', cTextTab9);
      [*] = ;   var cTextTab10 : String; _misc_GetNewTextLocale('encyclopedia.reload', cTextTab10);
      [*] = ;   var cTextTab11 : String; _misc_GetNewTextLocale('encyclopedia.maxrange', cTextTab11);
      [*] = ;   var cTextTab12 : String; _misc_GetNewTextLocale('encyclopedia.minrange', cTextTab12);
      [*] = ;   var cTextTab13 : String; _misc_GetNewTextLocale('encyclopedia.cost', cTextTab13);
      [*] = ;
      [*] = ;   var cTextSword : String; _misc_GetNewTextLocale('encyclopedia.s', cTextSword);
      [*] = ;   var cTextPike : String; _misc_GetNewTextLocale('encyclopedia.p', cTextPike);
      [*] = ;   var cTextBullet : String; _misc_GetNewTextLocale('encyclopedia.b', cTextBullet);
      [*] = ;   var cTextArrow : String; _misc_GetNewTextLocale('encyclopedia.a', cTextArrow);
      [*] = ;   var cTextCannon : String; _misc_GetNewTextLocale('encyclopedia.c', cTextCannon);
      [*] = ;   var cTextGrapeshot : String; _misc_GetNewTextLocale('encyclopedia.g', cTextGrapeshot);
      [*] = ;
      [*] = ;   var cTextFood : String; _misc_GetNewTextLocale('encyclopedia.f', cTextFood);
      [*] = ;   var cTextWood : String; _misc_GetNewTextLocale('encyclopedia.w', cTextWood);
      [*] = ;   var cTextStone : String; _misc_GetNewTextLocale('encyclopedia.st', cTextStone);
      [*] = ;   var cTextGold : String; _misc_GetNewTextLocale('encyclopedia.go', cTextGold);
      [*] = ;   var cTextIron : String; _misc_GetNewTextLocale('encyclopedia.i', cTextIron);
      [*] = ;   var cTextCoal : String; _misc_GetNewTextLocale('encyclopedia.co', cTextCoal);
      [*] = ;   //f w s g i c - cost
      [*] = ;   //s p b a c g - protection
      [*] = ;   //Range - bottom Aggro
      [*] = ;
      [*] = ;   // page 2
      [*] = ;
      [*] = ;   //var cTextTab14 : String; _misc_GetNewTextLocale('encyclopedia.protectionupgrades', cTextTab14);
      [*] = ;   //var cTextTab15 : String; _misc_GetNewTextLocale('encyclopedia.meleeupgrades', cTextTab15);
      [*] = ;   //var cTextTab16 : String; _misc_GetNewTextLocale('encyclopedia.rangedupgrades', cTextTab16);
      [*] = ;   //stext := stext+#9+gUIConst.fontstyle[fontsize]+cTextTab1;
      [*] = ;   stext := stext+#9+gUIConst.fontstyle[fontsize]+cTextTab2;
      [*] = ;   if ((gint_gui_encyclopediapage=1) or (gint_gui_encyclopediapage=2)) then
      [*] = ;   begin
      [*] = ;      stext := stext+#9+gUIConst.fontstyle[fontsize]+cTextTab3;
      [*] = ;      stext := stext+#9+gUIConst.fontstyle[fontsize]+cTextTab4;
      [*] = ;      stext := stext+#9+cTextTab5+#9+#9+#9+#9+#9;
      [*] = ;      stext := stext+#9+gUIConst.fontstyle[fontsize]+cTextTab6;
      [*] = ;      stext := stext+#9+gUIConst.fontstyle[fontsize]+cTextTab7;
      [*] = ;      stext := stext+#9+gUIConst.fontstyle[fontsize]+cTextTab8;
      [*] = ;      stext := stext+#9+gUIConst.fontstyle[fontsize]+cTextTab9;
      [*] = ;      stext := stext+#9+gUIConst.fontstyle[fontsize]+cTextTab10;
      [*] = ;      stext := stext+#9+gUIConst.fontstyle[fontsize]+cTextTab11;
      [*] = ;      stext := stext+#9+gUIConst.fontstyle[fontsize]+cTextTab12;
      [*] = ;      stext := stext+#9+gUIConst.fontstyle[fontsize]+cTextTab13;
      [*] = ;      stextbottom := stextbottom+#9+#9+#9+#9+' '+cTextSword+' ';
      [*] = ;      if(StrLength(cTextPike)=1) then
      [*] = ;      stextbottom := stextbottom+#9+' '+cTextPike+' '
      [*] = ;      else
      [*] = ;      stextbottom := stextbottom+#9+cTextPike+' ';
      [*] = ;      
      [*] = ;      if(StrLength(cTextBullet)=1) then
      [*] = ;      stextbottom := stextbottom+#9+' '+cTextBullet+' '
      [*] = ;      else
      [*] = ;      stextbottom := stextbottom+#9+cTextBullet+' ';
      [*] = ;      
      [*] = ;      stextbottom := stextbottom+#9+' '+cTextArrow+' ';
      [*] = ;      stextbottom := stextbottom+#9+' '+cTextCannon+' ';
      [*] = ;      stextbottom := stextbottom+#9+' '+cTextGrapeshot+' ';
      [*] = ;
      [*] = ;      var i : Integer;
      [*] = ;      for i:=0 to 6 do
      [*] = ;      stextbottom := stextbottom+#9;
      [*] = ;      stextbottom := stextbottom+#9+'  '+cTextFood+' ';
      [*] = ;      stextbottom := stextbottom+#9+'  '+cTextWood+' ';
      [*] = ;      stextbottom := stextbottom+#9+'  '+cTextStone+' ';
      [*] = ;      
      [*] = ;      //stextbottom := stextbottom+#9+'  '+cTextGold+' ';
      [*] = ;      
      [*] = ;      if(StrLength(cTextGold)=1) then
      [*] = ;      stextbottom := stextbottom+#9+'  '+cTextGold+' '
      [*] = ;      else
      [*] = ;      stextbottom := stextbottom+#9+' '+cTextGold+' ';
      [*] = ;      
      [*] = ;      if(StrLength(cTextIron)=1) then
      [*] = ;      stextbottom := stextbottom+#9+'  '+cTextIron+' '
      [*] = ;      else
      [*] = ;      stextbottom := stextbottom+#9+' '+cTextIron+' ';
      [*] = ;      
      [*] = ;      stextbottom := stextbottom+#9+'  '+cTextCoal+' ';
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (gint_gui_encyclopediapage=3) then
      [*] = ;   begin
      [*] = ;      stext := stext+#9+gUIConst.fontstyle[fontsize]+cTextTab5;
      [*] = ;      stext := stext+#9+#9+#9+#9+#9+#9+gUIConst.fontstyle[fontsize]+cTextTab8;
      [*] = ;      stext := stext+#9+#9+#9+#9+#9+#9+gUIConst.fontstyle[fontsize]+cTextTab9;
      [*] = ;
      [*] = ;      stextbottom := stextbottom+#9+#9+#9+#9+#9+#9+#9+#9+#9;
      [*] = ;      var i : Integer;
      [*] = ;      for i:=0 to 5 do
      [*] = ;      stextbottom := stextbottom+IntToStr(i+1)+#9;
      [*] = ;      for i:=0 to 5 do
      [*] = ;      stextbottom := stextbottom+IntToStr(i+1)+#9;
      [*] = ;      for i:=0 to 5 do
      [*] = ;      stextbottom := stextbottom+IntToStr(i+1)+#9;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var ind : Integer;
      [*] = ;   GUIListBoxAddItem(elmTabList, ' ', ind);
      [*] = ;   GUIListBoxAddItem(elmTabList, stext, 0);
      [*] = ;
      [*] = ;   GUIListBoxAddItem(elmTabListBottom, ' ', ind);
      [*] = ;   GUIListBoxAddItem(elmTabListBottom, stextbottom, 0);
      [*] = ;
      [*] = ;   const cPadding = 11;
      [*] = ;   const cMinTabWidth = 46;
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 12, 'tsText');
      [*] = ;
      [*] = ;   // page 1,2,3
      [*] = ;   //AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, Max(cMinTabWidth+54, _gui_GetFontTextWidth(cTextTab1, fontsize)+cPadding), 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, Max(cMinTabWidth+192, _gui_GetFontTextWidth(cTextTab2, fontsize)+cPadding), 'tsText');
      [*] = ;
      [*] = ;   //page 1,2
      [*] = ;   if ((gint_gui_encyclopediapage=1) or (gint_gui_encyclopediapage=2)) then
      [*] = ;   begin
      [*] = ;      AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, Max(cMinTabWidth, _gui_GetFontTextWidth(cTextTab3, fontsize)+cPadding), 'tsText');
      [*] = ;      AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, Max(cMinTabWidth, _gui_GetFontTextWidth(cTextTab4, fontsize)+cPadding), 'tsText');
      [*] = ;      //AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, Max(cMinTabWidth+110, _gui_GetFontTextWidth(cTextTab5, fontsize)+cPadding), 'tsText');
      [*] = ;      //exp1 start
      [*] = ;      AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;      AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;      AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;      AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;      AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;      AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   //exp end
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, Max(cMinTabWidth, _gui_GetFontTextWidth(cTextTab6, fontsize)+cPadding), 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, Max(cMinTabWidth, _gui_GetFontTextWidth(cTextTab7, fontsize)+cPadding), 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, Max(cMinTabWidth, _gui_GetFontTextWidth(cTextTab8, fontsize)+cPadding), 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, Max(cMinTabWidth, _gui_GetFontTextWidth(cTextTab9, fontsize)+cPadding), 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, Max(cMinTabWidth, _gui_GetFontTextWidth(cTextTab10, fontsize)+cPadding), 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, Max(cMinTabWidth, _gui_GetFontTextWidth(cTextTab11, fontsize)+cPadding), 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, Max(cMinTabWidth, _gui_GetFontTextWidth(cTextTab12, fontsize)+cPadding), 'tsText');
      [*] = ;   //AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, Max(cMinTabWidth+210, _gui_GetFontTextWidth(cTextTab13, fontsize)+3*cPadding), 'tsText');
      [*] = ;   //exp2 start
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 35, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 35, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 35, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 35, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 35, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 35, 'tsText');
      [*] = ;//exp end
      [*] = ;
      [*] = ;// bottom
      [*] = ;//AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, Max(cMinTabWidth, _gui_GetFontTextWidth(cTextTab3, fontsize)+cPadding), 'tsText');
      [*] = ;//AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, Max(cMinTabWidth, _gui_GetFontTextWidth(cTextTab4, fontsize)+cPadding), 'tsText');
      [*] = ;//AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, Max(cMinTabWidth+110, _gui_GetFontTextWidth(cTextTab5, fontsize)+cPadding), 'tsText');
      [*] = ;//exp1 start
      [*] = ;AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 12, 'tsText');
      [*] = ;AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, Max(cMinTabWidth+192, _gui_GetFontTextWidth(cTextTab2, fontsize)+cPadding), 'tsText');
      [*] = ;AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, Max(cMinTabWidth, _gui_GetFontTextWidth(cTextTab3, fontsize)+cPadding), 'tsText');
      [*] = ;AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, Max(cMinTabWidth, _gui_GetFontTextWidth(cTextTab4, fontsize)+cPadding), 'tsText');
      [*] = ;
      [*] = ;AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;//exp end
      [*] = ;AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, Max(cMinTabWidth, _gui_GetFontTextWidth(cTextTab6, fontsize)+cPadding), 'tsText');
      [*] = ;AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, Max(cMinTabWidth, _gui_GetFontTextWidth(cTextTab7, fontsize)+cPadding), 'tsText');
      [*] = ;AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, Max(cMinTabWidth, _gui_GetFontTextWidth(cTextTab8, fontsize)+cPadding), 'tsText');
      [*] = ;AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, Max(cMinTabWidth, _gui_GetFontTextWidth(cTextTab9, fontsize)+cPadding), 'tsText');
      [*] = ;AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, Max(cMinTabWidth, _gui_GetFontTextWidth(cTextTab10, fontsize)+cPadding), 'tsText');
      [*] = ;AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, Max(cMinTabWidth, _gui_GetFontTextWidth(cTextTab11, fontsize)+cPadding), 'tsText');
      [*] = ;AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, Max(cMinTabWidth, _gui_GetFontTextWidth(cTextTab12, fontsize)+cPadding), 'tsText');
      [*] = ;//AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, Max(cMinTabWidth+210, _gui_GetFontTextWidth(cTextTab13, fontsize)+3*cPadding), 'tsText');
      [*] = ;//exp2 start
      [*] = ;AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 35, 'tsText');
      [*] = ;AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 35, 'tsText');
      [*] = ;AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 35, 'tsText');
      [*] = ;AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 35, 'tsText');
      [*] = ;AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 35, 'tsText');
      [*] = ;AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 35, 'tsText');
      [*] = ;end;
      [*] = ;
      [*] = ;//page 3
      [*] = ;if (gint_gui_encyclopediapage=3) then
      [*] = ;begin
      [*] = ;   //tablist start
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabList, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   //tablist finish
      [*] = ;
      [*] = ;   //tablistbottom start
      [*] = ;   AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 12, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;
      [*] = ;   AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;
      [*] = ;   AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   AddGUIListBoxTabProperty(elmTabListBottom, 1, 1, 1, 1, 30, 'tsText');
      [*] = ;   //tablistbottom finish
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ShowUnitInList(elmList, plInd, cid, id, count, category : Integer; var categorytext : String; var ind : Integer);
      [*] = ;begin
      [*] = ;   var bok : Boolean;
      [*] = ;   case category of
      [*] = ;      0 : if (not gObjProp[cid, id].bbuilding) and (gObjProp[cid, id].media<>gc_obj_media_water) and (not gObjProp[cid, id].bartillery) then bok := True;
      [*] = ;      1 : if (gObjProp[cid, id].media=gc_obj_media_water) then bok := True;
      [*] = ;      2 : if (gObjProp[cid, id].bartillery) then bok := True;
      [*] = ;      3 : if (gObjProp[cid, id].bbuilding) then bok := True;
      [*] = ;   end;
      [*] = ;   if bok then
      [*] = ;   begin
      [*] = ;      if (categorytext<>'') then
      [*] = ;      begin
      [*] = ;         GUIListBoxAddItem(elmList, #9+' '+gc_font_color_white+categorytext+#9, -category);
      [*] = ;         categorytext := '';
      [*] = ;      end;
      [*] = ;      var csid : String;
      [*] = ;      _country_GetSIDByID(cid, csid);
      [*] = ;      var ttext : String = gc_loc_units+'|'+csid;
      [*] = ;      var textCountry : String;
      [*] = ;      _misc_StringToText(ttext, textCountry);
      [*] = ;      var sid : String;
      [*] = ;      _unit_ConvertObjIDToSID(cid, id, sid);
      [*] = ;      var sname, scount : String;
      [*] = ;      _misc_GetUnitNameBySID(sid, sname);
      [*] = ;      scount := IntToStr(count);
      [*] = ;
      [*] = ;      //protection
      [*] = ;      sname := GetGUIWrappedTextFormatByFont(gUIConst.font[gc_font_serif_11], sname, Max(cMinTabWidth+192, _gui_GetFontTextWidth(cTextTab2, fontsize)+cPadding));
      [*] = ;      var str : String = {#9+'%color(786040)%'+textCountry+}#9+sname;
      [*] = ;      if (gint_gui_encyclopediapage=1) then
      [*] = ;      begin
      [*] = ;         var hp : Integer = gPlayer[plInd].objbase[cid][id].maxhp;
      [*] = ;         str := str+#9+IntToStr(hp);
      [*] = ;         var stime : String;
      [*] = ;         if (gObjProp[cid][id].bBuilding) then
      [*] = ;         stime := IntToStr(round(1.06*gc_buildtime_progressperhit*gPlayer[plInd].objbase[cid][id].buildtime/gc_frames_to_time/gc_buildtime_modifier))
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            stime := FloatToStr(gPlayer[plInd].objbase[cid][id].buildtime);
      [*] = ;            var pos : Integer = StrPos('.', stime);
      [*] = ;            if (pos>0) then
      [*] = ;            begin
      [*] = ;               stime := SubStr(stime, 1, pos+2);
      [*] = ;               if (SubStr(stime, StrLength(stime), 1)='0') then
      [*] = ;               stime := SubStr(stime, 0, StrLength(stime)-1);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         str := str+#9+stime;
      [*] = ;         str := str+#9;
      [*] = ;         if (gPlayer[plInd].objbase[cid, id].protection[1]>0) then str := str+FloatToStr(gPlayer[plInd].objbase[cid, id].protection[1])+#9 else str:=str+#9;
      [*] = ;         if (gPlayer[plInd].objbase[cid, id].protection[2]>0) then str := str+FloatToStr(gPlayer[plInd].objbase[cid, id].protection[2])+#9 else str:=str+#9;
      [*] = ;         if (gPlayer[plInd].objbase[cid, id].protection[3]>0) then str := str+FloatToStr(gPlayer[plInd].objbase[cid, id].protection[3])+#9 else str:=str+#9;
      [*] = ;         if (gPlayer[plInd].objbase[cid, id].protection[5]>0) then str := str+FloatToStr(gPlayer[plInd].objbase[cid, id].protection[5])+#9 else str:=str+#9;
      [*] = ;         if (gPlayer[plInd].objbase[cid, id].protection[7]>0) then str := str+FloatToStr(gPlayer[plInd].objbase[cid, id].protection[7])+#9 else str:=str+#9;
      [*] = ;         if (gPlayer[plInd].objbase[cid, id].protection[4]>0) then str := str+FloatToStr(gPlayer[plInd].objbase[cid, id].protection[4]);
      [*] = ;         if (gObjProp[cid, id].vision>0) then
      [*] = ;         str := str+#9+IntToStr(gObjProp[cid, id].vision*1000)
      [*] = ;         else
      [*] = ;         str := str+#9+' ';
      [*] = ;
      [*] = ;         if (gObjProp[cid, id].searchradius>0) then
      [*] = ;         str := str+#9+FloatToStr(gObjProp[cid, id].searchradius*gc_pixels_to_tile)
      [*] = ;         else
      [*] = ;         str := str+#9+' ';
      [*] = ;
      [*] = ;         var pobjprop : Pointer = gObjProp[cid, id];
      [*] = ;         var pobjbase : Pointer = gPlayer[plInd].objbase[cid, id];
      [*] = ;
      [*] = ;         str := str+#9;
      [*] = ;         var weapInd : Integer;
      [*] = ;         for i:=0 to gc_obj_MaxWeapon-1 do
      [*] = ;         begin
      [*] = ;            if (weapInd<2) and (TObjProp(pobjprop).weapon[i].enabled) and (TObjBase(pobjbase).weapon[i].damage<>0) then
      [*] = ;            begin
      [*] = ;               if (TObjProp(pobjprop).weapon[i].kind=gc_obj_weapon_kind_pike)
      [*] = ;               or (TObjProp(pobjprop).weapon[i].kind=gc_obj_weapon_kind_sword) then
      [*] = ;               begin
      [*] = ;                  weapInd := weapInd+1;
      [*] = ;                  str := str+IntToStr(TObjBase(pobjbase).weapon[i].damage);
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         str := str+#9;
      [*] = ;         weapInd := 0;
      [*] = ;         for i:=0 to gc_obj_MaxWeapon-1 do
      [*] = ;         begin
      [*] = ;            if (weapInd<2) and (TObjProp(pobjprop).weapon[i].enabled) and (TObjBase(pobjbase).weapon[i].damage<>0) then
      [*] = ;            begin
      [*] = ;               if (TObjProp(pobjprop).weapon[i].kind=gc_obj_weapon_kind_bullet)
      [*] = ;               or (TObjProp(pobjprop).weapon[i].kind=gc_obj_weapon_kind_arrow)
      [*] = ;               or (TObjProp(pobjprop).weapon[i].kind=gc_obj_weapon_kind_cannonball)
      [*] = ;               or (TObjProp(pobjprop).weapon[i].kind=gc_obj_weapon_kind_mortarball) then
      [*] = ;               begin
      [*] = ;                  weapInd := weapInd+1;
      [*] = ;                  str := str+IntToStr(TObjBase(pobjbase).weapon[i].damage);
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         str := str+#9;
      [*] = ;         if (TObjBase(pobjbase).weapon[i].pause*32>20) then
      [*] = ;         str := str+FloatToStr(TObjBase(pobjbase).weapon[i].pause*32);
      [*] = ;
      [*] = ;         str:= str+#9;
      [*] = ;
      [*] = ;         var maxrange, reload : Float;
      [*] = ;         var minrange : Float = 10000;
      [*] = ;
      [*] = ;         for i:=0 to gc_obj_MaxWeapon-1 do
      [*] = ;         begin
      [*] = ;            if (TObjBase(pobjbase).weapon[i].radiusmax>maxrange) then
      [*] = ;            maxrange := TObjBase(pobjbase).weapon[i].radiusmax;
      [*] = ;            if ((TObjProp(pobjprop).weapon[i].radiusmin>0) and (TObjProp(pobjbase).weapon[i].radiusmin<minrange)) then
      [*] = ;            minrange := TObjProp(pobjprop).weapon[i].radiusmin;
      [*] = ;         end;
      [*] = ;
      [*] = ;         // adding maxrange
      [*] = ;
      [*] = ;         if (maxrange*gc_pixels_to_tile>0) then
      [*] = ;         str := str+FloatToStr(maxrange*gc_pixels_to_tile);
      [*] = ;
      [*] = ;         str:= str+#9;
      [*] = ;
      [*] = ;         // adding minarange
      [*] = ;         if ((minrange>=0) and (minrange<>10000)) then
      [*] = ;         str := str+FloatToStr(minrange*gc_pixels_to_tile);
      [*] = ;
      [*] = ;         str:= str+#9;
      [*] = ;
      [*] = ;         // adding cost
      [*] = ;
      [*] = ;         var food, wood, stone, gold, iron, coal : Integer;
      [*] = ;         _unit_GetCostByID(cid, id, TObj(pobjbase).pl, food, wood, stone, gold, iron, coal);
      [*] = ;
      [*] = ;         if (food>0) then
      [*] = ;         str:= str+IntToStr(food)+#9
      [*] = ;         else
      [*] = ;         str:= str+#9;
      [*] = ;
      [*] = ;         if (wood>0) then
      [*] = ;         str:= str+IntToStr(wood)+#9
      [*] = ;         else
      [*] = ;         str:= str+#9;
      [*] = ;
      [*] = ;         if (stone>0) then
      [*] = ;         str:= str+IntToStr(stone)+#9
      [*] = ;         else
      [*] = ;         str:= str+#9;
      [*] = ;
      [*] = ;         if (gold>0) then
      [*] = ;         str:= str+IntToStr(gold)+#9
      [*] = ;         else
      [*] = ;         str:= str+#9;
      [*] = ;
      [*] = ;         if (iron>0) then
      [*] = ;         str:= str+IntToStr(iron)+#9
      [*] = ;         else
      [*] = ;         str:= str+#9;
      [*] = ;
      [*] = ;         if (coal>0) then
      [*] = ;         str:= str+IntToStr(coal)+#9;
      [*] = ;
      [*] = ;         //first page ends
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (gint_gui_encyclopediapage=2) then
      [*] = ;      begin
      [*] = ;         // logic
      [*] = ;         var hp : Integer = gPlayer[plInd].objbase[cid][id].maxhp;
      [*] = ;         //str := str+#9+IntToStr(hp);
      [*] = ;         var stime : String;
      [*] = ;         var ftime : Float;
      [*] = ;         if (gObjProp[cid][id].bBuilding) then
      [*] = ;         stime := IntToStr(round(1.06*gc_buildtime_progressperhit*gPlayer[plInd].objbase[cid][id].buildtime/gc_frames_to_time/gc_buildtime_modifier))
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            stime := FloatToStr(gPlayer[plInd].objbase[cid][id].buildtime);
      [*] = ;            var pos : Integer = StrPos('.', stime);
      [*] = ;            if (pos>0) then
      [*] = ;            begin
      [*] = ;               stime := SubStr(stime, 1, pos+2);
      [*] = ;               if (SubStr(stime, StrLength(stime), 1)='0') then
      [*] = ;               stime := SubStr(stime, 0, StrLength(stime)-1);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         ftime := StrToFloat(stime);
      [*] = ;
      [*] = ;         var pobjprop : Pointer = gObjProp[cid, id];
      [*] = ;         var pobjbase : Pointer = gPlayer[plInd].objbase[cid, id];
      [*] = ;
      [*] = ;         // getting start-values
      [*] = ;         var meleedmg, rangedmg : Integer;
      [*] = ;         var protections : array [0..gc_obj_weapon_kind_count-1] of Integer;
      [*] = ;         var weapInd : Integer;
      [*] = ;         for i:=0 to gc_obj_MaxWeapon-1 do
      [*] = ;         begin
      [*] = ;            if (weapInd<2) and (TObjProp(pobjprop).weapon[i].enabled) and (TObjBase(pobjbase).weapon[i].damage<>0) then
      [*] = ;            begin
      [*] = ;               if (TObjProp(pobjprop).weapon[i].kind=gc_obj_weapon_kind_pike)
      [*] = ;               or (TObjProp(pobjprop).weapon[i].kind=gc_obj_weapon_kind_sword) then
      [*] = ;               begin
      [*] = ;                  weapInd := weapInd+1;
      [*] = ;                  meleedmg := TObjBase(pobjbase).weapon[i].damage;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         weapInd := 0;
      [*] = ;         for i:=0 to gc_obj_MaxWeapon-1 do
      [*] = ;         begin
      [*] = ;            if (weapInd<2) and (TObjProp(pobjprop).weapon[i].enabled) and (TObjBase(pobjbase).weapon[i].damage<>0) then
      [*] = ;            begin
      [*] = ;               if (TObjProp(pobjprop).weapon[i].kind=gc_obj_weapon_kind_bullet)
      [*] = ;               or (TObjProp(pobjprop).weapon[i].kind=gc_obj_weapon_kind_arrow)
      [*] = ;               or (TObjProp(pobjprop).weapon[i].kind=gc_obj_weapon_kind_cannonball)
      [*] = ;               or (TObjProp(pobjprop).weapon[i].kind=gc_obj_weapon_kind_mortarball) then
      [*] = ;               begin
      [*] = ;                  weapInd := weapInd+1;
      [*] = ;                  rangedmg := TObjBase(pobjbase).weapon[i].damage;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         // melee upgrades
      [*] = ;         var bar : String;
      [*] = ;         _unit_GetUnitProducePlace(cid, sid, bar);
      [*] = ;
      [*] = ;         var c : Integer;
      [*] = ;         for c := 1 to 6 do
      [*] = ;         begin
      [*] = ;            var upgstr : String = bar+'.'+sid+'.1.'+IntToStr(c);
      [*] = ;            var upgind : Integer = 0;
      [*] = ;            GetUpgradeIndBySID(upgind, cid, upgstr);
      [*] = ;            var dmgtype : Integer = gcountry[cid].upgrade[upgind].iarrparam1[0];
      [*] = ;            if (dmgtype=0) then
      [*] = ;            dmgtype := gcountry[cid].upgrade[upgind].iarrparam1[1];
      [*] = ;            if ((dmgtype=gc_obj_weapon_kind_pike) or (dmgtype=gc_obj_weapon_kind_sword)) then
      [*] = ;            begin
      [*] = ;               var upgvalue : Float = gcountry[cid].upgrade[upgind].value;
      [*] = ;               if (upgvalue>0) then
      [*] = ;               begin
      [*] = ;                  meleedmg := meleedmg + StrToInt(FloatToStr(upgvalue));
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         str:= str+#9;
      [*] = ;         // ranged upgrades
      [*] = ;         for c := 1 to 6 do
      [*] = ;         begin
      [*] = ;            var upgstr : String = bar+'.'+sid+'.1.'+IntToStr(c);
      [*] = ;            var upgind : Integer = 0;
      [*] = ;            GetUpgradeIndBySID(upgind, cid, upgstr);
      [*] = ;            var dmgtype : Integer = gcountry[cid].upgrade[upgind].iarrparam1[0];
      [*] = ;            var isgren : Boolean = StrExists(sid, 'grenadier');
      [*] = ;            if (not (isgren and (c=6))) then
      [*] = ;            if ((dmgtype=gc_obj_weapon_kind_bullet) or (dmgtype=gc_obj_weapon_kind_arrow) or (dmgtype=gc_obj_weapon_kind_firearrow) or (dmgtype=gc_obj_weapon_kind_cannister) or (dmgtype=gc_obj_weapon_kind_cannonball) or (dmgtype=gc_obj_weapon_kind_mortarball)) then
      [*] = ;            begin
      [*] = ;               var upgvalue : Float = gcountry[cid].upgrade[upgind].value;
      [*] = ;               if (upgvalue>0) then
      [*] = ;               begin
      [*] = ;                  rangedmg := rangedmg + StrToInt(FloatToStr(upgvalue));
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         
      [*] = ;         // protection upgrades
      [*] = ;         _unit_GetUnitProducePlace(cid, sid, bar);
      [*] = ;
      [*] = ;         for c := 1 to 6 do
      [*] = ;         begin
      [*] = ;            var upgstr : String = bar+'.'+sid+'.2.'+IntToStr(c);
      [*] = ;            var upgind : Integer = 0;
      [*] = ;            GetUpgradeIndBySID(upgind, cid, upgstr);
      [*] = ;            var iter2 : Integer;
      [*] = ;            for iter2 := 0 to gc_obj_weapon_kind_count-1 do
      [*] = ;            begin
      [*] = ;               var dmgtype : Integer = gcountry[cid].upgrade[upgind].iarrparam1[iter2];
      [*] = ;               if ((dmgtype=gc_obj_weapon_kind_pike) or (dmgtype=gc_obj_weapon_kind_sword) or (dmgtype=gc_obj_weapon_kind_arrow)) then
      [*] = ;               begin
      [*] = ;                  var upgvalue : Float = gcountry[cid].upgrade[upgind].value;
      [*] = ;                  if (upgvalue>0) then
      [*] = ;                  begin
      [*] = ;                     protections[dmgtype] := protections[dmgtype] + StrToInt(FloatToStr(upgvalue));
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var upgrades : array[0..cMaxUnitUpgrades-1] of Integer;
      [*] = ;         GetUnitUpgradeIndexes(cid, sid, upgrades);
      [*] = ;         var costchangeparam : Integer;
      [*] = ;         var additionalupgvalue : Float;
      [*] = ;         var additionalparam1 : Float;
      [*] = ;         var additionalparam2 : Float;
      [*] = ;         var food, wood, stone, gold, iron, coal : Integer;
      [*] = ;         _unit_GetCostByID(cid, id, TObj(pobjbase).pl, food, wood, stone, gold, iron, coal);
      [*] = ;         var reload : Float;
      [*] = ;         var maxrange: Float;
      [*] = ;         var minrange : Float = 10000;
      [*] = ;
      [*] = ;         for i:=0 to gc_obj_MaxWeapon-1 do
      [*] = ;         begin
      [*] = ;            if (TObjBase(pobjbase).weapon[i].radiusmax>maxrange) then
      [*] = ;            maxrange := TObjBase(pobjbase).weapon[i].radiusmax;
      [*] = ;            if ((TObjProp(pobjprop).weapon[i].radiusmin>0) and (TObjProp(pobjbase).weapon[i].radiusmin<minrange)) then
      [*] = ;            minrange := TObjProp(pobjprop).weapon[i].radiusmin;
      [*] = ;            if (TObjBase(pobjbase).weapon[i].pause*32>20) then
      [*] = ;            begin
      [*] = ;               reload := TObjBase(pobjbase).weapon[i].pause*32;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         {if (TObjBase(pobjbase).weapon[i].pause*32>20) then
      [*] = ;         reload := TObjBase(pobjbase).weapon[i].pause*32;}
      [*] = ;         for c:= 0 to cMaxUnitUpgrades-1 do
      [*] = ;         begin
      [*] = ;            if (upgrades[c]<>0) then
      [*] = ;            begin
      [*] = ;               case c of
      [*] = ;                  0,26 : begin
      [*] = ;                     var g : Integer;
      [*] = ;                     for g:= 1 to gc_ResCount-1 do
      [*] = ;                     begin
      [*] = ;                        var upgvalue : Float = StrToFloat(gcountry[cid].upgrade[upgrades[c]].sarrparam2[gc_upgrade_maxarrparam2count-gc_ResCount-1+g])/100;
      [*] = ;                        if (upgvalue<>0) then
      [*] = ;                        begin
      [*] = ;                           case g of
      [*] = ;                              gc_resource_type_food : begin
      [*] = ;                                 food := Round(food * (1 + upgvalue));
      [*] = ;                              end;
      [*] = ;                              gc_resource_type_wood : begin
      [*] = ;                                 wood := Round(wood * (1 + upgvalue));
      [*] = ;                              end;
      [*] = ;                              gc_resource_type_stone : begin
      [*] = ;                                 stone := Round(stone * (1 + upgvalue));
      [*] = ;                              end;
      [*] = ;                              gc_resource_type_gold : begin
      [*] = ;                                 gold := Round(gold * (1 + upgvalue));
      [*] = ;                              end;
      [*] = ;                              gc_resource_type_iron : begin
      [*] = ;                                 iron := Round(iron * (1 + upgvalue));
      [*] = ;                              end;
      [*] = ;                              gc_resource_type_coal : begin
      [*] = ;                                 coal := Round(coal * (1 + upgvalue));
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  1,2,3,4 : begin
      [*] = ;                     var upgvalue : Float = gcountry[cid].upgrade[upgrades[c]].value;
      [*] = ;                     additionalupgvalue := additionalupgvalue+upgvalue/100;
      [*] = ;                     if (c=4) then
      [*] = ;                     rangedmg := Floor(rangedmg*(1+additionalupgvalue));
      [*] = ;                  end;
      [*] = ;                  5,6 : begin
      [*] = ;                     var upgvalue : Float = gcountry[cid].upgrade[upgrades[c]].value;
      [*] = ;                     additionalparam1 := additionalparam1+upgvalue/100;
      [*] = ;                     if (c=6) then
      [*] = ;                     reload := Round(reload*(1+additionalparam1));
      [*] = ;                  end;
      [*] = ;                  7,16,19,27 : begin
      [*] = ;                     var upgvalue : Float = gcountry[cid].upgrade[upgrades[c]].value/(100*100000);
      [*] = ;                     ftime := Round(ftime*(1+upgvalue));
      [*] = ;                  end;
      [*] = ;                  9,10,17,18,20 : begin
      [*] = ;                     var upgvalue : Float = gcountry[cid].upgrade[upgrades[c]].value;
      [*] = ;                     additionalparam2 := additionalparam2 + upgvalue;
      [*] = ;                  end;
      [*] = ;                  8,11,12 : begin
      [*] = ;                     var upgvalue : Float = gcountry[cid].upgrade[upgrades[c]].value;
      [*] = ;                     meleedmg := meleedmg + StrToInt(FloatToStr(upgvalue))
      [*] = ;                  end;
      [*] = ;                  13 : begin
      [*] = ;                     var upgvalue : Float = gcountry[cid].upgrade[upgrades[c]].value;
      [*] = ;                     meleedmg := Floor(meleedmg*(1+upgvalue/100));
      [*] = ;                  end;
      [*] = ;                  14,15,23,24,21,22 : begin
      [*] = ;                     var upgvalue : Float = gcountry[cid].upgrade[upgrades[c]].value;
      [*] = ;                     maxrange := maxrange*(1+upgvalue/100);
      [*] = ;                  end;
      [*] = ;                  25,28 : begin
      [*] = ;                     var upgvalue : Float = gcountry[cid].upgrade[upgrades[c]].value;
      [*] = ;                     hp := Round(hp*(1+upgvalue/100));
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (sid='cannon' or sid='howitzer') then
      [*] = ;         begin
      [*] = ;            for c := 1 to 6 do
      [*] = ;            begin
      [*] = ;               // time
      [*] = ;               var upgstr : String = bar+'.'+sid+'.2.'+IntToStr(c);
      [*] = ;               var upgind : Integer = 0;
      [*] = ;               GetUpgradeIndBySID(upgind, cid, upgstr);
      [*] = ;               var upgvalue : Float = gcountry[cid].upgrade[upgind].value/(100*100000);
      [*] = ;               if (upgvalue<>0) then
      [*] = ;               begin
      [*] = ;                  ftime := Round(ftime*(1+upgvalue));
      [*] = ;               end;
      [*] = ;
      [*] = ;               // price
      [*] = ;               upgstr := bar+'.'+sid+'.1.'+IntToStr(c);
      [*] = ;               upgind := 0;
      [*] = ;               GetUpgradeIndBySID(upgind, cid, upgstr);
      [*] = ;               var g : Integer;
      [*] = ;               for g:= 1 to gc_ResCount-1 do
      [*] = ;               begin
      [*] = ;                  var upgvalue : Float = StrToFloat(gcountry[cid].upgrade[upgind].sarrparam2[gc_upgrade_maxarrparam2count-gc_ResCount-1+g])/100;
      [*] = ;                  if (upgvalue<>0) then
      [*] = ;                  begin
      [*] = ;                     case g of
      [*] = ;                        gc_resource_type_food : begin
      [*] = ;                           food := Round(food * (1 + upgvalue));
      [*] = ;                        end;
      [*] = ;                        gc_resource_type_wood : begin
      [*] = ;                           wood := Round(wood * (1 + upgvalue));
      [*] = ;                        end;
      [*] = ;                        gc_resource_type_stone : begin
      [*] = ;                           stone := Round(stone * (1 + upgvalue));
      [*] = ;                        end;
      [*] = ;                        gc_resource_type_gold : begin
      [*] = ;                           gold := Round(gold * (1 + upgvalue));
      [*] = ;                        end;
      [*] = ;                        gc_resource_type_iron : begin
      [*] = ;                           iron := Round(iron * (1 + upgvalue));
      [*] = ;                        end;
      [*] = ;                        gc_resource_type_coal : begin
      [*] = ;                           coal := Round(coal * (1 + upgvalue));
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         // visuals
      [*] = ;         str := str+IntToStr(hp); //hp
      [*] = ;
      [*] = ;         str := str+#9+FloatToStr(ftime); //build-time
      [*] = ;         str := str+#9;
      [*] = ;
      [*] = ;         if ((gPlayer[plInd].objbase[cid, id].protection[1]>0) or (additionalparam2>0) or (protections[1]>0)) then str := str+FloatToStr((gPlayer[plInd].objbase[cid, id].protection[1]+additionalparam2+protections[1]))+#9 else str:=str+#9;
      [*] = ;         if ((gPlayer[plInd].objbase[cid, id].protection[2]>0) or (additionalparam2>0) or (protections[2]>0)) then str := str+FloatToStr((gPlayer[plInd].objbase[cid, id].protection[2])+additionalparam2+protections[2])+#9 else str:=str+#9;
      [*] = ;         if ((gPlayer[plInd].objbase[cid, id].protection[3]>0) or (additionalparam2>0) or (protections[3]>0)) then str := str+FloatToStr((gPlayer[plInd].objbase[cid, id].protection[3]+additionalparam2+protections[3]))+#9 else str:=str+#9;
      [*] = ;         if ((gPlayer[plInd].objbase[cid, id].protection[5]>0) or (additionalparam2>0) or (protections[5]>0)) then str := str+FloatToStr((gPlayer[plInd].objbase[cid, id].protection[5]+additionalparam2+protections[5]))+#9 else str:=str+#9;
      [*] = ;         if ((gPlayer[plInd].objbase[cid, id].protection[7]>0) or (additionalparam2>0) or (protections[7]>0)) then str := str+FloatToStr((gPlayer[plInd].objbase[cid, id].protection[7]+additionalparam2+protections[7]))+#9 else str:=str+#9;
      [*] = ;         if ((gPlayer[plInd].objbase[cid, id].protection[4]>0) or (additionalparam2>0) or (protections[4]>0)) then str := str+FloatToStr((gPlayer[plInd].objbase[cid, id].protection[4]+additionalparam2+protections[4])); // protection
      [*] = ;
      [*] = ;         if (gObjProp[cid, id].vision>0) then
      [*] = ;         str := str+#9+IntToStr(gObjProp[cid, id].vision*1000)   // vision
      [*] = ;         else
      [*] = ;         str := str+#9+' ';
      [*] = ;
      [*] = ;         if (gObjProp[cid, id].searchradius>0) then
      [*] = ;         str := str+#9+FloatToStr(gObjProp[cid, id].searchradius*gc_pixels_to_tile) // aggrorange
      [*] = ;         else
      [*] = ;         str := str+#9+' ';
      [*] = ;
      [*] = ;         str := str+#9;
      [*] = ;         // melee full-upgrades
      [*] = ;         if (meleedmg>0) then
      [*] = ;         str:= str+IntToStr(meleedmg);
      [*] = ;
      [*] = ;         str:= str+#9;
      [*] = ;         // range full-upgrades
      [*] = ;         if (rangedmg>0) then
      [*] = ;         str:= str+IntToStr(rangedmg);
      [*] = ;
      [*] = ;         str:= str+#9;
      [*] = ;         // here should be reload
      [*] = ;         if (reload>0) then
      [*] = ;         str:= str+FloatToStr(reload);
      [*] = ;         str:= str+#9;
      [*] = ;
      [*] = ;         // adding maxrange
      [*] = ;
      [*] = ;         if (maxrange*gc_pixels_to_tile>0) then
      [*] = ;         begin
      [*] = ;            str := str+FloatToStr(Round(maxrange*gc_pixels_to_tile));
      [*] = ;         end;
      [*] = ;         str:= str+#9;
      [*] = ;
      [*] = ;         // adding minrange
      [*] = ;         if ((minrange>=0) and (minrange<>10000)) then
      [*] = ;         str := str+FloatToStr(minrange*gc_pixels_to_tile);
      [*] = ;
      [*] = ;         str:= str+#9;
      [*] = ;
      [*] = ;         // adding cost
      [*] = ;
      [*] = ;         //str:= str+IntToStr(food)+' '+IntToStr(wood)+' '+IntToStr(stone)+' '+IntToStr(gold)+' '+IntToStr(iron)+' '+IntToStr(coal);
      [*] = ;         if (food>0) then
      [*] = ;         str:= str+IntToStr(food)+#9
      [*] = ;         else
      [*] = ;         str:= str+#9;
      [*] = ;
      [*] = ;         if (wood>0) then
      [*] = ;         str:= str+IntToStr(wood)+#9
      [*] = ;         else
      [*] = ;         str:= str+#9;
      [*] = ;
      [*] = ;         if (stone>0) then
      [*] = ;         str:= str+IntToStr(stone)+#9
      [*] = ;         else
      [*] = ;         str:= str+#9;
      [*] = ;
      [*] = ;         if (gold>0) then
      [*] = ;         str:= str+IntToStr(gold)+#9
      [*] = ;         else
      [*] = ;         str:= str+#9;
      [*] = ;
      [*] = ;         if (iron>0) then
      [*] = ;         str:= str+IntToStr(iron)+#9
      [*] = ;         else
      [*] = ;         str:= str+#9;
      [*] = ;
      [*] = ;         if (coal>0) then
      [*] = ;         str:= str+IntToStr(coal)+#9;
      [*] = ;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (gint_gui_encyclopediapage=3) then
      [*] = ;      begin
      [*] = ;         str := str+#9;
      [*] = ;         var bar : String;
      [*] = ;         _unit_GetUnitProducePlace(cid, sid, bar);
      [*] = ;         var c : Integer;
      [*] = ;         // protection upgrades
      [*] = ;         for c := 1 to 6 do
      [*] = ;         begin
      [*] = ;            var upgstr : String = bar+'.'+sid+'.2.'+IntToStr(c);
      [*] = ;            var upgind : Integer = 0;
      [*] = ;            GetUpgradeIndBySID(upgind, cid, upgstr);
      [*] = ;            var upgvalue : Float = gcountry[cid].upgrade[upgind].value;
      [*] = ;            if (upgvalue>0) then
      [*] = ;            str:= str+'+'+FloatToStr(upgvalue)+#9
      [*] = ;            else
      [*] = ;            str:= str+#9;
      [*] = ;         end;
      [*] = ;         //str:= str+#9;
      [*] = ;
      [*] = ;         var pobjprop : Pointer = gObjProp[cid, id];
      [*] = ;         var pobjbase : Pointer = gPlayer[plInd].objbase[cid, id];
      [*] = ;
      [*] = ;         // getting start-values
      [*] = ;         var meleedmg, rangedmg : Integer;
      [*] = ;         var weapInd : Integer;
      [*] = ;         for i:=0 to gc_obj_MaxWeapon-1 do
      [*] = ;         begin
      [*] = ;            if (weapInd<2) and (TObjProp(pobjprop).weapon[i].enabled) and (TObjBase(pobjbase).weapon[i].damage<>0) then
      [*] = ;            begin
      [*] = ;               if (TObjProp(pobjprop).weapon[i].kind=gc_obj_weapon_kind_pike)
      [*] = ;               or (TObjProp(pobjprop).weapon[i].kind=gc_obj_weapon_kind_sword) then
      [*] = ;               begin
      [*] = ;                  weapInd := weapInd+1;
      [*] = ;                  meleedmg := TObjBase(pobjbase).weapon[i].damage;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         weapInd := 0;
      [*] = ;         for i:=0 to gc_obj_MaxWeapon-1 do
      [*] = ;         begin
      [*] = ;            if (weapInd<2) and (TObjProp(pobjprop).weapon[i].enabled) and (TObjBase(pobjbase).weapon[i].damage<>0) then
      [*] = ;            begin
      [*] = ;               if (TObjProp(pobjprop).weapon[i].kind=gc_obj_weapon_kind_bullet)
      [*] = ;               or (TObjProp(pobjprop).weapon[i].kind=gc_obj_weapon_kind_arrow)
      [*] = ;               or (TObjProp(pobjprop).weapon[i].kind=gc_obj_weapon_kind_cannonball)
      [*] = ;               or (TObjProp(pobjprop).weapon[i].kind=gc_obj_weapon_kind_mortarball) then
      [*] = ;               begin
      [*] = ;                  weapInd := weapInd+1;
      [*] = ;                  rangedmg := TObjBase(pobjbase).weapon[i].damage;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         // melee upgrades
      [*] = ;         for c := 1 to 6 do
      [*] = ;         begin
      [*] = ;            var upgstr : String = bar+'.'+sid+'.1.'+IntToStr(c);
      [*] = ;            var upgind : Integer = 0;
      [*] = ;            GetUpgradeIndBySID(upgind, cid, upgstr);
      [*] = ;            var dmgtype : Integer = gcountry[cid].upgrade[upgind].iarrparam1[0];
      [*] = ;            if ((dmgtype=gc_obj_weapon_kind_pike) or (dmgtype=gc_obj_weapon_kind_sword)) then
      [*] = ;            begin
      [*] = ;               var upgvalue : Float = gcountry[cid].upgrade[upgind].value;
      [*] = ;               if (upgvalue>0) then
      [*] = ;               begin
      [*] = ;                  str:= str+'+'+FloatToStr(upgvalue)+#9;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               str:= str+#9;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            str:= str+#9;
      [*] = ;         end;
      [*] = ;         //str:= str+#9;
      [*] = ;         // ranged upgrades
      [*] = ;         for c := 1 to 6 do
      [*] = ;         begin
      [*] = ;            var upgstr : String = bar+'.'+sid+'.1.'+IntToStr(c);
      [*] = ;            var upgind : Integer = 0;
      [*] = ;            GetUpgradeIndBySID(upgind, cid, upgstr);
      [*] = ;            var dmgtype : Integer = gcountry[cid].upgrade[upgind].iarrparam1[0];
      [*] = ;            var isgren : Boolean = StrExists(sid, 'grenadier');
      [*] = ;            if (not (isgren and (c=6))) then
      [*] = ;            if ((dmgtype=gc_obj_weapon_kind_bullet) or (dmgtype=gc_obj_weapon_kind_arrow) or (dmgtype=gc_obj_weapon_kind_firearrow) or (dmgtype=gc_obj_weapon_kind_cannister) or (dmgtype=gc_obj_weapon_kind_cannonball) or (dmgtype=gc_obj_weapon_kind_mortarball)) then
      [*] = ;            begin
      [*] = ;               var upgvalue : Float = gcountry[cid].upgrade[upgind].value;
      [*] = ;               if (upgvalue>0) then
      [*] = ;               begin
      [*] = ;                  str:= str+'+'+FloatToStr(upgvalue)+#9;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               str:= str+#9;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            str:= str+#9;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      GUIListBoxAddItem(elmList, str+' ', ind);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;ind := 0;
      [*] = ;var category, cid, id : Integer;
      [*] = ;for category:=0 to 3 do
      [*] = ;begin
      [*] = ;   var categorytext : String;
      [*] = ;   case category of
      [*] = ;      0 : categorytext := cTextCategoryUnits;
      [*] = ;      1 : categorytext := cTextCategoryShips;
      [*] = ;      2 : categorytext := cTextCategoryArtillery;
      [*] = ;      3 : categorytext := cTextCategoryBuildings;
      [*] = ;   end;
      [*] = ;   cid := gint_gui_encyclopedia_cid;
      [*] = ;   for id:=1 to gc_country_maxmembers-1 do
      [*] = ;   begin
      [*] = ;      if (gPlayer[0].objbase[cid][id].sid<>'')
      [*] = ;      and (gPlayer[0].objbase[cid][id].sid<>'unitbox')
      [*] = ;      and (gPlayer[0].objbase[cid][id].sid<>'euriro')
      [*] = ;      and (gPlayer[0].objbase[cid][id].sid<>'eurcoa')
      [*] = ;      and (gPlayer[0].objbase[cid][id].sid<>'eursga')
      [*] = ;      and (gPlayer[0].objbase[cid][id].sid<>'tursga')
      [*] = ;      and (gPlayer[0].objbase[cid][id].sid<>'russga')
      [*] = ;      and (gPlayer[0].objbase[cid][id].sid<>'ukrwga')
      [*] = ;      and (gPlayer[0].objbase[cid][id].sid<>'archerturdip')
      [*] = ;      and (gPlayer[0].objbase[cid][id].sid<>'lightcavalrydip')
      [*] = ;      and ((cid=19) or (gPlayer[0].objbase[cid][id].sid<>'lightcavalry'))
      [*] = ;      and (gPlayer[0].objbase[cid][id].sid<>'pikemanspa')
      [*] = ;      and (gPlayer[0].objbase[cid][id].sid<>'field') then
      [*] = ;      begin
      [*] = ;         // cid for Spain
      [*] = ;         if ((cid=3) and gPlayer[0].objbase[cid][id].sid='pikeman') then
      [*] = ;         begin
      [*] = ;            var coseletteid : Integer = 0;
      [*] = ;            //for spear
      [*] = ;            // hardcoded atm, replacing with coselette, change with search pikemanspa
      [*] = ;            ShowUnitInList(elmList, plInd, cid, 60, gPlayer[plInd].stat.produced[3][60], category, categorytext, ind);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            ShowUnitInList(elmList, plInd, cid, id, gPlayer[plInd].stat.produced[cid][id], category, categorytext, ind);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var totalwidth : Integer;
      [*] = ;for i:=0 to GetGUIListBoxTabsCount(elmTabList)-1 do
      [*] = ;begin
      [*] = ;   var ftmp : Float;
      [*] = ;   var width : Integer;
      [*] = ;   GetGUIListBoxTabProperty(elmTabList, i, ftmp, ftmp, ftmp, ftmp, width);
      [*] = ;   AddGUIListBoxTabProperty(elmList, ftmp, ftmp, ftmp, ftmp, width, 'tsText');
      [*] = ;   totalwidth := totalwidth+width;
      [*] = ;   var alpha : Float = 0.4;
      [*] = ;   if (gint_gui_encyclopediapage<>3) then
      [*] = ;   case i of
      [*] = ;      4,5,6,7,8,17,18,19,20,21 : alpha:=0.15;
      [*] = ;   end;
      [*] = ;   if (gint_gui_encyclopediapage=3) then
      [*] = ;   case i of
      [*] = ;      2,3,4,5,6,8,9,10,11,12,14,15,16,17,18 : alpha:=0.15;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var elm : Integer = _gui_CreateImage('', elmList, gc_gui_material_white, gc_halParentLeft, gc_valParentBottomHeight, totalwidth-6, -70, 1, 25*26-114, 0, False);
      [*] = ;   SetGUIElementUseUserColor(elm, True);
      [*] = ;   const usercolor = 1;
      [*] = ;   //const alpha = 0.15;
      [*] = ;   SetGUIElementUserColor(elm, usercolor, usercolor, usercolor, alpha);
      [*] = ;
      [*] = ;   if (i=GetGUIListBoxTabsCount(elmTabList)-1) then
      [*] = ;   begin
      [*] = ;      elm := _gui_CreateImage('', elmList, gc_gui_material_white, gc_halParentLeft, gc_valParentBottomHeight, 6, -69, totalwidth-11, 1, 0, False);
      [*] = ;      SetGUIElementUseUserColor(elm, True);
      [*] = ;      const usercolor = 1;
      [*] = ;      const alpha = 0.15;
      [*] = ;      SetGUIElementUserColor(elm, usercolor, usercolor, usercolor, alpha);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var bNeedScroll : Boolean = _gui_SetListBoxHeight(elmList, 24);
      [*] = ;var scrollHnd : Integer = _gui_AddScroller(elmList, gc_halParentRightWidth, gc_valParentTop, 46, 21, 0, GetGUIElementHeight(elmProduce), bNeedScroll);
      [*] = ;// restore scroller position
      [*] = ;var count : Integer = GetGUIListBoxItemsCount(elmList);
      [*] = ;if topIndex>=count then
      [*] = ;topIndex := count-1
      [*] = ;else
      [*] = ;if topIndex<0 then
      [*] = ;topIndex := 0;
      [*] = ;SetGUIListBoxTopIndex(elmList, topIndex);
      [*] = ;SetGUIScrollBarPosition(scrollHnd, lastScrollPos);
      [*] = ;end;
      [*] = ;
      [*] = ;var elmCountryComboBox : Integer = _gui_CreateComboBox('country|', elmParent, 22, ((GetViewerHeight-14) div 50)+9, gc_halParentMiddle, gc_valParentTop, 6, 45, 150, gc_halLeft, gc_valMiddle, 5, 0, gc_font_serif_16, True, eventstate, bupdate, True);
      [*] = ;SetGUIElementVisible(elmCountryComboBox, True);
      [*] = ;FillComboBoxCountries(elmCountryComboBox, 0, False, False, False);
      [*] = ;
      [*] = ;if (gint_gui_encyclopediapage=0) then
      [*] = ;begin
      [*] = ;   var countryname : String;
      [*] = ;   _country_GetSIDByID(gint_gui_encyclopedia_cid, countryname);
      [*] = ;   countryname := GetLocaleTableListItemByID(gc_loc_units, countryname);
      [*] = ;   _gui_CreateText('_countryname', elmParent, countryname, gc_halParentMiddle, gc_valParentTop, 0, GetGUIElementPositionY(elmTableSkinHead)+GetGUIElementHeight(elmTableSkinHead) div 2, 0, 0, gc_halMiddle, gc_valMiddle, gc_font_serif_16, color, bupdate);
      [*] = ;end;
      [*] = ;
      [*] = ;// background
      [*] = ;maxheight := Max(maxheight, _gui_GetBottomPos(elmHnd)+cmargin*7);
      [*] = ;var elmBackground : Integer = _gui_CreateMainWindow('background', elmBackgroundParent, gc_halParentMiddle, gc_valParentMiddle, 0, 0, cwidth, cheight, 1, bupdate);
      [*] = ;SetGUIElementPositionY(elmBackgroundParent, 0);
      [*] = ;//_gui_CreateButton('bback', elmBackground, 'btn.close', gc_halParentRightWidth, gc_valParentTop, 4, -4, 0, 0, eventstate, nul, gc_gui_event_tagClose, bupdate);
      [*] = ;
      [*] = ;// head
      [*] = ;elmHnd := GetGUIElementIndexByNameParent('head.head', elmBackground);
      [*] = ;elmHnd := _gui_CreateText('thead', elmHnd, cTextEncyclopedia, gc_halParentMiddle, gc_valParentMiddle, 9, 3, 0, 28, gc_halMiddle, gc_valMiddle, gc_font_serif_16, color, bupdate);
      [*] = ;
      [*] = ;_gui_CreateButton('bback', elmBackground, 'btn.close', gc_halParentRightWidth, gc_valParentTop, 4, -4, 0, 0, eventstate, nul, gc_gui_event_tagClose, bupdate);
      [*] = ;
      [*] = ;var elmBtnPrev : Integer = _gui_CreateImage('_img_btnprev', elmCountryComboBox, gc_hud_icons_control+'hideobjectives', gc_halParentRight, gc_valParentMiddle, {58+78}10, 0, 35, 35, 0, True);
      [*] = ;elmHnd := _gui_CreateButton('swobj', elmBtnPrev, gc_gui_material_blank, gc_halParentLeft, gc_valParentTop, 0, 0, GetGUIElementWidth(elmBtnPrev), GetGUIElementHeight(elmBtnPrev), eventstate, nul, cTagPrev, True);
      [*] = ;SetGUIElementEnabled(elmHnd, gint_gui_encyclopediapage>1);
      [*] = ;var elmBtnNext : Integer = _gui_CreateImage('_img_btnnext', elmBtnPrev, gc_hud_icons_control+'showobjectives', gc_halParentRight, gc_valParentMiddle, 5, 0, 35, 35, 0, True);
      [*] = ;elmHnd := _gui_CreateButton('swobj', elmBtnNext, gc_gui_material_blank, gc_halParentLeft, gc_valParentTop, 0, 0, GetGUIElementWidth(elmBtnNext), GetGUIElementHeight(elmBtnNext), eventstate, nul, cTagNext, True);
      [*] = ;SetGUIElementEnabled(elmHnd, gint_gui_encyclopediapage<3);
      [*] = ;
      [*] = ;var hint : String; _misc_GetNewTextLocale('encyclopedia.faq', hint);
      [*] = ;//SetGUIAllowEvents(elmHnd, False, False, False);
      [*] = ;elmHnd := _gui_CreateImage('imgfaq', elmHnd, 'encyclopedia.faq', gc_halParentRight, gc_valParentMiddle, 360, 15, 0, 0, 0, True);
      [*] = ;_gui_CreateButton('btnfaq', elmHnd, gc_gui_material_blank, gc_halParentLeft, gc_valParentTop, 0, 0, GetGUIElementWidth(elmHnd), GetGUIElementHeight(elmHnd), eventstate, hint, nil, True);
      [*] = ;
      [*] = ;var faqtext : String = '?';
      [*] = ;_gui_CreateText('txtfaq', elmHnd, faqtext, gc_halParentMiddle, gc_valParentMiddle, 0, 0, 0, 0, gc_halMiddle, gc_valMiddle, gc_font_serif_16, color, bupdate);
      [*] = ;
      [*] = ;if (gint_gui_encyclopediapage=0) then
      [*] = ;_gui_CreateText('_pagename', elmBtnNext, cTextInfo, gc_halParentRight, gc_valParentMiddle, 10, 0, 0, 0, gc_halMiddle, gc_valMiddle, gc_font_serif_16, color, bupdate);
      [*] = ;if (gint_gui_encyclopediapage=1) then
      [*] = ;_gui_CreateText('_pagename', elmBtnNext, cTextBasic, gc_halParentRight, gc_valParentMiddle, 10, 0, 0, 0, gc_halMiddle, gc_valMiddle, gc_font_serif_16, color, bupdate);
      [*] = ;if (gint_gui_encyclopediapage=2) then
      [*] = ;_gui_CreateText('_pagename', elmBtnNext, cTextUpgraded, gc_halParentRight, gc_valParentMiddle, 10, 0, 0, 0, gc_halMiddle, gc_valMiddle, gc_font_serif_16, color, bupdate);
      [*] = ;if (gint_gui_encyclopediapage=3) then
      [*] = ;_gui_CreateText('_pagename', elmBtnNext, cTextAdditional, gc_halParentRight, gc_valParentMiddle, 10, 0, 0, 0, gc_halMiddle, gc_valMiddle, gc_font_serif_16, color, bupdate);
   struct.end
section.end

