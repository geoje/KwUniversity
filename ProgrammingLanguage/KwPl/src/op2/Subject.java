package op2;

interface Subject {
    public int registerObserver(Observer o);

    public void reomveObserver(Observer o);

    public void notifyObserver(int start);
}
