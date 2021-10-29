package fp1;

class MrPizzaStore extends PizzaStore {
    @Override
    public Pizza createPizza(String pizzaType) {
        System.out.println("🍕  미스터 피자에서 피자를 만듭니다~  (" + pizzaType + ")");
        switch (pizzaType.replaceAll(" ", "")) {
            case "포슬포슬감자":
                return new MrSoftPotatoPizza();
            case "쉬림프골드":
                return new MrShrimpGoldPizza();
            case "페퍼로니":
                return new MrPepperoniPizza();
        }
        return null;
    }
}


class MrSoftPotatoPizza extends Pizza {
    public MrSoftPotatoPizza() {
        price = 17900;
    }
}


class MrShrimpGoldPizza extends Pizza {
    public MrShrimpGoldPizza() {
        price = 27900;
    }
}


class MrPepperoniPizza extends Pizza {
    public MrPepperoniPizza() {
        price = 16500;
    }
}
