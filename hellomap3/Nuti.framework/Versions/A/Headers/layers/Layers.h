/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_LAYERS_H_
#define _NUTI_LAYERS_H_

#include <memory>
#include <mutex>
#include <vector>

namespace Nuti {
    class Options;
    class Layer;
    class MapRenderer;
    class CancelableThreadPool;
    
    /**
     * Container for all raster and vector layers of the map view.
     *
     * The order in which layers are added is important for vector elements like Points, Lines
     * and Polygons. For these elements the layer ordering defines their draw order.
     * Other elements like NMLModels and Polygon3Ds are z ordered and are drawn using the depth buffer.
     * For Billboard elements like Markers and Labels, the layer ordering is unimportant, because
     * they will be sorted from back to front and drawn in that order on top of all other vector elements.
     */
    class Layers {
    public:
        Layers(const std::shared_ptr<CancelableThreadPool>& envelopeThreadPool,
               const std::shared_ptr<CancelableThreadPool>& tileThreadPool,
               const std::weak_ptr<Options>& options);
        virtual ~Layers();
		
		/**
		 * Returns the current layer count.
		 * @return The layer count.
		 */
		int count() const;
		
		/**
		 * Returns the layer at the specified index.
		 * @param index The layer index to return. Must be between 0 and count (exclusive).
		 * @return The layer at the specified index.
		 */
		std::shared_ptr<Layer> get(int index) const;

		/**
		 * Inserts a new layer at the specified position.
		 * All previous layers starting from this index will be moved to the next position.
		 * @param index The layer index. Must be between 0 and count (inclusive).
		 * @param layer The new layer.
		 */
		void insert(int index, const std::shared_ptr<Layer>& layer);
        /**
         * Adds a new layer to the layer stack. The new layer will be the last (and topmost) layer.
         * @param layer The layer to be added.
         */
        void add(const std::shared_ptr<Layer>& layer);
        /**
         * Removes a layer to the layer stack.
         * @param layer The layer to be removed.
		 * @return True if the layer was removed. False otherwise (layer was not found).
         */
        bool remove(const std::shared_ptr<Layer>& layer);
		
        /**
         * Returns a list of layers. The layers are in the order in which they were added.
         * @return A vector of all previously added layers.
         */
        std::vector<std::shared_ptr<Layer> > getLayers() const;
        
    protected:
        friend class BaseMapView;
        
        void setMapRenderer(const std::shared_ptr<MapRenderer>& mapRenderer);
    
    private:
        std::vector<std::shared_ptr<Layer> > _layers;
    
        std::shared_ptr<CancelableThreadPool> _envelopeThreadPool;
        std::shared_ptr<CancelableThreadPool> _tileThreadPool;
        std::weak_ptr<Options> _options;
        
        std::weak_ptr<MapRenderer> _mapRenderer;
    
        mutable std::mutex _mutex;
    };
    
}

#endif
