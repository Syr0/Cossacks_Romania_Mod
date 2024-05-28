section.begin
   Name = DoCreate
   Description[*] = ;
   UsedFileName = 
   Code : struct.begin
      [*] = ;Log('...DoCreate started...');
      [*] = ;if (GetGUIProgressBarElementHandle<>0) then
      [*] = ;_gui_AbsScaleByDPI(GetGUIProgressBarElementHandle);
      [*] = ;
      [*] = ;gint_maxcountrycountvisible := 0;
      [*] = ;gint_maxcountrycountplayable := 0;
      [*] = ;
      [*] = ;gint_gui_encyclopediapage := 1;
      [*] = ;
      [*] = ;if gfloat_gui_interfacescale<=0 then
      [*] = ;gfloat_gui_interfacescale := 1;
      [*] = ;
      [*] = ;var i : Integer;
      [*] = ;for i:=0 to gc_MaxCountryCount-1 do
      [*] = ;begin
      [*] = ;   var bVisibleInEditor, bVisibleInMultiplayer, bPlayable : Boolean;
      [*] = ;   _country_IsCountryAvailable(0, i, gProfile.lastknowndlcs, bVisibleInEditor, bVisibleInMultiplayer, bPlayable);
      [*] = ;   if (bVisibleInEditor) then
      [*] = ;   gint_maxcountrycountvisible := gint_maxcountrycountvisible+1;
      [*] = ;   if (bPlayable) then
      [*] = ;   gint_maxcountrycountplayable := gint_maxcountrycountplayable+1;
      [*] = ;end;
      [*] = ;
      [*] = ;for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;begin
      [*] = ;   if gScenario.bexists then
      [*] = ;   begin
      [*] = ;      gPlayer[i].playeradviser.adviser.bavailable := False;
      [*] = ;      gPlayer[i].playeradviser.adviser.benable := False;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      gPlayer[i].playeradviser.adviser.bavailable := (not gScenario.bexists) and (((_net_IsOnline) and (gMap.settings.additional.adviserassistant=gc_mapsettings_adviserassistant_default))
      [*] = ;      or ((not _net_IsOnline) and (gMap.settings.additional.adviserassistant=gc_mapsettings_adviserassistant_default) and ((gProfile.lastknowndlcs and gc_lastknowndlc_exp1)<>0)));
      [*] = ;      if (gPlayer[i].playeradviser.adviser.benable) and (not gPlayer[i].playeradviser.adviser.bavailable) then
      [*] = ;      gPlayer[i].playeradviser.adviser.benable := False;
      [*] = ;   end;
      [*] = ;   gPlayer[i].playeradviser.adviser.settings := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;if (GetPlayerHandleByIndex(0)=0) then // hard hack prevent from crash. seems like no more needed to add pine tree
      [*] = ;begin
      [*] = ;   gbool_gui_maxcameradist := True; // fix bug when this is engine, and on launch, do create triggered twice and camera in broken
      [*] = ;   gInterface.gamemode := gc_gamemode_mainmenu;
      [*] = ;   MapExecuteState('InitMap');
      [*] = ;   {if (GetCountOfPlayers>=gc_playerind_env) then
      [*] = ;   begin
      [*] = ;      var plHnd : Integer = GetPlayerHandleByIndex(gc_playerind_env);
      [*] = ;      if (plHnd<>0) then
      [*] = ;      CreatePlayerGameObjectHandleByHandle(plHnd, gc_racename_env, 'fir', -40, 0, 0);
      [*] = ;   end;}
      [*] = ;end;
      [*] = ;
      [*] = ;const cCamFilename = '.\data\cameras\camera.cfg';
      [*] = ;if (not gProfile.bDbgCamera) and (not gbool_gui_screenshotcamera) then
      [*] = ;SetCameraPropertiesFromFile(cCamFilename);
      [*] = ;
      [*] = ;if gbool_gui_maxcameradist then
      [*] = ;begin
      [*] = ;   var bsmooth : Boolean = GetCameraInfoSmoothingChange;
      [*] = ;   var camera : String;
      [*] = ;   if gProfile.bDbgCamera then
      [*] = ;   begin
      [*] = ;      const cCamDbgFilename = '.\data\cameras\cameradebug.cfg';
      [*] = ;      SetCameraPropertiesFromFile(cCamDbgFilename);
      [*] = ;      camera := '@CameraDebug';
      [*] = ;   end
      [*] = ;   else
      [*] = ;   camera := '@Camera0';
      [*] = ;   ImportTextCameras('.\data\cameras\default.cameras', true);
      [*] = ;   SetCameraInfoSmoothingChange(False);
      [*] = ;   CameraInfoLoadToCurrentView(camera);
      [*] = ;   SetCameraInfoSmoothingChange(bsmooth);
      [*] = ;   DeleteCameraInfo('Camera0');
      [*] = ;   DeleteCameraInfo('@Camera0');
      [*] = ;   DeleteCameraInfo('@CameraDebug');
      [*] = ;   SetCameraElasticDistance(100); // camera will clamp this value to maximum
      [*] = ;   gbool_gui_maxcameradist := False;
      [*] = ;end;
      [*] = ;
      [*] = ;SetCameraDepthOfView(1200);
      [*] = ;
      [*] = ;SetCameraElasticTargetObject(0);
      [*] = ;SetCameraElasticMoveTurnOff();
      [*] = ;SetCameraElasticRotationTurnOff();
      [*] = ;SetCameraControlMode('ccmRTS');
      [*] = ;SetCameraInfoSmoothingChange(true);
      [*] = ;SetCameraBounded(False);
      [*] = ;SetCameraDynamicFocalLength(gProfile.bDbgCamera);
      [*] = ;//SetCameraDynamicFocalLength(true);
      [*] = ;//SetCameraDynamicFocalLength(False); // camera won't reset focal length on ctrl+t
      [*] = ;SetCameraControlMouseWheelRotate(false);
      [*] = ;SetCameraControlMouseWheelDistance(false);
      [*] = ;SetGameManagerRestrictSelection(false);
      [*] = ;SetGameManagerSelectionUseStep(true);
      [*] = ;SetGUIBaseControlVisible(true);
      [*] = ;SetGUIMiniMapVisible(false);
      [*] = ;
      [*] = ;if gProfile.bDbgCamera then
      [*] = ;begin
      [*] = ;   SetCameraDepthOfView(1200);
      [*] = ;
      [*] = ;   const cMaxCameraHeight = 500;
      [*] = ;   var lx, rx, fy, by, htm, sh, shm, sl, slm : Float;
      [*] = ;   GetCameraRestrictInfo(lx, rx, fy, by, htm, sh, shm, sl, slm);
      [*] = ;   SetCameraRestrictInfo(lx, rx, fy, by, htm, cMaxCameraHeight, shm, cMaxCameraHeight, slm);
      [*] = ;
      [*] = ;   var minHMinAngle, minHMaxAngle, maxHMinAngle, maxHMaxAngle, angleLerpPower, minDistToTarget, maxDistToTargetm, maxHeightLerpFactor : Float;
      [*] = ;   GetCameraFreeRotationInfo(minHMinAngle, minHMaxAngle, maxHMinAngle, maxHMaxAngle, angleLerpPower, minDistToTarget, maxDistToTargetm, maxHeightLerpFactor);
      [*] = ;
      [*] = ;   maxHMaxAngle := 90;
      [*] = ;   maxHMinAngle := -90;
      [*] = ;   minHMaxAngle := 90;
      [*] = ;   minHMinAngle := -90;
      [*] = ;
      [*] = ;   SetCameraFreeRotationInfo(minHMinAngle, minHMaxAngle, maxHMinAngle, maxHMaxAngle, angleLerpPower, minDistToTarget, maxDistToTargetm, maxHeightLerpFactor);
      [*] = ;   SetCameraControlMouseWheelRotate(true);
      [*] = ;
      [*] = ;   SetCameraMouseDistanceSpeed(10);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   var plHnd : Integer = GetPlayerHandleInterfaceIO;
      [*] = ;   if (plHnd<>0) then
      [*] = ;   begin
      [*] = ;      var plInd : Integer = GetPlayerIndexByHandle(plHnd);
      [*] = ;      _player_UpdateFOW(plInd);
      [*] = ;   end;
      [*] = ;   gbool_gui_firstonresize := True;
      [*] = ;   ExecuteState('OnResize');
      [*] = ;   gbool_gui_firstonresize := False;
      [*] = ;end;
      [*] = ;
      [*] = ;if (not gbool_gui_isfileexists_checked_campaigns) then
      [*] = ;begin
      [*] = ;   gbool_gui_isfileexists_campaigns := IsFileExists(gc_filepath_campaigns);
      [*] = ;   gbool_gui_isfileexists_checked_campaigns := True;
      [*] = ;end;
      [*] = ;
      [*] = ;if (not gbool_gui_firstdocreate) then
      [*] = ;begin
      [*] = ;   gbool_gui_firstdocreate := True;
      [*] = ;   var pProject : Integer = _parser_ParserTemporary(True);
      [*] = ;   ParserLoadFromFileByHandle(pProject, '.\data\projects\project.main.prj');
      [*] = ;   gSVNVersion := ParserGetIntValueByKeyByHandle(pProject, 'SVNVersion');
      [*] = ;   gint_gui_progressbar_picnum := Floor(1+8*random);
      [*] = ;end;
      [*] = ;var width, height : Integer;
      [*] = ;_gui_GetProgressBarWidthHeight(width, height);
      [*] = ;var barname : String = 'load.game.'+IntToStr(height)+'.'+IntToStr(gint_gui_progressbar_picnum);
      [*] = ;SetGUILoadProgressBarActiveName(barname);
      [*] = ;
      [*] = ;ExecuteState('DoInitialize');
      [*] = ;
      [*] = ;if (gbool_gui_newmapfinished) then
      [*] = ;begin
      [*] = ;   if (_net_IsOffline) and (gMap.gamestage<gc_map_gamestage_started) then
      [*] = ;   _control_SetGameSpeedByMode(gMap.settings.additional.gamespeed, False);
      [*] = ;
      [*] = ;   if not _net_IsOnline then
      [*] = ;   SetGUIEventStateOnLanChange('OnLanEvent');
      [*] = ;   if GetSeasonType=2 then begin
      [*] = ;   SetCurrentColorTableIndex(5); //winter- dark - 6 was too bright. Maybe this is a bit too 'blueish'
      [*] = ;   SetCurrentPHDRIndex(1);
      [*] = ;   end;
      [*] = ;   if GetSeasonType=1 then begin
      [*] = ;   SetCurrentColorTableIndex(8); //autumn - Used to be 2 (red) in beta version.
      [*] = ;   end;
      [*] = ;   if GetSeasonType=3 then begin
      [*] = ;   SetCurrentColorTableIndex(7); //spring
      [*] = ;   end;
      [*] = ;   if GetSeasonType=0 then begin
      [*] = ;   SetCurrentColorTableIndex(0); //summer
      [*] = ;   SetCurrentPHDRIndex(0);
      [*] = ;   end;
      [*] = ;   gbool_gui_newmapfinished := False;
      [*] = ;   gLanHostID := 0;
      [*] = ;   if (gInternetShell.bauth) then
      [*] = ;   begin
      [*] = ;      gInternetShell.prevstate := 4;
      [*] = ;      _gui_InitShowMainMenu(True);
      [*] = ;      _gui_SetGUIElementVisibleByName('MainMenu.col1', False); // leave it at en_d
      [*] = ;
      [*] = ;      if (gInternetShell.bautosearch) then
      [*] = ;      _misc_QuickPlayUnsign(False);
      [*] = ;
      [*] = ;      gInternetShell.Clear(False);
      [*] = ;      gInternetShell.lanid := LanMyInfoID;
      [*] = ;
      [*] = ;      gInternetShell.bshowroom := False;
      [*] = ;      gInternetShell.bshowranking := False;
      [*] = ;      gInternetShell.currentpage := gc_internetshell_currentpage_sessions;
      [*] = ;
      [*] = ;      var pClients : Integer = _parser_ParserTemporary(True);
      [*] = ;      LanPublicServerClientsToParser(pClients);
      [*] = ;      var i : Integer;
      [*] = ;      for i:=0 to ParserGetCountByHandle(pClients)-1 do
      [*] = ;      begin
      [*] = ;         var pClient : Integer = ParserSelectByHandleByIndex(pClients, i);
      [*] = ;         if pClient<>0 then
      [*] = ;         gInternetShell.clients.AddOrUpdateFromParser(pClient);
      [*] = ;      end;
      [*] = ;
      [*] = ;      var pSessions : Integer = _parser_ParserTemporary(True);
      [*] = ;      LanPublicServerSessionsToParser(pSessions);
      [*] = ;      gInternetShell.sessions.Clear;
      [*] = ;      for i:=0 to ParserGetCountByHandle(pSessions)-1 do
      [*] = ;      begin
      [*] = ;         var pSession : Integer = ParserSelectByHandleByIndex(pSessions, i);
      [*] = ;         if pSession<>0 then
      [*] = ;         gInternetShell.sessions.AddFromParser(pSession);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (not gbool_internetshell_firstappearance) then
      [*] = ;      begin
      [*] = ;         var txtwelcome, txt : String;
      [*] = ;         _misc_GetNewTextLocale('internetshell.welcome.new', txtwelcome);
      [*] = ;         txtwelcome := gc_font_color_white+txtwelcome+gc_font_color_default;
      [*] = ;         //txtwelcome := txtwelcome+gc_gui_breakline;
      [*] = ;         _misc_GetNewTextLocale('internetshell.season5.start', txt);
      [*] = ;         txtwelcome := txtwelcome+gc_gui_breakline+txt;
      [*] = ;         LanPublicServerSendMessage(LanMyInfoID, txtwelcome);
      [*] = ;         LanPublicServerUpdateInfo; // shut down if srv version is different than client
      [*] = ;         LanPublicServerUpdateClientInfo(LanMyInfoID);
      [*] = ;         gbool_internetshell_firstappearance := True;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;case gInterface.gamemode of
      [*] = ;   gc_gamemode_mainmenu : begin
      [*] = ;      if (not GetRecordEnabled) then
      [*] = ;      _net_setRecord(False);
      [*] = ;      gbool_gui_outofmemoryrecordclean := False;
      [*] = ;      gbool_recordwascleared := False;
      [*] = ;      gbool_gui_hidenicks := False;
      [*] = ;      gfloat_gui_lanlastgametimesyncreceived := 0;
      [*] = ;      var clean : TLanRecreate;
      [*] = ;      gLanRecreate := clean;
      [*] = ;      var bskip : Boolean;
      [*] = ;      if (not gInternetShell.bauth) and (StringRegister7<>'') and ((StrLength(StringRegister7)=4) or (StrLength(StringRegister7)=5)) then
      [*] = ;      begin
      [*] = ;         _gui_InitShowMainMenu(True);
      [*] = ;         _init_CalcCheckSum;
      [*] = ;         if (gstring_checksum<>StringRegister7) then
      [*] = ;         _gui_ShowConnectStateMessage(gc_ConnectModsState_SyncFailed)
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            _gui_SetGUIElementVisibleByName('MainMenu.col1', False);
      [*] = ;            const cTagMultiplayer = 103;
      [*] = ;            _gui_SendTagToState('EventMainMenu', cTagMultiplayer);
      [*] = ;         end;
      [*] = ;         bskip := True;
      [*] = ;      end;
      [*] = ;
      [*] = ;      _net_lanmode_last := 0;
      [*] = ;      if (gInternetShell.bauth) then
      [*] = ;      begin
      [*] = ;         if (gInternetShell.bautosearch) then
      [*] = ;         _misc_QuickPlayUnsign(False);
      [*] = ;
      [*] = ;         _gui_InitShowMainMenu(True);
      [*] = ;         _gui_SetGUIElementVisibleByName('MainMenu.col1', False);
      [*] = ;         if (gInternetShell.bshowroom) then
      [*] = ;         begin
      [*] = ;            gbool_gui_showinternetshell := False;
      [*] = ;            if (gInternetShell.bhistoricalbattle) then
      [*] = ;            ExecuteState('ShowHistoricalBattle')
      [*] = ;            else
      [*] = ;            ExecuteState('ShowCustomGame')
      [*] = ;         end
      [*] = ;         else
      [*] = ;         ExecuteState('ShowInternetShell')
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (not bskip) then
      [*] = ;      _gui_InitShowMainMenu(True);
      [*] = ;   end;
      [*] = ;   gc_gamemode_game : begin
      [*] = ;      gbool_editor_placeunitsmaximized := False;
      [*] = ;   end;
      [*] = ;   gc_gamemode_editor : begin
      [*] = ;      gbool_editor_placeunits := True;
      [*] = ;      {if (GetPlayerGameObjectsCountByHandle(GetPlayerHandleByIndex(0))=0) then //hack
      [*] = ;      begin
      [*] = ;         _map_CreateStartPoint(0, -32-3, -14);
      [*] = ;         _map_CreateStartPoint(1, 32+3, -14);
      [*] = ;         TopologyBuild;
      [*] = ;      end;}
      [*] = ;      {if (GetPlayerHandleByIndex(0)=0) then
      [*] = ;      MapExecuteState('InitMap');}
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gInterface.gamemode=gc_gamemode_mainmenu) and (IsEngine) then // is first runned
      [*] = ;_control_MoveCameraToPosition(0, 0, 0, True);
      [*] = ;
      [*] = ;if (gbool_gui_screenshotcamera) or (gProfile.bfreezoom) then
      [*] = ;begin
      [*] = ;   const cScrCamFilename = '.\data\cameras\camerascreenshot.cfg';
      [*] = ;   SetCameraPropertiesFromFile(cScrCamFilename);
      [*] = ;   SetCameraControlMouseWheelRotate(True);
      [*] = ;   SetGUIEventStateOnMouseWheel('OnMouseWheel');
      [*] = ;   SetCameraControlMouseWheelDistance(True);
      [*] = ;   SetCameraMouseDistanceSpeed(2);
      [*] = ;
      [*] = ;   const cMaxCameraHeight = 140;
      [*] = ;   const cMinCameraHeight = 20;
      [*] = ;   var lx, rx, fy, by, htm, sh, shm, sl, slm : Float;
      [*] = ;   GetCameraRestrictInfo(lx, rx, fy, by, htm, sh, shm, sl, slm);
      [*] = ;   SetCameraRestrictInfo(lx, rx, fy, by, htm, cMaxCameraHeight, shm, cMaxCameraHeight, slm);
      [*] = ;   SetCameraRestrictInfo(lx-400, rx+400, fy-400, by+400, cMinCameraHeight, cMaxCameraHeight, cMinCameraHeight, cMaxCameraHeight, cMinCameraHeight);
      [*] = ;
      [*] = ;   SetCameraDynFogDepth(False);
      [*] = ;   SetCameraDynFogStart(0.125);
      [*] = ;   SetCameraDynFogEnd(0.625);
      [*] = ;   SetCameraDynFogDensity(0.5);
      [*] = ;   SetCameraDynFogPower(0.001);
      [*] = ;   SetCameraDynFogOffset(0);
      [*] = ;
      [*] = ;   SetShadowMapLightDepth(400);
      [*] = ;
      [*] = ;   var focal : Float = 400+gfloat_gui_screenshotcamerafov*5;
      [*] = ;   SetCameraFocalLengthInfo(focal, focal, 0.5);
      [*] = ;   log('focal='+FloatToStr(focal));
      [*] = ;   if gbool_gui_screenshotcamera then
      [*] = ;   begin
      [*] = ;      var size, dirx, diry, dirz: Float; var texs: Integer;
      [*] = ;      var scaling, visible: Boolean;
      [*] = ;      GetHighlightRenderSettings(size, dirx, diry, dirz, texs, scaling, visible);
      [*] = ;      size:=0.7;
      [*] = ;      SetHighlightRenderSettings(size, dirx, diry, dirz, texs, scaling, False);
      [*] = ;   end;
      [*] = ;
      [*] = ;   SetCameraDynamicFocalLength(True);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   // limit camera borders
      [*] = ;   //if (IsEngine) then
      [*] = ;   begin
      [*] = ;      var maplx, mapty : Float;
      [*] = ;      _misc_GetMapLeftTopPos(maplx, mapty);
      [*] = ;      SetCameraElasticRestrict(maplx+14, mapty, -(maplx+10.5), -mapty+85);
      [*] = ;
      [*] = ;      // force camera to clamp to max height
      [*] = ;      var newx, newy : Float;
      [*] = ;      _misc_ZoomCamera(0, 0, newx, newy, True);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var showpause : Boolean = (gint_gui_changeresolutionstage=0);
      [*] = ;if (gint_gui_changeresolutionstage<>0) then
      [*] = ;begin
      [*] = ;   case gint_gui_changeresolutionstage of
      [*] = ;      1, 3 : begin
      [*] = ;         gint_gui_changeresolutionstage := 0;
      [*] = ;         _gui_InvokeMouseMove;
      [*] = ;         if (gInterface.gamemode<>gc_gamemode_mainmenu) then
      [*] = ;         ExecuteState('ShowMenu');
      [*] = ;         ExecuteState('ShowSettings');
      [*] = ;      end;
      [*] = ;      4 : begin
      [*] = ;         gint_gui_changeresolutionstage := 0;
      [*] = ;         _gui_InvokeMouseMove;
      [*] = ;         if (gInterface.gamemode<>gc_gamemode_mainmenu) then
      [*] = ;         ExecuteState('ShowMenu');
      [*] = ;      end;
      [*] = ;      2 : begin
      [*] = ;         gint_gui_changeresolutionstage := 0;
      [*] = ;         _gui_InvokeMouseMove;
      [*] = ;         if (gInterface.gamemode<>gc_gamemode_mainmenu) then
      [*] = ;         ExecuteState('ShowMenu');
      [*] = ;         ExecuteState('ShowSettings');
      [*] = ;         const cTagResolutionApprove = 401;
      [*] = ;         const cTagResolutionRevert = 402;
      [*] = ;         _gui_ShowModalMessage('gui|menu.resolution.header', 'gui|menu.resolution.text', 'gui|btn.approve', 'gui|btn.revert', cTagResolutionApprove, cTagResolutionRevert);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (showpause) and (GetProgressingPauseMode) then
      [*] = ;ExecuteState('ShowPause');
      [*] = ;if (gMap.gamestage=gc_map_gamestage_waitingloading) then
      [*] = ;begin
      [*] = ;   if (_net_IsOnline) then
      [*] = ;   SetGUIEventStateOnLanChange('OnLanEventSession');
      [*] = ;end;
      [*] = ;{if (gMap.gamestage=gc_map_gamestage_waitingloading) then
      [*] = ;begin
      [*] = ;   var pl : Integer = GetPlayerIndexByHandle(GetPlayerHandleInterfaceIO);
      [*] = ;   if (pl>=0) and (pl<gc_MaxPlayerCount) then
      [*] = ;   gMap.players[pl].bloaded := True
      [*] = ;   else
      [*] = ;   ErrorLog('DoCreate invalid pl');
      [*] = ;
      [*] = ;   if (_net_IsOnline) then
      [*] = ;   begin
      [*] = ;      SetGUIEventStateOnLanChange('OnLanEventSession');
      [*] = ;      if (not IsLanReady) then
      [*] = ;      begin
      [*] = ;         if (LanGetClientsCount<=1) then
      [*] = ;         begin
      [*] = ;            Log('_net_IsOnline and LanGetClientsCount<=1');
      [*] = ;            LanDoReady;
      [*] = ;            gMap.gamestage := gc_map_gamestage_started;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            log('DoCreate:LanDoReady');
      [*] = ;            LanDoReady;
      [*] = ;            LanSendParser(gc_LAN_GAME_READY, _parser_ParserEmpty);
      [*] = ;            SetProgressingPauseMode(True);
      [*] = ;            ExecuteState('ShowPause');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   gMap.gamestage := gc_map_gamestage_started;
      [*] = ;end
      [*] = ;else}
      [*] = ;if (gMap.gamestage<>gc_map_gamestage_waitingloading) and (_net_IsOnline) then
      [*] = ;begin
      [*] = ;   SetProgressingPauseMode(gbool_gui_pausestate);
      [*] = ;   if (gbool_gui_pausestate) then
      [*] = ;   ExecuteState('ShowPause');
      [*] = ;end;
      [*] = ;
      [*] = ;if (not gbool_gui_showannouncementclosed) then
      [*] = ;ExecuteState('ShowAnnouncement');
      [*] = ;
      [*] = ;if (gInterface.gamemode<>gc_gamemode_mainmenu) then
      [*] = ;begin
      [*] = ;   var i, j : Integer;
      [*] = ;   for i:=0 to gc_MaxPlayerCount-1 do
      [*] = ;   begin
      [*] = ;      var plHnd : Integer = GetPlayerHandleByIndex(i);
      [*] = ;      if (GetPlayerRaceTagByHandle(plHnd)=gc_racetag_units) then
      [*] = ;      begin
      [*] = ;         for j:=0 to GetPlayerGameObjectsCountByHandle(plHnd)-1 do
      [*] = ;         begin
      [*] = ;            var goHnd : Integer = GetGameObjectHandleByIndex(j, plHnd);
      [*] = ;            var pobj : Pointer = _misc_GetObjectArgData(goHnd, gc_argunit_obj);
      [*] = ;            if (pobj<>nil) and (not TObj(pobj).bdead) and GetGameObjectVisibleByHandle(goHnd) then
      [*] = ;            gGuiUpdateHighlights.Add(goHnd);
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      Log('gui:DoCreate this seems to be replay with 8 players max');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gInterface.gamemode=gc_gamemode_mainmenu) and (gint_campaign_exittomenu_status<>gc_campaign_exittomenu_status_none) then
      [*] = ;begin
      [*] = ;   gint_campaign_selectedcampaign := -1;
      [*] = ;   const cTagCampaign = 101;
      [*] = ;   _gui_SendTagToState('EventMainMenu', cTagCampaign);
      [*] = ;
      [*] = ;   gint_campaign_exittomenu_status := gc_campaign_exittomenu_status_none;
      [*] = ;   gstring_campaign_exittomenu_campname := '';
      [*] = ;   gstring_campaign_exittomenu_missname := '';
      [*] = ;
      [*] = ;   ExecuteState('ShowCampaign');
      [*] = ;end;
      [*] = ;
      [*] = ;gSerialLoaded:=false;
   struct.end
section.end

