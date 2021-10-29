package fp1;

class Main {
    public static void main(String[] args) {
        // 피자 가게 오픈
        PizzaStore mrStore = new MrPizzaStore();
        PizzaStore doStore = new DominoPizzaStore();

        mrStore.orderPizza("포슬포슬감자").showPrice();
        doStore.orderPizza("하와이안슈림프").showPrice();
    }
}
