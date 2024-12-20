#pragma once

namespace ECS {

#pragma once

    namespace ECS {

        // システムの基底クラス
        class System {
        public:
            virtual ~System() = default;

            // Update メソッドの純粋仮想関数を定義
            virtual void Update(float deltaTime) = 0;
        };

    }

}