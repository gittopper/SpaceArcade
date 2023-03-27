#include "geometry.h"

namespace Geometry {

std::ostream& operator<<(std::ostream& os, const Vector& vec) {
  std::cout << "(" << vec[0] << "," << vec[1] << "," << vec[2] << ")";
  return os;
}

std::ostream& operator<<(std::ostream& os, const VolPart& v) {
  std::cout << (v.type() == VolPart::VolType::Empty
                    ? "Empty"
                    : v.type() == VolPart::VolType::Full ? "Full" : "Angle");
  std::cout << v.getCoords();
  if (v.type() == VolPart::VolType::Angle) std::cout << "," << v.getDir();
  return os;
}

std::ostream& operator<<(std::ostream& os, const Piece& p) {
  std::cout << "Part number " << p.id << ":" << std::endl;
  for (std::vector<VolPart>::const_iterator it = p.parts.begin();
       it != p.parts.end(); ++it) {
    std::cout << *it << std::endl;
  }
  std::cout << std::endl;
  return os;
}

std::ostream& operator<<(std::ostream& os, const PiecesSet& v) {
  for (unsigned i = 0; i < v.size(); i++) {
    std::cout << v[i];
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const Box& b) {
  int dimX = b.getDimX();
  int dimY = b.getDimY();
  int dimZ = b.getDimZ();
  for (int z = dimZ - 1; z >= 0; z--) {
    for (int x = dimX - 1; x >= 0; x--) {
      for (int y = 0; y <= dimY - 1; y++) {
        VolPart::VolType t = b.getVolPart(x, y, z).type();
        char s = t == VolPart::VolType::Empty
                     ? ' '
                     : t == VolPart::VolType::Full ? 178 : 176;
        // cout << b.getVolPart(x,y,z);
        std::cout << s;
      }
      std::cout << " ";
    }
    std::cout << std::endl;
  }
  return os;
}

}  // namespace Geometry
