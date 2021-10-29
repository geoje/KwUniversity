package fp1;

abstract class PizzaStore {
    public Pizza orderPizza(String pizzaType) {
        System.out.println("\n🏪  배달의민족 주문!  (" + pizzaType + ")");
        return createPizza(pizzaType);
    }

    public abstract Pizza createPizza(String pizzaType);
}
