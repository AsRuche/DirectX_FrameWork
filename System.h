#pragma once

namespace ECS {

#pragma once

    namespace ECS {

        // �V�X�e���̊��N���X
        class System {
        public:
            virtual ~System() = default;

            // Update ���\�b�h�̏������z�֐����`
            virtual void Update(float deltaTime) = 0;
        };

    }

}