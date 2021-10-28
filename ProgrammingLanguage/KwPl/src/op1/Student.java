package op1;

abstract class Student implements Observer {
    protected Subject lecture;
    protected String name;

    public Student(Subject lecture, String name) {
        lecture.registerObserver(this);
        this.lecture = lecture;
        this.name = name;
    }

    public boolean dropLecture() {
        if (lecture == null)
            return false;
        else {
            lecture.reomverObserver(this);
            lecture = null;
            return true;
        }
    }

    public abstract void readPost();
}
