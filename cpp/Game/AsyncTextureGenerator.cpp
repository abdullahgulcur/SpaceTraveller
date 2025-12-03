#include "pch.h"
#include "AsyncTextureGenerator.h"
#include "Graphics.h"
#include "Game.h"
#include "VertexBuffer.h"
#include "Vao.h"
#include "DrawCommand.h"

#include "stb_image_write.h"


#if PLATFORM == ANDROID
#include <EGL/egl.h>
#elif PLATFORM == WIN
#include "glfw3.h"
#endif

namespace Game {

	void AsyncTextureGenerator::init() {

		Engine::Graphics::initWorkerContext();

		Engine::Texture::Texture2DConfig config;
		config.width = 1024;
		config.height = 1024;
		config.minFilter = GL_NEAREST;
		config.magFilter = GL_NEAREST;
		config.wrap_s = GL_CLAMP_TO_EDGE;
		config.wrap_t = GL_CLAMP_TO_EDGE;
		config.internalFormat = GL_R8;
		config.format = GL_RED;

		Engine::Texture::createTexture2D(heightmapTextureId, config);

		fbo.generate();
		fbo.bind();
		fbo.attachTexColor(heightmapTextureId);
		fbo.unbind();

		Shader::createShader(shader);

		Engine::Texture::createTexture2D(noiseTexture, "texture/perlin/output.jpg");

		Engine::VertexBuffer::generateQuadVertexBuffer(vertexBufferQuad);
		Engine::Vao::createQuadMeshVao(quadVAO, vertexBufferQuad);

		glFlush(); // Ensure commands are pushed
	}

	void AsyncTextureGenerator::update() {

		std::unique_lock<std::mutex> lock(mtxHasJob);
		if (!hasJob)
			return;


		//std::unique_lock<std::mutex> lock(mtxHasJob);
		//hasJobCV.wait(lock, [this] { return hasJob; });

		fbo.bind();

		glViewport(0, 0, 1024, 1024);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Engine::Shader::bind(shader.programId);

		glm::vec2 position = glm::vec2(0.f);
		float rotation = 0.f;
		float scale = 1.f;
		float isBase = 0.f;
		Engine::Shader::uniform(shader.loc_Position, position);
		Engine::Shader::uniform(shader.loc_Rotation, rotation);
		Engine::Shader::uniform(shader.loc_Scale, scale);
		Engine::Shader::uniform(shader.loc_IsBase, isBase);
		Engine::Shader::uniformTexture(shader.loc_Tex, 0, noiseTexture);

		Engine::DrawCommand::drawQuad(quadVAO);


		Engine::Shader::unbind();

		//glFinish();

		//std::vector<unsigned char> pixels(1024 * 1024);
		//glBindTexture(GL_TEXTURE_2D, heightmapTextureId);
		//glGetTexImage(GL_TEXTURE_2D, 0, GL_RED, GL_UNSIGNED_BYTE, pixels.data());
		//stbi_write_jpg("outputtt.jpg", 1024, 1024, 1, pixels.data(), 100);

		fbo.unbind();

		//glFlush(); // Ensure commands are pushed


		hasJob = false;
		//isJobFinished = true; // ????

		glFlush(); // Ensure commands are pushed

	}
	
	void AsyncTextureGenerator::setHasJob() {
		
		{
			std::lock_guard<std::mutex> lock(mtxHasJob);
			hasJob = true;
		}
		//hasJobCV.notify_one();
	}

}