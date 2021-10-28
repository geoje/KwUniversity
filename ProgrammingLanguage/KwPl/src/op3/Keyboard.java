package op3;

import java.util.ArrayList;

class Keyboard implements Subject {
    ArrayList<Observer> observers;
    KeyboardEvent keyevent;

    public Keyboard() {
        observers = new ArrayList<>();
    }

    @Override
    public void registerObserver(Observer o) {
        observers.add(o);
    }

    @Override
    public void reomveObserver(Observer o) {
        observers.remove(o);
    }

    @Override
    public void notifyObserver() {
        observers.forEach(o -> o.update(keyevent));
    }

    public void performKeyDown(char key) {
        keyevent = new KeyboardEvent(key);
        System.out.println(String.format("\n⌨️  키보드 '%c' 누름.", key));
        notifyObserver();
    }
}
