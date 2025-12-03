#pragma once

#include "FrameBuffer.h"
#include "Shader.h"

namespace Game {

	struct TerrainTexGenJob {

	};

	class AsyncTextureGenerator {

	private:

		unsigned int quadVAO;
		unsigned int vertexBufferQuad;
		Engine::FrameBuffer fbo;
		Shader::ShaderTerrainHeightmapGenerator shader;

	public:

		unsigned int noiseTexture;
		unsigned int heightmapTextureId;

		std::mutex mtxHasJob;
		std::condition_variable hasJobCV;
		bool hasJob = false;


		bool isJobFinished = false; // ???

		AsyncTextureGenerator() {}
		~AsyncTextureGenerator() {}
		void init();
		void update();
		void setHasJob();
	};
}