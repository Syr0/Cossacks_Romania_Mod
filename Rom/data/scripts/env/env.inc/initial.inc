section.begin
   Name = Initial
   Code : struct.begin
      [*] = ;args arg_res : TRes;
      [*] = ;args arg_stolist : TIntegerList;
      [*] = ;args arg_attlist : TIntegerList;
      [*] = ;args arg_ordlist : TIntegerList;
      [*] = ;
      [*] = ;var myHnd : Integer = GetGameObjectMyHandle;
      [*] = ;
      [*] = ;SetGameObjectMyOnStateEndFrameReached('');
      [*] = ;SetGameObjectOnStateDestroyByHandle(myHnd, 'OnDestroy');
      [*] = ;
      [*] = ;SetGameObjectDeferredFrameBlendByHandle(myHnd, false);
      [*] = ;
      [*] = ;if (gSerialMode=0) and (GetGameObjectUniqueIdByHandle(myHnd)=0) then
      [*] = ;begin
      [*] = ;   GameObjectMakeUniqId(myHnd);
      [*] = ;
      [*] = ;   SetGameObjectMyOnStateEndPointReached('');
      [*] = ;   SetGameObjectMyOnStateDirectionReached('');
      [*] = ;   SetGameObjectMyOnStateEndCyclesReached('');
      [*] = ;   //SetGameObjectMyOnStateEndFrameReached('');
      [*] = ;   //SetGameObjectOnStateDestroyByHandle(myHnd, 'OnDestroy');
      [*] = ;   SetGameObjectMyStateTargetPosition(GetGameObjectMyPositionX, GetGameObjectMyPositionY, GetGameObjectMyPositionZ);
      [*] = ;   GameObjectMyTrackPointClear;
      [*] = ;   SetGameObjectMyTrackPointMovementMode('mmNone');
      [*] = ;   SetGameObjectMyTargetRotatingMode('trmNone');
      [*] = ;   //SetGameObjectMyAnimationControlerEnabled(true);
      [*] = ;   SetGameObjectMyPlayableObject(True);
      [*] = ;   SetGameObjectMyCollisionDetection(True);
      [*] = ;   SetGameObjectCollisionInertiaByHandle(myHnd, True);
      [*] = ;   SetGameObjectCIMovableByHandle(myHnd, False);
      [*] = ;   //SetGameObjectCIIntersectRadiusByHandle(myHnd, 0);
      [*] = ;   _unit_SetSTO(myHnd, 0);
      [*] = ;   //SetGameObjectDeferredFrameBlendByHandle(myHnd, false);
      [*] = ;
      [*] = ;   //GameObjectMySwitchToTreeAnimationCycles(gc_anim_idle, false, false, false, false);
      [*] = ;   //GameObjectSwitchToFrameAnimationByHandle(myHnd, gc_anim_idle, True);
      [*] = ;   //SetGameObjectMyCurrentFrame(floor(Random*GetGameObjectEndFrameByHandle(myHnd)-1));
      [*] = ;
      [*] = ;   var restype : Integer = gc_resource_type_none;
      [*] = ;   var basename : String = GetGameObjectMyBaseName;
      [*] = ;
      [*] = ;   // hardcoded for fast 30.09 version
      [*] = ;   var bdesert : Boolean;
      [*] = ;   case basename of
      [*] = ;      gc_basename_field : restype := gc_resource_type_food;
      [*] = ;      'minegold', 'minegolds' : restype := gc_resource_type_gold;
      [*] = ;      'mineiron', 'mineirons' : restype := gc_resource_type_iron;
      [*] = ;      'minecoal', 'minecoals' : restype := gc_resource_type_coal;
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (StrExists(basename, 'stones') or StrExists(basename, 'rocks')) and (not StrExists(basename, 'sea')) then
      [*] = ;         restype := gc_resource_type_stone
      [*] = ;         else
      [*] = ;         if ({not }StrExists(basename, 'broken')) or {and} (StrExists(basename, 'leaftree') or (StrExists(basename, 'spruce') or StrExists(basename, 'beech') or StrExists(basename, 'birch') or StrExists(basename, 'cypress') or StrExists(basename, 'maple') or StrExists(basename, 'olive') or StrExists(basename, 'poplar') or StrExists(basename, 'willow') or StrExists(basename, 'dry.tree') or StrExists(basename, 'fir') or StrExists(basename, 'burch') or StrExists(basename, 'pine') or StrExists(basename, 'oak') or StrExists(basename, 'drytree'))) then
      [*] = ;         restype := gc_resource_type_wood
      [*] = ;         else
      [*] = ;         if (StrExists(basename, 'palm') and (not StrExists(basename, 'palmsmall'))) or (StrExists(basename, 'desert')) then
      [*] = ;         begin
      [*] = ;            bdesert := True;
      [*] = ;            restype := gc_resource_type_wood;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         SetGameObjectCollisionDetectionByHandle(myHnd, False);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   _res_Init(arg_res, resType);
      [*] = ;   _res_ResGridAdd(myHnd);
      [*] = ;
      [*] = ;   var progress : Integer;
      [*] = ;   case restype of
      [*] = ;      gc_resource_type_wood : begin
      [*] = ;         _unit_SetTagStates(myHnd, gc_statetag_essential_none);
      [*] = ;         //if (not bdesert) then
      [*] = ;         //begin
      [*] = ;            var rnd : Float = random;
      [*] = ;            if (rnd>0.8) then
      [*] = ;            arg_res.hp := floor(8000*(1+random))
      [*] = ;            else
      [*] = ;            if (rnd>0.65) then
      [*] = ;            arg_res.hp := floor(125*(1+random*4))
      [*] = ;            else
      [*] = ;            if (rnd<0.2) then
      [*] = ;            arg_res.hp := 10
      [*] = ;            else
      [*] = ;            arg_res.hp := floor(10+rnd*(0.5+random*0.5)*100);
      [*] = ;         //end
      [*] = ;         //else
      [*] = ;         //arg_res.hp := 10000000;
      [*] = ;      end;
      [*] = ;      gc_resource_type_stone : begin
      [*] = ;         _unit_SetTagStates(myHnd, gc_statetag_essential_none);
      [*] = ;         arg_res.hp := 10000000;
      [*] = ;      end;
      [*] = ;      gc_resource_type_food : begin
      [*] = ;         _unit_SetTagStates(myHnd, gc_statetag_essential_birth or gc_statetag_visual_stage_0);
      [*] = ;         arg_res.timetransormlast := GetGameTime;
      [*] = ;         arg_res.hp := 0;
      [*] = ;         arg_res.brised := False;
      [*] = ;         arg_res.worktransorm := 1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if (restype=gc_resource_type_wood) or (restype=gc_resource_type_stone) then
      [*] = ;   SetGameObjectMyStateMachineInterval(0);
      [*] = ;   if (GetGameObjectMyPositionX>(GetMapWidth div 2)) or (GetGameObjectMyPositionX<(-GetMapWidth div 2)) or (GetGameObjectMyPositionZ>(GetMapHeight div 2)) or (GetGameObjectMyPositionZ<(-GetMapHeight div 2)) then
      [*] = ;   begin
      [*] = ;      //GameObjectRequestToDestroyByHandle(myHnd);
      [*] = ;      //Log('unit : Initial : obj out of map. removed');
      [*] = ;   end;
      [*] = ;
      [*] = ;   //if (GetMapCollisionTag(GetGameObjectMyPositionX, GetGameObjectMyPositionZ, True))>0 then
      [*] = ;   //GameObjectRequestToDestroyByHandle(myHnd);
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

