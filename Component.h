#pragma once

namespace ECS {

	using ComponentType = std::uint8_t;			 // コンポーネントタイプを表す型定義
	const ComponentType MAX_COMPONENTS = 32;	 // 最大コンポーネントタイプ数
	using Signature = std::bitset<MAX_COMPONENTS>; // シグネチャを表すビットセット

}