#pragma once

#include "glm.hpp"
#include "algebra.h"

namespace Engine {

	class TerrainGeometryManager {

	private:

		static constexpr int terrainSize = 1024;
		static constexpr int blocksPerLevel = 36;
		static constexpr int blockSize = 16;
		static constexpr int totalClipmapLevel = Algebra::intLog2(terrainSize / blockSize) + 1;
		static constexpr int totalBlocks = totalClipmapLevel * blocksPerLevel;

		StaticArray<glm::ivec2, totalClipmapLevel> clipmapGridIndexList;
		StaticArray<glm::ivec2, totalClipmapLevel> clipmapStartGridIndexList;
		StaticArray<glm::ivec2, totalBlocks> blockIndexList;
		StaticArray<unsigned char, totalBlocks> isInnerLists;
		StaticArray<unsigned char, totalBlocks> outOfBorderList;

		int startClipmapLevel;

		void setOutOfBorderList(const unsigned char clipmapLevel);
		void initBlockProperties(const glm::vec2 cameraPosition);
		void calculateBlockPositionIndices(const unsigned char clipmapLevel, const glm::vec2 cameraPosition);
		void getCurrentBlockProperties(unsigned char level, const glm::ivec2 gridIndex, const glm::ivec2 startGridIndex,
			glm::ivec2* currentBlockIndices, unsigned char* currentIsInners);
		glm::ivec2 getGridIndex(const unsigned char level, const glm::vec2 camPos);
		glm::ivec2 getStartGridIndex(glm::ivec2 const gridIndex);

		// -------------- SET --------------

		inline void setClipmapStartGridIndex(const unsigned char clipmapLevel, const glm::ivec2 index) {
			clipmapStartGridIndexList[clipmapLevel] = index;
		}

		inline void setClipmapGridIndex(const unsigned char clipmapLevel, const glm::ivec2 index) {
			clipmapGridIndexList[clipmapLevel] = index;
		}

		inline void setBlockIndex(const unsigned char clipmapLevel, const unsigned char blockIndex, const glm::ivec2 index) {
			blockIndexList[clipmapLevel * blocksPerLevel + blockIndex] = index;
		}

		inline void setIsInner(const unsigned char clipmapLevel, const unsigned char blockIndex, const unsigned char index) {
			isInnerLists[clipmapLevel * blocksPerLevel + blockIndex] = index;
		}

		inline void setOutOfBorder(const unsigned char clipmapLevel, const unsigned char blockIndex, const unsigned char outOfBorder) {
			outOfBorderList[clipmapLevel * blocksPerLevel + blockIndex] = outOfBorder;
		}

		// -------------- GET --------------

		inline glm::ivec2& getClipmapStartGridIndex(const unsigned char clipmapLevel) {
			return clipmapStartGridIndexList[clipmapLevel];
		}

		inline glm::ivec2& getClipmapGridIndex(const unsigned char clipmapLevel) {
			return clipmapGridIndexList[clipmapLevel];
		}

		inline glm::ivec2& getBlockIndex(const unsigned char clipmapLevel, const unsigned char blockIndex) {
			return blockIndexList[clipmapLevel * blocksPerLevel + blockIndex];
		}

		inline glm::vec2 worldSpaceToTerrainSpace(const glm::vec2 cameraPosition) {
			return cameraPosition + glm::vec2(32768);
		}

		inline int getTerrainMinBlockIndex(const unsigned char level) {
			return 32768 / (blockSize << level);
		}

		unsigned short getTerrainMaxBlockIndex(const unsigned char level);
		glm::ivec2 getOuterDegenerateIndexWorldSpace(const unsigned char clipmapLevel);

	public:

		TerrainGeometryManager() {}
		~TerrainGeometryManager() {}

		void init(glm::vec3& camPos);
		void update(glm::vec3& camPos);
		
		unsigned char getMinClipmapLevel(const glm::vec2 cameraPosition, float elevation);
		
		inline unsigned char& getIsInner(const unsigned char clipmapLevel, const unsigned char blockIndex) {
			return isInnerLists[clipmapLevel * blocksPerLevel + blockIndex];
		}

		inline unsigned char& getOutOfBorder(const unsigned char clipmapLevel, const unsigned char blockIndex) {
			return outOfBorderList[clipmapLevel * blocksPerLevel + blockIndex];
		}

		glm::ivec2 getBlockIndexWorldSpace(const unsigned char clipmapLevel, const unsigned char blockIndex);

		int getBlockSize() const {
			return blockSize;
		}

		int getTotalClipmapLevel() const {
			return totalClipmapLevel;
		}

		int getStartClipmapLevel() const {
			return startClipmapLevel;
		}
	};
}