package fp1;

class DominoPizzaStore extends PizzaStore {
    @Override
    public Pizza createPizza(String pizzaType) {
        System.out.println("🍕  도미노 피자에서 피자를 만듭니다~  (" + pizzaType + ")");
        switch (pizzaType.replaceAll(" ", "")) {
            case "우리고구마":
                return new DominoGoldPotatoPizza();
            case "하와이안슈림프":
                return new DominoHawaiianShrimpPizza();
            case "포테이토":
                return new DominoPotatoiPizza();
        }
        return null;
    }
}


class DominoGoldPotatoPizza extends Pizza {
    public DominoGoldPotatoPizza() {
        price = 23000;
    }
}


class DominoHawaiianShrimpPizza extends Pizza {
    public DominoHawaiianShrimpPizza() {
        price = 21000;
    }
}


class DominoPotatoiPizza extends Pizza {
    public DominoPotatoiPizza() {
        price = 19000;
    }
}
