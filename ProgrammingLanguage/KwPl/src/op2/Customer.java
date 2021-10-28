package op2;

class Customer implements Observer {
    String name;
    Store store;
    int order = 0;

    public Customer(Store store, String name) {
        this.store = store;
        this.name = name;
        order = store.registerObserver(this);

        System.out.println(String.format("[%s] 가게 입장하고 웨이팅 시작! 내 앞에 %d명 있군.", name, order));
    }

    @Override
    public void update(int order) {
        if (order >= 0)
            System.out.println(String.format("[%s] 내 앞에 %d명 남았군!", name, order));
        else
            System.out.println(String.format("[%s] 아싸 들어간다!", name));
    }

    public void leave() {
        System.out.println(String.format("[%s] 왜 이렇게 오래 걸려? 여기 안가!", name));
        store.reomveObserver(this);
    }
}
