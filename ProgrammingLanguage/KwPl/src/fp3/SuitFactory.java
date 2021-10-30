package fp3;

abstract class SuitFactory {
    public abstract Suit createSuit(String type);
}

class TypeSuitFactory extends SuitFactory {
    @Override
    public Suit createSuit(String type) {
        switch (type) {
        case "space":
            return new SpaceSuit();
        case "hydro":
            return new HydroSuit();
        case "stealth":
            return new StealthSuit();
        case "combat":
            return new CombatSuit();
        }
        return null;
    }
}