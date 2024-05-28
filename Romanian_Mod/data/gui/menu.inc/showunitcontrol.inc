section.begin
   Name = ShowUnitControl
   Code : struct.begin
      [*] = ;if (GetPlayerHandleInterfaceIO=0) then
      [*] = ;exit;
      [*] = ;
      [*] = ;const cFont = gc_font_serif_13;
      [*] = ;const cFont2 = gc_font_serif_14;
      [*] = ;
      [*] = ;//cControlMarginLeft+cIconMargin+x*cIconSize+x*cIconMargin
      [*] = ;//y*cControlIconSize+y*cIconMargin-1
      [*] = ;
      [*] = ;const currentstatename = 'ShowUnitControl';
      [*] = ;var elmname, showstate, eventstate : String;
      [*] = ;_misc_GetGUIShowEventStateNames(currentstatename, elmname, showstate, eventstate);
      [*] = ;
      [*] = ;if (gbool_gui_update_unitcontrol) then
      [*] = ;begin
      [*] = ;   var elmHnd : Integer = GetGUIElementIndexByNameParent(elmname, _gui_GetTop);
      [*] = ;   if (elmHnd<>0) then
      [*] = ;   begin
      [*] = ;      RemoveGUIChildren(elmHnd);
      [*] = ;      SetGUIAllowEvents(elmHnd, False, False, False);
      [*] = ;   end;
      [*] = ;   gbool_gui_updateprogress_unitcontrol := False;
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;var realtime : Float = _misc_GetRealTime;
      [*] = ;var deltatime : Float = Abs(realtime-gfloat_gui_update_unitcontrol_lasttime);
      [*] = ;
      [*] = ;if (gint_gui_progresstick=gint_gui_update_unitcontrol_progresstick) then
      [*] = ;exit
      [*] = ;else
      [*] = ;gint_gui_update_unitcontrol_progresstick := gint_gui_progresstick;
      [*] = ;
      [*] = ;{if (not GetProgressingPauseMode) and (deltatime<0.015) then
      [*] = ;begin
      [*] = ;   SafeTimeLog(FloatToStr(deltatime));
      [*] = ;   //gfloat_gui_update_unitcontrol_lasttime := GetRealTime;
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;//else
      [*] = ;gfloat_gui_update_unitcontrol_lasttime := realtime;}
      [*] = ;
      [*] = ;const cAlphaIconUnsufficientRes = 0.4; // 0.2;
      [*] = ;const cAlphaBlackMaskReqsNotOk = 0.75; // 0.85;
      [*] = ;
      [*] = ;const cIconSize = 46;
      [*] = ;const cResIconSize = 46;
      [*] = ;const cIconMarginX = 0;
      [*] = ;const cIconMarginY = 1;
      [*] = ;var cMaxControlBtnCount : Integer = Min((GetViewerWidth-270-220-2) div (cIconSize+cIconMarginX), 35);
      [*] = ;const cControlMarginLeft = 8;
      [*] = ;const cControlMarginTop = -2;
      [*] = ;//const cParamMarginLeft = 4+2;
      [*] = ;const cNameMarginLeft = 27;
      [*] = ;const cParamValueMarginLeft = 7;
      [*] = ;const cParamProtectionRowBase = 20-5;
      [*] = ;const cParamProtectionRowOffset = 66;
      [*] = ;const cParamProtectionMarginHeight = 8;
      [*] = ;const cParamDmgShieldXOff = 0;
      [*] = ;const cParamMineMarginWidth = 8;
      [*] = ;const cParamMineMarginHeight = -2;
      [*] = ;const cParamDamageMarginHeight = 2;
      [*] = ;const cParamMarginHeight = 6;
      [*] = ;const cParamMarginTop = 12;
      [*] = ;const cParamMarginBottom = 8;
      [*] = ;const cParamIconSize = 24;
      [*] = ;const cParamIconMargin = 5;
      [*] = ;const cSizeY = cIconSize*3+cIconMarginY*4;
      [*] = ;
      [*] = ;const cTagRally = 50;
      [*] = ;const cTagIdlePeasants = 60;
      [*] = ;const cTagIdleMines = 61;
      [*] = ;const cTagUnit = 100;
      [*] = ;const cTagUpgrade = 200;
      [*] = ;const cBaseTagSelectUnit = 2000;
      [*] = ;const cBaseTagSelectSquad = 5000;
      [*] = ;const cBaseTagGoOutside = 1000;
      [*] = ;const cBaseTagMarketResSell = 400;
      [*] = ;const cBaseTagMarketResBuy = 410;
      [*] = ;const cBaseTagMarketNumbers = 420;
      [*] = ;const cTagMarketAccept = 430;
      [*] = ;const cTagMarketClear = 440;
      [*] = ;const cTagControlHoldPosition = 300;
      [*] = ;const cTagControlCancelHoldPosition = 301;
      [*] = ;const cTagControlGoWithAttack = 302;
      [*] = ;const cTagControlEnableAttack = 303;
      [*] = ;const cTagControlDisableAttack = 304;
      [*] = ;const cTagControlPatrol = 305;
      [*] = ;const cTagControlGuard = 306;
      [*] = ;const cTagControlCancelGuard = 307;
      [*] = ;const cTagControlSquadFill = 310;
      [*] = ;const cTagControlSquadDisband = 311;
      [*] = ;const cTagControlSquadFormLine = 312;
      [*] = ;const cTagControlSquadFormColumn = 313;
      [*] = ;const cTagControlSquadFormSquare = 314;
      [*] = ;const cTagControlSquadGroups = 315;
      [*] = ;const cTagControlArtilleryPreparation = 316;
      [*] = ;const cTagControlSquadFormationUnit = 317;
      [*] = ;const cTagControlOpenGate = 318;
      [*] = ;const cTagControlCloseGate = 319;
      [*] = ;const cTagControlOfficerDecreaseSize = 320;
      [*] = ;const cTagControlOfficerIncreaseSize = 321;
      [*] = ;const cTagControlUnloadAll = 322;
      [*] = ;
      [*] = ;//const cParentSizeY = 2+cParamMarginTop+(cParamIconSize+cParamIconMargin*2)*5+cParamDamageMarginHeight+cParamProtectionMarginHeight+cParamMarginBottom;
      [*] = ;const cParentSizeY = 151;
      [*] = ;const cMinimapSizeX = 289;
      [*] = ;
      [*] = ;var cTextDamage : String = GetLocaleTableListItemByID('gui', 'unitpanel.hint.damage');
      [*] = ;var cTextShield : String = GetLocaleTableListItemByID('gui', 'unitpanel.hint.shield');
      [*] = ;var cTextProtection : String = GetLocaleTableListItemByID('gui', 'unitpanel.hint.protection');
      [*] = ;var cTextWeaponKindPike : String = GetLocaleTableListItemByID('gui', 'weaponkind.pike');
      [*] = ;var cTextWeaponKindSword : String = GetLocaleTableListItemByID('gui', 'weaponkind.sword');
      [*] = ;var cTextWeaponKindBullet : String = GetLocaleTableListItemByID('gui', 'weaponkind.bullet');
      [*] = ;var cTextWeaponKindCannister : String = GetLocaleTableListItemByID('gui', 'weaponkind.cannister');
      [*] = ;var cTextWeaponKindArrow : String = GetLocaleTableListItemByID('gui', 'weaponkind.arrow');
      [*] = ;var cTextWeaponKindFireArrow : String = GetLocaleTableListItemByID('gui', 'weaponkind.firearrow');
      [*] = ;var cTextWeaponKindCannonball : String = GetLocaleTableListItemByID('gui', 'weaponkind.cannonball');
      [*] = ;var cTextWeaponKindMortarball : String = GetLocaleTableListItemByID('gui', 'weaponkind.mortarball');
      [*] = ;var cTextRallyPoint : String = GetLocaleTableListItemByID('gui', 'control.btn.rallypoint');
      [*] = ;var cTextIdlePeasants : String = GetLocaleTableListItemByID('gui', 'control.btn.idlepeasants');
      [*] = ;var cTextIdleMines : String = GetLocaleTableListItemByID('gui', 'control.btn.idlemines');
      [*] = ;const cTextMarketResBase = 'gui|restype.';
      [*] = ;var cTextMarketPlusRes : String = GetLocaleTableListItemByID('gui', 'control.btn.market.plusres');
      [*] = ;var cTextMarketMinusRes : String = GetLocaleTableListItemByID('gui', 'control.btn.market.minusres');
      [*] = ;var cTextMarketAccept : String = GetLocaleTableListItemByID('gui', 'control.btn.market.accept');
      [*] = ;var cTextMarketClear : String = GetLocaleTableListItemByID('gui', 'control.btn.market.clear');
      [*] = ;var cTextMarketSell : String = GetLocaleTableListItemByID('gui', 'control.market.offer');
      [*] = ;var cTextMarketBuy : String = GetLocaleTableListItemByID('gui', 'control.market.demand');
      [*] = ;var cTextRequireDrummer : String = GetLocaleTableListItemByID('gui', 'control.btn.createsquad.requiredrummer');
      [*] = ;var cTextRequireMoreUnitsToFormation : String = GetLocaleTableListItemByID('gui', 'control.btn.createsquad.requiremoreunits');
      [*] = ;var cTextInside : String = GetLocaleTableListItemByID('gui', 'unitpanel.info.inside');
      [*] = ;var cTextMaxInside : String = GetLocaleTableListItemByID('gui', 'unitpanel.info.maxinside');
      [*] = ;var cTextKills : String = GetLocaleTableListItemByID('gui', 'unitpanel.info.kills');
      [*] = ;var cTextArtLimitCannon : String = GetLocaleTableListItemByID('gui', 'unitpanel.info.artlimit.cannon');
      [*] = ;var cTextArtLimitHowitzer : String = GetLocaleTableListItemByID('gui', 'unitpanel.info.artlimit.howitzers');
      [*] = ;var cTextArtLimitMortar : String = GetLocaleTableListItemByID('gui', 'unitpanel.info.artlimit.mortars');
      [*] = ;var cTextArtLimitMultiCannon : String = GetLocaleTableListItemByID('gui', 'unitpanel.info.artlimit.multicannon');
      [*] = ;var cTextTime : String = GetLocaleTableListItemByID('gui', 'unitpanel.hint.time');
      [*] = ;
      [*] = ;var cTextHoldPosition : String = GetLocaleTableListItemByID('gui', 'control.btn.holdposition');
      [*] = ;var cTextCancelHoldPosition : String = GetLocaleTableListItemByID('gui', 'control.btn.cancelholdposition');
      [*] = ;var cTextGoWithAttack : String = GetLocaleTableListItemByID('gui', 'control.btn.gowithattack');
      [*] = ;var cTextEnableAttack : String = GetLocaleTableListItemByID('gui', 'control.btn.enableattack');
      [*] = ;var cTextDisableAttack : String = GetLocaleTableListItemByID('gui', 'control.btn.disableattack');
      [*] = ;var cTextPatrol : String = GetLocaleTableListItemByID('gui', 'control.btn.patrol');
      [*] = ;var cTextGuard : String = GetLocaleTableListItemByID('gui', 'control.btn.guard');
      [*] = ;var cTextCancelGuard : String = GetLocaleTableListItemByID('gui', 'control.btn.cancelguard');
      [*] = ;var cTextSquadFill : String = GetLocaleTableListItemByID('misc', 'control.btn.fillform'); // misc, not in gui locale table
      [*] = ;var cTextSquadDisband : String = GetLocaleTableListItemByID('gui', 'control.btn.squaddisband');
      [*] = ;var cTextOfficerDecreasesize : String = GetLocaleTableListItemByID('gui', 'control.btn.officerdecreasesize');
      [*] = ;var cTextOfficerIncreasesize : String = GetLocaleTableListItemByID('gui', 'control.btn.officerincreasesize');
      [*] = ;var cTextArtilleryPreparation : String = GetLocaleTableListItemByID('gui', 'control.btn.artillerypreparation');
      [*] = ;var cTextSquadFormLine : String = GetLocaleTableListItemByID('gui', 'control.btn.squadformline');
      [*] = ;var cTextSquadFormColumn : String = GetLocaleTableListItemByID('gui', 'control.btn.squadformcolumn');
      [*] = ;var cTextSquadFormSquare : String = GetLocaleTableListItemByID('gui', 'control.btn.squadformsquare');
      [*] = ;var cTextCavSquadFormLine : String = GetLocaleTableListItemByID('gui', 'control.btn.cavsquadformline');
      [*] = ;var cTextCavSquadFormWedge : String = GetLocaleTableListItemByID('gui', 'control.btn.cavsquadformwedge');
      [*] = ;var cTextCavSquadFormColumn : String = GetLocaleTableListItemByID('gui', 'control.btn.cavsquadformcolumn');
      [*] = ;var cTextOpenGates : String = GetLocaleTableListItemByID('gui', 'control.btn.opengates');
      [*] = ;var cTextCloseGates : String = GetLocaleTableListItemByID('gui', 'control.btn.closegates');
      [*] = ;var cTextGroupFormations : String = GetLocaleTableListItemByID('gui', 'control.btn.groupformations');
      [*] = ;var cTextUnGroupFormations : String = GetLocaleTableListItemByID('gui', 'control.btn.ungroupformations');
      [*] = ;var cTextUnloadAll : String = GetLocaleTableListItemByID('misc', 'control.btn.unloadall');
      [*] = ;
      [*] = ;var colorBrown, colorWhite : TColor;
      [*] = ;colorWhite.r := 1;
      [*] = ;colorWhite.g := 1;
      [*] = ;colorWhite.b := 1;
      [*] = ;colorWhite.a := 1;
      [*] = ;colorBrown.r := 255/255;
      [*] = ;colorBrown.g := 225/255;
      [*] = ;colorBrown.b := 185/255;
      [*] = ;colorBrown.a := 1;
      [*] = ;
      [*] = ;procedure WeaponKindToText(kind : Integer; var text : String);
      [*] = ;begin
      [*] = ;   case kind of
      [*] = ;      gc_obj_weapon_kind_pike : text := GetLocaleTableListItemByID('gui', 'unitpanel.hint.damage.weaponkind.1');
      [*] = ;      gc_obj_weapon_kind_sword : text := GetLocaleTableListItemByID('gui', 'unitpanel.hint.damage.weaponkind.0');
      [*] = ;      gc_obj_weapon_kind_bullet : text := GetLocaleTableListItemByID('gui', 'unitpanel.hint.damage.weaponkind.2');
      [*] = ;      gc_obj_weapon_kind_cannister : text := GetLocaleTableListItemByID('gui', 'unitpanel.hint.damage.weaponkind.5');
      [*] = ;      gc_obj_weapon_kind_arrow : text := GetLocaleTableListItemByID('gui', 'unitpanel.hint.damage.weaponkind.3');
      [*] = ;      gc_obj_weapon_kind_firearrow : text := GetLocaleTableListItemByID('gui', 'unitpanel.hint.damage.weaponkind.6');
      [*] = ;      gc_obj_weapon_kind_cannonball : GetLocaleTableListItemByID('gui', 'unitpanel.hint.damage.weaponkind.5');
      [*] = ;      gc_obj_weapon_kind_mortarball : GetLocaleTableListItemByID('gui', 'unitpanel.hint.damage.weaponkind.7');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var goHnd : Integer;
      [*] = ;gint_gui_unitcontrolsquadind := -1;
      [*] = ;var psquad : Pointer;
      [*] = ;var plHnd : Integer = GetPlayerHandleInterfaceIO;
      [*] = ;var plInd : Integer = GetPlayerIndexByHandle(plHnd);
      [*] = ;var squadscount : Integer = gPlayer[plInd].squads.GetCount;
      [*] = ;var sumkills : Integer;
      [*] = ;var btowerexists, bbuildingexists, bunitexists, bsquadexists, bstandground, bnostandground, bcansearchvictim, bsearchvictim, bnosearchvictim, bmorethenonetype, bguard, babsorberexists, bwallexists, bgateexists, bartdepo, bpeasantexists, bunbuiltexists : Boolean;
      [*] = ;var bofficerexists, bdrummerexists : Boolean;
      [*] = ;var shipscount : Integer;
      [*] = ;var i : Integer;
      [*] = ;for i:=0 to gPlayer[plInd].squads.GetCount-1 do
      [*] = ;begin
      [*] = ;   var ptmpsquad : Pointer = gPlayer[plInd].squads.Get(i);
      [*] = ;   if (ptmpsquad<>nil) and (TSquad(ptmpsquad).fSelected) then
      [*] = ;   begin
      [*] = ;      if (TSquad(ptmpsquad).GetCount=0) then
      [*] = ;      TSquad(ptmpsquad).fSelected := False
      [*] = ;      else
      [*] = ;      if (TSquad(ptmpsquad).fSelected) and (_squad_IsWaterSquad(ptmpsquad)) then
      [*] = ;      begin
      [*] = ;         gSelectedObjects.Add(TSquad(ptmpsquad).Get(0));
      [*] = ;         shipscount := shipscount+1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;for i:=0 to squadscount-1 do
      [*] = ;begin
      [*] = ;   var ptmpsquad : Pointer = gPlayer[plInd].squads.Get(i);
      [*] = ;   if (ptmpsquad<>nil) then
      [*] = ;   begin
      [*] = ;      if (TSquad(ptmpsquad).fSelected) and (not _squad_IsWaterSquad(ptmpsquad)) then
      [*] = ;      begin
      [*] = ;         psquad := ptmpsquad;
      [*] = ;         gint_gui_unitcontrolsquadind := i;
      [*] = ;         var tmpHnd : Integer = _unit_GetSquadUnit(psquad);
      [*] = ;         if (tmpHnd<>0) then
      [*] = ;         begin
      [*] = ;            var pobj : Pointer = _unit_GetTObj(tmpHnd);
      [*] = ;            if (pobj<>nil) and (TObj(pobj).hp>0) and (not TObj(pobj).bdead) then
      [*] = ;            begin
      [*] = ;               goHnd := tmpHnd;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   ErrorLog('ShowUnitControl : ptmpsquad=nil');
      [*] = ;end;
      [*] = ;
      [*] = ;if (goHnd=0) then
      [*] = ;begin
      [*] = ;   for i:=0 to gSelectedObjects.GetCount-1 do
      [*] = ;   begin
      [*] = ;      var tmpHnd : Integer = gSelectedObjects.Get(i);
      [*] = ;      var pobj : Pointer = _unit_GetTObj(tmpHnd);
      [*] = ;      if (pobj<>nil) and (TObj(pobj).hp>0) and (not TObj(pobj).bdead) then
      [*] = ;      begin
      [*] = ;         goHnd := tmpHnd;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// clear gSelection
      [*] = ;var j : Integer;
      [*] = ;for i:=0 to gc_MaxCountryCount-1 do
      [*] = ;for j:=0 to gc_country_maxmembers-1 do
      [*] = ;if (gSelection[i][j].id<>0) then
      [*] = ;begin
      [*] = ;   gSelection[i][j].id := 0;
      [*] = ;   gSelection[i][j].count := 0;
      [*] = ;   gSelection[i][j].hp := 0;
      [*] = ;   gSelection[i][j].maxhp := 0;
      [*] = ;   if (not gbool_gui_shifticonsselection) then
      [*] = ;   gSelection[i][j].bshiftsel := False;
      [*] = ;   gSelection[i][j].bbuiltexists := False;
      [*] = ;end;
      [*] = ;
      [*] = ;for i:=0 to gc_gameplay_maxplayersquadcount-1 do
      [*] = ;begin
      [*] = ;   gSelectionSquads[i].squad := -1;
      [*] = ;   gSelectionSquads[i].count := 0;
      [*] = ;   gSelectionSquads[i].hp := 0;
      [*] = ;   gSelectionSquads[i].maxhp := 0;
      [*] = ;   if (not gbool_gui_shifticonsselection) then
      [*] = ;   gSelectionSquads[i].bshiftsel := False;
      [*] = ;end;
      [*] = ;
      [*] = ;// arrOfficerFormation start
      [*] = ;type TOfficerFormationMask = class
      [*] = ;   count : array [0..gc_country_maxofficersformationmask-1] of Integer;
      [*] = ;   bexists : array [0..gc_country_maxofficersformationmask-1] of Boolean;
      [*] = ;end;
      [*] = ;type TOfficerFormation = class
      [*] = ;   units : array [0..gc_country_maxformationunitcount-1] of TOfficerFormationMask;
      [*] = ;end;
      [*] = ;var arrOfficerFormation : array [0..gc_country_maxformationunitcount-1] of TOfficerFormation;
      [*] = ;var arrOfficerUnitsCount : array [0..gc_country_maxformationunitcount-1] of Integer;
      [*] = ;// arrOfficerFormation finish
      [*] = ;
      [*] = ;var arrProduceInfinite : array [0..gc_country_fixedproduce_maxcount-1] of Integer;
      [*] = ;var arrProduceCount : array [0..gc_country_fixedproduce_maxcount-1] of Integer;
      [*] = ;var arrProduceProgress : array [0..gc_country_fixedproduce_maxcount-1] of Float;
      [*] = ;
      [*] = ;const cMaxPerformUpgradeAtOnce = 16;
      [*] = ;var sarrPerformUpgrade : array [0..cMaxPerformUpgradeAtOnce-1] of String;
      [*] = ;var sarrPerformUpgradeProgress : array [0..cMaxPerformUpgradeAtOnce-1] of Float;
      [*] = ;
      [*] = ;var freeGoHnd, freeGoHndTemp, freeGoHndAny : Integer;
      [*] = ;var fixedproduceInd : Integer = -2;
      [*] = ;var lastcid, lastid, lastsquad, lasthnd : Integer = -1;
      [*] = ;
      [*] = ;var selsquadcount : Integer;
      [*] = ;for i:=0 to squadscount-1 do
      [*] = ;begin
      [*] = ;   var ptmpsquad : Pointer = gPlayer[plInd].squads.Get(i);
      [*] = ;   if (ptmpsquad<>nil) and (TSquad(ptmpsquad).fSelected) and (not _squad_IsWaterSquad(ptmpsquad)) then
      [*] = ;   begin
      [*] = ;      selsquadcount := selsquadcount+1;
      [*] = ;      var goHnd : Integer = _unit_GetSquadUnit(ptmpsquad);
      [*] = ;      var pobj : Pointer = _unit_GetTObj(goHnd);
      [*] = ;      if (pobj<>nil) and (TObj(pobj).hp>0) and (not TObj(pobj).bdead) then
      [*] = ;      begin
      [*] = ;         var id : Integer = TObj(pobj).id;
      [*] = ;         var cid : Integer = TObj(pobj).cid;
      [*] = ;         var squad : Integer = TObj(pobj).squad;
      [*] = ;
      [*] = ;         bsquadexists := True;
      [*] = ;
      [*] = ;         if ((lastcid<>-1) and (lastid<>-1) and (lasthnd<>-1) and (lastsquad<>-1)) and ((cid<>lastcid) or (id<>lastid) or (squad<>lastsquad)) then
      [*] = ;         bmorethenonetype := True;
      [*] = ;
      [*] = ;         if (not bstandground) and (TSquad(ptmpsquad).fStandGround) then bstandground := True;
      [*] = ;         if (not bnostandground) and (not TSquad(ptmpsquad).fStandGround) then bnostandground := True;
      [*] = ;         if (not bsearchvictim) and (TSquad(ptmpsquad).fSearchVictim) then bsearchvictim := True;
      [*] = ;         if (not bnosearchvictim) and (not TSquad(ptmpsquad).fSearchVictim) then bnosearchvictim := True;
      [*] = ;         if (not bcansearchvictim) and ((gObjProp[TObj(pobj).cid][TObj(pobj).id].weapon[0].enabled) or (gObjProp[TObj(pobj).cid][TObj(pobj).id].weapon[1].enabled)) then bcansearchvictim := True;
      [*] = ;
      [*] = ;         lastcid := cid;
      [*] = ;         lastid := id;
      [*] = ;         lastsquad := squad;
      [*] = ;         lasthnd := goHnd;
      [*] = ;
      [*] = ;         if (selsquadcount=1) then
      [*] = ;         begin
      [*] = ;            for j:=0 to TSquad(ptmpsquad).GetCount-1 do // todo : test performance
      [*] = ;            begin
      [*] = ;               var tmpHnd : Integer = TSquad(ptmpsquad).Get(j);
      [*] = ;               var pobjtmp : Pointer = _unit_GetTObj(tmpHnd);
      [*] = ;               if (pobjtmp<>nil) then
      [*] = ;               sumkills := sumkills+TObj(pobjtmp).kill;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         sumkills := 0;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var maxFindDrummerAttempts : Integer;
      [*] = ;if GameManagerIsSelectionMode then
      [*] = ;maxFindDrummerAttempts := 2
      [*] = ;else
      [*] = ;maxFindDrummerAttempts := 5;
      [*] = ;var findDrummerAttempts : Integer;
      [*] = ;
      [*] = ;gTmpIntListGUIInsideList.Clear;
      [*] = ;gTmpIntListGUIDrummerList.Clear;
      [*] = ;for i:=gSelectedObjects.GetCount-1 downto 0 do
      [*] = ;begin
      [*] = ;   var goHnd : Integer = gSelectedObjects.Get(i);
      [*] = ;
      [*] = ;   var bPerformUpgrade : Boolean;
      [*] = ;   var pobj : Pointer = _unit_GetTObj(goHnd);
      [*] = ;   if (pobj<>nil) and (TObj(pobj).hp>0) and (not TObj(pobj).bdead) then
      [*] = ;   begin
      [*] = ;      var pobjprop : Pointer = gObjProp[TObj(pobj).cid][TObj(pobj).id];
      [*] = ;      var psel : Pointer = gSelection[TObj(pobj).cid][TObj(pobj).id];
      [*] = ;      if (psel<>nil) then
      [*] = ;      begin
      [*] = ;         var cid : Integer = TObj(pobj).cid;
      [*] = ;         var id : Integer = TObj(pobj).id;
      [*] = ;
      [*] = ;         TSelection(psel).count := TSelection(psel).count+1;
      [*] = ;         TSelection(psel).hp := TSelection(psel).hp+TObj(pobj).hp;
      [*] = ;         TSelection(psel).maxhp := TSelection(psel).maxhp+gPlayer[TObj(pobj).pl].objbase[TObj(pobj).cid][TObj(pobj).id].maxhp;
      [*] = ;         TSelection(psel).id := id;
      [*] = ;         if (TObj(pobj).bbuilt) then
      [*] = ;         TSelection(psel).bbuiltexists := True;
      [*] = ;
      [*] = ;         sumkills := sumkills+TObj(pobj).kill;
      [*] = ;
      [*] = ;         if ((lastcid<>-1) and (lastid<>-1) and (lasthnd<>-1)) and ((cid<>lastcid) or (id<>lastid)) or (bsquadexists) then
      [*] = ;         bmorethenonetype := True;
      [*] = ;
      [*] = ;         if (not bmorethenonetype) then
      [*] = ;         begin
      [*] = ;            if (TObj(pobj).bbuilt) then
      [*] = ;            begin
      [*] = ;               if (fixedproduceInd=-2) then
      [*] = ;               begin
      [*] = ;                  var basename : String;
      [*] = ;                  if (TObjProp(pobjprop).bGate) then
      [*] = ;                  _unit_ConvertObjIDToSID(cid, id, basename)
      [*] = ;                  else
      [*] = ;                  if (TObjProp(pobjprop).bWall) then
      [*] = ;                  _unit_ConvertObjIDToSID(cid, id, basename)
      [*] = ;                  else
      [*] = ;                  basename := GetGameObjectBaseNameByHandle(goHnd);
      [*] = ;                  fixedproduceInd := _country_GetFixedProduceIndexBySID(cid, basename, False);
      [*] = ;               end;
      [*] = ;               var j : Integer;
      [*] = ;               for j:=gc_obj_MaxOrderCount-1 downto 0 do
      [*] = ;               begin
      [*] = ;                  if (TObj(pobj).orders[j].itype=gc_obj_order_type_guard) then
      [*] = ;                  bguard := True;
      [*] = ;                  if (fixedproduceInd<>-1) then
      [*] = ;                  begin
      [*] = ;                     if (TObj(pobj).orders[j].itype=gc_obj_order_type_produce) then
      [*] = ;                     begin
      [*] = ;                        var sid : String;
      [*] = ;                        _unit_ConvertObjIDToSID(cid, TObj(pobj).orders[j].info.produceid, sid);
      [*] = ;                        var fpbuildind : Integer = _country_GetFixedProduceBuildIndexBySID(cid, fixedproduceInd, sid);
      [*] = ;                        if (fpbuildind>-1) then
      [*] = ;                        begin
      [*] = ;                           if (j=0) then
      [*] = ;                           begin
      [*] = ;                              if (TObj(pobj).orders[j].info.progress>arrProduceProgress[fpbuildind]) then
      [*] = ;                              arrProduceProgress[fpbuildind] := TObj(pobj).orders[j].info.progress
      [*] = ;                              else
      [*] = ;                              arrProduceProgress[fpbuildind] := arrProduceProgress[fpbuildind]+0.001;
      [*] = ;                           end;
      [*] = ;                           if (TObj(pobj).orders[j].info.amount=gc_obj_order_produce_infinite) then
      [*] = ;                           arrProduceInfinite[fpbuildind] := arrProduceInfinite[fpbuildind]+1
      [*] = ;                           else
      [*] = ;                           arrProduceCount[fpbuildind] := arrProduceCount[fpbuildind]+TObj(pobj).orders[j].info.amount;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  if (TObj(pobj).orders[j].itype=gc_obj_order_type_performupgrade) then
      [*] = ;                  begin
      [*] = ;                     bPerformUpgrade := True;
      [*] = ;                     var k : Integer;
      [*] = ;                     for k:=0 to cMaxPerformUpgradeAtOnce-1 do
      [*] = ;                     if (sarrPerformUpgrade[k]='') then
      [*] = ;                     begin
      [*] = ;                        _country_GetUpgradeSIDByUpgradeID(TObj(pobj).cid, TObj(pobj).orders[j].info.upgradeid, sarrPerformUpgrade[k]);
      [*] = ;                        //sarrPerformUpgrade[k] := TObj(pobj).orders[j].info.upgradesid;
      [*] = ;                        sarrPerformUpgradeProgress[k] := TObj(pobj).orders[j].info.progress;
      [*] = ;                        break;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               if ((TObjProp(pobjprop).peasantabsorber>0) or (TObjProp(pobjprop).transport>0)) then
      [*] = ;               begin
      [*] = ;                  var pobjinside : Pointer = _misc_GetObjectArgData(goHnd, gc_argunit_inside);
      [*] = ;                  if (pobjinside<>nil) then
      [*] = ;                  begin
      [*] = ;                     var startInd : Integer;
      [*] = ;                     var k : Integer;
      [*] = ;                     for k:=gc_obj_MaxOrderCount-1 downto 0 do
      [*] = ;                     if (TObj(pObj).orders[k].itype=gc_obj_order_type_exitunits) then
      [*] = ;                     begin
      [*] = ;                        startInd := TObj(pObj).orders[i].info.amount;
      [*] = ;                        break;
      [*] = ;                     end;
      [*] = ;                     for k:=startInd to TIntegerList(pobjinside).GetCount-1 do
      [*] = ;                     begin
      [*] = ;                        var inHnd : Integer = TIntegerList(pobjinside).Get(k);
      [*] = ;                        var pinobj : Pointer = _unit_GetTObj(inHnd);
      [*] = ;                        if (pinobj<>nil) and (not TObj(pInObj).bLeaveRequested) then
      [*] = ;                        begin
      [*] = ;                           var unique : Integer = TObj(pinobj).cid*100+TObj(pinobj).id;
      [*] = ;                           gTmpIntListGUIInsideList.Add(unique);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if (not bPerformUpgrade) and (freeGoHnd=0) and (TObj(pobj).bbuilt) then
      [*] = ;         freeGoHnd := goHnd;
      [*] = ;
      [*] = ;         if (freeGoHnd=0) and (freeGoHndTemp=0) and (TObj(pobj).bbuilt) then // helps if we got unbuild and performupgrade only
      [*] = ;         freeGoHndTemp := goHnd;
      [*] = ;
      [*] = ;         if (freeGoHnd=0) and (freeGoHndTemp=0) and (freeGoHndAny=0) then // helps if we got unbuild and performupgrade only
      [*] = ;         freeGoHndAny := goHnd;
      [*] = ;
      [*] = ;         if (not babsorberexists) and ((TObjProp(pobjprop).peasantabsorber>0) or (TObjProp(pobjprop).transport>0)) then babsorberexists := True;
      [*] = ;         if (not btowerexists) and (TObjProp(pobjprop).usage=gc_obj_usage_tower) then btowerexists := True;
      [*] = ;         if (not bbuildingexists) and (TObjProp(pobjprop).bbuilding) then bbuildingexists := True;
      [*] = ;         if (not bunitexists) and (not TObjProp(pobjprop).bbuilding) then bunitexists := True;
      [*] = ;         if (not bstandground) and (TObj(pobj).bstandground) then bstandground := True;
      [*] = ;         if (not bnostandground) and (not TObj(pobj).bstandground) then bnostandground := True;
      [*] = ;         if (not bsearchvictim) and (TObj(pobj).bsearchenemy) then bsearchvictim := True;
      [*] = ;         if (not bnosearchvictim) and (not TObj(pobj).bsearchenemy) then bnosearchvictim := True;
      [*] = ;         if (not bcansearchvictim) and ((TObjProp(pobjprop).weapon[0].enabled) or (TObjProp(pobjprop).weapon[1].enabled)) then bcansearchvictim := True;
      [*] = ;         if (not bwallexists) and (TObjProp(pobjprop).bwall) then bwallexists := True;
      [*] = ;         if (not bgateexists) and (TObjProp(pobjprop).bgate) then bgateexists := True;
      [*] = ;         if (not bartdepo) and (TObjProp(pobjprop).bartdepo) then bartdepo := True;
      [*] = ;         if (not bpeasantexists) and (TObjProp(pobjprop).usage=gc_obj_usage_peasant) then bpeasantexists := True;
      [*] = ;         if (not bunbuiltexists) and (not TObj(pobj).bbuilt) then bunbuiltexists := True;
      [*] = ;         {if (not bguardexists) and (_unit_IsGuard(goHnd)) then bguardexists := True;
      [*] = ;
      [*] = ;         var bNonGuardExists : Boolean = _control_IsNonGuardExistsInSelection;
      [*] = ;         if (not bBuildingExists) and (bUnitExists) and (bNonGuardExists) and (_unit_IsGuard(goHnd)) then}
      [*] = ;
      [*] = ;         if (not bmorethenonetype) and (findDrummerAttempts<maxFindDrummerAttempts) then
      [*] = ;         begin
      [*] = ;            if (not bofficerexists) or (not bdrummerexists) then
      [*] = ;            begin
      [*] = ;               var sid : String = GetGameObjectBaseNameByHandle(goHnd);
      [*] = ;               var ind : Integer = _country_GetOfficersIndexByOfficerSID(cid, sid);
      [*] = ;               if (ind>-1) then
      [*] = ;               begin
      [*] = ;                  bofficerexists := True;
      [*] = ;                  var drummerid : Integer = _unit_ConvertObjSIDToID(cid, gCountry[cid].officers[ind].drummersid);
      [*] = ;                  var count : Integer = _unit_FindUnitsAndFillList(GetGameObjectPositionXByHandle(goHnd), GetGameObjectPositionZByHandle(goHnd), gc_gameplay_officersearchradius, cid, drummerid, plHnd, 1, -1, False, False, true, 1, gTmpIntListGUIDrummerList);
      [*] = ;                  findDrummerAttempts := findDrummerAttempts+1;
      [*] = ;                  gTmpIntListGUIDrummerList.Clear;
      [*] = ;                  if (count>0) then
      [*] = ;                  bdrummerexists := True;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         lastcid := cid;
      [*] = ;         lastid := id;
      [*] = ;         lasthnd := goHnd;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_misc_SortList(gTmpIntListGUIInsideList);
      [*] = ;
      [*] = ;for i:=0 to gTmpIntListGUIInsideList.GetCount-1 do
      [*] = ;begin
      [*] = ;   var val : Integer = gTmpIntListGUIInsideList.Get(i);
      [*] = ;   if (val<>0) then
      [*] = ;   for j:=0 to gTmpIntListGUIInsideList.GetCount-1 do
      [*] = ;   begin
      [*] = ;      var tmpval : Integer = gTmpIntListGUIInsideList.Get(j);
      [*] = ;      if (j<>i) and (val=tmpval) and (val<>0) and (tmpval<>0) then
      [*] = ;      begin
      [*] = ;         gTmpIntListGUIInsideList.Set(gTmpIntListGUIInsideList.Get(i)+1000000, i);
      [*] = ;         gTmpIntListGUIInsideList.Set(0, j);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;var k : Integer;
      [*] = ;for k:=gTmpIntListGUIInsideList.GetCount-1 downto 0 do
      [*] = ;if (gTmpIntListGUIInsideList.Get(k)=0) then
      [*] = ;gTmpIntListGUIInsideList.Delete(k);
      [*] = ;
      [*] = ;if (freeGoHnd<>0) then
      [*] = ;goHnd := freeGoHnd
      [*] = ;else
      [*] = ;if (goHnd=0) then
      [*] = ;begin
      [*] = ;   if (freeGoHndTemp<>0) then
      [*] = ;   goHnd := freeGoHndTemp
      [*] = ;   else
      [*] = ;   goHnd := freeGoHndAny;
      [*] = ;end;
      [*] = ;
      [*] = ;_ui_Reset(gInterface, False, True, True, True);
      [*] = ;var bupdate : Boolean = (not gbool_gui_update_unitcontrol);
      [*] = ;
      [*] = ;if (gbool_gui_update_unitcontrol) or (goHnd=0) then
      [*] = ;begin
      [*] = ;   var elmHnd : Integer = GetGUIElementIndexByNameParent(elmname, _gui_GetTop);
      [*] = ;   if (elmHnd<>0) then
      [*] = ;   begin
      [*] = ;      RemoveGUIChildren(elmHnd);
      [*] = ;      SetGUIAllowEvents(elmHnd, False, False, False);
      [*] = ;   end;
      [*] = ;   gbool_gui_updateprogress_unitcontrol := False;
      [*] = ;end
      [*] = ;else
      [*] = ;if (goHnd<>0) then // at this point, we are sure that he is not dead, hp>0 and pobj<>nil
      [*] = ;begin
      [*] = ;   gint_gui_unitcontroluid := GetGameObjectUniqueIdByHandle(goHnd);
      [*] = ;   gbool_gui_updateprogress_unitcontrol := True;
      [*] = ;   var yOff : Integer = cParamMarginTop;
      [*] = ;   var xOff : Integer;
      [*] = ;   if (bunitexists) and (bbuildingexists) then
      [*] = ;   ErrorLog('ShowUnitControl : (bunitexists) and (bbuildingexists)');
      [*] = ;   if (bunitexists) or (bbuildingexists) or (bsquadexists) then
      [*] = ;   begin
      [*] = ;      var elmParent : Integer = _gui_CreateParent(elmname, 0, gc_halLeft, gc_valBottomHeight, 0, -9, GetViewerWidth-cMinimapSizeX, cParentSizeY, bupdate);
      [*] = ;      _gui_AbsScaleByDPI(elmParent);
      [*] = ;
      [*] = ;      SetGUIElementVisible(elmParent, (gInterface.gamemode<>gc_gamemode_mainmenu));
      [*] = ;      var elmParams : Integer = _gui_CreateParent('params', elmParent, gc_halParentLeft, gc_valParentBottomHeight, 0, 0, 209, 142, bupdate);
      [*] = ;
      [*] = ;      var elmInfo : Integer = _gui_CreateImage('panelinfobcg', elmParams, 'unitpanel.leftbackground', gc_halParentLeft, gc_valParentTop, 0, 0, 0, 0, 0, bupdate);
      [*] = ;      var elmControl : Integer = _gui_CreateTileScaleImage('control', elmParams, 'unitpanel.rightbackground', gc_halParentLeft, gc_valParentTop, GetGUIElementWidth(elmInfo), 0, 0, 0, bupdate);
      [*] = ;      SetGUIAllowEvents(elmParent, True, False, False);
      [*] = ;      SetGUIAllowEvents(elmInfo, True, False, False);
      [*] = ;      //SetGUIAllowEvents(elmControl, True, False, False);
      [*] = ;      SetGUIElementCursorByName(elmInfo, 'crDefault');
      [*] = ;      SetGUIElementCursorByName(elmControl, 'crDefault');
      [*] = ;      var controlBtnMaxX : Integer = -1;
      [*] = ;
      [*] = ;      var bsquadunit : Boolean;
      [*] = ;      if (bsquadexists) and (psquad<>nil) then
      [*] = ;      bsquadunit := True;
      [*] = ;
      [*] = ;      var sid : String = GetGameObjectBaseNameByHandle(goHnd);
      [*] = ;      var pobj : Pointer = _unit_GetTObj(goHnd);
      [*] = ;      if (pobj<>nil) then
      [*] = ;      begin
      [*] = ;         var pobjbase : Pointer = gPlayer[TObj(pobj).pl].objbase[TObj(pobj).cid][TObj(pobj).id];
      [*] = ;         var pobjprop : Pointer = gObjProp[TObj(pobj).cid][TObj(pobj).id];
      [*] = ;         var cid : Integer = TObj(pobj).cid;
      [*] = ;         var csid : String;
      [*] = ;         _country_GetSIDByID(cid, csid);
      [*] = ;
      [*] = ;         var sid : String;
      [*] = ;         if (TObjProp(pobjprop).bWall) then
      [*] = ;         _unit_ConvertObjIDToSID(cid, TObj(pobj).id, sid)
      [*] = ;         else
      [*] = ;         sid := GetGameObjectBaseNameByHandle(goHnd);
      [*] = ;
      [*] = ;         var officersid : String;
      [*] = ;         if (not bsquadunit) then
      [*] = ;         officersid := sid
      [*] = ;         else
      [*] = ;         _unit_ConvertObjIDToSID(cid, TSquad(psquad).fOfficerID, officersid);
      [*] = ;
      [*] = ;         var curproduceid : Integer;
      [*] = ;         var curupgsid : String;
      [*] = ;         if (TObjProp(pobjprop).bbuilding) then
      [*] = ;         begin
      [*] = ;            if (TObj(pobj).orders[0].itype=gc_obj_order_type_produce) then
      [*] = ;            curproduceid := TObj(pobj).orders[0].info.produceid;
      [*] = ;            if (TObj(pobj).orders[0].itype=gc_obj_order_type_performupgrade) then
      [*] = ;            begin
      [*] = ;               _country_GetUpgradeSIDByUpgradeID(TObj(pobj).cid, TObj(pobj).orders[0].info.upgradeid, curupgsid);
      [*] = ;               //curupgsid := TObj(pobj).orders[0].info.upgradeid;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var fixedproduceInd : Integer = _country_GetFixedProduceIndexBySID(cid, sid, False);
      [*] = ;
      [*] = ;         var upgplaceind : Integer = _country_GetUpgradePlaceIndexBySID(cid, sid, False);
      [*] = ;
      [*] = ;         gInterface.control.bshowunitslist := bmorethenonetype;
      [*] = ;         gInterface.control.bshowproduce := (not bmorethenonetype) and (fixedproduceInd>=0);
      [*] = ;         gInterface.control.bshowupgrade := (not bmorethenonetype) and (upgplaceind>=0);
      [*] = ;         gInterface.control.bshowcontrol := (not gInterface.control.bshowproduce) or ((bgateexists) and (gSelectedObjects.GetCount=1));
      [*] = ;         gInterface.control.bshowmarket := (TObjProp(pobjprop).bmarket) and (not bmorethenonetype);
      [*] = ;         gInterface.control.bshowuniticon := (not bmorethenonetype);
      [*] = ;         gInterface.control.bshowunitinfo := (TObj(pobj).bbuilt) and (not bmorethenonetype);
      [*] = ;         gInterface.control.bshowinside := (not (bmorethenonetype)) and (babsorberexists);
      [*] = ;
      [*] = ;         gInterface.states.bstandground := bstandground;
      [*] = ;         gInterface.states.bnostandground := bnostandground;
      [*] = ;         gInterface.states.battack := gbool_gui_goinattackmode;
      [*] = ;         gInterface.states.benableattack := bcansearchvictim;
      [*] = ;         gInterface.states.bdisableattack := bnosearchvictim;
      [*] = ;         gInterface.states.bguard := gbool_gui_guardmode;
      [*] = ;         //gInterface.states.bsquadrank := False;
      [*] = ;         //gInterface.states.bsquadcolumn := False;
      [*] = ;         //gInterface.states.bsquadsquare := False;
      [*] = ;         gInterface.states.brally := TObj(pobj).brally;
      [*] = ;
      [*] = ;         var bshowunloadall : Boolean = (not (bmorethenonetype)) and (babsorberexists) and (TObjProp(pobjprop).usage=gc_obj_usage_transport);
      [*] = ;         var bshowartlimits : Boolean = (not (bmorethenonetype)) and (bartdepo);
      [*] = ;         var bArtilleryPreparation : Boolean = (TObjProp(pobjprop).bartprepare);
      [*] = ;
      [*] = ;         var shColor : TColor;
      [*] = ;         var text : String;
      [*] = ;         if (gInterface.control.bshowuniticon) then
      [*] = ;         begin
      [*] = ;            var elmHnd : Integer = _gui_CreateImage('name_background', elmInfo, 'unitpanel.unitname.background', gc_halParentLeft, gc_valParentTop, -16, -48, 0, 0, 0, bupdate);
      [*] = ;            var ttext : String = gc_loc_units+'|'+csid;
      [*] = ;            var textCountry : String;
      [*] = ;            _misc_StringToText(ttext, textCountry);
      [*] = ;            _misc_GetUnitNameBySID(sid, text);
      [*] = ;            text := text+' - '+textCountry;
      [*] = ;            _gui_CreateText('_txt_name', elmHnd, text, gc_halParentLeft, gc_valParentBottomHeight, cNameMarginLeft, -3, 0, 0, gc_halLeft, gc_valTop, cFont, colorBrown, bupdate);
      [*] = ;
      [*] = ;            var icon : String;
      [*] = ;            _misc_GetUnitIconNameByID(cid, TObj(pobj).id, icon);
      [*] = ;
      [*] = ;            elmHnd := _gui_CreateImage('portraitframe', elmParams, 'btn.56x56.frame', gc_halParentLeft, gc_valParentTop, 14, 6+1, 0, 0, 0, bupdate);
      [*] = ;            elmHnd := _gui_CreateImage('_img_icon', elmHnd, icon, gc_halParentLeft, gc_valParentTop, 0, 0, cIconSize, cIconSize, 0, bupdate);
      [*] = ;
      [*] = ;            if (TObj(pobj).hp<gc_gameplay_infinitehp) then
      [*] = ;            begin
      [*] = ;               var width : Integer;
      [*] = ;               var maxwidth : Integer = cIconSize;
      [*] = ;               var maxhp : Integer = TObjBase(pobjbase).maxhp;
      [*] = ;               if (maxhp>0) then
      [*] = ;               begin
      [*] = ;                  width := ClampInt(Round((TObj(pobj).hp/maxhp)*maxwidth), 2, maxwidth);
      [*] = ;                  var meterHnd : Integer = _gui_CreateImage('_meter_hp', elmHnd, gc_gui_material_white, gc_halParentLeft, gc_valParentBottomHeight, 0, 6, width, 4, 0, bupdate);
      [*] = ;                  SetGUIElementUseUserColor(meterHnd, True);
      [*] = ;                  var r, g : Float;
      [*] = ;                  var perc : Float = TObj(pobj).hp/maxhp*1.2 - 0.2;
      [*] = ;                  if (perc>=0.66) then
      [*] = ;                  begin
      [*] = ;                     r := Lerp(1, 0, (perc-0.5)*2);
      [*] = ;                     g := Lerp(1, 1, (perc-0.5)*2);
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     r := Lerp(1, 1, perc*2);
      [*] = ;                     g := Lerp(0, 1, perc*2);
      [*] = ;                  end;
      [*] = ;                  SetGUIElementUserColor(meterHnd, r, g, 0, 1);
      [*] = ;               end;
      [*] = ;               text := IntToStr(TObj(pobj).hp);
      [*] = ;               _gui_CreateText('_txt_name2', elmHnd, text, gc_halParentLeft, gc_valParentBottom, 0, 6, GetGUIElementWidth(elmHnd), 0, gc_halMiddle, gc_valTop, gc_font_serif_13, colorBrown, bupdate);
      [*] = ;            end;
      [*] = ;
      [*] = ;            var count : Integer;
      [*] = ;            if (bsquadunit) then
      [*] = ;            count := _unit_GetSquadUnitCount(psquad)
      [*] = ;            else
      [*] = ;            count := gSelection[cid][TObj(pobj).id].count;
      [*] = ;
      [*] = ;            ttext := IntToStr(count);
      [*] = ;            _gui_CreateText('_txt_name3', elmHnd, ttext, gc_halParentLeft, gc_valParentTop, 2, 0, GetGUIElementWidth(elmHnd), GetGUIElementHeight(elmHnd), gc_halLeft, gc_valTop, cFont, colorWhite, bupdate);
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (gbool_gui_requestsoundonunitcontrol) and (bunbuiltexists) then
      [*] = ;         _sound_PlaySound(gc_sndlib_ind_interface, gc_snd_ind_construct);
      [*] = ;
      [*] = ;         if (TObj(pobj).bbuilt) or (bmorethenonetype) then
      [*] = ;         begin
      [*] = ;            var i : Integer;
      [*] = ;            // weapons
      [*] = ;            if (gInterface.control.bshowunitinfo) then
      [*] = ;            begin
      [*] = ;               var weapInd : Integer;
      [*] = ;               var bCanDoDamage : Boolean;
      [*] = ;               for i:=0 to gc_obj_MaxWeapon-1 do
      [*] = ;               begin
      [*] = ;                  text := '';
      [*] = ;                  if (weapInd<2) and (TObjProp(pobjprop).weapon[i].enabled) and (TObjBase(pobjbase).weapon[i].damage<>0) then
      [*] = ;                  begin
      [*] = ;                     bCanDoDamage := True;
      [*] = ;                     var dmgtxt : String = IntToStr(TObjBase(pobjbase).weapon[i].damage);
      [*] = ;                     var dmgbonus : Integer;
      [*] = ;                     if (bsquadunit) and (TObjProp(pobjprop).weapon[i].kind<>gc_obj_weapon_kind_firearrow) then
      [*] = ;                     begin
      [*] = ;                        //if (weapInd=0) then
      [*] = ;                        //begin
      [*] = ;                           if (TSquad(psquad).fHoldMode) {and (TObjProp(pobjprop).weapon[i].kind<>gc_obj_weapon_kind_bullet)} then
      [*] = ;                           dmgbonus := TSquad(psquad).fAddDamageHold
      [*] = ;                           else
      [*] = ;                           dmgbonus := TSquad(psquad).fAddDamage;
      [*] = ;                           if (dmgbonus<>0) then
      [*] = ;                           dmgtxt := dmgtxt+'+'+IntToStr(dmgbonus);
      [*] = ;                        //end;
      [*] = ;                     end;
      [*] = ;                     WeaponKindToText(TObjProp(pobjprop).weapon[i].kind, text);
      [*] = ;                     //text := cTextDamage+' '+text+': '+dmgtxt;
      [*] = ;                     text := text+': '+dmgtxt;
      [*] = ;                     xOff := weapInd*cParamProtectionRowOffset+cParamProtectionRowOffset+cParamProtectionRowBase+cParamDmgShieldXOff;
      [*] = ;                     var elmHnd : Integer = _gui_CreateImageActive('_img_active_wpn'+IntToStr(i), elmParams, gc_hud_icons_weapon+IntToStr(TObjProp(pobjprop).weapon[i].kind), gc_halParentLeft, gc_valParentTop, xOff, yOff, 0, 0, 0, '', text, bupdate);
      [*] = ;                     _gui_CreateText('_txt_active_wpn'+IntToStr(i), elmHnd, dmgtxt, gc_halParentRight, gc_valParentTop, cParamValueMarginLeft, 0, 0, GetGUIElementHeight(elmHnd), gc_halLeft, gc_valMiddle, cFont, colorBrown, bupdate);
      [*] = ;                     weapInd := weapInd+1;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               // shield
      [*] = ;               var shieldbonus : Integer;
      [*] = ;               var shieldtxt : String = IntToStr(TObjBase(pobjbase).shield);
      [*] = ;               if (bsquadunit) then
      [*] = ;               begin
      [*] = ;                  if (TSquad(psquad).fHoldMode) then
      [*] = ;                  shieldbonus := TSquad(psquad).fAddShieldHold
      [*] = ;                  else
      [*] = ;                  shieldbonus := TSquad(psquad).fAddShield;
      [*] = ;                  if (shieldbonus<>0) then
      [*] = ;                  begin
      [*] = ;                     if (TObjBase(pobjbase).shield=0) then
      [*] = ;                     shieldtxt := '0+'+IntToStr(shieldbonus)
      [*] = ;                     else
      [*] = ;                     shieldtxt := shieldtxt+'+'+IntToStr(shieldbonus);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               //if (TObjBase(pobjbase).shield<>0) or (shieldbonus>0) then
      [*] = ;               begin
      [*] = ;                  text := cTextShield+': '+shieldtxt;
      [*] = ;                  xOff := cParamProtectionRowOffset+cParamProtectionRowBase+cParamDmgShieldXOff;
      [*] = ;                  if ((_misc_GetUnitType(goHnd)<>gc_result_unittype_ship) and (not TObjProp(pobjprop).bbuilding)) or (bCanDoDamage) then
      [*] = ;                  yOff := yOff+(cParamIconSize+cParamIconMargin);
      [*] = ;                  var elmHnd : Integer = _gui_CreateImageActive('_img_active_wpn'+IntToStr(i), elmParams, gc_hud_icons_defence+'0', gc_halParentLeft, gc_valParentTop, xOff, yOff, 0, 0, 0, '', text, bupdate);
      [*] = ;                  //SetGUIElementVisible(elmHnd, (TObjBase(pobjbase).shield<>0) or (shieldbonus>0));
      [*] = ;                  SetGUIElementUserBlend(elmHnd, _misc_SwitchFloat(1, 0.125, ((TObjBase(pobjbase).shield=0) and (shieldbonus=0))));
      [*] = ;                  elmHnd := _gui_CreateText('_txt_active_wpn'+IntToStr(i), elmHnd, shieldtxt, gc_halParentRight, gc_valParentTop, cParamValueMarginLeft, 0, 0, GetGUIElementHeight(elmHnd), gc_halLeft, gc_valMiddle, cFont, colorBrown, bupdate);
      [*] = ;                  SetGUIElementVisible(elmHnd, (TObjBase(pobjbase).shield<>0) or (shieldbonus>0));
      [*] = ;               end;
      [*] = ;
      [*] = ;               //var kill : Integer = TObj(pobj).kill;
      [*] = ;               if (sumkills>0) then
      [*] = ;               begin
      [*] = ;                  text := {cTextKills+': '+}IntToStr(sumkills);
      [*] = ;                  xOff := cParamProtectionRowOffset*2+cParamProtectionRowBase+cParamDmgShieldXOff;
      [*] = ;                  var elmHnd : Integer = _gui_CreateImageActive('_img_kills'+IntToStr(i), elmParams, 'icons.kills', gc_halParentLeft, gc_valParentTop, xOff, yOff, 0, 0, 0, '', cTextKills, bupdate);
      [*] = ;                  _gui_CreateText('_txt_kills'+IntToStr(i), elmHnd, text, gc_halParentRight, gc_valParentTop, cParamValueMarginLeft, 0, 0, 0, gc_halRight, gc_valMiddle, gc_font_serif_12, colorBrown, bupdate);
      [*] = ;                  //_gui_CreateText('_txt_kills'+IntToStr(i), elmHnd, IntToStr(TObj(pobj).kill), gc_halParentRight, gc_valParentTop, cParamValueMarginLeft, 0, 0, GetGUIElementHeight(elmHnd), gc_halLeft, gc_valMiddle, cFont, color, True)
      [*] = ;               end;
      [*] = ;
      [*] = ;               // protection
      [*] = ;               var bProtectionExists : Boolean;
      [*] = ;               var defInd, defType : Integer;
      [*] = ;               for i:=0 to 6-1 do
      [*] = ;               begin
      [*] = ;                  case i of
      [*] = ;                     0 : defType := gc_obj_weapon_kind_sword;
      [*] = ;                     1 : defType := gc_obj_weapon_kind_pike;
      [*] = ;                     2 : defType := gc_obj_weapon_kind_bullet;
      [*] = ;                     3 : defType := gc_obj_weapon_kind_arrow;
      [*] = ;                     4 : defType := gc_obj_weapon_kind_cannonball;
      [*] = ;                     5 : defType := gc_obj_weapon_kind_cannister;
      [*] = ;                  end;
      [*] = ;                  text := '';
      [*] = ;                  //if (TObjBase(pobjbase).protection[defType]>0) then
      [*] = ;                  begin
      [*] = ;                     WeaponKindToText(defType, text);
      [*] = ;                     //text := cTextProtection+' '+text+': '+IntToStr(TObjBase(pobjbase).protection[defType]);
      [*] = ;                     text := GetLocaleTableListItemByID('gui', 'unitpanel.hint.protection.weaponkind.'+IntToStr(i))+': '+IntToStr(TObjBase(pobjbase).protection[defType]);
      [*] = ;                     xOff := (i mod 3)*cParamProtectionRowOffset+cParamProtectionRowBase;
      [*] = ;                     yOff := (cIconSize+cParamIconSize+cParamIconMargin*1)+cParamProtectionMarginHeight+(cParamIconSize+cParamIconMargin)*(i div 3);
      [*] = ;                     var elmHnd : Integer = _gui_CreateImageActive('_img_protection'+IntToStr(defType), elmParams, gc_hud_icons_defence+IntToStr(defType), gc_halParentLeft, gc_valParentTop, xOff, yOff, 0, 0, 0, '', text, bupdate);
      [*] = ;                     SetGUIElementUserBlend(elmHnd, _misc_SwitchFloat(1, 0.125, (TObjBase(pobjbase).protection[defType]<=0)));
      [*] = ;                     SetGUIElementVisible(elmHnd, ((TObjBase(pobjbase).protection[defType]>0) or (not TObjProp(pobjprop).bbuilding)) and (not (gInterface.control.bshowinside)));
      [*] = ;                     var ttext : String = IntToStr(TObjBase(pobjbase).protection[defType]);
      [*] = ;                     elmHnd := _gui_CreateText('_txt_protection'+IntToStr(defType), elmHnd, ttext, gc_halParentRight, gc_valParentTop, cParamValueMarginLeft, 0, 0, GetGUIElementHeight(elmHnd), gc_halLeft, gc_valMiddle, cFont, colorBrown, bupdate);
      [*] = ;                     SetGUIElementVisible(elmHnd, (TObjBase(pobjbase).protection[defType]>0) and (not TObjProp(pobjprop).bbuilding) or (TObjProp(pobjprop).bwall));
      [*] = ;                     defInd := defInd+1;
      [*] = ;                     bProtectionExists := True;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               if (bProtectionExists) then
      [*] = ;               begin
      [*] = ;                  //_gui_CreateText('_txt_protection_exists', elmParams, cTextProtectionAgainst, gc_halParentLeft, gc_valParentTop, 4, 97, 202, 21, gc_halMiddle, gc_valMiddle, cFont, color, bupdate);
      [*] = ;               end;
      [*] = ;
      [*] = ;               // reload meter
      [*] = ;               if (TObjProp(pobjprop).bshowdelay) then
      [*] = ;               begin
      [*] = ;                  if (TObj(pobj).attackmaxdelay>0) then
      [*] = ;                  begin
      [*] = ;                     var maxheight : Integer = 134;
      [*] = ;                     // (GetGameTime-TObj(pobj).lastprogresstime) - needed to show smooth meter change
      [*] = ;                     var height : Integer = ClampInt(Round((TObj(pobj).attackmaxdelay-(TObj(pobj).attackdelay-(GetGameTime-TObj(pobj).lastprogresstime)))/(TObj(pobj).attackmaxdelay)*maxheight), 1, maxheight);
      [*] = ;                     var elmHnd : Integer = _gui_CreateImage('_meter_attackdelay', elmControl{elmInfo}, gc_gui_material_white, gc_halParentLeft, gc_valParentTop, 4, maxheight+4, 4, -height, 0, bupdate);
      [*] = ;                     SetGUIElementUserColor(elmHnd, 0.9, 0.8, 0, 1);
      [*] = ;                     SetGUIElementUseUserColor(elmHnd, True);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            var inside : Integer;
      [*] = ;            if (gInterface.control.bshowinside) then
      [*] = ;            begin
      [*] = ;               // inside
      [*] = ;               // maxinside + upgradeadd
      [*] = ;               // restype
      [*] = ;               xOff := cParamMineMarginWidth;
      [*] = ;               yOff := (cIconSize+cParamIconSize+cParamIconMargin*2)+cParamMineMarginHeight;
      [*] = ;               var maxinside, maxinsideadd : Integer;
      [*] = ;               var restype : Integer;
      [*] = ;
      [*] = ;               var pObjInside : Pointer = _misc_GetObjectArgData(goHnd, gc_argunit_inside);
      [*] = ;               if (pObjInside<>nil) then
      [*] = ;               inside := TIntegerList(pObjInside).GetCount;
      [*] = ;
      [*] = ;               if (TObjProp(pobjprop).peasantabsorber>0) then
      [*] = ;               begin
      [*] = ;                  maxinside := TObjProp(pobjprop).peasantabsorber;
      [*] = ;                  maxinsideadd := TObj(pobj).individual.addpeasantabsorber;
      [*] = ;                  case sid of
      [*] = ;                     gc_basename_minegold : restype := gc_resource_type_gold;
      [*] = ;                     gc_basename_mineiron : restype := gc_resource_type_iron;
      [*] = ;                     gc_basename_minecoal : restype := gc_resource_type_coal;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               //if (TObjBase(pobjbase).transport>0) then
      [*] = ;               begin
      [*] = ;                  maxinside := TObjProp(pobjprop).transport;
      [*] = ;                  maxinsideadd := TObj(pobj).individual.addtransport;
      [*] = ;               end;
      [*] = ;               text := '';
      [*] = ;               if (restype<>gc_resource_type_none) then
      [*] = ;               text := GetLocaleTableListItemByID(gc_loc_gui, 'restype.'+IntToStr(restype));
      [*] = ;               text := text+gc_gui_breakline+cTextInside+': '+IntToStr(inside);
      [*] = ;               text := text+gc_gui_breakline+cTextMaxInside+': '+IntToStr(maxinside);
      [*] = ;               if (maxinsideadd>0) then
      [*] = ;               text := text+'+'+IntToStr(maxinsideadd);
      [*] = ;               _gui_CreateText('_txt_mineinfo', elmParams, text, gc_halParentLeft, gc_valParentTop, xOff, yOff, 0, 0, gc_halLeft, gc_valTop, gc_font_serif_12, colorBrown, bupdate);
      [*] = ;
      [*] = ;               var elmInsiders : Integer = _gui_CreateParent('insiders', elmControl, gc_halParentLeft, gc_valParentTop, 0, 0, GetGUIElementWidth(elmParent), GetGUIElementHeight(elmParent), bupdate);
      [*] = ;               SetGUIElementVisible(elmInsiders, gTmpIntListGUIInsideList.GetCount>0);
      [*] = ;               for i:=0 to gc_MaxCountryCount-1 do
      [*] = ;               begin
      [*] = ;                  var tmpHnd : Integer = GetGUIElementIndexByNameParent('_img_unitinside_key'+IntToStr(i), elmInsiders);
      [*] = ;                  SetGUIElementVisible(tmpHnd, False);
      [*] = ;               end;
      [*] = ;
      [*] = ;               for i:=gTmpIntListGUIInsideList.GetCount-1 downto 0 do
      [*] = ;               begin
      [*] = ;                  var val : Integer = gTmpIntListGUIInsideList.Get(i);
      [*] = ;                  var counter : Integer = (val div 1000000);
      [*] = ;                  var cid : Integer = ((val-1000000*counter) div 100);
      [*] = ;                  var id : Integer = ((val-1000000*counter) mod 100);
      [*] = ;                  counter := counter+1;
      [*] = ;
      [*] = ;                  var x : Integer = i;
      [*] = ;                  var y : Integer;
      [*] = ;                  if (x>cMaxControlBtnCount) then break;
      [*] = ;                  if (x>controlBtnMaxX) then controlBtnMaxX := x;
      [*] = ;                  var elmHnd : Integer = _gui_CreateImage('_img_unitinside_key'+IntToStr(i), elmInsiders, 'btn.56x56.frame', gc_halParentLeft, gc_valParentTop, cControlMarginLeft+x*cIconSize+x*cIconMarginX, cControlMarginTop+y*cIconSize+y*cIconMarginY-1, 0, 0, 0, bupdate);
      [*] = ;                  SetGUIElementVisible(elmHnd, True);
      [*] = ;                  var icon : String = 'noname';
      [*] = ;                  var sid, hint : String;
      [*] = ;                  _misc_GetUnitIconNameByID(cid, id, icon);
      [*] = ;                  elmHnd := _gui_CreateImage('_img_unitinside'+IntToStr(i), elmHnd, icon, gc_halParentLeft, gc_valParentTop, 3, 3, cIconSize, cIconSize, 0, bupdate);
      [*] = ;                  _unit_ConvertObjIDToSID(cid, id, sid);
      [*] = ;                  _misc_GetUnitNameBySID(sid, hint);
      [*] = ;                  var tag : Integer = cBaseTagGoOutside+val;
      [*] = ;                  var btnHnd : Integer = _gui_CreateButton('_btn_unitinside'+IntToStr(i), elmHnd, gc_gui_material_blank, gc_halParentLeft, gc_valParentTop, 0, 0, cIconSize, cIconSize, eventstate, hint, tag, bupdate);
      [*] = ;                  var ttext : String = IntToStr(counter);
      [*] = ;                  _gui_CreateText('_txt_unitinside'+IntToStr(i), btnHnd, ttext, gc_halParentLeft, gc_valParentTop, 2, 0, GetGUIElementWidth(btnHnd), GetGUIElementHeight(btnHnd), gc_halLeft, gc_valTop, cFont, colorWhite, bupdate);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            gTmpIntListGUIInsideList.Clear;
      [*] = ;
      [*] = ;            //var keycolor : String = gc_hud_icons_keycolor+IntToStr(TObj(pobj).pl+1);
      [*] = ;            if (gInterface.control.bshowunitslist) then
      [*] = ;            begin
      [*] = ;               var ind : Integer;
      [*] = ;               if (bsquadexists) then
      [*] = ;               begin
      [*] = ;                  for i:=0 to squadscount-1 do
      [*] = ;                  begin
      [*] = ;                     var ptmpsquad : Pointer = gPlayer[plInd].squads.Get(i);
      [*] = ;                     if (ptmpsquad<>nil) then
      [*] = ;                     begin
      [*] = ;                        if (TSquad(ptmpsquad).fSelected) then
      [*] = ;                        begin
      [*] = ;                           var tmpHnd : Integer = _unit_GetSquadUnit(ptmpsquad);
      [*] = ;                           var ptmpobj : Pointer = _unit_GetTObj(tmpHnd);
      [*] = ;                           if (ptmpobj<>nil) then
      [*] = ;                           begin
      [*] = ;                              var x : Integer = (ind mod cMaxControlBtnCount);
      [*] = ;                              var y : Integer = (ind div cMaxControlBtnCount);
      [*] = ;                              if (x>controlBtnMaxX) then controlBtnMaxX := x;
      [*] = ;                              if (y>1) then break;
      [*] = ;                              var key : Integer = TObj(ptmpobj).pl+1;
      [*] = ;                              var elmHnd : Integer = _gui_CreateImage('_img_unittype_key'+IntToStr(ind), elmControl, 'btn.56x56.frame', gc_halParentLeft, gc_valParentTop, cControlMarginLeft+x*cIconSize+x*cIconMarginX, cControlMarginTop+y*cIconSize+y*cIconMarginY, 0, 0, 0, bupdate);
      [*] = ;                              var icon : String = 'noname';
      [*] = ;                              var sid, hint : String;
      [*] = ;                              _misc_GetUnitIconNameByID(TObj(ptmpobj).cid, TObj(ptmpobj).id, icon);
      [*] = ;                              elmHnd := _gui_CreateImage('_img_unittype'+IntToStr(ind), elmHnd, icon, gc_halParentLeft, gc_valParentTop, 3, 3, cIconSize, cIconSize, 0, bupdate);
      [*] = ;                              _unit_ConvertObjIDToSID(TObj(ptmpobj).cid, TObj(ptmpobj).id, sid);
      [*] = ;                              _misc_GetUnitNameBySID(sid, hint);
      [*] = ;                              var tag : Integer = cBaseTagSelectSquad+i;
      [*] = ;                              var btnHnd : Integer = _gui_CreateButton('_btn_unittype'+IntToStr(ind), elmHnd, gc_gui_material_blank, gc_halParentLeft, gc_valParentTop, 0, 0, cIconSize, cIconSize, eventstate, hint, tag, bupdate);
      [*] = ;                              var ttext : String = IntToStr(_unit_GetSquadUnitCount(ptmpsquad));
      [*] = ;                              _gui_CreateText('_txt_unitcount'+IntToStr(ind), btnHnd, ttext, gc_halParentLeft, gc_valParentTop, 2, 0, GetGUIElementWidth(btnHnd), GetGUIElementHeight(btnHnd), gc_halLeft, gc_valTop, cFont, colorWhite, bupdate);
      [*] = ;                              var shcolor : TColor;
      [*] = ;                              _gui_ConvertHexToTColor(gc_font_hex_color_black, shcolor);
      [*] = ;                              ////elmHnd := _gui_CreateText('_txt_squadindex'+IntToStr(ind), btnHnd, IntToStr(i), gc_halParentLeft, gc_valParentTop, -2, 0, GetGUIElementWidth(btnHnd), GetGUIElementHeight(btnHnd), gc_halRight, gc_valBottom, cFont, color, bupdate);
      [*] = ;                              ttext := IntToStr(i+1);
      [*] = ;                              _gui_CreateTextShadowed('_txt_squadindex'+IntToStr(ind), btnHnd, ttext, gc_halParentLeft, gc_valParentTop, -2, 0, GetGUIElementWidth(btnHnd), GetGUIElementHeight(btnHnd), gc_halRight, gc_valBottom, cFont, colorWhite, 2, 2, shColor, bupdate);
      [*] = ;                              ind := ind+1;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     ErrorLog('ShowUnitControl : ptmpsquad 2');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               for [MAIN]i:=0 to gc_MaxCountryCount-1 do
      [*] = ;               for j:=0 to gc_country_maxmembers-1 do
      [*] = ;               if (gSelection[i][j].id<>0) and (gSelection[i][j].count>0) then
      [*] = ;               begin
      [*] = ;                  var x : Integer = (ind mod cMaxControlBtnCount);
      [*] = ;                  var y : Integer = (ind div cMaxControlBtnCount);
      [*] = ;                  if (x>controlBtnMaxX) then controlBtnMaxX := x;
      [*] = ;                  if (y>1) then break(MAIN);
      [*] = ;                  var key : Integer;
      [*] = ;                  if (gSelection[i][j].bshiftsel) then
      [*] = ;                  key := 5
      [*] = ;                  else
      [*] = ;                  key := TObj(pobj).pl+1;
      [*] = ;                  var elmHnd : Integer = _gui_CreateImage('_img_unittype_key'+IntToStr(ind), elmControl, 'btn.56x56.frame', gc_halParentLeft, gc_valParentTop, cControlMarginLeft+x*cIconSize+x*cIconMarginX, cControlMarginTop+y*cIconSize+y*cIconMarginY, 0, 0, 0, bupdate);
      [*] = ;                  var icon : String = 'noname';
      [*] = ;                  var sid, hint : String;
      [*] = ;                  _misc_GetUnitIconNameByID(i, gSelection[i][j].id, icon);
      [*] = ;                  elmHnd := _gui_CreateImage('_img_unittype'+IntToStr(ind), elmHnd, icon, gc_halParentLeft, gc_valParentTop, 3, 3, cIconSize, cIconSize, 0, bupdate);
      [*] = ;                  _unit_ConvertObjIDToSID(i, gSelection[i][j].id, sid);
      [*] = ;                  _misc_GetUnitNameBySID(sid, hint);
      [*] = ;                  var tag : Integer = cBaseTagSelectUnit+i*100+j;
      [*] = ;                  var btnHnd : Integer = _gui_CreateButton('_btn_unittype'+IntToStr(ind), elmHnd, gc_gui_material_blank, gc_halParentLeft, gc_valParentTop, 0, 0, cIconSize, cIconSize, eventstate, hint, tag, bupdate);
      [*] = ;                  var ttext : String = IntToStr(gSelection[i][j].count);
      [*] = ;                  _gui_CreateText('_txt_unitcount'+IntToStr(ind), btnHnd, ttext, gc_halParentLeft, gc_valParentTop, 2, 0, GetGUIElementWidth(btnHnd), GetGUIElementHeight(btnHnd), gc_halLeft, gc_valTop, cFont, colorWhite, bupdate);
      [*] = ;
      [*] = ;                  ind := ind+1;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if (gbool_gui_requestsoundonunitcontrol) then
      [*] = ;            begin
      [*] = ;               var cid, id : Integer;
      [*] = ;               for cid:=0 to gc_MaxCountryCount-1 do
      [*] = ;               for j:=0 to gc_country_maxmembers-1 do
      [*] = ;               if (gSelection[cid][j].id<>0) and (gSelection[cid][j].count>0) then
      [*] = ;               begin
      [*] = ;                  var id : Integer = gSelection[cid][j].id;
      [*] = ;                  if (gObjProp[cid][id].bbuilding) and gSelection[cid][id].bbuiltexists then
      [*] = ;                  begin
      [*] = ;                     var sid : String = gObjProp[cid][id].sid;
      [*] = ;                     var sndname : String = 'bld'+SubStr(sid, StrLength(sid)-2, 3);
      [*] = ;                     if (sid='turcen') or (sid='algcen') or (sid='turtem') or (sid='algtem') then
      [*] = ;                     sndname := sndname+'tur';
      [*] = ;                     _misc_PlaySound(gc_snd_lib_interface, sndname);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               if (bpeasantexists) then
      [*] = ;               _sound_PlaySound(gc_sndlib_ind_interface, gc_snd_ind_selectpeasant);
      [*] = ;               if (shipscount>0) then
      [*] = ;               _sound_PlaySound(gc_sndlib_ind_interface, gc_snd_ind_selectship);
      [*] = ;            end;
      [*] = ;
      [*] = ;            // market
      [*] = ;            if (gInterface.control.bshowmarket) then
      [*] = ;            begin
      [*] = ;               if (gint_gui_market_sellrestype=gc_resource_type_none) then
      [*] = ;               gint_gui_market_sellrestype := gc_resource_type_food;
      [*] = ;               if (gint_gui_market_buyrestype=gc_resource_type_none) then
      [*] = ;               gint_gui_market_buyrestype := gc_resource_type_food;
      [*] = ;               var bsellvalid : Boolean = (gint_gui_market_sellrestype>gc_resource_type_none);
      [*] = ;               var bbuyvalid : Boolean = (gint_gui_market_buyrestype>gc_resource_type_none);
      [*] = ;               var btradevalid : Boolean = (bsellvalid) and (bbuyvalid);
      [*] = ;               var bnotsameres : Boolean = (gint_gui_market_buyrestype<>gint_gui_market_sellrestype);
      [*] = ;               // res sell
      [*] = ;               var num : Integer;
      [*] = ;               var resInd : Integer;
      [*] = ;               var elmResSellHnd : Integer = _gui_CreateImage('_ressellparent', elmControl, gc_gui_material_blank, gc_halParentLeft, gc_valParentTop, cControlMarginLeft+cIconMarginX, 0, (cIconSize+cIconMarginX-1)*2, 0, 0, bupdate);
      [*] = ;               var font : Integer = gc_font_serif_14;
      [*] = ;               var height : Integer = GetGUIElementFontHeight(gUIConst.font[font])+24;
      [*] = ;               var color, shcolor : TColor;
      [*] = ;               //_gui_ConvertHexToTColor(gc_font_hex_color_white, color);
      [*] = ;               color.r := _gui_ConvertIntColorToFloat(255);
      [*] = ;               color.g := _gui_ConvertIntColorToFloat(225);
      [*] = ;               color.b := _gui_ConvertIntColorToFloat(185);
      [*] = ;               color.a := _gui_ConvertIntColorToFloat(255);
      [*] = ;               //_gui_ConvertHexToTColor(gc_font_hex_color_black, shcolor);
      [*] = ;               _gui_CreateTextShadowed('_txt_ressellparent', elmResSellHnd, cTextMarketSell, gc_halParentLeft, gc_valParentTop, 0, -height, GetGUIElementWidth(elmResSellHnd), height, gc_halMiddle, gc_valMiddle, font, color, 1, 1, shcolor, bupdate);
      [*] = ;               for i:=1 to gc_ResCount-1 do
      [*] = ;               begin
      [*] = ;                  resInd := i;
      [*] = ;                  case i of
      [*] = ;                     1, 2, 3 : begin
      [*] = ;                     end;
      [*] = ;                     4 : resInd := gc_resource_type_iron;
      [*] = ;                     5 : resInd := gc_resource_type_coal;
      [*] = ;                     6 : resInd := gc_resource_type_gold;
      [*] = ;                  end;
      [*] = ;                  var x : Integer = num div 3;
      [*] = ;                  var y : Integer = num mod 3;
      [*] = ;                  if (x>cMaxControlBtnCount) then break;
      [*] = ;                  if (x>controlBtnMaxX) then controlBtnMaxX := x;
      [*] = ;                  var icon : String = gc_hud_icons_res+IntToStr(resInd);
      [*] = ;                  var elmHnd : Integer = _gui_CreateImage('_img_ressell_key'+IntToStr(i), elmControl, 'btn.56x56.frame', gc_halParentLeft, gc_valParentTop, cControlMarginLeft+x*cIconSize+x*cIconMarginX, cControlMarginTop+y*cIconSize+y*cIconMarginY-1, 0, 0, 0, bupdate);
      [*] = ;                  elmHnd := _gui_CreateImage('_img_ressell'+IntToStr(resInd), elmHnd, icon, gc_halParentLeft, gc_valParentTop, 3, 3, cResIconSize, cResIconSize, 0, bupdate);
      [*] = ;                  var tag : Integer = cBaseTagMarketResSell+resInd;
      [*] = ;                  var hint : String = cTextMarketResBase+IntToStr(resInd);
      [*] = ;                  var btnHnd : Integer = _gui_CreateButton('_btn_ressell'+IntToStr(resInd), elmHnd, gc_gui_material_blank, gc_halParentLeft, gc_valParentTop, 0, 0, cResIconSize, cResIconSize, eventstate, hint, tag, bupdate);
      [*] = ;                  var elmtmp : Integer = _gui_CreateImage('_btn_selectionsellmask'+IntToStr(resInd), btnHnd, gc_gui_material_orange, gc_halParentLeft, gc_valParentTop, 0, 0, GetGUIElementWidth(btnHnd), GetGUIElementHeight(btnHnd), 0, bupdate);
      [*] = ;                  SetGUIElementUserBlend(elmtmp, 0.5);
      [*] = ;                  SetGUIElementVisible(elmtmp, (resInd=gint_gui_market_sellrestype));
      [*] = ;                  num := num+1;
      [*] = ;               end;
      [*] = ;               // res buy
      [*] = ;               num := 0;
      [*] = ;               resInd := 0;
      [*] = ;               var elmResBuyHnd : Integer = _gui_CreateImage('_resbuyparent', elmControl, gc_gui_material_blank, gc_halParentLeft, gc_valParentTop, cControlMarginLeft+cIconMarginX+(cIconSize+cIconMarginX-1)*7, 0, (cResIconSize+2)*2, (cResIconSize+2)*3, 0, bupdate);
      [*] = ;               _gui_CreateTextShadowed('_txt_resbuyparent', elmResBuyHnd, cTextMarketBuy, gc_halParentLeft, gc_valParentTop, 0, -height, GetGUIElementWidth(elmResSellHnd), height, gc_halMiddle, gc_valMiddle, font, color, 1, 1, shcolor, bupdate);
      [*] = ;               for i:=1 to gc_ResCount-1 do
      [*] = ;               begin
      [*] = ;                  resInd := i;
      [*] = ;                  case i of
      [*] = ;                     1, 2, 3 : begin
      [*] = ;                     end;
      [*] = ;                     4 : resInd := gc_resource_type_iron;
      [*] = ;                     5 : resInd := gc_resource_type_coal;
      [*] = ;                     6 : resInd := gc_resource_type_gold;
      [*] = ;                  end;
      [*] = ;                  var x : Integer = num div 3+7;
      [*] = ;                  var y : Integer = num mod 3;
      [*] = ;                  if (x>cMaxControlBtnCount) then break;
      [*] = ;                  if (x>controlBtnMaxX) then controlBtnMaxX := x;
      [*] = ;                  var icon : String = gc_hud_icons_res+IntToStr(resInd);
      [*] = ;                  var elmHnd : Integer = _gui_CreateImage('_img_resbuy_key'+IntToStr(resInd), elmControl, 'btn.56x56.frame', gc_halParentLeft, gc_valParentTop, cControlMarginLeft+x*cIconSize+x*cIconMarginX, cControlMarginTop+y*cIconSize+y*cIconMarginY-1, 0, 0, 0, bupdate);
      [*] = ;                  elmHnd := _gui_CreateImage('_img_resbuy'+IntToStr(resInd), elmHnd, icon, gc_halParentLeft, gc_valParentTop, 3, 3, cResIconSize, cResIconSize, 0, bupdate);
      [*] = ;                  var tag : Integer = cBaseTagMarketResBuy+resInd;
      [*] = ;                  var hint : String = cTextMarketResBase+IntToStr(resInd);
      [*] = ;                  var btnHnd : Integer = _gui_CreateButton('_btn_resbuy'+IntToStr(resInd), elmHnd, gc_gui_material_blank, gc_halParentLeft, gc_valParentTop, 0, 0, cResIconSize, cResIconSize, eventstate, hint, tag, bupdate);
      [*] = ;                  var elmtmp : Integer = _gui_CreateImage('_btn_selectionbuymask'+IntToStr(resInd), btnHnd, gc_gui_material_orange, gc_halParentLeft, gc_valParentTop, 0, 0, GetGUIElementWidth(btnHnd), GetGUIElementHeight(btnHnd), 0, bupdate);
      [*] = ;                  SetGUIElementUserBlend(elmtmp, 0.5);
      [*] = ;                  SetGUIElementVisible(elmtmp, (resInd=gint_gui_market_buyrestype));
      [*] = ;                  num := num+1;
      [*] = ;               end;
      [*] = ;               // numbers
      [*] = ;               // values
      [*] = ;               var elmMarketNumbersHnd : Integer = _gui_CreateImage('_marketnumbersparent', elmControl, gc_gui_material_blank, gc_halParentLeft, gc_valParentTop, 0, 0, 0, 0, 0, bupdate);
      [*] = ;               var ttext : String = IntToStr(gint_gui_market_resamount);
      [*] = ;               var elmHnd : Integer = _gui_CreateTextShadowed('_txt_marketnumberssell', elmMarketNumbersHnd, ttext, gc_halParentLeft, gc_valParentTop, cControlMarginLeft+cIconMarginX+(cIconSize+cIconMarginX)*2-1+8, cControlMarginTop+(cIconSize+cIconMarginY)-1, cResIconSize*2, cResIconSize, gc_halMiddle, gc_valMiddle, font, color, 1, 1, shcolor, bupdate);
      [*] = ;               SetGUIElementVisible(elmHnd, bsellvalid);
      [*] = ;               var buycalc : Integer = _res_MarketCalculateBuyAmount(gint_gui_market_sellrestype, gint_gui_market_buyrestype, gint_gui_market_resamount);
      [*] = ;               ttext := IntToStr(buycalc);
      [*] = ;               elmHnd := _gui_CreateTextShadowed('_txt_marketnumbersbuy', elmMarketNumbersHnd, ttext, gc_halParentLeft, gc_valParentTop, cControlMarginLeft+cIconMarginX+(cIconSize+cIconMarginX)*5-1+8, cControlMarginTop+(cIconSize+cIconMarginY)-1, cResIconSize*2, cResIconSize, gc_halMiddle, gc_valMiddle, font, color, 1, 1, shcolor, bupdate);
      [*] = ;               SetGUIElementVisible(elmHnd, (btradevalid and bnotsameres));
      [*] = ;               // buttons
      [*] = ;               for i:=0 to 7 do
      [*] = ;               begin
      [*] = ;                  var x : Integer;
      [*] = ;                  var y : Integer;
      [*] = ;                  case i of
      [*] = ;                     0, 1 : begin
      [*] = ;                        x := 0;
      [*] = ;                        y := 0;
      [*] = ;                     end;
      [*] = ;                     2, 3 : begin
      [*] = ;                        x := 0;
      [*] = ;                        y := 2;
      [*] = ;                     end;
      [*] = ;                     4, 5 : begin
      [*] = ;                        x := 3;
      [*] = ;                        y := 0;
      [*] = ;                     end;
      [*] = ;                     6, 7 : begin
      [*] = ;                        x := 3;
      [*] = ;                        y := 2;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  if ((i mod 2)=0) then
      [*] = ;                  x := x+1;
      [*] = ;                  x := x+2;
      [*] = ;                  if (x>cMaxControlBtnCount) then break;
      [*] = ;                  if (x>controlBtnMaxX) then controlBtnMaxX := x;
      [*] = ;                  var value : Integer = round(pow(10, (i div 2+1)))*(1-2*(i mod 2));
      [*] = ;                  var icon : String = 'icons.market.num.'+IntToStr(value);
      [*] = ;                  var elmHnd : Integer = _gui_CreateImage('_img_marketnumbers_key'+IntToStr(i), elmControl, 'btn.56x56.frame', gc_halParentLeft, gc_valParentTop, cControlMarginLeft+cIconMarginX+(cIconSize+cIconMarginX)*x-1, cControlMarginTop+y*cIconSize+y*cIconMarginY-1, 0, 0, 0, bupdate);
      [*] = ;                  elmHnd := _gui_CreateImage('_img_marketnumbers'+IntToStr(i), elmHnd, icon, gc_halParentLeft, gc_valParentTop, 3, 3, cResIconSize, cResIconSize, 0, bupdate);
      [*] = ;                  var tag : Integer = cBaseTagMarketNumbers+i;
      [*] = ;                  var hint : String;
      [*] = ;                  if (value>0) then
      [*] = ;                  hint := cTextMarketPlusRes
      [*] = ;                  else
      [*] = ;                  hint := cTextMarketMinusRes;
      [*] = ;                  hint := StrReplace(hint, '%amount%', IntToStr(value));
      [*] = ;                  var btnHnd : Integer = _gui_CreateButton('_btn_marketnumbers'+IntToStr(i), elmHnd, gc_gui_material_blank, gc_halParentLeft, gc_valParentTop, 0, 0, cResIconSize, cResIconSize, eventstate, hint, tag, bupdate);
      [*] = ;                  var alpha : Float = _misc_SwitchFloat(0.3, 1, bsellvalid);
      [*] = ;                  SetGUIElementUserBlend(elmHnd, alpha);
      [*] = ;                  SetGUIElementEnabled(btnHnd, bsellvalid);
      [*] = ;               end;
      [*] = ;               // control
      [*] = ;               // accept
      [*] = ;               var elmMarketAccept : Integer = _gui_CreateImage('_img_marketaccept_key'+IntToStr(i), elmControl, 'btn.56x56.frame', gc_halParentLeft, gc_valParentTop, cControlMarginLeft+cIconMarginX+(cIconSize+cIconMarginX)*4-1, cControlMarginTop+(cIconSize+cIconMarginY)*0-1, 0, 0, 0, bupdate);
      [*] = ;               var icon : String = 'icons.market.accept';
      [*] = ;               var x : Integer;
      [*] = ;               var y : Integer;
      [*] = ;               elmHnd := _gui_CreateImage('_img_marketaccept', elmMarketAccept, icon, gc_halParentLeft, gc_valParentTop, 3, 3, cResIconSize, cResIconSize, 0, bupdate);
      [*] = ;               var tag : Integer = cTagMarketAccept;
      [*] = ;               var hint : String = cTextMarketAccept;
      [*] = ;               var btnHnd : Integer = _gui_CreateButton('_btn_marketaccept', elmHnd, gc_gui_material_blank, gc_halParentLeft, gc_valParentTop, 0, 0, cResIconSize, cResIconSize, eventstate, hint, tag, bupdate);
      [*] = ;               var alpha : Float = _misc_SwitchFloat(0.3, 1, (btradevalid and bnotsameres));
      [*] = ;               SetGUIElementUserBlend(elmHnd, alpha);
      [*] = ;               SetGUIElementEnabled(btnHnd, (btradevalid and bnotsameres));
      [*] = ;
      [*] = ;               // reset
      [*] = ;               icon := 'icons.market.clear';
      [*] = ;               x := 0;
      [*] = ;               y := 2;
      [*] = ;               var elmMarketClear : Integer = _gui_CreateImage('_img_marketclear_key'+IntToStr(i), elmControl, 'btn.56x56.frame', gc_halParentLeft, gc_valParentTop, cControlMarginLeft+cIconMarginX+(cIconSize+cIconMarginX)*4-1, cControlMarginTop+(cIconSize+cIconMarginY)*2-1, 0, 0, 0, bupdate);
      [*] = ;               elmHnd := _gui_CreateImage('_img_marketclear', elmMarketClear, icon, gc_halParentLeft, gc_valParentTop, 3, 3, cResIconSize, cResIconSize, 0, bupdate);
      [*] = ;               tag := cTagMarketClear;
      [*] = ;               hint := cTextMarketClear;
      [*] = ;               btnHnd := _gui_CreateButton('_btn_marketclear', elmHnd, gc_gui_material_blank, gc_halParentLeft, gc_valParentTop, 0, 0, cResIconSize, cResIconSize, eventstate, hint, tag, bupdate);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               function CreateControlButton(name : String; x, y : Integer; shint, icon : String; tag : Integer; bVisible, bChecked : Boolean) : Integer;
      [*] = ;               begin
      [*] = ;                  Result := 0;
      [*] = ;                  if (bVisible) and (x>controlBtnMaxX) then controlBtnMaxX := x;
      [*] = ;                  var hint : String = shint;
      [*] = ;                  var hotkey : String = GetRegisterGUIShortcut(name);
      [*] = ;                  if (hotkey<>'') and (not StrExists(hotkey, 'nohotkey')) then
      [*] = ;                  hint := hint+' ('+hotkey+')';
      [*] = ;                  var elmHnd : Integer = _gui_CreateImage('_img_'+name, elmControl, icon, gc_halParentLeft, gc_valParentTop, cControlMarginLeft+x*cIconSize+x*cIconMarginX+3, cControlMarginTop+y*cIconSize+y*cIconMarginY+3, cIconSize, cIconSize, 0, bupdate);
      [*] = ;                  SetGUIElementVisible(elmHnd, bVisible);
      [*] = ;                  Result := _gui_CreateButton('_btn_'+name, elmHnd, gc_gui_material_blank, gc_halParentLeft, gc_valParentTop, 0, 0, cIconSize, cIconSize, eventstate, hint, tag, bupdate);
      [*] = ;                  elmHnd := _gui_CreateImage('_img_checked_'+name, elmHnd, 'icons.control.frame.active.3', gc_halParentLeft, gc_valParentTop, 0, 0, cIconSize, cIconSize, 0, bupdate);
      [*] = ;                  SetGUIElementVisible(elmHnd, bChecked);
      [*] = ;               end;
      [*] = ;
      [*] = ;               // build icons
      [*] = ;               if (gInterface.control.bshowproduce) then
      [*] = ;               begin
      [*] = ;                  for i:=0 to gc_country_fixedproduce_maxcount-1 do
      [*] = ;                  begin
      [*] = ;                     var produceSID : String = gCountry[cid].fixedproduce[fixedproduceInd].build[i].id;
      [*] = ;                     if (produceSID<>'') then
      [*] = ;                     begin
      [*] = ;                        var checkresult : Integer = _player_CheckAccessControlRequirements(plHnd, cid, produceSID);
      [*] = ;                        if (checkresult<>gc_result_checkaccesscontrolreq_notenabled) and (checkresult<>gc_result_checkaccesscontrolreq_lockcount) and (checkresult<>gc_result_checkaccesscontrolreq_hide) then
      [*] = ;                        begin
      [*] = ;                           var id : Integer = _unit_ConvertObjSIDToID(cid, produceSID);
      [*] = ;                           if (not gObjProp[cid][id].bmercenary)
      [*] = ;                           or ((gProfile.purchaseunixtime>0) and (gProfile.purchaseunixtime<=gc_unixtime_earlybirdend))
      [*] = ;                           or ((produceSID<>'archerturdip') and (produceSID<>'lightcavalrydip')) then
      [*] = ;                           begin
      [*] = ;                              if (gint_gui_pickedbldhnd=0) then
      [*] = ;                              gint_gui_pickedbldcid := cid;
      [*] = ;                              var x : Integer = gCountry[cid].fixedproduce[fixedproduceInd].build[i].x;
      [*] = ;                              var y : Integer = gCountry[cid].fixedproduce[fixedproduceInd].build[i].y;
      [*] = ;                              if (x>cMaxControlBtnCount) then break;
      [*] = ;                              if (x>controlBtnMaxX) then controlBtnMaxX := x;
      [*] = ;
      [*] = ;                              // generate hint start
      [*] = ;                              var txtUnitName, txtUnitPrice, txtUnitDescription : String;
      [*] = ;                              _misc_GetUnitNameBySID(produceSID, txtUnitName);
      [*] = ;                              _misc_GetUnitDescriptionBySID(produceSID, txtUnitDescription);
      [*] = ;
      [*] = ;                              if StrExists(txtUnitDescription, '%farm%') then
      [*] = ;                              txtUnitDescription := StrReplace(txtUnitDescription, '%farm%', IntToStr(gObjProp[cid][id].farm));
      [*] = ;
      [*] = ;                              var sidmask : String;
      [*] = ;                              _country_GetUnitSIDMaskBySID(produceSID, cid, sidmask);
      [*] = ;                              var hotkeyhint : String;
      [*] = ;                              var hotkey : String = GetRegisterGUIShortcut('build|'+sidmask);
      [*] = ;                              if (hotkey<>'') and (not StrExists(hotkey, 'nohotkey')) then
      [*] = ;                              hotkeyhint := ' ('+hotkey+')';
      [*] = ;
      [*] = ;                              var bCurProduce : Boolean = (id=curproduceid);
      [*] = ;                              var binsufficient : Boolean;
      [*] = ;                              var food, wood, stone, gold, iron, coal : Integer;
      [*] = ;                              _unit_GetCostByID(cid, id, TObj(pobj).pl, food, wood, stone, gold, iron, coal);
      [*] = ;                              var j : Integer;
      [*] = ;                              for j:=0 to gc_ResCount-1 do
      [*] = ;                              begin
      [*] = ;                                 var value : Integer;
      [*] = ;                                 case j of
      [*] = ;                                    gc_resource_type_food : begin
      [*] = ;                                       value := food;
      [*] = ;                                    end;
      [*] = ;                                    gc_resource_type_wood : value := wood;
      [*] = ;                                    gc_resource_type_stone : value := stone;
      [*] = ;                                    gc_resource_type_gold : value := gold;
      [*] = ;                                    gc_resource_type_iron : value := iron;
      [*] = ;                                    gc_resource_type_coal : value := coal;
      [*] = ;                                 end;
      [*] = ;                                 if (value<>0) then
      [*] = ;                                 begin
      [*] = ;                                    var scolor : String;
      [*] = ;                                    if (value>not gPlayer[TObj(pobj).pl].res[j]) then
      [*] = ;                                    begin
      [*] = ;                                       scolor := gc_font_color_red;
      [*] = ;                                       binsufficient := True;
      [*] = ;                                    end
      [*] = ;                                    else
      [*] = ;                                    scolor := gc_font_color_orange;
      [*] = ;                                    txtUnitPrice := txtUnitPrice+gc_font_color_white+GetLocaleTableListItemByID(gc_loc_gui, 'restype.'+IntToStr(j))+': '+scolor+IntToStr(Value)+'   '+gc_font_color_white;
      [*] = ;                                 end;
      [*] = ;                              end;
      [*] = ;                              if (txtUnitPrice<>'') then
      [*] = ;                              if (gObjProp[cid][id].bBuilding) then
      [*] = ;                              txtUnitPrice := txtUnitPrice+gc_font_color_white+cTextTime+': '+gc_font_color_orange+IntToStr(round(1.06*gc_buildtime_progressperhit*gPlayer[plInd].objbase[cid][id].buildtime/gc_frames_to_time/gc_buildtime_modifier))+'   '+gc_font_color_white
      [*] = ;                              else
      [*] = ;                              begin
      [*] = ;                                 var stime : String = FloatToStr(gPlayer[plInd].objbase[cid][id].buildtime);
      [*] = ;                                 var pos : Integer = StrPos('.', stime);
      [*] = ;                                 if (pos>0) then
      [*] = ;                                 begin
      [*] = ;                                    stime := SubStr(stime, 1, pos+2);
      [*] = ;                                    if (SubStr(stime, StrLength(stime), 1)='0') then
      [*] = ;                                    stime := SubStr(stime, 0, StrLength(stime)-1);
      [*] = ;                                 end;
      [*] = ;                                 txtUnitPrice := txtUnitPrice+gc_font_color_white+cTextTime+': '+gc_font_color_orange+stime+'   '+gc_font_color_white;
      [*] = ;                              end;
      [*] = ;
      [*] = ;                              var mask : String = '%unitname%%hotkey%%unitprice%%unitdescription%';
      [*] = ;                              mask := StrReplace(mask, '%unitname%', gUIConst.fontstyle[gc_font_serif_17]+gc_font_color_white+txtUnitName);
      [*] = ;                              mask := StrReplace(mask, '%hotkey%', hotkeyhint);
      [*] = ;                              mask := StrReplace(mask, '%unitprice%', gc_gui_breakline+gc_gui_breakspace2+gUIConst.fontstyle[gc_font_serif_13]+txtUnitPrice);
      [*] = ;                              const schardef = #151+#32;
      [*] = ;                              const scharpos = #151+#32;
      [*] = ;                              const scharneg = #151+#32;
      [*] = ;                              txtUnitDescription := StrReplace(txtUnitDescription, '%def%', schardef);
      [*] = ;                              txtUnitDescription := StrReplace(txtUnitDescription, '%pos%', scharpos);
      [*] = ;                              txtUnitDescription := StrReplace(txtUnitDescription, '%neg%', scharneg);
      [*] = ;                              if (txtUnitDescription<>'') then
      [*] = ;                              mask := StrReplace(mask, '%unitdescription%', gc_gui_breakline+gc_gui_breakspace3+gUIConst.fontstyle[gc_font_serif_12]+gc_font_color_lightgrey+txtUnitDescription)
      [*] = ;                              else
      [*] = ;                              mask := StrReplace(mask, '%unitdescription%', '');
      [*] = ;                              // generate hint finish
      [*] = ;
      [*] = ;                              var icon : String = 'noname';
      [*] = ;                              _misc_GetUnitIconNameByID(cid, id, icon);
      [*] = ;                              var elmHnd : Integer = _gui_CreateImage('_img_fixedproduce'+IntToStr(i), elmControl, icon, gc_halParentLeft, gc_valParentTop, cControlMarginLeft+x*cIconSize+x*cIconMarginX+3, cControlMarginTop+y*cIconSize+y*cIconMarginY+3, cIconSize, cIconSize, 0, bupdate);
      [*] = ;                              if (checkresult=gc_result_checkaccesscontrolreq_ok) and (binsufficient) then
      [*] = ;                              SetGUIElementUserBlend(elmHnd, cAlphaIconUnsufficientRes)
      [*] = ;                              else
      [*] = ;                              SetGUIElementUserBlend(elmHnd, 1);
      [*] = ;
      [*] = ;                              var elmtmp : Integer;
      [*] = ;                              var bShowProductionElms : Boolean = (arrProduceProgress[i]>0) or (arrProduceInfinite[i]>0) or (arrProduceCount[i]>0);
      [*] = ;                              if (bShowProductionElms) then
      [*] = ;                              begin
      [*] = ;                                 var sizex : Integer = GetGUITextureWidth('icons.progress.meter')+1;
      [*] = ;                                 var progress : Integer = floor(arrProduceProgress[i]*sizex);
      [*] = ;                                 elmtmp := _gui_CreateImage('_i_pf'+IntToStr(i), elmHnd, 'icons.progress.frame', gc_halParentLeft, gc_valParentBottomHeight, 2, -2, 0, 0, 0, bupdate);
      [*] = ;                                 SetGUIElementVisible(elmTmp, (arrProduceProgress[i]>0) and (gObjProp[cid][id].usage<>gc_obj_usage_field));
      [*] = ;                                 _gui_CreateImage('_i_p_bc'+IntToStr(i), elmTmp, 'icons.progress.background', gc_halParentLeft, gc_valParentTop, 1, 1, 0, 0, 0, bupdate);
      [*] = ;                                 elmtmp := _gui_CreateTileScaleImage('_i_p_p'+IntToStr(i), elmTmp, 'icons.progress.meter', gc_halParentLeft, gc_valParentTop, 1, 1, progress, 0, bupdate);
      [*] = ;                                 SetGUIElementVisible(elmTmp, (progress>0));
      [*] = ;
      [*] = ;                                 var color2 : TColor;
      [*] = ;                                 color2.r := 0;
      [*] = ;                                 color2.g := 1;
      [*] = ;                                 color2.b := 0;
      [*] = ;                                 color2.a := 1;
      [*] = ;                                 var color1 : TColor;
      [*] = ;                                 color1.r := 0;
      [*] = ;                                 color1.g := 0;
      [*] = ;                                 color1.b := 0;
      [*] = ;                                 color1.a := 1;
      [*] = ;                                 elmtmp := _gui_CreateImage('_i_i'+IntToStr(i), elmHnd, 'sign.infinity', gc_halParentLeft, gc_valParentTop, 1, 2, 0, 0, 0, bupdate);
      [*] = ;                                 SetGUIElementUserColor(elmtmp, 0, 1, 0, 1);
      [*] = ;                                 SetGUIElementUseUserColor(elmtmp, True);
      [*] = ;                                 SetGUIElementVisible(elmtmp, (arrProduceInfinite[i]>0) and (gObjProp[cid][id].usage<>gc_obj_usage_field));
      [*] = ;                                 var ttext : String = IntToStr(arrProduceInfinite[i]);
      [*] = ;                                 elmtmp := _gui_CreateTextShadowed('_t_i'+IntToStr(i), elmHnd, ttext, gc_halParentLeft, gc_valParentTop, 1, -4, GetGUIElementWidth(elmHnd), GetGUIElementHeight(elmHnd), gc_halLeft, gc_valTop, gc_font_sans_14, color2, 1, 1, color1, bupdate);
      [*] = ;                                 if (arrProduceInfinite[i]>1) then
      [*] = ;                                 begin
      [*] = ;                                    SetGUIElementTextAlign(elmtmp, 'halRight', 'valTop', 3, 0);
      [*] = ;                                    SetGUIElementTextAlign(_gui_GetTextShadowElement(elmtmp), 'halRight', 'valTop', 3, 0);
      [*] = ;                                 end;
      [*] = ;                                 SetGUIElementVisible(elmtmp, (arrProduceInfinite[i]>1));
      [*] = ;                                 SetGUIElementVisible(_gui_GetTextShadowElement(elmtmp), (arrProduceInfinite[i]>1));
      [*] = ;                                 ttext := IntToStr(arrProduceCount[i]);
      [*] = ;                                 elmtmp := _gui_CreateTextShadowed('_t_p'+IntToStr(i), elmHnd, ttext, gc_halParentLeft, gc_valParentTop, 2, -3, GetGUIElementWidth(elmHnd), GetGUIElementHeight(elmHnd), gc_halLeft, gc_valTop, gc_font_sans_14, color2, 1, 1, color1, bupdate);
      [*] = ;                                 SetGUIElementVisible(elmtmp, (arrProduceCount[i]>0) and (arrProduceInfinite[i]=0) and (gObjProp[cid][id].usage<>gc_obj_usage_field));
      [*] = ;                                 SetGUIElementVisible(_gui_GetTextShadowElement(elmtmp), (arrProduceCount[i]>0) and (arrProduceInfinite[i]=0) and (gObjProp[cid][id].usage<>gc_obj_usage_field));
      [*] = ;                              end
      [*] = ;                              else
      [*] = ;                              begin
      [*] = ;                                 var tmp : Integer = GetGUIElementIndexByNameParent('_i_pf'+IntToStr(i), elmHnd);
      [*] = ;                                 if (tmp<>0) then
      [*] = ;                                 RemoveGUIChildren(elmHnd);
      [*] = ;                              end;
      [*] = ;
      [*] = ;                              if (checkresult<>gc_result_checkaccesscontrolreq_ok) then
      [*] = ;                              begin
      [*] = ;                                 var hint : String;
      [*] = ;                                 _misc_PrepareCheckAccessControlRequirementsText(hint, plHnd, cid, produceSID);
      [*] = ;                                 mask := mask+gc_gui_breakline+gc_gui_breakline+hint;
      [*] = ;                              end;
      [*] = ;
      [*] = ;                              var btnHnd : Integer = _gui_CreateButton('_btn_fixedproduce'+IntToStr(i), elmHnd, gc_gui_material_blank, gc_halParentLeft, gc_valParentTop, 0, 0, cIconSize, cIconSize, eventstate, mask, cTagUnit, bupdate);
      [*] = ;                              SetGUIElementStringTag(btnHnd, produceSID);
      [*] = ;
      [*] = ;                              if (gint_gui_pickedbldhnd<>0) and (GetGameObjectBaseNameByHandle(gint_gui_pickedbldhnd)=produceSID) then
      [*] = ;                              elmtmp := _gui_CreateImage('_i_cu_'+IntToStr(i), elmHnd, 'icons.control.frame.active.3', gc_halParentLeft, gc_valParentTop, 0, 0, cIconSize, cIconSize, 0, bupdate)
      [*] = ;                              else
      [*] = ;                              begin
      [*] = ;                                 var tmp : Integer = GetGUIElementIndexByNameParent('_i_cu_'+IntToStr(i), elmHnd);
      [*] = ;                                 if (tmp<>0) then
      [*] = ;                                 RemoveGUIElement(tmp);
      [*] = ;                              end;
      [*] = ;
      [*] = ;                              {elmtmp := _gui_CreateImageActive('_btn_blackmask'+IntToStr(i), elmHnd, gc_gui_material_black, gc_halParentLeft, gc_valParentTop, 0, 0, GetGUIElementWidth(btnHnd), GetGUIElementHeight(btnHnd), 0, '', '', bupdate);
      [*] = ;                              SetGUIElementUserBlend(elmTmp, 0.75);
      [*] = ;                              SetGUIElementVisible(elmtmp, (curupgsid<>''));}
      [*] = ;
      [*] = ;                              //elmtmp := _gui_CreateImageActive('_btn_blackmask'+IntToStr(i), elmHnd, gc_gui_material_black, gc_halParentLeft, gc_valParentTop, 0, 0, GetGUIElementWidth(btnHnd), GetGUIElementHeight(btnHnd), 0, '', hint, bupdate);
      [*] = ;                              if (curupgsid<>'') or (checkresult<>gc_result_checkaccesscontrolreq_ok) then
      [*] = ;                              begin
      [*] = ;                                 elmtmp := _gui_CreateImage('_btn_blackmask'+IntToStr(i), elmHnd, gc_gui_material_black, gc_halParentLeft, gc_valParentTop, 0, 0, GetGUIElementWidth(btnHnd), GetGUIElementHeight(btnHnd), 0, bupdate);
      [*] = ;                                 SetGUIElementUserBlend(elmTmp, cAlphaBlackMaskReqsNotOk);
      [*] = ;                              end
      [*] = ;                              else
      [*] = ;                              begin
      [*] = ;                                 var tmp : Integer = GetGUIElementIndexByNameParent('_btn_blackmask'+IntToStr(i), elmHnd);
      [*] = ;                                 if (tmp<>0) then
      [*] = ;                                 RemoveGUIElement(tmp);
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;                        end
      [*] = ;                        else
      [*] = ;                        if (checkresult=gc_result_checkaccesscontrolreq_lockcount) or (checkresult=gc_result_checkaccesscontrolreq_hide) then
      [*] = ;                        begin
      [*] = ;                           var elmHnd : Integer = GetGUIElementIndexByNameParent('_img_fixedproduce'+IntToStr(i), elmControl);
      [*] = ;                           if (elmHnd<>0) then
      [*] = ;                           RemoveGUIElement(elmHnd);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               if (not bbuildingexists) then
      [*] = ;               begin
      [*] = ;                  if (gInterface.control.bshowcontrol) then
      [*] = ;                  begin
      [*] = ;                     gInterface.buttons.bstandground := bcansearchvictim;
      [*] = ;                     gInterface.buttons.bnostandground := bcansearchvictim;
      [*] = ;                     gInterface.buttons.battack := bcansearchvictim;
      [*] = ;                     gInterface.buttons.benableattack := bcansearchvictim;
      [*] = ;                     gInterface.buttons.bdisableattack := bcansearchvictim;
      [*] = ;                     gInterface.buttons.bguard := (not bsquadexists) and (not bmorethenonetype) and (not bguard) and (shipscount=0);
      [*] = ;                     gInterface.buttons.bcancelguard := (not bsquadexists) and (not bmorethenonetype) and (bguard);
      [*] = ;                     gInterface.buttons.bsquadfill := bsquadexists and (not bmorethenonetype);
      [*] = ;                     gInterface.buttons.bsquaddisband := bsquadexists and (not bmorethenonetype);
      [*] = ;
      [*] = ;                     var bOfficer : Boolean = (bofficerexists);
      [*] = ;                     var bShowAvailableSquads : Boolean = (not bsquadexists) and bOfficer and (bdrummerexists) and (gint_gui_officer_selectedformation<>-1);
      [*] = ;                     if (GetGameObjectUniqueIdByHandle(goHnd)<>gint_gui_prevshowunitcontrolunituid) then
      [*] = ;                     begin
      [*] = ;                        gint_gui_officer_selectedformation := -1;
      [*] = ;                        gint_gui_officer_formationsizedecrease := 0;
      [*] = ;                     end;
      [*] = ;                     if ((bsquadunit) and (not bmorethenonetype)) or ((not bsquadexists) and (bOfficer) and (not bmorethenonetype) and (bdrummerexists)) then
      [*] = ;                     begin
      [*] = ;                        if (bsquadunit) or (gint_gui_officer_selectedformation>-1) then
      [*] = ;                        begin
      [*] = ;                           var ind : Integer = _country_GetOfficersIndexByOfficerSID(cid, officersid);
      [*] = ;                           if (ind>-1) then
      [*] = ;                           begin
      [*] = ;                              for i:=0 to gc_country_maxformationcount-1 do
      [*] = ;                              begin
      [*] = ;                                 //gCountry[cid].officers[ind].formations[i].stype;
      [*] = ;                                 for j:=0 to gc_country_maxofficersformationmask-1 do
      [*] = ;                                 begin
      [*] = ;                                    if (gCountry[cid].officers[ind].formations[i].masks[j]<>'') then
      [*] = ;                                    begin
      [*] = ;                                       var maskid : Integer = _misc_GetFormationIndexBySID(gCountry[cid].officers[ind].formations[i].masks[j]);
      [*] = ;                                       for k:=0 to gc_country_maxformationunitcount-1 do
      [*] = ;                                       arrOfficerFormation[i].units[k].count[j] := gFormation[maskid].countunits;
      [*] = ;                                    end;
      [*] = ;                                 end;
      [*] = ;                              end;
      [*] = ;                              if (not bsquadunit) then
      [*] = ;                              begin
      [*] = ;                                 var px : Float = GetGameObjectPositionXByHandle(goHnd);
      [*] = ;                                 var py : Float = GetGameObjectPositionZByHandle(goHnd);
      [*] = ;                                 _unit_FindUnitsAndFillList(px, py, gc_gameplay_officersearchradius, cid, -1, plHnd, 0, -1, False, False, False, 1, gIntegerList);
      [*] = ;                                 var i : Integer;
      [*] = ;                                 for i:=gIntegerList.GetCount-1 downto 0 do
      [*] = ;                                 begin
      [*] = ;                                    var tmpHnd : Integer = gIntegerList.Get(i);
      [*] = ;                                    var pobj : Pointer = _unit_GetTObj(tmpHnd);
      [*] = ;                                    for j:=0 to gc_country_maxformationunitcount-1 do
      [*] = ;                                    begin
      [*] = ;                                       var id : Integer = _unit_ConvertObjSIDToID(cid, gCountry[cid].officers[ind].units[j]);
      [*] = ;                                       if (TObj(pobj).id=id) and (TObj(pobj).cid=cid) then
      [*] = ;                                       begin
      [*] = ;                                          arrOfficerUnitsCount[j] := arrOfficerUnitsCount[j]+1;
      [*] = ;                                          break;
      [*] = ;                                       end;
      [*] = ;                                    end;
      [*] = ;                                 end;
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                     var btnHnd, elmHnd : Integer;
      [*] = ;                     btnHnd := CreateControlButton('unit|standground', 1, 2, cTextHoldPosition, gc_hud_icons_control+'holdposition', cTagControlHoldPosition, gInterface.buttons.bstandground, bstandground);
      [*] = ;                     var width : Integer = GetGUIElementWidth(btnHnd);
      [*] = ;                     var bvisible : Boolean;
      [*] = ;                     if (bsquadunit) then
      [*] = ;                     begin
      [*] = ;                        if (TSquad(psquad).fHoldModeProgress>0) then
      [*] = ;                        begin
      [*] = ;                           width := _misc_RoundUp(width*TSquad(psquad).fHoldModeProgress);
      [*] = ;                           bvisible := True;
      [*] = ;                        end
      [*] = ;                        else
      [*] = ;                        if (TSquad(psquad).fHoldMode) then
      [*] = ;                        bvisible := True;
      [*] = ;                     end;
      [*] = ;                     elmHnd := _gui_CreateImage('holdprogress', btnHnd, gc_gui_material_white, gc_halParentLeft, gc_valParentBottomHeight, 0, 0, width, 4, 0, bupdate);
      [*] = ;                     SetGUIElementVisible(elmHnd, bvisible);
      [*] = ;
      [*] = ;                     CreateControlButton('unit|nostandground', 2, 2, cTextCancelHoldPosition, gc_hud_icons_control+'freeposition', cTagControlCancelHoldPosition, gInterface.buttons.bnostandground, bnostandground);
      [*] = ;                     CreateControlButton('unit|attack', 3, 2, cTextGoWithAttack, gc_hud_icons_control+'gowithattack', cTagControlGoWithAttack, gInterface.buttons.battack, gbool_gui_goinattackmode);
      [*] = ;                     CreateControlButton('unit|enableattack', 4, 2, cTextEnableAttack, gc_hud_icons_control+'enableattack', cTagControlEnableAttack, gInterface.buttons.benableattack, bsearchvictim);
      [*] = ;                     CreateControlButton('unit|disableattack', 5, 2, cTextDisableAttack, gc_hud_icons_control+'disableattack', cTagControlDisableAttack, gInterface.buttons.bdisableattack, bnosearchvictim);
      [*] = ;                     CreateControlButton('unit|patrol', 2, 1, cTextPatrol, gc_hud_icons_control+'patrol', cTagControlPatrol, (not bsquadexists), False);
      [*] = ;                     CreateControlButton('unit|guard', 1, 1, cTextGuard, gc_hud_icons_control+'guard', cTagControlGuard, gInterface.buttons.bguard, gbool_gui_guardmode);
      [*] = ;                     CreateControlButton('unit|cancelguard', 1, 1, cTextCancelGuard, gc_hud_icons_control+'disableattack', cTagControlCancelGuard, gInterface.buttons.bcancelguard, False);
      [*] = ;                     CreateControlButton('squad|fill', 0, 1, cTextSquadFill, gc_hud_icons_control+'fillformation', cTagControlSquadFill, gInterface.buttons.bsquadfill, False);
      [*] = ;                     CreateControlButton('squad|disband', 0, 2, cTextSquadDisband, gc_hud_icons_control+'dismissformation', cTagControlSquadDisband, gInterface.buttons.bsquaddisband, False);
      [*] = ;                     //hidded, dont want to program it
      [*] = ;                     ////CreateControlButton('GroupFormations', 2, 1, cTextGroupFormations, gc_hud_icons_control+'groupformations', cTagControlSquadGroups, bsquadexists and (not bmorethenonetype), False);
      [*] = ;                     btnHnd := CreateControlButton('OfficerDecreaseSize', 4, 1, cTextOfficerDecreaseSize, gc_hud_icons_control+'decreaseformationsize', cTagControlOfficerDecreaseSize, (bOfficer and bShowAvailableSquads and (not bmorethenonetype) and (gint_gui_officer_formationsizedecreasemax>0)), False);
      [*] = ;                     elmHnd := GetGUIElementParentByIndex(btnHnd);
      [*] = ;                     if (gint_gui_officer_formationsizedecrease>=gint_gui_officer_formationsizedecreasemax) or (gint_gui_officer_formationsizedecreasemax=0) then
      [*] = ;                     begin
      [*] = ;                        SetGUIElementUserBlend(elmHnd, 0.3);
      [*] = ;                        SetGUIElementHint(btnHnd, '');
      [*] = ;                        SetGUIElementEnabled(btnHnd, False);
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     SetGUIElementUserBlend(elmHnd, 1);
      [*] = ;                     btnHnd := CreateControlButton('OfficerIncreaseSize', 5, 1, cTextOfficerIncreaseSize, gc_hud_icons_control+'increaseformationsize', cTagControlOfficerIncreaseSize, (bOfficer and bShowAvailableSquads and (not bmorethenonetype) and (gint_gui_officer_formationsizedecreasemax>0)), False);
      [*] = ;                     elmHnd := GetGUIElementParentByIndex(btnHnd);
      [*] = ;                     if (gint_gui_officer_formationsizedecrease<=0) or (gint_gui_officer_formationsizedecreasemax=0) then
      [*] = ;                     begin
      [*] = ;                        SetGUIElementUserBlend(elmHnd, 0.3);
      [*] = ;                        SetGUIElementHint(btnHnd, '');
      [*] = ;                        SetGUIElementEnabled(btnHnd, False);
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     SetGUIElementUserBlend(elmHnd, 1);
      [*] = ;
      [*] = ;                     CreateControlButton('unit|attackpoint', 0, 1, cTextArtilleryPreparation, gc_hud_icons_control+'artillerypreparation', cTagControlArtilleryPreparation, (bArtilleryPreparation and (not bmorethenonetype)), False);
      [*] = ;                     btnHnd := CreateControlButton('unit|unloadall', 0, 2, cTextUnloadAll, gc_hud_icons_control+'ferryunloadall', cTagControlUnloadAll, bshowunloadall, False);
      [*] = ;                     elmHnd := GetGUIElementParentByIndex(btnHnd);
      [*] = ;
      [*] = ;                     if (TObj(pobj).brally) and (gObjProp[TObj(pobj).cid][TObj(pobj).id].usage=gc_obj_usage_transport) and (inside>0) then
      [*] = ;                     SetGUIElementUserBlend(elmHnd, 1)
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        SetGUIElementUserBlend(elmHnd, 0.3);
      [*] = ;                        SetGUIElementHint(btnHnd, '');
      [*] = ;                        SetGUIElementEnabled(btnHnd, False);
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     if (bsquadunit) then
      [*] = ;                     begin
      [*] = ;                        var formmaskindmax : Integer;
      [*] = ;                        var formmaskind : Integer = -1;
      [*] = ;                        //trying to fix cavalry formations
      [*] = ;                        var bcavalry : Boolean = False;
      [*] = ;                        if ( _unit_GetUsage(goHnd)=gc_obj_usage_fasthorse) or ( _unit_GetUsage(goHnd)=gc_obj_usage_hardhorse) or ( _unit_GetUsage(goHnd)=gc_obj_usage_horseshooter) then
      [*] = ;                        bcavalry := True;
      [*] = ;                        for i:=0 to 2 do
      [*] = ;                        begin
      [*] = ;                           gInterface.buttons.bsquadrank := (bsquadexists or bOfficer) and (not bmorethenonetype);
      [*] = ;                           gInterface.buttons.bsquadcolumn := (bsquadexists or bOfficer) and (not bmorethenonetype) and (not TObjProp(pobjprop).bartillery);
      [*] = ;                           gInterface.buttons.bsquadsquare := (bsquadexists or bOfficer) and (not bmorethenonetype) and (not TObjProp(pobjprop).bartillery);
      [*] = ;                           case i of
      [*] = ;                              0 : btnHnd := CreateControlButton('squad|rank', 6, 0, cTextSquadFormLine, gc_hud_icons_control+'lineformation', cTagControlSquadFormLine, gInterface.buttons.bsquadrank, False);
      [*] = ;                              1 : btnHnd := CreateControlButton('squad|column', 6, 1, cTextSquadFormColumn, gc_hud_icons_control+'columnformation', cTagControlSquadFormColumn, gInterface.buttons.bsquadcolumn, False);
      [*] = ;                              2 : btnHnd := CreateControlButton('squad|square', 6, 2, cTextSquadFormSquare, gc_hud_icons_control+'squareformation', cTagControlSquadFormSquare, gInterface.buttons.bsquadsquare, False);
      [*] = ;                           end;
      [*] = ;                           //cavalry fix working
      [*] = ;                           if (bCavalry) then
      [*] = ;                           case i of
      [*] = ;                              0 : btnHnd := CreateControlButton('squad|rank', 6, 2, cTextSquadFormSquare, gc_hud_icons_control+'squareformation', cTagControlSquadFormLine, gInterface.buttons.bsquadrank, False);
      [*] = ;                              1 : btnHnd := CreateControlButton('squad|column', 6, 1, cTextCavSquadFormWedge, gc_hud_icons_control+'columnformation', cTagControlSquadFormColumn, gInterface.buttons.bsquadcolumn, False);
      [*] = ;                              2 : btnHnd := CreateControlButton('squad|square', 6, 0, cTextCavSquadFormLine, gc_hud_icons_control+'lineformation', cTagControlSquadFormSquare, gInterface.buttons.bsquadsquare, False);
      [*] = ;                           end;
      [*] = ;                           for j:=0 to gc_country_maxformationunitcount-1 do
      [*] = ;                           begin
      [*] = ;                              var k : Integer;
      [*] = ;                              for k:=0 to gc_country_maxofficersformationmask-1 do
      [*] = ;                              begin
      [*] = ;                                 if (arrOfficerFormation[i].units[j].count[k]>0) then
      [*] = ;                                 if (TSquad(psquad).fBaseCount>=arrOfficerFormation[i].units[j].count[k]) then
      [*] = ;                                 formmaskind := k;
      [*] = ;                              end;
      [*] = ;
      [*] = ;                              if (formmaskind>formmaskindmax) then
      [*] = ;                              formmaskindmax := formmaskind;
      [*] = ;                              var formmaskshowind : Integer = formmaskind;
      [*] = ;                              if (formmaskshowind>=0) then
      [*] = ;                              formmaskshowind := formmaskshowind-gint_gui_officer_formationsizedecrease;
      [*] = ;                              if (formmaskshowind<0) and (formmaskind>=0) then
      [*] = ;                              formmaskshowind := 0;
      [*] = ;                              var ind : Integer = _country_GetOfficersIndexByOfficerSID(cid, officersid);
      [*] = ;                              if (ind>-1) then
      [*] = ;                              begin
      [*] = ;                                 if (gCountry[cid].officers[ind].formations[i].masks[j]<>'') then
      [*] = ;                                 begin
      [*] = ;                                    var stag : String = gCountry[cid].officers[ind].units[j];
      [*] = ;                                    if (formmaskshowind>=0) then
      [*] = ;                                    stag := stag+gc_gui_delimitercharstr+gCountry[cid].officers[ind].formations[i].masks[formmaskshowind];
      [*] = ;                                    SetGUIElementStringTag(btnHnd, stag);
      [*] = ;                                 end;
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     for i:=0 to 2 do
      [*] = ;                     begin
      [*] = ;                        gInterface.buttons.bsquadrank := (bsquadexists or bOfficer) and (not bmorethenonetype);
      [*] = ;                        var bcavalry : Boolean = False;
      [*] = ;                        if ( _unit_GetUsage(goHnd)=gc_obj_usage_fasthorse) or ( _unit_GetUsage(goHnd)=gc_obj_usage_hardhorse) or ( _unit_GetUsage(goHnd)=gc_obj_usage_horseshooter) then
      [*] = ;                        bcavalry := True;
      [*] = ;                        if (i=0) or (not TObjProp(pobjprop).bartillery) then
      [*] = ;                        begin
      [*] = ;                           gInterface.buttons.bsquadcolumn := (bsquadexists or bOfficer) and (not bmorethenonetype);
      [*] = ;                           gInterface.buttons.bsquadsquare := (bsquadexists or bOfficer) and (not bmorethenonetype);
      [*] = ;                           case i of
      [*] = ;                              0 : btnHnd := CreateControlButton('squad|rank', 6, 0, cTextSquadFormLine, gc_hud_icons_control+'lineformation', cTagControlSquadFormLine, gInterface.buttons.bsquadrank, False);
      [*] = ;                              1 : btnHnd := CreateControlButton('squad|column', 6, 1, cTextSquadFormColumn, gc_hud_icons_control+'columnformation', cTagControlSquadFormColumn, gInterface.buttons.bsquadcolumn, False);
      [*] = ;                              2 : btnHnd := CreateControlButton('squad|square', 6, 2, cTextSquadFormSquare, gc_hud_icons_control+'squareformation', cTagControlSquadFormSquare, gInterface.buttons.bsquadsquare, False);
      [*] = ;                           end;
      [*] = ;                           //cavalry fix
      [*] = ;                           if (bCavalry) then
      [*] = ;                           case i of
      [*] = ;                              0 : btnHnd := CreateControlButton('squad|rank', 6, 2, cTextSquadFormSquare, gc_hud_icons_control+'squareformation', cTagControlSquadFormSquare, gInterface.buttons.bsquadsquare, False);
      [*] = ;                              1 : btnHnd := CreateControlButton('squad|column', 6, 1, cTextCavSquadFormWedge, gc_hud_icons_control+'columnformation', cTagControlSquadFormColumn, gInterface.buttons.bsquadcolumn, False);
      [*] = ;                              2 : btnHnd := CreateControlButton('squad|square', 6, 0, cTextCavSquadFormLine, gc_hud_icons_control+'lineformation', cTagControlSquadFormLine, gInterface.buttons.bsquadrank, False);
      [*] = ;                           end;
      [*] = ;                           if (not (bsquadexists or bdrummerexists)) then
      [*] = ;                           begin
      [*] = ;                              //SetGUIElementHint(btnHnd, 'ACHTUNG');
      [*] = ;                              SetGUIElementEnabled(btnHnd, False);
      [*] = ;                              SetGUIElementUserBlend(btnHnd, 0.5);
      [*] = ;                           end;
      [*] = ;                           var elmtmp : Integer = _gui_CreateImageActive('_btn_controlblackmask'+IntToStr(0), btnHnd, gc_gui_material_black, gc_halParentLeft, gc_valParentTop, 0, 0, GetGUIElementWidth(btnHnd), GetGUIElementHeight(btnHnd), 0, '', cTextRequireDrummer, bupdate);
      [*] = ;                           SetGUIElementVisible(elmtmp, (not (bsquadexists or bdrummerexists)));
      [*] = ;
      [*] = ;                           var ind : Integer = _country_GetOfficersIndexByOfficerSID(cid, officersid);
      [*] = ;                           if (ind>-1) then
      [*] = ;                           begin
      [*] = ;                              var enum : Integer;
      [*] = ;                              var formmaskindmax : Integer;
      [*] = ;                              for j:=0 to gc_country_maxformationunitcount-1 do
      [*] = ;                              begin
      [*] = ;                                 if (gCountry[cid].officers[ind].units[j]<>'') then
      [*] = ;                                 begin
      [*] = ;                                    var bVisible : Boolean = (i=gint_gui_officer_selectedformation) and (bdrummerexists);
      [*] = ;
      [*] = ;                                    var x : Integer;
      [*] = ;                                    var y : Integer;
      [*] = ;                                    if (GetViewerWidth<1152) then // low screen resoulution won't allow us to show all icons, so we use other positioning in that case_
      [*] = ;                                    begin
      [*] = ;                                       x := 7-enum-2;
      [*] = ;                                       y := 0;
      [*] = ;                                    end
      [*] = ;                                    else
      [*] = ;                                    begin
      [*] = ;                                       x := 7+enum;
      [*] = ;                                       if (bCavalry) then
      [*] = ;                                       y := 2-i
      [*] = ;                                       else
      [*] = ;                                       y := i;
      [*] = ;                                    end;
      [*] = ;                                    if (x>cMaxControlBtnCount) then break;
      [*] = ;                                    if ((bVisible) and (x>controlBtnMaxX)) then controlBtnMaxX := x;
      [*] = ;                                    ////var elmHnd : Integer = _gui_CreateImage('_img_'+name+'_key', elmControl, keycolor, gc_halParentLeft, gc_valParentTop, cControlMarginLeft+cIconMargin+x*cControlIconSize+x*cIconMargin-1, y*cControlIconSize+y*cIconMargin-1, cControlIconSize+2, cControlIconSize+2, 0, bupdate);
      [*] = ;                                    var elmHnd : Integer = _gui_CreateImage('_img_fixedproduce_key'+IntToStr(i)+'_'+IntToStr(j), elmControl, 'btn.56x56.frame', gc_halParentLeft, gc_valParentTop, cControlMarginLeft+x*cIconSize+x*cIconMarginX, cControlMarginTop+y*cIconSize+y*cIconMarginY, 0, 0, 0, bupdate);
      [*] = ;                                    var formmaskind : Integer = -1;
      [*] = ;                                    var k : Integer;
      [*] = ;                                    for k:=0 to gc_country_maxofficersformationmask-1 do
      [*] = ;                                    begin
      [*] = ;                                       if (arrOfficerFormation[i].units[j].count[k]>0) then
      [*] = ;                                       if (arrOfficerUnitsCount[j]>=arrOfficerFormation[i].units[j].count[k]) then
      [*] = ;                                       formmaskind := k;
      [*] = ;                                    end;
      [*] = ;                                    if (formmaskind>formmaskindmax) then
      [*] = ;                                    formmaskindmax := formmaskind;
      [*] = ;                                    var formmaskshowind : Integer = formmaskind;
      [*] = ;                                    if (formmaskshowind>=0) then
      [*] = ;                                    formmaskshowind := formmaskshowind-gint_gui_officer_formationsizedecrease;
      [*] = ;                                    if (formmaskshowind<0) and (formmaskind>=0) then
      [*] = ;                                    formmaskshowind := 0;
      [*] = ;                                    var binsufficient : Boolean = (formmaskshowind<0);
      [*] = ;                                    SetGUIElementUserBlend(elmHnd, _misc_SwitchFloat(1, 0.25, binsufficient));
      [*] = ;                                    SetGUIElementVisible(elmHnd, bVisible);
      [*] = ;                                    var icon : String;
      [*] = ;                                    _misc_GetUnitIconNameBySID(gCountry[cid].officers[ind].units[j], icon);
      [*] = ;                                    elmHnd := _gui_CreateImage('_img_fixedproduce'+IntToStr(i), elmHnd, icon, gc_halParentLeft, gc_valParentTop, 3, 3, cIconSize, cIconSize, 0, bupdate);
      [*] = ;
      [*] = ;                                    var txtName : String;
      [*] = ;                                    _misc_GetUnitNameBySID(gCountry[cid].officers[ind].units[j], txtName);
      [*] = ;
      [*] = ;                                    var btnHnd : Integer = _gui_CreateButton('_btn_officersunits'+IntToStr(i), elmHnd, gc_gui_material_blank, gc_halParentLeft, gc_valParentTop, 0, 0, cIconSize, cIconSize, eventstate, txtName, cTagControlSquadFormationUnit, bupdate);
      [*] = ;
      [*] = ;                                    var stag : String = gCountry[cid].officers[ind].units[j];
      [*] = ;                                    if (formmaskshowind>=0) then
      [*] = ;                                    stag := stag+gc_gui_delimitercharstr+gCountry[cid].officers[ind].formations[i].masks[formmaskshowind];
      [*] = ;                                    SetGUIElementStringTag(btnHnd, stag);
      [*] = ;
      [*] = ;                                    if (binsufficient) then
      [*] = ;                                    SetGUIElementEnabled(btnHnd, False);
      [*] = ;
      [*] = ;                                    //elmtmp := _gui_CreateImageActive('_btn_officersunitsblackmask'+IntToStr(i), btnHnd, gc_gui_material_black, gc_halParentLeft, gc_valParentTop, 0, 0, GetGUIElementWidth(btnHnd), GetGUIElementHeight(btnHnd), 0, '', cTextRequireMoreUnitsToFormation, bupdate);
      [*] = ;                                    //SetGUIElementUserBlend(elmTmp, 0.6);
      [*] = ;                                    //SetGUIElementVisible(elmtmp, binsufficient);
      [*] = ;
      [*] = ;                                    var scount : String;
      [*] = ;                                    if (formmaskshowind>=0) then
      [*] = ;                                    scount := IntToStr(arrOfficerFormation[i].units[j].count[formmaskshowind]);
      [*] = ;                                    _gui_CreateText('_txt_officersunits'+IntToStr(i)+'_'+IntToStr(j), btnHnd, scount, gc_halParentLeft, gc_valParentTop, 2, 0, GetGUIElementWidth(elmHnd), GetGUIElementHeight(elmHnd), gc_halLeft, gc_valTop, gc_font_sans_14, colorWhite, bupdate);
      [*] = ;                                    enum := enum+1;
      [*] = ;                                 end;
      [*] = ;                              end;
      [*] = ;                              gint_gui_officer_formationsizedecreasemax := formmaskindmax;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               //if (bbuildingexists) then
      [*] = ;               begin
      [*] = ;                  if (gInterface.control.bshowcontrol) and (not bmorethenonetype) then
      [*] = ;                  begin
      [*] = ;                     if (bgateexists) then
      [*] = ;                     begin
      [*] = ;                        var bClosed : Boolean = _unit_GetTagStateByType(goHnd, gc_statetag_visual)=gc_statetag_visual_none;
      [*] = ;                        //if (bClosed) then
      [*] = ;                        CreateControlButton('unit|opengate', 0, 0, GetLocaleTableListItemByID('misc', 'unitcontrol.gateopen'), gc_hud_icons_control+'gateopen', cTagControlOpenGate, True, not bClosed);
      [*] = ;                        //else
      [*] = ;                        CreateControlButton('unit|closegate', 1, 0, GetLocaleTableListItemByID('misc', 'unitcontrol.gateclose'), gc_hud_icons_control+'gateclose', cTagControlCloseGate, True, bClosed);
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     gInterface.buttons.benableattack := bcansearchvictim;
      [*] = ;                     gInterface.buttons.bdisableattack := bcansearchvictim;
      [*] = ;
      [*] = ;                     CreateControlButton('unit|attackpoint', 0, 1, cTextArtilleryPreparation, gc_hud_icons_control+'artillerypreparation', cTagControlArtilleryPreparation, (bArtilleryPreparation and (not bmorethenonetype)), False);
      [*] = ;                     CreateControlButton('unit|enableattack', 4, 2, cTextEnableAttack, gc_hud_icons_control+'enableattack', cTagControlEnableAttack, gInterface.buttons.benableattack, bsearchvictim);
      [*] = ;                     CreateControlButton('unit|disableattack', 5, 2, cTextDisableAttack, gc_hud_icons_control+'disableattack', cTagControlDisableAttack, gInterface.buttons.bdisableattack, bnosearchvictim);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               if (not gInterface.control.bshowunitslist) then
      [*] = ;               begin
      [*] = ;                  // rally point
      [*] = ;                  {if (TObjProp(pobjprop).bcansetrally) then
      [*] = ;                  begin
      [*] = ;                     gInterface.buttons.brally := True;
      [*] = ;                     const cRallyX = 6;
      [*] = ;                     const cRallyY = 2;
      [*] = ;                     if (cRallyX>controlBtnMaxX) then controlBtnMaxX := cRallyX;
      [*] = ;                     var elmHnd : Integer = _gui_CreateImage('_img_rally_key', elmControl, 'btn.56x56.frame', gc_halParentLeft, gc_valParentTop, cControlMarginLeft+cIconMarginX+cRallyX*cIconSize+cRallyX*cIconMarginX, cControlMarginTop+cRallyY*cIconSize+cRallyY*cIconMarginY, 0, 0, 0, bupdate);
      [*] = ;                     elmHnd := _gui_CreateImage('_img_rally', elmHnd, gc_hud_icons_control+'rallypoint', gc_halParentLeft, gc_valParentTop, 3, 3, cIconSize, cIconSize, 0, bupdate);
      [*] = ;                     var hint : String = cTextRallyPoint;
      [*] = ;                     _gui_CreateButton('_btn_rally', elmHnd, gc_gui_material_blank, gc_halParentLeft, gc_valParentTop, 0, 0, cIconSize, cIconSize, eventstate, hint, cTagRally, bupdate);
      [*] = ;                  end;}
      [*] = ;                  // idle peasants, idle mines
      [*] = ;                  if (TObjProp(pobjprop).usage=gc_obj_usage_center) and (not bmorethenonetype) then
      [*] = ;                  begin
      [*] = ;                     const cIdlePeasantsX = 2;
      [*] = ;                     const cIdlePeasantsY = 0;
      [*] = ;                     const cIdleMinesX = 3;
      [*] = ;                     const cIdleMinesY = 0;
      [*] = ;                     if (cIdleMinesX>controlBtnMaxX) then controlBtnMaxX := cIdleMinesX;
      [*] = ;                     var elmHnd : Integer = _gui_CreateImage('_img_idlepeasants_key', elmControl, 'btn.56x56.frame', gc_halParentLeft, gc_valParentTop, cControlMarginLeft+cIdlePeasantsX*cIconSize+cIdlePeasantsX*cIconMarginX, cControlMarginTop+cIdlePeasantsY*cIconSize+cIdlePeasantsY*cIconMarginY, 0, 0, 0, bupdate);
      [*] = ;                     elmHnd := _gui_CreateImage('_img_idlepeasants', elmHnd, gc_hud_icons_control+'idlepeasants', gc_halParentLeft, gc_valParentTop, 3, 3, cIconSize, cIconSize, 0, bupdate);
      [*] = ;                     var hotkeyhint : String;
      [*] = ;                     var hotkey : String = GetRegisterGUIShortcut('select|idlepeasants');
      [*] = ;                     if (hotkey<>'') and (not StrExists(hotkey, 'nohotkey')) then
      [*] = ;                     hotkeyhint := ' ('+hotkey+')';
      [*] = ;                     var hint : String = cTextIdlePeasants+hotkeyhint;
      [*] = ;                     var btnHnd : Integer = _gui_CreateButton('_btn_idlepeasants', elmHnd, gc_gui_material_blank, gc_halParentLeft, gc_valParentTop, 0, 0, cIconSize, cIconSize, eventstate, hint, cTagIdlePeasants, bupdate);
      [*] = ;                     var idlecount : Integer = gPlayer[plInd].counter.idlepeasants;
      [*] = ;                     if idlecount>0 then
      [*] = ;                     text := IntToStr(idlecount)
      [*] = ;                     else
      [*] = ;                     text := '';
      [*] = ;                     _gui_CreateText('_txt_idlepeasants', elmHnd, text, gc_halParentLeft, gc_valParentTop, 3, 0, GetGUIElementWidth(elmHnd), GetGUIElementHeight(elmHnd), gc_halLeft, gc_valTop, gc_font_serif_14, colorWhite, True);
      [*] = ;                     var alpha : Float = _misc_SwitchFloat(0.3, 1, idlecount>0);
      [*] = ;                     SetGUIElementUserBlend(elmHnd, alpha);
      [*] = ;                     SetGUIElementEnabled(btnHnd, idlecount>0);
      [*] = ;
      [*] = ;                     elmHnd := _gui_CreateImage('_img_idlemines_key', elmControl, 'btn.56x56.frame', gc_halParentLeft, gc_valParentTop, cControlMarginLeft+cIdleMinesX*cIconSize+cIdleMinesX*cIconMarginX, cControlMarginTop+cIdleMinesY*cIconSize+cIdleMinesY*cIconMarginY, 0, 0, 0, bupdate);
      [*] = ;                     elmHnd := _gui_CreateImage('_img_idlemines', elmHnd, gc_hud_icons_control+'idlemines', gc_halParentLeft, gc_valParentTop, 3, 3, cIconSize, cIconSize, 0, bupdate);
      [*] = ;                     hotkeyhint := '';
      [*] = ;                     hotkey := GetRegisterGUIShortcut('select|idlemines');
      [*] = ;                     if (hotkey<>'') and (not StrExists(hotkey, 'nohotkey')) then
      [*] = ;                     hotkeyhint := ' ('+hotkey+')';
      [*] = ;                     hint := cTextIdleMines+hotkeyhint;
      [*] = ;                     btnHnd := _gui_CreateButton('_btn_idlemines', elmHnd, gc_gui_material_blank, gc_halParentLeft, gc_valParentTop, 0, 0, cIconSize, cIconSize, eventstate, hint, cTagIdleMines, bupdate);
      [*] = ;                     idlecount := gPlayer[plInd].counter.idlemines;
      [*] = ;                     if idlecount>0 then
      [*] = ;                     text := IntToStr(idlecount)
      [*] = ;                     else
      [*] = ;                     text := '';
      [*] = ;                     _gui_CreateText('_txt_idlemines', elmHnd, text, gc_halParentLeft, gc_valParentTop, 3, 0, GetGUIElementWidth(elmHnd), GetGUIElementHeight(elmHnd), gc_halLeft, gc_valTop, gc_font_serif_14, colorWhite, True);
      [*] = ;                     alpha := _misc_SwitchFloat(0.3, 1, idlecount>0);
      [*] = ;                     SetGUIElementUserBlend(elmHnd, alpha);
      [*] = ;                     SetGUIElementEnabled(btnHnd, idlecount>0);
      [*] = ;                  end;
      [*] = ;                  if (bshowartlimits) then
      [*] = ;                  begin
      [*] = ;                     var text : String;
      [*] = ;                     var i : Integer;
      [*] = ;                     for i:=0 to gc_MaxArtilleryType-1 do
      [*] = ;                     if (TObjProp(pobjprop).artdepo[i]<>0) then
      [*] = ;                     begin
      [*] = ;                        if (text<>'') then
      [*] = ;                        text := text+gc_gui_breakline;
      [*] = ;                        case i of
      [*] = ;                           gc_obj_artind_cannon : text := text+cTextArtLimitCannon;
      [*] = ;                           gc_obj_artind_howitzer : text := text+cTextArtLimitHowitzer;
      [*] = ;                           gc_obj_artind_mortar : text := text+cTextArtLimitMortar;
      [*] = ;                           gc_obj_artind_multicannon : text := text+cTextArtLimitMultiCannon;
      [*] = ;                        end;
      [*] = ;                        text := text+': '+IntToStr(Max(gPlayer[plInd].artcount[i], 0))+'/'+IntToStr(gPlayer[plInd].artlimit[i]);
      [*] = ;                     end;
      [*] = ;                     xOff := 72;
      [*] = ;                     yOff := 50;
      [*] = ;                     _gui_CreateText('_txt_artlimitinfo', elmParams, text, gc_halParentLeft, gc_valParentTop, xOff, yOff, 0, 0, gc_halLeft, gc_valTop, gc_font_serif_12, colorBrown, bupdate);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               // upgrades
      [*] = ;               if (gInterface.control.bshowupgrade) then
      [*] = ;               begin
      [*] = ;                  var bCurUpgExists : Boolean;
      [*] = ;                  for i:=0 to gc_country_upgradeplace_maxcount-1 do
      [*] = ;                  begin
      [*] = ;                     var upgsid : String = gCountry[cid].upgradeplace[upgplaceind].upgrade[i];
      [*] = ;                     if (upgsid<>'') then
      [*] = ;                     begin
      [*] = ;                        if (curupgsid<>'') and (curupgsid<>upgsid) then
      [*] = ;                        begin
      [*] = ;                           bCurUpgExists := True;
      [*] = ;                           break;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  for i:=0 to gc_country_upgradeplace_maxcount-1 do
      [*] = ;                  begin
      [*] = ;                     var upgsid : String = gCountry[cid].upgradeplace[upgplaceind].upgrade[i];
      [*] = ;                     if (upgsid<>'') then
      [*] = ;                     begin
      [*] = ;                        var bCurUpgrade : Boolean;
      [*] = ;                        var progress : Float;
      [*] = ;                        for j:=0 to cMaxPerformUpgradeAtOnce-1 do
      [*] = ;                        if (sarrPerformUpgrade[j]=upgsid) then
      [*] = ;                        begin
      [*] = ;                           bCurUpgrade := True;
      [*] = ;                           progress := MinFloat(1, sarrPerformUpgradeProgress[j]);
      [*] = ;                           break;
      [*] = ;                        end;
      [*] = ;                        var upgind : Integer = _country_GetUpgradeIndexByUpgradeID(cid, upgsid, False);
      [*] = ;                        var checkresult : Integer = _player_CheckAccessControlRequirements(plHnd, cid, upgsid);
      [*] = ;                        if (checkresult<>gc_result_checkaccesscontrolreq_notenabled) and (checkresult<>gc_result_checkaccesscontrolreq_hide) then
      [*] = ;                        //if (_player_CheckAccessControlRequirements(plHnd, cid, upgsid)=gc_result_checkaccesscontrolreq_ok) then
      [*] = ;                        begin
      [*] = ;                           // check this
      [*] = ;                           if ((gCountry[cid].upgrade[upgind].bindividual) or (bCurUpgrade){(curupgsid=upgsid)} or (not gPlayer[TObj(pobj).pl].upgstate[cid][upgind].inprogress)) then
      [*] = ;                           begin
      [*] = ;                              //var a : Integer = gCountry[cid].upgrade[upgind].level;
      [*] = ;                              //var b : Integer = gObj.individual.upglevel;
      [*] = ;                              if (not gCountry[cid].upgrade[upgind].bindividual) or (gCountry[cid].upgrade[upgind].level=TObj(pobj).individual.upglevel+2) then
      [*] = ;                              begin
      [*] = ;                                 if (gint_gui_pickedbldhnd=0) then
      [*] = ;                                 gint_gui_pickedbldcid := cid;
      [*] = ;
      [*] = ;                                 var x : Integer = gCountry[cid].upgrade[upgind].x;
      [*] = ;                                 var y : Integer = gCountry[cid].upgrade[upgind].y;
      [*] = ;                                 if (x>cMaxControlBtnCount) then break;
      [*] = ;                                 if (x>controlBtnMaxX) then controlBtnMaxX := x;
      [*] = ;
      [*] = ;                                 // generate hint start
      [*] = ;                                 var txtName, txtPrice : String;
      [*] = ;                                 _country_GetUpgradeNameBySID(cid, upgsid, txtName);
      [*] = ;
      [*] = ;                                 var binsufficient : Boolean;
      [*] = ;
      [*] = ;                                 var j : Integer;
      [*] = ;                                 for j:=0 to gc_ResCount-1 do
      [*] = ;                                 begin
      [*] = ;                                    var value : Integer;
      [*] = ;                                    case j of
      [*] = ;                                       gc_resource_type_food : value := gCountry[cid].upgrade[upgind].price[gc_resource_type_food];
      [*] = ;                                       gc_resource_type_wood : value := gCountry[cid].upgrade[upgind].price[gc_resource_type_wood];
      [*] = ;                                       gc_resource_type_stone : value := gCountry[cid].upgrade[upgind].price[gc_resource_type_stone];
      [*] = ;                                       gc_resource_type_gold : value := gCountry[cid].upgrade[upgind].price[gc_resource_type_gold];
      [*] = ;                                       gc_resource_type_iron : value := gCountry[cid].upgrade[upgind].price[gc_resource_type_iron];
      [*] = ;                                       gc_resource_type_coal : value := gCountry[cid].upgrade[upgind].price[gc_resource_type_coal];
      [*] = ;                                    end;
      [*] = ;                                    if (value<>0) then
      [*] = ;                                    begin
      [*] = ;                                       var scolor : String;
      [*] = ;                                       if (value>not gPlayer[TObj(pobj).pl].res[j]) then
      [*] = ;                                       begin
      [*] = ;                                          scolor := gc_font_color_red;
      [*] = ;                                          binsufficient := True;
      [*] = ;                                       end
      [*] = ;                                       else
      [*] = ;                                       scolor := gc_font_color_orange;
      [*] = ;                                       txtPrice := txtPrice+gc_font_color_white+GetLocaleTableListItemByID(gc_loc_gui, 'restype.'+IntToStr(j))+': '+scolor+IntToStr(Value)+'   ';
      [*] = ;                                    end;
      [*] = ;                                 end;
      [*] = ;
      [*] = ;                                 var mask : String = '%name%%price%';
      [*] = ;                                 mask := StrReplace(mask, '%name%', gUIConst.fontstyle[gc_font_serif_14]+gc_font_color_white+txtName);
      [*] = ;                                 mask := StrReplace(mask, '%price%', gc_gui_breakline+gc_gui_breakspace2+gUIConst.fontstyle[gc_font_serif_13]+txtPrice);
      [*] = ;                                 var value : Float = gCountry[cid].upgrade[upgind].value;
      [*] = ;                                 if gCountry[cid].upgrade[upgind].itype=gc_upg_type_buildtimeperc then
      [*] = ;                                 value := value/100000;
      [*] = ;                                 mask := StrReplace(mask, '%value%', FloatToStr(value));
      [*] = ;                                 // generate hint finish
      [*] = ;
      [*] = ;                                 if (checkresult<>gc_result_checkaccesscontrolreq_ok) then
      [*] = ;                                 begin
      [*] = ;                                    var hint : String;
      [*] = ;                                    _misc_PrepareCheckAccessControlRequirementsText(hint, plHnd, cid, upgsid);
      [*] = ;                                    mask := mask+gc_gui_breakline+gc_gui_breakline+hint;
      [*] = ;                                 end;
      [*] = ;
      [*] = ;                                 var elmHnd : Integer = _gui_CreateImage('_img_upgrades_key'+IntToStr(i), elmControl, 'btn.56x56.frame', gc_halParentLeft, gc_valParentTop, cControlMarginLeft+x*cIconSize+x*cIconMarginX, cControlMarginTop+y*cIconSize+y*cIconMarginY, 0, 0, 0, bupdate);
      [*] = ;                                 if (bwallexists) then
      [*] = ;                                 SetGUIElementVisible(elmHnd, (gSelectedObjects.GetCount=1) and (_misc_GetGateBaseSprite(goHnd)>=0));
      [*] = ;                                 var icon : String = 'noname';
      [*] = ;                                 //if (not bunitexists) and (bbuildingexists) then
      [*] = ;                                 _misc_GetUpgradeIconNameBySID(upgsid, icon);
      [*] = ;                                 elmHnd := _gui_CreateImage('_img_upgrades'+IntToStr(i), elmHnd, icon, gc_halParentLeft, gc_valParentTop, 3, 3, cIconSize, cIconSize, 0, bupdate);
      [*] = ;                                 var level : Integer = gCountry[cid].upgrade[upgind].level;
      [*] = ;                                 if (level>1) then
      [*] = ;                                 _gui_CreateImage('_img_level'+IntToStr(i), elmHnd, 'icons.num.small.'+IntToStr(level), gc_halParentRightWidth, gc_valParentBottomHeight, -3, -5, 0, 0, 0, bupdate);
      [*] = ;
      [*] = ;                                 if (binsufficient) and (checkresult=gc_result_checkaccesscontrolreq_ok) and (not bCurUpgrade) then
      [*] = ;                                 SetGUIElementUserBlend(elmHnd, 0.2)
      [*] = ;                                 else
      [*] = ;                                 SetGUIElementUserBlend(elmHnd, 1);
      [*] = ;
      [*] = ;                                 if (bCurUpgrade) then
      [*] = ;                                 begin
      [*] = ;                                    var sizex : Integer = GetGUITextureWidth('icons.progress.meter')+1;
      [*] = ;                                    var elmTmp : Integer = _gui_CreateImage('_img_upgrademeter_frame', elmHnd, 'icons.progress.frame', gc_halParentLeft, gc_valParentBottomHeight, 2, -2, 0, 0, 0, bupdate);
      [*] = ;                                    _gui_CreateImage('_img_upgrademeter_bckg', elmTmp, 'icons.progress.background', gc_halParentLeft, gc_valParentTop, 1, 1, 0, 0, 0, bupdate);
      [*] = ;                                    elmTmp := _gui_CreateTileScaleImage('_img_upgrademeter_progress', elmTmp, 'icons.progress.meter', gc_halParentLeft, gc_valParentTop, 1, 1, floor(progress*sizex), 0, bupdate);
      [*] = ;                                    SetGUIElementVisible(elmTmp, (floor(progress*sizex)>0));
      [*] = ;                                 end
      [*] = ;                                 else
      [*] = ;                                 begin
      [*] = ;                                    var elmTmp : Integer = GetGUIElementIndexByNameParent('_img_upgrademeter_frame', elmHnd);
      [*] = ;                                    if (elmTmp<>0) then RemoveGUIElement(elmTmp);
      [*] = ;                                 end;
      [*] = ;
      [*] = ;                                 var btnHnd : Integer = _gui_CreateButton('_btn_upgrades'+IntToStr(i), elmHnd, gc_gui_material_blank, gc_halParentLeft, gc_valParentTop, 0, 0, cIconSize, cIconSize, eventstate, mask, cTagUpgrade, bupdate);
      [*] = ;                                 if ((binsufficient) and (not bCurUpgrade)) or (gPlayer[TObj(pobj).pl].upgstate[cid][upgind].grey) then
      [*] = ;                                 SetGUIElementEnabled(btnHnd, False);
      [*] = ;                                 SetGUIElementStringTag(btnHnd, upgsid);
      [*] = ;
      [*] = ;                                 var color2 : TColor;
      [*] = ;                                 color2.r := 0;
      [*] = ;                                 color2.g := 1;
      [*] = ;                                 color2.b := 0;
      [*] = ;                                 color2.a := 1;
      [*] = ;                                 var orderIndex : Integer = -1;
      [*] = ;                                 for j:=0 to gc_obj_MaxOrderCount-1 do
      [*] = ;                                 begin
      [*] = ;                                    if (TObj(pobj).orders[j].itype=gc_obj_order_type_performupgrade) then
      [*] = ;                                    begin
      [*] = ;                                       var tmpupgsid : String;
      [*] = ;                                       _country_GetUpgradeSIDByUpgradeID(TObj(pobj).cid, TObj(pobj).orders[j].info.upgradeid, tmpupgsid);
      [*] = ;                                       if (tmpupgsid=upgsid) then
      [*] = ;                                       begin
      [*] = ;                                          orderIndex := j;
      [*] = ;                                          break;
      [*] = ;                                       end;
      [*] = ;                                    end;
      [*] = ;                                 end;
      [*] = ;                                 var ttext : String = IntToStr(orderIndex+1);
      [*] = ;                                 var elmTmp : Integer = _gui_CreateText('_txt_produceamount'+IntToStr(i), elmHnd, ttext, gc_halParentLeft, gc_valParentTop, 2, 0, GetGUIElementWidth(elmHnd), GetGUIElementHeight(elmHnd), gc_halLeft, gc_valBottom, gc_font_sans_14, color2, bupdate);
      [*] = ;                                 SetGUIElementVisible(elmTmp, (orderIndex>0));
      [*] = ;
      [*] = ;                                 //elmTmp := _gui_CreateImage('_img_curupg_'+IntToStr(i), elmHnd, 'icons.control.frame.active.3', gc_halParentLeft, gc_valParentTop, 0, 0, cIconSize, cIconSize, 0, bupdate);
      [*] = ;                                 //SetGUIElementVisible(elmTmp, bCurUpgrade);
      [*] = ;
      [*] = ;                                 ////elmTmp := _gui_CreateImage('_btn_upgblackmask'+IntToStr(i), btnHnd, gc_gui_material_black, gc_halParentLeft, gc_valParentTop, 0, 0, GetGUIElementWidth(btnHnd), GetGUIElementHeight(btnHnd), 0, bupdate);
      [*] = ;                                 //elmTmp := _gui_CreateImageActive('_btn_upgblackmask'+IntToStr(i), btnHnd, gc_gui_material_black, gc_halParentLeft, gc_valParentTop, 0, 0, GetGUIElementWidth(btnHnd), GetGUIElementHeight(btnHnd), 0, '', '', bupdate);
      [*] = ;                                 elmTmp := _gui_CreateImage('_btn_upgblackmask'+IntToStr(i), btnHnd, gc_gui_material_black, gc_halParentLeft, gc_valParentTop, 0, 0, GetGUIElementWidth(btnHnd), GetGUIElementHeight(btnHnd), 0, bupdate);
      [*] = ;                                 SetGUIElementUserBlend(elmTmp, 0.75);
      [*] = ;                                 SetGUIElementVisible(elmtmp, (not bCurUpgrade) and (bCurUpgExists) and ((curupgsid<>'') and (curupgsid<>upgsid)));
      [*] = ;
      [*] = ;                                 //var hint : String;
      [*] = ;                                 //_misc_PrepareCheckAccessControlRequirementsText(hint, plHnd, cid, upgsid);
      [*] = ;                                 //elmtmp := _gui_CreateImageActive('_btn_blackmask'+IntToStr(i), elmHnd, gc_gui_material_black, gc_halParentLeft, gc_valParentTop, 0, 0, GetGUIElementWidth(btnHnd), GetGUIElementHeight(btnHnd), 0, '', hint, bupdate);
      [*] = ;                                 elmtmp := _gui_CreateImage('_btn_blackmask'+IntToStr(i), elmHnd, gc_gui_material_black, gc_halParentLeft, gc_valParentTop, 0, 0, GetGUIElementWidth(btnHnd), GetGUIElementHeight(btnHnd), 0, bupdate);
      [*] = ;                                 SetGUIElementUserBlend(elmtmp, _misc_SwitchFloat(cAlphaBlackMaskReqsNotOk, 0.65, (not bCurUpgrade) and (bCurUpgExists) and ((curupgsid<>'') and (curupgsid<>upgsid))));
      [*] = ;                                 SetGUIElementVisible(elmtmp, (checkresult<>gc_result_checkaccesscontrolreq_ok));
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        var elmHnd : Integer = GetGUIElementIndexByNameParent('_img_upgrades_key'+IntToStr(i), elmControl);
      [*] = ;                        if (elmHnd<>0) then
      [*] = ;                        RemoveGUIElement(elmHnd);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         //adjust panel width to button counts.
      [*] = ;         var iwidth : Integer = (controlBtnMaxX+1)*46+11;
      [*] = ;         var elmwidth : Integer = GetGUITextureWidth(GetGUIElementMaterial(elmControl));
      [*] = ;         var fscaleX : Float = 1;
      [*] = ;         if (iwidth<>0) and (iwidth<elmwidth) then
      [*] = ;         fscaleX := iwidth/elmwidth
      [*] = ;         else
      [*] = ;         iwidth := elmwidth;
      [*] = ;         if (fscaleX>1) then fscaleX := 1;
      [*] = ;         if (iwidth<0) then fscaleX := -fscaleX;
      [*] = ;         SetGUIElementTileScales(elmControl, fscaleX, 1);
      [*] = ;         SetGUIElementWidth(elmControl, iwidth);
      [*] = ;         SetGUIElementLogicWidth(elmControl, iwidth);
      [*] = ;
      [*] = ;         SetGUIElementWidth(elmParent, GetGUIElementWidth(elmInfo)+iwidth+11);
      [*] = ;         SetGUIElementLogicWidth(elmParent, GetGUIElementWidth(elmInfo)+iwidth+11);
      [*] = ;         SetGUIElementCursorByName(elmParent, 'crDefault');
      [*] = ;
      [*] = ;         GUIInvalidateParentPositions(elmParent);
      [*] = ;         //GUIInvalidateChildrenPositions(elmParent);
      [*] = ;
      [*] = ;         _gui_CreateTileScaleImage('controltopbordershadow', elmControl, 'unitpanel.rightframe.shadow', gc_halParentLeft, gc_valParentTop, iwidth+10, -GetGUITextureHeight('unitpanel.topframe')-12, 0, 0, bupdate);
      [*] = ;         _gui_CreateImage('controlrightborder', elmControl, 'unitpanel.rightframe', gc_halParentLeft, gc_valParentBottomHeight, iwidth-25, 9, 0, 0, 0, bupdate);
      [*] = ;         _gui_CreateTileScaleImage('controltopbordershadow', elmInfo, 'unitpanel.topframe.shadow', gc_halParentLeft, gc_valParentTop, 0, -GetGUITextureHeight('unitpanel.topframe')-12, GetGUIElementWidth(elmInfo)+iwidth+10, 0, bupdate);
      [*] = ;         _gui_CreateTileScaleImage('controltopborder', elmInfo, 'unitpanel.topframe', gc_halParentLeft, gc_valParentTop, 0, -GetGUITextureHeight('unitpanel.topframe')+6, GetGUIElementWidth(elmInfo)+iwidth, 0, bupdate);
      [*] = ;         _gui_CreateTileScaleImage('controlbottomborder', elmInfo, 'unitpanel.bottomframe', gc_halParentLeft, gc_valBottomHeight, 0, 0, GetGUIElementWidth(elmInfo)+iwidth, 0, bupdate);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   gint_gui_prevshowunitcontrolunituid := GetGameObjectUniqueIdByHandle(goHnd);
      [*] = ;   gbool_gui_requestsoundonunitcontrol := False;
      [*] = ;end;
      [*] = ;
      [*] = ;var curcount : Integer = gSelectedObjects.GetCount;
      [*] = ;for i:=1 to shipscount do
      [*] = ;gSelectedObjects.Delete(curcount-i);
   struct.end
section.end

