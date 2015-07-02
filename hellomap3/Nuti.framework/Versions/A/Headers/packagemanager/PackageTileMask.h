/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_PACKAGETILEMASK_H_
#define _NUTI_PACKAGETILEMASK_H_

#include <string>
#include <memory>
#include <queue>
#include <vector>
#include <unordered_set>

namespace Nuti {

    namespace PackageTileStatus {
        /**
         * Tile status.
         */
        enum PackageTileStatus {
            /**
             * Tile is not part of the package.
             */
            PACKAGE_TILE_STATUS_MISSING,
            /**
             * Tile is part of the package, but package does not fully cover it.
             */
            PACKAGE_TILE_STATUS_PARTIAL,
            /**
             * Tile if part of the package and package fully covers it.
             */
            PACKAGE_TILE_STATUS_FULL
        };
    }

    /**
	 * Information about map package. This includes id, version, name, description and size.
	 */
	class PackageTileMask {
	public:
		/**
		 * Tile info.
		 */
		struct Tile {
			int zoom;
			int x, y;

			Tile(int zoom, int x, int y) : zoom(zoom), x(x), y(y) { }
		};

		/**
		 * Constructs a new package tile mask instance from encoded string.
		 * @param stringValue The encoded tile mask of the package
		 */
		PackageTileMask(const std::string& stringValue);

		/**
		 * Constructs a new package tile mask instance from a list of tiles.
		 * @param tiles The list of tiles
		 */
		PackageTileMask(const std::vector<Tile>& tiles);

		/**
		 * Returns the encoded tile mask value. This should not be displayed to the user.
		 * @return The tile mask of the package
		 */
		const std::string& getStringValue() const {
			return _stringValue;
		}

		/**
		 * Returns the status of the specified tile. This method can be used for fast testing whether a tile is part of the package.
		 * @param zoom The zoom level of the tile.
		 * @param x The x coordinate of the tile.
		 * @param y The y coordinate of the tile.
		 * @return The status of the specified tile.
		 */
        PackageTileStatus::PackageTileStatus getTileStatus(int zoom, int x, int y) const;

	private:
		struct TileNode {
			Tile tile;
			bool inside;
			std::shared_ptr<TileNode> subNodes[4];

			TileNode(const Tile& tile, bool inside) : tile(tile), inside(inside) { }
		};

		struct TileHash {
			std::size_t operator() (const Tile& tile) const {
				return tile.zoom + 24 * (tile.x ^ (tile.y << 16));
			}
		};

		struct TileEq {
			bool operator() (const Tile& tile1, const Tile& tile2) const {
				return tile1.x == tile2.x && tile1.y == tile2.y && tile1.zoom == tile2.zoom;
			}
		};

		std::shared_ptr<TileNode> findTileNode(const Tile& tile) const;

		static std::shared_ptr<TileNode> buildTileNode(std::queue<bool>& data, const Tile& tile);
		static std::shared_ptr<TileNode> buildTileNode(const std::unordered_set<Tile, TileHash, TileEq>& tileSet, const Tile& tile);
		static std::vector<bool> encodeTileNode(const std::shared_ptr<TileNode>& node);

		std::string _stringValue;
		std::shared_ptr<TileNode> _rootNode;
	};
}

#endif
