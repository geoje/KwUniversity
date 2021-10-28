package op1;

interface Subject {
    public void registerObserver(Observer o);

    public void reomveObserver(Observer o);

    public void notifyObserver();
}
