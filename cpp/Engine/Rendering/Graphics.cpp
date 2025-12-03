#include "Graphics.h"
#include "GraphicsApi.h"

namespace Engine {

	namespace Graphics {

		void init() {

#if PLATFORM == WIN
            glewExperimental = true;
            glewInit();
#endif
            configure();
		}

        void initWorkerContext() {

#if PLATFORM == WIN
            glewExperimental = true;
            glewInit();

            /*glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            glFrontFace(GL_CCW);*/

            //glEnable(GL_BLEND);
            //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
#endif
        }

		void configure() {

            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);

            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            glFrontFace(GL_CCW);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);

            //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		}
	}
}