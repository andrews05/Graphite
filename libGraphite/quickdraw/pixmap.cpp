//
// Created by Tom Hancocks on 19/03/2020.
//

#include "libGraphite/quickdraw/pixmap.hpp"
#include "libGraphite/data/reader.hpp"

// MARK: - Constructors

graphite::qd::pixmap::pixmap()
    : m_bounds(0, 0, 100, 100)
{

}

graphite::qd::pixmap::pixmap(qd::rect frame)
    : m_base_address(0x000000ff),
      m_row_bytes(frame.width() * 4),
      m_bounds(frame),
      m_pm_version(0),
      m_pack_type(4),
      m_pack_size(0),
      m_h_res(0.001098632812),
      m_v_res(0.001098632812),
      m_pixel_type(16),
      m_pixel_size(32),
      m_cmp_count(3),
      m_cmp_size(8),
      m_pixel_format(unknown),
      m_pm_table(0),
      m_pm_extension(0)
{
}

graphite::qd::pixmap::pixmap(std::shared_ptr<data::data> px_data)
    : m_bounds(0, 0, 0, 0)
{
    // Setup a new data reader for the pixmap
    data::reader px_reader(px_data);

    // Read each of the member fields for the pixmap.
    m_base_address = px_reader.read_long();
    m_row_bytes = px_reader.read_signed_short() & 0x7FFF;
    m_bounds = graphite::qd::rect::read(px_reader, qd::rect::qd);
    m_pm_version = px_reader.read_signed_short();
    m_pack_type = px_reader.read_signed_short();
    m_pack_size = px_reader.read_signed_long();
    m_h_res = static_cast<double>(px_reader.read_signed_long() / static_cast<double>(1 << 16));
    m_v_res = static_cast<double>(px_reader.read_signed_long() / static_cast<double>(1 << 16));
    m_pixel_type = px_reader.read_signed_short();
    m_pixel_size = px_reader.read_signed_short();
    m_cmp_count = px_reader.read_signed_short();
    m_cmp_size = px_reader.read_signed_short();
    m_pixel_format = static_cast<graphite::qd::pixel_format>(px_reader.read_long());
    m_pm_table = px_reader.read_long();
    m_pm_extension = px_reader.read_long();
}

// MARK: - Accessors

auto graphite::qd::pixmap::bounds() const -> graphite::qd::rect
{
    return m_bounds;
}

auto graphite::qd::pixmap::set_bounds(const graphite::qd::rect rect) -> void
{
    m_bounds = rect;
}

auto graphite::qd::pixmap::row_bytes() const -> int16_t
{
    return m_row_bytes;
}

auto graphite::qd::pixmap::set_row_bytes(const int16_t row_bytes) -> void
{
    m_row_bytes = row_bytes;
}

auto graphite::qd::pixmap::pack_type() const -> int16_t
{
    return m_pack_type;
}

auto graphite::qd::pixmap::set_pack_type(const int16_t pack_type) -> void
{
    m_pack_type = pack_type;
}

auto graphite::qd::pixmap::pack_size() const -> int16_t
{
    return m_pack_size;
}

auto graphite::qd::pixmap::set_pack_size(const int16_t pack_size) -> void
{
    m_pack_size = pack_size;
}

auto graphite::qd::pixmap::pixel_type() const -> int16_t
{
    return m_pixel_type;
}

auto graphite::qd::pixmap::set_pixel_type(const int16_t pixel_type) -> void
{
    m_pixel_type = pixel_type;
}

auto graphite::qd::pixmap::pixel_size() const -> int16_t
{
    return m_pixel_size;
}

auto graphite::qd::pixmap::set_pixel_size(const int16_t pixel_size) -> void
{
    m_pixel_size = pixel_size;
}

auto graphite::qd::pixmap::cmp_count() const -> int16_t
{
    return m_cmp_count;
}

auto graphite::qd::pixmap::set_cmp_count(const int16_t cmp_count) -> void
{
    m_cmp_count = cmp_count;
}

auto graphite::qd::pixmap::cmp_size() const -> int16_t
{
    return m_cmp_size;
}

auto graphite::qd::pixmap::set_cmp_size(const int16_t cmp_size) -> void
{
    m_cmp_size = cmp_size;
}

auto graphite::qd::pixmap::pixel_format() const -> enum graphite::qd::pixel_format
{
    return m_pixel_format;
}

// MARK: -

auto graphite::qd::pixmap::write(graphite::data::writer& writer) -> void
{
    writer.write_long(m_base_address);
    writer.write_short(0x8000 | m_row_bytes);
    m_bounds.write(writer, rect::qd);
    writer.write_signed_short(m_pm_version);
    writer.write_signed_short(m_pack_type);
    writer.write_signed_long(m_pack_size);
    writer.write_signed_long(static_cast<int32_t>(m_h_res * (1 << 16)));
    writer.write_signed_long(static_cast<int32_t>(m_v_res * (1 << 16)));
    writer.write_signed_short(m_pixel_type);
    writer.write_signed_short(m_pixel_size);
    writer.write_signed_short(m_cmp_count);
    writer.write_signed_short(m_cmp_size);
    writer.write_signed_long(static_cast<int32_t>(m_pixel_format));
    writer.write_long(m_pm_table);
    writer.write_signed_long(m_pm_extension);
}