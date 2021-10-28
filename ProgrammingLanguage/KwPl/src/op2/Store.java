package op2;

import java.util.ArrayList;

class Store implements Subject {
    String title;
    ArrayList<Customer> customers;

    public Store(String title) {
        customers = new ArrayList<>();
        this.title = title;
        System.out.println(title + "(이)가 오픈하였습니다.");
    }

    @Override
    public int registerObserver(Observer o) {
        customers.add((Customer) o);
        return customers.size() - 1;
    }

    @Override
    public void reomveObserver(Observer o) {
        int i = customers.indexOf(o);
        customers.remove(i);
        notifyObserver(i);
    }

    @Override
    public void notifyObserver(int start) {
        for (int i = start; i < customers.size(); i++)
            customers.get(i).update(i);
    }

    public void enterCustomer() {
        System.out.println(String.format("\n[가게] %s 손님 입장하실게요~", customers.get(0).name));
        customers.get(0).update(-1);
        reomveObserver(customers.get(0));
    }
}
