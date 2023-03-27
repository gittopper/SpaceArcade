#pragma once

#include "geometry.h"

namespace Geometry
{
std::ostream& operator << (std::ostream& os, const Vector& vec);

std::ostream& operator << (std::ostream& os, const VolPart& v);

std::ostream& operator << (std::ostream& os, const Piece& v);

std::ostream& operator << (std::ostream& os, const PiecesSet& v);

std::ostream& operator << (std::ostream& os, const Box& b);
}
