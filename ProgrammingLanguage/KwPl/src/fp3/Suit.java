package fp3;

abstract class Suit {
    public abstract String getName();
}

class SpaceSuit extends Suit {
    @Override
    public String getName() {
        return "🩲  SpaceSuit";
    }
}

class HydroSuit extends Suit {
    @Override
    public String getName() {
        return "🩳  HydroSuit";
    }
}

class StealthSuit extends Suit {
    @Override
    public String getName() {
        return "👡  StealthSuit";
    }
}

class CombatSuit extends Suit {
    @Override
    public String getName() {
        return "🩱  CombatSuit";
    }
}