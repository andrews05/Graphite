//
// Created by Tom Hancocks on 26/03/2021.
//

#if !defined(GRAPHITE_IMAGEDESC_HPP)
#define GRAPHITE_IMAGEDESC_HPP

#include <memory>
#include "libGraphite/data/reader.hpp"

namespace graphite::qt {

    struct imagedesc
    {
    private:
        int32_t m_length { 0 };
        uint32_t m_compressor { 0 };
        int16_t m_width { 0 };
        int16_t m_height { 0 };
        int32_t m_data_size { 0 };
        int16_t m_depth { 0 };
        int16_t m_clut { 0 };
    public:
        explicit imagedesc(data::reader& reader);
        
        [[nodiscard]] auto length() const -> int32_t;
        [[nodiscard]] auto compressor() const -> uint32_t;
        [[nodiscard]] auto width() const -> int16_t;
        [[nodiscard]] auto height() const -> int16_t;
        [[nodiscard]] auto data_size() const -> int32_t;
        [[nodiscard]] auto depth() const -> int16_t;
        [[nodiscard]] auto clut() const -> int16_t;
    };

}

#endif //GRAPHITE_IMAGEDESC_HPP
