//
// Created by Tom Hancocks on 26/03/2021.
//

#include "libGraphite/quicktime/imagedesc.hpp"

// MARK: - Constructors

graphite::qt::imagedesc::imagedesc(data::reader& reader)
{
    m_length = reader.read_signed_long();
    if (m_length != 86) {
        throw std::runtime_error("Invalid QuickTime image description.");
    }
    m_compressor = reader.read_long();
    reader.move(24);
    m_width = reader.read_signed_short();
    m_height = reader.read_signed_short();
    reader.move(8);
    m_data_size = reader.read_signed_long();
    reader.move(34);
    m_depth = reader.read_signed_short();
    if (m_depth > 32) {
        m_depth -= 32; // grayscale
    }
    m_clut = reader.read_signed_short();
}

// MARK: - Accessors

auto graphite::qt::imagedesc::length() const -> int32_t
{
    return m_length;
}

auto graphite::qt::imagedesc::compressor() const -> uint32_t
{
    return m_compressor;
}

auto graphite::qt::imagedesc::width() const -> int16_t
{
    return m_width;
}

auto graphite::qt::imagedesc::height() const -> int16_t
{
    return m_height;
}

auto graphite::qt::imagedesc::data_size() const -> int32_t
{
    return m_data_size;
}

auto graphite::qt::imagedesc::depth() const -> int16_t
{
    return m_depth;
}

auto graphite::qt::imagedesc::clut() const -> int16_t
{
    return m_clut;
}
