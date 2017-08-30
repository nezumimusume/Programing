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

rollout SkeletonExporter "SkeletonExporter"
(
	button btn_saveSkeleton "Save skeleton" width:100 height:20 pos:[13,415] 
	button btn_saveAnimationClip "Save animation" with:100 height:20 pos:[13, 440]
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
		for i =1 to 2 do(
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
			)
		)
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

createDialog SkeletonExporter 200 530 style:#(#style_titlebar, #style_sysmenu)