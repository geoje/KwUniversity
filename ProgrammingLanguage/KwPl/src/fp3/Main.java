package fp3;

public class Main {
    public static void main(String[] args) {
        TypeSuitFactory typeSuitFactory = new TypeSuitFactory();

        Suit suit1 = typeSuitFactory.createSuit("stealth");
        Suit suit2 = typeSuitFactory.createSuit("space");
        Suit suit3 = typeSuitFactory.createSuit("combat");

        System.out.println(suit1.getName());
        System.out.println(suit2.getName());
        System.out.println(suit3.getName());
    }
}
