section.begin
   Name = OnTagStates
   Code : struct.begin
      [*] = ;args arg_res : TRes;
      [*] = ;args arg_stolist : TIntegerList;
      [*] = ;args arg_attlist : TIntegerList;
      [*] = ;args arg_ordlist : TIntegerList;
      [*] = ;
      [*] = ;var myHnd : Integer = GetGameObjectMyHandle;
      [*] = ;var oldState : Integer = GetGameObjectMyPrevStatesTag;
      [*] = ;var newState : Integer = GetGameObjectMyStatesTag;
      [*] = ;
      [*] = ;var iOldEssential : Integer = oldState and gc_statetag_essential;
      [*] = ;var iEssential : Integer = newState and gc_statetag_essential;
      [*] = ;var iOldVisual : Integer = oldState and gc_statetag_visual;
      [*] = ;var iVisual : Integer = newState and gc_statetag_visual;
      [*] = ;var switchEssential, switchVisual : Integer;
      [*] = ;if (iOldEssential<>iEssential) then switchEssential := iEssential;
      [*] = ;if (iOldVisual<>iEssential) then switchVisual := iEssential;
      [*] = ;
      [*] = ;//recheck:
      [*] = ;procedure SendPeasantsToNextRes;
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   for i:=arg_stolist.GetCount-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var trgHnd : Integer = arg_stolist.Get(i);
      [*] = ;      if (trgHnd<>0) then
      [*] = ;      _unit_SetSTO(trgHnd, 0);
      [*] = ;   end;
      [*] = ;   for i:=arg_ordlist.GetCount-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var trgHnd : Integer = arg_ordlist.Get(i);
      [*] = ;      if (trgHnd<>0) then
      [*] = ;      begin
      [*] = ;         var pobj2 : Pointer = _unit_GetTObj(trgHnd);
      [*] = ;         if (pobj2<>nil) then
      [*] = ;         begin
      [*] = ;            var j : Integer;
      [*] = ;            for j:=gc_obj_MaxOrderCount-1 downto 0 do
      [*] = ;            begin
      [*] = ;               if (TObj(pobj2).orders[j].info.trg=myHnd) then
      [*] = ;               _unit_SetOrderTrg(trgHnd, j, 0, True);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (switchEssential=gc_statetag_essential_death) and (arg_res.itype=gc_resource_type_wood) then
      [*] = ;begin
      [*] = ;   var rnd : Float = random;
      [*] = ;   var ind : Integer;
      [*] = ;   if rnd>0.9 then
      [*] = ;   ind := 2
      [*] = ;   else
      [*] = ;   if rnd>0.7 then
      [*] = ;   ind := 3
      [*] = ;   else
      [*] = ;   if rnd>0.20 then
      [*] = ;   ind := 1
      [*] = ;   else
      [*] = ;   ind := 4;
      [*] = ;//Following lines make pine,spruce, leaftrees,firs derp hard with textures on my mod (foreststype:taiga). Disabling for now.
      [*] = ;   {SetGameObjectLODActorNameByHandle(myHnd, 'pinestump');
      [*] = ;   SetGameObjectActorNameByHandle(myHnd, 'pinestump'+IntToStr(ind)+'.mesh');
      [*] = ;
      [*] = ;   SetGameObjectMaterialNameByHandle(myHnd, 'pinestump');
      [*] = ;   {if (ind=1) then
      [*] = ;   begin
      [*] = ;      rnd := 0.8+random*0.5;
      [*] = ;      var scaleX : float = GetGameObjectScaleXByHandle(myHnd)*rnd;
      [*] = ;      var scaleY : float = GetGameObjectScaleYByHandle(myHnd)*rnd;
      [*] = ;      var scaleZ : float = GetGameObjectScaleZByHandle(myHnd)*rnd;
      [*] = ;      SetGameObjectScaleByHandle(myHnd, scaleX, scaleY, scaleZ);
      [*] = ;   end;}
      [*] = ;   {SetGameObjectCollisionInertiaByHandle(myHnd, False);}
      [*] = ;end
      [*] = ;else
      [*] = ;if (arg_res.itype=gc_resource_type_food) then
      [*] = ;begin
      [*] = ;   if (iEssential=gc_statetag_essential_death) then
      [*] = ;   begin
      [*] = ;      SendPeasantsToNextRes();
      [*] = ;      arg_res.brised := False;
      [*] = ;      arg_res.hp := 0;
      [*] = ;      arg_res.timetransormlast := GetGameTime;
      [*] = ;      if (iVisual=gc_statetag_visual_stage_0) then
      [*] = ;      begin
      [*] = ;         arg_res.worktransorm := arg_res.worktransorm-1;
      [*] = ;         var material : String = GetGameObjectMyBaseName+'7';
      [*] = ;         if GetSeasonType=2 then
      [*] = ;         material := material+'w';
      [*] = ;         SetGameObjectMyMaterialName(material);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         ExecuteState('OnDestroy');
      [*] = ;         SetGameObjectOnStateDestroyByHandle(myHnd, '');
      [*] = ;         SetGameObjectCollisionDetectionByHandle(myHnd, False);
      [*] = ;         SetGameObjectPlayableObjectByHandle(myHnd, False);
      [*] = ;         SetGameObjectVisibleByHandle(myHnd, False);
      [*] = ;         GameObjectMyCancelDelayExecuteState;
      [*] = ;         GameObjectMyDelayExecuteState('DoDestroy', gc_unit_deathtime_3); // destroy on delay, to fix lan unsync if destory on tag change immidiatly, some time dont send tagstate to client.
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (iEssential=gc_statetag_essential_none) then
      [*] = ;   begin
      [*] = ;      arg_res.brised := True;
      [*] = ;      arg_res.timetransormlast := GetGameTime;
      [*] = ;      var suffix : String;
      [*] = ;      case iVisual of
      [*] = ;         gc_statetag_visual_stage_0 : suffix := '';
      [*] = ;         gc_statetag_visual_stage_1 : suffix := IntToStr(5);
      [*] = ;         gc_statetag_visual_stage_2 : suffix := IntToStr(6);
      [*] = ;      end;
      [*] = ;      if (iVisual=gc_statetag_visual_stage_0) then
      [*] = ;      arg_res.hp := gc_FieldMaxHP;
      [*] = ;      var material : String = GetGameObjectMyBaseName+suffix;
      [*] = ;      if GetSeasonType=2 then
      [*] = ;      material := material+'w';
      [*] = ;      SetGameObjectMyMaterialName(material);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (iEssential=gc_statetag_essential_birth) then
      [*] = ;   begin
      [*] = ;      arg_res.brised := False;
      [*] = ;      var stage : Integer;
      [*] = ;      case iVisual of
      [*] = ;         gc_statetag_visual_stage_0 : stage := 1;
      [*] = ;         gc_statetag_visual_stage_1 : stage := 2;
      [*] = ;         gc_statetag_visual_stage_2 : stage := 3;
      [*] = ;         gc_statetag_visual_stage_3 : stage := 4;
      [*] = ;      end;
      [*] = ;      var material : String = GetGameObjectMyBaseName+IntToStr(stage);
      [*] = ;      if GetSeasonType=2 then
      [*] = ;      material := material+'w';
      [*] = ;      SetGameObjectMyMaterialName(material);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

