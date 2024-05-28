section.begin
   Name = RegisterShortcuts
   Code : struct.begin
      [*] = ;var filter : String;
      [*] = ;if (gProfile.bDevMode) and (_net_IsOffline) and (not IsEngine) then
      [*] = ;filter := 'Alt';
      [*] = ;
      [*] = ;// OnCamera
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'CameraLeftR', 'Left' , filter, 'spiRepeat', 'OnCamera', 20);
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'CameraRightR', 'Right', filter, 'spiRepeat', 'OnCamera', 21);
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'CameraTopR', 'Up'   , filter, 'spiRepeat', 'OnCamera', 22);
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'CameraBotR', 'Down' , filter, 'spiRepeat', 'OnCamera', 23);
      [*] = ;
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'CameraLeftUp', 'Left' , filter, 'spiUp', 'OnCamera', 30);
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'CameraRightUp', 'Right', filter, 'spiUp', 'OnCamera', 30);
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'CameraTopUp', 'Up'   , filter, 'spiUp', 'OnCamera', 30);
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'CameraBotUp', 'Down' , filter, 'spiUp', 'OnCamera', 30);
      [*] = ;
      [*] = ;// OnMouseDown
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'LButton', 'LButton', '', 'spiDown', 'OnMouseDown', 0);
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'RButton', 'RButton', '', 'spiDown', 'OnMouseDown', 0);
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'MButton', 'MButton', '', 'spiDown', 'OnMouseDown', 0);
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'LButtonUp', 'LButton', '', 'spiUp', 'OnMouseDown', 0);
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'RButtonUp', 'RButton', '', 'spiUp', 'OnMouseDown', 0);
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'MButtonUp', 'MButton', '', 'spiUp', 'OnMouseDown', 0);
      [*] = ;
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'SpaceD', 'Space', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;
      [*] = ;// OnShortcuts
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Space', 'Space', 'Shift+Ctrl+Alt', 'spiUp', 'OnShortcut', 0);
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Escape', 'Escape', 'Shift+Ctrl+Alt', 'spiUp', 'OnShortcut', 0);
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Return', 'Return', 'Shift+Ctrl+Alt', 'spiUp', 'OnShortcut', 0);
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Ctrl+Return', 'Ctrl+Return', 'Shift+Ctrl+Alt', 'spiUp', 'OnShortcut', 0); // console
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'PrintScreen0', 'SNAPSHOT', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // should be spiDown, cause with spiUp, game deal 2 snapshots
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'PrintScreen1', 'Alt+SNAPSHOT', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // same as above
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'PrintScreen2', 'Ctrl+Alt+P', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // same as above
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Alt+F4', 'Alt+F4', 'Shift+Ctrl+Alt', 'spiUp', 'OnShortcut' , 0);
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'F10', 'F10', 'Shift+Ctrl+Alt', 'spiUp', 'OnShortcut', 0);
      [*] = ;//TOHOTKEYS//RegisterGUIShortcutIgnoreShift(False, 'A', 'A', 'Shift+Ctrl+Alt', 'spiRepeat', 'OnShortcut', 0); // go in attack mode
      [*] = ;//TOHOTKEYS//RegisterGUIShortcutIgnoreShift(False, 'Ctrl+A', 'Ctrl+A', 'Shift+Ctrl+Alt', 'spiRepeat', 'OnShortcut', 0); // need repeate, to update selected units, while shortcut is pressed
      [*] = ;//TOHOTKEYS//RegisterGUIShortcutIgnoreShift(False, 'Ctrl+Shift+A', 'Ctrl+Shift+A', 'Shift+Ctrl+Alt', 'spiRepeat', 'OnShortcut', 0); // need repeate, to update selected units, while shortcut is pressed
      [*] = ;//TOHOTKEYS//RegisterGUIShortcutIgnoreShift(False, 'Shift+A', 'Shift+A', 'Shift+Ctrl+Alt', 'spiRepeat', 'OnShortcut', 0); // need repeate, to update selected units, while shortcut is pressed
      [*] = ;//TOHOTKEYS//RegisterGUIShortcutIgnoreShift(False, 'Ctrl+Z', 'Ctrl+Z', 'Shift+Ctrl+Alt', 'spiRepeat', 'OnShortcut', 0); // same as above
      [*] = ;//TOHOTKEYS//RegisterGUIShortcutIgnoreShift(False, 'Shift+Z', 'Shift+Z', 'Shift+Ctrl+Alt', 'spiRepeat', 'OnShortcut', 0); // same as above
      [*] = ;//TOHOTKEYS//RegisterGUIShortcutIgnoreShift(False, 'Z', 'Z', 'Shift+Ctrl+Alt', 'spiRepeat', 'OnShortcut', 0); // same as above
      [*] = ;//TOHOTKEYS//RegisterGUIShortcutIgnoreShift(False, 'Ctrl+B', 'Ctrl+B', 'Shift+Ctrl+Alt', 'spiRepeat', 'OnShortcut', 0); // select all buildings
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Pause', 'Pause', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // pause
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Ctrl+Shift+P', 'Ctrl+Shift+P', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // pause
      [*] = ;//TOHOTKEYS//RegisterGUIShortcutIgnoreShift(False, 'Ctrl+P', 'Ctrl+P', 'Shift+Ctrl+Alt', 'spiRepeat', 'OnShortcut', 0); // select idle peasants without orders
      [*] = ;//TOHOTKEYS//RegisterGUIShortcutIgnoreShift(False, 'Ctrl+M', 'Ctrl+M', 'Shift+Ctrl+Alt', 'spiRepeat', 'OnShortcut', 0); // select idle mines
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Sub', 'Sub', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // decrease game speed
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Add', 'Add', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // increase game speed
      [*] = ;RegisterGUIShortcutIgnoreShift(False, '-', '-', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // decrease game speed
      [*] = ;RegisterGUIShortcutIgnoreShift(False, '=', '=', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // increase game speed
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'PGUP', 'PGUP', 'Shift+Ctrl+Alt', 'spiRepeat', 'OnShortcut', 0); // increase camera height
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'PGDN', 'PGDN', 'Shift+Ctrl+Alt', 'spiRepeat', 'OnShortcut', 0); // deccrease camera height
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Ctrl+PGUP', 'Ctrl+PGUP', 'Shift+Ctrl+Alt', 'spiRepeat', 'OnShortcut', 0); // increase camera fov
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Ctrl+PGDN', 'Ctrl+PGDN', 'Shift+Ctrl+Alt', 'spiRepeat', 'OnShortcut', 0); // deccrease camera fov
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Del', 'Del', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // kill selected units
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Home', 'Home', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // move camera to base
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Ctrl+Home', 'Ctrl+Home', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // move camera to base
      [*] = ;//TOHOTKEYS//RegisterGUIShortcutIgnoreShift(False, 'Ctrl+S', 'Ctrl+S', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // stop units
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'C', 'C', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // attach camera
      [*] = ;
      [*] = ;// gameplay
      [*] = ;//TOHOTKEYS//RegisterGUIShortcutIgnoreShift(False, 'S', 'S', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // stand ground
      [*] = ;//TOHOTKEYS//RegisterGUIShortcutIgnoreShift(False, 'V', 'V', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // free order
      [*] = ;//TOHOTKEYS//RegisterGUIShortcutIgnoreShift(False, 'D', 'D', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // disable attack
      [*] = ;//TOHOTKEYS//RegisterGUIShortcutIgnoreShift(False, 'E', 'E', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // enable attack
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'unit|patrol', 'P', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', -1); // patrol 
      [*] = ;//TOHOTKEYS//RegisterGUIShortcutIgnoreShift(False, 'G', 'G', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // guard
      [*] = ;
      [*] = ;// shifts
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Shift', 'Shift' , '', 'spiDown', 'OnShortcut', 0);
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'ShiftUp', 'Shift' , '', 'spiUp', 'OnShortcut', 0);
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Ctrl', 'Ctrl' , '', 'spiDown', 'OnShortcut', 0);
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'CtrlUp', 'Ctrl' , '', 'spiUp', 'OnShortcut', 0);
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Alt', 'Alt' , '', 'spiDown', 'OnShortcut', 0);
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'AltUp', 'Alt' , '', 'spiUp', 'OnShortcut', 0);
      [*] = ;
      [*] = ;// reserved
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Ctrl+Tab', 'Ctrl+Tab' , '', 'spiUp', 'OnShortcut', 0);
      [*] = ;
      [*] = ;// groups
      [*] = ;var i : Integer;
      [*] = ;for i:=0 to 9 do
      [*] = ;begin
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, IntToStr(i), IntToStr(i), 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Ctrl+'+IntToStr(i), 'Ctrl+'+IntToStr(i), 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Shift+'+IntToStr(i), 'Shift+'+IntToStr(i), 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;end;
      [*] = ;
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Back', 'Back', '', 'spiDown', 'OnShortcut', 0); // BackSpace
      [*] = ;if (not IsEngine) then
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'F7', 'F7', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;if (gProfile.bDevMode) then
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Ctrl+Shift+`', 'Ctrl+Shift+`', '', 'spiDown', 'OnShortcut', 0); // switch all cheats
      [*] = ;// Editor shortcuts
      [*] = ;if (gProfile.bDevMode) and (_net_IsOffline) and (not IsEngine){and ((gint_versionid=gc_versionid_dev) or (not IsEngine))} then
      [*] = ;begin
      [*] = ;   // Scenario
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'F4', 'F4', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'F2', 'F2', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'F3', 'F3', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'F9', 'F9', 'Shift+Ctrl+Alt', 'spiUp', 'OnShortcut', 0);
      [*] = ;
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Ctrl+Left', 'Ctrl+Left', '', 'spiRepeat', 'OnShortcut', 0); // move picked units
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Ctrl+Right', 'Ctrl+Right', '', 'spiRepeat', 'OnShortcut', 0); // move picked units
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Ctrl+Up', 'Ctrl+Up', '', 'spiRepeat', 'OnShortcut', 0); // move picked units
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Ctrl+Down', 'Ctrl+Down', '', 'spiRepeat', 'OnShortcut', 0); // move picked units
      [*] = ;
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Alt+Left', 'Alt+Left', '', 'spiRepeat', 'OnShortcut', 0); // interface debug hotkey
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Alt+Right', 'Alt+Right', '', 'spiRepeat', 'OnShortcut', 0); // interface debug hotkey
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Alt+Up', 'Alt+Up', '', 'spiRepeat', 'OnShortcut', 0); // interface debug hotkey
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Alt+Down', 'Alt+Down', '', 'spiRepeat', 'OnShortcut', 0); // interface debug hotkey
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Alt+,', 'Alt+,', '', 'spiRepeat', 'OnShortcut', 0); // interface debug hotkey
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Alt+.', 'Alt+.', '', 'spiRepeat', 'OnShortcut', 0); // interface debug hotkey
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Alt+Shift+Left', 'Alt+Shift+Left', '', 'spiRepeat', 'OnShortcut', 0); // interface debug hotkey
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Alt+Shift+Right', 'Alt+Shift+Right', '', 'spiRepeat', 'OnShortcut', 0); // interface debug hotkey
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Alt+Shift+Up', 'Alt+Shift+Up', '', 'spiRepeat', 'OnShortcut', 0); // interface debug hotkey
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Alt+Shift+Down', 'Alt+Shift+Down', '', 'spiRepeat', 'OnShortcut', 0); // interface debug hotkey
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Alt+Shift+,', 'Alt+Shift+,', '', 'spiRepeat', 'OnShortcut', 0); // interface debug hotkey
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Alt+Shift+.', 'Alt+Shift+.', '', 'spiRepeat', 'OnShortcut', 0); // interface debug hotkey
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Alt+/', 'Alt+/', '', 'spiRepeat', 'OnShortcut', 0); // interface debug hotkey
      [*] = ;
      [*] = ;   // Debug mode
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Ctrl+Shift+M', 'Ctrl+Shift+M', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // capture movie
      [*] = ;
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Ctrl+Del', 'Ctrl+Del', 'Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // force delete unit
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'F6', 'F6', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'F8', 'F8', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;   //RegisterGUIShortcutIgnoreShift(False, 'F11', 'F11', 'Shift+Ctrl+Alt', 'spiUp', 'OnShortcut', 0);
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Ctrl+F2', 'Ctrl+F2', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Ctrl+Shift+I', 'Ctrl+Shift+I', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;   //RegisterGUIShortcutIgnoreShift(False, 'M', 'M', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // show/hide minimap
      [*] = ;
      [*] = ;   {RegisterGUIShortcutIgnoreShift(False, '.', '.', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // debug animation change frame
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, ',', ',', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // debug animation change frame
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Shift+.', 'Shift+.', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // debug animation change frame
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Shift+,', 'Shift+,', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // debug animation change frame
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, '/', '/', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // debug animation play anim}
      [*] = ;
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Ctrl+F1', 'Ctrl+F1', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Ctrl+F2', 'Ctrl+F2', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Ctrl+F3', 'Ctrl+F3', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Ctrl+F4', 'Ctrl+F4', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Ctrl+Shift+F1', 'Ctrl+Shift+F1', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Ctrl+Shift+F2', 'Ctrl+Shift+F2', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Ctrl+Shift+F3', 'Ctrl+Shift+F3', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Ctrl+Shift+F4', 'Ctrl+Shift+F4', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;end;
      [*] = ;
      [*] = ;if (gInterface.gamemode=gc_gamemode_editor) or ((gProfile.bDevMode) and (_net_IsOffline) and (not IsEngine)) then
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'F11', 'F11', 'Shift+Ctrl+Alt', 'spiUp', 'OnShortcut', 0);
      [*] = ;
      [*] = ;for i:=1 to gc_MaxPlayerCount do
      [*] = ;begin
      [*] = ;   if i>9 then // support only num1..num9, and num0 is equal to num10. we dont have more keys.
      [*] = ;   begin
      [*] = ;      RegisterGUIShortcutIgnoreShift(False, 'NUM0', 'NUM0', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;      RegisterGUIShortcutIgnoreShift(False, 'Shift+Alt+0', 'Shift+Alt+0', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;      RegisterGUIShortcutIgnoreShift(False, 'Alt+0', 'Alt+0', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;      break;
      [*] = ;   end;
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'NUM'+IntToStr(i), 'NUM'+IntToStr(i), 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Shift+Alt+'+IntToStr(i), 'Shift+Alt+'+IntToStr(i), 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;   RegisterGUIShortcutIgnoreShift(False, 'Alt+'+IntToStr(i), 'Alt+'+IntToStr(i), 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;end;
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Shift+Alt+I', 'Shift+Alt+I', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Mul', 'Mul', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Shift+Alt+Mul', 'Shift+Alt+Mul', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Alt+Mul', 'Alt+Mul', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Ctrl+C', 'Ctrl+C', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // copy unit
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Ctrl+V', 'Ctrl+V', 'Shift+Ctrl+Alt', 'spiRepeat', 'OnShortcut', 0); // paste unit
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Ctrl+W', 'Ctrl+W', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // peace mode
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Ctrl+F', 'Ctrl+F', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // fog of war
      [*] = ;RegisterGUIShortcutIgnoreShift(False, '[', '[', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // decrease game speed
      [*] = ;RegisterGUIShortcutIgnoreShift(False, ']', ']', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // increase game speed
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Ctrl+Sub', 'Ctrl+Sub', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // decrease game speed
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'Ctrl+Add', 'Ctrl+Add', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // increase game speed
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'P', 'P', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0); // maximize place unit window
      [*] = ;
      [*] = ;if (IsEngine) then
      [*] = ;RegisterGUIShortcutIgnoreShift(False, 'F5', 'F5', 'Shift+Ctrl+Alt', 'spiDown', 'OnShortcut', 0);
      [*] = ;
      [*] = ;var pHotkeys : Integer = _parser_ParserTemporary(True);
      [*] = ;var bfileexists : Boolean = IsFileExists(GetAppSaveDirectoryPath+gc_filepath_hotkeys_relative);
      [*] = ;if (not bfileexists) then
      [*] = ;ParserLoadFromFileByHandle(pHotkeys, gc_filepath_hotkeys_default)
      [*] = ;else
      [*] = ;ParserLoadFromFileByHandle(pHotkeys, GetAppSaveDirectoryPath+gc_filepath_hotkeys_relative);
      [*] = ;
      [*] = ;for i:=0 to ParserGetCountByHandle(pHotkeys)-1 do
      [*] = ;begin
      [*] = ;   var pHotkey : Integer = ParserSelectByHandleByIndex(pHotkeys, i);
      [*] = ;   var hotkey : String = ParserGetValueByKeyByHandle(pHotkey, 'Key');
      [*] = ;   var alternativekey : String = ParserGetValueByKeyByHandle(pHotkey, 'AlternativeKey');
      [*] = ;   var action : String = ParserGetValueByKeyByHandle(pHotkey, 'Action');
      [*] = ;   if (action<>'') then
      [*] = ;   begin
      [*] = ;      if StrExists(action, 'event') then
      [*] = ;      action := action;
      [*] = ;      var brepeat : Boolean = ParserGetBoolValueByKeyByHandle(pHotkey, 'Repeat');
      [*] = ;      var bup : Boolean = ParserGetBoolValueByKeyByHandle(pHotkey, 'Up');
      [*] = ;      var presstype : String;
      [*] = ;      if (brepeat) then
      [*] = ;      presstype := 'spiRepeat'
      [*] = ;      else
      [*] = ;      if (bup) then
      [*] = ;      presstype := 'spiUp'
      [*] = ;      else
      [*] = ;      presstype := 'spiDown';
      [*] = ;      if (hotkey='') then
      [*] = ;      RegisterGUIShortcutIgnoreShift(False, action, 'nohotkey'+IntToStr(i), '', 'spiUp', 'OnShortcut', -1)
      [*] = ;      else
      [*] = ;      RegisterGUIShortcutIgnoreShift(False, action, hotkey, 'Shift+Ctrl+Alt', presstype, 'OnShortcut', -1);
      [*] = ;      if (alternativekey<>'') then
      [*] = ;      RegisterGUIShortcutIgnoreShift(False, action+'|alt', alternativekey, 'Shift+Ctrl+Alt', presstype, 'OnShortcut', -1);
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

