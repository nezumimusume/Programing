/*!
 * @brief	自然物関係のコンフィグ。
 */

#pragma once


namespace tkEngine{
	/*!
	 * @brief	空のコンフィグ。
	 */
	struct SSkyConfig{
		bool isEnable = false;	//!<空のシミュレーションをエンジンで行うかどうかのフラグ。
		bool isUseSun = false;	//!<太陽いる？
		bool isSunMove = false;	//!<太陽動く？
	};
	
	/*!
	 * @brief	自然物関係のコンフィグ。
	 */
	struct SNatureConfig{
		SSkyConfig		skyConfig;		//!<空のコンフィグ。
	};
}
