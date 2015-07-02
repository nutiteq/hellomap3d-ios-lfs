/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_NMLGL_SUBMESH_H_
#define _NUTI_NMLGL_SUBMESH_H_

#include "BaseTypes.h"

#include <memory>
#include <string>
#include <vector>

namespace nml {
    class Submesh;
    class SubmeshOpList;
}

namespace Nuti { namespace nmlGL {
    class Mesh;

    class Submesh {
    public:
        Submesh(const nml::Submesh& submesh);
        Submesh(const Mesh& glMesh, const nml::SubmeshOpList& submeshOpList);

        void create(const std::shared_ptr<GLContext>& gl);
        void dispose(const std::shared_ptr<GLContext>& gl);

        void draw(const std::shared_ptr<GLContext>& gl);

        void calculateRayIntersections(const cglib::vec3<double>& origin, const cglib::vec3<double>& dir, std::vector<RayIntersection>& intersections) const;

        const std::string& getMaterialId() const;

        int getDrawCallCount() const;
        int getTotalGeometrySize() const;

    private:
        void uploadSubmesh(const std::shared_ptr<GLContext>& gl);

        static GLint convertType(int type);
        static void convertToFloatBuffer(const std::string& str, std::vector<float>& buf);
        static void convertToByteBuffer(const std::string& str, std::vector<unsigned char>& buf);

        int _refCount;
        GLint _glType;
        std::vector<int> _vertexCounts;
        std::string _materialId;

        std::vector<float> _positionBuffer;
        std::vector<float> _normalBuffer;
        std::vector<float> _uvBuffer;
        std::vector<unsigned char> _colorBuffer;
        std::vector<unsigned int> _vertexIdBuffer;

        GLuint _glPositionVBOId;
        GLuint _glNormalVBOId;
        GLuint _glUVVBOId;
        GLuint _glColorVBOId;
        std::weak_ptr<GLContext> _glContext;
    };

} }

#endif
