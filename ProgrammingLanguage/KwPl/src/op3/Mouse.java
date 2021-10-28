package op3;

import java.util.ArrayList;

class Mouse implements Subject {
    ArrayList<Observer> observers;
    MouseEvent mouseevent;

    public Mouse() {
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
        observers.forEach(o -> o.update(mouseevent));
    }

    public void performMouseClick(int x, int y) {
        mouseevent = new MouseEvent(x, y);
        System.out.println(String.format("\n🖱️  마우스 (%d, %d) 누름.", x, y));
        notifyObserver();
    }

}
