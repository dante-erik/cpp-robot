#pragma once

#include <cmath>
#include <Windows.h>

namespace color
{
    // Colors From: https://www.computerhope.com/htmcolor.htm
    namespace colors
    {
        constexpr RGBQUAD BLACK{0x00, 0x00, 0x00, 0};
        constexpr RGBQUAD NIGHT{0x0A, 0x09, 0x0C, 0};
        constexpr RGBQUAD GUNMETAL{0x39, 0x35, 0x2C, 0};
        constexpr RGBQUAD MIDNIGHT{0x17, 0x1B, 0x2B, 0};
        constexpr RGBQUAD CHARCOAL{0x2C, 0x28, 0x34, 0};
        constexpr RGBQUAD DARK_SLATE_GREY{0x3C, 0x38, 0x25, 0};
        constexpr RGBQUAD OIL{0x31, 0x31, 0x3B, 0};
        constexpr RGBQUAD BLACK_CAT{0x39, 0x38, 0x41, 0};
        constexpr RGBQUAD IRIDIUM{0x3A, 0x3C, 0x3D, 0};
        constexpr RGBQUAD BLACK_EEL{0x3F, 0x3E, 0x46, 0};
        constexpr RGBQUAD BLACK_COW{0x46, 0x46, 0x4C, 0};
        constexpr RGBQUAD GRAY_WOLF{0x4B, 0x4A, 0x50, 0};
        constexpr RGBQUAD VAMPIRE_GRAY{0x51, 0x50, 0x56, 0};
        constexpr RGBQUAD GRAY_DOLPHIN{0x58, 0x58, 0x5C, 0};
        constexpr RGBQUAD CARBON_GRAY{0x5D, 0x5D, 0x62, 0};
        constexpr RGBQUAD ASH_GRAY{0x62, 0x63, 0x66, 0};
        constexpr RGBQUAD CLOUDY_GRAY{0x68, 0x69, 0x6D, 0};
        constexpr RGBQUAD SMOKEY_GRAY{0x6D, 0x6E, 0x72, 0};
        constexpr RGBQUAD GRAY{0x6E, 0x6F, 0x73, 0};
        constexpr RGBQUAD GRANITE{0x7C, 0x7E, 0x83, 0};
        constexpr RGBQUAD BATTLESHIP_GRAY{0x82, 0x84, 0x84, 0};
        constexpr RGBQUAD GRAY_CLOUD{0xB4, 0xB6, 0xB6, 0};
        constexpr RGBQUAD GRAY_GOOSE{0xCE, 0xD0, 0xD1, 0};
        constexpr RGBQUAD PLATINUM{0xE2, 0xE4, 0xE5, 0};
        constexpr RGBQUAD METALLIC_SILVER{0xCC, 0xC6, 0xBC, 0};
        constexpr RGBQUAD BLUE_GRAY{0xC7, 0xAF, 0x98, 0};
        constexpr RGBQUAD LIGHT_SLATE_GRAY{0x8D, 0x7B, 0x6D, 0};
        constexpr RGBQUAD SLATE_GRAY{0x83, 0x73, 0x65, 0};
        constexpr RGBQUAD JET_GRAY{0x7E, 0x6D, 0x61, 0};
        constexpr RGBQUAD MIST_BLUE{0x7E, 0x6D, 0x64, 0};
        constexpr RGBQUAD MARBLE_BLUE{0x7E, 0x6D, 0x56, 0};
        constexpr RGBQUAD SLATE_BLUE{0xA1, 0x7C, 0x73, 0};
        constexpr RGBQUAD STEEL_BLUE{0xA0, 0x63, 0x48, 0};
        constexpr RGBQUAD BLUE_JAY{0x7E, 0x54, 0x2B, 0};
        constexpr RGBQUAD DARK_SLATE_BLUE{0x56, 0x38, 0x2B, 0};
        constexpr RGBQUAD MIDNIGHT_BLUE{0x54, 0x1B, 0x15, 0};
        constexpr RGBQUAD NAVY_BLUE{0x80, 0x00, 0x00, 0};
        constexpr RGBQUAD BLUE_WHALE{0x7E, 0x2D, 0x34, 0};
        constexpr RGBQUAD LAPIS_BLUE{0x7E, 0x31, 0x15, 0};
        constexpr RGBQUAD DENIM_DARK_BLUE{0x8D, 0x1B, 0x15, 0};
        constexpr RGBQUAD EARTH_BLUE{0xA0, 0x00, 0x00, 0};
        constexpr RGBQUAD COBALT_BLUE{0xC2, 0x20, 0x00, 0};
        constexpr RGBQUAD BLUEBERRY_BLUE{0xC2, 0x41, 0x00, 0};
        constexpr RGBQUAD SAPPHIRE_BLUE{0xC7, 0x54, 0x25, 0};
        constexpr RGBQUAD BLUE_EYES{0xC7, 0x69, 0x15, 0};
        constexpr RGBQUAD ROYAL_BLUE{0xDE, 0x60, 0x2B, 0};
        constexpr RGBQUAD BLUE_ORCHID{0xFC, 0x45, 0x1F, 0};
        constexpr RGBQUAD BLUE_LOTUS{0xEC, 0x60, 0x69, 0};
        constexpr RGBQUAD LIGHT_SLATE_BLUE{0xFF, 0x6A, 0x73, 0};
        constexpr RGBQUAD WINDOWS_BLUE{0xC7, 0x7E, 0x35, 0};
        constexpr RGBQUAD GLACIAL_BLUE_ICE{0xC1, 0x8B, 0x36, 0};
        constexpr RGBQUAD SILK_BLUE{0xC7, 0x8A, 0x48, 0};
        constexpr RGBQUAD BLUE_IVY{0xC7, 0x90, 0x30, 0};
        constexpr RGBQUAD BLUE_KOI{0xC7, 0x9E, 0x65, 0};
        constexpr RGBQUAD COLUMBIA_BLUE{0xC7, 0xAF, 0x87, 0};
        constexpr RGBQUAD BABY_BLUE{0xC7, 0xB9, 0x95, 0};
        constexpr RGBQUAD LIGHT_STEEL_BLUE{0xCE, 0x8F, 0x72, 0};
        constexpr RGBQUAD OCEAN_BLUE{0xEC, 0x65, 0x2B, 0};
        constexpr RGBQUAD BLUE_RIBBON{0xFF, 0x6E, 0x30, 0};
        constexpr RGBQUAD BLUE_DRESS{0xEC, 0x7D, 0x15, 0};
        constexpr RGBQUAD DODGER_BLUE{0xFF, 0x89, 0x15, 0};
        constexpr RGBQUAD CORNFLOWER_BLUE{0xED, 0x95, 0x64, 0};
        constexpr RGBQUAD SKY_BLUE{0xFF, 0x98, 0x66, 0};
        constexpr RGBQUAD BUTTERFLY_BLUE{0xEC, 0xAC, 0x38, 0};
        constexpr RGBQUAD ICEBERG{0xEC, 0xA5, 0x56, 0};
        constexpr RGBQUAD CRYSTAL_BLUE{0xFF, 0xB3, 0x5C, 0};
        constexpr RGBQUAD DEEP_SKY_BLUE{0xFF, 0xB9, 0x3B, 0};
        constexpr RGBQUAD DENIM_BLUE{0xEC, 0xBA, 0x79, 0};
        constexpr RGBQUAD LIGHT_SKY_BLUE{0xFA, 0xCA, 0x82, 0};
        constexpr RGBQUAD DAY_SKY_BLUE{0xFF, 0xCA, 0x82, 0};
        constexpr RGBQUAD JEANS_BLUE{0xEC, 0xCF, 0xA0, 0};
        constexpr RGBQUAD BLUE_ANGEL{0xEC, 0xCE, 0xB7, 0};
        constexpr RGBQUAD PASTEL_BLUE{0xEC, 0xCF, 0xB4, 0};
        constexpr RGBQUAD SEA_BLUE{0xFF, 0xDF, 0xC2, 0};
        constexpr RGBQUAD POWDER_BLUE{0xFF, 0xDE, 0xC6, 0};
        constexpr RGBQUAD CORAL_BLUE{0xEC, 0xDC, 0xAF, 0};
        constexpr RGBQUAD LIGHT_BLUE{0xFF, 0xDF, 0xAD, 0};
        constexpr RGBQUAD ROBIN_EGG_BLUE{0xFF, 0xED, 0xBD, 0};
        constexpr RGBQUAD PALE_BLUE_LILY{0xEC, 0xEC, 0xCF, 0};
        constexpr RGBQUAD LIGHT_CYAN{0xFF, 0xFF, 0xE0, 0};
        constexpr RGBQUAD WATER{0xFA, 0xF4, 0xEB, 0};
        constexpr RGBQUAD ALICEBLUE{0xFF, 0xF8, 0xF0, 0};
        constexpr RGBQUAD AZURE{0xFF, 0xFF, 0xF0, 0};
        constexpr RGBQUAD LIGHT_SLATE{0xFF, 0xFF, 0xCC, 0};
        constexpr RGBQUAD LIGHT_AQUAMARINE{0xE8, 0xFF, 0x93, 0};
        constexpr RGBQUAD ELECTRIC_BLUE{0xFF, 0xFE, 0x9A, 0};
        constexpr RGBQUAD AQUAMARINE{0xD4, 0xFF, 0x7F, 0};
        constexpr RGBQUAD CYAN_OR_AQUA{0xFF, 0xFF, 0x00, 0};
        constexpr RGBQUAD TRON_BLUE{0xFE, 0xFD, 0x7D, 0};
        constexpr RGBQUAD BLUE_ZIRCON{0xFF, 0xFE, 0x57, 0};
        constexpr RGBQUAD BLUE_LAGOON{0xEC, 0xEB, 0x8E, 0};
        constexpr RGBQUAD CELESTE{0xEC, 0xEB, 0x50, 0};
        constexpr RGBQUAD BLUE_DIAMOND{0xEC, 0xE2, 0x4E, 0};
        constexpr RGBQUAD TIFFANY_BLUE{0xD0, 0xD8, 0x81, 0};
        constexpr RGBQUAD CYAN_OPAQUE{0xC7, 0xC7, 0x92, 0};
        constexpr RGBQUAD BLUE_HOSTA{0xC7, 0xBF, 0x77, 0};
        constexpr RGBQUAD NORTHERN_LIGHTS_BLUE{0xC7, 0xC7, 0x78, 0};
        constexpr RGBQUAD MEDIUM_TURQUOISE{0xCD, 0xCC, 0x48, 0};
        constexpr RGBQUAD TURQUOISE{0xDB, 0xC6, 0x43, 0};
        constexpr RGBQUAD JELLYFISH{0xC7, 0xC7, 0x46, 0};
        constexpr RGBQUAD BLUE_GREEN{0xB5, 0xCC, 0x7B, 0};
        constexpr RGBQUAD MACAW_BLUE_GREEN{0xC7, 0xBF, 0x43, 0};
        constexpr RGBQUAD LIGHT_SEA_GREEN{0x9F, 0xA9, 0x3E, 0};
        constexpr RGBQUAD DARK_TURQUOISE{0x9C, 0x9C, 0x3B, 0};
        constexpr RGBQUAD SEA_TURTLE_GREEN{0x80, 0x8D, 0x43, 0};
        constexpr RGBQUAD MEDIUM_AQUAMARINE{0x81, 0x87, 0x34, 0};
        constexpr RGBQUAD GREENISH_BLUE{0x7E, 0x7D, 0x30, 0};
        constexpr RGBQUAD GRAYISH_TURQUOISE{0x7E, 0x7D, 0x5E, 0};
        constexpr RGBQUAD BEETLE_GREEN{0x7E, 0x78, 0x4C, 0};
        constexpr RGBQUAD TEAL{0x80, 0x80, 0x00, 0};
        constexpr RGBQUAD SEA_GREEN{0x75, 0x89, 0x4E, 0};
        constexpr RGBQUAD CAMOUFLAGE_GREEN{0x6B, 0x86, 0x78, 0};
        constexpr RGBQUAD SAGE_GREEN{0x79, 0x8B, 0x84, 0};
        constexpr RGBQUAD HAZEL_GREEN{0x58, 0x7C, 0x61, 0};
        constexpr RGBQUAD VENOM_GREEN{0x00, 0x8C, 0x72, 0};
        constexpr RGBQUAD FERN_GREEN{0x26, 0x7C, 0x66, 0};
        constexpr RGBQUAD DARK_FOREST_GREEN{0x17, 0x41, 0x25, 0};
        constexpr RGBQUAD MEDIUM_SEA_GREEN{0x54, 0x67, 0x30, 0};
        constexpr RGBQUAD MEDIUM_FOREST_GREEN{0x35, 0x72, 0x34, 0};
        constexpr RGBQUAD SEAWEED_GREEN{0x17, 0x7C, 0x43, 0};
        constexpr RGBQUAD PINE_GREEN{0x44, 0x7C, 0x38, 0};
        constexpr RGBQUAD JUNGLE_GREEN{0x2C, 0x7C, 0x34, 0};
        constexpr RGBQUAD SHAMROCK_GREEN{0x17, 0x7C, 0x34, 0};
        constexpr RGBQUAD MEDIUM_SPRING_GREEN{0x17, 0x80, 0x34, 0};
        constexpr RGBQUAD FOREST_GREEN{0x58, 0x92, 0x4E, 0};
        constexpr RGBQUAD GREEN_ONION{0x21, 0xA1, 0x6A, 0};
        constexpr RGBQUAD SPRING_GREEN{0x2C, 0xA0, 0x4A, 0};
        constexpr RGBQUAD LIME_GREEN{0x17, 0xA3, 0x41, 0};
        constexpr RGBQUAD CLOVER_GREEN{0x55, 0xA0, 0x3E, 0};
        constexpr RGBQUAD GREEN_SNAKE{0x3C, 0xBB, 0x6C, 0};
        constexpr RGBQUAD ALIEN_GREEN{0x17, 0xC4, 0x6C, 0};
        constexpr RGBQUAD GREEN_APPLE{0x17, 0xC4, 0x4C, 0};
        constexpr RGBQUAD YELLOW_GREEN{0x17, 0xD0, 0x52, 0};
        constexpr RGBQUAD KELLY_GREEN{0x52, 0xC5, 0x4C, 0};
        constexpr RGBQUAD ZOMBIE_GREEN{0x71, 0xC5, 0x54, 0};
        constexpr RGBQUAD FROG_GREEN{0x8E, 0xC6, 0x99, 0};
        constexpr RGBQUAD GREEN_PEAS{0x5C, 0xC3, 0x89, 0};
        constexpr RGBQUAD DOLLAR_BILL_GREEN{0x65, 0xBB, 0x85, 0};
        constexpr RGBQUAD DARK_SEA_GREEN{0x81, 0xB3, 0x8B, 0};
        constexpr RGBQUAD IGUANA_GREEN{0x71, 0xB0, 0x9C, 0};
        constexpr RGBQUAD AVOCADO_GREEN{0x48, 0xC2, 0xB2, 0};
        constexpr RGBQUAD PISTACHIO_GREEN{0x09, 0xC2, 0x9D, 0};
        constexpr RGBQUAD SALAD_GREEN{0x35, 0xC9, 0xA1, 0};
        constexpr RGBQUAD HUMMINGBIRD_GREEN{0x17, 0xE8, 0x7F, 0};
        constexpr RGBQUAD NEBULA_GREEN{0x17, 0xE8, 0x59, 0};
        constexpr RGBQUAD STOPLIGHT_GO_GREEN{0x64, 0xE9, 0x57, 0};
        constexpr RGBQUAD ALGAE_GREEN{0x86, 0xE9, 0x64, 0};
        constexpr RGBQUAD JADE_GREEN{0x6E, 0xFB, 0x5E, 0};
        constexpr RGBQUAD GREEN{0x00, 0xFF, 0x00, 0};
        constexpr RGBQUAD EMERALD_GREEN{0x17, 0xFB, 0x5F, 0};
        constexpr RGBQUAD LAWN_GREEN{0x17, 0xF7, 0x87, 0};
        constexpr RGBQUAD CHARTREUSE{0x17, 0xFB, 0x8A, 0};
        constexpr RGBQUAD DRAGON_GREEN{0x92, 0xFB, 0x6A, 0};
        constexpr RGBQUAD MINT_GREEN{0x98, 0xFF, 0x98, 0};
        constexpr RGBQUAD GREEN_THUMB{0xAA, 0xEA, 0xB5, 0};
        constexpr RGBQUAD LIGHT_JADE{0xB8, 0xFD, 0xC3, 0};
        constexpr RGBQUAD TEA_GREEN{0x5D, 0xFB, 0xCC, 0};
        constexpr RGBQUAD GREEN_YELLOW{0x17, 0xFB, 0xB1, 0};
        constexpr RGBQUAD SLIME_GREEN{0x54, 0xE9, 0xBC, 0};
        constexpr RGBQUAD GOLDENROD{0x74, 0xDA, 0xED, 0};
        constexpr RGBQUAD HARVEST_GOLD{0x75, 0xE2, 0xED, 0};
        constexpr RGBQUAD SUN_YELLOW{0x7C, 0xE8, 0xFF, 0};
        constexpr RGBQUAD YELLOW{0x00, 0xFF, 0xFF, 0};
        constexpr RGBQUAD CORN_YELLOW{0x80, 0xF3, 0xFF, 0};
        constexpr RGBQUAD PARCHMENT{0xC2, 0xFF, 0xFF, 0};
        constexpr RGBQUAD CREAM{0xCC, 0xFF, 0xFF, 0};
        constexpr RGBQUAD LEMON_CHIFFON{0xC6, 0xF8, 0xFF, 0};
        constexpr RGBQUAD CORNSILK{0xDC, 0xF8, 0xFF, 0};
        constexpr RGBQUAD BEIGE{0xDC, 0xF5, 0xF5, 0};
        constexpr RGBQUAD BLONDE{0xD9, 0xF6, 0xFB, 0};
        constexpr RGBQUAD ANTIQUEWHITE{0xD7, 0xEB, 0xFA, 0};
        constexpr RGBQUAD CHAMPAGNE{0xCE, 0xE7, 0xF7, 0};
        constexpr RGBQUAD BLANCHEDALMOND{0xCD, 0xEB, 0xFF, 0};
        constexpr RGBQUAD VANILLA{0xAB, 0xE5, 0xF3, 0};
        constexpr RGBQUAD TAN_BROWN{0xB6, 0xE5, 0xEC, 0};
        constexpr RGBQUAD PEACH{0xB4, 0xE5, 0xFF, 0};
        constexpr RGBQUAD MUSTARD{0x58, 0xDB, 0xFF, 0};
        constexpr RGBQUAD RUBBER_DUCKY_YELLOW{0x01, 0xD8, 0xFF, 0};
        constexpr RGBQUAD BRIGHT_GOLD{0x17, 0xD0, 0xFD, 0};
        constexpr RGBQUAD GOLDEN_BROWN{0x17, 0xC1, 0xEA, 0};
        constexpr RGBQUAD MACARONI_AND_CHEESE{0x66, 0xBB, 0xF2, 0};
        constexpr RGBQUAD SAFFRON{0x17, 0xB9, 0xFB, 0};
        constexpr RGBQUAD BEER{0x17, 0xB1, 0xFB, 0};
        constexpr RGBQUAD CANTALOUPE{0x2F, 0xA6, 0xFF, 0};
        constexpr RGBQUAD BEE_YELLOW{0x17, 0xAB, 0xE9, 0};
        constexpr RGBQUAD BROWN_SUGAR{0x6F, 0xA7, 0xE2, 0};
        constexpr RGBQUAD BURLYWOOD{0x87, 0xB8, 0xDE, 0};
        constexpr RGBQUAD DEEP_PEACH{0xA4, 0xCB, 0xFF, 0};
        constexpr RGBQUAD GINGER_BROWN{0x62, 0xBE, 0xC9, 0};
        constexpr RGBQUAD SCHOOL_BUS_YELLOW{0x17, 0xA3, 0xE8, 0};
        constexpr RGBQUAD SANDY_BROWN{0x4D, 0x9A, 0xEE, 0};
        constexpr RGBQUAD FALL_LEAF_BROWN{0x60, 0xB5, 0xC8, 0};
        constexpr RGBQUAD ORANGE_GOLD{0x17, 0xA0, 0xD4, 0};
        constexpr RGBQUAD SAND{0x80, 0xB2, 0xC2, 0};
        constexpr RGBQUAD COOKIE_BROWN{0x17, 0xA3, 0xC7, 0};
        constexpr RGBQUAD CARAMEL{0x17, 0x8E, 0xC6, 0};
        constexpr RGBQUAD BRASS{0x42, 0xA6, 0xB5, 0};
        constexpr RGBQUAD KHAKI{0x6E, 0xA9, 0xAD, 0};
        constexpr RGBQUAD CAMEL_BROWN{0x6B, 0x9A, 0xC1, 0};
        constexpr RGBQUAD BRONZE{0x32, 0x7F, 0xCD, 0};
        constexpr RGBQUAD TIGER_ORANGE{0x41, 0x81, 0xC8, 0};
        constexpr RGBQUAD CINNAMON{0x17, 0x89, 0xC5, 0};
        constexpr RGBQUAD BULLET_SHELL{0x60, 0x9B, 0xAF, 0};
        constexpr RGBQUAD DARK_GOLDENROD{0x17, 0x78, 0xAF, 0};
        constexpr RGBQUAD COPPER{0x33, 0x73, 0xB8, 0};
        constexpr RGBQUAD WOOD{0x33, 0x6F, 0x96, 0};
        constexpr RGBQUAD OAK_BROWN{0x17, 0x65, 0x80, 0};
        constexpr RGBQUAD MOCCASIN{0x39, 0x78, 0x82, 0};
        constexpr RGBQUAD ARMY_BROWN{0x60, 0x7B, 0x82, 0};
        constexpr RGBQUAD SANDSTONE{0x5F, 0x6D, 0x78, 0};
        constexpr RGBQUAD MOCHA{0x26, 0x3D, 0x49, 0};
        constexpr RGBQUAD TAUPE{0x32, 0x3C, 0x48, 0};
        constexpr RGBQUAD COFFEE{0x37, 0x4E, 0x6F, 0};
        constexpr RGBQUAD BROWN_BEAR{0x3B, 0x5C, 0x83, 0};
        constexpr RGBQUAD RED_DIRT{0x17, 0x52, 0x7F, 0};
        constexpr RGBQUAD SEPIA{0x2C, 0x46, 0x7F, 0};
        constexpr RGBQUAD ORANGE_SALMON{0x51, 0x74, 0xC4, 0};
        constexpr RGBQUAD RUST{0x41, 0x62, 0xC3, 0};
        constexpr RGBQUAD RED_FOX{0x17, 0x58, 0xC3, 0};
        constexpr RGBQUAD CHOCOLATE{0x17, 0x5A, 0xC8, 0};
        constexpr RGBQUAD SEDONA{0x00, 0x66, 0xCC, 0};
        constexpr RGBQUAD PAPAYA_ORANGE{0x17, 0x67, 0xE5, 0};
        constexpr RGBQUAD HALLOWEEN_ORANGE{0x2C, 0x6C, 0xE6, 0};
        constexpr RGBQUAD PUMPKIN_ORANGE{0x17, 0x72, 0xF8, 0};
        constexpr RGBQUAD CONSTRUCTION_CONE_ORANGE{0x31, 0x74, 0xF8, 0};
        constexpr RGBQUAD SUNRISE_ORANGE{0x51, 0x74, 0xE6, 0};
        constexpr RGBQUAD MANGO_ORANGE{0x40, 0x80, 0xFF, 0};
        constexpr RGBQUAD DARK_ORANGE{0x17, 0x80, 0xF8, 0};
        constexpr RGBQUAD CORAL{0x50, 0x7F, 0xFF, 0};
        constexpr RGBQUAD BASKET_BALL_ORANGE{0x58, 0x81, 0xF8, 0};
        constexpr RGBQUAD LIGHT_SALMON{0x6B, 0x96, 0xF9, 0};
        constexpr RGBQUAD TANGERINE{0x61, 0x8A, 0xE7, 0};
        constexpr RGBQUAD DARK_SALMON{0x6B, 0x8B, 0xE1, 0};
        constexpr RGBQUAD LIGHT_CORAL{0x71, 0x74, 0xE7, 0};
        constexpr RGBQUAD BEAN_RED{0x59, 0x5D, 0xF7, 0};
        constexpr RGBQUAD VALENTINE_RED{0x51, 0x54, 0xE5, 0};
        constexpr RGBQUAD SHOCKING_ORANGE{0x3C, 0x5B, 0xE5, 0};
        constexpr RGBQUAD RED{0x00, 0x00, 0xFF, 0};
        constexpr RGBQUAD SCARLET{0x00, 0x24, 0xFF, 0};
        constexpr RGBQUAD RUBY_RED{0x17, 0x22, 0xF6, 0};
        constexpr RGBQUAD FERRARI_RED{0x1A, 0x0D, 0xF7, 0};
        constexpr RGBQUAD FIRE_ENGINE_RED{0x17, 0x28, 0xF6, 0};
        constexpr RGBQUAD LAVA_RED{0x17, 0x22, 0xE4, 0};
        constexpr RGBQUAD LOVE_RED{0x17, 0x1B, 0xE4, 0};
        constexpr RGBQUAD GRAPEFRUIT{0x1F, 0x38, 0xDC, 0};
        constexpr RGBQUAD CHESTNUT_RED{0x2C, 0x4A, 0xC3, 0};
        constexpr RGBQUAD CHERRY_RED{0x41, 0x46, 0xC2, 0};
        constexpr RGBQUAD MAHOGANY{0x00, 0x40, 0xC0, 0};
        constexpr RGBQUAD CHILLI_PEPPER{0x17, 0x1B, 0xC1, 0};
        constexpr RGBQUAD CRANBERRY{0x0F, 0x00, 0x9F, 0};
        constexpr RGBQUAD RED_WINE{0x12, 0x00, 0x99, 0};
        constexpr RGBQUAD BURGUNDY{0x1A, 0x00, 0x8C, 0};
        constexpr RGBQUAD CHESTNUT{0x35, 0x45, 0x95, 0};
        constexpr RGBQUAD BLOOD_RED{0x17, 0x35, 0x7E, 0};
        constexpr RGBQUAD SIENNA{0x17, 0x41, 0x8A, 0};
        constexpr RGBQUAD SANGRIA{0x17, 0x38, 0x7E, 0};
        constexpr RGBQUAD FIREBRICK{0x17, 0x05, 0x80, 0};
        constexpr RGBQUAD MAROON{0x41, 0x05, 0x81, 0};
        constexpr RGBQUAD PLUM_PIE{0x41, 0x05, 0x7D, 0};
        constexpr RGBQUAD VELVET_MAROON{0x4D, 0x35, 0x7E, 0};
        constexpr RGBQUAD PLUM_VELVET{0x52, 0x05, 0x7D, 0};
        constexpr RGBQUAD ROSY_FINCH{0x52, 0x4E, 0x7F, 0};
        constexpr RGBQUAD PUCE{0x58, 0x5A, 0x7F, 0};
        constexpr RGBQUAD DULL_PURPLE{0x5D, 0x52, 0x7F, 0};
        constexpr RGBQUAD ROSY_BROWN{0x81, 0x84, 0xB3, 0};
        constexpr RGBQUAD KHAKI_ROSE{0x8E, 0x90, 0xC5, 0};
        constexpr RGBQUAD PINK_BOW{0x89, 0x81, 0xC4, 0};
        constexpr RGBQUAD LIPSTICK_PINK{0x93, 0x87, 0xC4, 0};
        constexpr RGBQUAD ROSE{0xAA, 0xAD, 0xE8, 0};
        constexpr RGBQUAD ROSE_GOLD{0xC0, 0xC5, 0xEC, 0};
        constexpr RGBQUAD DESERT_SAND{0xAF, 0xC9, 0xED, 0};
        constexpr RGBQUAD PIG_PINK{0xE4, 0xD7, 0xFD, 0};
        constexpr RGBQUAD COTTON_CANDY{0xFF, 0xDF, 0xFC, 0};
        constexpr RGBQUAD PINK_BUBBLE_GUM{0xDD, 0xDF, 0xFF, 0};
        constexpr RGBQUAD MISTY_ROSE{0xB9, 0xBB, 0xFB, 0};
        constexpr RGBQUAD PINK{0xBE, 0xAF, 0xFA, 0};
        constexpr RGBQUAD LIGHT_PINK{0xBA, 0xAF, 0xFA, 0};
        constexpr RGBQUAD FLAMINGO_PINK{0xB0, 0xA7, 0xF9, 0};
        constexpr RGBQUAD PINK_ROSE{0xB0, 0xA1, 0xE7, 0};
        constexpr RGBQUAD PINK_DAISY{0xA3, 0x99, 0xE7, 0};
        constexpr RGBQUAD CADILLAC_PINK{0xAE, 0x8A, 0xE3, 0};
        constexpr RGBQUAD CARNATION_PINK{0xA1, 0x78, 0xF7, 0};
        constexpr RGBQUAD BLUSH_RED{0x94, 0x6E, 0xE5, 0};
        constexpr RGBQUAD HOT_PINK{0xAB, 0x60, 0xF6, 0};
        constexpr RGBQUAD WATERMELON_PINK{0x85, 0x6C, 0xFC, 0};
        constexpr RGBQUAD VIOLET_RED{0x8A, 0x35, 0xF6, 0};
        constexpr RGBQUAD DEEP_PINK{0x87, 0x28, 0xF5, 0};
        constexpr RGBQUAD PINK_CUPCAKE{0x9D, 0x5E, 0xE4, 0};
        constexpr RGBQUAD PINK_LEMONADE{0x7C, 0x28, 0xE4, 0};
        constexpr RGBQUAD NEON_PINK{0xAA, 0x35, 0xF5, 0};
        constexpr RGBQUAD MAGENTA{0xFF, 0x00, 0xFF, 0};
        constexpr RGBQUAD DIMORPHOTHECA_MAGENTA{0x9D, 0x31, 0xE3, 0};
        constexpr RGBQUAD BRIGHT_NEON_PINK{0xFF, 0x33, 0xF4, 0};
        constexpr RGBQUAD PALE_VIOLET_RED{0x87, 0x65, 0xD1, 0};
        constexpr RGBQUAD TULIP_PINK{0x7C, 0x5A, 0xC2, 0};
        constexpr RGBQUAD MEDIUM_VIOLET_RED{0x6B, 0x22, 0xCA, 0};
        constexpr RGBQUAD ROGUE_PINK{0x69, 0x28, 0xC1, 0};
        constexpr RGBQUAD BURNT_PINK{0x67, 0x22, 0xC1, 0};
        constexpr RGBQUAD BASHFUL_PINK{0x83, 0x52, 0xC2, 0};
        constexpr RGBQUAD DARK_CARNATION_PINK{0x83, 0x22, 0xC1, 0};
        constexpr RGBQUAD PLUM{0x8F, 0x3B, 0xB9, 0};
        constexpr RGBQUAD VIOLA_PURPLE{0x7E, 0x58, 0x7E, 0};
        constexpr RGBQUAD PURPLE_IRIS{0x7E, 0x1B, 0x57, 0};
        constexpr RGBQUAD PLUM_PURPLE{0x59, 0x37, 0x58, 0};
        constexpr RGBQUAD INDIGO{0x82, 0x00, 0x4B, 0};
        constexpr RGBQUAD PURPLE_MONSTER{0x7E, 0x1B, 0x46, 0};
        constexpr RGBQUAD PURPLE_HAZE{0x7E, 0x38, 0x4E, 0};
        constexpr RGBQUAD EGGPLANT{0x51, 0x40, 0x61, 0};
        constexpr RGBQUAD GRAPE{0x80, 0x5A, 0x5E, 0};
        constexpr RGBQUAD PURPLE_JAM{0x7E, 0x28, 0x6A, 0};
        constexpr RGBQUAD DARK_ORCHID{0x7E, 0x1B, 0x7D, 0};
        constexpr RGBQUAD PURPLE_FLOWER{0xC7, 0x4A, 0xA7, 0};
        constexpr RGBQUAD MEDIUM_ORCHID{0xB5, 0x48, 0xB0, 0};
        constexpr RGBQUAD PURPLE_AMETHYST{0xC7, 0x2D, 0x6C, 0};
        constexpr RGBQUAD DARK_VIOLET{0xCE, 0x2D, 0x84, 0};
        constexpr RGBQUAD VIOLET{0xC9, 0x38, 0x8D, 0};
        constexpr RGBQUAD PURPLE_SAGE_BUSH{0xC7, 0x5D, 0x7A, 0};
        constexpr RGBQUAD LOVELY_PURPLE{0xEC, 0x38, 0x7F, 0};
        constexpr RGBQUAD PURPLE{0xEF, 0x35, 0x8E, 0};
        constexpr RGBQUAD AZTECH_PURPLE{0xFF, 0x3B, 0x89, 0};
        constexpr RGBQUAD MEDIUM_PURPLE{0xD7, 0x67, 0x84, 0};
        constexpr RGBQUAD JASMINE_PURPLE{0xEC, 0x3B, 0xA2, 0};
        constexpr RGBQUAD PURPLE_DAFFODIL{0xFF, 0x41, 0xB0, 0};
        constexpr RGBQUAD TYRIAN_PURPLE{0xEC, 0x5A, 0xC4, 0};
        constexpr RGBQUAD CROCUS_PURPLE{0xEC, 0x72, 0x91, 0};
        constexpr RGBQUAD PURPLE_MIMOSA{0xFF, 0x7B, 0x9E, 0};
        constexpr RGBQUAD HELIOTROPE_PURPLE{0xFF, 0x62, 0xD4, 0};
        constexpr RGBQUAD CRIMSON{0xEC, 0x38, 0xE2, 0};
        constexpr RGBQUAD PURPLE_DRAGON{0xC7, 0x8E, 0xC3, 0};
        constexpr RGBQUAD LILAC{0xC8, 0xA2, 0xC8, 0};
        constexpr RGBQUAD BLUSH_PINK{0xEC, 0xA9, 0xE6, 0};
        constexpr RGBQUAD MAUVE{0xFF, 0xB0, 0xE0, 0};
        constexpr RGBQUAD WISTERIA_PURPLE{0xC7, 0xAE, 0xC6, 0};
        constexpr RGBQUAD BLOSSOM_PINK{0xFF, 0xB7, 0xF9, 0};
        constexpr RGBQUAD THISTLE{0xD3, 0xB9, 0xD2, 0};
        constexpr RGBQUAD PERIWINKLE{0xEC, 0xCF, 0xE9, 0};
        constexpr RGBQUAD LAVENDER_PINOCCHIO{0xE2, 0xDD, 0xEB, 0};
        constexpr RGBQUAD LAVENDER_BLUE{0xFA, 0xE4, 0xE3, 0};
        constexpr RGBQUAD PEARL{0xF4, 0xEE, 0xFD, 0};
        constexpr RGBQUAD SEASHELL{0xEE, 0xF5, 0xFF, 0};
        constexpr RGBQUAD MILK_WHITE{0xFF, 0xFC, 0xFE, 0};
        constexpr RGBQUAD WHITE{0xFF, 0xFF, 0xFF, 0};
    }

    inline LONG diffSq(RGBQUAD color1, RGBQUAD color2)
    {
        SHORT redDiff = color1.rgbRed - color2.rgbRed;
        SHORT greenDiff = color1.rgbGreen - color2.rgbGreen;
        SHORT blueDiff = color1.rgbBlue - color2.rgbBlue;
        return redDiff * redDiff + greenDiff * greenDiff + blueDiff * blueDiff;
    }

    inline DOUBLE diff(RGBQUAD color1, RGBQUAD color2)
    {
        return std::sqrt(diffSq(color1, color2));
    }

    inline BOOL diffLT(RGBQUAD color1, RGBQUAD color2, DOUBLE threshold)
    {
        return diffSq(color1, color2) < threshold * threshold;
    }

    inline BOOL diffLE(RGBQUAD color1, RGBQUAD color2, DOUBLE threshold)
    {
        return diffSq(color1, color2) <= threshold * threshold;
    }

    inline BOOL diffGT(RGBQUAD color1, RGBQUAD color2, DOUBLE threshold)
    {
        return diffSq(color1, color2) > threshold * threshold;
    }

    inline BOOL diffGE(RGBQUAD color1, RGBQUAD color2, DOUBLE threshold)
    {
        return diffSq(color1, color2) >= threshold * threshold;
    }

    inline BOOL equal(RGBQUAD color1, RGBQUAD color2)
    {
        return !diffSq(color1, color2);
    }
}