//
// Created by Tom Hancocks on 26/03/2021.
//

#if !defined(GRAPHITE_QTRLE_HPP)
#define GRAPHITE_QTRLE_HPP

#include <memory>
#include "libGraphite/data/reader.hpp"
#include "libGraphite/quickdraw/clut.hpp"
#include "libGraphite/quickdraw/internal/surface.hpp"
#include "libGraphite/quicktime/imagedesc.hpp"

namespace graphite::qt {

    struct rle
    {
    public:
        static auto decode(const qt::imagedesc& imagedesc, data::reader& reader) -> qd::surface;
    };

}

#endif //GRAPHITE_QTRLE_HPP
