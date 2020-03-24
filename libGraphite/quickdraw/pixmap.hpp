//
// Created by Tom Hancocks on 19/03/2020.
//

#if !defined(GRAPHITE_PIXMAP_HPP)
#define GRAPHITE_PIXMAP_HPP

#include <cstdint>
#include <libGraphite/data/reader.hpp>
#include "libGraphite/quickdraw/geometry.hpp"
#include "libGraphite/data/data.hpp"

namespace graphite { namespace qd {

    enum pixel_format
    {
        monochrome = 0x01,          // 1 bit indexed
        indexed_2 = 0x02,           // 2 bit indexed
        indexed_4 = 0x04,           // 4 bit indexed
        indexed_8 = 0x08,           // 8 bit indexed
        b16_rgb555 = 0x10,          // 16 bit, RGB 555 (Mac)
        true_color = 0x18,          // 24 bit RGB
        true_color_alpha = 0x20,    // 32 bit ARGB
    };

    class pixmap
    {
    private:
        uint32_t m_base_address;
        int16_t m_row_bytes;
        graphite::qd::rect m_bounds;
        int16_t m_pm_version;
        int16_t m_pack_type;
        int32_t m_pack_size;
        double m_h_res;
        double m_v_res;
        int16_t m_pixel_type;
        int16_t m_pixel_size;
        int16_t m_cmp_count;
        int16_t m_cmp_size;
        enum pixel_format m_pixel_format;
        uint32_t m_pm_table;
        uint32_t m_pm_extension;
    public:
        static const int length { 50 };

        pixmap();
        pixmap(std::shared_ptr<data::data> data);

        graphite::qd::rect bounds() const;
        int16_t row_bytes() const;
        int16_t pack_type() const;
        int16_t pack_size() const;
        int16_t pixel_type() const;
        int16_t pixel_size() const;
        int16_t cmp_count() const;
        int16_t cmp_size() const;
        enum pixel_format pixel_format() const;
    };

}};

#endif //GRAPHITE_PIXMAP_HPP