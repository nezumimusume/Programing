/*!
 * @brief	�X�P���g���G�N�X�|�[�^�[�B
 */

--�I�u�W�F�N�g�p�����[�^�B
struct ObjectParam(
	localPos,
	localRot ,
	objName,
	bindPose,
	invBindPose,
	parentId,
	n
)
--�A�j���[�V�����L�[�t���[��
struct KeyFrame(
	boneId,
	t,
	localTransform
)
--�A�j���[�V�����N���b�v
struct AnimationClip(
	animClipName,		--�A�j���[�V�����N���b�v��
	keyFrames = #()		--�L�[�t���[���̃��X�g
)
--�I�u�W�F�N�g�p�����[�^�̔z��B
g_objectParams = #()

rollout tkExporter "tkExporter"(
	groupBox grp1 "Animation clip" pos:[10,97] width:171 height:135
	groupBox grp2 "Skeleton" pos:[10,8] width:167 height:74
	button btn_saveAnimationClip "Save" pos:[31,187] width:120 height:28
	label lbl1 "start frame" pos:[29,119] width:60 height:16
	editText animClipStartFrame "" pos:[88,116] width:62 height:21
	label lbl2 "end frame" pos:[29,146] width:60 height:16
	editText animClipEndFrame "" pos:[88,145] width:62 height:21
	button btn_saveSkeleton "Save" pos:[31,35] width:120 height:28
	/*
	 *  �o�͂���m�[�h�̏����\�z�B
	 */
	fn BuildOutputNodeInfo n parentId= 
	(
		objParam = ObjectParam Point3 Quat "" Matrix3 Matrix3 -1 Node
		objParam.objName = n.name
		objParam.bindPose = n.transform
		objParam.invBindPose = inverse n.transform
		objParam.n = n
		if n.parent == undefined then(
			--�e�����Ȃ�
			objParam.parentId = -1
			objParam.localPos = n.pos
			objParam.localRot = n.rotation
			
		)else(
			--�e������
			objParam.parentId = parentId
			objParam.localPos = n.pos * inverse n.parent.transform
			objParam.localRot = n.rotation * inverse n.parent.rotation
		)

		append g_objectParams objParam
		parentId = g_objectParams.count-1
		--�q�����B
		for child in n.children do(
			BuildOutputNodeInfo child parentId
		)
	)
	/*
	 *  �X�P���g���̕ۑ��B
	 */
	fn SaveSkeleton = 
	(
		filepath = getSaveFileName caption:"" types: "skeleton (*tks)|*.tks|All Files (*.*)|*.*|"
		
		if filepath != undefined then
		(
			file = fopen filepath "wb"
			
			try(
				--�w�b�_�[���o��
				WriteLong file g_objectParams.count
				
				for o in g_objectParams do (
					
					WriteByte file o.objName.count
					WriteString file o.objName
					WriteLong file o.parentId
					--�o�C���h�|�[�Y���o�́B
					for i = 1 to 4 do(
						WriteFloat file o.bindPose[i].x
						WriteFloat file o.bindPose[i].y
						WriteFloat file o.bindPose[i].z
					)
					--�o�C���h�|�[�Y�̋t�����o�́B
					for i = 1 to 4 do(
						WriteFloat file o.invBindPose[i].x
						WriteFloat file o.invBindPose[i].y
						WriteFloat file o.invBindPose[i].z
					)
				)
			)catch(
				Messagebox "�t�@�C���̕ۑ��Ɏ��s���܂���"
			)
			FClose file
			
			--�e�L�X�g�t�@�C����
			/*file = createfile "C:/GitHub/Programing/tkEngine2_Sandbox/Game/Assets/modelData/hoge.txt"
			try(
				for o in g_objectParams do (
					
					format "objName : %\n" o.objName to:file
					format "localPos : %\n" o.localPos to:file
					format "localRot : %\n" o.localRot to:file
				--	format "parentName : %\n" o.parentName to:file
					
					--�o�C���h�|�[�Y���o�́B
					for i = 1 to 4 do(
						format "bindPose :%\n" o.bindPose[i] to:file
					)
					--�o�C���h�|�[�Y�̋t�����o�́B
					for i = 1 to 4 do(
						format "invBindPose : %\n" o.invBindPose[i] to:file
					)
				)
			)catch(
				Messagebox "�t�@�C���̕ۑ��Ɏ��s���܂���"
			)
			close file*/
		)
	)
	
	/*
	 *  �A�j���[�V�����N���b�v�̕ۑ��B
	 */
	fn SaveAnimationClip=
	(
		AnimationClip animClip string #()
		filepath = getSaveFileName caption:"" types: "animation clip (*tka)|*.tka|All Files (*.*)|*.*|"
		
		startFrame = animClipStartFrame.text as integer + 1
		endFrame = animClipEndFrame.text as integer + 1
		numKey = endFrame - startFrame + 1
		if numKey <= 0 then(
			--1�t���[�������o���B
			endFrame = startFrame
			numKey = 1
		)
		deltaTime = 1.0/60
		keyTime = 0.0
		
		numKey *= g_objectParams.Count
		matTransList = #()
		matRotList = #()
		if filepath != undefined then
		(
			file = fopen filepath "wb"
			--�w�b�_�[���o��
			WriteLong file numKey
			
			for i=startFrame to endFrame do(
				boneId = 0
				keyTime = (i - startFrame) * deltaTime
				for o in g_objectParams do (
					
					n = o.n
					transCtr = n.pos.track
					rotCtr = n.rotation.track
					
					matTrans = matrix3 1
					pos = Point3 0.0 0.0 0.0
					if matTransList.count <= boneId then(
						pos.x = o.localPos.x
						pos.y = o.localPos.y
						pos.z = o.localPos.z
						translate matTrans pos
						append matTransList matTrans
					)
					if matRotList.count <= boneId then(
						matRot = o.localRot as matrix3
						append matRotList matRot
					)
					if transCtr.x_position.keys.count >= i  then(
						pos.x = transCtr.x_position.keys[i].value
						pos.y = transCtr.y_position.keys[i].value 
						pos.z = transCtr.z_position.keys[i].value 
						 matTransList[boneId+1] = transMatrix(pos)
					)
					
					if rotCtr.x_rotation.keys.count >= i then(
						xRot = rotCtr.x_rotation.keys[i].value
						yRot = rotCtr.y_rotation.keys[i].value
						zRot = rotCtr.z_rotation.keys[i].value
						matRotList[boneId+1] = rotateXMatrix (xRot) * rotateYMatrix (yRot) * rotateZMatrix (zRot)
					)

					transformMatrix = matRotList[boneId+1] * matTransList[boneId+1]
					--�o��
					WriteLong file boneId -- ��ID
					WriteFloat file keyTime -- ����
					for i = 1 to 4 do(
						WriteFloat file transformMatrix[i].x
						WriteFloat file transformMatrix[i].y
						WriteFloat file transformMatrix[i].z
					)
					boneId +=1

				)
				
			)
		)

		FClose file
	)
	/*
	 *  �X�P���g���̏o�͂̃{�^���������ꂽ�Ƃ��̏����B
	 */
	on btn_saveSkeleton pressed do
	(
		if selection[1] == undefined then(
			Messagebox "�o�͂���X�P���g���̃��[�g�̃I�u�W�F�N�g��I�����ĉ������B�B�B"
		)else(
			g_objectParams = #()
			BuildOutputNodeInfo selection[1] -1
			SaveSkeleton()
		)
	)
	/*
	 *  �A�j���[�V�����N���b�v�̕ۑ��̃{�^���������ꂽ�Ƃ��̏����B
	 */
	on btn_saveAnimationClip pressed do
	(
		if selection[1] == undefined  then(
			Messagebox "�o�͂���A�j���[�V�����N���b�v���܂ރX�P���g���̃��[�g�̃I�u�W�F�N�g��I�����Ă��������B"
		)else(
			--�Ƃ肠�����S�N���b�v�o�͂���B
			g_objectParams = #()
			BuildOutputNodeInfo selection[1] -1
			SaveAnimationClip()
		)
	)
)
createDialog tkExporter style:#(#style_titlebar, #style_sysmenu)