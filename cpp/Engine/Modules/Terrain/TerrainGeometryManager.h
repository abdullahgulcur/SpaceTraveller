#pragma once

#include "glm.hpp"

namespace Engine {

	class TerrainGeometryManager {

	private:
		
	public:

		unsigned short terrainSize;
		unsigned char blockSize;

		unsigned char totalClipmapLevel;
		unsigned char startClipmapLevel;

		std::vector<glm::i16vec2> clipmapGridIndexList;
		std::vector<glm::i16vec2> clipmapStartGridIndexList;

		std::vector<glm::u16vec2> blockIndexList;
		std::vector<glm::u8vec2> blockLocalIndexList;
		std::vector<unsigned char> isInnerLists;
		std::vector<unsigned char> outOfBorderList;

		TerrainGeometryManager() {}
		~TerrainGeometryManager() {}

		void init(unsigned short terrainSize, unsigned short blockSize, glm::vec3& camPos);
		void update(glm::vec3& camPos);
		void setOutOfBorderList(const unsigned char clipmapLevel);
		void initBlockProperties(const glm::vec2 cameraPosition);
		void calculateBlockPositionIndices(const unsigned char clipmapLevel, const glm::vec2 cameraPosition);
		void getCurrentBlockProperties(unsigned char level, const glm::u16vec2 gridIndex, const glm::u16vec2 startGridIndex,
			glm::u16vec2* currentBlockIndices, glm::u8vec2* currentBlockLocalIndices, unsigned char* currentIsInners);
		unsigned char getMinClipmapLevel(const glm::vec2 cameraPosition, float elevation);
		glm::u16vec2 getGridIndex(const unsigned char level, const glm::vec2 camPos);
		glm::u16vec2 getStartGridIndex(glm::u16vec2 const gridIndex);
		void setClipmapStartGridIndex(const unsigned char clipmapLevel, const glm::i16vec2 index);
		void setClipmapGridIndex(const unsigned char clipmapLevel, const glm::i16vec2 index);
		glm::i16vec2& getClipmapStartGridIndex(const unsigned char clipmapLevel);
		glm::i16vec2& getClipmapGridIndex(const unsigned char clipmapLevel);
		void setBlockIndex(const unsigned char clipmapLevel, const unsigned char blockIndex, const glm::u16vec2 index);
		glm::u16vec2& getBlockIndex(const unsigned char clipmapLevel, const unsigned char blockIndex);
		void setIsInner(const unsigned char clipmapLevel, const unsigned char blockIndex, const unsigned char index);
		unsigned char& getIsInner(const unsigned char clipmapLevel, const unsigned char blockIndex);
		void setBlockLocalIndex(const unsigned char clipmapLevel, const unsigned char blockIndex, const glm::u8vec2 index);
		glm::u8vec2& getBlockLocalIndex(const unsigned char clipmapLevel, const unsigned char blockIndex);
		void setOutOfBorder(const unsigned char clipmapLevel, const unsigned char blockIndex, const unsigned char outOfBorder);
		unsigned char& getOutOfBorder(const unsigned char clipmapLevel, const unsigned char blockIndex);
		glm::vec2 worldSpaceToTerrainSpace(const glm::vec2 cameraPosition);
		//glm::u16vec2 terrainSpaceToWorldSpace(const glm::u16vec2 blockPosition, const unsigned char level);
		unsigned short getTerrainMinBlockIndex(const unsigned char level);
		unsigned short getTerrainMaxBlockIndex(const unsigned char level);
		glm::u16vec2 getBlockIndexWorldSpace(const unsigned char clipmapLevel, const unsigned char blockIndex);
		glm::i16vec2 getOuterDegenerateIndexWorldSpace(const unsigned char clipmapLevel);
	};
}