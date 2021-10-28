package op2;

class Main {
    public static void main(String[] args) {
        // 가게 오픈
        Store store = new Store("수육국밥집 광운대점");

        // 손님 입장 및 웨이팅 시작
        Customer alice = new Customer(store, "Alice");
        Customer bob = new Customer(store, "Bob");

        // 제일 앞 손님 받기
        store.enterCustomer();

        // 새로운 손님이 2명 더 왔다.
        Customer mallory = new Customer(store, "Mallory");
        Customer jack = new Customer(store, "Jack");

        // 조금만 더 기다리면 되는데 그걸 못참아서 제일 앞 손님 떠나버리고
        bob.leave();

        // 제일 앞 손님 2번 받기
        store.enterCustomer();
        store.enterCustomer();
    }
}
