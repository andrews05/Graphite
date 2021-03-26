//
// Created by Tom Hancocks on 26/03/2021.
//

#include "libGraphite/quickdraw/clut.hpp"
#include "libGraphite/quicktime/rle.hpp"

auto graphite::qt::rle::decode(const qt::imagedesc& imagedesc, data::reader& reader) -> qd::surface
{
    auto clut = qd::clut::load_resource(imagedesc.clut());
    auto surface = qd::surface(imagedesc.width(), imagedesc.height());
    auto chunk_size = reader.read_long();
    auto header = reader.read_short();
    auto y = 0;
    if (header & 0x0008) {
        y = reader.read_short();
        reader.move(6);
    }
    
    int8_t skip;
    int8_t code;
    auto x = 0;
    while ((skip = reader.read_byte())) {
        x += skip-1;
        while (true) {
            code = reader.read_signed_byte();
            if (code == 0) {
                break;
            } else if (code == -1) {
                x = 0;
                y++;
                break;
            } else if (code > 0) {
                for (auto i = 0; i < 4 * code; ++i) {
                    auto color = clut->get(reader.read_byte());
                    surface.set(x++, y, color);
                }
            } else {
                auto color1 = clut->get(reader.read_byte());
                auto color2 = clut->get(reader.read_byte());
                auto color3 = clut->get(reader.read_byte());
                auto color4 = clut->get(reader.read_byte());
                for (auto i = 0; i < -code; ++i) {
                    surface.set(x++, y, color1);
                    surface.set(x++, y, color2);
                    surface.set(x++, y, color3);
                    surface.set(x++, y, color4);
                }
            }
        }
    }
    return surface;
}
