package op1;

class StudentBob extends Student {
    private String title;

    public StudentBob(Subject lecture, String name) {
        super(lecture, name);
    }

    @Override
    public void update(Post post) {
        title = post.title;
        readPost();
    }

    @Override
    public void readPost() {
        System.out.println(String.format("[%s] 제목 (%s...) 대충 봤어요~", name, title.split(" ")[0]));
    }
}
