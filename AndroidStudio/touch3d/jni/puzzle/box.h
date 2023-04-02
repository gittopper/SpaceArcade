#pragma once

#include "base.h"
#include "vector.h"
#include "volpart.h"

namespace Geometry {

/// Cubically parted space
class Box {
   public:
    Box(int DX, int DY, int DZ);

    VolPart& getVolPart(const Vector& coords) {
        return getVolPart(coords[0], coords[1], coords[2]);
    }
    /// obtain volume part of space
    VolPart& getVolPart(int x, int y, int z) {
        BREAK_ON_LINE(x < m_dimX && y < m_dimY && z < m_dimZ);
        auto& val = m_box[x * m_dimZ * m_dimY + y * m_dimZ + z];
        BREAK_ON_LINE(val.getCoords()[0] == x && val.getCoords()[1] == y &&
                      val.getCoords()[2] == z);
        return val;
    }

    int getDimX() const { return m_dimX; }
    int getDimY() const { return m_dimY; }
    int getDimZ() const { return m_dimZ; }

    bool isInside(const Vector& coords) const {
        return isInside(coords[0], coords[1], coords[2]);
    }

    bool isInside(int x, int y, int z) const {
        return x < m_dimX && y < m_dimY && z < m_dimZ;
    }

    const VolPart& getVolPart(const Vector& coords) const {
        return getVolPart(coords[0], coords[1], coords[2]);
    }

    const VolPart& getVolPart(int x, int y, int z) const {
        BREAK_ON_LINE(x < m_dimX && y < m_dimY && z < m_dimZ);
        const auto& val = m_box[x * m_dimZ * m_dimY + y * m_dimZ + z];
        BREAK_ON_LINE(val.getCoords()[0] == x && val.getCoords()[1] == y &&
                      val.getCoords()[2] == z);
        return val;
    }

    void rotate(Mat rot);

    void add(const std::vector<VolPart>& vols);

    void remove(const std::vector<VolPart>& vols);

    bool isSqueezed(const VolPart& vol) const;

    bool isSqueezedV2(const VolPart& vol) const;

    bool operator==(const Box& b) const { return m_box == b.m_box; }

   private:
    std::vector<VolPart> m_box;
    int m_dimX;
    int m_dimY;
    int m_dimZ;
};
}  // namespace Geometry
