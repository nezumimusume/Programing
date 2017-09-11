/*!
 * @brief	スケルトンエクスポーター。
 */

--オブジェクトパラメータ。
struct ObjectParam(
	localPos,
	localRot ,
	objName,
	bindPose,
	invBindPose,
	parentId,
	n
)
--アニメーションキーフレーム
struct KeyFrame(
	boneId,
	t,
	localTransform
)
--アニメーションクリップ
struct AnimationClip(
	animClipName,		--アニメーションクリップ名
	keyFrames = #()		--キーフレームのリスト
)
--オブジェクトパラメータの配列。
g_objectParams = #()

rollout tkExporter "tkExporter" width:465 height:328
(
	editText 'animClipStartFrame' "" pos:[91,202] width:60 height:21 align:#left
	label 'lbl1' "start frame" pos:[23,205] width:60 height:16 align:#left
	groupBox 'grp1' "Animation clip" pos:[13,145] width:372 height:167 align:#left
	groupBox 'grp2' "Skeleton" pos:[12,8] width:373 height:119 align:#left
	button 'btn_saveAnimationClip' "Save" pos:[245,271] width:120 height:28 align:#left
	label 'lbl2' "end frame" pos:[23,236] width:60 height:16 align:#left
	editText 'animClipEndFrame' "" pos:[91,234] width:58 height:21 align:#left
	button 'btn_saveSkeleton' "Save" pos:[245,79] width:120 height:28 align:#left
	label 'lbl3' "Label" pos:[34,127] width:0 height:0 align:#left
	label 'lbl4' "base folder" pos:[23,173] width:60 height:14 align:#left
	editText 'animClipBaseFolder' "" pos:[91,168] width:274 height:21 align:#left
	label 'lbl5' "base folder" pos:[23,34] width:60 height:14 align:#left
	editText 'skeletonBaseFolder' "" pos:[91,31] width:274 height:21 align:#left
	/*
	 *  出力するノードの情報を構築。
	 */
	fn BuildOutputNodeInfo n parentId= 
	(
		objParam = ObjectParam Point3 Quat "" Matrix3 Matrix3 -1 Node
		objParam.objName = n.name
		objParam.bindPose = n.transform
		objParam.invBindPose = inverse n.transform
		objParam.n = n
		if n.parent == undefined then(
			--親がいない
			objParam.parentId = -1
			objParam.localPos = n.pos
			objParam.localRot = n.rotation
			
		)else(
			--親がいる
			objParam.parentId = parentId
			objParam.localPos = n.pos * inverse n.parent.transform
			objParam.localRot = n.rotation * inverse n.parent.rotation
		)

		append g_objectParams objParam
		parentId = g_objectParams.count-1
		--子供も。
		for child in n.children do(
			BuildOutputNodeInfo child parentId
		)
	)
	/*
	 *  スケルトンの保存。
	 */
	fn SaveSkeleton = 
	(
		filepath = ""
		if skeletonBaseFolder.text != "" then(
			baseFilePath = skeletonBaseFolder.text + "/"
			filepath = getSaveFileName caption:"" types: "skeleton (*tks)|*.tks|All Files (*.*)|*.*|" filename:baseFilePath
		)else(
			filepath = getSaveFileName caption:"" types: "skeleton (*tks)|*.tks|All Files (*.*)|*.*|"
		)
		if filepath != undefined then
		(
			file = fopen filepath "wb"
			
			try(
				--ヘッダーを出力
				WriteLong file g_objectParams.count
				
				for o in g_objectParams do (
					
					WriteByte file o.objName.count
					WriteString file o.objName
					WriteLong file o.parentId
					--バインドポーズを出力。
					for i = 1 to 4 do(
						WriteFloat file o.bindPose[i].x
						WriteFloat file o.bindPose[i].y
						WriteFloat file o.bindPose[i].z
					)
					--バインドポーズの逆数を出力。
					for i = 1 to 4 do(
						WriteFloat file o.invBindPose[i].x
						WriteFloat file o.invBindPose[i].y
						WriteFloat file o.invBindPose[i].z
					)
				)
			)catch(
				Messagebox "ファイルの保存に失敗しました"
			)
			FClose file
		)
	)
	
	/*
	 *  アニメーションクリップの保存。
	 */
	fn SaveAnimationClip=
	(
		AnimationClip animClip string #()
		filepath = ""
		if animClipBaseFolder.text != "" then(
			baseFilePath = animClipBaseFolder.text + "/"
			filepath = getSaveFileName caption:"" types: "animation clip (*tka)|*.tka|All Files (*.*)|*.*|" filename:baseFilePath

		)else(
			filepath = getSaveFileName caption:"" types: "animation clip (*tka)|*.tka|All Files (*.*)|*.*|"
		)
	
		startFrame = animClipStartFrame.text as integer + 1
		endFrame = animClipEndFrame.text as integer + 1
		numKey = endFrame - startFrame + 1
		if numKey <= 0 then(
			--1フレームだけ出す。
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
			--ヘッダーを出力
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
					--出力
					WriteLong file boneId -- 骨ID
					WriteFloat file keyTime -- 時間
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
	 *  スケルトンの出力のボタンが押されたときの処理。
	 */
	on btn_saveSkeleton pressed do
	(
		if selection[1] == undefined then(
			Messagebox "出力するスケルトンのルートのオブジェクトを選択して下さい。。。"
		)else(
			g_objectParams = #()
			BuildOutputNodeInfo selection[1] -1
			SaveSkeleton()
		)
	)
	/*
	 *  アニメーションクリップの保存のボタンが押されたときの処理。
	 */
	on btn_saveAnimationClip pressed do
	(
		if selection[1] == undefined  then(
			Messagebox "出力するアニメーションクリップを含むスケルトンのルートのオブジェクトを選択してください。"
		)else(
			--とりあえず全クリップ出力する。
			g_objectParams = #()
			BuildOutputNodeInfo selection[1] -1
			SaveAnimationClip()
		)
	)
)
createDialog tkExporter style:#(#style_titlebar, #style_sysmenu)