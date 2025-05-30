#pragma once

#include <string>
#include <vector>
#include <array>
#include <unordered_map>

namespace vivid::data {


struct ColorEntry {
    uint32_t rgb32;
    std::string name;
};


static const std::vector<ColorEntry> xterm =
{
    { 0xff000000, "Black" },
    { 0xff800000, "Maroon" },
    { 0xff008000, "Green" },
    { 0xff808000, "Olive" },
    { 0xff000080, "Navy" },
    { 0xff800080, "Purple" },
    { 0xff008080, "Teal" },
    { 0xffc0c0c0, "Silver" },
    { 0xff808080, "Grey" },
    { 0xffff0000, "Red" },
    { 0xff00ff00, "Lime" },
    { 0xffffff00, "Yellow" },
    { 0xff0000ff, "Blue" },
    { 0xffff00ff, "Fuchsia" },
    { 0xff00ffff, "Aqua" },
    { 0xffffffff, "White" },
    { 0xff000000, "Grey0" },
    { 0xff00005f, "NavyBlue" },
    { 0xff000087, "DarkBlue" },
    { 0xff0000af, "Blue3" },
    { 0xff0000d7, "Blue3" },
    { 0xff0000ff, "Blue1" },
    { 0xff005f00, "DarkGreen" },
    { 0xff005f5f, "DeepSkyBlue4" },
    { 0xff005f87, "DeepSkyBlue4" },
    { 0xff005faf, "DeepSkyBlue4" },
    { 0xff005fd7, "DodgerBlue3" },
    { 0xff005fff, "DodgerBlue2" },
    { 0xff008700, "Green4" },
    { 0xff00875f, "SpringGreen4" },
    { 0xff008787, "Turquoise4" },
    { 0xff0087af, "DeepSkyBlue3" },
    { 0xff0087d7, "DeepSkyBlue3" },
    { 0xff0087ff, "DodgerBlue1" },
    { 0xff00af00, "Green3" },
    { 0xff00af5f, "SpringGreen3" },
    { 0xff00af87, "DarkCyan" },
    { 0xff00afaf, "LightSeaGreen" },
    { 0xff00afd7, "DeepSkyBlue2" },
    { 0xff00afff, "DeepSkyBlue1" },
    { 0xff00d700, "Green3" },
    { 0xff00d75f, "SpringGreen3" },
    { 0xff00d787, "SpringGreen2" },
    { 0xff00d7af, "Cyan3" },
    { 0xff00d7d7, "DarkTurquoise" },
    { 0xff00d7ff, "Turquoise2" },
    { 0xff00ff00, "Green1" },
    { 0xff00ff5f, "SpringGreen2" },
    { 0xff00ff87, "SpringGreen1" },
    { 0xff00ffaf, "MediumSpringGreen" },
    { 0xff00ffd7, "Cyan2" },
    { 0xff00ffff, "Cyan1" },
    { 0xff5f0000, "DarkRed" },
    { 0xff5f005f, "DeepPink4" },
    { 0xff5f0087, "Purple4" },
    { 0xff5f00af, "Purple4" },
    { 0xff5f00d7, "Purple3" },
    { 0xff5f00ff, "BlueViolet" },
    { 0xff5f5f00, "Orange4" },
    { 0xff5f5f5f, "Grey37" },
    { 0xff5f5f87, "MediumPurple4" },
    { 0xff5f5faf, "SlateBlue3" },
    { 0xff5f5fd7, "SlateBlue3" },
    { 0xff5f5fff, "RoyalBlue1" },
    { 0xff5f8700, "Chartreuse4" },
    { 0xff5f875f, "DarkSeaGreen4" },
    { 0xff5f8787, "PaleTurquoise4" },
    { 0xff5f87af, "SteelBlue" },
    { 0xff5f87d7, "SteelBlue3" },
    { 0xff5f87ff, "CornflowerBlue" },
    { 0xff5faf00, "Chartreuse3" },
    { 0xff5faf5f, "DarkSeaGreen4" },
    { 0xff5faf87, "CadetBlue" },
    { 0xff5fafaf, "CadetBlue" },
    { 0xff5fafd7, "SkyBlue3" },
    { 0xff5fafff, "SteelBlue1" },
    { 0xff5fd700, "Chartreuse3" },
    { 0xff5fd75f, "PaleGreen3" },
    { 0xff5fd787, "SeaGreen3" },
    { 0xff5fd7af, "Aquamarine3" },
    { 0xff5fd7d7, "MediumTurquoise" },
    { 0xff5fd7ff, "SteelBlue1" },
    { 0xff5fff00, "Chartreuse2" },
    { 0xff5fff5f, "SeaGreen2" },
    { 0xff5fff87, "SeaGreen1" },
    { 0xff5fffaf, "SeaGreen1" },
    { 0xff5fffd7, "Aquamarine1" },
    { 0xff5fffff, "DarkSlateGray2" },
    { 0xff870000, "DarkRed" },
    { 0xff87005f, "DeepPink4" },
    { 0xff870087, "DarkMagenta" },
    { 0xff8700af, "DarkMagenta" },
    { 0xff8700d7, "DarkViolet" },
    { 0xff8700ff, "Purple" },
    { 0xff875f00, "Orange4" },
    { 0xff875f5f, "LightPink4" },
    { 0xff875f87, "Plum4" },
    { 0xff875faf, "MediumPurple3" },
    { 0xff875fd7, "MediumPurple3" },
    { 0xff875fff, "SlateBlue1" },
    { 0xff878700, "Yellow4" },
    { 0xff87875f, "Wheat4" },
    { 0xff878787, "Grey53" },
    { 0xff8787af, "LightSlateGrey" },
    { 0xff8787d7, "MediumPurple" },
    { 0xff8787ff, "LightSlateBlue" },
    { 0xff87af00, "Yellow4" },
    { 0xff87af5f, "DarkOliveGreen3" },
    { 0xff87af87, "DarkSeaGreen" },
    { 0xff87afaf, "LightSkyBlue3" },
    { 0xff87afd7, "LightSkyBlue3" },
    { 0xff87afff, "SkyBlue2" },
    { 0xff87d700, "Chartreuse2" },
    { 0xff87d75f, "DarkOliveGreen3" },
    { 0xff87d787, "PaleGreen3" },
    { 0xff87d7af, "DarkSeaGreen3" },
    { 0xff87d7d7, "DarkSlateGray3" },
    { 0xff87d7ff, "SkyBlue1" },
    { 0xff87ff00, "Chartreuse1" },
    { 0xff87ff5f, "LightGreen" },
    { 0xff87ff87, "LightGreen" },
    { 0xff87ffaf, "PaleGreen1" },
    { 0xff87ffd7, "Aquamarine1" },
    { 0xff87ffff, "DarkSlateGray1" },
    { 0xffaf0000, "Red3" },
    { 0xffaf005f, "DeepPink4" },
    { 0xffaf0087, "MediumVioletRed" },
    { 0xffaf00af, "Magenta3" },
    { 0xffaf00d7, "DarkViolet" },
    { 0xffaf00ff, "Purple" },
    { 0xffaf5f00, "DarkOrange3" },
    { 0xffaf5f5f, "IndianRed" },
    { 0xffaf5f87, "HotPink3" },
    { 0xffaf5faf, "MediumOrchid3" },
    { 0xffaf5fd7, "MediumOrchid" },
    { 0xffaf5fff, "MediumPurple2" },
    { 0xffaf8700, "DarkGoldenrod" },
    { 0xffaf875f, "LightSalmon3" },
    { 0xffaf8787, "RosyBrown" },
    { 0xffaf87af, "Grey63" },
    { 0xffaf87d7, "MediumPurple2" },
    { 0xffaf87ff, "MediumPurple1" },
    { 0xffafaf00, "Gold3" },
    { 0xffafaf5f, "DarkKhaki" },
    { 0xffafaf87, "NavajoWhite3" },
    { 0xffafafaf, "Grey69" },
    { 0xffafafd7, "LightSteelBlue3" },
    { 0xffafafff, "LightSteelBlue" },
    { 0xffafd700, "Yellow3" },
    { 0xffafd75f, "DarkOliveGreen3" },
    { 0xffafd787, "DarkSeaGreen3" },
    { 0xffafd7af, "DarkSeaGreen2" },
    { 0xffafd7d7, "LightCyan3" },
    { 0xffafd7ff, "LightSkyBlue1" },
    { 0xffafff00, "GreenYellow" },
    { 0xffafff5f, "DarkOliveGreen2" },
    { 0xffafff87, "PaleGreen1" },
    { 0xffafffaf, "DarkSeaGreen2" },
    { 0xffafffd7, "DarkSeaGreen1" },
    { 0xffafffff, "PaleTurquoise1" },
    { 0xffd70000, "Red3" },
    { 0xffd7005f, "DeepPink3" },
    { 0xffd70087, "DeepPink3" },
    { 0xffd700af, "Magenta3" },
    { 0xffd700d7, "Magenta3" },
    { 0xffd700ff, "Magenta2" },
    { 0xffd75f00, "DarkOrange3" },
    { 0xffd75f5f, "IndianRed" },
    { 0xffd75f87, "HotPink3" },
    { 0xffd75faf, "HotPink2" },
    { 0xffd75fd7, "Orchid" },
    { 0xffd75fff, "MediumOrchid1" },
    { 0xffd78700, "Orange3" },
    { 0xffd7875f, "LightSalmon3" },
    { 0xffd78787, "LightPink3" },
    { 0xffd787af, "Pink3" },
    { 0xffd787d7, "Plum3" },
    { 0xffd787ff, "Violet" },
    { 0xffd7af00, "Gold3" },
    { 0xffd7af5f, "LightGoldenrod3" },
    { 0xffd7af87, "Tan" },
    { 0xffd7afaf, "MistyRose3" },
    { 0xffd7afd7, "Thistle3" },
    { 0xffd7afff, "Plum2" },
    { 0xffd7d700, "Yellow3" },
    { 0xffd7d75f, "Khaki3" },
    { 0xffd7d787, "LightGoldenrod2" },
    { 0xffd7d7af, "LightYellow3" },
    { 0xffd7d7d7, "Grey84" },
    { 0xffd7d7ff, "LightSteelBlue1" },
    { 0xffd7ff00, "Yellow2" },
    { 0xffd7ff5f, "DarkOliveGreen1" },
    { 0xffd7ff87, "DarkOliveGreen1" },
    { 0xffd7ffaf, "DarkSeaGreen1" },
    { 0xffd7ffd7, "Honeydew2" },
    { 0xffd7ffff, "LightCyan1" },
    { 0xffff0000, "Red1" },
    { 0xffff005f, "DeepPink2" },
    { 0xffff0087, "DeepPink1" },
    { 0xffff00af, "DeepPink1" },
    { 0xffff00d7, "Magenta2" },
    { 0xffff00ff, "Magenta1" },
    { 0xffff5f00, "OrangeRed1" },
    { 0xffff5f5f, "IndianRed1" },
    { 0xffff5f87, "IndianRed1" },
    { 0xffff5faf, "HotPink" },
    { 0xffff5fd7, "HotPink" },
    { 0xffff5fff, "MediumOrchid1" },
    { 0xffff8700, "DarkOrange" },
    { 0xffff875f, "Salmon1" },
    { 0xffff8787, "LightCoral" },
    { 0xffff87af, "PaleVioletRed1" },
    { 0xffff87d7, "Orchid2" },
    { 0xffff87ff, "Orchid1" },
    { 0xffffaf00, "Orange1" },
    { 0xffffaf5f, "SandyBrown" },
    { 0xffffaf87, "LightSalmon1" },
    { 0xffffafaf, "LightPink1" },
    { 0xffffafd7, "Pink1" },
    { 0xffffafff, "Plum1" },
    { 0xffffd700, "Gold1" },
    { 0xffffd75f, "LightGoldenrod2" },
    { 0xffffd787, "LightGoldenrod2" },
    { 0xffffd7af, "NavajoWhite1" },
    { 0xffffd7d7, "MistyRose1" },
    { 0xffffd7ff, "Thistle1" },
    { 0xffffff00, "Yellow1" },
    { 0xffffff5f, "LightGoldenrod1" },
    { 0xffffff87, "Khaki1" },
    { 0xffffffaf, "Wheat1" },
    { 0xffffffd7, "Cornsilk1" },
    { 0xffffffff, "Grey100" },
    { 0xff080808, "Grey3" },
    { 0xff121212, "Grey7" },
    { 0xff1c1c1c, "Grey11" },
    { 0xff262626, "Grey15" },
    { 0xff303030, "Grey19" },
    { 0xff3a3a3a, "Grey23" },
    { 0xff444444, "Grey27" },
    { 0xff4e4e4e, "Grey30" },
    { 0xff585858, "Grey35" },
    { 0xff626262, "Grey39" },
    { 0xff6c6c6c, "Grey42" },
    { 0xff767676, "Grey46" },
    { 0xff808080, "Grey50" },
    { 0xff8a8a8a, "Grey54" },
    { 0xff949494, "Grey58" },
    { 0xff9e9e9e, "Grey62" },
    { 0xffa8a8a8, "Grey66" },
    { 0xffb2b2b2, "Grey70" },
    { 0xffbcbcbc, "Grey74" },
    { 0xffc6c6c6, "Grey78" },
    { 0xffd0d0d0, "Grey82" },
    { 0xffdadada, "Grey85" },
    { 0xffe4e4e4, "Grey89" },
    { 0xffeeeeee, "Grey93" }
};


static const std::unordered_map<std::string, uint8_t> xterm_names =
{
    { "black", 0 },
    { "maroon", 1 },
    { "green", 2 },
    { "olive", 3 },
    { "navy", 4 },
    { "purple", 5 },
    { "teal", 6 },
    { "silver", 7 },
    { "grey", 8 },
    { "red", 9 },
    { "lime", 10 },
    { "yellow", 11 },
    { "blue", 12 },
    { "fuchsia", 13 },
    { "aqua", 14 },
    { "white", 15 },
    { "grey0", 16 },
    { "navyblue", 17 },
    { "darkblue", 18 },
    { "blue3", 19 },
    { "blue3", 20 },
    { "blue1", 21 },
    { "darkgreen", 22 },
    { "deepskyblue4", 23 },
    { "deepskyblue4", 24 },
    { "deepskyblue4", 25 },
    { "dodgerblue3", 26 },
    { "dodgerblue2", 27 },
    { "green4", 28 },
    { "springgreen4", 29 },
    { "turquoise4", 30 },
    { "deepskyblue3", 31 },
    { "deepskyblue3", 32 },
    { "dodgerblue1", 33 },
    { "green3", 34 },
    { "springgreen3", 35 },
    { "darkcyan", 36 },
    { "lightseagreen", 37 },
    { "deepskyblue2", 38 },
    { "deepskyblue1", 39 },
    { "green3", 40 },
    { "springgreen3", 41 },
    { "springgreen2", 42 },
    { "cyan3", 43 },
    { "darkturquoise", 44 },
    { "turquoise2", 45 },
    { "green1", 46 },
    { "springgreen2", 47 },
    { "springgreen1", 48 },
    { "mediumspringgreen", 49 },
    { "cyan2", 50 },
    { "cyan1", 51 },
    { "darkred", 52 },
    { "deeppink4", 53 },
    { "purple4", 54 },
    { "purple4", 55 },
    { "purple3", 56 },
    { "blueviolet", 57 },
    { "orange4", 58 },
    { "grey37", 59 },
    { "mediumpurple4", 60 },
    { "slateblue3", 61 },
    { "slateblue3", 62 },
    { "royalblue1", 63 },
    { "chartreuse4", 64 },
    { "darkseagreen4", 65 },
    { "paleturquoise4", 66 },
    { "steelblue", 67 },
    { "steelblue3", 68 },
    { "cornflowerblue", 69 },
    { "chartreuse3", 70 },
    { "darkseagreen4", 71 },
    { "cadetblue", 72 },
    { "cadetblue", 73 },
    { "skyblue3", 74 },
    { "steelblue1", 75 },
    { "chartreuse3", 76 },
    { "palegreen3", 77 },
    { "seagreen3", 78 },
    { "aquamarine3", 79 },
    { "mediumturquoise", 80 },
    { "steelblue1", 81 },
    { "chartreuse2", 82 },
    { "seagreen2", 83 },
    { "seagreen1", 84 },
    { "seagreen1", 85 },
    { "aquamarine1", 86 },
    { "darkslategray2", 87 },
    { "darkred", 88 },
    { "deeppink4", 89 },
    { "darkmagenta", 90 },
    { "darkmagenta", 91 },
    { "darkviolet", 92 },
    { "purple", 93 },
    { "orange4", 94 },
    { "lightpink4", 95 },
    { "plum4", 96 },
    { "mediumpurple3", 97 },
    { "mediumpurple3", 98 },
    { "slateblue1", 99 },
    { "yellow4", 100 },
    { "wheat4", 101 },
    { "grey53", 102 },
    { "lightslategrey", 103 },
    { "mediumpurple", 104 },
    { "lightslateblue", 105 },
    { "yellow4", 106 },
    { "darkolivegreen3", 107 },
    { "darkseagreen", 108 },
    { "lightskyblue3", 109 },
    { "lightskyblue3", 110 },
    { "skyblue2", 111 },
    { "chartreuse2", 112 },
    { "darkolivegreen3", 113 },
    { "palegreen3", 114 },
    { "darkseagreen3", 115 },
    { "darkslategray3", 116 },
    { "skyblue1", 117 },
    { "chartreuse1", 118 },
    { "lightgreen", 119 },
    { "lightgreen", 120 },
    { "palegreen1", 121 },
    { "aquamarine1", 122 },
    { "darkslategray1", 123 },
    { "red3", 124 },
    { "deeppink4", 125 },
    { "mediumvioletred", 126 },
    { "magenta3", 127 },
    { "darkviolet", 128 },
    { "purple", 129 },
    { "darkorange3", 130 },
    { "indianred", 131 },
    { "hotpink3", 132 },
    { "mediumorchid3", 133 },
    { "mediumorchid", 134 },
    { "mediumpurple2", 135 },
    { "darkgoldenrod", 136 },
    { "lightsalmon3", 137 },
    { "rosybrown", 138 },
    { "grey63", 139 },
    { "mediumpurple2", 140 },
    { "mediumpurple1", 141 },
    { "gold3", 142 },
    { "darkkhaki", 143 },
    { "navajowhite3", 144 },
    { "grey69", 145 },
    { "lightsteelblue3", 146 },
    { "lightsteelblue", 147 },
    { "yellow3", 148 },
    { "darkolivegreen3", 149 },
    { "darkseagreen3", 150 },
    { "darkseagreen2", 151 },
    { "lightcyan3", 152 },
    { "lightskyblue1", 153 },
    { "greenyellow", 154 },
    { "darkolivegreen2", 155 },
    { "palegreen1", 156 },
    { "darkseagreen2", 157 },
    { "darkseagreen1", 158 },
    { "paleturquoise1", 159 },
    { "red3", 160 },
    { "deeppink3", 161 },
    { "deeppink3", 162 },
    { "magenta3", 163 },
    { "magenta3", 164 },
    { "magenta2", 165 },
    { "darkorange3", 166 },
    { "indianred", 167 },
    { "hotpink3", 168 },
    { "hotpink2", 169 },
    { "orchid", 170 },
    { "mediumorchid1", 171 },
    { "orange3", 172 },
    { "lightsalmon3", 173 },
    { "lightpink3", 174 },
    { "pink3", 175 },
    { "plum3", 176 },
    { "violet", 177 },
    { "gold3", 178 },
    { "lightgoldenrod3", 179 },
    { "tan", 180 },
    { "mistyrose3", 181 },
    { "thistle3", 182 },
    { "plum2", 183 },
    { "yellow3", 184 },
    { "khaki3", 185 },
    { "lightgoldenrod2", 186 },
    { "lightyellow3", 187 },
    { "grey84", 188 },
    { "lightsteelblue1", 189 },
    { "yellow2", 190 },
    { "darkolivegreen1", 191 },
    { "darkolivegreen1", 192 },
    { "darkseagreen1", 193 },
    { "honeydew2", 194 },
    { "lightcyan1", 195 },
    { "red1", 196 },
    { "deeppink2", 197 },
    { "deeppink1", 198 },
    { "deeppink1", 199 },
    { "magenta2", 200 },
    { "magenta1", 201 },
    { "orangered1", 202 },
    { "indianred1", 203 },
    { "indianred1", 204 },
    { "hotpink", 205 },
    { "hotpink", 206 },
    { "mediumorchid1", 207 },
    { "darkorange", 208 },
    { "salmon1", 209 },
    { "lightcoral", 210 },
    { "palevioletred1", 211 },
    { "orchid2", 212 },
    { "orchid1", 213 },
    { "orange1", 214 },
    { "sandybrown", 215 },
    { "lightsalmon1", 216 },
    { "lightpink1", 217 },
    { "pink1", 218 },
    { "plum1", 219 },
    { "gold1", 220 },
    { "lightgoldenrod2", 221 },
    { "lightgoldenrod2", 222 },
    { "navajowhite1", 223 },
    { "mistyrose1", 224 },
    { "thistle1", 225 },
    { "yellow1", 226 },
    { "lightgoldenrod1", 227 },
    { "khaki1", 228 },
    { "wheat1", 229 },
    { "cornsilk1", 230 },
    { "grey100", 231 },
    { "grey3", 232 },
    { "grey7", 233 },
    { "grey11", 234 },
    { "grey15", 235 },
    { "grey19", 236 },
    { "grey23", 237 },
    { "grey27", 238 },
    { "grey30", 239 },
    { "grey35", 240 },
    { "grey39", 241 },
    { "grey42", 242 },
    { "grey46", 243 },
    { "grey50", 244 },
    { "grey54", 245 },
    { "grey58", 246 },
    { "grey62", 247 },
    { "grey66", 248 },
    { "grey70", 249 },
    { "grey74", 250 },
    { "grey78", 251 },
    { "grey82", 252 },
    { "grey85", 253 },
    { "grey89", 254 },
    { "grey93", 255 }
};


static const std::unordered_map<uint32_t, uint8_t> xterm_rgb32 =
{
    { 0xff000000, 0 },
    { 0xff800000, 1 },
    { 0xff008000, 2 },
    { 0xff808000, 3 },
    { 0xff000080, 4 },
    { 0xff800080, 5 },
    { 0xff008080, 6 },
    { 0xffc0c0c0, 7 },
    { 0xff808080, 8 },
    { 0xffff0000, 9 },
    { 0xff00ff00, 10 },
    { 0xffffff00, 11 },
    { 0xff0000ff, 12 },
    { 0xffff00ff, 13 },
    { 0xff00ffff, 14 },
    { 0xffffffff, 15 },
    { 0xff000000, 16 },
    { 0xff00005f, 17 },
    { 0xff000087, 18 },
    { 0xff0000af, 19 },
    { 0xff0000d7, 20 },
    { 0xff0000ff, 21 },
    { 0xff005f00, 22 },
    { 0xff005f5f, 23 },
    { 0xff005f87, 24 },
    { 0xff005faf, 25 },
    { 0xff005fd7, 26 },
    { 0xff005fff, 27 },
    { 0xff008700, 28 },
    { 0xff00875f, 29 },
    { 0xff008787, 30 },
    { 0xff0087af, 31 },
    { 0xff0087d7, 32 },
    { 0xff0087ff, 33 },
    { 0xff00af00, 34 },
    { 0xff00af5f, 35 },
    { 0xff00af87, 36 },
    { 0xff00afaf, 37 },
    { 0xff00afd7, 38 },
    { 0xff00afff, 39 },
    { 0xff00d700, 40 },
    { 0xff00d75f, 41 },
    { 0xff00d787, 42 },
    { 0xff00d7af, 43 },
    { 0xff00d7d7, 44 },
    { 0xff00d7ff, 45 },
    { 0xff00ff00, 46 },
    { 0xff00ff5f, 47 },
    { 0xff00ff87, 48 },
    { 0xff00ffaf, 49 },
    { 0xff00ffd7, 50 },
    { 0xff00ffff, 51 },
    { 0xff5f0000, 52 },
    { 0xff5f005f, 53 },
    { 0xff5f0087, 54 },
    { 0xff5f00af, 55 },
    { 0xff5f00d7, 56 },
    { 0xff5f00ff, 57 },
    { 0xff5f5f00, 58 },
    { 0xff5f5f5f, 59 },
    { 0xff5f5f87, 60 },
    { 0xff5f5faf, 61 },
    { 0xff5f5fd7, 62 },
    { 0xff5f5fff, 63 },
    { 0xff5f8700, 64 },
    { 0xff5f875f, 65 },
    { 0xff5f8787, 66 },
    { 0xff5f87af, 67 },
    { 0xff5f87d7, 68 },
    { 0xff5f87ff, 69 },
    { 0xff5faf00, 70 },
    { 0xff5faf5f, 71 },
    { 0xff5faf87, 72 },
    { 0xff5fafaf, 73 },
    { 0xff5fafd7, 74 },
    { 0xff5fafff, 75 },
    { 0xff5fd700, 76 },
    { 0xff5fd75f, 77 },
    { 0xff5fd787, 78 },
    { 0xff5fd7af, 79 },
    { 0xff5fd7d7, 80 },
    { 0xff5fd7ff, 81 },
    { 0xff5fff00, 82 },
    { 0xff5fff5f, 83 },
    { 0xff5fff87, 84 },
    { 0xff5fffaf, 85 },
    { 0xff5fffd7, 86 },
    { 0xff5fffff, 87 },
    { 0xff870000, 88 },
    { 0xff87005f, 89 },
    { 0xff870087, 90 },
    { 0xff8700af, 91 },
    { 0xff8700d7, 92 },
    { 0xff8700ff, 93 },
    { 0xff875f00, 94 },
    { 0xff875f5f, 95 },
    { 0xff875f87, 96 },
    { 0xff875faf, 97 },
    { 0xff875fd7, 98 },
    { 0xff875fff, 99 },
    { 0xff878700, 100 },
    { 0xff87875f, 101 },
    { 0xff878787, 102 },
    { 0xff8787af, 103 },
    { 0xff8787d7, 104 },
    { 0xff8787ff, 105 },
    { 0xff87af00, 106 },
    { 0xff87af5f, 107 },
    { 0xff87af87, 108 },
    { 0xff87afaf, 109 },
    { 0xff87afd7, 110 },
    { 0xff87afff, 111 },
    { 0xff87d700, 112 },
    { 0xff87d75f, 113 },
    { 0xff87d787, 114 },
    { 0xff87d7af, 115 },
    { 0xff87d7d7, 116 },
    { 0xff87d7ff, 117 },
    { 0xff87ff00, 118 },
    { 0xff87ff5f, 119 },
    { 0xff87ff87, 120 },
    { 0xff87ffaf, 121 },
    { 0xff87ffd7, 122 },
    { 0xff87ffff, 123 },
    { 0xffaf0000, 124 },
    { 0xffaf005f, 125 },
    { 0xffaf0087, 126 },
    { 0xffaf00af, 127 },
    { 0xffaf00d7, 128 },
    { 0xffaf00ff, 129 },
    { 0xffaf5f00, 130 },
    { 0xffaf5f5f, 131 },
    { 0xffaf5f87, 132 },
    { 0xffaf5faf, 133 },
    { 0xffaf5fd7, 134 },
    { 0xffaf5fff, 135 },
    { 0xffaf8700, 136 },
    { 0xffaf875f, 137 },
    { 0xffaf8787, 138 },
    { 0xffaf87af, 139 },
    { 0xffaf87d7, 140 },
    { 0xffaf87ff, 141 },
    { 0xffafaf00, 142 },
    { 0xffafaf5f, 143 },
    { 0xffafaf87, 144 },
    { 0xffafafaf, 145 },
    { 0xffafafd7, 146 },
    { 0xffafafff, 147 },
    { 0xffafd700, 148 },
    { 0xffafd75f, 149 },
    { 0xffafd787, 150 },
    { 0xffafd7af, 151 },
    { 0xffafd7d7, 152 },
    { 0xffafd7ff, 153 },
    { 0xffafff00, 154 },
    { 0xffafff5f, 155 },
    { 0xffafff87, 156 },
    { 0xffafffaf, 157 },
    { 0xffafffd7, 158 },
    { 0xffafffff, 159 },
    { 0xffd70000, 160 },
    { 0xffd7005f, 161 },
    { 0xffd70087, 162 },
    { 0xffd700af, 163 },
    { 0xffd700d7, 164 },
    { 0xffd700ff, 165 },
    { 0xffd75f00, 166 },
    { 0xffd75f5f, 167 },
    { 0xffd75f87, 168 },
    { 0xffd75faf, 169 },
    { 0xffd75fd7, 170 },
    { 0xffd75fff, 171 },
    { 0xffd78700, 172 },
    { 0xffd7875f, 173 },
    { 0xffd78787, 174 },
    { 0xffd787af, 175 },
    { 0xffd787d7, 176 },
    { 0xffd787ff, 177 },
    { 0xffd7af00, 178 },
    { 0xffd7af5f, 179 },
    { 0xffd7af87, 180 },
    { 0xffd7afaf, 181 },
    { 0xffd7afd7, 182 },
    { 0xffd7afff, 183 },
    { 0xffd7d700, 184 },
    { 0xffd7d75f, 185 },
    { 0xffd7d787, 186 },
    { 0xffd7d7af, 187 },
    { 0xffd7d7d7, 188 },
    { 0xffd7d7ff, 189 },
    { 0xffd7ff00, 190 },
    { 0xffd7ff5f, 191 },
    { 0xffd7ff87, 192 },
    { 0xffd7ffaf, 193 },
    { 0xffd7ffd7, 194 },
    { 0xffd7ffff, 195 },
    { 0xffff0000, 196 },
    { 0xffff005f, 197 },
    { 0xffff0087, 198 },
    { 0xffff00af, 199 },
    { 0xffff00d7, 200 },
    { 0xffff00ff, 201 },
    { 0xffff5f00, 202 },
    { 0xffff5f5f, 203 },
    { 0xffff5f87, 204 },
    { 0xffff5faf, 205 },
    { 0xffff5fd7, 206 },
    { 0xffff5fff, 207 },
    { 0xffff8700, 208 },
    { 0xffff875f, 209 },
    { 0xffff8787, 210 },
    { 0xffff87af, 211 },
    { 0xffff87d7, 212 },
    { 0xffff87ff, 213 },
    { 0xffffaf00, 214 },
    { 0xffffaf5f, 215 },
    { 0xffffaf87, 216 },
    { 0xffffafaf, 217 },
    { 0xffffafd7, 218 },
    { 0xffffafff, 219 },
    { 0xffffd700, 220 },
    { 0xffffd75f, 221 },
    { 0xffffd787, 222 },
    { 0xffffd7af, 223 },
    { 0xffffd7d7, 224 },
    { 0xffffd7ff, 225 },
    { 0xffffff00, 226 },
    { 0xffffff5f, 227 },
    { 0xffffff87, 228 },
    { 0xffffffaf, 229 },
    { 0xffffffd7, 230 },
    { 0xffffffff, 231 },
    { 0xff080808, 232 },
    { 0xff121212, 233 },
    { 0xff1c1c1c, 234 },
    { 0xff262626, 235 },
    { 0xff303030, 236 },
    { 0xff3a3a3a, 237 },
    { 0xff444444, 238 },
    { 0xff4e4e4e, 239 },
    { 0xff585858, 240 },
    { 0xff626262, 241 },
    { 0xff6c6c6c, 242 },
    { 0xff767676, 243 },
    { 0xff808080, 244 },
    { 0xff8a8a8a, 245 },
    { 0xff949494, 246 },
    { 0xff9e9e9e, 247 },
    { 0xffa8a8a8, 248 },
    { 0xffb2b2b2, 249 },
    { 0xffbcbcbc, 250 },
    { 0xffc6c6c6, 251 },
    { 0xffd0d0d0, 252 },
    { 0xffdadada, 253 },
    { 0xffe4e4e4, 254 },
    { 0xffeeeeee, 255 }
};


static const std::array<uint8_t, 256> xterm_grey =
{
     16,  16,  16,  16,  16, 232, 232, 232,
    232, 232, 232, 232, 232, 232, 233, 233,
    233, 233, 233, 233, 233, 233, 233, 233,
    234, 234, 234, 234, 234, 234, 234, 234,
    234, 234, 235, 235, 235, 235, 235, 235,
    235, 235, 235, 235, 236, 236, 236, 236,
    236, 236, 236, 236, 236, 236, 237, 237,
    237, 237, 237, 237, 237, 237, 237, 237,
    238, 238, 238, 238, 238, 238, 238, 238,
    238, 238, 239, 239, 239, 239, 239, 239,
    239, 239, 239, 239, 240, 240, 240, 240,
    240, 240, 240, 240,  59,  59,  59,  59,
     59, 241, 241, 241, 241, 241, 241, 241,
    242, 242, 242, 242, 242, 242, 242, 242,
    242, 242, 243, 243, 243, 243, 243, 243,
    243, 243, 243, 244, 244, 244, 244, 244,
    244, 244, 244, 244, 102, 102, 102, 102,
    102, 245, 245, 245, 245, 245, 245, 246,
    246, 246, 246, 246, 246, 246, 246, 246,
    246, 247, 247, 247, 247, 247, 247, 247,
    247, 247, 247, 248, 248, 248, 248, 248,
    248, 248, 248, 248, 145, 145, 145, 145,
    145, 249, 249, 249, 249, 249, 249, 250,
    250, 250, 250, 250, 250, 250, 250, 250,
    250, 251, 251, 251, 251, 251, 251, 251,
    251, 251, 251, 252, 252, 252, 252, 252,
    252, 252, 252, 252, 188, 188, 188, 188,
    188, 253, 253, 253, 253, 253, 253, 254,
    254, 254, 254, 254, 254, 254, 254, 254,
    254, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 231,
    231, 231, 231, 231, 231, 231, 231, 231
};


}   //  ::vivid::res
