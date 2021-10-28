package op1;

import java.util.ArrayList;

class Lecture implements Subject {
    private Post recentPost;
    private ArrayList<Observer> students;

    public Lecture() {
        students = new ArrayList<>();
    }

    @Override
    public void registerObserver(Observer o) {
        students.add(o);
    }

    @Override
    public void reomveObserver(Observer o) {
        students.remove(o);
    }

    @Override
    public void notifyObserver() {
        students.forEach(o -> o.update(recentPost));
    }

    public void postAdded() {
        notifyObserver();
    }

    public void addNewPost(String title, String content) {
        recentPost = new Post(title, content);
        System.out.println(String.format("<게시글 등록>\n제목: %s\n내용: %s", title, content));
        postAdded();
        System.out.println();
    }
}
