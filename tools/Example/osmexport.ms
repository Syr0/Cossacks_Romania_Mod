-------------------------------------
--OSM Exporter
--Version 2.0 for max 2013
-------------------------------------

global osmLastfile=""
global osmExport
global nlist=#([-0.525731, 0.000000, 0.850651],[-0.442863, 0.238856, 0.864188],[-0.295242, 0.000000, 0.955423],[-0.309017, 0.500000, 0.809017],[-0.162460, 0.262866, 0.951056],[0.000000, 0.000000, 1.000000],[0.000000, 0.850651, 0.525731],[-0.147621, 0.716567, 0.681718],[0.147621, 0.716567, 0.681718],[0.000000, 0.525731, 0.850651],[0.309017, 0.500000, 0.809017],[0.525731, 0.000000, 0.850651],[0.295242, 0.000000, 0.955423],[0.442863, 0.238856, 0.864188],[0.162460, 0.262866, 0.951056],[-0.681718, 0.147621, 0.716567],[-0.809017, 0.309017, 0.500000],[-0.587785, 0.425325, 0.688191],[-0.850651, 0.525731, 0.000000],[-0.864188, 0.442863, 0.238856],[-0.716567, 0.681718, 0.147621],[-0.688191, 0.587785, 0.425325],[-0.500000, 0.809017, 0.309017],[-0.238856, 0.864188, 0.442863],[-0.425325, 0.688191, 0.587785],[-0.716567, 0.681718, -0.147621],[-0.500000, 0.809017, -0.309017],[-0.525731, 0.850651, 0.000000],[0.000000, 0.850651, -0.525731],[-0.238856, 0.864188, -0.442863],[0.000000, 0.955423, -0.295242],[-0.262866, 0.951056, -0.162460],[0.000000, 1.000000, 0.000000],[0.000000, 0.955423, 0.295242],[-0.262866, 0.951056, 0.162460],[0.238856, 0.864188, 0.442863],[0.262866, 0.951056, 0.162460],[0.500000, 0.809017, 0.309017],[0.238856, 0.864188, -0.442863],[0.262866, 0.951056, -0.162460],[0.500000, 0.809017, -0.309017],[0.850651, 0.525731, 0.000000],[0.716567, 0.681718, 0.147621],[0.716567, 0.681718, -0.147621],[0.525731, 0.850651, 0.000000],[0.425325, 0.688191, 0.587785],[0.864188, 0.442863, 0.238856],[0.688191, 0.587785, 0.425325],[0.809017, 0.309017, 0.500000],[0.681718, 0.147621, 0.716567],[0.587785, 0.425325, 0.688191],[0.955423, 0.295242, 0.000000],[1.000000, 0.000000, 0.000000],[0.951056, 0.162460, 0.262866],[0.850651, -0.525731, 0.000000],[0.955423, -0.295242, 0.000000],[0.864188, -0.442863, 0.238856],[0.951056, -0.162460, 0.262866],[0.809017, -0.309017, 0.500000],[0.681718, -0.147621, 0.716567],[0.850651, 0.000000, 0.525731],[0.864188, 0.442863, -0.238856],[0.809017, 0.309017, -0.500000],[0.951056, 0.162460, -0.262866],[0.525731, 0.000000, -0.850651],[0.681718, 0.147621, -0.716567],[0.681718, -0.147621, -0.716567],[0.850651, 0.000000, -0.525731],[0.809017, -0.309017, -0.500000],[0.864188, -0.442863, -0.238856],[0.951056, -0.162460, -0.262866],[0.147621, 0.716567, -0.681718],[0.309017, 0.500000, -0.809017],[0.425325, 0.688191, -0.587785],[0.442863, 0.238856, -0.864188],[0.587785, 0.425325, -0.688191],[0.688191, 0.587785, -0.425325],[-0.147621, 0.716567, -0.681718],[-0.309017, 0.500000, -0.809017],[0.000000, 0.525731, -0.850651],[-0.525731, 0.000000, -0.850651],[-0.442863, 0.238856, -0.864188],[-0.295242, 0.000000, -0.955423],[-0.162460, 0.262866, -0.951056],[0.000000, 0.000000, -1.000000],[0.295242, 0.000000, -0.955423],[0.162460, 0.262866, -0.951056],[-0.442863, -0.238856, -0.864188],[-0.309017, -0.500000, -0.809017],[-0.162460, -0.262866, -0.951056],[0.000000, -0.850651, -0.525731],[-0.147621, -0.716567, -0.681718],[0.147621, -0.716567, -0.681718],[0.000000, -0.525731, -0.850651],[0.309017, -0.500000, -0.809017],[0.442863, -0.238856, -0.864188],[0.162460, -0.262866, -0.951056],[0.238856, -0.864188, -0.442863],[0.500000, -0.809017, -0.309017],[0.425325, -0.688191, -0.587785],[0.716567, -0.681718, -0.147621],[0.688191, -0.587785, -0.425325],[0.587785, -0.425325, -0.688191],[0.000000, -0.955423, -0.295242],[0.000000, -1.000000, 0.000000],[0.262866, -0.951056, -0.162460],[0.000000, -0.850651, 0.525731],[0.000000, -0.955423, 0.295242],[0.238856, -0.864188, 0.442863],[0.262866, -0.951056, 0.162460],[0.500000, -0.809017, 0.309017],[0.716567, -0.681718, 0.147621],[0.525731, -0.850651, 0.000000],[-0.238856, -0.864188, -0.442863],[-0.500000, -0.809017, -0.309017],[-0.262866, -0.951056, -0.162460],[-0.850651, -0.525731, 0.000000],[-0.716567, -0.681718, -0.147621],[-0.716567, -0.681718, 0.147621],[-0.525731, -0.850651, 0.000000],[-0.500000, -0.809017, 0.309017],[-0.238856, -0.864188, 0.442863],[-0.262866, -0.951056, 0.162460],[-0.864188, -0.442863, 0.238856],[-0.809017, -0.309017, 0.500000],[-0.688191, -0.587785, 0.425325],[-0.681718, -0.147621, 0.716567],[-0.442863, -0.238856, 0.864188],[-0.587785, -0.425325, 0.688191],[-0.309017, -0.500000, 0.809017],[-0.147621, -0.716567, 0.681718],[-0.425325, -0.688191, 0.587785],[-0.162460, -0.262866, 0.951056],[0.442863, -0.238856, 0.864188],[0.162460, -0.262866, 0.951056],[0.309017, -0.500000, 0.809017],[0.147621, -0.716567, 0.681718],[0.000000, -0.525731, 0.850651],[0.425325, -0.688191, 0.587785],[0.587785, -0.425325, 0.688191],[0.688191, -0.587785, 0.425325],[-0.955423, 0.295242, 0.000000],[-0.951056, 0.162460, 0.262866],[-1.000000, 0.000000, 0.000000],[-0.850651, 0.000000, 0.525731],[-0.955423, -0.295242, 0.000000],[-0.951056, -0.162460, 0.262866],[-0.864188, 0.442863, -0.238856],[-0.951056, 0.162460, -0.262866],[-0.809017, 0.309017, -0.500000],[-0.864188, -0.442863, -0.238856],[-0.951056, -0.162460, -0.262866],[-0.809017, -0.309017, -0.500000],[-0.681718, 0.147621, -0.716567],[-0.681718, -0.147621, -0.716567],[-0.850651, 0.000000, -0.525731],[-0.688191, 0.587785, -0.425325],[-0.587785, 0.425325, -0.688191],[-0.425325, 0.688191, -0.587785],[-0.425325, -0.688191, -0.587785],[-0.587785, -0.425325, -0.688191],[-0.688191, -0.587785, -0.425325])

fn addcheck cb =
(
	if classof cb==string do messagebox cb title:"OSM Export Error"
)

struct OSM_Color
(
	r, g, b, a
)

struct OSM_Tex
(
	s,t
)

struct OSM_Vertex
(
	pos, lightNormalIndex
)

struct OSM_Frame
(
	name, vList, vNorm
)

struct OSM_Tri
(
	v1,v2,v3,	--vertIndices
	t1,t2,t3	--texCoordIndices
)

struct OSM_model
(
	skinlist,
	texlist,
	trilist,
	framelist,
	colorlist
)

fn makeOSM object =
(
	if OSMexport.useanim.state==1 then
	(
		astart=animationrange.start
		aend=animationrange.end
	)
	else
	(
		astart=OSMexport.animstart.value
		aend=OSMexport.animend.value
	)
	if not(OSMexport.oneframe.state) do
	(
		astart=0
		aend=0
	)
	if (OSMexport.savevertexcolors.state) then
	(
		usevcolor=1
	)
	else
	(
		usevcolor=0
	)
	
	obj=(object)
	OSM=OSM_model skinlist:#("SkinBitMap") texlist:#() trilist:#() framelist:#() colorlist:#()

	------------------------------------
	-- build texture vert list
	------------------------------------
	for i=1 to getnumtverts obj do
	(
		s=((getTVert obj i).x)
		t=(-(getTVert obj i).y+1)
		append OSM.texlist (OSM_tex s:s t:t)
	)

	------------------------------------
	-- build triangle list
	------------------------------------
	for i=1 to obj.numfaces do
	(
		v1=((getFace obj i).z)-1
		v2=((getFace obj i).y)-1
		v3=((getFace obj i).x)-1
		t1=((getTVFace obj i).z)-1
		t2=((getTVface obj i).y)-1
		t3=((getTVface obj i).x)-1
		append OSM.trilist (OSM_Tri v1 v2 v3 t1 t2 t3)
	)

	-------------------------------------
	-- build frame list
	-------------------------------------
	--print astart
	--print aend
	for f=astart to aend by OSMexport.stepframe.value do 
	(
		local vertlist=#()
		local normlist=#()
		frame=OSM_frame name:"FRAME 000......"
	
		for i=1 to obj.numverts do at time f
		(
			if (OSMexport.inversetransformation.state) then
			(
				local v=in coordsys world (getvert obj i) * (inverse obj.objectTransform) * obj.objectTransform.scale
			)
			else
			(
				local v=in coordsys world (getvert obj i)
			)
			append vertlist v
			------------------------------------
			--do normals
			------------------------------------
			local vn=in coordsys world (getnormal obj i)
			local maxdot=-99999.0
			local normindex=1
			if OSMexport.donormals.state do
			for j=1 to nlist.count do
			(
				local dotvalue
				dotvalue=dot nlist[j] vn
				if dotvalue>maxdot do
				(
					maxdot=dotvalue
					normindex=j
				)
			)
			append normlist normindex
		)
		frame.vList=vertlist
		frame.vNorm=normlist
		append OSM.framelist frame
	)

	------------------------------------
	-- build color vert list
	------------------------------------
	if usevcolor==1 do
	(
		for i=1 to obj.numverts do at time astart
		(
			append OSM.colorlist (OSM_Color 1 1 1 1)
		)

		for i=1 to obj.numfaces do
		(
			vi1=(getFace obj i).z
			vi2=(getFace obj i).y
			vi3=(getFace obj i).x
			ci1=(getVCFace obj i).z
			ci2=(getVCFace obj i).y
			ci3=(getVCFace obj i).x

			r=(GetVertColor obj ci1).r
			g=(GetVertColor obj ci1).g
			b=(GetVertColor obj ci1).b
			a=(GetVertColor obj ci1).a

			OSM.colorlist[vi1].r=r/255
			OSM.colorlist[vi1].g=g/255
			OSM.colorlist[vi1].b=b/255
			OSM.colorlist[vi1].a=a/255

			r=(GetVertColor obj ci2).r
			g=(GetVertColor obj ci2).g
			b=(GetVertColor obj ci2).b
			a=(GetVertColor obj ci2).a

			OSM.colorlist[vi2].r=r/255
			OSM.colorlist[vi2].g=g/255
			OSM.colorlist[vi2].b=b/255
			OSM.colorlist[vi2].a=a/255

			r=(GetVertColor obj ci3).r
			g=(GetVertColor obj ci3).g
			b=(GetVertColor obj ci3).b
			a=(GetVertColor obj ci3).a

			OSM.colorlist[vi3].r=r/255
			OSM.colorlist[vi3].g=g/255
			OSM.colorlist[vi3].b=b/255
			OSM.colorlist[vi3].a=a/255

			--OSM.colorlist[vi2]=GetVertColor obj ci2
			--OSM.colorlist[vi3]=GetVertColor obj ci3
		)
	)		
OSM
)

fn writeOSM obj OSMfile =
(
	if obj==undefined do return "No object"
	if (classof obj)!=editable_mesh do return "Object is not a mesh"
	model=makeOSM obj
	
	f=fopen OSMfile "wb"
	
	----------------------------------------
	-- write the header
	----------------------------------------
	
	magic=844121161
	version=8
	skinw=256
	skinh=256
	framenum=model.framelist.count
	skinnum=model.skinlist.count
	vertnum=model.framelist[1].vlist.count
	texnum=model.texlist.count
	trinum=model.trilist.count
	glnum=0

	texsize=8
	trisize=24
	framesize=16+(16*vertnum)

	headersize=68	-- bytes in header
	offsetskins=headersize
	offsettexcoords=offsetskins+(skinnum*64)
	offsettris=offsettexcoords+(texnum*texsize)
	offsetframes=offsettris+(trinum*trisize)
	offsetgl=offsetframes+(framenum*framesize)
	offsetend=offsetgl+(glnum*4)

	writelong f magic
	writelong f version
	writelong f skinw	--(blitz dont care)
	writelong f skinh	--(blitz dont care)
	writelong f framesize
	writelong f skinnum
	writelong f vertnum
	writelong f texnum
	writelong f trinum
	writelong f glnum
	writelong f framenum
	writelong f offsetskins		--offset to skins
	writelong f offsettexcoords	--offset to texture coords
	writelong f offsettris		--offset to triangles
	writelong f offsetframes	--offset to frames
	writelong f offsetgl		--offset to gl commands
	writelong f offsetend		--offset to end

	-----------------------------------------------------
	-- end of header
	-----------------------------------------------------
	-- write out the skin names
	-----------------------------------------------------
	for i in model.skinlist do
	(
		skinname=i
		while skinname.count<63 do skinname+=":"
		writestring f skinname
	)

	-----------------------------------------------------
	-- write texture coordinate list
	-----------------------------------------------------
	for i in model.texlist do
	(
		writefloat f i.s
		writefloat f i.t
	)

	-----------------------------------------------------
	--write triangles
	-----------------------------------------------------
	for i in model.trilist do
	(
		writelong f i.v1
		writelong f i.v2
		writelong f i.v3
		writelong f i.t1
		writelong f i.t2
		writelong f i.t3
	)

	-----------------------------------------------------
	-- write frames
	-----------------------------------------------------
	for i in model.framelist do
	(
		writestring f i.name
		k=0
		for j=1 to i.vlist.count do
		(
			writefloat f i.vlist[j].x
			writefloat f i.vlist[j].y
			writefloat f i.vlist[j].z
			writelong f i.vNorm[j]
		)
	)

	-----------------------------------------------------
	-- write colors
	-----------------------------------------------------	
	for i in model.colorlist do
	(
		writefloat f i.r
		writefloat f i.g
		writefloat f i.b
		writefloat f i.a
	)

	------------------------------------------------------
	-- end of file writing
	------------------------------------------------------
	fclose f
)

utility osmExport "OSM Exporter"
(
	group "Export"
	(
		checkbox inversetransformation "Inverse transformation" checked:false align:#center
		checkbox oneframe "Save Animation" checked:false align:#center
		spinner stepframe "Frame Step" range:[1,200,1] fieldwidth:40 type:#integer
		radiobuttons useanim labels:#("Active Time Segment","Custom Time Segment")
		spinner animstart range:[0,10000,0] type:#integer fieldwidth:40 across:2
		spinner animend "to" range:[0,10000,40] type:#integer fieldwidth:40
		checkbox donormals "Generate Normals" align:#center checked:false
		checkbox savevertexcolors "Save Vertex Colors" checked:false align:#center
		button bexport  "    Export    "
		button bmexport "  MultExport  "
	)

	group "About"
	(
		label titleLabel	"OSM Exporter v2.0"
		HyperLink addy "by Cossacks3" align:#center address:"mailto:support@cossacks3.com" color:(color 0 100 0) hoverColor:(color 0 0 100)
		HyperLink me "cossacks3.com" align:#center address:"http://cossacks3.com/" color:(color 0 100 0) hoverColor:(color 0 0 100)

	)

	on bexport pressed do
	(
		osmFilename=getsavefilename caption:"Save OSM" \
			filename:osmLastfile \
			types:"osm (*.osm)|*.osm|All Files (*.*)|*.*|"
		if osmFilename!=undefined do
		(
			addcheck (writeOSM $ osmFilename)
			osmLastfile=osmFilename
		)
	)

	on bmexport pressed do
	(
		for mesh in Objects do
		if (classOf mesh != BoneGeometry)  and (classOf mesh != Biped_Object) and (canConvertTo mesh TriMeshGeometry) then
		(
			osmFilename = ((GetDir #export)+"/"+mesh.name+".osm")
			addcheck (writeOSM mesh osmFilename)
		)
	)
)
--print nlist.count