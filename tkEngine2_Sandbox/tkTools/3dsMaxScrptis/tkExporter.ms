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

rollout tkExporter "tkExporter" width:194 height:248
(
	editText animClipStartFrame "" pos:[88,116] width:62 height:21
	label lbl1 "start frame" pos:[29,119] width:60 height:16
	groupBox grp1 "Animation clip" pos:[10,97] width:171 height:135
	groupBox grp2 "Skeleton" pos:[10,8] width:167 height:74
	button btn_saveAnimationClip "Save" pos:[31,187] width:120 height:28
	label lbl2 "end frame" pos:[29,146] width:60 height:16
	editText animClipEndFrame "" pos:[88,145] width:62 height:21
	button btn_saveSkeleton "Save" pos:[31,35] width:120 height:28
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
		filepath = getSaveFileName caption:"" types: "skeleton (*tsk)|*.tsk|All Files (*.*)|*.*|"
		
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
					WriteFloat file o.localPos.x
					WriteFloat file o.localPos.y
					WriteFloat file o.localPos.z
					WriteFloat file o.localRot.x
					WriteFloat file -o.localRot.z
					WriteFloat file -o.localRot.y
					WriteFloat file o.localRot.w
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
			
			--テキストファイル版
			/*file = createfile "C:/GitHub/Programing/tkEngine2_Sandbox/Game/Assets/modelData/hoge.txt"
			try(
				for o in g_objectParams do (
					
					format "objName : %\n" o.objName to:file
					format "localPos : %\n" o.localPos to:file
					format "localRot : %\n" o.localRot to:file
				--	format "parentName : %\n" o.parentName to:file
					
					--バインドポーズを出力。
					for i = 1 to 4 do(
						format "bindPose :%\n" o.bindPose[i] to:file
					)
					--バインドポーズの逆数を出力。
					for i = 1 to 4 do(
						format "invBindPose : %\n" o.invBindPose[i] to:file
					)
				)
			)catch(
				Messagebox "ファイルの保存に失敗しました"
			)
			close file*/
		)
	)
	/*
	 *  アニメーションクリップの保存。
	 */
	fn SaveAnimationClip=
	(
		--取り合えず適当に50フレーム分のキーフレームを出力してみよう。
		AnimationClip animClip string #()
		filepath = getSaveFileName caption:"" types: "animation clip (*tka)|*.tka|All Files (*.*)|*.*|"
		numKey = 2 * g_objectParams.Count
		if filepath != undefined then
		(
			file = fopen filepath "wb"
			--ヘッダーを出力
			WriteLong file numKey
			
			for i =1 to numKey do(
				boneId = 0
				for o in g_objectParams do (
					
					n = o.n
					transCtr = n.pos.track
					rotCtr = n.rotation.track
					
					matTrans = matrix3 1
					pos = Point3 0.0 0.0 0.0
					pos.x = transCtr.x_position.keys[i].value
					pos.y = transCtr.y_position.keys[i].value 
					pos.z = transCtr.z_position.keys[i].value 
					translate matTrans pos
					xRot = rotCtr.x_rotation.keys[i].value
					yRot = rotCtr.y_rotation.keys[i].value
					zRot = rotCtr.z_rotation.keys[i].value
					matRot = rotateXMatrix (xRot) * rotateYMatrix (yRot) * rotateZMatrix (zRot)
					
					transformMatrix = matRot * matTrans
					--出力
					WriteLong file boneId
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