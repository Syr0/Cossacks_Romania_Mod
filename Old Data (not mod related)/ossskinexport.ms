-------------------------------------
--OSS Skin Exporter
--Version 2.0 for max 2013
-------------------------------------

global ossLastfile=""
global ossSkinExport

fn addcheck cb =
(
	if classof cb==string do messagebox cb title:"OSS Export Error"
)

-- find bone indices by name
fn FindBone Name bones =
(
	for i = 1 to bones.count do
		if bones[i].Name == Name then
			return (i - 1)
)

fn PrepareMaxForSkinOps _pNode =
(
	-- Select @_pNode if needed.
	if not _pNode.IsSelected do
	(
		Select _pNode
	)

	-- Unfreeze @_pNode if needed.
	if _pNode.IsFrozen do
	(
		Unfreeze _pNode DoLayer:true
	)

	-- Set Modify Panel active if needed.
	if GetCommandPanelTaskMode() != #modify do
	(
		SetCommandPanelTaskMode mode:#modify
	)

	-- Set @_pNode skin modifier as current object in modpanel if needed.
	if ModPanel.GetCurrentObject() != _pNode.skin do
	(
		ModPanel.SetCurrentObject _pNode.skin
	)
)

fn writeOSS FileName =
(
	if ossSkinExport.useanim.state==1 then
	(
		astart=animationRange.start
		aend=animationRange.end
	)
	else
	(
		astart=ossSkinExport.animStart.value
		aend=ossSkinExport.animEnd.value
	)

	-- find mesh and bones
	bones = #()
		
	mesh = undefined
	skin = 0
	sel = selection as array  -- snapshot selection
	-- for obj in objects do  -- loop for objects
	for obj in sel do  -- loop for selection
		if ((classOf obj) == BoneGeometry) or ((classOf obj) == Biped_Object) then
			append bones obj
		else
		if (canConvertTo obj TriMeshGeometry) then
			if mesh == undefined then
				for i = 1 to obj.modifiers.count do -- look for modifier Skin
					if obj.modifiers[i].Name == "Skin" then
					(
						mesh = obj
						skin = obj.modifiers[i]
					)


	-- save to file
	-- FileName = GetSaveFileName types:"Skinned Mesh Animation (*.oss)|*.oss|"
	if (FileName != undefined) and (mesh != undefined) and (skin != undefined) then
	(
		-- set modify to Skin
		--max modify mode
		--modPanel.setCurrentObject skin
		-- export mesh
		-- start = animationRange.start.frame as integer -- start frame
		-- end = animationRange.end.frame as integer -- end frame
		start = astart
		end = aend
		FPS = frameRate -- FPS
		-- K_Count = (end - start + 1) -- animation frame count
		K_Count = 0
		for i=start to end by ossSkinExport.stepframe.value do K_Count = K_Count + 1

		file = fopen FileName "wb"
		--==// MESH HEADER //==--
		B_Count = bones.count    -- count of bones
		V_Count = mesh.numVerts  -- count of vertices
		F_Count = mesh.numFaces  -- count of faces
		T_Count = mesh.numTVerts -- count of tex coords

		-- save header to file
		WriteLong file K_Count
		WriteLong file FPS
		WriteLong file B_Count
		WriteLong file V_Count
		WriteLong file F_Count
		WriteLong file T_Count

		--==// GEOMETRY //==--
		--at time start
		at time ossSkinExport.animStatic.value
		for i = 1 to V_Count do
		(
			p = (GetVert mesh i)
			WriteFloat file p.x
			WriteFloat file p.y
			WriteFloat file p.z
		)
		-- save faces to file
		for i = 1 to F_Count do
		(
			f = (GetFace mesh i) - [1, 1, 1]
			WriteLong file (f.x as Integer)
			WriteLong file (f.y as Integer)
			WriteLong file (f.z as Integer)
		)
		-- save texcoords to file
		for i = 1 to T_Count do
		(
			t = (GetTVert mesh i)
			WriteFloat file t.x
			WriteFloat file (1 - t.y) -- inverse Y coord
		)
		-- save texfaces to file
		for i = 1 to F_Count do
		(
			f = (GetTVFace mesh i) - [1, 1, 1]
			WriteLong file (f.x as Integer)
			WriteLong file (f.y as Integer)
			WriteLong file (f.z as Integer)
		)

		--==// WEIGHTS //==--
		SetCommandPanelTaskMode mode:#modify
		PrepareMaxForSkinOps mesh
		for i = 1 to V_Count do
		(
			-- bones per vertex
			W_Count = skinOps.getVertexWeightCount skin i

			RW_Count = 0
			for j = 1 to W_Count do
			(
				weight = (skinOps.getVertexWeight skin i j)
				if (weight > 0) then
					RW_Count = RW_Count + 1
			)

			WriteLong file RW_Count
			for j = 1 to W_Count do
			(
				-- weigth
				weight = (skinOps.getVertexWeight skin i j)
				if (weight > 0) then
				(
					-- get name of bone
					name = skinOps.GetBoneName skin (skinOps.getVertexWeightBoneID skin i j) 0
					-- get if of bone
					ID = (FindBone name bones)
					WriteLong file ID
					WriteFloat file weight
				)
			)
		)
		SetCommandPanelTaskMode mode:#utility
		--==// ANIMATION //==--
		for bone in bones do
		(
			--at time start m0 = (inverse bone.objectTransform)
			at time ossSkinExport.animStatic.value m0 = (inverse bone.objectTransform)
			for frame = start to end by ossSkinExport.stepframe.value do
				at time frame
				(
					-- calculate rotation matrix
					m = m0 * bone.objectTransform
					p = m.Position
					r = m.Rotation
					-- position
					WriteFloat file p.x
					WriteFloat file p.y
					WriteFloat file p.z
					-- quaternion
					WriteFloat file r.x
					WriteFloat file r.y
					WriteFloat file r.z
					WriteFloat file r.w
				)
		)
		fclose file
		-- print "skin Model Conveted"
	)
)

utility ossSkinExport "OSS Skin Exporter"
(
	group "Export"
	(
		spinner stepframe "Frame Step" range:[1,200,1] fieldwidth:40 type:#integer
		radiobuttons useanim labels:#("Active Time Segment","Custom Time Segment")
		spinner animstart range:[0,10000,0] type:#integer fieldwidth:40 across:2
		spinner animend "to" range:[0,10000,40] type:#integer fieldwidth:40
		spinner animstatic "Static" range:[0,10000,0] type:#integer fieldwidth:40
		button bexport "     Export    "
	)
	group "About"
	(
		label titleLabel	"OSS Skin Exporter v2.0"
		HyperLink addy "by Cossacks3" align:#center address:"mailto:support@cossacks3.com" color:(color 0 100 0) hoverColor:(color 0 0 100)
		HyperLink me "cossacks3.com" align:#center address:"http://cossacks3.com/" color:(color 0 100 0) hoverColor:(color 0 0 100)

	)

	on bexport pressed do
	(
		ossFilename=getsavefilename caption:"Save OSS" \
			filename:ossLastfile \
			types:"oss (*.oss)|*.oss|All Files (*.*)|*.*|"
		if ossFilename!=undefined do
		(
			addcheck (writeOSS ossFilename)
			ossLastfile=ossFilename
		)
	)
)