/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_STYLESELECTORCONTEXT_H_
#define _NUTI_STYLESELECTORCONTEXT_H_

#include <memory>
#include <string>
#include <map>

#include <boost/variant.hpp>

namespace Nuti {
    class ViewState;
    class Geometry;

    /**
     * Style selector context for evaluating rules.
     */
    class StyleSelectorContext {
    public:
        /**
         * Constructs a new context based on view state, geometry and meta data (variables).
         * Note: context is a lightweight class that does not copy any of the input values, it keeps only references.
         * @param viewState The view state for the context
         * @param geometry The geometry element
         * @param metaData The meta data associated with the geometry
         */
        StyleSelectorContext(const ViewState& viewState, const std::shared_ptr<Geometry>& geometry, const std::map<std::string, std::string>& metaData);

        /**
         * Returns the view state associated with the context.
         * @return The view state of the context
         */
        const ViewState& getViewState() const;
        /**
        * Returns the geometry associated with the context.
        * @return The geometry of the context
        */
        const std::shared_ptr<Geometry>& getGeometry() const;
        /**
        * Returns the meta data associated with the context.
        * @return The meta data of the context
        */
        const std::map<std::string, std::string>& getMetaData() const;

        /**
         * Tries to find variable value based on its name.
         * @param name The name of the context variable
         * @param value The corresponding value, used as an output parameter
         * @return True if variable name was matched and its value was assigned to value parameter, false otherwise.
         */
        bool getVariable(const std::string& name, boost::variant<double, std::string>& value) const;

    private:
        const ViewState& _viewState;
        const std::shared_ptr<Geometry>& _geometry;
        const std::map<std::string, std::string>& _metaData;
    };
}

#endif
