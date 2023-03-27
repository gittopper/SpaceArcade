#include "box.h"

#include "bbox.h"

namespace Geometry {

Box::Box(int DX, int DY, int DZ) : m_dimX(DX), m_dimY(DY), m_dimZ(DZ) {
  for (int i = 0; i < DX; i++) {
    for (int j = 0; j < DY; j++) {
      for (int k = 0; k < DZ; k++) {
        VolPart v = VolPart(VolPart::VolType::Empty, Vector(i, j, k));
        m_box.push_back(v);
        BREAK_ON_LINE(getVolPart(i, j, k) == v);
      }
    }
  }
}
bool Box::isSqueezed(const VolPart& vol) const {
  if (vol.type() != VolPart::VolType::Angle) return false;
  BREAK_ON_LINE(!vol.getDir()[0] || !vol.getDir()[1] || !vol.getDir()[2]);
  int n = 0;
  if (vol.getDir()[0] != 0) {
    const VolPart& nVol = getVolPart(vol.getCoords()[0] + vol.getDir()[0],
                                     vol.getCoords()[1], vol.getCoords()[2]);
    if (nVol.type() == VolPart::VolType::Full) {
      n++;
    } else if (nVol.type() == VolPart::VolType::Angle) {
      if (vol.getDir()[0] * nVol.getDir()[0] >= 0) {
        n++;
      }
    }
  }
  if (vol.getDir()[1] != 0) {
    const VolPart& nVol =
        getVolPart(vol.getCoords()[0], vol.getCoords()[1] + vol.getDir()[1],
                   vol.getCoords()[2]);
    if (nVol.type() == VolPart::VolType::Full) {
      n++;
    } else if (nVol.type() == VolPart::VolType::Angle) {
      if (vol.getDir()[1] * nVol.getDir()[1] >= 0) {
        n++;
      }
    }
  }
  if (vol.getDir()[2] != 0) {
    const VolPart& nVol = getVolPart(vol.getCoords()[0], vol.getCoords()[1],
                                     vol.getCoords()[2] + vol.getDir()[2]);
    if (nVol.type() == VolPart::VolType::Full) {
      n++;
    } else if (nVol.type() == VolPart::VolType::Angle) {
      if (vol.getDir()[2] * nVol.getDir()[2] >= 0) {
        n++;
      }
    }
  }
  return n > 1;
}
bool Box::isSqueezedV2(const VolPart& vol) const {
  if (vol.type() != VolPart::VolType::Angle) return false;

  BREAK_ON_LINE(dot(vol.getDir(), vol.getDir()) == 2);
  int n = 0;
  if (vol.getDir()[0] > 0) {
    const VolPart& nVol = getVolPart(vol.getCoords() + XSHIFT);
    if (nVol.type() == VolPart::VolType::Full || (nVol.hasSide(0, 0))) {
      n++;
    }
  }
  if (vol.getDir()[0] < 0) {
    const VolPart& nVol = getVolPart(vol.getCoords() - XSHIFT);
    if (nVol.type() == VolPart::VolType::Full || nVol.hasSide(0, 1)) {
      n++;
    }
  }

  if (vol.getDir()[1] > 0) {
    const VolPart& nVol = getVolPart(vol.getCoords() + YSHIFT);
    if (nVol.type() == VolPart::VolType::Full || nVol.hasSide(1, 0)) {
      n++;
    }
  }
  if (vol.getDir()[1] < 0) {
    const VolPart& nVol = getVolPart(vol.getCoords() - YSHIFT);
    if (nVol.type() == VolPart::VolType::Full || nVol.hasSide(1, 1)) {
      n++;
    }
  }

  if (vol.getDir()[2] > 0) {
    const VolPart& nVol = getVolPart(vol.getCoords() + ZSHIFT);
    if (nVol.type() == VolPart::VolType::Full || nVol.hasSide(2, 0)) {
      n++;
    }
  }
  if (vol.getDir()[2] < 0) {
    const VolPart& nVol = getVolPart(vol.getCoords() - ZSHIFT);
    if (nVol.type() == VolPart::VolType::Full || nVol.hasSide(2, 1)) {
      n++;
    }
  }

  return n > 1;
}

void Box::add(const std::vector<VolPart>& vols) {
  for (unsigned i = 0; i < vols.size(); i++) {
    getVolPart(vols[i].getCoords()) += vols[i];
  }
}

void Box::rotate(Mat rot) {
  BBox bbox;

  for (int i = 0; i < m_dimX; i++) {
    for (int j = 0; j < m_dimY; j++) {
      for (int k = 0; k < m_dimZ; k++) {
        Vector v(i, j, k);
        v = rot * v;
        bbox.merge(v);
      }
    }
  }

  Box newBox(bbox.maxV[0] - bbox.minV[0] + 1, bbox.maxV[1] - bbox.minV[1] + 1,
             bbox.maxV[2] - bbox.minV[2] + 1);
  Vector shift(-bbox.minV);

  for (int i = 0; i < m_dimX; i++) {
    for (int j = 0; j < m_dimY; j++) {
      for (int k = 0; k < m_dimZ; k++) {
        VolPart newVol(getVolPart(i, j, k));
        newVol.rotate(rot).shift(shift);
        const Vector& xyz = newVol.getCoords();
        newBox.getVolPart(xyz[0], xyz[1], xyz[2]) = newVol;
      }
    }
  }
  *this = newBox;
}

void Box::remove(const std::vector<VolPart>& vols) {
  for (unsigned i = 0; i < vols.size(); i++) {
    getVolPart(vols[i].getCoords()) -= vols[i];
  }
}
}  // namespace Geometry
