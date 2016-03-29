
enchant();

const SCREEN_WIDTH 	= 512;					//スクリーンの幅。
const SCREEN_HEIGHT = 512;					//スクリーンの高さ。
const SPRITE_SIZE 	= 32;					//スプライトの幅
const MOVE_SPEED 		= SPRITE_SIZE / 4;	//プレイヤーの移動速度。
const ENEMY_MOVE_SPEED 	= SPRITE_SIZE / 8;	//敵の移動速度。
const ENEMY_IDLE_TIME   = 10;				//敵の待機時間。(単位はフレーム。)
const NUM_CLEAR_ITEM	= 3;				//クリアアイテムの数。
const ENEMY_MOVE_RIGHT	= 0;				//敵の右移動。
const ENEMY_MOVE_LEFT	= 1;				//敵の左移動。
const ENEMY_MOVE_UP		= 2;				//敵の上移動。
const ENEMY_MOVE_DOWN	= 3;				//敵の下移動。
const MAP_GRID 			= 16;				//マップのグリッド。
//マップ定義。
var map = [
	[16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16],
	[16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,16], 
	[16, 0,16,16,16,16,16,16,16,16,16, 0,16, 0, 0,16],
	[16, 0, 4, 4,16, 0,-2,16,16, 0,16, 0,16,16, 0,16],
	[16, 0, 4, 4,16, 0,16,16,16, 0,16, 0, 0, 0, 0,16],
	[16, 0, 4, 4, 0, 0, 0,-1, 0, 0,16, 0, 0,16, 0,16],
	[16, 0, 4, 4,16, 0, 4, 0, 0, 0,16, 0,-1,16, 0,16],
	[16, 0,16, 0,16, 0, 4, 0,16, 0,16,-2, 0,16, 0,16],
	[16, 0, 0, 0, 0, 0, 0, 0,16, 4,16,16,16,16, 0,16],
	[16, 0, 0, 0, 0,16,16,16,16, 4, 4, 4, 4, 4, 4,16],
	[16, 0, 0,16,16,16, 0, 0, 0, 4, 0, 0, 0, 4, 4,16],
	[16, 0, 0,16,-2,16, 0,16,16, 4, 0,16, 0, 0, 4,16],
	[16, 0, 0,16, 0, 0, 0,16,16, 0, 0,16, 0, 0, 4,16],
	[16, 0, 0,16, 0, 0, 0,16, 0, 0, 0,16, 0, 0, 4,16],
	[16, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0,16],
	[16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16],
];    
window.onload = function(){
	/*!---------------------------------------------------------------------------------
     *@brief	エントリポイント。
     ---------------------------------------------------------------------------------*/
    var game = new Core(SCREEN_WIDTH, SCREEN_HEIGHT);
    var bear;
    var enemyArray 		= new Array();
	var clearItemArray 	= new Array();
    game.fps = 15;
    game.preload("image/chara1.png");
    game.preload("image/map.png");
    game.preload("image/enemy.png");
    game.preload("image/item.png");
    game.preload("image/over.png");
    game.preload("image/effect.png");
    
    game.onload = function(){
        var mapArray 		= new Array();
        var gamManager		= new CGameManager();
        //マップを作成。
        for( var i = 0; i < map.length; i++ ){
			for( var j = 0; j < map[0].length; j++ ){
				var mapId = map[j][i];
				if(map[j][i] == -1 || map[j][i] == -2){
					//敵とアイテムが置かれているところは地面は平野にする。
					mapId = 0;	//敵がいるところのマップは０番目にする。
				}
				mapArray.push( new CMap(SPRITE_SIZE * i, SPRITE_SIZE * j, mapId) );
			}
		}
		//敵とクリアアイテムを作る。
		for( var i = 0; i < map.length; i++ ){
			for( var j = 0; j < map[0].length; j++ ){
				var mapId = map[j][i];
				if(map[j][i] == -1){
					//敵を作成。
					enemyArray.push( new CEnemy( SPRITE_SIZE * i, SPRITE_SIZE * j ) );
				}else if(map[j][i] == -2){
					//クリアアイテムを作成。
					clearItemArray.push( new CClearItem( SPRITE_SIZE * i, SPRITE_SIZE * j, i, j ) );
				}
			}
		}
		//熊作成。
		bear = new CBear(32, 32);
    };
    game.start();
    /*!--------------------------------------------------------------------------------
     *@brief	熊クラス。
     --------------------------------------------------------------------------------*/
    var CBear = enchant.Class.create(enchant.Sprite, {
	    /*!
	     * @brief	ゲーム開始時に一度だけ呼ばれる処理。
	     */
        initialize: function(x, y) {
            enchant.Sprite.call(this, SPRITE_SIZE, SPRITE_SIZE);
            this.x = x;
            this.y = y;
            this.updateCenterPosition();
            this.image = game.assets['image/chara1.png'];
            this.frame = 5;
            game.rootScene.addChild(this);
            this.scale.x = 1;
        },
        /*!
         * @brief	毎フレーム呼ばれる処理。
         */
        onenterframe : function()
        {
			//移動。
			this.move();
			//アニメーション
			this.animation();
		},
		/*!
		 *@brief	熊の中心座標を更新。
		 */
		updateCenterPosition : function()
		{
			this.center_x = this.x + SPRITE_SIZE / 2;
			this.center_y = this.y + SPRITE_SIZE / 2;
		},
		/*!
		 * @brief	移動処理。
		 */
		move : function()
		{
			var isMove = false;
			var rectHalfW = SPRITE_SIZE * 0.1;
            var rectHalfH = SPRITE_SIZE * 0.25;
			//x方向の移動処理。
			{
				var x = this.x;
				var y = this.y;
				if(game.input.left){
					x -= MOVE_SPEED;
				}else if(game.input.right){
					x += MOVE_SPEED;
				}
				var center_x = x + SPRITE_SIZE / 2;
	            var center_y = y + SPRITE_SIZE / 2;
				var hitFlag = CheckIntersectRectToTree(
					center_x - rectHalfW,
					center_x + rectHalfW,
					center_y - rectHalfH,
					center_y + rectHalfH
				);

				if(!hitFlag){
					//木にあたっていない。
					this.x = x;
				}
			}
			//y方向の移動処理。
			{
				var x = this.x;
				var y = this.y;
				if(game.input.up){
					y -= MOVE_SPEED;
				}else if(game.input.down){
					y += MOVE_SPEED;
				}
				var center_x = x + SPRITE_SIZE / 2;
	            var center_y = y + SPRITE_SIZE / 2;
				var hitFlag = CheckIntersectRectToTree(
					center_x - rectHalfW,
					center_x + rectHalfW,
					center_y - rectHalfH,
					center_y + rectHalfH
				);
				if(!hitFlag){
					//あたっていない。
					this.y = y;
				}
			}
			this.updateCenterPosition();
		},
		/*!
		 * @brief	アニメーション処理。
		 */
		animation : function()
		{
			if(game.input.left && this.scale.x != -1){
				this.scale.x = -1
				this.scale(-1, 1.0);
			}else if( game.input.right && this.scale.x != 1 ){
				this.scale.x = 1
				this.scale(-1, 1.0);
			}
			if( game.input.left 	||
				game.input.right 	||
				game.input.up 		||
				game.input.down
			){
				this.frame = 5 + this.age % 2;
			}
		}
    });
    /*!------------------------------------------------------------------------
     *@brief	マップクラス。
     -------------------------------------------------------------------------*/
	var CMap = enchant.Class.create(enchant.Sprite, {
		/*!
	     * @brief	ゲーム開始時に一度だけ呼ばれる処理。
	     */
        initialize: function(x, y, frame) {
			enchant.Sprite.call(this, SPRITE_SIZE, SPRITE_SIZE);
            this.x = x;
            this.y = y;
            this.image = game.assets['image/map.png'];
            this.frame = frame;
            this.moveCount = 0;
            game.rootScene.addChild(this);
		}
	});
	/*!----------------------------------------------------------------------
     *@brief	敵クラス。
    ----------------------------------------------------------------------*/
     var CEnemy = enchant.Class.create(enchant.Sprite, {
        initialize: function(x, y) {
			enchant.Sprite.call(this, SPRITE_SIZE, SPRITE_SIZE);
			this.initPos_x = x;				//初期のX座標。。。戻ってくるときに使う予定・・・。
			this.initPos_y = y;				//初期のY座標・・・戻ってくるときに使う予定・・・。
			this.x = x;
            this.y = y;
            this.updateCenterPosition();
            this.moveDir = -1;				//進行方向。
            this.enemyState = "待機";		//敵の状態。
            this.count = 0;
            this.idelCount = ENEMY_IDLE_TIME;
            this.image = game.assets['image/enemy.png'];
            this.frame = 0;
            this.baseFrame = 0;
            game.rootScene.addChild(this);
		},
		/*!
		 *@brief	中心座標の更新。
		 */
		updateCenterPosition : function()
		{
			this.center_x = this.x + SPRITE_SIZE / 2;
			this.center_y = this.y + SPRITE_SIZE / 2;
		},
		/*!
         * @brief	敵の毎フレーム呼ばれる処理。
         */
        onenterframe : function()
        {
		
			if(this.enemyState == '待機'){
				//敵が待機状態。
				this.idelCount++;
				if( this.idelCount > ENEMY_IDLE_TIME ){
					//移動状態に遷移する。
					this.enemyState = "移動";
					this.moveDir = parseInt( (Math.random() * 10) % 4 );
					if( this.moveDir == 0){
						//右移動。
						this.baseFrame = 6;
					}else if( this.moveDir == 1){
						//左移動
						this.baseFrame = 3;
					}else if( this.moveDir == 2){
						//上移動。
						this.baseFrame = 9;
					}else if( this.moveDir == 3){
						//下移動。
						this.baseFrame = 0;
					}
					this.idelCount = 0;
				}
			}else if(this.enemyState == '移動'){
				if((this.age % 10) == 0 || this.moveDir == -1 ){
					//待機状態に繊維する
					this.enemyState = '待機';
					return ;
				}
				//移動処理。
				this.move();
			}else if(this.enemyState == '発見'){
				this.count++;
				if(this.count > 10){	//10フレームくらいは停止させる。
					this.move();
					if(this.count > 20){
						//終わり。
						this.enemyState = "待機";
					}
				}
			}
			//熊を索敵。
			this.searchBear();
			this.updateCenterPosition();
			this.checkHitBear();
			this.frame = this.baseFrame + this.age % 2;
		},
		/*!
		 *@brief	熊との接触判定。
		 */
		checkHitBear : function()
		{
			//自分のいるマップを調べる。
			var mapCol = parseInt( this.center_x / SPRITE_SIZE );
			var mapRow = parseInt( this.center_y / SPRITE_SIZE );
			//クマの現在地を調べる。
			var bearMapCol = parseInt(bear.center_x / SPRITE_SIZE);
			var bearMapRow = parseInt(bear.center_y / SPRITE_SIZE);
			if( mapCol == bearMapCol 
				&& mapRow == bearMapRow
			){
				//敵と接触。
				//ゲームオーバ。
				game.end(0, 'over', game.assets['image/over.png'] );
			}
		},
		/*!
		 * @brief	敵の移動処理。
		 */
		move : function()
		{
			var rectHalfW = SPRITE_SIZE * 0.2;
            var rectHalfH = SPRITE_SIZE * 0.4;
			var x = this.x;
			var y = this.y;
			var moveSpeed = ENEMY_MOVE_SPEED;
			if(this.enemyState == '発見'){
				//発見状態は移動速度を倍にする。
				moveSpeed *= 4;
			}
			if(this.moveDir == ENEMY_MOVE_RIGHT){
				//右に動かす。
				x += moveSpeed;
			}else if( this.moveDir == ENEMY_MOVE_LEFT ){
				//左に動かす。
				x -= moveSpeed;
			}
			//衝突判定。
			var center_x = x + SPRITE_SIZE / 2;
            var center_y = y + SPRITE_SIZE / 2;
			var hitFlag = CheckIntersectRectToTree(
				center_x - rectHalfW,
				center_x + rectHalfW,
				center_y - rectHalfH,
				center_y + rectHalfH
			);
			if( !hitFlag ){
				//木にあたっていない。
				this.x = x;
			}
			if( this.moveDir == ENEMY_MOVE_UP ){
				//上に動かす。
				y -= moveSpeed;
			}else if( this.moveDir == ENEMY_MOVE_DOWN){
				//下に動かす。
				y += moveSpeed;
			}
			//衝突判定。
			var center_x = x + SPRITE_SIZE / 2;
            var center_y = y + SPRITE_SIZE / 2;
			var hitFlag = CheckIntersectRectToTree(
				center_x - rectHalfW,
				center_x + rectHalfW,
				center_y - rectHalfH,
				center_y + rectHalfH
			);
			if( !hitFlag ){
				//木にあたっていない。
				this.y = y;
			}
		},
		/*!
		 *@brief	熊を索敵。
		 */
		searchBear : function()
		{
			if( this.enemyState == '発見' ){
				//発見状態なら実行しない。
				return ;
			}
			//自分のいるマップを調べる。
			var mapCol = parseInt( this.center_x / SPRITE_SIZE );
			var mapRow = parseInt( this.center_y / SPRITE_SIZE );
			//クマの現在地を調べる。
			var bearMapCol = parseInt(bear.center_x / SPRITE_SIZE);
			var bearMapRow = parseInt(bear.center_y / SPRITE_SIZE);
			var searchRange = 4;	//索敵範囲。
			if( this.moveDir == ENEMY_MOVE_RIGHT ){
				//右側を調べる。
				for(var i = 0; i < searchRange; i++ ){
					mapCol++;
					mapCol = Math.min(mapCol, MAP_GRID - 1 );
					if( map[mapRow][mapCol] == 16){
						//視線の先に木があった
						break;
					}
					if( mapCol == bearMapCol
						&& mapRow == bearMapRow
					){
						//発見。
						this.changeStateFind();
						return ;
					}
				}
			}else if( this.moveDir == ENEMY_MOVE_LEFT ){
				//左前方を調べる。
				for(var i = 0; i < searchRange; i++ ){
					mapCol--;
					mapCol = Math.max(mapCol, 0 );
					if( map[mapRow][mapCol] == 16){
						//視線の先に木があった
						break;
					}
					if( mapCol == bearMapCol
						&& mapRow == bearMapRow
					){
						//発見。
						this.changeStateFind();
						return ;
					}
				}
			}else if( this.moveDir == ENEMY_MOVE_UP ){
				//上側を調べる。
				for(var i = 0; i < searchRange; i++ ){
					mapRow--;
					mapRow = Math.max(mapRow, 0 );
					if( map[mapRow][mapCol] == 16){
						//視線の先に木があった
						break;
					}
					if( mapCol == bearMapCol
						&& mapRow == bearMapRow
					){
						//発見。
						this.changeStateFind();
						return ;
					}
				}
			}else if( this.moveDir == ENEMY_MOVE_DOWN ){
				//下側を調べる。
				for(var i = 0; i < searchRange; i++ ){
					mapRow++;
					mapRow = Math.min(mapRow, MAP_GRID - 1 );
					if( map[mapRow][mapCol] == 16){
						//視線の先に木があった
						break;
					}
					if( mapCol == bearMapCol
						&& mapRow == bearMapRow
					){
						//発見。
						this.changeStateFind();
						return ;
					}
				}
			}
		},
		/*!
		 *@brief	発見状態に遷移
		 */
		changeStateFind : function()
		{
			//発見。
			this.enemyState = "発見";
			this.count = 0;
			
			new CEffect( this.x, 
						this.y - SPRITE_SIZE / 2 );
		}
	});
	/*!--------------------------------------------------------
	 * @brief	クリアのためのアイテム。
	 --------------------------------------------------------*/
	var CClearItem = enchant.Class.create(enchant.Sprite, {
		/*!
	     * @brief	ゲーム開始時に一度だけ呼ばれる処理。
	     */
        initialize: function(x, y, mapCol, mapRow) {
			enchant.Sprite.call(this, SPRITE_SIZE, SPRITE_SIZE);
            this.x = x;
            this.y = y;
            this.image = game.assets['image/item.png'];
            this.frame = 34;
            this.mapCol = mapCol;
            this.mapRow = mapRow;
            game.rootScene.addChild(this);
		},
		/*!
		 * @brief	毎フレーム呼ばれる処理。
		 */
		onenterframe : function()
        {
			//x軸に拡大縮小をすると２次元では回転しているように見えるというトリックを使う。
			this.scaleX = Math.sin(this.age * 0.2);
		}
	});
	/*!--------------------------------------------------------
	 * @brief	ゲームの進行管理。
	 --------------------------------------------------------*/
	var CGameManager = enchant.Class.create( enchant.Sprite,{
		initialize: function() {
			enchant.Sprite.call(this, SPRITE_SIZE, SPRITE_SIZE);
			this.getClearItemCount = 0;		//クリアアイテムをゲットした数。
			game.rootScene.addChild(this);
		},
		onenterframe : function()
        {
			var mapCol = parseInt( bear.x / SPRITE_SIZE );
			var mapRow = parseInt( bear.y / SPRITE_SIZE );
			if( map[mapRow][mapCol] == -2 ){
				//アイテムゲット。
				this.getClearItemCount++;
				map[mapRow][mapCol] = 0;	//アイテム取得済みにする。
				//ゲットしたアイテムを削除
				for( var i = 0; i < clearItemArray.length; i++ ){
					if(clearItemArray[i].mapCol == mapCol
					 	&& clearItemArray[i].mapRow == mapRow 
					){
						game.rootScene.removeChild(clearItemArray[i]);
						clearItemArray.splice(i,1);
						break;
					}
				}
			}
			if(this.getClearItemCount == NUM_CLEAR_ITEM){
				//ゲームクリア
				game.end(0, 'クリア');
			}
		}
	});
	/*!
	 *@brief	ビックリマークのエフェクト。
	 */
	var CEffect = enchant.Class.create( enchant.Sprite,{
		initialize: function( x, y ) {
			enchant.Sprite.call(this, 32, 32);
			this.image = game.assets['image/effect.png'];
            this.frame = 0;
            this.x = x;
            this.y = y;
            this.count = 0;
            game.rootScene.addChild(this);
        },
        onenterframe : function()
        {
			this.count++;
			if(this.count > 10){
				//エフェクト終了。
				game.rootScene.removeChild(this);
			}
		}
	});
};
/*!
 * @brief	木との衝突判定
 */
function CheckIntersectRectToTree( left, right, top, bottom )
{
	//左上
	var mapCol = parseInt( left / SPRITE_SIZE );
	var mapRow = parseInt( top / SPRITE_SIZE );
	if( map[mapRow][mapCol] == 16 ){
		//あたっている。
		return 1;
	}
	//左下
	mapCol = parseInt( left / SPRITE_SIZE );
	mapRow = parseInt( bottom / SPRITE_SIZE );
	if( map[mapRow][mapCol] == 16 ){
		//あたっている。
		return 1;
	}
	//右上
	var mapCol = parseInt( right / SPRITE_SIZE );
	var mapRow = parseInt( top / SPRITE_SIZE );
	if( map[mapRow][mapCol] == 16 ){
		//あたっている。
		return 1;
	}
	//右下
	var mapCol = parseInt( right / SPRITE_SIZE );
	var mapRow = parseInt( bottom / SPRITE_SIZE );
	if( map[mapRow][mapCol] == 16 ){
		//あたっている。
		return 1;
	}
	return 0;
}
