package sk.tuke.kpi.kp.bejeweled.core;

import java.util.Random;

public class Gem {
    private static final String[] GEM_TYPES = {"AMETHYST", "DIAMOND", "OPAL", "RUBY", "SAPPHIRE", "TOPAZ"};
    private final String gemType;

    private static final String AMETHYST_IMAGE = "/images/amethyst.png";
    private static final String DIAMOND_IMAGE  = "/images/diamond.png";
    private static final String OPAL_IMAGE     = "/images/opal.png";
    private static final String RUBY_IMAGE     = "/images/ruby.png";
    private static final String SAPPHIRE_IMAGE = "/images/sapphire.png";
    private static final String TOPAZ_IMAGE    = "/images/topaz.png";

    public Gem(String gemType) {
        this.gemType = gemType;
    }

    // Select a random gem type
    public static Gem randomGem() {
        Random random = new Random();
        return new Gem(GEM_TYPES[random.nextInt(GEM_TYPES.length)]);
    }

    public String getGemType() {
        return gemType;
    }

    public String getImagePath() {
        switch (gemType) {
            case "AMETHYST":
                return AMETHYST_IMAGE;
            case "DIAMOND":
                return DIAMOND_IMAGE;
            case "OPAL":
                return OPAL_IMAGE;
            case "RUBY":
                return RUBY_IMAGE;
            case "SAPPHIRE":
                return SAPPHIRE_IMAGE;
            case "TOPAZ":
                return TOPAZ_IMAGE;
            default:
                return "/images/default.png";
        }
    }

    @Override
    public String toString() {
        return gemType;
    }
}
