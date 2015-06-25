#pragma once
#include "Model.h"

namespace Rendering
{
	namespace Models
	{

		class Quad : public Models::Model
		{
		public:
			using IGameObject::Draw;
			Quad();
			~Quad();

			void Create();
			virtual void Draw()   override final;
			virtual void Update() override final;
		private:

		};

	}
}

