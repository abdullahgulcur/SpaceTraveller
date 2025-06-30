#include "pch.h"
#include "TerrainGeometryManager.h"

namespace Engine {

	void TerrainGeometryManager::init(glm::vec3& camPos) {

		glm::vec2 cameraPosition = glm::vec2(camPos.x, camPos.z);
		startClipmapLevel = TerrainGeometryManager::getMinClipmapLevel(cameraPosition, camPos.y);
		TerrainGeometryManager::initBlockProperties(TerrainGeometryManager::worldSpaceToTerrainSpace(cameraPosition));
	}

	void TerrainGeometryManager::update(glm::vec3& camPos) {

		glm::vec2 cameraPosition = glm::vec2(camPos.x, camPos.z);
		startClipmapLevel = TerrainGeometryManager::getMinClipmapLevel(cameraPosition, camPos.y);

		for (int i = startClipmapLevel; i < totalClipmapLevel; i++) {
			TerrainGeometryManager::calculateBlockPositionIndices(i, TerrainGeometryManager::worldSpaceToTerrainSpace(cameraPosition));
			TerrainGeometryManager::setOutOfBorderList(i);
		}
	}

	void TerrainGeometryManager::setOutOfBorderList(const unsigned char clipmapLevel) {

		for (int j = 0; j < blocksPerLevel; j++) {
			glm::ivec2 blockIndex = TerrainGeometryManager::getBlockIndex(clipmapLevel, j);
			unsigned short min = TerrainGeometryManager::getTerrainMinBlockIndex(clipmapLevel);
			unsigned short max = TerrainGeometryManager::getTerrainMaxBlockIndex(clipmapLevel);

			TerrainGeometryManager::setOutOfBorder(clipmapLevel, j, 0);
			if (blockIndex.x < min || blockIndex.y < min || blockIndex.x >= max || blockIndex.y >= max)
				TerrainGeometryManager::setOutOfBorder(clipmapLevel, j, 1);
		}
	}

	void TerrainGeometryManager::initBlockProperties(const glm::vec2 cameraPosition) {

		for (int i = 0; i < totalClipmapLevel; i++) {
			const glm::ivec2 gridIndex = TerrainGeometryManager::getGridIndex(i, cameraPosition);
			const glm::ivec2 startGridIndex = TerrainGeometryManager::getStartGridIndex(gridIndex);
			TerrainGeometryManager::setClipmapStartGridIndex(i, startGridIndex);
			TerrainGeometryManager::setClipmapGridIndex(i, gridIndex);

			glm::ivec2* blockIndexList = &TerrainGeometryManager::getBlockIndex(i, 0);
			unsigned char* currentIsInnerList = &TerrainGeometryManager::getIsInner(i, 0);

			TerrainGeometryManager::getCurrentBlockProperties(i, gridIndex, startGridIndex, blockIndexList, currentIsInnerList);
			TerrainGeometryManager::setOutOfBorderList(i);
		}
	}

	void TerrainGeometryManager::calculateBlockPositionIndices(const unsigned char clipmapLevel, const glm::vec2 cameraPosition) {

		const glm::ivec2 gridIndex = TerrainGeometryManager::getGridIndex(clipmapLevel, cameraPosition);
		const glm::ivec2 startGridIndex = TerrainGeometryManager::getStartGridIndex(gridIndex);
		TerrainGeometryManager::setClipmapStartGridIndex(clipmapLevel, startGridIndex);

		if (TerrainGeometryManager::getClipmapGridIndex(clipmapLevel) != gridIndex) {
			TerrainGeometryManager::setClipmapGridIndex(clipmapLevel, gridIndex);

			glm::ivec2 currentBlockIndices[blocksPerLevel];
			unsigned char currentIsInners[blocksPerLevel];

			bool previousCommon[blocksPerLevel];
			bool currentCommon[blocksPerLevel];

			for (int i = 0; i < blocksPerLevel; i++) {
				previousCommon[i] = false;
				currentCommon[i] = false;
			}
			TerrainGeometryManager::getCurrentBlockProperties(clipmapLevel, gridIndex, startGridIndex, currentBlockIndices, currentIsInners);

			for (int i = 0; i < blocksPerLevel; i++) {
				for (int j = 0; j < blocksPerLevel; j++) {
					if (TerrainGeometryManager::getBlockIndex(clipmapLevel, i) == currentBlockIndices[j] &&
						TerrainGeometryManager::getIsInner(clipmapLevel, i) == currentIsInners[j]) {
						previousCommon[i] = true;
						currentCommon[j] = true;
					}
				}
			}

			StaticArray<unsigned char, blocksPerLevel> willBeDiscarded;
			StaticArray<unsigned char, blocksPerLevel> willBeAdded;

			for (unsigned char i = 0; i < blocksPerLevel; i++) {
				if (!previousCommon[i])
					willBeDiscarded.push(i);
				if (!currentCommon[i])
					willBeAdded.push(i);
			}

			for (int i = 0; i < willBeDiscarded.size(); i++) {
				unsigned char discardIndex = willBeDiscarded[i];
				unsigned char addIndex = willBeAdded[i];

				TerrainGeometryManager::setBlockIndex(clipmapLevel, discardIndex, currentBlockIndices[addIndex]);
				TerrainGeometryManager::setIsInner(clipmapLevel, discardIndex, currentIsInners[addIndex]);
			}
		}
	}

	void TerrainGeometryManager::getCurrentBlockProperties(unsigned char level, const glm::ivec2 gridIndex, const glm::ivec2 startGridIndex,
		glm::ivec2* currentBlockIndices, unsigned char* currentIsInners) {

		for (int y = 0; y < 6; y++) {
			for (int x = 0; x < 6; x++) {
				int index = y * 6 + x;
				currentBlockIndices[index] = glm::ivec2(startGridIndex.x + x, startGridIndex.y + y);
				currentIsInners[index] = 0;
			}
		}

		glm::ivec2 startInnerIndex = (gridIndex - startGridIndex) - glm::ivec2(1);
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				int index = (y + startInnerIndex.y) * 6 + x + startInnerIndex.x;
				currentIsInners[index] = 1;
			}
		}

	}

	unsigned char TerrainGeometryManager::getMinClipmapLevel(const glm::vec2 cameraPosition, float elevation) {

		float terrainElevation = 0.f;
		elevation -= terrainElevation;

		if (elevation <= 0)
			return 0;

		const unsigned short clipmapSize = 3 * blockSize;
		unsigned short distancePrev = 0;

		for (int i = 0;; i++) {
			unsigned short size = clipmapSize * (1 << i);
			if (elevation > distancePrev && elevation < size)
				return i;
			distancePrev = size;
		}
	}

	glm::ivec2 TerrainGeometryManager::getGridIndex(const unsigned char level, const glm::vec2 camPos) {
		return glm::ivec2(camPos / glm::vec2(blockSize << level));
	}

	glm::ivec2 TerrainGeometryManager::getStartGridIndex(const glm::ivec2 gridIndex) {
		return  glm::ivec2((gridIndex.x / 2) * 2 - 2, (gridIndex.y / 2) * 2 - 2);
	}

	unsigned short TerrainGeometryManager::getTerrainMaxBlockIndex(const unsigned char level) {
		unsigned short max = terrainSize / (blockSize << level);
		return TerrainGeometryManager::getTerrainMinBlockIndex(level) + max;
	}

	glm::ivec2 TerrainGeometryManager::getBlockIndexWorldSpace(const unsigned char clipmapLevel, const unsigned char blockIndex) {
		return TerrainGeometryManager::getBlockIndex(clipmapLevel, blockIndex) - TerrainGeometryManager::getTerrainMinBlockIndex(clipmapLevel);
	}

	glm::ivec2 TerrainGeometryManager::getOuterDegenerateIndexWorldSpace(const unsigned char clipmapLevel) {
		glm::ivec2 a = glm::ivec2(TerrainGeometryManager::getClipmapStartGridIndex(clipmapLevel));
		glm::ivec2 b = glm::ivec2(TerrainGeometryManager::getTerrainMinBlockIndex(clipmapLevel));
		return a - b;
	}
}