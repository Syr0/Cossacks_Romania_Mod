global tlfLastfile=""
global tlfExport

fn addcheck cb =
(
	if classof cb==string do messagebox cb title:"TLF Export Error"
)

fn writeTLF obj TLFfile =
(
	if obj==undefined do return"No object"
	if (classof obj)!=editable_mesh do return "Object is not a mesh"

	--convertTo (obj = copy obj) TriMeshGeometry
	
	--f=fopen TLFfile "wb"
	f = CreateFile TLFfile

	if TLFexport.useanim.state==1 then 
	(
		astart=animationrange.start
		aend=animationrange.end
	)
	else
	(
		astart=TLFexport.animstart.value
		aend=TLFexport.animend.value
	)

	for i=astart to aend by TLFexport.stepframe.value do 
	(
		at time i
		(
			--p = in coordsys world (obj.objectTransform.position)
			--q = in coordsys world (obj.objectTransform.rotation)
			p = obj.objectTransform.position
			q = obj.objectTransform.rotation
		)
		Format ("% % %\n") p.x p.y p.z to:f
		Format ("% % % %\n") q.x q.y q.z q.w to:f
		--print p
		--print q
	)

	close f

	--delete obj
)

utility tlfExport "TLF Exporter"
(
	group "Export"
	(
		spinner stepframe "Frame Step" range:[1,200,1] fieldwidth:40 type:#integer
		radiobuttons useanim labels:#("Active Time Segment","Custom Time Segment")
		spinner animstart range:[0,10000,0] type:#integer fieldwidth:40 across:2
		spinner animend "to" range:[0,10000,40] type:#integer fieldwidth:40
		button bexport "     Export    "
	)
	group "About"
	(
		label titleLabel	"TLF Exporter v2.0"
		HyperLink addy "by Cossacks3" align:#center address:"mailto:support@cossacks3.com" color:(color 0 100 0) hoverColor:(color 0 0 100)
		HyperLink me "cossacks3.com" align:#center address:"http://cossacks3.com/" color:(color 0 100 0) hoverColor:(color 0 0 100)

	)
	
	on bexport pressed do
	(
		tlfFilename=getsavefilename caption:"Save TLF" \
			filename:tlfLastfile \
			types:"tlf (*.tlf)|*.tlf|All Files (*.*)|*.*|"
		if tlfFilename!=undefined do 
		(				
			addcheck (writeTLF $ tlfFilename)
			tlfLastfile=tlfFilename
		)
	)
)